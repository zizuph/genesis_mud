
/*
 * /d/Shire/claws/obj/guildobj.c
 *
 * The 'guild' object for the Black Claws.
 * This object is carried by he who is captain of the claws
 * and if he dies, he'll drop the object, and be kicked out
 * as captain. He will be set to scout. The object will be 
 * in random spots throughout the guild-halls, and/or tunnels.
 * The first orc to find it, he will become the new Captain, with
 * all the powers that come with it.
 *
 * Turgon, 17.10.96
 *
 * Modification log:
 *
 */
#pragma save_binary

inherit "/std/armour";

#include "/d/Shire/guild/claws/claw_defs.h"
#include "/d/Shire/skills.h"
#include <stdproperties.h>
#include <ss_types.h>
#include <language.h>
#include <formulas.h>
#include <composite.h>
#include <wa_types.h>
#include <macros.h>

#define CAPTAIN_SUBLOC "_captain_subloc_"

int initiated;


create_armour()
{
	set_name("crown");
	add_name("_captain_ob_");
	set_pname("crowns");
	set_adj("iron");
	set_short("iron crown");
	set_long("The Iron Crown symbolize the true ruler of the "+
	"Black Claws. There are some runes inscribed in the crown, "+
	"which appear to be written in the tongue of the orcs.\n");
	set_at(A_HEAD);
	set_am(({0, 0, 0}));
	set_ac(30);

	add_item("runes", VBFC("read_runes"));
	add_item("crown", "The crown is inserted with some weird "+
		"gems, and it looks old and rusty.\n");

	add_prop(OBJ_I_VALUE, 0);
	add_prop(OBJ_I_WEIGHT, 10000);
	add_prop(OBJ_I_VOLUME, 40);
	remove_prop(OBJ_I_NO_DROP);
	add_prop(OBJ_I_NO_STEAL, 1);
	setuid(); seteuid(getuid());
	
	initiated = 0;
}
 

void
read_runes()
{
	write("You carefully study the runes, written in the Black Speech:\n");
	write("\n I Fingolf made this Crown as a present for our great\n"+
		" friend Sauron!\n");
	return;
}
