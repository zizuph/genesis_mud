inherit "/d/Gondor/common/room";
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <filter_funs.h>
#include "/d/Gondor/defs.h"

object *guards;
int nr;

create_room()
{
  set_long(BSN("This small guard room has several arrow slits in the north "+
    "wall, and a barrel filled with arrows near each post. Through the "+
    "slits, guardsmen probably have full control with who is passing "+
    "through the gate beyond."));
  set_short("In a guard room at the Great Gate of Minas Tirith");
  add_prop(ROOM_I_INSIDE,1);
  add_item(({"slit","slits","arrow slit","arrow slits"}),"@@look_through_slit");
  clone_object(MINAS_DIR+"obj/sinwdoor2")->move(TO);
  nr = 3 + random(3);
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
    guards[n] = clone_object(MINAS_DIR + "npc/gondor_archer");
    guards[n]->move(TO);
    tell_room(TO,QCNAME(guards[n]) + " arrives. \n");
  }
  if(n) call_out("clone_guard", 1,n);
}

reset_room()
{
  call_out("clone_guard", 0, nr);
}

object *query_guards() { return guards; }

void reset_room_and_improve_guards(int level)
{
    nr += level;
    guards += allocate(level);
    reset_room();
}

look_through_slit()
{
  string desc;
  object ingate;
  object *lnames;
  int i, size;
  desc = "Looking through one of the arrow slits, you have a clear view "+
    "of the archway of the Great Gate of Minas Tirith; the cobbled street "+
    "climbing slightly towards the west, the iron doors on the steel posts "+
    "to the east. There are also similar slits in the opposite wall. ";
  seteuid(getuid(this_object()));
  "/d/Gondor/minas/ingate1"->teletull();
  ingate = find_object("/d/Gondor/minas/ingate1");
  lnames = FILTER_LIVE(all_inventory(ingate));
  size = sizeof(lnames);
  if (size)
    desc += "You see "+COMPOSITE_LIVE(lnames)+" inside the Gate. ";
  else desc += "You see noone inside the Gate. ";
  return BSN(desc);
}

enter_ingate(object ob, object from)
{
  if (!present("archer",TO)) return;
  present("archer",TO)->command("say Someone just entered the gate!\n");
}

  
