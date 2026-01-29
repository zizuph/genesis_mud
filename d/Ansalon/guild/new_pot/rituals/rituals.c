/* Stralle @ Genesis 011227
 *
 * Rituals Interface
 * 
 * This rituals interface is used by the Priests of Takhisis to perform
 * rituals. Rituals are actions which transform an object in some fashion.
 * This may involve adding a shadow to the object, or creating completely
 * new objects from existing objects.
 *
 * This interface is being re-written in December 2011 because the old
 * interface was too restrictive to allow for different rituals to share
 * the same components.
 *
 * Each ritual should be defined by inheriting std_ritual. Each ritual will
 * define the following things:
 *   - The number of priests required to run the ritual
 *   - The difficulty of the ritual
 *   - The ingredients necessary for the ritual
 *   - What the ritual should produce
 *   - The messages that should occur during the ritual
 *   - How the ritual should clean up the altar afterwards
 *
 * Originally by Stralle, December 27, 2001
 * Rewritten by Petros, December 2011
 */

#pragma strict_types

#include "../guild.h"
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <tasks.h>
#include <wa_types.h>

inherit "/d/Sparkle/area/city/lib/utility_functions";
inherit "/d/Genesis/specials/components";

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#ifdef DEBUG
#undef DEBUG
#define DEBUG(x)    send_debug_message("pot_ritual", x)
#endif

#define STANDING_DIFF   100
#define GUILD_RITUAL_DIR (GUILDDIR + "rituals/rituals/")
#define TEMP_I_COMPONENT_CHECKED "_temp_i_component_checked"

mapping gRituals = ([ ]);
object gAltar, gChantee, *gOthers;

/*
 * Function:    load_rituals
 * Description: Goes through the rituals directory and loads all rituals
 *              that are valid. It ignores the standard ritual object.
 */
public void
load_rituals()
{
    // We first clear all the rituals
    gRituals = ([ ]);
    
    // Now look through every object and try to load the ritual object
    setuid();
    seteuid(getuid());
    string * ritual_files = get_dir(GUILD_RITUAL_DIR);
    object current_ritual_object;
    foreach (string ritual_file : ritual_files)
    {
        if (!objectp(current_ritual_object = safely_load_master_file(GUILD_RITUAL_DIR + ritual_file)))
        {
            continue;
        }
        
        string ritual_name = current_ritual_object->query_name();
        if (!strlen(ritual_name))
        {
            continue;
        }
        
        // Add the name of the ritual object to the list of registered rituals
        gRituals[ritual_name] = MASTER_OB(current_ritual_object);
    }
}

/*
 * Function:    set_altar
 * Description  Sets the location of the altar. This is the item/container
 *              that should contain the spell components.
 */
public void
set_altar(object altar)
{
    gAltar = altar;
}

/*
 * Function:    query_altar
 * Description: Returns the currently set altar location.
 */
public object
query_altar()
{
    return gAltar;
}

/*
 * Function:    set_chantee
 * Description: The chantee is the person that initiates the chant
 *              for the ritual. This function sets it so that the
 *              chantee can be retrieved/determined during the ritual.
 */
public void
set_chantee(object chantee)
{
    gChantee = chantee;
}

/*
 * Function:    query_chantee
 * Description: Returns the person currently initiating the chanting.
 */
public object
query_chantee()
{
    return gChantee;
}

/*
 * Function:    set_others
 * Description: A ritual can have many priests participating in the process
 *              This sets the list of priests that were in the room when the
 *              initial priest started chanting.
 */
public void
set_others(object * others)
{
    gOthers = others;
}

/*
 * Function:    query_others
 * Description: Returns the list of people that are currently participating
 *              in the ritual with the chantee.
 */
public object *
query_others()
{
    return gOthers;
}

/*
 * Function:    guild_skill
 * Description: This checks the chantee to get a value for how well they
 *              should be able to "chant" based on their PS_SKILL_POINTS
 *              value.
 */
public int
guild_skill()
{
    return query_chantee()->exp_to_stat(query_chantee()->query_skill(PS_SKILL_POINTS));
}

/*
 * Function:    formula
 * Description: Runs a resolve_task against the difficulty level set for the
 *              particular ritual. This is used to determine a "result" that 
 *              can be used in determining whether the ritual was a success
 *              or not.
 */
public int
formula(int diff)
{
    return query_chantee()->resolve_task(diff, ({ TS_OCC, guild_skill }));
}    

/*
 * Function:    sort_ritual_by_ingredients_descending
 * Description: allows the sort_array call for rituals to sort the ritual
 *              list from most number of components to least. This will
 *              ensure that the best match for components for a ritual gets
 *              executed.
 */
private int
sort_ritual_by_ingredients_descending(object a, object b)
{
    return sizeof(b->query_ingredients()) - sizeof(a->query_ingredients());    
}

