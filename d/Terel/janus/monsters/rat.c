 /* rat */
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

create_creature()
{
  int alig;
  if (!IS_CLONE) return;
  alig=(-25);
  set_name(({"rat"}));
  set_short("gargantuan rat");
  set_long(break_string("A gargantuan brown sewer rat. It has beady red"+
     " eyes and huge sharp set of teeth. \n",70));
  set_adj(({"brown"}));
  set_race_name("rat");
  set_alignment(alig);
  set_stats(({110,40,110,15,15,60}));
  set_aggressive(1);
  set_hp(10000);
  set_gender(0);
  set_skill(SS_CLIMB,random(25));
  set_skill(SS_DEFENCE,random(15)+30);
  add_prop(OBJ_I_WEIGHT, 1900000);
  add_prop(OBJ_I_VOLUME, 1900000);
  add_prop(CONT_I_MAX_WEIGHT, 2400000);
  add_prop(CONT_I_MAX_VOLUME, 2400000);
  set_whimpy(0);
}

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_TAIL 3
#define H_EYES 4

public void
cr_configure()
{
    add_attack(85,85,W_SLASH,100,A_BITE);

    add_hitloc( ({ 35, 35, 35 }), 15, "head", H_HEAD);
    add_hitloc( ({ 5, 5, 5 }), 5, "eye", H_EYES);
    add_hitloc( ({ 45, 45, 45 }), 10, "tail", H_TAIL);
    add_hitloc( ({ 39, 39, 39 }), 55, "body", H_BODY);
    add_hitloc( ({ 35, 35, 35 }), 15, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    }
}
