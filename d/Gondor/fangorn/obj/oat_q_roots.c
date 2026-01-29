/*
 * The roots for the Faradan Oat quest.
 *    These roots are cloned to one of an array of rooms
 *    and will move a door (pathway) into the room if searched.
 *
 * /d/Gondor/fangorn/obj/oat_q_roots.c
 *
 * Alto, 13 May 2001
 *
 */


inherit "/std/object";

#include <stdproperties.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/minas/lib/porter_defs.h"
#include "/d/Gondor/bits.h"



#define INNER_MINAS "/d/Gondor/minas"
#define FANGORN_DIR "/d/Gondor/fangorn/"

object pathway;
object actor, here, *env;

public string do_search(object actor, string str);
public int find_pathway(object actor, int i);

void
create_object()
{
    set_short("roots");
    set_name("roots");
    add_name("root");
    add_name("_oat_quest_roots_");
    set_long("There is something VERY strange about the roots here. ");

    set_no_show_composite(1);

    add_prop(OBJ_M_NO_GET, "The roots are stuck firmly in the ground.\n");
    add_prop(OBJ_I_VOLUME,      1000);
    add_prop(OBJ_I_WEIGHT,      1000);

    add_prop(OBJ_I_SEARCH_TIME, 5);
    add_prop(OBJ_S_SEARCH_FUN, "do_search");


}


public string
do_search(object actor, string str)
{
    if(!str)
        NFN("Search what?");

    switch(str)
    {
        case "roots" :
            WRITE("You move aside the roots.\n");
            find_pathway(TP, 1);
            return "When you release them, the roots return to their "
                + "original position.\n";
     }
     NFN("You don't find any " + str + " to search.");
}




public int
find_pathway(object actor, int i)
{
    here = environment(actor);
    env = all_inventory(here);

    if (actor->test_bit("Gondor",
        MTIRITH_PORTER_GROUP,
        MTIRITH_OAT_BIT))
    {
        WRITE("Your search reveals nothing special.");
        return 0;
    }

    if (actor->query_prop(QUESTING_FOR_OATS))
    {
        if (sizeof(filter(env, &->id("_oat_q_path_")))) return 0;

        WRITE("You find a pathway concealed beneath the roots!");
        pathway = clone_object(FANGORN_DIR + "obj/oat_q_path.c");
        pathway->move(ENV(TO));
        return 1;
    }

    WRITE("There is nothing special about the roots.");
    return 0;
    
}

