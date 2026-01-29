/*
 * Training room
 * By Finwe, May 2006
 * 
 * Removed Swimming as a skill and replaced it with SS_FORM_ENCHANTMENT
 * for faerie fire spell.
 * Finwe, Feruary 2016.
 */

#include "/d/Faerun/defs.h"
#include "/d/Faerun/guilds/drow/race/guild.h"
#include <stdproperties.h>
#include <const.h>

inherit "/d/Faerun/guilds/drow/rooms/base_room.c";
inherit "/lib/guild_support"; 
inherit "/lib/skill_raise";
inherit "/d/Shire/lib/training";

string messages;
int new_mail;

void set_up_skills();

void
create_drow_room()
{
    add_prop(ROOM_S_MAP_FILE, "drow_guild_map.txt");
    set_short("Training Cave");
    set_long(short() + ". This enlarged cave is set off away from the " +
        "rest of the guild house. It is here that drow learn skills to better prepare " +
        "themselves for their life and patrols. The sparse looking cave has a " +
        "sign posted on a wall.\n");

    add_item("sign", "There are words written on it. You should read them.\n");
    add_cmd_item(({"sign", "words"}), "read", "@@read_sign@@");

	create_skill_raise();
    set_up_skills();
	//create_guild_support();
	

    add_exit("start", "west");
}


/*
 * Function name:	init
 * Description	:
 */
void
init() 
{
	init_skill_raise();
	init_guild_support();
	//set_up_skills();

	::init();
}


void
set_up_skills() 
{
	string me;
	
	me = "be wary of your surroundings";
	sk_add_train(SS_AWARENESS,({ me, me }),     0,0,50 );
	
	me = "be able to cast air spells";
	sk_add_train(SS_ELEMENT_AIR,({ me, me }),   0,0,30 );

	me = "be able to hide in rooms";
	sk_add_train(SS_HIDE,({ me, me }),          0,0,50 );

	me = "be able to sneak into rooms";
	sk_add_train(SS_SNEAK,({ me, me }),         0,0,50 );
    
	me = "be able to travel more easily";
	sk_add_train(SS_CLIMB,({ me, me }),         0,0,50 );

	me = "be able to enchant items";
	sk_add_train(SS_FORM_ENCHANTMENT,({ me, me }), 0,0,20 );

	me = "be able to cast spells";
	sk_add_train(SS_SPELLCRAFT,({ me, me }),    0,0,30 );
	
	me = "be able to handle animals";
	sk_add_train(SS_ANI_HANDL,({ me, me }),     0,0,30 );

	me = "be able to know where you are";
	sk_add_train(SS_LOC_SENSE,({ me, me }),     0,0,30 );

	me = "be able to track something in the wild";
	sk_add_train(SS_TRACKING,({ me, me }),      0,0,30 );

	me = "be skilled using swords";
	sk_add_train(SS_WEP_SWORD,({ me, me }),      0,0,30 );


}

int
sk_improve(string str) 
{
    return ::sk_improve(str);
}


string read_sign()
{

    return "\n\n" +
    "+------------------------------------------------------+\n" +
    "| * *                                              * * |\n" +
    "|  *                                                *  |\n" +
    "|                                                      |\n" +
    "|               D R O W   S K I L L S                  |\n" +
    "|                                                      |\n" +
    "|  Drow are skilled in many abilities. Below are what  |\n" +
    "|  may learn.                                          |\n" +
    "|                                                      |\n" +
    "|      Animal Handling. . . . . Superior Layman        |\n" +
    "|      Awareness. . . . . . . . Superior Journeyman    |\n" +
    "|      Air Spells . . . . . . . Superior Layman        |\n" +
    "|      Climb. . . . . . . . . . Superior Journeyman    |\n" +
    "|      Hide . . . . . . . . . . Superior Journeyman    |\n" +
    "|      Enchantment Spells . . . Superior Amateur       |\n" +
    "|      Location Sense . . . . . Superior Layman        |\n" +
    "|      Sneak. . . . . . . . . . Superior Journeyman    |\n" +
    "|      Spellcraft . . . . . . . Superior Layman        |\n" +
    "|      Tracking . . . . . . . . Superior Layman        |\n" +
    "|      Sword. . . . . . . . . . Superior Amateur       |\n" +
    "|                                                      |\n" +
    "|  *                                                *  |\n" +
    "| * *                                              * * |\n" +
    "+------------------------------------------------------+\n\n";
}


