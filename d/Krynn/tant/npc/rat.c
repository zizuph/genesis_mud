/* A rat for newbies to kill by Teth Jan 97 */

#include "../local.h"
#include <wa_types.h>
#include <macros.h>
inherit C_FILE
inherit "/std/act/action";
inherit "/std/act/domove";

#define A_BITE 0
#define A_CLAW 1

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

public void
create_creature()
{
   int i;

   set_gender(G_NEUTER);
   set_short("rat");
   set_name("rat");
   set_race_name("rat");
   set_adj("sewer");
   set_long("This is a sewer rat, known for its ferociousness.\n");

   LEFTOVER("tooth");
   set_m_in("languidly walks in");
   set_m_out("languidly walks");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 6+random(3));
   
   set_knight_prestige(0);
   set_alignment(0);

   set_random_move(50);
   set_restrain_path(TROOM);
   set_monster_home(TROOM + "sewer5");
   
   set_hp(query_max_hp());
   
   set_act_time(4);
   add_act("emote sniffs some raw sewage.");
   add_act("emote glares at you with hunger.");
   add_act("emote chews on something it found.");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,1000);
   add_prop(CONT_I_WEIGHT,1000);
   
   set_attack_unarmed(A_BITE, 10, 2, W_IMPALE, 70, "piercing bite");
   set_attack_unarmed(A_CLAW, 2, 5, W_SLASH, 30, "grey claw");
   
   set_hitloc_unarmed(H_HEAD, 1, 10, "head");
   set_hitloc_unarmed(H_BODY, 1, 80, "body");
   set_hitloc_unarmed(H_TAIL, 1, 10, "tail");
}




