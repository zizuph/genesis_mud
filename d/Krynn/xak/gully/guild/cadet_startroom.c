
/*  

    The start room for Cadets of Gelan

    Coded by Maniac@Genesis, March 1997

    Copyright (C) Miguel Leith 1997

*/

#pragma save_binary

inherit "/std/room";
inherit "/lib/guild_support";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <money.h>
#include "cadet.h"

int
gc_query_private_room()
{
    return 1;
}

void
create_room()
{
    set_short("Cadet bunks");
    set_long("The rough bare floorboards and hard granite walls " +
             "make this a rather harsh environment, so it's perfect " + 
             "as a cadets' dormitory. A number of hard wooden bunks are " +
             "lined up against the west wall with rocks for pillows. " +
             "Naturally " + GC_GM_NAME + " won't permit any naughty " +
             "tapestries to go up on the walls, and he forces anyone " +
             "caught writing graffiti on the bed frames to file it " + 
             "off with their teeth. You can " +
             "<start here> if you have the guts. You may also " +
             "<meditate> here.\n");  

    add_item(({ "wall", "walls", "granite wall", "granite walls" }),
        "Hard and smooth, appropriate for a dungeon, and not out of " +
        "place here.\n");

    add_item(({"bed", "beds", "bunk", "bunks" }), 
            "The bunks have strong solid oak frames. Lying on one " +  
            "is probably about as comfortable as a bed of nails, though " +
            "somewhat less painful of course. The pillows are indeed " +
            "rocks, although they are at least smooth.\n"); 

    add_item(({"pillow", "pillows"}), 
        "The pillows are smooth rocks. How very uncomfortable!\n"); 

    add_prop(OBJ_S_WIZINFO, "This is a default start location.\n");
    add_prop(ROOM_I_INSIDE, 1);

    add_exit(GC_TRAINROOM, "north"); 
    add_exit(GC_BOARDROOM, "east"); 
    add_exit(GC_POSTROOM, "south"); 
    add_exit(GC_COMMONROOM, "common"); 
}


int
start(string str)
{
    object tp = this_player(); 

    if (str != "here")
	return 0;
 
    if (!IS_GELAN_CADET(tp))  { 
        notify_fail("You are not a Cadet of Gelan!\n");  
        return 0;
    } 

    if (tp->query_default_start_location() == GC_STARTROOM) { 
        notify_fail("You already start here.\n"); 
        return 0;
    } 

    tp->set_default_start_location(GC_STARTROOM);
    write("Ok, you start here now.\n");
    return 1;
}


void
leave_inv(object ob, object to)
{
    gs_leave_inv(ob, to);
    ::leave_inv(ob, to);
}

void
init()
{
    ::init();
    init_guild_support(); 
    add_action(start, "start");
}

