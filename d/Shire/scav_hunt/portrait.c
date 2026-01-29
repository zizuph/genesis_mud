/* 
 * Dirty picture
 * -- Finwe, September 2003
 */
  
inherit "/std/object";
#include "/d/Shire/sys/defs.h"
#include <stdproperties.h>
#include <macros.h>

void
create_object()
{
    seteuid(getuid());
    set_name("picture");
    add_name("_shire_picture_");
    set_adj("dirty");
    set_short("dirty picture");
    set_long("This is "+short()+". It is a portrait of a young family, " +
		"painted by an experienced portrait. The paint has worn off " +
		"over time, but an outline of the people is still visible on " +
		"the square canvas. It appears to have been a portrait of a " +
		"young family as the impressions of a man, his wife, and two " +
		"young children are visible. In the background, it looks like " +
		"a meadow was painted.\n");

	add_prop(OBJ_I_WEIGHT, 1191);
//check volumes
	add_prop(OBJ_I_VOLUME, 100);
    add_prop(OBJ_I_VALUE, 400);
}
