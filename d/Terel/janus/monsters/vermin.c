 /* nuisance insect */
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
  RND=(random(2));
  alig=(-2);
  set_name(({"insect"}));
  set_short("bug");
  add_name("insect");
  set_long(break_string("A small insect. \n",70));
  set_adj(({"small"}));
  set_race_name("insect");
  add_name("bug");
  set_alignment(alig);
  set_stats(({1+RND,2+RND,1+RND,1+RND,1+RND,1+RND}));
  set_aggressive(1);
  set_hp(9999);
  set_mana(9999);
  set_fatigue(9999);
  set_gender(0);
  add_prop(LIVE_I_SEE_DARK,1);
  set_skill(SS_CLIMB,random(25));
  set_skill(SS_DEFENCE,random(5)+4);
  set_skill(SS_BLIND_COMBAT,random(2)+6);
  set_skill(SS_UNARM_COMBAT,random(2)+2);
  set_skill(SS_AWARENESS,random(15)+5);
  add_prop("_janus_peace_",0);
  add_prop(CONT_I_WEIGHT, 70);
  add_prop(CONT_I_VOLUME, 70);
  add_prop(CONT_I_MAX_WEIGHT, 80);
  add_prop(CONT_I_MAX_VOLUME, 80);
  set_whimpy(0);
}

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(8+RND,2+RND,W_SLASH,100,A_BITE);

    add_hitloc( ({ 1+RND, 1+RND, 1+RND }), 15, "head", H_HEAD);
    add_hitloc( ({ 2+RND, 2+RND, 2+RND }), 65, "body", H_BODY);
    add_hitloc( ({ 1+RND, 1+RND, 1+RND }), 20, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    }
}

public void
do_die(object killer)
{
    int n;

    if (query_hp() > 0) return;
    if (killer) {
        n = killer->query_prop("_killed_bugs_");
        if (n > 0) {
            killer->change_prop("_killed_bugs_", n+1);
        } else {
            killer->add_prop("_killed_bugs_", 1);
        }
    }
    ::do_die(killer);
    return;
}

