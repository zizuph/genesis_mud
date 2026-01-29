
inherit "/std/scroll";

#include <stdproperties.h>
#define DD "/d/Shire/common/writings/"
#define AI add_item
#define BS break_string
#define AP add_prop
void
create_scroll()
{
        set_name(({"map","paper"}));
	set_adj(({"brown","flakey"}));
        set_short("small brown piece of paper");
        set_long(BS(
        "This looks like an old map. "  
        + "From the looks of it, it is "
        + "a few decades old. There " 
        + "are faded writings on the " 
        + "paper but it's too hard to "
        + "make out what they say. "
        + "There appears to be nothing "
        + "on the back of this map "      
        + "except some stains of dirt "   
        + "and some layers of dust which "
        + "have collect of the years.\n",60));
        
        AI("dust",BS(
        "The dust is layered on the map. "
        + "It has become on with the map "  
        + "since it's long days in storage "
        + "some where in someone's attic.\n",60));
        AI("dirt",BS(
        "There is dried dirt smeared all over "
        + "map. It seems the dirt kept the "   
        + "map from rotting away but this has "
        + "made the map rather hard to "
        + "read.\n",60));
        AP(OBJ_I_VALUE, 1);
        AP(OBJ_I_WEIGHT, 5);
        AP(OBJ_I_VOLUME, 10);
    
        set_file(DD+"map_of_island");
}

