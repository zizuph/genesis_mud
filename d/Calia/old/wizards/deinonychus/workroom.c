inherit "/std/workroom";
#include <stdproperties.h>

create_workroom()
{
  set_short("Deinonychus' workroom");
  set_long(break_string(
    "This is Deinonychus' workroom.\n", 70));
  add_exit("/d/Genesis/wiz/entrance", "news", 0);
  add_exit("/d/Genesis/wiz/domain", "domain", 0);
  add_exit("/d/Genesis/wiz/idea", "idea", 0);
  add_exit("/d/Genesis/wiz/post", "post", 0);
  add_exit("/d/Genesis/start/human/town/post", "mpost", 0);
  add_exit("/d/Genesis/wiz/flame", "flame", 0);
  add_exit("/d/Genesis/wiz/discuss", "discuss", 0);
  add_exit("/d/Genesis/wiz/lpc", "lpc", 0);
  add_exit("/d/Genesis/wiz/infotool", "tool", 0);
  add_exit("/d/Genesis/wiz/admin", "admin", 0);
  add_exit("/d/Calia/workroom", "meet", 0);
  add_exit("/d/Calia/tmp/glykron/palace/stairs", "stair", 0);
  add_exit("/d/Calia/tmp/glykron/palace/guild", "guild", 0);
 add_exit("/d/Calia/common/entrance", "common", 0);
}
void
init()
{
  if(this_player()->query_name() == "Deinonychus")
    this_player()->add_prop(LIVE_I_SEE_DARK, 10);
    ::init();
}
