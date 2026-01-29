/* File farmer-market.c
 * Coded by Feofil
 */

inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h";

void create_room()
{
    ::create_room();
    set_short("On the intersection of Farmer's Way and Market Street");
    set_long("You are standing at the large intersection of the Farmer's "+
      "Way and the Market Street. People, carts, carriages, horses everywhere, "+
      "moving in east, west and southeast directions. Sometimes you feel as a "+
      "lost child in this chaos. Noise coming from south is so strong, that you "+
      "can clearly say, that here the Market district starts. To the north, "+
      "you hear nothing, and no crowds. This must be the start of the "+
      "noble "+
      "district, one of the most quiet and \"uncriminal\" places of Kabal. Your "+
      "eyes stop on the huge statue at the center of plaza.\n"); 
    hear_bell = 2;                   /*  2 = outdoor, 1 = indoor */
    add_exit(NOBLE(farmer/s6),"east",0,0,-1);
    add_exit(NOBLE(farmer/s7),"west",0,0,-1);
    add_exit(NOBLE(road/r1),"north",0,0,-1);
    add_exit(NOBLE(market/s1),"northwest",0,0,-1);
    add_item("statue","This is a large statue of the First Farmer of "
      + "Kalad, that rolled his cart this way, coming from the wild area. You "
      + "wonder what a strange construction the cart has.\n");
    add_item(({"construction","cart"}),"You note the "
      + "disproportionately large wheels of the cart. Strangely enough one of the "
      + "wheels seem to be out of the dust.\n");
}

