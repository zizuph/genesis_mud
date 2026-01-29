//             Spiked Kahve
// file name:  /d/Avenir/common/outpost/obj/food/spiked_kahve.c
// creator:    Lilith Mar 2022
// purpose:    sippable alcohol, giving players more control of their intake.
// notes :
// updates  :
#pragma no_inherit
#pragma strict_types

#include <macros.h>
#include <language.h>
#include "/d/Avenir/include/basic.h"
#include "/d/Avenir/include/relation.h"

inherit "/std/drink";

//This cup holds 20 sips
#define SIZE        20
// #define SIP        (TP->drink_max() / 20 )
#define SIP_SOFT   15 
#define SIP_BOOZE  5

#define SOFT_AMT   300 
#define BOOZE_AMT  100

public int sips = SIZE;
public static string cont, bev;

public void set_cont_name(string str) {cont = str;}
public string query_cont_name(void) {return cont;}

public void set_bev_name(string str) {bev = str;}
public string query_bev_name(void) {return bev;}

public void set_sips(int str) {sips = str;}
public int query_sips(void) {return sips;}

private void
create_drink(void)
{
    setuid();
    seteuid(getuid());

    set_cont_name("cup");

    set_bev_name("spiked kahve");

    set_name(({"kahve", "cup", "glass"}));
    set_pname(({"kahves", "cups", "glasses"}));
    set_adj(({"spiked", "cognac"}));
    set_short(query_cont_name() +" of "+ query_bev_name());
    set_pshort(query_cont_name() +"s of "+ query_bev_name());
    set_long("@@my_long");

    set_soft_amount(SOFT_AMT);
    set_alco_amount(BOOZE_AMT);

    set_drink_msg("You drain your "+ query_cont_name() +" of spiked "+
	"kahve.\n");

    add_item(({"glass"}),
        "This cup is made of clear, thick glass with a metal handle "+ 
        "attached to a band of metal just beneath the lip.\n");

    add_prop(HEAP_S_UNIQUE_ID, "fort:drink:spiked:kahve" + ":" + sips);
}

private string
how_much(void)
{
    switch(query_soft_amount())
    {
    case 271..300:  return "full";
    case 241..270:  return "quite full";
    case 201..240:  return "rather full";
    case 171..200:  return "somewhat full";
    case 161..170:  return "about half full";
    case 131..160:  return "about half empty";
    case 91..130:   return "somewhat empty";
    case 61..90:    return "rather empty";
    case 31..60:    return "close to empty";
    case  0..30:    return "nearly empty";
    default:        return "deceptively full";
    }
}

public string
my_long(void)
{
    return "This steaming glass cup of spiked coffee looks brown and creamy. "+
	"It has a heady aroma of coffee and cognac. The glass is "+ how_much() +"."+
	" Since it is a warm drink you might want to try sipping it.\n";
}

public void
hook_smelled(string str)
{
    write("It has the rich scent of coffee along with the heavy scent of "+
    "good cognac.\n");
}

public void
special_effect(int amount)
{
    say(QCTNAME(TP) +" drains "+ HIS(TP) +" "+ cont +" of the "+ bev +".\n");

    ::special_effect(amount);

    sips -= 1;
	
    while (--sips >= 0)
    {
	TP->drink_soft(SIP_SOFT);
	TP->drink_alco(SIP_BOOZE);
    }

}

public nomask int
is_fort_drink(void)         { return 1; }

public int
f_sip(string str)
{
    object *obs;
    int qi, im;
 
    if (!strlen(str))
	return NF(CAP(query_verb()) +" what?\n");
	
    obs = filter(all_inventory(TP), &->is_fort_drink());
    if (parse_command(str, obs, " 'kahve' / 'drink' / 'liquid' [from] "+
    "[the] [glass] [cup] "))
    {
        write("You take a sip of the spiked kahve. The rich flavour of "+
        "sybarun kahve brings out the caramel overtones in the cognac.\n");

        say(QCTNAME(TP) +" savours a sip of "+ bev +
	    " from "+ HIS(TP) +" "+ cont +".\n");

	TP->drink_soft(SIP_SOFT);
    TP->drink_alco(SIP_BOOZE);
    split_heap(1);
    set_soft_amount(query_soft_amount() - SIP_SOFT);
    set_alco_amount(query_alco_amount() - SIP_BOOZE);
    object others = make_leftover_heap();
    others->add_prop(HEAP_S_UNIQUE_ID, "fort:drink:spiked:kahve" + ":" + sips);
    sips -= 1;
    add_prop(HEAP_S_UNIQUE_ID, "fort:drink:spiked:kahve" + ":" + sips);
    others->move(TP,1);

	if (!sips)
	{
		write("You have reached the bottom of your cup of spiked kahve.\n");
	    set_alarm(0.0, 0.0, remove_object);
	}
    move(TP, 1);

	if (IS_SYBARITE(TP))
	{	
        qi = TP->query_intoxicated();    
        im = TP->intoxicated_max() / 4;   

        if (qi >= im)
            write("Something in your mind reminds you that you will soon reach a "+
            "level of intoxication beyond which is considered unseemly for sybarites.\n");
        
    }
        return 1;
    }
    return 0;
}

public void
init()
{
    ::init();

    add_action(f_sip, "sip");
    add_action(f_sip, "savour");
    add_action(f_sip, "savor");

}

public string query_recover()
{
    return ::query_recover() + "#SIP#" + sips + "#";
}

public void
init_recover(string arg)
{
    ::init_recover(arg);
    string foobar;
    sscanf(arg, "%s#SIP#%d#%s", foobar, sips, foobar);
    set_alco_amount(sips * SIP_BOOZE);
    set_soft_amount(sips * SIP_SOFT);
    add_prop(HEAP_S_UNIQUE_ID, "fort:drink:spiked:kahve" + ":" + sips);
}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
