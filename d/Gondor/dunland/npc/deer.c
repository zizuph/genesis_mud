 /* deer.c */
 
inherit "/std/creature";
inherit "std/combat/unarmed";

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
  alig=random(500)-200;
  set_name(({"deer","beast","animal"}));
  set_short("reddish brown deer");
  set_long("A reddish brown young deer.\n");
  set_adj(({"reddish","brown","young"}));
  set_race_name("animal");
  set_alignment(alig);
  
set_stats(({random(10)+19,random(24)+40,random(20)+10,random(5),random(10),random(5)+1}));
  set_aggressive((random(999)-alig)/1000);
  set_attack_chance((random(999)-alig)/20);
  set_hp(random(500)+300);
  set_gender(random(2));
  set_skill(SS_UNARM_COMBAT,random(10)+2);
  set_skill(SS_CLIMB,random(15)+20);
  set_skill(SS_SWIM,random(10)+15);
  set_skill(SS_DEFENCE,random(20)+10);
  set_skill(SS_PARRY,random(4)+6);
  set_whimpy(1);
  set_random_move(random(20)+2);
  seq_new("do_stuff");
  seq_addfirst("do_stuff","@@equip_me");
}
equip_me() {
  seteuid(getuid(this_object()));
  clone_object("/d/Gondor/dunland/armour/dskin") -> move(this_object());
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
    add_attack(random(10)+5,random(10)+15,W_IMPALE,5,A_BITE);
    add_attack(random(20)+10,random(20)+10,W_BLUDGEON,15,A_CHARGE);
    add_attack(random(20)+15,random(15)+5,W_SLASH,60,A_FHOOVES);
    add_attack(random(20)+10,random(30)+10,W_SLASH,20,A_RHOOVES);
 
    add_hitloc(({random(5)+15,random(2)+5,random(2)+6}),10,"head",H_HEAD);
    add_hitloc(({random(3)+8,random(2)+11,random(2)+10}),45,"body",H_BODY);
    add_hitloc(({random(10)+15,random(2)+4,random(2)+5}),40,"legs",H_LEGS);
    add_hitloc(({random(20)+30,random(2)+3,random(5)+15}),5,"tail",H_TAIL);
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
    case A_BITE:return "bite";
    case A_CHARGE:return "charge";
    case A_FHOOVES:return "front hooves";
    case A_RHOOVES:return "rear hooves";
    }
    return "mind"; /* should never occur */
}

