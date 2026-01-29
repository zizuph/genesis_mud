

inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define TO this_object()
#define TP this_player()
#define ENV environment(TO)

int open, sealed;

init(){
    add_action("do_open", "open");
    add_action("do_read", "read");
   ::init();
}

do_open(string str){
   int fs, ss, ts;
   
 if(str !="book") return 0;
   if(open == 1){
      TP->catch_msg("It is already open!\n");
      return 1;
   }
   if(open == 0){
      fs=TO->query_prop("first_seal");
      ss=TO->query_prop("second_seal");
      ts=TO->query_prop("third_seal");
      if(fs || ss || ts){
         TP->catch_msg("One of the seals has not been loosed!\n");
         return 1;
      }
      TP->catch_msg("You open the ancient black book.\n");
      open = 1;
      tell_room(environment(this_player()),
         QTNAME(TP) + " opens the ancient black book.\n", TP);
      return 1;
   }
}

create_object(){
   
  open = 0;

   set_name("book");
   set_adj("black");
   add_name("book_of_darkness");
   add_name("Tome of Darkness");
   
   set_long(
      "Scaled in dull black leather, it seems to be some ancient book\n"
      +"weathered and beaten, aged like a thing of battle. It is stained\n"
      +"and marked with ash and blood. Three seals adorn the cover.\n"
   );
   
  add_item("first seal", "@@fs");
  add_item("second seal", "@@ss");
   add_item("third seal", "@@ts");
  add_item("seals", "They are three, mighty and unbreakable.\n");
   add_item("cover", "It is black leather scales, like those of a dragon.\n");
   add_prop("first_seal", 1);
   add_prop("second_seal", 1);
   add_prop("third_seal", 1);
}

fs(){
 if(TO->query_prop("first_seal")){
  write("The first seal is in place and secure.\n");
}
else
write("The first seal has been loosed!\n");
}

ss(){
 if(TO->query_prop("second_seal")){
  write("The second seal is in place and secure.\n");
}
else
write("The second seal has been loosed!\n");
}
ts(){
 if(TO->query_prop("third_seal")){
  write("The third seal is in place and secure.\n");
}
else
write("The third seal has been loosed!\n");
}

remove_seal(){
   if(TO->query_prop("first_seal")){
      TO->remove_prop("first_seal");
      tell_room(ENV, "The first seal of the ancient black book opens!\n");
      call_out("add_first_seal", 100 + random(100));
      return 1;
   }
   if(TO->query_prop("second_seal")){
      TO->remove_prop("second_seal");
      tell_room(ENV, "The second seal of the ancient black book opens!\n");
      call_out("add_second_seal", 100 + random(100));
      return 1;
   }
   if(TO->query_prop("third_seal")){
      TO->remove_prop("third_seal");
      tell_room(ENV, "The third seal of the ancient black book opens!\n");
      call_out("add_third_seal", 100 + random(100));
      return 1;
   }
}

add_first_seal(){
   add_prop("first_seal", 1);
   tell_room(ENV, "A black halo forms over the ancient black book,\n"
      + "as it mysteriously seals itself!\n");
   open = 0;
   return 1;
}
add_second_seal(){
   add_prop("second_seal", 1);
   tell_room(ENV, "A black halo forms over the ancient black book,\n"
      + "as it mysteriously seals itself!\n");
   open = 0;
   return 1;
}
add_third_seal(){
   add_prop("third_seal", 1);
   tell_room(ENV, "A black halo forms over the ancient black book,\n"
      + "as it mysteriously seals itself!\n");
  open = 0;
   return 1;
}

