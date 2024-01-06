## Basic Idea: This is a Word Recommender .
Say you are typing : `Messi plays` this algorithm might recommend you `tonight`. 
However this totally depends upon the data in which the model is trained. As of now the 
collected data is mostly Nepali Roman Characters. 

So , If you type in `K cha ` you might get a recommendation of `halkhabar`

### Data Structure Requirement: 
   
   I followed by am -> number of occurence\
		  and -> number of occurence\
		  have -> number of occurence

   am followed by Ram -> number of occurence\
                  a -> number of occurence 

 ### Initial thought
 ```cpp
 std::tuple(std::string, std::unordered_map<std::string, int>) 
 ```
` big Noooo`, we'd then need collection of those tuples.

 why not have a `struct` then and then `std::vector` of those `struct` .

```cpp
 struct Data{
   std::string parent;
   std::unordered_map<std::string, int> predecessors;
 }
```
 and then 
 ```cpp
 std::vector<Data> DataObject; -> sounds ok as of now. 
```
Or should It be tree. I need some more time to decide.

## Implementation Detail
I decided to use something that sounds like a Lookup table. For every new word we encounter in our data set,
we assign a `std::unordered_map<std::string, int>` that holds the frequencies of the next word appearing
after that word which is stored in a `std::vector`. The index of the `std::vector` is 
stored in another `std::unordered_map<std::string, int>` where the key is the word we encounter and value is
the index.
```
{
  "I": Index,
   .
   .
   .
}
LookUp Table:
{
  0 : {
        "word1": count,
	"word2": count
      }
  .
  .
  .
  .
  Index : {
           "word1": count,
	   "word2": count
          }
}
```


## How is a word Recommended
we calculate all the possibilites
 ```
 probability of occurence of am after I = Total occurence of am after I / Total words after I 
```
The one with the higher probability or above some threshold will be recommeded.
