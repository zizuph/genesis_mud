/*
 *	/d/Gondor/common/dunedain/rooms/start_room.c
 *
 *	Coded by Olorin, November 1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/dunedain/rooms/dun_room.c";

#include "/d/Gondor/common/lib/gs_include.c"
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"

public void
create_gondor()
{
    set_short("the Dormitory in the House of the Dunedain");
    set_long(BSN("This quiet dark room is the dormitory in the House of "
      + "Dunedain in Gondor. Members of the Houses of the "
      + "Dunedain can <rest here> from their travels."));

    add_exit(GUILD_DIR + "rooms/hallw_s3", "east", 0, 0);

    floor(1);
    walls(1);
    ceiling(1);

    add_prop(ROOM_I_INSIDE, 1);
}

void
init()
{
    ::init();

    add_action("do_start", "start");
    add_action("do_start", "rest");
}

int
do_start(string here)
{
    object  tp = TP;

    if (!IS_MEMBER(tp))
        return 0;

    if (tp->query_wiz_level())
    {
        NF("You are a wizard, you do not need this!\n");
        return 0;
    }

    if (!strlen(here) || here != "here")
    {
        NF("Start where?\n");
        return 0;
    }

    tp->set_default_start_location(file_name(TO));
    write("From now on, you will begin your travels here.\n");
    return 1;
}

    
