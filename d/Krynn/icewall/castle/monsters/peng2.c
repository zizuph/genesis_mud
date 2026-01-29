/* A penguin
created for Icewall by Stevenson */

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
inherit C_FILE
inherit "/std/act/action";

create_creature() {
   int i;
   set_gender(G_FEMALE);
   set_short("penguin");
   set_name("penguin");
   set_race_name("penguin");
   set_long("This poor penguin is hopelessly lost.\n");
   
   LEFTOVER("foot");
   LEFTOVER("fat");
   set_alarm(1.0,0.0,"set_m_in","waddles in.");
   set_alarm(1.0,0.0,"set_m_out","waddles");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 15+random(5));
   
   set_skill(SS_DEFENCE, 15);
   set_knight_prestige(-1);
   set_alignment(1);
   
   set_hp(query_max_hp());
   
   set_act_time(1);
   add_act("emote looks up at you pathetically.");
   add_act("emote squawks.");
   add_act("emote flaps her wings.");
   add_act("emote shivers.");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,250);
   add_prop(CONT_I_WEIGHT,500);
   
   set_attack_unarmed(0, 10, 10, W_IMPALE, 60, "beak");
   set_attack_unarmed(1, 10, 10, W_BLUDGEON, 40, "wing");
   
   set_hitloc_unarmed(0, 5, 30, "head");
   set_hitloc_unarmed(1, 5, 30, "wing");
   set_hitloc_unarmed(2, 7, 40, "body");
}
