inherit "/d/Gondor/common/room";
#include <macros.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

object *guards;
int nr;

void reset_room();

void
create_room()
{
  set_long(BSN("This is the guard room where soldiers of the City spend "+
    "their time when not on duty. A doorway leads north to a bedroom, "+
    "and an exit leads west out into the Main Street. A spiral stairway "+
    "of grey stone leads up. There are chairs and tables here, and some "+
    "racks to put weapons and armours on."));
  set_short("In a guard room at the Great Gate of Minas Tirith");
  add_exit(MINAS_DIR + "e3crc1","west",0,1);
  add_exit(MINAS_DIR + "wall/ninwall2","north",0,0);
  add_exit(MINAS_DIR + "wall/topnwall1","up",0,1);
  add_prop(ROOM_I_INSIDE,1);
  add_item("stairway","The stone spiraling stairway leads up to the battlements.\n");
  add_item(({"chairs","tables","chair","table"}),
    "There are some chairs and tables here, for the off-duty soldiers to use.\n");
  add_item("racks","There are no weapons nor armours in the racks now.\n"+
    "Perhaps the soldiers are carrying their weapons themselves?\n");
  clone_object(MINAS_DIR+"obj/ninwdoor1")->move(TO);
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
    guards[n] = clone_object(MINAS_DIR + "npc/wall_guard");
    guards[n]->arm_me();
    guards[n]->move(TO);
    tell_room(TO,QCNAME(guards[n]) + " arrives. \n");
  }
  if (n)
    set_alarm(1.0, 0.0, &clone_guard(n));
}

reset_room()
{
    set_alarm(1.0, 0.0, &clone_guard(nr));
}

object *query_guards() { return guards; }

void reset_room_and_improve_guards(int level)
{
    nr += level;
    guards += allocate(level);
    reset_room();
}

