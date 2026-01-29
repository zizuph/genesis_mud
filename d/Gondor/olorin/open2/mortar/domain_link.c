inherit "/std/domain_link";

void
preload_link()
{
  preload("/d/Gondor/elessar/lib/clock");
  preload("/d/Gondor/elessar/misc/tmp_room");
  preload("/d/Gondor/pelargir/docks/dock2");
  preload("/d/Gondor/pelargir/docks/dock3");
  preload("/d/Gondor/pelargir/docks/dock5");
  preload("/d/Gondor/pelargir/docks/dock7");
  preload("/d/Gondor/pelargir/docks/dock8");
  preload("/d/Gondor/minas/lib/master");
  preload("/d/Gondor/tharbad/pier/pier1");
  preload("/d/Gondor/ithilien/poros/pier");
  preload("/d/Gondor/common/guild/recruithall");
  preload("/d/Gondor/common/guild/gondor_council");
  preload("/d/Gondor/common/guild2/death_room");
  preload("/d/Gondor/common/herbs/herb_master");
  preload("/d/Gondor/common/lib/weather_master");
}

#include "/d/Gondor/common/potions/potion_defs.h"
mapping Potion_Ingr;
public mapping
query_potion_map()
{
    if (!mappingp(Potion_Ingr))
        Potion_Ingr = GONDOR_POTION_INGREDIENTS;
    return Potion_Ingr;
}

