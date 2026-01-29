/* township/npc/townguard.c is cloned by township/inside_gate.c  */
inherit "/std/monster";
 
#include "/d/Emerald/defs.h"
#include "/d/Emerald/lib/prestige.h"
 
void
create_monster()
{
    if (!IS_CLONE)
        return;
 
    set_name("guard");
    set_adj("big");
    add_adj("swarthy");
    set_race_name("human");
    set_short("big city guard");
    set_long("It is one of the many guards patrolling the "+
             "township to make sure nothing untoward happens. He doesn't "+
             "look like anyone you would want to mess with.\n");
 
    set_stats( ({ 75+random(51), 75+random(51), 75+random(51),
                      60+random(51), 60+random(51), 75+random(51) }) );
 
    set_skill(SS_WEP_SWORD, 70);
    set_skill(SS_PARRY, 60);
    set_skill(SS_DEFENCE, 30);
 
    set_all_hitloc_unarmed(query_stat(SS_CON) / 4);
 
    set_alignment(random(150)+150);
 
    add_prop(OBJ_I_WEIGHT, 19000);
    add_prop(CONT_I_MAX_WEIGHT, 180000);
    add_prop(OBJ_I_VOLUME, 89000);
    add_prop(CONT_I_MAX_VOLUME, 100000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_QUICKNESS, query_stat(SS_DEX));
 
    seteuid(getuid());
 
    set_random_move(10);
    set_restrain_path(TOWNSHIP_DIR);
    set_monster_home(TOWNSHIP_DIR + "inside_gate");
}
 
void
arm_me()
{
    if (random(5) < 3)
        clone_object(TOWNSHIP_DIR + "arm/plate")->move(this_object(),1);
    if (random(5) < 3)
        clone_object(TOWNSHIP_DIR + "arm/helmet")->move(this_object(),1);
    if (random(5) < 2)
        clone_object(TOWNSHIP_DIR + "arm/gauntlets")->move(this_object(),1);
    if (random(5) < 2)
        clone_object(TOWNSHIP_DIR + "arm/leggings")->move(this_object(),1);
    if (random(5) < 2)
        clone_object(TOWNSHIP_DIR + "arm/boots")->move(this_object(),1);
    clone_object("/d/Emerald/telberin/wep/g_sword")->move(this_object(),1);
    command("wear all");
    command("wield all");
}
