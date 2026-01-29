#include "/d/Krynn/common/defs.h"
#include <stdproperties.h>
#include <macros.h>

inherit "/d/Krynn/wayreth/std/out_room";

#define BETA_ROOM   "/d/Calia/guilds/elementalists/temple/ec_beta_rack"
#define TESTING_DIR "d/Calia/guilds/elementalists/temple/testing/"
#define GUILD_MANAGER "/d/Calia/guilds/elementalists/lib/guild_manager"

object golem;

void
reset_wayreth_room()
{
}

void
clone_golem()
{
    clone_object(TESTING_DIR + "test_golem")->move(TO, 1);
}

void
clone_wight()
{
    clone_object(TESTING_DIR + "test_undead_wight")->move(TO, 1);
}

void
clone_giant()
{
    golem = clone_object(TESTING_DIR + "test_giant");
    golem->arm_me();
    golem->move(TO, 1);
}

void
clone_zombie()
{
    golem = clone_object(TESTING_DIR + "test_undead_zombie");
    golem->arm_me();
    golem->move(TO, 1);
}

void
create_wayreth_room()
{
    set_long("This is a test room for the Elemental Clerics of Calia. It should " +
         "not be accessible after the guild opens.\nYou can 'create golem', " +
         "'create giant', 'create wight', or 'create zombie' here.\n" +
         "The golem and wight aren't offensive, the giant and zombie are.\n"+
         "You can also 'heal me' to restore your health, 'nuke health' to "+
         "remove your health to just above dead, 'calm me' to calm "+
         "your panic, 'mana me' " +
         "to restore your mana, 'nuke mana' to remove your mana totally, " +
         "'nuke fatigue' to remove your fatigue, "+
         "'switch reset' to reset your switching elements flag, "+
         "and 'low skills', 'mid skills', 'high skills' , 'max "+
         "skills' to set your "+
         "guild trained skills to low, mid, high and max levels.\n");
    set_short("EC test room");

    add_exit(BETA_ROOM,"beta",0);
    add_cmd_item("golem","create","@@create_golem");
    add_cmd_item("giant","create","@@create_giant");
    add_cmd_item("wight","create","@@create_wight");
    add_cmd_item("zombie","create","@@create_zombie");
    add_cmd_item("me","heal","@@heal_me");
    add_cmd_item("me","mana","@@mana_me");
    add_cmd_item("me","calm","@@calm_me");
    add_cmd_item("mana","nuke","@@nuke_mana");
    add_cmd_item("health","nuke","@@nuke_health");
    add_cmd_item("fatigue","nuke","@@nuke_fatigue");
    add_cmd_item("reset","switch","@@switch_reset");
    add_cmd_item("skills","low","@@low_skills");
    add_cmd_item("skills","mid","@@mid_skills");
    add_cmd_item("skills","high","@@high_skills");
    add_cmd_item("skills","max","@@max_skills");

    reset_wayreth_room();
}

string
create_golem()
{
    TO->clone_golem();
    return "You clone a new golem.\n";
}

string
create_wight()
{
    TO->clone_wight();
    return "You clone a new undead wight.\n";
}

string
create_giant()
{
    TO->clone_giant();
    return "You clone a new offensive giant.\n";
}

string
create_zombie()
{
    TO->clone_zombie();
    return "You clone a new offensive zombie.\n";
}

string
calm_me()
{
    TP->add_panic(-(TP->query_panic()));
    return "You calm yourself.\n";
}

string
heal_me()
{
    TP->heal_hp(10000);
    return "You heal yourself.\n";
}

string
mana_me()
{
    TP->add_mana(10000);
    return "You restore your mana.\n";
}

string
nuke_mana()
{
    TP->add_mana(-10000);
    return "You nuke your mana.\n";
}

string
nuke_health()
{
	TP->set_hp(1);
	return "You nuke your health.\n";
}

nuke_fatigue()
{
    TP->set_fatigue(TP->query_max_fatigue());
    return "You nuke your fatigue.\n";
}


string
switch_reset()
{
	GUILD_MANAGER->set_has_changed_element(TP,0);
	return "You can switch elements now.\n";
}

string
low_skills()
{
	TP->set_skill(4,20); // Club
	TP->set_skill(24, 20); // Defence
	TP->set_skill(23, 10); // Parry
	TP->set_skill(30, 30); // Spellcraft
	TP->set_skill(32, 20); // Abjuration
	TP->set_skill(39, 20); // Divination
	TP->set_skill(40, 20); // Conjuration
	TP->set_skill(33, 20); // Life 
	TP->set_skill(41, 20); // Fire
	TP->set_skill(42, 20); // Air
	TP->set_skill(43, 20); // Earth
	TP->set_skill(44, 20); // Water
	TP->set_skill(106, 20); // Location Sense
	TP->set_skill(110, 20); // Awareness
	TP->set_skill(36, 20); // Herbalism	
	
	return "You now have minimal level guild trained skills.\n";
}

