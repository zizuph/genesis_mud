/*
 *  River1 
 */

#pragma save_binary

inherit "/std/room";

#include "defs.h"
#include <stdproperties.h>

create_room()
{
   add_prop(ROOM_S_MAP_FILE, "hobbiton.txt");
   set_short("River Bywater");
   set_long("@@my_long");

   add_item("water", 
      "The water of the river Bywater is clear and cold. Perhaps too "
    + "cold to take a bath in it. The water came all the way from the "
    + "hills to the west.\n");

   add_item(({"river","Bywater","bywater","river bywater"}), 
      "The river Bywater comes from a spring in the hills to the west. "
    + "The water in it is clear and cold, and flows to the east. It is "
    + "not too deep here.\n");

   add_item(({"mill","watermill"}), 
      "The mill is a stone building, built just across the river. "
    + "A wheel is used to drive mechanical saws inside the mill.\n");

   add_item("wheel","@@wheel_long");
   add_item("board","@@board_long");

   add_exit(STAND_DIR + "river2","west",0);

   add_prop(ROOM_I_INSIDE, 0);  /* This is an open air room */
   add_prop(OBJ_I_CONTAIN_WATER, 1); /* There is water here */
}

init() {
   ::init();
 /* Make sure the mill-room is loaded. */
   (STAND_DIR + "mill")->query_wheel_fixed();
}

my_long() {
   string str;

   str =  "You are standing before the river "
        + "Bywater. The sunlight is reflected by the "
        + "clear, cold water with which the river is filled. "
        + "Across the river you see a watermill. ";

   if(wheel_fixed())
   {
      str += ("The wheel of the mill is slowly turning around, while "
            + "making a tranquilizing, gurgling sound. "); 
   }
   else
   {
      str += ("There is a board stuck between the wheel and the stone "
            + "wall of the mill. The board is blocking the wheel, so it "
            + "cannot turn any more. ");
   } 
   str += ("The river is not too deep here, so you can reach the "
        + "wheel on the other side. The river continues to the west.\n");
   return str;
}

wheel_long() {
   string str;

   str = "The wheel is made of oak, and is wet and slippery from "
       + "the green algea that are growing on it. ";

   if(wheel_fixed())
   {
      str += ("The wheel slowly revolves around its axis, making "
            + "gurgling noises while it is moved by the water.\n");
   }
   else
   {
      str += ("The wheel is being blocked by a board that is stuck "
            + "between the stone wall of the mill and the wheel.\n");
   }
   return str;
}

board_long() {
   string str;

   if(wheel_fixed())
   {
      str = "You find no board.\n";
   }
   else
   {
      str = "The board is preventing the wheel from turning around. "
          + "The only way to remove the board is to destroy it, "
          + "because the water pushes the wheel "
          + "firmly against the board, making it impossible to "
          + "move it.\n";
   }
   return str;
}

wheel_fixed() {
 /* This function is called by a Value By Function Call procedure,
    so we must set the euid to be able to use a call_other ('->')
 */
   seteuid(geteuid(this_object()));   
   return (STAND_DIR + "mill")->query_wheel_fixed();
}