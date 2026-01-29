/*
 * /d/Shire/guild/AA/rooms/g3.c
 * Path to AA guild, branch to forge
 *
 * Re-opened forge path /11/6/2021 - Varian
 */

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
             "or crawl up northeast. A hidden trail heads southeast.\n");

    add_item("valley", "This is a fair green valley. Unlike the mountains " +
                       "ahead.\n");
    add_item("mountains", "Mountains look somehow dark. Maybe there is " +
                          "danger brooding there.\n");

    add_exit(AA_DIR+"rooms/g2", "west", 0, 3);
    add_exit(AA_DIR+"rooms/gates", "northeast", 0, 3);
    add_exit(AA_DIR+"rooms/forge", "southeast", 0, 3, 1);

    reset_room();
}

/*
int
block()
{
    if (this_player()->query_wiz_level()) return 0;
    write("It looks like a landslide has blocked the hidden " +
      "trail! Some soldiers appear to be working on clearing " +
      "it, perhaps it will be usable again soon.\n");
    return 1;
}
*/
