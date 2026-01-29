/* Ashlar, 5 Jul 97 - The Red Dragon Tavern */

#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>

inherit INNER_IN;
inherit "/d/Ansalon/lib/pub";

object ob, barkeeper = 0;
object off,m1,m2;

void
reset_neraka_room()
{
    if (!objectp(barkeeper))
    {
        barkeeper = clone_npc(NNPC + "pbarkeep1");
        set_barkeeper(barkeeper);
    }
    
    if (!objectp(off))
        off = clone_npc(NNPC + "humcaptain",({"black","red","blue"})[random(3)]);
    if (!objectp(m1))
        m1 = clone_npc(NNPC + "minotaur");
    if (!objectp(m2))
        m2 = clone_npc(NNPC + "minotaur");
}

void
create_neraka_room()
{
    set_short("the Red Dragon Tavern");

    set_long("This is a tavern in the city of Neraka. Smoke from the " +
        "fireplace hangs in the air below the high ceiling. A menu " +
        "hangs in a frame on one wall, and a couple of tables with " +
        "benches for seats, are placed in the middle of the room. " +
        "Since the floor of the tavern is below the level of the " +
        "street outside, there are a few steps leading up to the front " +
        "door to the north.\n");

    add_item(({"door","front door"}),"The front door is sturdy, made of " +
        "thick oak planks. It bears the marks of several boots and not a " +
        "few weapons.\n");
    add_item(({"steps","stone steps"}),"The stone steps are worn from a " +
        "multitude of boots. They lead up to the front door.\n");
    add_item("frame","It is a simple wooden frame, and it holds the menu.\n");
    add_item_inside();
    remove_item("ceiling");
    add_item(({"ceiling","beamed ceiling"}),
        "The beamed ceiling is rather high, and covered in thick smoke.\n");
    add_item("fireplace","A fireplace is set in one corner of the room. " +
        "A fire burns in it, spreading warmth and smoke into the room.\n");
    add_item("fire","The fire burning in the fireplace gives warmth to " +
        "the room. It is crackling and sizzling.\n");
    add_item("smoke","The smoke which is thicker at the ceiling stings " +
        "your eyes a bit.\n");

    add_item(({"patrons","patron"}),"The patrons seem to be enjoying " +
        "their food and drink.\n");

    add_item(({"pricelist","menu"}),
        "It contains some words.\n");
    add_cmd_item(({"pricelist","menu"}),({"read"}),
        ({"@@read_pricelist@@"}));
    add_item(({"table","tables"}),
        "The tables are made of thick oak planks. They are none too clean.\n");
    add_item(({"bench","benches"}),"The benches are made of wooden planks. " +
        "They provide seating at the tables.\n");

    add_exit(NINNER + "r15","north","@@go_north");

    add_drink_object(({"ale","ales","mug of ale","mugs of ale"}),
        NOBJ + "drink/ale1", 17);
    add_drink_object(({"wine","wines","red wine","red wines"}),
        NOBJ + "drink/redwine", 70);
    add_drink_object(({"brandy","brandys","brandies",
        "apple brandy","apple brandys","apple brandies"}),
        NOBJ + "drink/applebrandy", 180);

    reset_room();
}

int
go_north()
{
    write("You walk up the steps and exit the tavern.\n");
    return 0;
}

string
read_pricelist()
{
    return "\n+-----------------------+\n" +
           "| The Red Dragon Tavern |\n" +
           "|                       |\n" +
           "| Ale             17 cc |\n" +
           "| Red wine        70 cc |\n" +
           "| Apple brandy   180 cc |\n" +
           "+-----------------------+\n";
}


/*
* Function name: init
* Description:   Initalize the pub actions
*/
void
init()
{
    ::init();
    init_pub();
}

