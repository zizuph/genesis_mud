/*
 * Magical axe wielded by Koen, sergant of the Neverwinter guard
 * at the bridge blocade
 * ~faerun/highroad/bridge/rooms/bri00
 * by Kehr, Mar 2007
 */

#pragma save_binary
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <wa_types.h>

inherit FAERUN_WEP_BASE;

#define ADJ1        "jet-black"
#define ADJ2        "crescent"
#define WEAPON      "waraxe"
#define WEP_TYPE    W_AXE
#define DAMAGE      W_SLASH

#define HIT	47
#define PEN	48


// this is not a special and not a combat aid !
// this function may hurt the WIELDER of the weapon
// when s/he examines the reflection on the axe
void hurt_me (object victim)
{
	if (objectp(victim)) {
		victim->command("$scream");
		victim->heal_hp(-500);
	}
}
	

string movie0() {
	int phase;
	string str;
	
	tell_room (ENV(TP), QCTNAME(TP) + " stares intensly at " + TP->query_possessive() + 
		" axe.\n", TP); 
	
	if (TP->query_mana() < 1000) 
		return "You feel to weak to focus on the reflection.\n"; 

	// suck mana
	//TP->add_mana(-10);	// testing
	TP->add_mana(-1000);
	
	phase = TP->query_prop("_koens_axe_movie");
	if (phase > 12)
		phase = 0;
		
	TP->add_prop("_koens_axe_movie", phase + 1);
	
	switch(phase) {
		case 0:
			str = "You take a look at the reflections and suddenly realize " +
				"that they move with blurring speed and do not resemble anything " +
				"around you. You slowly realize that what you see is a " + 
				"battlefield, with a swarm of warriors clashing their weapons " +
				"in a deadly struggle. You see a face rapidly closing to you " +
				"at a weird angle and then suddenly the vision blurrs...\n";
			break;
		case 1:
			str = "As you stare intensly at the reflection the vision slowly " +
				"reappears. There is a warrior before you and you seem to be " +
				"following him. In a swift movement you " +
				"rise high above and then, just before burying into his head " +
				"a greatsword clashes with you, sending thousands " + 
				"of sparks all around.\n";
			break;
		case 2:
			str = "You carefully look at the axe, searching for a vision again. " +
				"You seem to have moved forward on the battlefield, the enemy " +
				"unable to stop you advance. You see corpses all around, bloodied " +
				"and crushed. You seem to hear joyfull shouts of victory, mixed " +
				"with the cries of wounded. Suddenly a great shade blocks the sun " +
				"and everyone around immediately silence...\n";
			break;
		case 3:
			str = "You are moving fast, but the beast always keeps up. " +
				"You see as warriors around disappear when it swiftly dives from the " +
				"sky and grabs them in its claws. You hear a short intake and then " +
				"pain filled shouts from unfortunate victims of creature's fiery breath. " +
				"The forest is slowly getting closer and perhaps, just perhaps it " +
				"would provide enough cover for warriors to hide.\n";
			break;
		case 4:
			str = "You seem to be lying on the ground. There are just a few men sitting " +
				"nearby, all deadly tired, charred and bruised. They are in a narrow " +
				"valley, with only one path to follow. And going back is not an option " +
				"as the beast still circles high in the air. One of the warriors extends " +
				"his hand toward you.\n";
			break;
		case 5:
			str = "It is the end of the path. There is no escape with the dragon behind " +
				"you and the Sorcerer before. You do know there is no hope as this man " +
				"feels no mercy and shows no grace. Warriors around lower their weapons " +
				"slightly bow their heads, telling last prayers, words of love " +
				"for their families and curses for the enemy and the fate.\n";
			break; 
		case 6:
			str = "Everything around you is in flames. You feel extreme pain.\n";
			set_alarm(3.0, 0.0, &hurt_me(TP));
			break;
		case 7..10: 
			str = "You look at the reflections... You feel cold and alone.\n";
			break;
		case 11:
			str = "There is light again! At least a trace of it that manages " +
				"to reach you through the gaps between the boards. You hear " +
				"the merry shouts, ocassional curses and bursts of uncontrolled " +
				"laughter.\n";
			break;
		case 12:
			str = "Someone opens the lid and lifts you up. You see an elderly tall " +
				"human, with worried face. He extends his hand towards you and then " +
				"moves you towards a muscular, cold-eyed dwarf.\n";
			break;
		default:
			str = "You sense that this should not have happened... The bugs " +
				"are crawling all over you.\n";
	}
	return str;
}

