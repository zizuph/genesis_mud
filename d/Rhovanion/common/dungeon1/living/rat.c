inherit "/std/monster";
inherit "/std/combat/unarmed";
#include <stdproperties.h>
#include <wa_types.h>
#include <macros.h>
#define A_BITE  0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_HEAD 0
#define H_BODY 1
#include <ss_types.h>
void
create_monster()
{
   int i;
   set_name("rat");
   add_name("rat");
   set_race_name("rat");
   set_long("This is a filthy brown rodent over a foot long with nasty, yellow teeth, sopping wet fur slicked back over its body, and yellow eyes that peer hungrily at you.  It reaks of disease and fecality. \n");
   set_gender(G_NEUTER);
   set_adj("filthy");
   set_adj("brown");
   set_stats(({ 10, 15, 15, 5, 15, 55 }));
   set_alignment(0);
   set_aggressive(1);
   set_hp(100);
   add_prop(CONT_I_WEIGHT, 7000);
   add_prop(CONT_I_HEIGHT, 100);
   add_prop(CONT_I_VOLUME, 6500);
   set_attack_unarmed(A_BITE, 15, 10, W_IMPALE, 75, "maw");
   set_attack_unarmed(A_LCLAW, 12, 8, W_SLASH, 10, "left paw");
   set_attack_unarmed(A_RCLAW, 12, 8, W_SLASH, 15, "right paw");
   set_hitloc_unarmed(H_HEAD, ({ 10, 15, 15, 10 }), 15, "head");
   set_hitloc_unarmed(H_BODY, ({  5,  9, 10, 10 }), 85, "body");
   set_act_time(5);
   add_act("emote scampers slowly from one place to another, knawing on filth as it goes.");
}
