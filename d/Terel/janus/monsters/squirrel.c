 /* squirrel.c */
 /* janus 929621 */
 
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
  alig=random(20)+5;
  set_name(({"squirrel"}));
  set_short("small squirrel");
  set_long("A small red squirrel, leaping from branch to branch\n"+
	   "searching for edibles.\n");
  set_adj(({"small","red"}));
  set_race_name("squirrel");
  set_alignment(alig);
  set_stats(({2,10,3,1,1,5}));
  set_aggressive(0);
  set_hp(9);
  set_act_time(11);
  add_act(({"sniff","stare","flip"}));
  set_gender(random(2));
  add_prop(OBJ_I_WEIGHT, 300);
  add_prop(OBJ_I_VOLUME, 300);
  set_skill(SS_CLIMB,random(25)+50);
  set_skill(SS_DEFENCE,random(10)+5);
  add_prop(CONT_I_MAX_WEIGHT, 1000);
  add_prop(CONT_I_MAX_VOLUME, 1000);
  set_whimpy(1);
  seq_new("do_stuff");
  seq_addfirst("do_stuff",({"@@equip_me"}));
}
  equip_me(){
  seteuid(getuid(this_object()));
  clone_object("/d/Terel/janus/other/sqskin") -> move(this_object());
  }

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_TAIL 3

public void
cr_configure()
{
    add_attack(5,1,W_IMPALE,100,A_BITE);

    add_hitloc( ({ 2, 2, 2 }), 5, "head", H_HEAD);
    add_hitloc( ({ 1, 1, 1 }), 60, "body", H_BODY);
    add_hitloc( ({ 2, 2, 4 }), 35, "tail", H_TAIL);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    }
}

