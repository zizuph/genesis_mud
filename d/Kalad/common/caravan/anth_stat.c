inherit "/std/object";
#include "default.h"

void
create_object()
{
    set_name("statue");
    set_adj("grand");
    set_adj("obsidian");
    set_short("grand obsidian statue");
    set_long("As you gaze upon this mighty statue, you feel yourself "+
      "become very small and humble. Before you stands the statue of "+
      "a treacherous conniving overgod. He towers over you like a "+
      "giant over an ant, "+
      "dark and cloaked in many robes. In the hood, two gleaming silver "+
      "slits stare down at you. Around his neck, you notice a medallion "+
      "on a chain that is circular with sun rays shooting out. Clutched "+
      "in one of his gloved hands is a massive, deadly looking scythe. "+
      "The other hand is balled into a fist, raised above his head, "+
      "looking ready to strike down any foe with an unearthly power. "+
      "The longer you stare at this statue, the more real it seems. "+
      "There is a silver plaque at the base of this awesome statue.\n");

    add_item(({ "plaque", "silver plaque" }), "It gleams brightly. On "+
      "it, you see red, readable runes engraved.\n");
    add_cmd_item(({ "plaque", "silver plaque" }), "read", "This statue "+
      "is created in the honor of Lord Antharanos Darksun, the God "+
      "of Greed, Immorality and Deceit, and the one to bring life into "+
      "this great domain when it was dying. Without him, there would be "+
      "no Kalad.\n");

    add_prop(OBJ_M_NO_GET, "You don't dare even touch this statue.\n");
}
