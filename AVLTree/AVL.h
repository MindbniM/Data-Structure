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
                Node* rl = root->_left;
                int bf=rl->_bf;
                RotateR(root);
                RotateL(prante);

                if(bf==1)
                {
                    rl->_bf = 0;
                    root->_bf=0;
                    prante->_bf = -1;
                }
                else if(bf==-1)
                {
                    rl->_bf = 0;
                    prante->_bf=0;
                    root->_bf = 1;
                }
                break;
            }
            else if(prante->_bf==-2&&root->_bf==1)
            {
                Node* rr = root->_right;
                int bf = rr->_bf;
                RotateL(root);
                RotateR(prante);
                if(bf==1)
                {
                    rr->_bf = 0;
                    root->_bf=-1;
                    prante->_bf = 0;
                }
                else if(bf==-1)
                {
                    rr->_bf = 0;
                    prante->_bf=1;
                    root->_bf = 0;
                }
                break;
            }
            else
            {
                cout << prante->_bf<<endl;
                cout << root->_bf<<endl;
                assert(false);
            }
        }
        return true;
    }
    void inorder()
    {
        _inorder(_root);
    }
    bool isAVLTree()
    {
        int h = 0;
        return _isAVLTree(_root, h);
    }
    void order()
    {
        if(_root==nullptr)
            return;
        int i=1,j=0;
        queue<Node*> st;
        Node* root=_root;
        st.push(root);
        while(!st.empty())
        {
            Node* top=st.front();
            cout<<(top->_date.first)<<" ";
            st.pop();
            i--;
            if(top->_left!=nullptr)
            {
                st.push(top->_left);
                j++;
            }
            if(top->_right!=nullptr)
            {
                st.push(top->_right);
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
    bool _isAVLTree(Node* root,int& h)
    {
        if (root == nullptr)
        {
            h = 0;
            return true;
        }
        int Hleft = 0, Hright = 0;
        if (!_isAVLTree(root->_left, Hleft) || !_isAVLTree(root->_right, Hright))
            return false;
        int n = Hright-Hleft;
        if (abs(n) > 1 || n != root->_bf)
        {
            cout << "bf erory"<<endl;
            cout << root->_date.first << "->" << root->_bf<<endl;
            return false;
        }
        h = Hleft > Hright ? Hleft+1 : Hright+1;
        return true;
    }
    void _inorder(Node* root)
    {
        if (root == nullptr)
            return;
        _inorder(root->_left);
        cout << root->_date.first << " ";
        _inorder(root->_right);
    }
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
            cur->_prante = nullptr;
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
            cur->_prante = nullptr;
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
