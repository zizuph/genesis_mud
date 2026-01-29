inherit "/d/Emerald/ctower/room/ctower_base";
 
#include <stdproperties.h>
#include <macros.h>

public void
create_maze()
{
}
 
public nomask void
create_ctower_room()
{
  int i;
  string *dirs = ({ "north", "south", "east", "west", "northeast", 
                    "northwest", "southeast", "southwest" });
  string *desc_arr;

  set_short("Mirror maze");
 
  set_long("All surfaces of this room are mirrored, "+
      "making reflections stretching away to infinity in all "+
      "directions. There is a soft glow emanating from the very walls "+
      "themselves, giving you plenty of light.\n");

  for_each(dirs, &add_exit("", ,"@@bump@@"));
 
  desc_arr = ({ "wall", "floor", "ceiling", "mirror" });
  for (i = 0; i < (sizeof(dirs) / 2); i++)
  {
    desc_arr += ({ dirs[i] + " wall", dirs[i] + " mirror" });
  }

  add_item(desc_arr, "You see infinite relections of yourself in all " +
      "directions. It is extremely disorienting and impossible to " +
      "distinguish any difference in the different directions.\n");

  add_prop(ROOM_I_LIGHT, 3);
 
  set_noshow_obvious(1);

  create_maze();
}
 
int bump()
{
  write("You bump into the wall.\n");
  say(QCTNAME(this_player()) + " bumps into the wall.\n");
  return 1;
}
 
int sure()
{
  write("You encounter slight resistance but make it through.\n");
  return 0;
}

void add_maze_exit(string room, string exit_cmd)
{
  remove_exit(exit_cmd);
  add_exit(room, exit_cmd, "@@sure@@");
}
