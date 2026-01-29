/*
 * The store room for the herb shop in the temple (Alister)
 *
 * This stores herbs not as objects but as recover strings for three reasons:
 *
 * 1) Saves memory
 * 2) Easy way to stop herb decay
 * 3) The store inventory can be saved over armageddon
 *
 * When a herb is extracted, a recovery is simulated by cloning the herb
 * and calling init_recover with the appropriate recover string.
 */

inherit "/std/room";

#include <stdproperties.h>
#include "/d/Ansalon/common/defs.h"

// Define this to make the store rebootable (herbs are saved over armageddon)
#define REBOOTABLE

mapping gHerbs;

void herb_store_update(object herb);
void restore_inventory();
void save_inventory();

mapping query_herb_list() { return gHerbs; }
void clear_herb_list() { gHerbs = ([ ]); }

public void
enter_inv(object ob, object from)
{
   ::enter_inv(ob, from);
   herb_store_update(ob);
}

create_room()
{
    set_short("Herb store room");
    set_long("This is the store room for the herb shop in the temple.\n");

    add_prop(OBJ_S_WIZINFO,
	"To list herb files in the store (but not individual copies), call " +
	"list_herb_files(). \n" +
	"To remove a herb, or a group of herbs, call " +
	"purge_herbs(filename, test). filename accepts wildcards - " +
	"purge_herbs(\"/d/Krynn/*\") for example will remove every Krynn " +
	"herb from the store. If test is specified, and non-zero, " +
	"only a list of herbs that would be purged will be written, " +
	"nothing will be removed.\n");

    clear_herb_list();

    set_alarm(2.0, 0.0, restore_inventory);
}

void destruct_herb(object herb)
{
/* This is unnecessary

    tell_room(this_object(),
	"The " + herb->query_short() +
	" is absorbed into the magic of the room.\n");

*/
    herb->remove_object();
}

void
herb_store_update(object herb)
{
    string master, arg, *arr;
	
    if (function_exists("create_object",herb) != "/std/herb")
	return;

    arg = herb->query_recover();

    arr = explode(arg, ":");

    master = arr[0];
    arg = implode(arr[1..], ":");

    if (pointerp(gHerbs[master]))
    {
	gHerbs[master] += ({ arg });
    }
    else
    {
	gHerbs[master] = ({ herb->query_herb_name(), herb->query_herb_value(), arg });
    }

    save_inventory();
    
    set_alarm(2.0, 0.0, &destruct_herb(herb));
}

mixed
list_herb_files()
{
    int i;
    string result = "";
    string *herbfiles;

    herbfiles = m_indexes(gHerbs);

    if (sizeof(herbfiles) == 0)
	return 0;

    for (i = 0; i < sizeof(herbfiles); i++)
    {
	result += " " + (sizeof(gHerbs[herbfiles[i]]) - 2) + " " + herbfiles[i] + "\n";
    }

    return result;
}
	
varargs mixed
purge_herbs(string herb, int test = 0)
{
    int i;
    string *herbfiles;
    string result = "";

    herbfiles = m_indexes(gHerbs) + ({ });

    if (sizeof(herbfiles) == 0)
	return 0;

    for (i = 0; i < sizeof(herbfiles); i++)
    {
    	if (wildmatch(herb, herbfiles[i]))
    	{
	    result += herbfiles[i] + "\n";
	    if (!test)
		gHerbs = m_delete(gHerbs, herbfiles[i]);
    	}
    }

    if (!test && result != "")
	save_inventory();

    return result;
}

/*
 * Function name: extract_herb
 * Description:   Creates a herb from the herb list, and removes it
 *                from the list.
 * Arguments:     name - the name of the herb to extract
 * Result:        pointer to extracted herb, or 0 if none such
 *                existed
 */
object
extract_herb(string name)
{
    int i,j;
    string *herbfiles;
    object herb;
    string recover;

    herbfiles = m_indexes(gHerbs) + ({ });

    if (sizeof(herbfiles) == 0)
	return 0;

    for (i = 0; i < sizeof(herbfiles); i++)
    {
    	j = sizeof(gHerbs[herbfiles[i]]);
    	
    	if ( j && (gHerbs[herbfiles[i]])[0] == name )
    	{
	    recover = herbfiles[i] + ":" + (gHerbs[herbfiles[i]])[j-1];
	    if (j > 3)
	    {
	    	gHerbs[herbfiles[i]] = (gHerbs[herbfiles[i]])[0..(j-2)];
	    }
	    else
	    {
	    	gHerbs = m_delete(gHerbs, herbfiles[i]);
	    }
	    herb = clone_object(herbfiles[i]);
	    if (herb)
	    {
	    	save_inventory();
	    	
	    	herb->init_recover(recover);
	    	return herb;
	    }
	    else
	    	return 0;
    	}
    }
    return 0;
}

void
save_inventory()
{
#ifdef REBOOTABLE

    setuid();
    seteuid(getuid());

    save_map(gHerbs, "/d/Ansalon/taman_busuk/neraka/temple/herb_shop_inventory");

#endif
}

void
restore_inventory()
{
#ifdef REBOOTABLE

    setuid();
    seteuid(getuid());

    gHerbs = restore_map("/d/Ansalon/taman_busuk/neraka/temple/herb_shop_inventory");

#endif
}
