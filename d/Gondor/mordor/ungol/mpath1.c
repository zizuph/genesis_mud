inherit "/d/Gondor/common/room";
#include "/d/Gondor/defs.h"

create_room()
{
  set_short("The first room in what's to be Shelob's Lair");
  set_long("From here will lead the path and steps to Shelob's Lair,\n"+
    "Cirith Ungol, where the giant spider Shelob will be.\n");
  add_exit(ITH_DIR+"road/mrd3","south",0);
}
