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
        // public:
        //     typedef typename ft::node_iterator<value_type> iterator;
        //     typedef typename ft::node_iterator<const value_type> const_iterator;

        private:
            node <value_type> current;
            node <value_type> *root;
            size_t tsize;
            
        public:
            tree<value_type>(){
                tsize = 0;
                root = &current;
                current.color = BLACK;
                current.nil = true;
                current.parent = 0;
                current.left = &current;
                current.right = &current;
                }
                
            tree(tree <value_type> &x){ // tree<value_type> 
                tsize = 0;
                root = current;
                current.color = BLACK;
                current.nil = (x == x);
                current.parent = 0;
                current.left = current;
                current.right = current;
                }
            // tree& operator=(const tree<value_type> &x){ //  
            //     if (this != x){
            //         if (x->left->nil != )
            //         }
            //         return *this;
            //     }

            // tree& operator=(tree<value_type> &x){
            //     if (this != &x)
            //     {
            //         //clear it
            //         iterator first = iterator(x.begin());
            //         iterator last = (iterator(x.end()))++;
            //         while (first != last)
            //         {
            //             insert(*first);
            //             first++;
            //         }
            //         return *this;
            //     }
            // }
            

            void left_rotate(node <value_type> *x){
                node <value_type> *y = x->right;
                x->right = y->left;

                if (y->nil == false)
                    root = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else
                    y->left = x;
                x->parent = y;
            }

            void right_rotate(node <value_type> *x){
                node <value_type> *y = x->left;
                x->left = y->right;

                if (y->nil == false)
                    root = y;
                else if (x == x->parent->right)
                    x->parent->right = y;
                else
                    y->right = x;
                x->parent = y;                
            }

            void insert(node <value_type> *z){
                node <value_type> *y = node<value_type>();
                node <value_type> *x = root;
                while (x->nil == false)
                {
                    y = x;
                    if (z->key_value < x->key_value)
                        x = x->left;
                    else
                        x = x->right;
                }
                z->parent = y;
                if (y->nil)
                    root = z;
                else if (z->key_value < y->key_value)
                    y->left = z;
                else
                    y->right = z;
                z->left->nil = true;
                z->right->nil = true;
                z->color =  RED;
                tsize++;
                insert_fixup(z);
            }

            void insert_fixup(node <value_type> *z)
            {
                node <value_type> *y;

                while (z->parent->color == RED)
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
                root->color = BLACK;   
            }

            void transplant(node <value_type> *u, node <value_type> *v){ //delete 1 element
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
                    y_color = y->color;
                    x = y->right;
                    if (y->parent == z)
                        x->parent = y;
                    else{ 
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
            }

        void printBT(const std::string& prefix, const node<value_type>* nodeV, bool isLeft) const
		{
				std::cout << prefix;

				std::cout << (isLeft ? "├──" : "└──" );
				
				if (nodeV->nil){
					std::cout <<"\033[0;36m"<< "nil" << "\033[0m"<<std::endl;
					return ;
				}
				// print the value of the node
				if (nodeV->color == 0)
					std::cout <<"\033[0;36m"<< nodeV->key_value<<"\033[0m"<<std::endl;
				else
					std::cout <<"\033[0;31m"<< nodeV->key_value << "\033[0m"<<std::endl;
				printBT( prefix + (isLeft ? "│   " : "    "), nodeV->left, true);
				printBT( prefix + (isLeft ? "│   " : "    "), nodeV->right, false);		
		}

        void size(){
            return tsize;
        }

        node<value_type> *begin(){
            node <value_type> tmp = root;
            while (tmp->left->nil == 0)
                tmp = tmp->left;
            return tmp;
        }

        node<value_type> *end(){
            node <value_type> tmp = root;
            while (tmp->right->nil == 0)
                tmp = tmp->right;
            return tmp;
        }
        };
}

#endif