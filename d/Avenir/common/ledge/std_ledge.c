
// (std_ledge.c)           Standard room for ledge area
// creator(s):  Ilyian  Jan 95
// last update:
// purpose:     Inheritable room for ledge area
//
// note:
// bug(s):
// to-do:

inherit "/std/room";
#include "ledge.h"

/*
 * This function defines the room.
 */

varargs void
make_the_room(string extra_long)
{
    if (!extra_long) { extra_long = "\n"; }


    LONG("You are travelling along an extremely steep and narrow "+
       "ledge that runs along the cliff face to your west." + extra_long);

        AI(({"cliff","wall","walls"}),"The wall of the cliff rises "
         +"high above you to your west, ending at a ledge over which "
         +"a small amount of mist is gently flowing down. The wall is "
         +"roughly hewn stone, but definitely man made, and seems to have "
         +"been carved out fairly recently.\n");

        AI(({"ceiling","rocks"}),"To the east, high above you, you can "
         +"see the enormous cavern "
         +"ceiling that stretches over all of the land. It seems to be "
         +"criss-crossed by veins of some substance that sheds a dazzling "
         +"white light. The veins seem more prominent on the eastern "
         +"reaches of the ceiling, many leagues away.\n");

        AI(("mist"),"A thin sheen of white mist gently pours down "
         +"from the top of the cliff above you, coating everything "
         +"in a glistening layer of water.\n");

        AI(({"floor","ground"}),"The ledge beneath you runs down "
         +"at a frighteningly steep angle. It is slippery as well, "
         +"making your footing treacherous and reminding you "
         +"that a fall would mean your death.\n");

        AI(({"ledge","dropoff"}),"Merely looking over the dropoff "
         +"gives "
         +"you a terrifying sense of vertigo. The cliff falls hundreds "
         +"of meters down to a great sea in which appear to be islands. "
         +"The entire great cavern is lit by strange phospherescent veins "
         +"that run through the ceiling. A narrow path has been carved "
         +"out of the cliff below you, winding steeply downwards to "
         +"the southern part of the cavern.\n");

        AI(({"veins","light","glow"}),"The veins seem to be more "
         +"clustered to the "
         +"eastern end of the cavern, but elsewhere they are "
         +"fairly evenly "
         +"distributed. The light gives an unearthly glow to everything, "
         +"reminding you that you are in the sunless realms, far from the "
         +"light of day.\n");

        AI(({"sea","ocean","water","waters"}),"The great "
         +"underground sea stretches out "
         +"hundreds "
         +"of meters beneath you, making for a breathtaking sight. "
         +"Throughout the sea are islands of various sizes, and you can "
         +"even make out a ship or two travelling across the waters. The "
         +"light from above does not penetrate the sea, making it a heavy "
         +"shade of black.\n");

        AI(({"island","islands"}),"There are a number of islands of various "
         +"shapes and sizes far beneath you in the sea. From this height "
         +"you can make out few details, but one larger island in the "
         +"centre seems to contain a city, while others appear to be "
         +"green with forests and vegetation.\n");

        add_cmd_item (({"ledge","off","cliff","down"}), ("jump"),
         ("As you approach the edge, you are overcome by a paralyzing "
           +"sense of vertigo, and cannot make yourself jump off.\n"));


    IN
    LIGHT
}

