#include <iostream>
#include "SelfOrganizingList.h"
#include <string>

using namespace std;

int main(){

    // Specific user creates table wrapper and allocates to heap
    SelfList ls;
    SelfList ls_Friend;
    string name = "Daniel";

    // InitTable Test: Pass with valid Table Name 
    shared_ptr<metaTable> root_table = ls.InitTable(name);
    
    // InitNode Test: Pass with Non-Null Table  
    shared_ptr<metaTable> tableWrapper = ls.InitNode(root_table); 

    // create pointer for updated tables 
    shared_ptr<metaTable> new_table; 

    // InitNode Test: Pass with Null Table  
    // shared_ptr<metaTable> tableWrapper = ls.InitNode(shared_ptr<metaTable>(NULL));

    cout << " \n \n%%%%%%%%%%%%%%%%%%%%%%%%%%%%   " << tableWrapper->table_name << "   %%%%%%%%%%%%%%%%%%%%%%%%%%%% \n" << endl;


    
    // **********************************************************
    // Test: Insert Tests
    // **********************************************************
    cout << "\n \n \n*****  Add and Remove Tests  *****" << endl;
    cout << "Order should be: top_ptr >> Beatles >> Kanye >> Jay Z >> Coldplay >> The Weekend >> Null \n" << endl;
    
    
    new_table = ls.add_node(shared_ptr<metaTable>(NULL), "Elton John", "Rock", "Your Song"); // Insert Test: with Null table 
    new_table = ls.add_node(new_table, "The Beatles", "Rock", "Hey Jude"); // Insert Test: to not empty Empty Table
    new_table = ls.add_node(new_table, "The Beatles", "Rock", "Hey Jude"); // Insert Test : Song already exists
    new_table = ls.add_node(new_table, "Kanye", "Rap", "Street Lights");
    new_table = ls.add_node(new_table, "Jay Z", "Rap","Made in America");
    new_table = ls.add_node(new_table, "Coldplay", "Pop","Yellow");
    new_table = ls.add_node(new_table, "The Weekend", "Pop", "Blinding Lights");
    new_table = ls.add_node(new_table, "Frank Ocean", "Pop", "Swim Good");



    // **********************************************************
    // Test: Remove Tests
    // **********************************************************
    ls.remove_node(shared_ptr<metaTable>(NULL), "Elton John", "Rock", "Your Song"); // Remove Test: with Null table 
    ls.remove_node(new_table, "Elton John", "Rock", "Your Song"); // Remove Node Test: First Node 
    ls.remove_node(new_table, "Frank Ocean", "Pop", "Swim Good"); // Remove Node Test: Last Node
    ls.remove_node(new_table, "Frank Ocean", "Pop", "Swim Goof"); // Remove Node Test: Non Existant Node

    ls.View_All(new_table);  



    // **********************************************************
    // Test: Search Tests
    // **********************************************************
    cout << "\n \n \n*****  Search Tests  *****" << endl;


    // **********************************************************
    // Test: Search tests (History) -- Move to front    
    // **********************************************************
    cout << " \n \nBefore History Search" << endl;
    ls.View_All(new_table, HISTORY);

    shared_ptr<node> cursor;

    // History Search Test: Searching for first value
    string search_artist = "The Beatles";
    string search_genre = "Rock";
    string search_song ="Hey Jude";
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);

    search_artist = "Kanye";
    search_genre = "Rap";
    search_song ="Street Lights";
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);

    search_artist = "The Weekend";
    search_genre = "Pop";
    search_song ="Blinding Lights";
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);

    cout << "\n \nAfter History Search " << endl;
    cout << "Order searched in -- Beatles >> Kanye >> The Weekend" << endl;
    ls.View_All(new_table, HISTORY);



    // **********************************************************
    // Test: Search tests (Popular) --  Organize by Count
    // **********************************************************
    
    // Test: First Value
    search_artist = "The Beatles";
    search_genre = "Rock";
    search_song ="Hey Jude";
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);

    
    // Test: Last Value
    // Weekend takes lead
    search_artist = "Jay Z";
    search_genre = "Rap";
    search_song ="Made in America";
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);

    // Test: Middle value
    search_artist = "Kanye";
    search_genre = "Rap";
    search_song ="Street Lights";
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);
    ls.search_artist_wrapper(new_table, search_artist, search_genre, search_song);

    cout << "\n \nFrequent Search Ouput - Beatles (9), Kanye (7), Jay Z (4)" << endl;
    ls.View_All(new_table, FREQUENT);

    return 0;
}