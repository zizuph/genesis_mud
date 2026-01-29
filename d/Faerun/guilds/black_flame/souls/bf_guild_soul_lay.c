/* /d/Faerun/guilds/black_flame/souls/bf_guild_soul_lay.c
*
*  Black Flame Guild soul.
*
*  Nerull, 2022
*
*/
#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";
inherit "/d/Faerun/guilds/black_flame/souls/bf_emotes";
inherit "/d/Gondor/common/lib/tail.c";

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
#include <const.h>
#include <flags.h>
#include <formulas.h>

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Black Flame"; }


public mapping
query_ability_map()
{

    return ([
            "flame":BF_GUILD_DIR + "specials/flame",
            ]);
}


public mapping
query_cmdlist()
{
    seteuid(getuid());
    
    return ([
        // commands
        "bfhelp"            : "s_bfhelp",
        "bftitles"          : "do_bftitles",
        "bfsummon"          : "do_bf_summon",
        "bfcheck"           : "do_bfcheck",
                      
        
        // Specials and Abilties
        "flame"             : "do_ability",
		
		 // Spells
        "flamepurge"        : "do_ability",
        "flashbang"         : "do_ability",
        "frenzy"            : "do_ability", 
        "medicate"          : "do_ability",        
        "polymorth"         : "do_ability",   
        "reconstitute"      : "do_ability",
        "mesmerize"         : "do_ability",
        
        // Emotes        
        "bfregard"          : "bfregard",
        "bfhail"            : "bfhail",
        "bfack"             : "bfack",
        "bfbless"           : "bfbless",
        "bfassess"          : "bfassess",
        "bfrage"            : "bfrage",
        "bfbored"           : "bfbored",
        "bfcelebrate"       : "bfcelebrate",
        "bfshowoff"         : "bfshowoff",
        "bfsuggest"         : "bfsuggest",
        "bftitles"          : "do_bftitles",
        ]);
       
}


int
s_bfhelp(string str)
{ 
    if (str == "commands")
    {
        write("");                    
        write("|===========================================================|\n");
        write("|     O R D E R   O F   T H E   B L A C K   F L A M E       |\n");
        write("|                                                           |\n");       
        write("|                      C O M M A N D S                      |\n");  
        write("|-----------------------------------------------------------|\n");
        write("| flame            : Combat special. Requires a weapon      |\n");     
        write("|                    engulfed in the black flame.           |\n"); 
        write("|                                                           |\n");   
        write("| bfsummon         : Summons the black flame on your        |\n");     
        write("|                    weapon.                                |\n");                
        write("|___________________________________________________________|\n");
            
        return 1;
    }
    
    if (str == "emotes")
    {
        write("");
 
        write("|===========================================================|\n");
        write("|     O R D E R   O F   T H E   B L A C K   F L A M E       |\n");
        write("|                                                           |\n");       
        write("|                        E M O T E S                        |\n");  
        write("|-----------------------------------------------------------|\n");
        write("|                                                           |\n");   
        write("| bfregard     - Regard someone.                            |\n");
        write("| bfhail       - Hail someone in the name of the Fire Lord. |\n");
        write("| bfack        - Acknowledge someone.                       |\n");
        write("| bfbless      - Proclaim a blessing in the name of the     |\n");
        write("|                Fire Lord.                                 |\n");
        write("| bfassess     - Scrutinize someone.                        |\n");
        write("| bfrage       - Curse violently, showing your rage.        |\n");
        write("| bfbored      - Show how bored you are.                    |\n");           
        write("| bfcelebrate  - celebrate, in homage to the Fire Lord.     |\n");  
        write("| bfshowoff    - Displaying the black flame in all its      |\n");
        write("|                glory.                                     |\n");
        write("| bfsuggest    - Suggest the need of a purification.        |\n");
        write("| bftitles     - Displaying the available titles of the     |\n");
        write("|                members of the order.                      |\n");
        write("|___________________________________________________________|\n");
        
        
        return 1;
    }
    
    if (str == "recipes")
    {
        write("");         
        write("|===========================================================|\n");
        write("|     O R D E R   O F   T H E   B L A C K   F L A M E       |\n");
        write("|                                                           |\n");       
        write("|                       R E C I P E S                       |\n");  
        write("|-----------------------------------------------------------|\n");
		write("| *A large alchemy set is required to craft the products of |\n");
		write("|  these recipes.                                           |\n");
		write("|                                                           |\n");
		write("| *ALL recipes require a jar of Fire Water!                 |\n");
        write("|                                                           |\n"); 
        write("|     Vial name                         Herb Component      |\n"); 
		write("|     ---------                         --------------      |\n"); 
		write("|     Purgatory                         bilberry            |\n"); 
		write("|     Flare                             locoweed            |\n"); 
		write("|     Fury                              ginger              |\n"); 
		write("|     Polyjuice                         amanita             |\n"); 
		write("|     Convalesce                        hawthorn            |\n"); 
        write("|                                                           |\n"); 
        write("|___________________________________________________________|\n");
        
        return 1;
    }
          
    write("|===========================================================|\n");
    write("|     O R D E R   O F   T H E   B L A C K   F L A M E       |\n");
    write("|                                                           |\n");       
    write("|                          H E L P                          |\n");  
    write("|-----------------------------------------------------------|\n");
    write("|  > bfhelp                  : This list                    |\n");
    write("|  > bfhelp emotes           : List of emotes               |\n");
    write("|  > bfhelp commands         : List of commands             |\n");
    write("|  > bfhelp recipes          : List of tools of the trade   |\n");
    write("|___________________________________________________________|\n");      
    
    return 1;   
}


