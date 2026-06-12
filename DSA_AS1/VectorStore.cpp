#include "VectorStore.h"

// ----------------- ArrayList Implementation -----------------

// Vì mình định nghĩa template nên mọi thành viên khi triển khai bên ngoài đều phải khai báo template
// Để compiler biết nó thuộc về 1 class template

// Vì sao phải là Array<T>?
// Vì đang làm việc với template nên phải viết là ArrayList <T> chứ không phải ArrayList:: thôi

// 0
template <class T>
void ArrayList<T>::ensureCapacity (int cap){
    // Nếu nhỏ hơn giới hạn capacity thì không cần làm gì hết
    if (cap <= capacity) return;

    // Nếu > capacity thì nhân 1.5 rồi copy qua hết
    int grow = static_cast<int> (capacity*1.5);
    int newCapacity;
    if (cap > grow) newCapacity = cap;
    else newCapacity = grow;

    T* newData = new T[newCapacity];
    for (int i=0; i<count; i++){
        newData[i] = data[i];
    }

    delete[] data;
    data = newData;
    capacity = newCapacity;
}

// 1
template <class T>
ArrayList<T>::ArrayList(int initCapacity) {
    // TODO
    if (initCapacity < 0) this-> capacity = 10;
    else this->capacity = initCapacity;
    this-> count = 0;
    this-> data = new T[capacity];

}

// 2
template <class T>
ArrayList<T>::ArrayList(const ArrayList<T>& other) {
    // TODO
    this-> capacity = other.capacity;
    this-> count =  other.count;
    this-> data = new T[capacity];
    for (int i=0; i<count; i++){
        this->data[i] = other.data[i];
        // tại sao lại có thể duyệt theo chỉ số như thế này
        // mảng này cấp phát động thì cũng như mảng thông thường nên có số chỉ 
        // con trỏ data trỏ vào phần tử đầu tiên của mảng
        //other.data[i] biên dịch thành *(other.data+i)
    }
}   

// 3
template <class T>
ArrayList<T>::~ArrayList() {
    // TODO
    delete[] data;
    // Mảng nên chỉ cần xóa như thế này thôi
    data = nullptr;
    capacity = 0;
    count = 0;
}

// 4
template <class T>
ArrayList<T>& ArrayList<T> :: operator= (const ArrayList<T> & other){
    if (this == &other) return *this;
    delete[] this->data;

    this->capacity = other.capacity;
    this->count = other.count;
    this->data = new T[capacity];
    for (int i=0; i<count; i++){
        this->data[i] = other.data[i];
    }

    return *this;
}

// 5
// Thêm ở cuối 
template <class T> 
void ArrayList<T>::add(T e){
    if (count >= capacity) ensureCapacity(count +1);
    // Cần kiểm tra kích thước trước khi thêm vào 
    data[count++] = e;
}

// 6
// Thêm không ở cuối
template <class T>
void ArrayList<T>::add (int index, T e){
    if (index<0 || index> count){
        throw out_of_range("Index is invalid!");
        // cái throw này dùng để làm gì, dùng như thế nào
        // out_of_range nằm trong thư viện <stdexcept>
        // Khi gặp throw thì ngừng chạy đoạn code và nhảy ra ngoài đi tìm try ... catch phù hợp (thường nằm trong main)
    }

    ensureCapacity (count +1);
    for (int i = count; i> index ; i--){
        // Yêu cầu dịch phải bit
        data[i] = data [i-1];
    }
    data[index] = e;
    count ++;
}

// 7
template <class T>
T ArrayList<T>::removeAt (int index){
    // Yêu cầu dịch trái 
    if(index < 0 || index >= count) throw out_of_range ("Index is invalid!");
    T removed = data[index];
    for (int i= index; i<count-1; i++){
        // Tại sao lại là count -1
        data[i] = data[i+1];
    }
    count --;
    return removed;
}

// 8
template <class T> 
bool ArrayList<T>:: empty() const{
    return count == 0;
}

