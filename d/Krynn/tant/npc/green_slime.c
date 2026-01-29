/* A green slime for newbies to kill by Teth Jan 97 */

#include "../local.h"
#include <wa_types.h>
#include <macros.h>
inherit C_FILE
inherit "/std/act/action";
inherit "/std/act/domove";

#define A_SLME 0

#define H_BODY 0

public void
create_creature()
{
   int i;

   set_gender(G_NEUTER);
   set_short("green slime");
   set_name("slime");
   set_race_name("slime");
   set_adj("green");
   set_long("This is a hideous green slime.\n");

   set_m_in("oozes in");
   set_m_out("oozes");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 10+random(2));
   
   set_knight_prestige(0);
   set_alignment(0);

   set_random_move(50);
   set_restrain_path(TROOM);
   set_monster_home(TROOM + "sewer20");
   
   set_hp(query_max_hp());
   
   set_act_time(4);
   add_act("emote blurbles.");
   add_act("emote gathers itself up into a mucousy ball.");
   add_act("emote oozes around.");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,1000);
   add_prop(CONT_I_WEIGHT,1000);
   
   set_attack_unarmed(A_SLME, 2, 15, W_BLUDGEON, 100, "painful slime");
   
   set_hitloc_unarmed(H_BODY, 5, 100, "body mass");
}



