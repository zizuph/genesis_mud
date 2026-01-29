/*
 *	/d/Gondor/guilds/bnumen/rooms/start_room.c
 *
 *	Coded by Olorin, November 1994
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/guilds/bnumen/rooms/bnumen_room.c";

#include "/d/Gondor/common/lib/gs_include.c"
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/guilds/bnumen/lib/bnumen_defs.h"

public void
create_cabin()
{
    set_short("the Dormitory in the House of the Black Numenoreans");
    set_long("This chamber has many hammocks attached to the ceiling " +
        "and walls to allow the warriors to sleep comfortably. "+ 
        long_cabin_level_1(1) + "Members of the Black " +
        "Numenoreans can <rest here> from their travels.\n");
    set_cabin_sound("The hammocks sway with the movement of the ship.\n");
    add_item(({"hammocks", "warriors"}), "There are hammocks hanging " +
        "from the ceiling and walls. You see some warriors who are " +
        "off duty sleeping in them. They sway rhythmically with the " +
        "movement of the ship and are quite comfortable.\n");
    floor(1);
    walls(1);
    ceiling(1);
    add_exit(BNUMEN_DIR + "ship/ncabin_hall1", "starboard", check_exit());

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

    
