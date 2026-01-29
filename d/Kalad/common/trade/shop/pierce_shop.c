inherit "/d/Kalad/room_std";
inherit "/lib/trade";
#define NUM sizeof(MONEY_TYPES)
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/noble/arm/ring.h"
void check_more(object ob);

object ob1;
/* by Milashk, modified by Antharanos, modified by Sarr */
   create_room()
{
   ::create_room();
   hear_bell = 1;
   INSIDE;
   set_short("Body piercing shop");
   set_long("You have entered a small dimly lit room. There is a chair in "
      +"one corner, as well as a table in the middle of the room. "
      +"Two signs, one red, one black, on the wall have something on them "+
       " to read. There is "
      +"the smell of alcohol on the air, mixed with sweat and dirt. "
      +"The room is so sloppy, only a goblin could live here.\n");
   add_item(({"room"}),"Why don't you look around?\n");
   add_item(({"smell"}),"There is the smell of strong alcohol, as well "
      +"the smell of sweat and other filth.\n");
   add_item(({"chair"}),"The chair seems to be well-used, and has traces "
      +"of blood on it.\n");
   add_item(({"table"}),"There is a big bottle and a strange machine sitting on it.\n");
   add_item(({"bottle"}),"It says: XXX Brand Whiskey.\n");
   add_item(({"strange machine","machine"}),"A strange, box-shaped object "+
      "made from tin. It has several holes which seem to correspond to varying "+
      "body parts.\n");
   add_cmd_item("from bottle","drink","You drink from the bottle and feel "
      +"brave enough to get parts of your body pierced.\n");
   add_item(({"red sign","black sign","sign"}),"Its something you read.\n");
   add_cmd_item("sign","read","Read which sign?\n");
   add_cmd_item("red sign","read","@@red_sign@@");
   add_cmd_item("black sign","read","The sign says:\n"
      +"Get your body pierced! It will make you look cool.\n"
      +"I do 13 piercing packages, to buy one try 'buy pierce1'\n"
      +"that will get you my first piercing job. Here is what \n"
      +"I pierce: (Each one costs but 1 gold coin)\n"
      +"pierce1........left ear\n"
      +"pierce2........right ear\n"
      +"pierce3........both ears\n"
      +"pierce4........nose\n"
      +"pierce5........left eyebrow\n"
      +"pierce6........right eyebrow\n"
      +"pierce7........both eyebrows\n"
      +"pierce8........tongue\n"
      +"pierce9........lip\n"
      +"pierce10.......left nipple\n"
      +"pierce11.......right nipple\n"
      +"pierce12.......both nipples\n"
      +"pierce13.......navel\n"
      +"You can only have one piercing job done per body part. You can\n"
      +"have multiple piercing jobs on different parts of your body. "+
       "You can also buy rings for your piercing. Read the red sign "+
       "for details. You can also 'unpierce' a 'body part'.\n");
   config_default_trade();
   set_alarm(1.0,0.0,"reset_room");
   add_exit(TRADE(tsquare/c2),"west",0,-1,-1);
}
string
red_sign()
{
    return
    "You can buy two types of rings here. Single ones, and pairs. "+
    "The pairs are used for piercings of both left and right body "+
    "parts, which are option 3, 7, and 12 on the black sign. The "+
    "rest are for the single piercings. You cannot wear singles "+
    "in double slots, or vice versa. To wear them, simply type "+
    "insert <ring(s)> in <body part>. The body part must be specific. "+
    "Example: insert gold ring in left eyebrow, and, insert silver rings "+
    "in both ears. To remove them, simply type remove <ring(s)>. "+
    "To buy a ring, type order <ring(s)>. All the listed rings "+
    "are of single rings. You can order pairs by adding an 's' to "+
    "the word 'ring'. The price is doubled for pairs. If you want "+
    "to have a gem with them, you can. Just: order <ring(s)> with <gem>.\n"+
    "NEW!!! -----\n"+
    "You can now get studs the same way you get rings. Just use "+
    "order <stud(s)> with <gem> instead.\n\n"+
    "---- Available rings and costs ----\n"+
    "Copper ring              2 copper\n"+
    "Brass ring               6 copper\n"+
    "Bronze ring             12 copper\n"+
    "Steel ring              16 copper\n"+
    "Silver ring              2 silver\n"+
    "White-silver ring        3 silver\n"+
    "Gold ring                1 gold\n"+
    "Platinum ring            1 platinum\n"+
    "Mithril ring             2 platinum\n"+
    "---- Available gems and costs ----\n"+
    "Turquoise                1 gold\n"+
    "Jasper                   2 gold\n"+
    "Amber                    4 gold\n"+
    "Garnet                   8 gold\n"+
    "Onyx                     1 platinum\n"+
    "Jade                     1 platinum 4 gold\n"+
    "Pearl                    1 platinum 8 gold\n"+
    "Topaz                    2 platinum\n"+
    "Opal                     2 platinum 4 gold\n"+
    "Emerald                  2 platinum 8 gold\n"+
    "Sapphire                 3 platinum\n"+
    "Ruby                     3 platinum 4 gold\n"+
    "Jacinth                  3 platinum 8 gold\n"+
    "Diamond                  4 platinum\n";
}

