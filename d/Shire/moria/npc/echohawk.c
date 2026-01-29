//
// echohawk.c
//
// Echohawks are lone birds with an increadible infra-vision to be able
// to maneuver inside dark caverns. No pigmentation. Strong musclature
// resembling eagles. Two-three feet wingspan. Speed ninety miles per hour
// (144 km/hour). Beaks do penetrate armour.
//

#include "defs.h"
#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>
#include <stdproperties.h>

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit IM_TELL_FILE;

#define ATT_BEAK 0
#define ATT_CLAWS 1

#define HIT_BODY 0
#define HIT_LWING 1
#define HIT_RWING 2
#define HIT_HEAD 3

int not_hitable;
int attack_alarm;
int check_alarm;

void check_present();
void first_attack(object who);

create_creature()
{
    if (!IS_CLONE)
	return;

    set_name("echohawk");
    set_living_name("echohawk");
    set_race_name("hawk");
    set_long(
	  "This is a large echohawk, a bird with three feet wingspan "
	+ "and strong musclature resembling eagles. It is remarkable "
	+ "that the echohawk do not have any pigmentation, typical of "
        + "underground creatures, not being able to use the light of "
        + "the sun for navigation. It probably uses sonar senses like "
        + "that of bats instead.\n");
    set_stats(({ 30, 93, 80, 12, 10, 100 }));
    /* Typical of birds having high dexterity and rather low strength,
       this bird is vicious when it is faced with hunger, attacking about
       all there is. */
    set_skill(SS_DEFENCE, 5);
    set_attack_unarmed(ATT_BEAK, 30, 19, W_IMPALE, 40, "beak");
    set_attack_unarmed(ATT_CLAWS, 30, 30, W_IMPALE, 60, "claws");
    set_hitloc_unarmed(HIT_BODY,  7, 40, "body");
    set_hitloc_unarmed(HIT_LWING, 5, 20, "left wing");
    set_hitloc_unarmed(HIT_RWING, 5, 20, "right wing");
    set_hitloc_unarmed(HIT_HEAD, 12, 20, "head");

    refresh_mobile();

   set_aggressive(1);
   set_alignment(-250 + random(25));
    add_prop(CONT_I_WEIGHT, 12000);
    add_prop(CONT_I_VOLUME, 14000);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 10);  
    add_prop(LIVE_I_SEE_INVIS, 40); /* Can a sonar see invis? Of course.. */
    not_hitable = 0;
    check_alarm = set_alarm(13.0, 0.0, &check_present());
}

int
first_attack(object enemy)
{
    object room;
    string res;

    room = ENV(enemy);
    move_living("M", room);

    add_prop(LIVE_O_ENEMY_CLING, enemy);
    
    not_hitable = 0;
    res = enemy->hit_me(120, W_IMPALE, TO, -1);

    switch(res[0])
	{
	  case -1..0:
	    res = "but mysteriously manages to stand up again, unhurt.";
	    break;
	  case 1..10:
	    res = "completely surprised by the attack.";
	    break;
	  case 11..30:
	    res = "hurt badly by the echohawk's beak.";
	    break;
	  case 31..60:
	    res = "terribly hurt from the echohawk's beak and forceful impact.";
	    break;
	  case 61..80:
	    res = "utterly massacrated from the echohawk's blindingly fast speed.";
	    break;
	  case 81..99:
	    res = "wasted in the increadible fast echohawk's attack!";
	    break;
	}
    
    tellem(TO, enemy,
	"A huge white and dirty bird swishes into the room and "
      + "strikes #name with staggering force!\n", 1);

    if (HP(enemy) <= 0)
    {
	tell_room(room,
	    QCTNAME(enemy) + " is knocked unconsious, gurgles some blood, sighs deeply, gets pale and "
	  + "leaves the world in the Deeps of Moria....\n", enemy);
	enemy->catch_msg(
            "The bird strikes you terribly, piercing your body!!!!!\n"
	  + "You cough up some blood, feeling a terrible inner pain, before "
	  + "you meet Death as you met your faith in the Deeps of Moria.\n");
	enemy->do_die(TO);
    }


    enemy->catch_msg("You are knocked down on the floor, " + res + "\n");
    tell_room(room,
          QCTNAME(enemy) + " is knocked down on the floor, "+ res + "\n", enemy);

    return 1;
}

int
special_attack(object enemy)
{
    if (query_hp() < query_max_hp() / 3)
    {
	tell_room(environment(),
	    "The echohawk decides that its enemies costs more "
	  + "energy than gained by eating its corpses, and "
          + "with a few flaps, the great echohawk flies away "
          + "into the darkness.\n");
        move_living("M", MINES_DIR + "orc_lair");
	heal_hp(1000);
        return 1;
    }
    if (not_hitable)
      {
	tell_room(environment(),
		  "The echohawk circles above you, gaining speed!\n");
	return 1;
      }
    if ((random(10) == 2) && (!attack_alarm))
    {
        tell_room(environment(),
	    "The echohawk flies up in the air to prepare an attack!\n" +
            "It circles around above you, gaining an awesome speed!\n");
	not_hitable = 1;
    attack_alarm = set_alarm(10.0, 0.0, &first_attack(query_attack()));
	return 1;
    }
    return 0;
}

//
// I want to find out if the damage is done by a weapon, or a spell.
// I want to find out if the weapon is hurled, or not.
//
public mixed
hit_me(int wcpen, int dt, object attacker, int attack_id)
{
    object po = previous_object();
    object catt = attacker->query_combat_object();

    if (!not_hitable)
      return ::hit_me(wcpen, dt, attacker, attack_id);

    if (po->check_weapon())
      {
	if (po->query_prop("_weapon_i_hurled_distance") < 1000)
	  {
	    attacker->catch_msg("You can't reach the hawk at that range!\n");
	    return ({ 0, 0, 0, 0 });
	  }
	else
	  return ::hit_me(wcpen, dt, attacker, attack_id);
      }

    if (attacker->query_prop(LIVE_O_SPELL_ATTACK) || dt <= -1)
      return ::hit_me(wcpen, dt, attacker, attack_id);

    attacker->catch_msg("The echohawk can't be attacked in that range.\n");
    return ({ 0, 0, 0, 0 });
} 

check_present()
{
    if (query_attack())
        if (present(query_attack(), environment(TO)))
        {
            if (!check_alarm)
                check_alarm = set_alarm(12.0, 0.0, &check_present());
            return;
        }
	tell_room(environment(),
		  "The echo-hawk flaps away into the darkness.\n");
	move_living("M", MINES_DIR + "orc_lair");
    if ((query_attack()) && (!check_alarm))
        check_alarm = set_alarm(12.0, 0.0, &check_present());
}
