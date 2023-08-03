import java.awt.*;
import java.lang.String;
import java.awt.event.*;
import java.applet.Applet;

// You should also code applet.html in another file
// and execute as follows
// appletviewer applet.html

public class Factorial extends Applet implements ActionListener {

    String str; Button b0;
    TextField t1,t2; Label l1;
    public void init(){
        Panel p=new Panel();
        p.setLayout(new GridLayout());
        add(new Label("Enter any Integer value"));
        add(t1=new TextField(20));
        add(new Label("Factorial value is: "));
        add(t2=new TextField(20));
        add(b0=new Button("compute"));
        b0.addActionListener(this);
    }

    public void actionPerformed(ActionEvent e) {
        int i,n,f=1;
        n=Integer.parseInt(t1.getText());
        for(i=1;i<=n;i++)
            f=f*i;
        t2.setText(String.valueOf(f));
        repaint();
    }
}
