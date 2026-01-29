/*
 * Genesis Magic System Gem Shard
 *
 * A gem shard is a portion of a gem that is obtained through the
 * shatter gems spell. this allows a single gem to be used for
 * multiple spells.
 *
 * Created by Petros, April 2010
 */

#include <stdproperties.h>
#include <macros.h>

#include "/d/Genesis/gems/gem.h"

inherit "/d/Genesis/gems/gem";
inherit "/d/Sparkle/area/city/lib/utility_functions";

public void
create_gems()
{
    config_gems("shard", "shards", "clear", 1, 
        GEM_COMMON, 1, 1);

    add_prop(OBJ_I_NO_SELL, "You can't sell a shattered gem.\n");    

    set_long("@@default_gem_long@@ This is a standard gem shard from "
        + "an unknown gem.\n");
}

/*
 * Function:    query_gem_shard
 * Description: Convenience function to indicate that this is a
 *              gem shard, and not just a gem.
 */
public int
query_gem_shard()
{
    return 1;
}

/*
 * Function:    config_shards
 * Description: This configures this shard object to be based on an actual
 *              gem file. The argument passed in should be one of the gem
 *              files in /d/Genesis/gems/obj.
 *              Example: config_shards("amethyst")
 * Returns      0/1 - failure/success
 */
public int
config_shards(string gemname)
{
    setuid();
    seteuid(getuid());
    object master_gem;    
    if (!objectp(master_gem = safely_load_master_file(GEM_OBJECT(gemname))))
    {        
        // Must be a bad gem file.
        return 0;
    }

    gem_name = gemname; // set the gem name correctly
    string shard_type = "shard_" + master_gem->query_gem_type();
    string shard_ptype = "shard_" + master_gem->query_gem_ptype();
    string shard_colour = master_gem->query_gem_colour();
    int shard_rarity = master_gem->query_gem_rarity();
    int shard_weight = max(1, master_gem->query_prop(HEAP_I_UNIT_WEIGHT) / 5);
    int shard_volume = max(1, master_gem->query_prop(HEAP_I_UNIT_VOLUME) / 5);
    int shard_value = max(1, master_gem->query_prop(HEAP_I_UNIT_VALUE) / 5);
    
    remove_name("clear_shard");
    remove_adj("clear");
    config_gems(shard_type, shard_ptype, shard_colour, shard_value, shard_rarity, shard_volume, shard_weight);
    add_name("shard");
    add_pname("shards");
    add_name(master_gem->query_name());
    add_pname(master_gem->query_pname());
    add_adj( ({ master_gem->query_name() }) );
    set_short(shard_colour + " " + master_gem->query_name() + " shard");
    set_pshort(shard_colour + " " + master_gem->query_name() + " shards");
    string default_long, shard_long;
    sscanf(master_gem->long(), "%s.%s", default_long, shard_long);
    set_long("@@default_gem_long@@" + shard_long);
    
    return 1;
}

/*
 * Function name: config_split
 * Description  : When a part of this heap is split, we make sure the new
 *                heap is made into the correct type of shard as well by
 *                setting the correct heap unique id.
 * Arguments    : int new_num - the number of coins in this new heap.
 *                object orig - the heap we are split from.
 */
public void
config_split(int new_num, object orig)
{
    ::config_split(new_num, orig);

    config_shards(orig->query_gem_name());
}

/*
 * Function name: query_auto_load
 * Description  : Shards are autoloading. This function is called to find
 *                out what shard type they are. It returns the shard type.
 * Returns      : string - the auto-load string.
 */
public string
query_auto_load()
{
    /* Don't auto load if we are about to destroy. */
    if (query_prop(TEMP_OBJ_ABOUT_TO_DESTRUCT))
        return 0;

    return (MASTER + ":" + num_heap() + "," + query_gem_name());
}

/* 
 * Function name: init_arg
 * Description  : Called when autoloading. It will set the type of shard
 * Arguments    : string arg - the auto-load argument.
 */
void
init_arg(string arg)
{
    int size;
    string gemname;

    if (sscanf(arg, "%d,%s", size, gemname) == 2)
    {
        config_shards(gemname);
        set_heap_size(size);
    }
}
