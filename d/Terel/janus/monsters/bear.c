 /* bear.c */
 /* janus 920620 */
 
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
  alig=random(100)-40;
  set_name(({"bear"}));
  set_short("dark brown bear");
  set_long(break_string("This is a large female bear. She doesn't seem to " +
           "be in a good mood. Maybe because she is worried for her " +
           "children. Pity the poor soul who harms her children in any " +
           "way.\n",70));
  set_adj(({"brown","furry"}));
  set_race_name("bear");
  set_alignment(alig);
  set_stats(({55,25,60,5,5,70}));
  set_aggressive(0);
  set_random_move(random(50)+10);
  set_gender(1);
  set_skill(SS_CLIMB,random(25));
  set_skill(SS_DEFENCE,random(5)+20);
  add_prop(OBJ_I_WEIGHT, 600000);
  add_prop(OBJ_I_VOLUME, 700000);
  add_prop(CONT_I_MAX_WEIGHT, 1000000);
  add_prop(CONT_I_MAX_VOLUME, 1000000);
  set_whimpy(0);
  set_act_time(21);
  add_act(({"growl","snarl","sniff","glare"}));
  seq_new("do_stuff");
  set_hp(6000);
  seq_addfirst("do_stuff",({"@@equip_me"}));
}
  equip_me() {
  seteuid(getuid(this_object()));
  clone_object("/d/Terel/janus/armor/bskin") -> move(this_object());
  clone_object("/d/Terel/janus/other/bteeth") -> move(this_object());
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
    add_attack(45,40,W_SLASH,25,A_BITE);
    add_attack(55,50,W_BLUDGEON,30,A_RPAW);
    add_attack(55,50,W_BLUDGEON,30,A_LPAW);
    add_attack(55,60,W_BLUDGEON,15,A_BHUG);

    add_hitloc( ({ 4, 5, 5 }), 15, "head", H_HEAD);
    add_hitloc( ({ 9, 9, 9 }), 60, "body", H_BODY);
    add_hitloc( ({ 9, 9, 9 }), 25, "legs", H_LEGS);
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

