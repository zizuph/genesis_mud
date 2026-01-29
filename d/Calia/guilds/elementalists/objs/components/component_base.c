/*
 * Base File for the Spell Components used by the Elementalist Guilds of Calia
 *
 * This is the base file that spell components will inherit from.
 * It provides a few basic things like name and query functions that
 * allow a component to be identified uniquely by other items in
 * the game, such as the belt of pouches sold by Raspatoon.
 *
 * Created by Petros, July 2012
 */

inherit "/std/heap";

#include <stdproperties.h>
#include <macros.h>

// Prototypes
public void         set_component_type(string type);
public string       query_component_name();
public void         set_id_long(string str);
public void         set_unid_long(string str);

// Global Variables
public string       m_component_type = "";
static string       id_long,        /* the description of identified component */
                    unid_long;      /* the description of unidentif. component */

/*
 * Function:    query_is_elementalist_component
 * Description: Returns true always to indicate that this is a component
 *              of the Elementalist guild.
 */
public int
query_is_elementalist_component()
{
    return 1;
}

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
    set_adj(({"black", "blue"}));
    set_unid_long("This is an unidentified spell component.\n");
    set_id_long("This is an identified spell component.\n");
}

public nomask void
create_heap()
{
    set_name("component");
    
    set_heap_size(1);    
    set_long("@@long_description");

    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_SELL, 1);
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
    string component_name = query_component_name();

    // Now set the specifics for names, adjectives, and props
    add_prop(HEAP_S_UNIQUE_ID, component_name);
    add_name("_" + m_component_type + "_component_");
    add_adj(m_component_type);
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

public string
query_component_name()
{
    return query_component_type() + " component";
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
 * Function:    query_elementalist_spell_component
 * Description: An identification function that allows other
 *              objects to easily identify objects that are actually
 *              elementalist spell components.
 */
public int
query_elementalist_spell_component()
{
    return 1;
}

static object last_player;
static int last_state;


/*
 * Function name: can_id_component
 * Description  : This little function is called each time the component is referred
 *                to by a player, to check if (s)he identifies it or not.
 * Arguments    : object player - The player, defaults to this_player()
 * Returns      : int - 1 for identification, else 0.
 */
varargs int
can_id_component(object player = this_player())
{
    /* We cache the last check */
    if (last_player == player)
        return last_state;

    int can = 0;
    
    string component_type_match = query_component_type();
    switch (component_type_match) 
    {
        case "syndyasmos":
        case "aeria":
        case "diabrecho":
        case "gu":
        case "psuchae":
        case "pyros":
            can = 1;  
            break;

        default:
            foreach (object spellobj : player->query_spellobjs())
            {
                if (spellobj->query_spell_name() == component_type_match)
                {
                    can = 1;
                    break;
                }
            }
            break;
    }

    last_player = player;
    last_state = can;

    return can;
}

/*
 * Function name: long_description
 * Description  : This is an VBFC function for the set_long in the component,
 *                which tests if the player examining it can identify it, before
 *                returning the appropriate long-description. To make this
 *                work, you must be sure to do set_id_long(str) and
 *                set_unid_long(str) from the create_component() function.
 * Returns      : string - the long description.
 */
nomask string
long_description()
{
    return can_id_component() ? id_long : unid_long;
}

/*
 * Function Name: parse_command_id_list
 * Description  : Used by parse_command to find the names of this item. It
 *                verifies whether the player can identify this component.
 * Returns      : string * - An array of the names for this component.
 */
public string *
parse_command_id_list()
{
    if (can_id_component())
        return ::parse_command_id_list() + ({ query_component_name() });
    else
        return ::parse_command_id_list();
}

/*
 * Function Name: parse_command_plural_id_list
 * Description  : Used by parse_command to find the names of this item. It
 *                verifies whether the player can identify this component.
 * Returns      : string * - An array of the names for this component.
 */
public string *
parse_command_plural_id_list()
{
    if (can_id_component())
        return ::parse_command_plural_id_list() + ({ LANG_PWORD(query_component_name()) });
    else
        return ::parse_command_plural_id_list();
}

/*
 * Function name: set_id_long
 * Description:   Set the long description you see for identified components.
 * Arguments:     string str - The description
 */
public void
set_id_long(string str)
{
    id_long = str;
}

/*
 * Function name: query_id_long
 * Description:   The long description if you can id the component.
 * Returns:       string - The long description
 */
public string
query_id_long()
{
    return id_long;
}

/*
 * Function name: set_unid_long
 * Description:   Set the long description you see if you cannot identify the
 *		  component.
 * Arguments:     string str - The long description
 */
public void
set_unid_long(string str)
{
    unid_long = str;
}

/*
 * Function name: query_unid_long
 * Description:   Query the long description you get if you cannot identify
 *		  the component.
 * Returns:   	  string - The unidentified long description
 */
public string
query_unid_long()
{
    return unid_long;
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

