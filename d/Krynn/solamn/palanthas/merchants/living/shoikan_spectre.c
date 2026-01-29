#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"

inherit M_FILE

void arm_me();

void
create_krynn_monster()
{
    set_name("spectre");    
    set_race_name("undead");
    set_adj("guardian");
    set_short("guardian spectre");

    TO->add_prop(LIVE_I_NO_CORPSE, 1);
    TO->add_prop(MAGIC_I_BREATH_WATER, 1);
    TO->add_prop(LIVE_I_UNDEAD, 100);

    set_long("Before you hovers a spectre, an incorporeal creature " +
       "of evil that hates all living things. This one stalks the " +
       "boundaries of the Shoikan Grove, seeking out any creature " +
       "foolish enough to enter.\n");

    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_WEIGHT, 150);
    add_prop(CONT_I_VOLUME, 140);

    set_gender(G_NEUTER);
    set_aggressive(1);

    /* Undead can see in the dark */
    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_stats(({80+random(30),50+random(50),80+random(20),80,90,180}));

    set_exp_factor(110);  // Because they have a drain special attack.

    set_skill(SS_UNARM_COMBAT, 80);
    set_skill(SS_DEFENCE, 85);
    set_skill(SS_PARRY, 80);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 60);

    set_alignment(-1150);
    set_knight_prestige(100);
    set_all_hitloc_unarmed(20);

    clone_object("/d/Ansalon/dargaard/obj/armour/shroud.c")->move(TO,1);
    command("wear all");

}

varargs public mixed
hit_me(int wcpen, int dt, object attacker, int
attack_id, int target_hitloc = -1)
{
    mixed a;

    a = ::hit_me(wcpen, dt, attacker, attack_id, target_hitloc);

    return a;
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
    string description, name;

    attacktype = random(12);

    hitloc = ({"left arm","right arm","body","left leg","right leg","head"});

    if (attacktype == 0)
    {
        pen = 100 + random(100);
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
          "his ghostlike hands.\n"+
          "You feel a sudden coldness spreading from your "+
          hitloc[wloc]+".\n");

        tell_room(E(TO), QCTNAME(TO) + " grabs around " +
          QTNAME(enemy) +"'s "+ hitloc[wloc] + " with his "+
          "ghostlike hands.\n",({enemy, TO}));

        if (enemy->query_hp() <= 0)
        {
            enemy->do_die(TO);     
        }
        return 1;
    }
    return 0;
}
