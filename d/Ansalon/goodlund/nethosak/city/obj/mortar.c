/*
 *	/d/Genesis/std/potions/mortar.c
 *
 *	A mortar to mix potions.
 *
 *	Olorin, August 1995
 *
 *	Copyright (c) 1996 by Christian Markus
 *
 *	Modification log:
 *	- Olorin, Nov 1996:	Revision to make the mortar generally available.
 */
#pragma save_binary
#pragma strict_types

inherit "/std/container.c";

#include <composite.h>
#include <files.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <std.h>
#include <tasks.h>

#define DEBUG			0
#define MORTAR_AS_MIX	"_mortar_as_mix"
#define MORTAR_INGR_SIZE	6
#define MORTAR_MIN_ALCO		0
#define MORTAR_MIN_SOFT		1
#define MORTAR_HERBS		2
#define MORTAR_HEAPS		3
#define MORTAR_OTHER		4
#define MORTAR_POTION_FILE	5
#define MIX_TASK		TASK_ROUTINE
#define MIX_SKILLS		({ SS_ALCHEMY, SKILL_AVG, SS_HERBALISM, \
							 SS_SPELLCRAFT, TS_WIS, SKILL_END })
#define MIX_FAIL_MSG	"There is something missing. Check the ingredients!"
#define ONE_OF_LIST(array) ((array)[random(sizeof(array))])
#define NFN(x)			notify_fail((x) + "\n")

/*
 *	Prototypes:
 */

/*
 *	Global variables:
 */
/*
 * Mapping Ingredients:
   potion name : ({min alco, min soft, ({ herb1, ..., }), ({ heap1, ..., }),
                 ({ other1, ..., }), potion file name
 */
static mapping Ingredients = ([ ]);
static string  Fail_Ingr_Msg = MIX_FAIL_MSG;

/*
 * Function name: list_potions
 * Description:   List all potions that can be mixed with this mortar.
 * Returns:       Array of string with potion names.  
 */
public string *
list_potions()
{
    return m_indexes(Ingredients);
}

/*
 * Function name: filter_herbs
 * Description:   Find herbs.
 * Argument:      x - object pointer
 * Returns:       1 if x is an object pointer to a herb.
 */
static int
filter_herbs(object x)
{
    return IS_HERB_OBJECT(x);
}

/*
 * Function name: filter_heaps
 * Description:   Find heaps.
 * Argument:      x - object pointer
 * Returns:       1 if x is an object pointer to a heap.
 */
static int
filter_heaps(object x)
{
    return IS_HEAP_OBJECT(x);
}

/*
 * Function name: filter_drinks
 * Description:   Find drinks.
 * Argument:      x - object pointer
 * Returns:       1 if x is an object pointer to a drink.
 */
static int
filter_drinks(object x)
{
    return IS_DRINK_OBJECT(x);
}

/*
 * Function name: check_heaps
 * Description:   Match all heaps in the list of ingredients,
 *                to the heap ingredients of the potion to be mixed.
 *                The match is done based on the filename.
 * Arguments:     heaps - the required heaps
 *                all_heaps - all heaps in the mortar
 * Returns:       The matched heaps or an empty array if the match
 *                failed.
 */
static object *
check_heaps(string *heaps, object *all_heaps)
{
    int     i, j, si, sj;
    object *return_heaps = ({});

    for (i = 0, si = sizeof(heaps); i < si; i++)
    {
        for (j = 0, sj = sizeof(all_heaps); j < sj; j++)
        {
            if (MASTER_OB(all_heaps[j]) == heaps[i])
            {
                return_heaps += ({ all_heaps[j] });
                break;
            }
        }
    }

    if (sizeof(return_heaps) == sizeof(heaps))
        return return_heaps;
    else
        return ({ });
}

/*
 * Function name: check_herbs
 * Description:   check if required herbs are in the mortar
 *                the match is done based on the filename
 * Arguments:     herbs     - required herbs
 *                all_herbs - herbs inside the mortar
 * Returns:       array pointing to the required herbs that
 *                are inside the mortar
 */
static object *
check_herbs(string *herbs, object *all_herbs)
{
    int     i, j, si, sj;
    object *return_herbs = ({});

    for (i = 0, si = sizeof(herbs); i < si; i++)
    {
        for (j = 0, sj = sizeof(all_herbs); j < sj; j++)
        {
            if (MASTER_OB(all_herbs[j]) == herbs[i])
            {
                return_herbs += ({ all_herbs[j] });
                break;
            }
        }
    }

    if (sizeof(return_herbs) == sizeof(herbs))
        return return_herbs;
    else
    {
        Fail_Ingr_Msg = "There is a herb missing in the ingredients!";
        return ({ });
    }
}

/*
 * Function name: check_others
 * Description:   Match all other ingredients in the list of ingredients
 *                to the ingredients of the potion to be mixed.
 *                The match is done based on the names.
 * Arguments:     others - the required heaps
 * Returns:       The matched ingredients or an empty array if the match
 *                failed.
 */
