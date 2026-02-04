/* queen bug */
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
#include "/d/Terel/common/terel_defs.h"
#define TO this_object()
#define TP this_player()

int RND;

create_creature()
{
  if (!IS_CLONE) return;
  RND=(random(10));
  set_name("bug");
  add_name("queen");
  set_short("queen bug");
  set_long(break_string("A huge glistening black bug. "+
	"It has huge facetted "+
	"eyes and relatively huge mandibles, about the size of your "+
	"leg. The abdomen is swollen, greysish white, and, soft looking. "+
	"As you study the queen, she lays an childsized egg, which the "+
	"worker ants take care of. \n",70));
  set_adj(({"black","queen"}));
  set_race_name("bug");
  set_alignment(-47);
  set_stats(({85+RND,65+RND,88+RND,45+RND,45+RND,89+RND}));
  set_aggressive(1);
  set_hp(9999);
  set_mana(9999);
  set_fatigue(9999);
  set_gender(1);
  add_prop(LIVE_I_SEE_DARK,1);
  set_skill(SS_CLIMB,random(55));
  set_skill(SS_DEFENCE,random(15)+60);
  set_skill(SS_BLIND_COMBAT,random(15)+85);
  set_skill(SS_UNARM_COMBAT,random(15)+75);
  set_skill(SS_AWARENESS,random(15)+70);
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
//  add_attack(79+RND,55+RND,W_SLASH,100,A_BITE);
    add_attack(50,30,W_SLASH,100,A_BITE);
  add_hitloc( ({ 35+RND, 35+RND, 35+RND }), 25, "head", H_HEAD);
  add_hitloc( ({ 25+RND, 25+RND, 20+RND }), 45, "body", H_BODY);
  add_hitloc( ({ 30+RND, 30+RND, 25+RND }), 30, "legs", H_LEGS);
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
    n = killer->query_prop("_killed_queen_");
    if (n > 0) {
      killer->change_prop("_killed_queen_", n+1);
    } else {
      killer->add_prop("_killed_queen_", 1);
    }
  }
  ::do_die(killer);
  return;
}
