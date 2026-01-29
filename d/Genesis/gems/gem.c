/*
 * /d/Genesis/std/gems.c
 *
 * This is the heap object for gems.
 */

#pragma strict_types

inherit "/std/heap";
inherit "/lib/keep";

#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include "gem.h"

static int gem_rarity = GEM_COMMON,     /* The rarity of the gem */
           random_placement = 1;        /* If the gem can be randomly placed */
static string gem_name;
static string gem_type = "";
static string gem_ptype = "";
static string gem_colour = "";

/*
 * Function name: query_gem
 * Description:   indicate that this object is a gem
 * Returns:       1
 */
public nomask int
query_gem()
{
    return 1;
}

/*
 * Function name: query_gem_rarity
 * Description:   Get the gem's rarity
 * Returns:       The rarity
 */
public int
query_gem_rarity()
{
    return gem_rarity;
}

/*
 * Function name: query_gem_name
 * Description  : Returns the "name" of the gem, this is the name of the file
 *                (without .c) that defines this gem.
 * Returns      : string - the name.
 */
public string
query_gem_name()
{
    return gem_name;
}

/*
 * Function name: query_gem_colour
 * Description  : Returns the colour of the gem.
 * Returns      : string - the colour.
 */
public string
query_gem_colour()
{
    return gem_colour;
}

/*
 * Function name: query_gem_type
 * Description  : Returns the type of the gem.
 * Returns      : string - the type.
 */
public string
query_gem_type()
{
    return gem_type;
}

/*
 * Function name: query_gem_ptype
 * Description  : Returns the plural type of the gem.
 * Returns      : string - the plural type.
 */
public string
query_gem_ptype()
{
    return gem_ptype;
}

/*
 * Function name: query_random_placement
 * Description  : Returns true if the gem can be randomly
 *                distributed over the game.
 *                This should be the case for nearly all gems.
 */
public int
query_random_placement()
{
    return random_placement;
}

/*
 * Function name: set_random_placement
 * Description  : Set if this gem can be randomly placed by the gem master
 */
 public void
 set_random_placement(int state)
 {
     random_placement = state;
 }

/*
 * Function name: config_gems
 * Description:   Configure a gem. The name "colour_name" is automatically
 *                added for easy identification.
 * Arguments:     string type   - the gem's type (name)
 *                string ptype  - plural form of the gem's type
 *                string colour - the gem's colour
 *                int rarity    - the gem's rarity
 *                int value     - the gem's value in copper coins
 *                int volume    - the gem's volume
 *                int weight    - the gem's value
 */
varargs public void
config_gems(string type, string ptype, string colour, int value,
    int rarity, int volume, int weight)
{
    string c = (strlen(colour) ? colour + " " : "");

    if (!ptype)
    {
        ptype = LANG_PWORD(type);
    }

    gem_rarity = rarity;
    gem_type = type;
    gem_ptype = ptype;
    gem_colour = colour;

    set_name(type);
    set_pname(ptype);
    set_short(c + type);
    set_pshort(c + ptype);
    add_adj(type);

    if (strlen(colour))
    {
            set_adj(colour);
        /* All gems by default have their colour plus type as name with an
        * underscore for external identification. */
        add_name(colour + "_" + type);
    }

    add_prop(HEAP_S_UNIQUE_ID, "_gem_" + type + "_" + colour);
    add_prop(HEAP_I_UNIT_VALUE, value);

    mark_state();
    add_prop(HEAP_I_UNIT_VOLUME, volume);
    add_prop(HEAP_I_UNIT_WEIGHT, weight);
    update_state();
}

/*
 * Function name: create_gems
 * Description  : Called at creation of the gem(s).
 */
public void
create_gems()
{
}

/*
 * Function name: default_gem_long
 * Description:   Give a simple, default description for the gems
 * Returns:       The description
 */
public string
default_gem_long()
{
    if (num_heap() > 1)
    {
        return "These are " + plural_short() + ".";
    }

    return "It is " + LANG_ADDART(singular_short()) + ".";
}

/*
 * Function name: create_heap
 * Description  : Constructor for heap objects.
 */
public nomask void
create_heap()
{
    gem_name = extract(MASTER, strlen(GEM_OBJ_DIR), -1);

    set_name("gem");
    set_pname("gems");
    set_keep(1);
    set_heap_size(1);

    set_long("@@default_gem_long@@\n");

    create_gems();

    if (query_prop(HEAP_I_UNIT_VALUE) >= 144)
    {
        add_name("_gem_ingredient");
    }
}

/*
 * Function name: reset_gems
 * Description  : Redefine this to reset the gem heap.  Note that you
 *                will have to call enable_reset() in create_gems() for
 *                this to be called.
 */
public void
reset_gems()
{
}

/*
 * Function name: reset_heap
 * Description  : Called to make this heap reset. You may not mask this
 *                function, so use reset_gems() instead.
 */
public nomask
void reset_heap()
{
    reset_gems();
}

/*
 * Function name: query_auto_load
 * Description  : Get the autoload string for the gems
 * Returns      : string - the auto-load string.
 */
public string
query_auto_load()
{
    /* Don't auto load if we are about to destroy. */
    if (query_prop(TEMP_OBJ_ABOUT_TO_DESTRUCT))
        return 0;

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
