inherit "/d/Kalad/room_std";
inherit "/lib/trade";
#include "/d/Kalad/defs.h"
#define NUM sizeof(MONEY_TYPES)

#define BRA NOBLE(lingerie_shop/bra)
#define STO NOBLE(lingerie_shop/stockings)
#define GLO NOBLE(lingerie_shop/gloves)
#define GBE NOBLE(lingerie_shop/gbelt)
#define FST NOBLE(lingerie_shop/fstock)
#define GOW NOBLE(lingerie_shop/gown)
#define DRE NOBLE(lingerie_shop/dress)
#define PAN NOBLE(lingerie_shop/gpant)

void
create_room()
{
   hear_bell = 1;
   INSIDE;
   set_short("The Noble District Lingerie Store");
   set_long("This is fine lingerie store of the Noble district. "+
   "The air is filled with sweet smelling perfume. This is where "+
   "all the rich noblewomen come to by their intimate apparel. There "+
   "is a poster on one wall.\n");
    add_item("poster","It is a large poster listing the various "+
    "items available here.\n");
    add_cmd_item("poster","read","@@poster@@");
   add_exit(NOBLE(gateway/s3),"north");
   config_default_trade();
}

string
poster()
{
    return 
    "Here we offer the following in various colors:\n"+
    "1. A pair of long leather gloves:            120 cc\n"+
    "2. A lacy garter belt:                       120 cc\n"+
    "4. A lacy bra:                               100 cc\n"+
    "5. A pair of thigh-high silk stockings:      120 cc\n"+
    "6. A pair of thigh-high fish-net stockings:  120 cc\n"+
    "7. A silky night-gown:                       144 cc\n"+
    "8. A satin dress:                            144 cc\n"+
    "9. A pair of panties:                        120 cc\n"+
    "We offer then in these colors:\n"+
    "Red, white, black, yellow, pink, light blue and green.\n"+
    "Simply enter the number followed by the color. EX:\n"+
    "'buy 7 black'\n"+
    "NEW: You can now wear them with armours! Although if you "+
    "wear them with an armour, and it covers it, it will not "+
    "be shown to others.\n"+
    "Enjoy!\n";
}


void
init()
{
   ::init();
   AA(do_buy,buy);
}

int
do_buy(string str)
{
    int *result,m_res,price;
    string type,col,color,for_c,get_c,change;
    object buy_ob;
    NF("Buy what?\n");
    if(!str)
        return 0;
    sscanf(str,"%s %s",type,col);
    switch(type)
    {
        case "1":
            buy_ob = clone_object(GLO);
        break;
        case "2":
            buy_ob = clone_object(GBE);
        break;
        case "4":
            buy_ob = clone_object(BRA);
        break;
        case "5":
            buy_ob = clone_object(STO);
        break;
        case "6":
            buy_ob = clone_object(FST);
        break;
        case "7":
            buy_ob = clone_object(GOW);
        break;
        case "8":
            buy_ob = clone_object(DRE);
        break;
        case "9":
            buy_ob = clone_object(PAN);
        break;
        default:
            NF("There is no such number:"+type+".\n");
            return 0;
    }
    switch(col)
    {
        case "red":
            color = "red";
            break;
        case "white":
            color = "white";
            break;
        case "pink":
            color = "pink";
            break;
        case "green":
            color = "green";
            break;
        case "light blue":
            color = "light blue";
            break;
        case "black":
            color = "black";
            break;
        case "yellow":
            color = "yellow";
            break;
        default:
            NF("There is no such color "+col+".\n");
            return 0;
    }
    buy_ob->set_color(color);
    price = buy_ob->query_prop(OBJ_I_VALUE);
    result = pay(price,TP,for_c,0,0,get_c);
    if(sizeof(result) == 1)
    {
        buy_ob->remove_object();
        return 0;
    }
    if(buy_ob->move(TP))
    {
        write("The object is too heavy, you drop it.\n");
        say(QCTNAME(TP)+" drops his item.\n");
        buy_ob->move(E(TP));
    }
    else
    {
        write("You bought a "+buy_ob->short()+".\n");
        say(QCTNAME(TP)+" bought a "+buy_ob->short()+".\n");
    }
    write("You pay "+text(result[0 .. NUM - 1])+".\n");
    if(change)
    {
        write("You get "+change+" as change.\n");
    }
    return 1;
}
