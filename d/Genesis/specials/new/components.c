/*
 * Ability components
 * ================
 * Ability components are found and used automatically by the ability
 * casting routine.
 * Necessary components are specified with the set_ability_ingredients()
 * function, which accepts an array of mixed values, one for each
 * component expected.  An object pointer element designates that
 * particular object as a component.  A function pointer element will
 * be called with two arguments, an array of possible component objects
 * and an array of components already found; the function should return
 * an object pointer to the component found.  A string element will
 * first be checked against the true names of any herbs that the actor
 * is able to identify; if no matching herbs are found, parse_command()
 * is used to try to match an object.  Note that only one object will be
 * matched:  strings of the form "two swords" or "second stick" will not
 * work.  "two swords" can, however, be simulated with two elements,
 * "sword" and "sword".
 * Components may define the function use_component(), which can be used
 * to implement special behaviour in an object when it is used as a
 * component (reusable components, for example).  If use_component()
 * returns 1, the component will not be destroyed.
 *
 * To force an ability to use components, simply add
 * set_ability_components(use_ability_components);
 * set_ability_ingredients(({ "nose" }));
 * set_ability_optional_ingredients(({ "finger" }));
 *
 *
 * 2022-06-14 Zizuph - added support for spells with only optional ingredients.
 *
 *
 */

#include <files.h>
#include <macros.h>
#include <composite.h>
#include <stdproperties.h>

#define TEMP_I_COMPONENT_CHECKED "_temp_i_component_checked"
#define WIZ_IGNORE_INGREDIENTS_PROP "_wizard_ignore_spell_ingredients"

static mixed    Ingredients,        /* The list of ingredients needed */  
                Ingredients_opt;    /* List of optional ingredients */
static mapping  Ingredients_found;

/*
 * Function name:   hook_use_ingredients
 * Description:     This function should return the message that will be printed
 *                  to the caster when he/she has used some ingredients.
 * Arguments:       (object *) ingrs - The ingredients that will be used.
 * Returns:         Nothing
 */
public void
hook_use_ingredients(object *ingrs)
{
    if (sizeof(ingrs))
    {
        write("You sacrifice " + COMPOSITE_ALL_DEAD(ingrs) + ".\n");
    }
} /* hook_use_ingredients */


/*
 * Function name:   hook_no_ingredients_fail
 * Description:     Return the message that should be printed when the caster
 *                  doesn't have the right ingredients
 * Arguments:       (mixed *) ingredients_needed
 * Returns:         Nothing
 */
public void
hook_no_ingredients_fail(mixed *ingredients_needed)
{
    write("Sorry, but you are not properly prepared to do that!\n");
} /* hook_no_ingredients_fail */

/*
 * Function name:   hook_no_identify_herb_ingredient
 * Description:     Return the message that should be printed when the caster
 *                  can't identify an herbal ingredient
 * Arguments:       (object *) unidentified_herb
 * Returns:         Nothing
 */
public void
hook_no_identify_herb_ingredient(object unidentified_herb)
{
    write("Sorry, but you have no idea how to use one of your herbal "
    + "ingredients!\n");
} /* hook_no_identify_herb_ingredient */

/*
 * Function name:   hook_ingredients_lost_fail
 * Description:     Return the message that should be printed when the caster
 *                  if an ingredient is lost
 * Arguments:       (object *) ingredients_found
 * Returns:         Nothing
 */
public void
hook_ingredients_lost_fail(object *ingredients_found)
{
    write("You have lost some of the ingredients!\n");
} /* hook_ingredients_lost_fail */

/*
 * Function:    ignore_ability_ingredients
 * Description: Function that allows a person to ignore ability ingredients
 *              By default, npcs and wizards who have a special property
 *              set will be able to ignore ability ingredients.
 */
