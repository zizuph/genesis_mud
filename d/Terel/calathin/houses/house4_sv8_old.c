/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4_sv8.c -- captain of the guard quarters
 * Calathin external house.
 * 09/30/1999 -- TOMAS
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>

inherit STDROOM;
#include <stdproperties.h>

object door;
object guard = 0;
object arlenn = 0;


public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("captains quarters");
    set_long("This room is a bit larger than the other guards quarters. " +
       "A map hangs on the north wall over " +
       "a desk and chair. Against the southern wall is a bed and wooden stool. " +
       "A multi-colored pennant stands " +
       "in the northwestern corner. And in the middle of the room sits a " +
       "small cast iron stove.\n");


    add_item(("map"),"A large paper map is tacked up on the wall showing " +
       "a detailed map of the house and the grounds around it. Several " +
       "red dots can be seen about the inside of the house. Your guess is " +
       "that the dots represent sentry positions.\n");
    
    add_item(({"desk","chair"}),
       "An average desk and wooden chair can be seen against the wall. " +
       "Nothing on the desk peaks your interest however.\n");

    add_item(({"bed","wooden stool","stool"}),
       "A small bed and stool can be seen against the far wall. The bed " +
       "is covered by a wool blanket.\n");
 

    add_item(({"cast iron stove","stove"}),
       "The cast iron stove is used to heat the room. You notice that " +
       "its the only one of its kind in the servants quarters.\n");

    add_item(({"multi-colored pennant","pennant"}),
       "A multi-colored pennant stands sheathed in a brass holder against " +
       "the northwest corner. The meaning of the pennant is unclear to you " +
       "however.\n");

   add_exit(CALATHIN_DIR + "houses/house4_sv3","west","@@guarded");
    
    reset_room();

}


void
reset_room()
{    
  
   if(!arlenn)
   {
       arlenn = clone_object(CALATHIN_DIR + "houses/npc/house4_captain");
       arlenn->move(TO);
   }

}



int
guarded(object attacker)
{
    string name;

    arlenn = present("arlenn");
    attacker = arlenn->query_enemy();

    if (TP->query_prop(OBJ_I_INVIS))
       return 0;

    if(attacker == TP)
    {
       if((TP->query_average_stat()) > (arlenn->query_average_stat()) ||
          (TP->query_fatigue()) > (arlenn->query_fatigue()))
       {
          write("You manage to push the sandy-haired human aside.\n");
          say(QTNAME(TP) +" pushes past the sandy-haired human.\n");
          return 0;
       }

       write("The sandy-haired human forcefully shoves you away from " +
          "the door. You feel winded from the struggle.\n");
       say("The sandy-haired human shoves " + QTNAME(TP) +" away from the " +
          "exit.\n");
       TP->add_fatigue(-20);
       return 1;
    }
    return 0;
}
