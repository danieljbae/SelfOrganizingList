#include <iostream>
using namespace std;
#include <string> 
#include <sstream>
#include <vector>
#include "SelfOrganizingList.h"

const int HISTORY = 0;
const int FREQUENT = 1;


// Constructor for each Self-Organization Approach
SelfList::SelfList(){
  __historyHead__ = shared_ptr<node>(NULL); // Method: Move to Front
  __freqHead__ = shared_ptr<node>(NULL); // Method: Count 
}

// Deconstructor (shared pointers de-allocate off heap automatically)
SelfList::~SelfList(){
}

// Intiliaze Table Wrapper, containing all lists 
shared_ptr<metaTable> SelfList::InitTable(string userName="No Name"){
    shared_ptr<metaTable> tableWrapper(new metaTable);
    tableWrapper->table_name = userName + "'s Playlists ";
    return tableWrapper;
}

// Intialize Nodes or list heads, and attach to table  
shared_ptr<metaTable> SelfList::InitNode(shared_ptr<metaTable> userTable){

    if (!userTable){
        shared_ptr<metaTable> tableWrapper = InitTable();
        userTable = InitNode(tableWrapper);
    }
    int numLists = 2;
    shared_ptr<playlistContainer> userPlaylists (new playlistContainer(numLists));
    userTable->playlists = userPlaylists; 

    // History Playlist
    shared_ptr<node> Init_node_MTF_History_Top(new node);
    __historyHead__ = Init_node_MTF_History_Top;
    userTable->playlists->at(HISTORY) = __historyHead__ ;
    userTable->playlists->at(HISTORY)->listName = "History Playlist";
    userTable->playlists->at(HISTORY)->next = shared_ptr<node>(NULL);
    userTable->playlists->at(HISTORY)->last = shared_ptr<node>(NULL);
    userTable->playlists->at(HISTORY)->artist = "Artist Name";
    userTable->playlists->at(HISTORY)->genre = "Genre Name";
    userTable->playlists->at(HISTORY)->song = "Song Name";
    userTable->playlists->at(HISTORY)->searchCount = 0;
    
    // Most Frequent Playlist
    shared_ptr<node> Init_count_favorites_Top(new node);
    __freqHead__ = Init_count_favorites_Top;
    userTable->playlists->at(FREQUENT) = __freqHead__;
    userTable->playlists->at(FREQUENT)->listName = "Favorites Playlist";
    userTable->playlists->at(FREQUENT)->next = shared_ptr<node>(NULL);
    userTable->playlists->at(FREQUENT)->last = shared_ptr<node>(NULL);
    userTable->playlists->at(FREQUENT)->artist = "Artist Name";
    userTable->playlists->at(FREQUENT)->genre = "Genre Name";
    userTable->playlists->at(FREQUENT)->song = "Song Name";
    userTable->playlists->at(FREQUENT)->searchCount = 0;

    return userTable;
}

// Display: Specified playlist or All playlist
void SelfList::View_All(shared_ptr<metaTable> new_table, int playlistID){

    // Specified Playlist view
    if (playlistID == HISTORY || playlistID == FREQUENT){   
        shared_ptr<node> cursor = new_table->playlists->at(playlistID)->next;
        cout << "\n View : " << new_table->playlists->at(playlistID)->listName << "\n" << endl;

        // Traverse through all songs in playlist
        while(cursor->next){
            if(playlistID == FREQUENT){
                cout << "  Artist: " << cursor->artist << "  |  Song: " << cursor->song
                << "  |  Search Count: " << cursor->searchCount << endl;
                cursor = cursor->next;
            }
            else{
                cout << "  Artist: " << cursor->artist << "  |  Song: " << cursor->song << endl;
                cursor = cursor->next;
            }
        }
        cout << "  Artist: " << cursor->artist << "  |  Song: " << cursor->song << "\n ****************** \n" << endl;

    }
    // All Playlists view
    else{
        // Traverse over each playlist
        for (int i = 0; i < new_table->playlists->size(); i++){
            shared_ptr<node> cursor = new_table->playlists->at(i); 
            cout << "View : " << new_table->playlists->at(i)->listName << endl;
            
            // Traverse through all songs in playlist
            while(cursor){
                 if(i == FREQUENT){
                    cout << "  Artist: " << cursor->artist << "  |  Song: " << cursor->song
                    << "  |  Search Count: " << cursor->searchCount << endl;
                    // cursor = cursor->next;
                }
                cout << "  Artist: " << cursor->artist << "  |  Song: " << cursor->song << endl;
                cursor = cursor->next;
            }
        }
    }
    
}


