/*
 * This is the scroll given the player when he/she joins
 * the WoHS.
 *
 * The scroll contains info that is needed to know when
 * you have joined.
 *
 * /Rastlin, 951117
 */

#include <stdproperties.h>
#include "../../local.h"

inherit "/std/object";

public void
create_object()
{
    setuid();
    seteuid(getuid());

    set_name("scroll");

    set_short("scroll of the Wizards of High Sorcery");
    set_long("This scroll was given to you when you joined " +
	     "the Wizards of High Sorcery. The scroll contains valuable " +
	     "information about your new guild, which you should read.\n");

    add_cmd_item(({"scroll", "text", "text on scroll"}), "read", 
		 "@@read_scroll@@");

    remove_prop(OBJ_I_VALUE);
    add_prop(OBJ_I_WEIGHT, 10);
    add_prop(OBJ_I_VOLUME, 10);
    add_prop(OBJ_I_NO_DROP, "@@drop_scroll@@");
}

public string
read_scroll()
{
    cat(GOBJ + "scroll_text");
    return "";
}

public void
destruct_scroll()
{
    tell_room(E(TO), "The scroll disappears with a puff of smoke when " +
	      "it falls to the ground.\n");

    remove_object();
}

public int
drop_scroll()
{
    set_alarm(0.5, 0.0, destruct_scroll);

    return 0;
}
