#include <fstream>
#include "Table.h"
#include "String.h"

using namespace std;

bool isInteger(const String &test)
{
    if (!test.length()) 
        return false;

    if (test[0] != '-' && !isdigit(test[0]))
        return false;

    for (int i = 1; i < test.length(); ++i)
    {
        if (!isdigit(test[i]))
            return false;
    }
    return true;
}

String *Table::operator[](int index) const
{

    if (index >= numCols || index < 0)
    {
        cout << "Table column index is out of bounds." << endl;
        return nullptr;
    }

    Field *cur = fieldHead;
    for (int count = 0; count < index; cur = cur->next, ++count)
        ;
    return cur->column;
}


Table:: Table(const String &name)
{
    Table:: name = name;
    primaryKey = nullptr;
    fieldHead = nullptr;
    numRows = 0;
    numCols = 0;
    tableSize =100;
    return;
}


Table:: Table(ifstream &ifs, const String &name)
{
    Table:: name = name;
    tableSize =100;
    primaryKey = nullptr;
    fieldHead = nullptr;
    numRows = 0;
    numCols = 0;

    String col;
    getline(ifs, col , '\n');
    String row;
    getline(ifs, row , '\n');

    if(stoi(col)==0) return;

    //set field
    Field *PF = fieldHead;

    for(int i=0 ; i < stoi(col); i++)
    {
        bool pri =0;
        String *Fname = new String;
        if(i == stoi(col)-1)
        {
            getline(ifs, *Fname, '\n' );
        }
        else
        {
            getline(ifs, *Fname, ',' );
        }


        if (Fname->substr(0,1) == "*")
        {
            *Fname = Fname->substr(1, Fname->length()-1);
            pri = 1;
        }

        TYPE ft = (stoi(Fname->substr(Fname->length()-1 , 1)) == 0) ? INT : STRING;
        *Fname = Fname->substr(0, Fname->length()-2);

        // make field
        Field *f = new Field;
        f->type = ft;
        f->name = *Fname;
        numCols++;
        String *col = new String[100];
        f->column = col;
        if(pri) primaryKey =f;

        // link field
        if(i==0) 
        {
            fieldHead=f;
            PF = f;
            f->next = nullptr;
        }
        else
        {
            f->next = nullptr;
            PF->next = f;
            PF = PF->next;
        }
        
        delete Fname;
    }

    
    //set record
    Field *p3 = fieldHead;
    for(int i =0; i<stoi(row); i++)
    {
        // get record
        p3 = fieldHead;
        for( int j=0 ; j< numCols; j++)
        {
            String *R = new String; 
            if(j == stoi(col)-1)
            {
                getline(ifs, *R, '\n' );
            }
            else
            {
                getline(ifs, *R, ',' );
            }

            //put record
            p3->column[i] = *R;
            p3=p3->next;
            delete R;
        }
        numRows++;
        
    }
    
    return;
}

 
Table:: ~Table()
{
    Field *p = fieldHead;
    for(; p != nullptr; p = fieldHead)
    {
        fieldHead = p->next;
        delete [] p->column;
        delete p;
    }

    return;
}


void Table:: addRecord(int index, String *record)
{
    
    if(record == nullptr) 
    {
        cout<< "Record is empty.\n";
        return;
    }
    if( (index < 0)|| (index > numRows))
    {
        cout<< "Table row index is out of bounds.\n";
        return;
    }
    //primary key check
    Field *p = fieldHead;
    int p_num =0;
    for(; p!=primaryKey; p =p->next, p_num++);
    if(record[p_num] == "") 
    {
        cout<< "Empty or duplicate primary key.\n";
        return;
    }
    String *p_list = operator[](p_num);
    for(int i =0; i < numRows; i++ )
    {
        if(record[p_num] == p_list[i])
        {
            cout<< "Empty or duplicate primary key.\n";
            return;
        }
    }
    
    // Type mismatch
    Field *p2 = fieldHead;
    for(int i =0; i< numCols ; i++ ,p2 =p2->next)
    {
        if( !(p2->type) &&  !(isInteger(record[i]))  )
        {
            cout<<"Cannot insert non-integer in integer field.\n";
            return;
        }
    }

    //add record
    Field *p3 = fieldHead;
    for(int k=0; p3!=nullptr; p3=p3->next, k++)
    {
        for(int i=numRows; i>index;i--)
        {
            p3->column[i] = p3->column[i-1];
        }
        p3->column[index] = record[k];


        if( numRows+1 == tableSize)
        {
            String *col = new String[100+tableSize];
            for(int j=0 ; j<=numRows ; j++)
            {
                col[j]= p3->column[j];
            }
            delete [] p3->column;  /////
            p3->column = col;
        }
    }
    if(numRows +1 == tableSize)
    {
        tableSize+=100;
    }
    numRows++;
    return;
    
}


