/*
 * Author     : Nuf
 * File       : /d/Genesis/start/human/sparkle/docks/ware1_1a.c
 * Description: Base floor storeroom in warehouse 1. Contains 
 *              some searchable crates and a cellar/basement. 
 */

#pragma save_binary
#pragma strict_types

inherit "std/room.c";

#include <stdproperties.h> 	/* For standard properties */
#include <macros.h>    	/* For pre-defined macros */
#include <tasks.h>     	/* For difficulty and stat defines */
#include <ss_types.h>  	/* For skill defines */


#include "../defs.h"
#include "local.h"

/* Prototypes */
public string do_search(object tp, string arg);

/* Defines */

/* Function : nowalk
 * Arguments: string arg - the argument passed with the search
 * Returns  : string with the description of the search event.
 * Purpose  : perform special searches
 */
public int
nowalk(string dir)
{
    tell_room(ENV(TP), QCNAME(TP) + " takes a stroll off to the " +
                       dir + " corner.\n", TP);
    write("You walk to the " + dir + " corner and lurk around.\n");
    return 1;
}

void
create_room()
{
    set_short("A storeroom on the ground floor");
    set_long("A storeroom on the ground floor.\n"+
             "Large crates are piled up in here. Some of them\n"+
             "have strange labels and come from quite unknown places.\n"+
             "");

    add_item(({"crates"}), "You see crates in stacked in the four corners "+
                           "of the room.\n");
    add_item(({"corners"}), "There are four corners, southwest, southeast, "+
                            "northwest and northeast.\n");
    add_item(({"corner"}), "Which corner?\n");
    add_item(({"sw corner", "southwest corner", "ne corner", "northeast corner",
               "se corner", "southeast corner"}), "The corner has a few heavy crates, "+
               "with smaller ones stashed upon.\n");
    add_item(({"sw crate", "southwest crate", "ne crate", "northeast crate", "se crate",
               "southeast crate"}), "The crate has circle with three dots burnt into "+
               "the side.\n");     
    add_item(({"nw corner", "northwest corner"}), "The corner has heavy crates piled "+
               "upon eachother. One of the crates has a strange mark on it.\n");
    add_item(({"nw crate", "northwest crate"}), "The crate has heavy crates piled upon "+
               "eachother. One of the crates has a circle with four dots burnt into the "+
               "side.\n");

    /* Exits */
    add_exit("", "northwest", &nowalk(WALK_NW), 0, 1);
    add_exit("", "northeast", &nowalk(WALK_NE), 0, 1);
    add_exit("", "southwest", &nowalk(WALK_SW), 0, 1);
    add_exit("", "southeast", &nowalk(WALK_SE), 0, 1);

    /* Properties */
    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_I_TYPE, ROOM_NORMAL);

    add_prop(OBJ_I_SEARCH_TIME, 5); 
    add_prop(OBJ_S_SEARCH_FUN, "do_search");
}

/* Function : do_search
 * Arguments: object tp - the object performing the search
 *            string arg - the argument passed with the search
 * Returns  : string with the description of the search event.
 * Purpose  : perform special searches
 */
public string
do_search(object tp, string arg)
{
    string msg, saymsg;
    object ob;

    arg = lower_case(arg);
    
    if ( parse_command(arg, ({}), "[the] 'northwest' / 'nw' 'crate'") )
    {   
	msg = "finding something.\n";
	saymsg = "finding something.\n";
       if (TP->resolve_task(TASK_DIFFICULT, ({SS_AWARENESS, SKILL_AVG, TS_WIS,
                              TS_INT, SKILL_END})) > 0)
       {
          msg = "finding something else.\n";
       }
    }
    else
    {
        return "";
    }
    say(saymsg);
    return msg;
}

public void
enter_inv(object ob, object from)
{
    string base_log;
    ::enter_inv(ob, from);
    if (living(ob))
    {
        if (sizeof(explode(read_file("d/Genesis/start/human/sparkle/docks/base.log"), ob->query_real_name())) == 1)
            write_file("d/Genesis/start/human/sparkle/docks/base.log", ctime(time()) + "\tEntered the basement: " + ob->query_real_name() + ".\n");
    }
}