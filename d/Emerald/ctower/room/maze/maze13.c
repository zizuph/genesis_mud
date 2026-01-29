#include "../../ctower.h" 

inherit MAZESTD;

#include <macros.h>
#include <cmdparse.h>
#include <tasks.h>

static int exit_open;
 
void disrupt();

void
create_maze()
{
  set_long("All surfaces of this room are mirrored, "+
      "making reflections stretching away to infinity in all "+
      "directions. There is a soft glow eminating from the very "+
      "walls themselves, giving you plenty of light.\n" +
      "There is a small but rather conspicuous hole in the " +
      "wall to the east.\n");

  add_item(({ "hole", "small hole", "conspicuous hole",
      "small conspicuous hole" }), "The hole is about 6cm deep "+
      "and 2cm wide.\n@@wand_desc@@");

  add_maze_exit(CTOWER_ROOM_MAZE + "maze18", "south");

  remove_exit("east");
  add_exit(CTOWER_ROOM_MAZE + "maze22", "east", "@@mirror_open@@");
}

int query_exit_open()
{
  return exit_open;
}

object wand_in_hole()
{
  return present("wand_in_hole");
}

int mirror_open()
{
  if (exit_open && wand_in_hole())
  {
    return sure();
  }

  return bump();
}

string wand_desc()
{
  if (wand_in_hole())
  {
    return "There is a crystal wand in it.\n";
  }

  return "";
}

int insert(string str)
{
  object *what;

  if (!strlen(str))
  {
    return 0;
  }

  if (!parse_command(str, this_player(), "%i 'in' / 'into' [the] [small] " +
      "[conspicuous] 'hole' / 'wall' / 'mirror'", what))
  {
    return 0;
  }
  
  if (!sizeof(what = NORMAL_ACCESS(what, "is_wand", this_object())))
  {
    notify_fail("Put what into the hole?\n");
    return 0;
  }

  if (wand_in_hole())
  {
    write("There is already a wand in it.\n");
    return 1;
  }

  what[0]->set_no_show();
  what[0]->add_name("wand_in_hole");
  what[0]->move(this_object(), 1);

  add_item(({ "wand", "crystal wand", "wand in hole" }),
      "A crystal wand, the head of which is protruding from a small " +
      "hole in the east wall.\n");
      
  write("You slide the wand into the hole.\n");
  set_alarm(2.0, 0.0, disrupt);
  return 1;
}

int is_wand(object ob)
{
  return (ob && ob->id("phase_quest_wand"));
}

void disrupt()
{
  object *who, room;

  if (!wand_in_hole())
  {
    return;
  }

  if (room = find_object(CTOWER_ROOM_MAZE + "maze22"))
  {
    who = filter(all_inventory(room), interactive);
    filter(who, &->resolve_task(TASK_ROUTINE, 
        ({ TS_INT, SS_AWARENESS })))->catch_msg("You notice a " +
        "tiny ripple radiate out through the west mirror.\n");    
  }

  who = filter(all_inventory(this_object()), interactive);
  filter(who, &->resolve_task(TASK_ROUTINE, 
      ({ TS_INT, SS_AWARENESS })))->catch_msg("You notice a " +
      "tiny ripple radiate out through the east mirror.\n");

  exit_open = 1;
}  

int remove(string str)
{
  object wand;

  if (!(wand = wand_in_hole()) ||
      !parse_command(str, ({ }), "[the] [crystal] 'wand' 'from' " +
      "[the] [small] [conspicuous] 'hole' / 'wall' / 'mirror'"))
  {
    return 0;
  }

  write("You remove the wand from the hole.\n");

  wand->unset_no_show();
  wand->set_no_show_composite(0);
  wand->remove_name("wand_in_hole");
  wand->move(this_player(), 1);

  exit_open = 0;

  remove_item("wand");
  
  return 1;
}
  
void init()
{
  ::init();

  if (!wand_in_hole)
  {
    exit_open = 0;
  }

  add_action(insert, "insert");
  add_action(insert, "put");
  add_action(remove, "remove");
  add_action(remove, "get");
}

