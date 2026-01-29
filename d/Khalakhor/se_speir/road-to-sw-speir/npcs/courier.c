/*
 * Camp courier
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
    "He seems to be young person in training, not yet acquiring a "+
    "stocky build. He has patches of " + query_colors() + " on "+
    "his armor to indicate his clan allegiance. He seems to be a "+
    "running messages and errands for the officers.\n";
  return _long;
}

void
create_khalakhor_human ()
{
  add_act("say I hope I'll be able to get a few hours of sleep now.");
  add_act("emote sways a little bit sideways from tiredness.");
  adjs1 = ({ "tall", "young", "wide-eyed", "springy" });
  adjs2 = ({ "dark-haired", "thin", "tired", "sleepy" });
  name   = "courier";


  equipment = ({
    WEPS_DIR + "dirk",
    ARMS_DIR + "chainmail",
    ARMS_DIR + "helmet",
  });

  create_camp_warrior(LEVEL_COURIER);
}
