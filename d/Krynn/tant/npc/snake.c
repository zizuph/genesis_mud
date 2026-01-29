/* A snake for newbies to kill by Teth Jan 97 
 * Changed the 'skin' leftover to the snake skin object
 * Morgul Mages can use.
 * Arman - Aug 2019
 */
  

#include "../local.h"
#include <wa_types.h>
#include <macros.h>
inherit C_FILE
inherit "/std/act/action";
inherit "/std/act/domove";

#define A_BITE 0
#define A_PRCE 1

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

public void
create_creature()
{
   int i;

   set_gender(G_NEUTER);
   set_short("green snake");
   set_name("snake");
   set_race_name("snake");
   set_adj("green");
   set_long("This green snake looks relatively harmless.\n");

   LEFTOVER("fang");
   LEFTOVER("fang");
   add_leftover("/d/Gondor/common/npc/snake_skin", "snake skin", 1, 0, 0, 0);
   set_m_in("slithers in");
   set_m_out("slithers");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 3+random(5));
   
   set_knight_prestige(0);
   set_alignment(0);

   /* Disabled to more widely use this snake outside of TROOM

   set_random_move(50);
   set_restrain_path(TROOM);
   set_monster_home(TROOM + "road4");
   */
   
   set_hp(query_max_hp());
   
   set_act_time(4);
   add_act("emote hisses dangerously.");
   add_act("emote wraps itself into a coil.");
   add_act("emote flicks its tongue in and out.");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,1000);
   add_prop(CONT_I_WEIGHT,500);
   
   set_attack_unarmed(A_BITE, 3, 4, W_IMPALE, 60, "pitiful bite");
   set_attack_unarmed(A_PRCE, 4, 3, W_IMPALE, 40, "dull fangs");
   
   set_hitloc_unarmed(H_HEAD, 2, 10, "head");
   set_hitloc_unarmed(H_BODY, 2, 80, "body");
   set_hitloc_unarmed(H_TAIL, 2, 10, "tail");
}



