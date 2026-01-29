/*
 * Made flower so it can be picked up and taken.
 * Finwe, January 2004
 */

#include "../spells.h"

inherit SPELL_OBJECT;
inherit "/std/object";

//   Protoypes
varargs int dispell_spell_effect(object dispeller);
void wither();

static string color;

void
create_object() 
{
    color = ONE_OF_LIST(({"orange","purple","red","white","yellow","violet","maroon",
        "blue","golden","silver"}));
    set_short("beautiful " + color + " flower");
    set_long("This is a beautiful " + color + " flower. It is fragile " +
        "looking and like no flower you have ever imagined. It is a gift " +
        "from Lorien.\n");
    set_name("flower");
    set_adj(({"beautiful",color}));


//    add_prop(OBJ_I_NO_GET,  0);
//    add_prop(OBJ_I_NO_INS,  1);
    add_prop(OBJ_I_VOLUME,  3);
    add_prop(OBJ_I_WEIGHT, 10);
}

public int
start()
{
    set_spell_effect_desc("conjured flower");
    if (!::start())
    {
	remove_spell_effect_object();
	return 0;
    }
    move(spell_target, 1);
    set_alarm(300.0, 0.0, wither);
    return 1;
}

void
wither() 
{
    set_short("withered " + color + " flower");
    set_long("The once beautiful " + color + " flower is withering slowly.\n");
    set_adj(({"withered",color}));
    set_alarm(400.0, 0.0, dispell_spell_effect);
}

varargs int
dispell_spell_effect(object dispeller)
{
    tell_room(environment(), "The "+short()+" crumbles to dust.\n");
    remove_spell_effect_object();
    return 1;
}
