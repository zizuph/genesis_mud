inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>

#define TO  this_object()
#define TP  this_player()

init_living()
{
   ::init_living();
   add_action("do_ask", "ask");
}

do_ask(string what)
{
   string s, dum;
   object ob;

   if (!what || !parse_command(lower_case(what), environment(),
       " %o %s ", ob, s)) {
      return 0;
   }
   if (ob != TO) return 0;
   if (sscanf(s, "about %s", dum) == 1) s = dum;
   if (sscanf(s, "for %s", dum) == 1) s = dum;

   if (TP->query_alignment()<50) {
      TO->command("say Your heart has little of good in it, go away...");
      return 1;
   }

   if(s=="waters"){
    TO->command("say It is within the waters that the Keeper resides");
   return 1;
   }
  if(s=="shrine"){
TO->command("say The shrine is in the mountains to the west...");
return 1;
}
    if(s=="ancient order"){
    TO->command("say Indeed, the Shrine is the home of the Ancients");
    return 1;
    }
   if(s=="door"){
    TO->command("say To enter the door you will need the sacred key!");
    return 1;
     }
    if(s=="mystics" || s=="ancient ones") {
    TO->command("say They are members of the Ancient Order");
     return 1;
    }
   if(s=="star"){
    TO->command("say It is the sign of the Order");
    TO->command("say It stands for Truth and Wisdom");
     return 1;
      }
     if(s=="entrance"){
       TO->command("say The door to the great shrine is locked");
     return 1;
    }
  if(s=="key"){
   TO->command("say The shrine key is with the great keeper");
   return 1;
    }
     if(s =="blessing"){
       TO->command("say Seek the Temple of Calathin");
   return 1;
   }
   if(s=="keeper"){
   TO->command("say The keeper lives in the waters");
   TO->command("say Be kind and bring the keeper some luvico");
        TO->command("say Pray so the keeper can hear you");
   return 1;
    }
   if(s=="luvico"){
    TO->command("say Luvico is a sacred bush that grows in the icy peaks");
   TO->command("say It is not an easy thing to find and pick");
   TO->command("say You must be gentle with such sacred things");
   return 1;
   }
   if(s=="leaf"){
    TO->command("say It is good to have the leaf blessed");
    TO->command("say You can make a prayer to the Ancient Ones");
    return 1;
    }
 TO->command("say I have no idea what you are asking me...");
TO->command("smile");
return 1;
}

create_monster(){

set_race_name("faun");
set_name("gildiyus");
set_short("faun");
set_long(
"A beautiful and graceful creature, a young elvish looking man with\n"
+ "the legs of a deer and small goat-like horns. He has reddish\n"
+ "hair, both on his legs and head. His body is thin and pale,\n"
+ "but strong and swift. His face is mesmerizing and he looks to know\n"
 + "many things, his eyes a golden color.\n"
);

set_stats(({ 43, 103, 76, 99, 108, 72 }));
set_alignment(534);

set_all_attack_unarmed(55);
set_all_hitloc_unarmed(50);

set_chat_time(2);
add_chat("Wisdom is my life");
add_chat("I know many things... I might help you");
add_chat("Seek the shrine for the greater wisdom and truth...");
add_chat("Ask me anything you like");

set_act_time(5);
add_act("giggle");
add_act("smile");
add_act("grin");
add_act("bounce");

}
