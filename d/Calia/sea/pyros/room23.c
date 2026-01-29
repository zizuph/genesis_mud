
 /* Digit 03 FEB 95 */

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <ss_types.h>
#include "defs.h"
#include FIRE_HEADER
#include "obsidian.h"


void
create_room()
{
    set_short("In a warm tunnel");
#include "desc2.h"

    add_exit(CAVE+"room22","north");
    add_exit(CAVE+"room24","west","@@go_west",1,"@@see_west");
    add_exit(CAVE+"room25","south");
}

int
go_west()
{
    if (TP->query_prop(I_SEE_WEST_EXIT))
    {
        write("You press on the west wall and end up falling through it.\n");
        return 0;
    }
    else
    if (TP->query_skill(SS_AWARENESS) > 65)
    {
        write("You press on the west wall and end up falling through it.\n");
        return 0;
    }
    write("There is something strange about the west wall, but you "+
        "just can't quite put your finger on it.\n");
    return 1;
}
int
see_west()
{
    if (TP->query_prop(I_SEE_WEST_EXIT))
        return 0;
    if (TP->query_skill(SS_AWARENESS) > 65)
        return 0;
    else
        return 1;
}

int
do_show(string str)
{
    object *target;
    int i;
    if (!str || str == "")
        return 0;
    if (!parse_command(str, all_inventory(environment(this_player())), "%l", target) || !sizeof(target = NORMAL_ACCESS(target - ({this_player()}), 0, 0)))
        return 0;
    else
    for (i=0; i < sizeof(target); i++)
    {
        target[i]->catch_tell(TP->query_The_name(target[i])+" shows you that the "+
            "west wall is actually an illusion.\n");
        target[i]->add_prop(I_SEE_WEST_EXIT,1);
    }
    write("You reveal the west wall as illusionary.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action("do_show","show");
    add_action("do_collect","collect");
}
