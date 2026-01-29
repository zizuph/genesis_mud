
/* 
   Code to set up the wall item descriptions in the parts of the fountain 
   in Gelan that are near the walls (i.e. most of it), originally coded by 
   Snarf. 
   There was a mana drain placed on those who enter such locations, probably 
   something to do with the coin that was supposed to be found in the fountain 
   that snarf planned (see coinmaster.c and fountain.c) and the chance of 
   removing headaches by drinking/washing the fountain (commented out, see 
   fountain.c). 
   I've commented out all code relating to the mana drain for the time being. 

   Maniac, 7.94 


   Revision history: 
       4/10/01    typo fixed                                  Maniac
       14/7/95    Typos corrected                             Maniac
       13.2.95    some errors corrected                       Maniac
          8.94    spash/drip for entering/leaving fountain    Maniac
*/
 
#include "room.h"
#pragma save_binary

inherit GELAN_ROOMS + "fountain";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#define TP this_player()


void 
make_fountain_wall() 
{ 
    make_fountain(); 
    add_item(({"wall","walls","stone wall","stone walls"}), 
	     "The wall surrounding the fountain is made of " + 
	     "some kind of black stone.\n"); 
    add_item(({"stone","black stone"}),"@@stone"); 
} 


string
stone()
{
  string text;

  text = "The stone is black as ebony and has an extremely smooth surface.\n";
  if (((TP->query_skill(SS_SPELLCRAFT))>50) ||
      ((TP->query_skill(SS_AWARENESS))>50)) text = text + 
	   "You also notice that the stone emits a dim light.\n";
  return (text);
}


void
enter_inv(object ob, object from)
{
    if (objectp(from) && 
        !(from->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER) && 
        living(ob) && !ob->query_ghost())
    {
        tell_object(ob, "You enter the fountain. Splash!\n");
        if (!living(from)) 
            tell_room(from, QCTNAME(ob) + " enters the " +
                      "fountain. Splash!\n", ob);
        tell_room(environment(ob), QCTNAME(ob) + " enters the " +
                                   "fountain. Splash!\n", ob);
    }
    ::enter_inv(ob, from);
}


void
leave_inv(object ob, object to)
{
    if (objectp(to) && 
        !(to->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER) && 
        living(ob) && !ob->query_ghost()) 
    { 
        tell_object(ob, "You leave the fountain. Drip drip..\n"); 
        if (!living(to)) 
            tell_room(to, 
                QCTNAME(ob) + " leaves the fountain. Drip drip..\n", ob); 
        tell_room(this_object(), QCTNAME(ob) + " leaves " + 
                  "the fountain. Drip drip..\n", ob); 
    } 
    ::leave_inv(ob, to); 
}

