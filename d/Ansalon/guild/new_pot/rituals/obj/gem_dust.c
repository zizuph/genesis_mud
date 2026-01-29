/*
 * Gem dust
 *
 * Gem dust is what happens when a caster takes a gem and grinds it into
 * dust.  This allows a single gem to be used for multiple spells.
 *
 * Created by Zizuph, November 2022
 *
 */
#pragma strict_types

#include <stdproperties.h>
#include <macros.h>

inherit "/std/heap";

private string gem;

/*
 * Function:    query_gem_dust
 * Description: Convenience function to indicate that this is a
 *              gem dust object
 */
public int
query_gem_dust(void)
{
    return 1;
}

int is_ritual_object()
{
    return 1;
}


public string query_gem()
{
    return gem;
}

public void create_heap()
{
    add_prop(HEAP_I_UNIT_WEIGHT, 2);
    add_prop(HEAP_I_UNIT_VOLUME, 2);
}

public string
long_description(void)
{
    string my_verb = "consist";

    if (num_heap() == 1)
        my_verb += "s";
    
    return "This " + my_verb + " of the crushed dust of "
        + LANG_ADDART(gem) + ".\n";
}

/*
 * Function:    gem_init
 * Description: This configures this powder object to be based on an actual
 *              gem file.
 * Returns      0/1 - failure/success
 */
public int
dust_init(string desired_gem)
{
    gem = desired_gem;

    string under_name = implode(explode(gem, " "), "_");
    
    string gem_type = explode(gem, " ")[-1];

    add_name("_leftover_" + under_name + "_dust");
    add_name("_leftover_" + gem_type + "_dust");

    add_adj("pinch");
    add_adj("pinches");
    
    foreach(string word : explode(desired_gem, " "))
    {
        add_adj(word);
    }
    add_name("dust");
    add_pname("dusts");

    set_short("pinch of " + gem +  " dust");
    set_pshort("pinches of " + gem + " dust");
    set_long(long_description);

    add_prop(HEAP_S_UNIQUE_ID, "_leftover_dust_" + under_name);
    
    return 1;
}

void
config_split(int new_num, object orig)
{
    ::config_split(new_num, orig);
    
    dust_init(orig->query_gem());
}


/*
 * Function name: query_recover
 * Description  : Get the recover string, so that the gem type is 
 *                preserved.
 * Returns      : string - the recover string.
 */
public string
query_recover(void)
{
    /* Don't auto load if we are about to destroy. */
    if (query_prop(TEMP_OBJ_ABOUT_TO_DESTRUCT))
        return 0;

    return (MASTER + ":" + num_heap() + "," + query_gem());
}

/*
 * Function name: init_recover
 * Description  : Re-initialise the race and organ.
 * Arguments    : string - the recover arguments.
 */
public void
init_recover(string arg)
{
    int size;
    string recover_gem;

    if (sscanf(arg, "%d,%s", size, recover_gem) == 2)
    {
        dust_init(recover_gem);
        set_heap_size(size);
    }
}

