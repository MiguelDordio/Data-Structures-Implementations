abstract class ArrayQueue<E> implements Queue<E>{


    private E[] queue;
    private int ini, end, DEFAULT_CAPACITY;

    public ArrayQueue(){
        int DEFAULT_CAPACITY = 101; //actual default size is 100
        queue = (E[]) new Object[DEFAULT_CAPACITY];
        ini= 0;
        end = 0;
    }

    public ArrayQueue(int initial_size){
        DEFAULT_CAPACITY = initial_size+1;
        queue = (E[]) new Object[DEFAULT_CAPACITY];
        ini= 0;
        end = 0;
    }

    public int size(){
        return ((queue.length - ini + end) % queue.length);
    }

    public boolean isEmpty(){
        return ini == end;
    }

    private int increment(int i){
        return ((i+1) % DEFAULT_CAPACITY);
    }

    public void enqueue(E x){
        if(size() == DEFAULT_CAPACITY-1){
            System.out.println("Full");
        }else{
            queue[end] = x;
            end = increment(end);
        }

    }

    public E dequeue(){
        E x;
        if(isEmpty())
            System.out.println("Full");

        x = queue[ini];
        queue[ini] = null;
        ini = increment(ini);

        return x;
    }

    public void display(){
        if (!isEmpty()) {
            int i = ini;
            do {
                System.out.print(queue[i] + " ");
                i = ++i % DEFAULT_CAPACITY;
            }while (i != end);
        }
    }
}
