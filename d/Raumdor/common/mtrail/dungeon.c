/* SARR */
/* 2017-10-21 Malus: Added escape method */ 
#include "defs.h"
#include <tasks.h>
#define RAUMDOR_TRAP_FOUND_MOSS "_raumdor_trap_found_moss"
inherit SECRET_ROOM;

object wraith;
object crevice;
object moss;

void
create_room()
{
    ::create_room();
    set_short("Inside a pit");
    set_long("You are in a dark and dismal pit. Jagged sharp rocks "+
        "litter the ground. Along the walls you see nothing but stone.\n");
    add_item("pit", "You are trapped in it.\n");
    add_item("rocks", "They are hard and jagged, and covered with "+
        "old blood. Along the ground you also see skeletons and bones.\n");
    add_item(({"blood", "bloodstains"}),
        "Faded bloodstains cover the rocks and ground.\n");
    add_item("ground", "Bloodstained rocks and the remains of previous " + 
        "victims are scattered on the ground.\n");
    add_item(({"wall", "walls"}), "The cold stone walls rise into darkness.\n");  
    add_item(({"skeletons", "bones"}),
        "Poor souls like you are about to become.\n");
    add_prop(ROOM_I_LIGHT,0);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    moss = clone_object(COMMON_OBJ_DIR + "moss");
    moss->move(TO, 1);

    crevice = clone_object(COMMON_OBJ_DIR + "crevice");
    crevice->move(TO, 1);
}

public int
query_moss_ripped()
{
    return moss->query_ripped();
}

void
summon_wraith()
{
    if(!wraith)
    {
        wraith = clone_object(COMMON_NPC_DIR + "wraith");
        wraith->move_living("M",TO);
        TELL_SEEN(wraith, "Out of the darkness, " + 
                LANG_ASHORT(wraith) + " floats into view!\n");
    }
}

void
init()
{
    ::init();
    set_alarm(2.0, 0.0, "summon_wraith");
}

void
reset_room()
{
    if(!sizeof(FILTER_PLAYERS(all_inventory(TO))))
    {
        moss->reset_ripped();
    }
}

mixed
do_search(object searcher, string what)
{
    if (what == "wall" || what == "walls")
    {
        int success;
        if (searcher->query_prop(RAUMDOR_TRAP_FOUND_MOSS))
        {
            write("You find nothing new.\n");
            return "You find nothing new\n"; 
        }
        success = searcher->resolve_task(TASK_HARD, 
                ({SS_AWARENESS, SKILL_AVG, TS_DEX, TS_INT, SKILL_END}));
        if (success < 0)
        {
            return "You did not find anything.\n";
        }
        searcher->add_prop(RAUMDOR_TRAP_FOUND_MOSS, 1);
        return "You find a vein of dark moss.\n";
    }
    return 0;
}
