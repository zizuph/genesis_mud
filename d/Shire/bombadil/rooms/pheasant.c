 /*
  * /d/Gondor/common/npc/rabbit.c
  * an animal for the plains of Rohan
  * attack and hitloc id's copied from Zephram,
  * idea and code for making the corpse edible from Glindor
  *
  * Olorin              feb 1993
   * Borrowed for use in the Shire as a Squirrel. Dunstable ;)
   * Oct 1994
  */

inherit "/std/creature";

inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/common/lib/goodkill.h"
#include "/d/Shire/common/defs.h"


/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2
#define A_LHPAW 3
#define A_RHPAW 4

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

create_creature()
{
  if (!IS_CLONE) return;
  set_name("pheasant");
  add_name("animal");
  add_name("creature");
  add_name("pheasant");
  set_short("brown striped squirrel");
  set_long("A brown striped squirrel with a bushy tail and big teeth, looking quite harmless. \n");
  set_adj(({"small","brown"}));
  set_race_name("squirrel");
set_alignment(75-random(25));
  set_stats(({7+random(8),10+random(6),5+random(5),5+random(5),5+random(10),1+random(5)}));
  set_hp(5000);
  set_gender(random(2));
  set_skill(SS_UNARM_COMBAT,20+random(10));
  set_skill(SS_DEFENCE,20+random(10));
  set_skill(SS_SWIM,40+random(20));
  set_whimpy(50 + random(50));
  set_random_move(5);
  add_prop(CONT_I_WEIGHT,4500+random(2500));
  add_prop(CONT_I_VOLUME,TO->query_prop(CONT_I_WEIGHT)*75/100);
  seq_new("do_first");
  seq_addfirst("do_first",({"@@arm_me","stare","emote nibbles at the grass."}));
}

arm_me()
{
  seteuid(getuid(TO));
  set_m_out("flies");
    set_m_in("flies in");
}

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
    add_attack(5+random(5),5+random(5),W_IMPALE,30,A_BITE);
    add_attack(5+random(5),5+random(5),W_SLASH,20,A_LPAW);
    add_attack(5+random(5),5+random(5),W_SLASH,20,A_RPAW);
    add_attack(5+random(5),5+random(5),W_SLASH,15,A_LHPAW);
    add_attack(5+random(5),5+random(5),W_SLASH,15,A_RHPAW);

    add_hitloc(({5+random(5),5+random(5),5+random(5)}),20,"head",H_HEAD);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),50,"body",H_BODY);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),30,"legs",H_LEGS);
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
    case A_LPAW:return "left wing;
    case A_RPAW:return "right wing";
    case A_LHPAW:return "left claw";
    case A_RHPAW:return "right claw";
    }
    return "mind"; /* should never occur */
}

query_combat_file()
{
  return "/std/combat/cplain";
}

