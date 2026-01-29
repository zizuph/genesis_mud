inherit "/d/Gondor/common/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#define TP this_player()
#define TO this_object()
#define BS(xxx) break_string(xxx,70)

int windowopen;

create_room()
{
  set_short("The hallway in the second floor of a house in Minas Tirith");
  set_long("@@describe");
  add_prop(ROOM_I_INSIDE,1);
  add_prop(ROOM_I_LIGHT,"@@test_time");
  add_exit("/d/Gondor/minas/houses/peentryhall","down",0,0);
  add_exit("/d/Gondor/minas/houses/pebedroom1","north",0,0);
  add_exit("/d/Gondor/minas/houses/pebedroom2","west",0,0);
  add_item(({"staircase","stairs","stair"}),
    "The spiral staircase of stone leads down to the first floor.\n");
  add_item("window","@@exa_window");
  windowopen = 1;
}

exa_window()
{
  string s1;
  if (windowopen) s1 = "open";
  else s1 = "closed";
  return "The window is very small and narrow. Through it you see the front yard\n"+
    "outside the house. The window is "+s1+".\n";
}

describe()
{
  string longstr;
  longstr = "You are in the hallway in the second floor of the house. "+
    "There's a doorway leading north into the masters bedroom, and "+
    "another leading west into the ladys bedroom. A spiral staircase "+
    "leads down to the first floor. ";
  if (tod()=="night" || tod()=="early morning")
    longstr= longstr+"Now as it is "+tod()+", the house is quiet and dark. ";
  if (tod()=="morning" || tod()=="evening")
    longstr =longstr+"Now in the "+tod()+" you hear people in the house. ";
  if (tod()=="noon")
    longstr = longstr+"It is noon, and the house is quiet. ";
  longstr = longstr+"To the south is a little window.\n";
  return BS(longstr);
}

test_time()
{
  if (tod()=="night" || tod()=="early morning") return 0;
  return 1;
}

init()
{
  ::init();
  add_action("close_window","close");
  add_action("open_window","open");
  add_action("enter_window","enter");
  add_action("enter_window","exit");
  add_action("enter_window","jump");
  add_action("enter_window","leave");
  add_action("enter_window","climb");
}

enter_window(string str)
{
    string race;
  if (!str) return 0;
  if (str == "through window" || str == "window" || str == "out through window"
      || str == "through the window" || str == "through the open window"
      || str == "out window" || str == "out the window"
      || str == "through open window" || str == "out through the open window") {
    if (windowopen) {
      if ((race = TP->query_race()) == "hobbit" || race == "gnome") {
        if (query_outside()) {
          write("There is already someone just outside the window! If you tried to exit\n"+
            "through the window now, you would push "+query_outside()->query_objective()+" down!\n");
          say(QCTNAME(TP)+" is about to exit through the open window, when "+TP->query_noun()+
            "\ndiscovers there is someone there already!\n",TP);
          tell_room("/d/Gondor/minas/houses/peyard",
	  "You see "+QNAME(TP)+" tried to climb out through the open window, but\n"+
          "someone was in "+TP->query_possessive()+" way!\n");
          return 1;
          }
        if (TP->query_fight() && present(TP->query_fight())) {
          write("You can't climb out through the window when you're in a fight!\n");
          return 1;
          }
        write("You climb out through the open window.\n");
        say(QCTNAME(TP)+" climbs out through the open window.\n",TP);
        tell_room("/d/Gondor/minas/houses/peyard",QCNAME(TP)+" comes climbing out through the open window on\n"+
          "the second floor of the house.\n");
        TP->move("/d/Gondor/minas/houses/peyard");
        ("/d/Gondor/minas/houses/peyard")->set_outside_window(TP);
        TP->init_command("look");
        return 1;
        }
      write("You try to squeeze yourself out through the open window, but quickly\n"+
        "realize that you are too big!\n");
      say(QCTNAME(TP)+" tries to squeeze "+TP->query_objective()+"self out through\n"+
        "the open window, but realizes "+TP->query_noun()+" is too big.\n",TP);
      tell_room("/d/Gondor/minas/houses/peyard",QCNAME(TP)+" tries to climb out through the open window\n"+
        "on the second floor, but is too big!\n");
      return 1;
      }
    write("The window is shut, you'll have to open it first.\n");
    return 1;
    }
  return 0;
}

open_window(string str)
{
  if (!str) {
    write("Open what?\n");
    return 1;
    }
  if (str == "window") {
    if (windowopen) {
      write("The window is already open!\n");
      return 1;
      }
    write("You open the little window. A gust of fresh air hits you.\n");
    say(QCTNAME(TP)+" opens the little window.\n",TP);
    tell_room("/d/Gondor/minas/houses/peyard","Someone opens the right-most window up on the second floor from the inside.\n");
    windowopen = 1;
    return 1;
    }
  return 0;
}

close_window(string str)
{
  if (!str) {
    write("Close what?\n");
    return 1;
    }
  if (str == "window" || str == "little window" || str == "the window") {
    if (windowopen) {
      write("You close the little window.\n");
      say(QCTNAME(TP)+" closes the little window.\n");
      tell_room("/d/Gondor/minas/houses/peyard","Someone closes the right-most window up on the second floor from the inside.\n");
      windowopen = 0;
      return 1;
      }
    write("The window is already closed!\n");
    return 1;
    }
  return 0;
}

query_outside()
{
  return ("/d/Gondor/minas/houses/peyard")->query_by_window();
}

