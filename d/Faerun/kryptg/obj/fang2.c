/*
 * Vampire fangs, found on corpses
 * -- Finwe, October 2007
 */

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <stdproperties.h>

inherit "/std/object";

#define FANG_SHAPE  ({"chiseled", "sharp", "chipped", "dull", "long", "short"})
#define FANG_COLOR  ({"yellow", "dark", "clear", "transluscent", "black", "white"})

public int loaded;
public string gfang_shape = "", gfang_color = "";

public void
setup_fangs(string shape , string color)
{
    if (loaded)
	return;

    loaded = 1;

    if (!strlen(shape))  shape = one_of_list(FANG_SHAPE);
    if (!strlen(color))  color = one_of_list(FANG_COLOR);

    gfang_shape = shape;
    gfang_color = color;

    add_adj(gfang_shape);
    add_adj(gfang_color);
    set_short(gfang_shape + " " + gfang_color + " fang");
    set_long("This is a vampire's fang. It is " +
	gfang_shape + " and " + gfang_color +
	" colored. The fang was cut from the corpse of a vampire.\n");
}

public void
create_object(void)
{
    add_name(({"fang"}));
    add_prop(OBJ_I_WEIGHT, 10); 
    add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 12);

    set_alarm(0.5, 0.0, &setup_fangs("",""));
}

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

public void init_arg(string arg)
{
    string *arglist = explode(arg, "#");
    setup_fangs(arglist[0], arglist[1]);
}
