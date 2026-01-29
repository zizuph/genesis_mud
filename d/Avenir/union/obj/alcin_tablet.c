// file name:	/d/Avenir/union/obj/alcin_tablet
// creator(s): 	Lilith Dec 2003
// purpose:	      Required for Akram's dagger quest	
/*
 * Revisions:
 * 	Lucius, Jul 2017: Re-code.
 */	
#pragma strict_types

inherit "/std/object";
#include <stdproperties.h>

#include "../defs.h"
#define TEXT "/d/Avenir/union/obj/alcin_text"

public string
get_text(void)
{
    this_player()->more(TEXT, 1);
    return "";
}

public void
create_object(void)
{
    set_name("_alcin_tablet");
    add_name("tablet");   
    set_adj(({"stone", "dark"}));
    set_short("stone tablet");
    set_pshort("stone tablets");
    set_long("This is a tablet made of dark stone. "+
      "It has been deeply inscribed with symbols "+
      "and a spherical decoration. Its edges appear "+
      "to have been worn smooth by uncounted years "+
      "of handling.\n");

    add_item(({"inscription", "decoration", "spherical decoration",
	"symbols"}), "@@get_text@@");

    add_prop(OBJ_I_VOLUME, 1000);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VALUE, 50);
}

public int
do_read(string str)
{
    if (str != "tablet" && str != "stone tablet")
	return 0;

    this_player()->more(TEXT, 1);
    return 1;
}

public void
init()
{
    ::init();
    add_action(do_read, "read");
    add_action(do_read, "study");
}
