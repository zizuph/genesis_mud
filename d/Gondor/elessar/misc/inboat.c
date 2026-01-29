inherit "/d/Gondor/common/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/defs.h"

int boat_loc, livings;
string shore_east, shore_west;
object boat_obj;

create_room()
{
  set_short("In a rowing boat");
  set_long("@@long_func");
  set_noshow_obvious(1);
  set_boat_loc(1);
  setup_locs();
  add_prop(ROOM_I_NO_CLEANUP,1);
}

init()
{
  ::init();
  add_action("row","row");
  add_action("leave_boat","leave");
  add_action("leave_boat","exit");
  add_action("leave_boat","out");
  add_action("leave_boat","disembark");
  add_action("do_light_update","_update_light");
}

long_func()
{
  string longstr;
  longstr = "You are sitting in a little wooden boat, currently ";
  if (boat_loc == 1) longstr=longstr+"by the western riverbank of the river Anduin. ";
  else if (boat_loc == 5) longstr=longstr+"by the eastern riverbank of the river Anduin. ";
  else longstr=longstr+"out on the mighty river Anduin. ";
  return break_string(longstr+"\n",70);
}

leave_boat()
{
  if (boat_loc == 1) {
    this_player()->move_living("ashore",shore_west);
    return 1;
    }
  else if (boat_loc == 5) {
    this_player()->move_living("ashore",shore_east);
    return 1;
    }
  else write("You don't dare to leave the boat and dive into the river!\n");
  return 1;
}

row(str)
{
  if (!str) {
    write("Row in which direction?\n");
    return 1;
    }
  if (!present("oars",this_player())) {
    write("How can you row without oars??\n");
    return 1;
    }
  if (str == "east") {
    boat_loc++;
    if (boat_loc > 5) {
      write("You can't row the boat any further east; you are already by the\n"+
        "east bank of the river!\n");
      boat_loc = 5;
      return 1;
      }
    else if (boat_loc == 5) {
      write("The boat lands at the east riverbank.\n");
      say(QCTNAME(this_player())+" rows the boat to the east riverbank.\n");
      boat_obj->move(shore_east);
      tell_room(shore_east,QCNAME(this_player())+" comes rowing in a boat.\n");
      return 1;
      }
    else {
      write("You row east across the mighty river Anduin, braving the currents.\n");
      say(QCTNAME(this_player())+" rows the boat east across the river currents.\n");
      boat_obj->move("/d/Gondor/anorien/osgiliath/riverroom");
      if(boat_loc == 2)
          tell_room(shore_west,"The boat leaves onto the waters of the Anduin.\n");
      return 1;
      }
    }
  if (str == "west") {
    boat_loc--;
    if (boat_loc < 1) {
      write("You can't row the boat any further west; you are already by the\n"+
        "west bank of the river!\n");
      boat_loc = 1;
      return 1;
      }
    else if (boat_loc == 1) {
      write("The boat lands at the west riverbank.\n");
      say(QCTNAME(this_player())+" rows the boat to the west riverbank.\n");
      boat_obj->move(shore_west);
       tell_room(shore_west,QCNAME(this_player())+" comes rowing in a boat.\n");
      return 1;
      }
    else {
      write("You row west across the currents of the mighty river Anduin.\n");
      say(QCTNAME(this_player())+" rows the boat west across the currents of the river.\n");
      boat_obj->move("/d/Gondor/anorien/osgiliath/riverroom");
      if(boat_loc == 4)
          tell_room(shore_east,"The boat leaves onto the waters of the Anduin.\n");
      return 1;
      }
    }
  if (str == "north") {
    write("The current is too strong, you are unable to row upstream.\n");
    return 1;
    }
  if (str == "south") {
    write("You row south for a while, but a swift and swirling current returned\n"+
      "you to where you were.\n"+
      "(Actually, this is only Elessar's way of saying:\n"+
      "           'That area is not yet finished. Try again later please.'\n");
    return 1;
    }
  if (str == "upstream") row("north");
  if (str == "downstream") row("south");
  write("Row where?\n");
  return 1;
}

set_boat_loc(int i)
{
  boat_loc = i;
}

set_boat_obj(object obj)
{
  boat_obj = obj;
}

setup_locs()
{
  shore_west = "/d/Gondor/anorien/osgiliath/boatplace";
   shore_east = "/d/Gondor/ithilien/osgiliath/boatplace";
}

enter_inv(obj,from)
{
  if (living(obj)) {
    if (livings > 2) {
      obj->move(from);
      tell_object(obj,"The boat only holds three persons.\n");
      tell_room(this_object(),QCNAME(obj)+" tried to enter the boat, but there's not enough room.\n");
      return;
      }
    livings++;
    }
  ::enter_inv(obj,from);
}

leave_inv(obj,to)
{
  if (living(obj)) livings--;
  if (livings < 0) livings = 0;
  ::leave_inv(obj,to);
}

query_livings()
{
  return livings;
}

int
do_light_update(string str)
{
  if(!str) return 0;
  write("Please make a bug report. In the report, please give these two numbers:\n");
  write("OBJ_I_LIGHT: " + TO->query_prop(OBJ_I_LIGHT) + 
    ", ROOM_I_LIGHT: " + TO->query_prop(ROOM_I_LIGHT) + ".\n");
  TO->update_light();
  write("Hope this helped! \n");
  write("Please don't forget the bug report, if you want to have this fixed for good!\n");
  return 1;
}
