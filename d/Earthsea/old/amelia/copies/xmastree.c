#include "/d/Roke/common/defs.h"
#include <macros.h>

inherit "/std/object";

create_object()
{
  set_long("A very nice looking xmas tree. You can dance around it.\n"+
	   "There is a golden star on top of it.\n");
   set_short("xmas tree");
   set_name("tree");
   set_adj("xmas", "evergreen");
  add_item("star","It is very beautiful.\n");
  add_prop(OBJ_I_NO_GET,"You greedy little sucker!\n");
}
init()
{
  ::init();

    add_action("dance","dance");
  }
dance(string s)
{
  if(s!="around tree") return 0;

  say(QCTNAME(TP)+" dances around the xmas tree.\n");
  write("You dance around the xmas tree.\n");

return 1;
}

