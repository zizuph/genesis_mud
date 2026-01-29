 /* lion.c */
 
inherit "/std/creature";
inherit "/std/combat/unarmed";

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
  alig=random(1200)-400;
  set_name(({"animal","beast","lion"}));
  set_short("spotted tawny lion");
  set_long("A spotted tawny prowling lion.\n");
  set_adj(({"spotted","tawny","prowling"}));
  set_race_name("animal");
  set_alignment(alig);
  set_stats(({random(60)+40,random(25)+50,random(50)+50,random(5),random(10),random(40)+40}));
  set_aggressive((random(999)-alig)/1000);
  set_attack_chance((random(999)-alig)/20);
  set_hp(random(4000)+4000);
  set_gender(random(2));
  set_skill(SS_UNARM_COMBAT,random(50)+50);
  set_skill(SS_CLIMB,random(15)+10);
  set_skill(SS_SWIM,random(10)+5);
  set_skill(SS_DEFENCE,random(40)+30);
  set_skill(SS_PARRY,random(40)+40);
  set_skill(SS_SWIM,random(10)+5);
  set_skill(SS_CLIMB,random(20)+10);
  set_whimpy(random(2));
  set_random_move(random(30)+10);
  seq_new("do_stuff");
  seq_addfirst("do_stuff",({"@@equip_me","growl"}));
}
equip_me() {
  seteuid(getuid(this_object()));
  clone_object("/d/Gondor/zephram/armour/lskin") -> move(this_object());
  }


/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_CHARGE 1
#define A_LFCLAW 2
#define A_RFCLAW 3
#define A_RAKE 4

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
    add_attack(random(40)+40,random(40)+60,W_IMPALE,25,A_BITE);
    add_attack(random(40)+40,random(20)+60,W_BLUDGEON,5,A_CHARGE);
    add_attack(random(20)+50,random(30)+40,W_SLASH,30,A_LFCLAW);
    add_attack(random(20)+50,random(30)+40,W_SLASH,30,A_RFCLAW);
    add_attack(random(50)+25,random(60)+60,W_SLASH,10,A_RAKE);
 
    add_hitloc(({random(2)+11,random(2)+7,random(2)+6}),10,"head",H_HEAD);
    add_hitloc(({random(3)+8,random(2)+11,random(2)+10}),55,"body",H_BODY);
    add_hitloc(({random(10)+15,random(2)+4,random(2)+5}),30,"legs",H_LEGS);
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
    case A_LFCLAW:return "left front claw";
    case A_RFCLAW:return "right front claw";
    case A_RAKE:return "raking rear claws";
    }
    return "mind"; /* should never occur */
}

