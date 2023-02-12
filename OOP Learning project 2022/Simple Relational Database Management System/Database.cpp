#include <fstream>
#include <iomanip>
#include <iostream>
#include "Database.h" 
#include "String.h"
#include "Table.h"

using namespace std;

void Database::printTable(Table *table) const
{
    if (table == nullptr)
    {
        cout << "No such table exists in the database." << endl;
        return;
    }

    for (Field *cur = table->getFieldHead(); cur != nullptr; cur = cur->next)
    {
        cout << setw(15) << left;
        String curPrintName = (cur == table->getPrimaryKey() ? "*" : "") + cur->name + ' ' + (cur->type == INT ? "0" : "1");
        cout << curPrintName;
    }
    cout << endl;
    for (int i = 0; i < table->getNumRows(); ++i)
    {
        for (int j = 0; j < table->getNumCols(); ++j)
        {
            cout << setw(15) << left;
            cout << (*table)[j][i];
        }
        cout << endl;
    }

    return;
}

// f C Z
Database:: Database(const String &name, int numTables) 
{   
    Database:: name = name;
    Database:: numTables = numTables;
    currentTable = nullptr;
    tableHead = nullptr;

    if(numTables >0)
    {
        Table *t = new Table( "Table_1" );
        tableHead = t;
    }
    else
    {
        return;
    }
    

    Table *p = tableHead;

    for( int i=2; i<=numTables; i++)
    {
        char buffer[10];
        snprintf(buffer, 10, "%d", i);
        String T = "Table_";
        T = T + buffer;
        Table *t = new Table( T );
        
        p->next = t;
        p = p->next;
        
    }
    p->next = nullptr;

    return;
}

// f C z
Database:: Database(const String &filename)
{

    currentTable = nullptr;
    tableHead = nullptr;

    const char *cstr = filename.getStr();
    ifstream iss( cstr);
    String Dname;
    getline( iss, Dname, '\n');
    Database:: name = Dname;
    String numT; 
    getline( iss, numT, '\n');
    Database:: numTables = stoi(numT);

    // create Table
    Table *p= tableHead;
    for(int i =0; i< stoi(numT); i++)
    {
        String Tname; 
        getline( iss, Tname, '\n');
        Table *t = new Table(iss, Tname);
        
        if(i==0)
        {
            tableHead = t;
            t->next = nullptr;
            p = t;
        }
        else
        {
            t-> next = nullptr;
            p->next = t;
            p=t;
        }
    }

    return;

}

// f c z
Database:: ~Database()
{

    Table *p = tableHead;
    for(; p!=nullptr ; p= tableHead)
    {
        tableHead = p->next;
        delete p;
    }
    
    return;
}

// f  C Z
bool Database:: addTable(Table *table)
{

    if( table == nullptr )
    {
        cout<<"Table is a null pointer.\n";
        return false;
    }

    Table *p = tableHead;
    for( ; p!= nullptr; p= p->next)
    {
        if (p->getName() == table->getName())
        {
            cout<< "Table with given name already exists in the database.\n";
            return false;
        }
    }

    Table *pp = tableHead;
    if(pp == nullptr)
    {
        pp = table;
        pp->next = nullptr;
        tableHead = table;
        numTables++;
        return true;
    }
    
    for(;pp->next != nullptr; pp= pp->next);
    pp->next = table;
    pp->next->next = nullptr;
    numTables++;
    return true;

}

//f C Z
void Database::addTable(const String &name)
{
    
    Table *p = tableHead;
    for( ; p != nullptr; p= p->next)
    {
        if (name == p->getName())
        {
            cout<< "Table with given name already exists in the database.\n";
            return;
        }
    }
    Table *add = new Table(name);

    Table *pp = tableHead;
    if(pp == nullptr)
    {
        pp = add;
        pp->next = nullptr;
        tableHead = add;
        numTables++;
        return;
    }
    
    for(;pp->next != nullptr; pp= pp->next);
    pp->next = add;
    pp->next->next = nullptr;
    numTables++;
    return;
}

//f  C Z
Table* Database:: findTable(const String &name) const
{

    Table *p = tableHead;
    for( ; p != nullptr; p= p->next)
    {
        if (name == p->getName())
        {
           return p;
        }
    }
    return nullptr;

}