public int
ignore_ability_ingredients(object actor)
{
    if (!objectp(actor))
    {
        return 0;
    }
    
    if (actor->query_npc())
    {
        // NPCs always ignore ingredients
        return 1;
    }

    else if ((actor->query_wiz_level()
              || wildmatch("*jr", actor->query_real_name()))
             && actor->query_prop(WIZ_IGNORE_INGREDIENTS_PROP))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function:    query_ability_ingredients_description
 * Description: Returns a string description of the ingredients. Can be used
 *              in messages to actors about what is actually required
 *              for this ability.
 */
public string
query_ability_ingredients_description()
{
    return 0;
}

/*
 * Function name: set_ability_ingredients
 * Description:   Set the ingredients needed for the ability.
 * Arguments:     1. (mixed *)  An array of ingredients needed for the ability
 *                   (function) Function that produces an ingredient list
 */
public varargs void
set_ability_ingredients(mixed list)
{
    Ingredients = list;
}

/*
 * Function:    query_ability_ingredients
 * Description: Returns an string array of ingredients or 0 if there are
 *              none defined. It will properly handle if Ingredients variable
 *              is a function as well.
 * Arguments    bShowAlways - If set to non-zero, will not call the ignore
 *                            function. Allows one to always return the total
 *                            ingredients.
 */
public string *
query_ability_ingredients(int bShowAlways = 0)
{
    string * ingredients;
    object player = this_player();
    
    if (!bShowAlways && ignore_ability_ingredients(player))
    {
        return ingredients;
    }
    
    if (functionp(Ingredients))
    {
        function ingredients_func = Ingredients;
        ingredients = ingredients_func(this_player());
    }
    else if (objectp(Ingredients))
    {
        ingredients = ({ Ingredients });
    }
    else if (pointerp(Ingredients))
    {
        ingredients = Ingredients;
    }
    
    return ingredients;
}

/*
 * Function name: set_ability_ingredients
 * Description:   Set the optional ingredients for the ability.
 * Arguments:     1. (mixed *)  An array of ingredients needed for the ability
 *                   (function) Function that produces an ingredient list
 */
public varargs void
set_ability_optional_ingredients(mixed list)
{
    Ingredients_opt = list;
}

/*
 * Function:    query_ability_optional_ingredients
 * Description: Returns an string array of ingredients or 0 if there are
 *              none defined. It will properly handle if Ingredients_opt
 *              variable is a function as well.
 * Arguments    bShowAlways - If set to non-zero, will not call the ignore
 *                            function. Allows one to always return the total
 *                            ingredients.
 */
public string *
query_ability_optional_ingredients(int bShowAlways = 0)
{
    string * ingredients;
    object player = this_player();

    if (!bShowAlways && ignore_ability_ingredients(player))
    {
        return ingredients;
    }
    
    if (functionp(Ingredients_opt))
    {
        function ingredients_func = Ingredients_opt;
        ingredients = ingredients_func(this_player());
    }
    else if (objectp(Ingredients_opt))
    {
        ingredients = ({ Ingredients_opt });
    }
    else if (pointerp(Ingredients_opt))
    {
        ingredients = Ingredients_opt;
    }
    
    return ingredients;
}

public int
filter_components(object component, object actor)
{
    return !component->query_prop(TEMP_I_COMPONENT_CHECKED);
}

public object
prepare_heap_component(object component)
{
    component->split_heap(1);
    return component->force_heap_split();
}

public void
restore_components(object *ingrs)
{
    // If you're using a heap, please make sure that you have
    // properly configured config_split in the heap. If you don't,
    // you may end up with strangely heaped components, especially
    // if you change HEAP_S_UNIQUE_ID
    ingrs->remove_prop(TEMP_I_COMPONENT_CHECKED);
    ingrs->force_heap_merge();
}

public object *
get_item_search_list(object actor)
{      
    int i;
    object *inv = all_inventory(actor);

    i = sizeof(inv);
    while (i--)
    {
        if (inv[i]->query_prop(CONT_I_HOLDS_COMPONENTS) &&
            !(inv[i]->query_prop(CONT_I_CLOSED)))
        {
            inv += all_inventory(inv[i]);
        }
    }

    return inv;
}

/*
 * Function name: find_components
 * Description:   Search for an ingredient or a number of ingredients in
 *                the actor.  Note that you should always call 
 *                restore_components() for the components this function
 *                returns (once you are done with them).
 * Arguments:     object actor - the actor
 *                mixed component_list - the components to be found (see above
 *                                       documentation)
 *                objet *itemlist - An array of items to search for components
 * Returns:       The ingredients found, or 0 if all were not found
 */
public varargs mixed
find_components(object actor, mixed component_list, object *itemlist)
{
    int i, j;
    object new_heap, component_found;
    object *found_ingrs, *items;
    function f;

    if (functionp(component_list))
    {
        return component_list(actor);
    }

    if (!itemlist)
    {   
        itemlist = get_item_search_list(actor);
    }

    if (!sizeof(itemlist))
    {
        return (sizeof(component_list) ? 0 : ({}));
    }

    found_ingrs = ({ });

    i = sizeof(component_list);
    while (i--)
    {
        component_found = 0;

        if (!component_list[i])
        {
            restore_components(found_ingrs);
            return 0;
        }

        if (objectp(component_list[i]))
        {
            found_ingrs += ({ component_list[i] });
            component_list[i]->add_prop(TEMP_I_COMPONENT_CHECKED, 1);
            continue;
        }

        if (functionp(component_list[i]))
        {
            object ob;

            f = component_list[i];
            if (ob = f(itemlist, found_ingrs))
            {
                found_ingrs += ({ ob });
                ob->add_prop(TEMP_I_COMPONENT_CHECKED, 1);
                continue;
            }

            restore_components(found_ingrs);
            return 0;
        }

        /* We check for herbs separately because of the screwy way
         * herb identification works.
         */
        for (j = 0; j < sizeof(itemlist); j++)
        {
            if ((itemlist[j]->query_herb_name() == component_list[i]) &&
                filter_components(itemlist[j], actor))
            {
                // We no longer do a actor herb identification check here. We do it
                // instead in the ability itself so that we can give better
                // error messages.
                component_found = itemlist[j];
                break;
            }
        }

        if (!component_found)
        {
            if (parse_command(component_list[i], itemlist, "%i", items))
            {
                /* Use the first of the visible items.  Notice that we don't
                 * bother to check for "one", "two", "first", "second", etc.
                 */
                items = filter(items[1..], &filter_components(, actor));
                
                if (sizeof(items))
                {
                    component_found = items[0];
                }
            }
        }

        if (!component_found)
        {
            restore_components(found_ingrs);
            return 0;
        }

        if (component_found->query_prop(HEAP_I_IS) &&
            (new_heap = prepare_heap_component(component_found)))
        {
            itemlist += ({ new_heap });
        }

        found_ingrs += ({ component_found });
        component_found->add_prop(TEMP_I_COMPONENT_CHECKED, 1);
    }

    return found_ingrs;
}

public int
use_ability_components(object actor, mixed * targets, string arg, mixed *items,
    int pretest)
{
    string *ingredients, *optional;

    if (!mappingp(Ingredients_found))
        Ingredients_found = ([]);

    ingredients = query_ability_ingredients();
    optional = query_ability_optional_ingredients();

    if (!sizeof(ingredients) && !sizeof(optional))
        return 1;

    Ingredients_found[actor] = find_components(actor, ingredients);
    if (sizeof(Ingredients_found[actor]) != sizeof(ingredients))
    {
        hook_no_ingredients_fail(ingredients);
        if (pointerp(Ingredients_found[actor]))
        {
            // Need to remove the property
            restore_components(Ingredients_found[actor]);
        }
        return 0;
    }

    // We have to loop through the components and see if there are herbs
    // that we cannot identify
    if (sizeof(Ingredients_found[actor]))
    {
        foreach (object ingredient : Ingredients_found[actor])
        {
            if (objectp(ingredient) && IS_HERB_OBJECT(ingredient)
                && ingredient->do_id_check(actor) == 0)
            {
                hook_no_identify_herb_ingredient(ingredient);
                restore_components(Ingredients_found[actor]);
                return 0;
            }
        }
    }

    if (pretest)
    {
        if (sizeof(Ingredients_found[actor]))
            restore_components(Ingredients_found[actor]);

        return 1;
    }

    Ingredients_found[actor] += find_components(actor, optional) || ({ });

    // We may have only optional ingredients.
    if (!sizeof(ingredients))
        return 1;
    
    return sizeof(Ingredients_found[actor]);
}

public mixed
query_ability_found_components(object actor)
{
    if (mappingp(Ingredients_found) && pointerp(Ingredients_found[actor]))
        return Ingredients_found[actor];

    return ({});
}