/* /d/Shire/common/herbs/obj/bundle.c
*
* by Palmer, Feb 2003
* The bundle object for wrap.c
* See /d/Shire/common/herbs/obj/wrap.c for info
*
* Revisions:
*
* Sept 23, 2003 - Palmer:
* Modified bundle to work with /d/Genesis/newmagic/components.c
*
* Jan 04, 2004 - Palmer:
* Added query_amount with outrageous return so players can't eat bundles.
*  Normally you can't eat a bundle, but in odd cases, such as having an
*  herb in your inventory and a bundle and typing "eat herbs" would let
*  players eat bundles.
*
*/


#pragma strict_types

inherit "/std/herb.c";

#include "/sys/herb.h"
#include "../defs.h"
#include "/d/Shire/sys/defs.h"
#include <macros.h>
#include "/sys/stdproperties.h"

#define WRAP "/d/Shire/common/herbs/obj/nwrap.c"
#define MASTER_BUNDLE "/d/Shire/common/herbs/obj/nmaster_bundle.c"
#define LOG write

public void remove_single_herb();
public int use_component(int i);
public int query_qty();
public void set_single_volume(int v);
public void set_single_weight(int w);
public void decrease_volume(int v);
public void decrease_weight(int w);
public void give_wrap();

string Herb_file, Herb_short, Herb_name, Key;
int Weight, Volume, Herb_qty, *Decay_times;
int Single_weight, Single_volume;

public void
create_herb()
{
    set_ingest_verb("zxcvsdfasdf");
    set_decay_time(99999);
    set_herb_value(0);
//    stop_decay();
    setuid();
    seteuid(getuid());
    add_prop(CONT_I_HOLDS_COMPONENTS, 1);
    add_prop(CONT_I_CLOSED, 0);
    Volume = 10;
    Weight = 4;
}

/*
 * Function name:	ingest_it
 * Description:		Ingests the objects described as parameter to the
 *                      ingest_verb. It uses command parsing to find which
 *                      objects to ingest.
 * Arguments:		str: The trailing command after 'ingest_verb ...'
 * Returns:		True if command successfull
 */
public int
ingest_it(string str)
{
	notify_fail("You can't eat bundles of herbs.\n");
	return 0;

}


/*
 * Function name:	query_amount
 * Description:	Returns outragous ammount so players can't eat bundles
 * Arguments:	None
 * Returns:	int - outragous number.
 */

public int
query_amount()
{
    return 99999999;
}



/*
 * Function name: query_herb_name
 *
 * Description  : We overload this function so that the spell
 * system detects this bundle as an herb. We only return the
 * true herb name in this case, so people can't eat, sell etc.
 * this bundle by its herb name.
 *
 * Arguments: none
 * Returns: string
 */
mixed
query_herb_name()
{
    // find_living("palmer")->catch_msg(calling_program(-1));
    // find_living("palmer")->catch_msg(calling_function(-1));
    //if (calling_function(-1) == "find_components")
    if (calling_function(-1) == "cast_spell" || calling_function(-1) == "find_components")
        return Herb_name;
    else
        return 0;
}


/*
 * Function name: use_component
 *
 * Description  : Removes herb from bundle when herb
 *  is used as spell component. If it is the last herb, clone
 *  a wrap and remove bundle.
 *  Returning 1 tells the spell system not to destruct this bundle
 *
 * Arguments: none
 * Returns: object or int 1
 */
public int
use_component(int i)
{
    int n;
    object master_bundle;

    master_bundle = find_object(MASTER_BUNDLE);
    n = query_qty();

    if (n == 1)
    {
        give_wrap();
        if (objectp(master_bundle))
        {
            master_bundle->remove_bundle(Key);
        }
        remove_object();
    }
    else
    {
        remove_single_herb();
        decrease_volume(Single_volume);
        decrease_weight(Single_weight);
        if (objectp(master_bundle))
        {
            master_bundle->remove_one_herb(Key);
        }

    }

    return 1;
}


/*
 * Function name: decrease_volume
 *
 * Description  : Decreases volume of bundle when removing herb
 *
 *
 * Arguments: int - volume
 * Returns: none
 */
public void
decrease_volume(int v)
{
    Volume -= v;
    add_prop("_obj_i_volume", Volume);
}


/*
 * Function name: decrease_weight
 *
 * Description  : Decreases weight of bundle when removing herb
 *
 *
 * Arguments: int - weight
 * Returns: none
 */
public void
decrease_weight(int w)
{
    Weight -= w;
    add_prop("_obj_i_weight", Weight);
}