/*
 * Function:    get_sorted_ritual_list
 * Description: This function returns a list of rituals sorted by the greatest
 *              number of ingredients to the least. This helps to ensure that
 *              we match on the best ingredient list when running the ritual.
 */
public object *
get_sorted_ritual_list()
{
    string * ritual_files = m_values(gRituals);
    object * ritual_list = ({ });
    foreach (string ritual_file : ritual_files)
    {
        object ritual_object = safely_load_master_file(ritual_file);
        if (objectp(ritual_object))
        {
            ritual_list += ({ ritual_object });
        }
    }
    return sort_array(ritual_list, sort_ritual_by_ingredients_descending);
}

/*
 * Function:    parse_ingredient
 * Description: Given a list of items and an ingredient string to look for,
 *              this function will return the object that represents the
 *              ingredient. If it can't be found, it'll return 0. It accepts
 *              a few types of ingredient strings.
 *                 - W<weapon type>. For example, Wclub means to look for a club type.
 *                 - A<armour type>. for example "A" + A_ROBE for a robe.
 *                 - /path/file. This is a fully qualified path to the object
 *                 - _<property>. For example _live_is_undead is a property that can be checked.
 *                 - name - can be either the name of an herb or an object
 * Returns:     object - the ingredient object
 *              or 0   - ingredient cannot be found
 */
public object
parse_ingredient(string name)
{
    object * items_to_check = all_inventory(query_altar());
    items_to_check = filter(items_to_check, &operator(!=)(1) @ &->query_prop(TEMP_I_COMPONENT_CHECKED));  
    switch (name[0])
    {
        case 'A':
            foreach (object item : items_to_check)
            {
                if (item->query_at() == atoi(name[1..]))
                {
                    item->add_prop(TEMP_I_COMPONENT_CHECKED, 1);
                    return item;
                }
            }
            break;
            
        case 'W':
            int wt = W_FIRST + member_array(name[1..], W_NAMES);
            foreach (object item : items_to_check)
            {
                if (item->query_wt() == wt)
                {
                    item->add_prop(TEMP_I_COMPONENT_CHECKED, 1);
                    return item;
                }
            }
            break;

        case '/':
            foreach (object item : items_to_check)
            {
                if (MASTER_OB(item) == name)
                {
                    item->add_prop(TEMP_I_COMPONENT_CHECKED, 1);
                    return item;
                }
            }
            break;

        case '_':
            foreach (object item : items_to_check)
            {
                if (item->query_prop(name))
                {
                    item->add_prop(TEMP_I_COMPONENT_CHECKED, 1);
                    return item;
                }
            }
            break;

        default:
            // We use the spell components class to find the components to
            // properly handle heaps and other things.
            // Remember to call restore_components when the components are
            // not needed.
            object * components = find_components(query_altar(), ({ name }), items_to_check);
            if (sizeof(components))
            {
                return components[0];
            }

            break;
    }

    return 0;
}

/*
 * Function:    get_ritual_ingredient_objects
 * Description: Returns a list of ingredient objects for a particular
 *              ritual. Note that the list of ingredients will have
 *              the component property set, which means they will need
 *              to have restore_components called if it is going to not
 *              be consumed.
 */
public object *
get_ritual_ingredient_objects(object ritual_master_object)
{
    string * ritual_ingredients = ritual_master_object->query_ingredients();
    object * ingredient_objects = ({ });
    foreach (string ritual_ingredient : ritual_ingredients)
    {
        object ingredient = parse_ingredient(ritual_ingredient);
        if (!objectp(ingredient))
        {
            continue;
        }
        ingredient_objects += ({ ingredient });
    }
    
    // If not all components were found, then we restore them and return
    // 0. This is very different from an empty set, which is a ritual
    // that doesn't require any components.
    if (sizeof(ingredient_objects) != sizeof(ritual_ingredients))
    {
        DEBUG("Did not find all components for ritual.");
        restore_components(ingredient_objects);
        return 0;
    }
    
    return ingredient_objects;
}

/*
 * Function:    validate_ritual_requirements
 * Description: Checks the ingredients of the specified ritual and see
 *              if all the ingredients are present on the altar. Also checks
 *              to make sure that there are enough priests to perform the
 *              ritual in the room.
 * Returns:     0 - ritual could not be found
 *             -1 - don't have enough priests to perform the ritual
 *             -2 - some ingredient is missing
 *              1 - successfully have all the ingredients 
 */
