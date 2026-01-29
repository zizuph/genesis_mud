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
 * Modified for the Lich Priesthood of the Khiraa, Sarr
 * Modified by Toby, 971007 (fixed a linebreak when already tied to belt)
 */

#pragma save_binary
#pragma strict_types

inherit "/std/receptacle.c";

#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Kalad/defs.h"

#define NO_SELL_PROP	"The pouch is tied to your belt! It cannot be sold!\n"
#define NO_DROP_PROP	"The pouch is tied to your belt! It cannot be dropped!\n"
#define BELT_O_SUBLOC	"belt_o_subloc"
#define LIVE_AO_BELT_SUBLOC	"_live_ao_belt_subloc"


public int     do_keep(string str);
static mixed   check_insert();
public string  short_func();
public string  long_func();

static int     Prop_Aid;

public void
create_container()
{
    set_name("pouch");
    set_adj("leather");
    add_adj("black");
    set_short(short_func);

    set_pshort("black leather pouches");
    set_long(long_func);

    add_prop(CONT_I_IN,            1);
    add_prop(CONT_I_RIGID,         0);
    add_prop(CONT_I_TRANSP,        0);
    add_prop(CONT_I_WEIGHT,      200);
    add_prop(CONT_I_VOLUME,      200);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 5000);
    add_prop(OBJ_I_VALUE,         72);

    add_prop(CONT_M_NO_INS, check_insert);
}

static mixed
check_insert()
{
    int     i = 1;
    object  obj;

    while (objectp(obj = previous_object(--i)))
    {
        if (obj == TO)
	{
	    if (IS_HERB_OBJECT(previous_object(i-1)))
		return 0;
	    else
		return "You can only put herbs in the "+query_name()+".\n";
	}
    }
    return "You can only put herbs in the "+query_name()+".\n";
}

public void
init()
{
    ::init();

    add_action(do_keep, "tie");
    add_action(do_keep, "untie");
}


string
short_func()
{
    if (sizeof(all_inventory(TO)))
        return "black leather pouch containing herbs";
    return "black leather pouch";
}

public string
long_func()
{
    string long_desc = "This is a small herb pouch fasioned out of "+
    "black leather. On the front you see a picture of a grim skull. "+
    "On the skull's head is a sort of S-shaped symbol on it with "+
    "a spear-like object going through it.\n";

    if (query_prop(OBJ_M_NO_SELL))
        long_desc += "Presently, the pouch is tied to your belt.";
    else
        long_desc += "It is possible to tie the pouch to your belt "
	    + "to prevent it from being stolen or sold inadvertently.";
    return long_desc;
}

string
query_recover()
{
    return MASTER + ":" + query_container_recover();
}

void
init_recover(string arg)
{
    init_container_recover(arg);
}

public int
do_keep(string str)
{
    int     ibelt;
    object *objs,
            tp = TP, 
           *belt_cont;
    string  vb = query_verb();

    NF(C(vb)+" what?\n");
    if (!strlen(str) || (E(TO) != tp))
        return 0;

    if (!parse_command(lower_case(str), all_inventory(tp),
	"%i [to] [from] [the] [my] [belt]", objs))
        return 0;

    objs = NORMAL_ACCESS(objs, 0, 0);

    if (!sizeof(objs))
        return 0;

    if (member_array(TO, objs) < 0)
        return 0;

    if (query_prop(OBJ_M_NO_SELL))
    {
        if (vb == "tie")
        {
            NF("The pouch is already tied to your belt.\n");
            return 0;
        }
        remove_prop(OBJ_M_NO_SELL);
        remove_prop(OBJ_M_NO_DROP);
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
        write("You untie the "+query_name()+" from your belt.\n");
        say(QCTNAME(tp)+" unties "+LANG_ADDART(query_name())
          + " from "+HIS(tp)+" belt.\n");
    }
    else
    {
        if (vb == "untie")
        {
            NF("The pouch is already untied.\n");
            return 0;
        }
        add_prop(OBJ_M_NO_SELL, NO_SELL_PROP);
        add_prop(OBJ_M_NO_DROP, NO_DROP_PROP);
        tp->add_subloc(BELT_O_SUBLOC, TO);
        belt_cont  = tp->query_prop(LIVE_AO_BELT_SUBLOC);
	if (pointerp(belt_cont))
	    belt_cont -= ({ 0 });
	else
	    belt_cont = ({ });
        belt_cont += ({ TO });
        tp->add_prop(LIVE_AO_BELT_SUBLOC, belt_cont);
        write("You tie the "+query_name()+" to your belt, to remind "
          + "yourself not to sell it, and to protect it from thieves "
          + "(but of course not from cutpurses).\n");
        say(QCTNAME(tp)+" ties "+LANG_ADDART(query_name())+" to "
          + HIS(tp)+" belt.\n");
    }
    return 1;
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns:       The string the looker shall see
 */
public string
show_subloc(string subloc, object me = TP, object for_obj = TP)
{
    object *items = ({ });
    string  desc,
            his;

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (subloc != BELT_O_SUBLOC)
        return show_subloc(subloc, me, for_obj);

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
        desc = C(HE(me))+" has ";
        his = HIS(me);
    }

    items += me->query_prop(LIVE_AO_BELT_SUBLOC);
    items -= ({ 0 });
    desc += COMPOSITE_DEAD(items);
    desc += " tied to "+his+" belt.\n";
    return desc;
}

/*
 * Function name: query_auto_load
 * Description:   remove the OBJ_M_NO_DROP property if it is set
 *                so the backpack and its contents are not lost
 *                when a player logs out.
 * Returns:       0
 */

public string
query_auto_load()
{
    mixed   setting;

    if (setting = query_prop_setting(OBJ_M_NO_DROP))
    {
        remove_prop(OBJ_M_NO_DROP);
        Prop_Aid = set_alarm(0.5, 0.0, &add_prop(OBJ_M_NO_DROP, setting));
    }
    return 0;
}

/*
 * Function name: leave_env
 * Description  : This function is called each time this object leaves an
 *                old environment. If you mask it, be sure that you
 *                _always_ call the ::leave_env(dest, old) function.
 * Arguments    : object old  - the location we are leaving.
 *                object dest - the destination we are going to. Can be 0.
 */
public void
leave_env(object old, object dest)
{
    int     ibelt;
    object *belt_cont;

    ::leave_env(old, dest);

    if (!objectp(old) || !living(old) || 
	!query_prop(OBJ_M_NO_SELL))
	return;

    remove_prop(OBJ_M_NO_SELL);
    remove_prop(OBJ_M_NO_DROP);
    remove_alarm(Prop_Aid);
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
