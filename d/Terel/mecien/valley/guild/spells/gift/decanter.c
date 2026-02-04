inherit "/std/object";
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>

#define TP this_player()
#define TO this_object()
#define EN environment

init(){
   add_action("drinks", "drink");
   ::init();
}

drinks(string str){
   if(!str) return 0;
   if(str == "from decanter"){
      write("You drink from the golden decanter.\n");
      say(QCTNAME(TP) + " drinks from the magnificent golden decanter.\n");
      set_alarm(2.0, -1.0, "yum", TP);
      set_alarm(5.0, -1.0, "wings", TP);
      return 1;
   }
}

yum(object who){
   who->catch_msg("It tastes like sweet rainwater from the heavens!\n");
   TO->move("/d/Terel/mecien/hill");
   TP->catch_msg("As you drink the last of it, the decanter vanishes.\n");
}

wings(object who){
   object win;
  seteuid(getuid(TO));
   who->catch_msg("A magnificent pair of wings emerge from your back!\n");
   tell_room(EN(who), "A pair of feathery white wings emerge from the back of " + QTNAME(who) + "!\n", who);
   win=clone_object("/d/Terel/mecien/valley/guild/spells/wings");
   win->move(who);
  TO->remove_object();
}

create_object(){
   set_name("decanter");
   set_adj(({ "magnificent", "golden" }));
   
   set_long(
      "It is a bright, gleaming golden decanter. Its lip is made of ivory, " +
      "below which is a ring of aquamarines. The base is inscribed with winged spirits " +
      "dancing upon clouds.\n");
   
   add_prop(MAGIC_AM_MAGIC, ({ 40, "conjurations" } ));
   add_prop(OBJ_I_VALUE, 0);
}

