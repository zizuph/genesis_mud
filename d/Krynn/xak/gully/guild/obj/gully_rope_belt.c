/*
 * Gully dwarf guilditem
 *
 * Andrew Smith - Karath@Genesis - Feb 1998
 *
 */

#pragma save_binary
#pragma strict_types

inherit "std/object.c";
inherit "cmd/std/command_driver.c";

string *guilditem_type, color;
public mixed guilditem_random();
public string guilditem_color();

#include "/sys/stdproperties.h"

public void init_gully_guilditem()
{
    if (!sizeof(guilditem_type))
	guilditem_type = guilditem_random();

}

public void
create_object()
{
    set_name("belt");
    set_short("dirty rope belt");
    add_adj(({"dirty", "rope"}));
    set_long("The cap seems to be standard issue for the basic "+
	"properly-constructed light piece of armour.\n");
}
