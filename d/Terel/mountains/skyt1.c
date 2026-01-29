

inherit "/std/room";
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>


init(){
   add_action("pray", "pray");
   ::init();
}

pray(string str){
   int hm;
   if(!str){
      write("You feel the spirits of the winds close at hand.\n");
      return 1;
   }
   if(str == "to the sky"){
      if(this_player()->query_alignment()<100){
         write("A voice from the sky intones: You are unworthy to be here!\n");
         write("A streak of lightning descends from the sky striking you!\n");
         say(QCTNAME(this_player()) + " is struck by a bolt of lightning.\n");
         hm=this_player()->query_hp();
         this_player()->heal_hp(-hm/2);
         return 1;
      }
      write("The silver door opens and a wind ushers you inside.\n");
      this_player()->move_living("enters the tower followed by a forceful wind", "/d/Terel/mountains/skyt2");
      return 1;
   }
}

create_room(){
   
   set_short("Tower of the Sky");
   set_long(
      "Hovering at the edge of this icy cliff, a ornate white tower\n"
      +"rises upwards into the mists. Bits of ice hang from its craggy\n"
      +"stones and supports. A silver arched door leads into the tower,\n"
      +"upon it are many runes.\n"
   );
   
   add_prop("_can_summon_the_air", 2);

  add_item("door", "It is ornate silver and has runes upon it.\n");
  add_item("tower", "It is made of white craggy stone, it looks very\n"
   + "ornate with its spiralling minarets.\n");
  add_item("minarets", "They are almost hidden by the clouds.\n");
  add_item("cliff", "Its a long way down!\n");
   add_cmd_item("door", "open", "It will not open.\n");
   add_cmd_item(({"door", "runes"}), "read", "@@read");
   
}

read(){
   if(this_player()->query_skill(SS_LANGUAGE)<30){
      write("It is obscure.\n");
      return 1;
   }
   write("Pray to the sky and entrance shall be given to thee.\n");
   return 1;
}

