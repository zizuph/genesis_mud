inherit "/std/room";
#include "/d/Roke/common/defs.h"
#include <ss_types.h>
#include <stdproperties.h>
#include <language.h>
#include "/d/Roke/Cirath/defs.h"
#include <macros.h>

#define SBEACH CIUBORI+"homes/sneakbeach"

int door = 0; /*closed */

void create_room()
{
  set_short("In a small room");
  
  set_long(break_string(
           "You're standing inside a small room underneath the city wall. There's a "+
           "ladder leading upwards and a door leading out. The door is closed.\n"
           ,60));  
  add_item("ladder","It's a wooden ladder leading down.\n");

  INSIDE;
  add_prop(ROOM_I_LIGHT,0);

  add_exit(CIUBORI+"homes/sneakladder","up");
  add_exit(CIUBORI+"homes/sneakbeach","north","@@query_door");

}

void init()
{
  ::init();

  add_action("d_open","open");
  add_action("d_close","close");
}

int query_door()
{
  if (!door)
    return 1;

  return 0;
}

int d_open(string str)
{
  NF("The door is already open!");

  if (str == "door" && door == 0)
  {
    write("You open the door.\n");
    say(QCTNAME(TP)+" opens the door.\n");
    door = 1;
    set_long(break_string(
             "You're standing inside a small room underneath the city wall. There's a "+
             "ladder leading upwards and a door leading out. The door is open.\n"
             ,60));  
    SBEACH->ch_door(1);
    return 1;
  }
  else if (str == "door" && door == 1) return 0;

  NF("What?");
  return 0;
}

int d_close(string str)
{
  NF("The door is already closed!");

  if (str == "door" && door == 1)
  {
    write("You open the door.\n");
    say(QCTNAME(TP)+" closes the door.\n");
    door = 0;
    set_long(break_string(
             "You're standing inside a small room underneath the city wall. There's a "+
             "ladder leading upwards and a door leading out. The door is closed.\n"
             ,60));  
    SBEACH->ch_door(0);
    return 1;
  }
  else if (str == "door" && door == 0) return 0;

  NF("What?");
  return 0;
}

int ch_door(int a)
{
  if (!a)
  {
    door = 0;
    tell_room(TO,"Someone closes the door from the other side.\n");
    set_long(break_string(
           "You're standing in a small room. The floor slopes into the water. "+
           "There's a door to the south. The door is closed.\n"
           ,60));  
    return 1;
  }
  door = 1;
  tell_room(TO,"Someone opens the door from the other side.\n");
  set_long(break_string(
         "You're standing in a small room. The floor slopes into the water. "+
         "There's a door to the south. The door is closed.\n"
         ,60));  
  return 1;
}
