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
           16/1/2000  removed Aeria description, it 
                      doesn't fit with obelisk history   Maniac
           18/3/98    added Aeria description            Jaacar
           13/2/97    tidied up                          Maniac   
            5/9/95    Updated for polymorph quest        Maniac
           28.4.95          Created                      Maniac
*/

#pragma save_binary

inherit "/d/Calia/std/std_west_moor";
#include <macros.h>
#include <cmdparse.h>
#include "/d/Calia/mountain/defs.h"
#include OBELISK_QUEST
inherit ROAD+"obelisk";

#define LIVE_I_INSERTED_AERIA_STAFF "_live_i_inserted_aeria_staff"

string scop_quest = "";

void
create_room()
{
    make_the_room("\n", 1);
    add_exit(ROAD+"m01", "northeast");
    add_exit(ROAD+"m06", "east"); 
    add_exit(ROAD+"m11", "southeast");

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
    if (present("_aeria_staff_",TP))
    {
        scop_quest = "There is a small hole on the top of the obelisk. ";
        scop_quest += "You could probably insert something into it if ";
        scop_quest += "you wanted to. <insert (itemname)>";
    }
    else if (TP->query_prop(LIVE_I_INSERTED_AERIA_STAFF))
    {
        scop_quest = "There is a white staff sticking out of a small hole ";
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
    
    staff = present("_aeria_staff_",TP);
    if (!staff)
        return 0;

    if (parse_command(str, ({}), 
        "[the] [staff] 'white' [in] [the] [small] [hole]"))
    {
        NF("Insert what coloured staff in the small hole?\n");
        return 0;
    }

    write("You place the white staff into the hole.\n");
    say(QCTNAME(TP)+" does something to the obelisk.\n");
    staff->remove_object();
    TP->add_prop(LIVE_I_INSERTED_AERIA_STAFF,1);
    return 1;
}

/* Handles automatic removal of hand from impression */
void
leave_inv(object ob, object to)
{
    if (hand_in_impression == ob)
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

