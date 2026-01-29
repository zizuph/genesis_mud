inherit "/d/Gondor/anorien/nimrais/quest/chimney.c";
#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include "dirdefs.h".

#define UP_ROOM    "chimney4"
#define DOWN_ROOM    "chimney2"

create_room()
{
  area = "White Mountains";
  where = "in a narrow chimney between two rock walls";
  extraline = "You are probably halfway up in the chimney. " +
    "It extends far up and down. It would probably be dangerous to fall down now. ";
  down_room = THIS_DIR + DOWN_ROOM;
  up_room = THIS_DIR + UP_ROOM;
  make_the_room();
}
