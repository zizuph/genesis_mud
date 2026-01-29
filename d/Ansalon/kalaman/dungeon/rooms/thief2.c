/*
 * Thief Hideout Drapery Room 
 * 
 * Lunatari of Krynn
 * 2008-02-10
 */
#include "local.h"

inherit DUNGEON_IN;

string get_drapery_desc();
int check_drapery();

create_dungeon_room()
{
   set_short("A small alcove");
   set_long("This is a small alcove in the otherwise not so very large cave. " +
      "In the eastern wall a small altar has been carved out of the rock. A " +
      "wooden beam across the room from north to south holds a long cloth " +
      "drapery. A few chests and coffers stand against the south wall.\n");

   add_item(({"cloth", "curtain", "drapery"}), get_drapery_desc);
   add_item(({"coffer", "coffers", "chest", "chests" }),
     "A few coffers and chests stand against the south wall, they are all " +
     "opened and totally empty of items except a few rocks.\n");
   add_item(({"altar","eastern wall", "wall"}), 
     "The altar that has been carved out of the rock seems to be a dedication " +
     "to the thief god of Hiddukel. The altar is a bares a small resemblance of " +
     "a face, two small rubies has been inserted as eyes and some smaller black " +
     "onyxes has been used for teeth. Ears and nose has just been carved out of " +
     "the rock itself. A small dentation in the forehead of the face seems to " +
     "indicate that something was once attached to it.\n");
   add_item(({"onyx", "onyxes", "teeth", "tooth" }), 
     "These are prestine black onyxes that have been used as teeth in the altar.\n");
   add_item(({"rubies", "ruby", "eyes", "eye" }),
     "These are prestine red rubies that have been used as eyes for the altar.\n");
   add_item(({"forehead", "indentation"}),
     "It looks like something was once attached to the forehead of the alter.\n");

   add_exit("thief1", "west", check_drapery, 5);
}

string
get_drapery_desc()
{
  string text;

  switch (DMASTER->query_status(S_TDRAPERY))
  {
    case 1:
      text = "The drapery seems to have been moved all the way to the " +
        "left.";
    break;
    default:
      text = "A long piece of rugged cloth hangs from a small wooden " +
        "pole on the west wall. It conceals this room from the ohter.";
  }

  return text + "\n";
}

int
check_drapery()
{
  if(!DMASTER->query_status(S_TDRAPERY)) 
  {
    write("You quickly move the drapery to the side and step through " +
     "to the other room.\n");
    tell_room(ENV(TP), QCTNAME(TP) + " gently moves the drapery aside.\n", TP);

    return 0;
  }

  return 0;
}