int
do_bftitles()
{
    write("   Titles within the Order of the Black Flame\n");
    write("   ==========================================\n");   
    write("   Black Flame Initiate\n");
    write("   Black Flame Adept\n");
    write("   Black Flame Acolyte\n");
    write("   Devotee of Black Fire\n");
    write("   Fury of the Black Flame\n");
    write("   Pillar of Black Fire\n");
    write("   Righteous Fire\n");
    write("   Devoted Pyre of the Black Flame\n");
    write("   Zealeous Pyre of the Black Flame, Torch of the Faith\n");
    write("   Black Flame Zealot\n");
    write("\n");
    
    return 1;
}


int do_bfcheck(string str)
{
    if (!str)
    {
        write("Check on who?\n");
        
        return 1;
    }
    write("Your eyes darken with black fire as you inquire with "
	+"the spy network the whereabouts of "+capitalize(str)
	+", and in your mind's eye you hear ...:\n");
    BF_MAPPINGS->ask_about_encountered(str);
    
    return 1;
}


int
do_bf_summon()
{
    object weapon0, weapon1, env;
    
    setuid();
    seteuid(getuid());
 
 
    weapon0 = this_player()->query_weapon(W_LEFT);
    weapon1 = this_player()->query_weapon(W_RIGHT);

    env = environment(this_player());
         
    tell_room(env, QCTNAME(this_player()) 
    + " mutters something strange.\n", this_player());
    
    if (weapon0 == 0 && weapon1 == 0)
    {
        write("You need to wield a weapon in order to summon "
        +"the black flames.\n");
        
        return 1;
    }

    if (weapon0 != 0)
    {
        if (weapon0->query_bf_summoned() == 0)
        {
            //write("You summon black flames upon the "
            //+ weapon0->short() + ".\n");
            
            
            clone_object(BF_FLAMES)->shadow_me(weapon0);
            
            weapon0->set_playa(this_player());
            weapon0->enchant_weapon(99999);
        }
        else
        write("The "
            + weapon0->short() + " is already engulfed in "
            +"the black flames.\n");
    }
    
    if (weapon1 != 0)
    {
        if (weapon1->query_bf_summoned() == 0)
        {
            //write("You summon black flames upon the "
            //+ weapon0->short() + ".\n");
            
            clone_object(BF_FLAMES)->shadow_me(weapon1);
            
            weapon1->set_playa(this_player());
            weapon1->enchant_weapon(99999);
        }
        else
        write("The "
            + weapon1->short() + " is already engulfed in "
            +"the black flames.\n");
    }
    
    return 1;
}
