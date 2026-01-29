inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"
#include "/sys/stdproperties.h"

create_room()
{
  set_short("Preliminary room for the Hall of Stars in Osgiliath");
  set_long("This room is only made to hold the other side of the door.\n"+
    "Will be improved later when the rest of Osgiliath is coded.\n"+
    "No mortal should be able to enter this room.\n");
  seteuid(getuid(this_object()));
  clone_object(OSG_DIR+"obj/lvl1_ghsdoor1")->move(this_object());
  add_exit(OSG_DIR+"lvl1corr2","south",0,0);
}

