inherit "/std/monster";
inherit "/std/combat/unarmed";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#define A_BITE  0
#define A_HORDE 0
#define H_MASS 0
#include <ss_types.h>
void
create_monster()
{
   int i;
   set_name("the spider horde");
   add_name("horde");
   set_living_name("bat swarm");
   set_race_name("spider horde");
   set_short("spider horde");
   set_long("This horde is comprised of hundreds of spiders ranging anywhere in size from an inch to a foot long!  It is crawling all over you and the cavern!\n");
   set_act_time(0);
   add_act("get orb");
   set_stats(({ 25, 50, 30, 20, 40, 150 }));
   set_gender(G_NEUTER);
   set_alignment(0);
   set_aggressive(1);
   set_hp(500);
   set_skill(SS_BLIND_COMBAT, 100);
   add_prop(CONT_I_WEIGHT, 15000);
   add_prop(CONT_I_HEIGHT, 100);
   add_prop(CONT_I_VOLUME, 22000);
   set_attack_unarmed(A_BITE, 100, 30, W_IMPALE, 35, "bite");
   set_attack_unarmed(A_HORDE, 75, 25, W_IMPALE, 65, "horde");
   set_hitloc_unarmed(H_MASS, ({ 100, 60, 20, 90 }), 100, "mass");
}
