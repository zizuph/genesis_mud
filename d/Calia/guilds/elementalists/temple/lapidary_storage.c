/*
 * Lapidary Storage Room for the Elemental Temple of Calia
 *
 * This room stores the actual gems that are bought and sold in the
 * temple. It will try to maintain a minimum amount that can be
 * defined and configured to support the guilds.
 *
 * Created by Petros, April 2010
 *
 * Added a maximum cap on gems auto-spawned, based on rarity.
 * - Arman Kharas, Feb 2019
 */
 
#include "/d/Genesis/gems/gem.h"
#include <stdproperties.h>
#include "defs.h"

inherit TEMPLE_ROOM_BASE;
inherit "/lib/store_support.c";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

// Global Variables
public mapping gem_minimums = ([
    "agate"         :   2,
    "alexandrite"   :   2,
    "amber"         :   11,
    "amethyst"      :   10,
    "aquamarine"    :   2,
    "beryl"         :   2,
    "beryl_red"     :   2,
    "bloodstone"    :   12,
    "carnelian"     :   17,
    "chalcedony"    :   13,
    "chrysoprase"   :   2,
    "coral"         :   24,
    "diamond"       :   5,
    "diamond_black" :   4,
    "emerald"       :   2,
    "garnet"        :   9,
    "jade"          :   5,
    "jasper"        :   2,
    "lapis"         :   15,
    "moonstone"     :   10,
    "onyx"          :   14,
    "opal"          :   10,
    "opal_fire"     :   10,
    "pearl"         :   10,
    "pearl_black"   :   10,
    "peridot"       :   2,
    "pyrite"        :   2,
    "quartz"        :   14,
    "ruby"          :   2,
    "sapphire"      :   2,
    "sea_agate"     :   2,
    "spinel"        :   5,
    "spinel_blue"   :   3,
    "spinel_red"    :   7,
    "topaz"         :   6,
    "topaz_yellow"  :   12,
    "tourmaline"    :   2,
    "tourmaline_pink"   :   2,
    "turquoise"     :   10,
]);

// Rare gems will not continuously be spawned.

public mapping gem_clone_max = ([
    "agate"         :   50,
    "alexandrite"   :   5,
    "amber"         :   40,
    "amethyst"      :   25,
    "aquamarine"    :   25,
    "beryl"         :   25,
    "beryl_red"     :   5,
    "bloodstone"    :   25,
    "carnelian"     :   35,
    "chalcedony"    :   40,
    "chrysoprase"   :   35,
    "coral"         :   45,
    "diamond"       :   10,
    "diamond_black" :   5,
    "emerald"       :   10,
    "garnet"        :   35,
    "jade"          :   20,
    "jasper"        :   45,
    "lapis"         :   20,
    "moonstone"     :   30,
    "onyx"          :   30,
    "opal"          :   20,
    "opal_fire"     :   10,
    "pearl"         :   20,
    "pearl_black"   :   15,
    "peridot"       :   20,
    "pyrite"        :   50,
    "quartz"        :   50,
    "ruby"          :   10,
    "sapphire"      :   15,
    "sea_agate"     :   5,
    "spinel"        :   35,
    "spinel_blue"   :   20,
    "spinel_red"    :   20,
    "topaz"         :   30,
    "topaz_yellow"  :   15,
    "tourmaline"    :   25,
    "tourmaline_pink"   :   5,
    "turquoise"     :   40,
]);
     
public void
create_temple_room() 
{
    set_short("Lapidary Storage Room");
    set_long("This is the storage room for the temple lapidary.\n");

    setuid();
    seteuid(getuid());

    max_items = 40; // a bit of a hack. set_max_items restricts to maximum 30
    
    reset_room();
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    store_update(ob);
}

void
reset_room()
{
    object * all_gems = filter(all_inventory(this_object()), &->query_gem());
    foreach (string gemname, int minimum : gem_minimums)
    {
        send_debug_message("lapidary_storage", "Processing " + gemname
            + " with a minimum of " + minimum + ".");
        if (!minimum)
        {
            // If there is no minimum for this gem, we don't do anything for
            // this particular gem.
            continue;
        }

        int maximum = gem_clone_max[gemname];

        object * matching_gems = filter(all_gems, &operator(==)(gemname) @ &->query_gem_name());

        if (!sizeof(matching_gems))
        {
            send_debug_message("lapidary_storage", gemname + " does not exist in this "
                + "room. Cloning " + GEM_OBJECT(gemname) + ".");
            // Gem doesn't exist in this store room.
            object new_gem = clone_object(GEM_OBJECT(gemname));
            new_gem->set_heap_size(minimum);
            new_gem->move(this_object(),1);
            continue;
        }
        
        object current_gem = matching_gems[0];
        if (current_gem->num_heap() < minimum)
        {
            // If we have less than the minimum, we reset it back to the minimum
            current_gem->set_heap_size(minimum);
        }
        else
        {
            // Already has some gems. We just gradually add more gems here up to max.
            // Chance of gem spawn per room reset is 25%

            if((current_gem->num_heap() < maximum) && (!random(4)))
            {
                int gem_increase = random(3);
                // find_player("arman")->catch_msg("[Lapidary] " + gemname + 
                //    " increased by " +gem_increase+ ".\n");
                current_gem->set_heap_size(current_gem->num_heap() + gem_increase);
            }
        }
    }
}
