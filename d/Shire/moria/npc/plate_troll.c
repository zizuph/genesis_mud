/*  -*- LPC -*-  */

/* 
 * This file has been changed to inherit the cavetroll. 
 * 
 * ---  NEVER COPY THINGS WHICH YOU CAN EASILY INERHIT! ---
 *
 * The results are that the size of this file became
 * very small. Check it out for yourself, and the 
 * gamedriver smiles happily at me.
 *
*  The troll is located in /d/Shire/moria/mines/deep/plateau
 * It uses the dwarven fullplate /d/Shire/moria/arm/durplate
 * Sir Rogon.
 */

inherit "/lib/unique";
inherit "/d/Shire/moria/npc/cavetroll";
inherit "/d/Shire/lib/kill_logger";

#include <tasks.h>
#include "/d/Shire/common/defs.h"

create_troll_guard(int r)
{
    ::create_troll_guard(r);
    set_skill(SS_WEP_SWORD, 100);
    make_gold(5);    
    set_kill_log_name("troll");
}

/* 
 * arm_me calls up cavetroll's arm_me(), but adds the dwarven fullplate.
 */
arm_me()
{
    clone_object("/d/Shire/moria/wep/urukscim")->move(TO);
    clone_unique("/d/Shire/moria/arm/durplate", MAX_UNIQUE_ITEMS, "/d/Shire/moria/arm/blackpl")->move(TO);
    command("wield all");
    command("wear all");
}    

int
special_attack(object enemy)
{
    if (!random(10))
    {
    object victim;
    int task;
 
    victim = TO->query_enemy();
    task = (TO->resolve_task(TASK_ROUTINE,(TS_STR), victim, (TS_DEX)));
        if ((task) < 0)
            {
            enemy->catch_msg(QCTNAME(TO)+
            " pushes you back over the edge.\n");
            tell_room(ENV(TO), QCTNAME(TO)+" pushes "+QTNAME(enemy)
                       +" over the edge.\n", (enemy));
    enemy->move_living("into the boiling water","/d/Shire/moria/mines/deep/boilwat");
            return 1;
            }
        enemy->catch_msg(QCTNAME(TO)+
                " tries to push you over the edge. You are dangerously close to fall over.\n");
        tell_room(ENV(TO), QCTNAME(TO)+" tries to push "+QTNAME(enemy)+ 
                  "over the edge.\n",(enemy));
        return 0;
    }
    return 0;
}
 
