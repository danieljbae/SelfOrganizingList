#include <string>
#include <memory>
#include <vector>

using namespace std;

const int HISTORY = 0;
const int POPULAR = 1;


struct node {
    string artist; //name of artist (Test: if 2 songs are by different artists)
    string song; // song name (TEST: IF two artists have 2 same song names)
    string genre; //genre of artist
    int search_count; //number of times a user has searched the artist
    shared_ptr<node> next; // pointer to next node, NULL if last node (TEST)
    shared_ptr<node> last; // pointer to last node, NULL if 1st node (TEST)
    string list_name; // name for user to reference as to how list was intended to be used
};


typedef vector<shared_ptr<node>> approach_table;


struct meta_data_approach_table{
    shared_ptr<approach_table> array_of_approaches;
    string table_name;



};


class SelfList {
public:
    // constructor will intialize a pointer to each list organizing apprach
    SelfList();

    //deconstructor, if you are using shared_pointers you don't need to keep track of
    // freeing memory and you can leave this blank
    ~SelfList();
    
    // Creates table wrapper
    shared_ptr<meta_data_approach_table> InitTable();

    // Intialize table to contain all nodes/versions of list
    // Attach table to wrapper and Returns table after
    shared_ptr<meta_data_approach_table> InitNode(shared_ptr<meta_data_approach_table> table);
    
    void View_All(shared_ptr<meta_data_approach_table> new_table, int specify_list = 2);

    // Add node: Always add node to back of every playlist 
    // (as new artist would not have been searched before)
    shared_ptr<meta_data_approach_table> add_node(shared_ptr<meta_data_approach_table> table, string spotify_artist,string spotify_genre, string init_song_name);
    
    // TO DO
    shared_ptr<meta_data_approach_table> remove_node(shared_ptr<meta_data_approach_table> table, string spotify_artist,string spotify_genre, string spotify_song);
    
    // To DO
    void search_artist(shared_ptr<meta_data_approach_table> table, string spotify_artist,string spotify_genre, string spotify_song);
    
    // To DO
    shared_ptr<node> search_artist_history(shared_ptr<meta_data_approach_table> table, string spotify_artist,string spotify_genre, string spotify_song);
    shared_ptr<node> search_popular(shared_ptr<meta_data_approach_table> table, string spotify_artist,string spotify_genre, string spotify_song);

private:
    shared_ptr<meta_data_approach_table> remove_node_helper(shared_ptr<meta_data_approach_table> table, string spotify_artist, string spotify_genre, string spotify_song);
    shared_ptr<meta_data_approach_table> add_node_helper(shared_ptr<meta_data_approach_table> table, string spotify_artist,string spotify_genre,string init_song_name);
    
    // Pointer to top of playlists
    shared_ptr<meta_data_approach_table> table_top;
    shared_ptr<node> __History__Top__Ptr;
    shared_ptr<node> __Favorites__Top__Ptr;

};