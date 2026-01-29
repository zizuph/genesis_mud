/*
 * satchel to carry leftovers. Based on the Shire packs
 * -- Finwe, May 2006
 *
 * Recoded 2010/08/31 Lavellan
 *
 */

inherit "/d/Genesis/std/wearable_pack.c";

inherit "/lib/shop";
inherit "/lib/keep";

#include "/d/Faerun/defs.h"
#include <composite.h>
#include <filter_funs.h>
#include <macros.h>
#include <money.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

#define MORGUL_M_MAGIC_INGREDIENT "_Morgul_m_magic_ingredient"
static string
    endlin  = "+--------------------------------------------+\n",
    blklin  = "|                                            |\n",
    catlin  = "| Qty. |  Potions & Components               |\n",
    heaplin = "| %4d | %-=35s |\n";


void
create_wearable_pack()
{
//    ::create_container();

    add_prop(OBJ_I_VALUE, 250+random(150));
    remove_adj("camouflaged");
    remove_adj("green-coloured");
    add_adj(({"well-used", "leather"}));

    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 2000);
    add_prop(CONT_I_MAX_WEIGHT, 150000);
    add_prop(CONT_I_MAX_VOLUME, 150000);
    add_prop(CONT_I_REDUCE_VOLUME, 125);
    add_prop(CONT_I_CLOSED, 0);


    set_short("well-used leather satchel");
    set_pshort("well-used leather satchels");
    set_long("@@long_description");

    set_name("satchel");
    set_slots(A_WAIST);
    
    set_mass_storage(1);

}

string
long_description()
{
    string long_desc = "This " + query_short() + " is made of supple canvas. " +
        "It is a small bag designed to hold spell components. The satchel " +
        "looks like it has been used for some time because it is worn in " +
        "places. ";

    if (query_keep())
    {
        long_desc += "\n  The " + short() + " is protected from being sold. " +
        "Use <unkeep satchel> to sell it.";
    }
    else
    {
        long_desc += "\n  The " + short() + " is not protected from being " +
        "sold. <keep satchel> will protect it, but not from thieves or " +
        "cutthroats.";
    }

    return long_desc+"\n";
}


public int
sort_objects_to_list(object *a, object *b)
{
    string na, nb;
    na = a->query_organ() + a->query_race();
    if (!na) na = a->short();
    nb = b->query_organ() + b->query_race();
    if (!nb) nb = b->short();
    if (na == nb) return 0;
    if (na < nb) return -1;
    return 1;
}


/*
 * Function name: describe_contents
 * Description:   Give a description of items in this container
 * Arguments:     object for_obj - To whom to give the description
 *                object *obarr  - The items to describe
 */
public void
describe_contents(object for_obj, object *obarr)
{
    string out, last = "??";

    for_obj->catch_tell(show_sublocs(for_obj));

    if (sizeof(obarr) > 0)
    {
        obarr = sort_array(obarr, "sort_objects_to_list");
        out = endlin + blklin + catlin;
        foreach(object ob: obarr)
        {
            if (last != ob->query_organ())
                out += blklin;
            if (IS_HEAP_OBJECT(ob))
                out += sprintf(heaplin, ob->num_heap(), (ob->num_heap() == 1 ? ob->singular_short() : ob->plural_short()));
            else
                out += sprintf(heaplin, 1, ob->short());
            last = ob->query_organ();
        }
        out += blklin + endlin;
        
        for_obj->catch_tell(out);
    }
    else
    {
        for_obj->catch_tell("  " + "The " + short() + " is empty.\n");
    }
}


/* Function name: prevent_enter
 * Description  : Checks if it is bodypart or not
 * Arguments    : object obj - the object entering
 * Returns      : 1 if not a bodypart, 0 if it is
 */
public int
prevent_enter(object obj)
{
//    if (obj->create_leftover())
    if (!IS_POTION_OBJECT(obj))
    {
        write("Only potions and their components can be put into the " + short() + ".\n");
        return 1;
    }
    return 0;
}

public int
item_filter(object obj)
{
//    return ((IS_POTION_OBJECT(obj) ||
//            (obj->id("stone")) ||
//            (obj->id("rock")) ||
//            (obj->id("feather")) ||
//            (obj->id("torch")) ||
//            (IS_DRINK_OBJECT(obj)) ||
//            (obj->id("gem")) ||
//            (obj->id("leftover")) ||
//            (obj->query_prop(MORGUL_M_MAGIC_INGREDIENT)) ||
//            (obj->id("vial"))));
  return IS_POTION_OBJECT(obj);
}

/*
 * Function name:       query_recover
 * Description  :       check whether pack is recoverable (it is)
 * Returns      :       string -- the recovery string
 */
public string
query_recover()
{
    return MASTER + ":" + query_container_recover() + query_keep_recover();
} /* query_recover */

/*
 * Function name:       init_recover
 * Description  :       set the recovery vars
 * Arguments    :       string arg -- the arguments to parse
 */
public void
init_recover(string arg)
{
    init_keep_recover(arg);
    init_container_recover(arg);
} /* init_recover */