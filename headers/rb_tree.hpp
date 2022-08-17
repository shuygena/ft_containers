#ifndef RB_TREE_HPP
#define RB_TREE_HPP

#define BLACK 0
#define RED 1

#include <iostream>
#include "iterator.hpp"
#include "node_iterator.hpp"
#include "utils.hpp"


namespace ft
{
    template <class value_type>
        struct node{
            value_type key_value;
            bool color;
            struct node *left; // <value_type>
            struct node *right; // <value_type>
            struct node *parent; // <value_type>
            bool nil;

            node(): key_value(value_type()), color(BLACK),
                left(this), right(this), parent(0), nil(1){}
            node(const value_type& key_value): key_value(value_type(key_value)), 
                color(BLACK), left(this), right(this), parent(0), nil(0){}
            ~node() {}
    };

    template <class value_type>
        class tree{
        public:
        typedef typename value_type::first_type	    key_type;
        typedef typename value_type::second_type    mapped_type;

        private:
            node <value_type> const_nil;
            node <value_type> *root;
            size_t tsize;
            
        public:
            tree<value_type>(){
                tsize = 0;
                root = &const_nil;
                const_nil.color = BLACK;
                const_nil.nil = true;
                const_nil.parent = 0;
                const_nil.left = &const_nil;
                const_nil.right = &const_nil;
                }
                
            tree(tree<value_type> &x){  
                tsize = 0;
                root = const_nil;
                const_nil.color = BLACK;
                const_nil.nil = (x == x);
                const_nil.parent = 0;
                const_nil.left = const_nil;
                const_nil.right = const_nil;
                }

            tree& operator=(const tree<value_type> &x){ //  
                if (this != &x){
                    root = x.root;
                    const_nil = x.const_nil;
                    tsize = x.tsize;
                    }
                    return *this;
                }
            
            ~tree(){}

            node<value_type> *next(node<value_type> *tmp) const{
            node<value_type> *current = tmp;
            if (current->nil == 0){
                if (current->right->nil == 0){
                    current = current->right;
                    while (current->left->nil == 0)
                        current = current->left;
                    return current;
                }
                else{
                    node<value_type> *parent = current->parent;
                    while(parent->nil == 0 && current == parent->right)
                    {
                        current = parent;
                        parent = parent->parent;
                    }
                    current = parent;
                    return current;
                }  
            }
                return current;
            }

            bool operator==(const tree<value_type> &x) const{
            if (x.size() != size())
                return false;
            size_t distance = size();
            node <value_type> *it1= begin();
            node <value_type> *it2 = x.begin();
            for (size_t i = 0; i != distance; i++){
                if ((it1->key_value.first != it2->key_value.first ) ||
                    (it1->key_value.second != it2->key_value.second))
                    return false;
                it2 = next(it2);
                it1 = next(it1);
            }
            return true;
            }

            bool operator<(const tree<value_type> &x) const{
            size_t distance = (size() < x.size()) ? size() : x.size();
            node <value_type> *it1= begin();
            node <value_type> *it2 = x.begin();
            for (size_t i = 0; i != distance; i++){
                if (it1->key_value.first != it2->key_value.first)
                    return (it1->key_value.first < it2->key_value.first);
                if (it1->key_value.second != it2->key_value.second)
                    return (it1->key_value.second < it2->key_value.second);
                it2 = next(it2);
                it1 = next(it1);
            }
            return (size() < x.size());
            }
            

            void left_rotate(node <value_type> *x){
                node <value_type> *y = x->right;
                x->right = y->left;

                if (y->left->nil == false)
                    y->left->parent = x;
                y->parent = x->parent;
                if (x->parent->nil)
                    root = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else
                    x->parent->right = y;
                y->left = x;
                x->parent = y;
            }

            void right_rotate(node <value_type> *x){
                node <value_type> *y = x->left;
                x->left = y->right;

                if (y->right->nil == false)
                    y->right->parent = x;
                y->parent = x->parent;
                if (x->parent->nil)
                    root = y;
                else if (x == x->parent->right)
                    x->parent->right = y;
                else
                    x->parent->left = y;
                y->right = x;
                x->parent = y;          
            }

            void insert(const value_type &kv, node <value_type> *x){
                if (x == 0)
                    x = root;
                node <value_type> *z = new node<value_type>(kv);
                node <value_type> *y = &const_nil;
                while (x->nil == false)
                {
                    y = x;
                    if (z->key_value.first < x->key_value.first)
                        x = x->left;
                    else
                        x = x->right;
                }
                z->parent = y;
                if (y->nil)
                    root = z;
                else if (z->key_value.first < y->key_value.first)
                    y->left = z;
                else
                    y->right = z;
                z->left = &const_nil;
                z->right = &const_nil;
                z->color = RED;
                tsize++;
                insert_fixup(z);
            }

            void insert_fixup(node <value_type> *z)
            {
                node <value_type> *y;

                while (z->parent->color == RED){
                    if (z->parent == z->parent->parent->left){
                        y = z->parent->parent->right;
                        if (y->color == RED){
                            z->parent->color = BLACK;
                            y->color = BLACK;
                            z->parent->parent->color = RED;
                            z = z->parent->parent;
                        }
                        else {
                            if (z == z->parent->right){
                                z = z->parent;
                                left_rotate(z);
                            }
                            z->parent->color = BLACK;
                            z->parent->parent->color = RED;
                            right_rotate(z->parent->parent);
                        }   
                    }
                    else{
                        y = z->parent->parent->left;
                        if (y->color == RED){
                            z->parent->color = BLACK;
                            y->color = BLACK;
                            z->parent->parent->color = RED;
                            z = z->parent->parent;
                        }
                        else {
                            if (z == z->parent->left){
                                z = z->parent;
                                right_rotate(z);
                            }
                            z->parent->color = BLACK;
                            z->parent->parent->color = RED;
                            left_rotate(z->parent->parent);
                        }
                    }
                }
                root->color = BLACK;
                const_nil.parent = last();   
            }

