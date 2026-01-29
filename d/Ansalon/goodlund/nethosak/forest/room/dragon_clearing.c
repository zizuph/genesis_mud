#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

object dragon; 

void
reset_mithas_room()
{
   if(!objectp(dragon))
   {
      dragon = clone_object(MNPC + "firestar");
      dragon->move(this_object());
   }
}

void
create_mithas_room()
{
    set_short("Small clearing");
    set_long("@@long_descr"); 

    add_exit(MROOM + "forest62","northwest",0,2,1);
    reset_mithas_room();

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

}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+
    "You stand within a small clearing in the southern part "+
    "of Mithas. The all the trees here has been cut down by "+
    "some great force. All the moss and grass from the ground "+
    "has been removed and scooped to one side. The forest is "+
    "very silent here, only a few birds can be seen.\n";
}

