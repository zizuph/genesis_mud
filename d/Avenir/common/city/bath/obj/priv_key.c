/*
 * ~/priv_key.c
 *
 * Key to a private room in the baths.
 *
 * Revisions:
 *   Lilith, Feb 2002: Created
 *   Lucius, Aug 2016: Recoded baths.
 *
 */
#pragma strict_types
inherit "/std/key";

#include "../bath.h"
#include <stdproperties.h>

public static string room;


public string
what_room(void)		{ return (room ?: "none"); }

public void
set_room(string str)
{
    if (!strlen(str))
	return;

    room = str;
    add_adj(room);
}

public void
create_key(void)
{
    add_name(({ PRIV_KEY_ID }));
    set_adj(({ "iron", "room", "bath", "private" }));

    set_short("key to room @@what_room@@");
    set_long("This is a key to private room @@what_room@@ of "+
	"Melchoir's Baths. It is made of iron and inset at the "+
	"handle with a cabochon garnet.\n");

    add_item(({"garnet", "cabochon", "cabochon garnet"}),
        "The garnet is cut in a convex form, highly polished, "+
        "but not faceted. It is seated in the handle of the key.\n");

    add_prop(OBJ_I_NO_SELL, 1);
    add_prop(OBJ_I_WEIGHT, 100);    
    add_prop(OBJ_I_VOLUME, 100);  
    add_prop(OBJ_I_VALUE, 1000);
}
