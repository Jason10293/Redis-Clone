# Redis Clone

This project is a clone of the popular key-value database Redis. Users can interact with the program using commands such as `LPUSH`, `SET`, `GET`, `SADD`, and more.  
Additionally, the program supports **persistent data storage** to ensure databases are not lost upon program exit or in the event of a crash.

---

## How It's Made

This project is implemented almost entirely in **C**, chosen for its low-level nature, performance, and educational value.  
As part of this project, I built several fundamental data structures from scratch, including:

- Singly Linked List
- Doubly Linked List
- Hashset
- Hashmap
- Dynamic Array (List)

### Hashmap

The hashmap is implemented using a **hash table with separate chaining** to handle collisions, where each bucket contains a singly linked list.  
Key operations include:
- **Insertion**
- **Retrieval**
- **Deletion**

![Hashmap Illustration](https://github.com/user-attachments/assets/688498bf-7828-414d-ba79-52317865a022)

---

### Hashset

The hashset is built on top of the hashmap to achieve **O(1)** average performance for common operations.  
Key operations include:
- **Insertion**
- **Retrieval**
- **Membership Checking**
- **Intersection of Two Hashsets**

---

### Dynamic Array (List)

The dynamic array is implemented using a **doubly linked list** for efficient insertion and deletion at both ends.  
Key operations include:
- **Left/Right Push**
- **Left/Right Pop**

---

## Optimizations

One key optimization involves improving the hashmap's performance.  
In a hashmap with separate chaining, retrieval can degrade to **O(N)** in the worst case (when a bucket's linked list grows too long).  

To combat this and maintain the **O(1)** average retrieval time, I implemented **hashmap resizing**. When the hashmap exceeds 75% capacity, the following occurs:
1. The number of buckets is doubled.
2. All elements are re-inserted into the new hashmap, reducing the linked list size in each bucket.

This optimization ensures faster retrieval times even as the data grows.

![Resizing Illustration](https://github.com/user-attachments/assets/e91f7474-46da-4bce-8769-e98b8cf1dc8d)

---

## Testing

### Memory Management
One of the challenges of using C is dynamic memory allocation, which can lead to memory leaks.  
To prevent memory leaks, I tested all data structures with **Valgrind**, ensuring that all allocated memory is freed appropriately.

### Unit Testing
To ensure all implemented data structures work as intended, I wrote unit tests using the **Criterion** testing framework.  
This added an extra layer of verification for the correctness and stability of the program.

---

## Lessons Learned

Throughout the development process of this project, here are a few key takeaways:

1. **Development Environment:** Working with C on Linux is significantly easier than on Windows due to better support for tools like Valgrind and GCC.
2. **Memory Management:** Properly managing memory in C is both challenging and crucial. Using tools like Valgrind helped me identify and fix potential leaks and dangling pointers.
3. **Testing Frameworks:** Incorporating a unit testing framework such as Criterion greatly improved the development process by enabling robust testing for each component of the program.
4. **Data Structures in Depth:** Implementing data structures from scratch reinforced my understanding of their internal workings and helped me appreciate their performance trade-offs in real-world scenarios.
5. **Resizing Strategies:** Implementing a resizing mechanism for the hashmap highlighted the balance between complexity and runtime performance.

---

## Future Improvements

Here are some ideas for future improvements:

1. **Networking**: Allow for users to connect to a server via TCP that processes the requests
3. **More Data Structures and Commands**: Expand the program to support more data strucutres such as skip lists and more commands like `ZRANK`, `ZADD`.
