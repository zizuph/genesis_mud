/* Ckrik June 1998
 */

inherit "/d/Earthsea/ckrik/marisol/generic_goat.c";

#include "wa_types.h"
#include "ss_types.h"
#include "macros.h"
#include "/sys/stdproperties.h"

int goat_type = random(2);

string* adj1 = ({"idle", "old", "adolescent"});
string* adj2 = ({"spirited", "wily", "unruly"});

create_goat()
{
  set_gender(G_MALE);
  set_adj(adj1[goat_type]);
  add_adj(adj2[goat_type]);
  set_act_time(50);

  set_long("An " + adj1[goat_type] + " " + adj2[goat_type] +
	   " male goat. He is munching " +
	   "on a bite of grass he just put in his mouth.\n");

  set_stats( ({10, 10, 10, 7, 7, 25}));
  set_skill(SS_DEFENSE, 10);
  set_skill(SS_UNARM_COMBAT, 10);

  add_act("emote chews some grass.");
  add_act("emote grazes on the pasture.");
}
