#include "../local.h"
inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/std/group_cluster";
inherit "/d/Genesis/specials/npc/stat_based_specials.c";

public void         create_monster();

void
create_monster()
{
    ::create_monster();
    set_name("guardian");
    add_name("shadow");
    add_name("demon");
    add_name("_thanar_npc");
    set_race_name("human");
    set_adj("otherworldly");
    add_adj("invisible");
    set_long("A shadow summoned from the demonic plains.\n");
    set_gender(G_NEUTER);
    set_stats(({125, 100, 125, 50, 50, 100}));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 80);
    set_act_time(6);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_DARK, 50);
    add_prop(LIVE_I_SEE_INVIS, 50);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    set_aggressive(1);
    set_knight_prestige(500);
    
    set_prospective_cluster(({"_thanar_npc"}));
}

int
special_attack(object enemy)
{
    object stun;
    object *ob;
    object *enemies;
    object kill_enemy;
    int i;
    int did_push;
    int pen;
    object me;
    mixed* hitresult;
    string how;
    me = this_object();
    
    if(!present(enemy, environment(this_object())))
    {
        return 0;
    }
    
        /* This decides if we shall do anything more... */
    if (random(2))
        return 0;
    
    /* This part will make the shadow attack the weakest enemy.*/
    
    kill_enemy= me->query_attack();
    enemies = me->query_enemy(-1);
    for (i=0;i<sizeof(enemies);i++)
    {
        if (enemies[i]->query_stat(SS_CON) < kill_enemy->query_stat(SS_CON))
            kill_enemy = enemies[i];
    }
    if(kill_enemy != me->query_attack())
    {
        command("kill "+kill_enemy->query_real_name());
    }
    
    pen = query_pen_by_stat(TO->query_average_stat());
    hitresult = enemy->hit_me(query_pen_by_stat(TO->query_average_stat()) 
    + random(400));
    switch (hitresult[3])
    {
        case 0..20:
            how = "without effect";
            break;
        case 21..50:
            how = "softly";
            break;
        case 51..80:
            how = "hard";
            break;
        case 81..110:
            how = "very hard";
            break;
        case 111..140:
            how = "extremely hard";
            break;
        case 141..170:
            how = "smashingly";
            break;
        default:
            how = "smashingly";
            break;
    }   
    me -> catch_msg("You strike your opponent in the stomach, "+how+"!\n");
    enemy->catch_msg(QCTNAME(me)+" strikes you "+how+" in your stomach!\n");
    tell_watcher(QCTNAME(me)+" strikes "+QTNAME(enemy)+" "+how+
        " in the stomach!\n",enemy);
    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(me);
        return 1;
    }

    /* add a stun if damage above 10 */
    if (hitresult[0] < 9) return 1;
    if (random(2) == 0) return 1;
    ob = all_inventory(enemy);
    for(i=0;i<sizeof(ob);i++)
    {
        if(ob[i]->query_name()=="stun")
        {
            return 1;
        }
    }
    seteuid(getuid(TO));
    stun = clone_object("/d/Kalad/common/central/obj/lord_stun");
    stun->move(enemy, 1);
    enemy->catch_msg("The blow makes you lose your breath!\n");
    return 1;
}
