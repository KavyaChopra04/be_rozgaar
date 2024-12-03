#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <sstream>
#include <exception>
using Price = double;
using Symbol = std::string;
using Volume = int64_t;
using Id = int64_t;
std::vector<std::string> splitString(const std::string &s, char delimiter)
{
    std::stringstream splitAtChar(s);
    std::vector<std::string> allFields;
    std::string currentField;
    while (std::getline(splitAtChar, currentField, delimiter))
    {
        allFields.push_back(currentField);
    }
    return allFields;    
}
// Timestamps and related logic: constructors and comparators
typedef struct Timestamp
{
    int hours_;
    int minutes_;
    int seconds_;
    int microseconds_;
    Timestamp();
    Timestamp(const std::string &s);
} Timestamp;
Timestamp::Timestamp (const std::string &s)
{
    std::vector<std::string> individualFields = splitString(s, ':');
    hours_ = std::stoi(individualFields[0]);
    minutes_ = std::stoi(individualFields[1]);
    seconds_ = std::stoi(individualFields[2]);
    if(individualFields.size() > 3)
    {
        microseconds_ = std::stoi(individualFields[3]);
    }
}
bool operator ==(const Timestamp &a, const Timestamp &b)
{
    return a.hours_ == b.hours_ && a.minutes_ == b.minutes_ && a.seconds_ == b.seconds_;
}
bool operator < (const Timestamp &a, const Timestamp &b)
{
    return 
        (a.hours_ < b.hours_) || 
        (a.hours_ == b.hours_ && a.minutes_ < b.minutes_) || 
        (a.hours_ == b.hours_ && a.minutes_ == b.minutes_ && a.seconds_ < b.seconds_);
}
class Order{
    enum Side
    {
        BUY,
        SELL
    };
    enum Type
    {
        INSERT,
        CANCEL,
        AMEND
    };
    Side side_;
    Type type_;
    Price price_;
    Symbol symbol_;
    Volume volume_;
    Id id_;
    Timestamp timestamp_;
    Order() {}
    Order(std::unordered_map<std::string, std::string> parsedFields) : 
        price_(std::stod(parsedFields["price"])), 
        symbol_(parsedFields["symbol"]), 
        volume_(std::stoll(parsedFields["volume"])),
        id_(std::stoll(parsedFields["id"])),
        timestamp_(Timestamp(parsedFields["timestamp"]))
    {
        switch(parsedFields["side"][0])
        {
            case('B'):
            {
                side_ = Side::BUY;
                break;
            }
            case('S'):
            {
                side_ = Side::SELL;
                break;
            }
            default : {}
        }
        switch(parsedFields["type"][0])
        {
            case('A'):
            {
                type_ = Type::AMEND;
                break;
            }
            case('I'):
            {
                type_ = Type::INSERT;
                break;
            }
            case('C'):
            {
                type_ = Type::CANCEL;
                break;
            }
            default : {}
        }
    }
    int getKey() const {return id_;}
    void setID(int id){id_ = id;}

};
class IntW{
    public:
    int k;
    int x;
    IntW() : k(0), x(0) {}
    IntW(int k, int x): k(k), x(x){}
    int getKey() {return k;}
};
auto cmp = [](IntW &a, IntW &b) {return a.x > b.x;};

class OrderBook{

