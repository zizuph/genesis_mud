/* A rabbit for newbies to kill by Teth Jan 97 */

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
   set_short("fuzzy rabbit");
   set_name("rabbit");
   set_race_name("rabbit");
   set_adj("fuzzy");
   set_long("This is a harmless-looking fuzzy rabbit.\n");
 

   LEFTOVER("fang");
   CUTLEFTOVER("tail");
   set_m_in("bounces in");
   set_m_out("hops");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 4+random(2));
   
   set_knight_prestige(0);
   set_alignment(0);

   set_random_move(50);
   set_restrain_path(TROOM);
   set_monster_home(TROOM + "forest8");
   
   set_hp(query_max_hp());
   
   set_act_time(4);
   add_act("emote hops about the area.");
   add_act("emote sniffs around.");
   add_act("emote suddenly scampers around!");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,1200);
   add_prop(CONT_I_WEIGHT,1000);
   
   set_attack_unarmed(A_BITE, 3, 4, W_IMPALE, 60, "bite");
   set_attack_unarmed(A_CLAW, 4, 3, W_IMPALE, 40, "clawed paw");
   
   set_hitloc_unarmed(H_HEAD, 2, 30, "head");
   set_hitloc_unarmed(H_BODY, 2, 40, "body");
   set_hitloc_unarmed(H_TAIL, 2, 30, "tail");
}