// 9
template <class T>
int ArrayList<T>::size() const{
    return count;
}

// 10
template <class T>
void ArrayList<T>::clear(){
    // Xóa hết các phần tử
    // Đặt lại về khởi tạo ban đầu

    // Vì sao chỉ cần delete []
    delete[] data;
    capacity = 10;
    data = new T[capacity];
    count = 0;
}

// 11
template <class T>
T& ArrayList<T>::get (int index){
    if (index < 0 || index >= count){
        throw out_of_range ("Index is invalid!");
    }
    return data[index];
    // Trả về tham chiếu đến phần tử tại index 
}

template <class T> 
const T& ArrayList<T>:: get(int index) const{
    // Phiên bản để dùng cho đối tượng const 
    if ( index <0 || index >= count) throw out_of_range ("Index is invalid!");
    return data[index];
}

// 12
template <class T> 
void ArrayList<T>::set (int index, T e){
    // Gán phần tử tại vị trí index thành e
    if (index < 0 || index >= count ) throw out_of_range ("Index is invalid!");
    data[index] = e;
}

// 13
template <class T>
int ArrayList<T>::indexOf (T item) const{
    // Trả về chỉ số của phần tử đầu tiên có giá trị bằng item 
    // Nếu không có trả về -1 
    for (int i=0; i<count; i++){
        if (data[i] == item) return i;
    }
    return -1;
}

// 14
template <class T>
bool ArrayList<T>::contains(T item) const{
    // Kiểm tra xem danh sách có chứa phần tử có giá trị bằng item 
    return indexOf(item) != -1;
}

// 15
template <class T>
string ArrayList<T>::toString(string(*item2str)(T&)) const{
    // Giải thích cả cụm string*item2str (&T) là sao
    // item2str là con trỏ trỏ đến hàm, tức là truyền hàm vào 
    // Nếu chưa truyền hàm thì sẽ in ra như thông thường thôi 
    // Hàm này yêu cầu phải truyền tham chiếu vào cho nhanh hơn

    stringstream ss;
    ss << "[";
    for (int i=0; i<count; i++){
        if (item2str) ss << item2str (data[i]);
        else ss << data[i];
        if (i < count -1) ss << ", ";
    }
    ss << "]";
    return ss.str();
}

// 16
template <class T> 
typename ArrayList<T>::Iterator ArrayList<T>::begin(){
    return Iterator(this,0);
    // Vì sao cần có typename 
    // return Iterator(this,0); dòng này nghĩa là gì 

    // Vì ArrayList là template class nên viết iterator thôi compiler chưa biết iterator này là gì (tên biến hay hằng số...)
    // Cần viết thêm typename để biết iterator là kiểu dữ liệu
    // Nếu không có sẽ báo lỗi

    // Iterator(this, 0) tạo ra một iterator mới 
    // this trỏ đến ArrayList hiện tại, bắt đầu từ vị trí index 0
    // Đây là cách khởi tạo constructor vắng tắt
}

// 17
template <class T>
typename ArrayList<T>::Iterator ArrayList<T>::end(){
    return Iterator (this, count);
}

// ----------------- Iterator of ArrayList Implementation -----------------
// 1
template <class T>
ArrayList<T>::Iterator::Iterator(ArrayList<T>* pList, int index)
            : cursor(index), pList(pList) {
    // TODO
    // Đặt constructor sau end() và begin() có bị lỗi không
    // Không quan trọng thứ tự trước sau 
    
    if (pList != nullptr){
        if (index < 0 || index > pList->count){
            // Duyệt tới = count thì đang trỏ đến end() không bị lỗi nhưng không được giải tham chiếu *it
            throw out_of_range ("Index is invalid!");
        }
    }
}

// 2
template <class T>
typename ArrayList<T>::Iterator&
// Dòng này là sao 
ArrayList<T>::Iterator::operator= (const Iterator&other){
    this->pList = other.pList;
    this->cursor = other.cursor;
    return *this;
}

