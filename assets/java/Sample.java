import java.swing.*;
import java.awt.*;
import java.awt.event.*;

public class Sample extends JApplet {
    public void init() {
        CalculatorPanel calc = new CalculatorPanel();
        getContentPane().add(calc);
    }
}

class CalculatorPanel extends JPanel implements ActionListener {
    JButton n1,n2,n3,n4,n5,n6,n7,n8,n9,n0,plus,minus,div,mul,equal,dot;
    static JTextField result = new JTextField("0", 45);
    static String lastCommand = null;
    JOptionPane p = new JOptionPane();
    double preRes = 0, secValue = 0, res;
    private static void assign(String no) {
        if((result.getText().equals("0")))
            result.setText();
        else if(lastCommand == "=") {
            result.setText(no);
            lastCommand = null;
        }
        else
            result.setText(result.getText() + no);
    }
    public CalculatorPanel() {
        setLayout(new BorderLayout());
        result.setEditable(false);
        result.setSize(300, 200);
        add(result,BorderLayout.NORTH);
