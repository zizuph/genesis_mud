inherit "std/object";

#include <macros.h>
#include <stdproperties.h>

create_object(){
   
   set_name("statue");
  set_adj("tall");
  add_adj("stone");
  set_long(
  "It is a tall stone statue, taking the shape of a heroic looking\n"
+ "man that holds a shield and sword aloft.\n");
   add_prop(OBJ_I_NO_GET, 1);
   
   
}


bow_statue(string str){
   if(str!="statue") return;
   write("You bow before the statue.\n");
   say(QCTNAME(this_player()) + " bows before the statue.\n");
   return 1;
}
