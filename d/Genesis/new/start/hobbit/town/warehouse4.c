/*
 * File         : /d/Genesis/start/hobbit/town/warehouse4.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/12/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        Empty warehouse with a pile of junk in the back. Behind the junk
 *        some loose planks makes it possible to enter the back of the
 *        warehouse and from there a secret swamppath to the canal.
 * 
 * TODO         :
 *         * - Add rodent NPC's running around on the floor
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
public void     create_room();
public void     reset_room();
public string   do_search(object tp, string arg);

/* globals */
int secret_exit_found;

/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("A warehouse");
    set_long(
      "A few barrels and some crates are scattered at the floor in this " +
      "warehouse. Even though there is only one visible entrance a " +
      "small breath of fresh air can be noticed through the room. The " +
      "containers seems to have been placed here quite recently.\n");
    add_item(({ "barrel", "barrels" }), 
      "A few sealed barrels are piled in a corner of this warehouse. \n");
    add_item("ceiling", 
      "The inside of the reed roof is tigthly put onto the wall to " +
      "keep the temprature. \n");
    add_item(({ "container", "containers" }), 
      "Some barrels and crates fills a part of this warehouse. \n");
    add_item(({ "crate", "crates" }), 
      "There are some crates here filled with wool. \n");
    add_item("floor", 
      "The plank floor is pretty worn due to the heavy traffic of " +
      "goods here. \n");
    add_item(({ "label", "labels" }), 
      "Most goods has a label which tells about originator and " +
      "destination as well as contents \n");
    add_item(({ "seal", "seals" }), 
      "Almost all containers are tightly closed and a wearing a " +
      "wax-seal to detect unauthorized access to the goods. \n");
    add_item("sign", 
      "A sign-ring pressed into hot seal-wax signs a container with a " +
      "wax-seal before delivery. \n");
    add_item("smell", 
      "A mix of wool and oak barrels makes up an dence smell in this " +
      "warehouse. \n");
    add_item("walls", 
      "Sturdy timber walls protects the goods from thiefs and there " +
      "is only a small window at the back wall. \n");
    add_item(({ "wax-seal", "wax-seals" }), 
      "A signed wax-seal confirms who wrote the label and that the " +
      "goods are untouched and that the label has not been altered. \n");
    
    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, do_search);
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG,
      "It's dark, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the warehouse.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/12/99.\n");
    
    add_exit("eastpier5.c", "west");
    
    
    
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
    ::reset_room();
    if (secret_exit_found)
    {
        secret_exit_found = 0;
        remove_exit("east");
        remove_item("hole");
    }
    
}

/*
* Function name: do_search
* Description  : perform search and generate messages The code
*                is based on an example from Gnadnar in the startloc
*                project
*/
public string
do_search(object tp, string arg)
{
    string msg;
    string saymsg;
    
    arg = lower_case(arg);
    if (arg == "here")
    {
        msg    = "You crawl around on the floor searching for " +
                 "the unknown but it leaves you clueless.\n";
        saymsg = QCTNAME(tp) + " found no secrets on the floor.\n";
    }
    else if (secret_exit_found)
    {
        msg    = "";
        saymsg = "";
    }
    else switch (arg)
    {
        case "barrel":
        case "barrels":
        case "crate":
        case "crates":
        case "container":
        case "containers":
        {
            msg    = "You reveal a big hole in the back wall!\n";
            saymsg = QCTNAME(tp) + " reveals a big hole in the back wall!\n";
            secret_exit_found = 1;
            add_exit("swamppath2", "east");
            add_item("hole", 
                "The hole in the back wall seems big enough to enter.\n");
            break;
        }
        default:
        {
            msg    = "";
            saymsg = "";
        }
    }
    if (saymsg != "")
    {
        say(saymsg);
    }
    return(msg);
}


