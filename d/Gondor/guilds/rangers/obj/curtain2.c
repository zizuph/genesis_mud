/*
 * /d/Gondor/common/guild/ithilien/curtain2.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * the curtain in ithilien_train. the other side is 
 * curtain1 in erockchamber
 *
 * Modified by Alto, 20 July 2001, changed inheritance.
 *
 */
#include "../rangers.h"

inherit RANGERS_OBJ + "ith_door";

#include <files.h>
#include "/d/Gondor/defs.h"

public void create_door();
public int  pass_door(string arg);
public int  lock_door(string arg);

/*
 * Function name: create_door
 * Description  : set up the curtain
 */
public void
create_door() 
{
    ::create_door();
    set_door_id("ith_curtain");
    set_door_name( ({ "grey cloth curtain", "cloth curtain", "curtain" }));
    set_close_command( ({ "close", "draw" }) );
    set_pass_command( ({"w", "west"}) );
    set_door_desc("The curtain is made of smooth grey cloth. It reaches " +
        "to the floor, and appears fairly heavy. A cord attached to " +
        "the edge of the curtain probably is used to tie it shut.");

    set_open_desc(0);
    set_closed_desc(0);
    set_lock_desc(0);

    set_other_room(RANGERS_ITH_DIR + "start");

    set_open(1);
    set_locked(0);
    set_knock_command(0);


    /* officers may tie curtain shut */
    set_lock_command("tie");
    set_lock_mess( ({ "ties the grey cloth curtain shut.\n",
        "The grey cloth curtain is pulled more tightly shut.\n" }) );
    set_fail_lock( ({ "The grey cloth curtain is already tied shut.\n",
        "You must close the grey cloth curtain before you can tie "+
        "it shut.\n" }) );
    set_fail_open( ({ "The grey cloth curtain is already open.\n",
        "The grey cloth curtain is tied shut.\n" }) );
    set_unlock_command("untie");
    set_unlock_mess( ({ "unties the grey cloth curtain.\n",
        "The grey cloth curtain seems to loosen slightly.\n" }) );
    set_fail_unlock("The grey cloth curtain is already untied.\n");
    set_no_pick();

}


/*
 * Function name: pass_door
 * Description  : mask parent to allow passing closed (but not tied)
 *                curtain, and to do custom messages
 * Arguments    : string arg -- unused
 * Returns      : 1 -- always
 */
public int
pass_door(string arg)
{
    if (!other_door)
    {
        load_other_door();
    }

    if (open_status)
    {
        write("You brush past the curtain, and step out of the recess.\n");
        TP->move_living(query_verb(), other_room);
    }
    else if (!lock_status)
    {
        /* say "falls shut" here, because when they see the new room
        * its long desc will be describing a closed curtain */
        WRITE("You open the curtain just enough to let you leave the " +
            "recess. The curtain falls shut behind you.");
        SAY(" opens the grey cloth curtain just enough to slip past.");
        tell_room(other_room, "The grey cloth curtain opens.\n");
        TP->move_living(query_verb(), other_room);
        tell_room(other_room, "The grey cloth curtain falls shut.\n", TP);
        tell_room(ENV(), "The grey cloth curtain falls shut.\n");
    }
    else
    {
        write("The grey cloth curtain is tied shut.\n");
    }

    return 1;
}

/*
 * Function name: lock_door
 * Description  : mask parent so 1) only officers can close off the room
 *                and 2) "tie curtain shut" works
 * Arguments    : string arg -- whatever the player typed
 * Returns      : int -- 1 on success, 0 on failure
 */
public int
lock_door(string arg)
{
    if (!strlen(arg) ||
      !parse_command(LOW(arg), ({}), "[the] [grey] [cloth] 'curtain' [shut]"))
    {
        NF("Tie what?\n");
        return 0;
    }

    if (!R_COUNCIL->is_officer(TP->query_name()) && !TP->query_wiz_level())
    {
        NF("Only officers may prevent others from entering the recess.\n");
        return 0;
    }

    return ::lock_door(arg);
}
