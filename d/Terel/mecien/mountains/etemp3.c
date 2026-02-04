inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define TP this_player()
#define TO this_object()
#define ENV environment
#define PATH "/d/Terel/mecien/mountains/"

anguish(object who){
   if(present(who, TO)){
      who->catch_msg("You have strayed too long in the darkness and it overtakes you.\n");
      who->heal_hp(-500);
   set_alarm(3.0, -1.0, "summon", who);
   }
}
summon(object who)
{
   object mon;
   mon=clone_object(PATH + "hound");
   tell_room(TO, "A cloud of smoke appears before the statue and forms into something.\n");
   mon->move_living("X", TO);
  mon->attack_object(who);
}


heart(object who){
   who->catch_msg("You sense a spiritual darkness here and it begins to eat away at your spirit!\n");
   who->heal_mana(-10);
   set_alarm(15.0, -1.0, "anguish", who);
}

enter_inv(object from, object to){
  object who;
   ::enter_inv(from, to);
   if(TP->query_guild_member("The Ancient Mystic Order")){
  who = TP;
      set_alarm(5.0, -1.0, "heart", who);
   }
   
}
create_room(){
   
   set_short("Ruined Temple");
   set_long(
      "Though cast in ruin, this was surely the center of this most " +
      "forsaken of places. Circular steps ascend to a platform of glassy " +
      "black stone, around which rise up four iron poles. At the " +
      "north end of this place is a huge statue. The wall behind it is crumbled " +
      "away, open to the flowing wind.\n"
   );
   
   add_item("sconces", "They are black iron, made to hold large candles.\n");
   add_item("walls", "They are crumbling and ruinous, though they remain.\n");
   add_item("ceiling", "Mostly crumbled away, but still providing some shelter.\n");
   add_item("platform", "It is made of glassy black stone and appears to be some kind of " +
      "altar. It appears to have some kind of markings on it.\n");
   add_item("markings", "They are some kind of strange letters.\n");
   add_item("letters", "They are of unknown origin. At close inspection you " +
      "see that they are carved into the block and now stained with dried blood.\n");
   add_cmd_item(({"letters", "markings", "platform"}),
      "Though you do not understand how, suddenly the words become very clear : \n\nMy Glory Is Come From The Pit\n");
   add_item("glassy stone", "It is black, most probably volcanic.\n");
  add_item("statue", "It is a gigantic statue of black rock, it is the image of a shapeless man.\n");
   add_item("block", "It is the base upon which the temple is built, some strange black, "
      + " glassy stone.\n");
   
   add_exit(PATH + "etemp2", "south", 0);
}

darkness(){
   object target;
   if(random(2)){
      target = TP;
      set_alarm(5.0, -1.0, "add_tick", target);
   }
}

add_tick(object target){
   object tick;
   
   tick = clone_object(PATH + "tick");
   tick->change_prop(OBJ_M_NO_GET, 0);
   tick->move(target);
   tick->change_prop(OBJ_M_NO_GET, 1);
   tick->change_prop(OBJ_M_NO_DROP, "It is stuck to you!\n");
}

