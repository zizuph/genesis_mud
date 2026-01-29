inherit "/d/Gondor/common/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

object wagon;

make_the_room()
{
  set_short("Inside a horse carriage");
  set_long("@@inside_long");
  add_prop(ROOM_I_NO_CLEANUP,1);
  add_item("view","@@exa_view");
  add_item(({"horse","horses"}),"@@exa_horses");
}

set_wagonob(object obj)
{
  wagon = obj;
}

query_allinv()
{
  return all_inventory(this_object());
}

init()
{
  ::init();
    add_action("leave_wagon","jump");
    add_action("leave_wagon","leave");
    add_action("leave_wagon","out");
    add_action("leave_wagon","exit");
    add_action("check_time","time");
}

inside_long()
{
  string long_descf,
         env_short;
  long_descf = "You are inside a wooden horse carriage, currently ";
  if (wagon->query_leavable()) long_descf = long_descf+"standing still in ";
  else long_descf=long_descf+"rambling along ";
  env_short = environment(wagon)->short();
  env_short = lower_case(env_short[0..0]) + env_short[1..strlen(env_short)];
  long_descf += env_short+". ";
  long_descf = long_descf+"There's an old, skinny human driving the carriage, "+
    "controlling the "+wagon->query_horses()+" horses that are pulling. ";
  if (wagon->query_leavable()) long_descf = long_descf+"You may 'jump out' of the carriage here, as it is not moving now.\n";
  else long_descf = long_descf+"It could be dangerous to jump out of the carriage now, as it is moving.\n";
  return (break_string(long_descf,70));
}

leave_wagon(string str)
{
  if (!str) { write(capitalize(query_verb())+" what?\n"); return 1; }
  if (query_verb() == "leave" && (str != "wagon" && str != "carriage"))
    { write("Leave what? The wagon?\n"); return 1; }
  if (query_verb() == "out" && str != "of wagon" && str != "of carriage") {
    write("Out of what? The wagon?\n"); return 1; }
  if (query_verb() == "jump" && (str != "out" && str != "off" &&
    str != "off wagon" && str != "out of wagon")) {
    write("Jump where? Off?\n"); return 1; }
  if (query_verb() == "exit" && str != "wagon" && str != "carriage") {
    write("Exit what? The wagon?\n"); return 1; }
  if (wagon->query_leavable()||this_player()->query_wiz_level())
    {
if (!wagon) {
      write("You jump out the emergency exit of the wagon.\n");
        say(QCTNAME(this_player())+" jumps out of the wagon.\n");
        this_player()->move_living("M","/d/Gondor/rohan/edoras/path2");
        return 1;
        }
      write("You jump out of the carriage.\n");
      say(QCTNAME(this_player())+" jumps out of the carriage.\n",this_player());
      tell_room(environment(wagon),QCNAME(this_player())+
          " suddenly comes jumping out of the horse carriage!\n",this_player());
      wagon->remove_living();
      this_player()->move_living("M",environment(wagon));
      return 1;
    }
  write("No, you don't dare to do that - the wagon is moving, and you could get hurt!\n");
  return 1;
}

exa_view()
{
  return "Outside the wagon you see:\n"+
    environment(wagon)->long();
}

exa_horses()
{
  if (wagon->query_horses() == 0) return "There are no horses pulling the wagon now.\n";
  else if (wagon->query_horses() == 1) 
    return "There is only one horse pulling the wagon. It does not seem to have\n"+
      "a problem doing the job, being a strong and fine horse, but the pace\n"+
      "is not exactly great.\n";
  else return "There are "+wagon->query_horses()+" horses pulling the wagon now.\n"+
    "All look healthy and strong, and they pull the wagon at a fine pace.\n";
}



