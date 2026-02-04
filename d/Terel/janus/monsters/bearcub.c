 /* bearcub.c */
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
  string prace;
  if (!IS_CLONE) return;
  alig=random(20)+30;
  set_name(({"bear","bearcub"}));
  set_short("dark brown bearcub");
  set_long(break_string("A small dark brown bearcub, running around in the " +
           "snow. It doesnt seem to be afraid of you. Perhaps it know that " +
           "it's mother will protect it.\n",70));
  set_adj(({"small","brown","furry"}));
  set_race_name("bear");
  set_alignment(alig);
  set_stats(({5,4,7,3,3,10}));
  set_aggressive(0);
  set_act_time(11);
  prace = this_player()->query_race_name();
  add_act(({"sniff","flip","growl","tackle human","tackle hobbit","tackle dwarf"}));
  set_hp(49);
  set_gender(random(2));
  set_skill(SS_CLIMB,random(25));
  set_skill(SS_DEFENCE,random(5));
  add_prop(OBJ_I_WEIGHT, 7500);
  add_prop(OBJ_I_VOLUME, 8000);
  set_whimpy(1);
  seq_new("do_stuff");
  seq_addfirst("do_stuff",({"@@equip_me"}));
}
  equip_me() {
  seteuid(getuid(this_object()));
  clone_object("/d/Terel/janus/armor/smbskin") -> move(this_object());
  clone_object("/d/Terel/janus/other/smbteeth") -> move(this_object());
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
    add_attack(3,6,W_SLASH,20,A_BITE);
    add_attack(5,5,W_BLUDGEON,35,A_RPAW);
    add_attack(5,5,W_BLUDGEON,35,A_LPAW);
    add_attack(10,8,W_BLUDGEON,10,A_BHUG);

    add_hitloc( ({ 2, 2, 2 }), 15, "head", H_HEAD);
    add_hitloc( ({ 3, 3, 3 }), 60, "body", H_BODY);
    add_hitloc( ({ 3, 3, 3 }), 25, "legs", H_LEGS);
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
    return "mind"; /* should never occur */
}
