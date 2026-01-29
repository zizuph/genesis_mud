/* Tantallon coded by Nick */

#include "/d/Krynn/common/defs.h"
#include "local.h"
inherit TANTALLON_INSIDE;

object priest, aurak;


create_tantallon_room()
{
  set_short("Inside a torture room in a damp tunnel.");
  set_long("You have entered a room that is completely bare except " +
	   "for a table, which appears to be used for strapping down " +
	   "prisoners for torture and interrogation.\n");
  
  add_item(({"walls", "wall"}), "The wall is rough and cold. This is no natural cave.\n");
  
  add_item("table", "A dead elf is strapped to the table.\n");
  add_item(({"elf", "dead elf"}), "The elf seems to have been tortured to death on the table.\n");

  add_exit(TDIR + "torture_room", "southeast", 0);
  reset_tantallon_room();
}

reset_tantallon_room()
{
  if(!objectp(priest))
  {
    priest = clone_object(MON+"ev_priest");
    priest->move(TO, 1);
  }

  if(!objectp(aurak))
  {
    aurak = clone_object(MON+"aurak");
    aurak->move(TO, 1);
  }
}
