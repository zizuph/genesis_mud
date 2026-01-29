inherit "/d/Gondor/common/room";
#include "/sys/macros.h"
#include "/sys/stdproperties.h"
#define BS(xxxx)  break_string(xxxx,75)
#define TP        this_player()
#define TO        this_object()

object by_open_window;

create_room()
{
  set_short("A yard outside a private house in Minas Tirith");
  set_long("@@describe");
  add_prop(ROOM_I_INSIDE,0);
  add_exit("/d/Gondor/minas/n1crc4","south","@@test_by_window",0);
  add_item(({"windows","window"}),"@@exa_windows");
  add_item(({"iron bars","bars"}),BS("They are most probably put there to prevent thieves from just entering the house.\n"));
  add_item("house","@@exa_house");
  add_item("words","The words above the door read:\n  Mansion of Hir Pelendur.\n");
  add_dogs();
  clone_object("/d/Gondor/minas/houses/pedoorout")->move(TO);
}

describe()
{
  string longstr;
  longstr = "You are in the front yard of a fashionable building in the "+
     "Wainwrights' Street in Minas Tirith. The building has two floors, "+
     "with a door in front, and a window on the left side of the door on "+
     "the first floor, and two windows on the second floor. ";
  if (tod()=="night" || tod()=="early morning")
     longstr = longstr + "Now in the night-time, the windows of the building "+
     "are dark; the people in the house are probably sleeping. ";
  if (tod()=="morning")
     longstr = longstr + "You see candles lit in the windows on the second "+
     "floor. The people in the mansion are probably awake now. ";
  if (tod()=="noon" || tod()=="afternoon")
     longstr = longstr + "The windows of the house are dark, as the inhabitants "+
     "might be at work. ";
  if (tod()=="evening")
     longstr = longstr + "There are lights in all windows. You guess that the "+
     "people in the house are at home now. ";
  longstr = longstr+"There are some words written above the door. To the "+
     "south is the exit from the yard leading out in the Wainwrights' Street "+
     "again.";
  return BS(longstr+"\n");
}

exa_windows()
{
  string wstr;
  wstr = "The windows are all closed except the rightmost window on the "+
    "second floor, and the window on the first floor even has iron bars; "+
    "the people of Minas Tirith knows the threat of thievery. ";
  if (tod()=="night" || tod()=="early morning" || tod()=="noon" || tod()=="afternoon")
     wstr = wstr+"The windows are all dark. ";
  if (tod()=="morning" || tod()=="evening")
     wstr = wstr+"There are candles burning in all three windows. ";
  wstr = wstr+"You guess that the windows of the second floor are about "+
  "3 meters above the ground.\n";
  return BS(wstr);
}

exa_house()
{
  return BS("The house looks fashionable, made of white marble-like stone. The "+
  "house has two floors, on the first floor is the entrance door and one "+
  "window. On the second floor, about 3 meters above the ground there are "+
  "two windows, the rightmost of them is open. The door on the first floor "+
  "looks solid enough, made of strong oak wood, strengthened with steel in "+
  "the frames.\n");
}

init()
{
  ::init();
  add_action("pull_bars","pull");
  add_action("pull_bars","push");
  add_action("climb_wall","climb");
  add_action("enter_window","enter");
  add_action("look_through_window","look");
}

pull_bars(string str)
{
  if (!str) return 0;
  if (str=="iron bars" || str=="iron bar" || str=="bars" || str=="bar") {
    write("You try to pull the iron bars out of their position, but they\n"+
    "won't budge.\n");
    say(QCTNAME(TP)+" tries to pull at the iron bars, but they won't budge.\n",TP);
    return 1;
    }
  write("Pull what?\n");
  return 1;
}

climb_wall(string str)
{
  string s1,s2;
  if (!str) {
    write("Climb what?\n");
    return 1;
    }
  if (sscanf(str,"%s window",s1)==1) {
    if (present("awake_dog",TO)) {
       write("As you start to climb the wall, the watch-dogs attack you!\n");
       say("As "+QTNAME(TP)+" starts climbing, the watch-dogs attack "+
         TP->query_objective()+"!\n",TP);
       present("awake_dog")->command("kill "+TP->query_real_name());
       return 1;
       }
    if (by_open_window) {
      if (TP==by_open_window) {
        write("But you have already climbed up the wall!\n");
        return 1;
        }
      TP->catch_msg("But "+QTNAME(by_open_window)+" is there already, and there's only room for one!\n");
      return 1;
      }
    if (TP->query_skill(104) > (45+random(10))) {
      write("You successfully climb up to the open window, and grab a hold of\n"+
      "the window frame.\n");
      say(QCTNAME(TP)+" successfully climbs the wall up to the open window, and\n"+
      "holds on to the window frame.\n",TP);
      by_open_window = TP;
      return 1;
      }
    write("You try to climb up the wall to the open window, but the wall is too\n"+
      "difficult for you to climb!\n");
    say(QCTNAME(TP)+" tries to climb the wall up to the open window, but fails!\n",TP);
    return 1;
    }
  if (str == "down" || str == "down the wall" || str == "down wall") {
    if (!by_open_window || TP != by_open_window) {
      write("You are not up the wall, so how can you climb down?\n");
      return 1;
      }
    write("You climb down the wall again.\n");
    say(QCTNAME(TP)+" climbs down the wall again.\n",TP);
    by_open_window = 0;
    return 1;
    }
  write("Climb what?\n");
  return 1;
}

test_by_window()
{
  if (TP == by_open_window) {
    write("You should climb down the wall first!\n");
    return 1;
    }
  return 0;
}

enter_window(string str)
{
    string race;
  if (!str) {
    write("Enter what?\n");
    return 1;
    }
  if (str == "open window" || str == "window") {
    if (TP != by_open_window) {
      write("The window here is secured with iron bars, you cannot enter!\n");
      return 1;
      }
    if (TP == by_open_window) {
      if ((race = TP->query_race_name()) == "hobbit" || race == "gnome") {
        write("You manage to squeeze yourself through the open window.\n");
        say(QCTNAME(TP)+" manages to squeeze "+TP->query_objective()+
          "self through the open window.\n",TP);
        by_open_window = 0;
        TP->move("/d/Gondor/minas/houses/pehall2");
        TP->init_command("look");
        return 1;
        }
      write("You try to enter the open window, but discover it's too narrow\n"+
        "for a "+TP->query_race_name()+" to enter through!\n");
      say(QCTNAME(TP)+" tries to enter the open window, but is too big!\n",TP);
      return 1;
      }
    }
  write("Enter what?\n");
  return 1;
}

look_through_window(string str)
{
  if (str !="through window") return 0;
  if (TP==by_open_window) {
    write("Through the open window you see a hall in the second floor of the\n"+
    "house. A spiral stairway leads down in the southeastern corner of the\n"+
    "hall. There's a door in the north wall, and another in the west wall.\n");
    say(QCTNAME(TP)+" looks in through the open window.\n",TP);
    return 1;
    }
  write("Through the iron barred window you see the livingroom in the first\n"+
  "floor of the house. There are two doors in the east wall of the room,\n"+
  "and there are some nice pieces of furniture there.\n");
  say(QCTNAME(TP)+" looks in through the iron barred window.\n",TP);
  return 1;
}

add_dogs()
{
  clone_object("/d/Gondor/minas/npc/wdog")->move(TO);
}

query_by_window()
{
  return by_open_window;
}

set_outside_window(object pl)
{
  by_open_window = pl;
}

