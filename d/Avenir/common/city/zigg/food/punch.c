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

//This bottle holds 4 cups or 60 sips
#define PORTIONS     4
//There are 60 sips in a carafe
#define SIZE        60
//One carafe will quench your thirst.
#define SIP        (TP->drink_max() / SIZE )

private static int sips = SIZE;
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

    set_cont_name("carafe");

    set_bev_name("cool refreshing punch");

    set_name(({"punch", "liquid", "carafe", "bottle"}));
    set_name(({"punches", "liquids", "carafes", "bottles"}));
    set_adj(({"lime", "mint", "green", "glass", "cool", "refreshing",
	"clear"}));
    set_short(cont +" of "+ bev +" with matching tumblers");
    set_pshort(cont +"s of "+ bev +" with matching tumblers");
    set_long("@@my_long");

    set_soft_amount(SIP);
    set_alco_amount(0);

    set_drink_msg("You guzzle down the refreshing punch directly from the  "+
        "carafe, letting the faintly green liquid run from the corners of "+
	"your mouth as you try not to swallow the pieces of lime and mint "+
	"bumping against your lips. The flavors of sweet water, tangy "+
	"lime and cool mint chase each other over your tongue leaving "+
	"throughly refreshed.\n");

    add_item(({"glass", "glasses", "cups", "tumblers"}),
        "The carafe is made of clear, unadorned glass with a round body "+
        "and curving lines from the body to the wide neck and flared mouth. "+
	"The matching tumblers are made of the same glass but rounded like "+
	"an egg, with just a small flat spot on the bottom allow it to "+
	"stand.\n");

    add_item(({"lid",}),
        "The top of the glass carafe has a fitted glass lid which is "+
	"threaded to screw onto the wide opening and allows it to be "+
	"portable without spilling.");

    add_prop(HEAP_S_UNIQUE_ID,
	"zigg:drink:punch");
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
    return "The glass carafe is elegantly simple with clean lines devoid "+
	"of decoration. The smooth glass bottle has a wide neck, which "+
	"flares to a wider opening fitted with a threaded lid. Inside the "+
	"carafe, sprigs of mint and slices of lime float in a nearly clear "+
        "liquid with a faint green tint. The carafe is "+ how_much() +
	". The glass is cool to the touch and lightly misted with "+
	"tantalizing condensation. Four matching glass tumblers wait to "+
	"be filled with punch.\n";
}

public void
hook_smelled(string str)
{
    write("It smells like cool mint and tropical lime.\n");
}

public void
special_effect(int amount)
{
    say(QCTNAME(TP) +" guzzles punch directly from the carafe, letting the "+
	"faintly green liquid run from the corners of "+ HIS(TP) +" mouth "+
	"in "+ HIS(TP) +" fervor until at last, with the carafe empty, "+
	HE(TP) +" appears throughly refreshed.\n");

    ::special_effect(amount);

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
    object obj1, obj2, *obs;

    if (!strlen(str))
	return NF(CAP(query_verb()) +" what?\n");

    obs = filter(all_inventory(TP), &->is_zig_drink());

    if (parse_command(str, obs, "%o [from] [the] %o", obj1, obj2)
    && (obj1 == TO) && (obj2 == TO))
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

public int
f_pour(string str)
{
    object *obs, obj;

    if (!strlen(str))
	return NF("Pour glass of what?\n");

    obs = filter(all_inventory(TP), &->is_zig_drink());

    if (parse_command(str, obs, " 'glass' / 'tumbler' / 'cup' 'of' / 'with' "+
    "'punch' / 'drink' / 'liquid' [from] [the] [carafe] / [bottle] "))
    {
	if (sips > (SIZE / PORTIONS))
	{
	    write("You fill a tumbler with "+ bev +" from the "+
		 cont +".\n");

	    say(QCTNAME(TP) +" fills a tumbler with "+ bev +
		" from "+ HIS(TP) +" "+ cont +".\n");

	    obj = clone_object(ZIG_FOOD +"punch_cup");
	    obj->set_sips(SIZE / PORTIONS);
	    obj->move(ENV(), 1);

	    sips -= (SIZE / PORTIONS);

            return 1;
	}
	else
	{
	    write("You pour the rest of the "+ bev +" from your "+
		 cont +" into a tumbler.\n");

	    say(QCTNAME(TP) +" pours the rest of the "+ bev +
		" from "+ HIS(TP) +" "+ cont +" into a tumbler.\n");

	    obj = clone_object(ZIG_FOOD +"punch_cup");
	    obj->set_sips(sips);
	    obj->move(ENV(), 1);

	    sips = 0;
	    set_alarm(0.0, 0.0, remove_object);

            return 1;
	}
    }
    NF("Fill tumbler with what? Punch?\n");
    return 0;
}


public void
init()
{
    ::init();

    add_action( f_sip, "sip");
    add_action( f_sip, "savour");
    add_action( f_sip, "savor");
    add_action(f_pour, "pour");
    add_action(f_pour, "fill");

}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
