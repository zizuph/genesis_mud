// Private meeting room for Avenir.
//   -Cirion May 31, 1996

inherit "/std/room";
#include "/d/Avenir/common/common.h"

#define BOARD  "/d/Avenir/private/board"

void create_room()
{
  set_short("twilight cavern");
  set_long(break_string("Glimmering like a million dazzling stars, tiny beads of water "
       +"glisten on the rough walls around. Petrified stalagtites made from "
       +"hardened minerals and some jade-coloured stone jut upwards all "
       +"about the cavern. The air is humid and hot, and it feels like there "
       +"is a great weight pressing down from overhead.\nThere is no way out.\n", 55));
  add_item(({"stalagtites","stalagtites"}),"They are long, having formes over "
       +"the aeons.\n");

  if(file_size(BOARD + ".c") && !catch((BOARD))->teledensanka())
     (BOARD)->move(TO);
}

int query_prevent_snoop()
{
  return 1;
}
