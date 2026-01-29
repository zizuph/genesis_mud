//             Goats Milk (non-alcoholic)
// file name:  /d/Avenir/common/outpost/obj/food/goats_milk.c
// creator:    Lilith May 2022
// purpose:    sippable drink, no alcohol
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
#define SIZE       20
#define SIP_SOFT   25 
#define SIP_BOOZE  0

#define SOFT_AMT   500 
#define BOOZE_AMT  0

public static int sips = SIZE;
public static string cont, bev;

public void set_cont_name(string str) {cont = str;}
public string query_cont_name(void) {return cont;}

public void set_bev_name(string str) {bev = str;}
public string query_bev_name(void) {return bev;}

public void set_sips(int str) {sips = str;}
public int query_sips(void) {return sips;}

private string how_much();

public string
my_long(void)
{
    return "This is a half-liter earthenware crock containing "+
    "chilled goat milk. "+
    "The jug is "+ how_much() +".\n";
}

private void
create_drink(void)
{
    setuid();
    seteuid(getuid());

    set_cont_name("crock");

    set_bev_name("goat milk");

    set_name(({"crock", "jug", "vessel", "milk"}));
    set_pname(({"crocks", "milks"}));
    set_adj(({"goat", "goats", "goat's", "milk"}));
    set_short(query_cont_name() +" of "+ query_bev_name());
    set_pshort(query_cont_name() +"s of "+ query_bev_name());
    set_long(my_long);

    set_soft_amount(SOFT_AMT);
    set_alco_amount(BOOZE_AMT);

    set_drink_msg("You drain your "+ query_cont_name() +" chilled "+
	    "goat milk.\n");

    add_item(({"jug", "crock", "vessel", "earthenware"}),
        "This crock looks like a smal jug. It is a simple earthenware "+
        "vessel with a small handle and a narrow opening. There is "+
        "a trefoil symbol on the bottom.\n");

    add_prop(HEAP_S_UNIQUE_ID, "fort:drink:goat:milk");
}

private string
how_much(void)
{
    int val = 100;

    if (sips != SIZE)
    {
	float fsize, fsips;

	fsips = itof(sips);
	fsize = itof(SIZE);
	val = ftoi(100.0 - (((fsize - fsips) / fsize) * 100.0));
    }

    switch(val)
    {
    case 91..100: return "full";
    case 81..90:  return "quite full";
    case 71..80:  return "rather full";
    case 61..70:  return "somewhat full";
    case 51..60:  return "about half full";
    case 41..50:  return "about half empty";
    case 31..40:  return "somewhat empty";
    case 21..30:  return "rather empty";
    case 11..20:  return "close to empty";
    case  0..10:  return "nearly empty";
    default:      return "deceptively full";
    }
}


public void
hook_smelled(string str)
{
    write("It has sweet and floral scent of pears.\n");
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
    if (parse_command(str, obs, " [goat] 'milk' / 'drink' / 'liquid' "+
    "[from] [the] [crock] / [jug]"))
    {
        write("You take a sip goat milk. The sweet, creamy "+
        "flavour is perfectly mild.\n");

        say(QCTNAME(TP) +" sips a bit of "+ bev +
	    " from "+ HIS(TP) +" "+ cont +".\n");
		
    	TP->drink_soft(SIP_SOFT);
        TP->drink_alco(SIP_BOOZE);
        sips -= 1;

	    if (!sips)
	    {
		    write("You have reached the bottom of your jug of goat milk.\n");
	        set_alarm(0.0, 0.0, remove_object);
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
    add_action(f_sip, "taste");
}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
