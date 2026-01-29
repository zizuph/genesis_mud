/*
 * hole.c
 * FIXA
 * Used in wep/shovel.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/container";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <language.h>

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
}

void
enter_env(object dest, object old)
{ 
    ::enter_env(dest, old);
    dest->add_my_desc("Someone has dug a hole in the ground.\n",
                      this_object());
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

        enter_env(environment(this_object()), 0);
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
    object *obs;
    int error;
    mixed snok;

    notify_fail("Push what into the hole?\n");
    if (!parse_command(s, this_object(), "%s 'into' [the] 'hole'", what))
        return 0;

    obs = CMDPARSE_ONE_ITEM(what, "filter_env", "filter_env");

    if (!sizeof(obs))
        return 0;

    if (living(obs[0]))
        obs[0]->catch_msg(QCTNAME(this_player()) +
                          " pushes you into the hole.\n");

    this_player()->catch_msg("You push " + LANG_THESHORT(obs[0]) +
                             " into the hole.\n");
    say(QCTNAME(this_player()) + " pushes " + LANG_ASHORT(obs[0]) +
        " into the hole.\n");

    if (living(obs[0]))
    {
        snok = obs[0]->query_prop(OBJ_M_NO_GET);
        error = obs[0]->move_living("M", this_object());
        obs[0]->add_prop(OBJ_M_NO_GET, snok);
    }
    else
        error = obs[0]->move(this_object());

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
    add_action(dig,"dig");
    add_action(push,"push");
}




