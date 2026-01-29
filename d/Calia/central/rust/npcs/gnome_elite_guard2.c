/* Created 07/1|/98 by Bishop, of Calia. This is an elite gnome
guard, a veteran of the war with Kroug and the earlier warlords
of Calia. */

inherit "/std/monster.c";

#include <ss_types.h>
#include <stdproperties.h>
#include <money.h>
#include <macros.h>
#include <wa_types.h>
#include <options.h>
#include <const.h>
#include "/d/Genesis/gems/gem.h"

#include "defs.h"

#define STATDIFF  20
#define ALIGN   -100

/* Equips him */

void
equip_me()
{
    object armour;
    object armour2;
    object armour3;
    object armour4;

    object weapon;
    object weapon2;

    seteuid(getuid(TO));

    weapon = clone_object(RUST_WEAPONS + "stabbing_shortsword");
    weapon->move(TO);

    weapon2 = clone_object(RUST_WEAPONS + "stabbing_shortsword");
    weapon2->move(TO);

    armour = clone_object(RUST_ARMOURS + "chain_tunic");
    armour->move(TO);

    armour2 = clone_object(RUST_ARMOURS + "steel_banded_mail");
    armour2->move(TO);

    armour3 = clone_object(RUST_ARMOURS + "plate_leggings");
    armour3->move(TO);

    armour4 = clone_object(RUST_ARMOURS + "close_faced_helmet");
    armour4->move(TO);
   
    command("wield all");
    command("wear all");
}

int
special_attack(object enemy)
{
    object me;
    mixed *hitresult;
    int stun_duration, x, y;
    string how, onlooker, *tackle1, *tackle2;

    tackle1 = ({"blindingly fast","spinning","devastating"});
    tackle2 = ({"flying tackle", "sliding tackle", "aerial tackle",
        "shoulder-tackle", "scissor-tackle"});

    x = random(sizeof(tackle1));
    y = random(sizeof(tackle2));
    
    stun_duration = 0;    
    me = TO;
    
    if (random(8))
    {
        return 0;
    }

    hitresult = enemy->hit_me(150+random(100), W_BLUDGEON, me, -1);
    switch (hitresult[0])
    {
        case 0:
            how = "You are unscathed";
            onlooker = "unscathed";
            break;
        case 1..5:
            how = "You are barely hit, but stumble slightly";
            onlooker = "barely hit, but stumbles slightly";
            stun_duration = 2;
            break;
        case 6..13:
            how = "The tackle connects solidly with you, causing" +
                " you to stagger";
            onlooker = "hit solidly by the tackle and staggers";
            stun_duration = 4;
            break;
        case 14..25:
            how = "You are almost knocked the ground by the force" +
                " of the tackle";
            onlooker = "almost knocked to the ground by the forceful" +
                " tackle";
            stun_duration = 6;
            break;
        case 26..45:
            how = "The tackle sweeps you off your feet and you slam" +
                " hard into the ground";
            onlooker = "slammed hard into the ground by the tackle";
            stun_duration = 8;
            break;
        default:
            how = "The devastating tackle flips you over and slams you" +
                " into the ground with a crushing sound";
            onlooker = "devastated by the tackle, and you hear a crushing" +
                " sound as " + enemy->query_pronoun() + " hits the ground";
            stun_duration = 10;
            break;
    }
    
    if (enemy->query_hp() <= 0)
        {
            how = "You are brutally tackled into the ground, and the" +
                " guard grapples your head between his legs. With an" +
                " abrupt scissor-like movement, he breaks your neck";
            onlooker = "brutally tackled into the ground, and the guard" +
                " grapples " + QTNAME(enemy) + "'s head. With an abrupt," +
                " scissorlike movement, " + enemy->query_possessive() +
                " neck snaps";
         }
 
    enemy->catch_tell(query_The_name(enemy) + " strikes you with a " +
                      tackle1[x] + " " + tackle2[y] +"! " +
                     how + ".\n");
    tell_watcher(QCTNAME(me) + " strikes " + QTNAME(enemy) + " with a " +
        tackle1[x] + " " + tackle2[y] + "! " +
        capitalize(enemy->query_pronoun()) + " is " + onlooker + ".\n", enemy);
    enemy->add_attack_delay(stun_duration, 1);

    if (enemy->query_hp() <= 0)
    {
        enemy->do_die(TO);
    }
    
    return 1;
}

void
create_monster()
{
    int x, y;
    string *guardfeatures, *elitefeatures;

    guardfeatures = ({"vigilant","dark-eyed","wary","attentive",
        "serious","dutiful","calm", "alert", "cautious"});

    elitefeatures = ({"powerful","forceful","deadly","mighty",
        "fierce"});

    x = random(sizeof(guardfeatures));
    y = random(sizeof(elitefeatures)); 

    set_race_name("gnome");
    add_name("guard");
    set_short(elitefeatures[y] + " " + guardfeatures[x]+" male gnome");
    add_adj(guardfeatures[x]);
    add_adj(elitefeatures[y]);

    set_gender(G_MALE);

    set_long("This gnome looks like a very experienced warrior." +
        " His lean muscles and composed stance suggests he could" +
        " kill easily, and the impassive set of his features" +
        " indicate that he would feel little remorse over doing" +
        " just that.\n");
        
    set_alignment(ALIGN);

    set_base_stat(SS_STR, 110 + random(STATDIFF));
    set_base_stat(SS_DEX, 130 + random(STATDIFF));
    set_base_stat(SS_CON, 110 + random(STATDIFF));
    set_base_stat(SS_INT, 100 + random(STATDIFF));
    set_base_stat(SS_WIS, 80 + random(STATDIFF));
    set_base_stat(SS_DIS, 120 + random(STATDIFF));

    set_skill(SS_UNARM_COMBAT, 60);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_WEP_SWORD, 90);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_PARRY, 50);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_2H_COMBAT, 90);

    set_hp(query_max_hp());

    add_prop(CONT_I_WEIGHT, 40000);
    add_prop(CONT_I_VOLUME, 40000);
    add_prop(CONT_I_HEIGHT, 95);
}

void
notify_attacked(object friend, object attacker)
{
    if (!objectp(query_attack()))
        set_alarm(1.0, 0.0, &command("assist"));
}

void
attacked_by(object enemy)
{
    object *friend;
  
    friend = (object *)query_team_others();

    friend->notify_attacked();
  
    ::attacked_by(enemy);
}

int 
query_option(int opt)
{ 
    if (opt == OPT_UNARMED_OFF) 
        return 1; 
   
    else return
       ::query_option(opt);

}