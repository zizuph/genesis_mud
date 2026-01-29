/* 
 * Modified Louie March 2006 - PoT can "open/close" the passage
 * up into the upper areas.  I assume it will usually be open, and
 * closed to non-PoT during times of war.
 */
#pragma strict_types

#include "defs.h"

inherit TEMPLE + "std_stair.c";

private int is_blocked = 0;
string my_field();
string my_long();


void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("On a winding stairway");
    set_long("@@my_long@@");

    add_exit( TEMPLE + "corr6.c", "west" );
/*
    add_exit( LVLTWO   + "stair2.c", "up" );
*/
    add_item(({"field","shimmering field","black field"}),
        "@@my_field@@");

    add_exit( DUNGONE  + "stair0.c", "down" );
    add_exit (LVLTWO +"stair2.c", "up", "@@check_member");
}

string
my_field()
{
    if (!is_blocked)
    {
        return "You find field.\n";
    }

    string s = "The shimmering field of black blocks the passage up.  ";

    if (this_player()->query_guild_name_occ() == "Priests of Takhisis"
         || this_player()->query_wiz_level()) 
    {
        s += "You realize you can 'unblock' the passage if you wish.  ";
    }

    s += "\n";

    return s;
}

string
my_long()
{
    string l = 
        "You are standing on the ground floor landing of a spiraling " +
        "stone stairway in the Temple of Darkness. To the west is a long " +
        "shadowy corridor and the stairway leads both up and down. ";

    if (is_blocked)
    {
        l += "A shimmering field of black seems to block the passage up.  ";
    } else {
        if (this_player()->query_guild_name_occ() == "Priests of Takhisis"
         || this_player()->query_wiz_level()) 
        {
            l += "You realize you can 'block' the passage up if need be.  ";
        }
    }

    l += "\n";

    return l;
}

int
check_member()
{
    if (!is_blocked)
    {
        return 0;
    }

    if (this_player()->query_guild_name_occ() == "Priests of Takhisis"
         || this_player()->query_wiz_level()) {
         return 0;
    }

    write("You try to go up but are unable to pass through the blackness.\n");
    return 1;
}

int
do_block(string str)
{
    if (!(this_player()->query_guild_name_occ() == "Priests of Takhisis")
         && !(this_player()->query_wiz_level()))
    {
        notify_fail("What?\n");
        return 0;
    }


    if (!strlen(str) || (str != "passage" && str != "the passage"))
    {
        notify_fail("Block the passage?\n");
        return 0;
    }

    is_blocked = 1;
    write("You summon a shimmering field of black to block the "+
        "passage up.\n");

    return 1;
}

int
do_unblock(string str)
{
    if (!(this_player()->query_guild_name_occ() == "Priests of Takhisis")
         && !(this_player()->query_wiz_level()))
    {
        notify_fail("What?\n");
        return 0;
    }


    if (!strlen(str) || (str != "passage" && str != "the passage"))
    {
        notify_fail("Unblock the passage?\n");
        return 0;
    }

    is_blocked = 0;
    write("You remove the shimmering field of black, opening the "+
        "passage up.\n");

    return 1;
}

void
init()
{
    ::init();
    add_action(do_block, "block");
    add_action(do_unblock, "unblock");
}
