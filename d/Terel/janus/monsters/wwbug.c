/* warrior bug */
/* janus 920901 */
/* Revisions: Lilith Oct 2021: Player notified me that these are way too 
 *                    tough after the white hits change. I've reduced the 
 *                    damage of the bite attack.
 */
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
  if (!IS_CLONE) return;
  RND=(random(10));
  set_name("bug");
  set_short("warrior bug");
  set_long(break_string("A large black glistening bug. It has huge faceted "+
      "eyes and relatively huge mandibles, about the size of your leg.\n",70));
  set_adj(({"black","warrior"}));
  set_race_name("bug");
  set_alignment(-22);
  

  set_stats(({80+RND,60+RND,82+RND,40+RND,40+RND,90+RND}));
  set_aggressive(1);
  set_hp(9999);
  set_mana(9999);
  set_fatigue(9999);
  set_gender(0);
  add_prop(LIVE_I_SEE_DARK,1);
  set_skill(SS_CLIMB,random(25));
  set_skill(SS_DEFENCE,random(15)+40);
  set_skill(SS_BLIND_COMBAT,random(15)+70);
  set_skill(SS_UNARM_COMBAT,random(15)+70);
  set_skill(SS_AWARENESS,random(15)+50);
  add_prop("_janus_peace_",1);
  add_prop(CONT_I_WEIGHT, 700000);
  add_prop(CONT_I_VOLUME, 700000);
  add_prop(CONT_I_MAX_WEIGHT, 800000);
  add_prop(CONT_I_MAX_VOLUME, 800000);
  set_whimpy(0);
}

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
  cr_configure()
{
// White hits change has made this insanely damaging, especially
// for a quest. I'm going to reduce this significantly.	-Lilith
//  add_attack(83+RND,40+RND,W_SLASH,100,A_BITE);
  add_attack(40, 40, W_SLASH, 100, A_BITE);
  add_hitloc( ({ 30+RND, 30+RND, 30+RND }), 15, "head", H_HEAD);
  add_hitloc( ({ 38+RND, 38+RND, 38+RND }), 65, "body", H_BODY);
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
