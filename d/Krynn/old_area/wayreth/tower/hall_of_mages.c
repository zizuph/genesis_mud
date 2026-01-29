/*
   Wayreth.

   hall_of_mages.c
   ---------------

   Coded ........: 95/06/14
   By ...........: Jeremiah

   Latest update : 95/06/14
   By ...........: Jeremiah

*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/wayreth/guild/local.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>

inherit TOWERROOM;

void
create_tower_room()
{
   set_short("The hall of mages");
   set_long("You are standing in a vast chamber carved of dark obsidian. " +
            "The room is so wide that its perimeter is lost in the " +
            "shadows, so high that its ceiling is obscured in darkness. " +
            "No pillars supports the room, no light illuminates it. Yet " +
            "light there is, although you're not able to name or point out " +
            "its source. It is a pale light, white, not yellow, but cold and " +
            "cheerless, giving no warmth. A golden plaque on the wall.\n");
    add_cmd_parse("[the] [golden] 'plaque'", "read",
	"Commands:\n" +
	"---------\n" +
	"test order - To test which order you will join.\n" +
	"join order - Will join the appropiate order.\n");
}
