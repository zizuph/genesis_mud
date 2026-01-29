/*
 * Camp standard-bearer
 * Tapakah, 10/2021
 */

#include "macros.h"

#include "../defs.h"

inherit BASE_WARRIOR;

string
my_long ()
{
  string _long =
    "This man is a representative of the clan " + query_clan() + ". "+
    "He is a bit younger than the regular soldiers, but "+
    "radiates the energy and the authority of a future "+
    "commander. He has patches of " + query_colors() + " on "+
    "his armor to indicate his clan allegiance. He seems to be the "+
    "standard bearer of the camp, also helping the lieutenants.\n";
  return _long;
}

void
create_khalakhor_human ()
{
  add_act("say Our colors shall fly high and proud!");
  add_act("emote looks around the camp eagerly.");
  adjs1 = ({ "tall", "strong", "determined", "thick-armed" });
  adjs2 = ({ "dark-haired", "bright-eyed", "eager", "energetic" });
  name   = "standard bearer";


  equipment = ({
    WEPS_DIR + "backsword",
    ARMS_DIR + "chainmail",
    ARMS_DIR + "helmet",
    ARMS_DIR + "leggings",
  });

  create_camp_warrior(LEVEL_STANDARD_BEARER);
}