// Add node: Always add node to back of every playlist and New addtions must not exist 
shared_ptr<metaTable> SelfList::add_node_helper(shared_ptr<metaTable> table, string spotify_artist,string spotify_genre,string init_song_name){

    // If NULL Table is passed in
    // Allocate on heap and connect wrapper table
    if (!table){
        shared_ptr<metaTable> tableWrapper = InitTable();
        table = InitNode(tableWrapper);
    }

    shared_ptr<node> cursor;
    // For each of the plalists: 
    // find insert point, Allocate memory on heap for new artist, maintain links 
    for (int i = 0; i < table->playlists->size(); i++){
        cursor = table->playlists->at(i); // set cursor to top of each playlist

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
        new_node->searchCount = 0; // Set intial search count to 0, can overide in main
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
        new_node->searchCount = 0; // Set intial search count to 0, can overide in main
        new_node->next = shared_ptr<node>(NULL); // set new node to point next to null indicating end playlist 
        new_node->last = cursor;// set new node to point last to previously last artist in playlist
        }

    }
    return table;
}

// Add node: Always add node to back of every playlist and New addtions must not exist 
 shared_ptr<metaTable> SelfList::add_node(shared_ptr<metaTable> table, string spotify_artist,string spotify_genre,string init_song_name){

    shared_ptr<metaTable> out_table = add_node_helper(table,spotify_artist,spotify_genre, init_song_name);
    return out_table;
 }

// Remove node: removes links to value if it exists
shared_ptr<metaTable> SelfList::remove_node_helper(shared_ptr<metaTable> table, string spotify_artist,string spotify_genre, string spotify_song){
    
    // Removing from empty Table
    if (!table){
        shared_ptr<metaTable> tableWrapper = InitTable();
        table = InitNode(tableWrapper);
        return table;
    }
    
    shared_ptr<node> cursor;
    // For each playlist
    for (int i = 0; i < table->playlists->size(); i++){
        cursor = table->playlists->at(i); //cursor is top song of each playlist
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

 
shared_ptr<metaTable> SelfList::remove_node(shared_ptr<metaTable> table, string spotify_artist,string spotify_genre, string spotify_song){
    shared_ptr<metaTable> out_table = remove_node_helper(table,spotify_artist, spotify_genre, spotify_song);
    return out_table;
}

// This should update all playlists: updates  both history and popular list 
void SelfList::search_artist(shared_ptr<metaTable> table, string spotify_artist,string spotify_genre, string spotify_song){
   
   if (!table){
        cout << "Empty table inputed, using newly created table" << endl;
        shared_ptr<metaTable> tableWrapper = InitTable();
        table = InitNode(tableWrapper);
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
shared_ptr<node> SelfList::search_artist_history(shared_ptr<metaTable> table, string spotify_artist,string spotify_genre, string spotify_song){
    
    cout << "Searching for... " << "Artist: " <<  spotify_artist << " &  Song: " << spotify_song << endl; 
    int no_artist_found = 0;
    int no_song_found = 0;

    // Cursor is set to beginning of playlist
    shared_ptr<node> cursor(new node); // To return we allocate
    cursor = table->playlists->at(0);
    
    
    // Top Cursor is set to beginning of playlist
    // THIS WILL BE Anchor to beggining of list
    shared_ptr<node> top_cursor;
    top_cursor = table->playlists->at(0); 

    // Traverse through all playlists
    while(cursor->next){ // while there is a next song
        if (cursor->next->artist == spotify_artist && cursor->next->song == spotify_song){ // If next song and artist is equal to search 
            no_artist_found = 1;
            no_song_found = 1;

            shared_ptr<node> found = cursor->next;  // Set for found node
            cursor->next = found->next; // ( A->C/Null ) Link to fill gap for where B used to be
            found->next = table->playlists->at(0)->next; // Found follows after Top Pointer Always
            // found->next = top_cursor; // ( B->A->C ) Set search song to have next >> point to beggining of list 
                                     //-- Now new beginnning  
            table->playlists->at(0)->next = found;
            found->last = table->playlists->at(0); // ( Null/Beg<-B->A->C )Set search songg to have last point to NULL 
                                // -- Indicating beggining of list
            
            return table->playlists->at(0); // Top of History Playlist
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
// Approach 1, Most frequently searched list is at top
shared_ptr<node> SelfList::search_popular(shared_ptr<metaTable> table, string spotify_artist,string spotify_genre, string spotify_song){
    shared_ptr<node> cursor;
    shared_ptr<node> found;
    cursor = table->playlists->at(1);
    while(cursor->next){
        if (cursor->next->artist == spotify_artist){
            // Found value
            found = cursor->next; 
            found->searchCount ++; // Increase view count

            // Reorganize list based on view count
            cursor = table->playlists->at(1);


            while(!cursor){
                // Searching for insert point

                if (cursor->next->searchCount > found->searchCount && cursor->next->next->searchCount >= found->searchCount){
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




