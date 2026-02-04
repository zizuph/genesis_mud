 /* rodent.c */
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
  if (!IS_CLONE) return;
  alig=random(20)-5;
  set_name(({"rodent"}));
  set_short("small furry rodent");
  set_long("A small brown rodent is running around scurruing for food. \n");
  set_adj(({"small","furry","rodent" }));
  set_race_name("rodent");
  set_alignment(alig);
  set_stats(({1,5,2,2,2,4}));
  set_aggressive(0);
  set_hp(4);
  set_act_time(20);
  add_act(({"stare","sniff"}));
  set_gender(random(2));
  set_skill(SS_DEFENCE,random(5)+5);
  add_prop(OBJ_I_WEIGHT, 500);
  add_prop(OBJ_I_VOLUME, 500);
  set_whimpy(1);
}
#define A_BITE   0
#define A_LFCLAW 1
#define A_RFCLAW 2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_TAIL 3

public void
cr_configure()
{
    add_attack(2,1,W_SLASH,40,A_BITE);
    add_attack(1,1,W_SLASH,30,A_LFCLAW);
    add_attack(1,1,W_SLASH,30,A_RFCLAW);

    add_hitloc( ({ 2, 2, 2 }), 10, "head", H_HEAD);
    add_hitloc( ({ 1, 1, 1 }), 40, "body", H_BODY);
    add_hitloc( ({ 2, 2, 1 }), 25, "legs", H_LEGS);
    add_hitloc( ({ 3, 3, 3 }), 25, "tail", H_TAIL);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    case A_LFCLAW:return "left paw";
    case A_RFCLAW:return "right paw";
    }
}
