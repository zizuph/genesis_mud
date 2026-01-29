inherit "/std/room";
inherit "/d/Genesis/lib/post";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void
create_room()
{
  set_short("The post office of Ciubori");
  set_long(break_string(
    "You're standing inside the post-office of Ciubori. The room has white walls, "+
    "roof and floor which makes it kind of boring. A clerk is sitting behid a "+
    "couter. "+get_std_use(),60));
  
  add_item("clerk","The clerk is poking his nose. You wonder if he finds anything "+
    "interesting.\n");
  add_exit(CIUBORI + "crystal/street2","east");

  add_prop(ROOM_I_INSIDE, 1);  /* This is a real room */
}

init()
{
  ::init();
  post_init();
}

leave_inv(ob,to)
{
  ::leave_inv(ob,to);
  post_leave_inv(ob,to);
}

void
mail_message(string new)
{
  write("\nThere is" + new + " mail for you in the post office of Ciubori!\n"+
        "(Norteast part of town at Crystal Street.)\n\n");
}
