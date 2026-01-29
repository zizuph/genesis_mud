/* A deer for newbies to kill by Teth Jan 97 */

#include "../local.h"
#include <wa_types.h>
#include <macros.h>
inherit C_FILE
inherit "/std/act/action";
inherit "/std/act/domove";

#define A_BUTT 0
#define A_HOOF 1

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

public void
create_creature()
{
   int i;

   set_gender(G_NEUTER);
   set_short("white-tailed deer");
   set_pshort("white-tailed deer");
   set_name("deer");
   set_pname("deer");
   set_race_name("deer");
   set_adj("white-tailed");
   set_long("This is a white-tailed deer that lives in the valley because " +
      "of the plentiful food.\n");

   LEFTOVER("horn");
   CUTLEFTOVER("hide");
   set_m_in("prances in");
   set_m_out("prances");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 10+random(6));
   
   set_knight_prestige(0);
   set_alignment(0);

   set_random_move(50);
   set_restrain_path(TROOM);
   set_monster_home(TROOM + "valley12");
   
   set_hp(query_max_hp());
   
   set_act_time(4);
   add_act("emote prances about, carefree.");
   add_act("emote searches here for some herbs to eat.");
   add_act("emote suddenly stands still, fully alert!");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,10000);
   add_prop(CONT_I_WEIGHT,10000);
   
   set_attack_unarmed(A_BUTT, 10, 5, W_IMPALE, 20, "horn");
   set_attack_unarmed(A_HOOF, 2, 7, W_IMPALE, 80, "hoof");
   
   set_hitloc_unarmed(H_HEAD, 2, 40, "head");
   set_hitloc_unarmed(H_BODY, 2, 50, "body");
   set_hitloc_unarmed(H_TAIL, 2, 10, "tail");
}



