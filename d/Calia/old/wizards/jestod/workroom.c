inherit "/std/workroom";

create_workroom()
{
  set_short("Jestod's workroom");
  set_long("This is Jestod's crystal dome.  White light shines in from the\n"
    + "spires above, the rays focusing on a central desk.\n");
  add_exit("/d/Genesis/wiz/entrance", "news", "@@wiz_check");
  add_exit("/d/Genesis/wiz/domain", "domain", "@@wiz_check");
  add_exit("/d/Genesis/wiz/post", "post", "@@wiz_check");
  add_exit("/d/Genesis/start/human/town/post", "mpost", "@@wiz_check");
  add_exit("/d/Genesis/wiz/flame", "flame", "@@wiz_check");
  add_exit("/d/Genesis/wiz/discuss", "discuss", "@@wiz_check");
  add_exit("/d/Genesis/wiz/lpc", "lpc", "@@wiz_check");
  add_exit("/d/Genesis/wiz/infotool", "tool", "@@wiz_check");
  add_exit("/d/Genesis/wiz/admin", "admin", "@@wiz_check");
  add_exit("/d/Dville/workroom", "meet", "@@wiz_check");
  add_exit("/d/Dville/glykron/palace/guild", "guild", "@@wiz_check");
 add_exit("/d/Dville/common/entrance", "common", "@@wiz_check");
add_exit("/d/Dville/glykron/workroom", "lord", "@@wiz_check");
}

init()
{
  ::init();
  add_action("do_time", "time");
}

int do_time()
  {
    int tm;
    tm = time();
    write("CET: " + ctime(tm) + "\nEST: " + ctime(tm - 21600) + "\n");
  return 1;
  }

int wiz_check()
{
    if (this_player()->query_wiz_level())
        return 0;
    write("You find it impossible to leave.\n");
    return 1;
}
