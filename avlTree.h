
#ifndef MEVNI_WET1_TREE_H
#define MEVNI_WET1_TREE_H
const int Zero = 0;
const int right = 0;
const int left = 1;
const int no_parent = -1;
const int SUCCESS = 0;
const int Fail = -1;
const int AllocationError = -2;



template<class Id,class DataType>
class Node{
private:
    Id NodeId;
    DataType NodeData;
    int Height;
    int BF;
public:
    Node* LeftSon;
    Node* RightSon;
    Node* Parent;
    Node(Id NodeId,DataType NodeData): NodeId(NodeId),NodeData(NodeData),Height(Zero),BF(Zero)
            ,LeftSon(nullptr),RightSon(nullptr),Parent(nullptr)
    {}
    ~Node(){}
    Node(const Node& node) = default;
    DataType& getData()
    {
        return NodeData;
    }

     Id getId() const
    {
        return NodeId;
    }
    Node* getLeftSon()
    {
        return LeftSon;
    }
    Node* getRightSon()
    {
        return RightSon;
    }
    Node* getParent()
    {
        return Parent;
    }
    int getHeight()
    {
        return Height;
    }
    int getBF()
    {
        return BF;
    }
    void SetHeight(int newHeight)
    {
        Height = newHeight;
    }
    void SetBF(int newBF)
    {
        BF = newBF;
    }

};


template<class Id,class DataType>
class Tree
{
private:
    int TreeSize;
    Node<Id,DataType>* root;
public:
    Node<Id,DataType>* mostLeft;
    Tree():TreeSize(Zero), root(nullptr),mostLeft(nullptr)
    {}
    void updateLeftmost(Node<Id,DataType>* node) {
        if (node == nullptr) {
            return;
        }
        while (node->getLeftSon() != nullptr) {
            node = node->getLeftSon();
        }
        mostLeft = node;
    }
    void DeleteTree(Node<Id,DataType>* CurrNode)
    {
        if(CurrNode==nullptr)
        {
            return;
        } else
        {

            DeleteTree(CurrNode->RightSon);
            DeleteTree(CurrNode->LeftSon);
            delete CurrNode;
        }
    }
    ~Tree()
    {
        DeleteTree(root);
        root = nullptr;
    }
    Tree(const Tree& tree) = default;
    int getSize()
    {
        return TreeSize;
    }
    void setSize(int newSize)
    {
        TreeSize = newSize;
    }
    Node<Id,DataType>* getRoot() const
    {
        return root;
    }
    void SetRoot(Node<Id,DataType>* newRoot)
    {
        root = newRoot;
    }
    void UpdateSize(int Extra)
    {
        TreeSize+=Extra;
        return;
    }


    static void Update(Node<Id,DataType>* node)
    {
        int LeftHeight = 0;
        int RightHeight = 0;
        Node<Id,DataType>* CurrRight = node->getRightSon();
        Node<Id,DataType>* CurrLeft = node->getLeftSon();
        if(CurrRight== nullptr)
        {
            RightHeight = -1;
        }
        else
        {
            RightHeight = CurrRight->getHeight();
        }
        if(CurrLeft== nullptr)
        {
            LeftHeight = -1;
        }
        else
        {
            LeftHeight = CurrLeft->getHeight();
        }
        if(RightHeight>LeftHeight)
        {
            node->SetHeight(RightHeight+1);
        }
        else
        {
            node->SetHeight(LeftHeight+1);
        }
        node->SetBF(LeftHeight-RightHeight);
    }

    void RightRotation(Node<Id,DataType>* node)
    {
        Node<Id,DataType>* Temp = node->LeftSon;
        node->LeftSon = Temp->RightSon;
        if(Temp->RightSon!= nullptr)
        {
            Temp->RightSon->Parent = node;
        }
        Temp->RightSon = node;
        Node<Id,DataType>* CurrParent = node->Parent;
        node->Parent = Temp;
        Temp->Parent = CurrParent;
        if(CurrParent==nullptr)
        {
            SetRoot(Temp);
        }
        else
        {
             Id id = CurrParent->getId();
             Id tempId = Temp->getId();
            if(id < tempId)
            {
                CurrParent->RightSon = Temp;
            }
            else
            {
                CurrParent->LeftSon = Temp;
            }
        }
        Update(node);
        Update(node->Parent);
    }

