inherit "/d/Rhovanion/lib/caves.c";

#include "/d/Rhovanion/defs.h"
#include "def.h"
#include <stdproperties.h>
#include <macros.h>

object master;

void
reset_room()
{
  if(!master)
  {
    master = clone_object(NPC_DIR+"Questmasters/galian");
    master->arm_me();
    master->move(TO);
  }
  else if(!present(master, TO))
  {
    master->command("say What am I doing here???");
    master->command("say I should be in my office...");
    tell_room(ENV(master), QCTNAME(master)+" runs quickly away.\n");
    tell_room(TO, QCTNAME(master)+" enters room.\n");
    master->move(TO);
    master->command("say I am back to bussiness.");
    master->command("smile");
  }
}


create_cave()
{
  set_rock_type("soluble limestone");
  set_cave_name("Thranduil's Caverns");
  set_region("northern");
  set_cave("Mirkwood");
  set_cave_type(2);

  set_long("This is the council room, where Thranduil normally holds " +
           "his councils. It is also the office of Thranduil's advisor, " +
           "Galian. To the south you see the Throneroom.\n");

  set_noshow_obvious(1);
  add_exit(THIS_DIR + "throneroom","south",0,1);
  
  reset_room();
}
