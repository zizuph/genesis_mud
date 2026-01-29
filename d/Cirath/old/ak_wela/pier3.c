inherit "/d/Cirath/ak_wela/inherit/pier";
#include "/d/Cirath/common/defs.h"

void
create_room()
{
    ::create_room();
    set_long(query_long() + "\n");
    add_exit(AK_WELA_DIR + "brdwlk3", "west", 0, 2 /* crowds */);
}
