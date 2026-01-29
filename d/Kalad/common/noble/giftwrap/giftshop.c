inherit "/d/Kalad/room_std";
inherit "/lib/trade";
#include "/d/Kalad/defs.h"
#define NUM sizeof(MONEY_TYPES)

/* Sarr */

void
create_room()
{
    set_short("Inside the gift wrapping service building");
    set_long("You have entered a large room that is decorated with "+
      "many colors and patterns of wall paper. At the far end of the "+
      "room, a large, oak table runs the length of the wall, upon "+
      "which sit stacks of blank, white boxes. Behind the tables, "+
      "many little gnomes run about madly, wraping up boxes with "+
      "brilliant colored paper. Behind them, on the wall, there is "+
      "a large rack with rolls of colored paper stacked in it. There "+
      "is a large sign on the front side of the table.\n");
    add_item("walls","The walls of the room are decorated in a "+
      "splash of many colors and patterns.\n");
    add_item("table","The table is huge and heavy, and a sign "+
      "hangs off the front of it.\n");
    add_item("gnomes","They run about madly.\n");
    add_item("rack","The rack is made of wood, and has many slots in "+
      "it where rolls of paper are stored.\n");
    add_item("paper","Many different colors of paper.\n");
    add_cmd_item("sign","read","@@sign@@");
    config_default_trade();
    add_exit(NOBLE(market/s4),"west",0,-1,-1);
    INSIDE;
}

string
sign()
{
    return "Welcome to the gift wrapping service. Here, you can "+
    "get any single item wrapped up in a box and bow of your "+
    "choosing, and sent as a gift. To do so, we charge a fee of "+
    "4 gold coins. To do so, please use the syntax:\n"+
    "wrap (item) with (# color for box) and (# color for bow) to "+
    "(person you want to address the gift to).\n"+
    "To list the # of colors available, do: list colors.\n";
}

void
init()
{
    ::init();
    AA(do_wrap,wrap);
    AA(do_list,list);
}

int
do_list(string str)
{
    NF("List what?\n");
    if(str != "colors")
	return 0;
    seteuid(getuid());
    cat(NOBLE(giftwrap/BOX_DESC));
    return 1;
}

int
do_wrap(string str)
{
    object item,box;
    string target,sbox,sbow,str2,str3;
    int *arr, price, num,nbox,nbow;

    NF("Wrap what?\n");
    if(!parse_command("wrap "+str,TP,"'wrap' %o 'with' %d 'and' %d 'to' %s",item,nbox,nbow,target))
	return 0;
    if(!item || !present(item, TP))
    {
	write("Wrap what?\n");
	return 0;
    }
    if(item->query_prop(OBJ_M_NO_DROP))
    {
	write("You can't wrap that item.\n");
	return 0;
    }
    if(!target)
    {
	write("Send it to whom?\n");
	return 0;
    }
    switch(nbox)
    {
    case 1:
	sbox = "red";
	break;
    case 2:
	sbox = "green";
	break;
    case 3:
	sbox = "blue";
	break;
    case 4:
	sbox = "yellow";
	break;
    case 5:
	sbox = "orange";
	break;
    case 6:
	sbox = "brown";
	break;
    case 7:
	sbox = "black";
	break;
    case 8:
	sbox = "purple";
	break;
    case 9:
	sbox = "violet";
	break;
    case 10:
	sbox = "white";
	break;
    case 11:
	sbox = "pearl-white";
	break;
    case 12:
	sbox = "sea-green";
	break;
    case 13:
	sbox = "forest-green";
	break;
    case 14:
	sbox = "sky-blue";
	break;
    case 15:
	sbox = "jet-black";
	break;
    case 16:
	sbox = "dark-blue";
	break;
    case 17:
	sbox = "silver";
	break;
    case 18:
	sbox = "gold";
	break;
    case 19:
	sbox = "copper";
	break;
    case 20:
	sbox = "dark-brown";
	break;
    case 21:
	sbox = "yellow-orange";
	break;
    case 22:
	sbox = "glittering white";
	break;
    case 23:
	sbox = "blood-red";
	break;
    case 24:
	sbox = "light-brown";
	break;
    case 25:
	sbox = "cherry-red";
	break;
    case 26:
	sbox = "pink";
	break;
    case 27:
	sbox = "bright yellow";
	break;
    case 28:
	sbox = "deep-purple";
	break;
    case 29:
	sbox = "stripped orange";
	break;
    case 30:
	sbox = "dawn-orange";
	break;
    default:
	NF("There is no number "+nbox+" in the list.\n");
	return 0;
    }

    switch(nbow)
    {
    case 1:
	sbow = "red";
	break;
    case 2:
	sbow = "green";
	break;
    case 3:
	sbow = "blue";
	break;
    case 4:
	sbow = "yellow";
	break;
    case 5:
	sbow = "orange";
	break;
    case 6:
	sbow = "brown";
	break;
    case 7:
	sbow = "black";
	break;
    case 8:
	sbow = "purple";
	break;
    case 9:
	sbow = "violet";
	break;
    case 10:
	sbow = "white";
	break;
    case 11:
	sbow = "pearl-white";
	break;
    case 12:
	sbow = "sea-green";
	break;
    case 13:
	sbow = "forest-green";
	break;
    case 14:
	sbow = "sky-blue";
	break;
    case 15:
	sbow = "jet-black";
	break;
    case 16:
	sbow = "dark-blue";
	break;
    case 17:
	sbow = "silver";
	break;
    case 18:
	sbow = "gold";
	break;
    case 19:
	sbow = "copper";
	break;
    case 20:
	sbow = "dark-brown";
	break;
    case 21:
	sbow = "yellow-orange";
	break;
    case 22:
	sbow = "glittering white";
	break;
    case 23:
	sbow = "blood-red";
	break;
    case 24:
	sbow = "light-brown";
	break;
    case 25:
	sbow = "cherry-red";
	break;
    case 26:
	sbow = "pink";
	break;
    case 27:
	sbow = "bright yellow";
	break;
    case 28:
	sbow = "deep-purple";
	break;
    case 29:
	sbow = "stripped orange";
	break;
    case 30:
	sbow = "dawn-orange";
	break;
    default:
	NF("There is no number "+nbow+" in the list.\n");
	return 0;
    }
    box = clone_object(NOBLE(giftwrap/box));
    box->set_box_name(C(target),C(TP->query_name()));
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
    box->add_prop(CONT_I_CLOSED,1);
    if (sizeof(arr = pay(price, this_player(), str2, 0, 0, str3)) == 1)
	return 0;  /* pay() handles notify_fail() call */
    write("You pay " + text(exclude_array(arr, NUM, NUM*2-1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM-1)))
	write("You get " + text(exclude_array(arr, 0, NUM-1)) + ".\n");
    write("Your "+item->short()+" is taken from you and wrapped.\n");
    write("You are handed a "+box->short()+".\n");
    say(QCTNAME(TP)+" gets a "+box->short()+".\n");
    if(box->move(TP))
    {
	write("Its too heavy, and you drop it.\n");
	box->move(E(TP));
    }
    return 1;
}
