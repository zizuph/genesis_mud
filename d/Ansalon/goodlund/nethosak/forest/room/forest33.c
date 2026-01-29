/* Navarre June 25th 2006, changed a lot of trouts to
 * a lot of trout
 *
 *  Added fishing properties allowing fishing - Arman 2021
 */

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
inherit MITHAS_OUT;

#include "/d/Krynn/common/herbsearch.h"

#define H1 KRHERB + "grey_willow"
#define H2 KRHERB + "grey_willow"
#define H3 KRHERB + "jewelweed"
#define H4 KRHERB + "jewelweed"

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

object deer;
object deer2; 

void
reset_mithas_room()
{
   set_searched(random(4));
   if(!objectp(deer))
   {
      deer = clone_object(MNPC + "deer");
      deer->move(this_object());
   }
   if(!objectp(deer2))
      {
      deer2 = clone_object(MNPC + "deer");
      deer2->move(this_object());
   }
}

void
create_mithas_room()
{
    set_search_places(({"underbrush","herbs",
                       "trail", "path", "ground"}));
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    add_prop(LIVE_I_CAN_FISH, "freshwater");

    add_herb_file(H1);
    add_herb_file(H2);
    add_herb_file(H3);
    add_herb_file(H4);
   
    set_short("Next to a stream");
    set_long("@@long_descr"); 

    add_exit(MROOM + "forest34","east",0);
    add_exit(MROOM + "nowhere","southwest","@@cross_stream");  

    add_cmd_item(({"fish"}),"catch","@@catch_fish");
    add_cmd_item(({"trout"}),"catch","@@catch_fish");
    add_cmd_item(({"stream","water","from stream","water from stream"}),
      "drink","@@drink_water");

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

    add_item(({"stream", "water", "river"}),
     "The crystal clear water of the small stream, looks "+
     "very cold. A few fish are swimming in the shallow "+
     "stream.\n");

    add_item(({"fish", "fishes", "trout"}),
     "A lot of trout are swimming in the water. You wonder if you "+
     "might be able to catch one.\n");

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

    add_cmd_item(({"stream","water","from stream","water from stream"}),
      "drink","@@drink_water");

    reset_mithas_room();
}

int
cross_stream()
{
    write("You begin to cross to stream, but realize that the "+
          "water is too deep at the moment.\n");
    return 1;
}


string
drink_water()
{
    if(TP->drink_soft(TP->drink_max() /16, 0))
    {
        write("You find a spot with some fairly clean water "+
              "and take a drink from the stream.\n");
        say(QCTNAME(TP) + " finds a spot with some clean "+
              "water and takes a drink from the stream.\n");
        return "";
    }
    else
        write("You are full of water, you can't drink anymore.\n");
    return "";
}


string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+
    "You are standing beside a small stream within "+
    "a vast forest in the southern part of Mithas. "+
    "The undergrowth here consists of a wide "+
    "variety of plant and herbs. "+
    "The trail continues to the east and "+
    "to the southwest across a stream.\n";
}

int
catch_fish()
{
    int chance;
    object obj;
    chance = random(5);

    if (TP->query_fatigue() < 10)
    {
        write("You are too exhausted to try and catch another fish.\n");
        return 1;
    }
    write("You attempt to catch a fish with your hands.\n");
    say(QCTNAME(this_player()) + " attempts to catch a fish.\n");
    if (chance == 1)
    {
        write("You skillfully catch a fish!\n");
        say(QCTNAME(this_player()) + " caught a fish!\n");
        setuid();
        seteuid(getuid());
        obj = clone_object("/d/Ansalon/goodlund/nethosak/forest/obj/random_fish");
        obj->move(TP,1);
        return 1;
    }
    write("You didn't manage to catch anything.\n");
    TP->add_fatigue(-10);
    return 1;
}
