 /* bird.c */
 /* janus 920621 */
 
inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

#include <wa_types.h>
#include <ss_types.h>
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

create_creature()
{
  int alig;
  int volym;
  int weight;
  if (!IS_CLONE) return;
  weight=random(1000)+1500;
  volym=random(1000)+1500;
  set_name(({"bat"}));
  set_short("small black bat");
  set_long(break_string("The small hairy black bat is zooming around this "+
            "room, searching for some good tasting insects.\n",70));
  set_adj(({"black","hairy","small"}));
  set_race_name("bat");
  set_alignment(-10);
  set_stats(({5,16,10,5,5,5}));
  set_aggressive(0);
  add_prop(OBJ_I_WEIGHT, weight);
  add_prop(OBJ_I_VOLUME, volym);
  set_hp(100);
  set_gender(random(1));
  set_skill(SS_DEFENCE,random(5)+35);
  set_whimpy(0);
}
#define A_BITE   0
#define A_WING   1

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_WING 3

public void
cr_configure()
{
    add_attack(15,5,W_IMPALE,75,A_BITE);
    add_attack(10,4,W_BLUDGEON,25,A_WING);

    add_hitloc( ({ 3, 3, 3 }), 10, "head", H_HEAD);
    add_hitloc( ({ 2, 2, 2 }), 30, "body", H_BODY);
    add_hitloc( ({ 2, 2, 1 }), 5, "legs", H_LEGS);
    add_hitloc( ({ 2, 2, 1 }), 55, "wings", H_WING);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    case A_WING:return "wing bash";
    }
}

