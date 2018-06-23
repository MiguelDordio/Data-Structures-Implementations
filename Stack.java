public interface Stack<E> {
    E push(E o);
    E top();
    E pop();
    int size();
    boolean empty();
}
