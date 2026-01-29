/*
 * The gift wrapping and delivery shop of Frogmorton.
 *
 * This shop was originally in Kalad and presumedly coded by Sarr
 * but brought over by Finwe and the delivery service was added.
 * --Finwe, November 2001
 */

inherit "/std/room";
inherit "/lib/trade";
#include "/d/Shire/sys/defs.h"
#include "/d/Shire/hobbitmaker/hobbitmaker.h"
#include "defs.h"
#include <macros.h>
#include <money.h>
#include <stdproperties.h>

#define NUM sizeof(MONEY_TYPES)
#define MORE(x)   this_player()->more(read_file(x,2))
#define FROG_DIR  "/d/Shire/frogmorton/"

void
create_room()
{
    set_short("Frogmorton Gift Wrapping Service");
    set_long("This is the headquarters for the Shire Gift " +
        "Wrapping Service. Is is a busy place where hobbits come " +
        "from all over to drop of gifts to be wrapped and " +
        "delivered. A large table sits in the center of the room " +
        "behind a counter. It is so popular that it is busy all " +
        "the time.\n");
    add_item("counter",
        "it is made of wood and spans the length of the room. It " +
        "protects the back of the shop from the customers.\n");
    add_item("walls",
        "The walls decorated with an assortment of wrapped gift " +
        "boxes, showing off the expertise of the shop. A sign and " +
        "a poster are posted on the wall near the table.\n");
    add_item("table",
        "The table is huge and heavy. It is made of solid wood " +
        "and covered with wrapping paper and bows.\n");
    add_item(({"wrapping paper", "paper"}),
        "The wrapping paper is bright and an assortment of " +
        "colors and patterns. It is used to wrap gifts.\n");
    add_item(({"bows"}),
        "The bows are made of different materials and used to " +
        "decorated wrapped gifts. The bows come in an assortment " +
        "of colors and patterns.\n");
    add_item("rack",
        "The rack is made of wood and set against a wall. It has many slots  where rolls of wrapping paper and bows are stored.\n");
    add_item(({"materials"}),
        "The materials are stiff wrapping paper and formed in the shapes of bows for decorating gifts.\n");
    

    add_item(({"sign","poster"}), "Maybe you should read it.\n");
    add_cmd_item("sign", "read", "@@read_sign@@");
    add_cmd_item("poster", "read", "@@read_poster@@");
//    add_cmd_item("sign", "read", MORE(GIFT_DIR+"sign.txt"));
//    add_cmd_item("poster", "read", MORE(GIFT_DIR+"poster.txt"));


    config_default_trade();
    add_exit(FROG_DIR + "road03", "out");

}

int
read_sign()
{

    MORE(GIFT_DIR+"sign.txt");
    return 1;
}

int
read_poster()
{

    MORE(GIFT_DIR+"poster.txt");
    return 1;
}


void
init()
{
    ::init();
    add_action("do_wrap","wrap");

}


