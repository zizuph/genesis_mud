/* an arctic eel souped up and made nice by Stevenson */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";

inherit C_FILE

create_creature()
{
   int i;
   
   set_name("eel");
   set_race_name("eel");
   set_short("giant ice eel");
   set_long(
      "You see a two meter long eel. It is white and very "
      + "slippery. Its bite is known to numb a person to the bone. "
      + "\n");
   set_adj("giant");
   add_adj("ice");
   
   for (i = 0; i < 6; i++)
   set_base_stat( i, 30 + random( 10, time() ) );
   
   set_alignment(-50);
   
   set_random_move(30);
   set_restrain_path(CAVE);
   set_hp(query_max_hp());
   set_monster_home(CAVE + "cavern1.c");
   
   add_act("emote brushes against your leg, numbing you with cold.\n");
   add_act("emote sends freezing shocks into the water.\n");
   add_act("@@dive");
   add_act("@@surface");
   add_prop(OBJ_I_HIDE,1);
   
   set_attack_unarmed(0, 20, 20, W_SLASH, 20, "squeeze");
   set_attack_unarmed(1, 20, 20, W_IMPALE, 20, "freeze");
   set_attack_unarmed(2, 30, 30, W_BLUDGEON, 80, "tail");
   
   set_hitloc_unarmed(0, 20, 80, "body");
   set_hitloc_unarmed(1, 20, 20, "head");
   
   set_aggressive(1);
   
   LEFTOVER("skin");
   LEFTOVER("fin");
   
   set_alarm(1.0,0.0,"set_m_in","slithers in.");
   set_alarm(1.0,0.0,"set_m_out","slithers");
}

string dive() {
   if (TO->query_prop(OBJ_I_HIDE)) return "";
   tell_room(E(TO),"The eel dives under the water.\n");
   TO->add_prop(OBJ_I_HIDE,1);
   return "";
}

string surface() {
   if (TO->query_prop(OBJ_I_HIDE)) {
      tell_room(E(TO),"A giant ice eel surfaces next to you.\n");
      TO->remove_prop(OBJ_I_HIDE);
   }
   return "";
}

void do_die(object killer)
{
   string *organs = 
   ( { "finger", "nose", "toe", "elbow" } );
   
   object organ;
   
   organ = clone_object("/std/leftover");
   organ->leftover_init( organs[ random(4) ], QRACE(killer) );
   organ->move(TO);
   
   set_race_name("eel floating on the water");
   ::do_die(killer);
}
