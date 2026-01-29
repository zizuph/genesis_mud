/* A wari for newbies to kill by Teth Jan 97 */

#include "../local.h"
#include <wa_types.h>
#include <macros.h>
inherit C_FILE
inherit "/std/act/action";
inherit "/std/act/domove";

#define A_BITE 0
#define A_KICK 1

#define H_HEAD 0
#define H_BODY 1
#define H_WING 2

public void
create_creature()
{
   int i, j;

   set_gender(G_NEUTER);
   set_short("wari");
   set_name("wari");
   set_race_name("wari");
   set_adj("tall");
   set_long("This tall bird is a wari, a two meter tall flightless bird. " +
      "It is rather docile, but aggressive when attacked.\n");

   j = 2;
   add_leftover("/std/leftover", "wing", j, "", 0, 1);

   set_m_in("lurks in");
   set_m_out("lurks");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 10+random(2));
   
   set_knight_prestige(0);
   set_alignment(0);

   set_random_move(50);
   set_restrain_path(TROOM);
   set_monster_home(TROOM + "valley14");
   
   set_hp(query_max_hp());
   
   set_act_time(4);
   add_act("emote flaps its wings uselessly.");
   add_act("emote stretches out its neck.");
   add_act("emote scratches at the dirt with its claw.");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,40000);
   add_prop(CONT_I_WEIGHT,40000);
   
   set_attack_unarmed(A_BITE, 2, 2, W_IMPALE, 60, "blunt beak");
   set_attack_unarmed(A_KICK, 8, 3, W_BLUDGEON, 40, "powerful leg");
   
   set_hitloc_unarmed(H_HEAD, 2, 10, "head");
   set_hitloc_unarmed(H_BODY, 1, 80, "body");
   set_hitloc_unarmed(H_WING, 2, 10, "wing");
}

