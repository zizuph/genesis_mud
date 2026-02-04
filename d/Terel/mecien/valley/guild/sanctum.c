/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
#define PATH "/d/Terel/mecien/valley/guild"
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>


reset_room(arg){
   
   object elder;
   if(present("elder")) return;
   elder=clone_object("/d/Terel/mecien/valley/guild/elder");
   elder->move(this_object());
   
}

init()
{
   add_action("pray", "pray");
   ::init();
}

id(str) {
   return str == "mist";
}

pray()
{
   write("You find peace in praying here.\n");
   write("The ancients abide here, you feel closer to them.\n");
   say("In great reverence "+QCNAME(this_player())+" kneels down and prays.\n");
   return 1;
}

create_room(){
   
   set_short("Sanctum");
   set_long(
      "This chamber is dominated by the presence of a large statue\n"
      +"that stands upon an emerald dias. An arch of ivory, set with\n"
      +"rubies and sapphires, rises over the statue.\n"
      +"The walls themselves are imprinted with script, the words\n"
    +"being those of the ancients, lost in time, unknown to mortals.\n"
      +"The ceiling rises to a dome, which is covered with crystals,\n"
      +"set acurately to depict the constellations. A moon, made of\n" 
      +"ivory, is in the center of the dome.\n"
      +"Upon the floor is set a tile mosaic of an immense tree, some\n"
      +"of which is made of jade. In the center of the mosaic is an\n"
      +"inscription in silver letters.\n");
   add_prop(ROOM_I_NO_ATTACK, 1);
   
   add_exit("/d/Terel/mecien/valley/guild/guild", "south", 0);
   
   add_item("statue","It is a woman, wrapped in red with a green garland.\n");
   add_item(({"tree","mosaic"}), "It is a tree of great majesty.\n");
   add_item("dias","It is two meters in diameter, a single stone.\n");
   
   add_item(({"ceiling", "dome"}), 
    "It has been set with crystals to depict the constellations.\n");
   add_item("floor", "It is covered with a huge tile mosaic.\n");
   add_item(({"inscription","letters"}),
      "Strange gothic letters that form three words.\n");
   add_cmd_item(({"letters", "inscription"}),
      "read", "WISDOM GLORY TRUTH\n");
   reset_room();
}

int guarded(){
   object rat;
   rat=present("rat");
   if(rat && rat->query_name()!="corpse"){
      write("The nasty rat guards the way.\n");
      say("The rat keeps "+QCNAME(this_player())+" from going any further.\n");
      return 1;
   }
   return 0;
}
