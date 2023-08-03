import java.awt.*;
import java.applet.*;
import java.awt.event.*;

public class TrafficSignal extends Applet implements Runnable {
    Thread t;
    Font f, f1;
    int i = 0, a = 0, j = 0;
    public void init() {
        setBackground(Color.lightGray);
        f = new Font("TimesNewRoman", f.ITALIC, 28);
        f1 = new Font("TimesNewRoman", Font.ITALIC + Font.BOLD, 28);
    }
    public void start() {
        t = new Thread(this);
        t.start();
    }
    public void run() {
        for (i = 10; i >= 0; i--) {
            try {
                Thread.sleep(1000);
            }
            catch (Exception e) {
                System.out.println(e);
            }
            if (i <= 10 && i > 3) {
                a = 1;
                repaint(); 
            }
            else if (i <= 3 && i > 0) {
                a = 2;
                repaint(); 
            }
            else if (i == 0) {
                for (j = 0; j < 10; j++) {
                    a = 3;
                    try {
                        Thread.sleep(1000);
                    }
                    catch (Exception e) {
                        System.out.println(e);
                    } repaint();
                }
                if (j == 10) {
                    run();
                }
            }
        }
        repaint();
    }
    public void paint(Graphics g) {
        setBackground(Color.lightGray); //ROAD
        g.setColor(Color.black); ////POLE UP
        g.fillRect(150, 150, 50, 150);
        g.drawRect(150, 150, 50, 150);
        g.setColor(Color.black);//POLE DOWN
        g.fillRect(165, 300, 20, 155);

        g.drawRect(165, 300, 20, 155);
        g.drawOval(150, 150, 50, 50);//RED
        g.drawOval(150, 200, 50, 50);//YELLOW 
        g.drawOval(150, 250, 50, 50);//GREEN
        g.setColor(Color.red);//COUNTDOWN STOP
        g.setFont(f);
        g.drawString("" + i, 50, 50);
        if (a == 1)//REDSIGNAL
        {
            g.setColor(Color.red);
            g.fillOval(150, 150, 50, 50);
            g.drawOval(150, 150, 50, 50);
            g.drawString("STOP", 50, 150);
        }
        if (a == 2)//YELLOWSIGNAL 
        {
            g.setColor(Color.yellow);
            g.fillOval(150, 200, 50, 50);
            g.drawOval(150, 200, 50, 50);
            g.drawString("READY", 50, 200);
        }
        if (a == 3)//GREENSIGNAL
        {
            g.setColor(Color.blue);//countdown
            g.setFont(f);
            g.drawString("" + j, 150, 50);
            g.setColor(Color.green);
            g.fillOval(150, 250, 50, 50);
            g.drawOval(150, 250, 50, 50);
            g.drawString("GO", 50, 250);
        }
        int x1[] = {220, 300, 300, 280};
        int y1[] = {250, 150, 250, 150};
        int n1 = 4;
        int n2 = 3;
        int x2[] = {340, 380, 380};
        int y2[] = {150, 100, 150};
        int x3[] = {460, 460, 500};
        int y3[] = {150, 100, 150};
    }
}

// You should also code TrafficSignal.html in another fill
// Execute as follows
// appletviewer TrafficSignal.html
