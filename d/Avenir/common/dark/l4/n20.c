/*
n13.c is E
n21 is W
*/

inherit "/std/room";
#include "/d/Avenir/common/dark/dark.h"


create_room()
{

set_short("Dirty tunnel");
 set_long(
    "This western tunnel branch is extremely dark and dirty.  " +
    "The way is strewn with cobwebs, and the floor of the " +
    "tunnel is very rough and uneven.  A large cavern is to " +
    "the east, while this passageway continues westward.\n");

AE(L4+"n13","east",0,DIRT);
AE(L4+"n21","west","@@do_web",DIRT);

add_prop(ROOM_I_LIGHT,0);
IN

AI(({"cobweb","cobwebs"}),"The cobwebs hang down in your " +
   "face, tickling your skin.\n");

AI(({"ceiling", "walls", "wall", "floor", "tunnel", "passage", 
   "passageway"}), "Very uninteresting stone.\n");    

}
// Added by Tep for creepiness factor
int
do_web()
{
    if (!random(3))
    {
	write("You break through the cobwebs.\n" +
	  "A shiver runs up your spine as they brush against " +
	  "your face. This place makes your skin crawl.\n\n");
	this_player()->add_panic(5);
    } 
  return 0;
}
