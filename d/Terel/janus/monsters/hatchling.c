 /* hatchling bug */
 /* janus 920901 */
 
inherit "/std/creature";

inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#define TO this_object()
#define TP this_player()

int RND;

create_creature()
{
  int alig;
  if (!IS_CLONE) return;
  alig=(-5);
  RND=(10-random(10));
  set_name(({"bug"}));
  set_short("hatchling bug");
  set_long(break_string("A newly hatched bug. The carapace is still slightly moist " +
     "and soft. It looks almost cute for a 100 pound bug. \n",70));
  set_adj(({"black","hatchling"}));
  set_race_name("bug");
  set_alignment(alig);
  set_stats(({15+RND,5+RND,15+RND,4+RND,4+RND,10+RND}));
  set_aggressive(0);
  set_hp(9999);
  set_fatigue(9999);
  set_mana(9999);
  set_gender(2);
  add_prop(LIVE_I_SEE_DARK,1);
  set_skill(SS_CLIMB,random(25));
  set_skill(SS_UNARM_COMBAT,15+RND);
  set_skill(SS_BLIND_COMBAT,35+random(25));
  set_skill(SS_AWARENESS,35+random(25));
  set_skill(SS_DEFENCE,random(15)+2);
  add_prop(OBJ_I_WEIGHT, 100000);
  add_prop(OBJ_I_VOLUME, 100000);
  add_prop(CONT_I_MAX_WEIGHT, 600000);
  add_prop(CONT_I_MAX_VOLUME, 600000);
  set_whimpy(0);
}

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(10+RND,15+RND,W_SLASH,100,A_BITE);

    add_hitloc( ({ 10+RND, 10+RND, 10+RND }), 15, "head", H_HEAD);
    add_hitloc( ({ 30+RND, 30+RND, 30+RND }), 65, "body", H_BODY);
    add_hitloc( ({ 25+RND, 25+RND, 25+RND }), 20, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    }
}

