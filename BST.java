public interface BST<T> {
    boolean isEmpty();
    boolean contains(T x);
    T findMin();
    T findMax();
    void insert(T x);
    void remove(T x);
    void inOrderTraverse();
    void postOrderTraverse();
    void preOrderTraverse();
}

