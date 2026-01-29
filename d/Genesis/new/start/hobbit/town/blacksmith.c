/*
 * File         : /d/Genesis/start/hobbit/town/blacksmith.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/18/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The village smith is rather primitive but very functional. The
 *        speciality for this smith is the farmer tools made. Even weapons
 *        can be remade to fairly useful farmer tools here. Remeber the
 *        history when the hobbits came here with nothing but a load of
 *        weapons and armours. Most of it passed the hands of this skilled
 *        smith and her mentor (who died a couple of years ago).
 * 
 * TODO         :
 *        Add blacksmith trade features
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
static string exa_list();

/* globals */
object Smith;

/*
 * Function name:       create_room
 * Description  :       set up the room, called on first entry
 */
void
create_room()
{
    set_short("the village blacksmith's workshop");
    set_long(
      "A moisty heat fills the room and a high piercing sound comes from " +
      "an anvil where glowing metal pieces are formed to all kinds of " +
      "equipment. Instead of a front wall there is a number a skins " +
      "sewn together into two halfs and now tied apart to let steam out " +
      "and customers in. The forge is filled with live coals and the " +
      "heat makes pieces of metal incandescent.\n");
    add_item("anvil", 
      "The blackened and battered iron anvil stands nearby the forge. \n");
    add_item("ceiling", 
      "The ceiling has been covered with animal skin on the inside " +
      "except for round hole in the middle to let the smoke out. \n");
    add_item("floor", 
      "This building has a stamped sand floor. \n");
    add_item(({ "forge", "coal", "coals", "heat" }), 
      "Live coals resides in the open forge and are used to heat " +
      "metal pieces so that they can be formed on the anvil. \n");
    add_item(({ "metal", "pieces", "metal pieces" }), 
      "Metal equipment are scattered all over the workshop awaiting " +
      "forging or delivery. \n");
    add_item(({ "skin", "skins" }), 
      "Old sooted animal skins are used as door and covers the reed " +
      "roof on the inside to avoid sparkles to set the building on " +
      "fire. \n");
    add_item("smell", 
      "A warm moisty mix of sweat, mysk and hot metal fills this tent " +
      "like building. \n");
    add_item(({ "wall", "walls" }), 
      "There are sooted walls on each side of the forge except " +
      "towards the road where there is no wall because of the heat. \n");

    // forging stuff    
    add_item(({"sign", "pricelist", "list", }), exa_list);
    add_cmd_item(({"sign", "pricelist", "list", }), "read", 
        exa_list);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG,
      "It's dark, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the blacksmith.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/18/99.\n");
    
    add_exit("portroad2.c", "east");
    
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
    if (!objectp(Smith))
    {
        Smith = clone_object(EX_MON + "smith");
        Smith->move(this_object(), 1);
        tell_room(TO, QCTNAME(Smith) + 
            " appears from the dark behind the anvil.\n");
    }
    
}

/*
 * Function name:       init
 * Description  :       called when a player enters the room
 */
void
init()
{
    ::init();
    
    // Check if the NPC is here and let him check the player
    if (Smith && present(Smith))
    {
        Smith->set_visitor(this_player());
    }
}

static string
exa_list()
{
    if (Smith && present(Smith))
    {
        cat(EX_ROOM + "smith_emptystock.txt");
//        Smith->do_weapon_list("", 1);
    }
    else
    {
        cat(EX_ROOM + "smith_pricelist.txt");
    }

    return "";
}
