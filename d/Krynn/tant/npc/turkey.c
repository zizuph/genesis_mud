/* A wild turkey for newbies to kill by Teth Jan 97 */

#include "../local.h"
#include <wa_types.h>
#include <macros.h>
inherit C_FILE
inherit "/std/act/action";
inherit "/std/act/domove";

#define A_PECK 0
#define A_CLAW 1

#define H_HEAD 0
#define H_BODY 1
#define H_TAIL 2

public void
create_creature()
{
   int i;

   set_gender(G_NEUTER);
   set_short("wild turkey");
   set_name("turkey");
   set_race_name("turkey");
   set_adj("wild");
   set_long("This wild turkey roams about searching for food.\n");

   set_m_in("stalks in");
   set_m_out("stalks");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 4+random(2));
   
   set_knight_prestige(0);
   set_alignment(0);

   set_random_move(50);
   set_restrain_path(TROOM);
   set_monster_home(TROOM + "forest1");
   
   set_hp(query_max_hp());
   
   set_act_time(4);
   add_act("emote goes GOBBLE! GOBBLE! GOBBLE!");
   add_act("emote roots about for grubs.");
   add_act("emote cocks its head and looks up at you.");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,4500);
   add_prop(CONT_I_WEIGHT,4500);
   
   set_attack_unarmed(A_PECK, 3, 4, W_IMPALE, 60, "beak");
   set_attack_unarmed(A_CLAW, 4, 3, W_IMPALE, 40, "claw");
   
   set_hitloc_unarmed(H_HEAD, 2, 40, "head");
   set_hitloc_unarmed(H_BODY, 2, 40, "body");
   set_hitloc_unarmed(H_TAIL, 2, 20, "tail");

   LEFTOVER("feather");
   LEFTOVER("feather");
   LEFTOVER("feather");
}

