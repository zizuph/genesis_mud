/* File:          /d/Khalakhor/std/obj/tree.c
 * Creator:       Teth
 * Date:          March 10, 1998
 * Modifications:
 * Purpose:       The tree is inheritable, and is to be used when
 *                more detail is wanted in a forest.
 * Related Files: 
 * Comments:      should be climbable
 *                lean on it emote
 *                emote scratch one's back
 *                emote talk to it
 *                emote carve into it (if the person has a knife),
 *                restrict this to the person's name, can't allow
 *                just any name
 *                emote piss on it
 *                search for herbs
 *                be really daring, allow people to shoot from above
 *                to the ground below
 *                should be easy to hide in
 *                what kind of terrain type tho???
 *                should be able to chop it down (if the person has an axe)
 *                chopping it should leave wood chips
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Khalakhor/sys/defs.h"
#include "/d/Khalakhor/sys/paths.h"

string query_tree_name();
string set_tree_name(string str);
string Treename;
void set_up_tree();


public void
create_tree()
{
}

public void
create_object()
{
    set_name("tree");
    set_adj("base");
    set_short("base tree");
    set_long("This is the base tree.\n");

    add_prop(OBJ_M_NO_GET, "The tree is firmly rooted in the " +
        "ground, and you are unable to remove it from its earthly " +
        "home.\n");

    seteuid(getuid(this_object());

    create_tree();
}

public string
query_tree_name()
{
    return Treename;
}

public string
set_tree_name(string str);
{
    Treename = str;
}


public void
set_up_tree()
{
    switch(Treename)
    {
      case "oak"
      break;
      case default:
      break;
    }
}

public void
init()
{
    add_action("do_break","break");
    ::init();
}

public int
do_break(string str)
{
}
