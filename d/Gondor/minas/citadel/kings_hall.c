inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

object denethor;

create_room()
{
  set_short("The Kings Hall in the White Tower");
  set_long("You are in a great hall, lit by deep windows in the wide aisles\n"+
    "at either side, beyond the rows of tall pillars that uphold the roof.\n"+
    "No dust or storied webs, nor any things of woven stuff or of wood can\n"+
    "be seen in the long, solemn hall, but between the pillars are placed a\n"+
    "silent company of tall statues carved of cold stone. At the far west\n"+
    "end of the hall, upon a dais of many steps, sits a high throne. At the\n"+
    "foot of the dais, upon the lowest step, is a stone chair, black and\n"+
    "unadorned. Behind the throne, carved upon the wall and set with gems,\n"+
    "is an image of a tree in flower.\n");
  add_item(({"pillar","pillars"}),
    "Rows of tall pillars stand on either side of the floor, upholding the\n"+
    "roof. Monoliths of black marble, they rise to great capitals carved in\n"+
    "many strange figures of beasts and leaves; and far above in shadow the\n"+
    "wide vaulting gleams with dull gold, inset with flowing traceries of\n"+
    "many colours. Between the pillars stands a silent company of tall\n"+
    "images graven in cold stone.\n");
  add_item(({"statues","statue","images"}),
    "You are looking upon an avenue of statues of kings long dead. After the\n"+
    "death of a king, a new statue was carved in his image and placed here.\n"+
    "All the statues look extremely old to you, and by studying the plaque\n"+
    "of one of them, you find out that the last King of Gondor was Earnur,\n"+
    "who was killed by the Witch-king almost a thousand years ago.\n");
  add_item("dais","At the west end of the hall is a dais of many steps, made of white marble.\n"+
    "Upon the dais is set a high throne, and at the foot of the dais is\n"+
    "a black stone chair.\n");
  add_item("throne","@@exa_throne");
  add_item("chair","@@exa_chair");
  add_item("tree","Carved into the wall behind the throne, and set with gems\n"+
    "is an image of a tree in flower. It is the White Tree of Gondor.\n");
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_NO_ATTACK,"@@try_attack");
  clone_object(MINAS_DIR+"obj/hall_door_in")->move(this_object());
  add_stuff();
}

exa_throne()
{
  string str;
  str = "Upon the dais sits a high throne under a canopy of marble shaped\n"+
    "like a crowned helm, and behind it, carved upon the wall and set\n"+
    "with gems, is an image of a tree in flower.\n";
  if (present("elessar",this_object())) str = str+"King Elessar Telcontar is sitting in the throne.\n";
  else str = str+"The throne is empty.\n";
  return str;
}

exa_chair()
{
  string str;
  str = "The stone chair is black and unadorned.\n";
  if (present("denethor",this_object())) str = str+"Lord Denethor, Steward of Gondor is sitting upon it.\n";
  else str = str+"The chair is empty.\n";
  return str;
}

add_stuff()
{
  if (!denethor) {
    denethor = clone_object(MINAS_DIR+"npc/denethor");
    denethor->move(TO);
  }
}

reset_room()
{
  add_stuff();
}

