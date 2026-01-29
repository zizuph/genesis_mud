/*
 * egg.c  -> Goes with the eggmaker.c :)
 * Dunstable
 *
 *
 */

inherit "/std/food";
#include "/d/Shire/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

int do_roll(string str);

string thiscolor;

void
create_food()
{
    thiscolor = ONE_OF_LIST(({"red", "yellow", "green", "brown", "scarlet", "black", "ocher", "peach", "ruby", "olive", "violet", "fawn", "lilac", "gold", "chocolate", "mauve", "cream", "crimson", "silver", "rose", "azure", "lemon", "russet", "grey", "purple", "white", "pink", "orange", "blue"}));

    set_name("egg");
    add_name("easter egg");
    set_adj(thiscolor);
    set_short(thiscolor + " colored easter egg");
    set_long("This "+thiscolor+ " egg is very beautiful and precious. " +
        "It is also fragile so be careful with it or it might break. You " +
        "may be able to roll it around. However, the egg cannot be thrown " +
        "or used in events.\n");

    add_prop(OBJ_I_WEIGHT,  100);
    add_prop(OBJ_I_VOLUME,  74);
    add_prop(OBJ_I_VALUE,  0);
    set_amount(25); 


}

void
init()
{
    ::init();
    add_action("do_roll", "roll");
}

int
do_roll(string str)
{

    if((str != "egg") && (str != "easter egg") && (str !="egg on the ground"))
    {
	write("Roll what, a "+str+"?  Why not roll the egg?\n");
	return 1;
    }

    write("You roll the "+thiscolor+" egg carefully on the ground, taking care not to "+
      "damage it.\n");
    say(QCTNAME(TP)+ " rolls the "+thiscolor+" egg on the ground, taking "+
      "care not to damage it, isn't that cute?\n");
    return 1;

}
