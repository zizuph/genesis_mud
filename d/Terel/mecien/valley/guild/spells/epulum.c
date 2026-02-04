#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Terel/mecien/valley/guild/mystic_defs.h";

#define TO this_object()
#define TP this_player()
#define ENV environment
#define PATH "/d/Terel/mecien/valley/guild/spells/"



epulum(){
   
   int blessed;
   
   
   
   blessed = ENV(TP)->query_prop("blessed");
   
   if(TP->query_mana()<250) return "You do not have the strength.\n";
   if(!present(MYSTIC_MANTLE, TP)) return "You will need the mantle.\n";
   if(!present("sacred_chalice", TP)) return "You will need the chalice.\n";
   
   if(!blessed) return "This place has not been suitably prepared.\n";
   if(!ENV(TP)->query_prop("mystic_presence")) return "The ancient powers must be present.\n";
   if(random(TP->query_skill(SS_FORM_CONJURATION)) +
         random(TP->query_skill(SS_ELEMENT_LIFE)) < 50)
   return "Your call is not heard.\n";
   TP->catch_msg("You wrap your chalice in your mantle, hold it aloft " +
      "and intone the sacred words.\n");
   say(QCTNAME(TP) + " wraps " + TP->query_possessive() +
      " chalice " + "in " + TP->query_possessive() + " mantle, holds it aloft and "
      + "intones some ancient words.\n");
   set_alarm(4.0, -1.0, "winds");
   set_alarm(8.0, -1.0, "shadows");
   TP->add_mana(-250);
   return 1;
}
winds(){
   tell_room(ENV(TP), "The air churns and begins to blow about like wild winds of a storm.\n");
}

shadows(){
   object here;
   here = ENV(TP);
   set_alarm(3.0, -1.0, "lay_cloth", here);
   tell_room(ENV(TP), "Shadows and dark forms begin to dance about in the air all around.\n");
   set_alarm(8.0, -1.0, "servants", here);
   set_alarm(12.0, -1.0, "serve", here);
   set_alarm(15.0, -1.0, "servants", here);
}

servants(object here){
   object spirit;
   spirit = clone_object(PATH + "spectre");
   spirit->move(here);
   tell_room(here, "A spectral image descends from above and stands at the edge of the glorious cloth laid upon the ground.\n");
   set_alarmv(4.0, -1.0, "bring_food", ({ spirit, here }));
   set_alarmv(9.0, -1.0, "bring_drink", ({ spirit, here }));
   set_alarm(80.0, -1.0, "depart", spirit);
}

serve(object here){
   object spirit;
   spirit = clone_object(PATH + "spectre");
   spirit->move(here);
   tell_room(here, "A spectral image rises from below and stands at the edge of the glorious cloth laid upon the ground.\n");
   set_alarmv(4.0, -1.0, "bring_drink", ({ spirit, here }));
   set_alarm(10.0, -1.0, "get_more", spirit);
   set_alarmv(20.0, -1.0, "bring_food", ({ spirit, here }));
   set_alarmv(15.0, -1.0, "bring_drink", ({ spirit, here }));
   set_alarm(60.0, -1.0, "depart", spirit);
}
depart(object spirit){
   spirit->command("bow");
   spirit->remove_object();
}

lay_cloth(object here){
   object cloth;
   cloth = clone_object(PATH + "cloth");
   cloth->move(here);
   set_alarm(4.0, -1.0, "add_more", cloth);
   tell_room(here, "A beautiful spirit descends from above, followed by the " +
      "sounds of trumpets. It lays a glorious cloth upon the ground and quickly departs.\n");
   set_alarmv(150.0, -1.0, "take_cloth", ({ cloth, here }));
}

take_cloth(object cloth, object here){
   tell_room(here, "A darkness begins to form, trumpets sound and the cloth fades from existance.\n");
   cloth->remove_object();
}

bring_food(object spirit, object here){
   object food;
   string item;
   int n;
   
   n = random(6);
   if(n == 0) item = "food1";
   if(n == 1) item = "food2";
   if(n == 2) item = "food3";
   if(n == 3) item = "food4";
   if(n == 4) item = "food5";
   if(n == 5) item = "food6";
   seteuid(getuid());
   food=clone_object(PATH + item);
   food->move(spirit);
   spirit->command("emote raises a hand upward and a light shines down.");
   spirit->command("smile mysteriously");
   spirit->command("put mystic_food in cloth");
   set_alarm(12.0, -1.0, "get_more", spirit);
}

bring_drink(object spirit, object here){
   object drink;
   string item;
   int n;
   
   n = random(6);
   if(n == 0) item = "drink1";
   if(n == 1) item = "drink2";
   if(n == 2) item = "drink3";
   if(n == 3) item = "drink4";
   if(n == 4) item = "drink5";
   if(n == 5) item = "drink6";
   seteuid(getuid());
   drink=clone_object(PATH + item);
   drink->move(spirit);
   spirit->command("emote puts out its hands and pronounces a blessing.");
   spirit->command("put mystic_drink in cloth");
}

add_more(object cloth){
   object food;
  seteuid(getuid());
   food=clone_object(PATH + "food" + (random(6) + 1));
   food->move(cloth);
}

get_more(object spirit){
   object food;
   spirit->command("emote humbles an ancient prayer.");
   food=clone_object(PATH + "food" + (random(6) + 1));
   food->move(spirit);
   spirit->command("put mystic_food in cloth");
}