string metal_type() {
	if (TP->query_guild_name_craft()=="The Smiths Guild")
		return "some weird metal alloy";
	return "an unknown metal";
}

string metal_description() {
	if (TP->query_guild_name_craft()=="The Smiths Guild")
		return "You study the blade carefully and soon realize, that it must " +
			"have been created from an alloy of at least three different metals. " +
			"You are absolutely sure that iron was one of them, however the rest " +
			"of the ingredients is unknown to you.";
	return "Its some metal. What else could it be ?";
}


void create_faerun_weapon()
{
    set_name("axe");
    add_name(WEAPON);
    set_adj(ADJ1);
    set_adj(ADJ2);
    set_short(ADJ1 + " " + ADJ2 + " " + WEAPON); 
    set_long("This axe has been forged from @@metal_type@@, black but " +
    	"still casting slight reflections. Its sharp crescent blade is " +
    	"quite heavy, ensuring that a hit would not go unnoticed. " +
		"The haft of the axe was made from from steel-hard dried " +
		"hickory. Gentle curve of its belly leads to the leather-bound " +
		"grip.\n");

    add_item("leather", "The axe's handle has been wrapped with green, rough " +
	"leather.\n");
    add_item(({"reflection", "reflections"}), movie0);
    add_item(({"metal", "alloy"}), metal_description);
	
    set_hit(HIT);
    set_pen(PEN);
    set_wt(WEP_TYPE); 
    set_dt(DAMAGE); 
	set_hands(W_LEFT); 
    
    add_prop(OBJ_I_WEIGHT, F_WEIGHT_DEFAULT_WEAPON(PEN, WEP_TYPE)+random(1000)-500);
    add_prop(OBJ_I_VOLUME, 2500 + random(500));
    add_prop(OBJ_I_VALUE, F_VALUE_WEAPON(HIT,PEN) + random(500)-250);
	add_prop(OBJ_I_IS_MAGIC_WEAPON, 1);
	add_prop(MAGIC_AM_MAGIC, ({ 22, "enchantment" }));  // value as good as any other...
	add_prop(MAGIC_AM_ID_INFO, ({
		"Extreme heat must have been applied to this axe.\n", 10,
		"Searing flames treated its blade.\n", 20, 
		"Its been hit with the blast of flame spell.\n", 50
	}));
	
	add_prop(OBJ_S_WIZINFO,
    	"----------------------------------------------------------------------------\n" +
        "This axe is wielded by Koen, dwarf sergeant near Neverwinter " +
        "(/d/Faerun/highroad/bridge/npcs/sergeant.c)\n " +
        "\n" +
        "Parameters: hit = " + HIT + ", PEN = " + PEN + "\n" +
        "Specials: none\n" +
        "Other: \n" + 
        "  - Smiths get slightly different description\n" +
        "  - Player can examine the reflection, which tells him a little\n" +
        "    of the axes' history. It drains mana (1000 each time) and\n" +
        "    health (500 once)\n" +
        "----------------------------------------------------------------------------\n");
	
	
    
}

/* IT WAS ONLY EXPERIMENTAL !
int
did_hit(int aid, string hdesc, int phurt,
		        object enemy, int dt, int phit, int dam)
{
    object me = ENV(TO);
    mixed* hitresult;

    ::did_hit();

    enemy->heal_hp(-100);
    return 1;
}    
*/

