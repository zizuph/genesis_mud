/************************************************
 * Name: Spectral minion                                                      
 * Based on Dargaard Keep wraith.
 *                                                                             
 ************************************************/
  
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE

int gHaveSetTrigger = 0;

void
create_krynn_monster()
{
    set_name("minion");    
    set_race_name("undead");
    set_adj("spectral");

    set_short("spectral minion");

    TO->add_prop(LIVE_I_NO_CORPSE, 1);
    TO->add_prop(MAGIC_I_BREATH_WATER, 1);
    TO->add_prop(LIVE_I_UNDEAD, 100);

    set_long("Before you stands a spectral minion, an ethereal " +
             "creature summoned to serve a powerful wizard. " +
             "This creature has no true "+
             "substance, instead this one has shaped itself "+
             "with two upper limbs, a torso, and a head with two "+
             "glowing red eyes. This shape might be a convenience "+
             "born from the habit of once having a human body.\n");

    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_WEIGHT, 150);
    add_prop(CONT_I_VOLUME, 140);

    set_gender(G_NEUTER);

    /* Undead can see in the dark */
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_stats(({120, 120, 120, 100, 100, 160}));

    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 80);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 60);

    set_alignment(0);
    set_knight_prestige(0);
    set_all_hitloc_unarmed(35);

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
    string description, name;

    attacktype = random(12);

    hitloc = ({"left arm","right arm","body","left leg","right leg","head"});

    if (attacktype == 0)
    {
        pen = 100 + random(500);
        hitres = enemy->hit_me(pen, 45, TO, -1);

        wloc = random(6);
        att  = random(2);

        enemy->catch_msg(QCTNAME(TO) + 
          " grabs around your " + hitloc[wloc] + " with "+
          "his spectral hands.\n"+
          "You feel a freezing coldness spread through your "+
          hitloc[wloc]+".\n");

        tell_room(E(TO), QCTNAME(TO) + " grabs " +
          QTPNAME(enemy) +" "+ hitloc[wloc] + " with his "+
          "spectral hands, hurting " +HIM(enemy)+ " with a " +
          "freezing coldness.\n",({enemy, TO}));

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);     
        }
        return 1;
    }
    return 0;
}
