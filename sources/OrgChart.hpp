#include <string>
#include <vector>
#include <iostream>
#include <stdexcept>
#include <type_traits>
#include <deque>
#include <iterator>
#include <iostream> // std::cout
#include <vector>
using namespace std;
#pragma once

namespace ariel
{
    class OrgChart
    {
        class Node
        {
        public:
            string info;
            Node *child;
            Node *brother;
            Node *parent;
            vector<Node*>children;
            int depth;
            Node(string const &data)
            {
                this->info = data;
                this->brother = nullptr;
                this->child = nullptr;
                this->parent = nullptr;
                this->depth = -1;
            }
        };

    public:
        Node *root;
        vector<Node *> data;
        OrgChart()
        {
            this->root = nullptr;
        }
        ~OrgChart()
        {
            delete_tree(this->root);
        }
        void delete_tree(Node* node)
        {
            if(node==nullptr)
            {
                return;
            }
            for(unsigned int i=0;i<node->children.size();i++)
            {
                delete_tree(node->children[i]);
            }
            delete node;
        }
        OrgChart(const OrgChart &other)
        {
            this->root = other.root;
            for (unsigned int i = 0; i < other.data.size(); i++)
            {
                this->data.push_back(other.data[i]);
            }
        }

        OrgChart &operator=(const OrgChart &other)
        {
            if (this == &other)
            {
                return *this;
            }
            for (unsigned int i = 0; i < this->data.size(); i++)
            {
                delete data[i];
            }
            this->root=other.root;
            for (unsigned int i = 0; i < other.data.size(); i++)
            {
                this->data.push_back(other.data[i]);
            }
            return *this;
        }
        OrgChart &add_root(string const &value);

        OrgChart &add_sub(string const &value1, string const &value2);

        class iterator
        {
        public:
            vector<Node *> iter;
            Node *pointer_to_current_node;
            unsigned int index;
            string type;
            iterator()
            {
            }
            iterator(string const &order, Node *ptr) //when we call the iterator we will also send the data transfer method
            {
                this->pointer_to_current_node = ptr;
                this->index = 0;
                this->type = order;
                this->iter.clear();
                if (this->type == "level")
                {
                    create_vec_level_order(ptr);
                }
                if (this->type == "reverse")
                {
                    create_vec_reverse_order(ptr);
                }
                if (this->type == "preorder")
                {
                    create_vec_preorder(ptr);
                }
            }
            void create_vec_level_order(Node *ptr);

            void create_vec_reverse_order(Node *ptr);

            void create_vec_preorder(Node *ptr);

            iterator &operator++();

            iterator operator++(int a);

            bool operator==(const iterator &rhs) const;

            bool operator!=(const iterator &rhs) const;

            string &operator*() const;

            string *operator->() const;
        };

        iterator begin() const;

        iterator end() const;

        iterator begin_level_order() const;

        iterator end_level_order() const;

        iterator begin_reverse_order() const;

        iterator reverse_order() const;

        iterator begin_preorder() const;

        iterator end_preorder() const;

        friend ostream &operator<<(ostream &out, const OrgChart &a);
    };
}