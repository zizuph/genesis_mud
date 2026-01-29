/* A raccoon for newbies to kill by Teth Jan 97 */

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
   set_short("masked raccoon");
   set_name("raccoon");
   set_race_name("raccoon");
   set_adj("masked");
   set_long("This masked bandit is a raccoon.\n");

   LEFTOVER("tooth");
   set_m_in("waddles in");
   set_m_out("waddles");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 6+random(2));
   
   set_knight_prestige(0);
   set_alignment(0);

   set_random_move(50);
   set_restrain_path(TROOM);
   set_monster_home(TROOM + "road16");
   
   set_hp(query_max_hp());
   
   set_act_time(4);
   add_act("emote makes a gurgling sound in its throat.");
   add_act("emote seems to rub its two front paws together.");
   add_act("emote looks about here and there for some food.");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,1000);
   add_prop(CONT_I_WEIGHT,500);
   
   set_attack_unarmed(A_BITE, 5, 4, W_IMPALE, 60, "vicious bite");
   set_attack_unarmed(A_CLAW, 5, 3, W_IMPALE, 40, "paw");
   
   set_hitloc_unarmed(H_HEAD, 3, 30, "head");
   set_hitloc_unarmed(H_BODY, 3, 40, "body");
   set_hitloc_unarmed(H_TAIL, 3, 30, "tail");
}



