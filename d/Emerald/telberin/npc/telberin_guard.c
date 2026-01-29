inherit "/d/Emerald/telberin/npc/telberin_elf";
inherit "/d/Emerald/lib/aid_npc";

#include <options.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "/d/Emerald/sys/paths.h"
#include "/d/Genesis/login/login.h"

#define STATMOD(stat, lvl) (lvl * RACESTATMOD["elf"][stat] / 10)

void arm_me();

void
config_guard(int level)
{
    set_stats(({ STATMOD(SS_STR, level) * 11 / 10,
                 STATMOD(SS_DEX, level) * 11 / 10,
                 STATMOD(SS_CON, level) * 11 / 10,
                 STATMOD(SS_INT, level) * 8 / 10,
                 STATMOD(SS_WIS, level) * 8 / 10,
                 STATMOD(SS_DIS, level), }));

    set_skill(SS_WEP_SWORD,    level + random(10));
    set_skill(SS_DEFENSE,      level + random(10));
    set_skill(SS_PARRY,        level * 8 / 10 + random(10));
    set_skill(SS_BLIND_COMBAT, level * 9 / 10 + random(10));
    set_skill(SS_AWARENESS,    level * 9/ 10 + random(10));
    set_skill(SS_UNARM_COMBAT, level * 9 / 10 + random(10));
}

void
create_guard()
{
    config_guard(60);
}

nomask void
create_telberin_elf()
{
    set_name("guard");
    set_short("elven guard");

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
   
    set_alignment(150);

    remove_prop(OBJ_M_NO_ATTACK);
    create_guard();
}

void
arm_me()
{
    setuid();
    seteuid(getuid());
    add_equipment(EMERALD_WEP_DIR + "mil_longsword");
}

void 
attacked_by(object enemy)
{
    ::attacked_by(enemy);
    get_assistance(enemy);
}

void
assist()
{
    tell_room(environment(), ({
        "The " + short() + " gives assistance unto his comrade.\n",
        "The " + short() + " gives assistance unto his comrade.\n",
        "" }),  this_object());
}

int
query_option(int opt)
{
    return (opt == OPT_UNARMED_OFF);
}
