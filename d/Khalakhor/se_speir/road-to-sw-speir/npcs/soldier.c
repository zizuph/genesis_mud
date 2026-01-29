/*
 * Regular soldier
 * Tapakah, 09/2021
 */

#include "macros.h"

#include "../defs.h"

inherit BASE_WARRIOR;

string
my_long ()
{
  string _long =
    "This man is a representative of the clan " + query_clan() + ". "+
    "He seems to be well-built and trained for battle, although not "+
    "too eager for one. He has patches of " + query_colors() + " on "+
    "his armor to indicate his clan allegiance. He looks like a "+
    "seasoned soldier.\n";
  return _long;
}

void
create_khalakhor_human ()
{
  add_act("say What is your business here, stranger?");
  adjs1 = ({ "tall", "stocky", "lanky", "broad-shouldered" });
  adjs2 = ({ "dark-haired", "flat-nosed", "dark-eyed", "thin-lipped" });
  name   = "soldier";

  equipment = ({
    WEPS_DIR + "backsword",
    ARMS_DIR + "chainmail",
    ARMS_DIR + "helmet",
    ARMS_DIR + "leggings",
    ARMS_DIR + "shield"
  });
  
  create_camp_warrior(LEVEL_SOLDIER);
  
}
