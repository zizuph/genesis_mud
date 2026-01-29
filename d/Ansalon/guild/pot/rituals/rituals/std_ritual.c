/*
 * Base Ritual
 * 
 * This is the base standard ritual object. Inherit this to create your
 * own ritual.
 *
 * These are the basic steps to creating your ritual:
 * 1. inherit from this object
 * 2. set a name for the ritual (set_name) inside create_ritual
 * 3. override and define these following functions
 *    a. ritual_specific_effect
 *    b. perform_ritual
 *    c. query_ingredients
 *    d. query_difficulty
 *    e. query_minimum_priests
 *    f. exclude_ritual_products
 *    g. query_object_to_enchant (required if enchanting object)
 *
 * Rewritten by Petros, December 2011
 */

#include "../rituals.h"
#include "../../guild.h"
#include <filter_funs.h>
#include <macros.h>
#include <composite.h>
#include <wa_types.h>
#include <tasks.h>

string gName, gFail;
int gType, gResult;
object gAltar, gChantee, gRitualRoom, *gOthers;

/* Various set and query functions
 *****************************************************************
 */
/* Function name: set_result
 * Description:   The result as per the resolve_task in rituals.c
 * Arguments:     int result - the result
 */
public void
set_result(int result)
{
    gResult = max(0, min(100, result));
}

public int
query_result()
{
    return gResult;
}

public void
set_fail(string fail)
{
    gFail = fail;
}

public string
query_fail()
{
    return gFail;
}

public void
set_chantee(object chantee)
{
    gChantee = chantee;
}

public object
query_chantee()
{
    return gChantee;
}

public void
set_others(object * others)
{
    gOthers = others;
}

public object *
query_others()
{
    return gOthers;
}

public void
set_name(string str)
{
    gName = str;
}

public string
query_name()
{
    return gName;
}

public void
set_altar(object altar)
{
    gAltar = altar;
}

public object
query_altar()
{
    return gAltar;
}

/*
 * Function:    set_ritual_room
 * Description: Sets the ritual room object so that one can refer back to
 *              it for specific component functions.
 */
public void
set_ritual_room(object ritual_room)
{
    gRitualRoom = ritual_room;
}

/*
 * Function:    query_ritual_room
 * Description: Returns the currently set ritual room so that one can refer
 *              back to it for specific component functions
 */
public object
query_ritual_room()
{
    return gRitualRoom;
}

/*
 * Function:    query_difficulty
 * Description: Returns the difficulty level (task-based) by which the
 *              ritual should be compared against the PS_SKILL_POINTS of
 *              the chantee.
 */
public int
query_difficulty()
{
    // By default, set the ritual to be something simple.
    return TASK_SIMPLE;
}

/* Function name: chantee
 * Description:   Similar to actor(). Writes a message to the chantee.
 * Arguments:     string - the message to print
 */
public void
chantee(string str)
{
    query_chantee()->catch_msg(str + "\n");
}

/* Function name: others
 * Description:   Similar to all2act(). Writes a message to the others
 *                performing the ritual in unison with the chantee.
 * Arguments:     string str - the first part if any to write
 *                string str1 - the part after the name of the chantee
 */
public varargs void
others(string str, string str1)
{
    if (sizeof(query_others()))
    {
        query_others()->catch_msg((stringp(str) ? str : "") +
            (stringp(str) ? QTNAME(query_chantee()) :
            QCTNAME(query_chantee())) + str1 + "\n");
        if (str)
            query_chantee()->catch_msg(COMPOSITE_LIVE(query_others()) +
                " chants in unison with you.\n");
    }
}

/* Function name: onlookers
 * Description:   Similar to all(). Writes a message to everyone not
 *                performing a ritual
 * Arguments:     string str - the message
 */
public void
onlookers(string str, string str1)
{
    object *oblist, tp;

    tp = this_player();
    set_this_player(query_chantee());
    oblist = FILTER_OTHER_LIVE(all_inventory(environment(query_chantee())) -
        query_others());
    set_this_player(tp);

    if (!sizeof(oblist))
        return;

    if (sizeof(query_others()))
        oblist->catch_msg(str + "," + str1 + "\n");
    else
        oblist->catch_msg(str + ".\n");
}

/*
 * Function:    reset_ritual_variables
 * Description: Resets all the variables used to set the ritual state.
 *              This allows future runs to be clean.
 */
public void
reset_ritual_variables()
{
    // First reset the ritual room's variables
    query_ritual_room()->reset_ritual_variables();
    
    // Now reset all the variables for this ritual
    set_altar(0);
    set_chantee(0);
    set_others(0);
    set_ritual_room(0);
    set_result(0);
    set_fail(0);
}

/* Function name: sanity_check
 * Description:   Checks to see if we still can perform the ritual
 * Returns:       int - 1/0, still valid or not
 */
public int
sanity_check()
{
    object *arr = ({ query_chantee() }) + query_others();

    switch (query_ritual_room()->validate_ritual_requirements(query_name()))
    {
        case 0:
            arr->catch_tell("Ritual became non-existant " +
                "while performing. Most odd.\n");
            break;
        case -1:
            arr->catch_tell("The ritual failed due to " +
                "the required number of priests performing changed.\n");
            break;
        case -2:
            arr->catch_tell("The contents of the altar has changed " +
                "the conditions for the ritual.\n");
            break;
        case 1:
            return 1;
    }

    return 0;
}    

