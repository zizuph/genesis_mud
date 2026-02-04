inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#define TP this_player()
#define TO this_object()
#define ENV environment
#define PATH "/d/Terel/mecien/valley/city/"
#define SL "is_upon_the_dias"

init(){
   ::init();
   add_action("lay", "lay");
   add_action("pray", "pray");
}

enter_inv(object ob, object from){
   ::enter_inv(ob, from);
      if(ob->query_prop("laid_upon_dias"))
  {
   ob->show_subloc("is upon the dias", ob, TO);
  }
   
}

create_room(){
   
   set_short("Chapel");
   set_long(
      "This place appears to be some kind of shadowy chapel. Formed of ancient " +
      "stone, dark and unyielding, set with no windows or allowances to light. " +
      "Two statues stand over the entry to this place, like warding sentinels " +
      "prepared for battle. Upon the walls are ancient carvings. In the center of the " +
      "room a stone dias stands, raised a few steps.\n"
   );
   
   add_subloc(SL, TO);
   
   add_item("dias", "It is an elevated area, upon which is a mosaic.\n");
   add_item("mosaic", "It depicts a gathering of knights.\n");
   add_item("statues", "They are winged spirits with swords.\n");
   add_item("carvings", "They are upon the walls.\n");
   add_cmd_item("carvings", "read", "@@cread");
   add_item("knights", "They seem to be noble warriors of some kind.\n");
   add_item("stone", "It is an ancient dark stone.\n");
   add_exit(PATH + "street6", "out", 0);
}

lay(string str){
   object ob;
   if(!str) return 0;
  notify_fail("Lay what where?\n");
   if(!parse_command(str, ENV(TP), " %o [upon] [on] 'dias' ", ob))
      return 0;
  notify_fail("It cannot be dropped.\n");
   if(ob->query_prop(OBJ_M_NO_DROP)) return 0;

   write("You lay the " + ob->query_short() + " upon the dias.\n");
   say(QCTNAME(TP) + " lays a " + ob->query_short() + " upon the dias.\n");
  ob->add_prop("laid_upon_dias", 1);
  ob->move(TO);

   
   return 1;
}

pray(){
   TP->catch_msg("You pray next to the dias and find a small sense of peace.\n");
   tell_room(ENV(TP), QCTNAME(TP) + " prays next to the dias.\n", TP);
}

cread(){
   
   if(TP->query_skill(SS_LANGUAGE)>10){
      write("To the noble dead do we pray, for the glory that once " +
         "was and may yet be again.\n");
      return 1;
   }
   write("The words are obscure to you.\n");
   return 1;
}
