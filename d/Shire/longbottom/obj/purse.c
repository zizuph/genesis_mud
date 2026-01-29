/*
 * /d/Shire/longbottom/obj/purse.c
 *
 * Money and gem purse
 * Based on coin pouch from Gondor
 * -- Finwe, December 2019
 */
 
#include <stdproperties.h>
#include <macros.h>
#include <files.h>
#include <cmdparse.h>
#include <composite.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

inherit "/d/Genesis/std/pack.c";
inherit "/lib/keep.c";

public string short_description();
public string long_description();

#define NO_SELL_PROP "The purse is tied to your belt! It cannot be sold!\n"
#define NO_DROP_PROP obj_m_no_drop

#define PURSE_O_SUBLOC         "purse_o_subloc"
#define LIVE_AO_PURSE_SUBLOC   "_live_ao_purse_subloc"

static int     gPropAid;

void create_pack() {

    set_name("purse");
    set_adj("leather");
    set_short(short_description);
    set_pshort("leather pursees");
    set_long(long_description);

    add_prop(CONT_I_CLOSED, 0);
    add_prop(CONT_I_IN, 1);
    add_prop(CONT_I_RIGID, 0);
    add_prop(CONT_I_TRANSP, 0);
    add_prop(CONT_I_WEIGHT, 200);
    add_prop(CONT_I_VOLUME, 200);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(OBJ_I_VALUE, 72);
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    
    set_mass_storage(1);
}

string short_description()
{
    if (sizeof(all_inventory(TO)))
        return "leather purse containing money";

    return "leather purse";
}

string long_description()
{
    string long_desc = "This is a leather purse to store money in. ";

    if (query_prop(OBJ_M_NO_SELL))
        long_desc += " At present, the purse is tied to your belt.\n";
    else
        long_desc += " It is possible to tie the purse to your belt "
	    + "to prevent it from being stolen or inadvertently sold.\n";
        
    long_desc += "You can <fill> or <empty> the purse.";
    return (long_desc + "\n");
}

string query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}

public int
prevent_enter(object obj)
{
    if (!IS_COINS_OBJECT(obj))
    {
        write("You can only put coins in the " + query_name() + ".\n");
        return 1;
    }

    return 0;
}

mixed obj_m_no_drop()
{
    /* Allow dropping when the player quits, or when he dies. The ghost property
     * is not set yet when the dropping occurs. */
    if ((query_verb() == "quit") ||
        (environment()->query_hp() <= 0))
    {
        return 0;
    }

    return "The purse is tied to your belt! It cannot be dropped!\n";
}

void
tie()
{
    object *purse_cont, tp = environment(TO);

    tp->add_subloc(PURSE_O_SUBLOC, TO);
    purse_cont = tp->query_prop(LIVE_AO_PURSE_SUBLOC);
    if (pointerp(purse_cont))
        purse_cont -= ({ 0 });
    else
        purse_cont = ({ });
    purse_cont += ({ TO });
    tp->add_prop(LIVE_AO_PURSE_SUBLOC, purse_cont);
    write("You tie the " + query_name() + " to your belt, to remind "
        + "yourself not to sell it, and to protect it from thieves "
        + "(but of course not from cutpurses).\n");
    say(QCTNAME(tp) + " ties " + LANG_ADDART(query_name()) + " to "
        + POSSESSIVE(tp) + " belt.\n");
}

public void
untie()
{
    int ipurse;
    object tp = TP, *purse_cont;

    purse_cont  = tp->query_prop(LIVE_AO_PURSE_SUBLOC);
    if (pointerp(purse_cont))
        purse_cont -= ({ 0 });
    else
        purse_cont = ({ });

    if ((ipurse = member_array(TO, purse_cont)) > -1)
        purse_cont = exclude_array(purse_cont, ipurse, ipurse);

    if (sizeof(purse_cont))
        tp->add_prop(LIVE_AO_PURSE_SUBLOC, purse_cont);
    else
    {
        tp->remove_prop(LIVE_AO_PURSE_SUBLOC);
        tp->remove_subloc(PURSE_O_SUBLOC);
    }

    write("You untie the " + query_name() + " from your belt.\n");
    say(QCTNAME(tp) + " unties " + LANG_ADDART(query_name())
        + " from " + POSSESSIVE(tp) + " belt.\n");
}

public void
set_keep(int keep = 1)
{
    if (keep)
    {
    	add_prop(OBJ_M_NO_SELL, NO_SELL_PROP);
    	add_prop(OBJ_M_NO_DROP, NO_DROP_PROP);
    }
    else
    {
    	remove_prop(OBJ_M_NO_SELL);
    	remove_prop(OBJ_M_NO_DROP);
    }
}

void init_recover(string arg)
{
    init_container_recover(arg);
    init_keep_recover(arg);
    
    if (query_prop(OBJ_M_NO_SELL))
        set_alarm(0.2, 0.0, &tie());    
}

