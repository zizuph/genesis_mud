
/* 
   Moorland in the mid-west of Calia.

   Coded by Maniac.

   History:
           04/9/2003  added insertion of staff for 
                      Spirit Circle entrance quest
                      (didn't change the description
                      unless they are on the quest so
                      it doesn't interfere with the 
                      obelisk history)                   Jaacar 
           16/1/2000  removed Pyros description, it 
                      doesn't fit with obelisk history   Maniac
          18/2/98   added Pyros description             Jaacar
          13/2/97   tidied up                           Maniac 
           5/9/95   updated for polymorph quest         Maniac
           2.5.95          Created                      Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";
#include <macros.h>
#include "/d/Calia/mountain/defs.h"
#include OBELISK_QUEST
inherit ROAD+"obelisk";

#define LIVE_I_INSERTED_PYROS_STAFF "_live_i_inserted_pyros_staff"

string scop_quest = "";

void
create_room()
{
    make_the_room("\n", 1, 1);
    add_exit(ROAD+"m22", "northwest");
    add_exit(ROAD+"m27", "west"); 
    add_exit(ROAD+"m32", "southwest");
    add_exit(FOOTHILL+"fh01", "south"); 
    add_exit(FOOTHILL+"fh02", "southeast");

    add_item("obelisk", "This four-sided stone column, standing some "+
        "ten feet high, tapers to a pyramid at the top. The stone "+
        "that the column is made of is a deep grey colour, and "+
        "has a smooth surface. There is an impression in the stone "+
        "about four feet up from the base. @@scop_quest@@\n");

    add_item("impression", "It is about the right size for a large " +
             "hand.\n"); 
}

string
scop_quest()
{
    if (present("_pyros_staff_",TP))
    {
        scop_quest = "There is a small hole on the top of the obelisk. ";
        scop_quest += "You could probably insert something into it if ";
        scop_quest += "you wanted to. <insert (itemname)>";
    }
    else if (TP->query_prop(LIVE_I_INSERTED_PYROS_STAFF))
    {
        scop_quest = "There is a red staff sticking out of a small hole ";
        scop_quest += "on the top of the obelisk.";
    }
    else
        scop_quest = "";

    return scop_quest;
}

int
do_insert(string str)
{
    object staff;

    if (!str)
        return 0;
    
    staff = present("_pyros_staff_",TP);
    if (!staff)
        return 0;

    if (parse_command(str, ({}), 
        "[the] [staff] 'red' [in] [the] [small] [hole]"))
    {
        NF("Insert what coloured staff in the small hole?\n");
        return 0;
    }

    write("You place the red staff into the hole.\n");
    say(QCTNAME(TP)+" does something to the obelisk.\n");
    staff->remove_object();
    TP->add_prop(LIVE_I_INSERTED_PYROS_STAFF,1);
    return 1;
}

/* Handles automatic removal of hand from impression */
void
leave_inv(object ob, object to)
{
    if (ob == hand_in_impression)
        remove_result(ob);
    ::leave_inv(ob, to);
}

void
init()
{
    ::init();
    add_action(obq_block, "", 1); 
    add_action(obq_place, "place");
    add_action(obq_place, "put");
    add_action(obq_remove, "remove");
    add_action(do_insert, "insert");
    add_action(pq_chip, "chip");
    add_action(pq_chip, "chisel");
}

