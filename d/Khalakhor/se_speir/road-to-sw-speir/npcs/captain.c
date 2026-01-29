/*
 * Camp captain
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
    "Slightly older than most of the soldiers in the camp, "+
    "he has taken upon himself to lead them on this task. "+
    "He has patches of " + query_colors() + " on "+
    "his armor to indicate his clan allegiance. He is the captain "+
    "of the camp, and he seems the most dangerous warrior in it as well.\n";
  return _long;
}

void
create_khalakhor_human ()
{
  add_act("say I hope Fahlmar makes up his mind soon.");
  add_act("emote touches his chainmail, as if he is keeping something in "+
          "close to his chest.");
  adjs1 = ({ "tall", "intense", "magnetic", "wrinkled" });
  adjs2 = ({ "dark-haired", "dark-eyed", "scarred", "tight-jawed" });
  name   = "captain";


  equipment = ({
    WEPS_DIR + "captain-claymore",
    ARMS_DIR + "captain-chainmail",
    ARMS_DIR + "helmet",
    ARMS_DIR + "leggings",
    OBJS_DIR + "cpt-token",
    OBJS_DIR + "letter",
  });

  create_camp_warrior(LEVEL_CAPTAIN);
}
