#include <iostream>
#include "SelfOrganizingList.h"
#include <string>

using namespace std;

int main(){

    // Specific user creates table wrapper and allocates to heap
    SelfList ls;
    SelfList ls_Friend;
    string name = "Daniel";
    string nameFriend = "Jeff";
    shared_ptr<metaTable> root_table = ls.InitTable(name);
    shared_ptr<metaTable> root_table_friend = ls_Friend.InitTable(nameFriend);

    
    // InitNode: Takes Root Table Wrapper and attaches concrete table with top nodes for every playlist type 
    // InitNode Test: Pass with Null Table  
    // shared_ptr<metaTable> tableWrapper = ls.InitNode(shared_ptr<metaTable>(NULL));
    
    // InitNode Test: Pass with Non-Null Table  
    shared_ptr<metaTable> tableWrapper = ls.InitNode(root_table);
    shared_ptr<metaTable> init_table_friend = ls_Friend.InitNode(root_table_friend);



    cout << "" << endl;
    cout << "" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%   " << tableWrapper->table_name << "   %%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "" << endl;

    // create pointer for updated tables 
    shared_ptr<metaTable> new_table; 
    shared_ptr<metaTable> new_table_friend; 


// **********************************************************
// Test: Insert Tests
// **********************************************************
    // Insert Test: with Null table >> insert to empty table
    new_table = ls.add_node(shared_ptr<metaTable>(NULL), "Elton John", "Rock", "Your Song");
     
    // Insert TEst: to not empty Empty Table
    new_table = ls.add_node(new_table, "The Beatles", "Rock", "Hey Jude");
    // Insert Test : Song already exists
    new_table = ls.add_node(new_table, "The Beatles", "Rock", "Hey Jude");
    
        
    
    new_table = ls.add_node(new_table, "Kanye", "Rap", "Street Lights");
    new_table = ls.add_node(new_table, "Jay Z", "Rap","Made in America");
    new_table = ls.add_node(new_table, "Coldplay", "Pop","Yellow");
    new_table = ls.add_node(new_table, "The Weekend", "Pop", "Blinding Lights");
    new_table = ls.add_node(new_table, "Frank Ocean", "Pop", "Swim Good");

// **********************************************************
// Test: Insert Tests End
// **********************************************************




// **********************************************************
// Test: Remove Tests
// **********************************************************
    // Remove Test: with Null table >> insert to empty table
    // This will create initial tablewrapper and attach table for you >> return this table 
    ls.remove_node(shared_ptr<metaTable>(NULL), "Elton John", "Rock", "Your Song");

    // Remove Node Test: First Node 
    ls.remove_node(new_table, "Elton John", "Rock", "Your Song");

    // Remove Node Test: Last Node
    ls.remove_node(new_table, "Frank Ocean", "Pop", "Swim Good");
 
    // Remove Node Test: Non Existant Node
    // This will do nothing and simplt return table
    ls.remove_node(new_table, "Frank Ocean", "Pop", "Swim Goof");
// **********************************************************
// Test: Remove Tests End
// **********************************************************
    



// **********************************************************
// Test: Link Tests -- View All Playlists links after add and remove from top to bottom 
// **********************************************************
 


// This Order should be: //  top_ptr >> Beatles >> Kanye >> Jay Z >> Coldplay >> The Weekend >> Null
    cout << "" << endl;cout << "" << endl;cout << "" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "*****  Add and Remove Tests: Begin  *****" << endl;
    cout << "Order should be: top_ptr >> Beatles >> Kanye >> Jay Z >> Coldplay >> The Weekend >> Null" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    ls.View_All(new_table);

// **********************************************************
// Test: Link Tests End
// **********************************************************

    
    

// **********************************************************
// Test: Search Tests
// **********************************************************
    
    cout << "" << endl;
    cout << "" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "*****  Search Tests: Begin  *****" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;



// **********************************************************
// **********************************************************
// Test: Search tests (History) --  Most recebtly searched be at top every search
// **********************************************************
// **********************************************************


    cout << "" << endl;cout << "" << endl;cout << "" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "Before History Search" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    ls.View_All(new_table, HISTORY);



    shared_ptr<node> cursor;

    // // History Search Test: Empty Table
    // string search_artist = "The Beatle";
    // string search_genre = "Rock";
    // string search_song ="Hey Jud";
    // shared_ptr<node> node = ls.search_artist(shared_ptr<metaTable>(NULL), search_artist, search_genre, search_song);
    // if (node->next->artist == search_artist && node->next->song == search_song){
    //     cout << "Result found!";
    //     // cout << "  Search Results -- Artist: " << node->next->artist << " &  Song: "<< node->next->song << endl;
    //     cout << "" << endl;
    // }

    //// History Search Test: Searching for non existant value >> Error helper messages appear
    //string search_artist = "The Beatle";
    //string search_genre = "Rock";
    //string search_song ="Hey Jud";
    //// shared_ptr<node> node = ls.search_artist(new_table, search_artist, search_genre, search_song);
    //ls.search_artist(new_table, search_artist, search_genre, search_song);
/// HERE **************************************************************

    // History Search Test: Searching for first value
    string search_artist = "The Beatles";
    string search_genre = "Rock";
    string search_song ="Hey Jude";
    ls.search_artist(new_table, search_artist, search_genre, search_song);


    // History Search Test: Top pointer is always maintained at top, even after searching
    //  (ex. Top >> Kanye >> Beatles ...) 
    search_artist = "Kanye";
    search_genre = "Rap";
    search_song ="Street Lights";
    ls.search_artist(new_table, search_artist, search_genre, search_song);


    
    //History Search Test: Last value & History Search Test: History Updates for newly searched to be following top and 
    // Previously searched to follow newly searched (ex. Top >> The Weekend >>Kanye >> Beatles ... )
    search_artist = "The Weekend";
    search_genre = "Pop";
    search_song ="Blinding Lights";
    ls.search_artist(new_table, search_artist, search_genre, search_song);


    cout << "" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "After History Search " << endl;
    cout << "Order searched in -- Beatles >> Kanye >> The Weekend" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    ls.View_All(new_table, HISTORY);




    // search_artist = "The Beatles";
    // search_genre = "Rock";
    // search_song ="Hey Jude";
    // node = ls.search_artist(new_table, search_artist, search_genre, search_song);
    // node = ls.search_artist(new_table, search_artist, search_genre, search_song);
    // node = ls.search_artist(new_table, search_artist, search_genre, search_song);
    // node = ls.search_artist(new_table, search_artist, search_genre, search_song);
    // node = ls.search_artist(new_table, search_artist, search_genre, search_song);
    

// **********************************************************
// Test: Search test (History) END 
// **********************************************************



// **********************************************************
// Test: Search tests (Popular) --  Most frequently searched be at top every search
// **********************************************************


    // Test: First Value
    // 
    search_artist = "The Beatles";
    search_genre = "Rock";
    search_song ="Hey Jude";

    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);

    
    // Test: Last Value
    // Weekend takes lead
    search_artist = "Jay Z";
    search_genre = "Rap";
    search_song ="Made in America";

    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);

    // Kanye should be follow after Weekend
    search_artist = "Kanye";
    search_genre = "Rap";
    search_song ="Street Lights";
    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);
    ls.search_artist(new_table, search_artist, search_genre, search_song);


    cout << "" << endl;cout << "" << endl;cout << "" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "Popular Search Ouput - Beatles (9), Kanye (7), Jay Z (4)" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%" << endl;
    ls.View_All(new_table, FREQUENT);




    return 0;
}