    void LeftRotation(Node<Id,DataType>* node)
    {
        Node<Id,DataType>* CurrRight = node->RightSon;
        node->RightSon = CurrRight->LeftSon;
        if(CurrRight->LeftSon!=nullptr)
        {
            CurrRight->LeftSon->Parent = node;
        }
        CurrRight->LeftSon = node;
        Node<Id,DataType>* CurrParent = node->Parent;
        node->Parent = CurrRight;
        CurrRight->Parent = CurrParent;
        if(CurrParent==nullptr)
        {
            SetRoot(CurrRight);
        }
        else
        {
            if(CurrParent->getId()< CurrRight->getId())
            {
                CurrParent->RightSon = CurrRight;
            }
            else
            {
                CurrParent->LeftSon = CurrRight;
            }
        }
        Update(node);
        Update(node->Parent);

    }
    static void InOrder(Node<Id,DataType>* node, int* Index, DataType Array[])//PUT IN ARRAY
    {
        if(node==nullptr)
        {
            return;
        }
        InOrder(node->LeftSon,Index,Array);
        Array[*Index] = node->getData();
        (*Index)++;
        InOrder(node->RightSon,Index,Array);
        return;
    }
    void DescendingOrder(Node<Id,DataType>* node, int* Index, DataType Array[])//PUT IN ARRAY
    {
        if(node==nullptr)
        {
            return;
        }
        DescendingOrder(node->RightSon,Index,Array);
        Array[*Index] = node->getData();
        (*Index)++;
        DescendingOrder(node->LeftSon,Index,Array);
        return;
    }

    void RotateIsNeeded(Node<Id,DataType>* CurrNode)
    {
        if((CurrNode->getBF())==2)
        {
            if(CurrNode->getLeftSon()->getBF()==-1)///*
            {
                LeftRotation(CurrNode->LeftSon);
            }
            RightRotation(CurrNode);
            return;
        }
        if((CurrNode->getBF())==-2)
        {
            if(CurrNode->RightSon->getBF()==1)
            {
                RightRotation(CurrNode->RightSon);
            }
            LeftRotation(CurrNode);
            return;
        }
    }

    void TrackTree(Node<Id,DataType>* node)
    {
        Node<Id,DataType>* CurrNode = node;
        while(CurrNode!=nullptr)
        {
            Update(CurrNode);
            RotateIsNeeded(CurrNode);
            CurrNode = CurrNode->Parent;
        }
    }
    Node<Id,DataType>* WhereToAdd(Node<Id,DataType>* CurrRoot,Id NodeId, int* rightORLeft)
    {
        Id id = CurrRoot->getId();
        if(id == NodeId)
        {
            return nullptr;
        }
        if(id< NodeId)
        {
            *rightORLeft = 0;
            if(CurrRoot->RightSon==nullptr)
            {
                return CurrRoot;
            }
            else
            {
                return WhereToAdd(CurrRoot->RightSon,NodeId,rightORLeft);
            }
        }
        if (id > NodeId)
        {
            if(CurrRoot->LeftSon==nullptr)
            {
                return CurrRoot;
            }
            else
            {
                return WhereToAdd(CurrRoot->LeftSon,NodeId,rightORLeft);
            }
        }
        return nullptr;
    }

    int AddNode(Id NodeId, DataType& NodeData)
    {
        Node<Id,DataType>* NewNode = new Node<Id,DataType>(NodeId,NodeData);
        if (NewNode == nullptr){
            return AllocationError;
        }
        if(root==nullptr)
        {
            this->setSize(1);
            SetRoot(NewNode);
            updateLeftmost(root);
            return SUCCESS;
        }
        int CurrSize = this->getSize();
        int IsLeftSon = 1;
        Node<Id,DataType>* NewParent=WhereToAdd(this->root,NodeId, &IsLeftSon);
        if(NewParent==nullptr)//The new node was founded in the tree
        {
            delete NewNode;
            return  Fail;
        }
        Id id = NewParent->getId();
        if(id<NodeId)
        {
            NewParent->RightSon = NewNode;
        }
        if(id>NodeId)
        {
            NewParent->LeftSon = NewNode;
        }
        NewNode->Parent = NewParent;
        this->setSize(CurrSize+1);
        TrackTree(NewNode->Parent);
        updateLeftmost(root);
        return SUCCESS;
    }

    Node<Id,DataType>* FindNode(Id NodeId,Node<Id,DataType>* CurrRoot)
    {
        if(CurrRoot==nullptr)
        {
            return nullptr;
        }
        if(CurrRoot->getId()==NodeId)
        {
            return CurrRoot;
        }
        Node<Id,DataType>* CurrNode=nullptr;
        if(CurrRoot->getId()>NodeId)
        {
            CurrNode = FindNode(NodeId,CurrRoot->LeftSon);
            if(CurrNode!=nullptr)
            {
                return CurrNode;
            }
            return nullptr;
        }
        if(CurrRoot->getId()<NodeId)
        {
            CurrNode = FindNode(NodeId,CurrRoot->RightSon);
            if(CurrNode!=nullptr)
            {
                return CurrNode;
            }
            return nullptr;
        }
        return nullptr;
    }

    Node<Id,DataType>* FindNext(Node<Id,DataType>* start)
    {
        while(start->LeftSon!=nullptr)
        {
            start = start->LeftSon;
        }
        return start;
    }
    Node<Id,DataType>* Biggest(Node<Id,DataType>* start)
    {
        while(start->RightSon!=nullptr)
        {
            start = start->RightSon;
        }
        return start;
    }

