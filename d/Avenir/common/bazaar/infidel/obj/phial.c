// file name:        /d/Avenir/common/bazaar/infidel/obj/phial.c
// creator(s):       Cirion
// revision history: Lilith, Aug 2002: made it impossible to poison 
//                   magical weapons.
//                   Denis, Jan'97: Misc changes.
// purpose:          
// note:             
// bug(s):           
// to-do:            

# include "../infidel.h"
# include <cmdparse.h>
# define WEAPON_POISON    OBJ + "weapon_poison"
inherit "/std/object";

int    num = 4;

int
phial_val()
{
    return (num * 200) + 1;
}

void
create_object()
{
    set_name("phial");
    set_short("long narrow phial");
    set_adj(({ "long", "narrow" }));
    set_long("It is a long phial made from faceted yellow " +
             "crystal@@level@@.\n");

    add_item(({ "liquid", "fluid" }), VBFC_ME("liquid"));

    add_prop(OBJ_I_WEIGHT, 20);
    add_prop(OBJ_I_VALUE, phial_val);
    add_prop(OBJ_I_VOLUME, 50);
}

string
level()
{
    switch(num)
    {
    case 4:
	return ", full with a clear, sticky fluid";
    case 3:
	return ", nearly full with clear, sticky fluid";
    case 2:
	return ", about half full of a clear, sticky fluid";
    case 1:
	return ", containing a small measure of clear, sticky fluid.";
    default:
	return ". It is empty";
    }
}

string
liquid()
{
    if (num <= 0)
        return "There is no liquid in the phial.\n";
    else
        return "The liquid in the phial is a thick translucent " +
               "amber fluid that seems to dance in the light.\nYou " +
               "might be able to coat something with it.\n";
}

int
poison(string str)
{
    object   wep, *things, shadow;
    string   which;

    NF("The phial is empty.\n");
    if (num <= 0)
        return 0;

    NF("You are too busy right now.\n");
    if (sizeof(TP->query_enemy(-1)))
        return 0;

    NF(CAP(QVB) + " what weapon?\n");
    if (!str || !strlen(str))
        return 0;

    things = FIND_STR_IN_OBJECT(str, TP);
    if (!sizeof(things))
        return 0;

    wep = things[0];
    if (wep->query_is_poisoned())
    {
        TP->catch_msg("But the " + wep->short(TP) + " is already " +
                      "coated with poison.\n");
        return 1;
    }

    if (!strlen(wep->weapon_type()) ||
	(wep->query_wt() != W_KNIFE &&
	 wep->query_wt() != W_SWORD &&
	 wep->query_wt() != W_AXE))
    {
        TP->catch_msg("You would need to use a bladed weapon.\n");
        return 1;
    }

    if (wep->query_prop(OBJ_I_IS_MAGIC_WEAPON))
    {
        num--;
        TP->catch_msg("You coat the blade of the " + wep->short(TP) +
            " with a small measure of sticky liquid.\n");
        TP->catch_msg("The magic in your weapon annuls the effects "+
            "of the poison.\n");
        return 1;
    }

    seteuid(getuid());
    shadow = clone_object(WEAPON_POISON);
    if(!shadow->shadow_me(wep))
    {
        write("That weapon may not be poisoned.\n");
        shadow->remove_shadow();
        return 1;
    }

    num--;
    TP->catch_msg("You coat the blade of the " + wep->short(TP) +
                  " with a small measure of sticky liquid.\n");
    say(QCTNAME(TP) + " coats the blade of " + POSSESS(TP) +
        " " + wep->short() + " with a small measure of sticky liquid.\n");
    return 1;
}


void
init()
{
    ::init();
    add_action(poison, "poison");
    add_action(poison, "coat");
}

/*
 * Function name: 
 * Description:   
 * Arguments:     
 * Returns:       
 */
