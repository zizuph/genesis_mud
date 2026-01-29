#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void add_stuff();

//object rock;

void
create_er_room()
{
   
   area = "a good distance"; /* Distance from areaname */
   areaname = "Undertowers";
   land = "Eriador";
   areatype = 10;
   areadesc = "tiny settlement";
   grass = "green";
   
   extraline = "The village of Undertowers is gathered around the Great East Road. "+
   "This village is a part of the area known as Westmarch, here in Eriador. "+
   "The rolling hills that surround the road to both the east and "+
   "the west lie between the Tower Hills and the Far Downs. "+
   "There are a few small hobbit-holes here, but since "+
   "Undertowers is small even by hobbit standards, it is unlikely "+
   "for a crowd to form. The Great East Road leads east and west, "+
   "some parts of the village lie north and south.";

   add_item(({"undertowers","westmarch","village"}),
   "The village of Undertowers in Westmarch is a tiny one indeed, "+
   "not surprising, considering it lies outside the boundaries of the "+
   "Shire.\n");

   add_item(({"hills","hill","rolling hills","tower hills","far downs"}),
   "This area is made of hills, hills and more hills. The Far Downs "+
   "wrinkle the surface of the earth to the east, as the Tower Hills "+
   "do so in the west. In between are these hills, which make "+
   "up a great deal of Westmarch.\n");

   add_item(({"hobbit holes","hobbit-holes","holes"}),
   "The hobbit holes around here are dug right into the "+
   "sides of the hills, a convenient arrangement to be sure. "+
   "They look reasonably big and not too crowded, though "+
   "it seems impossible to enter them.\n");

   add_exit(EAST_R_DIR + "er2","west");
   add_exit(EAST_R_DIR + "er4","east", "@@enter_shire@@");
   add_exit(EAST_R_DIR + "er3s","south");
   add_exit(EAST_R_DIR + "er3n","north");

    add_stuff();
}



void add_stuff()
{
//    rock = clone_object(ROCK_DIR + "rock");
//    rock->move(TO);
}


void
reset_shire_room()
{
    add_stuff();
}


void enter_shire()
{
    write("You cross the West Farthing border and enter the Shire.\n");
}