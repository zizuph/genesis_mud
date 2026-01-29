inherit "/d/Gondor/common/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

object *guards;
int nr;
string WFILE;

create_room()
{
  set_long(BSN("This is the guard room where soldiers of the gate spend "+
    "their time when not on duty. "+
    "There are chairs and tables here, and some "+
    "racks to put weapons and armours on."));
  set_short("In a guard room at the gate");
  add_prop(ROOM_I_INSIDE,1);
  add_item(({"chairs","tables","chair","table"}),
    "There are some chairs and tables here, for the off-duty soldiers to use.\n");
  add_item("racks","There are no weapons nor armours in the racks now.\n"+
    "Perhaps the soldiers are carrying their weapons themselves?\n");
  nr = 6 + random(3);
  guards = allocate(nr);
  reset_room();
}

void
clone_guard(int n)
{
  int rs;
  n--;
  if(!guards[n])
  {
    guards[n] = clone_object(WFILE);
    guards[n]->arm_me();
    guards[n]->move(TO);
    tell_room(TO,QCNAME(guards[n]) + " arrives. \n");
  }
  if (n)
    set_alarm(1.0, 0.0, &clone_guard(n));
}

reset_room()
{
    set_alarm(0.0, 0.0, &clone_guard(nr));
}

object *query_guards() { return guards; }

void reset_room_and_improve_guards(int level)
{
    nr += level;
    guards += allocate(level);
    reset_room();
}

set_wfile(string str) { WFILE = str; }
