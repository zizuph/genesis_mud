//              rice bowl with eel (unagi donburi)
// file name:  /d/Avenir/common/outpost/obj/food/rice_bowl.c
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

#define SIZE       5
#define AMT        40

public static int bites = SIZE;

public void set_bites(int str) {bites = str;}
public int query_bites(void) {return bites;}

private string how_much();

public string
my_long(void)
{
    return "Marinated strips of grilled sybarun eel rest on a bed "+ 
	"of rice in a wide, shallow bowl. You can nibble on each strip "+
    "one at a time, or eat them all at once. "+
    "You can see "+ how_much() +"\n";
}

private void
create_food(void)
{
    setuid();
    seteuid(getuid());

    set_name(({"bowl", "strips", "strip", "strip of eel", "strips of eel"}));
    set_adj(({"grilled", "rice", "marinated"}));
    set_short("rice bowl with grilled eel");
    set_pshort("rice bowls with grilled eel");
    set_long(my_long);
    add_item("rice", "It is steamed and slightly sticky.\n");
    add_item(({"marinade", "sauce"}), "It is thick and dark and "+
    "sweet and salty, all at once.\n");
    set_amount(200);
    add_prop(HEAP_S_UNIQUE_ID, "fort:rice");
}

private string
how_much(void)
{
    string str;
    switch(bites)
    {
    case 0..1:
	str = "a single strip of eel left in the bowl.";
	break;
    case 2:
	str = "two strips of eel left in the bowl.";
	break;
    case 3:
	str = "three strips of eel in the bowl.";
	break;
    case 4:
	str = "four strips of eel in the bowl.";
	break;
    default:
	str = "five strips of eel in the bowl.";
	break;
    }
	
    return str;
}

public void
hook_smelled(string str)
{
    write("It has that delicious smell that seems to be a result of "+
    "the sauce.\n");
}

public void
special_effect(int amount)
{
    say(QCTNAME(TP) +" fills "+ HIS(TP) 
        +" mouth with a strip of grilled eel.\n");
    write("You fill your mouth with a strip of grilled eel " 
        +"mouth and chew happily.\n");
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
    if (parse_command(str, obs, "[on] [a] 'eel' / 'strip' "+
    "[of] [eel] [from] [the] [bowl]"))
    {
        write("You nibble on a strip of the grilled eel, "+
        "relishing both the tenderness of the meat and "+
        "deliciousness of the sauce.\n");

        say(QCTNAME(TP) +" nibbles on a strip of eel.\n");

        bites -= 1;
    	TP->eat_food(AMT);
	    if (!bites)
	    {
		    write("You have eaten the last of your rice bowl.\n");
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
	add_action(f_nib, "relish");
    
}

public string
stat_object(void)
{
    return ::stat_object() +
	"Unique ID: "+ query_prop(HEAP_S_UNIQUE_ID) + "\n";
}