static object *
check_others(string *others)
{
    int     i, si;
    object  ob,
           *return_others = ({ });

    for (i = 0, si = sizeof(others); i < si; i++)
    {
        if (objectp(ob = present(others[i], this_object())))
        {
            return_others += ({ ob });
            break;
        }
    }

    if (sizeof(return_others) == sizeof(others))
        return return_others;
    else
        return ({ });
}

/*
 * Function name: check_potion_ingr
 * Description:	  Find an ingredient or a number of ingredients in
 *		          the mortar.
 * Arguments:	  ingr: array of required ingredients:
 *                min alco content of drink,
 *           	  min soft content of drink,
 *           	  array of required herbs (file name)
 *                array of required heaps (file name)
 *                array of required other ingredients (name)
 * Returns:	      the ingredients
 */
static object *
check_potion_ingr(mixed ingr)
{
    int     need_drink = 0,
            i, 
            id = -1,
            am,
            alco_max = 0;
    object *inv = all_inventory(this_object()),
           *all_drinks,
           *all_herbs,
           *all_heaps,
           *return_arr = ({ });
#if DEBUG
    write("DEBUG ***** check_potion_ingr ***** STARTING now with " 
      + ingr[MORTAR_MIN_ALCO] + ", " + ingr[MORTAR_MIN_SOFT] + "\n");
    dump_array(ingr[MORTAR_HERBS]);
    dump_array(ingr[MORTAR_HEAPS]);
    dump_array(ingr[MORTAR_OTHER]);
#endif

    Fail_Ingr_Msg = MIX_FAIL_MSG;
    if ((ingr[MORTAR_MIN_SOFT] > 0) || (ingr[MORTAR_MIN_ALCO] > 0))
    {
        need_drink = 1;
        all_drinks = filter(inv, filter_drinks);
        for (i = 0; i < sizeof(all_drinks); i++)
        {
        // find strongest drink with at least minimum required soft amount
            if (((am = all_drinks[i]->query_alco_amount()) >= alco_max)
                && (all_drinks[i]->query_soft_amount() >= ingr[MORTAR_MIN_SOFT]))
            {
                alco_max = am;
                id = i;
            }
        }

        if (id == -1)
        {
            Fail_Ingr_Msg = "There is not enough liquid in the mortar to mix the potion!";
            return 0;
        }
        else if (alco_max < ingr[MORTAR_MIN_ALCO])
        {
            Fail_Ingr_Msg = "There is not enough alcohol in the mortar to mix the potion!";
            return 0;
        }
        else
            return_arr = ({ all_drinks[id] });
    }
#if DEBUG
write("DEBUG drinks checked!\n");
dump_array(return_arr);
#endif

    if (sizeof(ingr[MORTAR_HERBS]))
    {
        all_herbs = filter(inv, filter_herbs);
        return_arr += check_herbs(ingr[MORTAR_HERBS] + ({}), all_herbs);
    }
#if DEBUG
write("DEBUG herbs checked!\n");
dump_array(return_arr);
#endif

    if (sizeof(ingr[MORTAR_HEAPS]))
    {
        all_heaps = filter(inv, filter_heaps);
        return_arr += check_heaps(ingr[MORTAR_HEAPS] + ({}), all_heaps);
    }

    if (sizeof(ingr[MORTAR_OTHER]))
        return_arr += check_others(ingr[MORTAR_OTHER]);

    /* do we have everything? */
    if (sizeof(return_arr) == ((sizeof(ingr[MORTAR_HERBS])
      + sizeof(ingr[MORTAR_HEAPS]) + sizeof(ingr[MORTAR_OTHER]) + need_drink)))
    {
#if DEBUG
write("DEBUG everything checked!\n");
dump_array(return_arr);
#endif
        return return_arr;
    }
    else
        return 0;
}

/*
 * Function name: do_mix
 * Description:   Try to mix a potion.
 * Argument:      str - command line argument, the name of the potion.
 * Returns:       1/0 - success/failure
 */
