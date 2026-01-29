#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include "/d/Krynn/common/warfare/warfare.h"

#include <macros.h>
#include <stdproperties.h>

inherit ICEOUTROOM2;

void
create_icewall_room()
{

    set_short("On the vast snow plains");
    set_long("@@long_descr");

    set_area_name(WAR_AREA_ICEWALL);

    add_exit("snow_plain8","west");
    add_exit("snow_plain11","southeast","@@southeast");

   add_item(({"bay","icy bay"}),"The icy bay is nothing more then a " +
     "deep gouge in the snow-covered coast, offering shelter from the " +
     "mad, cold wind.\n");
   add_item(({"waste","snow waste","snow plains","plains"}),"Frozen. " +
     "Endless. Dangerous. Venture with care...\n");

   set_tell_time(900);

   add_tell("It is hellishly cold, and the wind picks up. Move before " +
    "frostbite kills you... To stay motionless is to die.\n");
}

void

enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}

string

long_descr()

{ return ("" +
   "You are standing on a snow-covered bank. To your " +
   "west, the snow sparkles as far as you can see, but to " +
   "your east, the dark, cold ocean hammers the frozen coast. " +
   "There is a path venturing into a sheltered ice bay here but " +
   "someone crazy enough could venture boldly further, onto " +
   "the great snow waste.\n");
  
}
      
int
southeast()
{ 
  write("You tred downward, into the sheltered ice bay. The wind dies " +
   "down around you.\n");
  say(QCTNAME(TP) + " treds downard, into the sheltered ice bay.\n");
  return 0;
}        