/* Ckrik 1998
 * Modified by Marisol (08/21/98)
 */

inherit "/d/Emerald/marisol/ovejuno/npcs/generic_sheep.c";

#include "wa_types.h"
#include "ss_types.h"
#include "macros.h"
#include "/sys/stdproperties.h"

int sheep_type = random(2);

string* adj1 = ({"gentle", "silent", "calm"});
string* adj2 = ({"young", "juvenile", "old"});

create_sheep()
{
  set_gender(G_FEMALE);
  set_adj(adj1[sheep_type]);
  add_adj(adj2[sheep_type]);

  set_long("A " + adj1[sheep_type] + " " + adj2[sheep_type] +
        " ewe. She is grazing placidly "+
	   "on the pastures, unconcern of you or anything else.\n");

  set_stats( ({10, 10, 10, 7, 7, 25}));
  set_skill(SS_DEFENSE, 10);
  set_skill(SS_UNARM_COMBAT, 10);

  set_act_time(50);

  add_act("emote chews some grass.");
  add_act("emote grazes on the pasture.");
}
