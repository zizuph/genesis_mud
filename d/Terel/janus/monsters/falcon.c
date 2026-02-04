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
  alig=random(100)-50;
  set_name(({"falcon"}));
  set_short("white falcon");
  set_long(break_string("This falcon has adapted to a life in cold climates."+ 
       " The feathers are white, making it difficult for its prey to spot " + 
       "it, and many, keeping the bird warm even in cold weather. It " + 
       "appears to search for prey as it is flying fast and high. \n",70));
  set_adj(({"white"}));
  set_race_name("falcon");
  set_alignment(alig);
  set_stats(({10,30,8,5,5,20}));
  set_aggressive(0);
  set_random_move(random(50)+20);
  set_gender(random(2));
  set_skill(SS_DEFENCE,random(25)+30);
  add_prop(OBJ_I_WEIGHT, 1500);
  add_prop(OBJ_I_VOLUME, 1600);
  add_prop(CONT_I_MAX_WEIGHT, 1000);
  add_prop(CONT_I_MAX_VOLUME, 1000);
  set_whimpy(0);
  set_act_time(21);
  add_act(({"glare","kill rodent","kill bird","get corpse"}));
  set_hp(64);
}

#define A_BITE  0
#define A_LCLW  1
#define A_RCLW  2

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_LWNG 3
#define H_RWNG 4

public void
cr_configure()
{
    add_attack(15,8,W_IMPALE,20,A_BITE);
    add_attack(25,10,W_SLASH,40,A_RCLW);
    add_attack(25,10,W_SLASH,40,A_LCLW);

    add_hitloc( ({ 2, 2, 2 }), 10, "head", H_HEAD);
    add_hitloc( ({ 2, 2, 2 }), 40, "body", H_BODY);
    add_hitloc( ({ 2, 2, 2 }), 20, "legs", H_LEGS);
    add_hitloc( ({ 3, 3, 3 }), 15, "left wing", H_LWNG);
    add_hitloc( ({ 3, 3, 3 }), 15, "right wing", H_RWNG);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_BITE:return "bite";
    case A_RCLW:return "right claw";
    case A_LCLW:return "left claw";
    }
}

