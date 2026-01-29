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
    set_amount(45);
    set_name("cheese");
    set_pname("cheeses");
    add_name(({"hunk"}));
    set_adj(({"winder"}));
    set_short("hunk of winder cheese");
    set_pshort("hunks of winder cheese");
    set_long("This a hunk of wedge cheese renowned for its mildly smoky and "
    + "classic soft cheese taste. It comes from Winder Farms.\n");

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
    if (!str || !parse_command(str, ({}), "[winder] [hunk] [of] 'hunk' / 'cheese'"))
    { return 0; }

    TP->catch_msg("You smell " + short() + ".  The scent of "
    + "mildly smoky and classically soft cheese fills your senses.\n");
    tell_room(E(TP), QCTNAME(TP)+ " lifts " + HIS(TP) + " " + short()
    + " to " + HIS(TP) + " nose sniffing it for a moment as " + PRONOUN(TP)
    + " inhales its scents.\n", ({TO, TP}));
    return 1;
}

void
special_effect(int n)
{
    write("You begin consuming " + short() + ", its dry crumbly "
    + "flavours filling your mouth with the taste of soft, mildly smoky "
    + "cheese.\n");
    tell_room(E(TP), QCTNAME(TP) + " begins consuming " + HIS(TP) + " "
    + short() + ", its flavours spilling into " + HIS(TP) + " mouth and "
    + "filling the air with the scent of Winder cheese.\n", ({TO, TP}));
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
