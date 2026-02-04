 /* ferret.c */
 /* janus 920701 */ 
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
  alig=random(20)-40;
  set_name(({"ferret"}));
  set_short("gray ferret");
  set_long("A small grey ferret. The long sleek body seems made for hunting\n"+
           "small rodents and birds. \n");
  set_adj(({"small","gray"}));
  set_race_name("ferret");
  set_alignment(alig);
  set_stats(({5,4,4,3,3,10}));
  set_random_move(random(80)+20);
  set_aggressive(0);
  set_act_time(11);
  add_act(({"snarl","kill rodent","kill hare","get corpse"}));
  set_hp(20);
  set_gender(random(1));
  set_skill(SS_CLIMB,random(25)+20);
  set_skill(SS_DEFENCE,random(5)+15);
  add_prop(OBJ_I_WEIGHT, 2000);
  add_prop(OBJ_I_VOLUME, 2400);
  set_whimpy(1);
  seq_new("do_stuff");
  seq_addfirst("do_stuff",({"@@equip_me"}));
}
  equip_me() {
  seteuid(getuid(this_object()));
  clone_object("/d/Terel/janus/other/fskin") -> move(this_object());
  }
#define A_BITE  0
#define A_LPAW  1
#define A_RPAW  2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_TAIL 3

public void
cr_configure()
{
    add_attack(8,3,W_SLASH,70,A_BITE);
    add_attack(5,2,W_BLUDGEON,15,A_RPAW);
    add_attack(5,2,W_BLUDGEON,15,A_LPAW);

    add_hitloc( ({ 1, 1, 1 }), 10, "head", H_HEAD);
    add_hitloc( ({ 2, 2, 2 }), 50, "body", H_BODY);
    add_hitloc( ({ 2, 2, 2 }), 20, "legs", H_LEGS);
    add_hitloc( ({ 2, 2, 2 }), 30, "tail", H_TAIL);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    case A_RPAW:return "right front paw";
    case A_LPAW:return "left front paw";
    }
}
