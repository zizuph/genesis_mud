/*
 * store room of the drow guild shop
 * By Finwe, May 2006
 */

#pragma strict_types

#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/drow/race/guild.h"
#include <stdproperties.h>
#include <const.h>

inherit "/d/Faerun/guilds/drow/rooms/base_room.c";


void
create_drow_room()
{
    set_short("Store room of the Drow shop");
    set_long(short() + ". Only wizards can come here.\n");
    add_exit("shop", "out");

}

/*
 * Function name:	init
 * Description	:
 */
public void
init()
{
    ::init();

}

/* Just a helper function to verify someones rank. */
private int
check_drow(mixed who, int rank)
{
    if (objectp(who))
	who = who->query_real_name();
    else
	who = lower_case(who);

    return GSERVER->query_member(who, rank);
}
