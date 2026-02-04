inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define PATH "/d/Terel/mecien/valley/city/"
#define TP this_player()
#define EN environment


init(){
   ::init();
   add_action("knock", "knock");
}

in_garden(object where){
 object n;
  n=clone_object("/d/Terel/mecien/valley/bf");
   n->move(PATH + "g1");
  n->remove_object();
  if(find_living("wentis")){
  if(where = EN(TP)){
   TP->catch_msg("Someone comes and opens the gate and leads you into the garden.\n");
    TP->move_living("through the gate", PATH + "g1");
}
}
}

knock(string str){
   notify_fail("You knock upon the gate, disturbing the peace of this place.\n");
  if(!str) return 0;
   notify_fail("You knock upon the gate, disturbing the peace here.\n");
   if(!parse_command(str, TP, " 'quietly' [upon] [on] [the] 'gate'"))
      return 0;
   
   TP->catch_msg("You knock quietly upon the gate.\n");
   set_alarm(3.0, -1.0, "in_garden", EN(TP));
   return 1;
   
}

create_room(){
   
   set_short("Monastery of Elnoven");
   set_long(
      "Austere and silent, this large stone chamber seems to be the foyer " +
      "of this great building. An iron gate leads into a garden area from " +
      "here, but is closed to the public. A sense of serenity falls upon this " +
      "place, its whispered stillness and solemn stonework project this very " +
      "clearly.\n"
   );
   
   add_item("gate", "It is an iron gate leading into a garden. Over it " +
      "there is an inscription in the stone.\n");
   add_item("stonework", "It is very smooth, being of a gothic style, it " +
      "has a grand flavour.\n");
   add_item("inscription", "It is inscribed over the gate in the stone.\n");
   add_item("garden", "It is very beautiful and can be seen through the gate.\n");
   add_cmd_item("inscription", "read", "IN SILENTIUM REDIGERE IN MYSTERIA SUMUS\n");
   add_exit(PATH + "street6", "southeast", 0);
}

