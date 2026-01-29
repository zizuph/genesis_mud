/*
 * File         : /d/Genesis/start/hobbit/town/bank.c
 * Creator      : Seaweed
 * Copyright    : Copyright (C) 1998 Joakim Larsson
 * Date         : 2/17/99
 * Purpose      : 
 * Related Files: 
 * Comments     :
 *        the bank will have all basic features with exchange and a
 *        strongroom. The hobbit clerk running this little office is a
 *        dreamer and sometimes he fells a sleep because hobbits don't
 *        care much about putting money in the bank. Still he thinks this
 *        is a mush nicer job than working in the fields. The bank is the
 *        only stone house however which is needed because of the many
 *        thieves in the neighborhood.
 * 
 * TODO         :
 *        Let NPC sleepy almost uninterested in your affairs, Let NPC snore
 *         if player inactive for some time, Add bank features,
 *
 * Modifications:
 *     N.B. This file is generated from templates hosted elsewhere and
 *     if someone corrects something in this file, please mail Seaweed
 * 
 */

#pragma strict_types

/* inherits */
inherit "/std/room";
inherit "/lib/bank";


/* includes */
#include <stdproperties.h> 
#include <macros.h> 

#include "../hobbit.h"

/* defines */



/* prototypes */
void create_room();
void reset_room();

/* globals */
object Clerk;

/*
 * Function name:       create_room
 * Description  :       set up the room
 */
void
create_room()
{
    set_short("The village bank.");
    set_long(
      "The silence in this building is an effect of the rather thick " +
      "stone walls protecting the earnings for the village " +
      "inhabitatants. It doesn't look like there is much business here " +
      "right now. A clerk resides behind the bars on the other side of " +
      "the counter.\n");
    add_item("bar", 
      "The iron bars in all windows seems to be firmly fastened to " +
      "the stone wall. \n");
    add_item("sign", 
      "The sign has official looking letters. \n");
    add_item("strongroom", 
      "The strong room protects your savings. \n");
    add_item("wall", 
      "The walls are white painted and made of stone. \n");
    
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_DARK_LONG,
      "It's dark, you can't see anything.\n");
    add_prop(ROOM_S_DARK_MSG,
      "The darkness makes it impossible to");
    add_prop(ROOM_S_EXIT_FROM_DESC,
      "from the bank.");
    add_prop(OBJ_S_WIZINFO, "Made by Seaweed 2/17/99.\n");
    
    add_exit("villageroad2.c", "southwest");
    
    
    config_default_trade();
    add_cmd_item( ({ "sign", "instructions" }), "read", standard_bank_sign);
    set_bank_fee(30); 
    config_trade_data();
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
    if (!objectp(Clerk))
    {
        Clerk = clone_object(EX_MON + "clerk");
        Clerk->equip_me();
        Clerk->move(this_object(), 1);
        tell_room(TO, QCTNAME(Clerk) + " appears slowly from behind the counter\n");
    }
    
}

void
init()
{
    ::init();
    
     // Add the bank commands
    bank_init();
    
    // Check if the Clerk is here and let him check the player
    if (Clerk && present(Clerk))
    {
        Clerk->set_visitor(this_player());
    }
}


