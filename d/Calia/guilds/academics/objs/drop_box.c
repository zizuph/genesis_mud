/* 
 * Donation Box for the Academy of Elemental Arts
 *
 * This box allows others to put donations into the box, and allows Academics
 * to take them out.
 *
 * Created by Petros, December 2009
 */

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <cmdparse.h>
#include <formulas.h>
#include <composite.h>
#include "/d/Genesis/gems/gem.h"

inherit "/std/container";
inherit "/d/Sparkle/area/city/lib/utility_functions"; // for the master loading safely
inherit "/d/Genesis/specials/lib/item_recovery_lib";

// Defines
#define ACADEMIC_DONATION_TAG "_academic_donation_tag"
#define DONATION_DATA         (ACADEMIC_OBJS + "donation_data")

// Global Variables
public mapping      m_donation_data = ([ ]);

static string * academic_spells = ({
        ACADEMIC_SPELLS + "cheiropoto",
        ACADEMIC_SPELLS + "pyrofosti",
        ACADEMIC_SPELLS + "numastomo",
        ACADEMIC_SPELLS + "hydrokine",
        ACADEMIC_SPELLS + "lithodermu" });

// Prototypes
public void         add_donation_points(object player, object donated_object);
public void         deduct_donation_points(object player, object donated_object);
        
public void
save_donation_data()
{
    save_map(m_donation_data, DONATION_DATA);
}

public void
load_donation_data()
{
    m_donation_data = restore_map(DONATION_DATA);    
}

void
create_container()
{
    set_name("box");
    set_adj("marble");
    add_adj("donation");
    set_long("This " + short() + " is hewn out of solid marble and looks "
        + "to be rather immobile. Someone painstakingly hollowed out "
        + "the marble lode and formed it into something that can fit "
        + "items donated to the Academy. There is an opening at the top "
        + "of the box large enough to fit most items. A small bronze "
        + "plaque at the front of the box reads: 'Donations for the "
        + "Academy of Elemental Arts'.\n");

    add_prop(CONT_I_MAX_WEIGHT, 5000000);
    add_prop(CONT_I_MAX_VOLUME, 5000000);
    add_prop(CONT_I_WEIGHT, 500000);
    add_prop(CONT_I_VOLUME, 500000);
    add_prop(CONT_I_RIGID, 1);
    add_prop(OBJ_M_NO_GET, "The " + short() + " can't be removed" +
        " from the floor.\n");

    setuid();
    seteuid(getuid());
    
    load_donation_data();
    
    // Set the options for the item recovery library
    if (!IS_CLONE)
    {
        return;
    }
    set_enable_logging(0);
    set_enable_recovery(1);
    
    init_database();
    set_alarm(0.0, 0.0, &recover_objects_from_database()); 
}

public int
prevent_enter(object ob)
{
    if (!IS_WEAPON_OBJECT(ob)
        && !IS_ARMOUR_OBJECT(ob)
        && !IS_HERB_OBJECT(ob)
        && !IS_LEFTOVER_OBJECT(ob)
        && !IS_GEM_OBJECT(ob)
        && !IS_COINS_OBJECT(ob)
        && !ob->query_gem_shard())
	{
        write("The " + short() + " will only accept weapons, armours, "
            + "herbs, leftovers, coins, and gems.\n");
        return 1;
    }
    else if (ob->query_prop(OBJ_I_BROKEN))
    {
        write("You wouldn't want to put the " + ob->short() + " in there -" +
            " it's useless!\n");
        return 1;
    }

    return ::prevent_enter(ob);
}

public int
prevent_leave(object ob)
{
    if (TP->query_wiz_level())
    {
        // Wizards are always allowed to remove things.
        return 0;
    }
    
    if (!IS_MEMBER(TP) && 
        (ob->query_prop(ACADEMIC_DONATION_TAG) != this_player()->query_real_name()))
    {
        write("You can only remove items from the receptable if you" +
            " put them there yourself or are a member of the Academy!\n");
        return 1;
    }

    return ::prevent_leave(ob);
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    
    add_rack_entry(ob);
    
    if (!objectp(from) || !IS_PLAYER_OBJECT(from))
    {
        return;
    }
    
    ob->add_prop(ACADEMIC_DONATION_TAG, from->query_real_name());
    add_donation_points(from, ob);
}

public void
leave_inv(object ob, object to)
{
    ::leave_inv(ob, to);

    remove_rack_entry(ob);

    if (!objectp(to)
        || !IS_PLAYER_OBJECT(to)
        || !strlen(ob->query_prop(ACADEMIC_DONATION_TAG)))
    {
        return;
    }
        
    string donator = "yourself";
    if (to->query_real_name() != ob->query_prop(ACADEMIC_DONATION_TAG))
    {
        donator = capitalize(ob->query_prop(ACADEMIC_DONATION_TAG));
    } 

    to->catch_tell("The " + ob->short() + " was donated by " + donator
        + ".\n");
    deduct_donation_points(to, ob);
}

public int
calculate_points(object donated_object)
{
    if (!IS_GEM_OBJECT(donated_object)
        && !IS_HERB_OBJECT(donated_object)
        && !IS_LEFTOVER_OBJECT(donated_object)
        && !donated_object->query_gem_shard())
    {
        // We only give points for spell component types
        return 0;
    }

    string * all_ingredients = ({ });
    // Loop through the spells and get the list of spell components being used
    foreach (string spell : academic_spells)
    {
        if (!objectp(safely_load_master_file(spell)))
        {
            continue;
        }
        all_ingredients += spell->query_spell_ingredients(1);
    }
    
    int isIngredient = 0;
    foreach (string name : all_ingredients)
    {
        if (donated_object->id(name))
        {
            isIngredient = 1;
            break;
        }
    }
    
    int point_value = 1;
    // Only Ingredients count as points
    int multiplier = IS_HEAP_OBJECT(donated_object) ? donated_object->num_heap() : 1;
    if (!isIngredient)
    {
        // Non-ingredients get a base value of 1 point.
        return point_value * multiplier;
    }
    
    if (IS_LEFTOVER_OBJECT(donated_object))
    {
        point_value = 2;
    }
    else if (IS_HERB_OBJECT(donated_object))
    {
        point_value = 5;
    }
    else if (IS_GEM_OBJECT(donated_object))
    {
        point_value = 10;
    }
    else if (donated_object->query_gem_shard())
    {
        point_value = 1;
    }
    
    return point_value * multiplier;
}

public void
add_donation_points(object player, object donated_object)
{
    string name = player->query_real_name();
    int value = calculate_points(donated_object);
    m_donation_data[name] = m_donation_data[name] + value;
    save_donation_data();
}

public void
deduct_donation_points(object player, object donated_object)
{
    string name = player->query_real_name();
    int value = calculate_points(donated_object);
    m_donation_data[name] = m_donation_data[name] - value;
    save_donation_data();
}

public int
get_donation_points_for_player(mixed player)
{
    load_donation_data();
    
    string name;
    if (stringp(player))
    {
        name = player;
    }
    else if (objectp(player) && IS_PLAYER_OBJECT(player))
    {
        name = player->query_real_name();
    }
    
    return m_donation_data[name];
}
