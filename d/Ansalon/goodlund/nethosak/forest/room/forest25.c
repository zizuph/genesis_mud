#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define H1 KRHERB + "cladina"
#define H2 KRHERB + "cladina"
#define H3 KRHERB + "cladina"
#define H4 KRHERB + "cladina"

object wolf;
object wolf2; 

void
reset_mithas_room()
{
    set_searched(random(4));

   if(!objectp(wolf))
   {
      wolf = clone_object(MNPC + "wolf");
      wolf->move(this_object());
   }
   if(!objectp(wolf2))
   {
      wolf2 = clone_object(MNPC + "wolf");
      wolf2->move(this_object());
   }
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
    set_short("Gloomy forest");
    set_long("@@long_descr"); 

    add_exit(MROOM + "forest24","west",0,2,1);
    add_item(({"forest"}),
     "The forest looks ancient. Old logs and branches "+
     "fill the forest floor and the strong smell of "+
     "decay and moisture fills the air. The forest "+
     "consists of different sorts of trees, a "+
     "mixture of pines and oaktrees.\n");

    add_item(({"trees","oaktrees","pine trees", "pines"}),
     "The trees here consist of a mixture of pines "+
     "and oaktrees. Only a few old trees remains, the rest "+
     "of the trees are either dead or dying.\n");

    add_item(({"underbrush","undergrowth"}),
     "The undergrowth here looks gray and dense with different "+
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

}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+
    "You stand within a gloomy forest in the southern part of "+
    "Mithas. The air here is filled with the smell of "+
    "decomposing wood and leaves. Only a few trees are left "+
    "here, most of them have died. Their rotten logs lie all "+
    "over the place, all of them filled with moss and fungus.\n";
}

