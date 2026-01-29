/* Navarre July 3rd 2006, added awareness to the dragon, people 
 * with low sneak skill could sneak bounce it
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
inherit "/d/Krynn/std/dragon_base";
inherit "/std/act/attack";
inherit "/std/act/action";
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>

void
create_dragon_npc()
{
    ::create_dragon_npc();
    set_age("aged");
    add_name("emerald");
    set_gender(G_FEMALE);
    set_colour("green");
    set_long("Before you stands a huge and ancient winged " +
      "serpent, a fearsome creature of legends, a green " +
      "dragon! Eighty feet in length from snout to tail tip, " +
      "darkly beautiful and exceedingly graceful, it is far from " +
      "the hulking and ponderous monster you had visualised " +
      "from fairy tales. Most frightening of all are its " +
      "eyes, orbs of golden green slashed by vertical pupils " +
      "and bright with a cold, alien intelligence.\n");

    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_SEE_DARK, 1);
    set_skill(SS_BLIND_COMBAT, 100);
    set_skill(SS_AWARENESS, 100);
    set_act_time(4);
    add_act("emote twirls its long slender tail in the air " +
      "in a slow, sinuous motion.");
    add_act("emote begins to prowl around you like a wolf " +
      "closing in on its prey.");
    add_act("emote flexes its enormous batlike wings in the " +
      "cool air.");
    add_act("emote clears its throat, emitting as it does a " +
      "small puff of foul smelling gas.");
    add_act("emote stares intensely at you.");

    set_cact_time(5);
    add_cact("emote looks at you with cold hatred in its eyes.");
    add_cact("emote opens its terrible maw and lets out a " +
      "terrifying roar!");
    add_cact("grin");

}