/*
 * Function:    exclude_ritual_products
 * Description: Returns a list of ritual products to exclude from the
 *              ingredient list. This ensures that the product won't be
 *              removed when the ingredients are consumed.
 */
public object *
exclude_ritual_products(object * ingredients)
{
    return ({ });
}


/*
 * Function:    query_object_to_enchant
 * Description: Returns the object from the ingredients list that should
 *              be enchanted.
 */
public object
query_object_to_enchant()
{
    object * ritual_ingredients = query_ritual_room()->get_ritual_ingredient_objects(this_object());
    object * excluded_objects = exclude_ritual_products(ritual_ingredients);
    query_ritual_room()->restore_components(ritual_ingredients);
    
    if (sizeof(excluded_objects))
    {
        return excluded_objects[0];
    }
    
    return 0;
}

/*
 * Function:    consume_ingredients
 * Description: This function looks through the altar's content and consumes all the
 *              ingredients. It ensures that it doesn't consume the product of
 *              the ritual by calling exclude_ritual_products.
 */
public void
consume_ingredients()
{
    // First use the ritual interface to actually get all the applicable ingredients.
    object * ingredients = query_ritual_room()->get_ritual_ingredient_objects(this_object());
    if (!sizeof(ingredients))
    {
        // Nothing to consume.
        return;
    }
    
    // Next, we need to exclude any ingredients that are actually part of the "product"
    // of this ritual.
    object * products_to_exclude = exclude_ritual_products(ingredients);
    if (sizeof(products_to_exclude))
    {
        query_ritual_room()->restore_components(products_to_exclude);
        ingredients = ingredients - products_to_exclude;
    }
    
    // Finally, consume all the ingredients from the altar.
    ingredients->remove_object();
}

/*
 * Function:    ritual_specific_effect
 * Description: This is the function that should be overridden by the ritual
 *              to actually describe the "meat" of the ritual. It does the
 *              cloning, shadowing, and the creation of the "product" of the
 *              ritual.
 */
public void
ritual_specific_effect()
{
}

/*
 * Function:    ritual_effect
 * Description: This is the main function that controls the ritual's effects.
 *              It is a nomask function that ensures that certain things (such
 *              as ingredient consumption are properly handled.
 */
public nomask void
ritual_effect()
{
    // Call the ritual-specific effect function. This will actually perform the "meat"
    // of the ritual.
    ritual_specific_effect();
    
    if (strlen(query_fail()))
    {
        // Something happened and the ritual failed. In this case, we don't consume
        // ingredients, and we don't add any experience. Simply reset the variables
        // and return.
        reset_ritual_variables();
        return;
    }
    
    // Make sure to consumer all the ingredients that were used
    consume_ingredients();
    
    /* Give out guild internal exp. The amount is the difficulty
     * unless participating in which case it is half of that.
     */
    if (query_result())
    {
        query_chantee()->set_skill(PS_SKILL_POINTS,
            query_chantee()->query_skill(PS_SKILL_POINTS) +
            query_difficulty());
        query_chantee()->adjust_standing(RND_RANGE(10, 5));
        foreach (object other_priest : query_others())
        {
            other_priest->set_skill(PS_SKILL_POINTS, other_priest->query_skill(PS_SKILL_POINTS) + query_difficulty() / 2);
            other_priest->adjust_standing(RND_RANGE(8, 3));
        }
    }
    
    // Reset all the variables
    reset_ritual_variables();
}

/*
 * Function:    create_ritual
 * Description: This is the standard create_ritual function that all
 *              rituals can use to initialize during the creation of the
 *              master object. Override this in your own ritual to
 *              set specific properties.
 */
public void
create_ritual()
{
}     
     
/*
 * Function:    create
 * Description: Default create function. Will get called whenever this
 *              object is created. We call "create_ritual" here to make
 *              sure to have a creation function that one can override
 *              and customize
 */
public void
create()
{
    create_ritual();
}

/*
 * Function:    perform_ritual
 * Description: This is the function that will get called to do all the
 *              ritual descriptions, and the actual calling of the ritual_effect.
 *              It takes in an optional argument for the current round of the
 *              ritual (which can span many rounds).
 */
varargs void
perform_ritual(int round = 0)
{
}

/*
 * Function:    do_ritual
 * Description: This is the "start" function that gets called to actually initiate
 *              the ritual sequence. One should pass in the following arguments.
 *                - set the altar (set_altar)
 *                - set the chantee (set_chantee)
 *                - set the other priests (set_others)
 *                - set the resolve_task result (set_result)
 */
public void
do_ritual(object altar, object chantee, object * others, object ritual_room, int result)
{
    set_altar(altar);
    set_chantee(chantee);
    set_others(others);
    set_ritual_room(ritual_room);
    set_result(result);
    set_fail(0);
    
    // Start the ritual with Round 0.
    perform_ritual(0);
}

/*
 * Function:    query_ingredients
 * Description: This returns the string list of ingredients that the ritual
 *              requires. It accept a few types of ingredient strings.
 *                 - W<weapon type>. For example, Wclub means to look for a club type.
 *                 - /path/file. This is a fully qualified path to the object
 *                 - _<property>. For example _live_is_undead is a property that can be checked.
 *                 - name - can be either the name of an herb or an object
 */
public string *
query_ingredients()
{
    return ({ });
}

/*
 * Function:    query_minimum_priests
 * Description: Each ritual can have a minimum number of priests requried
 *              to perform the ritual. 
 */
public int
query_minimum_priests()
{
    return 1;
}
