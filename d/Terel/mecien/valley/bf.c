inherit "/std/monster";
#include <macros.h>
#include <stdproperties.h>

create_monster(){
   set_race_name("butterfly");
   set_name("butterfly");
   set_adj(kind());
   add_adj(colour());
   
   set_gender(2);
   set_alignment(150);
   set_act_time(1);
   add_act("emote lands on you.");
   add_act("emote flutters about.");
   add_act("emote flies in a circle about you.");
   add_act("emote flies around, showing off its colours.");
   add_prop(NPC_I_NO_LOOKS, 1);
   add_prop(OBJ_M_NO_ATTACK, "It is too small and quick!\n");
   set_stats(({ 1, 50, 1, 1, 1, 1}));
   
}

colour(){
   string *colours;
   colours = ({ "red-white", "blue-yellow", "white", "fiery-yellow", 
         "purple-red", "red-black", "silvery", "blue-white", "gold-red",
         "sapphire", "yellow-black"});
   return colours[random(sizeof(colours))];
}
kind(){
   string *kinds;
   kinds = ({ "spotted", "striped", "long-tailed", "royal",
         "heavenly", "mystical", "speckled", "banded" });
   return kinds[random(sizeof(kinds))];
}


