inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"

create_room()
{
   
   ::create_room();
   hear_bell = 3;
   
   set_short("Caravan Street");
   set_long(
      "You are on Caravan Street. "+
      "This wide concourse is paved in cobblestones and continues " +
      "northeast towards the Caravan district. "+
      "Buildings of various sizes compete for space on either side " +
      "and to the west you can see a huge structure; It is "+
      "the Gladiatoral arena. The road continues southwestwards.\n");
   
   add_item(({"street","caravan street","concourse","wide concourse"}),BS(
         "It is paved in cobblestones and " +
         "runs southwest towards the basket-lift and northeast towards "+
         "the Caravan district.\n"));
   add_item(({"stones","cobblestones","pavement","cobbles"}),BS(
         "The stone cobbles of the street are worn and missing in places " +
         "but overall the pavement is in good repair for such a well-travelled " +
         "roadway.\n"));
   add_item(({"buildings","structures"}),BS(
         "The structures are of varying sizes, usually two or three stories " +
         "high, and have been squeezed in wherever there was space. They " +
         "provide lodging for the local shopkeepers and laborers of " +
         "the district.\n"));
   add_item(({"arena","gladiatoral","gladiatoral arena"}),
      "Its a huge circular structure made of rough-cut stones. "+
      "On the top of it, at the third level, you see several different "+
      "coloured flags flicker slightly in the wind.\n");
   
   add_exit(CENTRAL(caravan/s2),"northeast");
   add_exit(CENTRAL(caravan/s4),"southwest");
}