            void transplant(node <value_type> *u, node <value_type> *v){ 
                if (u->parent->nil == true)
                    root = v;
                else if (u == u->parent->left)
                    u->parent->left = v;
                else
                    u->parent->right = v;
                v->parent = u->parent;
            }

            void rb_delete(node <value_type> *z){
                node <value_type> *y = z;
                node <value_type> *x;
                bool y_color = y->color;
                if (z->left->nil == true){
                    x = z->right;
                    transplant(z, z->right);
                }
                else if (z->right->nil){
                    x = z->left;
                    transplant(z, z->left);
                }
                else{
                    y = z->right;
                    while (y->left->nil == 0)
                        y = y->left;
                    y_color = y->color;
                    x = y->right;
                    if (y->parent == z)
                        x->parent = y;
                    else{ 
                        transplant(y, y->right);
                        y->right = z->right;
                        y->right->parent = y;
                    }
                    transplant(z, y);
                    y->left = z->left;
                    y->left->parent = y;
                    y->color = z->color;
                }
                tsize--;
                if (y_color == BLACK)
                    delete_fixup(x);
                delete z;    
            }

            void delete_fixup(node <value_type> *x){
                node <value_type> *w;
                while (x != root && x->color == BLACK){
                    if (x == x->parent->left){
                        w = x->parent->right;
                        if (w->color == RED){
                            w->color = BLACK;
                            x->parent->color = RED;
                            left_rotate(x);
                            w = x->parent->right;
                        }
                        if (w->left->color == BLACK && w->right->color == BLACK){
                            w->color = RED;
                            x = x->parent;
                        }
                        else 
                            if (w->right->color == BLACK){
                                w->left->color = BLACK;
                                w->color = RED;
                                right_rotate(w);
                                w = x->parent->right;
                            }
                            w->color = x->parent->color;
                            x->parent->color = BLACK;
                            w->right->color = BLACK;
                            left_rotate(x->parent);
                            x = root;
                    }
                    else{
                        w = x->parent->left;
                        if (w->color == RED){
                            w->color = BLACK;
                            x->parent->color = RED;
                            right_rotate(x);
                            w = x->parent->left;
                        }
                        if (w->right->color == BLACK && w->left->color == BLACK){
                            w->color = RED;
                            x = x->parent;
                        }
                        else 
                            if (w->left->color == BLACK){
                                w->right->color = BLACK;
                                w->color = RED;
                                left_rotate(w);
                                w = x->parent->left;
                            }
                            w->color = x->parent->color;
                            x->parent->color = BLACK;
                            w->left->color = BLACK;
                            right_rotate(x->parent);
                            x = root;
                    }
                }
                x->color = BLACK;
                const_nil.parent = last(); 
            }

        /*void printBT(const std::string& prefix, const node<value_type>* nodeV, bool isLeft) const
		{
				std::cout << prefix;

				std::cout << (isLeft ? "├──" : "└──" );
				
                
				if (nodeV->nil){
					std::cout <<"\033[0;36m"<< "nil" << "\033[0m"<<std::endl;
					return ;
				}
                
				// print the value of the node
				if (nodeV->color == 0)
					std::cout <<"\033[0;36m"<< nodeV->key_value.first <<"\033[0m"<<std::endl;
				else
					std::cout <<"\033[0;31m"<< nodeV->key_value.first << "\033[0m"<<std::endl;
				printBT( prefix + (isLeft ? "│   " : "    "), nodeV->left, true);
				printBT( prefix + (isLeft ? "│   " : "    "), nodeV->right, false);		
		}

        void printTree(){
			printBT("" , root, false);
		}*/

        size_t size() const{
            return tsize;
        }

        node<value_type> *begin(){
            node <value_type> *tmp = root;
            while (tmp->left->nil == 0)
                tmp = tmp->left;
            return tmp;
        }
        node<value_type> *begin() const{
            node <value_type> *tmp = root;
            while (tmp->left->nil == 0)
                tmp = tmp->left;
            return tmp;
        }

        node<value_type> *last(){
            node <value_type> *tmp = root;
            while (tmp->right->nil == 0)
                tmp = tmp->right;
            return tmp;
        }

        node<value_type> *last() const{
            node <value_type> *tmp = root;
            while (tmp->right->nil == 0)
                tmp = tmp->right;
            return tmp;
        }

        node<value_type> *search(key_type z){
                node <value_type> *y = &const_nil;
                node <value_type> *x = root;
                while (x->nil == false)
                {
                    y = x;
                    if (x->key_value.first == z)
                        return x;
                    if (z < x->key_value.first)
                        x = x->left;
                    else
                        x = x->right;
                }
                return x;
        }

        node<value_type> *end(){
            node <value_type> *tmp = root;
            while (tmp->right->nil == 0)
                tmp = tmp->right;
            return tmp->right;
        }

        node<value_type> *end() const{
            node <value_type> *tmp = root;
            while (tmp->right->nil == 0)
                tmp = tmp->right;
            return tmp->right;
        }
        };
}

#endif