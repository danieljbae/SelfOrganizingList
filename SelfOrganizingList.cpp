#include "SelfOrganizingList.h"
#include <iostream>
using namespace std;
#include <string> 
#include <sstream>
#include <vector>


// constructor will intialize a pointer to each list organizing apprach
// intialize pointer value to null
SelfList::SelfList(){


  __History__Top__Ptr = shared_ptr<node>(NULL);
  __Favorites__Top__Ptr = shared_ptr<node>(NULL);
}

//deconstructor, not necesary as we are using shared pointers
// which de-allocate off heap automatically
SelfList::~SelfList(){
}


shared_ptr<meta_data_approach_table> SelfList::InitTable(){
    shared_ptr<meta_data_approach_table> Init_Table(new meta_data_approach_table);
    Init_Table->table_name = "Daniel's Spotify searches: ";
    return Init_Table;
}

// Intialize table to contain all nodes/versions of list
// Attach table to wrapper
shared_ptr<meta_data_approach_table> SelfList::InitNode(shared_ptr<meta_data_approach_table> table){
    // If Null table passed
    if (!table){
        shared_ptr<meta_data_approach_table> wrapper_table = InitTable();
        table = InitNode(wrapper_table);

    }


    // Intialize table to contain all nodes/versions of list
    shared_ptr<approach_table> ret_approach_tbl (new approach_table(2));
    table->array_of_approaches = ret_approach_tbl; //attach table to wrapper

//   History : Allocate and Intialize top of list for History
    shared_ptr<node> Init_node_MTF_History_Top(new node);
    __History__Top__Ptr = Init_node_MTF_History_Top; // set this to top pointer (TEST THIS IN FUNCTIONS, ALWAYS TOP)
    table->array_of_approaches->at(0) = __History__Top__Ptr;

    table->array_of_approaches->at(0)->artist = "**Top History Node: Artist Name**";
    table->array_of_approaches->at(0)->genre = "**Top History Node: Genre Name**";
    table->array_of_approaches->at(0)->search_count = 0;
    table->array_of_approaches->at(0)->next = shared_ptr<node>(NULL);
    table->array_of_approaches->at(0)->last = shared_ptr<node>(NULL);
    table->array_of_approaches->at(0)->list_name = "History Playlist";
    table->array_of_approaches->at(0)->song = "**Top History Node: Song Name**";

//   Most popular: Allocate and Intialize top of list for popular
    shared_ptr<node> Init_count_favorites_Top(new node);
    __Favorites__Top__Ptr = Init_count_favorites_Top;
    table->array_of_approaches->at(1) = __Favorites__Top__Ptr;

    table->array_of_approaches->at(1)->artist = "**Top Favorites Node: Artist Name**";
    table->array_of_approaches->at(1)->genre = "**Top Favorites Node: Genre Name**";
    table->array_of_approaches->at(1)->search_count = 0;
    table->array_of_approaches->at(1)->next = shared_ptr<node>(NULL);
    table->array_of_approaches->at(1)->last = shared_ptr<node>(NULL);
    table->array_of_approaches->at(1)->list_name = "Favorites Playlist";
    table->array_of_approaches->at(1)->song = "**Top Favorites Node: Song Name**";

  return table;
}

// Display All Playlists per given table or specified playlist
void SelfList::View_All(shared_ptr<meta_data_approach_table> new_table,int specify_list){
    shared_ptr<node> cursor;
    
    // Specifc Playlist
    if (specify_list != 2 ){ 
        cursor = new_table->array_of_approaches->at(specify_list);
        cout << "" << endl;
        cout << "View : " << new_table->array_of_approaches->at(specify_list)->list_name << endl;
        cout << "" << endl;
        // Cursor is set to top pointer for each playlist
        // Cursor traverses through all songs
        while(cursor->next){
            if(specify_list == 1){
                cout << "  Artist: " << cursor->artist << "  |  Song: " << cursor->song
                << "  |  Search: " << cursor->search_count << endl;
                cursor = cursor->next;
            }
            else{
                cout << "  Artist: " << cursor->artist << "  |  Song: " << cursor->song << endl;
                cursor = cursor->next;
            }
        }
        cout << "  Artist: " << cursor->artist << "  |  Song: " << cursor->song << endl;
        cout << "******************" << endl;
        cout << "" << endl;
    }
    // All Playlists
    else{
        for (int i = 0; i < new_table->array_of_approaches->size(); i++){
        cursor = new_table->array_of_approaches->at(i); // Cursor is Playlist
        cout << "View : " << new_table->array_of_approaches->at(i)->list_name << endl;
        // Cursor is set to top pointer for each playlist
        // Cursor traverses through all songs
        while(cursor->next){
             cout << "  Artist: " << cursor->artist << "  |  Song: " << cursor->song << endl;
             cursor = cursor->next;
        }
        cout << "  Artist: " << cursor->artist << "  |  Song: " << cursor->song << endl;
        cout << "******************" << endl;
        cout << "" << endl;
        }
    }
    
}


