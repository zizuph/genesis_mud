inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>

create_object(){
   set_name("wand");
   add_adj("black");
   set_long("A think jet black wand.\n");
}

init(){
add_action("mdes", "mdes");
::init();
}

mdes(string str){
   string who, what;
   object obj, person;
   
   if(!strlen(str) || sscanf(str, "%s %s", who, what) != 2) {
      return "Destruct what in whom?\n";
   }
   person = find_living(lower_case(who));
   if (!person) return "Cannot locate this person.\n";
   if(present(what, person)){
         obj->remove_object();
      }
   }
