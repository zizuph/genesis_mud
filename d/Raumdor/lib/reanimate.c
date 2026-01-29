#include "defs.h"

// To be called on livings, in theory right before their death.
// Present version makes a zombie, but this could be split out to
// work in a variety of ways
object
reanimate_living(object living)
{
    object *itemList = ({}),
           *equipList = ({}),
           reanimation = clone_object(COMMON_NPC_DIR + "reanimated_zombie");
    string race = living->query_race_name();

    // Descriptions
    reanimation->add_name(race);
    reanimation->set_adj(race);
    reanimation->set_short(race + " zombie");

    // It's an "it" now
    reanimation->set_gender(G_NEUTER);

    // Zombies retain some muscle memory
    foreach (int skill: living->query_all_skill_types())
    {
        reanimation->set_skill(skill, (6 * living->query_skill(skill)) / 10);
    }

    // Stats
    reanimation->set_stats(({
        living->query_stat(SS_STR),
        living->query_stat(SS_DEX),
        living->query_stat(SS_CON),
        living->query_stat(SS_INT) / 3,
        living->query_stat(SS_WIS) / 3,
        living->query_stat(SS_DIS) * 2,
    }));

    itemList += living->subinventory(SUBLOC_HELD);
    itemList += living->query_weapon(-1);
    itemList += living->query_clothing(-1);

    foreach (object item: itemList)
    {
       if (!item->move(reanimation))
           equipList += ({item});
    }

    reanimation->equip(equipList);

    // Rest of inventory
    foreach (object item: all_inventory(living))
    {
        if (IS_POISON_OBJECT(item))
            item->remove_object();

        item->move(reanimation);
    }

    living->add_prop(LIVE_I_NO_CORPSE, 1);

    return reanimation;
} 
