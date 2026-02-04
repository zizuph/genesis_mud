/* Creative rights reserved to Mecien (Jeff Babcock) and team. */
inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TO      this_object()
#define TP      this_player()

static int warned = 0;
static object doorkeeper;

public void
reset_room()
{
   if (!doorkeeper) {
       doorkeeper = clone_object(GUILD_DIR + "doorkeeper");
       doorkeeper->move_living("M", TO);
   }

   if (sizeof(query_desc())) remove_my_desc();
}

public void
create_room()
{
   object sdoor2;

   set_short("Chamber");
   set_long(
       "This hall is the entry chamber of the shrine. Here tall pillars " +
       "rise to the ceiling, carved into spirals. Tall candles line the " +
       "walls in silver sconces, the air traced with incense. " +
       "A dark set of stairs leads down.\n");
   
   add_prop(ROOM_I_INSIDE, 1);
   add_prop(ROOM_I_HIDE, 85);

   sdoor2 = clone_object(GUILD_DIR + "sdoor2");
   sdoor2->move(TO);

   add_exit(GUILD_DIR + "guild", "north", "@@clean");
   add_exit(GUILD_DIR + "office/acham", "west", 0);
   add_exit(GUILD_DIR + "antechamber", "south", 0);
   add_exit(GUILD_DIR + "d_hall1", "down", "@@npc_check");

   add_cmd_item("incense", "smell",
        "It smells wondrous, like sandalwood and balsam.\n");
   add_item(({"silver sconces", "sconces", "sconce"}),
        "Beautiful silver sconces. They are fashioned in the shape " +
        "of griffins, serpents and unicorns.\n");
   add_item(({"candle", "candles"}),
        "They are silvery-white bees-wax tapers. They cast a faint " +
        "blue glow.\n");
   add_item(({"spirals","pillars"}),
      "They are of the purest white marble.\n"
   );
   reset_room();
}

public int
npc_check()
{
    if (interactive(TP)) return 0;
    if (!MEMBER(TP)) return 0;
    if (TP->query_attack()) return 0;
    return 1;
}

public int
clean()
{
   if (doorkeeper && environment(doorkeeper) == TO &&
         TP != doorkeeper) {
       if (TP->query_alignment() < 100) {
           tell_room(TO, QCTNAME(doorkeeper) + " places his sword " +
                     "in front of " + QTNAME(TP) + ".\n", TP);
           doorkeeper->command("say I have no intention of " +
                               "letting you enter this sacred place.");
           TP->catch_msg(QCTNAME(doorkeeper) + " places " +
                         doorkeeper->query_possessive() +
                         " sword in front of you.\n");
           return 1;
       }
   }

   if (TP->query_prop("purified")) {
      write("You sense a sanctity as you enter.\n");
      if (interactive(TP))
          TP->remove_prop("purified");
      return 0;
   }
   write("A sense of sacredness resides within, you must be purified.\n");
   return 1;
}

public int
warn_mystic(object who)
{
    if (MEMBER(who) && present(MYSTIC_RING, who) &&
        environment(who) != TO) {
        who->catch_msg("Cirthes calls with the mystic voice: " +
                       "Evil has entered the Shrine!\n");
    }
}

public void
clear_warned()
{
    warned = 0;
}

public void
warn(object who)
{
    if (!doorkeeper || environment(doorkeeper) != TO) return;
    if (!who) return;
    if (environment(who) == TO) {
        doorkeeper->command("say You are not wanted here, " +
                            who->query_nonmet_name() + ".");
    }
    map(users(), warn_mystic);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!ob || !living(ob) || !doorkeeper) return;
    if (environment(doorkeeper) != TO) return;

    if (ob->query_alignment() < -10 && warned == 0 &&
        ob->query_prop("_shrine_attacker") == 0) {
        warned = 1;
        ob->add_prop("_shrine_attacker", 1);
        set_alarm(  1.0, -1.0, &warn(ob));
        set_alarm(300.0, -1.0, clear_warned);
    }
}
