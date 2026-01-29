#include "/d/Shire/greenfields/camp/tent.h"
inherit "/d/Shire/room.c";
#include "/d/Shire/common/defs.h"

void
create_room()
{
   set_short("Inside an orc tent");
   set_long("This tent is empty, unlike most of the others, and as you walk "+
   "across the floor you notice it is covered with a light layer of sand "+
   "and other things too small to examine carefully."+
   " The camp outside seems cold and dim compared to this "+
   "warm, dry, bright place.\n");
   

   add_item(({"sand","floor"}), "The sand covers the floor completely.\n");
   add_item(({"camp","outside"}), "The camp is outside, but you cannot "+
   "see it from in here.\n");
     add_prop(ROOM_I_INSIDE,1);
     add_prop(ROOM_I_LIGHT,3);
   
     add_exit(GREEN_DIR + "camp/camp08","out",0,1);
}
