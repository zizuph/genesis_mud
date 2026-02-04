/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 *
 * Dwarven Stronghold
 * Tomas  -- Jan. 2000
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

inherit STDROOM;
inherit MOUNTAIN_DIR + "stronghld/passageway";


object warrior1;
object warrior2;


reset_room()
{
    if (!warrior1) {
        warrior1=clone_object(MOUNTAIN_DIR + "stronghld/npc/std_dwf_warrior");
        warrior1->move(this_object());
    }

    if (!warrior2) {
        warrior2=clone_object(MOUNTAIN_DIR + "stronghld/npc/std_dwf_warrior");
        warrior2->move(this_object());
    }

    if ((warrior1) && (warrior2))
        warrior1->team_join(warrior2);
}



public void
create_room()
{
    ::create_room();
    INSIDE;
    set_short("Stairs");
    set_long(query_long() + "A stone staircase leads " +
       "down to the lower level of the stronghold. The mess " +
       "hall is to the south. The passageway continues " +
       "west and east.\n");


    add_exit(MOUNTAIN_DIR + "stronghld/fortj","east",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/forte","down",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fortg","north",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/forth","south",0,1);
    add_exit(MOUNTAIN_DIR + "stronghld/fortn","west",0,1);
    
    reset_room();

}


