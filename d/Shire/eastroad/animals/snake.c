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

#define NAME1 "snake"
#define NAME2 "grass snake"
#define NAME3 "snake"
#define PNAME "snakes"
#define LONG "This green snake looks rather harmless.\n"
#define ADJ1 "tiny"
#define ADJ2 "green"
#define ALIGN 15
#define WEIGH 1500
#define MOUT "slithers"
#define AMIN "slithers in."   /* Don't forget the period. :) */
#define FIGHT1 30   /* Unarmed */
#define FIGHT2 20  /* Defence */
#define RM 8   /* Random move */
#define EMOTE "emote uncoils slowly."
#define ACTTIME 7
#define ACT1 "emote slithers around in the grass."
#define ACT2 "emote wriggles gently."
#define ACT3 "emote hisses quietly."

void
create_creature()
{
  if (!IS_CLONE) return;
  set_name(NAME1);
  add_name(({NAME2,NAME3}));
  set_pname(PNAME);
  set_long(LONG);
  set_adj(({ADJ1,ADJ2}));
  set_race_name(NAME1);
  set_alignment(ALIGN-random(50));
   set_stats(({3+random(8),9+random(6),4+random(7),5+random(5),5+random(10),1+random(5)}));

  set_gender(random(2));
  set_skill(SS_UNARM_COMBAT, FIGHT1+random(10));
  set_skill(SS_DEFENCE,FIGHT2+random(10));
  set_whimpy(50 + random(50));
  set_random_move(RM);
  add_prop(CONT_I_WEIGHT,WEIGH+random(2500));
  add_prop(CONT_I_VOLUME,TO->query_prop(CONT_I_WEIGHT)*75/100);
   add_prop(LIVE_I_NEVERKNOWN,1);
  seq_new("do_first");
  seq_addfirst("do_first",({"@@arm_me",EMOTE}));
  set_act_time(ACTTIME);
  add_act(ACT1);
  add_act(ACT2);
  add_act(ACT3);
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
    add_attack(5+random(5),5+random(5),W_SLASH,20,A_BITE);
    add_attack(5+random(5),5+random(5),W_SLASH,20,A_BITE);
    add_attack(5+random(5),5+random(5),W_SLASH,15,A_BITE);
    add_attack(5+random(5),5+random(5),W_SLASH,15,A_BITE);

    add_hitloc(({5+random(5),5+random(5),5+random(5)}),30,"head",H_HEAD);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),40,"body",H_BODY);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),30,"tail",H_LEGS);
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

