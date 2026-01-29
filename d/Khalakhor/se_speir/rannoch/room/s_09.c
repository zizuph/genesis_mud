/* File         : /d/Khalakhor/se_speir/rannoch/room/s_09.c
 * Creator      : Darragh@Genesis
 * Date         : 01-04-02         
 * Purpose      : 
 * Related Files: 
 * Comments     :
 * Modifications: 
 */

#pragma strict_types

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include <ss_types.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"
#include "/d/Khalakhor/sys/terrains.h"
#include "room.h"

inherit "/d/Khalakhor/std/room";
inherit HERBSEARCH;

//int climb_down(string str);

public void
create_khalakhor_room()
{
    set_short("A room");
    set_long("Bläh.\n");

    add_exit(ROOM + "r_10.c","northeast",0,1,0);

}

int
climb_down(string str)
{

    if (str != "down")
    {
        notify_fail("Climb where? Down?\n");
        return 0;
    }

    write("You climb down.\n");

    say(QCTNAME(this_player())+" climbs down.\n");

    this_player()->move_living("M", ROOM + "v_08",1,0);

    say(QCTNAME(this_player())+" suddenly appears.\n");

    return 1;

}

void
init()
{
    ::init();

    add_action(climb_down, "climb");

}

