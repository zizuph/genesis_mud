// The Apothecary Awning
// file name:    /d/Avenir/common/bazaar/intr/apoth.c
// creator(s):   Ilyian, May 1995
// last update:  Lilith, 17Feb97: see below (note)
// purpose:      Herbseller (herbmerchant) is cloned here
// note:         Making additions to the Apothecary shop so it isn't
//               just herbs. Apothecary (apoth1), Potion shop (apoth2) 
// bug(s):
// to-do:

inherit "/std/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "../bazaar.h"

object npc;
string *herbs = HERB_MASTER->query_herbs( ({"boreal","garden"}) );
void reset_room();

void
create_room()
{
    set_short("Apothecary awning, doorway leading east");
    set_long("You stand under a cloth awning marked with archaic "+
        "symbols, just within the entrance to the Apothecary shop. "+
        "Garlands of dried herbs sway in the light breeze, perfuming "+
        "the air with their scents. Bushels of dried grasses and "+
        "leaves crowd the floor, and colourful baskets bulging with "+
        "herbs rest atop them. Curtains of the same material and "+
        "print of the awning have been pulled back to reveal an "+
        "easterly doorway into the shadowy interior of the shop.\n");
    add_item(({"cloth", "awning", "curtains", "material"}), 
        "The cloth is made of fine plant fibre. It is dyed dark "+
        "blue and has archaic symbols in glittering silver and "+
        "gold imprinted on it.\n");
    add_item(({"symbols", "archaic symbols", "print"}), 
        "The symbols are unfamiliar to you, but look like they "+ 
        "may indicate something magical.\n");
    add_item(({"garlands", "dried herbs", "baskets", "basket", 
        "bushel", "bushels", "dried grasses", "leaves"}), 
        "The baskets and bushels are filled with herbs.\n");
    add_item(({"doorway", "east", "interior"}), 
        "Beyond the curtains there is a doorway into the dark "+
        "interior of the building.\n");

	
	IN;       // Avenir is an undergound domain.
	IN_IN;    // Interior room, no flux msgs, steeds etc.


    add_exit(EXTR + "str24","west",0);
    add_exit(INTR + "apoth1", "east", "@@curtains");
    reset_room();
}

void
init()
{
    ::init();
    add_action("do_get",    "get");
    add_action("do_get",    "take");
}

void
reset_room()
{
    if (!npc)
    {
        npc = clone_object(NPC +"herbmerchant.c");
        npc->arm_me();
        npc->move_living("M", this_object());
    }
}
int
curtains()
{
    write("You brush past the curtains and enter the dark, scented "+
        "interior of the apothecary shop.\n\n");
    return 0;
}

int
do_get(string str)
{
    object herb;

    notify_fail("Get what from where?\n");
    if (!str || !strlen(str))    
        return 0;
    
    notify_fail("A strange and unpleasant feeling invades your "+
        "hands, forcing you to release the "+ str +".\n");
    if (parse_command(str, ({ }), "[a] / [the] 'basket' / 'bushel'"))
        return 0;

    if (parse_command(str, ({ }), "[a] / [the] 'herb' / 'herbs' / "+
        "'grass' / 'leaves' [from] [the] 'basket' / 'bushel'"))
    { 
        if (TP->query_prop(AVENIR_BAZAAR_THIEF))
        {
            TP->catch_msg("A burning sensation in your hands! They "+
                "feel like they're on fire!\n");
            TP->heal_hp(-20);
            return 1;
        }           
        else
        {        
            TP->add_prop(AVENIR_BAZAAR_THIEF, 1);
            herb = clone_object(ONEOF(herbs));
            herb->force_dry();
            herb->move(TP, 1);
            TP->catch_msg("You take an herb from the basket.\n");
            return 1;
        }
    }         
}        

            
     