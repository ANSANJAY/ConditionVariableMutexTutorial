
An educational repository featuring hands-on examples and tutorials to understand the intricacies of Condition Variables and Mutex in multithreaded programming. This project aims to help developers synchronize threads safely, prevent deadlocks, and ensure efficient resource management

```
                             +--------------------------+
                             |                          |
                             |         Candy Box         |
                             |                          |
                             +-----------+--------------+
                                         |
                            +------------|--------------+
                            |                           |
               +------------+------------+             |
               |                         |             |
            Consumer                  Producer         |
              (You)                  (Your Friend)     |
               |                         |             |
               |                         |             |
   Grab Key & Unlock -------> Fill with Candy -------> Mutex
               |                         |             |
               |                         |             |
  Check if Empty ------> Wait for Candy ------> Condition Variable
               |                         |             |
               |                         |             |
  Take Candy & Lock -----> Signal to Wake ------> Mutex
               |                         |             |
               |                         |             |
    Release Key & Wait -----> Release Key -------> Mutex
               |                         |             |
               |                         |             |
                            +------------|--------------+
                                         |
                             +-----------+--------------+
                             |                          |
                             |         Candy Box         |
                             |                          |
                             +--------------------------+


```