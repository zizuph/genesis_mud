#include <stdproperties.h>

inherit "/std/object";
inherit "/lib/keep";

string c_id, c_info;
int c_value, c_used, c_muse;


/* Unique idendity */
public string query_component_id()
{
	return c_id;
}

public void set_component_id(string new_id)
{
	c_id = new_id;
}

/* Value for which it can be bought in hunters shop */
public int query_component_value()
{
	return c_value;
}

public void set_component_value(int new_value)
{
	c_value = new_value;
}

/* Additional component info. */
public string query_component_info()
{
	return c_info;
}

public void set_component_info(string new_info)
{
	c_info = new_info;
}

/* Does this item stays with the hunter, or it's moved to a trap. */
public void set_multiple_use(int new_muse = 1)
{
	c_muse = new_muse;
}

public int query_multiple_use()
{
	return c_muse;
}

/* Does this item stays with the hunter, or it's moved to a trap. */
public void set_used(int new_used = 1)
{
	c_used = new_used;
}

public int query_used()
{
	return c_used;
}

void create_component()
{}

void create_object()
{
	set_name("component");
	set_short("component");
	set_long("Non descripted component.\n");
	set_keep(1);
	add_prop(OBJ_I_VALUE, 1);
	create_component();
}
	