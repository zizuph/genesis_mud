inherit "/std/workroom";
#include "/d/Terel/common/terel_defs.h"


create_workroom()
{
  set_short("dusts home");
  set_long(break_string("This is dusts workroom. As many know, dust " +
	"hates to write long room descriptions - so, to make it " +
	"short, this room looks SO AMAZING that it throws you out " +
	"or your socks (old chinese saying ;--)\n",70));
  add_exit("/d/Genesis/wiz/post", "post", 0);
  add_exit(MANSION + "porcia/riddle_room","porcia",0);
  add_exit(DUSTDIR + "door_room","door",0);
  add_exit(MANSION + "crt/well","well",0);
  add_exit(MANSION + "crt/level4","dive",0);
}

