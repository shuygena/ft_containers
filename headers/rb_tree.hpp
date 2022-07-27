#ifndef RB_TREE
#define RB_TREE

#define BLACK 0
#define RED 1

#include <iostream>

namespace ft
{
    template <class T>
        struct node{
            T key_value;
            bool color;
            struct node<T> *left;
            struct node<T> *right;
            struct node<T> *parent;
            bool nil;

            node(): key_value(T()), color(BLACK),
                parent(0), right(this), left(this), nil(1){}
            node(const T& key_value): key_value(new T(key_value)), 
                color(BLACK), parent(0), right(this), left(this), nil(0){}
            ~node() { delete key_value;}
    };

    template <class T>
        class tree{
            node <T> current;
            node <T> *root;
            size_t tsize;
            
        public:
            tree(){
                tsize = 0;
                root = &current;
                current.color = BLACK;
                current.nil = true;
                current.parent = 0;
                current.left = &current;
                current.right = &current;
                }
            // tree(tree<T> &x){
            //     tsize = 0;
            //     root = &current;
            //     current.color = BLACK;
            //     current.nil = true;
            //     current.parent = 0;
            //     current.left = &current;
            //     current.right = &current;
            //     }

            void left_rotate(node <T> *x){
                node <T> *y = x->right;
                x->right = y->left;

                if (y->nil == false)
                    root = y;
                else if (x == x->parent->left)
                    x->parent->left = y;
                else
                    y->left = x;
                x->parent = y;
            }

            void right_rotate(node <T> *x){
                node <T> *y = x->left;
                x->left = y->right;

                if (y->nil == false)
                    root = y;
                else if (x == x->parent->right)
                    x->parent->right = y;
                else
                    y->right = x;
                x->parent = y;                
            }

            void insert(node <T> *z){
                node <T> *y = node<T>();
                node <T> *x = root;
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
                insert_fixup(z);
            }

            void insert_fixup(node <T> *z)
            {
                node <T> *y;

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

            void transplant(node <T> *u, node <T> *v){ //delete 1 element
                if (u->parent->nil == true)
                    root = v;
                else if (u == u->parent->left)
                    u->parent->left = v;
                else
                    u->parent->right = v;
                v->parent = u->parent;
            }

            void rb_delete(node <T> *z){
                node <T> *y = z;
                node <T> *x;
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
                if (y_color == BLACK)
                    delete_fixup(x);
            }

            void delete_fixup(node <T> *x){
                node <T> *w;
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

        };
}

#endif