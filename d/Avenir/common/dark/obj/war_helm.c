/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 * Lilith May 2014: Updated desc and ac
 */
#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour(void)
{
    set_name(({ "helmet", "war-helm","helm" }));
    set_adj(({ "black", "war" }));
    set_short("black war-helm");
    set_pshort("black war-helms");
    set_long("A war-helm, black as the Utterdark from which it came, "+
			 "carved with ornate serpents.\nIt is good protection.\n");
    add_item("serpents", "The serpents carved into the war helm are "+
			 "beautifully rendered.\n");
    set_default_armour(20, A_HEAD, 0, 0);
}
