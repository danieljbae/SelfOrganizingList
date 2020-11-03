#include <iostream>
using namespace std;
#include <string> 
#include <sstream>
#include <vector>
#include "SelfOrganizingList.h"

const int HISTORY = 0;
const int FREQUENT = 1;
const int PLAYLISTCOUNT = 2;


// Constructor for each Self-Organization Approach
SelfList::SelfList(){
  __historyHead__ = shared_ptr<node>(NULL); // Method: Move to Front
  __freqHead__ = shared_ptr<node>(NULL); // Method: Count 
}

// Deconstructor (shared pointers de-allocate off heap automatically)
SelfList::~SelfList(){
}

// Intialize Table Wrapper, containing all lists 
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

    // Attaching lists to Table
    int numLists = PLAYLISTCOUNT;
    shared_ptr<playlistContainer> userPlaylists (new playlistContainer(numLists));
    userTable->playlists = userPlaylists; 
    string playlistName;

    // Intializing Lists 
    for (int i = 0; i < PLAYLISTCOUNT; i++){
        if (i == FREQUENT) {
            playlistName = "Frequent";
            shared_ptr<node> freqTop(new node);
            __freqHead__ = freqTop;
            userTable->playlists->at(i) = __freqHead__;
        }
        else{
            playlistName = "History";
            shared_ptr<node> historyTop(new node);
            __historyHead__ = historyTop;
            userTable->playlists->at(i) = __historyHead__;
        }
        userTable->playlists->at(i)->listName = playlistName;   
        userTable->playlists->at(i)->next = shared_ptr<node>(NULL);
        userTable->playlists->at(i)->last = shared_ptr<node>(NULL);
        userTable->playlists->at(i)->artist = "Artist Name";
        userTable->playlists->at(i)->genre = "Genre Name";
        userTable->playlists->at(i)->song = "Song Name";
        userTable->playlists->at(i)->searchCount = 0;
        
    }
    return userTable;
}

// Display: Specified playlist or All playlist
void SelfList::View_All(shared_ptr<metaTable> new_table, int playlistID){
    shared_ptr<node> cursor;

    // Finish: you can figure out how to collapse this to 1
    // Display Specified Playlist 
    if (playlistID == HISTORY || playlistID == FREQUENT){   
        cursor = new_table->playlists->at(playlistID)->next;
        cout << "\n View : " << new_table->playlists->at(playlistID)->listName << "\n" << endl;

        while(cursor){
            cout << "   Artist: " << cursor->artist << "  |  Song: " << cursor->song;
            if(playlistID == FREQUENT){
                cout << "  |  Search Count: " << cursor->searchCount;
            }
            cout << endl;
            cursor = cursor->next;
        }
    }
    // Display All Playlists
    else{
        for (int i = 0; i < new_table->playlists->size(); i++){ // Traverse over each playlist
            cursor = new_table->playlists->at(i); 
            cout << "View : " << new_table->playlists->at(i)->listName << "\n" << endl;
               
            while(cursor){
                cout << "   Artist: " << cursor->artist << "  |  Song: " << cursor->song;
                if(i == FREQUENT){
                    cout << "  |  Search Count: " << cursor->searchCount;
                }
                cout << endl;
                cursor = cursor->next;
            }
        }
    }
    
}


// Add node: Always add node to back of every playlist, no dupes
shared_ptr<metaTable> SelfList::add_node_private(shared_ptr<metaTable> userTable, string newArtist,string newGenre,string newSong){
    
    shared_ptr<node> cursor;
    // If Null Table passed
    if (!userTable){
        shared_ptr<metaTable> tableWrapper = InitTable();
        userTable = InitNode(tableWrapper);
    }
    // Find end of each playlist and insert if unique song
    for (int i = 0; i < userTable->playlists->size(); i++){
        cursor = userTable->playlists->at(i); 
        while(cursor->next){ 
            
            if (cursor->artist == newArtist && cursor->genre == newGenre && cursor->song ==  newSong){
                return userTable; // If Song already Exists
            }
            cursor = cursor->next; 
        }
        
        // Finish: Unncesary, we're checking if new song is unique, but while loop checks for that too
        // Insert new song
        if (cursor->next == NULL && cursor->artist != newArtist && cursor->song !=  newSong){
            shared_ptr<node> new_node(new node);
            cursor->next = new_node;
            new_node->artist = newArtist; 
            new_node->genre = newGenre; 
            new_node->song = newSong; 
            new_node->next = shared_ptr<node>(NULL); 
            new_node->last = cursor;
            new_node->searchCount = 0; 
            }

    }
    return userTable;
}
// Public function
 shared_ptr<metaTable> SelfList::add_node(shared_ptr<metaTable> table, string newArtist,string newGenre,string newSong){
    shared_ptr<metaTable> out_table = add_node_private(table,newArtist,newGenre, newSong);
    return out_table;
 }




