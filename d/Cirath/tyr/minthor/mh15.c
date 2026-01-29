inherit "/std/room";
#include "/d/Cirath/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "defs.h"
create_room()
 {
  set_short("Ballroom");
  set_long("You have entered a grand ballroom that appears to have "
	+"frequent visitors. To the east is a large window that opens "
	+"to the gardens outside. A plush red carpet cushions your "
	+"feet, and muffles all noise from walking. Around the window "
	+"is a thick curtain made of some exotic material, and under "
	+"the curtain is a row of small chairs.\n");
  add_item("ballroom","You are standing inside one.\n");
  add_item("window","It is standing open to your east, offering a nice "
	+"view of the gardens below.\n");
  add_item(({"garden","gardens"}),"They are below the window, and "
	+"outside. They are much too difficult to examine from here.\n");
  add_item(({"chair","chairs"}),"There is a row of them under the "
	+"window. They look small and uncomfortable, yet expensive.\n");
  add_item("curtain","A beautiful red and black curtain that helps "
	+"keep the sun out of the room at midday.\n"); 
  add_item("carpet","It is a thick red carpet, obviously costly.\n");
  add_item(({"house","mansion"}),"You are inside of it.\n");
  ADD_SUN_ITEM
  ADD_ZIG_ITEM
  INSIDE
  add_exit(TZ_MINTHOR + "mh16","north", 0);
  add_exit(TZ_MINTHOR + "mh14","west", 0);
}

