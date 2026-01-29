// file name: /d/Avenir/common/outpost/obj/food/stew.c
// creator(s): Lilith, May 2022
// purpose:    Food for Fort Sybarus
// revisions:

inherit "/std/food";
#include "/sys/stdproperties.h"

void
create_food() 
{
   set_amount(200);   
   set_name("stew");
   add_name("bowl");
   set_adj(({"hearty", "goat", "broth"}));
   set_short("bowl of hearty goat stew");
   set_pshort("bowls of hearty goat stew");
   set_long("This is a deep bowl of hearty stew. The broth is "+
      "thick with vegetables and chunks of tender goat meat.\n");
   add_prop(OBJ_I_VALUE, 0);
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME, 500);
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

public void
hook_smelled(string str)
{
    write("The stew smells like... childhood, stimulating vague "+
       "memories of your grandmother.\n");
}

public void
special_effect(int amnt)
{
    write("The stew is slightly sweet and rich with the "+
        "flavours of goat meat, herbs, and vegetables.\n");
}


