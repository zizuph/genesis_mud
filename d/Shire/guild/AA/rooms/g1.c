#pragma save_binary
#pragma strict_types

#include <macros.h>
#include "../guild.h"

inherit SHIRE_ROOM;

#ifdef RHOVANION_CLOSED
#define SHIRE_MISTY_DIR  "/d/Shire/misty/"
#else 
#define SHIRE_MISTY_DIR  MISTY_DIR
#endif

void
reset_room()
{
    object ob;

    seteuid(getuid());

    if(!present("_shield_guild_guard_"))
    {
	ob = clone_object(AA_DIR+"npc/shield_guard");
	ob->set_guard_base_stat(55+random(20));
	ob->arm_me();
	ob->move(TO, 1);
	tell_room(TO, (ob->query_guard_race() == "orc" ? "An " : "A ")+
	  ob->query_guard_race()+" arrives attracted by the noise.\n");
    }
}

void
create_room()
{
    set_short("small path");
    set_long("You have found the beginning of a small path that climbs the "+
      "south slope of the valley full of bushes and turns towards "+
      "the Misty Mountains.\n");
    add_item("valley", "This is a fair green valley. Unlike the mountains " +
      "ahead.\n");
    add_item("mountains", "The mountains look somehow dark. Maybe there is " +
      "hidden danger there.\n");
    add_item(({"bushes", "bush"}), "You see ordinary green bushes all "+
      "around. They all seems to grow well except maybe one "+
      "to the north that looks a bit damaged. Perhaps just "+
      "some animals?\n");

    /* The other room,           direction, VBFC, fatigue */
    add_exit(AA_DIR+"rooms/g2", "southeast",    0,    3);
    reset_room();
}

void
init()
{
    ::init();
    add_action("enter_bushes", "enter");
}

int
enter_bushes(string str)
{
    NF("Enter what?\n");
    if((str != "bushes") && (str != "bush")) return 0;
    tell_room(SHIRE_MISTY_DIR+"p1", QCTNAME(TP)+" jumps out of the bushes.\n");
    TP->catch_msg("You wade through the bushes to the other side.\n");
    TP->move_living("M", SHIRE_MISTY_DIR+"p1", 1);
    tell_room(TO, QCTNAME(TP)+" wades "+HIS(TP)+" way through the bushes.\n");
    return 1;
}
