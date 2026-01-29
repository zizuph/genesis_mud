/*
 * A wraith, found in the Chamber of DOom
 *
 * 950504 by Rastlin
 */

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <money.h>
#include <cmdparse.h>
#include "/d/Krynn/common/defs.h";
#include "/d/Krynn/pax/local.h";
inherit M_FILE

inherit "/std/act/domove";
inherit "/std/act/action";

object gEnemy;

void
create_krynn_monster()
{
    int i;

    set_name("wraith");
    set_race_name("undead");
    set_long("This undead creature is the evil remnant of a graverobber " +
      "who broke into the Sla-Mori trying to plunder the tomb of " +
      "Kith-Kanan.\n");

    set_short("wraith");

    for (i = 0; i < 5; i++)
        set_base_stat(i, 120 + random(40));
    set_base_stat(SS_DIS, 170 + random(40));

    set_skill(SS_DEFENCE,      70);
    set_skill(SS_PARRY,        50);
    set_skill(SS_UNARM_COMBAT, 90);
    set_skill(SS_AWARENESS,    200);
    add_prop(LIVE_I_QUICKNESS, 10);
    add_prop(LIVE_I_SEE_DARK,  100);
    add_prop(NPC_I_NO_RUN_AWAY,  1);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_UNDEAD, 70);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_NO_BODY, 1);

    set_aggressive(1);

    set_alignment(-720);
    set_knight_prestige(670);

    set_all_hitloc_unarmed(45);

    trig_new("%w 'leaves' / 'sneaks' %s", "follow_attacker");
}

public void
init_attack()
{
    if ((!monster_aggressive) || (this_player()->query_npc()))
        return;

    if (!gEnemy)
        set_attack_chance(100);
    else
    if (!present(gEnemy, E(TO)))
        set_attack_chance(100);

    if ((monster_attack_chance == 0) || (random(100) < monster_attack_chance))
    {
        set_alarm(2.0, 0.0, &aggressive_attack(this_player()));
        gEnemy = this_player();
        set_attack_chance(30);
    }
}

public void
do_follow(string where)
{
    if (where != "enter")
        command(where);
}

public int
follow_attacker(string who, string where)
{
    mixed arr;
    int i;

    sscanf(where, "%s.", where);

    if (gEnemy && (gEnemy->query_real_name() == L(who)))
        set_alarm(0.2, 0.0, "do_follow", where);

    return 1;
}
