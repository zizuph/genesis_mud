// Container:  covert_container.c

    /* Calia Domain

    HISTORY

    [98-09-28] Created by Uhclem from
    [D:\CALIA\CENTRAL\FOREST\SPECIALS\COVERT_C.DOC].

    PURPOSE

    This container represents the space enclosed by the branches of a tree. It
    is cloned into rooms in the Great Central Forest when a player climbs into
    one of the trees that doesn't have a room leading up to the forest canopy.
    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/container";

#include <macros.h>
#include <composite.h>
#include <language.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "defs.h"

// FUNCTIONS

// Function:  break_stick()

/*

Purpose:  break a stick off the tree.

Arguments:  string, "stick".

Returns:  0/1.

*/

int
break_stick(string stick)

    {

    object tp = this_player();
    object ob;

    if(stick != "stick")

        {

        notify_fail("Break what?\n");
        return 0;

        }

    write("You break the stick off the tree; it separates cleanly" +
        " with a loud, sharp 'snap!'\n");

    ob = clone_object(FOREST_OBJECTS + "stick");
    ob->create_stick(query_short());
    ob->move(tp);
    return 1;

    }

// Function:  climb_down()

/*

Purpose:  get the player out of the tree.

Arguments:  none.

Returns:  1.

*/

int
climb_down()

    {

    object tp = this_player();
    object to = this_object();
    object en = environment(to);
    object noseeum;
    object *contents;

    tp->move_living("M", en, 1);

    tell_room(en,
        QCNAME(tp) + " climbs down from the " + query_short() + ".\n",
        ({tp}));

    contents = all_inventory(to);

    if (sizeof(contents) == 1 && contents[0]->query_name() == "No-see-um")

        {

        contents[0]->close_channel();  /* removes internal noseeum */
        noseeum = present("no-see-um", en);
        noseeum->close_channel(this_object());  /* silences external noseeum */
        remove_object();

        }

    else

        {

        tell_room(to, QCTNAME(tp) + " climbs down.\n");

        }

    return 1;

    }

// Function:  am_i_hidden()

/*

Purpose:  .
Arguments:  none.
Returns:  nothing.

*/

int
am_i_hidden()

    {

    if (environment(this_player()) == this_object()) return 0;
    else return 100;

    }

// Function:  init()

/*

Purpose:  add local commands.
Arguments:  none.
Returns:  nothing.

*/

void
init()

    {

    if (environment(this_player()) == this_object())

        {

        ::init();

        write(query_long());

        add_action(climb_down, "climb");
        add_action(break_stick, "break");

        }

    }

// CONTAINER DEFINITION

void
create_container()

    {

    // set_no_show();
    set_name("");
    add_name("covert_container");
    set_short("unknown tree");

    set_long("You have climbed up into a tree from which you" +
        " can hear everything that goes on below. Of course, those" +
        " below can probably also hear you, so you probably shouldn't" +
        " make too much noise. You can climb down any time you want.\n");

    add_item(({"tree", "branches"}),
        "This tree is so dense that you can't see out to the forest" +
        " below, and that means that nobody below can see you. While" +
        " the outer branches are lush and green, inside, where" +
        " the sunlight never reaches, many of the branches are" +
        " slender and nearly bare, some of them no more than sticks.\n");

    add_item(({"stick", "sticks"}),
        "You see a stick that is straight and round, with no" +
        " knots or other blemishes, jutting out within easy reach" +
        " of your position. It certainly doesn't look strong enough" +
        " to hold your weight, so be careful lest you break it and" +
        " reveal your hiding place!\n");

    add_prop(CONT_I_VOLUME, 1);
    add_prop(CONT_I_WEIGHT, 1);
    add_prop(CONT_I_LIGHT, 1);
    add_prop(CONT_I_MAX_VOLUME, random(100000) + 100000);
    add_prop(CONT_I_MAX_WEIGHT, random(110000) + 110000);
    remove_prop(CONT_I_CLOSED);
    remove_prop(CONT_I_NO_REM);
    remove_prop(CONT_M_NO_REM);
    add_prop(OBJ_M_NO_GET, 1);
    add_prop(OBJ_I_INVIS, "@@am_i_hidden@@");

    }