void Table:: addField(int index, const String &name, TYPE type)
{
    //check
    if( (index > numCols) || (index < 0) )
    {
        cout <<"Table column index is out of bounds.\n"; return;
    }
    Field *p = fieldHead;
    for( ; p != nullptr; p= p->next)
    {
        if ( p->name == name )
        {
            cout<< "Field with given name already exists in table.\n"; return;
        }
    }

    // create Field
    Field *f = new Field;
    if( fieldHead == nullptr)
    {
        primaryKey = f;
    }
    f->type = type;
    f->name = name;
    numCols++;
    String *col = new String[100];
    f->column = col;

    if(type == INT)
    {
        for(int i=0; i< numRows ; i++)
        {
            col[i] = "0";
        }
    }
    else
    {
        for(int i=0; i< numRows ; i++)
        {
            col[i] = "";
        }
    }    


    //Link Field

    Field *pp = fieldHead;
    if(pp == nullptr)
    {
        pp= f;
        f->next = nullptr;
        fieldHead =f;
        return;
    }
    if(index == 0)
    {
        f->next = pp;
        fieldHead = f;
        return;
    }
    for(int i =1 ; i<index ; i++, pp=pp->next);
    f->next = pp->next;
    pp->next = f;
    return;

}


void Table:: deleteRecord(int row)
{
    if( (row < 0)|| (row >= numRows))
    {
        cout<< "Table row index is out of bounds.\n";
        return;
    }

    Field *p3 = fieldHead;
    for(; p3!=nullptr; p3=p3->next)
    {
        for(int i=row; i<numRows-1 ;i++)
        {
            p3->column[i] = p3->column[i+1];
        }

    }
    numRows--;
    return;
}


void Table:: modifyRecord(int row, int column, const String &newVal)
{
    if( (row < 0)|| (row >= numRows))
    {
        cout<< "Table row index is out of bounds.\n";
        return;
    }
    if( (column < 0)|| (column >= numRows))
    {
        cout<< "Table column index is out of bounds.\n";
        return;
    }

    //primary key check
    Field *p = fieldHead;
    int p_num =0;
    for(; p_num< column; p =p->next, p_num++);
    
    if(newVal == "") 
    {
        cout<< "Empty or duplicate primary key.\n";
        return;
    }
    String *p_list = operator[](p_num);
    if(p_list[row] == newVal) return;
    for(int i =0; i < numRows; i++ )
    {
        if(newVal == p_list[i])
        {
            cout<< "Empty or duplicate primary key.\n";
            return;
        }
    }
    
    // Type mismatch
    Field *p2 = fieldHead;
    for(int i =0; i< column ; i++ ,p2 =p2->next);
    if( (!(p2->type)) &&  (!(isInteger(newVal))) )
    {
        cout<<"Cannot insert non-integer in integer field.\n";
        return;
    }

    //modify record
    p_list[row] = newVal;
    return;
}


void Table:: setPrimaryKey(const String &name)
{
    Field *p = fieldHead;
    for(; p != nullptr; p=p->next)
    {
        if( p->name == name)
        {
            break;
        }
    }
    if(p == nullptr) 
    {
        cout<<"No such field with provided name exists.\n";
        return;
    }

    String *k = new String[numRows];
    for(int i=0; i<numRows ; i++)
    {
        k[i]= p->column[i];
        for(int j=0; j<i; j++)
        {
            if(p->column[j] ==k[i])
            {
                cout<<"Cannot set field with duplicate elements as primary key.\n";
                delete[] k;
                return;
            }
        }
        if( p->column[i] == "")
        {
            cout<<"Cannot set field with empty data as primary key.\n";
             delete[] k;
            return;
        }
    }
    delete[] k;

    primaryKey = p;
    return;
}


