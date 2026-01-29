/* /d/Shire/common/herbs/obj/wrap.c
*
* Feb 2003
*  by Palmer
*
* This piece of cloth lets you wrap herbs into a pseudo-heap 
* called a "bundle".
*
* You can unwrap the bundle at a later time.
*
* You can have one type of herb in each bundle only.
*
* You can only bundle herbs that you can identify. This is so
* you won't bundle "green berries" and bundle huckleberries
* and hemlock. Well. And because its a parsing nightmare.
* Also, casting spells is being tested with bundles.
*
* This is mainly used during Armageddon so you can recover one
* bundle of herbs rather than a large quantity of herbs.
*
* This should help reduce the number of herb objects and all
* the related alarms keeping track of decay.
* And kids love it. Less recovery time after Armageddon.
*
* Hopefully /std/heap.c will do all this in the Fifth Age.
*
* TODO: Add 'The bundle is full', 'almost empty' etc to 
*            the description.
*/

#pragma strict_types

#define MAX_HERBS 25
#define BUNDLE "/d/Shire/common/herbs/obj/bundle"

inherit "/std/object";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Shire/sys/defs.h"

/* Function Prototypes */
public int do_bundle(string str);
public mixed get_herb_ref(string str);
public int valid_herb(object o);


/* Globals */
string Herb_name;
int Nbr_herbs;

// 01234567890123456789012345678901234567890123456789012345678901234567890123456
/*
 * Function name: create_object
 * Description  : Constructor. To define your own bundle, use create_bundle().
 *
 * Arguments: none
 * Returns: none
 */
public int
create_object()
{
    set_name("wrap");
    add_name("herb wrap");

    set_short("herb wrap");
    add_adj("cloth");

    set_long("This is a piece of cloth used to wrap herbs into a single " +
        "bundle. You can 'wrap herbname' with it. When you are ready to " +
        "use or sell the herbs in the bundle you can 'unwrap bundle'. " +
        "There is a tag sewn onto the cloth.\n");

    add_item("tag", "This bundle will last through Armageddon " +
                "so you won't have to recover the individual herbs in it. It also " +
                "keeps the herbs fresh.\n");

    add_prop(OBJ_I_WEIGHT,  4);
    add_prop(OBJ_I_VALUE,  24);
    add_prop(OBJ_I_VOLUME, 10);
    setuid();
    seteuid(getuid());

}


/*
 * Function name: valid_herb
 *
 * Description  : Checks to see if you have herb in inventory
 *
 * Arguments: object - herb to check
 * Returns: 1/0
 */
public int
valid_herb(object o)
{
    if (o->query_herb_name() == Herb_name)
        return 1;

    else
        return 0;
}

/*
 * Function name: get_herb_ref
 *
 * Description  : Finds herb object from string description
 *
 * Arguments: string - herb to find
 * Returns: object or int 0
 */
public mixed
get_herb_ref(string str)
{
    object herb;
    
    herb = present(str, this_player());
    return herb;
        
}


/*
 * Function name: get_herbs
 *
 * Description  : Create array of herbs in inventory
 *
 * Arguments: object - herb to look for
 * Returns: object array of herbs
 */
public mixed
get_herbs(object o)
{
    object *things, *all_herbs;
    
    things = all_inventory(this_player());
    all_herbs = filter(things, valid_herb);
        
    return all_herbs;
}


/*
 * Function name: get_herb_name
 *
 * Description  : Gets the herbs official name
 *
 * Arguments: object - herb to be queried
 * Returns: string
 */
public string
get_herb_name(object o)
{
    return o->query_herb_name();
}



/*
 * Function name: destroy_herbs
 *
 * Description  : Destroys each herb that goes into bundle
 *
 * Arguments: object - array of herbs
 * Returns: none
 */
public void
destroy_herbs(object *o)
{
    int i;

    for (i=0; i < Nbr_herbs; i++)
    {
        o[i]->remove_object();
    }
}
  

/*
 * Function name: query_decay_left
 *
 * Description  : Get the time left before herb decays to nothing
 *
 * Arguments: object - herb
 * Returns: int - time in second
 */
public int
query_decay_left(object o)
{
  mixed *calls = o->query_alarms();
  int i, dl;
  float t;
  
  for (i = 0; i < sizeof(calls); ++i)
  {
    t = calls[i][2]; // how soon until it gets called?
    dl = (ftoi(t));
  }
  return dl;
}

/*
 * Function name: make_decay_list
 *
 * Description  : Gets a list of each herb's decay state
 *
 * Arguments: object - array of herbs
 * Returns: array of integers
 */
public mixed
make_decay_list(object *o)
{
    int *decay_rates, i;

    decay_rates = allocate(Nbr_herbs);    
    for (i=0; i < Nbr_herbs; i++)
    {
        // decay_rates[i] = o[i]->query_decay_time();
        decay_rates[i] = query_decay_left(o[i]);
    }    
    return decay_rates;
}

/*
 * Function name: create_bundle
 *
 * Description  : Creates object with list of decay values
 *
 * Arguments: object, *int, int - herb, array of decay vals, weight
 * Returns: object - bundle of herbs
 */
public object
create_bundle(object herb, int *decay_rates, int weight, int volume,
             string full_desc, string unknown_desc, int diff)
{
    string herb_file, name;
    object bundle;
    
    herb_file = MASTER_OB(herb);


    bundle = clone_object(BUNDLE);
    bundle->add_herb(herb_file);
    
    name = herb->query_plural_short();
    // Some herbs don't have plural set
    if (!stringp(name))
    {
        name = herb->short() + "s";
    }
    bundle->add_short(herb->query_herb_name());
    bundle->add_weight(weight);
    bundle->add_volume(volume);
    bundle->add_decays(decay_rates);
    bundle->add_id(full_desc);
    bundle->add_unid(unknown_desc);
    bundle->set_id_diff(diff);
    bundle->add_herb_name(herb->query_herb_name());

    return bundle;
}
 
/*
 * Function name: do_bundle
 *
 * Description  : Checks to see if you have herbs and prepares
 *                to create an object with reference to herbs
 *
 * Arguments: string - herb name to bundle up
 * Returns: 1/0
 */
public int
do_bundle(string str)
{
    write("Wraps are disabled until a critical bug is fixed.\n");
    TO->remove_object();
    return 1;
}


public void
init()
{
    add_action(do_bundle, "wrap");
}

public string
query_recover()
{
    return MASTER;
}
