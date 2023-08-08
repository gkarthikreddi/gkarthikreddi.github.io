class ConstructOverloading {
    public static void main(String args[]) {
        Sample s1=new Sample();
        Sample s2=new Sample(10);
        Sample s3=new Sample(20,40);
    }
}
class Sample {
    Sample ()
    {
        System.out.println("welcome");
    }
    Sample(int a)
    {
        System.out.println("value of a:"+a);

    }
    Sample(int p,int q)
    {
        System.out.println("value of p:"+p);
        System.out.println("value of q:"+q);
    }
}
