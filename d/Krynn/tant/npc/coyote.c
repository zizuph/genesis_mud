/* A coyote for newbies to kill by Teth Jan 97 */

#include "../local.h"
#include <wa_types.h>
#include <macros.h>
inherit C_FILE
inherit "/std/act/action";
inherit "/std/act/domove";

#define A_BITE 0
#define A_MAUL 1

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

public void
create_creature()
{
   int i;

   set_gender(G_NEUTER);
   set_short("mangy coyote");
   set_name("coyote");
   set_race_name("coyote");
   set_adj("mangy");
   set_long("This coyote seems to be inflicted with mange.\n");

   LEFTOVER("tooth");
   CUTLEFTOVER("pelt");
   set_m_in("lopes in");
   set_m_out("lopes");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 1+random(20));
   
   set_knight_prestige(0);
   set_alignment(0);

   set_random_move(50);
   set_restrain_path(TROOM);
   set_monster_home(TROOM + "valley6");
   
   set_hp(query_max_hp());
   
   set_act_time(4);
   add_act("emote howls!");
   add_act("emote looks at you with a distrustful glance.");
   add_act("emote breathes in an odd manner.");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,5000);
   add_prop(CONT_I_WEIGHT,5000);
   
   set_attack_unarmed(A_BITE, 12, 4, W_IMPALE, 60, "painful bite");
   set_attack_unarmed(A_MAUL, 4, 8, W_IMPALE, 40, "maul");
   
   set_hitloc_unarmed(H_HEAD, 2, 20, "head");
   set_hitloc_unarmed(H_BODY, 2, 60, "body");
   set_hitloc_unarmed(H_TAIL, 2, 20, "tail");
}

