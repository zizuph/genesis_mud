/* a snowbird
created for Icewall by Stevenson */

#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
inherit C_FILE
inherit "/std/act/domove";
inherit "/std/act/action";

create_creature() {
   int i;
   set_gender(G_NEUTER);
   set_short("snow bird");
   set_name("bird");
   set_race_name("bird");
   set_adj("snow");
   set_long("You see a very tiny bird. It is shivering from the cold.\n");
   
   set_alarm(1.0,0.0,"set_m_in","flies in.");
   set_alarm(1.0,0.0,"set_m_out","flies");
   
   for (i=0;i<6;i++)
   set_base_stat(i, 5+random(5));
   set_knight_prestige(-1);
   set_alignment(1);
   
   set_hp(query_max_hp());
   set_monster_home(ICE_FOREST+"forest_1");
   set_restrain_path(ICE_FOREST);
   set_random_move(30);
   
   set_act_time(1);
   add_act("emote digs around in the snow with its beak.");
   add_act("emote squawks.");
   add_act("flaps its wings.");
   add_act("emote chirps.");
   add_act("emote shivers.");
   
   add_prop(LIVE_I_NEVERKNOWN,1);
   add_prop(CONT_I_VOLUME,90);
   add_prop(CONT_I_WEIGHT,170);
   
   set_attack_unarmed(0, 5, 5, W_IMPALE, 100, "beak");
   set_hitloc_unarmed(0, 2, 100, "body");
}