public int
do_tie(string str)
{
    object *objs, tp = TP, *purse_cont;
    string vb = query_verb();

    if (!strlen(str) || (ENV(TO) != tp))
    {
        notify_fail(CAP(vb) + " what?\n");
        return 0;
    }

    if (!parse_command(LOW(str), all_inventory(tp),
      "%i [onto] [to] [from] [the] [my] [belt]", objs))
    {
        notify_fail(CAP(vb) + " what?\n");
        return 0;
    }

    objs = NORMAL_ACCESS(objs, 0, 0);

    if (!sizeof(objs))
    {
        notify_fail(CAP(vb) + " what?\n");
        return 0;
    }

    if (member_array(TO, objs) < 0)
    {
        notify_fail(CAP(vb) + " what?\n");
        return 0;
    }

    if (query_prop(OBJ_M_NO_SELL))
    {
        if (vb == "tie")
        {
            notify_fail("The purse is already tied to your belt.\n");
            return 0;
        }

        set_keep(0);
        untie();
    }
    else
    {
        if (vb == "untie")
        {
            notify_fail("The purse is already untied.\n");
            return 0;
        }

        set_keep(1);
        tie();
    }

    return 1;
}

public string
show_subloc(string subloc, object me, object for_obj)
{
    object *items = ({ });
    string desc, his;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";
 
    if (subloc != PURSE_O_SUBLOC)
        return me->show_subloc(subloc, me, for_obj);

    if (for_obj == me)
    {
        desc = "You have ";
        his  = "your";
    }
    else
    {
        // If a robe is worn, what is tied to the belt is concealed.
        if (objectp(me->query_armour(A_ROBE)))
            return "";
        desc = CAP(PRONOUN(me)) + " has ";
        his = POSSESSIVE(me);
    }

    items += me->query_prop(LIVE_AO_PURSE_SUBLOC);
    items -= ({ 0 });
    desc += COMPOSITE_DEAD(items);
    desc += " tied to " + his + " belt.\n";
    return desc;
}

public string query_auto_load()
{
    mixed setting;

    if (setting = query_prop_setting(OBJ_M_NO_DROP))
    {
        remove_prop(OBJ_M_NO_DROP);
        gPropAid = set_alarm(0.5, 0.0, &add_prop(OBJ_M_NO_DROP, setting));
    }

    return 0;
}

public void leave_env(object old, object dest)
{
    int ipurse;
    object *purse_cont;

    ::leave_env(old, dest);

    if (!objectp(old) || !living(old) || !query_prop(OBJ_M_NO_SELL))
	return;

    remove_prop(OBJ_M_NO_SELL);
    remove_prop(OBJ_M_NO_DROP);
    remove_alarm(gPropAid);
    purse_cont = old->query_prop(LIVE_AO_PURSE_SUBLOC);
    if ((ipurse = member_array(TO, purse_cont)) > -1)
        purse_cont = exclude_array(purse_cont, ipurse, ipurse);
    if (sizeof(purse_cont))
        old->add_prop(LIVE_AO_PURSE_SUBLOC, purse_cont);
    else
    {
        old->remove_prop(LIVE_AO_PURSE_SUBLOC);
        old->remove_subloc(PURSE_O_SUBLOC);
    }
}

public void
init()
{
    ::init();

    add_action(do_tie, "tie");
    add_action(do_tie, "untie");

    remove_name("pack");
}

int item_filter(object obj) {
    return IS_HERB_OBJECT(obj);
}

int sort_objects_by_short(object *a, object *b)
{
    string aname = a[0]->query_coin_name ();
    string bname = b[0]->query_coin_name ();

    if (aname < bname) return (-1);
    if (aname > bname) return (1);
    return 0;
}

void describe_coins(object *coins, object for_obj)
{
    if (sizeof(coins) == 0) return;
    
    int quantity = 0;
    foreach(object coin : coins) quantity += coin->num_heap() || 1;

    string coin_description = coins[0]->singular_short();
    string coin_name = coins[0]->do_id_check(for_obj) 
        ? coins[0]->query_coin_name() : "";
    
//    for_obj->catch_tell(sprintf("| %-:39s | %-:19s | %5d |\n",
//        coin_description, coin_name, quantity));

    for_obj->catch_tell(sprintf("| %,5d | %-:20s | %-:43s |\n",
        quantity, coin_name, coin_description));
}

void describe_contents(object for_obj, object *obarr)
{
    if (sizeof(obarr) == 0)
    {
        for_obj->catch_tell("  " + "The " + this_object()->short() +
            " is empty.\n");
        return;
    }

    mixed *sorted_objects = sort_array(unique_array(obarr, "query_coin_name"), 
        sort_objects_by_short);
    
    for_obj->catch_tell(
"+----------------------------------------------------------------------------+\n" +
"| Qty   | Herb Name            | Description                                 |\n" +
"|=======+======================+=============================================|\n"
);
    
    foreach(object *coins : sorted_objects) {
        describe_coins(coins, for_obj);
    }    
    
    for_obj->catch_tell(
"+----------------------------------------------------------------------------+\n");
}

