// file name: /d/Avenir/common/outpost/obj/food/cheese.c
// creator(s): Lilith, May 2022
// purpose:    Food for Fort Sybarus
// revisions:
inherit "/std/food";
inherit "/lib/commands";

#include <macros.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <composite.h>
#include <adverbs.h>
#include "/d/Avenir/common/outpost/outpost.h"

void
create_food() 
{
   set_amount(50);   
   set_name("cheese");
   add_name("ball");
   set_adj(({"cheese", "goat", "soft", "creamy", "almond", "honey"}));
   set_short("ball of soft goat cheese");
   set_pshort("balls of soft goat cheese");
   set_long("This is a walnut-sized ball of soft and creamy "+
      "goat cheese. It has been dipped in honey and rolled in "+
      "chopped almonds. It looks like a tasty snack.\n");
   add_prop(OBJ_I_VALUE,  0);
   add_prop(OBJ_I_WEIGHT, 50);
   add_prop(OBJ_I_VOLUME, 50);
}


/*
 * int amnt = # of portions to try to eat.
 *            0 == try to eat all remaining.
 */
private int
try_to_eat(int amnt)
{

    if (!this_player()->eat_food())
    {
	write("The " + singular_short() + " is too much for you.\n");
	return 0;
    }

	special_effect(1);
    return 1;
}


public nomask int
is_fort_food(void)         { return 1; }

public int
do_savour(string str)
{
    object obj, *obs;
    string *how, flavor;

    how = parse_adverb_with_space(str, NO_DEFAULT_ADVERB, 1);

    if (!strlen(how[0]))
	return NF(CAP(query_verb()) +" what?\n");

    obs = filter(all_inventory(TP), is_fort_food);

    if (!parse_command(how[0], obs, "[on] [the] [my] %o", obj) ||
	(obj != TO))
    {
	notify_fail(CAP(query_verb()) +" what?\n");
	return 0;
    }
/*
    if (current <= portion)
    {
	int num = num_heap();

	if (!try_to_eat(0))
	    return 1;

	special_effect(1);
	current = food_amount;
	set_heap_size(num - 1);
	return 1;
    }
*/
    switch(query_verb())
    {
    case "nibble":
	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("delicately");

	write("You"+ how[1] +" at the "+ singular_short()+
	    ", getting a small taste of tangy cheese along "+
        "with a few bits of honey-covered almonds.\n");
	say(QCTNAME(TP)+ " nibbles"+ how[1] +" on the "+ 
        singular_short() +".\n");
	break;

    case "taste":
    case "sample":
    //	if (!try_to_eat(1))
    //	    return 1;

	if (how[1] == NO_DEFAULT_ADVERB_WITH_SPACE)
	    how[1] = ADD_SPACE_TO_ADVERB("carefully");

	write("You"+ how[1] +" sample the "+ singular_short() +
	    ", getting a small taste of tangy cheese along "+
        "with a few bits of honey-covered almonds.\n");
	say(QCTNAME(TP) + how[1] +" samples "+ POSSESS(TP) +" "+
	    singular_short() +".\n");

	break;
    }

    return 1;
}

public void
hook_smelled(string str)
{
    write("It smells like honey and cream.\n");
}

public void
special_effect(int amnt)
{
    write("Wow! It just melted in your mouth, a sweet, creamy, "+
        "and crunchy treat.\n");
}


public void
init(void)
{
    ::init();

    if (ENV() != TP)
	return;
    add_action( do_savour, "sample"  );
    add_action( do_savour, "nibble" );
    add_action( do_savour, "taste"  );
}



