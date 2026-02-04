/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house1.c
 *
 * Calathin external house.
 * 09/30/1999 -- Tomas
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>


inherit STDROOM;
object door;
object citizen = 0;

#include <stdproperties.h>


public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("living room");
    set_long("The room has that lived in feeling. Various " +
       "pieces of furniture are scattered throughout the room. To the east is a " +
       "a hallway leading to more rooms. To the north is the dining room. " +
       "A fireplace is set into the south wall. Two windows " +
       "can be seen on either side of the door on the west wall.\n");

    add_item(({"window","windows"}),"The windows are closed with the curtains drawn " +
       "to keep the adverse weather outside.\n");
    add_item(({"drapes","curtain","curtains"}),
       "The curtains are double-lined showing a lovely floral pattern.\n");
    add_item(("floor"),"The hardwood floor has been swept recently.\n");
    add_item(("living room"),"The room has that lived in feeling. Various " +
       "pieces of furniture are scattered throughout the room. To the east is " +
       "a hallway leading to more rooms. To the north is a combination kitchen " +
       "dining room. A fireplace can be seen against the south wall. Two windows " +
       "surround the door on the west wall.\n");
    add_item(("fireplace"),"The large fireplace appears to be the only source of heat " +
       "for the house. The mantle above the fireplace looks as if it was carved from " +
       "a single piece of oak. Intricate designs are carved into the mantle piece. " +
       "There are various items displayed on top of the mantle. A metal screen " +
       "covers the front of the fireplace.\n");
    add_item(({"intricate designs","carvings","designs"}),
       "Resembles vines intertwining with large leaves extending from the vines.\n");
    add_item(({"furniture","chair","chairs","stool","couch","end table","end tables","table"}),
       "A couple chairs and a couch face the fireplace. Two end tables can be seen " +
       "on either side of the couch. There is a stool pushed up against the far wall.\n");



    add_cmd_item(({"drape", "drapes","curtains"}),
                 ({"tear","rip","open"}),
                 ("Its cold enough inside, why would you want to do that?\n"));
    add_cmd_item(({"chair","couch","stool"}), 
                 ({"sit","lie","sit on","lie on"}),
                 ("You sit a spell, then decide to get on with your business.\n"));


     add_exit(CALATHIN_DIR + "houses/house1_hall","east",0,1);
     add_exit(CALATHIN_DIR + "houses/house1_dr","north",0,1);
  
     door = clone_object(CALATHIN_DIR + "houses/obj/house1_lr_door");
        door->move(TO);

     reset_room();

}

void
reset_room()
{    
  
    if(!citizen)
    {
       citizen = clone_object(CALATHIN_DIR + "npc/std_citizen");
          citizen->move(TO);
       citizen = clone_object(CALATHIN_DIR + "npc/std_citizen");
          citizen->move(TO);

    }
}
