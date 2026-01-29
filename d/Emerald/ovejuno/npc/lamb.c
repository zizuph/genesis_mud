/* Ckrik June 1998
 * Modified by Marisol (08/21/98)
 */

inherit "/d/Emerald/marisol/ovejuno/npcs/generic_sheep.c";

#include "wa_types.h"
#include "ss_types.h"
#include "macros.h"
#include "/sys/stdproperties.h"

int sheep_type = random(2);

string* adj1 = ({"frisky", "young", "adolescent"});
string* adj2 = ({"spirited", "wily", "playful"});

create_sheep()
{
  set_gender(G_NEUTER);
  set_adj(adj1[sheep_type]);
  add_adj(adj2[sheep_type]);
  set_act_time(50);

  set_long("A " + adj1[sheep_type] + " " + adj2[sheep_type] +
	   " lamb. It is playing with its siblings " +
	   "on the green pastures under the watchful eyes of its elders.\n");

  set_stats( ({10, 10, 10, 7, 7, 25}));
  set_skill(SS_DEFENSE, 10);
  set_skill(SS_UNARM_COMBAT, 10);

  add_act("emote jumps playfully on the green grass.");
  add_act("emote runs in circles around you.");
}
