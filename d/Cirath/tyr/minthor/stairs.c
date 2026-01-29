inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/tyr/tyr.h"
#include "defs.h"

 
create_room()
 {
  set_short("Hidden Staircase");
  set_long("You are standing on a wooden staircase hidden in an alcove "
	+"at the end of the northeastern hallway.  It is very dusty here "
	+"and you are not sure if anyone has been here for a long time.  "
	+"The stairs lead up into darkness.  All you can see here is the "
	+"dust on the floor.\n");
  add_item(({"stairs","staricase"}),"The staircase seems to have gotten "
	+"little use lately as there is dust all over the steps.\n");
  add_item("dust","There is a lot of dust on the floor here.  It all "
	+"looks relatively undisturbed at first.  Upon careful "
	+"examination, though, you notice faint footprints in the "
	+"dust.\n");
  add_item(({"wall","walls"}),"The walls stretch out around you.\n");
  add_item(({"footprint","footprints"}),"They are footprints the size "
	+"of a young man or possibly a woman.  You can't be absolutely "
	+"sure because they are so faint.\n");
  INSIDE
  add_exit(TZ_MINTHOR + "mh35","south","@@south");
  add_exit(TZ_MINTHOR + "mh36","up");
}

south()
{
    write("You quietly step through the the frame back into the hall.\n");
    say(QCTNAME(TP)+" steps through the picture frame back into the "
	+"hall.\n");
    return 0;
}


