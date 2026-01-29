/* a brain (pain in the membrane)
 * coded by Amelia   5/24/97
*/

#pragma strict_types

inherit "/std/food";

#include <stdproperties.h>

private string str;

public void
create_food()
{
    set_name("brain");
    set_adj(str);
    set_short("@@query_what_from");
    set_pshort("@@query_what_from_plural");
    set_long("The brain from a " + "@@query_what_from_long");
    set_amount(20);
    add_prop(OBJ_I_WEIGHT, 500);
    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_VALUE, 20);
}

public string
query_what_from()
{
    return str + " brain";
}

public string
query_what_from_plural()
{
    return str + " brains";
}

public string
query_what_from_long()
{
    return str + ".\n";
}

public int
set_str(string s)
{
    str = s;
    return 1;
}

public void
special_effect(int num_brains)
{
    object tp = this_player();

    if(str == "goblin" || str == "orc" || str == "troll")
    {
        tp->catch_msg("You feel more stupid.\n");
    } else {
        tp->catch_msg("You feel more intelligent.\n");
    }

    return;
}

public int
query_recover()
{
    return 0;
}
