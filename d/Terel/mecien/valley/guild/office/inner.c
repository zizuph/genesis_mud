inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Terel/mecien/valley/guild/mystic_defs.h"

#define TP this_player()
#define TO this_object()
#define ENV environment
#define PATH "/d/Terel/mecien/valley/guild/"

int wish;

init(){
   ::init();
   add_action("pray", "pray");
   add_action("wish", "wish");
}


wish(string str){
   if(!str) return 0;
   if(TP->query_skill(OFFICE)!=2) return 0;
   if(wish == 0) return 0;
   if(str == "to be heard"){
      set_alarm(3.0, -1.0, "fulfill");
  return 1;
   }
   
   
}

fulfill(){
object ob;
   wish = 0;
   TP->catch_msg("Someone says: So be it then, Orator!\n");
  if(!present("ancient_horn")){
      ob=clone_object(PATH + "obj/horn");
      ob->move(TP);
      TP->catch_msg("You sense that something has been given to you.\n");
      return 1;
   }
   return 1;
}

pray(){
   if(random(TP->query_skill(PIETY)) + random(100) > 100){
      set_alarm(4.0, -1.0, "glow");
      set_alarm(10.0, -1.0, "do_image");
   }
   return 0;
}

create_room(){
   
   set_short("Inner Chamber");
   set_long(
      "A dark and somber hall, formed of blackened rock that glistens with " +
      "streaks of silver veins. A long tapestry hangs from the wall, deep red " +
      "in color, flooded with silver stars. A redwood shelf rests against one wall, "
      + "a dark painting on another and in the center of the room is an obelisk.\n"
   );
   add_item("tapestry", "It is a field of red, with small silver stars all over it.\n");
   add_item("veins", "It is silver that streaks through the rouch black rock.\n");
   add_item("painting", "It depicts a great tree being swallowed up by a dark tempestuous storm.\n");
   add_item("obelisk", "Fashioned of a dark gray stone, it is carved with symbols and runes.\n");
   add_item("symbols", "They are mysterious creatures, known only to the wise.\n");
   add_item("shelf", "It is made of redwood and seems to be used for storage.\n");
   
   add_cmd_item("tapestry", "touch", "@@do_touch");
   add_cmd_item("runes", "read", "Those that hear me have known my name.\n");
   clone_object(PATH + "office/od2")->move(TO);
   
   
}

glow(){
   tell_room(TO, "The obelisk begins to glow with a pale light.\n");
}

do_image(){
   
   int n;
   n = random(4);
   
   if(n == 0){
      tell_room(TO, "The image of a fiery eagle rises from the obelisk!\n");
      set_alarm(4.0, -1.0, "consume");
      return 1;
   }
   if(n == 1){
      tell_room(TO, "The image of silvery winged serpent arises from the obelisk!\n");
      set_alarm(4.0, -1.0, "swoop");
      return 1;
   }
   if(n == 2){
      tell_room(TO, "The image of a one-eyed giant arises from the obelisk!\n");
      set_alarm(4.0, -1.0, "crack");
      return 1;
   }
   if(n == 3){
      tell_room(TO, "The image of a goatlike-fish arises from the obelisk!\n");
      set_alarm(4.0, -1.0, "splash");
   }
   
}


do_touch(){
   object me;
   me = TP;
   if(TP->query_skill(OFFICE)!=2){
      TP->catch_msg("You touch the tapestry and feel a strong sense of peace pass through your body.\n");
      tell_room(TO, QCTNAME(TP) + " touches the tapestry.\n", TP);
      return 1;
   }
   TP->catch_msg("You touch the sacred tapestry.\n");
   set_alarm(3.0, -1.0, "speak", me);
   return 1;
}

speak(object me){
   tell_room(TO, "You hear whispers from the shadows.\n", me);
   TP->catch_msg("Someone says: What is thy wish, " + me->query_name() + 
      "?\n");
   wish = 1;
   set_alarm(10.0, -1.0, "bye");
}

bye(){
   wish = 0;
}


consume(){
   object ob;
   tell_room("The fiery eagle flares up and is consumed in fire. As it "
      + "disappears into the flames something is deposired upon the floor.\n");
   ob = clone_object(PATH + "obj/fscroll");
}

