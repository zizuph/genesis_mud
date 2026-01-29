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
#define A_STING  0

#define H_HEAD 0
#define H_BODY 1
#define H_WINGS 2

/* Some definitions used to mass produce these suckers ;)
 * Dunstable, Jan 30, 1995
*/

#define NAME1 "bee"
#define NAME2 "bee"
#define NAME3 "bee"
#define PNAME "bees"
#define LONG "The bee flutters around with the wind.\n"
#define ADJ1 "golden"
#define ADJ2 "striped"
#define ALIGN 25
#define WEIGH 500
#define MOUT "buzzes"
#define AMIN "enters buzzing."   /* Don't forget the period. :) */
#define FIGHT1 30   /* Unarmed */
#define FIGHT2 60  /* Defence */
#define RM 8   /* Random move */
#define EMOTE "emote alights on a blade of grass."
#define ACTTIME 7
#define ACT1 "emote buzzes past your ear."
#define ACT2 "emote alights on a blade of grass."
#define ACT3 "emote flies around quickly."

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
   set_stats(({3+random(2),15+random(6),2+random(2),5+random(5),5+random(10),1+random(5)}));

  set_gender(random(2));
  set_skill(SS_UNARM_COMBAT, FIGHT1+random(10));
  set_skill(SS_DEFENCE,FIGHT2+random(10));
  set_whimpy(20 + random(50));
  set_random_move(RM);
  add_prop(CONT_I_WEIGHT,WEIGH+random(2500));
  add_prop(CONT_I_VOLUME,TO->query_prop(CONT_I_WEIGHT)*75/100);
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
    add_attack(5+random(5),5+random(5),W_SLASH,100,A_STING);

    add_hitloc(({5+random(5),5+random(5),5+random(5)}),20,"head",H_HEAD);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),50,"body",H_BODY);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),30,"legs",H_WINGS);
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
    case A_STING:return "sting";
    }
    return "mind"; /* should never occur */
}

query_combat_file()
{
  return "/std/combat/cplain";
}

