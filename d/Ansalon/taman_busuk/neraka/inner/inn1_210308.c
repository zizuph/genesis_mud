/* Ashlar, 5 Jul 97 - The Swan and Hedgehog Inn */
/* Trading code taken from Inn in solace, coded by Nick */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

inherit INNER_IN;
inherit "/d/Ansalon/lib/pub";

object ob, barkeeper = 0;
object d1,d2;

string  *block_serve_race = ({ "goblin", "orc", "draconian" });

void
reset_neraka_room()
{
    if (!objectp(barkeeper))
    {
        barkeeper = clone_npc(NNPC + "ibarkeep1");
        set_barkeeper(barkeeper);
    }
    
    if (!objectp(d1))
        d1 = clone_npc(NNPC + "humlieutenant","green");
    if (!objectp(d2))
        d2 = clone_npc(NNPC + "humlieutenant","green");
}

void
create_neraka_room()
{
    set_short("the Swan and Hedgehog Inn");
	
    set_long("You are standing in a small inn in the city of Neraka. " +
        "A number of tables and benches are placed in the common room, " +
        "and a bar counter is placed in one end of the room. Some " +
        "patrons are sitting at the tables, drinking and eating.\n");

    add_item(({"counter","bar counter"}),
        "An old and scratched counter, it has a pricelist on top of it.\n");

    add_item(({"patrons","patron"}),"The patrons seem to be enjoying " +
        "their food and drink.\n");

    add_item(({"pricelist","menu"}),
        "It contains some words.\n");
    add_cmd_item(({"pricelist","menu"}),({"read"}),
        ({"@@read_pricelist@@"}));
    add_item(({"table","tables"}),"The tables are a bit dirty.\n");
    add_item(({"bench","benches"}),"The wooden benches provide seating " +
        "at the tables.\n");
    add_item_inside();

    add_exit(NINNER + "r2","east");
    add_exit(NINNER + "r3","south");

    add_drink_object(({"ale","ales","tankard","tankards"}),
        NOBJ + "drink/ale2", 15);
    add_drink_object(({"wine","wines","red wine","red wines"}),
        NOBJ + "drink/redwine", 72);
    add_drink_object(({"gin","gins","sprout gin","sprout gins"}),
        NOBJ + "drink/sproutgin", 150);
        

    reset_room();
}

string
read_pricelist()
{
	return "The menu reads:\n\n" +
	    "Tankard of ale         15 copper\n" +
	    "Red wine               72 copper\n" +
	    "Sprout gin             150 copper\n";
}


/*
* Function name: init
* Description:   Initalize the pub actions
*/
void
init()
{
    ::init(); /* Since it's a room this must be done. */
    init_pub();
}


