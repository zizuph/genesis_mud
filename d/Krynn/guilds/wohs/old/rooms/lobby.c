/*
   Wayreth.

   lobby.c
   -------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : 96/12/05
   By ...........: Kentari

*/

#include "../guild.h"
inherit TOWERROOM;

void
create_tower_room()
{
   set_short("Central lobby");
   set_long("This sparsely furnished room is a place where you can stop " +
            "to count the money needed in the adjoining rooms. The ceiling " +
	    "is covered in a beautiful mosaic. To the " +
	    "north, the scent of spiced drinks and the soft sound of a lyre " +
	    "drifts towards you through the archway to the inn. To the west " +
	    "is a drugstore, and to the south is a components shop, " +
	    "selling the essentials for any who practice the arts of " +
	    "magic.\n"); 
   AI(("furniture"),
	    "The plain furniture is what makes this room a lobby instead " +
	    "of a corridor.  The few pieces look comfortable enough to " +
	    "take a moments rest in, but as this is a busy place, any " +
	    "comfort would be short lived.\n");   
   AI(({"archway","arch"}),
	    "This is the archway you should go through to get to the inn.\n");
   AI(({"mosaic","ceiling","beautiful mosaic","up"}),
	    "This mosaic is painted so well that it seems to almost " +
	    "possess a life of its own.  It depicts the three gods " +
	    "of magic, Solinari, Lunitari, and Nuitari, giving their " +
	    "first apprentice the keys to the mythical Lost Citadel.\n");
   AI(({"gods","three gods","three","gods of magic"}),
	    "The gods of magic, Solinari, Lunitari, and Nuitari are " +
	    "shown, each bearing a striking resemblance to their " +
	    "brothers, and united by magic.\n");
   AI(({"Solinari","solinari","white moon","white"}),
	    "The patron god of 'good' magic, Solinori glows a soft " +
	    "white as he kindly bestows a key to his beloved " +
	    "apprentice.\n");
   AI(({"Lunitari","lunitari","red moon","red"}),
	    "The patron god of 'neutral' magic, Lunitari flickers with " +
	    "a plain red light as he necessarily gives a key to his random " +
	    "apprentice.\n");
   AI(({"Nuitari","nuitari","black moon","black"}),
	    "The patron god of 'evil' magic, Nuitari emanates a dark " +
	    "black as he thrusts a key into the hands of his submissive " +
	    "apprentice.\n");
   AI(({"apprentice","beloved apprentice","random apprentice","apprentices",
	"submissive apprentice","beloved","random","sumbissive"}),
	    "The receiver of the keys to the mythical Lost Citadel, these " +
	    "apprentices became the founders of the three orders of " +
	    "magic. They all appear in the robes of their respective " +
	    "orders, fully hooded, so the facial feature cannot be made " +
	    "out.\n");
   AI(({"keys","key"}),
	    "These are the keys to the mythical Lost Citadel.\n");
   AI(({"Citadel","Lost Citadel","citadel","lost citadel"}),
	    "Though the keys are apparent, the actual Citadel is not " +
	    "shown in the mosaic.\n");

   add_exit("inn", "north", 0);
   add_exit("stairwell05", "east", 0);
   add_exit("components", "south", 0);
   add_exit("shop", "west", 0);
}
