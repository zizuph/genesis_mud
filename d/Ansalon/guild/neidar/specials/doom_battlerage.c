/* 
 */
inherit "/d/Ansalon/guild/neidar/specials/battlerage.c";

#include "../guild.h"

public void 
ability_msg(object actor, mixed * targets, string arg)
{
    object br_object;
    
    if (option_fiercely(actor) || option_stubbornly(actor))
        actor->catch_msg("By your death-oath you will only battlerage " +
            "aggressively now!\n");
    
    br_object = clone_object(BATTLERAGE_AGGRESSIVE);
    br_object->set_effect_caster(actor);
    br_object->set_effect_target(actor);
    br_object->move(actor, 1);
    br_object->start();
}