inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

int rug;

void reset_room()
{
  rug = 0;
}

void create_room()
{
  set_short("a home in Ciubori");
  
  set_long(break_string(
           "This is one of the homes in Ciubori. The room looks quite scabby and you "+
           "wonder who wants to live here. The furniture is sparse. Just a bed in the "+
           "corner and a wooden table with a chair. The carpets are filthy and a dirty "+
           "rug is covering the floor. In the window stands a pot which contains something "+
           "that smells foul.\n"
           ,60));  

  add_item("ciubori","The third largest city in Cirath.\n");
  add_item(({"wall","walls"}),"They were white...\n");
  add_item("table","Its a wooden table. Doesn't look very clean.\n");
  add_item("chair","The chair doesn't look very confortable.\n");
  add_item("carpet","The carpets are stained by grease and other unmentional stuff.\n");
  add_item("pot","Eeeks!! It smells terribly.\n");
  add_item("rug","The rug covers the floor, but it looks like someone lifted it not long ago.\n");
  add_item("window","Outside the window you can see the street.\n");
  add_item("room","It's not a nice room.\n");

  INSIDE;

  add_exit(CIUBORI+"diamond/street4","south");

  reset_room();
}

void
init()
{
  ::init();

  add_action("ruglift","lift");
  add_action("holeenter","enter");
}

int
ruglift(string str)
{
  if (str=="rug" && rug==0)
  {
    write("You discover a hole in the floor that are covered with some wood.\n");
    add_item("hole","The hole is covered with wood. Perhaps you could lift that off too.\n");
    add_item("wood","It's covering the hole. You think you can manage to lift it off.\n");
    set_long(break_string(
           "This is one of the homes in Ciubori. The room looks quite scabby and you "+
           "wonder who wants to live here. The furniture is sparse. Just a bed in the "+
           "corner and a wooden table with a chair. The carpets are filthy and a dirty "+
           "rug is covering the floor. In the window stands a pot which contains something "+
           "that smells foul. The rug has been lifted off and reveals a hole covered with "+
           "wood.\n"
           ,60));  
    rug = 1;
    return 1;
  }
  else if (str == "rug" && rug==1)
  {
    write("The rug is already lifted off, and where it have lied you can see a hole covered "+
      "with wood.\n");
    return 1;
  }

  if (str=="wood" && rug==1)
  {
    write("You lift off the wood and discover a ladder leading down.\n");
    remove_item("hole");
    remove_item("wood");
    add_item("hole","The hole lies open, why don't you enter it?\n");
    add_item("wood","It's lies beside the hole.\n");
    set_long(break_string(
           "This is one of the homes in Ciubori. The room looks quite scabby and you "+
           "wonder who wants to live here. The furniture is sparse. Just a bed in the "+
           "corner and a wooden table with a chair. The carpets are filthy and a dirty "+
           "rug is covering the floor. In the window stands a pot which contains something "+
           "that smells foul. The rug has been lifted off and reveals a hole and some "+
           "pieces of wood lying beside it.\n"
           ,60));  
    rug = 2;
    return 1;
  }
  else if (str=="wood" && rug==2)
  {
    write("The wood is already lifted off. Where it has lied, a ladder leads down into a hole.\n");
    return 1;
  }

  NF("What?");
  return 0;
}

int
holeenter(string str)
{
  if (str=="hole" && rug==2)
  {
    write("You enter the hole.\n");
    TP->move_living("through the hole",CIUBORI+"homes/sneakladder");
    return 1;
  }
  NF("What?!");
  return 0;
}