// Add node: Always add node to back of every playlist and New addtions must not exist 
shared_ptr<meta_data_approach_table> SelfList::add_node_helper(shared_ptr<meta_data_approach_table> table, string spotify_artist,string spotify_genre,string init_song_name){

    // If NULL Table is passed in
    // Allocate on heap and connect wrapper table
    if (!table){
        shared_ptr<meta_data_approach_table> wrapper_table = InitTable();
        table = InitNode(wrapper_table);
    }

    shared_ptr<node> cursor;
    // For each of the plalists: 
    // find insert point, Allocate memory on heap for new artist, maintain links 
    for (int i = 0; i < table->array_of_approaches->size(); i++){
        cursor = table->array_of_approaches->at(i); // set cursor to top of each playlist

        // Traverse all of playlist till null 
        while(cursor->next){ 
             cursor = cursor->next; // if next artist is not null, set cursor to be next artist
            
            // If Song already Exists
            if (cursor->artist == spotify_artist && cursor->genre == spotify_genre && cursor->song ==  init_song_name){
                break;
            }
        }

    // If EMPTY table and/or found empty spot (+) If song does not already exist
    if (cursor->next == NULL // Cursor is top pointer
        && cursor->artist != spotify_artist && cursor->song !=  init_song_name){
        shared_ptr<node> new_node(new node);
        cursor->next = new_node;
        
        new_node->artist = spotify_artist; // Set new artist name 
        new_node->genre = spotify_genre; // Set new artist genre
        new_node->song = init_song_name; // Set new song name
        new_node->search_count = 0; // Set intial search count to 0, can overide in main
        new_node->next = shared_ptr<node>(NULL); // set new node to point next to null indicating end playlist 
        new_node->last = cursor;// set new node to point last to previously last artist in playlist
        // return table;
        }
    
    if (cursor->artist != spotify_artist && cursor->song !=  init_song_name){
        // Allocate memory on heap for new artist
        shared_ptr<node> new_node(new node);
        // Cursor is last artist in playlist 
        cursor->next = new_node; // last artist now connected to new artits  

        new_node->artist = spotify_artist; // Set new artist name 
        new_node->genre = spotify_genre; // Set new artist genre
        new_node->song = init_song_name; // Set new song name
        new_node->search_count = 0; // Set intial search count to 0, can overide in main
        new_node->next = shared_ptr<node>(NULL); // set new node to point next to null indicating end playlist 
        new_node->last = cursor;// set new node to point last to previously last artist in playlist
        }

    }
    return table;
}

// Add node: Always add node to back of every playlist and New addtions must not exist 
 shared_ptr<meta_data_approach_table> SelfList::add_node(shared_ptr<meta_data_approach_table> table, string spotify_artist,string spotify_genre,string init_song_name){

    shared_ptr<meta_data_approach_table> out_table = add_node_helper(table,spotify_artist,spotify_genre, init_song_name);
    return out_table;
 }

// Remove node: removes links to value if it exists
shared_ptr<meta_data_approach_table> SelfList::remove_node_helper(shared_ptr<meta_data_approach_table> table, string spotify_artist,string spotify_genre, string spotify_song){
    
    // Removing from empty Table
    if (!table){
        shared_ptr<meta_data_approach_table> wrapper_table = InitTable();
        table = InitNode(wrapper_table);
        return table;
    }
    
    shared_ptr<node> cursor;
    // For each playlist
    for (int i = 0; i < table->array_of_approaches->size(); i++){
        cursor = table->array_of_approaches->at(i); //cursor is top song of each playlist
        // Traverse Until end of list for each playlist
        while(cursor->next){ 
            // If values are found in playlist
            if (cursor->artist == spotify_artist && cursor->song == spotify_song && cursor->genre == spotify_genre){
                cursor->last->next = cursor->next; //(A -> C) set cursor's last song  >> have next point to song after deleted song
                cursor->next->last = cursor->last; // (C -> A) set curor's next song >> have last song point to song before deleted song
                // return table; 
            }
            cursor = cursor->next; // Traverse through 
        }
        // Removing last value 
        if (cursor->artist == spotify_artist && cursor->song == spotify_song && cursor->genre == spotify_genre){
            cursor->last->next = NULL;
            }
    }
    return table;
}

 
shared_ptr<meta_data_approach_table> SelfList::remove_node(shared_ptr<meta_data_approach_table> table, string spotify_artist,string spotify_genre, string spotify_song){
    shared_ptr<meta_data_approach_table> out_table = remove_node_helper(table,spotify_artist, spotify_genre, spotify_song);
    return out_table;
}

