inherit "/std/room";
#include <stdproperties.h>
#include <macros.h>

#define TO this_object()
#define PATH "/d/Terel/mecien/valley/guild/"
#define EN environment
#define TP this_player()

int broken;
int lamp1, lamp2, lamp3;


init(){
   add_action("do_break", "break");
   add_action("do_break", "smash");
   add_action("do_lamp", "light");
   ::init();
}

blasphemed(object who){
   object staff, amulet, icon;
   if(who->query_guild_member("The Ancient Mystic Order")){
      who->catch_msg("The sacred seal has been broken!\n");
      set_alarm(4.0, -1.0, "blood", who);
      who->heal_hp(-100);
      who->set_mana(0);
   staff = present("mystic_staff", who);
      if(staff){
         who->catch_msg("Your staff disintigrates.\n");
         staff->remove_object();
      }
  icon = present("holy_icon", who);
      if(icon){
         who->catch_msg("Your icon turns to dust.\n");
         icon->remove_object();
      }
   amulet = present("mystic_amulet", who);
      if(amulet){
         who->catch_msg("Your amulet shatters into tiny pieces.\n");
         amulet->remove_object();
      }
   }
}

blood(object who){
   tell_room(EN(who), QCTNAME(TP) + " falls upon the ground and blood issues from " 
      + who->query_possessive() + " eyes and nose!\n", who);
   who->catch_msg("You feel blood run down your face.\n");
}

winds(){
   tell_room(TP, "An icy winds rips through this place.\n");
}

lamp1_desc(){
   if(lamp1){
      return "It is burning with a radiant fiery light! It is in the shape of a winged "
  + "spirit holding aloft a chalice. Upon its chest a word.\n";
   }
   else return
  "It stands cold and lifeless. A winged spirit holding a chalice.\n";
}
lamp2_desc(){
   if(lamp2){
      return "It is burning with a radiant fiery light! It is in the shape of a winged "
  + "spirit holding aloft a chalice. Upon its chest is a word.\n";
   }
   else return
  "It stands cold and lifeless. A winged spirit holding a chalice.\n";
}
lamp3_desc(){
   if(lamp3){
      return "It is burning with a radiant fiery light! It is in the shape of a winged "
  + "spirit holding aloft a chalice. Upon its chest is a word.\n";
   }
   else return
  "It stands cold and lifeless. A winged spirit holding a chalice.\n";
}
destroy_seal(){
   tell_room("The sacred seal breaks into pieces.\n");
   map(users(), blasphemed);
   broken = 1;
   set_alarm(3.0, -1.0, "winds");
   lamp1 = 0;
   lamp2 = 0;
   lamp3 = 0;
}

thunder(){
  tell_room(TO, "You hear a thundering noise and the whole place begins to shake!\n");
}

int
do_break(string str){
   if(!str) return 0;
   if(str == "seal"){
      write("You strike the sacred seal.\n");
      say(QCTNAME(TP) + " strikes the sacred seal.\n");
   set_alarm(2.0, 0.0, "thunder");
      if(random(20) > 15){
         set_alarm(4.0, 0.0, "destroy_seal");
      }
      return 1;
   }
}


desc(){
   if(broken){
      return "A cold and lifeless chamber. Three silver lamps stand in the center of the chamber. " +
      "The north wall has a hole broken through it.\n";
   }
   else
      return "Timeless in its forgotten majesty, here at the deep parts of the world, " +
   "a place of serenity and peace, overshadowed by a churning darkness of" +
   " fiery mist. Flashes of electricity seem to crackle through this place, giving " +
   "it a direct sense of life. The floor is painted like the canopy of a tree, with "
   +"silver and gold leaves stretches out to its edges. In the center of this " +
   "place are three very tall silver lamps. The north wall has a large diamond " +
   "shaped seal upon it.\n";
}

read_ins(){
  if(broken) return 0;
 
  return "It is unfathomable!\n";
}

seal_desc(){
  if(broken){
  return "Once a seal made of some strange materals, now broken " +
"through and destroyed.\n";
  }
   else
  return "A massive seal upon the north wall, formed of some mysterious " +
"materials. It takes the shape of a star within a diamond. The star is circled by serpents " +
"and winged spirits. In the center of the seal is an inscription.\n";
}


create_room(){
   set_short("Holy Chamber");
   set_long("@@desc");
   
   
   add_exit(PATH + "sfoyer", "south", 0);
   add_item("lamps", "They are tall silver oil lamps. They take the shapes of "
      +"winged spirits holding aloft chalices.\n");
   add_item("lamp", "Which of the three?\n");
   add_item("leaves", "They are beautiful gold and silver.\n");
  add_item("floor", "It is painted to look like the top of a tree, so as to see its leaves.\n");
   add_item("first lamp", "@@lamp1_desc");
   add_item("second lamp", "@@lamp2_desc");
   add_item("third lamp", "@@lamp3_desc");
   add_item("seal", "@@seal_desc");
  add_cmd_item("first lamp", "read", "GLORY\n");
   add_cmd_item("second lamp", "read", "WISDOM\n");
   add_cmd_item("third lamp", "read", "TRUTH\n");
  add_cmd_item("inscription", "read", "@@read_ins");
   
   
  lamp1 = 1;
  lamp2 = 1;
   lamp3 = 1;
   
}

