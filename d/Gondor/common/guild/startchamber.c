/*
 * /d/Gondor/common/guild/startchamber.c IS OBSOLETE!
 *
 * This is only here to move rangers who still have the old
 * start location set to the new room!
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild/lib/punish_defs.h"

public int    check_ranger();

public void
create_room()
{
    set_short("the bed-chambers of the Gondorian Rangers Guild");
    set_long(BSN("You are in the bed-chambers of the Gondorian Rangers Guild, "+
      "the place where Rangers may sleep when not playing the game. "+
      "Rangers may type 'start here' to select this as the place where they "+
      "will enter the game from now on if they wish. All around "+
      "you you can see sleeping Rangers lying on their bunks. A set of stairs "+
      "leads down in a corner, and west is a doorway to a storage room."));
    add_exit(RANGER_GON_DIR + "rangerinn", "down", 0, 2);
    add_exit(RANGER_GON_DIR + "armroom",   "west", check_ranger, 0);

    add_prop(ROOM_I_INSIDE,1);
    add_prop(ROOM_I_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK,1);
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_item(({"rangers","bunks"}), BSN(
      "You see several rugged Rangers asleep on bunks along each wall of the "+
      "room. They have probably had a hard day."));
    add_item("stairs", "The stairs lead down to the dining hall of the Rangers Guild.\n");
}

public int
start_here(string str)
{
   if (str != "here")
   {
      NF("Where?\n");
      return 0;
   }

   if (TP->query_wiz_level())
       return 0;
   if (IS_RANGER(TP))
   {
      TP->set_default_start_location(file_name(TO));
      write("From now on you will start here when entering the game.\n");
      return 1;
   }
   else
   {
      NF("But you are not one of the Gondorian Rangers!\n");
      return 0;
   }
}

public int
check_ranger()
{
   if (!IS_RANGER(TP))
   {
      write("You don't have access to that room, not being a ranger.\n");
      return 1;
   }
   else if (TP->query_skill(SS_PUNISHMENT) == NOACCESS)
   {
      write("The Council of Rangers have closed that door for you.\n");
      return 1;
   }
   return 0;
}

public void
move_to_new_startloc(object ob)
{
    // Change start loc.
    if (ob->query_default_start_location() == MASTER)
    {
        ob->set_default_start_location(RANGER_GON_DIR + "startchamber");
	log_file("startloc", ob->query_name() + ": changed at " + ctime(time()) + ".\n");
    }

    // Move always and unconditionally!
    log_file("startloc", ob->query_name() + ": moved at " + ctime(time()) + ".\n");
    ob->move(RANGER_GON_DIR + "startchamber", 1);
    tell_room(RANGER_GON_DIR + "startchamber", QCNAME(ob) + " enters the game.\n", ob);
}

void
enter_inv(object ob, object from)
{
   ::enter_inv(ob,from);

   if (!living(ob) || !interactive(ob))
      return;

   set_alarm(0.0, 0.0, &move_to_new_startloc(ob));
}

public void
init()
{
   ::init();
   /*
   add_action(start_here, "start");
   */
}

