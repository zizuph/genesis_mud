#pragma save_binary

inherit "/std/domain_link";

#include "/d/Calia/common/potions/potion_defs.h"

static mapping Potion_Ingr;

void
preload_link()
{
    preload("/d/Calia/ships/shire/pier");
    preload("/d/Calia/ships/krynn/pier");
    preload("/d/Calia/sea/beach/village9");
    preload("/d/Calia/eldoral/special/name_macros");
}

public mapping
query_potion_map()
{
    if (!mappingp(Potion_Ingr))
        Potion_Ingr = CALIA_POTION_INGREDIENTS;
    return Potion_Ingr;
}

