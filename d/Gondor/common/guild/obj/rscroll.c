#pragma save_binary

inherit "/std/object";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#define DIR      "/d/Gondor/common/guild/"

create_object()
{
  set_name("scroll");
  add_name("ranger-scroll");
  add_name("ranger_scroll");
  set_short("scroll of the Gondorian Rangers");
  set_long("This scroll was given to you as an introduction to your new guild,\n"+
	   "the Gondorian Rangers Guild. There's a lot of text on it, which you\n"+
	   "may read.\n");
  add_prop(OBJ_I_VALUE,0);
  add_prop(OBJ_I_WEIGHT,10);
  add_prop(OBJ_I_VOLUME,10);
  add_prop(OBJ_I_NO_DROP,"@@do_destruct");
}

init()
{
  add_action("read_scroll","read");
}

read_scroll(string str)
{
  if (!str)
    {
      write("Read what?\n");
      return 1;
    }
  if (str=="scroll" || str == "text" || str == "text on scroll")
    {
         cat(DIR+"txt/rscroll.txt");
      return 1;
    }
  return 0;
}

do_destruct()
{
  call_out("destruct_me",2);
  return 0;
}

destruct_me()
{
  object room;
  if (living(room = environment()))
    room = environment(room);
  tell_room(room,"The scroll suddenly catches fire, and burns to dust in a flash!\n");
  remove_object();
}











