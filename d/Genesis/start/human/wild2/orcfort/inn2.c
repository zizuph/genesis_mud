/*
* Vladimir 9-8-94
*/

#pragma strict_types

inherit "/std/room";
inherit "/lib/pub";

#include <stdproperties.h>
#include <macros.h>
#include <money.h>

#include "local.h"


/*
* Function name: create_room
* Description:   Set up default trade and cofigure it if wanted.
   */
void
create_room()
{
    set_short("The Belching Orc Bar");
    set_long(
      "This is the Belching Orc Bar.\n"
      + "All you can think about is how much this place lives up\n"
      + "to its name! There are four crudely built tables scattered\n"
      + "about the room. Each table is crowded with drunk, smelly\n"
      + "orcs. As you walk in they drunkenly stare at you. Eventually\n"
      + "one of them passes out and the rest go about their business.\n"
      + "Behind the bar you notice some rather strange concoctions.\n"
      + "You notice orc guards standing near the door, you assume\n"
      + "them to be bouncers.\n"
      + "There is a plaque standing prominently on the wall.\n");
   
    add_item("plaque", 
      "-------------------------------------------------------------\n"
      + "|                                                           |\n"
      + "|     G E N E S I S  B O A R D  O F  H E A L T H            |\n"
      + "|     ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~            |\n"
      + "|              ------------                                 |\n"
      + "|              |                                            |\n"
      + "|              |                                            |\n"
      + "|              |                                            |\n"
      + "|              |______                                      |\n"
      + "|              |                                            |\n"
      + "|              |                                            |\n"
      + "|              |                                            |\n"
      + "|              |                                            |\n"
      + "|              |                                            |\n"
      + "|                                                           |\n"
      + "|                                                           |\n"
      + "|     WARNING!!! EATING HERE CAN BE HAZARDOUS TO            |\n"
      + "|                YOUR HEALTH, AS WELL AS TO YOUR            |\n"
      + "|                POCKET!!!                                  |\n"
      + "|                                                           |\n"
      + "|                                                           |\n"
      + "-------------------------------------------------------------\n");
    add_item("bar", "It consists of rotting wood.\n");
    add_item("menu", "It has a lot of readable words on it.\n");
    add_item("concoctions",
             "They look rather gross.\n");
    add_item("tables", "They falling apart, and seem to have many "+
             "sticky beer stains on them.\n");
    add_cmd_item("menu", "read", "@@read");
   
    add_prop(ROOM_I_INSIDE,1);  /* This is a real room */
    add_prop(ROOM_S_MAP_FILE, "orc_temple.txt");
   
    add_drink( ({ "beer", "beers", "orc", "orc beer" }),
               "beer", "orc", 100, 4, 150, 0, 0,
               "An extremely strong, nasty beer.\n", 0);
    add_drink( ({ "ale", "ales", "watered down", "watered down ale" }),
               "ale", "watery", 200, 20, 72, 0, 0,
               "It is just old ale that has been watered down.\n", 0);
    add_food( ({ "rat", "rats" }),
              "rat", "fried", 85, 80, 0, 0,
              "It smells and looks disgusting.\n", 0);
    add_food( ({ "moldy", "moldy soup", "soup", "soups" }),
              "soup", "moldy", 65, 80, "bowl of moldy soup",
              "bowls of moldy soup",
              "It doesn't smell very good at all.\n", 0);
    add_food( ({ "brain", "bird", "bird brains",
                     "bird brain", "brains" }),
              "bird brain", 110, 105,
              "A small bunch of bird brains.\n", 0);

    add_exit(ORC+"r4", "west");
    add_exit(ORC+"bckroom", "north");

    add_npc(OBJ_DIR + "orc", 3, &->arm_me());
    add_npc(ORC + "monsters/borc", 2, &->arm_me());
}


/*
* Function name: init
* Description:   Initalize the pub actions
*/
void
init()
{
   ::init(); /* Since it's a room this must be done. */
   
   init_pub();
}

/*
* Function name: read
* Description:   Read the menu
* Arguments:     str - hopefully the menu
*/
int
read(string str)
{
    write("" +
          "   Orc pride beer             100 cc\n" +
          "   Watered down ale           72 cc\n" +
          "   Moldy soup                 80 cc\n"+
          "   Fried rat                  80 cc\n" +
          "Try 'buy beer with gold' if you wanna specify what to\n" +
          "pay with, or 'test buy beer' to see what would happen\n" +
          "if you typed 'buy beer'. 'buy 10 beer' would get you\n" +
          "ten beers from the bar, but it takes a little while to\n" +
          "give them all to you.\n");
    return 1;
}