/*
 * Function name: remove_single_herb
 *
 * Description  : Removes herb from bundle when herb
 *  is used as spell component. If it is the last herb, clone
 *  a wrap and remove bundle.
 *
 * Arguments: none
 * Returns: none
 */
public void
remove_single_herb()
{
    int n;
    n = query_qty();
    Decay_times = Decay_times[1..1] + Decay_times[2..n];
    Herb_qty -= 1;
}


/*
 * Function name: add_herb
 *
 * Description  : Sets the herb file
 *
 * Arguments: string - filename
 * Returns: none
 */
public void
add_herb(string h)
{
    Herb_file = h;
}


/*
 * Function name: add_herb_name
 *
 * Description  : Sets the herb's real name for use
 * in spellcasting components.
 *
 * Arguments: string
 * Returns: none
 */
public void
add_herb_name(string s)
{
    Herb_name = s;
}


/*
 * Function name: add_short
 *
 * Description  : Sets the short, pshort, names
 *
 * Arguments: string - plural of herb
 * Returns: none
 */
public void
add_short(string s)
{

    Herb_short = "small bundle of " + s;

    set_short("small bundle of " + s);
    set_pshort("small bundles of " + s);
    set_pname("small bundles of " + s);
    add_pname("bundles");
    add_name("small bundle of " + s);
    add_name("bundle");
}


/* Format is:
*  player_name*time*random_int
*
* The reason for the random integer on the end is because the
* time() function is only to the second. If someone wraps more
* than one bundle in one second, the first key would be overwritten.
*/
public string
make_key()
{
    return this_player()->query_name() + "*" + time() +
            "*" + random(10000);
}

public void
add_to_master()
{
    object o;

    Key = make_key();

    o = find_object(MASTER_BUNDLE);
    if (!objectp(o))
    {
         write("This bundle won't save. Please bug it.\n");
    }
    else
    {
        o->add_bundle(Key, Herb_file, Decay_times);
    }
}



public void
add_weight(int w)
{
    Weight += w;
    add_prop("_obj_i_weight", Weight);
}

public void
add_volume(int v)
{
    Volume += v;
    add_prop("_obj_i_volume", Volume);
}

public void
add_decays(int *d)
{
    Decay_times = d;
    Herb_qty = sizeof(Decay_times);
}


public void
set_single_volume(int v)
{
    Single_volume = v;
}

public void
set_single_weight(int w)
{
    Single_weight = w;
}


// We overload restart_decay and make it do nothing.
void
restart_decay()
{
    ;
}

/*
 * Function name: start_decay
 * Description:   We overload start_decay and make it do nothing.
 */
void
start_decay()
{
    ;
}


/*
 * Function name: get_bundle_ref
 *
 * Description  : Finds herb bundle object from string description
 *
 * Arguments: string - bundle to find
 * Returns: object or int 0
 */
public mixed
get_bundle_ref(string str)
{
    object o;

    o = present(str, this_player());
    return o;

}


public string
query_herb_file()
{
    return Herb_file;
}


public int
query_qty()
{
    return Herb_qty;
}

public mixed
query_decays()
{
    return Decay_times;
}


void
add_id(string s)
{
        set_id_long("This is a bundle of herbs wrapped in cloth. You " +
        "can 'unwrap bundle' when you are ready to use or sell the " +
        "herbs in individually.\n" +"Wrapped inside you see:\n" + s);
}

void
add_unid(string s)
{
        set_unid_long("This is a bundle of herbs wrapped in cloth. You " +
        "can 'unwrap bundle' when you are ready to use or sell the " +
        "herbs in individually.\n" +"Wrapped inside you see:\n" + s);
}

public int
is_bundle()
{
    return 1;
}

public int
count_herbs()
{
    return sizeof(Decay_times);
}


public void
give_wrap()
{
    object wrap;

    wrap = clone_object(WRAP);
    wrap->move(this_player());
}


/*
 * Function name: injest_it
 *
 * Description  : Override eat
 *
 * Arguments: string
 * Returns: 1/0
 */
void
injest_it(string str)
{
        write("You've got a big mouth but it won't quite fit.\n");

}
/*
 * Function name: do_unwrap
 *
 * Description  : Unwrap bundle and create herbs
 *
 * Arguments: string
 * Returns: 1/0
 */
