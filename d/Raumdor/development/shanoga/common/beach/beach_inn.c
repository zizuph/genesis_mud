#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include "defs.h"

#undef    COMMON_DIR
#undef    BEACH_DIR
#define   COMMON_DIR   "/d/Raumdor/development/shanoga/common/"
#define   BEACH_DIR    COMMON_DIR + "beach/"

inherit STD_ROOM;
inherit "/lib/pub";

object obj;

void
create_room()
{
    set_short("The Hollow Haven");
    set_long("@@inn_long@@");
    
    add_item("counter", "The planks of wood that make up the surface of " +
      "the counter are rough and likely to give you splinters.\n");
    add_item(({ "window", "small window" }), "@@window_item@@");
    add_item(({"high chair","high chairs","stool","stools"}), "These " +
      "simple stools serve the dual purposes of giving visitors a place " +
      "to rest but simultaneously preventing them from getting " +
      "comfortable or enjoying themselves.\n");
    add_item("menu", "The short menu is carved into a piece of scrap wood " +
      "and haphazardly nailed to a post near the counter. You can read it.\n");
    add_item(({"chair","chairs"}), "@@chair_item@@");
    add_item(({"table","tables"}), "@@table_item@@");
    add_item(({"small table","small tables"}),"There are a few small " +
      "tables scattered about that could seat a traveler or two.\n");
    add_item("large table","This one round table is large enough to allow " +
      "a small group of patrons to sit together.\n");
    add_item("walls", "The walls of this small building are made of wood " +
      "planks of various lengths that effectively keep out the sea breeze " +
      "despite their rough construction.\n");
    add_item(({"shelves","shelving"}),"Plain and sturdy, the shelves on " +
      "the west wall are littered with unlabeled bottles.\n");
    add_item("bottles","Upon closer inspection, all of the bottles " +
      "scattered amongst the shelving are empty, except one bottle of " +
      "crudely hand-labeled whiskey.\n");
    add_cmd_item("menu", "read", "@@read");
    
    add_prop(ROOM_I_INSIDE,1); 
    add_drink( ({ "whiskey", "whiskeys", "flask", "flasks",
      "flask of whiskey", "flasks of whiskey"}),
      "whiskey", "strong", 80, 40, 200, "flask of whiskey",
      "flasks of whiskey", "This is a shot of strong whiskey stored in a " +
      "disposable container, making it easier to travel with.\n", 0);
    add_drink( ({ "water", "waters", "pouch", "pouches", "water pouch",
      "water pouches" }), "water", "pouch", 200, 0, 12,
      "water pouch", "water pouches", "A pouch of water that must be " +
      "torn open to drink.\n", 0);
    add_food( ({ "special", "specials", "adventurer's special",
      "adventurer's specials" }), "special", "adventurer's", 40, 25,
      "adventurer's special", "adventurer's specials", "This is " +
      "a small packet of nuts, dried berries, and crusty bread mixed " +
      "together to provide adventurers with a bit of energy when " +
      "traveling.\n", 0);

    add_exit(BEACH_DIR + "beach3","out");
    obj = clone_object(BEACH_DIR + "npc/innkeeper.c");
    obj->arm_me();
    obj->move_living("M",TO);
}

string
inn_long()
{
    string str = "You are in a simple, dimly-lit wooden shack that " +
      "operates as a refuge to weary travelers. ";
      
    if (DAY)
    {
        str += "Chairs and tables are scattered around to give patrons " +
          "a place to rest and wait for the relative safety of daylight " +
          "before venturing into the forest. The innkeeper is focused on " +
          "cleaning up after the previous night's visitors and preparing " +
          "for another busy night ahead. ";
    }
    else
    {
        str += "The plain interior offers a place of rest and relative " +
          "safety from the cold dark of night. The tables and chairs are " +
          "set up for travelers to wait until daybreak to continue their " +
          "adventures. ";
    }
    str += "There is a counter near the east wall. Given the shelving behind it and the high chairs in front, it seems to double as a bar. A small window is framed about halfway up the west wall. There is a menu posted by the counter.\n";
    return str;
}

string
window_item()
{
    string str = "There is a small four-paneled window in the west wall " +
      "over looking the beach and the sea. The glass is warped, " +
      "distorting the view and betraying its shoddy craftsmanship. "; 
    if (DAY)
    {
        str += "The sun is shining brightly and glistening off the gently " +
          "rolling waves, inviting adventure and tales untold beyond the " +
          "horizon.\n";
    }
    else
    {
        str += "The darkness outside fills you with discomfort and you " +
          "feel a surprising appreciation for the warmth and protection " +
          "this inn provides through the night.\n";
    }
    return str;
}

string
chair_item()
{
    string str = "There are high stools along the counter and smaller chairs " +
      "to go with the tables. The chairs are simple and clearly were " +
      "designed for function over form or comfort. "; 
    if (DAY)
    {
        str += "The chairs are strewn about the room after another night " +
          "of travelers have come and gone from the inn.\n";
    }
    else
    {
        str += "The innkeeper has placed the chairs around the tables so " +
          "visitors can gather and rest through the night.\n";
    }
    return str;
}

string
table_item()
{
    string str = "There are a few small tables and one large table for " +
      "the rare group of adventurers that have the misfortune of spending " +
      "time here. ";
    
    if (DAY)
    {
        str += "If the tables were ever set up in an organized fashion, " +
        "the innkeeper has not yet restored them to order after the " +
        "previous night's visitors.\n";
    }
    else
    {
        str += "The chairs are spread out amongst the tables, welcoming " +
          "patrons to stay through the night.\n";
    }
    return str;
}

void
reset_room()
{
    if(!obj)
    {
    obj = clone_object(BEACH_DIR + "npc/innkeeper.c");
    obj->arm_me();
    obj->move_living("M",TO);
    }
}

void
init()
{
    ::init(); 

    init_pub();
}

int
read(string str)
{
    write(
      "@~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~@\n" +
      "}          The Hollow Haven         }\n" +
      "}                                   }\n" +
      "} Water pouch            ~    12 cc }\n" +
      "} Flask of whiskey       ~    80 cc }\n" +
      "}                                   }\n" +
      "} Adventurer's special   ~   160 cc }\n" +
      "}                                   }\n" +
      "} ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ }\n" +
      "}                                   }\n" +
      "}  All items specially packaged to  }\n" +
      "}  aid travelers in their journeys  }\n" +
      "}   through the wicked forest and   }\n" +
      "}      the defiling rot within      }\n" +
      "}                                   }\n" +
      "@~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~@\n\n");
    return 1;
}