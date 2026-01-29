/*
 * Genesis ShipLines - Sparkle office.
 * TAPAKAH, 10/2008
 * To be transferred later into /d/Sparkle
 */

#include <macros.h>
#include "/d/Genesis/ship_new/ships.h"
#include "gs_office.h";

inherit "/std/room";

int check_paid ();

void
create_room () {

  ::create_room();

  setuid();
  seteuid(getuid());
  set_short("Inside the Sparkle Office of Genesis ShipLines");
  set_long("You are inside the Sparkle Office of Genesis ShipLines Company"+
           "Currently it is a relatively small hall, albeit with a very "+
           "high ceiling. You notice some doors and windows are still "+
           "locked. A door to the west however is open, and an old goblin "+
           "is sitting next to it behind a desk.\n");

  add_exit("../pier7","north");
  add_exit("toilet_entrance", "west", &check_paid());

  add_npc(GS_OFFICE_DIR + "ticket_engineer", 1, &->equip_me());
  add_npc(GS_OFFICE_DIR + "toilet_keeper", 1, &->equip_me());

  add_item(({"windows", "window"}),
           "Through the window in the south wall you can see the Pensea of " +
           "Sparkle. The reset of the windows are closed and locked.\n");
  add_item(({"doors", "door"}),
           "Most of the doors seem to be closed and locked. "+
           "The door in the western direction is open. An old goblin sits "+
           "behind a desk next to it.\n");
  add_item(({"west door", "western door"}),
           "The door in the western direction has a writing on it: 'This "+
           "way comes relief'.\n");
  add_item(({"desk"}),
           "A new simple wooden desk. There is a box on the desk.\n"+
           "A heap of leaflets is piled next to it.\n");
  add_item(({"box", }),
           "A simple cardboard box that is currently empty. It "+
           "is closely watched by the goblin behind the desk.\n");
  add_object(GS_OFFICE_DIR + "timetable");
}

int
get_leaflet (string str)
{
  string verb;
  object leaflet;

  verb = query_verb();
  if(! str)
    NF0(capitalize(verb) + " what?");
  leaflet = clone_object(GS_OFFICE_DIR + "leaflet");
  leaflet->move(TP);
  write("You pick a leaflet from the heap on the desk.\n");
  tell_room(QCTNAME(TP) + " picks a leaflet from the heap on the desk.\n");
  return 1;
}

void
init()
{
  ::init();
  add_action(get_leaflet, "get");
  add_action(get_leaflet, "take");
  add_action(get_leaflet, "pick");
}

int
check_paid () {

  object toilet_keeper;
  toilet_keeper = present("toilet_keeper",TO);
  toilet_keeper->command("say sorry, da toilit iz nut opin yet!");
  return 1;
  return TP->query_prop(PAID_FOR_TOILET_USAGE);
}