//  f  c  Z
void Database:: listTables() const
{
    
    cout<<"The tables currently existing in the database are:\n";
    Table *p = tableHead;
    for( int i=1; p != nullptr; p= p->next, i++)
    {
        cout << p->getName() <<"\n";
    }
    return;

}

// f c  z
void Database::  deleteTable(const String &name)
{
    
    Table *p = tableHead;
    if(p == nullptr) 
    {
        cout<<"No such table exists in the database.\n";
        return;
    }

    if (p->getName() == name)
    {
        Table *p4 = p;
        tableHead = p->next;
        numTables--;
        delete p4;
        return;
    }
    
    if(p->next == nullptr)
    {
        cout<<"No such table exists in the database.\n";
        return;
    }

    for( ; p != nullptr; p= p->next)
    {
        if(p->next == nullptr) break;

        if(p->next->getName() == name)
        {
            Table *d = p->next; 
            p->next = d->next;
            delete d;
            numTables--;
            return;
        }
    }
    
    cout<<"No such table exists in the database.\n";
    return;
}

// f C Z 
void Database:: setCurrentTable(const String &name)
{
    
    Table *p = tableHead;
    for( ; p != nullptr; p= p->next)
    {
        if(p->getName() == name)
        {
            currentTable = p;
            return;
        }
    }

    currentTable = nullptr;
    cout<<"No such table exists in the database.\n";
    return;
}

//  
void Database:: saveDatabase(const String &filename) const
{

    const char *cstr = filename.getStr();
    ofstream ofs(cstr);
    ofs << name << '\n';
    ofs<< numTables<<'\n';
    Table* p =tableHead;
    Field* fp;
    for( ; p!=nullptr ; p = p->next)
    {
        ofs<< p->getName() <<'\n';
        ofs<< p->getNumCols()<<'\n';
        ofs<< p->getNumRows()<<'\n';

        fp = p->getFieldHead();
        for(; fp != nullptr; fp =fp->next)
        {
            if(fp == p->getPrimaryKey()) ofs<<'*';

            ofs<< fp->name<<' '<< fp->type;

            if(fp->next!= nullptr) ofs<< ", ";
        }
        if( p->getNumCols()!=0)
        ofs<<'\n';


        for(int i=0 ; i< p->getNumRows(); i++ )
        {
            fp = p->getFieldHead();
            for(; fp!=nullptr ; fp=fp->next)
            {
                ofs<< fp->column[i];
                if(fp->next!= nullptr) ofs<< ", ";
            }
            ofs<<'\n';
        }
    }

    return;
}

// bonus
void Database:: innerJoin(Table* table1, Table* table2)
{

    if( (table1== nullptr)|| (table2 == nullptr))
    {
        cout<<"No such table exists in the database.\n";
        return;
    }

    Field *PF1 = table1->getPrimaryKey();
    Field *PF2 =  table2->getPrimaryKey();
    if( PF1->type != PF2->type )
    {
        cout<< "Type mismatch between target fields.\n";
        return;
    }

    String n_name = table1->getName() + '+' + table2->getName();
    Table* n = new Table(n_name);

    String pf_name = PF1->name + '+' + PF2->name ;

    n->addField(0 , pf_name, PF1->type);

    Field *p1 = table1->getFieldHead();
    String T1_F[table1->getNumCols()-1]; 

    int i = 1 ; 
    for(; p1!= nullptr ; p1 = p1->next)
    {   
        if( p1->name != PF1->name )
        {
            n->addField(i, p1->name , p1->type);
            T1_F[i] = p1->name;
            i++;
            cout<< p1->name<<endl;
        }
    }

    Field *p2 = table2->getFieldHead();
    String F2_name;
    for(; p2!= nullptr ; p2 = p2->next)
    {   
        if( p2->name != PF2->name )
        {
            F2_name = p2->name;
            for( int k=0 ; k<table1->getNumCols()-1;k++)
            {
                if(p2->name == T1_F[k])
                {
                    F2_name = F2_name+"(T2)"; 
                }
            }
            n->addField(i, F2_name , p2->type);
            i++;
            cout<< F2_name <<endl;
        }
    }

    


    return;
}





