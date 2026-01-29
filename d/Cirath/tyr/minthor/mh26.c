

inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_room()
 {
  set_short("Waiting Room");
  set_long("You have entered what appears to be the northwestern "
	+"room made for visitors to wait for an opportunity to "
        +"speak with Lord Minthor. Plush couches and comfortable  "
        +"looking chairs are set up around the room.\n");
  add_item(({"couch","couches"}),"They are made of some of the "
        +"finest fabrics in the Tyr region. They look very comfortable "
        +"to sit on.\n");
  add_item(({"chair","chairs"}),"They are made of fine hardwoods, lined "
        +"with soft plush materials to make them comfortable.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  add_cmd_item("in chair","sit","@@chair");
  add_cmd_item("on couch","sit","@@couch");
  add_cmd_item("up","stand","@@stand");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE
  add_exit(TZ_MINTHOR + "mh25","west",0);
  add_exit(TZ_MINTHOR + "mh11","southeast",0);
}

stand()
{
        write("You stand up from your seat.\n");
             say(QCTNAME(TP) + " stands up from " + HIS_HER(TP) +
        " seat.\n");
             return 1;
}

chair()
{
        write("You settle down on one of the comfortable chairs.\n");
        say(QCTNAME(TP) + " sits down on one of the chairs.\n");
        return 1;
}

couch()
{
        write("You sit down and relax on the soft couch.\n");
        say(QCTNAME(TP) + " settles down on the plush couch.\n");
        return 1;
}

