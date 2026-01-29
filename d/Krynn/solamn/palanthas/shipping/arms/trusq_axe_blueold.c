/* Mortis 03.2006
 *
 * Enchanted axe used by merchant house Trusq
 * lord's bodyguard in Palanthas.
 *
 */

inherit "/std/weapon";
inherit "/lib/keep";

#include <wa_types.h>
#include <macros.h>
#include "../../local.h"

#define PRETENDED				"_obj_has_already_been_tended"

int honed = 0, hones = 3, myhit, myhitbonus;

create_weapon()
{
	set_name("grip-axe");
	add_name(({"axe", "gripaxe"}));
	set_adj("sparkling");
	add_adj("blue");
	set_short("sparkling blue grip-axe");
	set_long("@@my_long");

	set_hit(39);
	set_pen(42 + random(4));
	set_wt(W_AXE);
	set_dt(W_SLASH);
	set_hands(W_ANYH);

	set_likely_dull(8);   // Decreased chance to dull.  Too well-tended.
	set_likely_break(10); // Same chance to break.
	
	set_keep(1);
	
	add_prop(OBJ_M_NO_SELL, "The shopkeeper cannot afford to buy " +
      "magical weapons.  You will have to find another market.\n");
    add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
    add_prop(MAGIC_AM_MAGIC,({25, "enchantment"}));
    add_prop(MAGIC_AM_ID_INFO, ({"You sense the dweomer of human enchantments "
	+ "concentrated in the core of the grip-axe's crescent blade.  Although "
	+ "focused on guiding the axe deep through armour and flesh, its power "
	+ "is enhanced each time it is honed for arcane guidance in striking "
	+ "accurately.\n", 20,
	  "Its power may only be released when honed three times and the "
	+ "enhancement will only last a short time.\n", 50}));
	add_prop(OBJ_S_WIZINFO, "You sense the dweomer of human enchantments "
	+ "concentrated in the core of the grip-axe's crescent blade.  Although "
	+ "focused on guiding the axe deep through armour and flesh, its power "
	+ "is enhanced each time it is honed for arcane guidance in striking "
	+ "accurately.\n"
	+ "Unique cap of three.  Can be honed three "
	+ "times for 2-4 extra points of hit.  Only lasts up to an hour and is "
	+ "non-cumulative.  Must be tended to by master smith Ken in Palanthas "
	+ "Arms District before it is ready to be honed.\n");

    add_prop(OBJ_I_WEIGHT, 2000 + random(1000));
    add_prop(OBJ_I_VOLUME, 1900 + random(300));
    add_prop(OBJ_I_VALUE, 1000 + random(1000));
}

string
my_long()
{
	if (honed == 0)
		return "The grip-axe has a short, contoured grip just large enough "
	+ "for one hand attached directly to its crescent blade.  Where the "
	+ "blade has been sharpened along its edge, the steel is metallic "
	+ "blue and sparkles when swung through the air.  The grip has been "
	+ "blackened and wrapped tightly in soft, black leather.\n";

	return "The grip-axe has a short, contoured grip just large enough for "
	+ "one hand attached directly to its crescent blade.  Where the blade "
	+ "has been honed along its edge, the steel is glowing with a metallic "
	+ "blue light and sparkles when swung through the air.  The grip has "
	+ "been blackened and wrapped tightly in soft, black leather which "
	+ "seems to hum in your grip.\n";
}

int
remove_hone()
{
	myhit = TO->query_hit();
	set_hit(myhit - myhitbonus);
	honed = 0;
	set_long("@@my_long@@" + "It has been cleaned, polished, oiled, and "
	+ "tended to by professionals.\n");

	object mywielder = TO->query_wielded();

	if (objectp(mywielder))
	{
		mywielder->catch_msg("The blue glow along the edge of your grip-axe "
		+ "slowly fades away.\n");
		tell_room(E(mywielder), "The blue glow along the edge of "
		+ QTNAME(mywielder) + "'s grip-axe slowly fades away.\n", mywielder);
	}

	return 1;
}

int
hone(string str)
{
	NF("Hone what?  The edge of your grip-axe?\n");
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[the] 'edge' / 'grip-axe' / 'gripaxe' / 'axe' [of] [the] [my] [axe] [gripaxe] [grip-axe]"))
		return 0;

	NF("Honing a weapon of this calibre requires that it first be tended to "
	+ "by a master smith.\n");
	if (TO->query_prop(PRETENDED) != 1)
		return 0;

	NF("The glowing metallic blue edge of the sparkling blue grip-axe "
	+ "resists your attempt to hone it further.\n");
	if (honed == 1)
		return 0;

	NF("You hone the edge of your sparkling blue grip-axe with a nearby "
	+ "stone.  A dull blue light throbs once from within the core of the "
	+ "axe's blade.\n");
	if (hones <= 0)
		return 0;

	write("You hone the edge of your sparkling blue grip-axe with a nearby "
	+ "stone.  A sparkling blue light pulses from within the core of the "
	+ "blade then moves out into the honed edge where it glows with a "
	+ "metallic blue hue.\n");
	hones--;
	honed = 1;
	set_long("@@my_long@@" + "It has been cleaned, polished, oiled, and "
	+ "tended to by professionals.\n");
	myhit = TO->query_hit();
	myhitbonus = 2 + random(3);
	set_hit(myhit + myhitbonus);
	set_alarm(3600.0, 0.0, "remove_hone");
	return 1;
}

int
swing(string str)
{
	NF("Swing what through the air?  Your grip-axe?\n");
	if (!str)
		return 0;

	if (!parse_command(str, ({}), "[the] [my] 'axe' / 'grip-axe' / 'gripaxe' [through] [the] [air]"))
		return 0;
	
	if (honed == 1)
	{
		write("You swipe your sparkling blue grip-axe through the air, its "
		+ "metallic blue glowing edge leaving sparkling blue dweomers "
		+ "trailing behind as it seems to guide your hand of its own "
		+ "volition.\n");
		say(QCTNAME(TP) + " swipes " + HIS(TP) + " sparkling blue grip-axe "
		+ "through the air, its metallic blue glowing edge leaving sparkling "
		+ "blue dweomers trailing behind.\n");
		return 1;
	}

	write("You swing your sparkling blue grip-axe through the air, its "
	+ "metallic blue edge leaving a few sparkling blue dweomers trailing "
	+ "behind.\n");
	say(QCTNAME(TP) + " swipes " + HIS(TP) + " sparkling blue grip-axe "
	+ "through the air, its metallic blue edge leaving a few sparkling "
	+ "blue dweomers trailing behind.\n");
	return 1;
}

void
init()
{
    ::init();

	ADA("hone");
	ADA("swing");
}