void
reset_room()
{
   if (!ob1)
      {
      ob1 = clone_object(TRADE(npc/piercer));
      ob1 -> move_living("xxx",TO);
   }
}

int
order(string str)
{
   object buy_ob;
   string for_c, get_c, change, *rorder,gem,metal;
   int *result, m_res, price, no_gem;
   int val;
seteuid(getuid());
write_file("/d/Kalad/common/trade/shop/order_log", this_player()->query_real_name()+" -> Verb: "+query_verb()+" Arg: "+str+"\n");
   NF("Order what?\n");
   if(!str)
       return 0;
   rorder = explode(str," ");
   NF("Order what?\n");
   if(sizeof(rorder) > 4 || sizeof(rorder) < 2)
       return 0;
   NF("Order "+rorder[0]+" what?\n");
   if(rorder[1] != "ring" && rorder[1] != "rings" && rorder[1] != "stud" &&
      rorder[1] != "studs")
       return 0;
   if(sizeof(rorder) == 2)
       no_gem = 1;
   if(no_gem == 0)
   {
       NF("Order "+rorder[0]+" "+rorder[1]+" with what?\n");
       if(rorder[2] != "with")
           return 0;
       if(rorder[3] == "")
           return 0;
   }
   switch(rorder[0])
   {
       case "copper":
       val = 2;
       metal = "copper";
       break;
       case "brass":
       val = 6;
       metal = "brass";
       break;
       case "bronze":
       val = 12;
       metal = "bronze";
       break;
       case "steel":
       val = 16;
       metal = "steel";
       break;
       case "silver":
       val = 24;
       metal = "silver";
       break;
       case "white-silver":
       val = 36;
       metal = "white-silver";
       break;
       case "gold":
       val = 144;
       metal = "gold";
       break;
       case "platinum":
       val = 1728;
       metal = "platinum";
       break;
       case "mithril":
       val = 3456;
       metal = "mithril";
       break;
       default:
       NF("Sorry, we don't have the metal type '"+rorder[0]+"'.\n");
       return 0;
   }
   if(no_gem == 0)
   {
   switch(rorder[3])
   {
       case "turquoise":
       val = val + 144;
       gem = "turquoise";
       break;
       case "jasper":
       val = val + 288;
       gem = "jasper";
       break;
       case "amber":
       val = val + 576;
       gem = "amber";
       break;
       case "garnet":
       val = val + 1152;
       gem = "garnet";
       break;
       case "onyx":
       val = val + 1728;
       gem = "onyx";
       break;
       case "jade":
       val = val + 2304;
       gem = "jade";
       break;
       case "pearl":
       val = val + 2880;
       gem = "pearl";
       break;
       case "topaz":
       val = val + 3456;
       gem = "topaz";
       break;
       case "opal":
       val = val + 4032;
       gem = "opal";
       break;
       case "emerald":
       val = val + 4608;
       gem = "emerald";
       break;
       case "sapphire":
       val = val + 5184;
       gem = "sapphire";
       break;
       case "ruby":
       val = val + 5760;
       gem = "ruby";
       break;
       case "jacinth":
       val = val + 6336;
       gem = "jacinth";
       break;
       case "diamond":
       val = val + 6912;
       gem = "diamond";
       break;
       default:
       NF("Sorry, we don't have a gem-type '"+rorder[3]+"'.\n");
       return 0;
   }
   }
   if(rorder[1] == "ring")
       buy_ob = clone_object(NOBLE(arm/single_ring));
   if(rorder[1] == "rings")
   {
       val = val * 2;
       buy_ob = clone_object(NOBLE(arm/pair_rings));
   }
   if(rorder[1] == "stud")
       buy_ob = clone_object(NOBLE(arm/single_stud));
   if(rorder[1] == "studs")
   {
       val = val * 2;
       buy_ob = clone_object(NOBLE(arm/pair_studs));
   }
   buy_ob->set_ring_metal(metal);
   if(no_gem == 0)
       buy_ob->set_ring_metal(gem,1);
   price = val;
   buy_ob->set_ring_value(val / 2);
   result=pay(price,this_player(),for_c,0,0,get_c);
   if (sizeof(result)==1) {
      buy_ob->remove_object();
      return 0;
   }
   if (buy_ob->move(this_player())) {
      write("Too heavy for your load.\n");
      say(QCTNAME(TP) + " drops something.\n");
      buy_ob->move(environment(this_player()));
   }
   else {
      write("You get yourself a "+buy_ob->short()+".\n");
      say(QCTNAME(TP) + " orders a "+buy_ob->short()+".\n");
   }
   write("You pay " + text(result[0 .. NUM - 1]) + ".\n");
   if (change)
      write("You get " + change + " as change.\n");
   return 1;
}