// 3
template <class T> 
T& ArrayList<T>::Iterator::operator*(){
    if (pList == nullptr || cursor <0 || cursor >= pList->count){
        throw out_of_range("Iterator is out of range!");
    }
    return pList->data[cursor];
    // Lấy giá trị của phần tử thứ cursor của pList
}

// 4
template <class T>
bool ArrayList<T>::Iterator::operator!= (const Iterator& other) const{
    // operator!= phải viết liền luôn sao 
        return (this->pList != other.pList) || (this->cursor != other.cursor);
    // Vì sao là ||
}

// 5
// Prefix ++
template <class T> 
typename ArrayList<T>::Iterator&
ArrayList<T>::Iterator::operator++(){
    // Vì sao phải có Iterator&
    // Để có thể dùng ++++ liên tục được 
    // Nếu không thì sẽ tạo bản sao để thực hiện rồi sau đó hủy bản sao liền -> tốn hiệu năng
    
    if (pList == nullptr) return *this;
    // Cần phải kiểm tra xem danh sách có rỗng không nếu rỗng mà ++ thì sẽ bị segment

    if (cursor >= pList->count) {
        throw out_of_range ("Iterator cannot advance past end!");
    }
    ++ cursor;
    return *this;

    // this đang trỏ tới gì
    // this = địa chỉ của it.
    // *this = chính đối tượng it.
}

// 6
//Postfix ++
template <class T>
typename ArrayList<T>::Iterator 
ArrayList<T>::Iterator::operator++ (int){
    // Vì sao để int thôi mà không để tên biến

    Iterator tmp = *this;
    if (pList == nullptr) return tmp;

    if (cursor >= pList->count){
        throw out_of_range ("Iterator cannot advance past end!");
    }
    ++ cursor;
    return tmp;
}

// 7
//Prefix --
template <class T> 
typename ArrayList<T>::Iterator&
ArrayList<T>::Iterator::operator--(){
    if (pList == nullptr) return *this;

    if (cursor == 0){
       throw out_of_range("Iterator cannot move before begin!"); 
    }
    --cursor;
    return *this;
}

// 8
//Postfix --
template <class T>
typename ArrayList<T>::Iterator
ArrayList<T>::Iterator::operator--(int){
    Iterator tmp = *this;
    if (pList == nullptr) return tmp;

    if(cursor == 0) {
        throw out_of_range ("Iterator cannot move before begin!");
    }
    --cursor;
    return tmp;
}

// ----------------- SinglyLinkedList Implementation -----------------
// 1
template <class T>
SinglyLinkedList<T>::SinglyLinkedList() {
    // TODO
    head = nullptr;
    tail = nullptr;
    count = 0;
}   

// 2
template <class T>
SinglyLinkedList<T>::~SinglyLinkedList() {
    // TODO
    Node* cur = head;
    while (cur != nullptr){
        Node *next = cur->next;
        delete cur;
        cur = next;
    }
    head = tail = nullptr;
    count = 0;
}   

// 3
template <class T> 
void SinglyLinkedList<T>::add (T e){
    // thêm ở cuối 
    Node *newNode = new Node (e);
    if (!head) head = tail = newNode;
    else {
        tail->next = newNode;
        tail = newNode;
    }
    count++;
}

// 4
template <class T>
void SinglyLinkedList<T>:: add(int index, T e){
    if (index < 0 || index > count) throw out_of_range ("Index is invalid!");
    if (index == count) { 
        add(e);
        return;
    }
    if (index == 0){
        Node *newNode = new Node (e, head);
        head = newNode;
        if (count == 0) tail = newNode;
        count ++;
        return; 
    }
    Node *prev = head;
    for (int i=0; i<index -1; i++) prev = prev -> next;
    Node* newNode = new Node (e, prev->next);
    prev-> next = newNode;
    count ++;
}