public int
do_unwrap(string str)
{
    mixed *o_list;
    int i, index, qty, *decays;
    object herb, master_bundle;
    object bundle_to_unwrap = 0;
    string herb_file;

    if (!stringp(str))
    {
        write("Unwrap a bundle maybe?\n");
        return 1;
    }

    if ((!parse_command(str, all_inventory(this_player()), "%i", o_list)))
    {
        write("Unwrap what? Bundle?\n");
        return 1;
    }

    index = o_list[0];

    if (index == 0)   // don't allow "unwrap all bundles" or "unwrap bundles"
    {
        write("You can only unwrap one bundle at a time. Slow down.\n");
        return 1;
    }
    if (index > 0)    // allow "unwrap bundle"
    {
        if (index > 1) // don't allow "unwrap two bundles"
        {
            write("You can only unwrap one bundle at a time. Slow down.\n");
            return 1;
        }

        // Try unwrapping first, then second etc.
        o_list = filter(o_list[1..], &->is_bundle());
        for (i = 0; i < sizeof(o_list); i++)
        {
            bundle_to_unwrap = o_list[i];
            break;
        }
        if (!bundle_to_unwrap)
        {
            write("You can't seem to unwrap your " + str + "\n");
            return 1;
        }
    }
    else       // e.g. allow "unwrap second bundle"
    {
        if (catch(!o_list[-index]->is_bundle()))
            {
                write("You don't have a " + str + " you can unwrap.\n");
                return 1;
            }
        bundle_to_unwrap = o_list[-index];
    }

    qty = bundle_to_unwrap->count_herbs();
    herb_file = bundle_to_unwrap->query_herb_file();
    decays = bundle_to_unwrap->query_decays();
    // write (qty + herb_file + "\n");
    for (i=0; i < qty; i++)
    {
        herb = clone_object(herb_file);
        herb->set_decay_time(decays[i]);
	if (decays[i] % 2)
	   herb->force_dry();
        herb->move(this_player());
    }

    write("You unwrap your " + bundle_to_unwrap->short() + ".\n");
    say(QCTNAME(TP) + " unwraps a " + bundle_to_unwrap->short()  + ".\n");

    give_wrap();

    master_bundle = find_object(MASTER_BUNDLE);
    if (objectp(master_bundle))
        master_bundle->remove_bundle(Key);
    bundle_to_unwrap->remove_object();
    return 1;
}


void
init()
{
    add_action(do_unwrap, "unwrap");
    // add_action(do_eat, "eat");
}


/*
 * Function name: query_herb_recover
 * Description:   Return the recover strings for changing herb variables.
 */
string
query_herb_recover()
{
    string str;

    str = "#h_h#" + Key + "#";
    return str;
}


/*
 * Function name: init_herb_recover
 * Description:   Initialize the herb variables at recover.
 */
void
init_herb_recover(string arg)
{
    object herb, master_bundle;
    mixed bundle;
    string h_plural, foobar;
    int w, v;

    sscanf(arg, "%s#h_h#%s#%s", foobar, Key, foobar);

    if (!objectp(master_bundle = find_object(MASTER_BUNDLE)))
    {
        write("Bundle not found\n");
        return ;
    }

    Herb_file = master_bundle->query_file(Key);
    Decay_times = master_bundle->query_decays(Key);
    Herb_qty = sizeof(Decay_times);
    herb = clone_object(Herb_file);
    add_id(herb->query_id_long());
    add_unid(herb->query_unid_long());


    h_plural = herb->query_plural_short();
    // Some herbs don't have plural set
    if (!stringp(h_plural))
    {
        h_plural = herb->short() + "s";
    }

    Herb_short = "small bundle of " + h_plural;
    set_short(Herb_short);

    set_pshort("small bundles of " + h_plural);
    set_pname("small bundles of " + h_plural);
    add_pname("bundles");
    add_name("small bundle of " + h_plural);
    add_name("bundle");

/*
    Herb_short =  h_plural + " in a bundle";
    set_short(Herb_short);
    set_pshort(h_plural + " in bundles");
    set_pname(h_plural + " in bundles");
    add_pname("bundles");
    add_name(h_plural + " in a bundle");
    add_name("bundle");
*/

    // Add weight and volume of bundle's cloth itself
    w = herb->query_prop("_obj_i_weight");
    v = herb->query_prop("_obj_i_volume");
    set_single_weight(w);
    set_single_volume(v);
    Weight = w * Herb_qty;
    Volume = v * Herb_qty;

    add_prop("_obj_i_weight", Weight + 4);
    add_prop("_obj_i_volume", Volume + 10);
    add_herb_name(herb->query_herb_name());
    herb->remove_object();

}


/*
 * Function name: query_recover
 * Description:   A default query_recover() for herbs.
 * Returns:	  A default recovery string.
 */
string
query_recover()
{
    return MASTER + ":" + query_herb_recover();
}


/*
 * Function name: init_recover
 * Description:   A default init_recover() for herbs.
 * Arguments:	  arg - String with variables to recover.
 */
void
init_recover(string arg)
{
    init_herb_recover(arg);
}

