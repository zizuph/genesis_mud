/*
 * File Name        : pirate_center_room.c
 * By               : Elmore.
 * Inspiration from : -
 * Date             : Nov. 2000.
 * Description      : Just another guild room :)
 *
 */

#include "/d/Ansalon/goodlund/nethosak/city/local.h"
#include "../local.h"
#include <stdproperties.h>

inherit MITHAS_IN;

void
create_mithas_room()
{
   set_short("Huge underground cave");
   set_long("@@long_descr");

   add_exit("underground_cave","south",0,0);
   add_exit("pirate_drop_room","west",0,0);
   add_exit("pirate_train_room","north",0,0);
   add_exit("pirate_shop","east",0,0);
}

string
long_descr()
{ 
   return "You are standing in a huge underground cave, beneth "+
          "the isle of Mithas. The cave must have been made "+
          "by some sort of violent erosion of the stones that "+
          "form the bedrock of the isle. The black rock walls "+
          "are drenched with water and the smell of the fresh "+
          "seawater and wet soil dominate this place. This "+
          "might be a good place to hide ourself or something. "+
          "Three some exits leads to the east towards a small "+
          "shop, west towards some sort of big hall and south "+
          "to the entrance of the caves.\n";
}

