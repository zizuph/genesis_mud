/*************************************************
 * Name     : ghoul                              *
 * Location : Dargaard keep                      *
 * Made by  : Elmore                             *
 * Date     : April, 2001                        *
 *************************************************/

#pragma save_binary
#pragma strict_types

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <ss_types.h>
#include <money.h>
#include <macros.h>
#include <composite.h>
inherit "/std/act/action.c";

inherit AM_FILE

string *face = ({"grey", "rotten", "undead"});


int
check_aggressive()
{
    return !TP->query_prop(LIVE_I_UNDEAD);
}



void
create_krynn_monster()
{
    string faces        = face[random(sizeof(face))];

    set_race_name("human");
    set_name("ghoul");
    add_adj(faces);
    set_short(faces+ " ghoul");
    set_long("This ghoul might be vaguely recognizable "+
             "as once having been human, but he has "+
             "become horribly disfigured by the change "+
             "to ghoul. His tongue has become long and "+
             "tough for licking marrow from cracked "+
             "bones, and the teeth have been changed into "+
             "sharp fangs. His once short nails are now "+
             "strong and sharp like claws.\n");

    set_stats(({(random(120)+20),90,128,109,98,100}));

    set_skill(SS_DEFENCE, 65);
    set_skill(SS_UNARM_COMBAT, 65);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 80);

    MONEY_MAKE(random(10),"gold")->move(TO,1);  

    set_alignment(-1200);
    set_knight_prestige(100);
    set_all_hitloc_unarmed(25);
    add_prop(CONT_I_WEIGHT, 4000);
    add_prop(CONT_I_HEIGHT, 2000);
    add_prop(CONT_I_VOLUME, 35000);
    add_prop(LIVE_I_UNDEAD, 100);
    add_prop(LIVE_I_SEE_DARK, 5);
    set_aggressive(VBFC_ME("check_aggressive"));
    set_exp_factor(130);  // Paralyze special attack.
    set_random_move(30); 
    
    set_act_time(random(40));
    add_act("scream");
    add_act("scream");
    add_act("scream");
    add_act("cackle");
    add_act("grin");
    add_act("grin");

    command("wield all");
    command("wear all");
}

int
special_attack(object enemy)
{
    int     attacktype,
    pen,
    att,
    wloc;

    mixed hitres;

    string *hitloc,
    *attack,
    how,
    weapon;

    attacktype = random(7);

    hitloc = ({"left arm","right arm","body","left leg","right leg","head"});

    if (attacktype == 1)
    {
        pen = random(200);
        hitres = enemy->hit_me(pen, 40, TO, -1);

        wloc = random(6);
        att  = random(2);

        if (hitres[0] <= 0)
            how = "barely grazes";
        if(hitres[0] > 0)
            how = "just grazes";
        if(hitres[0] > 10)
            how = "grazes";
        if(hitres[0] > 20)
            how = "scratches";
        if (hitres[0] > 40)
            how = "deeply buries themselves into";
        if (hitres[0] > 60)
            how = "penetrates";

        enemy->catch_msg(QCTNAME(TO) + 
          " claws at you. The "+short()+", " +how+ " your " + hitloc[wloc] + " with "+
          "his claws.\n");

        tell_room(E(TO), QCTNAME(TO) + " claws " +
          "at " + QTNAME(enemy) + ". The claws " +
          how + " " + QTNAME(enemy) +
          "'s " + hitloc[wloc] + ".\n",({enemy, TO}));

         if(!P("ghoul_paralyze", enemy))
             clone_object(DOBJ + "ghoul_stun")->move(enemy);

        enemy->heal_hp(-pen);
        TO->heal_hp(pen);

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);
        }
        return 1;
    }
    return 0;
}