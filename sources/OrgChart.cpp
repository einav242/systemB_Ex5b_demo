#include "OrgChart.hpp"
using namespace std;
namespace ariel
{


    OrgChart &OrgChart::add_root(string const &value)
    {
        if (root == nullptr) //if there is not root create one
        {
            this->root = new Node(value);
            this->data.push_back(this->root);
        }
        else
        {
            this->root->info = value; //if there is a root change the value
        }
        this->root->depth=0;
        return *this;
    }

    OrgChart &OrgChart::add_sub(string const &value1, string const &value2)
    {
        bool check = false;
        for (unsigned int i=0;i<this->data.size(); i++) //we will go through the whole tree with the iterator to find the right node
        {
            if (this->data[i]->info == value1)
            {
                Node *child = new Node(value2); //create a new node
                this->data.push_back(child);
                data[i]->children.push_back(child);
                child->depth=data[i]->depth+1;
                child->parent=data[i];
                check = true; //we dont need to throw exception
                break;
            }
        }
        if (!check) //If we did not find the requested Node we would throw an exception
        {
            throw std::invalid_argument("value does not exit");
        }
        return *this;
    }

    void OrgChart::iterator::create_vec_level_order(Node *ptr = nullptr)
    {
        /*
            To go through the tree in this method we will use a queue, 
            each time we enter a Node and its children and 
            we take out the first Node we entered
        */
        this->iter.clear();
        if (ptr != nullptr)
        {
            vector<Node *> queue;
            this->iter.clear();
            queue.push_back(this->pointer_to_current_node);
            this->iter.push_back(this->pointer_to_current_node);
            while (!queue.empty())
            {
                Node *tmp = queue[0];
                queue.erase(queue.begin());
                for(unsigned int i=0;i<tmp->children.size();i++)
                {
                    this->iter.push_back(tmp->children[i]);
                    queue.push_back(tmp->children[i]);
                }

            }
        }
    }

    void OrgChart::iterator::create_vec_reverse_order(Node *ptr = nullptr)
    {
        /*
         To go through the tree in this method we will use a queue only this
         time every time we enter to the vector a node we will enter from 
        the beginning and so whoever enters last will be the first
        */
               if (ptr != nullptr)
        {
            this->iter.clear();
            vector<Node *> queue;
            queue.push_back(this->pointer_to_current_node);
            while (!queue.empty())
            {
                 Node *tmp = queue[queue.size()-1];
                 this->iter.insert(this->iter.begin(), tmp);
                 queue.erase(queue.begin()+(int)queue.size()-1);
                 for(unsigned int i=0;i<tmp->children.size();i++)
                 {
                     unsigned int j=tmp->children.size()-1-i;
                     queue.insert(queue.begin(),tmp->children[j]);
                 }
            }            
            this->pointer_to_current_node = this->iter[0];
        }
    }

    void OrgChart::iterator::create_vec_preorder(Node *ptr = nullptr)
    {
        /*
        To go through the tree in this method we will use a stack, 
        which means that each time we insert 
        the Node and its children and remove the one we inserted last.
        */
        if (ptr != nullptr)
        {
            this->iter.clear();
            vector<Node *> stack;
            stack.insert(stack.begin(), this->pointer_to_current_node);
            while (!stack.empty())
            {
                Node *tmp = stack[0];
                this->iter.push_back(tmp);
                stack.erase(stack.begin());
                for(unsigned int i=0;i<tmp->children.size();i++)
                {
                    unsigned int j=tmp->children.size()-1-i;
                     stack.insert(stack.begin(), tmp->children[j]);
                }

            }
        }
    }

    OrgChart::iterator &OrgChart::iterator::operator++() //We will first advance the index and then send the iterator back
    {
        if(index==this->iter.size()-1)
        {
            this->pointer_to_current_node=nullptr;
            return *this;
        }
        this->index++;
        this->pointer_to_current_node = this->iter[this->index];
        return *this;
    }

    OrgChart::iterator OrgChart::iterator::operator++(int a) //We will first send the iterator back and then advance the index
    {
        if(index==this->iter.size()-1)
        {
            this->pointer_to_current_node=nullptr;
            return *this;
        }
        iterator tmp=*this;
        index++;
        return tmp;
    }

    bool OrgChart::iterator::operator==(const iterator &rhs) const //We will check if the two pointers are points for the same address
    {
        return pointer_to_current_node == rhs.pointer_to_current_node;
    }

    bool OrgChart::iterator::operator!=(const iterator &rhs) const
    {
        return pointer_to_current_node != rhs.pointer_to_current_node;
    }

    string &OrgChart::iterator::operator*() const //return the value of the current node
    {
        return pointer_to_current_node->info;
    }

    string *OrgChart::iterator::operator->() const //return a pointer to the value of the current node
    {
        return &(this->pointer_to_current_node->info);
    }

    OrgChart::iterator OrgChart::begin() const//so we can go throw the tree
    {
        if(root==nullptr)
        {
            throw std::invalid_argument("value does not exit");
        }
        return iterator{"level", root};
    }

    OrgChart::iterator OrgChart::end()const
    {
        if(root==nullptr)
        {
            throw std::invalid_argument("value does not exit");
        }
        return iterator{"level", nullptr};
    }

    OrgChart::iterator OrgChart::begin_level_order() const
    {
        if(root==nullptr)
        {
            throw std::invalid_argument("value does not exit");
        }
        return iterator{"level", root};
    }

    OrgChart::iterator OrgChart::end_level_order() const
    {
        if(root==nullptr)
        {
            throw std::invalid_argument("value does not exit");
        }
       return iterator{"level", nullptr};
        // return nullptr;
    }

    OrgChart::iterator OrgChart::begin_reverse_order() const
    {
        if(root==nullptr)
        {
            throw std::invalid_argument("value does not exit");
        }
        return iterator{"reverse", root};
    }

    OrgChart::iterator OrgChart::reverse_order()const
    {
        if(root==nullptr)
        {
            throw std::invalid_argument("value does not exit");
        }
        return iterator{"reverse", nullptr};
    }

    OrgChart::iterator OrgChart::begin_preorder()const
    {
        if(root==nullptr)
        {
            throw std::invalid_argument("value does not exit");
        }
        return iterator{"preorder", root};
    }

    OrgChart::iterator OrgChart::end_preorder()const
    {
        if(root==nullptr)
        {
            throw std::invalid_argument("value does not exit");
        }
        return iterator{"preorder", nullptr};
    }

    ostream &operator<<(ostream &out, const OrgChart &a)
    {
        vector<OrgChart:: Node *> stack;
        stack.insert(stack.begin(), a.root);
        a.root->depth=0;
        const int space=6;
        while (!stack.empty())
        {
            OrgChart:: Node *tmp = stack[0];
            out<<"("<<tmp->depth<<")"<<tmp->info<<"-->";
            stack.erase(stack.begin());
            if (tmp->children.empty())
            {
                out<<"nullptr\n\n";
                unsigned int s=(unsigned int)stack[0]->depth*space+stack[0]->parent->info.size();
                for(unsigned int i=0;i<s;i++)
                {
                    out<<" ";
                }
                if(!stack.empty())
                {
                     out<<"-->";
                }
                continue;
            }
            for(unsigned int i=0;i<tmp->children.size();i++)
            {
                stack.insert(stack.begin(), tmp->children[i]);      
            }
        }
        return out;
    }

}