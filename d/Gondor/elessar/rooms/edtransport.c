/* The transport-office of Edoras, where the carriage is cloned and
 * loaded into the game. By Elessar for Genesis, March '92.
 */

inherit "/std/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
object wagon;

create_room()
{
  set_short("The transport stable of Edoras");
  set_long("This is the stable from where the horse carriages are sent out\n"+
           "to Minas Tirith. It is a new business, and still only in a test-phase\n"+
	   "so expect bugs, and report them!\n"+
            "You may start the wagon by 'start' if it's not running.\n"+
          "There's a pile of hay in the corner of the room.\n");
  add_prop(ROOM_I_INSIDE,1);
  add_item(({"hay","pile of hay"}),"Searching through the hay you find that there's an open hatch below\n"+
"the hay, through which you can go down to the basement!\n");
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_exit("/d/Gondor/rohan/edoras/path2","east",0);
  seteuid(getuid(this_object()));
  wagon_reset();
}

clean_up()
{
  return 1;
}

init()
{
  ::init();
    add_action("start_wagon","start");
    add_action("go_down","down");
    add_action("go_down","d");
}

start_wagon()
{
  if (wagon)
    {
      if (!present(wagon,this_object()))
	{
	  write("The wagon is already out.\n");
	  return 1;
	}
      write("You pay the driver, and he attaches two horses to the carriage.\n");
      write("Then he drives the wagon out into the street.\n");
      say(QCTNAME(this_player())+" pays the driver, and the driver attaches two\n"+
	  "horses to the carriage, and drives it out into the street.\n",this_player());
      seteuid(getuid(this_object()));
      write_file("/d/Gondor/elessar/log/wagons",this_player()->query_name()+" started the wagon in Edoras, "+ctime(time())+".\n");
      wagon->set_horses(2);
      wagon->set_tour_loop(1);
      wagon->move("/d/Gondor/rohan/edoras/path2");
      wagon->start(20);
      return 1;
    }
  else wagon_reset();
  start_wagon();
}

wagon_reset()
{
  wagon = clone_object("/d/Gondor/elessar/obj/edwagon");
  wagon->move(this_object());
  seteuid(getuid(this_object()));
  write_file("/d/Gondor/elessar/log/wagons","RESET of the wagon in Edoras, "+ctime(time())+".\n");
  wagon->set_leavable(1);
  return 1;
}

reset_room()
{
  if (!wagon) wagon_reset();
}

go_down()
{
  write("You climb down through the hatch, and find yourself in the basement.\n");
  this_player()->move_living("down through a hatch","/d/Gondor/rohan/edoras/basement");
  return 1;
}

