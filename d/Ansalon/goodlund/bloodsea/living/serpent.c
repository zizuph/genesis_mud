
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/goodlund/bloodsea/local.h"
inherit AC_FILE
inherit "/d/Calia/std/sea_creature";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

inherit "/std/act/domove"; /* Include this if you want the creature to move */
inherit "/std/act/action"; /* Include this if you want your creature to act */
inherit "/std/act/attack";

string *gAdj1 = ({"long","fanged","hungry","lithe",
  "old","blue-green","black"});
int sX = random(100);

#ifndef ONE_OF
#define ONE_OF(x)  (x[random(sizeof(x))])
#endif

#define FLESH   "/d/Ansalon/goodlund/bloodsea/obj/serpent_flesh"

void
create_creature()
{
    int i;

    set_name("serpent");
    set_adj(ONE_OF(gAdj1)); 
    set_short(query_adj() + " sea serpent");
    set_race_name("serpent");
    set_adj("sea");
    set_long("Before you is a scourge of the Bloodsea, a sea serpent! " +
       "Quick and deadly, this creature is infamous for pulling sailors " +
       "from their ships and ripping them to shreads with their razor " +
       "sharp teeth.\n");

    set_stats(({100 +sX, 160 + sX, 110 + sX, 50 + sX, sX, 160}));

    set_hp(query_max_hp());

    set_skill(SS_DEFENCE, 80);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_SWIM, 100);

    set_knight_prestige(100);

    set_alignment(-100);

    set_attack_unarmed(0,55,50,W_IMPALE,80,"bite");
    set_attack_unarmed(1,60,30,W_BLUDGEON,20,"tail");


    set_hitloc_unarmed(0,40,30,"head");
    set_hitloc_unarmed(1,30,50,"torso");
    set_hitloc_unarmed(2,20,10,"tail");
    set_hitloc_unarmed(3,10,10,"soft underbelly");

    add_prop(NPC_I_NO_LOOKS, 1); 
    add_prop(LIVE_I_NEVERKNOWN, 1); 

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(CONT_I_VOLUME,     220000);
    add_prop(CONT_I_WEIGHT,     500000);

    int flesh_num = 1 + random(3);
    add_leftover(FLESH, "luminous flesh", flesh_num, "", 0, 0);

    set_act_time(4);
    add_act("emote slaps its tail in the water furiously.");

    add_act("emote dives under the water, then surfaces right in front of you!");
    add_act("emote stares intensely at you, its eyes full of hate.");

    set_cact_time(5);
    add_cact("emote looks at you with cold hatred in its eyes.");
    add_cact("emote opens its terrible maw and lets out a " +
      "terrifying roar!");
    add_cact("grin");

}

