
inherit "/d/Shire/khazad/moria_room";
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/defs.h"
 
create_room()
{
  set_short("Deep within the mining tunnels");
  set_long("You stand deep within one of the many mining tunnels "+
     "that run through the western portion of Khazad-dum. Rough walls "+
     "show signs of mining activity. Loose chunks of rock litter the "+
     "uneven ground. Tunnels branch off here in all four cardinal "+
     "directions.\n");
 
  add_exit("@@which_room@@","north",0,3);
  add_exit("@@which_room@@","south",0,3);
  add_exit("@@which_room@@","west",0,3);
  add_exit("@@which_room@@","east",0,3);
}
 
string
which_room()
{
  int i;
  i = random(6);
  switch (i)
  {
    case 0:
      return "/d/Shire/khazad/west/random_tunnel3";
      break;
    case 1:
      return "/d/Shire/khazad/west/random_tunnel2";
      break;
    case 2:
      return "/d/Shire/khazad/west/random_tunnel1";
      break;
    default:
      return "/d/Shire/khazad/west/random_tunnel";
      break;
  }
}
