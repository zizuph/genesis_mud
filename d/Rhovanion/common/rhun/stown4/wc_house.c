inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

#define TALKED_TO_WIFE  "_player_talked_to_wife"

static object wife;

void reset_room()
{
  if (!objectp(wife))
    wife = clone_object(RHUN_DIR+"npc/wife");
  wife->move(TO, 1);
  tell_room(TO, QCTNAME(wife)+" arrives.\n");
}

void create_room()
{
  set_short("Woodcutter's home");
  set_long("This small hut looks to be the home of a"
	+" woodcutter.  Everything here is carved of wood, from"
	+" furniture to utensils, save the stone fireplace.  The"
	+" only exit lies back to the northwest.\n");

  add_exit(RHUN_DIR+"stown4/crossroads", "northwest", "@@check@@");

  add_prop(ROOM_I_INSIDE,1);

  add_item("fireplace","A simple stone fireplace. "+
           "It is probably used for cooking.\n");

  reset_room();
}

int check()
{
  if (TP->query_prop(TALKED_TO_WIFE))
  {
    set_alarm(0.0, 0.0, "make_shout");
  }
  return 0;
}

void make_shout()
{
  wife->command("shout Ask him about affair and house!");
}
