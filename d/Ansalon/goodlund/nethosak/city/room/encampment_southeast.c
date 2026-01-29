#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include <stdproperties.h>
inherit MITHAS_OUT;

object troll, troll2, troll3;

void
reset_mithas_room()
{
   if(!objectp(troll))
   {
      troll = clone_object(MNPC + "troll");
      troll->move(this_object());
   }
   if(!objectp(troll2))
   {
      troll2 = clone_object(MNPC + "troll");
      troll2->move(this_object());
   }
   if(!objectp(troll3))
   {
      troll3 = clone_object(MNPC + "troll");
      troll3->move(this_object());
   }
}

void
create_mithas_room()
{
    reset_mithas_room();
    set_short("Southeast corner of encampment");
    set_long("@@long_descr"); 

    add_exit(MROOM + "encampment_center","northwest",0);

    add_item(({"forest"}),
     "The forest looks ancient. Old logs and branches "+
     "fill the forestfloor and the strong smell of "+
     "decay and moisture fills the air. The forest "+
     "consists of different sorts of trees, a "+
     "mixture of pines and oaktrees.\n");

    add_item(({"trees","oaktrees","pine trees", "pines"}),
     "The trees here consist of a mixture of pines "+
     "and oaktrees. Only a few old trees remains, the rest "+
     "of the trees are either dead or dying.\n");

    add_item(({"underbrush","undergrowth", "forestfloor"}),
     "The undergrowth here looks gray and dense with different "+
     "plants and herbs. It seems like it's impossible "+
     "to enter it. \n");

    add_item(({"trail","path"}),
     "The forest trail twists itself further into "+
     "the forest. It's a bit overgrown with different "+
     "plants and herbs species.\n");

    add_item(({"canopy", "treetops"}),
     "The canopy above you looks thick, only a few sunrays "+
     "are able to enter the forest. You notice a few birds "+
     "above you, but they quickly vanish in the thick canopy.\n");

    add_item(({"leaves","branches"}),
     "The branches and leaves here, have almost decomposed "+
     "into dirt. Only a few of them looks fairly new, but "+
     "they are still covered with moss and fungus.\n");

    add_item(({"bone","bones"}),
     "The bones are from the different forest creatures. They have "+
     "chewed up and broken.\n");

    add_item(({"skins", "skin"}),
     "The different skins smells very bad, they are almost rotten, and some of "+
     "them even has quite a collection of maggots.\n");
}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+
    "You stand in the southeast corner of the troll encampment. The ground "+
    "here has been covered with leaves, and skins from various creatures. A "+
    "few bones lies scattered to one of the sides. A few trees seems to give "+
    "the trolls a bit of shade from the hot sun. The only exit out of here is "+
    "to the northwest.\n";
}

