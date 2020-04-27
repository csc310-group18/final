#include "list.h"
#include "customErrorClass.h"

/**************************** PUBLIC: Constructor ****************************/
list::list()
{
    this->p_Head = nullptr;
    this->p_Tail = nullptr;
    this->p_IsSorted = 1;
}

/**************************** PUBLIC: Destructor ****************************/
list::~list(void)
{
    this->deleteList();
}

/*****************************************************************************************/
/*                                                                                       */
/*                                   PUBLIC FUNCTIONS                                    */
/*                                                                                       */
/*****************************************************************************************/

/**************************** PUBLIC: appendEmployee ****************************/
int list::appendEmployee(s_EMPLOYEE employee)
{
    int retVal = 2;
    try
    {
        p_InsertNode(employee);
        retVal = 0;
    }
    catch(myException &e)
    {
        cerr << e.what() << endl;
    }

    return retVal;
}

/**************************** PUBLIC: deleteList ****************************/
int list::deleteList(void)
{
    int retVal = 1;
    
    try
    {
        this->p_DeleteList();
    }
    catch (myException &e)
    {
        throw e;
    }
    catch (exception &e)
    {
        string msg = e.what();
        throw myException(msg, SYSTEM_FAILURE);
    }
    
    return retVal;
}

/**************************** PUBLIC: printList ****************************/
int list::printList()
{
    int retVal = 1;

    try
    {
        s_NODE *walker = p_GetHead();

        while (walker != nullptr)
        {
            // Print node value
            cout << walker->employee.department << " ";
            cout << walker->employee.number << " ";
            cout << walker->employee.name << endl;

            walker = walker->next;
        }
    }
    catch (myException &e)
    {
        //string msg = "Print failure. " + e.what();
        //throw myException(msg, WARNING);
        cout << "<empty list>" << endl;

    }

    retVal = 0;
    return retVal;
}

/**************************** PUBLIC: sortList ****************************/
void list::sortList(void)
{
    try 
    {
        this->p_InsertionSort();
    }
    catch (myException &e)
    {
        throw e;
    }
}

/**************************** PUBLIC: isSorted ****************************/
int list::isSorted()
{
   return this->p_IsSorted;
}

/**************************** PUBLIC: getTotalNodes ****************************/
int list::getTotalNodes()
{
   return this->p_TotalNodes;
}

/**************************** PUBLIC: getTotalNodes ****************************/
node* list::getHead()
{
   return p_GetHead();
}


/*****************************************************************************************/
/*                                                                                       */
/*                                  PRIVATE FUNCTIONS                                    */
/*                                                                                       */
/*****************************************************************************************/

/**************************** PRIVATE: p_CreateNode ****************************/
s_NODE *list::p_CreateNode(s_EMPLOYEE employee)
{
    s_NODE *newNode;

    // Ensure memory is allocated correctly
    try
    {
        // allocate memory
        newNode = new node;

        // initialize values
        newNode->next = nullptr;
        newNode->previous = nullptr;
        newNode->employee = employee;
    }
    catch (bad_alloc &e)
    {
        string msg = "Failed to allocate memory on employee: " + string(employee.name) + ". Exiting.";
        throw myException(msg, SYSTEM_FAILURE);
    }
    catch (exception &e)
    {
        throw myException(e.what(), SYSTEM_FAILURE);
    }

    return newNode;
}

/**************************** PRIVATE: p_DeleteList ****************************/
int list::p_DeleteList(void)
{
    s_NODE *walker = this->p_Head;
    s_NODE *tmp;

    while (walker != nullptr)
    {
        tmp = walker;
        walker = walker->next;        
        try
        {
            p_DeleteNode(tmp);
        }
        catch (myException &e)
        {
            string msg = e.what();
            throw myException(msg, SYSTEM_FAILURE);
        }
        catch (exception &e)
        {
            string msg = e.what();
            throw myException(msg, SYSTEM_FAILURE);
        }
    }

    return 0;
}

