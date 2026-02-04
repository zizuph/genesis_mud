/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house2a.c
 *
 * Calathin external house.
 * 09/30/1999 -- CALATHIN
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
    set_long("The living room is small but cozy. Several " +
       "pieces of wooden furniture fill the room. The living room " +
       "extends into the kitchen to the north. A fireplace can be " +
       "seen to the south, while another door can be seen to the east. " +
       "Windows can be seen in the living room and one above the " +
       "counter in the kitchen.\n");

    add_item(({"window","windows"}),"The windows are closed with the curtains drawn " +
       "to keep the adverse weather outside.\n");
    add_item(({"drapes","curtain","curtains"}),
       "The curtains are double-lined showing a lovely floral pattern.\n");
    add_item(("floor"),"The hardwood floor has been swept recently.\n");
    add_item(("fireplace"),"The large fireplace appears to be the only source of heat " +
       "for the house.\n");
    add_item(({"furniture","chair","chairs","stool","couch","end table","end tables","table"}),
       "A couple chairs and a couch face the fireplace. Two end tables can be seen " +
       "on either side of the couch. There is a stool pushed up against the far wall.\n");
    add_item(("kitchen"),"The small kitchen extends from the living area. A small table " +
       "can be seen against the far wall.\n");



    add_cmd_item(({"drape", "drapes","curtains"}),
                 ({"tear","rip","open"}),
                 ("Its cold enough inside, why would you want to do that?\n"));
    add_cmd_item(({"chair","couch","stool"}), 
                 ({"sit","lie","sit on","lie on"}),
                 ("You sit a spell, then decide to get on with your business.\n"));


     door = clone_object(CALATHIN_DIR + "houses/obj/house2_bedrm1_door");
        door->move(TO);

     door = clone_object(CALATHIN_DIR + "houses/obj/house2a_door");
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


