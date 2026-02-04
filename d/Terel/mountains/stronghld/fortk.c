/* This comment tells emacs to use c++-mode -*- C++ -*- */

/*
 * Dwarven Stronghold
 * Tomas  -- Jan. 2000
 */

#include "/d/Terel/include/Terel.h"
#include <ss_types.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>
#include <macros.h>

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
    set_short("Passageway");
    set_long(query_long() + "To the east is a door. " +
       "The passageway leads back towards the south.\n");

    add_exit(MOUNTAIN_DIR + "stronghld/fortl","east","@@guarded");
    add_exit(MOUNTAIN_DIR + "stronghld/fortj","south",0,1);

    reset_room();

}


int
guarded()
{
    object warrior;
    string name;

    warrior = present("warrior");

    if (TP->query_prop(OBJ_I_INVIS))
        return 0;

    if (warrior && warrior->query_name()!="corpse" )
    {
       return 0;
    }

    write("The dwarf lowers his weapon blocking you from continuing east.\n");
    say("The dwarf blocks " + QTNAME(TP) +"'s from heading east.\n");
    return 1;
}