    int RemoveNode(Id& NodeId)
    {
        if(this->root==nullptr)
        {
            return Fail;
        }
        int NodeStatus = -2;
        Node<Id,DataType>* NodeToDelete = FindNode(NodeId,getRoot());
        if(NodeToDelete==nullptr)
        {
            return Fail;
        }
        if(NodeToDelete == mostLeft){
            if(mostLeft->LeftSon != nullptr){
                mostLeft = mostLeft->LeftSon;
            }
            else{
                mostLeft = mostLeft->Parent;
            }
        }
        Node<Id,DataType>* NodeParent = NodeToDelete->Parent;
        if(NodeParent==nullptr)
        {
            NodeStatus = no_parent;
        }
        else if(NodeParent->getId()<NodeId)
        {
            NodeStatus = right;
        }
        else
        {
            NodeStatus = left;
        }
        if(NodeToDelete->RightSon==nullptr && NodeToDelete->LeftSon==nullptr)
        {
            if(NodeStatus==left)
            {
                NodeParent->LeftSon = nullptr;
            }
            else if(NodeStatus==right)
            {
                NodeParent->RightSon = nullptr;
            }
            else
            {
                root = nullptr;
            }
        }
        else if(NodeToDelete->RightSon == nullptr)
        {
            if(NodeStatus==right)
            {
                NodeParent->RightSon= NodeToDelete->LeftSon;
            }
            if(NodeStatus==left)
            {
                NodeParent->LeftSon = NodeToDelete->LeftSon;
            }
            if(NodeStatus==no_parent)
            {
                root = NodeToDelete->LeftSon;
            }
            NodeToDelete->LeftSon->Parent= NodeParent;
        }
        else if(NodeToDelete->LeftSon==nullptr)
        {
            if(NodeStatus==right)
            {
                NodeParent->RightSon = NodeToDelete->RightSon;
            }
            if(NodeStatus==left)
            {
                NodeParent->LeftSon = NodeToDelete->RightSon;
            }
            if (NodeStatus==no_parent)
            {
                root = NodeToDelete->RightSon;
            }
            NodeToDelete->RightSon->Parent = NodeParent;
        }
        else
        {
            bool HasNext = false;
            Node<Id,DataType>* ToReplace = FindNext(NodeToDelete->RightSon);
            if(ToReplace != NodeToDelete->RightSon)
            {
                HasNext = true;
            }
            Node<Id,DataType>* TempParent = ToReplace->Parent;
            Node<Id,DataType>* TempRight = ToReplace->RightSon;
            (NodeToDelete->LeftSon)->Parent = ToReplace;
            ToReplace->LeftSon = NodeToDelete->LeftSon;
            ToReplace->Parent = NodeToDelete->Parent;
            if(NodeStatus==right)
            {
                (NodeToDelete->Parent)->RightSon = ToReplace;
            }
            if(NodeStatus==left)
            {
                (NodeToDelete->Parent)->LeftSon = ToReplace;
            }
            if(NodeStatus==no_parent)
            {
                root = ToReplace;
            }
            if(HasNext==true)
            {
                (NodeToDelete->RightSon)->Parent = ToReplace;
                ToReplace->RightSon = NodeToDelete->RightSon;
                TempParent->LeftSon = TempRight;
                if (TempRight != nullptr)
                {
                    TempRight->Parent = TempParent;
                }
                TrackTree(TempParent);
            }
            else
            {
                TrackTree(ToReplace);
            }
            if(NodeToDelete == mostLeft){
                mostLeft = nullptr;
            }
            delete NodeToDelete;
            int CurrSize = this->getSize();
            setSize(CurrSize-1);
            updateLeftmost(root);
            return SUCCESS;
        }
        if(NodeToDelete == mostLeft){
            mostLeft = nullptr;
        }
        delete NodeToDelete;
        int CurrSize = this->getSize();
        setSize(CurrSize-1);
        if(NodeParent==nullptr)
        {
            updateLeftmost(root);
            return SUCCESS;
        }
        TrackTree(NodeParent);
        updateLeftmost(root);
        return SUCCESS;
    }

   /// void debugging_printTree(const std::string& prefix, const Node<Id,DataType>* node, bool isLeft, std::string& str);
    ///void debugging_printTree(const Node<Id,DataType>* node, std::string& str);
    ///std::string debugging_printTree();

};
/**
template<class Id,class DataType>
void Tree<Id,DataType>::debugging_printTree(const std::string& prefix, const Node<Id,DataType>* node, bool isLeft, std::string& str)
{
    if( node != nullptr )
    {
        str += prefix;

        str += (isLeft ? "└──" : "├──" );

        // print the value of the node
        str += std::to_string(node->getId());
        str += "\n";

        // enter the next tree level - left and right branch
        debugging_printTree( prefix + (isLeft ? "    " : "│   "), node->right, false, str);
        debugging_printTree( prefix + (isLeft ? "    " : "│   "), node->left, true, str);
    }
}

template<class Id,class DataType>
void Tree<Id,DataType>::debugging_printTree(const Node<Id,DataType>* node, std::string& str)
{
    debugging_printTree("", node, true, str);
}

template<class Id,class DataType>
std::string Tree<Id,DataType>::debugging_printTree()
{
    std::string tree = "";
    debugging_printTree(root, tree);
    return tree;
}*/

#endif //MEVNI_WET1_TREE_H
