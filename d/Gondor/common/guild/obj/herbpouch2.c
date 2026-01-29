/*
 * A leather pouch to contain herbs in.
 *
 * Coded by Lord Elessar Telcontar.
 *
 * Revision history:
 * /Mercade, 23 November 1993, changed it from container to /std/receptacle
 * /Mercade, 7 January 1994, fixed recovery of the pouch.
 * Olorin, 8-feb-96: added protection against stealing
 * Olorin, 11-feb-96: pouches will add a subloc if tied to the belt
 * Olorin, 14-Feb-97: Fixed message and move error when trying to insert
 *                    non-herb objects, following example by Khail in herbjar.
 * Gnadnar, 21-Feb-98: inherit /lib/keep
 * Gwyneth, 04-Nov-03: Made the pouch add the subloc upon recovery if tied.
 *                     Cleaned up.
 * Gwyneth, 20-Nov-03: Made entering and leaving more efficient to try to
 *                     prevent so many runtimes.
 * Palmer,  01-Mar-04: Added 'hsort pouch' to remove non-glowing herbs.
 *                     Thanks to Lilith for the nifty functions.
 * Mercade, 21 May 2004; removed decay related code.
 */
inherit "/std/receptacle.c";
inherit "/lib/keep.c";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"

#define NO_SELL_PROP "The pouch is tied to your belt! It cannot be sold!\n"
#define NO_DROP_PROP "The pouch is tied to your belt! It cannot be dropped!\n"

#define BELT_O_SUBLOC         "belt_o_subloc"
#define LIVE_AO_BELT_SUBLOC   "_live_ao_belt_subloc"

public int     do_tie(string str);
public string  short_func();
public string  long_func();

static int     gPropAid;

public void
create_container()
{
    set_name("pouch");
    set_adj("leather");
    set_short(short_func);
    set_pshort("leather pouches");
    set_long(long_func);

    add_prop(CONT_I_CLOSED,        1);
    add_prop(CONT_I_IN,            1);
    add_prop(CONT_I_RIGID,         0);
    add_prop(CONT_I_TRANSP,        0);
    add_prop(CONT_I_WEIGHT,      200);
    add_prop(CONT_I_VOLUME,      200);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(OBJ_I_VALUE,         72);

    /* some herbs are spell components */
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
}

/* Function name: prevent_enter
 * Description  : Checks that it is an herb.
 * Arguments    : object obj - the object entering
 * Returns      : 1 if it is not an herb, 0 if it is
 */
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

/* Function name: short_func
 * Description  : Returns a string for the short description depending
 *                on whether or not there are herbs in the pouch.
 * Returns      : string description
 */
string
short_func()
{
    if (sizeof(all_inventory(TO)))
        return "leather pouch containing herbs";

    return "leather pouch";
}

/* Function name: long_func
 * Description  : Returns a string for the long description depending
 *                on whether or not the pouch is tied to your belt.
 * Returns      : string description
 */
public string
long_func()
{
    string long_desc = "This is a leather pouch to store herbs in. " +
      "You can <hsort pouch> to remove non-glowing herbs.";

    if (query_prop(OBJ_M_NO_SELL))
        long_desc += " At present, the pouch is tied to your belt.";
    else
        long_desc += " It is possible to tie the pouch to your belt "
	    + "to prevent it from being stolen or inadvertently sold.";
    return (long_desc + "\n");
}

/* Function name: query_recover
 * Description  : Allows open/closed props and kept status to be
 *                saved through recovery.
 * Returns      : A string with the status.
 */
string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
}

/* Function name: tie
 * Description  : Ties the pouch to the belt, adds a subloc to the player.
 */
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

/* Function name: untie
 * Description  : Unties the pouch from the belt and removes the subloc.
 */
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

/* Function name: init_recover
 * Description  : Initiates the open/closed and kept status. Calls tie
 *                if the pouch was tied before recovery.
 * Arguments    : The recover string
 */
void
init_recover(string arg)
{
    init_container_recover(arg);
    init_keep_recover(arg);
    if (query_prop(OBJ_M_NO_SELL))
        set_alarm(0.2, 0.0, &tie());
}

/* Function name: do_tie
 * Description  : Handles an attempt to tie/untie the pouch to/from the belt.
 * Arguments    : The string entered by the player.
 * Returns      : 1/0 success/failure 
 */
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

/*
 * Function name: show_subloc
 * Description  : This function is called each time someone looks at us
 * Arguments    : subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns      : The string the looker shall see
 */
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

/*
 * Function name: query_auto_load
 * Description:   remove the OBJ_M_NO_DROP property if it is set
 *                so the pouch and its contents are not lost
 *                when a player logs out.
 * Returns:       0
 */
public string
query_auto_load()
{
    mixed setting;

    if (setting = query_prop_setting(OBJ_M_NO_DROP))
    {
        remove_prop(OBJ_M_NO_DROP);
        gPropAid = set_alarm(0.5, 0.0, &add_prop(OBJ_M_NO_DROP, setting));
    }

    return 0;
}

/*
 * Function name: leave_env
 * Description  : Masks leave_env to remove the no-sell and no-drop
 *                props as well as the subloc if the pouch manages
 *                to leave the inventory, despite being no-drop.
 * Arguments    : object old  - the location we are leaving
 *                object dest - the destination we are going to
 */
public void
leave_env(object old, object dest)
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

/*
 * Function name: set_keep
 * Description  : Mask parent in order to set or remove the 'keep'
 *                protection of the pouch. If no argument is passed to the
 *                function, the default will be 1 - i.e. set the 'keep'
 *                protection. Keepable also means not droppable in this
 *                case, since the pouch is tied to the player's belt.
 * Arguments    : int 1 - set the 'keep' protection.
 *                    0 - remove the 'keep' protection.
 */
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

/*
 * Function name: reject_me
 * Description  : Move item to environment
 * Returns      : 1 = success  0 = fail
 */
int
reject_me(object ob, object env)
{
    if (ob->move(env) == 0) 
    {  
        //write("You remove "+ LANG_THESHORT(ob) +" from " + 
        //    LANG_THESHORT(this_object()) + ".\n"); 
        return 1; 
    } 
    return 0; 
}

/*
 * Function name: check_lasting
 * Description  : check to see if item is recoverable or autoloading
 */
void
check_lasting(object ob, object env)
{
    if (ob->check_recoverable()) 
        return;
    if (ob->query_auto_load())
        return;
    else
        reject_me(ob, env);
}

/*
 * Function name: do_sort
 * Description  : runs inventory through check_lasting.
 */
void
do_sort()
{
    map(all_inventory(this_object()), 
         &check_lasting(,environment(this_object()))); 
}

/*
 * Function name: start_sort
 * Description  : 
 */
int
start_sort(string arg)
{
    object *ob;

    if (!stringp(arg))
    {
        notify_fail("Sort what?\n");
        return 0;
    }
    
    if (!parse_command(arg, deep_inventory(ENV(TP)), "%i"))
    {
        notify_fail("Sort what?\n");
        return 0;
    }
    
    dump_array(ob);
    ob = NORMAL_ACCESS(ob, 0, 0);
    if (!sizeof(ob) || member_array(TO, ob) == -1)
    {
        notify_fail("You can't find anything to sort.\n");
        return 0;
    }

    do_sort();       
    write("You remove non-glowing herbs from the " + short() + ".\n");
    return 1;
}



/* Function name: init
 * Description  : Masks init to add tie and untie verbs.
 */
public void
init()
{
    ::init();

    add_action(do_tie, "tie");
    add_action(do_tie, "untie");
    add_action(start_sort, "hsort");    
}






