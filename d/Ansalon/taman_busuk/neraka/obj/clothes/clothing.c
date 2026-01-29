#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>

inherit "/std/object";
inherit "/lib/wearable_item";

static string colour, fabric;

public void create_clothing() { }

public void
set_colour(string col)
{
    if (stringp(colour))
        remove_adj(explode(colour, " "));

    colour = col;

    add_adj(explode(colour, " "));
}
        
public string
query_colour()
{
    return colour;
}

public string
query_Colour()
{
    return capitalize(colour);
}

public void
set_fabric(string fab)
{
    if (stringp(fabric))
        remove_adj(explode(fabric, " "));
        
    fabric = fab;

    add_adj(explode(fabric, " "));
}

public string
query_fabric()
{
    return fabric;
}

public string
query_Fabric()
{
    return capitalize(fabric);
}

public nomask void
create_object()
{
	set_name("clothing");
	add_name("garment");

	set_slots(A_TORSO);

	set_layers(1);
	set_looseness(6);

	set_colour("white");
	set_fabric("wool");

	set_short("@@query_colour@@ @@query_fabric@@ clothing");

	create_clothing();
}

void
leave_env(object from, object to)
{
	wearable_item_leave_env(from, to);
	::leave_env(from, to);
}

public string query_clothing_auto_load() { return 0; }
public void init_clothing_arg(string arg) { }

string
query_auto_load()
{
    string s,t;

    s = MASTER + ":" + colour + "|" + fabric;
    
    if (stringp(t = query_clothing_auto_load()))
        s += "|" + t;
    return s;
}

public void
init_arg(string arg)
{
    string *arr;

    arr = explode(arg, "|");

    if (sizeof(arr) > 0)
        set_colour(arr[0]);
    if (sizeof(arr) > 1)
        set_fabric(arr[1]);
    if (sizeof(arr) > 2)
        init_clothing_arg(implode(arr[2..],"|"));
}
        
        
