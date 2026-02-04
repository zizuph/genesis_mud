 /* killer rabbit2.c */
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
  alig=random(50);
  set_name(({"rabbit"}));
  set_short("white rabbit");
  set_long(" A small cute white rabbit. It has a cuddly furry pelt and \n"+
           "large white teeth. \n");
  set_adj(({"small","cute"}));
  set_race_name("rabbit");
  set_alignment(alig);
  set_stats(({4,8,5,3,3,3}));
  set_aggressive(0);
  set_act_time(15);
  add_act(({"sniff","stare"}));
  set_hp(20);
  set_gender(random(2));
  set_skill(SS_DEFENCE,random(25));
  add_prop(OBJ_I_WEIGHT, 2500);
  add_prop(OBJ_I_VOLUME, 3000);
  add_item("teeth","Looking closer at the rabbit's teeth you see that\n"+
           "they look perfectly normal.\n");
  add_item(({"pelt","skin"}),"The pelt could be worth a few coppers properly prepared.\n");
  seq_addfirst("do_stuff",({"@@equip_me"}));
  set_whimpy(0);
}
  equip_me() {
    seteuid(getuid(this_object()));
  clone_object("/d/Terel/janus/other/meat") -> move(this_object());
  clone_object("/d/Terel/janus/other/hskin") -> move(this_object());
  }

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(3,3,W_SLASH,100,A_BITE);

    add_hitloc( ({ 1, 1, 1 }), 15, "head", H_HEAD);
    add_hitloc( ({ 1, 1, 1 }), 60, "body", H_BODY);
    add_hitloc( ({ 1, 1, 1 }), 25, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    }
}
