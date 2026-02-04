/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
inherit "/std/room";
#include <macros.h>
#include <stdproperties.h>

#define GUILD "The Ancient Mystic Order"
#define PATH "/d/Terel/mecien/valley/guild/"

create_room(){
   
   set_short("Bell Tower");
   set_long("High up into the misty sky, looking out into the rocky\n"
      + "cliffs, this tower room houses the great bells of the\n"
      + "shrine. Large copper bells set into stone frames taking up\n"
      + "most of the space in the tower, they rest like sleeping\n"
      + "giants awaiting the time of their glory. Long rectangular\n"
      + "windows provide the view of the mountains and of the valley\n"
      + "down below. The walls are deep grey stone and appear to be\n"
      + "rather worn, but still strong.\n"
   );
   
   add_item("valley", "Far below to the east can be seen the great"
      + " valley. It is\n mostly forest, but a lake is in its center.\n");
   add_item(({"bells", "bell", "copper bells"}),
      "These copper bells are four in number, they symbolize the\n"
      + "circle and are mounted on stone frames.\n"
      + "They are green with age and seem very worn. From them a\n"
      + "strange and wondrous feeling emanates, a mystical power\n"
      + "that arouses spirits.\n");
   add_item(({"frames" , "stone frames", "frame"}),
      "These tall stone frames form a small circle and from\n"
      + "them hang the great bells. A cord hangs in the center of\n"
      + "them and is attached to the bells.\n");
   add_item("walls", "They are made of small grey stones.\n");
   add_item("cord", "It looks very strong. It hangs from the center frame.\n");
   add_cmd_item("cord", "pull", "@@ring_bells");
   add_cmd_item("cord", "cut", "It is impervious.\n");
   
   add_item("stairs", "A spiral staircase leading down the tower.\n");
   add_my_desc("A spiral staircase leads down.\n");
   add_exit(PATH + "tower3", "down", 0);
   
}

ring_bells(){
   object *userlist, sec, inv;
   int i, n;
   string dom;
   
   if(this_player()->query_guild_name_occ()!=GUILD){
      write("The ancient bells do not seem to move.\n");
      return 1;
   }
   write("You pull the chord of the ancient bells.\n");
   write("They slowly begin to move.\n");
   write("The bells ring like the voices of the ancients.\n");
   userlist = users();
   for (i = 0; i< sizeof(userlist); i++)
   if (userlist[i]->query_guild_member(GUILD) &&
         present("Mystic_ring", userlist[i]))
   tell_object(userlist[i], 
      "You hear the ancient bells of the sacred shrine sounding.\n");
   
   return 1;
}

