inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* by korat */

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,0);
   set_short("Within the dwarven city of Underhome");
   set_long("The path you are standing on seems to have "+
      "suffered some damage through time, but still shows "+
      "clear signs of excellent handwork. It continues "+
      "northwest and southeast, with a entrance to a "+
      "cavern to the northeast.\n");

   add_item("cavern","It looks very plain, being simply "+
      "cut into the wall of this enormous cavern.\n");
   add_item(({"path","street","streets"}),"You can "+
      "walk along a large trodden path that the dwarven boots has "+
      "managed to clear.\n");
  
   add_exit(CPASS(dwarf/s17),"southeast");
   add_exit(CPASS(dwarf/s15),"northwest","@@block");
   add_exit(CPASS(dwarf/barracks/b11),"northeast");
}

int
block()
{
   write("A large group of deep dwarves blocks your attempts "+
      "to walk that way.\n");
   return 1;
}
