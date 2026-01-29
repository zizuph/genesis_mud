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

    set_short("West end of the grand hall");
    set_long("@@long_descr");


    add_exit("hall1","east");

   add_item(({"columns","column"}),"Smooth, grey, and as thick as " +
    "an ancient tree, they support the walls, giving the hall a " +
    "certain grandur. They have weathered the time quite well.\n");
   add_item(({"remains","statues","statue"}),"By the sad remains left " +
    "in the niches you realise that the statues represented platemail " +
    "clad warriors and robed clerics, or perhaps magic users of old. " +
    "Who they were, or why were they depicted here, only a historian " +
    "of Palanthas could say.\n");
   add_item(({"niche","niches"}),"The niches set in the north and south " +
    "walls house the sad remains of many life-size statues.\n");
   add_item("altar","Of what God or Gods, you cannot say, though " +
    "the minotaurs worship Sargonnas and would rebel should anyone " +
    "try to destroy his altar. Noone has yet established what " +
    "the thanoi believe in, except plunder and murder.\n");
   add_item(({"wall","walls"}),"Which wall do you wish to examine " +
    "closer? South, west, or north?\n");
   add_item("south wall","A wall as many others. You see nothing " +
    "special about it... though there are ways to check for hidden " +
    "rooms. Like simply knocking on the wall.\n");
   add_item("west wall","A wall as many others. You see nothing " +
    "special about it... Except of course for the remains of " +
    "the mysterious altar. There are ways to check for hidden " +
    "rooms - like simply knocking on the wall.\n");
   add_item("north wall","A wall as many others. You see nothing " +
    "special about it... though there are ways to check for hidden " +
    "rooms. Like simply knocking on the wall.\n");

   set_tell_time(900);

   add_tell("You hear some footsteps above you, on the second floor " +
    "of the lower building.\n");
   add_tell("You think you have just heard a muted, and barely " +
    "audible scream of anguish from behind one of the walls... " +
    "strange. It could be the cold playing tricks with your mind.\n");
 
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
   "This is the grand hall of the Icewall Castle. Here, among the " +
   "marble columns supporting the walls and niches housing beautiful " +
   "statues lord of the castle held important ceremononies. The " +
   "floor of the hall has been laid out with white and black marble " +
   "set in a complicated pattern. Long ago, the hall must have been " +
   "decorated with banners and colorful cloth, but today they are " +
   "long gone, decayed and crumbled to dust. Most of the statues " +
   "are missing as well - looted, or most likely destroyed. Only " +
   "the smooth columns managed to survive the test of time. The " +
   "east wall is marred by the broken remains of an altar. Someone " +
   "has methodically destroyed it, and cleared away the debris. " +
   "The hall continues to the east.\n");
  
}


int
knock(string str)
{
    if(str == "on south wall")
      {
        write("You knock soundly on the south wall, but no hollow " +
         "sound accompanies your test.\n");        
        say(QCTNAME(TP) + " knocks soundly on the south wall, but " +
         "no hollow sound accompanies the test.\n");
        return 1;
      }

    if(str == "on west wall")
      {
        write("You knock soundly on the west wall, but no hollow " +
         "sound accompanies your test.\n");        
        say(QCTNAME(TP) + " knocks soundly on the west wall, but " +
         "no hollow sound accompanies the test.\n");
        return 1;
      }

    if(str == "on north wall")
      {
        write("You knock soundly on the north wall, and faint hollow " +
         "sound rings out in response.\n");        
        say(QCTNAME(TP) + " knocks soundly on the north wall, and " +
         "faint hollow sound out in response.\n");
        tell_room(ROOMSK + "treasury", "A faint sound " +
         "of knocking resounds, as if someone was banging on the " +
         "south wall from the other side.\n");
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
              