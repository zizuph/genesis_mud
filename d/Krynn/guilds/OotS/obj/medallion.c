#pragma strict_types

inherit "/std/object";
inherit "/d/Genesis/specials/abilities";
inherit "/lib/wearable_item";

#include "/d/Krynn/common/defs.h"
#include "../defs.h"
#include <wa_types.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>

object wearer;

string
medallion_adj()
{
    string god;

    if(!wearer)
        god = OOTS_MANAGER->query_oots_god(TP);
    else
        god = OOTS_MANAGER->query_oots_god(wearer);

    switch (god)
    {
    case "Habbakuk":
    case "Mishakal":
      return "silver";
      break;
    case "Paladine":
      return "platinum";
      break;
    case "Majere":
    case "Kiri-Jolith":
      return "copper";
      break;
    case "Branchala":
      return "gold";
      break;
    default:
      return "silver";
      break;
    }
}

void
create_object()
{
    set_name("medallion");
    add_name("oots_guild_object");
    add_name("medallion of faith");
    set_short("@@medallion_short");
    set_pshort("@@medallion_pshort");
    set_adj(medallion_adj());
    set_long("@@medallion_long@@ As you gaze upon the " +
        "medallion, you realise you can use the command <help oots> " +
        "to get help on the Holy Order of the Stars guild!\n");

    set_slots(A_NECK);
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
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 80, "divination" }));
    add_prop(MAGIC_AM_ID_INFO, ({ "Divine magic flows from this " +
        "medallion.\n", 0,"It is a symbol of an ancient and holy " +
        "mythos.\n", 10, "Disciples of the Holy Order of the Stars " +
        "use this medallion in their holy rituals.\n", 40 }));
}

string
medallion_short()
{
    string god;

    if(!wearer)
        god = OOTS_MANAGER->query_oots_god(TP);
    else
        god = OOTS_MANAGER->query_oots_god(wearer);

    switch (god)
    {
    case "Habbakuk":
    case "Mishakal":
      return "silver medallion of faith";
      break;
    case "Paladine":
      return "platinum medallion of faith";
      break;
    case "Majere":
    case "Kiri-Jolith":
      return "copper medallion of faith";
      break;
    case "Branchala":
      return "gold medallion of faith";
      break;
    default:
      return "silver medallion of faith";
      break;
    }
}

string
medallion_pshort()
{
    string god;

    if(!wearer)
        god = OOTS_MANAGER->query_oots_god(TP);
    else
        god = OOTS_MANAGER->query_oots_god(wearer);

    switch (god)
    {
    case "Habbakuk":
    case "Mishakal":
      return "silver medallions of faith";
      break;
    case "Paladine":
      return "platinum medallions of faith";
      break;
    case "Majere":
    case "Kiri-Jolith":
      return "copper medallions of faith";
      break;
    case "Branchala":
      return "gold medallions of faith";
      break;
    default:
      return "silver medallions of faith";
      break;
    }
}

string
medallion_long()
{
    string god;

    if(!wearer)
        god = OOTS_MANAGER->query_oots_god(TP);
    else
        god = OOTS_MANAGER->query_oots_god(wearer);

    switch (god)
    {
    case "Habbakuk":
      return "The medallion is a plain disk of silver inscribed with " +
        "the symbol of a phoenix.";
    case "Mishakal":
      return "The medallion is a plain disk of silver inscribed with a " +
        "lemniscate, the symbol for infinity.";
      break;
    case "Paladine":
      return "The medallion is a plain disk of platinum inscribed " +
        "with the symbol of a dragon.";
      break;
    case "Majere":
      return "The medallion is a plain disk of copper inscribed " +
        "with the symbol of a rose.";
    case "Kiri-Jolith":
      return "The medallion is a plain disk of copper inscribed " +
        "with the symbol of a bison's head.";
      break;
    case "Branchala":
      return "The medallion is a plain disk of gold inscribed with " +
        "the symbol of a harp.";
      break;
    default:
      return "The medallion is a plain disk of silver.";
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

/* Override as this doesn't break */

/*
varargs int
got_hit(int hid, int ph, object att, int dt, int dam)
{
    hits++;
}
*/

