/*
 * Vampire fangs, found on corpses
 * Thanks for Mercade and Lucius for their help
 * -- Finwe, October 2007
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit "/std/object";
/* These defines create a list of adjectives for the fangs */
#define FANG_SHAPE  ({"chiseled", "sharp", "chipped", "dull", "long", "short"})
#define FANG_COLOR  ({"yellow", "dark", "clear", "transluscent", "black", "white"})

/* Var set to fang was recovered */
public int loaded;
/* Global vars for shape and color */
public string gfang_shape = "", gfang_color = "";

/* sets up the fangs when recovered or create */
public void
setup_fangs(string shape, string color)
{

    if (loaded)
	    return;

    loaded = 1;

/* If this routine was called from create_object, get a new adjective */
    if (!strlen(shape))  
        shape = one_of_list(FANG_SHAPE);
    if (!strlen(color))  
        color = one_of_list(FANG_COLOR);

/* Assigns global vars here. If the fang was recovered, 
 * then shape and color will be received when passed and
 * assigned here.
 */
    gfang_shape = shape;
    gfang_color = color;

/* Assigns the global vars to the adjectives */
    add_adj(gfang_shape);
    add_adj(gfang_color);
/* sets up the short description */
    set_short(gfang_shape + " " + gfang_color + " fang");
/* sets the long description */
    set_long("This is a vampire's fang. It is " + gfang_shape + " and " + 
        gfang_color + " colored. The fang came from the corpse of a vampire.\n");
}

public void
create_object(void)
{
    add_name(({"fang"}));
    add_prop(OBJ_I_WEIGHT, 10); 
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 12);
/* passes blank values to setup_fangs() so new descriptions are set up */
    set_alarm(0.5, 0.0, &setup_fangs("",""));
}

/* Called to save the global color and shape variables so they recover */
public mixed
query_auto_load(void)
{
    return (MASTER + ":" + gfang_shape + "#" + gfang_color);
}

public string
query_recover(void)
{
    return 0;
}

/* Initializes the recovery routines. gfang_shape is arglist[0] and 
 * gfang_color is arglist[1]. These values are passed to setup_fangs
 * when the fangs are recovered.
 */
public void init_arg(string arg)
{
    string *arglist = explode(arg, "#");
    setup_fangs(arglist[0], arglist[1]);
}
