/*
 * guard1.c
 *
 * Used in nyreese/cas_a6.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* gresolle -92 */

/* an automatically attacking monster intended for use in the
   guard room of the castle 
*/

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <money.h>
#include <ss_types.h>
#include <macros.h>

void
create_monster()
{
    default_config_npc(25);

    set_skill(SS_DEFENCE, 50);
    set_skill(SS_WEP_SWORD, 50);
    set_skill(SS_PARRY, 50);
    set_aggressive(1);
    set_alignment(50);

    set_name("guard");
    set_race_name("human");
    set_short("castle guard");
    set_adj("castle");

    set_long("The guard is NOT happy about you intruding in his lunch room!\n");

    NEVERKNOWN;
}

void
equip_me()
{
    seteuid(getuid());

    clone_object(ROKEDIR + "wep/sword")->move(TO);
    clone_object(ROKEDIR + "arm/brigandine")->move(TO);
    clone_object(ROKEDIR + "arm/chainhelm")->move(TO);

    command("wear all");
    command("wield all");
}

int
query_knight_prestige()
{
    return 300;
}

void
help_friend(object ob)
{
    command("shout An intruder!");
    command("kill " + ob->query_real_name());
}
