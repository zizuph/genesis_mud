inherit "/d/Gondor/anorien/nimrais/quest/chimney.c";
#include "/d/Gondor/defs.h"
#include <ss_types.h>
#include "dirdefs.h".

#define UP_ROOM    "plateau1"
#define DOWN_ROOM    "chimney3"

create_room()
{
  area = "White Mountains";
  where = "in a narrow chimney between two rock walls";
  extraline = "You are at the top of the chimney, and it looks as if it extends far down. " +
    "The western wall of the chimney ends rather abruptly not far above your head, " +
    "whereas the eastern wall continues to rise towards the sky. ";
  up_room = THIS_DIR + UP_ROOM;
  down_room = THIS_DIR + DOWN_ROOM;
  make_the_room();
}
