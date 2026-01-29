/* Castle_room06-The Kitchen.
 * Coded by Marisol (09/06/98)
 * Copyright (c) Marisol Ramos 1998
 */

#pragma strict_types
#include "../defs.h"
inherit CASTLE_OV;

void
create_castle_room()
{
    set_short("The Kitchen");
    set_em_long("As you enter this room, you feel the heat coming "+
        "from the brick stoves set in one of the walls. The smell "+
        "of bread and roasts waft deliciously to your nose. Pots "+
        "and pans hang in metal hooks or are being used to cook "+
        "the next meal. There is a brick chute over the stoves to "+
        "take out the smoke and steam out of the kitchen. A big, "+
        "long table is set along one of the walls and all kind "+
        "of vegetables are scattered, together with knives and bowls. "+
        "The kitchen helpers with the chef are working frantically "+
        "oblivious of your present.\n");

    add_item("brick stoves",
        "Four big square brick stoves are line up in the wall. All "+
        "of them have a iron door that open inside their respective "+
        "ovens. Each of them have four burners where pots and pans "+
        "are being used for the next meal. A delicious smells of baked "+
        "bread, roast beef and delicate sauces are coming from the "+
        "burning stoves and ovens.\n");

    add_item(({"pots", "pans"}),
        "Copper pots and iron pans are all around in the kitchen. "+
        "Some are hanging from metal hooks and other are being used "+
        "to cook the next meal for the Lord and his courtiers.\n");

    add_item(({"walls", "chute"}),
        "Brick and mortar walls enclosed the kitchen. In one of the "+
        "red walls, over the stoves, a brick chute rise up to the "+
        "ceiling, carry with it smoke and steam from the kitchen. "+
        "Small windows are set in both side of the brick chute but "+
        "they are useless to bring light inside the kitchen. Black "+
        "debris covers the outside of the windows. So torches are "+
        "lighted to bring the light necessarily to cook here.\n");

    add_item("table",
        "A long, big, rectagular, dark-wooden table. It looks very "+
        "sturdy. A variety of vegetables and kitchen tools are "+
        "spread all along its surface.\n");

    add_item(({"vegetables", "kitchen tools"}),
        "You see lettuces, tomates, potatoes, turnips, broccolies, "+
        "onions, garlic' heads and some exotic veggies that you "+
        "don't recognize. Along side these vegetables there are "+
        "chef, carving and veggie knives, copper and wooden bowls, "+
        "rolling pins and measuring cups.\n");

    add_item("lettuces",
        "These are green, luscious, iceberg lettuce heads.\n");

    add_item("tomates",
        "These are bright, juicy, red tomatoes.\n");

    add_item("potatoes",
        "These are exotic purple and green potatoes imported from far "+
        "away.\n");

    add_item("turnips", 
        "Big bulbous white and brown turnips.\n");

    add_item("broccolies",
        "Many emerald-green broccoli's flower' heads.\n");

    add_item("onions",
        "These are red-purple sweet onions, the prize of the kitchen.\n");

    add_item("garlic",
        "These are white-paper garlic heads.\n");        

    add_item(({"knives", "chef, carving and paring knives"}),
        "There are an assortment of knives in the table. A big "+
        "triangular bladed chef knife for multiple uses. A slender "+
        "bladed carving knife to cut meats and roasts and a small "+
        "bladed veggie knife to cut vegetables.\n");

    add_item(({"copper and wooden bowls", "bowls", "copper bowls", 
            "wooden bowls"}),
        "There are two different kind of bowls used in the table. "+
        "Really fancy copper bowls large and wide-mouthed to do "+
        "cake mixes and sauces. And big and smalls wooden bowls to "+
        "be used for the rest of the cooking.\n");

    add_exit("castle1_03", "west");
}
