// hp2
// grace feb 1995

#include "../local.h"
inherit SPURRM;

object guard;

create_spur_room()
{

   SHORT("Hidden room");
   LONG("Torches placed every few paces along the walls of this "+
      "passage make it bright as day. Numbered crates of all sizes "+
      "are piled in neat rows along the perimeter.\n   A circular "+
      "stairwell leads down into darkness.\n");

   INSIDE;
   LIGHT;

   AE(ROOM + "hp3", "down", 0);
   AE(ROOM + "hp1", "west", 0);
   

   AI(({"floor","stone floor"}),
      "It is so shiny you can see your reflection in it.\n");
   AI(({"crates","crate"}), "The wooden crates are all nailed " +
      "closed, and have words like 'Iron', 'Tools', "+
      "'Torches', and 'Misc' printed on the front.\n");
   ACI(({"crate", "crates"}), ({"open", "smash", "break"}), "You "+
      "are unable to do that at this time.\n"); 
   AI(({"wall", "walls"}), "Smooth dark stone, bare and cool to "+
      "the touch.\n");
   AI(({"reflection", "my reflection"}), "Yes, sure enough, that "+
      "is a distorted image of your face. At least, you hope it "+
      "is distorted. You've seen draconians prettier than that!\n");
   AI(({"stair", "stairwell"}), "It is circular and winds downward.\n");

   reset_spur_room();
}

reset_spur_room()
{
   if (!guard)
      (guard = clone_object(KNIGHT))->move_living(0,this_object());
}
