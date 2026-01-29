inherit "/d/Shire/room";

#include "/d/Shire/common/defs.h"
#include "/sys/stdproperties.h"


create_room() {
   set_short("Dark room in the downs");
   set_long(
      "You are inside the Barrow downs. There "
      + "is a slight draft along the floor. It "
      + "smells like a three month old open grave. "
      + "You can still see the remains of the poor "
      + "creatures that have been locked up inside "
      + "this hellish place.\n");
   
   add_item(({"remains"}),
      "These are fragments of bones, all that remain "
      +"of some long-dead mortal.  You can see big "
      +"teeth marks on the bones, where something or someone "
      +"has been chewing.\n");
   
   add_exit(DOWNS_DIR + "stone4_1", "west");
   add_prop(ROOM_I_INSIDE,1);
   add_prop(ROOM_I_LIGHT,0);
   reset_room();       
}

init()
{
   ::init();
   add_action("do_smell","smell");
}


do_smell(string str)
{
   if (str=="air")
      {
      this_player()->command("puke");
      return 1;
   }
   write("Smell what?\n");
   return 1;
}

reset_room() {
   int i;
   object ghast;    
   if (!present ("ghast")){
      for (i=1; i<=3; i++ ) {
         ghast=clone_object(DOWNS_DIR+"npc/r_ghast")->move(TO);
         tell_room(TO,"A nasty ghast arrives.\n");  
       };
   };
}

