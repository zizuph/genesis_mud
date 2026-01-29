/* 
 *  /d/Gondor/clubs/nisse/obj/waterskin.c
 *
 *  A waterskin which may be used for carrying a water or another liquid.
 *
 *  Deagol, April 2003
 */

#pragma strict_types
#pragma save_binary

inherit "/d/Calia/gelan/objects/bottle";
inherit "/lib/keep"; 
inherit "/lib/wearable_item";

#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

/*
 *  Prototypes
 */
//int	fill_waterskin(string str);

void 
create_object()
{
    set_name("waterskin");
    add_name("skin");
    set_pname("waterskins");
    add_pname("skins");
    set_adj("medium");
    set_short("medium waterskin");
    set_pshort("medium waterskins");
    set_long("@@my_long@@");
    max_amount = 1500;

    add_prop(OBJ_I_VOLUME, "@@my_volume@@");
    add_prop(OBJ_I_WEIGHT, "@@my_weight@@");
    add_prop(OBJ_I_VALUE,  "@@my_value@@");
    set_keep(1); 

    config_wearable_item(A_R_SHOULDER, 1, 0);
    set_wf(this_object());

    add_item(({"strap", "long strap", "goatskin strap", 
        "long goatskin strap"}), "A long goatskin strap has been " +
        "sewn to either end of the waterskin, allowing it to be worn " +
        "over the shoulder.\n");

    add_prop(OBJ_I_VALUE, 390);
}

/*
 *  Function name: my_long
 *  Description  : Gives a long description of this object. It depends on
 *                 fullness of the waterskin.
 *  Returns      : string with the description
 */
string
my_long()
{
    string text, mix;

    text = "This " + short() + " is made from soft and supple goat skin " +
        "which has been sewn into a teardrop-shaped container. It holds " +
        "enough water for at least a half day's journey and you can " +
        "drink from it or fill or empty it. There is a long goatskin strap " +
        "running from one end of the waterskin to the other, allowing you " +
        "to wear the skin over your shoulder. Right now ";

    if (!soft_amount)
        return text + "it is empty.\n";
  
    if (sizeof(filled_short) == 1)
        mix = filled_short[0];
    else
        mix = "mixture of " + COMPOSITE_WORDS(filled_short);

    if (max_amount > 8 * soft_amount)
        return text + "it contains little of the " + mix + ".\n";

    if (3 * max_amount > 8 * soft_amount)
        return text + "it contains approx one quarter of the " + mix + ".\n";

    if (5 * max_amount > 8 * soft_amount)
        return text + "it contains approx one half of the " + mix + ".\n";

    if (7 * max_amount > 8 * soft_amount)
        return text + "it contains approx three quarters of the "
            + mix + ".\n";

    if (max_amount > soft_amount)
        return text + "it is nearly full of the " + mix + ".\n";

    return text + "it is full of the " + mix + ".\n";
} 

/*
int
fill_waterskin(string str)
{
    if (!strlen(str) || !parse_command(str, ({}),
        "[the] [mediumsized [with] 'water'"))
    {
        notify_fail(CAP(query_verb()) + " what with what?\n", 0);
        return 0;
    }
    
    if (!ENV(TP)->query_prop(OBJ_I_CONTAIN_WATER))
    {
        notify_fail("You search for water to fill a waterskin with, but " +
            "do not find any.\n");
        return 0;
    }
    
    soft_amount = max_amount;
    filled_short += ({ "water" });
    filled_names += ({ "water" });
    write("blah\n");
    return 1;
}


void
init()
{
    ::init();
    
    add_action(fill_waterskin, "fill");
}
*/

int
fill_bottle(string arg)
{
    string arg1, arg2;
    object *a;
    int i;

    NF("Fill what?\n");
    if (!arg)
        return 0;

    if (max_amount == soft_amount)
    {
        notify_fail("The " + short() + " is full.\n");
        return 0;
    }

    if (parse_command(arg, TO, " [the] %o 'with' [the] 'water' ") &&
        (ENV(TO) == TP) &&
        ((ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_IN_WATER) ||
         (ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_UNDER_WATER) ||
         (ENV(TP)->query_prop(ROOM_I_TYPE) == ROOM_BEACH ||
         ENV(TP)->query_prop(OBJ_I_CONTAIN_WATER))))
    {
        set_soft(max_amount);
        if (member_array("water", filled_short) == -1)
            filled_short += ({ "water" });
        if (member_array("water", filled_names) == -1)
            filled_names += ({ "water" });
        write("You fill the "+short()+" with the water.\n");
        say(QCTNAME(TP)+" fills the "+short()+" with the water.\n");
        return 1;
    }

    sscanf(arg, "%s with %s", arg1, arg2);
    if (!arg1)
        arg1 = arg;

    NF("Fill what?\n");
    if (!parse_command(arg1, TO, " [the] %o "))
        return 0;

    NF("Fill "+short()+" with what?\n");
    if(!arg2)
        return 0;

    a = CMDPARSE_ONE_ITEM(arg2, "fill_one_thing", "drink_access");
    if (sizeof(a) > 0)
    {
        write("You fill the "+short()+" with "+COMPOSITE_DEAD(a)+".\n");
        say(QCTNAME(TP)+" fills the "+short()+" with "+QCOMPDEAD+".\n");
        for (i = 0; i < sizeof(a); i++)
            a[i]->remove_drink();
        return 1;
    }

    if (sizeof(gFail))
        NF("@@fill_fail:" + file_name(TO));

    return 0;
}

/*
 *  Function name: leave_env
 *  Description  : We must redefine this function to ensure that the waterskin
 *                 is removed when it is dropped while we wear it.
 *  Arguments    : object env - the environment we leave.
 *                 object to  - the environment we enter.
 */
public void
leave_env(object env, object to)
{
    ::leave_env(env, to);

    wearable_item_leave_env(env, to);
}
