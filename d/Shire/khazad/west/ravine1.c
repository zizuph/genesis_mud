
inherit "/d/Shire/common/lib/rom";
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"

void
create_moria_room()
{
  set_short("In a ravine");
  set_long("The ravine slopes down to the northeast. A small trickle "+
     "of water makes its way along this slick, stone channel. "+
     "Stalagmites surround you on the eastern and western sides. "+
     "The ravine runs to the northeast, growing deeper. Leaving the "+
     "ravine will take you southwest towards the cavern road.\n");

   add_item(({ "stalactites", "stalactite" }),
     "From this distance its hard to tell their exact size. Most "+
     "seem fairly large and have water streaking down their sides "+
     "from time to time.\n");
  add_item(({ "stalagmites", "stalagmite" }),
     "Some are small stumps while others tower above you. Traces "+
     "of water can be seen on most.\n");
  add_item("stumps",
     "Small stalagmites, nothing spectacular about them.\n");
  add_item("ravine",
     "While fairly shallow it offers a clear path through the "+
     "stalagmites to the northeast. You also see an opening to the "+
     "southwest, outside the ravine.\n");
  add_exit("/d/Shire/khazad/west/ravine2","northeast",0,1);
}

public void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);
  if(!living(ob))
    return;
  if (file_name(from) == "/d/Shire/khazad/west/cp6")
    write("You carefully lower yourself into the slick ravine.\n");
}

int
do_exit(string str)
{
  if (str != "ravine")
  {
    notify_fail("Climb what?\n");
    return 0;
  }

  else
  {
    say(QCTNAME(TP) + " climbs out of the slick ravine.\n");
    TP->move_living("M","/d/Shire/khazad/west/cp6",0);
    say(QCTNAME(TP) + " steps out from behind a stalagmite.\n");
    return 1;
  }
}

void
init()
{
  ::init();
  add_action(do_exit, "climb");
}
