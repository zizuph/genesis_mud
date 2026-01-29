/*
 * sack.c
 *
 * The herald's herb sack.
 * Keep and no sell abilites borrowed from Gondor's herb pouch 
 * and modified for this bag. 
 * -- Finwe, 9/2000
 *
 */

#pragma save_binary

//inherit "/std/receptacle";
inherit "/lib/keep";
inherit "/d/Shire/common/obj/herb_sack";

#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <wa_types.h>
#include "herald.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"


#define NO_SELL_PROP "The soft bag is attached to your your belt. Selling it would not be a good idea.\n"
#define NO_DROP_PROP "The soft bag is attached to your your belt. Dropping it would not be a good idea.\n"

#define BELT_O_SUBLOC   "bag_o_subloc"
#define LIVE_AO_BELT_SUBLOC     "_live_ao_bag_subloc"

#define HE(x)   (x)->query_pronoun()
#define HIS(x)  (x)->query_possessive()

public int     do_keep(string str);
//static mixed   check_insert();
public string  short_func();
public string  long_func();
static int     Prop_Aid;


/*
 *  Description: Constructor.
 */
public void
create_container()
{
    set_name("small soft bag");
    add_name(({"bag","herb bag"}));
    set_pname("bags");
    set_adj( ({ "silk","small" }) );
    set_short("small soft bag");
    set_pshort("small soft bags");
    set_long(long_func);
    add_prop(OBJ_I_VALUE, 100+random(150));
    add_prop(CONT_I_WEIGHT, 300);
    add_prop(CONT_I_VOLUME, 5000);
    add_prop(CONT_I_MAX_WEIGHT, 5000);
    add_prop(CONT_I_MAX_VOLUME, 6000);
    add_prop(CONT_I_CLOSED,     0);
    add_prop(OBJ_M_NO_SELL,     "@@check_sell@@");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
//    add_prop(CONT_M_NO_INS, check_insert);

}


public void
init()
{
    ::init();

    add_action(do_keep, "tie");
    add_action(do_keep, "untie");
}

/*
static mixed
check_insert()
{
    int     i = 1;
    object  obj,
    pobj;

    while (objectp(obj = previous_object(--i)))
    {
        if (obj == TO)
        {
            if ((function_exists("create_object", (pobj =
                    previous_object(i-1))) == POTION_OBJECT) || 
                    ((pobj->query_adj() == "small") && (pobj->id("stone"))) ||
              pobj->query_prop(MORGUL_M_MAGIC_INGREDIENT) || 
              pobj->id("vial") || pobj->query_herb_name())
                return 0;
            else
                return "The "+query_name()+" is only for herbs, " +
                    "potions and magical ingredients.\n";
        }
    }
    return "The "+query_name()+" is only for potions and magical ingredients.\n";
}
*/

/*
public int
do_default_open(string str)
{

    if(str == "bag" || str == "small silk bag" || str == "silk bag")
    {
//
//    	if(!IS_MEMBER(TP) || !TP->query_wiz_level())
//	    {
//	        write("A magical seal on the silk bag prevents you from opening it.\n");
//	        return 1;
//	    }

    }
    ::do_default_open(str);

    return 1;
}
*/

mixed
check_sell()
{
    if (sizeof(all_inventory(TO)))
	return "There are things in the "+short()+"! Empty it first.\n";
    else
	return 0;
}


string
short_func()
{
    if (sizeof(all_inventory(TO)))
        return "soft bag containing items";
    return "soft bag";
}

public string
long_func()
{
    string long_desc = "This bag is made from a soft material. Its color seems to change when moved in the light and seems to almost be invisible. It is designed to hold a large number of herbs and other spell items.";

    if (query_prop(OBJ_M_NO_SELL))
        long_desc += " Currently, the bag is attached to your belt.";
    else
        long_desc += " You may <tie bag> to " +
            "keep it, or <untie bag> to remove " +
            "it and unkeep it.";
    return BSN(long_desc);
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
        return me->show_subloc(subloc, me, for_obj);

    if (for_obj == me)
    {
        desc = "You have ";
        his  = "your";
    }
    else

    {
        // If a robe is worn, what is tied to the bag is concealed.
/*
        if (objectp(me->query_armour(A_ROBE)))
            return "";
*/
        desc = CAP(HE(me))+" has ";
        his = HIS(me);
    }

    items += me->query_prop(LIVE_AO_BELT_SUBLOC);
    items -= ({ 0 });

    desc += COMPOSITE_DEAD(items);
    desc += " attached to "+his+" belt.\n";

    return desc;
}


/*
 * Function name: set_keep
 * Description  : Mask parent in order to set or remove the 'keep'
 *                protection of this object. If no argument is passed to the
 *                function, the default will be 1 - i.e. set the 'keep'
 *                protection.
 * Arguments    : int 1 - set the 'keep' protection.
 *                    0 - remove the 'keep' protection.
 * For the pouch, keepable also means not droppable, since it's tied
 * to the player's betl.
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



public int
do_keep(string str)
{
    int     ibelt;
    object *objs,
    *belt_cont;
    string  vb = query_verb();

    NF(CAP(vb)+" what?\n");
    if (!strlen(str) || (ENV(TO) != TP))
        return 0;

    if (!parse_command(LOW(str), all_inventory(TP),
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
            NFN("The "+query_name()+" is already tied to your belt.");
            return 0;
        }
        remove_prop(OBJ_M_NO_SELL);
        remove_prop(OBJ_M_NO_DROP);
        belt_cont  = TP->query_prop(LIVE_AO_BELT_SUBLOC);
        if (pointerp(belt_cont))
            belt_cont -= ({ 0 });
        else
            belt_cont  = ({ });
        if ((ibelt = member_array(TO, belt_cont)) > -1)
            belt_cont = exclude_array(belt_cont, ibelt, ibelt);
        if (sizeof(belt_cont))
            TP->add_prop(LIVE_AO_BELT_SUBLOC, belt_cont);
        else
        {
            TP->remove_prop(LIVE_AO_BELT_SUBLOC);
            TP->remove_subloc(BELT_O_SUBLOC);
        }
        write("You untie the "+query_name()+" from your belt.\n");
        say(QCTNAME(TP)+" unties "+LANG_ADDART(query_name())
          + " from "+HIS_HER(TP)+" belt.\n");
    }
    else
    {
        if (vb == "untie")
        {
            NFN("The "+query_name()+"  is already untied.");
            return 0;
        }
        add_prop(OBJ_M_NO_SELL, NO_SELL_PROP);
        add_prop(OBJ_M_NO_DROP, NO_DROP_PROP);
        TP->add_subloc(BELT_O_SUBLOC, TO);
        belt_cont  = TP->query_prop(LIVE_AO_BELT_SUBLOC);
        if (pointerp(belt_cont))
            belt_cont -= ({ 0 });
        else
            belt_cont  = ({ });
        belt_cont += ({ TO });
        TP->add_prop(LIVE_AO_BELT_SUBLOC, belt_cont);
        write("You tie the "+query_name()+" to your belt as a " +
            "reminder not to sell it. However, thieves may still " +
            "have access to it.\n");
        say(QCTNAME(TP)+" ties "+LANG_ADDART(query_name())+" to "
          + HIS_HER(TP)+" belt.\n");
    }
    return 1;
}


void init_recover(string arg)
{
    init_container_recover(arg);
}

string query_recover()
{
    return MASTER + ":" + query_container_recover();
}
