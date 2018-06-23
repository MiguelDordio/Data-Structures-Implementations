import java.util.EmptyStackException;

/**
 * Implementation of a Last In First Out data structure
 * @param <E>
 */

abstract class ArrayStack<E> implements Stack<E> {

    public E[] stackarray;
    private int top;

    //constructor
    public ArrayStack(int initsize){

        stackarray = (E[]) new Object[initsize];
        top = -1;
    }
    //adds an item in the stack
    public E push(E o){
        return stackarray[++top] = o;

    }
    //returns the item on top of the stack
    public E top() throws EmptyStackException{
        if(top==-1){
            throw new EmptyStackException();
        }else{
            return stackarray[top];
        }
    }
    //removes the last item
    public E pop() throws EmptyStackException{
        if(top==-1){
            throw new EmptyStackException();
        }
        return stackarray[top--];
    }
    //removes a given number of items
    public void popMany(int x){
        for(int i = 0; i < x; i++){
            pop();
        }
    }
    //checks if the stack is empty
    public boolean isEmpty(){
        return top == -1;
    }

    //returns the size of the stack
    public int size(){

        return top+1;
    }

    //displays the stack
    public void display() {
        for(int i=0;i<=top;i++){
            System.out.print(stackarray[i]+ " ");
        }
        System.out.println();
    }
}
