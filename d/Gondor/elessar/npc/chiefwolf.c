inherit "/std/creature";
inherit "/std/combat/unarmed";   /* This gets us standard unarmed routines */
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
#include "/d/Gondor/elessar/lib/evilkill.h"
#include <wa_types.h>
#include <ss_types.h>
/*
 * Define some attack and hitloc id's (only for our own benefit)
 */
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2

#define H_HEAD 0
#define H_BODY 1

int pack_size;

create_creature()
{
    set_name("wolf"); 
    set_race_name("wolf");
    set_short("white wolf");
    set_pshort("white wolves");
    set_adj(({"white", "ferocious" }));
    set_aggressive(1);
    set_attack_chance(100);
    set_random_move(16);
    set_long("This wolf seems larger than the others, and has a few more battle-scars\n"+
    "in its grey-white fur. Its red eyes are gleaming with evil, and it\n"+
    "looks hungrily at you.\n");

    /* str, con, dex, int, wis, dis
    */
    set_stats(({ 90, 45, 35, 20, 5, 95}));
    set_hp(1000);

    set_skill(SS_DEFENCE, 20);
    set_skill(SS_UNARM_COMBAT,72);
    set_skill(SS_SWIM, 80);

    set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 40, 20, W_SLASH,  30, "left paw");
    set_attack_unarmed(A_RCLAW, 40, 20, W_SLASH,  30, "right paw");
   
    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30 }), 80, "body");
  call_out("add_pack",5);
}


query_combat_file()
{
  return "/std/combat/cplain";
}

add_pack()
{
  int n;
  object wolf;
  this_object()->set_leader();
  while (n < pack_size + random(4)) {
    wolf = clone_object("/d/Gondor/elessar/npc/wolf");
    wolf->move(environment(this_object()));
    this_object()->team_join(wolf);
    n++;
    }
  return 1;
}

set_pack_size(int i)
{
  pack_size = i;
}

monster_ranwalk()
{
  if (query_attack()) return;
  else
  ::monster_ranwalk();
  return;
}

