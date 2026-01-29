//             fried grubs
// file name:  /d/Avenir/common/outpost/obj/food/fried_grubs.c
// creator:    Lilith May 2022
// purpose:    food at the fort
// notes :
// updates  :

#pragma strict_types

#include <macros.h>
#include <language.h>
#include "/d/Avenir/include/basic.h"
#include "/d/Avenir/include/relation.h"

inherit "/std/food";

//This cup holds 10 grubs
#define SIZE       10
#define AMT        10

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
    return "The fried, crispy goodness of spiced grubs rests "+ 
	"within a flimsy cup made of folded paper. You can nibble "+
    "on them one at a time, or eat them all at once. "+
    how_much() +"\n";
}

private void
create_food(void)
{
    setuid();
    seteuid(getuid());

    set_cont_name("cup");

    set_food_name("spicy fried grubs");

    set_name(({"cup", "grubs", "paper cup"}));
    set_pname(({"cups"}));
    set_adj(({"fried", "grub", "grubs", "spicy", "crispy", "cruchy"}));
    set_short("cup of spicy fried grubs");
    set_pshort("cups of spicy fried grubs");
    set_long(my_long);
    add_item("grub", "High in protein and fairly abundant in parts of "+
       "Sybarus, these grubs are especially delicious served "+
       "fried with spices sprinkled over them.\n");
    add_item(({"paper", "flimsy paper"}), "This paper is thick enough "+
       "stand up to the grease, but not for long.\n");
    set_amount(100);

    add_prop(HEAP_S_UNIQUE_ID, "fort:grubs");
}

private string
how_much(void)
{
    string str;
    switch(grubs)
    {
    case 0..2:
	str = "There isn't much left inside.";
	break;
    case 3..4:
	str = "There are a few delicious grubs left in the cup.";
	break;
    case 5:
	str = "About half of the spicy fried grubs remain.";
	break;
    case 6..7:
	str = "There are many spicy fried grubs in the cup.";
	break;
    case 8..9:
	str = "The paper cup is mostly full of delicious grubs.";
	break;
    default:
	str = "The cup is full of crispy, crunchy grubs.";
	break;
    }
	
    return str;
}

public void
hook_smelled(string str)
{
    write("It has that delicious smell that all fried goodies have.\n");
}

public void
special_effect(int amount)
{
    say(QCTNAME(TP) +" pops spicy fried grubs into "+ HIS(TP) 
        +" mouth and chews happily.\n");
    write("You pop spicy fried grubs into your " 
        +"mouth and chew happily.\n");
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
    if (parse_command(str, obs, "[on] [one] [of] [a] / [the] [spicy] "+
    "[fried] 'grub' / 'grubs' [from] [the] [paper] [cup]"))
    {
        write("You nibble on the spicy fried grub, enjoying how it "+
            "crunches between your teeth.\n");

        say(QCTNAME(TP) +" nibbles on one of the "+ food +
	    " from "+ HIS(TP) +" "+ cont +".\n");

        grubs -= 1;
    	TP->eat_food(AMT);
	    if (!grubs)
	    {
		    write("You have eaten the last of your "+ food +".\n");
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

}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
