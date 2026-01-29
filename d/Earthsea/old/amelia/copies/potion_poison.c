/*
 *  Potion poison, part of the Alchemist quest in Gelan
 *  Based on corpse poison from Gondor.
 *  Coded by Maniac 13.3.95
 *  History:
 *          12/6/95    Poison power decreased 
 *          21/5/95    Poison power increased
 */

inherit "/std/poison_effect";

#include <poison_types.h>
#include "object.h"
#include ALCHEMIST_QUEST

void
create_poison_effect()
{
    set_interval(30);
    set_time(600);
    set_damage(({POISON_HP, 50, POISON_MANA, 25}));
    set_strength(300);
}

void
kill_player()
{
    string name;
    name = poisonee->query_name();
    log_file("alchemist_quest", name+" killed by poison.\n");
    ::kill_player();
}

