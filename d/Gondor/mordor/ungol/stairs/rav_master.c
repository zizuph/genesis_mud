inherit "/std/object";

#include <macros.h>
#include "/d/Gondor/defs.h"

#define CAVES ({ (STAIRS_DIR + "hole1"),\
                 (STAIRS_DIR + "hole2"),\
                 (STAIRS_DIR + "hole3"),\
                 (STAIRS_DIR + "hole4"),\
                 (STAIRS_DIR + "hole5"),\
                 (STAIRS_DIR + "hole6"),\
                 (STAIRS_DIR + "hole7"),\
                 (STAIRS_DIR + "hole8"),\
              })

int  this_hole = -1;

void create_object()
{
    if(IS_CLONE)
        return;

    this_hole = random(sizeof(CAVES));
  enable_reset();
}

string query_hole()
{
    if(this_hole < 0)
        this_hole = random(sizeof(CAVES));
    return CAVES[this_hole];
}

void reset_object()
{
    this_hole = random(sizeof(CAVES));
}

string * query_holes()
{
    return CAVES;
}
