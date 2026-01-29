// second sword   /d/Avenir/common/city/obj/wield/d2ndsword
// creator(s): 	Lilith
// last update: 	July 2002
// purpose:       Sword for the dej-minha	
// note:          Similar desc to Shintor, wielded by Jadestone Doll.         
// bug(s):
// to-do:
#pragma strict_types

inherit "/d/Avenir/inherit/weapon";

#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <wa_types.h>

#include "/d/Avenir/include/defs.h"

public void
create_weapon(void)
{
    set_name("sword");
    add_name(({"_dej_sword_", "blade", "longsword"}));
    set_adj(({"blooded", "steel"}));
    set_short("blooded steel longsword");
    /* similar to shintor */
    set_long("This sword is very thin and long, with a blade that "+
        "suddenly tapers off to a sharp point at the end. "+
        "The handle is of polished steel, moulded to fit the "+
        "right hand with a narrow, decorative guard at the base "+
        "of the blade. Reflected in the polished surface of the "+
        "blade is a reverse image of the area around you. "+
        "Looking at it, you expect that swinging this blade "+
        "will be a very satisfying experience.\n");

    set_hit(35 + random(6));
    set_pen(35 + random(6));
    set_wt(W_SWORD);
    set_dt(W_SLASH | W_IMPALE);
    set_hands(W_ANYH);

    add_item("guard", "This guard is quite narrow and mostly "+
        "decorative. Whoever wields this sword must be so "+
        "confident of her skills that she is not concerned "+
        "about damaging her hand in combat.\n");
}

public int
swing_func(string arg)
{
    string str;

    if (arg == "sword" || arg == "blade")
    {
        if (query_interactive(TP) && STR(TP) < 70)
        {
            write("You feebly swing the " + short() + 
                " through the air.\n" +
                "You are unable to stop path of the " + short() + 
                ", and it flies right out of your hands!\n");
            say(QCTNAME(this_player()) + " swings the " + short() + 
                " in an arc through the " +
                "air, but is unable to stop its motion.\nThe " + 
                short() + " flies right out of " +
                POSSESS(this_player()) + " hands.\n");

            move(ENV(TP));
            return 1;
        }

        write("You strain your muscles and swing the " + short() + 
            " through the air.\nYou hear a satisfying 'swoosh'.\n");
        say(QCTNAME(TP) + " swings the " + short() + 
            " through the air with incredible strength.\nSwoosh.\n");

        return 1;
    }

    notify_fail("Swing what?\n");
    return 0;
}

public void
init(void)
{
    ::init();

    if (ENV() != TP)
	return;

    add_action(swing_func, "swing");
}