// 5
template <class T> 
T SinglyLinkedList<T>::removeAt (int index){
    if (index < 0 || index >= count) {
        throw out_of_range ("Index is invalid!");
    }

    Node *del;
    T val;
    if (index == 0){
        del = head;
        head = head-> next;
        if (count == 1) tail = nullptr;
    } else {
        Node* prev = head;
        for (int i=0; i< index-1; i++) {
            prev = prev-> next;
        }
        del = prev->next;
        prev->next = del->next;
        if (del == tail) tail = prev;
    }

    val = del-> data;
    delete del;
    count-- ;
    return val;
}

template <class T>
T SinglyLinkedList<T>::removeLast() {
    if (count == 0) {
        return T();   // trả về giá trị mặc định của T
    }
    return removeAt(count - 1);
}
// 6
template <class T> 
bool SinglyLinkedList <T> :: removeItem (T item){
    Node* prev = nullptr;
    Node* cur = head;
    while (cur){
        if (cur->data == item){
            if (prev == nullptr) head = cur-> next;
            else prev->next = cur->next;
            if (cur == tail) tail = prev;
            delete cur;
            count --;
            return true;
        }
        prev = cur;
        cur = cur-> next;
    }
    return false;
}

// 7
template <class T>
bool SinglyLinkedList<T>::empty () const {
    return count == 0;
}

// 8
template <class T>
int SinglyLinkedList<T>::size() const {
    return count;
    // Vì đề yêu cầu O(1)
}

// 9
template <class T> 
void SinglyLinkedList<T>::clear (){
    Node * cur = head;
    while (cur){
        Node *next = cur->next;
        delete cur;
        cur = next;
    }

    // Xóa hết rồi phải đặt head và tail về nullptr
    head = tail = nullptr;
    count = 0;
}

// 10
template <class T>
T& SinglyLinkedList<T>::get (int index){
    if (index <0 || index >= count){
        throw out_of_range ("Index is invalid!");
    }
    Node *cur = head;
    for (int i=0; i<index; i++) cur = cur->next;
    return cur->data;
}

// 11
template <class T> 
int SinglyLinkedList<T> :: indexOf (T item) const {
    // Nếu mà tìm thấy thì trả về index, nếu không tìm thấy trả về -1
    Node *cur = head;
    int idx = 0;
    while (cur){
        if (cur-> data == item) return idx;
        cur = cur-> next;
        idx++;
    }
    return -1;
}

// 12
template <class T> 
bool SinglyLinkedList<T>::contains (T item) const {
    return indexOf (item) != -1;
    // Đề yêu cầu độ phức tạp O(n), viết như thế này thì ngắn hơn chứ độ phức tạp vẫn là O(n)
}

// 13
template <class T>
string SinglyLinkedList<T>::toString(string (*item2str)(T&)) const {
    stringstream ss;
    Node * cur = head;
    while (cur){
        ss << "[";
        if (item2str) ss << item2str (cur->data);
        else ss << cur->data;
        ss << "]";

        if (cur->next) ss << "->";
        cur = cur-> next;
    }
    return ss.str();
}

// 14
template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T> :: begin(){
    return Iterator (head);
}

template <class T> 
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T> :: begin () const {
    return Iterator (head);
}

// 15
template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>::end(){
    return Iterator (nullptr);
}

template <class T>
typename SinglyLinkedList<T>::Iterator SinglyLinkedList<T>:: end() const {
    return Iterator (nullptr);
}

// ----------------- Iterator of SinglyLinkedList Implementation -----------------
// 1
template <class T>
SinglyLinkedList<T>::Iterator::Iterator(Node* node) 
        : current (node){
    // TODO
    // current đã trỏ đến Node rồi nên không cần làm gì nữa 

}   

// 2
template <class T> 
typename SinglyLinkedList <T>:: Iterator&
SinglyLinkedList<T>::Iterator::operator = (const Iterator& other){
    this -> current = other.current;
    // other ở đây dùng . hay là ->
    // Cái này là deep copy hay shalow copy 
    // Đây là shadow copy 
    return *this;
}

