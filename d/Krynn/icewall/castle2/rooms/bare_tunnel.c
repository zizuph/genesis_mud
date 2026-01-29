#pragma strict_types
#include "/d/Krynn/icewall/castle2/local.h"
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"

#include <macros.h>
#include <stdproperties.h>
 
inherit ICEINROOM;

void
create_icewall_room()
{

    set_short("Short, empty tunnel");
    set_long("@@long_descr");

    add_prop(ROOM_M_NO_TELEPORT, "Dark magical protections prevent you from "+
               "teleporting to that location.\n");

    add_exit("library_secret","east");
    add_exit("treasury","west");

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
   "This is a short and unremarkable tunnel, a secret passage " +
   "created by the old lords of the Icewall Castle for their " +
   "own private purpose. It is rumoured, for not many wander " +
   "around castles, that such secret spaces can be easily " +
   "discovered by soundly knocking on a suspicious wall. The " +
   "tunnel opens up into chambers both to your east and west, " +
   "and is illuminated by a soft, magical glow.\n");
  
}


int
knock(string str)
{
    if(str == "on north wall")
      {
        write("You knock soundly on the north wall, but no hollow " +
         "sound accompanies your test.\n");        
        say(QCTNAME(TP) + " knocks soundly on the north wall, but " +
         "no hollow sound accompanies the test.\n");
        return 1;
      }

    if(str == "on south wall")
      {
       write("You knock soundly on the south wall, and faint hollow " +
         "sound rings out in response.\n");        
       say(QCTNAME(TP) + " knocks soundly on the south wall, and " +
         "faint hollow sound out in response.\n");
       tell_room(ROOMSK + "hall1", "A faint sound " +
         "of knocking resounds, as if someone was banging on the " +
         "north wall from the other side.\n");
       return 1;

      }

    notify_fail("Knock on which wall?\n");

    return 0;
}
 
void
init()
{
    ::init();

    add_action(knock, "knock");

}
              