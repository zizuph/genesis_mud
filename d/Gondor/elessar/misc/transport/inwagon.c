/* Inside of the wagon running between Minas Tirith and Edoras */
inherit "/std/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
object wagon;

create_room()
{
  set_short("Inside a horse carriage");
  set_long("@@inside_long");
  add_prop(ROOM_I_INSIDE,0);
}

init()
{
  ::init();
    wagon = find_object("tour_wagon");
  add_action("leave_wagon","jump");
}

inside_long()
{
  string long_descf;
  long_descf = "You are inside a wooden horse carriage, driving in "+environment(wagon)->short()+". ";
  long_descf = long_descf + "In front of the wagon you can see "+wagon->query_horses()+" pulling. ";
  long_descf = long_descf+"A skinny old human is driving the carriage. ";
  if (wagon->query_leavable()) long_descf=long_descf+"You can jump out of the wagon safely, as it is not moving now.\n";
  else long_descf=long_descf+"It could be dangerous jumping out of the carriage now, as it is moving.\n";
  return (break_string(long_descf,70));
}

leave_wagon(string str) {
  wagon = find_object("tour_wagon");
  if (str!="out" && str!="out of wagon" && str!="out of carriage" && str!="out of horse carriage") return 0;
  if (wagon->query_leavable())
    {
      write("You jump out of the carriage.\n");
      say(QCTNAME(this_player())+" jumps out of the carriage.\n",this_player());
      tell_room(environment(wagon),QCNAME(this_player())+" comes jumping out of the carriage.\n");
      this_player()->move(environment(wagon));
      wagon->remove_living();
      return 1;
    }
  write("No, you don't dare to do that - the wagon is moving!\n");
  return 1;
}
