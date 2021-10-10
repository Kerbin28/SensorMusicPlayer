public class Run {
    public static void main(String[] args){
        BluetoothCommunicator bc = new BluetoothCommunicator(1);
        int state=0;
        while(state !=2){
            state=Integer.parseInt(bc.readLine());

        }
    }
}