// 3
template <class T>
T& SinglyLinkedList<T>::Iterator::operator *(){
    if (current == nullptr) throw out_of_range("Iterator is out of range!");
    return current->data;
}

// 4
template <class T>
bool SinglyLinkedList <T>::Iterator::operator != (const Iterator& other) const{
    return this->current != other.current;
}

// 5
template <class T>
typename SinglyLinkedList <T>:: Iterator&
SinglyLinkedList<T>::Iterator::operator++(){
    if (current == nullptr) throw out_of_range("Iterator cannot advance past end!");
    current = current -> next;
    return *this;
}

// 6
template <class T> 
typename SinglyLinkedList<T>::Iterator
SinglyLinkedList<T>::Iterator::operator++(int){
    if (current == nullptr) throw out_of_range ("Iterator cannot advance past end!");
    Iterator tmp = *this;
    current = current ->next;
    return tmp;
}

// ----------------- VectorStore Implementation -----------------

// 1
VectorStore::VectorStore(int dimension, EmbedFn embeddingFunction) 
            : dimension (dimension), count (0), embeddingFunction (embeddingFunction){
    // TODO
}

VectorStore::VectorRecord::VectorRecord(int id, const string& rawText, SinglyLinkedList<float>* vec) {
    this->id = id;
    this->rawText = rawText;
    this->rawLength = rawText.length();
    this->vector = vec;
}

VectorStore::~VectorStore() {
    // TODO
    for (int i=0; i<count; i++){
        // delete records[i]->vector;
        // delete records[i];
        // records này có ở đâu
        // Trong ArrayList của mình không có định nghĩa toán hạng [] chỉ có get 
        delete records.get(i)->vector;
        delete records.get(i);
    }
    records.clear();
    count = 0;
}

// 2: O(1)
int VectorStore::size() const{
    return count;
}

// 3: O(1)
bool VectorStore::empty () const{
    return count == 0;
}

// 4 O(n)
void VectorStore::clear(){
    for (int i=0; i<count; i++){
        delete records.get(i) -> vector;
        delete records.get(i);
    }
    records.clear();
    count = 0;
    // Hàm này dùng get hay [] thì độ phức tạp đều là O(n)
}

// 5: O(d)
SinglyLinkedList <float>* VectorStore:: preprocessing (string rawText){
    SinglyLinkedList<float>* vec = embeddingFunction (rawText);
    if (vec == nullptr) {
    return nullptr; // embeddingFunction sai thì trả về luôn
    }

    int len = 0;
    for (SinglyLinkedList<float>:: Iterator it = vec->begin(); it!= vec->end(); it++){
        len++;
    }

    while (len > dimension){
        vec->removeLast();
        // Nếu dùng removeAt ở chỗ này có thể độ phức tạp lên được O(n^2) nên viết riêng hàm removeLast O(1)
        len--;
    }

    while (len < dimension){
        vec -> add (0.0f);
        len++;
    }

    return vec;
}

// 6: O(n)
void VectorStore:: addText (string rawText){
    SinglyLinkedList<float> * vec = preprocessing (rawText);
    count++;
    VectorRecord* rec = new VectorRecord (count, rawText, vec);
    records.add(rec);

    // Xử lí rawText -> vector 
    // Chèn vector vào 
    // Tăng số chỉ lên
}

// 7: O(1), độ phức tạp chính xác của code hiện tại là O(L)
SinglyLinkedList<float> &VectorStore::getVector (int index){
    if (index <0 || index >= count) {
        throw out_of_range ("Index is invalid!");
    }
    return *(records.get(index)->vector);
    // Tại sao chỗ này phải giải tham chiếu 
}

// 8: O(1), độ phức tạp chính xác của code hiện tại là O(L)
string VectorStore::getRawText (int index) const{
    if (index < 0 || index >= count) throw out_of_range("Index is invalid!");
    // return records[index]->rawText;
    return records.get(index)->rawText;
}

// 9: O(1)
int VectorStore::getId (int index) const{
    if (index < 0 || index >= count) throw out_of_range ("Index is invalid!");
    return records.get(index)->id;
}

