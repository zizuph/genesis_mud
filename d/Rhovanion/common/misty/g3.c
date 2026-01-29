inherit "/d/Rhovanion/lib/room";
#include "/d/Rhovanion/defs.h"

void
reset_room()
{
  object ob;

  seteuid(getuid());

  if(!present("_shield_guild_guard_"))
  {
    ob = clone_object(NPC_DIR+"shield_guard");
    ob->set_guard_base_stat(75+random(20));
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
    set_long("You are on the small path that climbs the slope of Misty "+
             "Mountains. You can either go down west towards the valley "+
             "or crawl up northeast.\n");

    add_item("valley", "This is a fair green valley. Unlike the mountains " +
                       "ahead.\n");
    add_item("mountains", "Mountains look somehow dark. Maybe there is " +
                          "danger brooding there.\n");

              /* The other room,           direction, VBFC, fatigue */
    add_exit(MISTY_DIR+"g2", "west",    0,    3);
    add_exit("/d/Kalad/common/guilds/angmar/gates", "northeast", 0, 3);
    reset_room();
}

