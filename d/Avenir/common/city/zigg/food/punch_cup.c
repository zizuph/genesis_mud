// file name  :  punch.c
// creator(s) :  Zielia 2006
// revision(s):
// purpose    :
// note       :
// bug(s)     :
// to-do      :

#pragma no_inherit
#pragma strict_types

#include "zigg.h"
#include "/d/Avenir/include/deities.h"
#include <macros.h>
#include <language.h>

inherit "/std/drink";

//This cup holds 15 sips
#define SIZE        15
//One 4 cups will quench your thirst.
#define SIP        (TP->drink_max() / 60 )

public static int sips = SIZE;
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

    set_cont_name("tumbler");

    set_bev_name("cool refreshing punch");

    set_name(({"punch", "liquid", "cup", "tumbler", "glass"}));
    set_name(({"punches", "liquids", "carafes", "bottles"}));
    set_adj(({"lime", "mint", "green", "glass", "cool", "refreshing",
	"clear"}));
    set_short(query_cont_name() +" of "+ query_bev_name());
    set_pshort(query_cont_name() +"s of "+ query_bev_name());
    set_long("@@my_long");

    set_soft_amount(SIP);
    set_alco_amount(0);

    set_drink_msg("You drain your "+ query_cont_name() +" of refreshing "+
	"punch, letting the flavors of sweet water, tangy lime and fresh "+
	"mint cool you and quench your thirst.\n");

    add_item(({"glass"}),
        "The tumbler is made of clear, unadorned glass with a rounded "+
        "bottom. A small spot on the very bottom has been sanded flat "+
	"enough to allow it to stand on a tray or other surface.\n");

    add_prop(HEAP_S_UNIQUE_ID,
	"zigg:drink:punch:cups");
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

public string
my_long(void)
{
    return "The glass tumbler is elegant and devoid of decoration. The "+
	"bottom is rounded like an egg, but with a small flat spot to "+
	"allow it to stand. Inside, the punch is nearly clear with just a "+
	"faint green tint. It looks refeshingly cool and has a minty, "+
	"citrus scent. The glass is "+ how_much() +".\n";
}

public void
hook_smelled(string str)
{
    write("It smells like cool mint and tropical lime.\n");
}

public void
special_effect(int amount)
{
    say(QCTNAME(TP) +" drains "+ HIS(TP) +" "+ cont +" of the "+ bev +".\n");

    ::special_effect(amount);

    sips -= 1;

    while (--sips >= 0)
    {
	TP->drink_soft(SIP);
    }

}

public nomask int
is_zig_drink(void)         { return 1; }

public int
f_sip(string str)
{
    object *obs;

    if (!strlen(str))
	return NF(CAP(query_verb()) +" what?\n");

    obs = filter(all_inventory(TP), &->is_zig_drink());

    if (parse_command(str, obs, " 'punch' / 'drink' / 'liquid' [from] "+
    "[the] [cup] / [tumbler] / [glass] "))
    {
        write("The cool, light liquid teases your tongue with the "+
	"flavors of sweet water and lime and the refreshing finish of "+
	"fresh mint as you sip the "+ bev +" from the "+ cont +".\n");

        say(QCTNAME(TP) +" savours a sip of "+ bev +
	    " from "+ HIS(TP) +" "+ cont +".\n");

	TP->drink_soft(SIP);
        sips -= 1;

	if (!sips)
	{
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

}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
