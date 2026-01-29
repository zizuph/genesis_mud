/* A shrew for newbies to kill by Teth Jan 97 */

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
   set_short("shrew");
   set_name("shrew");
   set_race_name("shrew");
   set_adj("little");
   set_long("This is a little shrew, that roots about, minding its own " +
      "business.\n");  

   LEFTOVER("tooth");
   set_m_in("skitters in");
   set_m_out("skitters");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 2+random(3));
   
   set_knight_prestige(0);
   set_alignment(0);

   set_random_move(50);
   set_restrain_path(TROOM);
   set_monster_home(TROOM + "forest5");
   
   set_hp(query_max_hp());
   
   set_act_time(4);
   add_act("emote scurries about.");
   add_act("emote roots about for grubs.");
   add_act("emote darts back and forth beneath your feet.");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,1000);
   add_prop(CONT_I_WEIGHT,500);
   
   set_attack_unarmed(A_BITE, 3, 2, W_IMPALE, 60, "piercing bite");
   set_attack_unarmed(A_CLAW, 2, 3, W_SLASH, 40, "small claw");
   
   set_hitloc_unarmed(H_HEAD, 1, 10, "head");
   set_hitloc_unarmed(H_BODY, 1, 80, "body");
   set_hitloc_unarmed(H_TAIL, 1, 10, "tail");
}

