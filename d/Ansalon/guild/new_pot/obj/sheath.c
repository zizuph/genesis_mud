/* Stralle@Genesis: 010103
 *
 * A knife sheath for the priests.
 */

#pragma strict_types

inherit "/std/container";
inherit "/lib/wearable_item";
inherit "/lib/keep";

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"
#include <macros.h>
#include <wa_types.h>

void
create_container()
{
    set_name("sheath");
    set_adj(({"silver-inlaid", "black"}));
    set_long("This is a black sheath ornamented with silver.\n");

    set_slots(A_WAIST);
    set_keep();

    add_prop(OBJ_I_VALUE, 600);
    add_prop(CONT_I_WEIGHT, 350);
    add_prop(CONT_I_VOLUME, 400);
    add_prop(CONT_I_MAX_VOLUME, 3000);
    add_prop(CONT_I_MAX_WEIGHT, 3000);
}

string
query_recover()
{
    return MASTER;
}

int
prevent_enter(object ob)
{
    return !(ob->check_weapon() && ob->query_wt() == W_KNIFE);
}

void
leave_env(object from, object to)
{
    wearable_item_leave_env(from, to);
    ::leave_env(from, to);
}

int
do_sheathe(string str)
{
    object *knives = filter(TP->query_weapon(-1),
        &operator(==)(W_KNIFE) @ &->query_wt());
    mixed *arr = allocate(2);

    if (str && !parse_command(str, environment(), "[the] %i", arr))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!str && sizeof(knives))
    {
        arr[1] = knives[random(sizeof(knives))];
    }
    else if (arr[0] != 1)
    {
        if ((arr[0] < 0) && (-arr[0] < sizeof(arr)))
            arr[1] = arr[-arr[0]];
        else
        {
            notify_fail(capitalize(query_verb()) + " what?\n");
            return 0;
        }
    }

    if (!arr[1]->check_weapon() && arr[1]->query_wt() != W_KNIFE)
    {
        notify_fail("Nothing larger than a knife would fit.\n");
        return 0;
    }

    if (sizeof(all_inventory()))
    {
        notify_fail("Your " + short() + " already has something in it.\n");
        return 0;
    }
    
    if (arr[1]->move(TO))
    {
        write("The " + arr[1]->short() + " resists your action.\n");
        return 1;
    }
    
    write("You sheathe " + LANG_ADDART(arr[1]->short()) +
        " in your " + short() + ".\n");
    say(QCTNAME(TP) + " sheathes " + LANG_ADDART(arr[1]->short()) +
        " in " + HIS(TP) + " " + short() + ".\n");
    
    return 1;
}

int
do_draw(string str)
{
    object knife;
    mixed *arr;

    if (!str && sizeof(all_inventory()))
    {
        knife = all_inventory()[0];

        write("You draw " + LANG_ADDART(knife->short()) + " from your " +
            short() + ".\n");
        say(QCTNAME(TP) + " draws " + LANG_ADDART(knife->short()) +
            " from " + HIS(TP) + " " + short() + ".\n");

        if (knife->move(TP))
            knife->move(TP, 1);

        /* Try to wield it. */
        knife->wield_me();
        
        return 1;
    }
    else if (str && !parse_command(str, TP, "[the] %i", arr))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    else
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }
    
    if (arr[0] != 1)
    {
        if ((arr[0] < 0) && (-arr[0] < sizeof(arr)))
            arr[1] = arr[-arr[0]];
        else
        {
            notify_fail(capitalize(query_verb()) + " what?\n");
            return 0;
        }
    }
    
    if (!sizeof(all_inventory()))
    {
        notify_fail("But your " + short() + " is empty.\n");
        return 0;
    }
    
    if (arr[1] != all_inventory()[0])
    {
        notify_fail("The " + arr[1]->short() + " is not in your " +
            short() + ".\n");
        return 0;
    }
    
    write("You draw " + LANG_ADDART(arr[1]) + " from " +
        "your " + short() + ".\n");
    say(QCTNAME(TP) + " draws " + LANG_ADDART(arr[1]) +
        " from " + HIS(TP) + " " + short() + ".\n");

    if (arr[1]->move(TP))
        arr[1]->move(TP, 1);

    /* Try to wield it. */
    arr[1]->wield_me();

    return 1;
}

void
init()
{
    ::init();
    
    add_action(do_sheathe, "sheathe");
    add_action(do_draw, "draw");
}