// 10: O(n)
bool VectorStore:: removeAt (int index){
    if (index < 0 || index >=count) throw out_of_range ("Index is invalid!");
    delete records.get(index)->vector;
    // Nếu không xóa con trỏ đến vùng vector trước sẽ gây memory leak
    delete records.get(index);
    // Nếu xóa cái này trước cái trên thì sẽ mất đường đẫn để xóa vector ->leak
    records.removeAt(index);
    count--;
    return true;
    // Vì sao lại xóa theo thứ tự này
    // Thứ tự xóa: giải phóng bên trong -> giải phóng chính nó -> xóa cả container
}

// 11: O(n)
bool VectorStore::updateText (int index, string newRawText){
    if (index<0 || index>= count) throw out_of_range("Index is invalid!");
    VectorRecord *rec = records.get(index);

    delete rec->vector;
    rec -> vector = preprocessing(newRawText);
    rec -> rawText = newRawText;
    rec -> rawLength = newRawText.size();

    return true;
}

// 12: O(1)
void VectorStore:: setEmbeddingFunction ( SinglyLinkedList<float>* (*newEmbeddingFunction) (const string&)){
        embeddingFunction = newEmbeddingFunction;
        // Chỉ có 1 phép gán đơn thuần nên độ phức tạp đúng là O(1)
}

// 13: O(n)
void VectorStore:: forEach (void (*action)(SinglyLinkedList<float>&, int, string&)){
    for (int i=0; i<count; i++){
        action(*(records.get(i)->vector), records.get(i)->id, records.get(i)->rawText);
    }

    // Hàm này là sao, không hiểu nha 
    // Hàm này duyệt toàn bộ bản ghi trong kho và áp dụng hàm actions
    // Hàm action do đề truyền vào nên mặc định độ phức tạp là O(1)
    // Đúng độ phức tạp O(n)
}

// 14: O(d)
double VectorStore::cosineSimilarity (const SinglyLinkedList <float> &v1,
                                     const SinglyLinkedList<float> &v2) const{
    double dot = 0.0, a = 0.0, b = 0.0;

    SinglyLinkedList<float>::Iterator it1 = v1.begin();
    SinglyLinkedList<float>::Iterator it2 = v2.begin();

    for (; it1 != v1.end() && it2 != v2.end(); ++it1, ++it2){
        // Tính tích vô hướng
        dot += (*it1)*(*it2);
        
        // Tính độ dài vector
        a += (*it1)*(*it1);
        b += (*it2)*(*it2);
    }

    if (a==0 || b==0) return 0.0;
    return dot / (sqrt(a)*sqrt(b));


    // Duyệt từng phần tử của v1 và v2 song song
    // Giả sử cả 2 có chiều dài = d + mỗi vòng tính toán O(1)
    // Tổng O(d);
}

// 15: O (d)
double VectorStore::l1Distance (const SinglyLinkedList<float>& v1,
                    const SinglyLinkedList<float>& v2) const{
    double sum = 0.0;
    SinglyLinkedList<float>::Iterator it1 = v1.begin();
    SinglyLinkedList<float>::Iterator it2 = v2.begin();

    for (; it1 != v1.end() && it2 != v2.end(); ++it1, ++it2){
        sum += fabs((*it1)- (*it2));
    }

    return sum;
}

// 16
double VectorStore::l2Distance (const SinglyLinkedList<float>& v1, 
                    const SinglyLinkedList<float>& v2) const{
    double sumSq = 0.0;
    SinglyLinkedList<float>::Iterator it1 = v1.begin();
    SinglyLinkedList<float>::Iterator it2 = v2.begin();
    for (; it1 != v1.end() && it2 != v2.end(); ++it1, ++it2){
        double diff = (*it1) - (*it2);
        sumSq += diff * diff;
    }
    return sqrt (sumSq);
}

