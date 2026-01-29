/**********************************************************************
 * - globe.c                                                        - *
 * - A small globe of Khalakor that is used for the entrance quest  - *
 * - to Eil-Galaith. It can be found on th boat (cabin) traveling   - *
 * - to Samorgan or given by members of the guild                   - *
 * - Created by Damaris@Genesis 01/2001                             - *
 * - Updated by Damaris@Genesis 08/05                               - *
 **********************************************************************/

#pragma strict_types
#include "guild.h";
inherit "/std/object";
inherit "/lib/holdable_item";
inherit "/lib/keep";
#include <stdproperties.h>
#include <macros.h>
string
long_description()
{
	if (IS_MEMBER(this_player()))
	return ("This is a small crystal globe that can fit in the palm "+
	"of a hand. The sphere itself is clear and is laden with five "+
	"ornate points of gold, which would rest perfectly within your "+
	"elven hand. Within the sphere you can see sections of land that "+
	"appear to be shaped like a 3-bladed pinwheel. The 'blades' of "+
	"land point approximately north, southeast, and southwest. "+
	"Spread in a circular chain between the tips of the blades are "+
	"small islands. You can see the sanctuary tower majestically "+
	"rising upwards on one of the isles. When the light flickers on "+
	"the globe the forests in the southwest speir sparkle "+
	"mysteriously. You see the small engraving that reads "+
	"'Khalakhor'. It looks shakable and you somehow realize you can "+
	"lift, and stare at the globe as well.\n");
	
	else
	return ("This is a small crystal globe that can fit in the palm "+
	"of a hand. The sphere itself is clear and is laden with five "+
	"ornate points of gold, which would rest perfectly within an "+
	"elven hand. Within the sphere you can see sections of land that "+
	"appear to be shaped like a 3-bladed pinwheel. The 'blades' "+
	"of land point approximately north, southeast, and southwest. "+
	"Spread in a circular chain between the tips of the blades are "+
	"small islands. When the light flickers on the globe the forests "+
	"in the southwest speir sparkle mysteriously. Underneath the "+
	"globe you see a small engraving that reads 'Khalakhor'.\n"+
	"It looks shakable.\n");
      
}

void
create_object()
{
	setuid(); seteuid(getuid());
	set_short("small crystal globe");
	set_name("globe");
	add_name("_eil-galaith_globe_");
	set_adj( ({"small", "crystal"}) );
	set_long(long_description);
	set_keep(1);
	
	add_prop(OBJ_I_WEIGHT, 400);
	add_prop(OBJ_I_VOLUME, 1200);
	add_prop(OBJ_I_VALUE,  100);
	add_prop(OBJ_M_NO_BUY,  1);
}


int
shake_globe(string str)
{
	if(!strlen(str))
	return notify_fail("Shake what?\n");
	
	if((str == "globe") || (str == "crystal globe") ||
	(str == "small crystal globe"))
	{
		if (IS_MEMBER(this_player()))
		{
			write("You shake the " + short() + " "+
			"vigorously, and the palm of your hand becomes "+
			"warm, inside the globe you notice the "+
			"sanctuary tower of Eil-Galaith glowing. A soft "+
			"whisper calls unto your soul speaking the words "+
			"of sanctuary.\n");
			say(QCTNAME(TP)+" shakes the " + short() + " "+
			"vigorously then gets a distant look in "+
			""+HIS(TP)+" eyes.\n");
			return 1;
		}
		if ((TP->query_race_name() != "elf") && (TP->query_race_name() != "half-elf")||	(TP->query_alignment() <= GUILD_MIN_ALIGN))
		{
			write("You shake the " + short() + " vigorously, "+
			"and you suddenly notice within the globe a "+
			"large tower glowing on one of the isles near "+
			"the southwest speir.\n");
			say(QCTNAME(TP)+" shakes the " + short() + " "+
			"vigorously.\n");
			return 1;
		}
		write("You shake the " + short() + " vigorously, and the "+
		"palm of your hand becomes warm, inside the globe you "+
		"notice a large tower glowing on one of the isles near "+
		"the southwest speir. A soft whisper calls unto your "+
		"soul speaking the words of sanctuary.\n");
		say(QCTNAME(TP)+" shakes the " + short() + " vigorously "+
		"then gets a distant look in "+HIS(TP)+" eyes.\n");
		return 1;
	}
}

int
lift_globe(string str)
{
	if(!strlen(str))
	return notify_fail("Lift what?\n");
	
	if((str == "globe") || (str == "crystal globe") ||
	(str == "small crystal globe"))
	{
		if (IS_MEMBER(this_player()))
		{
			write("You lift the " + short() + " up and you "+
			"can see beloved Khalakhor glisten in magical "+
			"beauty. The echos of times past flood your mind "+
			"then just as quickly they drift away.\n");
			say(QCTNAME(TP)+" lifts the " + short() + " "+
			"upwards and examines it and a wistful gleem "+
			"sparkles in "+HIS(TP)+" eyes.\n");
			return 1;
		}
		write("You lift the " + short() + " upwards and you "+
		"marvel at the beauty that is held within the fine "+
		"crystal.\n");
		say(QCTNAME(TP)+" lifts the " + short() + " upwards, "+
		"inspecting it carefully.\n");
		return 1;
	}
}
int
stare_globe(string str)
{
	if(!strlen(str))
	return notify_fail("Stare at what?\n");
	if((str == "globe") || (str == "at globe") ||
	(str == "crystal globe") || (str == "small crystal globe"))
	{
		if (IS_MEMBER(this_player()))
		{
			write("As you stare intensely at the "+
			"" + short() + " you sense yourself floating "+
			"across the vast forests, endless highlands "+
			"and proud chasms of great Khalakhor. To the "+
			"far south you see a small island and the "+
			"sanctuary tower reaching to the sky.\n");
			say(QCTNAME(TP)+" stares intensely at the "+
			"" + short() + " and a faint glow briefly "+
			"appears around "+ HIM(TP) +".\n");
			return 1;
		}
	}
}

void
init()
{
	::init();
	add_action(shake_globe, "shake");
	add_action(lift_globe, "lift");
	add_action(stare_globe, "stare");
}
