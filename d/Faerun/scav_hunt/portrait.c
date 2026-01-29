/*
 * Random item for the Scavanger hunt
 * Coded by Finwe September 2003
 * Originally coded for the Shire, cleaned up in October 2015
 */

inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    seteuid(getuid());
    set_name("portrait");
    set_adj("faded");
    set_short("faded portrait");
    set_long("This is "+short()+" of a young family. The paint has faded" +
		"over time, but an outline of the people is still visible on " +
		"the square canvas. There are impressions  of a man, his wife, and two " +
		"young children. In the background, it looks like " +
		"a meadow was painted.\n");

	add_prop(OBJ_I_WEIGHT, 1191);
	add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 400);
}
