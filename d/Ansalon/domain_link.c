/*
* This file used by the mudlib when the game boots and goes down.
*/
#include "/d/Ansalon/common/defs.h"

inherit "/std/domain_link";

#include <const.h>

/*
* Function name: preload_link
* Description:   Build a list of objects that should be loaded
*                before the first player enters the game.
*/
public void
preload_link()
{
    preload("/d/Ansalon/dargaard/wagon/wagonbed");
    preload("/d/Ansalon/balifor/flotsam/room/street09");
    preload("/d/Ansalon/balifor/flotsam/room/street08");
    preload("/d/Ansalon/balifor/flotsam/room/street05");
    preload("/d/Ansalon/balifor/flotsam/room/alley");
    preload("/d/Ansalon/kalaman/room/dock1");
    preload("/d/Ansalon/kalaman/room/dock2");
    preload("/d/Ansalon/kalaman/room/dock3");
    preload("/d/Ansalon/estwilde/plains/10f");
    preload("/d/Ansalon/dargaard/room/road1");
    preload("/d/Ansalon/kalaman/room/dock4");
    preload("/d/Ansalon/kalaman/room/dock5");
    preload("/d/Ansalon/kalaman/room/dock6");
    preload("/d/Ansalon/estwilde/iron_delving/cave2");
    preload("/d/Ansalon/silvanesti/new_kurinost/rooms/pier");
    preload("/d/Ansalon/taman_busuk/neraka/admin/wagons");
    preload("/d/Ansalon/taman_busuk/sanction/room/city/pier04");
    preload("/d/Ansalon/taman_busuk/sanction/room/city/pier07");
    preload("/d/Ansalon/taman_busuk/neraka/guild/admin/admin");
    preload("/d/Ansalon/guild/dragonarmy/obj/manager");
    preload("/d/Ansalon/guild/neidar/lib/neidar_member_manager");
    preload("/d/Ansalon/guild/neidar/lib/options_manager");
    preload("/d/Ansalon/guild/neidar/rooms/admin");
    preload("/d/Ansalon/guild/pirates/soul/pirate_soul");
    preload("/d/Ansalon/balifor/flotsam/room/landing");
    preload("/d/Ansalon/guild/society/room/vote_room");
    preload("/d/Ansalon/guild/pot/admin/admin");
    preload("/d/Ansalon/guild/neidar/objects/exile_master");
    preload("/d/Ansalon/estwilde/steed/steed_room");
}

/*
 * Function name: armageddon
 * Description:   This function is called when the game is about
 *                to reboot. All it should do is to save certain
 *                objectdata. Nothing more and nothing less.
 * Arguments    : int level - what armageddon is doing.
 */
public void
armageddon(int level)
{
    if (level == ARMAGEDDON_SHUTDOWN)
    {
         "/d/Ansalon/guild/dragonarmy/obj/manager"->save();
    }
}


