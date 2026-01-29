/*
 * Base File for the Spell Components used by the Spirit Circle
 *
 * This is the base file that spell components will inherit from.
 * It provides a few basic things like name and query functions that
 * allow a component to be identified uniquely by other items in
 * the game, such as the belt of pouches sold by Raspatoon.
 *
 * Created by Petros, August 2011
 */

inherit "/std/heap";

#include <stdproperties.h>
#include <macros.h>
#include "defs.h"

// Prototypes
public void         set_component_type(string type);

// Global Variables
public string       m_component_type = "";

/*
 * Function:    create_component
 * Description: Inherit this create function in your own
 *              component to override any of the defaults.
 */
public void
create_component()
{
    // Set the component type. This should be called by the inheriting component
    // to set the proper name.
    set_component_type("generic");    
}

public nomask void
create_heap()
{
    set_name("component");
    
    set_long("This is the base component used by different gifts in the "
        + "Spirit Circle of Psuchae.\n");    
    set_heap_size(1);    

    add_prop(OBJ_M_NO_STEAL, 1);
//    add_prop(OBJ_M_NO_SELL, 1);
// Making these sellable now that the guild is closed as per Arman (AoB)   
    add_prop(OBJ_I_VALUE, 100);
    add_prop(OBJ_I_NO_STEAL,1);
    add_prop(HEAP_I_UNIT_VOLUME,1);
    add_prop(HEAP_I_UNIT_WEIGHT,1);
    add_prop(HEAP_I_UNIT_VALUE,0);
    
    // Call the create function of the inheriting object
    create_component();    
}

/*
 * Function:    set_component_type
 * Description: This sets the component type (spell that will use this 
 *              component. It will also set a bunch of things that support
 *              this component type, like heap name, object name, and
 *              adjectives.
 */
public void
set_component_type(string type)
{
    m_component_type = type;
    if (!strlen(m_component_type))
    {
        m_component_type = "generic";
    }
    
    // Clear all the names and adjectives
    remove_name(query_names());
    set_name("component");
    remove_adj(query_adj(1));
    string component_name = m_component_type + " component";

    // Now set the specifics for names, adjectives, and props
    add_adj(m_component_type);
    add_prop(HEAP_S_UNIQUE_ID, component_name);
    add_name(component_name);
    set_short(component_name);
    add_name("_" + m_component_type + "_component_");
}

/*
 * Function:    query_component_type
 * Description: Returns the component type. ie. the spell that this
 *              component will be used for.
 */
public string
query_component_type()
{
    return m_component_type;
}

/*
 * Function:    query_auto_load
 * Description: Spell components automatically load.
 */
public string
query_auto_load()
{
    return MASTER + ":" + num_heap();
}


/*
 * Function name: init_arg
 * Description:   Initialize autoloading gems
 * Arguments:     string arg - the autoload argument
 */
public void
init_arg(string arg)
{
    set_heap_size(max(1, atoi(arg)));
}

/*
 * Function:    query_scop_spell_component
 * Description: An identification function that allows other
 *              objects to easily identify objects that are actually
 *              scop spell components.
 */
public int
query_scop_spell_component()
{
    return 1;
}
