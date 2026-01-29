/*
 * Food available from the Draft Pub in the Tower of Arms in Palanthas.
 *
 * Mortis 09.2014
 */

#pragma save_binary
#pragma strict_types

#include <macros.h>
#include <composite.h>
#include "../../../local.h"

inherit "/std/food.c";
inherit "/lib/keep";

public void
create_food()
{
    set_amount(65);
    set_name("bread");
    set_pname("breads");
    add_name(({"roll", "rolls"}));
    set_adj(({"twisted"}));
    set_short("twisted bread roll");
    set_pshort("twisted bread roll");
    set_long("This a golden brown roll of twisted bread, fresh baked on Winder "
    + "farms. It smells like it just came out of the oven.\n");

}

void
init()
{
    ::init();
    ADA("smell");
}

int
smell(string str)
{
    if (!str || !parse_command(str, ({}), "[twisted] 'bread' / 'roll'"))
    { return 0; }

    TP->catch_msg("You smell " + short() + ".  The scent of "
    + "fresh baked, hearty bread fills your senses.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " " + short()
    + " to " + HIS(TP) + " nose sniffing it for a moment as " + PRONOUN(TP)
    + " inhales its scents.\n", ({TO, TP}));
    return 1;
}

void
special_effect(int n)
{
    write("You begin consuming " + short() + ", its fresh, yeasty "
    + "flavours filling your mouth with the taste of a hot roll of "
    + "bread that just came out of the oven.\n");
    tell_room(E(TP), QCTNAME(TP) + " begins consuming " + HIS(TP) + " "
    + short() + ", its flavours spilling into " + HIS(TP) + " mouth and "
    + "filling the air with the scent of fresh baked bread.\n", ({TO, TP}));
}

string
query_recover()
{
    return MASTER + ":" + query_keep_recover();
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
}
