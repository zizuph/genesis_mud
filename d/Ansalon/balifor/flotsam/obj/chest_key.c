/*
*    Key for treasure chest in quest in Flotsam
*/
#include "/d/Ansalon/balifor/flotsam/local.h"
inherit "/std/key";

void
create_key() 
{
   ::create_key();
   set_name("key");
   set_short("brass key");
   set_adj("brass");
   set_long("This as a peculiar looking brass key. Strange "
      + "engravings ornament the head of the key. Time has "
      + "left marks of corrosion on the brass key.\n");
   
   set_key(CHEST_KEY);
}
