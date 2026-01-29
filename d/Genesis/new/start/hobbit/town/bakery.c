/*
 * File         : /d/Genesis/start/hobbit/town/bakery.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/18/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The baker is a very fat young female hobbit. She met her husband
 *        in the camp on the other continent. She has fresh bread, pies,
 *        cakes, 25 different kind of candies and 3 kinds of cookies. Also
 *        she makes a special adventurer bread made of seaweed and a
 *        special bark which gives extra energy exploring the realms.
 * 
 * TODO         :
 *        add baked goods, handle selling them
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

#pragma strict_types

/* inherits */
inherit "/std/room";



/* includes */
#include <stdproperties.h> 
#include <macros.h> 

#include "../hobbit.h"

/* defines */



/* prototypes */
void create_room();
void reset_room();

/* globals */
static object   Baker;


/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("The village bakery");
    set_long(
      "The room is bright and filled with boxes of sweets and pastries. " +
      "A beam of sunlight can be seen in the dusty air and behind the " +
      "counter stands an increadably fat female baker. On the wall " +
      "hangs a floury pricelist.\n");
    add_item(({ "candy", "sweets", "boxes", "heaps" }), 
      "Paper screws with sweets and candies lies stapled on the " +
      "counter \n");
    add_item("ceiling", 
      "In contrast to the clean white walls the ceiling is quite " +
      "sooted. \n");
    add_item(({ "counter", "counter top" }), 
      "Piles of candies completelly cover the counter top \n");
    add_item("floor", 
      "Besides a thin layer of flour the floor is rather clean. \n");
    add_item(({ "pricelist", "price list" }), 
      "The pricelist is well dusted with flour, but prices are still " +
      "readable. \n");
    add_item(({ "walls", "wall" }), 
      "The walls seems to be white and clean. The east wall has a " +
      "round window towards the street. \n");
    add_item("window", 
      "The window has a round shape as most windows in this village. \n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG,
      "It's dark, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the bakery.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/18/99.\n");
    
    add_exit("portroad1.c", "east");
    
    
        add_cmd_item(({ "pricelist", "price list" }),
          "read",
          " Pricelist\n------------\n\n");
    
    
    
    reset_room();
}
/*
 * Function name:       reset_room
 * Description  :       replenish npc & stuff, if needed
 */
void
reset_room()
{
    setuid();
    seteuid(getuid());
    if (!objectp(Baker))
    {
        Baker = clone_object(EX_MON + "baker");
        Baker->move(this_object(), 1);
        tell_room(TO, QCTNAME(Baker) + 
            " appears from behind the counter with a happy smile.\n");
    }
    
}

void
init()
{
    ::init();
    
    // Check if the NPC is here and let it check the player
    if (Baker && present(Baker))
    {
        Baker->set_visitor(this_player());
    }
}


