/*
 * The Shirriffe's off in Frogmorton
 * By Finwe, September 1998
 */
 
inherit "/d/Shire/room.c";
#include "/d/Shire/sys/defs.h"
#include "defs.h"

//void reset_room();
 
static object hobbit;

void
create_room()
{
    set_short("Headquarters of the East Farthing Troop of " +
        "the Watch");
    set_long("This is the headquarters of the East Farthing " +
        "Troop of the Watch. The watch is made up of Bounders " +
        "that keep undesirable outsiders from entering the " +
        "Shire and taking care of Inside Work. Bounders come " +
        "and get their orders from the Shirriffe here for the " +
        "East Farthing. The stone building has little in it " +
        "except for a desk, a chair, and a poster.\n");

    add_item(({"up", "ceiling"}),
        "The ceiling is peaked and made of wood slats\n");
    add_item(({"down", "ground", "floor"}),
        "The floor is made of wood planks. They are swept clean " +
        "and have a worn trail around the desk and from the " +
        "desk to the door.\n");
    add_item(({"wall", "walls"}), 
        "The walls are made of vertical wood planks. Some " +
        "posters are nailed to the walls.\n");
   add_item(({"planks", "slats"}),
        "They are yellow from age and look like they were " +
        "from beech.\n");
    add_item("desk", 
        "The desk is made of dark maple. It looks well used " +
        "and has some papers scattered across the top.\n");
    add_item("papers",
        "They are orders and instructions for the Troops of " +
        "the East Farthing Watch.\n");
    add_item("poster", 
        "It is large and covers part of one wall. There is some " +
        "stuff written on it.\n");
        
 
 
    add_cmd_item("poster", "read", "@@read_poster@@");
    add_cmd_item(({"orders", "papers"}), "read", "@@read_orders@@");   
 
 
    add_exit(FROG_DIR + "road02", "out");
    reset_shire_room();
 
}
 
int read_orders()
{
    write ("They are orders relating to catching missing animals " +
        "and keeping track of undesirables in the Shire.\n");
    say(QCTNAME(TP) + " reads some papers on the desk.\n");
    return 1;
}

int read_poster()
{
    write ("\n\n" +
          "        +--------------------------------------------------+\n" +
          "        |  *                                            *  |\n" +
          "        | * *                                          * * |\n" +
          "        |   When travelling through the Shire, be careful  |\n" +
          "        |   who you talk to and where you go. Strange      |\n" +
          "        |   travellers have been seen on the Great East    |\n"+
          "        |   Road and even stranger things have been        |\n" +
          "        |   observed. If you see anything unusual, be sure |\n" +
          "        |   to report it to a Bounder who will take care   |\n" +
          "        |   of the situation.                              |\n" +
          "        |                                                  |\n" +
          "        |   Also, be on the lookout for the following:     |\n" +
          "        |                                                  |\n" +
          "        |   * Amanda is looking for her husband. Seems he  |\n" +
          "        |     always leaves with out his lunch. What are   |\n" +
          "        |     we going to do about him? Anyhow, find her   |\n" +
          "        |     to get more information.                     |\n" +
          "        |   * The Shirriffe near Michel Delving needs      |\n" +
          "        |     some help. Rumour has it there are orcs      |\n" +
          "        |     nearby but he needs someone to find them for |\n" +
          "        |     him.                                         |\n" +
          "        |   * Bibbles is having trouble with his cow. See  |\n" +
          "        |     what you can do yo help him.                 |\n" +
          "        |   * Isembold has run out of hay for his pony. He |\n" + 
          "        |     may need your help.                          |\n" + 
          "        | * *                                          * * |\n" +
          "        |  *                                            *  |\n" +
          "        +--------------------------------------------------+\n\n");
    say(QCTNAME(TP) + " read the poster on the wall.\n");
    return 1;
}


void
reset_shire_room()
{
    if (!hobbit)
    {
        hobbit = clone_object(FNPC_DIR + "falco");
        hobbit->move(TO);
    }
}