// This should update all playlists: updates  both history and popular list 
void SelfList::search_artist(shared_ptr<meta_data_approach_table> table, string spotify_artist,string spotify_genre, string spotify_song){
   
   if (!table){
        cout << "Empty table inputed, using newly created table" << endl;
        shared_ptr<meta_data_approach_table> wrapper_table = InitTable();
        table = InitNode(wrapper_table);
    }
    // Updating History
    shared_ptr<node> top_history = search_artist_history(table, spotify_artist,spotify_genre,spotify_song);
    if (top_history->next->artist == spotify_artist && top_history->next->song == spotify_song){
        cout << "Result found!";
        // cout << "  Search Results -- Artist: " << node->next->artist << " &  Song: "<< node->next->song << endl;
        cout << "" << endl;
    }

    // updating most popular
    shared_ptr<node> top_popular = search_popular(table, spotify_artist,spotify_genre,spotify_song);
    if (top_popular->next->artist == spotify_artist && top_popular->next->song == spotify_song){
        cout << "Result found!";
        // cout << "  Search Results -- Artist: " << node->next->artist << " &  Song: "<< node->next->song << endl;
        cout << "" << endl;
    }


}
// History: most recently searched node is at front of list
shared_ptr<node> SelfList::search_artist_history(shared_ptr<meta_data_approach_table> table, string spotify_artist,string spotify_genre, string spotify_song){
    
    cout << "Searching for... " << "Artist: " <<  spotify_artist << " &  Song: " << spotify_song << endl; 
    int no_artist_found = 0;
    int no_song_found = 0;

    // Cursor is set to beginning of playlist
    shared_ptr<node> cursor(new node); // To return we allocate
    cursor = table->array_of_approaches->at(0);
    
    
    // Top Cursor is set to beginning of playlist
    // THIS WILL BE Anchor to beggining of list
    shared_ptr<node> top_cursor;
    top_cursor = table->array_of_approaches->at(0); 

    // Traverse through all playlists
    while(cursor->next){ // while there is a next song
        if (cursor->next->artist == spotify_artist && cursor->next->song == spotify_song){ // If next song and artist is equal to search 
            no_artist_found = 1;
            no_song_found = 1;

            shared_ptr<node> found = cursor->next;  // Set for found node
            cursor->next = found->next; // ( A->C/Null ) Link to fill gap for where B used to be
            found->next = table->array_of_approaches->at(0)->next; // Found follows after Top Pointer Always
            // found->next = top_cursor; // ( B->A->C ) Set search song to have next >> point to beggining of list 
                                     //-- Now new beginnning  
            table->array_of_approaches->at(0)->next = found;
            found->last = table->array_of_approaches->at(0); // ( Null/Beg<-B->A->C )Set search songg to have last point to NULL 
                                // -- Indicating beggining of list
            
            return table->array_of_approaches->at(0); // Top of History Playlist
        }
        // Could be many songs by different artists so keep on traversing after
        else if (cursor->next->artist != spotify_artist && cursor->next->song == spotify_song && no_artist_found != 1){
            no_artist_found = 0;
            no_song_found = 1;

        }
        // Could be many artits that has lots of songs
        else if (cursor->next->artist == spotify_artist && cursor->next->song != spotify_song && no_song_found != 1){
            no_artist_found = 1;
            no_song_found = 0;
        }

        cursor = cursor->next; // Traverse
    }
    if (no_song_found == 0 && no_artist_found == 0){
        cout << "Search Error helper: No Artists or Song found" << endl;
        cout << "" << endl;
        
        return cursor->last;
    }
    else if (no_song_found == 0 && no_artist_found == 1){
        cout << "Search Error helper: No Song found" << endl;
        cout << "" << endl;
        return cursor->last;
    }
    else if (no_song_found == 1 && no_artist_found == 0){
        cout << "Search Error helper: No Artist found" << endl;
        cout << "" << endl;
        return cursor->last;
    }

    
    // return cursor;
    return cursor->next;
}
// Most ffrequently seareched list is at top
shared_ptr<node> SelfList::search_popular(shared_ptr<meta_data_approach_table> table, string spotify_artist,string spotify_genre, string spotify_song){
    shared_ptr<node> cursor;
    shared_ptr<node> found;
    cursor = table->array_of_approaches->at(1);
    while(cursor->next){
        if (cursor->next->artist == spotify_artist){
            // Found value
            found = cursor->next; 
            found->search_count ++; // Increase view count

            // Reorganize list based on view count
            cursor = table->array_of_approaches->at(1);


            while(!cursor){
                // Searching for insert point

                if (cursor->next->search_count > found->search_count && cursor->next->next->search_count >= found->search_count){
                     cursor = cursor->next;   
                }
                else{ // Found insert point
                    found->next->last = found->last;
                    found->last->next = found->next;
                    
                    found->next = cursor->next;
                    found->last = cursor;
                    cursor->next = found;
                }
            }
            return cursor->next;
        }
        cursor = cursor->next;
    }
}




