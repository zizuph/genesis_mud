 /* large male bear.c */
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
  alig=random(60)-30;
  set_name(({"bear"}));
  set_short("dark brown bear");
  set_long(break_string("This is a large male bear. He appears to be " + 
     "sleeping. Better not wake him, those claws of his looks " + 
     "awfully big.\n",70));
  set_adj(({"brown","furry"}));
  set_race_name("bear");
  set_alignment(alig);
  set_stats(({65,25,55,4,4,80}));
  set_aggressive(0);
  set_hp(7000);
  set_gender(0);
  set_skill(SS_CLIMB,random(25));
  set_act_time(21);
  add_act(({"snore","growl","snarl","yawn"}));
  set_skill(SS_DEFENCE,random(15)+20);
  add_prop(OBJ_I_WEIGHT, 1200000);
  add_prop(OBJ_I_VOLUME, 1200000);
  add_prop(CONT_I_MAX_WEIGHT, 1400000);
  add_prop(CONT_I_MAX_VOLUME, 1400000);
  set_whimpy(0);
  seq_new("do_stuff");
  seq_addfirst("do_stuff",({"@@equip_me","snore"}));
}
  equip_me() {
  seteuid(getuid(this_object()));
  clone_object("/d/Terel/janus/armor/mbskin") -> move(this_object());
  clone_object("/d/Terel/janus/other/mbteeth") -> move(this_object());
}

#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2
#define A_BHUG  3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
cr_configure()
{
    add_attack(45,45,W_SLASH,25,A_BITE);
    add_attack(55,65,W_BLUDGEON,30,A_RPAW);
    add_attack(55,65,W_BLUDGEON,30,A_LPAW);
    add_attack(50,80,W_BLUDGEON,15,A_BHUG);

    add_hitloc( ({ 7, 7, 7 }), 15, "head", H_HEAD);
    add_hitloc( ({ 10, 10, 10 }), 60, "body", H_BODY);
    add_hitloc( ({ 10, 10, 10 }), 25, "legs", H_LEGS);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    case A_RPAW:return "right front paw";
    case A_LPAW:return "left front paw";
    case A_BHUG:return "bearhug";
    }
}

