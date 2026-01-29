#include "/d/Krynn/common/defs.h"
#include "../../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Krynn/common/clock/clock.h"

inherit CAVERNS_BASE;

#define HAS_SEARCHED   "_i_searched_dragon_eggs"

int eggs_broken = 0;
int figurine_found = 0;
object d1, d2, d3, d4, d5;

void
reset_tharkadan_room()
{
    if(eggs_broken)
      eggs_broken = 0; 

    figurine_found = 0;

    return;
}

create_tharkadan_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_exit(CAVERNS + "cavern_floor3","northeast","@@check_slip");
    add_exit(CAVERNS + "cavern_floor2","north","@@check_slip");
    add_exit(CAVERNS + "cavern_floor6","southeast","@@check_slip");

    add_prop(ROOM_S_DARK_LONG, "A dark, cold cavern. Without a light " +
          "source it is too dark to see in here.\n"); 
    add_prop(ROOM_S_DARK_MSG, "The cavern is too dark to"); 
    add_prop(ROOM_I_LIGHT, DARKNESS_PASSIVE);

    add_item(({"cold cavern","cavern","throat","floor","icy floor"}),
        "You stand on the icy floor of a great cavern within the throat " +
        "of the ancient volcano you stand within. It is quite " +
        "slippery... if you are not careful you think it likely to lose " +
        "your footing.\n");
    add_item(({"ice","basalt","sheet of ice","sheet"}), "The floor of " +
        "the cavern is a thick sheet of ice and basalt, accumulated " +
        "over ages and blocking the throat of the volcano.\n");
    add_item(({"volcano","ancient volcano"}),
        "You stand within the throat of what was once an ancient " +
        "volcano, long dormant. Over time its great vent above you " +
        "filled with ice and fell in on itself, creating the great " +
        "cavern you now stand within.\n");
    add_item(({"raised pile","pile of rocks","rocks","wall"}),
        "Against the wall of the cavern here has been raised a pile " +
        "of rocks... almost in the form of a halfheartedly-built nest.\n");
    add_item(({"eggs","large eggs","dragon eggs","clutch",
        "clutch of dragon eggs","dragon egg"}), "@@dragon_eggs_short");
    add_item(({"shells","broken shells","broken dragon eggs",
        "broken eggs"}), "@@dragon_shells_short");

    add_cmd_item(({"eggs","egg","dragon eggs","dragon egg","large egg",
        "large eggs","clutch of dragon eggs"}), ({"break","get","touch",
        "take"}), "@@get_dragon_eggs");

   add_search(({"eggs","large eggs","dragon eggs","clutch",
        "clutch of dragon eggs","dragon egg"}), 10, "search_eggs", 1);
               

    reset_tharkadan_room();
}

void
set_eggs_broken()
{
   eggs_broken = 1;
   seteuid(getuid(TO));

   d1 = clone_object(LIVING + "white_hatchling");
   d1->move(TO, 1);

   if(random(2) == 0)
   {
      d2 = clone_object(LIVING + "white_hatchling");
      d2->move(TO, 1);
   }
   if(random(3) == 0)
   {
      d3 = clone_object(LIVING + "white_hatchling");
      d3->move(TO, 1);
   }
   if(random(4) == 0)
   {
      d4 = clone_object(LIVING + "white_hatchling");
      d4->move(TO, 1);
   }
   if(random(5) == 0)
   {
      d5 = clone_object(LIVING + "white_hatchling");
      d5->move(TO, 1);
   }
}

void
set_eggs_reset()
{
   eggs_broken = 0;
}

string
dragon_eggs_broken()
{
   if(eggs_broken)
    return " broken";
   else
    return "";
}

string
dragon_eggs_short()
{
   if(eggs_broken)
     return "Upon the raised pile of rocks are a clutch of broken " +
         "dragon eggs, their shattered shells large and icy white.\n";
   else
     return "The shells of the dragon eggs radiate a cold " +
         "comparable to the icy floor around you.\n";
}

string
dragon_shells_short()
{
   if(eggs_broken)
     return "Shattered dragon egg shells are scattered across the " +
         "pile of rocks before you.\n";
   else
     return "Upon the raised pile of rocks are a clutch of large " +
         "dragon eggs! White in colour, they radiate a cold " +
         "comparable to the icy floor around you.\n";
}


string
short_descr()
{
    return "on the icy floor of a dark, cold cavern.\n" +
           "A clutch of" +dragon_eggs_broken()+ " dragon eggs";
}

string
long_descr()
{
    return "You stand on the floor of the cavern, a thick sheet of " +
        "slippery ice and basalt that now blocks the throat of " +
        "the ancient volcano you stand within. Upon a raised pile " +
        "of rocks against the wall here you notice a clutch of large" +
        dragon_eggs_broken()+ " eggs.\n";
}

int
check_slip()
{
   if(random(TP->query_stat(SS_DEX)) < random(200))
   {
      write("You slip on the icy floor of the cavern!\n");
      say(QCTNAME(TP) + " slips on the icy floor of the cavern!\n");
      return 1;
   }

   return 0;
}

string
get_dragon_eggs()
{
   if(eggs_broken)
     return "The dragon eggs are broken beyond any value.\n";

   write("As you reach towards the clutch of dragon eggs, they suddenly " +
      "crack and explode open, releasing young but hungry hatchlings!\n");
   say("As " +QTNAME(TP) + " reaches towards the clutch of dragon eggs, " +
      "they suddenly crack and explode open, releasing young but hungry " +
      "hatchlings!\n");

   set_eggs_broken();
   return "";
}

string
search_eggs(object searcher, string what) 
{
    object figurine; 
    object figurine_object = present("_thark_polymorph_figurine", TP);

    if (objectp(figurine_object) || figurine_found)
    {
	return ("You find nothing amongst the" +dragon_eggs_broken()+ 
                " dragon eggs.\n");
    }

    if (this_player()->query_prop(HAS_SEARCHED))
    {
	return ("You find nothing further amongst the" +
            dragon_eggs_broken()+ " dragon eggs.\n.\n");
    }

    if (!this_player()->query_prop(HAS_SEARCHED))
    {
	this_player()->add_prop(HAS_SEARCHED, 1);
        figurine = clone_object(TOBJ + "polymorph_figurine");
        figurine->move(searcher, 1);
        figurine_found = 1;

        say(QCTNAME(searcher) + " finds something nestled amongst the" +
            dragon_eggs_broken()+" dragon eggs.\n");
	return ("You carefully search through the"+dragon_eggs_broken()+ 
            " dragon eggs and find a strange quartz figurine nestled " +
            "among them! You pick it up.\n");
    }

  return 0;
}
