 /* killer rabbit.c */
 /* janus 920629 */ 
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
  alig=-10000;
  set_name(({"rabbit"}));
  set_short("brown rabbit");
  set_long(" A small cute brown rabbit. It has a cuddly furry pelt and \n"+
           "large white teeth. \n");
  set_adj(({"small","cute"}));
  set_race_name("animal");
  set_alignment(alig);
  set_stats(({80,100,60,15,15,90}));
  set_aggressive(0);
  set_act_time(15);
  add_act(({"growl","glare"}));
  set_hp(6000);
  set_gender(random(1));
  set_skill(SS_DEFENCE,random(50)+50);
  add_prop(OBJ_I_WEIGHT, 2500);
  add_prop(OBJ_I_VOLUME, 3000);
  add_item("teeth","Looking closer at the rabbit's teeth you see that\n"+
           "they look awfully sharp. Sharp enough to rip your throat out.\n");
  add_item(({"pelt","skin"}),"The pelt has some dark stains on it.\n");
  add_item(({"stains","dark stains"}),"They appear to be dried blood.\n");
}

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(120,140,W_SLASH,140,A_BITE);

    add_hitloc( ({ 20, 20, 20 }), 15, "head", H_HEAD);
    add_hitloc( ({ 18, 18, 18 }), 60, "body", H_BODY);
    add_hitloc( ({ 18, 18, 18 }), 25, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    }
}
