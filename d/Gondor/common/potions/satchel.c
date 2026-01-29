/*
 * A satchel to carry potions in.
 *
 * From the herb pouch coded by Lord Elessar Telcontar.
 * Modified for potions by Olorin.
 *
 * Revision history:
 * /Mercade, 23 November 1993, changed it from container to /std/receptacle
 * /Mercade, 7 January 1994, fixed recovery of the pouch.
 * Olorin, 8-feb-96: added protection against stealing,
 *                   modified for potions.
 * Olorin, 14-Feb-97: Fixed message and move error when trying to insert
 *                    non-herb objects, following example by Khail in herbjar.
 * Morbeche, 17-Oct-99: Allowed small stones to be put in satchel,
 * since it is an ingredient in Herald of the Valar spells.
 *
 * Tigerlily--27-Feb-2004: made satchel keepable
 * Gwyneth--07-June-2004: made satchel fillable
 * Eowul--04-Okt-2008: removed keep option, the tie to belt already does that
 *                     and using both causes unpredictable results.
 * Eowul--06-Sep-2015: keep was introduced globally in containers, piggyback
 *                     on the keep functionality with the tie command.
 * Arman--12-Mar-2018: Included holy water phials to be put in satchel
 * Zizuph - 09-Sep-2022: Set weight and volume reductions in line with jars.
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/std/pack.c";

#include <cmdparse.h>
#include <composite.h>
#include <files.h>
#include <language.h>
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#undef  DEBUG
#ifdef  DEBUG
#define DEBUG_MSG(x)    find_player("olorin")->catch_tell((x) + "\n")
#else
#define DEBUG_MSG(x)
#endif

#define NO_DROP_PROP    obj_m_no_drop
#define BELT_O_SUBLOC    "belt_o_subloc"
#define LIVE_AO_BELT_SUBLOC    "_live_ao_belt_subloc"

public string  long_func();
static mixed   check_insert();

static int     Prop_Aid;

public void
create_container()
{
    set_name("satchel");
    set_adj("leather");
    set_short("leather satchel");
    set_pshort("leather satchels");
    set_long(long_func);
    set_mass_storage(1);

    add_prop(CONT_I_IN,             1);
    add_prop(CONT_I_RIGID,          0);
    add_prop(CONT_I_TRANSP,         0);
    add_prop(CONT_I_CLOSED,         1);
    add_prop(CONT_I_WEIGHT,       300);
    add_prop(CONT_I_VOLUME,       300);
    add_prop(CONT_I_MAX_WEIGHT, 18000);
    add_prop(CONT_I_MAX_VOLUME,  9000);
    add_prop(CONT_I_REDUCE_WEIGHT, 200);
    add_prop(CONT_I_REDUCE_VOLUME, 200);    
    add_prop(OBJ_I_VALUE,          96);

    add_prop(CONT_M_NO_INS, check_insert);
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
}

static mixed
check_insert()
{
    int     i = 1;
    object  obj,
    pobj;

    while (objectp(obj = previous_object(--i)))
    {
        if (obj == this_object())
        {
            pobj = previous_object(i-1);
            if (IS_POTION_OBJECT(pobj) || 
                pobj->id("stone") || pobj->id("rock") ||
                pobj->id("feather") || IS_DRINK_OBJECT(pobj) ||
                ((pobj->query_adj() == "copper") && (pobj->id("coin"))) ||
                pobj->id("gem") || pobj->id("leftover") ||
                pobj->id("jar") ||
                pobj->query_prop(MORGUL_M_MAGIC_INGREDIENT) ||
                pobj->id("vial") ||
                pobj->id("_oots_holy_water") ||
                pobj->id("_spell_ingredient") ||
                (pobj->id("torch") && !pobj->query_prop(OBJ_I_HAS_FIRE)))
            {
                return 0;
            }
            else
            {
                return "The "+ query_name()+ " is only for potions and "+
                    "magical ingredients.\n";
            }
        }
    }
    return "The "+ query_name()+ " is only for potions and magical "+
        "ingredients.\n";
}

public int
item_filter(object ob)
{
    int val = !(ob->query_prop(OBJ_M_NO_GIVE) ||
         ob->query_prop(OBJ_M_NO_DROP) ||
         ob->query_worn() ||
         ob->query_wielded() ||
         ob->query_prop(LIVE_I_IS) ||
         ob->query_prop(OBJ_I_HAS_FIRE) ||
         ob->id("message") ||
         ob->id("note") ||
         ob->query_keep() ||
         !CAN_SEE(this_player(), ob));

    return (val &&
            (IS_POTION_OBJECT(ob) ||
            ob->id("stone") ||
            ob->id("rock") ||
            ob->id("feather") ||
            ob->id("torch") ||
            IS_DRINK_OBJECT(ob) ||
            ob->id("gem") ||
            ob->id("leftover") ||
            ob->id("jar") ||
            ob->id("_oots_holy_water") ||
            ob->query_prop(MORGUL_M_MAGIC_INGREDIENT) ||
            ob->id("vial")));
}

string
long_func()
{
    string long_desc = "This is a leather satchel to store potions and "+
        "other magical ingredients in.";

    if (query_prop( OBJ_M_NO_SELL ))
    {
        long_desc += " Presently, the satchel is tied to your belt.";
    }
    else
    {
        long_desc += " It is possible to tie the satchel to your belt "+
            "to prevent it from being sold inadvertently.";
    }
    return long_desc + " You may <fill> and <empty> the satchel.\n";
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

public string
keep_obj_m_no_sell()
{
    return capitalize(LANG_THESHORT(this_object())) + " is tied to your belt! "
        + "It cannot be sold.\n";
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

    return capitalize(LANG_THESHORT(this_object())) + " is tied to your belt! "
        + "It cannot be dropped.\n";
}

void
tie()
{
    write("You tie the " + query_name() + " to your belt, to remind "
        + "yourself not to sell it, and to protect it from thieves "
        + "(but of course not from cutpurses).\n");
    say(QCTNAME(this_player()) + " ties " + LANG_ADDART(query_name()) + " to "
        + POSSESSIVE(this_player()) + " belt.\n");
}

public void
untie()
{
    write("You untie the " + query_name() + " from your belt.\n");
    say(QCTNAME(this_player()) + " unties " + LANG_ADDART(query_name())
        + " from " + POSSESSIVE(this_player()) + " belt.\n");
}

public void
set_keep(int keep = 1)
{
    ::set_keep(keep);
    
    if (keep)
    {
        add_prop(OBJ_M_NO_DROP, NO_DROP_PROP);

        object *belt_cont, tp = environment(TO);

        tp->add_subloc(BELT_O_SUBLOC, TO);
        belt_cont = this_player()->query_prop(LIVE_AO_BELT_SUBLOC);
        if (pointerp(belt_cont))
            belt_cont -= ({ 0 });
        else
            belt_cont = ({ });
        belt_cont += ({ TO });
        tp->add_prop(LIVE_AO_BELT_SUBLOC, belt_cont);
    }
    else
    {
        remove_prop(OBJ_M_NO_DROP);

        int ibelt;
        object tp = this_player(), *belt_cont;

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
    }
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
            notify_fail("The satchel is already tied to your belt.\n");
            return 0;
        }

        set_keep(0);
        untie();
    }
    else
    {
        if (vb == "untie")
        {
            notify_fail("The satchel is already untied.\n");
            return 0;
        }

        set_keep(1);
        tie();
    }

    return 1;
}

public void
init()
{
    ::init();

    add_action(do_tie, "tie");
    add_action(do_tie, "untie");

    remove_name("pack");
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
show_subloc( string subloc, object me = this_player(),
    object for_obj = this_player() )
{
    object *items = ({ });
    string  desc,
    poss;

    if (me->query_prop( TEMP_SUBLOC_SHOW_ONLY_THINGS ))
    {
        return "";
    }

    if (subloc != BELT_O_SUBLOC)
    {
        return me->show_subloc( subloc, me, for_obj );
    }

    if (for_obj == me)
    {
        desc = "You have ";
        poss  = "your";
    }
    else
    {
        // If a robe is worn, what is tied to the belt is concealed.
        if (objectp( me->query_armour(A_ROBE) ))
        {
            return "";
        }
        desc = capitalize(me->query_pronoun())+ " has ";
        poss = me->query_possessive();
    }

    items += me->query_prop(LIVE_AO_BELT_SUBLOC);
    items -= ({ 0 });
    desc += COMPOSITE_DEAD( items );
    desc += " tied to "+ poss+ " belt.\n";
    return desc;
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

    if (query_keep())
    {
        set_keep(0);
    }
}

int
prevent_enter(object ob)
{
    return 0;
}
