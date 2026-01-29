/* A bear for newbies to kill by Teth Jan 97 */

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
   set_short("bear cub");
   set_name("cub");
   set_race_name("bear");
   set_adj("bear");
   add_name("bear");
   set_long("This bear cub looks lost, as if it is mother was no longer " +
      "around.\n");

   CUTLEFTOVER("paw");
   CUTLEFTOVER("paw");

   set_m_in("waddles in");
   set_m_out("waddles");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 6+random(8));
   
   set_knight_prestige(0);
   set_alignment(0);

   set_random_move(50);
   set_restrain_path(TROOM);
   set_monster_home(TROOM + "forest6");
   
   set_hp(query_max_hp());
   
   set_act_time(4);
   add_act("emote bellows for its mother.");
   add_act("emote climbs up a tree, then down again.");
   add_act("emote looks at you with playful eyes.");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,10000);
   add_prop(CONT_I_WEIGHT,10000);
   
   set_attack_unarmed(A_BITE, 3, 2, W_IMPALE, 60, "bite");
   set_attack_unarmed(A_CLAW, 7, 3, W_IMPALE, 40, "paw");
   
   set_hitloc_unarmed(H_HEAD, 2, 30, "head");
   set_hitloc_unarmed(H_BODY, 2, 40, "body");
   set_hitloc_unarmed(H_TAIL, 2, 30, "tail");
}


