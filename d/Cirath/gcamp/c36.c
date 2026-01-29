inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/d/Cirath/common/defs.h"
#include "defs.h"
#include "/d/Cirath/common/mobber.h"

void
reset_room()
{
bring_room_mob("gith",GITH_NPC+ "gith2.c",1);
}

void
create_room()
 {
  set_short("Top of Lookout Tower");
  set_long("You are standing atop a tall parapet looking out "
  	+"over a long narrow valley.  Down below you, tents and "
  	+"other items belonging to the gith that live here are "
  	+"visible.  Sitting low on the horizon, Athas's twin "
  	+"suns shine their trademark harsh yellow light down "
  	+"upon you and everyone else.\n");
  add_item(({"sun","suns","twin suns"}),"These two stars are "
  	+"responsible for the irrepressible heat of Athas as well "
  	+"as the blinding yellow light that both gives and takes "
  	+"life here.\n");
  add_item("parapet","It is tall and made of time hardened stone.  "
  	+"Narrow handholds form a precarious ladder back down to "
  	+"the wall below.\n");
  add_item("wall","It circles the gith compound providing protection "
  	+"to the inhabitants here.\n");
    add_exit(CAMP + "c35","down");
    set_alarm(1.0,0.0,"reset_room");
}

