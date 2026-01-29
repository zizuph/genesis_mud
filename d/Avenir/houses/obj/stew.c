/*
 * HOBJ + stew.c
 *
 * Varian - Jan 2020
 */

#include <stdproperties.h>
#include <formulas.h>
#include <macros.h>
#include <files.h>
#include "/d/Gondor/met_defs.h"
#include "/d/Gondor/defs.h"

inherit "/std/food";

int do_taste(string str);
int do_devour(string str);

void
create_food() 
{
    set_name("hearty_stew");
    add_name( ({"stew", "hearty stew"}) );
    set_short("hearty stew");
    set_adj("hearty");
    set_long("This hearty stew looks fresh and home-made! " +
    	"You can just have a little taste or devour the " +
    	"whole thing - but be careful, it is still hot!\n");

    set_amount(575);
    add_prop(OBJ_I_WEIGHT,750);
    add_prop(OBJ_I_VOLUME,900);
    add_prop(OBJ_I_VALUE, 500);
}

init()
{
    ::init();
    add_action("do_taste","taste");
    add_action("do_devour","devour");
}

int
do_taste(string str)
{

    if (!str || !strlen(str)) 
    {
        notify_fail("Taste what?\n");
        return 0;
    }

    if (!id(str))
    {
        notify_fail("Taste what?\n");
        return 0;
    }

    if(environment(this_object()) == this_player())
    {
        write("You lean carefully over the bowl of stew, taking " +
            "a small sip of the hot stew. A wonderful blend of " +
            "spices dance across your tongue as perfectly " +
            "cooked chunks of vegetables and venison delight " +
            "your tastebuds.\n");
    SAYBB(" tastes their hearty stew by taking a small sip");
        return 1;
    }

    if(environment(this_object()) != this_player())
    {
        this_player()->catch_tell("You aren't holding anything " +
            "you can taste.\n");
        return 1;
    }

    notify_fail("You cannot taste the stew at this time.\n");
    return 0;
}

int
do_devour(string str)
{

    if (!str || !strlen(str)) 
    {
        notify_fail("Devour what?\n");
        return 0;
    }

    if (!id(str))
    {
        notify_fail("Devour what?\n");
        return 0;
    }

    if(environment(this_object()) == this_player())
    {
        write("Unable to resist temptation, you devour your " +
            "bowl of hearty stew in mere seconds! You barely " +
            "had time to appreciate the delicate blend of spices" +
            "or the savoury taste of perfectly cooked cubes " +
            "of vegetables and venison.\n");
        SAYBB(" dives into a bowl of hearty stew with great gusto, " +
            "devouring it instantly!");
        this_player()->command("eat hearty_stew");
        return 1;
    }

    if(environment(this_object()) != this_player())
    {
        this_player()->catch_tell("You don't have any stew " +
            "to devour right now.\n");
        return 1;
    }

    notify_fail("You are not able to devour anything at this time.\n");
    return 0;
}
