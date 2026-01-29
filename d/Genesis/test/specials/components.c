/*
 * Spell components
 * ================
 * Spell components are found and used automatically by the spell
 * casting routine.
 * Necessary components are specified with the set_spell_ingredients()
 * function, which accepts an array of mixed values, one for each
 * component expected.  An object pointer element designates that
 * particular object as a component.  A function pointer element will
 * be called with two arguments, an array of possible component objects
 * and an array of components already found; the function should return
 * an object pointer to the component found.  A string element will
 * first be checked against the true names of any herbs that the caster
 * is able to identify; if no matching herbs are found, parse_command()
 * is used to try to match an object.  Note that only one object will be
 * matched:  strings of the form "two swords" or "second stick" will not
 * work.  "two swords" can, however, be simulated with two elements,
 * "sword" and "sword".
 * Components may define the function use_component(), which can be used
 * to implement special behaviour in an object when it is used as a
 * component (reusable components, for example).  If use_component()
 * returns 1, the component will not be destroyed.
 */

#include <macros.h>
#include <stdproperties.h>

#define TEMP_I_COMPONENT_CHECKED "_temp_i_component_checked"

public int
filter_components(object component, object caster)
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
    ingrs->remove_prop(TEMP_I_COMPONENT_CHECKED);
    ingrs->force_heap_merge();
}

public object *
get_item_search_list(object caster)
{      
    int i;
    object *inv = all_inventory(caster);

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
 *                the caster.  Note that you should always call 
 *                restore_components() for the components this function
 *                returns (once you are done with them).
 * Arguments:     object caster - the caster
 *                mixed component_list - the components to be found (see above
 *                                       documentation)
 *                objet *itemlist - An array of items to search for components
 * Returns:       The ingredients found, or 0 if all were not found
 */
public varargs mixed
find_components(object caster, mixed component_list, object *itemlist)
{
    int i, j;
    object new_heap, component_found;
    object *found_ingrs, *items;
    function f;

    if (functionp(component_list))
    {
        return component_list(caster);
    }

    if (!itemlist)
    {   
        itemlist = get_item_search_list(caster);
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
                filter_components(itemlist[j], caster) &&
                itemlist[j]->do_id_check(caster))
            {
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
                items = filter(items[1..], &filter_components(, caster));
                
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
