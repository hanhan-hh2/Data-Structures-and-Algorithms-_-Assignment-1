#ifndef VECTORSTORE_H
#define VECTORSTORE_H

#include "main.h"

// ==============================
// Class ArrayList
// ==============================

template <class T>
// Template này là sao 
class ArrayList {
    #ifdef TESTING
        friend class TestHelper;
    #endif  
    // Mấy dòng này nghĩa là gì 
private:
    T* data;
    int capacity;
    int count;

    void ensureCapacity(int cap);

public:
    class Iterator;
    friend class Iterator;
    // Có khai báo Iterator là friend class nè 

    ArrayList(int initCapacity = 10);
    ArrayList(const ArrayList<T>& other); //Deep Copy
    ~ArrayList();
    ArrayList<T>& operator=(const ArrayList<T>& other); //Deep Copy

    void add(T e);
    void add(int index, T e);
    T removeAt(int index);
    bool empty() const;
    int size() const;
    void clear();
    T& get(int index);
    // Phiên bản const 
    const T& get(int index) const;
    void set(int index, T e);
    int indexOf(T item) const;
    bool contains(T item) const;
    string toString(string (*item2str)(T&) = 0) const;

    Iterator begin();
    Iterator end();

    // Inner class Iterator
    // Định nghĩa friend class ngay trong class luôn sao 
    class Iterator {
        #ifdef TESTING
            friend class TestHelper;
        #endif  
            // Mấy dòng này là gì 
    private:
        int cursor;
        ArrayList<T>* pList;
    public:
        Iterator(ArrayList<T>* pList = nullptr, int index = 0);
        Iterator& operator=(const Iterator& other); //Deep Copy
        T& operator*();
        bool operator!=(const Iterator& other) const;
        Iterator& operator++();
        Iterator operator++(int);
        Iterator& operator--();
        Iterator operator--(int);
    };
};

// =====================================
// Class SinglyLinkedList
// =====================================
template <class T>
class SinglyLinkedList {
    #ifdef TESTING
        friend class TestHelper;
    #endif  
private:
    class Node {
    public:
        T data;
        Node* next;

        Node() : data(), next(nullptr) {}
        Node(const T& data, Node* next = nullptr) : data(data), next(next) {}
        // Vì sao lại cần tạo 2 constructor 
    };

    Node* head;
    Node* tail;
    int count;

public:
    class Iterator;
    friend class Iterator;
    // 2 class Iterator này có phải là cùng 1 cái không

    SinglyLinkedList();
    ~SinglyLinkedList();

    void add(T e);
    void add(int index, T e);
    T removeAt(int index);
    // Hàm thêm vào
    T removeLast();
    bool removeItem(T item);
    bool empty() const;
    int size() const;
    void clear();
    T& get(int index);
    int indexOf(T item) const;
    bool contains(T item) const;
    string toString(string (*item2str)(T&) = 0) const;

    Iterator begin();
    Iterator end();

        // phiên bản const (dùng cho list const)
    Iterator begin() const;
    Iterator end() const;

    // Inner class Iterator
    // Inner tức là định nghĩa ngay bên trong hàm đó hả
    class Iterator {
        #ifdef TESTING
            friend class TestHelper;
        #endif
    private:
        Node* current;
    public:
        Iterator(Node* node = nullptr);
        Iterator& operator=(const Iterator& other); //Deep Copy
        T& operator*();
        bool operator!=(const Iterator& other) const;
        Iterator& operator++();
        Iterator operator++(int);
    };
};

// =====================================
// Class VectorStore
// =====================================

class VectorStore {
    #ifdef TESTING
        friend class TestHelper;
    #endif
public:
    struct VectorRecord {
        int id;
        string rawText;
        int rawLength;
        SinglyLinkedList<float>* vector;

        VectorRecord(int id, const string& rawText, SinglyLinkedList<float>* vector);
    };

    using EmbedFn = SinglyLinkedList<float>* (*)(const string&);
    // EmbedFn là một kiểu con trỏ hàm 
    // Hàm này nhận vào 1 đối tượng duy nhất là const string
    // Trả về một con trỏ đến một danh sách liên kết chứa các số thực
    
    // (*)(const string&): cú pháp để khai báo 1 con trỏ hàm 
    // <float>* kiểu trả về của hàm

private:
    ArrayList<VectorRecord*> records;
    int dimension;
    int count;
    EmbedFn embeddingFunction;
    // Embed Fn là gì 

public:
    VectorStore(int dimension = 512, EmbedFn embeddingFunction = nullptr);
    ~VectorStore();
    int  size() const;
    bool empty() const;
    void clear();    

    SinglyLinkedList<float>* preprocessing(string rawText);

    void addText(string rawText);
    SinglyLinkedList<float>& getVector(int index);
    string getRawText(int index) const;
    int getId(int index) const;
    bool removeAt(int index);
    bool updateText(int index, string newRawText);
    void setEmbeddingFunction(EmbedFn newEmbeddingFunction);

    void forEach(void (*action)(SinglyLinkedList<float>&, int, string&));

    double cosineSimilarity(const SinglyLinkedList<float>& v1,
                            const SinglyLinkedList<float>& v2) const;
    double l1Distance(const SinglyLinkedList<float>& v1,
                      const SinglyLinkedList<float>& v2) const;
    double l2Distance(const SinglyLinkedList<float>& v1,
                      const SinglyLinkedList<float>& v2) const;

    int findNearest(const SinglyLinkedList<float>& query, const string& metric = "cosine") const;

    void quickSort(double* scores, int* indices, int left, int right, bool maximize) const;
    int* topKNearest(const SinglyLinkedList<float>& query, int k, const string& metric = "cosine") const;
};

#endif // VECTORSTORE_H
