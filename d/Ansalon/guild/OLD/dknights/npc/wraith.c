/************************************************
 * Name: Wraith                                                      
 * By: Elmore
 * Desc: A wraith for Dargaard Keep.
 * Note: Has a hunting function.
 *                                                                             
 ************************************************/
  
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/dargaard/local.h"

inherit AM_FILE

void arm_me();

int
check_alignment()
{
    if (TP->query_alignment() >= -500)
        return 1;

    return 0;
}


void
create_krynn_monster()
{
    set_name("wraith");    
    set_race_name("undead");

    set_adj("unholy");
    add_adj("black-robed");

    set_short("unholy black-robed wraith");

    TO->add_prop(LIVE_I_NO_CORPSE, 1);
    TO->add_prop(MAGIC_I_BREATH_WATER, 1);
    TO->add_prop(LIVE_I_UNDEAD, 100);

    set_long("You stand before one of the wraiths in Dargaard Keep. "+
             "This horrible creature is seen as black, vaguely "+
             "man-shaped clouds. This creature has no true "+
             "substance, instead this one has shaped itself "+
             "with two upper limbs, a torso, and a head with two "+
             "glowing red eyes. This shape might be a convenience "+
             "born from the habit of once having a human body.\n");

    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_WEIGHT, 150);
    add_prop(CONT_I_VOLUME, 140);

    set_gender(G_NEUTER);
    set_aggressive(VBFC_ME("check_alignment"));

    /* Trolls can see in the dark */
    add_prop(LIVE_I_SEE_DARK, 5);

    set_stats(({140+random(30),140+random(50),140+random(20),80,90,110}));

    set_exp_factor(115);  //Because they can only be hit by magical
                          //weapons, and they have a special attack.

    set_skill(SS_WEP_POLEARM, 90);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 80);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 60);

    set_alignment(-1150);
    set_knight_prestige(100);

    set_all_hitloc_unarmed(20);
}

arm_me()
{
    seteuid(getuid(this_object()));

    command("wield all");
    command("wear all");
  
}

int
special_attack(object enemy)
{
    int     attacktype,
    pen,
    att,
    wloc,
    hps;

    mixed hitres;

    string *hitloc,
    *attack,
    how,
    weapon;

    object extra_wraith;

    attacktype = random(8);

    hitloc = ({"left arm","right arm","body","left leg","right leg","head"});

    if (attacktype == 1)
    {
        pen = 300 + random(300);
        hitres = enemy->hit_me(pen, 45, TO, -1);
        TO->heal_hp(pen);

        wloc = random(6);
        att  = random(2);

        if (hitres[0] <= 0)
            how = "tiny";
        if(hitres[0] > 0)
            how = "small";
        if(hitres[0] > 10)
            how = "bleeding";
        if(hitres[0] > 20)
            how = "serious";
        if (hitres[0] > 40)
            how = "lethal";
        if (hitres[0] > 60)
            how = "mortal";


        enemy->catch_msg(QCTNAME(TO) + 
          " grabs around your " + hitloc[wloc] + " with "+
          "his claw-like arms.\n"+
          "You feel a sudden coldness spreading from your "+
          hitloc[wloc]+".\n");

        tell_room(E(TO), QCTNAME(TO) + " grabs around" +
          QTNAME(enemy) +"'s "+ hitloc[wloc] + " with his "+
          "claw-like arms.\n",({enemy, TO}));

        if (enemy->query_hp() <= 0)
        {
            enemy->add_prop(LIVE_I_NO_CORPSE, 1);
            enemy->do_die(TO);
            tell_room(E(TO),QCTNAME(enemy) + "'s corpse turns to dust " +
                "suddenly a new wraith appears!\n", enemy);
            extra_wraith = clone_object(DNPC + "wraith");
            extra_wraith->move(E(TO));
            extra_wraith->command("get armours");
            extra_wraith->command("get weapons");
            extra_wraith->command("wear all");
            extra_wraith->command("wield all");
            extra_wraith->command("howl");
        }
        return 1;
    }
    return 0;
}

