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

#define H_HEAD 0
#define H_BODY 1
#define H_SECTION 2

/* Some definitions used to mass produce these suckers ;)
 * Dunstable, Jan 30, 1995
*/

#define NAME1 "worm"
#define PNAME "worms"
#define LONG "The grey wriggling worm wriggles as you watch.\n"
#define ADJ1 "wriggling"
#define ADJ2 "grey"
#define ALIGN 40
#define WEIGH 50
#define MOUT "wriggles"
#define AMIN "arrives wriggling."   /* Don't forget the period. :) */
#define FIGHT1 6   /* Unarmed */
#define FIGHT2 6  /* Defence */
#define RM 15   /* Random move */
#define EMOTE "emote pulses back and forth."
#define ACTTIME 7
#define ACT1 "emote wriggles and slithers."
#define ACT2 "emote pulses as a whole mass."
#define ACT3 "emote coils up tightly."

void
create_creature()
{
  set_name(NAME1);
  set_pname(PNAME);
  set_long(LONG);
   set_short("grey wriggling worm");
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
    add_prop(NPC_M_NO_ACCEPT_GIVE,1);
  set_act_time(ACTTIME);
  add_act(ACT1);
  add_act(ACT2);
  add_act(ACT3);

   remove_prop(OBJ_I_NO_GET);
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

    add_hitloc(({5+random(5),5+random(5),5+random(5)}),20,"head",H_HEAD);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),50,"body",H_BODY);
    add_hitloc(({5+random(5),5+random(5),5+random(5)}),30,"legs",H_SECTION);
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
    }
    return "mind"; /* should never occur */
}

query_combat_file()
{
  return "/std/combat/cplain";
}

