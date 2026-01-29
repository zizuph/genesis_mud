#include "../../ctower.h"

inherit FINSTD;
inherit "/d/Emerald/ctower/ctower_bits";

#include <stdproperties.h>
 
private void reset_image(object ob);
 
void
create_fin()
{
  set_long("You seem to be inside a mirror. This room seems very unreal...\n");
  add_exit(CTOWER_ROOM_FIN + "mirror", "south", "@@check_south@@");
  add_exit(CTOWER_ROOM_FIN + "central2", "north", "@@check_north@@");
  add_prop(ROOM_M_NO_MAGIC, 1);
  add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
  add_prop(ROOM_I_NO_TELEPORT, 1);
}

int
block(string str)
{
  write("Somehow you are unable to do that!\n");
  return 1;
}
 
void
init()
{
  ::init();

  if (interactive(this_player())) 
  {
    add_action(block, "wield");
    add_action(block, "wear");
    add_action(block, "unwield");
    add_action(block, "remove");
    add_action(block, "drop");
#if 0
    add_action(block, "bash");
    add_action(block, "ckick");
    add_action(block, "savage");
    add_action(block, "brawl");
#endif
  }
}
 
int
check_north()
{
  if (present("ctower_image"))
  {
    write("Your image blocks your way!\n");
    return 1;
  }

  return 0;
}
 
int
check_south()
{
  if (this_player()->query_prop(LIVE_I_KILLED_IMAGE)) 
  {
    write("Something prevents you from turning back!\n");
    return 1;
  }

  return 0;
}
 
private void
reset_image(object player)
{
  object image;

  while (image = present(player->query_real_name() + "_image"))
  {
    image->remove_object();
  }
  
  setuid();
  seteuid(getuid());

  image = clone_object(CTOWER_NPC + "image");
  image->clone_player(player);
  image->move(this_object(), 1);
}
 
void
enter_inv(object ob, object from)
{
  ::enter_inv(ob, from);

  if (!interactive(ob)) 
  {
    return;
  }

  if (get_ctower_bits(ob) > 4)
  {
    return;
  }

  if (!ob->query_prop(LIVE_I_KILLED_IMAGE))
  {
    reset_image(ob);
  }
}
 
void
leave_inv(object ob, object to)
{
  object image;

  ::leave_inv(ob, to);

  if (!interactive(ob)) 
  {
    return;
  }

  while (image = present(ob->query_real_name() + "_image"))
  {
    image->remove_object();
  }
}
