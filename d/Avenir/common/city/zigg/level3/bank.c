// Ziggurat galleria (bank.c)
// creator(s):   Zielia 2006
// last update:
//                 Lucius, Jan 2008: Added Bank ID.
// purpose:
// note:
// bug(s):
// to-do:
//
#pragma strict_types

#include "zigg.h"
#include <macros.h>

inherit ZIG_ROOM;
inherit "/lib/bank";
/*
 * We do not have any of the kesoit stuff/items as the other
 * Galleria rooms, the Exchange is too far removed to include them.
 *
 * Z.E.B.S = Ziggurat Exchange and Banking Services
 */
public void
zig_room(void)
{
    set_short("Ziggurat Exchange, north of the Galleria");
    set_long("Glossy black stone surrounds you, here, in the "+
	"Ziggurat Exchange. The stone walls and floor are "+
	"polished to a mirror shine, reflecting the lights, "+
	"shadows and other bits of activity that transpire in "+
	"their purview. The walls are formed of deeply molded, "+
	"rectangular stones which are inlaid with oversized "+
	"gold-foil coins. The floor is a smooth expanse without "+
	"break except in the centre, where a large red trefoil "+
	"is embedded. At the far end of the room, opposite the "+
	"entrance, stands a glassy-black counter behind which "+
	"clerks await your transactions. Behind the counter, "+
	"attached to the wall, can be seen a bronze plaque."+
	"@@see_nearby@@\n");

    add_item(({"floor","ground"}),
	"The floor of the Exchange is a smooth and mirror-polished "+
	"expanse of black stone. Seemlessly embedded into the centre "+
	"of it is an immense red trefoil.\n");
    add_item(({"centre","trefoil","red trefoil","carnelion","seal"}),
	"In the centre of the glossy black stone floor is seemlessly "+
	"embedded an immense trefoil seal. Upon closer inspection, you "+
	"notice the trefoil is made up completely of red carnelion. "+
	"Written repeatedly around the seal in gold lettering is the "+
	"phrase: Syb'Arus aveni Idrys.\n");
    add_item(({"wall","walls","black walls","stone walls"}),
	"The glossy black stone walls appear solid. Each large block "+
	"is surrounded by a deep molding so as to set them apart and "+
	"give the appearance of a massive grid. Inlaid into each of "+
	"large stones is an oversized gold-foil coin.\n");
    add_item(({"molding"}),
	"The molding between each stone in the black walls looks to "+
	"go deep, partly revealing just how thick and solid the walls "+
	"must be. You do not notice any skew to the grid lines formed "+
	"by the interconnected moldings, such is the meticulousness "+
	"with which they must have been lain.\n");
    add_item(({"coins","inlay","gold coins", "oversized coins",
	"inlaid coins", "gold-foil coins","nitikas"}),
	"Inlaid into each rectangular stone of the walls is an oversized "+
	"gold-foil coin. They closely resemble the wooden Sybarun coins "+
	"except instead of the stern image of the Hegemon, there is a "+
	"shrewd face of indeterminate age and race whose eyes seem to "+
	"shine with voracious greed.\n");
    add_item(({"counter","glassy counter","obsidian counter"}),
	"The counter at the back of the Exchange looks to be made from "+
	"solid slabs of obsidian, which is what lends it the distinctive "+
	"glassy sheen that is visible throughout the room. Etched into "+
	"the outward facing front of the counter are the letters "+
	"Z.E.B.S.\n");
    add_item(({"clerk","clerks"}),
	"They are clerks that help visitors to the Ziggurat Exchange "+
	"conduct whatever monetary transactions they may require. They "+
	"all appear to be either gnome or human in race, and each of "+
	"them is dressed in the same gleaming white and emerald green "+
	"uniform, making it impossible to determine rank amongst them.\n");
    add_item(({"ceiling"}),
	"The ceiling is a mystery. A subdued and luminous golden "+
	"light manages to filter through what is otherwise an "+
	"impenetrable blackness.\n");
    add_item(({"plaque", "bronze plaque"}),
	"It appears to have written information pertaining to this "+
	"establishment.\n");

    add_exit("room1", "south", 0);

    add_zigg();

    config_default_trade();
    config_trade_data();

    /* GoG Deposit object. */
    object gndep = clone_object("/d/Genesis/obj/deposit");
    gndep->set_short("deposit");
    gndep->set_bank_id(3903, "Sybarus Ziggurat");
    gndep->set_no_show_composite(1);
    gndep->move(TO);
//    remove_my_desc(gndep);
}

private string *grosse = ({
    "hobbit", "kender", "orc", "hobgoblin", "ogre", "minotaur",
});

private void
bank_fee(void)
{
    if (IN_ARRAY(TP->query_race_name(), grosse))
        set_bank_fee(25);
    else
        set_bank_fee(15);

    config_trade_data();
}

public int
change(string str)
{
    bank_fee();
    return ::change(str);
}

public int
test(string str)
{
    bank_fee();
    return ::test(str);
}

public int
minimize(string str)
{
    bank_fee();
    return ::minimize(str);
}

private string
footer(void)
{
    return " Pashat! And may the Idrys bless your "+
	"visit to the Ziggurat.\n\n NOTICE: The Ziggurat Exchange "+
	"and Banking Services branch may not be\n"+
	" held liable for transactions undertaken with the Gnomes "+
	"of Genesis division.\n We shall also not be held responsible "+
	"by any person(s) attracting the\n attention of His "+
	"most-eminent and avaricious self, Nitikas.\n\n";
}

public string
standard_bank_sign(void)
{
    bank_fee();
    return ::standard_bank_sign() + footer();
}

public int
read_sign(string str)
{
    if ((str != "bronze plaque") && (str != "plaque"))
    {
	notify_fail("Do you mean to read the sign or plaque?\n");
	return 0;
    }

    write(standard_bank_sign());
    return 1;
}

public void
init(void)
{
    ::init();
    bank_init();

    add_action(read_sign, "read");
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (IS_INFIDEL(ob))
    {
        tell_object(from, "One of the emerald-clad clerks rushes forwards "+
	    "and shoves you out the door.\n");
        tell_room(environment(from), "An emerald-clad clerk rushes "+
	    "forwards and shoves "+ QTNAME(from) +" out the door.\n", from);
        from->command("$west");
        say("The clerk shouts: Defenders! We have an infidel "+
	   "inside the Ziggurat!\n"); 
    }
}
