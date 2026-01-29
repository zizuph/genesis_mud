#pragma strict_types
#pragma save_binary
inherit "/std/armour";

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/herald/herald.h"
#include <wa_types.h>

#define STARTING_AC  5

void
create_armour()
{
    set_name("necklace");
    add_name("_heren_istimor_necklace_");
    set_short("shimmering mithril necklace");
    add_adj(({"flawless","glistening"}));
    set_long("This beautiful necklace was forged in ages "+
      "long forgotten. Glowing facets attract your gaze.\n");

    add_prop(OBJ_I_WEIGHT,   120);
    add_prop(OBJ_I_VOLUME,   500);
    add_prop(OBJ_I_VALUE,      0);
    add_prop(OBJ_M_NO_DROP,    1);

    set_default_armour(STARTING_AC, A_NECK);

    add_item(({"pulsing facets","facets"}), "They read: 'help heren'.\n");
    add_cmd_item("facets","gaze","The facets read:\n"+
      "Use 'help heren'.\n");
}

public string query_recover() { return 0; }

public int
query_ondo_effect()
{
    if (query_ac() > STARTING_AC)
	return 1;

    return 0;
}

void
ondo_spell(int result)
{
    if (!result)
    {
	set_ac(STARTING_AC);
	query_worn()->update_armour(TO);
	return;
    }

    set_ac(result);
    query_worn()->update_armour(TO);
}
