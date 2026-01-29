// hp6
// room just before the training room
// grace feb 1995
// crown, bronze, and brass banners (courtesy of Teth) added 2/23/96

#include "../local.h"
inherit SPURRM;

object ban1, ban2, ban3;

void
reset_spur_room()
{                                                                       
/*
    if (!ban1)
      (ban1 = clone_object(SOBJ + "brnzbnr"))->move(TO);
    if (!ban2)
      (ban2 = clone_object(SOBJ + "brssbnr"))->move(TO);
    if (!ban3)
      (ban3 = clone_object(SOBJ + "crwnbnr"))->move(TO);
*/
}  

void 
create_spur_room()
{

   SHORT("Hidden hallway");
   LONG("You have entered a strange passage which seems "+
      "to have been constructed during two distinct time "+
      "periods.\n   The section stretching away to the "+
      "east appears to be newer, though even then the "+
      "stones were cut and laid centuries ago.  The "+
      "western portion is older, made by craftsmen long-"+
      "forgotten, perhaps in the days before the Cata"+
      "clysm.\n   Here you can see the base of a stairwell "+
      "winding upwards.\n");

   AE(ROOM + "hp5", "up", 0);
   AE(ROOM + "hp7", "east", 0);
/*
AE(ROOM + "hp8", "west", 0);
*/

   AI(({"floor","stone floor"}),
      "It is so shiny you can see your reflection in it.\n");
   AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
      "is a distorted image of your face. At least, you hope it "+
      "is distorted. You've seen draconians prettier than that!\n");
   AI(({"stair", "stairwell"}), "It is circular and winds upward.\n");
   AI(({"torch", "torches"}), "They are just like all the others "+
      "you have seen here in the Knights' Spur.\n");
   AI(({"door", "doorway"}), "Bright light illuminates the darkened "+
      "stairwell which lies beyond the doorway.\n");

   reset_spur_room();
}

