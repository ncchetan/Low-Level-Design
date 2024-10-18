/*
    Directories, sub-directories, files
    File - name,size, extension
    Different Filters - all combinations of AND and OR
    File system -> find API -> all files based on given filters
    
    Entities:
        Node - Composite Design Patetrn
            File
            Directory
        
        Filter - Strategy Design Pattern & Builder - creating finfl filter
            NameFilter
            ......
        
        FileSystem
*/

#include <bits/stdc++.h>

using namespace std;

enum Type {
    F,
    Dir
};

class Node {
public:
    string name;
    Type type;
    int size;
};

class File : public Node {
public:
    string extension;
    File(string name, int size, string extension) {
        this->name = name;
        this->size = size;
        this->extension = extension;
        this->type = Type::F;
    }   
};

class Directory : public Node {
public:
    vector<Node*> children;
    Directory(string name, int size) {
        this->name = name;
        this->children = {};
        this->size = size;
        this->type = Type::Dir;
    }
    
    void add(Node* child) {
        children.push_back(child);
        this->size += child->size;
    }
    
    void remove(Node* child) {
        auto it = find(children.begin(), children.end(), child);
        children.erase(it);
    }
};

class FilterStrategy {
public:
    virtual bool isValid(Node* file) = 0;
};

class NameFilter : public FilterStrategy {
public:
    string name;
    
    NameFilter(string name) : name(name) {
        
    }
    
    bool isValid(Node* file) override {
        return file->name == name;
    }
};

class GreaterOrEqualSizeFilter : public FilterStrategy {
public:
    int size;
    
    GreaterOrEqualSizeFilter(int size) : size(size) {
        
    }
    
    bool isValid(Node* file) override {
        return file->size >= size;
    }
};

class ANDFilter : public FilterStrategy {
public:
    FilterStrategy *f1, *f2;
    
    ANDFilter(FilterStrategy *f1, FilterStrategy *f2) : f1(f1), f2(f2) {
        
    }
    
    bool isValid(Node* file) override {
        return f1->isValid(file) and f2->isValid(file);
    }
};

class ORFilter : public FilterStrategy {
public:
    FilterStrategy *f1, *f2;
    
    ORFilter(FilterStrategy *f1, FilterStrategy *f2) : f1(f1), f2(f2) {
        
    }
    
    bool isValid(Node* file) override {
        return f1->isValid(file) or f2->isValid(file);
    }
};

class DefaultFilter : public FilterStrategy {
public:
    bool isValid(Node* file) override {
        return true;
    }
};

class FilterBuilder {
private:
    FilterStrategy* filter;
public: 
    FilterBuilder() {
        this->filter = new DefaultFilter();
    }
    
    FilterStrategy* andOp(FilterStrategy* newFilter) {
         return this->filter = new ANDFilter(this->filter, newFilter);
    }
    
    FilterStrategy* orOp(FilterStrategy* newFilter) {
         return this->filter = new ORFilter(this->filter, newFilter);
    }    
};

class FileSystem {
public:
    Node* root;
    
    FileSystem(Node* root) : root(root) {
        
    }
    
    void findAPI(Node*root, FilterStrategy* filter, vector<Node*>& searchResults) {
        if(root->type == Type::F) {
            if(filter->isValid(root)) {
                searchResults.push_back(root);
            }
            return;
        }
        
        for(auto& node : ((Directory*)root)->children) {
            findAPI(node, filter, searchResults);
        }              
    }
};

int main() {
    Directory* root = new Directory("/", 0);
    File* f1 = new File("f1", 5, ".txt");
    File* f2 = new File("f2", 3, ".cpp");
    
    NameFilter* namefilter = new NameFilter("f1");
    
    root->add(f1);
    root->add(f2);

    FilterBuilder* builder = new FilterBuilder();
    FilterStrategy* filter = builder->andOp(namefilter);
    
    
    FileSystem* fs = new FileSystem(root);
    vector<Node*> searchResults;
    fs->findAPI(root, filter, searchResults);
    
    for(auto& file : searchResults) {
        cout<<file->name<<endl;
    }
        
    return 0;
}
