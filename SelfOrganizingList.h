#include <string>
#include <memory>
#include <vector>
using namespace std;

extern const int HISTORY;
extern const int FREQUENT;
extern const int PLAYLISTCOUNT;


struct node {
    string listName; 
    string artist; 
    string song; 
    string genre; 
    int searchCount;
    shared_ptr<node> next; 
    shared_ptr<node> last; 
};

typedef vector<shared_ptr<node>> playlistContainer;

struct metaTable{
    shared_ptr<playlistContainer> playlists;
    string table_name;
};

class SelfList {

    public:
        // Constructor for each Self-Organization Approach
        SelfList();
        // Deconstructor (shared pointers de-allocate off heap automatically)
        ~SelfList();
        
        // Intiliaze Table Wrapper, containing all lists 
        shared_ptr<metaTable> InitTable(string userName);
        // Intialize Nodes or list heads, and attach to table  
        shared_ptr<metaTable> InitNode(shared_ptr<metaTable> userTable);
        
        // Display: Specified playlist or All playlist
        void View_All(shared_ptr<metaTable> new_table, int playlistID = 2);

        // Add node: Always add node to back of every playlist
        // Remove node from all playlists 
        shared_ptr<metaTable> add_node(shared_ptr<metaTable> table, string newArtist,string newGenre,string newSong);
        shared_ptr<metaTable> remove_node(shared_ptr<metaTable> table, string removeArtist,string removeGenre, string removeSong);
        
        // Organize list per method: History (Move to Front) and Frequent (Count)
        void search_artist_wrapper(shared_ptr<metaTable> table, string searchArtist,string searchGenre, string searchSong);
        shared_ptr<node> search_history(shared_ptr<metaTable> table, string searchArtist,string searchGenre, string searchSong);
        shared_ptr<node> search_frequent(shared_ptr<metaTable> table, string searchArtist,string searchGenre, string searchSong);

    private:
        shared_ptr<metaTable> remove_node_private(shared_ptr<metaTable> table, string removeArtist,string removeGenre, string removeSong);
        shared_ptr<metaTable> add_node_private(shared_ptr<metaTable> userTable, string newArtist,string newGenre,string newSong);
        
        // Pointer to top of playlists
        shared_ptr<metaTable> __tableHead__;
        shared_ptr<node> __historyHead__;
        shared_ptr<node> __freqHead__;

};