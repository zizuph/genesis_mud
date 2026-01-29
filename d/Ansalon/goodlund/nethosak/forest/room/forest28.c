/* 
 *  Added fishing properties allowing fishing - Arman 2021
 */

#include "/d/Ansalon/goodlund/nethosak/forest/local.h"
#include "/d/Ansalon/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
inherit MITHAS_OUT;

#include "/d/Krynn/common/herbsearch.h"
#include "/d/Ansalon/common/defs.h"

#define H1 KRHERB + "grey_willow"
#define H2 KRHERB + "cattail"
#define H3 KRHERB + "bur_reed"
#define H4 KRHERB + "raspberry"

#define LIVE_I_CAN_FISH      "_live_i_can_fish"

object fox;

void
reset_mithas_room()
{
   set_searched(random(4));

   if(!objectp(fox))
   {
      fox = clone_object(MNPC + "fox");
      fox->move(this_object());
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
   
    reset_mithas_room();

    set_short("Next to a stream");
    set_long("@@long_descr"); 


    add_item(({"stream", "water", "river"}),
     "The crystal clear water of the small stream, looks "+
     "very cold. A few fish are swimming in the shallow "+
     "stream.\n");

    add_item(({"fish", "fishes", "trouts", "trout"}),
     "Alot of trouts are swimming in the water. You wonder if you "+
     "might be able to catch one.\n");

    add_exit(MROOM + "forest27","northeast",0);
    add_exit(MROOM + "swamp1","southwest",0,2,1);

    add_cmd_item(({"fish"}),"catch","@@catch_fish");
    add_cmd_item(({"stream","water","from stream","water from stream"}),
      "drink","@@drink_water");
   
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


int
catch_fish()
{
    int chance;
    object obj;
    chance = random(10);

    if (TP->query_fatigue() < 35)
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
        obj = clone_object("/d/Ansalon/goodlund/nethosak/forest/obj/random_fish2");
        obj->move(TP,1);
        return 1;
    }
    write("You didn't manage to catch anything.\n");
    TP->add_fatigue(-40);
    return 1;
}

string
long_descr()
{ 
    return tod_descr()+ "" +season_descr()+
    "You are standing beside a small stream within "+
    "a vast forest in the southern part of Mithas. "+
    "The undergrowth here consists of a wide "+
    "variety of plant and herbs. "+
    "The trail continues to the northeast and "+
    "to the southwest across a stream.\n";
}

