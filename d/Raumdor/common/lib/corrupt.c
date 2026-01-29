#include "defs.h"

void
corrupt(object player)
{
    int i;
    int amount;
    object *all;
    object *drinks;
    object *foods;
    object corrupted;
    string message;
    all = all_inventory(player);
    drinks = filter(FILTER_DRINK_OBJECTS(all),
            &operator(==)(0) @ &->id("_raumdor_corrupt_drink")); 
    foods = filter(FILTER_FOOD_OBJECTS(all),
            &operator(==)(0) @ &->id("_raumdor_corrupt_food"));
    foods = foods - FILTER_LEFTOVER_OBJECTS(foods);
    all = foods + drinks;
    if (!sizeof(all))
        return;
    message = capitalize(FO_COMPOSITE_DEAD(all, player));
    if (sizeof(all) == 1 && all[0]->num_heap() == 1 )
        message += " is";
    else
        message += " are";
    message += " corrupted by the aura!\n";
    for (i=0; i<sizeof(all); i++)
    {
        if IS_FOOD_OBJECT(all[i])
        {
            corrupted = clone_object("/d/Raumdor/common/obj/corrupt_food");
            corrupted->set_long("This rotten lump looks like it used to be " +
                   LANG_ADDART(all[i]->singular_short()) + ".\n");
            corrupted->add_prop(HEAP_S_UNIQUE_ID, "_raumdor_corrupt_food_" + 
                    all[i]->singular_short());
        }
        else
        {
            corrupted = clone_object("/d/Raumdor/common/obj/corrupt_drink");
            corrupted->set_long("This fouled liquid looks like it used to be " +
                   LANG_ADDART(all[i]->singular_short()) + ".\n");
            corrupted->add_prop(HEAP_S_UNIQUE_ID, "_raumdor_corrupt_drink_" + 
                    all[i]->singular_short());
        }
        corrupted->set_heap_size(all[i]->num_heap());
        corrupted->add_prop(HEAP_I_UNIT_WEIGHT,
                all[i]->query_prop(HEAP_I_UNIT_WEIGHT));
        corrupted->add_prop(HEAP_I_UNIT_VOLUME,
                all[i]->query_prop(HEAP_I_UNIT_VOLUME));
        corrupted->move(player, 1);
        all[i]->remove_object();
    }
    if (player->can_see_in_room())
        player->catch_msg(message);
}

void
do_corrupt()
{
    int i;
    object *players;
    players = FILTER_PLAYERS(all_inventory(E(TO)));
    if (!sizeof(players))
        return;
    tell_room(E(TO),({
        "A black aura surrounds " + TO->query_name() + "!\n",
        "A black aura surrounds the " + TO->query_nonmet_name() + "!\n",
        ""
    }), 0, TO);
    for (i=0; i<sizeof(players); i++)
        corrupt(players[i]);
}

