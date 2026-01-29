#include "defs.h"
#include <money.h>

inherit PARTY_BASE;
inherit "/lib/trade";

#define COSTUME  (PARTY_OBJ + "costume")
#define COSTUME_MAP (PARTY_DIR + "costumes")
#define CC 0
#define SC 0
#define GC 3
#define PC 0
#define NUM sizeof(MONEY_TYPES)

mapping costumes;

void
create_party_room()
{
    add_prop(ROOM_S_MAP_FILE, "party.txt");

    set_short("A cluttered tent filled with clothing");
    set_long("You are within a large blue tent, filled with sheets of "+
      "cloth and other fabrics used to make costumes.  In one corner you see "+
      "clay masks of several creatures as well as other attachments which "+
      "might be used to make a costume more realistic.  A small sign "+
      "is nailed to a wooden desk, which a curious looking hobbit sits behind.\n");

    add_item(({"sign","small sign"}),"You notice some readable words on the "+
      "sign.\n");
    add_cmd_item(({"sign","small sign"}),"read",
      "@@my_sign");
    add_item(({"tent","blue tent"}),
      "This tent is made of a delicate blue material.  You suspect the "+
      "tent material was choosen for it's pleasing looks rather than it's "+
      "durability as the tent would surely get blown away and destroyed in "+
      "the smallest of storms.\n");
    add_item(({"cloth","sheets","sheets of cloth","fabrics","sheets of fabrics"}),
      "Mult-coloured scraps of material litter the ground of this tent.\n");
    add_item(({"mask","masks","clay mask","clay masks","corner"}),
      "Expertly crafted masks sit on the northeastern corner of the tent.  "+
      "They range from a simple orc mask to a complex dragon shaped one.\n");
    add_item( "attachments",
      "Costume accessories, such as wooden swords, makeshift leather "+
      "satchels, paste-jewelery, and the like help clutter this tent.\n");
    add_item(({"wooden desk","desk"}),
      "A small wooden desk, made of pine wood.\n");
    add_item(({"curious looking hobbit","curious hobbit","hobbit"}),
      "This hobbit is wearing a silly looking costume of a "+
      "insect, what type of insect you can not figure out.\n");

    add_prop(ROOM_I_INSIDE, 1);

    add_exit(PARTY_DIR + "entrance","east",0,1);

    config_default_trade();
    set_money_give_out(({10000,32,2,1,}));
    set_money_give_reduce(({0,4,2,1}));

    costumes = restore_map(COSTUME_MAP);
}

string
my_sign()
{
    return "Welcome to the costume shop!\n\n\tFor a list of costumes "+
    "type 'list costumes'\n\tTo buy one a costume type '"+
    "buy <costume race name>'.\n\n"+
    "For a more detailed explaination try 'help room'.\n";
}

void
add_costume(string r_name,string a1,string a2,string r_say,string in,string out)
{
    if (costumes[r_name])
    {
	write("That costume already exists!\n");
	return;
    }
    costumes[r_name] = ({a1,a2,r_say,in,out});
    write("Adding "+r_name+" to the list of costumes.\n");
    save_map(costumes, COSTUME_MAP);
    return;
}

varargs void
wear_costume(string type, object player)
{
    if (!objectp(player))
	player = TI;

    if (!costumes[type])
	return;
    if (player->query_shire_costume())
	player->remove_shire_costume();
    clone_object(COSTUME)->shadow_me(player);

    player->set_up_costume(({type}) + costumes[type]);
}

int
buy(string str)
{
    int price;
    int *money_arr;
    string name,pay_type,get_type,coin_pay_text,coin_get_text;

    if (!strlen(str))
    {
        NF(CAP(query_verb()) + " what?\n");
        return 0;
    }
    price = CC + (SC * 12) + (GC * 144) + (PC * 1720);
    if (sscanf(str, "%s for %s and get %s",name,pay_type,get_type) != 3)
    {
	get_type = "";
	if (sscanf(str, "%s for %s", name, pay_type) != 2)
	{
	    pay_type = "";
	    name = str;
	}
    }
    if (!costumes[name])
    {
	NF(CAP(query_verb()) +" what?\nType 'list costumes' to see what ones we have to buy.\n");
	return 0;
    }
    if (sizeof(money_arr = pay(price,TP,pay_type,0,0,get_type)) == 1)
    {
	NF("You are unable to afford a costume!\n");
	return 0;
    }
    wear_costume(name, TP);

    coin_pay_text = text(exclude_array(money_arr, NUM, NUM*2-1));
    coin_get_text = text(exclude_array(money_arr, 0, NUM-1));

    write("You pay "+coin_pay_text+" for your costume.\n");
    if (coin_get_text)
	write("You get "+coin_get_text+" back.\n");
    say(QCTNAME(TP)+" buys "+HIM_HER(TP)+"self a costume.\n");
    return 1;
}

int
list(string str)
{
    int i;
    string name, to_write;
    string *names;

    if (str != "costumes")
    {
	NF("List what? Costumes maybe?\n");
	return 0;
    }
    to_write = "Costumes cost "+MONEY_TEXT(({CC,SC,GC,PC}))+" each.\n"+
    "If you are wearing a costume and buy another the old costume is "+
    "replaced by the newly purchased one.\n\n"+
    "These are the costumes that are in stock at the moment.\n\n";
    names = m_indexes(costumes);
    names = sort_array(names);
    for (i = 0; i < sizeof(names); i++)
    {

	name = names[i];
	to_write += LANG_ADDART(costumes[name][0]) + " " + costumes[name][1] + " " +
	name +".\n";
    }
    TP->more(to_write);
    return 1;
}

void
init()
{
    ::init();
    add_action(buy,"buy");
    add_action(list,"list");
}
