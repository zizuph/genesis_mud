/*
 * /d/Gondor/common/guild/ithilien/curtain1.c
 *
 * Copyright (C) 1998 by Nancy L. Mintz (Gnadnar)
 *
 * the curtain in erockchamber. the other side is 
 * curtain2 in ithilien_train
 *
 * Modified by Alto, 20 July 2001, changed inheritance.
 */
#include "../rangers.h"

inherit RANGERS_OBJ + "ith_door";

#include "/d/Gondor/defs.h"
#include <macros.h>

public void create_door();
public int  pass_door(string arg);
public int  lock_door(string arg);
public int  unlock_door(string arg);

/*
 * Function name: create_door
 * Description  : set up the curtain
 */
public void
create_door() 
{
    set_door_id("ith_curtain");
    set_door_name( ({ "grey cloth curtain", "cloth curtain", "curtain" }));
    set_close_command( ({ "close", "draw" }) );
    set_pass_command( ({"e", "east"}) );
    set_door_desc("The curtain is made of dull grey cloth. It reaches " +
        "to the floor, and appears fairly heavy.");

    set_open_desc(0);
    set_closed_desc(0);

    set_other_room(RANGERS_ITH_DIR + "train");

    set_open(1);
    set_locked(0);
    set_knock_command(0);

    /* cannot tie/untie curtain from this side, but 
     * set up the commands so the failure messages look right */
    set_lock_command("tie");
    set_lock_mess( ({ "ties the grey cloth curtain shut.\n", "" }) );
    set_fail_lock( ({ "The grey cloth curtain is already tied shut.\n",
        "You must close the grey cloth curtain before you can " +
        "tie it shut.\n" }) );
    set_fail_open( ({ "The grey cloth curtain is already open.\n",
        "The grey cloth curtain is tied shut.\n" }) );
    set_unlock_command("untie");
    set_unlock_mess( ({ "unties the grey cloth curtain.\n", "" }) );
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
        if (TP->query_company() != "ithilien" && !TP->query_wiz_level())
        {
            write("A green-cloaked sentinel prevents you from passing "
                + "that way.\n");
            return 1;
        }

        write("You brush past the curtain, and enter the recess.\n");
        TP->move_living(query_verb(), other_room);
    }
    else if (!lock_status)
    {
        /* say "falls shut" here, because when they see the new room
         * its long desc will be describing a closed curtain */
         write("You open the curtain just enough to let you enter the " +
              "recess. The curtain falls shut behind you.\n");
         say(QCTNAME(TP) + " opens the grey cloth curtain just enough to " +
              "slip past.\n");
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
 * Function name: unlock_door
 * Description  : mask parent so always to fail from this side.
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 if we understand the arg, 0 if not
 */
public int
unlock_door(string arg)
{
    if (strlen(arg) &&
      parse_command(LOW(arg), ({}), "[the] [grey] [cloth] 'curtain'"))
    {
        write("You see no way to untie the grey cloth curtain from here.\n");
        return 1;
    }

    return 0;
}

/*
 * Function name: lock_door
 * Description  : mask parent so always to fail from this side.
 * Arguments    : string arg -- whatever the player typed
 * Returns      : 1 if we understand the arg, 0 if not
 */
public int
lock_door(string arg)
{
    if (strlen(arg) &&
      parse_command(LOW(arg), ({}), "[the] [grey] [cloth] 'curtain' [shut]"))
    {
        write("You see no way to tie the grey cloth curtain from here.\n");
        return 1;
    }

    return 0;
}
