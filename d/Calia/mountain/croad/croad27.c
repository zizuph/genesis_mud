/*  Crystalline road on the plateau atop Mount Kyrus
    Maniac 27/3/95 
    Modified, Maniac, 10/5/95, 19/9/95
    Magical unlock and open for kroug raids added, Maniac, 28/9/95
   exits to garden added, 24/2/96, Maniac
*/

inherit "/d/Calia/std/kr_room";

#include <macros.h>
#include "crdefs.h"

inherit SLIP;

object door;

void
create_room()
{
    set_short("Crystalline Palace Gates");

    set_long("You stand before the gates of the crystalline Palace of " +
        "Caliana, which are set in the south walls of the " +
        "massive building. Towering and mist-enshrouded, the palace " +
        "is set at the centre of the plateau, and can truly be said " +
        "to crown the mountain. The palace walls rise in front of " +
        "you to a great height. " +
        "A few yards in front of the gates, a flag, mounted on a tall " +
        "steel flagpole, flutters proudly in the breeze. On either " +
        "side of it are the Calian battle standards. To your south, " +
        "the crystalline road leads towards southern mountain side.\n");

    add_item(({"flag"}), "The flag depicts the very Crystalline " +
               "Palace that it is mounted in front of, a monument " +
               "to the rise and defence of free civilisation over " +
               "barbarism and tyranny.\n");    

   add_item(({"standards", "standard", "battle standard", 
              "battle standards", "calian battle standard", 
              "calian battle standards"}),
             "You see two tall battle standards. One depicts a noble " +
             "grey wolf, the other a swarm of bees.\n");

    add_item(({"mist", "pale mist"}), "A thin pale mist is all about " +
        "you since you are now at quite a high altitude. One cannot " +
        "see far above or below from here.\n");

    add_item(({"palace", "crystalline palace", "palace of caliana"}),
       "The palace is fortified and very grand in appearance. Made of " +
       "crystal, it glitters in the light, giving it a somewhat magical " +
       "air.\n");

    add_item(({"road", "crystalline road"}), "The road surface is made " +
         "of crystal. The path on which it was based is very ancient, " +
         "perhaps thousands of years old.\n");

    add_item(({"view"}),
        "A pale mist hangs in the air at this high altitide. " +
        "The mist is stopping you " +
        "from seeing the view of the lands below from here; " +
        "a pity as it would surely be magnificent from this " +
        "height.\n");

    add_item(({"plateau"}), "You are currently on the plateau " +
        "at the top of Mount Kyrus, which is roughly elliptical " +
        "in shape and some three hundred yards across at its longest. " +
        "The surface of the plateau appears to have " +
        "been artificially levelled, and a crystalline road " +
        "runs along it towards the Palace of Caliana, which is " +
        "immediately to your north.\n");

    door = clone_object(CROAD + "doors/crystalline");
    door->move(THIS);
    add_exit(CROAD+"croad26","south", "@@slip");
    add_exit(CROAD+"garden1", "west", "@@slip");
    add_exit(CROAD+"garden13", "east", "@@slip");
}


void
kroug_raid_open_door()
{
    object door2;

    if (!objectp(door))
        return;
    door2 = door->query_other_door();
    if (door->query_locked()) { 
        door->do_unlock_door("Kroug appears, casts a spell on the lock " +
                        "of the door, gives an evil grin, and vanishes.\n");
        door2->do_unlock_door("With a flash of black magic, " +
                              "the doors unlock!\n");
   }
   if (!door->query_open()) {
       door->do_open_door("The doors burst open!\n"); 
       door2->do_open_door("The doors burst open!\n");
   }
}


