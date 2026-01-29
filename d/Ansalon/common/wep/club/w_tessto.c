inherit "/std/weapon";
inherit "/lib/keep";
#include <wa_types.h>
#include <stdproperties.h>

void
create_weapon()
{
    set_name("tessto");
    set_adj("heavy");
    add_adj("wooden");
    set_short("heavy wooden tessto");
    set_long("This great weapon, the tessto, is common amongst the minotaurs " +
      "of the Blood Sea. Made of hardwood, this club is heavier than a lot of metal weapons, " +
      "and is cleverly weighted so as to maximize damage. Nasty looking spikes " +
      "protrude from its head, adding to its deadliness.\n");
    set_default_weapon(30,39,W_CLUB,W_BLUDGEON,W_BOTH);
    update_prop_settings();
    add_prop(OBJ_I_VOLUME, query_prop(OBJ_I_WEIGHT)/7);
}