string
mid_skills()
{
	TP->set_skill(4,30); // Club
	TP->set_skill(24, 35); // Defence
	TP->set_skill(23, 20); // Parry
	TP->set_skill(30, 60); // Spellcraft
	TP->set_skill(32, 45); // Abjuration
	TP->set_skill(39, 45); // Divination
	TP->set_skill(40, 45); // Conjuration
	TP->set_skill(33, 45); // Life 
	TP->set_skill(41, 45); // Fire
	TP->set_skill(42, 45); // Air
	TP->set_skill(43, 45); // Earth
	TP->set_skill(44, 45); // Water
	TP->set_skill(106, 40); // Location Sense
	TP->set_skill(110, 40); // Awareness
	TP->set_skill(36, 40); // Herbalism		
	
	return "You now have mid level guild trained skills.\n";
}

string
high_skills()
{
	TP->set_skill(4,40); // Club
	TP->set_skill(24, 60); // Defence
	TP->set_skill(23, 30); // Parry
	TP->set_skill(30, 80); // Spellcraft
	TP->set_skill(32, 60); // Abjuration
	TP->set_skill(39, 60); // Divination
	TP->set_skill(40, 60); // Conjuration
	TP->set_skill(33, 60); // Life 
	TP->set_skill(41, 60); // Fire
	TP->set_skill(42, 60); // Air
	TP->set_skill(43, 60); // Earth
	TP->set_skill(44, 60); // Water
	TP->set_skill(106, 60); // Location Sense
	TP->set_skill(110, 60); // Awareness
	TP->set_skill(36, 60); // Herbalism		
	
	return "You now have high level guild trained skills.\n";
}

