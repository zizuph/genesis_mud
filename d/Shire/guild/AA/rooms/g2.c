#pragma save_binary
#pragma strict_types

#include "../guild.h"

inherit SHIRE_ROOM;

void
reset_room()
{
  object ob;

  seteuid(getuid());

  if(!present("_shield_guild_guard_"))
  {
    ob = clone_object(AA_DIR+"npc/shield_guard");
    ob->set_guard_base_stat(70+random(20));
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
    set_long("You are on the path, south above the valley. The path climbs up "+
             "east to the Misty Mountains.\n");

    add_item("valley", "This is a fair green valley. Unlike the mountains " +
                       "ahead.\n");
    add_item("mountains", "The mountains look somehow dark. Maybe there is " +
                          "danger brooding there.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(AA_DIR+"rooms/g1", "northwest",    0,    3);
    add_exit(AA_DIR+"rooms/g3", "east",    0,    3);
    reset_room();
}

