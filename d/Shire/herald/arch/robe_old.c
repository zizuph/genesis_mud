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
    set_name("robe");
    add_name("_herald_robe_");
    set_short("flawless flowing white robe");
    add_adj(({"flawless","flowing","white"}));
    set_long("This beautiful white robe is made of the finest silk "+
      "imaginable, and woven in such a way that it all seems "+
      "a whole, rather than stitched parts.  When you hold it "+
      "up to the light, some secret letters appear.\n");

    add_prop(OBJ_I_WEIGHT,   120);
    add_prop(OBJ_I_VOLUME,   500);
    add_prop(OBJ_I_VALUE,      0);
    add_prop(OBJ_M_NO_DROP,    1);

    set_default_armour(STARTING_AC, A_ROBE);

    add_item(({"secret letters","letters"}), "They read: 'help herald'.\n");
    add_cmd_item("letters","read","The letters read:\n"+
      "If you find yourself lost, just 'help herald'.\n");
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
