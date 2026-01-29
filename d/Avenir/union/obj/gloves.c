/* 
 * Gloves for the Union of the Warriors
 * of Shadow. Cirion 062797
 *
 * Revisions:
 *   Lucius, Aug 2016: Cleanups. Added new property so that these
 *                     fingerless gloves do not hide the Palanthas
 *                     Nails subloc.
 *
 */
#pragma strict_types

inherit "/std/armour";
inherit "/lib/keep";

#include <macros.h>
#include <wa_types.h>
#include <composite.h>
#include <stdproperties.h>

#include "../defs.h"

public void
create_armour(void)
{
    set_name("gloves");
    add_name("glove");

    set_adj(({"brown","soft","leather","fingerless"}));
    add_adj("union");
    add_adj("unworn");

    set_short("pair of soft leather gloves");
    set_pshort("pairs of soft gloves");

    set_long("These gloves are made of a tough brown leather, yet" +
      " are quite soft when worn. They cover the palms of each" +
      " hand but leave the fingers open to the air.  Upon the" +
      " back of each is the bold symbol of the Union: A black sphere" +
      " with a serpentine flame arising from it.  There is a label" +
      " sewn onto the seam.\n");

    add_item("label", "This label is sewn into the "+ short() +
      ". It says: There are several emotes associated with these gloves.\n"+
      "     Flex, tighten, stretch.\n");


    add_prop(OBJ_I_VOLUME,  300);
    add_prop(OBJ_I_WEIGHT,  264);
    add_prop(OBJ_I_VALUE,   102);

    // Do not hide Palanthas Nails
    add_prop("_obj_i_show_nails", 1);

    set_at(A_HANDS);
    set_af(TO);
    set_ac(4);
}

public mixed
wear(object ob)
{
    if (TP != ENV(TO))
	return 0;

    write("You pull "+ LANG_THESHORT(TO) +" over your hands.\n");
    say(QCTNAME(TP) +" pulls "+ LANG_ASHORT(TO) +" over " +
	HIS(TP) +" hands.\n");

    return 1;
}

public int
flex(string str)
{
    if (query_worn() != TP)
	return 0;

    if (str != "fingers" && str != "hand" && str != "gloves")
	return 0;

    write("You flex your gloved hand into a fist.\n");
    say(QCTNAME(TP) + " flexes " + HIS(TP) +
      " gloved hand into a fist.\n");

    return 1;
}

public int
tighten(string str)
{
    if (query_worn() != TP)
	return 0;

    object *weps = TP->query_weapon(-1);

    if (!sizeof(weps))
    {
	write("You tighten your gloved hand into a fist.\n");
	say(QCTNAME(TP) + " tightens " + HIS(TP) +
	  " gloved hand into a fist.\n");

	return 1;
    }

    string hand = "hand";
    if (sizeof(weps) > 1)
	hand += "s";

    write("You tighten your gloved " + hand + " around your "+
	COMPOSITE_WORDS(weps->short()) + ".\n");
    say(QCTNAME(TP) + " tightens " + HIS(TP) + " " + hand +
	" around " + HIS(TP) + " " +
	COMPOSITE_WORDS(weps->short()) + ".\n");

    return 1;
}

public int
stretch(string str)
{
    if (query_worn() != TP)
	return 0;

    if (str != "hands" && str != "fingers" && str != "hand")
	return 0;

    write("You stretch out your fingers within the " + short(TP) +
      " and curl them back into a fist.\n");
    say(QCTNAME(TP) + " stretches out " + HIS(TP) + " fingers "+
      "within " + HIS(TP) + " " + QSHORT(TO) + " and curls them "+
      "back into a fist.\n");

    return 1;
}

public void
init(void)
{
    ::init();

    add_action(flex, "flex");
    add_action(tighten, "tighten");
    add_action(stretch, "stretch");
}
