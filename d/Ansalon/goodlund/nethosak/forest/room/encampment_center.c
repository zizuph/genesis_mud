#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include <stdproperties.h>
#include "/d/Genesis/gems/gem.h"

inherit MITHAS_OUT;

object troll, troll2, troll3;
object gem, gem2, gem3;

void
reset_mithas_room()
{
   if(!objectp(troll))
   {
      troll = clone_object(MNPC + "troll");
        // Provides gems up to very rare
        gem = RANDOM_GEM_BY_RARITY(GEM_VERY_RARE);
        gem->move(troll,1);
      troll->move(this_object());
   }
   if(!objectp(troll2))
   {
      troll2 = clone_object(MNPC + "troll");
        // Provides gems up to very rare
        gem2 = RANDOM_GEM_BY_RARITY(GEM_VERY_RARE);
        gem2->move(troll2,1);
      troll2->move(this_object());
   }
   if(!objectp(troll3))
   {
      troll3 = clone_object(MNPC + "troll");
        // Provides gems up to very rare
        gem3 = RANDOM_GEM_BY_RARITY(GEM_VERY_RARE);
        gem3->move(troll3,1);
      troll3->move(this_object());
   }
}

void
create_mithas_room()
{
    set_short("Center of encampment");
    set_long("@@long_descr"); 
    enable_reset(33);

    add_exit(MROOM + "trail2","north",0);
    add_exit(MROOM + "encampment_south","south",0);
    add_exit(MROOM + "encampment_east","east",0);
    add_exit(MROOM + "encampment_west","west",0);
    add_exit(MROOM + "encampment_southwest","southwest",0);
    add_exit(MROOM + "encampment_southeast","southeast",0);
    add_exit(MROOM + "encampment_northwest","northwest",0);
    add_exit(MROOM + "encampment_northeast","northeast",0);

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

    add_item(({"fire"}),
     "The large fire burns brightly. Looks like someone recently "+
     "threw some logs on it.\n");

    add_item(({"cauldron"}),
     "The mat dark cauldron is empty.\n");

    reset_mithas_room();
}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+
    "You stand in the center of a small troll encampment. The trees and bushes "+
    "has been removed from this area, revealing the soft dirt. A large fire "+
    "in the center of the camp, and over it a large cauldron has been set up. "+
    "The encampment continues in almost every direction, however going northward "+
    "would take you out of it, and into the forest again.\n";
}