// Remove node from all playlists 
shared_ptr<metaTable> SelfList::remove_node_private(shared_ptr<metaTable> table, string removeArtist,string removeGenre, string removeSong){
    
    // Null table passed
    if (!table){
        shared_ptr<metaTable> tableWrapper = InitTable();
        table = InitNode(tableWrapper);
        return table;
    }
    
    shared_ptr<node> cursor;
    for (int i = 0; i < table->playlists->size(); i++){
        cursor = table->playlists->at(i); 
        while(cursor->next){ 
            // If values are found in playlist, delete
            if (cursor->artist == removeArtist && cursor->song == removeSong && cursor->genre == removeGenre){
                cursor->last->next = cursor->next; 
                cursor->next->last = cursor->last;
            }
            cursor = cursor->next; 
        }
        
        // Finish: This is redudant with if statement above
        // Removing last value 
        if (cursor->artist == removeArtist && cursor->song == removeSong && cursor->genre == removeGenre){
            cursor->last->next = NULL;
            }
    }
    return table;
}
// Public function
shared_ptr<metaTable> SelfList::remove_node(shared_ptr<metaTable> table, string removeArtist,string removeGenre, string removeSong){
    shared_ptr<metaTable> out_table = remove_node_private(table,removeArtist, removeGenre, removeSong);
    return out_table;
}


// Update all playlists according to approach
void SelfList::search_artist_wrapper(shared_ptr<metaTable> table, string searchArtist,string searchGenre, string searchSong){
   
   if (!table){
        shared_ptr<metaTable> tableWrapper = InitTable();
        table = InitNode(tableWrapper);
    }
    // Updating History and Popular
    shared_ptr<node> topHistory = search_history(table, searchArtist,searchGenre,searchSong);
    shared_ptr<node> topFreq = search_frequent(table, searchArtist,searchGenre,searchSong);
}

// History: most recently searched node is at front of list
shared_ptr<node> SelfList::search_history(shared_ptr<metaTable> table, string searchArtist,string searchGenre, string searchSong){
    
    int artistFound = 0;
    int songFound = 0;
    shared_ptr<node> found;
    shared_ptr<node> cursor(new node);
    shared_ptr<node> top_cursor;

    cursor = table->playlists->at(HISTORY);
    top_cursor = table->playlists->at(HISTORY); 


    while(cursor->next){ 
        // Move to front, if song found
        if (cursor->next->artist == searchArtist && cursor->next->song == searchSong){ 
            found = cursor->next;  
            cursor->next = found->next; 
            found->next = table->playlists->at(HISTORY)->next; 
            table->playlists->at(HISTORY)->next = found; // Move to front (after playlist head)
            found->last = table->playlists->at(HISTORY);          
            return table->playlists->at(HISTORY); 
        }
        cursor = cursor->next;
    }
    return cursor->next;
}

// Most frequent: organize per count
shared_ptr<node> SelfList::search_frequent(shared_ptr<metaTable> table, string searchArtist,string searchGenre, string searchSong){
    shared_ptr<node> cursor;
    shared_ptr<node> found;
    cursor = table->playlists->at(1);
    while(cursor->next){
        // Found value
        if (cursor->next->artist == searchArtist && cursor->next->genre == searchGenre && cursor->next->song == searchSong){
            found = cursor->next; 
            found->searchCount ++; // Increase view count
            cursor = table->playlists->at(1); // Reorganize list based on view count

            // Search for insert point and organize per count
            while(!cursor){        
                if (cursor->next->searchCount > found->searchCount && cursor->next->next->searchCount >= found->searchCount){
                     cursor = cursor->next;   
                }
                else{
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




