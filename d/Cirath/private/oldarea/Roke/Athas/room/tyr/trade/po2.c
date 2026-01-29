

inherit "/std/room.c";
inherit "/d/Genesis/lib/post";

#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>
object shadow;

#define SHADOW STAND_DIR + "dirty_shadow"

void
create_room()
{
   set_short("Hobbit Post Office.");
   set_long(
            "A rough wet room stands here. A faint trickling sound "+
            "can be heard coming from somewhere above. This is where "+
            "hobbits come to peacefully read their mail. A small "+
            "sign is hanging from a beam in the ceiling. Just behind "+
            "a very small desk is a petite hobbit, with blue hair.\n");
   set_noshow_obvious(1);
   add_item(({"hobbit", "petite hobbit", "bobby-sue"}), 
            "She look fairly pretty for a hobbit. This is the mail "+
            "clerk that handles your mail, so be nice to her.\n");
   add_item("sign", "Why not read it, eh tough guy?\n");
   add_item("ceiling", "It covers your head.\n");
   add_item(({"beam", "ceiling beam"}),
         "It seems to be holding up the ceiling, why don't you try "+
            "and pull it?\n");
   add_cmd_item("beam", "pull", "Like the complete and total idiot "+
                "that you are, you attempt to pull the ceiling down.\n"
              + "\n"
              + "Luckily you are either too weak or too stupid, or "+
                "even both, to pull the beam down.\n");
   add_cmd_item("sign", "read", "The sign reads:\n"
              + "You have all of your regular post office commands "+
                "here. Use 'from', 'read', and 'mail'.\n");
   add_prop(ROOM_I_INSIDE,1);
   add_exit(HOBGLD_DIR+"blah", "blooh");
}

init()
{
    ::init();
    post_init();
    add_action("t_pull", "pull");
}

int
do_read(string str)
{
    notify_fail("Read what?\n");
    if (str != "beam")
        return 0;
  if(!this_player()->query_dirty_shadow()) {
    if (this_player()->query_stat(2) < 25 + random(100)) {

    write("Like the complete and total idiot you are, you attempt "+
          "to pull the ceilling down on your head.\n"
        + "Suddenly, you realize where the dripping noise is coming "+
          "from!\n"
         + "Water splashes down on you from above!\n");
      call_out("give", 0, this_player());
      return 1;
    }

  }

return 0;
}

give(object ob) {
  shadow = clone_object(SHADOW);
  shadow->shadow_me(ob);
  shadow->destruct_dirty_shadow();
}

leave_inv(ob,to)
{
    ::leave_inv(ob,to);
    post_leave_inv(ob,to);
}
void
mail_message(string new)
{
 write("There is" + new + " stuff for you in the Hobbit "+
 "Post Office.\n\n");
}

