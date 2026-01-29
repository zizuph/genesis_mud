#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define H1 KRHERB + "blk_currant"
#define H2 KRHERB + "labr_tea"
#define H3 KRHERB + "cladina"
#define H4 KRHERB + "cladina"

void
reset_mithas_room()
{
   set_searched(random(4));
}

create_mithas_room()
{
    set_search_places(({"underbrush","herbs",
                       "trail", "path", "ground"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);
   
    reset_mithas_room();
    set_short("On a dusty forest trail");
    set_long("@@long_descr"); 

    add_exit(MROOM + "forest26","north",0);
    add_exit(MROOM + "forest27","south",0);

    add_item(({"forest"}),
     "The forest looks ancient. Old logs and branches "+
     "fill the forest floor and the strong smell of "+
     "decay and moisture fills the air. The forest "+
     "consists of different sorts of trees, a "+
     "mixture of pines and oaktrees.\n");

    add_item(({"trees","oaktrees","pine trees", "pines"}),
     "The trees here consist of a mixture of pines "+
     "and oaktrees. Some of them look quite old "+
     "while others are fairly young.\n");

    add_item(({"underbrush","undergrowth"}),
     "The undergrowth here looks dense with different "+
     "plants and herbs. It seems like it's impossible "+
     "to enter it. \n");

    add_item(({"trail","path"}),
     "The forest trail twists itself further into "+
     "the forest. It's a bit overgrown with different "+
     "plants and herbs.\n");

    add_item(({"canopy", "treetops"}),
     "The canopy above you looks thick, only a few sunrays "+
     "are able to enter the forest. You notice a few birds "+
     "above you, but they quickly vanish in the thick canopy.\n");

    add_item(({"leaves","branches"}),
     "The branches and leaves here, have almost decomposed "+
     "into dirt. A few of them look alive, but "+
     "they are still covered with moss and fungus.\n");

    add_item(({"herbs","plants"}),
     "There are a lot of different herbs here! If you want to "+
     "look at a specific one, perhaps you should search for "+
     "it.\n");

    add_item(({"mountain peaks ","peaks"}),
     "You realize that the four mountain peaks in the "+
     "southern part of the isle, are the four volcanoes "+
     "of Mithas. These were once very active, but they "+
     "haven't erupted for centuries, and are thought of "+
     "as being 'dead'.\n");

}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+
    "You are standing on a small hill within a "+
    "vast forest in the southern part of Mithas. "+
    "The undergrowth here consists of a wide "+
    "variety of plant and herbs. "+
    "Far to the south, you notice four mountain "+
    "peaks reaching towards the sky. The trail "+
    "continues to the north and south.\n";
}


