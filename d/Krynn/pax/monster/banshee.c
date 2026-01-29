/*
 * Arman - May 2016
 * The dark elf banshee guarding the vault of Kith Kanan                                                            
 */
  
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
    set_name("banshee");    
    set_race_name("undead");
    set_short("coldly beautiful banshee");
    add_adj("beautiful");
    add_adj("coldly");

    TO->add_prop(LIVE_I_NO_CORPSE, 1);
    TO->add_prop(MAGIC_I_BREATH_WATER, 1);
    TO->add_prop(LIVE_I_UNDEAD, 100);

    set_long("Before you coalescing from the shadows is the coldly " +
      "beautiful, distorted features of a female drow - an evil elf " +
      "of ages past, whose punishment for crimes unspeakable has been " +
      "execution. Powerful elven magic-users chained her spirit here, " +
      "to guard the king's treasure for eternity.\n");

    add_prop(CONT_I_HEIGHT, 180);
    add_prop(CONT_I_WEIGHT, 150);
    add_prop(CONT_I_VOLUME, 140);

    set_gender(G_FEMALE);
    set_aggressive(1);

    add_prop(LIVE_I_SEE_DARK, 5);
    add_prop(LIVE_I_NO_CORPSE, 1);

    set_stats(({100+random(30),100+random(50),100+random(20),80,90,180}));

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

    set_cact_time(6);
    add_act("emote lets out a wailing keen, so frightful that you feel " +
      "your heart stop beating for a moment.");
    add_act("emote screams wordlessly her grief and her hatred for all " +
      "living things.");

    seteuid(geteuid(TO));
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

void
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
        pen = 300 + random(300);
        hitres = enemy->hit_me(pen, 45, TO, -1);
        TO->heal_hp(pen);

        wloc = random(6);
        att  = random(2);

        if (hitres[0] <= 0)
            how = "She just misses grabbing your "+ hitloc[wloc]+".\n";
        if(hitres[0] > 0)
            how = "Her hand brushes your "+ hitloc[wloc]+", chilling " +
              "and burning you with her unholy touch.\n";
        if(hitres[0] > 10)
            how = "Her hand brushes your "+ hitloc[wloc]+", chilling " +
              "and burning you with her unholy touch.\n";
        if(hitres[0] > 20)
            how = "She grabs your "+ hitloc[wloc]+" forcibly, shriveling " +
              "you with her undead touch.\n";
        if (hitres[0] > 40)
            how = "She grabs your "+ hitloc[wloc]+" forcibly, shriveling " +
              "you with her undead touch.\n";
        if (hitres[0] > 60)
            how = "She grabs your "+ hitloc[wloc]+" forcibly, draining " +
              "the life from your body with her undead touch.\n";

        enemy->catch_msg(QCTNAME(TO) + 
          " stretches out her hands towards your " + hitloc[wloc] + ", "+
          "craving the warmth of your flesh.\n"+ how);

        tell_room(E(TO), QCTNAME(TO) + " stretches out her hands towards " +
          QTPNAME(enemy) +" "+ hitloc[wloc] + ", seeking the warmth of " +
          "living flesh.\n",({enemy, TO}));

        return 1;
    }
    return 0;
}

public void
do_die(object killer)
{
    object room = E(TO);
    object s_stone;

    s_stone = clone_object("/d/Krynn/pax/obj/spirit_stone");
    s_stone->move(room, 1); 

    ::do_die(killer);
    tell_room(room, "With a wail of fury the evil banshee is banished to the " +
         "Abyss, leaving behind the spirit stone that entrapped her.\n", ({ TO }));
 
}