int
do_wrap(string str)
{
    object item,box;
    string target, sbox, sbow, str2, str3, nitem;
    int *arr, price, num, nbox, nbow;

    NF("Wrap what wonderful item?\n");
    
    if (str=="gift")
    {
        NF("Sorry, we don't wrap gifts multiple times. If you "+
            "don't like it, you can always open the gift and it " +
            "can be wrapped again.\n");
        return 0;
    }
    
    if(!parse_command("wrap "+str,TP,"'wrap' %o 'with' %d 'and' %d 'for' %s",item,nbox,nbow,target))
	return 0;
    
    if(!item || !present(item, TP))
    {
	    write("Wrap what item?\n");
    	return 0;
    }
    if(item->query_prop(OBJ_M_NO_DROP))
    {
    	write("You can't wrap that item.\n");
	    return 0;
    }

    if(!target)
    {
	    write("Who is this wonderous gift for?\n");
    	return 0;
    }
    
    switch(nbox)
    {
        case 1: sbox = "red"; break;
        case 2: sbox = "green"; break;
        case 3: sbox = "blue"; break;
        case 4: sbox = "yellow"; break;
        case 5: sbox = "orange"; break;
        case 6: sbox = "gold"; break;
        case 7: sbox = "silver"; break;
        case 8: sbox = "bright yellow"; break;
        case 9: sbox = "white"; break;
        case 10: sbox = "pink"; break;
        case 11: sbox = "sky blue"; break;
        case 12: sbox = "beige"; break;
        case 13: sbox = "black"; break;
        case 14: sbox = "forest green"; break;
        case 15: sbox = "purple"; break;
        case 16: sbox = "black and white striped"; break;
        case 17: sbox = "bright floral print"; break;
        case 18: sbox = "red and white checkered"; break;
        case 19: sbox = "cheery bird print"; break;
        case 20: sbox = "silver and gold bells print"; break;
        case 21: sbox = "bright sunflower print"; break;
        case 22: sbox = "rising sun print"; break;
        case 23: sbox = "sunny butterfly print"; break;
        case 24: sbox = "happy birthday print"; break;
        case 25: sbox = "green frog print"; break;
        case 26: sbox = "diamond print"; break;
        case 27: sbox = "romantic print"; break;
        case 28: sbox = "roses and heart print"; break;
        case 29: sbox = "silver foil;"; break;
        case 30: sbox = "gold foil"; break;
        default: 
	        NF("There is no number "+nbox+" in the list.\n");
    	return 0;
    }

    switch(nbow)
    {
        case 1: sbow = "red"; break;
        case 2: sbow = "green"; break;
        case 3: sbow = "blue"; break;
        case 4: sbow = "yellow"; break;
        case 5: sbow = "orange"; break;
        case 6: sbow = "gold"; break;
        case 7: sbow = "silver"; break;
        case 8: sbow = "bright yellow"; break;
        case 9: sbow = "white"; break;
        case 10: sbow = "pink"; break;
        case 11: sbow = "sky blue"; break;
        case 12: sbow = "beige"; break;
        case 13: sbow = "black"; break;
        case 14: sbow = "forest green"; break;
        case 15: sbow = "purple"; break;
        case 16: sbow = "black and white striped"; break;
        case 17: sbow = "bright floral print"; break;
        case 18: sbow = "red and white checkered"; break;
        case 19: sbow = "cheery bird print"; break;
        case 20: sbow = "silver and gold bells print"; break;
        case 21: sbow = "bright sunflower print"; break;
        case 22: sbow = "rising sun print"; break;
        case 23: sbow = "sunny butterfly print"; break;
        case 24: sbow = "happy birthday print"; break;
        case 25: sbow = "green frog print"; break;
        case 26: sbow = "diamond print"; break;
        case 27: sbow = "romantic print"; break;
        case 28: sbow = "roses and heart print"; break;
        case 29: sbow = "silver foil;"; break;
        case 30: sbow = "gold foil"; break;
        default:
            NF("There is no number "+nbow+" in the list.\n");
        return 0;
    }
    box = clone_object(GIFT_DIR+"box");
//    box->set_box_name(C(target),C(TP->query_name()));
    box->set_box_name((target),TP->query_name());
    box->set_box_color(sbox,sbow);
    price = 576; /* 4 gold */
    box->add_prop(CONT_I_MAX_VOLUME,item->query_prop(OBJ_I_VOLUME)+100);
    box->add_prop(CONT_I_VOLUME,box->query_prop(OBJ_I_VOLUME)-100);
    box->add_prop(CONT_I_MAX_WEIGHT,item->query_prop(OBJ_I_WEIGHT)+100);
    box->remove_prop(CONT_I_CLOSED);
    if(item->move(box) != 0)
    {
	    NF("Odd, it didn't work. Please report this as a bug.\n");
    	box->remove_object();
	    return 0;
    }

    nitem=item->short();

    box->add_prop(CONT_I_CLOSED,1);
    
    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
	    return 0;  /* pay() handles notify_fail() call */

    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    
    if (text(exclude_array(arr, 0, NUM-1)))
	    write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");

    write(CAP(nitem)+" is taken from you and wrapped.\n");
    write("You are handed a "+box->short()+".\n");
    say(QCTNAME(TP)+" gets a "+box->short()+".\n");
    
    if(box->move(TP))
    {
	    write("Its too heavy, and you drop it.\n");
	    box->move(E(TP));
    }
    return 1;
}
