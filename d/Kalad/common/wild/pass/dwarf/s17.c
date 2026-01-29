inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

/* by korat */

create_room()
{
   ::create_room();
   INSIDE;
   add_prop(ROOM_I_LIGHT,1);
   set_short("Within the dwarven city of Underhome");
   set_long("A red, flickering light streams out of a doorway "+
      "to the east, lighting up the street you stand on. You hear "+
      "the sound of metal hitting metal, mixed with the sounds of "+
      "deep voices singing in a harsh language. The two sounds seems "+
      "to mix in a rythm as ancient as this place itself. Another "+
      "path enters a cavern in the northeast.\n");

   add_item(({"buildings","building","wall"}),
      "The building looks to be in a good shape, and are probably "+
      "being in use by some of the deep dwarves that live in Underhome. "+
      "It has been built next to the wall of this enormous cave.\n");
   add_item(({"path","street","streets"}),"You can "+
      "walk along a large trodden path that the dwarven boots has "+
      "managed to clear.\n");
  
   add_exit(CPASS(dwarf/s16),"northwest");
   add_exit(CPASS(dwarf/s18),"south");
   add_exit(CPASS(dwarf/smith/s21),"east");
   add_exit(CPASS(dwarf/houses/h21),"northeast");
}