public int
do_mix(string str)
{
    int     in,
            sk;
    object  vial,
            pl = this_player(),
            pot,
           *garb,
           *result;
    string  msg;

    if (pl != environment(this_object()))
        return 0;

    NFN("What potion do you want to mix?");
    if (!strlen(str))
        return 0;

    str = lower_case(str);

    if (member_array(str, list_potions()) == -1)
        return 0;

    NFN("Without a vial, you cannot mix a potion.");
    if (!objectp(vial = present("_std_potion_vial", pl)))
        return 0;

    result = check_potion_ingr(Ingredients[str]);

    if (!pointerp(result))
    {
        NFN(Fail_Ingr_Msg);
        return 0;
    }

    garb = all_inventory(this_object()) - result;
    if (sizeof(garb))
    {
        NFN("You have to take " + COMPOSITE_DEAD(garb) +
           " out of the mortar if you want to mix " +
           LANG_ADDART(str) + " potion.\n");
        return 0;
    }

    // Are we skilled enough?
    if ((sk = pl->resolve_task(MIX_TASK, MIX_SKILLS)) <= 0)
    {
        msg = "You fumble around with your "+short()+" and the " +
            "ingredients, but you fail to mix " +
            LANG_ADDART(str) + " potion.";
        // remove one random ingredient if in bad luck
        if (!random((100+sk)/10+1))
        {
            garb = ({ ONE_OF_LIST(result) });
            msg += " You ruin "+LANG_ASHORT(garb[0])+ " in the attempt.";
            garb[0]->remove_object();
        }
        NFN(msg);
        return 0;
    }

    seteuid(getuid());

#if DEBUG
    write("DEBUG trying to clone now ");
    dump_array(Ingredients[in + 6]);
    write("\n");
#endif
    // clone the potion
    pot = clone_object(Ingredients[str][MORTAR_POTION_FILE]);
    pot->set_identified();

    // set up
    if (!pot->set_up_potion(result))
    {
        // tellem
        write("From " + COMPOSITE_DEAD(result) + " you mix a potion.\n"
          + "You pour the potion into your empty vial.\n");
        say(QCTNAME(pl) + " mixes a potion in " + pl->query_possessive() +
        " mortar and pours it into a vial.\n", pl);
    }
    // remove the vial
    vial->remove_object();
    // remove the ingredients
    for (in = 0; in < sizeof(result); in++)
        result[in]->remove_object();
    // move it
    if (pot->move(pl))
        pot->move(environment(pl),1);
    return 1;

}

private void
set_up_mortar()
{
    int     i;
    object *links;

    links = map(SECURITY->query_domain_links(), find_object);
    if (!sizeof(links))
        return;

    links -= ({ 0 });

    i = sizeof(links);
    while(i--)
        if (pointerp(links[i]->query_potion_map()))
        Ingredients += links[i]->query_potion_map();
}

/*
 * Function name: create_container
 * Description:   Creator.
 */
public void
create_container()
{
    set_name("mortar");

    set_long("This is a mortar made out of black stone. If you put the " +
        "right ingredients into the mortar you can \"mix <potion>\".\n");

    add_prop(OBJ_I_VALUE, 720);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(CONT_I_WEIGHT, 1500);
    add_prop(CONT_I_VOLUME,  300);
    add_prop(CONT_I_MAX_WEIGHT,  2500);
    add_prop(CONT_I_MAX_VOLUME,  1300);

    set_up_mortar();
}

public void
init()
{
    add_action(do_mix, "mix");

    ::init();
}

public string
query_auto_load()
{
    return MASTER + ":";
}

void
remove_drink(object ob)
{
    ob->remove_object();
}

public void
enter_inv(object ob, object from)
{
    int     num;
    object *drink;
    string *mix;

    ::enter_inv(ob, from);
    if (!objectp(ob) || !filter_drinks(ob))
        return;

    drink = filter(all_inventory(this_object()), filter_drinks);
    drink -= ({ ob });

    if (sizeof(drink))
        if (drink[0]->query_prop(HEAP_S_UNIQUE_ID) == ob->query_prop(HEAP_S_UNIQUE_ID))
            drink[0]->set_heap_size(1);

    if ((num = ob->num_heap()) > 1)
    {
        ob->set_heap_size(1);
        ob->set_alco_amount(MIN(50, ob->query_alco_amount() * num));
        ob->set_soft_amount(ob->query_soft_amount() * num);
    }

    if (!sizeof(drink))
        return;

    mix = drink[0]->query_prop(MORTAR_AS_MIX);

    drink[0]->set_alco_amount(MIN(50,drink[0]->query_alco_amount() + ob->query_alco_amount()));
    drink[0]->set_soft_amount(drink[0]->query_soft_amount() + ob->query_soft_amount());

    if (!sizeof(mix))
        mix = ({ drink[0]->query_name() });
    if (member_array( ob->query_name(), mix) == -1)
        mix += ({ ob->query_name() });
    drink[0]->add_prop(MORTAR_AS_MIX, mix);

    this_player()->catch_msg("When you pour " + ob->short() + " to " +
            drink[0]->short() + " in the mortar, both liquids are mixed with each other.\n");

    if (sizeof(mix) >= 2)
    {
        drink[0]->set_long("This liquid is a mixture of " + COMPOSITE_WORDS(mix) + ".\n");
        drink[0]->set_short("liquid mixed from " + COMPOSITE_WORDS(mix));
        drink[0]->set_name("liquid");
        drink[0]->add_prop(HEAP_S_UNIQUE_ID, drink[0]->query_long());
    }

    set_alarm(0.0, 0.0, &remove_drink(ob));
}

