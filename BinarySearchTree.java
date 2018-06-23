abstract class BinarySearchTree<T extends Comparable<? super T>> implements BST<T> {

    protected static class BNode<E>{
        E element;
        BNode<E> leftChild;
        BNode<E> rightChild;
        BNode (E e){
            element=e;
            leftChild=null;
            rightChild=null;
        }
        BNode(E e, BNode<E> leftChild, BNode<E> rightChild){
            element=e;
            this.leftChild=leftChild;
            this.rightChild=rightChild;
        }
        public String toString(){
            return element.toString();
        }
    }

    private BNode<T> root;

    public BinarySearchTree(T x){
        root=new BNode<T>(x);
    }
    public BinarySearchTree(BNode<T> r){
        root=r;
    }
    public BinarySearchTree(){
        root=null;
    }
    public boolean empty(){
        return root==null;
    }
    public BinarySearchTree(T r, BNode<T> e, BNode<T> d){
        root=new BNode<T>(r,e,d);
    }

    public boolean isEmpty() {
        return root == null;
    }

    public boolean contains(T x) {
        return contains_alg(root, x);
    }

    private boolean contains_alg(BNode<T> current, T x) {
        if (current.element.compareTo(x) > 0 && current.leftChild != null) {
            return contains_alg(current.leftChild, x);
        }
        if (current.element.compareTo(x) < 0 && current.rightChild != null) {
            return contains_alg(current.rightChild, x);
        }
        if (current.element.compareTo(x) == 0) {
            return true;
        }
        return false;
    }

    public T findMin() {
        return findMin_alg(root);
    }

    private T findMin_alg(BNode<T> current){
        if (current.leftChild == null) {
            return current.element;
        }
        return findMin_alg(current.leftChild);
    }

    public T findMax() {
        return findMax_alg(root);
    }

    private T findMax_alg(BNode<T> current){
        if (current.rightChild == null) {
            return current.element;
        }
        return findMax_alg(current.rightChild);
    }

    public void insert(T x) {
        insert_alg(root, x);
    }

    private void insert_alg(BNode<T> current, T x) {
        if (isEmpty()) {
            root = new BNode<>(x);
            return;
        }
        int v = current.element.compareTo(x);
        if (v > 0) {
            if (current.leftChild != null) {
                insert_alg(current.leftChild, x);
            } else {
                current.leftChild = new BNode<>(x);
            }
        }
        if (v < 0) {
            if (current.rightChild != null) {
                insert_alg(current.rightChild, x);
            } else {
                current.rightChild = new BNode<>(x);
            }
        }

    }

    public void remove(T x) {
       root = remove_alg(root, x);
    }

    private BNode<T> remove_alg(BNode<T> current, T x) {
        if (isEmpty()) {
            root = new BNode<>(x);
            return null;
        }
        int v = current.element.compareTo(x);

        if (v < 0) {
            current.rightChild = remove_alg(current.rightChild, x);
        } else if (v > 0) {
            current.leftChild = remove_alg(current.leftChild, x);
        }

        //leaf
        else if(current.rightChild == null && current.leftChild == null) {
            current = null;
        }

        //left child

        else if (current.rightChild == null){
            current = current.leftChild;
        }

        //right child

        else if (current.leftChild == null){
            current = current.rightChild;
        }

        // 2 childs

        else {
            T min = findMin_alg(current.rightChild);
            current.element = min;
            current.rightChild = remove_alg(current.rightChild, min);
        }

        return current;
    }

    public void inOrderTraverse() {
        inOrderTraverse(root);
    }

    private void inOrderTraverse(BNode<T> current) {
        if (current.leftChild != null) {
            inOrderTraverse(current.leftChild);
        }
        System.out.println(current.element.toString());
        if (current.rightChild != null) {
            inOrderTraverse(current.rightChild);
        }
    }


    public void postOrderTraverse() {
        postOrderTraverse(root);
    }

    private void postOrderTraverse(BNode<T> current) {
        if (current.leftChild != null) {
            postOrderTraverse(current.leftChild);
        }
        if (current.rightChild != null) {
            postOrderTraverse(current.rightChild);
        }
        System.out.println(current.element.toString());
    }

    public void preOrderTraverse() {
        preOrderTraverse(root);
    }

    private void preOrderTraverse(BNode<T> current) {
        System.out.println(current.element.toString());
        if (current.leftChild != null) {
            preOrderTraverse(current.leftChild);
        }
        if (current.rightChild != null) {
            preOrderTraverse(current.rightChild);
        }
    }
}
