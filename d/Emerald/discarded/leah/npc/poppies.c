inherit "/std/creature";
/*Wuz dun bi Karath*/
inherit "/std/combat/unarmed";
inherit "/std/act/domove";
inherit "/std/act/attack";
inherit "/std/act/action";

#include "/sys/wa_types.h"
#include "/sys/ss_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#define BS(xxx) break_string(xxx, 76)

#define ATT_SNARL     0
#define ATT_CHARM    1

#define HIT_MIDDLE     0
#define HIT_EDGE     1
#define HIT_ROOTS    2

void
create_creature()
{
   if (!IS_CLONE)
      return;
   set_name("poppies");
   set_race_name("flowers");
   set_short("field of poppies");
   set_gender(G_NEUTER);
   add_adj("enchanting");
   set_long(BS("These poppies seem to be swaying ryhthmically "+
         "yet not with the wind but an independent "+
         "action. You think you hear murmurs from them also.\n"));
   
   add_prop(CONT_I_WEIGHT, 250);   
   add_prop(CONT_I_VOLUME, 25000);   
   add_prop(LIVE_I_NEVERKNOWN, 1);  /* You'll never know it */
   add_prop(LIVE_I_NO_CORPSE, 1);
   
   set_stats(({ 10, 50, 20, 20, 20, 140}));
   set_hp(10000); /* Heal fully */
   
   
   set_attack_unarmed(ATT_SNARL, 15, 15, W_SLASH, 70, "snarl");
   set_attack_unarmed(ATT_CHARM, 20, 20, W_BLUDGEON, 30, "charm");
   
   set_hitloc_unarmed(HIT_MIDDLE, ({ 5, 5, 5, 5 }), 50, "middle");
   set_hitloc_unarmed(HIT_EDGE, ({ 10, 10, 10, 10 }), 20, "edge");
   set_hitloc_unarmed(HIT_ROOTS, ({ 7, 7, 7, 7 }), 30, "roots");
   
   set_act_time(2);
   add_act("kill elf");
   add_act("kill human");
   add_act("kill goblin");
   add_act("kill gnome");
   add_act("kill dwarf");
   add_act("kill hobbit");
   add_act("emote sway and rustle.");
}
