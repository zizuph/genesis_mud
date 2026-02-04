/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/container";
#include <stdproperties.h>
#include <macros.h>

int closed;

#define GUILD "The Ancient Mystic Order"

init(){
   add_action("place", "place");
   add_action("open", "open");
   add_action("close", "close");
   ::init();
}

create_container(){
   set_name("cabinet");
   set_adj("elegant");
  add_adj("carved");
   set_long(
      "It is a beautiful piece of workmanship. The whole, made from\n"
      +"a soft golden wood, carved and engraved. Most of the carvings take\n"
      +"the shape of mysterious winged spirits. It has paned silvery\n"
      +"glass, so its contents can be seen.\n"
   );
   
   closed = 1;
   
   add_prop(OBJ_I_NO_GET, 1);
   add_prop(CONT_I_MAX_WEIGHT, 99999);
   add_prop(CONT_I_MAX_VOLUME, 99999);
   add_prop(CONT_M_NO_INS, "You cannot put things into the cabinet.\n");
   add_prop(CONT_M_NO_REM, "@@check_remove@@");
   
}

place(string str){
   
   
   object ob;
   
   notify_fail("Place what?\n");
   if(!str)
      return 0;
   if(!parse_command(str, this_player(), 
            "%o [in] [into] 'cabinet'", ob))
   return 0;
   notify_fail("You have no such thing.\n");
   if(!ob)
      return 0;
   if(closed){
      this_player()->catch_msg("The cabinet is closed.\n");
      return 1;
   }
   
  if(ob->query_prop(OBJ_I_NO_DROP)){
    this_player()->catch_msg("You cannot place that in the cabinet.\n");
  return 1;
  }
   if(ob->query_prop("blessed")){
      this_player()->catch_msg("You place the " + ob->query_name() +
         " within the cabinet.\n");
      tell_room(environment(this_player()),
         QCTNAME(this_player()) + " places something within the cabinet.\n",
         this_player());
      remove_prop(CONT_M_NO_INS);
      ob->move(this_object());
      add_prop(CONT_M_NO_INS, "You cannot put things into the cabinet.\n");
      return 1;
   }
   this_player()->catch_msg("You cannot place that within the cabinet.\n");
   return 1;
   
}

close(string str){
   if(!str) return 0;
   if(str == "cabinet"){
   if(closed){
   write("It is already closed.\n");
   return 1;
    }
      write("You close the cabinet.\n");
      say(QCTNAME(this_player()) + " closes the cabinet.\n");
    closed = 1;
      return 1;
   }
   
}

open(string str){
   if(!str) return 0;
   if(str == "cabinet"){
  if(closed < 1){
   write("It is already open.\n");
   return 1;
    }
      if(this_player()->query_guild_member(GUILD)){
         write("You open the cabinet.\n");
         say(QCTNAME(this_player()) + " opens the cabinet.\n");
         closed = 0;
         return 1;
      }
      write("It will not open.\n");
     say(QCTNAME(this_player()) + " tries to open the cabinet.\n");
      return 1;
   }
}

check_remove(){
   
   if(closed) return "It is closed\n";
   
   
}