void Table:: setColumnIndex(int index, const String &target)
{

    Field *p = fieldHead;
    if( (p == nullptr))
    {
        cout<<"No such field with provided name exists.\n";
        return;
    }

    bool F=0;
    if((p->next==nullptr))
    {
        if(p->name != target)
        {
            cout<<"No such field with provided name exists.\n";
            return;
        }
    }
    else
    {
        for(; p->next != nullptr; p=p->next)
        {
            if(fieldHead->name == target)
            {
                F=1;
                break;
            }
            if( p->next->name == target)
            {
                break;
            }                   
        }
        if(p->next == nullptr) 
        {
            cout<<"No such field with provided name exists.\n";
            return;
        }
    }    

    Field *m = p->next;


    if((index<0)||(index>= numCols))
    {
        cout<<"Table column index is out of bounds.\n";
        return;
    }
    if(F)
    {
        m = fieldHead;
        index++;
    }

    if(F && (index ==1)) 
    {
        return;
    }
    if(index ==0)
    {
        p->next=m->next;
        m->next =fieldHead;
        fieldHead = m;
        return;
    }

    Field *p2 = fieldHead;
    p->next=m->next;
    for(int i=0; i<index-1; p2 = p2->next ,i++);
    if(F)
    {
        fieldHead = m->next;
    }
    m->next=p2->next;
    p2->next=m;
    return;

}


void Table:: deleteField(const String &name)
{

    Field *p = fieldHead;
    if( (p == nullptr))
    {
        cout<<"No such field with provided name exists.\n";
        return;
    }

    bool F=0;
    if((p->next==nullptr))
    {
        if(p->name != name)
        {
            cout<<"No such field with provided name exists.\n";
            return;
        }
        cout<<"Cannot delete primary key field.\n";
        return;
    }
    else
    {
        for(; p->next != nullptr; p=p->next)
        {
            if(fieldHead->name == name)
            {
                F=1;
                break;
            }
            if( p->next->name == name)
            {
                break;
            }                   
        }
        if(p->next == nullptr) 
        {
            cout<<"No such field with provided name exists.\n";
            return;
        }
    }
    

    Field* d = p->next;

    if(F&& (primaryKey==p))
    {
        cout<<"Cannot delete primary key field.\n";
        return;
    }
    else if(F)
    {
        fieldHead = d;
        delete [] p->column;
        delete p;
        numCols--; 
        return;
    }
    
    if( primaryKey == d)
    {
        cout<<"Cannot delete primary key field.\n";
        return;
    }


    p->next = d->next; 
    
    delete [] d->column;
    delete d;
    numCols--;  

    return;
}


Field*  Table:: findField(const String &name) const
{

    Field *n =fieldHead;
    for(; n!=nullptr; n=n->next)
    {
        if(n->name == name)
        {
            return n;
        }
    }

    cout<< "No such field with provided name exists.\n";
    return nullptr;
}


void Table:: sortTable(Field* field)
{
    if(field == nullptr)
    {
        cout<<"Invalid field provided.\n";
        return;
    }

    Field *p;

    String temp;
    if(field->type == 0)
    {
        
        for(int i =0 ; i<numRows-1 ; i++)
        {
            for(int k=0 ; k<numRows-1;k++)
            {
                if( stoi(field->column[k]) > stoi(field->column[k+1]))
                {
                    p= fieldHead;
                    for(; p!=nullptr ; p=p->next)
                    {
                        temp = p->column[k];
                        p->column[k] = p->column[k+1];
                        p->column[k+1] = temp;
                    } 
                }
            }
        }
    }
    else
    {
        for(int i =0 ; i<numRows-1 ; i++)
        {
            for(int k=0 ; k<numRows-1;k++)
            {
                if( field->column[k] >field->column[k+1])
                {
                    p= fieldHead;
                    for(; p!=nullptr ; p=p->next)
                    {
                        temp = p->column[k];
                        p->column[k] = p->column[k+1];
                        p->column[k+1] = temp;
                    }
                }
            }
        }
    }
    return;
}


