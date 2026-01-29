#pragma strict_types

inherit "/std/object";
inherit "/d/Genesis/specials/abilities";
inherit "/lib/wearable_item";

#include "/d/Krynn/common/defs.h"
#include "guild.h"
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>

#define     AOD_WEAR_PROP        ("_aod_wear_prop")

object wearer;

void
create_object()
{
    set_name("totem");
    add_name(GUILD_EMBLEM_ID);
    set_short("@@totem_short");
    set_adj("@@totem_adj");
    add_adj("worg");

    set_long("You look upon a primitive @@totem_adj@@ goblin totem fashioned " +
       "into the shape of an evil worg, gifted to you by the hobgoblin shaman " +
       "when you first claimed your place amongst the tribes of Throtyl. " +
       "Goblinish markings, reading [help raiders help], have been burnt along " +
       "the totem, and a leather strap has been attached to it allowing you to " +
       "attach the totem to your hip.\n");

    set_slots(A_ANY_HIP);
    set_looseness(20);
    set_layers(1);
    set_wf(TO);

    add_prop(OBJ_I_WEIGHT,50);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE,850);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_STEAL, 1);
    add_prop(OBJ_M_NO_GIVE, 1);

    /* This armour is wearable by ogres. */
    add_prop(AOD_WEAR_PROP, 1);

}

string
totem_adj()
{
    int loot = this_player()->query_skill(SS_RAIDERS_LOOT_VALUE);

    switch (loot)
    {
    case 0..400000:
      return "wooden";
      break;
    case 400001..800000:
      return "copper";
      break;
    case 800001..1200000:
      return "silver";
      break;
    case 1200001..2000000:
      return "golden";
      break;
    case 2000001..2800000:
      return "platinum";
      break;
    case 2800001..3600000:
      return "steel";
      break;
    case 3600001..4200000:
      add_adj("dark");
      return "steel";
      break;
    default:
      add_adj("dragon");
      return "steel";
      break;
    }
}

string
totem_short()
{
    int loot = this_player()->query_skill(SS_RAIDERS_LOOT_VALUE);

    switch (loot)
    {
    case 0..400000:
      return "wooden worg totem";
      break;
    case 400001..800000:
      return "copper worg totem";
      break;
    case 800001..1200000:
      return "silver worg totem";
      break;
    case 1200001..2000000:
      return "golden worg totem";
      break;
    case 2000001..2800000:
      return "platinum worg totem";
      break;
    case 2800001..3600000:
      return "steel worg totem";
      break;
    case 3600001..4200000:
      return "dark steel worg totem";
      break;
    default:
      return "dragon steel worg totem";
      break;
    }
}

/* We do not want this to recover as it is re-cloned at login */
public string
query_recover()
{
    return 0;
}

public mixed 
remove(object ob)
{
    wearer = 0;    
    return 0;
}

public mixed 
wear(object ob)
{
    if (ob != this_object())
    {
        return -1;
    }

    wearer = TP;

    return 0;
}