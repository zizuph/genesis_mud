/******************************************************
 *
 *
 * NOTE!!!!!!!! Quest-solution for this quest in Mithas
 * is already out! So, this is just a dummy door.
 * It will never be opened.
 * -Elmore.
 *
 ******************************************************/

#include "/d/Ansalon/goodlund/nethosak/city/obj/door.h"
#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit MITHAS_OUT;

void
create_mithas_room()
{
    object door;
    set_short("Forest of Mithas");
    set_long("@@long_descr"); 

    add_exit(MROOM + "forest74","north",0,2,1);

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

    add_item(({"stones","rocks"}),
     "These thin stones cover a square area on the forest floor. "+
     "They might have been put here to cover the gate.\n");

     door = clone_object(MOBJ + "woodendoor3");
     door->move(this_object());
}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+ 
    "You are standing on a small hill within a vast "+
    "forest in the southern part of Mithas. The trail "+
    "here is covered in moss and branches, it looks "+
    "like there hasn't been anyone here for years. "+
    "A few rocks are lying here in a small circle.\n";
}

