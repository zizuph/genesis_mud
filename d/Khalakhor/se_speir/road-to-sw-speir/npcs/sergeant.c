/*
 * Camp sergeant
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
    "He is a older than the regular soldiers, carrying a spirit "+
    "of experience around him, although he is not an officer "+
    "ion this force. He has patches of " + query_colors() + " on "+
    "his armor to indicate his clan allegiance. He seems to be the "+
    "sergeant of the camp, in charge of a particular unit.\n";
  return _long;
}

void
create_khalakhor_human ()
{
  add_act("say I don't like the change of the direction of the wind!");
  add_act("emote knocks the pole of his weapon on the rocks as if "+
          "testing something.");
  adjs1 = ({ "tall", "grizzly", "heavy", "wrinkled" });
  adjs2 = ({ "dark-haired", "experienced", "bearded", "balding" });
  name   = "sergeant";


  equipment = ({
    WEPS_DIR + "jedwart",
    ARMS_DIR + "chainmail",
    ARMS_DIR + "helmet",
    ARMS_DIR + "leggings",
  });

  create_camp_warrior(LEVEL_SERGEANT);
}
