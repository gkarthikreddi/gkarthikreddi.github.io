import java.io.*;
class Palindrome {
    public static void main(String args[ ])throws IOException {
        BufferedReader br=new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter the string to check for palindrome:");
        String s1=br.readLine();
        StringBuffer sb=new StringBuffer();
        sb.append(s1);
        sb.reverse();
        String s2=sb.toString();
        if(s1.equals(s2))
            System.out.println("palindrome");
        else
            System.out.println("not palindrome");
    }
}

