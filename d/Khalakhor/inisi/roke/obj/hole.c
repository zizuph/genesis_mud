/*
 * hole.c
 *
 * Used in wep/shovel.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Updated by Shanoga, 2020-09-29.
 *  - Added function for the hole to remove itself after 10 minutes
 *  - Hole served no purpose after being created and could prevent
 *  - Future players from completing the quest
 */

#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>
#include <filter_funs.h>

void
remove_me()
{
    if (!sizeof(FILTER_PLAYERS(all_inventory(environment())))) {
        remove_object();
        return;
    } else {
        tell_room(environment(), "The ground softly rumbles for a moment, " +
            "then settles.\n", 0, environment());
        remove_object();
        return;
    }
}

void
create_container()
{
    set_name("hole");
    set_short("hole");
  
    add_prop(CONT_I_MAX_WEIGHT, 70000);
    add_prop(CONT_I_MAX_VOLUME, 70000);
    add_prop(OBJ_I_NO_GET, "Take a hole? Get serious!\n");
    add_prop(ROOM_I_LIGHT, 1);

    set_no_show_composite(1);

    // The hole disappears after 10 minutes.
    set_alarm(600.0, 0.0, &remove_me());
}

void
enter_env(object dest, object old)
{ 
    ::enter_env(dest, old);
    dest->add_my_desc(VBFC_ME("hole_desc"),  this_object());
}

/*
 * Add a row to the room description depending on the holes status.
 */
string
hole_desc()
{
    if (query_prop(CONT_I_CLOSED))
    {
        if ((this_player()->query_skill(SS_AWARENESS) + 30) < random(90))
            return "";
        
        return "The soil here shows signs of recent movement.\n";
    }

    return "Someone has dug a hole in the ground.\n";
}

void
leave_env(object old, object dest)
{
    ::leave_env(old, dest);
    
    if (!old)
        return;

    old->remove_my_desc(this_object());
}

int
dig()
{
    if (environment(this_player()) != this_object())
        return 0;

    this_player()->catch_msg("You dig your way out of the hole.\n");
    tell_room(environment(this_object()), QCTNAME(this_player()) +
              " digs out of the ground.\n");


    if (query_prop(CONT_I_CLOSED))
    {
        set_long("It is a rather large hole in the ground.\n");
        remove_prop(CONT_I_CLOSED);
    }
    
    this_player()->move_living("the hole", environment(this_object()));
    return 1;
}

int
filter_env(object ob)
{
    if (environment(ob) != environment(this_object()))
        return 0;

    return 1;
}

int
push(string s)
{
    string what;
    object *obs, ob;
    int error;
    mixed snok;

    notify_fail("Push what into the hole?\n");
    if (!s || !parse_command(s, this_object(), "%s 'into' [the] 'hole'", what))
        return 0;

    obs = CMDPARSE_ONE_ITEM(what, "filter_env", "filter_env");

    if (!sizeof(obs))
        return 0;

    ob = obs[0];

    if (living(ob) || ob->query_prop(OBJ_M_NO_GET))
    {
        if (living(ob))
        this_player()->catch_msg("You can not push " + QTNAME(ob) +
                                 " into the hole.\n");
        else
        this_player()->catch_msg("You can not push the "+ob->short()+
            " into the hole.\n");
        return 1;
    }

    if (living(ob))
        ob->catch_msg(QCTNAME(this_player()) +
                      " pushes you into the hole.\n");

    this_player()->catch_msg("You push " + LANG_THESHORT(ob) +
                             " into the hole.\n");
    say(QCTNAME(this_player()) + " pushes the "+ob->short()+
        " into the hole.\n");

    if (living(ob))
    {
        snok = ob->query_prop(OBJ_M_NO_GET);
        error = ob->move_living("M", this_object());
        ob->add_prop(OBJ_M_NO_GET, snok);
    }
    else
        error = ob->move(this_object());

    switch(error)
    {
    case 0: return 1;
    case 1: 
    case 8:
        notify_fail("The hole is too small for that object!\n");
        break;
    case 2:
        notify_fail("Too bad... That object is not possible to drop into the hole.\n");
        break;
    case 3:
        notify_fail("That object can't leave the room!\n");
        break;
    case 4:
    case 7:
        notify_fail("It is not possible to put that in the hole!\n");
        break;
    case 5:
    case 9:
    case 10:
        notify_fail("What hole?\n");
        break;
    case 6:
        notify_fail("You can't pick up that object!\n");
        break;
    }

    return 0;
}

void
init()
{
    ::init();
    add_action(dig, "dig");
    add_action(push, "push");
}
