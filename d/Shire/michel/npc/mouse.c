 
inherit "/std/creature";
inherit "/std/act/action";
inherit "/std/act/domove";
inherit "/std/combat/unarmed";
 
#include "/sys/ss_types.h"
#include "/sys/wa_types.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#include "/sys/language.h"
#include "/d/Shire/common/defs.h"
 
#define DESC (({"small","grey","field","furry","swift"}))
 
create_creature()
{
   int rnd;
   rnd = random(5);
   if (!IS_CLONE)
   return;
   set_name("mouse");
   set_pname("mice");
   set_short(DESC[rnd] + " mouse");
   set_pshort(DESC[rnd] + " mice");
   set_living_name("mouse");
   set_race_name("rodent");
   set_gender(G_NEUTER);
   set_long("This is a small field mouse. Its is furry and grey. \n"
    + "These mice are are the biggest peasant enemies as they eat \n"
    + "too much crops in fields and granaries. It is small but \n"
    + "looks very swift and dexterous. \n");
   set_adj(DESC[rnd]);
   add_prop(LIVE_I_NEVERKNOWN,1);
   set_stats(({3,9,5,3,3,5}));
   set_alignment(-10);
   set_random_move(20);
   set_restrain_path(MICH_DIR);
 
   set_attack_unarmed(0,5,5,W_IMPALE,50,"jaws");
   set_attack_unarmed(0,5,5,W_SLASH,25,"left claw");
   set_attack_unarmed(0,5,5,W_SLASH,25,"right claw");
   set_hitloc_unarmed(0,({5,5,5,5}),30,"head");
   set_hitloc_unarmed(0,({5,5,5,5}),70,"body");
 
   add_prop(CONT_I_WEIGHT,100);
   add_prop(CONT_I_VOLUME,150);
 
}
 
query_knight_prestige() {return 10;}
