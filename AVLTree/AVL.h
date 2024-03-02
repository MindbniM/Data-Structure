#ifndef AVL 
#define AVL
template<class K,class V>
struct TreeNode
{
    typedef TreeNode<K,V> Node;
    Node* _prante=nullptr;
    Node* _left=nullptr;
    Node* _right=nullptr;
    int _bf=0;
    pair<K,V> _date;
    TreeNode(const pair<K,V>& date)
        :_date(date)
    {
    }
};
template<class K,class V>
class AVLTree 
{
    typedef TreeNode<K,V> Node;
public:
    ~AVLTree()
    {
        drestroy(_root);
    }
    bool insert(const pair<K,V>& date)
    {
        if(_root==nullptr)
        {
            _root=new Node(date);
            return true;
        }
        Node* prante=nullptr;
        Node* root=_root;
        while(root!=nullptr)
        {
            if(date.first> root->_date.first)
            {
                prante=root;
                root=root->_right;
            }
            else if(date.first< root->_date.first)
            {
                prante=root;
                root=root->_left;
            }
            else 
            {
                return false;
            }
         }
        root=new Node(date);
        root->_prante=prante;
         if(date.first> prante->_date.first)
         {
             prante->_right=root;
         }
         else 
         {
             prante->_left=root;
         }
        while(prante)
        {
            if(root==prante->_left)
            {
                prante->_bf--;
            }
            else 
            {
                prante->_bf++;
            }
            if(prante->_bf==1||prante->_bf==-1)
            {
                root=root->_prante;
                prante=prante->_prante;
            }
            else if(prante->_bf==0)
            {
                break;
            }
           else if(prante->_bf==2&&root->_bf==1)
           {
               RotateL(prante);
               break;
           }
           else if(prante->_bf==-2&&root->_bf==-1)
           {
               RotateR(prante);
               break;
           }
           else if(prante->_bf==2&&root->_bf==-1)
           {
               int bf=root->_left->_bf;
               RotateR(root);
               RotateL(prante);
               if(bf==1)
               {
                   root->_bf=1;
               }
               else if(bf==-1)
               {
                   prante->_bf=-1;
               }
          }
           else if(prante->_bf==-2&&root->_bf==1)
           {
               int bf=root->_right->_bf;
               RotateL(root);
               RotateR(prante);
               if(bf==1)
               {
                   root->_bf=-1;
               }
               else if(bf==-1)
               {
                   prante->_bf=1;
               }
           }
        }
        return true;
    }
    void order()
    {
        if(_root==nullptr)
            return;
        int i=1,j=0;
        stack<Node*> st;
        Node* root=_root;
        st.push(root);
        while(!st.empty())
        {
            Node* top=st.top();
            cout<<(top->_date.first)<<" ";
            st.pop();
            i--;
            if(top->_right!=nullptr)
            {
                st.push(top->_right);
                j++;
            }
            if(top->_left!=nullptr)
            {
                st.push(top->_left);
                j++;
            }
            if(i==0)
            {
                cout<<endl;
                i=j;
                j=0;
            }
        }
        cout<<endl;
    }
private:
    void RotateL(Node* root)
    {
        Node* prante=root->_prante;
        Node* cur=root->_right;
        Node* curL=cur->_left;
        root->_right=curL;
        if(curL!=nullptr)
        {
            curL->_prante=root;
        }
        cur->_prante=prante;
        if(root==_root)
        {
            _root=cur;
        }
        else 
        {
            if(prante->_left==root)
            {
                prante->_left=cur;
            }
            else 
            {
                prante->_right=cur;
            }
        }
        cur->_left=root;
        root->_prante=cur;
        root->_bf=0;
        cur->_bf=0;
    }
    void RotateR(Node* root)
    {
        Node* prante=root->_prante;
        Node* cur=root->_left;
        Node* curR=cur->_right;
        root->_left=curR;
        if(curR!=nullptr)
        {
            curR->_prante=root;
        }
        cur->_prante=prante;
        if(root==_root)
        {
            _root=cur;
        }
        else 
        {
            if(prante->_left==root)
            {
                prante->_left=cur;
            }
            else 
            {
                prante->_right=cur;
            }
        }
        cur->_right=root;
        root->_prante=cur;
        root->_bf=0;
        cur->_bf=0;
    }
    void drestroy(Node* root)
    {
        if(root==nullptr)
            return;
        drestroy(root->_left);
        drestroy(root->_right);
        delete root;
    }
    Node* _root=nullptr;
};
#endif 