int
unpierce(string s)
{
    object ob;
    switch(s)
    {
        case "left ear":
        NF("You don't have a pierced left ear.\n");
        if(!TP->query_prop(KALAD_RING_EAR_LEFT))
            return 0;
        NF("Please remove all rings from body part.\n");
        if(TP->query_prop(KALAD_RING_EAR_LEFT) == 2)
            return 0;
        NF("You don't have a pierced left ear.\n");
        ob = present("pierce1",TP);
        if(!ob)
            return 0;
        ob->remove_object();
        check_more(TP);
        break;
        case "right ear":
        NF("You don't have a pierced right ear.\n");
        if(!TP->query_prop(KALAD_RING_EAR_RIGHT))
            return 0;
        NF("Please remove all rings from body part.\n");
        if(TP->query_prop(KALAD_RING_EAR_RIGHT) == 2)
            return 0;
        NF("You don't have a pierced right ear.\n");
        ob = present("pierce2",TP);
        if(!ob)
            return 0;
        ob->remove_object();
        check_more(TP);
        break;
        case "both ears":
        NF("You don't have both ears pierced.\n");
        if(!TP->query_prop(KALAD_RING_EAR_BOTH))
            return 0;
        NF("Please remove all rings from body part.\n");
        if(TP->query_prop(KALAD_RING_EAR_BOTH) == 2)
            return 0;
        NF("You don't have have both ears pierced.\n");
        ob = present("pierce3",TP);
        if(!ob)
            return 0;
        ob->remove_object();
        check_more(TP);
        break;
        case "nose":
        NF("You don't have a pierced nose.\n");
        if(!TP->query_prop(KALAD_RING_NOSE))
            return 0;
        NF("Please remove all rings from body part.\n");
        if(TP->query_prop(KALAD_RING_NOSE) == 2)
            return 0;
        NF("You don't have a pierced nose.\n");
        ob = present("pierce4",TP);
        if(!ob)
            return 0;
        ob->remove_object();
        check_more(TP);
        break;
        case "left eyebrow":
        NF("Please remove all rings from body part.\n");
        if(TP->query_prop(KALAD_RING_EYEB_LEFT) == 2)
            return 0;
        NF("You don't have a pierced left eyebrow.\n");
        if(!TP->query_prop(KALAD_RING_EYEB_LEFT))
            return 0;
        ob = present("pierce5",TP);
        if(!ob)
            return 0;
        ob->remove_object();
        check_more(TP);
        break;
        case "right eyebrow":
        NF("Please remove all rings from body part.\n");
        if(TP->query_prop(KALAD_RING_EYEB_RIGHT) == 2)
            return 0;
        NF("You don't have a pierced right eyebrow.\n");
        if(!TP->query_prop(KALAD_RING_EYEB_RIGHT))
            return 0;
        ob = present("pierce6",TP);
        if(!ob)
            return 0;
        ob->remove_object();
        check_more(TP);
        break; 
        case "both eyebrows":
        NF("Please remove all rings from body part.\n");
        if(TP->query_prop(KALAD_RING_EYEB_BOTH) == 2)
            return 0;
        NF("You don't have both eyebrows pierced.\n");
        if(!TP->query_prop(KALAD_RING_EYEB_BOTH))
            return 0;
        ob = present("pierce7",TP);
        if(!ob)
            return 0;
        ob->remove_object();
        check_more(TP);
        break;
        case "tongue":
        NF("Please remove all rings from body part.\n");
        if(TP->query_prop(KALAD_RING_TONGUE) == 2)
            return 0;
        NF("You don't have a pierced tongue.\n");
        if(!TP->query_prop(KALAD_RING_TONGUE))
            return 0;
        ob = present("pierce8",TP);
        if(!ob)
            return 0;
        ob->remove_object();
        check_more(TP);
        break;
        case "lip":
        NF("Please remove all rings from body part.\n");
        if(TP->query_prop(KALAD_RING_LIP) == 2)
            return 0;
        NF("You don't have a pierced lip.\n");
        if(!TP->query_prop(KALAD_RING_LIP))
            return 0;
        ob = present("pierce9",TP);
        if(!ob)
            return 0;
        ob->remove_object();
        check_more(TP);
        break;
        case "left nipple":
        NF("Please remove all rings from body part.\n");
        if(TP->query_prop(KALAD_RING_NIP_LEFT) == 2)
            return 0;
        NF("You don't have a pierced left nipple.\n");
        if(!TP->query_prop(KALAD_RING_NIP_LEFT))
            return 0;
        ob = present("pierce10",TP);
        if(!ob)
            return 0;
        ob->remove_object();
        check_more(TP);
        break;
        case "right nipple":
        NF("Please remove all rings from body part.\n");
        if(TP->query_prop(KALAD_RING_NIP_RIGHT) == 2)
            return 0;
        NF("You don't have a pierced right nipple.\n");
        if(!TP->query_prop(KALAD_RING_NIP_RIGHT))
            return 0;
        ob = present("pierce11",TP);
        if(!ob)
            return 0;
        ob->remove_object();
        check_more(TP);
        break;    
        case "both nipples":
        NF("Please remove all rings from body part.\n");
        if(TP->query_prop(KALAD_RING_NIP_BOTH) == 2)
            return 0;
        NF("You don't have a both nipples pierced.\n");
        if(!TP->query_prop(KALAD_RING_NIP_BOTH))
            return 0;
        ob = present("pierce12",TP);
        if(!ob)
            return 0;
        ob->remove_object();
        check_more(TP);
        break;    
        case "navel":   
        NF("Please remove all rings from body part.\n");
        if(TP->query_prop(KALAD_RING_NAVEL) == 2)
            return 0;
        NF("You don't have a pierced navel.\n");
        if(!TP->query_prop(KALAD_RING_NAVEL))
            return 0;
        ob = present("pierce13",TP);
        if(!ob)
            return 0;
        ob->remove_object();
        check_more(TP);
        break;
    default:
        NF("There is no such body part "+s+".\n");
        return 0;
    }
    write("You stick your pierced body part in the strange machine.\n");
    write("Your piercing job has been removed!\n");
    say(QCTNAME(TP) + " sticks " + TP->query_possessive() + " pierced body part in the machine and gets it removed.\n");
    return 1;
}

void
init()
{
   ::init();
   AA(unpierce,unpierce);
   AA(order,order);
}

void
check_more(object ob)
{
    int i;
    object *inv,temp;
    inv = all_inventory(ob);
    for(i=0;i<sizeof(inv);i++)
    {
        if(inv[i]->query_prop(KALAD_RING_HOLE))
        {
            temp = clone_object(MASTER_OB(inv[i]));
            inv[i]->remove_object();
            temp->move(ob);
            break;
        }
    }
}