// 17
int VectorStore:: findNearest (const SinglyLinkedList <float>& query, const string& metric) const {
    int bestIdx = -1;
    double bestScore = 0.0;

    for (int i=0; i<count; i++){
        double score;
        
        if (metric == "cosine"){
            score = cosineSimilarity (query, *(records.get(i)->vector));
            if (bestIdx == -1 || score > bestScore){
                bestIdx = i;
                bestScore = score;
            }
        } else if (metric == "euclidean"){
            score = l2Distance (query, *(records.get(i)->vector));
            if (bestIdx == -1 || score < bestScore){
                bestIdx = i;
                bestScore = score;
            } 
        } else if (metric == "manhattan"){
            score = l1Distance (query, *(records.get(i)->vector));
            if (bestIdx == -1 || score < bestScore){
                bestIdx = i;
                bestScore = score;
            } 
        }
        else {
            throw invalid_metric();
        }
    }

    return bestIdx;
}

// 18
void VectorStore::quickSort(double* scores, int* indices, int left, int right, bool maximize) const {
    // Tạo stack thủ công bằng mảng
    int* stackLeft = new int[right - left + 1];
    int* stackRight = new int[right - left + 1];
    int top = -1;

    // Đẩy khoảng ban đầu vào stack
    stackLeft[++top] = left;
    stackRight[top] = right;

    while (top >= 0) {
        int l = stackLeft[top];
        int r = stackRight[top];
        top--;

        if (l >= r) continue;

        // Chọn pivot
        double pivot = scores[(l + r) / 2];
        int i = l, j = r;

        while (i <= j) {
            if (maximize) { // cosine → chọn lớn nhất
                while (scores[i] > pivot) i++;
                while (scores[j] < pivot) j--;
            } else {        // euclidean / manhattan → chọn nhỏ nhất
                while (scores[i] < pivot) i++;
                while (scores[j] > pivot) j--;
            }
            if (i <= j) {
                // Hoán đổi thủ công
                double tmpScore = scores[i];
                scores[i] = scores[j];
                scores[j] = tmpScore;

                int tmpIdx = indices[i];
                indices[i] = indices[j];
                indices[j] = tmpIdx;

                i++;
                j--;
            }
        }

        // Đẩy các đoạn còn lại vào stack
        if (l < j) {
            stackLeft[++top] = l;
            stackRight[top] = j;
        }
        if (i < r) {
            stackLeft[++top] = i;
            stackRight[top] = r;
        }
    }

    delete[] stackLeft;
    delete[] stackRight;
}


int* VectorStore::topKNearest(const SinglyLinkedList<float>& query, int k, const string& metric) const {
    if (k <= 0 || k > count) {
        throw invalid_k_value();
    }

    double* scores = new double[count];
    int* indices = new int[count];

    for (int i = 0; i < count; i++) {
        indices[i] = i;
        if (metric == "cosine") {
            scores[i] = cosineSimilarity(query, *(records.get(i)->vector));
        } else if (metric == "euclidean") {
            scores[i] = l2Distance(query, *(records.get(i)->vector));
        } else if (metric == "manhattan") {
            scores[i] = l1Distance(query, *(records.get(i)->vector));
        } else {
            delete[] scores;
            delete[] indices;
            throw invalid_metric();
        }
    }

    bool maximize = (metric == "cosine");
    quickSort(scores, indices, 0, count - 1, maximize);

    int* result = new int[k];
    for (int i = 0; i < k; i++) {
        result[i] = indices[i];
    }

    delete[] scores;
    delete[] indices;

    return result;
}

// Explicit template instantiation for char, string, int, double, float, and Point

template class ArrayList<char>;
template class ArrayList<string>;
template class ArrayList<int>;
template class ArrayList<double>;
template class ArrayList<float>;
template class ArrayList<Point>;

template class SinglyLinkedList<char>;
template class SinglyLinkedList<string>;
template class SinglyLinkedList<int>;
template class SinglyLinkedList<double>;
template class SinglyLinkedList<float>;
template class SinglyLinkedList<Point>;
