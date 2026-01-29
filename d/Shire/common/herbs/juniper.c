/*
 * Juniper Berry
 * Raymundo
 * Jan, 2020
 */

inherit "/std/herb.c";
#include <macros.h>
#include "/sys/herb.h"
#include "defs.h"
#include "/sys/stdproperties.h"

create_herb()
{
    set_name("juniper_berry");
    add_name("juniper");
    add_name("berry");
    add_name("juniper berry");
    set_adj(({"round","green", "juniper"}));
    set_short("round green berry");
    set_pshort("round green berries");
    set_herb_name("juniper berry");
    set_id_long("This is a juniper berry. If you wanted to cook food with "
        + "it, you'd wait to pick it until it was mature and dark. Green "
        + "berries like this, "
        + "when fully grown but not yet changing color, are perfect "
        + "for favoring gin.\n");
    set_unid_long("This is a green berry. It smells like a pine tree.\n");
    set_ingest_verb("eat");
    set_id_diff(20);
    set_find_diff(1);
    set_effect(HERB_HEALING,"hp",1);
    set_decay_time(1800);
    set_herb_value(200);
}

query_recover() { return MASTER+":"+query_herb_recover(); }
init_recover(arg) { init_herb_recover(arg); }