/**************************** PRIVATE: p_DeleteNode ****************************/
int list::p_DeleteNode(s_NODE *nodeToDelete)
{
    int retVal = 1;
    
    //cout << "\tDeleting value: " << nodeToDelete->value << endl;

    // Delete the appropriate connections
    if (nodeToDelete->previous != nullptr && nodeToDelete->next != nullptr) // internal node
    {
        nodeToDelete->next->previous = nodeToDelete->previous;
        nodeToDelete->previous->next = nodeToDelete->next;
    }
    else if (nodeToDelete->next != nullptr) // first node
    {
        this->p_Head = nodeToDelete->next;
        p_Head->previous = nullptr;
    }
    else if (nodeToDelete->previous != nullptr) // last node
    {
        p_Tail = nodeToDelete->previous;
        p_Tail->next = nullptr;
    }
    else // single node
    {
        p_Head = nullptr;
        p_Tail = nullptr;
    }

    // Deallocate memory
    delete nodeToDelete;

    retVal = 0;
    return retVal;
}

/**************************** PRIVATE: p_GetHead ****************************/
s_NODE *list::p_GetHead()
{
    if (this->p_Head != nullptr)
    {
        return this->p_Head;
    }
    else
    {
        throw myException("List is empty.", WARNING);
    }
}

/**************************** PRIVATE: p_GetTail ****************************/
s_NODE *list::p_GetTail()
{
    if (this->p_Tail != nullptr)
    {
        return this->p_Tail;
    }
    else
    {
        throw myException("Tail is null", WARNING);
    }
}

/**************************** PRIVATE: p_InsertNode ****************************/
int list::p_InsertNode(s_EMPLOYEE employee)
{
    int retVal = 2; // WARNING

    s_NODE *newNode;

    try
    {
        newNode = p_CreateNode(employee);
    }
    catch (myException &e)
    {
        e_CODES errCode = e.retrieveCode();
        
        if (errCode == SYSTEM_FAILURE) // print message and exit
        {
            cout << e.what();
            exit(int(SYSTEM_FAILURE));
        } 
        else
        {
            throw e; // throw exception on less serious error
        }
    }
    
    s_NODE *walker = p_Head;

    if (walker == nullptr)
    {
        p_Head = newNode;
    }
    else
    {
        p_Tail->next = newNode;   
        newNode->previous = p_Tail;
    }
    
    p_Tail = newNode;
    
    // Declare unsorted if new node's employee number is less than previous
    if (p_IsSorted == 1 && p_Tail->previous != nullptr &&
        p_Tail->previous->employee.number > p_Tail->employee.number)
    {
        p_IsSorted = 0;
    }
    
    p_TotalNodes++;
    retVal = 0;

    return retVal;
}

/**************************** PRIVATE: p_InsertionSort ****************************/
// Sort by employee number

int list::p_InsertionSort()
{
    int retVal = 2;

    if (this->p_IsSorted != 1) // don't bother if already sorted
    {
        try
        {
            s_NODE *current = nullptr;
            s_NODE *walker = nullptr;    
            s_EMPLOYEE hold;

            for (current = p_GetHead()->next; current != nullptr; 
                current = current->next) 
            {
                
                hold = current->employee;

                for (walker = current->previous; 
                    walker != nullptr && hold.number < walker->employee.number; 
                    walker = walker->previous) 
                {
                    walker->next->employee = walker->employee;
                    
                }

                if (walker == nullptr)
                {
                    p_GetHead()->employee = hold;
                }
                else
                {
                    walker->next->employee = hold;
                }  

            } 
        }
        catch (exception &e)
        {
            // Repackage generic exception as myException
            string msg = "Sorting failure. " + string(e.what());
            throw myException(msg, ERROR);
        }    
    }

    retVal = 0;
    this->p_IsSorted = 1;

    return retVal;
}
