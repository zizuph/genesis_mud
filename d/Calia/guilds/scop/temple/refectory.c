
/*
 * refectory.c
 *
 * Refectory (dining hall) for the Spirit Circle of Psuchae Temple
 * This chamber will sell various foods and water for the members
 *
 * Copyright (C): Jaacar (Mike Phipps), July 30th, 2003
 *
 */
 
#pragma strict_types
#pragma save_binary

inherit "/std/room";
inherit "/lib/pub";

#include <stdproperties.h>
#include <macros.h>

#include "defs.h"

// object caterer;

void
reset_room()
{
    //  if (!objectp(caterer)) { 
    //      caterer = clone_object(SPIRIT_NPCS+"caterer"); 
    //      caterer->move_living("behind the counter", TO); 
    // } 
}

void
create_room()
{
    set_short("Refectory");
    set_long("This chamber is the refectory of this temple. It is here "+
        "so that members of the Circle can nourish themselves. The chamber "+
        "is fashioned of beautifully stained wood. Rows of long tables "+
        "fill the chamber, aside each are long benches. There is a silver "+
        "curtain hanging on the northern section of the east wall.\n");
    
    add_item("counter","There is a counter lining the western wall. Behind "+
        "the counter is the refectory caterer.\n");

    add_item(({"floor","brick","bricks","stone brick","stone bricks",
        "grey stone brick","grey stone bricks","grey brick","grey bricks"}),
        "The floor is made of grey stone bricks placed together.\n");

    add_item(({"wall","walls","ceiling","roof"}),"All of the walls and the "+
        "ceiling are covered in a beautifully stained wood.\n");

    add_item(({"table","tables","bench","benches","long table",
        "long tables","long bench","long benches"}),"There are rows of "+
        "long tables in the chamber and beside each of them are long "+
        "benches (one on each side). They are made of wood and look "+
        "very comfortable.\n");

    add_item(({"curtain","silver curtain"}),"A silver curtain hangs "+
        "on the northern section of the east wall. Upon closer "+
        "inspection you see there is a chamber beyond it and you "+
        "could enter it if you wanted. <enter curtain>\n");
                                   
 //   add_item(({"pricelist","menu"}),"It appears to have the prices of "+
 //       "all of the things you can order here. Perhaps you should "+
 //      "read it.\n");
 //   add_cmd_item("pricelist","read","@@read");
 //   add_cmd_item("menu","read","@@read");
/*    
    add_drink(({"bottle","water bottle","water bottles","bottles","water"}),
        "water","bottle",100,0,12,"bottle of water","bottles of water",
        "It's a refreshing bottle of clear water.\n",0);

    add_drink(({"milk","milk glass","glass","glass of milk","milks",
        "glasses","glasses of milk","milk glasses"}),
        "milk","glass",135,0,15,"glass of milk","glasses of milk",
        "It is an ice cold glass of milk.\n",0);
    
    add_drink(({"jug","water jug","water jugs","jugs","water"}),
        "water","jug",600,0,50,"jug of water","jugs of water",
        "It is a refreshing jug of clear water.\n",0);

    add_drink(({"pot","pot of tea","pots of tea","teas","pots","tea"}),
        "tea","pot",600,0,50,"pot of tea","pots of tea",
        "It is a perfectly steeped pot of tea.\n",0);

    add_food(({"muffin","small muffin","small muffins","small muffin"}),
        "muffin","small", 30, 25, "small muffin",
        "small muffins",
        "It is a small muffin.  It looks very delicious.\n",0);

    add_food(({"cookie","chocolate chip cookie","chocolate chip cookies",
        "chocolate cookie","chocolate cookies","cookies"}),
        "cookie","chocolate chip", 30, 25, "chocolate chip cookie",
        "chocolate chip cookies",
        "It is a chocolate chip cookie.  It looks very delicious.\n",0);

    add_food(({"stick","sticks","bread stick","bread sticks",
        "bread","breads"}),"stick","bread",  65, 80, "bread stick",
        "bread sticks","It is a fresh baked bread stick.\n",0);

    add_food(({"broth","herb broth","broths","herb broths"}),
        "broth","herb", 100,100,"bowl of herb broth","bowls of herb broth",
        "It is a fairly large bowl of herb broth. It looks and smells "+
        "quite delicious.\n",0);

    add_food(({"sandwich","cheese sandwich","sandwiches","cheese sandwiches"}),
        "sandwich","cheese",150,150,"cheese sandwich","cheese sandwiches",
        "It is a cheese sandwich.\n",0);
*/
    IN;
    add_prop(ROOM_M_NO_ATTACK,"You cannot attack in here, you are in a "+
        "sacred place!\n");
    add_prop(ROOM_M_NO_MAGIC_ATTACK,"You cannot attack in here, you are in "+
        "a sacred place!\n");

    add_exit(SPIRIT_TEMPLE+"vestibule","west","@@non_pure",1);
    add_exit(SPIRIT_TEMPLE+"meditation_chamber","east",0,1);
    reset_room();
}
/*
int
order(string str)
{
    if (!objectp(caterer) || !objectp(present(caterer, TO)))  
    { 
        NF("The caterer isn't here!\n"); 
        return 0;
    }

    return ::order(str); 
}

int
read(string str)
{
    write("\n"+
        "    Water Bottle                  12 cc\n"+
        "    Glass of Milk                 15 cc\n"+
        "    Water Jug                     50 cc\n"+
        "    Pot of Tea                    50 cc\n"+
        "\n"+
        "    Small Muffin                  25 cc\n"+
        "    Chocolate Chip Cookie         25 cc\n"+
        "    Bread Stick                   80 cc\n"+
        "    Bowl Of Herb Broth           100 cc\n"+
        "    Cheese Sandwich              150 cc\n"+
        "\n"+
        "Try 'buy water with gold' if you want to specify what\n"+
        "coin type to pay with, or 'buy 10 water' would get\n"+
        "you ten water from the refectory.\n\n");
    return 1;
}
*/

int
do_enter(string str)
{
    NF("Enter what? The curtain perhaps? <enter curtain>\n");
    
    if (!str)
        return 0;
    if (str == "curtain")
    {
        write("You push the curtain aside and make your way past it "+
            "and into the chamber beyond.\n");
        say(QCTNAME(TP)+" pushes the curtain aside and makes "+
            TP->query_possessive()+" way past it and into the "+
            "chamber beyond.\n");
        set_dircmd("curtain");
        TP->move_living("M",SPIRIT_TEMPLE+"statue_chamber");
        tell_room(environment(TP), QCTNAME(TP)+" arrives from behind "+
            "the western curtain.\n",TP);
        return 1;
    }

    return 0;
}

int
non_pure()
{
    if (TP->query_wiz_level())
    {
        write("Normally if you left the sanctity of the temple, "+
            "you would feel that if you wanted to return that "+
            "you would have to purify yourself once again, but since "+
            "you are a wizard, you do not need to worry about that "+
            "anyways.\n");
        return 0;
    }
    
    else
    {
        write("\n\nAs you leave the sanctity of the temple, you feel "+
            "if you wanted to return inside that you would have to "+
            "purify yourself once again.\n\n");
        return 0;
    }
}

void
init()
{
    ::init();
 //   init_pub();
    add_action(do_enter,"enter");
}
