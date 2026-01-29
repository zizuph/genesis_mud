#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

void
reset_mithas_room()
{

}

void
create_mithas_room()
{
    reset_mithas_room();
    set_short("Hidden forest trail");
    set_long("@@long_descr"); 

    add_exit(MROOM + "trail1","north",0);

    add_exit(MROOM + "encamp_center3","southeast",0);
    add_exit(MROOM + "encampment_center","south",0);
    add_exit(MROOM + "encamp_center2","southwest",0);

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

    add_item(({"prints","footprints"}),
     "These footprints are quite large, they might resemble "+
     "the ones of a troll or ogre.\n");

    add_item(({"camp","encampment"}),
     "To your surprise you spot some tall trolls to the south, "+
     "you better be careful if you want to stay alive.\n");

}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+
    "You stand on a vague forest trail. A few large footprints have "+
    "been made in the soft forest floor. The trail continues to the "+
    "south where a small encampment has been made, and further "+
    "into the forest to the north.\n";
}

