/*
 * rabbit's foot
 * coded for Tenalders, Amelia, 9/14/97
 * used for herb witch's 'lucky items' quest
*/

#pragma strict_types

inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

public void
create_object()
{
    set_name("_lucky_rabbits_foot_");
    add_name("foot");
    add_name("rabbit's foot");
    add_adj("fuzzy");
    add_adj("white");
    add_adj("rabbit's");
    set_pname("feet");
    set_short("fuzzy white rabbit's foot");
    set_pshort("fuzzy white rabbit's feet");
    set_long("A small foot taken from a white " +
        "fuzzy rabbit. There is an old superstition that you " +
        "can rub a rabbit's foot for good luck.\n");
    add_prop(OBJ_I_WEIGHT, 200);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 25);
}

public int
query_lucky_foot()
{
    return 1;
}

public int
rub_foot(string str)
{
    object tp = this_player();

    if(environment() != tp)
    {
        return notify_fail("You do not have the rabbit's foot!\n");
    }

    if(id(str))
    {
        write("You rub the rabbit's foot and feel this " +
            "could be your lucky day!\n");
        tell_room(environment(tp), QCTNAME(tp) + " rubs something " +
            "that " + tp->query_pronoun() + " is holding in " +
            tp->query->possessive()+ " hands.\n", ({ tp }));
        return 1;
    }

    return notify_fail("Rub what?\n");
}

public void
init()
{
    ::init();
    add_action(rub_foot, "rub");
}
