/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * house4a.c
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
object guard;
object guard2;
object guard3;
object guard4;
object citizen;

public void
create_room()
{
    ::create_room();
    INSIDE;

    set_short("entrance way");
    set_long("The entrance way is guarded by " +
       "two ancient suits of elaborately decorated " +
       "armour located on either side of the main door. " +
       "Each suit of armour holds multi-colored pennants clutched " +
       "firmly within their gauntlets. " +
       "To the west is the sitting room. To the east is the " +
       "the dining room. A spiral staircase is set in the " +
       "middle of the room leading upstairs. The hallway " +
       "continues north.\n");

    add_item(({"ancient suit","ancient suits","armour","suit","suits"}),
       "Massive suits of plated armour lined in gold " + 
       "and silver. The suits look more for show " +
       "than protection.\n");

    add_item(("pennants"),"The multi-colored pennants " +
       "appear to have some meaning to the owners.\n");

    add_item(("staircase"),"The staircase is painted " +
       "white. The bannister has been polished depicting " +
       "elaborate engravings of various plantlife and " +
       "wild animals.\n");

    add_cmd_item(({"ancient suit","ancient suits","armour","suits","suit"}),
                 ("get"),
                 ("The suits of armour are secured tightly " +
                  "to the wall and cannot be removed.\n"));
 
    add_exit(CALATHIN_DIR + "houses/house4b","west",0,1);
    add_exit(CALATHIN_DIR + "houses/house4c","east",0,1);
    add_exit(CALATHIN_DIR + "houses/house4_2a","stairs",0,1);
    add_exit(CALATHIN_DIR + "houses/house4d","north", "@@guarded");
    door = clone_object(CALATHIN_DIR + "houses/obj/house4a_door");
       door->move(TO);

    reset_room();

}


void
reset_room()
{
    if(!guard)
    {
       guard = clone_object(CALATHIN_DIR + "houses/npc/house4_guard");
       guard->move(TO);

       guard2 = clone_object(CALATHIN_DIR + "houses/npc/house4_guard");
       guard2->move(TO);
       guard2->team_join(guard);

       guard3 = clone_object(CALATHIN_DIR + "houses/npc/house4_guard");
       guard3->move(TO);
       guard3->team_join(guard);

       guard4 = clone_object(CALATHIN_DIR + "houses/npc/house4_guard");
       guard4->move(TO);
       guard4->team_join(guard);
    }

    if(!citizen)
    {
       citizen = clone_object(CALATHIN_DIR + "npc/std_citizen");
       citizen->move(TO);
    }

}


int
guarded()
{
    object warrior;
    string name;

    warrior = present("guard");
    if (TP->query_prop(OBJ_I_INVIS) || TP->query_race() !="goblin")
        return 0;
    
    if(warrior && warrior->query_name()!="corpse")
    {
        write("The guard blocks you from continuing north.\n");
        say("The guard blocks " + QTNAME(TP) +"'s from heading north.\n");
        return 1;
    }
    return 0;
}
