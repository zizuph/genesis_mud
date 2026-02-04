inherit "/std/object";
#include <stdproperties.h>
#include <macros.h>

#define EN environment
#define TO this_object()
#define TP this_player()
#define SUBLOC "wings_subloc"

show_subloc(string subloc, object carrier, object for_obj){
   string str;
   if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS)) return "";
   if(for_obj == carrier)
      str = "A pair of feathery white wings arise from you back.\n";
   else
      str = "A pair of feathery white wings arise from " + carrier->query_possessive() + " back.\n";
   return str;
}



enter_env(object inv, object from){
   ::enter_env(inv, from);
   if(living(inv)){
      inv->add_subloc(SUBLOC, TO);
   }
   ::enter_env(inv, from);
}

leave_env(object inv, object to){
   if(living(inv)){
      inv->remove_subloc(SUBLOC, TO);
      inv->catch_msg("The wings wade away.\n");
      tell_room(EN(inv), "The wings on " + QTNAME(inv) + " fade away.\n", inv);
   }
   ::leave_env(inv, to);
}

init(){
   add_action("fly", "fly");
   add_action("flap", "flap");
   ::init();
}

flap(string str){
   if(!str) return 0;
   if(str == "wings"){
      tell_room(EN(TP), QCTNAME(TP) + " flaps " + TP->query_possessive() + " feathery white wings.\n", TP);
      TP->catch_msg("You flap your feathery white wings.\n");
      return 1;
   }
}

fly(string str){
   string *places;
   string destination;
   if(!str){
      write("Fly where?\n");
      return 1;
   }
  places = ({ "twelve", "cornerstone", "valley" });
   if(member_array(str, places) > -1){
      write("You fly off into the sky.\n");
      say(QCTNAME(TP) + " flies off into the sky.\n");
  if(str == "twelve") destination = "/d/Terel/mecien/valley/guild/guild";
  if(str == "valley") destination = "/d/Terel/mecien/valley/entrance";
      TP->move_living("M", destination);
      tell_room(EN(TP), QCTNAME(TP) + " flies down from above.\n", TP);
      return 1;
   }
   TP->catch_msg("The spirits of the skies know no such place.\n");
   return 1;
}

create_object(){
   set_name("wings_obj");
   set_no_show(1);
   add_prop(OBJ_M_NO_DROP, 1);
   
   add_item("wings", "They are long feathery white wings.\n");
   set_alarm(120.0, -1.0, "bye");
}
bye(){
   TO->remove_object();
}


