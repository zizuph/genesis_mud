#include "defs.h"
inherit "/d/Earthsea/guilds/roke/std/apprentice";

void create_roke_apprentice()
{
  set_level(1);
  set_random_move(30);
  set_restrain_path(({THWIL+"h", THWIL+"t", THWIL+"a",
		      ROKE_BEACH}));
}