    OrderBook(std::vector<std::string> &testData) {}
};
template<typename Value, typename Key, typename CustomComparator>
class IndexedPriorityQueue
{
    std::vector<Value> heapContents;
    std::map<Key, int> keyToIndex;
    void elementSwap(int a, int b)
    {
        keyToIndex[heapContents[a].getKey()] = b;
        keyToIndex[heapContents[b].getKey()] = a;
        std::swap(heapContents[a],heapContents[b]);
    }
    int upheapify(int value_index)
    {
        int parent_index = value_index/2;
        while(parent_index >= 1 && cmp(heapContents[value_index], heapContents[parent_index]))
        {
            elementSwap(value_index, parent_index);
            value_index = parent_index;
            parent_index = value_index/2;
        }
        return value_index;
    }
    int downheapify(int parent_index)
    {
        while(true)
        {
            int child_1_index = 2 * parent_index;
            int child_2_index = 2 * parent_index + 1;
            if(heapContents.size() <= child_1_index) break;
            if(heapContents.size() > child_2_index && cmp(heapContents[child_2_index], heapContents[child_1_index]))
            {
                std::swap(child_1_index, child_2_index);
            }
            if(cmp(heapContents[child_1_index],heapContents[parent_index]))
            {
                elementSwap(child_1_index, parent_index);
                parent_index = child_1_index;
            }
            else
            {
                break;
            }
        }
        return parent_index;
    }
    public:
    IndexedPriorityQueue() {heapContents.push_back(Value());}
    Key getKey(const Value &v)
    {
        return v;
    }
    Value top()
    {
        if (heapContents.size() < 1) return heapContents[0];
        return heapContents[1];
    }
    void pop()
    {        
        elementSwap(heapContents.size() - 1, 1);
        keyToIndex.erase(heapContents[heapContents.size() - 1].getKey());
        heapContents.pop_back();
        downheapify(1);              
    }   
    void update(Value value)
    {
        Key key = value.getKey();
        remove(key);
        insert(value);
    }
    bool presentID(Key key)
    {
        return keyToIndex.find(key) != keyToIndex.end();
    }
    Value getAtID(Key key)
    {
        return heapContents[keyToIndex[key]];
    }
    void insert(Value value)
    {
        Key key = value.getKey();
        int value_index = heapContents.size();
        keyToIndex[key] = value_index;
        heapContents.push_back(value);
        upheapify(value_index);
        downheapify(value_index);        
    }
    void remove(Value value)
    {
        Key key = value.getKey();
        remove(key);
    }
    void remove(Key key)
    {
        if(keyToIndex.find(key) != keyToIndex.end())
        {
            int previous_index = keyToIndex[key];
            elementSwap(heapContents.size() - 1, previous_index);
            heapContents.pop_back();
            downheapify(previous_index);
            upheapify(previous_index);
            keyToIndex.erase(key);
        }
    }
    void print()
    {
        for(auto x: heapContents)
        {
            std::cout<<x.x<<", ";
        }
        std::cout<<std::endl;
        for(auto x: keyToIndex)
        {
            std::cout<<x.first<<": "<<x.second<<", ";
        }
        std::cout<<std::endl;
    }
};

// std::unordered_map<std::string, std::string> 
int main()
{
    IndexedPriorityQueue<IntW,int, decltype(cmp)> pq;
    pq.insert(IntW(5, 10));
    pq.print();
    pq.insert(IntW(7, 8));
    pq.print();
    pq.insert(IntW(9, 5));
    pq.print();
    pq.insert(IntW(17, -1));
    pq.print();
    pq.insert(IntW(11, 95));
    pq.print();
    pq.insert(IntW(15, 110));
    pq.print();
    pq.insert(IntW(17, 18));
    pq.print();
    pq.insert(IntW(19, 15));
    pq.print();
    pq.insert(IntW(117, -11));
    pq.print();
    pq.insert(IntW(111, 195));
    pq.insert(IntW(131, 20));
    pq.print();
    std::cout<<pq.top().x<<std::endl;
    pq.remove(5);
    pq.print();
    std::cout<<pq.top().x<<std::endl;
    if(pq.getAtID(9).x < 71){
    pq.update(IntW(9, 71));};
    pq.print();
    std::cout<<pq.top().x<<std::endl;
    auto obj = pq.getAtID(9);
    std::cout<<obj.k<<" "<<obj.x<<std::endl;
    pq.pop();
    pq.print();
    std::cout<<pq.top().x<<std::endl;
    pq.pop();
    pq.print();
    std::cout<<pq.top().x<<std::endl;
    pq.pop();
    pq.print();
    std::cout<<pq.top().x<<std::endl;
    pq.pop();
    pq.print();
    std::cout<<pq.top().x<<std::endl;

}
