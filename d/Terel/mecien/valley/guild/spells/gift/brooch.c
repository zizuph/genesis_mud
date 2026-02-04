inherit "/std/object";
#include <macros.h>
#include <stdproperties.h>

#define TP this_player()
#define TO this_object()
#define EN environment

init(){
   add_action("pin", "pin");
   add_action("stare", "stare");
   ::init();
}

pin(string str){
   object who;
   int n;
   
   if(!str) return 0;
   
   notify_fail("Pin what where?\n");
   if(!parse_command(str, EN(TP), " 'brooch' [on] %o ", who)) return 0;
   
   notify_fail("Pin the brooch on who?\n");
   if(!living(who)) return 0;
   
  if(who = TP) return 0;
   n = who->query_panic();
   who->add_panic(-n);
   tell_room(EN(TP), QCTNAME(TP) + " pins a brooch on " + QTNAME(who) + ".\n", ({ who, TP }));
   who->catch_msg(QCTNAME(TP) + " pins a silver sapphire brooch on you.\n");
   TP->catch_msg("You pin the brooch upon " + QTNAME(who) + ".\n");
   set_alarm(2.0, -1.0, "calm", who);
   return 1;
}

calm(object who){
   who->catch_msg("The brooch shines bright and becomes a pale blue aura about you and disappears. It calms your spirit and makes you feel secure.\n");
   tell_room(EN(who), "The brooch pinned on " + QTNAME(who) + " pulses into a pale blue aura about " + who->query_objective() + " and disappears.\n", who);
   TO->remove_object();
}



stare(string str){
   if(!str) return 0;
   if(str == "into brooch"){
      tell_room(EN(TP), QCTNAME(TP) + " stares deeply into a silver brooch.\n", TP);
      TP->catch_msg("You stare deep into the sapphire of the brooch, feeling a peace within it that comforts your spirit.\n");
      return 1;
   }
}

create_object(){
   set_name("brooch");
   set_adj(({ "silvery", "sapphire" }));
   
   set_long(
      "A beautiful brooch, made from silver, it is oval in shape. A large " +
      "sapphire is set in the center it. On either side of the sapphire, " +
      "the silver is carved to form two candlesticks.\n");
   
   add_prop(MAGIC_AM_MAGIC, ({ 30, "conjuration" }));
   add_prop(OBJ_I_VALUE, 0);
   
}