string
max_skills()
{
	string element = (GUILD_MANAGER->query_primary_element(TP));
	
	switch (element)
	{
		case "fire":
			if (GUILD_MANAGER->query_is_racial(TP))
			{
				TP->set_skill(4,50); // Club
				TP->set_skill(24, 75); // Defence
				TP->set_skill(23, 40); // Parry
				TP->set_skill(30, 100); // Spellcraft
				TP->set_skill(32, 60); // Abjuration
				TP->set_skill(39, 60); // Divination
				TP->set_skill(40, 60); // Conjuration
				TP->set_skill(33, 70); // Life 
				TP->set_skill(41, 100); // Fire
				TP->set_skill(42, 70); // Air
				TP->set_skill(43, 70); // Earth
				TP->set_skill(44, 70); // Water
				TP->set_skill(106, 70); // Location Sense
				TP->set_skill(110, 70); // Awareness
				TP->set_skill(36, 80); // Herbalism
			}
			else
			{
				TP->set_skill(4,50); // Club
				TP->set_skill(24, 70); // Defence
				TP->set_skill(23, 40); // Parry
				TP->set_skill(30, 100); // Spellcraft
				TP->set_skill(32, 60); // Abjuration
				TP->set_skill(39, 60); // Divination
				TP->set_skill(40, 60); // Conjuration
				TP->set_skill(33, 70); // Life 
				TP->set_skill(41, 100); // Fire
				TP->set_skill(42, 70); // Air
				TP->set_skill(43, 70); // Earth
				TP->set_skill(44, 70); // Water
				TP->set_skill(106, 60); // Location Sense
				TP->set_skill(110, 60); // Awareness
				TP->set_skill(36, 60); // Herbalism
			}
			break;
		
		case "air":
			if (GUILD_MANAGER->query_is_racial(TP))
			{
				TP->set_skill(4,50); // Club
				TP->set_skill(24, 75); // Defence
				TP->set_skill(23, 45); // Parry
				TP->set_skill(30, 100); // Spellcraft
				TP->set_skill(32, 80); // Abjuration
				TP->set_skill(39, 80); // Divination
				TP->set_skill(40, 80); // Conjuration
				TP->set_skill(33, 70); // Life 
				TP->set_skill(41, 70); // Fire
				TP->set_skill(42, 100); // Air
				TP->set_skill(43, 70); // Earth
				TP->set_skill(44, 70); // Water
				TP->set_skill(106, 70); // Location Sense
				TP->set_skill(110, 70); // Awareness
				TP->set_skill(36, 80); // Herbalism
			}
			else
			{
				TP->set_skill(4,50); // Club
				TP->set_skill(24, 70); // Defence
				TP->set_skill(23, 40); // Parry
				TP->set_skill(30, 100); // Spellcraft
				TP->set_skill(32, 80); // Abjuration
				TP->set_skill(39, 80); // Divination
				TP->set_skill(40, 80); // Conjuration
				TP->set_skill(33, 70); // Life 
				TP->set_skill(41, 70); // Fire
				TP->set_skill(42, 100); // Air
				TP->set_skill(43, 70); // Earth
				TP->set_skill(44, 70); // Water
				TP->set_skill(106, 60); // Location Sense
				TP->set_skill(110, 60); // Awareness
				TP->set_skill(36, 60); // Herbalism
			}
			break;
		
		case "water":
			if (GUILD_MANAGER->query_is_racial(TP))
			{
				TP->set_skill(4,50); // Club
				TP->set_skill(24, 80); // Defence
				TP->set_skill(23, 45); // Parry
				TP->set_skill(30, 100); // Spellcraft
				TP->set_skill(32, 80); // Abjuration
				TP->set_skill(39, 80); // Divination
				TP->set_skill(40, 80); // Conjuration
				TP->set_skill(33, 70); // Life 
				TP->set_skill(41, 70); // Fire
				TP->set_skill(42, 70); // Air
				TP->set_skill(43, 70); // Earth
				TP->set_skill(44, 100); // Water
				TP->set_skill(106, 70); // Location Sense
				TP->set_skill(110, 70); // Awareness
				TP->set_skill(36, 80); // Herbalism
			}
			else
			{
				TP->set_skill(4,50); // Club
				TP->set_skill(24, 70); // Defence
				TP->set_skill(23, 40); // Parry
				TP->set_skill(30, 100); // Spellcraft
				TP->set_skill(32, 80); // Abjuration
				TP->set_skill(39, 80); // Divination
				TP->set_skill(40, 80); // Conjuration
				TP->set_skill(33, 70); // Life 
				TP->set_skill(41, 70); // Fire
				TP->set_skill(42, 70); // Air
				TP->set_skill(43, 70); // Earth
				TP->set_skill(44, 100); // Water
				TP->set_skill(106, 60); // Location Sense
				TP->set_skill(110, 60); // Awareness
				TP->set_skill(36, 60); // Herbalism
			}
			break;
			
		case "earth":
			if (GUILD_MANAGER->query_is_racial(TP))
			{
				TP->set_skill(4,50); // Club
				TP->set_skill(24, 80); // Defence
				TP->set_skill(23, 40); // Parry
				TP->set_skill(30, 100); // Spellcraft
				TP->set_skill(32, 60); // Abjuration
				TP->set_skill(39, 60); // Divination
				TP->set_skill(40, 60); // Conjuration
				TP->set_skill(33, 70); // Life 
				TP->set_skill(41, 70); // Fire
				TP->set_skill(42, 70); // Air
				TP->set_skill(43, 100); // Earth
				TP->set_skill(44, 70); // Water
				TP->set_skill(106, 70); // Location Sense
				TP->set_skill(110, 70); // Awareness
				TP->set_skill(36, 80); // Herbalism
			}
			else
			{
				TP->set_skill(4,50); // Club
				TP->set_skill(24, 70); // Defence
				TP->set_skill(23, 40); // Parry
				TP->set_skill(30, 100); // Spellcraft
				TP->set_skill(32, 60); // Abjuration
				TP->set_skill(39, 60); // Divination
				TP->set_skill(40, 60); // Conjuration
				TP->set_skill(33, 70); // Life 
				TP->set_skill(41, 70); // Fire
				TP->set_skill(42, 70); // Air
				TP->set_skill(43, 100); // Earth
				TP->set_skill(44, 70); // Water
				TP->set_skill(106, 60); // Location Sense
				TP->set_skill(110, 60); // Awareness
				TP->set_skill(36, 60); // Herbalism
			}
			break;
			
		case "life":
			if (GUILD_MANAGER->query_is_racial(TP))
			{
				TP->set_skill(4,50); // Club
				TP->set_skill(24, 75); // Defence
				TP->set_skill(23, 45); // Parry
				TP->set_skill(30, 100); // Spellcraft
				TP->set_skill(32, 80); // Abjuration
				TP->set_skill(39, 80); // Divination
				TP->set_skill(40, 80); // Conjuration
				TP->set_skill(33, 100); // Life 
				TP->set_skill(41, 70); // Fire
				TP->set_skill(42, 70); // Air
				TP->set_skill(43, 70); // Earth
				TP->set_skill(44, 70); // Water
				TP->set_skill(106, 70); // Location Sense
				TP->set_skill(110, 70); // Awareness
				TP->set_skill(36, 80); // Herbalism
			}
			else
			{
				TP->set_skill(4,50); // Club
				TP->set_skill(24, 70); // Defence
				TP->set_skill(23, 40); // Parry
				TP->set_skill(30, 100); // Spellcraft
				TP->set_skill(32, 80); // Abjuration
				TP->set_skill(39, 80); // Divination
				TP->set_skill(40, 80); // Conjuration
				TP->set_skill(33, 100); // Life 
				TP->set_skill(41, 70); // Fire
				TP->set_skill(42, 70); // Air
				TP->set_skill(43, 70); // Earth
				TP->set_skill(44, 70); // Water
				TP->set_skill(106, 60); // Location Sense
				TP->set_skill(110, 60); // Awareness
				TP->set_skill(36, 60); // Herbalism
			}
			break;
	}
	
	return "You now have max level guild trained skills.\n";
}
