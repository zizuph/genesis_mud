#pragma strict_types
#pragma save_binary

#include "../guild.h"

inherit TRAVELLERS_STD_DIR + "room_base";

#include "/d/Earthsea/sys/macros.h"
#include <macros.h>

static object guard;

int is_member();
void reset_room();

void
create_traveller_room() 
{
    set_short("Stairwell");
    set_long("This is the main stairwell of the chateau. It leads" +
	" upwards to the second floor balcony and downward to" +
	" the cellar. Archways lead from this room to other" +
	" finely decorated rooms.\n");

    add_item(({"stair","stairs"}),"They are magnificently carved marble.\n");
    add_item(({"balcony"}),"It runs the length of the second floor.\n");

    add_exit("cellar","down");
    add_exit("balcony","up", is_member);
    add_exit("start","north");
    add_exit("boardroom","west");
    add_exit("hall","east");

    reset_room();
}

void
reset_room()
{
    if (!guard)
    {
        setuid();
        seteuid(getuid());

        guard = clone_object(TRAVELLERS_NPC_DIR + "guard");

        tell_room(this_object(), "A guard arrives.\n");

        guard->move(this_object(), 1);
    }
}

int
is_member()
{
    reset_room();

    if (!IS_MEMBER(this_player()) && !IS_WIZ(this_player()) &&
        !sizeof(filter(deep_inventory(this_player()),
        &wildmatch(TRAVELLERS_BADGE + "*") @ file_name)))
    {
        write("The guard stops you.\n");
        say("The guard stops " + QTNAME(this_player()) +
            " from going up.\n");

        return 1;
    }

    return 0;
}
