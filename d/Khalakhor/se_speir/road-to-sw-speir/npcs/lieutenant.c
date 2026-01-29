/*
 * Camp lieutenant
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
    "Around the same age as most of the soldiers in the camp, "+
    "he has proven himself to be an authority "+
    "in this force. He has patches of " + query_colors() + " on "+
    "his armor to indicate his clan allegiance. He seems to be the "+
    "lieutenant of his clan in the force, reporting directly to "+
    "the captian.\n";
  return _long;
}

void
create_khalakhor_human ()
{
  add_act("say I wonder when the next meeting with the captain is going "+
          "to be.");
  add_act("emote twiddles his lieutenant token between the fingers.");
  adjs1 = ({ "tall", "middle-aged", "distinguished", "light-skinned" });
  adjs2 = ({ "dark-haired", "captivating", "square-faced", "lithe" });
  name   = "lieutenant";


  equipment = ({
    WEPS_DIR + "claymore",
    ARMS_DIR + "chainmail",
    ARMS_DIR + "helmet",
    ARMS_DIR + "leggings",
    OBJS_DIR + "lt-token",
  });

  create_camp_warrior(LEVEL_LIEUTENANT);
}
