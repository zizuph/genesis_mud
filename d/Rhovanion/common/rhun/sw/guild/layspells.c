inherit "/d/Rhovanion/lib/room";
#include <macros.h>
#include "/sys/stdproperties.h"
#include "/d/Rhovanion/defs.h"
#include SWS + "spellobj.h"

init()
{
	::init();
	add_action("touch_rune", "touch");
}

create_room()
{
	set_short("Lesser Rune room.");
	set_long("You have entered the room where"
		+" the lesser runes are taught to those who are able."
		+" The entire room is curved, being perfectly round,"
		+" and is formed of that same mysterious dark stone"
		+" that makes up the rest of this guild."
		+" The dark walls are covered with a dozen intricately"
		+" carved large runes, with many small runes covering the space"
		+" in between. The meaning of many of the runes has been"
		+" lost during the ages.\n");
	
	add_exit(SWG+"depart","north",0);
	
	add_prop(ROOM_I_LIGHT,1);
	add_prop(ROOM_I_INSIDE,1);
	
	add_item(({"wall","walls","stone"}),"The walls of this"
		+" chamber are made of dark stone, and are polished"
		+" smooth.  You are unable to recognize the variety of"
		+" stone from which they were made, centuries ago."
		+"  Hundreds of intricately-carved runes adorn the walls"
		+" here."
		+"\n");
	add_item("runes","@@exa_runes");	
}

int
exa_runes()
{
	int n;
	string *lrunes;
	string outtext;
	object tpso; /* this player's spell object */
	
	NF("Your mind goes blank as you look at the runes. You seem"
		+ " to have lost your knowledge of runes. Please make a"
		+ " bug report here.\n"); /* no spell object !?!? */
	if(!(tpso = TP->present("_sw_spell_object"))) return 0;
	
	lrunes = ({ });
	for(n = 0; n < N_SPELLS; n++)
	{
		if(! tpso->has_spell(ALL_SPELLS[n]) && tpso->can_learn(n))
			lrunes += ({ ALL_SPELLS[n] });
	}
	
	/* lrunes now contain all the spells TP can learn from this room.*/
				
	if(sizeof(lrunes)) /* new runes to learn */
	{
		outtext = "You study the runes on the wall. Engraved on the"
			+" wall you see the following runes :";
		for(n = 0; n < sizeof(lrunes); n++)
		{
			outtext += "\n" + CAP(ALL_SPELL[n]) + 
				ONE_OF_LIST( ({ ", enabling you to ", ", with which you"
					+ " can ", ", letting you ", ", allowing you to " }) )
					+ SPELL_DESCRIPT[n] + ".\n";
		}
		outtext += "\nTouching a rune will suffuse you with the knowledge.\n";
	}
	else
		outtext += "You study the runes on the wall, but are unable to"
			+ " learn anything from them.\n";
	
	TP->catch_msg(outtext);
	tell_room(ENV(TP), QCTNAME(TP) + " studies the runes on the wall.\n", TP);
	return 1;
}

int
touch_rune(string str)
{
	object tpso; /* this player's spell object */
	
	NF("You must name the rune you wish to touch.\n");
	if(str == "rune") return 0;
	
	NF("Nothing happens as you touch the rune. Please make"
		+ " a bug report.\n"); /* no spell object !?!? */
	if(!(tpso = TP->present("_sw_spell_object"))) return 0;
	
	NF("You find no rune with that name here.\n");
	n = member_array(str, ALL_SPELLS);
	if(n < 0) return 0;
	if(!tpso->can_learn(n)) return 0; /* not give away the names */										

	tell_room(ENV(TP), QCTNAME(TP) + " touches a rune on the wall.\n", TP);
	TP->catch_msg("You touch the rune " + str + ".\n");
	NF("The rune feels familiar under your hand, you have already"
		+" learned that rune.\n");
	if(tpso->has_spell(str)) return 0;
	
	/* Ok, rune exists and TP doesn't have it. */
	tpso->add_a_single_spell(str);
	TP->
	lrunes = ({ });
	for(n = 0; n < N_SPELLS; n++)
	{
		
		if(! tpso->has_spell(ALL_SPELLS[n]) && tpso->can_learn(n))
			lrunes += ({ ALL_SPELLS[n] });
	}
	
	TP->catch_msg("A sudden dizziness comes over you as you run your"
		+ " finger over the surface of the rune. The rune etches itself"
		+ " in your mind and the secret of the rune is imparted upon you.\n");
	tell_room(ENV(TP), QCTNAME(TP) + " looks a bit dizzy.\n");
}
