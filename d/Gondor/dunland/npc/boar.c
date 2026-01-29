 /* boar.c */
inherit "/std/combat/unarmed";
 
inherit "/std/creature";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include "/sys/macros.h"

create_creature()
{
  int alig;
  if (!IS_CLONE) return;
  alig=random(1400)-1000;
  set_name(({"boar","beast","pig","animal"}));
  set_short("bristly brown boar");
  set_long("A bristly brown wild male pig with large ivory tusks.\n");
  set_adj(({"bristly","brown","wild","male"}));
  set_race_name("pig");
  set_alignment(alig);
  
set_stats(({random(30)+20,random(15)+30,random(40)+40,random(17),random(20),random(25)+25}));
  set_aggressive((random(999)-alig)/1000);
  set_attack_chance((random(999)-alig)/20);
  set_hp(random(2000)+1500);
  set_gender(0);
  set_skill(SS_UNARM_COMBAT,random(20)+30);
  set_skill(SS_CLIMB,random(15)+10);
  set_skill(SS_SWIM,random(10)+5);
  set_skill(SS_DEFENCE,random(20)+30);
  set_skill(SS_PARRY,random(20)+30);
  set_whimpy(random(2));
  set_random_move(random(5)+1);
  seq_new("do_stuff");
  seq_addfirst("do_stuff",({"@@equip_me","snarl"}));
}
equip_me() {
  seteuid(getuid(this_object()));
  clone_object("/d/Gondor/dunland/armour/boarskin") -> move(this_object());
  clone_object("/d/Gondor/dunland/armour/boarhelm") -> move(this_object());
  clone_object("/d/Gondor/dunland/obj/boartusk") -> move(this_object());
  clone_object("/d/Gondor/dunland/obj/boartusk") -> move(this_object());

  }


/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_CHARGE 1
#define A_FHOOVES 2
#define A_RHOOVES 3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_TAIL 3

/*
 * Here we add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *
 * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */
public void
cr_configure()
{
    add_attack(random(15)+5,random(20)+15,W_SLASH,45,A_BITE);
    add_attack(random(40)+30,random(30)+30,W_BLUDGEON,25,A_CHARGE);
    add_attack(random(20)+15,random(15)+5,W_SLASH,20,A_FHOOVES);
    add_attack(random(20)+10,random(30)+10,W_BLUDGEON,10,A_RHOOVES);
 
    add_hitloc(({random(15)+25,random(20)+15,random(20)+20}),10,"head",H_HEAD);
    add_hitloc(({random(6)+4,random(12)+11,random(12)+10}),45,"body",H_BODY);
    add_hitloc(({random(10)+15,random(4)+4,random(4)+5}),40,"legs",H_LEGS);
    add_hitloc(({random(30)+40,random(12)+13,random(15)+25}),5,"tail",H_TAIL);
}

/*
 * Give description of each attack. We could also redefine the entire
 * hitdescription by redefining 'cr_did_hit'
 */
public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "tusks";
    case A_CHARGE:return "charge";
    case A_FHOOVES:return "front feet";
    case A_RHOOVES:return "trample";
    }
    return "mind"; /* should never occur */
}


