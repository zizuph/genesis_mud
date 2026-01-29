inherit "/d/Shire/room";
#include "/d/Shire/common/defs.h"

create_room()
{
   set_short("A dense path north of Bree");
   set_long("The path you are on is hard to distinguish from the dense "
	   +"vegetation around you. To the north, you see some tracks "
	   +"that have been rather roughly stomped out, and you begin "
	   +"to fear all the possibilities: wolves, orcs and more orcs.\n");

   add_item(({"bushes","bush","vegetation","tracks","track"}), 
	    "The bushes around here are quite dense, except to the "
	   +"north where you think you can explore more, and "
	   +"the bush you came in through, of course.\n");

   add_exit(BREE_DIR + "northgate","bushes",0,1);
   add_exit(BREE_DIR + "path2","north",0,1);

}
