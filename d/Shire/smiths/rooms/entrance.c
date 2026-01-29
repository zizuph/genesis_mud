/*
     The entrance to the smiths guild
*/

#pragma save_binary;

inherit "/d/Shire/room";

#include "smiths.h"
#include "/d/Shire/common/defs.h"
#include "/sys/macros.h"
#include "/sys/stdproperties.h"

#define SITTING "_waiting_i_sit"

void
create_room() {
   set_short("Entrance to the Smiths guild");
   set_long("This room is called the Hall and is supposed to be the"+
      " place where foreigners stay when they are with smiths if they don't"+
    " have business in the guild. The room is filled with all"+
      " kinds of marvelous items, many of them of dwarven make. There are some"+
      " nice chairs here to make it more comfortable for people waiting"+ 
      " here.\n");

   add_item(({"chair","chairs"}),"The chairs seem nice and soft, perhaps you"+
      " want to sit in it?\n");
   add_item("items","There are some fine examples of dwarven stone carving"+
      " among them.\n");

   add_exit(SMITHSDIR_ROOMS+"discus","southwest",0);
//   add_exit("/d/Shire/common/bree/smith_temp","east",0);
    add_exit("/d/Shire/smiths/rooms/yard","east");


   add_prop(ROOM_I_INSIDE,1);
// safe rooms
    add_prop(ROOM_I_NO_ATTACK, 1);
    add_prop(OBJ_M_NO_ATTACK,1);
    add_prop(ROOM_I_NO_MAGIC_ATTACK, 1); 

}

init() {
   ::init();

   add_action ("catch_cmd" , "", 1);
   add_action ("sit"       , "sit");
   add_action ("rise"      , "rise");
}

int
sit() {
   if (!TP->query_prop(SITTING)) {
      write("You sit down in the chair and make yourself comfortable.\n");
      say(QCTNAME(TP)+" sits down in a chair.\n");
      TP->add_prop(SITTING,1);
      return 1;
   }

   write("You are already sitting in a chair.\n");
   return 1;
}

int
rise() {
   if (TP->query_prop(SITTING)) {
      write("You rise from the chair.\n");
      say(QCTNAME(TP)+" rises from the chair.\n");
      TP->remove_prop(SITTING);
      return 1;
   }
   else {
      write("Rise.. how? from what?\n");
      return 1;
   }
}

int
catch_cmd() {
   if (TP->query_prop(SITTING)) {
      write("You rise from the chair.\n");
      say(QCTNAME(TP)+" rises from the chair.\n");
      TP->remove_prop(SITTING);
   }

   return 0;
}

