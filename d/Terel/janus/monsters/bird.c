 /* bird.c */
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
  int volym;
  int weight;
  if (!IS_CLONE) return;
  alig=random(20)-5;
  weight=random(1000)+1000;
  volym=random(1000)+1000;
  set_name(({"bird"}));
  set_short("small white bird");
  set_long(break_string("The white color of the bird makes it difficult to " + 
     "see. It's searching for food on the cold icy ground.\n",70));
  set_adj(({"white"}));
  set_race_name("bird");
  set_alignment(alig);
  set_stats(({2,5,2,2,2,2}));
  set_aggressive(0);
  set_act_time(31);
  add_act(({"stare"}));
  add_prop(OBJ_I_WEIGHT, weight);
  add_prop(OBJ_I_VOLUME, volym);
  set_hp(10);
  set_gender(random(1));
  set_skill(SS_DEFENCE,random(5)+5);
  seq_new("do_stuff");
  seq_addfirst("do_stuff",({"@@equip_me"}));
  set_whimpy(0);
}
  equip_me() {
      seteuid(getuid(this_object()));
        clone_object("/d/Terel/janus/other/meat") -> move(this_object());
}
#define A_PECK   0
#define A_LFCLAW 1
#define A_RFCLAW 2
#define A_WING   3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2
#define H_WING 3

public void
cr_configure()
{
    add_attack(3,2,W_IMPALE,15,A_PECK);
    add_attack(1,1,W_SLASH,30,A_LFCLAW);
    add_attack(1,1,W_SLASH,30,A_RFCLAW);
    add_attack(2,2,W_BLUDGEON,25,A_WING);

    add_hitloc( ({ 2, 2, 2 }), 10, "head", H_HEAD);
    add_hitloc( ({ 1, 1, 1 }), 20, "body", H_BODY);
    add_hitloc( ({ 2, 2, 1 }), 25, "legs", H_LEGS);
    add_hitloc( ({ 2, 2, 1 }), 45, "wings", H_WING);
}

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_PECK:return "beak";
    case A_LFCLAW:return "left claw";
    case A_RFCLAW:return "right claw";
    case A_WING:return "wing bash";
    }
}

