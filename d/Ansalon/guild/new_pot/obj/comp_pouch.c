/*
 * Component pouch
 *
 * Ashlar, 01 Jul 98
 *
 * Tie code by Stralle @ Genesis on some unknown date in 2001.
 * Removed decay code by Mercade, 21 May 2004
 */

inherit "/std/receptacle";
inherit "/lib/keep";
// wearable item also!

#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include <cmdparse.h>
#include "/d/Ansalon/common/defs.h"
#include "../guild.h"

#define OBJ_I_TIED  "_my_obj_i_tied"

object *gHerbs;
int gAlarm;

void
create_receptacle()
{
    set_name("pouch");
    set_pname("pouches");
    
    set_adj("soft");
    add_adj("leather");

    set_short("soft leather pouch");
    set_pshort("soft leather pouches");

    set_long("It is a soft leather pouch, ideal for holding " +
    "spell components.\n");

    add_prop(OBJ_I_VALUE, 100);
    add_prop(CONT_I_WEIGHT, 150);
    add_prop(CONT_I_VOLUME, 100);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    remove_prop(CONT_I_RIGID);

    add_prop(CONT_I_HOLDS_COMPONENTS, 1);

    set_keep(1);
}

int
prevent_enter(object ob)
{
    return !(IS_HERB_OBJECT(ob) || IS_LEFTOVER_OBJECT(ob) || IS_COINS_OBJECT(ob) || ob->is_ritual_object());
}

void
leave_env(object from, object to)
{
    if (living(from))
    {
        if (query_prop(OBJ_I_TIED))
        {
            from->catch_tell("You untie your " + short() + " before " +
                "putting it away.\n");
            remove_prop(OBJ_I_TIED);
        }
    }

    ::leave_env(from, to);
}

string
query_recover()
{
    return MASTER + ":" + query_keep_recover() + query_container_recover();
}

void
init_recover(string arg)
{
    init_keep_recover(arg);
    init_container_recover(arg);
}

int
do_tie(string str)
{
    mixed *arr = allocate(2);

    if (!str)
    {
        notify_fail("Tie what?\n");
        return 0;
    }
    
    if (!parse_command(str, environment(), "[the] %i", arr))
    {
        notify_fail("Tie what?\n");
        return 0;
    }
    
    if (arr[0] != 1)
    {
        if ((arr[0] < 0) && (-arr[0] < sizeof(arr)))
            arr[1] = arr[-arr[0]];
        else
        {
            notify_fail("Tie what?\n");
            return 0;
        }
    }
    
    if (arr[1] != TO)
    {
        notify_fail("Tie what?\n");
        return 0;
    }

    if (arr[1]->query_prop(OBJ_I_TIED))
    {
        write("But the " + arr[1]->short() + " is already tied.\n");
        return 1;
    }
    
    write("You tie your " + arr[1]->short() + " in your belt.\n");
    say(QCTNAME(TP) + " ties " + HIS(TP) + " " + arr[1]->short() +
        " to " + HIS(TP) + " belt.\n");
        
    arr[1]->add_prop(OBJ_I_TIED, 1);
    arr[1]->add_prop(OBJ_M_NO_STEAL, "The " + arr[1]->short() +
        " is tied to a belt.\n");
    return 1;
}
    
int
do_untie(string str)
{
    mixed *arr = allocate(2);

    if (!str)
    {
        notify_fail("Untie what?\n");
        return 0;
    }
    
    if (!parse_command(str, environment(), "[the] %i", arr))
    {
        notify_fail("Untie what?\n");
        return 0;
    }
    
    if (arr[0] != 1)
    {
        if ((arr[0] < 0) && (-arr[0] < sizeof(arr)))
            arr[1] = arr[-arr[0]];
        else
        {
            notify_fail("Untie what?\n");
            return 0;
        }
    }
    
    if (arr[1] != TO)
    {
        notify_fail("Untie what?\n");
        return 0;
    }

    if (!arr[1]->query_prop(OBJ_I_TIED))
    {
        write("But your " + arr[1]->short() + " has not been " +
            "previously tied to your belt.\n");
        return 1;
    }

    write("You untie your " + arr[1]->short() + " from your belt.\n");
    say(QCTNAME(TP) + " unties " + HIS(TP) + " " + arr[1]->short() +
        " from " + HIS(TP) + " belt.\n");
        
    arr[1]->remove_prop(OBJ_I_TIED);
    arr[1]->remove_prop(OBJ_M_NO_STEAL);

    return 1;
}

int
reject_me(object ob, object env)
{
    return (ob->move(env) == 0);
}

void
check_lasting(object ob, object env)
{
    if (ob->check_recoverable())
        return;
    if (ob->query_auto_load())
        return;
    
    reject_me(ob, env);
}

int
do_hsort(string arg)
{
    object *ob;
    
    if (!stringp(arg) || !parse_command(arg, environment(this_player()), "[the] %i", ob))
    {
        notify_fail("Sort what?\n");
        return 0;
    }

    ob = NORMAL_ACCESS(ob, 0, 0);

    if (sizeof(ob) > 1)
    {
        notify_fail("Sorting is a practice best done with one object at a time.\n");
        return 0;
    }

    if (!sizeof(ob) || ob[0] != this_object())
    {
        notify_fail("Sort what?\n");
        return 0;
    }

    /* This rather nifty line borrowed from the Shire herbjar
     */
    map(all_inventory(this_object()),
        &check_lasting(,environment(this_object())));
    write("You remove non-glowing herbs from the " + ob[0]->short() + ".\n");
    return 1;
}

void
init()
{
    ::init();
    
    add_action(do_tie, "tie");
    add_action(do_untie, "untie");
    add_action(do_hsort, "hsort");
    add_action(do_hsort, "sort");
}
