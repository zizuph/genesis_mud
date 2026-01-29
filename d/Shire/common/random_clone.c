/*
*   Functions to randomly create objects in a room.
*   This file should never be used alone. It has to
*   be inherited into a file that contains all the standard
*   includes and inheritance.
*
*   created by Merrygrin 920724
*/

/*
*   get_monster(int perc, string name) 
*   
*   perc = chance of this object being in this room.
*   name = filename of monster
*/
#include "defs.h"

object get_object(int perc, string name) {
  int ran;
  object ob;

  ran = random(100);

  if(ran > perc)
    return 0;

  ob = clone_object(name);
  if (living(ob))
    ob->move_living(this_object());
  else
    ob->move(this_object());

  return ob;
}

