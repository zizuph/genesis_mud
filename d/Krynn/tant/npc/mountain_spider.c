/* A spider for newbies to kill by Teth Jan 97 */

#include "../local.h"
#include <wa_types.h>
#include <macros.h>
inherit C_FILE
inherit "/std/act/action";
inherit "/std/act/domove";

#define A_BITE 0

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2

public void
create_creature()
{
   int i;

   set_gender(G_NEUTER);
   set_short("mountain spider");
   set_name("spider");
   set_race_name("spider");
   set_adj("mountain");
   set_long("This is a little black mountain spider.\n"); 

   set_m_in("skitters in");
   set_m_out("skitters");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 1+random(2));
   
   set_knight_prestige(0);
   set_alignment(0);

   set_random_move(50);
   set_restrain_path(TROOM);
   set_monster_home(TROOM + "road15");
   
   set_hp(query_max_hp());
   
   set_act_time(4);
   add_act("emote skitters about.");
   add_act("emote pauses momentarily in its movements.");
   add_act("emote taps the ground with one leg.");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,1000);
   add_prop(CONT_I_WEIGHT,500);
   
   set_attack_unarmed(A_BITE, 1, 4, W_IMPALE, 100, "venomous bite");
   
   set_hitloc_unarmed(H_HEAD, 2, 20, "head");
   set_hitloc_unarmed(H_BODY, 2, 30, "body");
   set_hitloc_unarmed(H_LEGS, 2, 50, "legs");
}

