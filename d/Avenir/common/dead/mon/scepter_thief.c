// file name:        /d/Avenir/common/dead/mon/scepter_thief.c
// creator(s):       Lilith, July 2021
// revision history: Lilith, Sep 2021 added death mask to cloned items.
// purpose:          Quest npc for Hegemon Ghost Quest
//                   modified from sneaky human in the bazaar
// bug(s):           
// to-do:
inherit "/d/Avenir/inherit/monster";
#include "../dead.h"
#include <language.h>
#include <ss_types.h>

string
sneak_away()
{
    string *directions = ENV(TO)->query_exit_cmds();

    if (sizeof(directions))
	command("sneak "+ directions[random(sizeof(directions))]);
    add_panic(15);
    return "";
}


void
create_monster()
{
    ::create_monster();

    set_name("gnome");
	set_living_name("tigiluligiti");
    add_name(({"thief", "follower of nitikas", "tigi", "_Scepter_Thief"}));
    set_adj(({"wide-eyed", "edgy"}));
    set_race_name("gnome");
    set_gender(G_FEMALE);
    set_short("wide-eyed edgy female gnome");
    set_long("This wide-eyed edgy female gnome is one of the few "
	    +"living beings you've seen in this place.\n"
		+"She has a tattoo of a gold coin on the inside of her wrist.\n"
		+"She is quite small, even for a gnome.\n");
	
    set_alignment(0);
	set_default_answer("say NO time for answering questions if I want "
	    +"to get out of here alive!", 1);
    default_config_npc(50 +random(25));   
    set_hp(query_max_hp());
	set_monster_home("crypt");
    set_restrain_path(CRYPT +"crypt20");

    set_skill(SS_DEFENCE, 40 +random(40)); 	
    set_skill(SS_AWARENESS, 50);    
    set_skill(SS_BLIND_COMBAT, 40 +random(30));
	set_skill(SS_UNARM_COMBAT, 40 +random(20));
    set_skill(SS_HIDE, 30);
    set_skill(SS_SNEAK, 30);

    NEVERKNOWN;
	add_prop(NPC_I_NO_LOOKS, 1);
	add_prop(OBJ_I_VOLUME, 25000);
	add_prop(OBJ_I_WEIGHT, 25000);
    set_act_time(2);
    add_act(sneak_away);
}

/* Logging death info. 
 * Cloning these quest items when npc is dying
 * to prevent then from being stolen and 
 * disappointing the questor.
 */
void
do_die(object killer)
{	
   // waiting to clone these now so they don't get stolen.
   if (!present("_Hegemon_Scepter_Top"))
       add_weapon(OBJ +"scepter_top");
   if (!present("_Hegemon_Scepter_Wand"))
       add_weapon(OBJ +"scepter_wand");
   if (!present("_Avenir_death_mask"))
       add_armour(OBJ +"death_mask");	
   //This is from /d/Avenir/smis/sys/statserv.h included in the dead.h file.
    STATSERV_LOG_EVENT("crypt", "Scepter thief killed");
 
    ::do_die(killer);
}

