inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>

void
create_object()
{
    set_name("gem");
    set_adj("sparkling");
    set_long("It is a sparkling gem, shaped vaguely like an ear.\n");

    add_prop(OBJ_I_VALUE, 1234);
}

/*
 * The following two functions will make it possible to restore the
 * gem after reboots etc.
 */
string
query_recover()
{
    return MASTER + ":";
}

void
init_recover(string arg)
{
}

/*
 * This function checks if the gem can be inserted into the specified
 * socket on the statue.  'where' is the name of the location, 'side'
 * is 0 when not specified, -1 for left and 1 for right.  Return value
 * is 0 when it cannot be used at the specified location, 1 when it
 * can be used.
 */
int
query_match(string where, int side)
{
    if (side > -1 || where != "ear")
	return 0;
    return 1;
}
