// file name:	~Avenir/common/outpost/obj/food/salad.c	
// creator(s): 	Lilith May 2022	
// purpose:	    Food for the Fort	
// revisions:     
#pragma strict_types

#include <macros.h>
#include <language.h>
#include "/d/Avenir/include/basic.h"
#include "/d/Avenir/include/relation.h"

inherit "/std/food";

#define SIZE       10
#define AMT        20

public static int grubs = SIZE;
public static string cont, food;

public void set_cont_name(string str) {cont = str;}
public string query_cont_name(void) {return cont;}

public void set_food_name(string str) {food = str;}
public string query_food_name(void) {return food;}

public void set_grubs(int str) {grubs = str;}
public int query_grubs(void) {return grubs;}

private string how_much();

public string
my_long(void)
{
    return "This is a plate of chartess mushrooms that were marinated "+
        "in balsamic vinegar and cooked slowly until the vinegar reduced "+
        "to coat the mushrooms in a dark, flavourful glaze. The mushrooms "+
        "have been sliced to about the thickness of your smallest finger. "+
        how_much() +  " You can nibble on them one at a time, or eat "+
        "them all at once.\n";
}

void
create_food()
{
    set_name("marinated mushrooms");
    add_name(({"plate", "plate of sliced mushrooms", 
        "plate of mushrooms","sliced mushrooms"}));
    set_adj(({"glazed", "marinated"}));
    set_short("plate of sliced mushrooms in balsamic glaze");
    set_long(my_long);
    set_amount(200);
	set_cont_name("plate");
    set_food_name("mushrooms in balsamic glaze");
	add_item(({"mushroom", "chartess", "slices", "mushroom slices",
	    "slice", "mushroom slice"}),
        "The chartress mushrooms were cut into slices about the "+
        "thickness of your littlest finger.\n");
    add_item(({"glaze", "marinade"}), "The glaze on the mushrooms "+
        "a made of balsamic vinegar that was slowly cooked down,\n");
}


private string
how_much(void)
{
    string str;
    switch(grubs)
    {
    case 0..2:
	str = "There is just a slice or two left.";
	break;
    case 3..4:
	str = "About a third of the mushroom slices remain.";
	break;
    case 5:
	str = "The plate is about half full of sliced mushrooms.";
	break;
    case 6..7:
	str = "About a third of the mushroom slices have been eaten.";
	break;
    case 8..9:
	str = "The plate is mostly covered in mushroom slices.";
	break;
    default:
	str = "The plate is covered with many slices of mushrooms.";
	break;
    }
	
    return str;
}

public void
hook_smelled(string str)
{
    write("It smells of mushrooms cooked in a hearty balsamic vinegar.\n");
}

public void
special_effect(int amount)
{

    write("The marinade and the thickness of the flesh lends a "+
        "surprisingly 'meaty' flavour to the dish.\n");			
		
    ::special_effect(amount);

    grubs -= 1;
	
    while (--grubs >= 0)
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
    if (parse_command(str, obs, "[on] [a] 'slice' [of] [glazed] "+
    "[mushroom]"))
    {
        write("You pop a slice of glazed mushroom into your " 
        +"mouth and sigh blissfully. Delicious!\n");

        say(QCTNAME(TP) +" pops a slice of glazed mushroom into "+ 
        HIS(TP) +" mouth and sighs blissfully.\n");

        if (!random(5))
        write("The marinade and the thickness of the flesh lends a "+
        "surprisingly 'meaty' flavour to the dish.\n");		
		
        grubs -= 1;
    	TP->eat_food(AMT);
	    if (!grubs)
	    {
		    write("You have eaten the last of your "+ food +"s.\n");
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
    add_action(f_nib, "savour");
    add_action(f_nib, "savor");	
}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
