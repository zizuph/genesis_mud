/* Beans beans the magical fruit
 * The more you eat, the more you toot.
 *
 * Raymundo, Feb 2020
 */

inherit "/std/food";
#include "/d/Shire/common/defs.h"
#include "/d/Shire/eastroad/western/local.h"

#define FARTS	EAST_R_DIR + "supplies/beansef.c"

void
create_food()
{
	setuid();
    seteuid(getuid());
	
    set_name("beans");
	add_name("bowl");
	add_adj( ({"of", "stewed", "stew", "beans", "bean"}));
    set_pname("bowls of beans");
    set_short("bowl of stewed beans");
    set_pshort("bowls of stewed beans");
    
    set_long("This is a bowl of beans. You see some chunks of bacon, as "
		+ "well as some onions and cabbage in the bowl, but mostly, it's "
		+ "beans.\n");
	add_item("bowl", "The bowl is made of cheap pottery, a bit chipped and "
		+ "very rustic, the kind of bowl you would use if people kept getting "
		+ "drunk and raising hell in your inn, because when they eventually "
		+ "smash the bowl in a fight, at least it didn't cost you much money.\n");
    set_amount(250);
    
}

//Clones in the farting. Beans make you fart.
public void
special_effect(int amount)
{
	object fart;
	write("Ooooh, those beans taste good, but now you start to worry "
		+ "they'll make you gassy!\n");
	fart = clone_object(FARTS);
	fart->move(TP);
	
}