public int
validate_ritual_requirements(string ritual)
{
    int x, size;
    string ingr;
    
    if (!gRituals[ritual])
    {
        return 0;
    }
    
    // Test to see if the ritual object can be loaded properly
    object ritual_master_object = safely_load_master_file(gRituals[ritual]);
    if (!objectp(ritual_master_object))
    {
        return 0;
    }
    
    /* Not enough priests performing */
    if ((1 + sizeof(query_others())) < ritual_master_object->query_minimum_priests())
    {
        return -1;
    }
    
    object * ingredient_objects = get_ritual_ingredient_objects(ritual_master_object);
    if (!ingredient_objects)
    {
        // Don't have all the ingredients.
        restore_components(ingredient_objects);
        return -2;
    }
    
    restore_components(ingredient_objects);
    return 1;
}

int
perform_ritual(string ritual, int result)
{
    /* Load GUILDDIR + "rituals/rituals/<name>"
     *
     * This contains the descriptions of the ritual, the effect and so on
     * Much like spells
     * Really, this function should only take care of loading the effect
     */

    switch (validate_ritual_requirements(ritual))
    {
        case 0:
            DEBUG("No such ritual");
            /* No such ritual */
            return 0;
        case -1:
            DEBUG("Not enough priests");
            /* Not enough priests */
            return 0;
        case -2:
            DEBUG("Missing ingredient");
            /* Something amiss with the ingredients */
            return 0;
        case 1:
            DEBUG("Success");
            if (random(query_chantee()->query_standing()) < STANDING_DIFF)
            {
                query_chantee()->catch_tell("As you are about to speak " +
                    "the words for your prayer you begin questioning " +
                    "if you got it all right and decide it best to " +
                    "start from anew.\n");
                query_chantee()->adjust_standing(RND_RANGE(-35, 20));
                return 0;
            }

            object ritual_object = safely_load_master_file(gRituals[ritual]);
            query_chantee()->add_mana(-(ritual_object->query_difficulty() / 5));
            GUILD_ADMIN->log(query_chantee(), "rituals", "chants " + ritual + ", success: " + result);
            ritual_object->do_ritual(query_altar(), query_chantee(), query_others(), this_object(), result);
            return 1;
    }
}

/* In the abbey (altar is a container)
 *
 * inherit "this_file";
 * ...
 * altar = clone_object("altar");
 * altar->move(TO);
 * set_altar(altar);
 */

/*
 * Function:    reset_ritual_variables
 * Description: Resets all the variables that determine the state of the
 *              ritual.
 */
public void
reset_ritual_variables()
{
    set_chantee(0);
    set_others(0);
}

/*
 * Function:    do_chant
 * Description: This is the action function that gets called when a priest
 *              initiates the "chant" command.
 */
public int
do_chant(string str)
{
    object *pots, *arr;
    int x, size;
    string *indices;

    if (!MEMBER(this_player()) && !this_player()->query_wiz_level())
        return 0;

    if (query_chantee())
    {
        notify_fail("Better not disrupt " + QTNAME(query_chantee()) + ".\n");
        return 0;
    }

    if (!query_altar())
    {
        notify_fail("With no altar around it would be no use.\n");
        return 0;
    }
    
    if (!sizeof(all_inventory(query_altar())))
    {
        notify_fail("With no contents in the altar it would be no use.\n");
        return 0;
    }
    
    pots = filter(FILTER_OTHER_LIVE(all_inventory(environment(query_altar()))),
        &->query_pot_member());

    if (sizeof(pots) > 1)
    {
        pots -= ({ this_player() });
        for (x = 0, size = sizeof(pots) ; x < size ; x++)
        {
            pots[x]->catch_msg("In unison with " +
                COMPOSITE_LIVE(pots - ({ pots[x] })) +
                " you begin chanting.\n");
        }

        arr = FILTER_PRESENT_LIVE(all_inventory(environment(query_altar())));
        arr -= pots;
        if (sizeof(arr))
        {
            arr->catch_msg("In unison " + COMPOSITE_LIVE(pots) +
                " begins chanting.\n");
        }
    }
    else
    {
        write("You begin chanting.\n");
        say(QCTNAME(this_player()) + " begins chanting.\n");
    }

    set_chantee(this_player());
    set_others(pots);

    // Loop through each ritual and try to perform each one
    object * ritual_list = get_sorted_ritual_list();
    foreach (object ritual : ritual_list)
    {
        if (perform_ritual(ritual->query_name(), formula(ritual->query_difficulty())))
        {
            return 1;
        }
    }
    
    if (sizeof(pots) > 1)
    {
        pots -= ({ this_player() });
        write("Nothing appears to happen.\n");

        for (x = 0, size = sizeof(pots) ; x < size ; x++)
        {
            pots[x]->catch_msg("Nothing appears to happen.\n");
        }
    }
    else
        write("Nothing appears to happen.\n");

    reset_ritual_variables();

    return 1;
}    
            

void
init_rituals()
{
    add_action("do_chant", "chant");
}
