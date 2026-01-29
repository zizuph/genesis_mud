/* an sea monster souped up and made nice by Stevenson */

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
inherit "/std/act/action";
inherit "/std/act/attack";

inherit C_FILE

void init_living()
{
   ::init_living();
   TP->catch_msg("You feel very afraid at the sight of "
      + "a repulive seamonster staring at you hungrily.\n");
}

void
create_creature()
{
   int i;
   
   set_name("seamonster");
   set_race_name("seamonster");
   set_short("seamonster");
   set_long(
      "This horrid and repulsive creature has come up from the depths "
      + "of the deep for the purpose of exacting revenge "
      + "upon all who would disturb its sleep. "
      + "\n");
   
   for (i = 0; i < 6; i++)
   set_base_stat( i, 170 + random( 10, time() ) );
   
   set_alignment(-70);
   set_knight_prestige(70);
   
   
   add_act("emote screeches hideously.");
   add_act("emote spews vile, filthy water at you.");
   add_act("emote lunges at your throat.");
   add_act("@@dive");
   add_act("@@surface");
   add_prop(OBJ_I_HIDE,1);
   
   set_attack_unarmed(0, 20, 20, W_SLASH, 20, "teeth");
   set_attack_unarmed(1, 20, 20, W_IMPALE, 20, "claw");
   set_attack_unarmed(2, 30, 30, W_BLUDGEON, 80, "tail");
   
   set_hitloc_unarmed(0, 20, 80, "body");
   set_hitloc_unarmed(1, 20, 20, "head");
   
   set_aggressive(1);
   
   LEFTOVER("skin");
   LEFTOVER("fin");
   
}

string dive() {
   if (TO->query_prop(OBJ_I_HIDE)) return "";
   tell_room(E(TO),"The seamonster dives under the water.\n");
   TO->add_prop(OBJ_I_HIDE,1);
   return "";
}

string surface() {
   if (TO->query_prop(OBJ_I_HIDE)) {
      tell_room(E(TO),"A giant ice seamonster surfaces in front of you.\n");
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
   
   set_race_name("seamonster floating on the water");
   ::do_die(killer);
}
