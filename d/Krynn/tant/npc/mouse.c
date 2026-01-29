/* A mouse for newbies to kill by Teth Jan 97 */

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
   set_short("forest mouse");
   set_pshort("forest mice");
   set_name("mouse");
   set_pname("mice");
   set_race_name("mouse");
   set_adj("forest");
   set_long("This is a forest mouse, shy and demure.\n");

   LEFTOVER("tooth");
   set_m_in("scurries in");
   set_m_out("scurries");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 1+random(2));
   
   set_knight_prestige(0);
   set_alignment(0);

   set_random_move(50);
   set_restrain_path(TROOM);
   set_monster_home(TROOM + "forest2");
   
   set_hp(query_max_hp());
   
   set_act_time(4);
   add_act("emote squeaks!");
   add_act("emote rustles about, looking for food.");
   add_act("emote searches for some seeds.");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,200);
   add_prop(CONT_I_WEIGHT,200);
   
   set_attack_unarmed(A_BITE, 1, 1, W_IMPALE, 70, "pitiful bite");
   set_attack_unarmed(A_CLAW, 1, 1, W_SLASH, 30, "little claw");
   
   set_hitloc_unarmed(H_HEAD, 1, 30, "head");
   set_hitloc_unarmed(H_BODY, 1, 40, "body");
   set_hitloc_unarmed(H_TAIL, 1, 30, "tail");
}




