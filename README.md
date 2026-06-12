# Data Structures & Algorithms — Assignment 1: VectorStore Using List

A VectorStore system implemented in C++ from scratch, simulating the core storage and similarity search mechanism found in modern semantic search engines.

## Concepts Applied

**Data Structures (implemented from scratch)**
- `ArrayList<T>` — dynamic array with amortized O(1) append, automatic capacity growth (×1.5), index-based O(1) access
- `SinglyLinkedList<T>` — pointer-based linked list with head/tail tracking, O(1) head insertion
- Custom `Iterator` inner class for both structures — supports prefix/postfix `++`/`--`, dereference, and range-based traversal

**Memory Management (C++)**
- Manual dynamic memory allocation and deallocation (`new` / `delete`)
- Copy constructor and assignment operator for deep copy
- Proper destructor implementation to prevent memory leaks

**VectorStore Logic**
- Embedding pipeline: raw text → high-dimensional float vector via function pointer
- Dimension normalization: truncation if over-dimension, zero-padding if under-dimension
- CRUD operations on vector records: add, update, remove, retrieve

**Similarity Search**
- Cosine similarity: measures angle between vectors (used in semantic search)
- L1 distance (Manhattan): sum of absolute differences
- L2 distance (Euclidean): square root of sum of squared differences
- `findNearest()` — single nearest neighbor search: O(n × d)
- `topKNearest()` — top-k search with sorting: O(n × d + n log n)

**OOP & C++ Features**
- Templates (`ArrayList<T>`, `SinglyLinkedList<T>`) for generic type support
- Function pointers for pluggable embedding strategies
- Exception handling: `out_of_range`, custom `metric_error`, `invalid_k_value`

## Tech
C++ | Data Structures | OOP | Template Programming | Similarity Search
