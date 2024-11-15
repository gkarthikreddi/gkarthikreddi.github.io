+++
title = "TCP/IP"
date = "2024-08-22"
description = "Building TCP/IP Stack in Go"
+++ 

# Why Go?
I wanted to learn Go and the best way to do that is by building something. So, I decided to implement TCP/IP stack in Go. Generally people implement this using 'C', it's a conventional way to doing it but has I decided to try Go I'm building this in Go.

Things I liked about Go:
- You just have to capitalize to export something like functions or members of a struct, everything else stays in the package.
- Returning multiple things of different type from a function, because of this error handling becomes very easy.
- Conversion from array to splice and vice versa.
- It's fast, very fast.

Some constraints in Go:
- There is no pointer arithmetic in Go. The thing with TCP/IP stack is that you need pointer arithmetic because has you pass packet from one layer to another, you need to access it's payload and manipulate it, because of this entire concept `GlueThread` is impractical in Go.
- In Go byte is the least size datatype. This makes it hard to implement header formats of different layers. Even in areas where we just need a few bits we have to use a byte(8 bits).
# Basics
I use graphs to represent a topology, each node in the graph acts has a router. Each node(router) contains a bunch of interfaces and every node and it's interface have network properties. Each node is connected using a Link through one of its interface. 
Link to the whole <a href="https://github.com/gkarthikreddi/tcp/">project</a>.

<img class="svg" src="/class_diagram.svg" >
## Network Properties
Very node and interface has some network properties. Node has loopback address and routing table has layer3 properties, arp table and mac address table has layer2 properties. Interface either operates in layer2 or layer3, so it contains Ip, Mac addresses and L2 mode.
## Command Parser
This is a CLI application so we need a command parser to interact with the user. There are many CLI libraries in Go but I decided to implement my own has I'm trying to learn Go. I went with the conventional CLI implementation. Each param is either a Leaf node or Command node. A command node shouldn't contain more than one leaf node has it creates ambiguity. These nodes have ***validation*** and ***callback*** functions which are performed when the user runs the command. The parser runs in an infinite loop creating a REPL(Read Eval Print Loop).

I don't want to get too technical about how the Command Parser is implemented because it needs its own post.
## Layer 5 (Application)
This layer generates the data to be sent, I implemented `ping` functionality  in this layer so that we can test all other layers. You can further add IP-IN-IP encapsulation and other functionality later.
## Layer 4 (TCP / UDP)
Each node uses UDP to listen and send packets. I've used "net" package to implement this, every node has a port number to uniquely identify itself in the topology. The problem is that we don't know to which interface the package is designated so we use a special packet to include interface name in the packet along with the actual packet.
```go
type packet struct {
	Intf       string // Identify to which interface the packet is sent
	EtherFrame ethernetHeader
}
```
## Layer 3 (Internet)
This layer creates the IP packet based on the data sent from the TCP layer but in our implementation the application layer directly sends the data to internet layer. This layer creates an IP header with source and destination IP addresses.

The node lookups up it's `routingTable` and by using the gateway address and interface it sends the packet out. The lookup in routing table works through LPM (Least prefix match).A node must have route in it's routing table to send a packet. We can add the route in out application using the below commad
	config node `node-name` route `dstIP` `mask` `gatewayIP` `outIntferface`
Example of a routing table

<img class="svg" src="/rttable.svg" >

When a layer3 receives a packet it checks whether the packet is designated to it or not, if it's not then it sends the packet out through another interface, else it process the packet.
## Layer 2 (Ethernet)
A router can operate in either L3 Mode or L2 Mode. In L3 mode it uses `Arp Table` to send packets to other nodes. In L2 mode(switch) it uses `Mac Table` to send packets to other nodes.

In a general node(Host) this layer creates an ethernet header with destination and source mac addresses and adds IP header has payload of the packet. To convert a struct to byte array I've used `encoding/gob` package. Then it sends the packet out using arp table.
```go
type ethernetHeader struct {
	DstMacAddr [6]byte
	SrcMacAddr [6]byte
	Tagged     *vlan8021qHeader
	EtherType  uint16
	Payload    [500]byte // Ideally it could be between 45 - 1500 bytes
	Fcs        uint32
}
```
### ARP (Address Resolution Protocol)
This is used to resolve a mac-address of an interface. You can either pass the Ip address of the interface of which you want to find the mac address or you can resolve all mac addresses of all connected interfaces of a node
> run node `node-name` resolve-arp `dst-ip`
> 
> run node `node-name` resolve-arp all
```go
type arpHeader struct {
	HardwareType    uint16 // Always 1 for ethernet cable
	ProtocolType    uint16 // 0x0800 for IPv4
	HardwareLength  uint8  // 6 for network.Mac Address
	ProtocolLength  uint8  // 4 for IPv4
	Operation       uint16 // request:1 or reply:2
	SrcMacAddr      [6]byte
	SrcProtocolAddr [4]byte
	DstMacAddr      [6]byte
	DstProtocolAddr [4]byte
}
```
The way it resolves is that, It uses the broadcast mac-address as `DstMacAddr` of ethernet header and sends the packet through interfaces which belong in the same subnet has `DstProtocolAddr`.  When the other interface receives the packet and knows that it is an ARP request it checks whether the `DstProtocolAddr` is the Ip address of the interface if so, then it responds with an arp reply. From the arp reply the source node updates the its `ArpTable`.

<img class="svg" src="/arptable.svg" >

### Switch
First we need to understand how a switch(node operating in L2 mode) works. An interface in a switch can operate in either **TRUNK** or **ACCESS** mode. In access mode an interface has a single vlan membership, in trunk mode it can have multiple vlan memberships. Trunks can handle traffic from multiple vlans whereas Access mode usually connects to single end device(host). Ethernet Header has tagged member which tells if a packet is associated with any vlan.
```go
type vlan8021qHeader struct {
	TPID uint16
	Id   uint16 // This should be 12 bits has there are PRI (3bits) and CFI (1bits)
}
```
When a switch receives a packet on an interface. It updates its `macTable` and sends the packet out based on the outInterface associated with `DstMacAddress` of ethernet header. It doesn't contain an entry in the `macTable` then it sends the packet out of all interfaces expect the interface through which the packet was received.

<img class="svg" src="/mactable.svg" >
