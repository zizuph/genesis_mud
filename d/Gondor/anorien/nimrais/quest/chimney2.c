inherit "/d/Gondor/anorien/nimrais/quest/chimney.c";
#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include "dirdefs.h".

#define UP_ROOM    "chimney3"
#define DOWN_ROOM    "chimney1"

create_room()
{
  area = "White Mountains";
  where = "in a narrow chimney between two rock walls";
  extraline = "You are a few yards above the bottom of the chimney, and it looks as if it extends far up. ";
  down_room = THIS_DIR + DOWN_ROOM;
  up_room = THIS_DIR + UP_ROOM;
  make_the_room();
}
