/*
 * Lucius May 2009: Cleaned and updated, moved from /d/Terel/dark/
 */
#pragma strict_types

inherit "/std/armour";

#include <stdproperties.h>
#include <wa_types.h>

public void
create_armour(void)
{
    set_name(({ "chainmail","hauberk","mail" }));
    set_adj(({ "black", "chain" }));
    set_short("black chainmail");
    set_pshort("black chainmails");
    set_long("A glimmering black suit of chainmail. "+
	"It is well crafted and very ornate.\n");

    set_default_armour(35, A_BODY, 0, 0);
}
