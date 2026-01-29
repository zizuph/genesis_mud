/*
* This animal owes a great deal to /d/Gondor/common/npc/rabbit.
* Altered by Dunstable for mass production of East Road life,
* Jan 30, 1995, with alignment considerations by Elix
*
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
#include "/d/Shire/animals/animals.h"


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

/* Some definitions used to mass produce these suckers ;)
 * Dunstable, Jan 30, 1995
*/

#define NAME1 "chipmunk"
#define PNAME "chipmunks"
#define LONG "This chipmunk darts about energetically.\n"
#define ADJ1 "speedy"
#define ADJ2 "small"
#define ALIGN 55
#define WEIGH 2500
#define MOUT "scampers"
#define AMIN "scampers in."   /* Don't forget the period. :) */
#define FIGHT1 30   /* Unarmed */
#define FIGHT2 50  /* Defence */
#define RM 8   /* Random move */
#define EMOTE "emote looks carefully for leftover food."
#define ACTTIME 7
#define ACT1 "bounce ener"
#define ACT2 "emote darts around energetically."
#define ACT3 "emote rolls over in some nearby grass."

void
create_creature()
{
  if (!IS_CLONE) return;
  set_name(NAME1);
  set_pname(PNAME);
  set_long(LONG);
  set_adj(({ADJ1,ADJ2}));
  set_race_name(NAME1);
  set_alignment(ALIGN-random(50));
   set_stats(({3+random(8),5+random(6),4+random(7),5+random(5),5+random(10),1+random(5)}));

  set_gender(random(2));
  set_skill(SS_UNARM_COMBAT, FIGHT1+random(10));
  set_skill(SS_DEFENCE,FIGHT2+random(10));
  set_whimpy(50 + random(50));
  set_random_move(RM);
  add_prop(CONT_I_WEIGHT,WEIGH+random(2500));
  add_prop(CONT_I_VOLUME,TO->query_prop(CONT_I_WEIGHT)*75/100);
  seq_new("do_first");
  seq_addfirst("do_first",({"@@arm_me",EMOTE}));
  set_act_time(ACTTIME);
  add_act(ACT1);
  add_act(ACT2);
  add_act(ACT3);
  add_leftover(ANIM_DIR + "chipmunkskin", "skin", 1, 0, 1, 1);

}

void
arm_me()
{
  seteuid(getuid(TO));
  set_m_out(MOUT);
  set_m_in(AMIN);
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
    case A_LPAW:return "left paw";
    case A_RPAW:return "right paw";
    case A_LHPAW:return "left hind paw";
    case A_RHPAW:return "right hind paw";
    }
    return "mind"; /* should never occur */
}

query_combat_file()
{
  return "/std/combat/cplain";
}

