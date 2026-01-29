/*
 * File         : /d/Genesis/start/hobbit/town/villagehall.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/24/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        The village hall is where the start location is. The genesis FAQ,
 *        Village history and related documents sits on a shelf besides a
 *        proclamation board with hints about the city and a brief city
 *        map. Outside the creek makes a nice view with flowerbeds on both
 *        sides and 2-3 wooden bridges. There is also a young female
 *        hobbit sitting behind a desk answering 10-12 newbie questions
 *        like: Q: I am hungry A: The bakery is south of here. Q: I am
 *        thirsty A: The pub is just north of here. Q: I want adventure A:
 *        The port for distant lands is just down-streams Q: I am bored A:
 *        Buy a rod in the shop and go fishing. The village hall is built
 *        of white painted dried mud and stones and has a tower with a
 *        copper roof. The tower bell can be tolled when under danger to
 *        gather the village garde. The garde will assist an attacked
 *        newbie hobbit against the attacker. If no attack or the puller
 *        is not a hobbit the garde will just be annoyed and tell the
 *        combatants where they should go if they want to fight (outside
 *        the gate)
 * 
 * TODO         :
 *        - Add descriptions - Add bell functionality (sound + gather team
 *         of npc:s)
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
object Board;
object Informer;

/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("The village hall");
    set_long(
      "The light and height of this building makes ideal for mass " +
      "meetings with the village inhabitants. It is the highest " +
      "building in the village with a bell tower as high as roughly 5 " +
      "normal hobbit lengths. There are sounds of rippling water, " +
      "chirping birds and and an active village population comming from " +
      "just outside. A desk with a sign resides in one corner and in " +
      "the opposite a narrow wooden staircase leads down. A rope hangs " +
      "down from the ceiling.\n");
    add_item("bell", 
      "The bell seems to be made of bronze and has a rope attached to " +
      "it. \n");
    add_item("rope", 
      "The rope is rather thick and is attached to a small bell in " +
      "the tower of the village hall. \n");
    add_item("sign", 
      "The small sign reads 'Ask me about our village'. \n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG,
      "It's dark, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the villagehall.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/24/99.\n");
    
    add_exit("crypt.c", "down");
    add_exit("villageroad3.c", "east");
    add_exit("villageroad1.c", "north");
    add_exit("villageroad5.c", "south");
    add_exit("woodenbridge2.c", "west");
    
    
    add_cmd_item("rope", "pull",
      "You pull the rope and a second later the village bell tolls bright and clear\n");
    
    seteuid(getuid());
    
    Board = clone_object(EX_OBJ + "board");
    Board->move(this_object(), 1);
    
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
    if (!objectp(Informer))
    {
        Informer = clone_object(EX_MON + "informer");
        Informer->move(this_object(), 1);
        tell_room(TO, QCTNAME(Informer) + 
            " appears behind the desk.\n");
    }
    
}

void
init()
{
    ::init();
    
    // Check if the NPC is here and let him check the player
    if (Informer && present(Informer))
    {
        Informer->set_visitor(this_player());
    }
}


