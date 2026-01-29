/*
 *  /d/Gondor/common/obj/herbpouch.c
 *
 *  Common herb pouch for usage within Middle Earth. 
 *
 *  Created by Eowul, Februari 2009
 *  Based upon the various pouches found with the Shire/Gondor
 *  Especially /d/Gondor/common/guild/obj/herbpouch.c
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

#define NO_SELL_PROP "The pouch is tied to your belt! It cannot be sold!\n"
#define NO_DROP_PROP obj_m_no_drop

#define BELT_O_SUBLOC         "belt_o_subloc"
#define LIVE_AO_BELT_SUBLOC   "_live_ao_belt_subloc"

static int     gPropAid;

void create_pack() {

    set_name("pouch");
    set_adj("leather");
    set_short(short_description);
    set_pshort("leather pouches");
    set_long(long_description);

    add_prop(CONT_I_CLOSED, 1);
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
        return "leather pouch containing herbs";

    return "leather pouch";
}

string long_description()
{
    string long_desc = "This is a leather pouch to store herbs in. ";

    if (query_prop(OBJ_M_NO_SELL))
        long_desc += " At present, the pouch is tied to your belt.\n";
    else
        long_desc += " It is possible to tie the pouch to your belt "
	    + "to prevent it from being stolen or inadvertently sold.\n";
        
    long_desc += "You can <fill> or <empty> the pouch.";
    return (long_desc + "\n");
}

string query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}

public int
prevent_enter(object obj)
{
    if (!IS_HERB_OBJECT(obj))
    {
        write("You can only put herbs in the " + query_name() + ".\n");
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

    return "The pouch is tied to your belt! It cannot be dropped!\n";
}

void
tie()
{
    object *belt_cont, tp = environment(TO);

    tp->add_subloc(BELT_O_SUBLOC, TO);
    belt_cont = tp->query_prop(LIVE_AO_BELT_SUBLOC);
    if (pointerp(belt_cont))
        belt_cont -= ({ 0 });
    else
        belt_cont = ({ });
    belt_cont += ({ TO });
    tp->add_prop(LIVE_AO_BELT_SUBLOC, belt_cont);
    write("You tie the " + query_name() + " to your belt, to remind "
        + "yourself not to sell it, and to protect it from thieves "
        + "(but of course not from cutpurses).\n");
    say(QCTNAME(tp) + " ties " + LANG_ADDART(query_name()) + " to "
        + POSSESSIVE(tp) + " belt.\n");
}

public void
untie()
{
    int ibelt;
    object tp = TP, *belt_cont;

    belt_cont  = tp->query_prop(LIVE_AO_BELT_SUBLOC);
    if (pointerp(belt_cont))
        belt_cont -= ({ 0 });
    else
        belt_cont = ({ });

    if ((ibelt = member_array(TO, belt_cont)) > -1)
        belt_cont = exclude_array(belt_cont, ibelt, ibelt);

    if (sizeof(belt_cont))
        tp->add_prop(LIVE_AO_BELT_SUBLOC, belt_cont);
    else
    {
        tp->remove_prop(LIVE_AO_BELT_SUBLOC);
        tp->remove_subloc(BELT_O_SUBLOC);
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
    object *objs, tp = TP, *belt_cont;
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
            notify_fail("The pouch is already tied to your belt.\n");
            return 0;
        }

        set_keep(0);
        untie();
    }
    else
    {
        if (vb == "untie")
        {
            notify_fail("The pouch is already untied.\n");
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
 
    if (subloc != BELT_O_SUBLOC)
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

    items += me->query_prop(LIVE_AO_BELT_SUBLOC);
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
    int ibelt;
    object *belt_cont;

    ::leave_env(old, dest);

    if (!objectp(old) || !living(old) || !query_prop(OBJ_M_NO_SELL))
	return;

    remove_prop(OBJ_M_NO_SELL);
    remove_prop(OBJ_M_NO_DROP);
    remove_alarm(gPropAid);
    belt_cont = old->query_prop(LIVE_AO_BELT_SUBLOC);
    if ((ibelt = member_array(TO, belt_cont)) > -1)
        belt_cont = exclude_array(belt_cont, ibelt, ibelt);
    if (sizeof(belt_cont))
        old->add_prop(LIVE_AO_BELT_SUBLOC, belt_cont);
    else
    {
        old->remove_prop(LIVE_AO_BELT_SUBLOC);
        old->remove_subloc(BELT_O_SUBLOC);
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
    string aname = a[0]->query_short ();
    string bname = b[0]->query_short ();

    if (aname < bname) return (-1);
    if (aname > bname) return (1);
    return 0;
}

void describe_herbs(object *herbs, object for_obj)
{
    if (sizeof(herbs) == 0) return;
    
    int quantity = 0;
    foreach(object herb : herbs) quantity += herb->num_heap() || 1;

    string herb_description = herbs[0]->singular_short();
    string herb_name = herbs[0]->do_id_check(for_obj) 
        ? herbs[0]->query_herb_name() : "";
    
    for_obj->catch_tell(sprintf("| %-:39s | %-:19s | %5d |\n",
        herb_description, herb_name, quantity));
}

void describe_contents(object for_obj, object *obarr)
{
    if (sizeof(obarr) == 0)
    {
        for_obj->catch_tell("  " + "The " + this_object()->short() +
            " is empty.\n");
        return;
    }

    mixed *sorted_objects = sort_array(unique_array(obarr, "query_herb_name"), 
        sort_objects_by_short);
    
    for_obj->catch_tell(
        "+-----------------------------------------------------------------------+\n"
      + "| Herb                                    | Name                | Qty   |\n"
      + "|                                         |                     |       |\n");
    
    foreach(object *herbs : sorted_objects) {
        describe_herbs(herbs, for_obj);
    }    
    
    for_obj->catch_tell(
        "+-----------------------------------------------------------------------+\n");
}

