inherit "/std/room.c";
#include <stdproperties.h>
#include <macros.h>
#include "../defs.h"

void
create_room()
{
    set_short("Fred's Bounty Service");
    set_long(break_string(
"Welcome to Fred's Bounty Service!  Here you can place a bounty on anyone " +
"you like.  Place a bounty on enemies that are too tough for you to kill.  " +
"Place a bounty on your friends for a joke.  Fred doesn't care, he want's " +
"the interest on the money you pay him.  There is a sign on the wall that " +
"you can read for more details on the services he offers.\n", 78));

    add_exit(G_ROOMS + "ghall1", "east", 0);

    add_item(({"lanterns", "lantern"}), break_string(
"They are rusty, smoky, and in great need of more oil.  Unfortuantely for " +
"you, they are firmly attached to the wall.\n", 78));

    add_item(({"sign", "instructions"}) , break_string(
"It is large, square, and very clean.  The lettering was done in black ink " +
"in a flowing script.  This is clearly the work of a professional.\n", 78));

    add_prop(ROOM_I_INSIDE, 1);
}

void
init()
{
  ::init();

    add_action("try_read", "read");
}

int
try_read(string str)
{
    notify_fail("Read what?\n");
    if(!str) return 0;
    if(str != "sign") return 0;
    write("" +    
"Here you can place a bounty on whomever you like.  There is no set\n" +
"'cost.'  This bounty is determined by you, and whatever you pay.  E.g.\n" +
"a 100cc bounty on 'Ralph the Ranger would cost 100cc.  Here you can\n" +
"use the following commands:\n" +
"\n" +
"     list                         Displays the current bounty list.\n" +
"     place <amount> on <player>   Places a bounty of <amount> on\n" +
"                                       player <player>.\n" +
"     buy list                     This will get you a hard copy of the\n" +
"                                       current bounty list for 50sc.\n" +
"     collect <player>             Will let you receive the bounty placed\n" + 
"                                       on player <player>.\n" +
"\n" +
"To collect the bounty placed on a player, you must have the corpse, or\n" +
"part of the corpse of that player in your inventory.\n");
    say (QCTNAME(this_player()) + " reads the sign on the wall.\n");
    return 1;
}


