/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/armour";
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>

#define TP this_player()
#define EN environment
#define TO this_object()


init()
{
    add_action("warlord", "warlord");
    add_action("virtue", "virtue");
    add_action("stardust", "stardust");
    ::init();
}

query_value(){ return 0; }

public void
create_armour()
{
   
   set_name("ring");
   set_adj("ancient");
   add_adj("gold");
    set_short("ancient gold ring");
   
   set_long("A gold ring set with ancient runes.\n");
   add_item("runes", "They are mysterious and unknown.\n");
   
   add_name("protector_ring");
   
   add_prop(OBJ_I_NO_DROP, 1);
   add_prop(OBJ_M_NO_SELL, 1);
   
   set_at(A_ANY_FINGER);
   set_af(TO);
   
}

query_recover(){ return 0; }
query_auto_load(){
   return MASTER + ":";
}

enter_env(object dest, object old){
   ::enter_env(dest, old);
}

stardust(){
 tell_room(EN(TP), QCTNAME(TP) + " holds out " + TP->query_possessive() +
 " hands and a mist of shiny gold dust springs up into a tiny vortex.\n", TP);
  TP->catch_msg("You call upon the stars to manifest their glory.\n");
   set_alarm(4.0, -1.0, "star", EN(TP));
  return 1;
}

star(object where){
  tell_room(where, "A sparkling golden star appears over you, casting forth rays of golden light, with beams of glittering stardust!\n");
}

wear(object obj){
   write("You feel great virtue as you wear the ancient ring.\n");
   say(QCTNAME(TP) + " emanates a golden light as he wears the " + TO->query_short() + ".\n");
   return 1;
}


virtue(string str){
   object who;
   if(!str){
      write("You kneel upon the groud in an attempt to show the virtues of humility and obedience.\n");
      say(QCTNAME(TP) + " kneels upon the ground, humbly lowering " + TP->query_possessive() + 
         " head in obedience.\n");
      return 1;
   }
   who = present(str, EN(TP));
   if(!who) return "Show virtue to who?\n";
  if(!living(who)) return "Show virtue to who?\n";
   TP->catch_msg("You grasp " + QCTNAME(who) + " by the shoulder, look into " +
      who->query_possessive() + " eyes and pray that the ancients will show " +
      who->query_objective() + " their glory.\n");
  who->catch_msg(QCTNAME(TP) + " grasps you by the shoulder, stares into your eyes, " + TP->query_possessive() + " gold ring glowing brightly as " +
      TP->query_pronoun() + " intones a prayer.\n");
   tell_room(EN(TP), QCTNAME(TP) + " grasps " + QCTNAME(who) + " by the shoulder and stares into " +
      who->query_possessive() + " eyes.\n", ({ TP, who }));
   set_alarm(5.0, -1.0, "virtues", who);
   return 1;
}

virtues(object who){
  who->catch_msg("You feel overcome with a sense of humility.\n");
}

warlord(){
   write("You cast forth the eminence of the ancient world.\n");
   say(QCTNAME(TP) + " stands tall and proud, like a forgotten hero of the ancient days.\n");
   return 1;
}
