/**********************************************************************
 * - pie01205.c                                                     - *
 * - The Riddler is here. She gives entrance quest to Galaith Isle. - *
 * - Created by Damaris@Genesis 07/Y2K                              - *
 * - ReCoded by Damaris@Genesis 03/2005                             - *
 **********************************************************************/

#pragma strict_types
#pragma save_binary
#include "../defs.h"

inherit PIER_ROOM;

#include <stdproperties.h>
#include "/d/Khalakhor/sys/paths.h"
#include "../npc/riddler.h"

object riddler;

public int *
query_local_coords()
{
    return ({12, 5});
}

public void
reset_pier()
{
    if (!riddler)
    {
	riddler = clone_object(NPC + "riddler");
	riddler->move(this_object(), 1);        
    }

}

private int
check_exit()
{
    if (this_player()->test_bit("Khalakhor", SAMORGAN_QUEST_GROUP, SAMORGAN_ENTRANCE_EILGALAITH) ||
      this_player()->query_prop("__answered_galaith_riddles"))
	return 0;

    write("There is no obvious exit "+ query_verb() +".\n");
    return 1;
}

private int
show_exit()
{
    return !(this_player()->query_guild_member("Eil-Galaith") ||
      this_player()->test_bit("Khalakhor", SAMORGAN_QUEST_GROUP,  SAMORGAN_ENTRANCE_EILGALAITH) ||
      this_player()->query_prop("__answered_galaith_riddles"));
}

public void
create_pier()
{
    add_exit("pie1204", "west");
    add_exit("pie1305", "south");
    add_exit("pie1105", "north");
    add_exit("pie1206", "east", check_exit, 0, show_exit);
    reset_pier();
}
