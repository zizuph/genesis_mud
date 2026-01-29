//            fish kebab
// file name:  /d/Avenir/common/outpost/obj/food/fish_kebab.c
// creator:    Lilith May 2022
// purpose:    Food at the Fort
// notes :
// updates:

#pragma strict_types

#include <macros.h>
#include <language.h>
#include "/d/Avenir/include/basic.h"
#include "/d/Avenir/include/relation.h"

inherit "/std/food";

#define SIZE       6
#define AMT        25

public static int bites = SIZE;
public static string cont, food;

public void set_cont_name(string str) {cont = str;}
public string query_cont_name(void) {return cont;}

public void set_food_name(string str) {food = str;}
public string query_food_name(void) {return food;}

public void set_bites(int str) {bites = str;}
public int query_bites(void) {return bites;}

private string how_much();

public string
my_long(void)
{
    return "Chunks of fish have been threaded on a skewer and "+ 
	"grilled to perfection. "+
    "You can savour each chunk of fish one bite at a time, "+
    "or eat the whole kebob	at once. "+
    how_much() +"\n";
}

private void
create_food(void)
{
    setuid();
    seteuid(getuid());

    set_cont_name("skewer");

    set_food_name("grilled fish chunks");

    set_name(({"kebob", "skewer", "chunk", "fish"}));
    set_adj(({"grilled", "fish", "chunks"}));
    set_short("fish kebob");
    set_pshort("fish kebobs");
    set_long(my_long);
    set_amount(150);

    add_prop(HEAP_S_UNIQUE_ID, "fort:kebob");
}

private string
how_much(void)
{
    string str;
    switch(bites)
    {
    case 0..1:
	str = "There's just one chunk left on the skewer.";
	break;
    case 2..3:
	str = "There are a few delicious chunks of fish left.";
	break;
    case 4..5:
	str = "The skewer is mostly full of chunks of fish.";
	break;
    default:
	str = "There are a half-dozen chunks of fish on the skewer.";
	break;
    }
	
    return str;
}

public void
hook_smelled(string str)
{
    write("It smells like grilled fish and herbs.\n");
}

public void
special_effect(int amount)
{
    say(QCTNAME(TP) +" gobbles down "+ HIS(TP) 
        +" skewer of grilled fish.\n");
    write("You hungrily gobble down the grilled fish chunks.\n");
    ::special_effect(amount);

    bites -= 1;
	
    while (--bites >= 0)
    {
    	TP->eat_food(AMT);
    }

}

public nomask int
is_fort_food(void)         { return 1; }

public int
f_nib(string str)
{
    object *obs;
    int qi, im;
 
    if (!strlen(str))
	return NF(CAP(query_verb()) +" what?\n");
	
    obs = filter(all_inventory(TP), &->is_fort_food());
    if (parse_command(str, obs, "[on] [a] 'fish' / 'chunk' "+
    "[of] [grilled] [fish]"))
    {
        write("You bite a chunk of grilled fish off the skewer "+
            "and chew it slowly, savouring the flavours.\n");

        say(QCTNAME(TP) +" bites a chunk of fish off a skewer.\n");

        bites -= 1;
    	TP->eat_food(AMT);
	    if (!bites)
	    {
		    write("You eat the last chunk of fish.\n");
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

    add_action(f_nib, "nibble");
    add_action(f_nib, "taste");
	add_action(f_nib, "bite");
	add_action(f_nib, "savor");
	add_action(f_nib, "savour");	
}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
