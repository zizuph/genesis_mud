/*
 *   shrine_low1.c
 * 
 *  Dark underground chamber.
 *
 * Baldacin@Genesis, Sep 2003
 * 
 * Modifications:
 *   2015-12-06: Changed so that the undead champion will only spawn once. During
 *               a reset_room, will bring him back to this room if he's not in
 *               combat [Petros]
 */

#pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include "ldefs.h"
inherit "/std/room";

private object undead_champion = 0;
private int    last_undead_champion_spawn = 0;

int
leave_north()
{
    mixed kill_time = this_player()->query_prop(LIVE_I_KILLED_UNDEAD_CHAMP);
    if (intp(kill_time)
        && kill_time > last_undead_champion_spawn)
    {
        // If the player has killed the undead champion and it hasn't spawned
        // again since, then we allow them into the room.
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        write("Normally you would be prevented from going north, but since you "
              + "are a wizard, we'll let that slide.\n");
        return 0;
    }
    
    if (objectp(undead_champion)
        && environment(undead_champion) == this_object())
    {
        // The undead champion is in the room, so we give a message that indicates
        // that he will not let the player pass.
        undead_champion->command("snarl "+this_player()->query_name());
        undead_champion->command("emote hisses: You sshall not passss.");
        say(QCTNAME(undead_champion) + " prevents " + QTNAME(this_player()) +
          " from going north.\n");
        this_player()->catch_msg(QCTNAME(undead_champion) + " prevents you " +
          "from going north.\n");
    }
    else
    {
        this_player()->catch_msg("A strong force prevents you from going north.\n");
    }
    return 1;
}

void
reset_room()
{
    if (!objectp(undead_champion))
    {
		setuid();
        seteuid(getuid());
    
		undead_champion = clone_object(SFLIVDIR+"undead_champ.c");
        last_undead_champion_spawn = time();
        undead_champion->move(TO, 1);
    }

    if (objectp(undead_champion)
        && environment(undead_champion) != this_object())
    {
        // If the undead champion is not in this room, we will bring him back to this room.
        // But we will do this only if he's not currently fighting anyone
        if (!objectp(undead_champion->query_attack()))
        {
            undead_champion->move(TO, 1);
        }
    }
    
	(SFDIR + "shrine_low2.c")->load_the_bloody_room(); 
}

public void
create_room()
{   
    set_short("A dark underground chamber");
    set_long("In a dark underground chamber. This is a small, "+
      "dark and moist room, hidden below the shrine, forgotten by time. "+
      "The rocky walls are low, you need to bend over slightly to be "+
      "able to move in here. A small opening leads further north into "+
      "a small backroom.\n");
    
    add_item(({"wall", "walls", "rocky walls"}),"The low, rocky walls are "+
      "made of some sort of greyish rock, some moldy lichens and mosses\n");
    add_item(({"lichens", "mosses"}),"The lichens and mosses are "+
      "leafy-stemmed and crustlike, they grow in clusters.\n");
    add_item(({"opening", "backroom"}),"A small opening in the northern wall "+
      "leads into some sort of backroom.\n");
    
    add_prop(ROOM_I_LIGHT, -1);
	
    add_exit(SFDIR + "shrine01x11.c", "up");
    add_exit(SFDIR + "shrine_low2.c", "north", &leave_north());

	reset_room();
}

