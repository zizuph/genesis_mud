/*
 * Half Orc Guild soul racial
 *
 * Nerull, 2022
 *
 */

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";
inherit "/d/Faerun/guilds/half_orcs/souls/ho_emotes";

#include "/d/Faerun/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <login.h>


public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Half Orc Racial"; }

public mapping
query_ability_map()
{
    return ([
            ]);
}


public mapping
query_cmdlist()
{
    return ([
	    "hohelp"       : "hohelp",
        "horoar"       : "horoar",
        "holaugh"      : "holaugh",
        "hostretch"    : "hostretch",
        "hothink"      : "hothink",
        "hoscowl"      : "hoscowl",
        "hogreet"      : "hogreet",
        "hoamused"     : "hoamused",
        "hofrown"      : "hofrown",        
            ]);
}


int
hohelp(string str)
{ 
    if (str == "emotes")
    {
        write("");     
		write("|===========================================================|\n");
		write("|             H A L F   O R C ,   E M O T E S               |\n");
        write("|-----------------------------------------------------------|\n");
        write("| horoar          : Let out a terrifying roar.              |\n");
		write("| holaugh         : Let out a hearty laugh.                 |\n");
		write("| hostretch       : Display your impressive physique.       |\n");
		write("| hothink         : Contemplate things.                     |\n");
		write("| hoscowl         : Scowl at someone.                       |\n");
		write("| hogreet         : Greet someone.                          |\n");
		write("| hoamused        : Show your amusement.                    |\n");
		write("| hofrown         : Frown at someone.                       |\n");
		write("|___________________________________________________________|\n");
		
		return 1;		
	}
	
	
	if (str == "about")
    {
        write("");     
		write("|===========================================================|\n");
		write("|             H A L F   O R C ,   A B O U T                 |\n");
        write("|-----------------------------------------------------------|\n");
        write("| Whether united under the leadership of a mighty warlock   |\n");
		write("| or having fought to a standstill after years of           |\n");
		write("| conflict, orc and human communities, sometimes form       |\n");
		write("| alliances.                                                |\n");
		write("|                                                           |\n");
        write("| When these alliances are sealed by marriages, half-orcs   |\n");
		write("| are born. Some half-orcs rise to become proud leaders of  |\n");
		write("| orc communities. Some venture into the world to prove     |\n");
		write("| their worth. Many of these become adventurers, achieving  |\n");
		write("| greatness for their mighty deeds.                         |\n");
        write("|                                                           |\n");
        write("| The one-eyed god Gruumsh-lord of war and fury created the |\n");
		write("| first orcs, and even those orcs who turn away from his    |\n");
		write("| worship carry his blessings of might and endurance. The   |\n");
		write("| same is true of half-orcs. Some half-orcs hear the        |\n");
		write("| whispers of Gruumsh in their dreams, calling them to      |\n");
		write("| unleash the rage that simmers within them. Others feel    |\n");
		write("| Gruumsh's exultation when they join in melee combat - and |\n");
		write("| either exult along with him or shiver with fear and       |\n");
		write("| loathing.                                                 |\n");
        write("|                                                           |\n");
        write("| Beyond the rage of Gruumsh, half-orcs feel emotion        |\n");
		write("| powerfully. Rage doesn't just quicken their pulse, it     |\n");
		write("| makes their bodies burn. An insult stings like acid, and  |\n");
		write("| sadness saps their strength. But they laugh loudly and    |\n");
		write("| heartily, and simple pleasures - feasting, drinking,      |\n");
		write("| wrestling, drumming, and wild dancing - fill their hearts |\n");
		write("| with joy. They tend to be short-tempered and sometimes    |\n");
		write("| sullen, more inclined to action than contemplation and    |\n");
		write("| to fighting than arguing. And when their hearts swell     |\n");
		write("| with love, they leap to perform acts of great kindness    |\n");
		write("| and compassion.                                           |\n");
		write("|___________________________________________________________|\n");
		
		return 1;		
	}
	
	write("");     
	write("|===========================================================|\n");
	write("|               H A L F   O R C ,   H E L P                 |\n");
	write("|-----------------------------------------------------------|\n");
	write("| hohelp          : This menu.                              |\n");
	write("|                                                           |\n");
	write("| hohelp about    : About the Half Orcs.                    |\n");
	write("|                                                           |\n");
	write("| hohelp emotes   : List of emotes for half orcs.           |\n");
	write("|___________________________________________________________|\n");
	
	return 1;
}