/* Stralle @ Genesis 040226
 */

#pragma strict_types

inherit "/std/container";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>

int contains_water;

void
create_container()
{
    set_name("phial");
    add_name("_std_potion_vial");
    set_short("@@dshort");
    set_pshort("@@dpshort");
    set_adj(({"small", "empty"}));
    set_long("@@get_long");
    add_prop(CONT_I_MAX_VOLUME, 100);
    add_prop(CONT_I_MAX_WEIGHT, 250);
    add_prop(CONT_I_VOLUME, 50);
    add_prop(CONT_I_WEIGHT, 50);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_I_VALUE, 24);
}

void
describe_contents(object for_obj, object *obarr)
{
    for_obj->catch_tell(show_sublocs(for_obj));
    
    if (sizeof(obarr) > 0)
    {
        for_obj->catch_tell("The " + short() + " contains " +
            COMPOSITE_DEAD(obarr) + ".\n");
    }
}

string
dshort()
{
    return contains_water ? "small phial" : "small empty phial";
}

string
dpshort()
{
    return contains_water ? "small phials" : "small empty phials";
}

void
set_contains_water()
{
    contains_water = 1;
}

varargs mixed
query_adj(int arg)
{
    if (arg && contains_water)
        return ({ "small" });

    return ::query_adj(arg);
}

string
get_long()
{
    if (contains_water)
        return "A small phial, containing blackened water that sparkles.\n";
    else
        return "A small empty phial, suitable for filling liquid into it.\n";
}

void
init_recover(string arg)
{
    string str;
    int t;
    
    if (sscanf(arg, "%s#wa#%d#wa%s", str, t, str) == 3)
        contains_water = t;
}

string
query_recover()
{
    return MASTER + ":#wa#" + contains_water + "#wa#";
}
