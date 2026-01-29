/*
 * Fire Knives Guild soul
 *
 * Nerull, 2018
 *
 */

#include "/d/Genesis/specials/defs.h"

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";

#include "/d/Faerun/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <composite.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <macros.h>
#include <wa_types.h>

#include <const.h>
#include <flags.h>
#include <formulas.h>

#define ASSIST_BACKSTAB "_assist_backstab"

string chip_component;
string shop_component;
string herb_component;

object wield_par;

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Fire Knives"; }

public mapping
query_ability_map()
{

    return ([
            //"backstabtest":FIREKNIVES_GUILD_DIR + "specials/backstabtest",
            "backstab":FIREKNIVES_GUILD_DIR + "specials/backstab",
            "eviscerate":FIREKNIVES_GUILD_DIR + "specials/eviscerate",
            "envenom":FIREKNIVES_GUILD_DIR + "specials/envenom",
            "garrote":FIREKNIVES_GUILD_DIR + "specials/garrote",
            "stun":FIREKNIVES_GUILD_DIR + "specials/stun",
            "evade":FIREKNIVES_GUILD_DIR + "specials/evade",
            "blind":FIREKNIVES_GUILD_DIR + "specials/blind",
            ]);
}


public mapping
query_cmdlist()
{
    return ([
        // Commands
        "filist"                         : "filist",
        "fiemotes"                       : "fiemotes",
        "fihelp"                         : "s_fihelp",
        "fiincognito"                    : "s_fiincognito",
        "fiautosneak"                    : "fiautosneak",
        "fianalyze"                      : "do_fianalyze",
        
        
        "fivisitpermission_elder"        : "visit_guild_permission_elder",
        "fivisitpermission_fist"         : "visit_guild_permission_fist",
        "fivisitpermission_inquisitor"   : "visit_guild_permission_mentor",
        "fivisitpermission_conference"   : "visit_guild_permission_conference",
		
	    "fiaddlibrarian"                 : "do_addlibrarian",
        "firemovelibrarian"              : "do_removelibrarian",
        
        "fiaddwhisper"                   : "do_addwhisper",
        "firemovewhisper"                : "do_removewhisper",
		
		"fiaddhonorable"                 : "do_addhonorableposition",
        "firemovehonorable"              : "do_removehonorableposition",
       
	    "fimemberlist"                   : "fimemberlist",
        "fititlelist"                    : "do_fititlelist",
        "fienemylist"                    : "fienemylist",      
        "fiaddenemy"                     : "fiadd_enemy",
        "firemoveenemy"                  : "firemove_enemy",
        "ficrowlist"                     : "ficrowlist",      
        "fiaddcrow"                      : "fiadd_crow",
        "firemovecrow"                   : "firemove_crow",
        "fiexpel"                        : "do_fiexpel",
        "fiexecute"                      : "do_fiexecute",
        "fireward"                       : "increase_rank",
        "fipunish"                       : "decrease_rank",
        "fiexchange_fist"                : "do_fiexchange_fist",
        "fiexchange_inquisitor"          : "do_fiexchange_inquisitor",
        "fipromote_inquisitor"           : "do_fipromote_mentor",
        "fipromote_fist"                 : "do_fipromote_thefist",
        "fidemote_councilmember"         : "do_fidemote_councilmember",
        "fileader"                       : "do_fileader",
        "firesign"                       : "do_firesign",
        "fiactivity"                     : "do_fiactivity",
        "figuildaccept"                  : "join_guild_permission",  
		"fifullmembertest"               : "become_fullmember_test",
        "ficontractcompletepermission"   : "contract_complete_permission",
        "ficontractaddpermission"        : "contract_create_permission",       
        "fimeetingroompermission"        : "contract_meetingroom_permission", 
        
        "figarroteenable"                : "reward_ability1",
        "fievadeenable"                  : "reward_ability2",
        "fiblindenable"                  : "reward_ability3",
        "fistunenable"                   : "reward_ability4",
        "fitorpefyenable"                : "reward_ability5",
        
        "figarroteremove"                : "remove_ability1",
        "fievaderemove"                  : "remove_ability2",
        "fiblindremove"                  : "remove_ability3",
        "fistunremove"                   : "remove_ability4",
        "fitorpefyremove"                : "remove_ability5",
        
        "betray"                         : "betray_the_outfit",       
        "fiboss"                         : "add_boss",
        "fihang"                         : "do_fihang",
            
        // Emotes
        "fiindicate"                     : "do_fiindicate",
        "fibow"                          : "do_fibow",
        "fiack"                          : "do_fiack",
        "fiback"                         : "do_fiback",
        "fitap"                          : "do_fitap",
        "fiprice"                        : "do_fiprice",
        "figaze"                         : "do_figaze",
            
        "fiangry"                        : "do_fiangry",
        "ficrouch"                       : "do_ficrouch",
        "fiprepare"                      : "do_fiprepare",
        "fipay"                          : "do_fipay",
        "fistretch"                      : "do_fistretch",
        "fistance"                       : "do_fistance",
        "fiscan"                         : "do_fiscan",
        "fibback"                        : "do_fibback",
        "fithreaten"                     : "do_fithreaten",
        "fibreak"                        : "do_fibreak",
		"fiassist"                       : "do_fiassist",
        
        // Specials and Abilties
        //"backstabtest"                   : "do_ability",
        "backstab"                       : "do_ability",
        "eviscerate"                     : "do_ability",
        "envenom"                        : "do_ability",
        "stun"                           : "do_ability",
        "evade"                          : "do_ability",
        "garrote"                        : "do_ability",
        "blind"                          : "do_ability",
		//"fiappraise"                     : "do_fiappraise",
        
        // Weapon oils
        "ficoat"                         : "do_ficoat",
        //"ficoat2"                         : "do_ficoat2",
        "ficreate"                       : "create_oil",
        
        // Components
        "ficomponent"                    : "do_ficreatecomp",
        ]);
}


int
s_fihelp(string str)
{ 
    if (str == "emotes")
    {
        write(""   
        +"================================================================\n"
        +"|             F I R E    K N I V E S   E M O T E S             |\n"
        +"|--------------------------------------------------------------|\n"
        +"|           The general emotes for the Fire Knives.            |\n"
        +"|                                                              |\n"
        +"| fiindicate <target>     : Draw attention to a target         |\n"
        +"| fibow <target>          : Bow as an assassin would           |\n"
        +"| fiack <target>          : Acknowledge someone's presence     |\n"
        +"| fiback <target>         : Turn your back to someone          |\n"
        +"| fitap <target>          : Sneak up on someone                |\n"
        +"| fiprice <target>        : Assess someone's life value        |\n"
        +"| figaze <target>         : Fix your gaze upon someone         |\n"
        +"| fiangry                 : Contain your anger                 |\n"
        +"| ficrouch                : Crouch down on the floor           |\n"
        +"| fiprepare               : Ready yourself for combat          |\n"
        +"| fipay                   : Make your interests clear          |\n"
        +"| fistretch               : Stretch your muscles               |\n"
        +"| fistance                : Adopt a readied stance             |\n"
        +"| fiscan                  : Scan your immediate surroundings   |\n"
        +"| fibback                 : Take a few steps back              |\n"
        +"| fithreaten              : Threaten someone's life            |\n"
        +"| fibreak                 : Indicate the calling of the nether |\n"
        +"|______________________________________________________________|\n");
        
        return 1;
    }
    
    
    if (str == "weapon oils" || str == "weaponoils" || str == "oils")
    {
        if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) < AB1)
        {
             write("This list is not yet available to you.\n");   

            return 1;             
        }    

        write(""   
        +"===================================================================\n"
        +"|       F I R E    K N I V E S   W E A P O N   O I L S            |\n"
        +"|-----------------------------------------------------------------|\n"
        +"|       Weapon oils created and applied by the outfit.            |\n"
        +"|                                                                 |\n"
        +"|_________________________________________________________________|\n"
        +"|     Name     | Components    |              Effect              |\n"
        +"|==============|===============|==================================|\n"
        +"| Manslayer    | Hemlock       | Slaying vs Mankind               |\n"
        +"| Eldarbane    | Crocus        | Slaying vs Elvenkind             |\n"
        +"| Dwarfbane    | Foxglove      | Slaying vs Dwarvenkind           |\n"
        +"| Gnomeslayer  | Myrtleberry   | Slaying vs Gnomekind             |\n"
        +"| Halflingbane | Nightshade    | Slaying vs Halflingkind          |\n"
        +"| Giantsbane   | Skullcap      | Slaying vs Giantkind             |\n"
        +"| Dragonbane   | Mint          | Slaying vs Dragonkind            |\n"
        +"| Greenslayer  | Sumac         | Slaying vs Greenskinkind         |\n"
        +"| Deathbane    | Garlic        | Slaying vs The Undead            |\n"
        +"| Naturebane   | Amanita       | Slaying vs Nature & constructs   |\n"		
        +"|______________|_______________|__________________________________|\n");
		
		if (FIREKNIVES_MAPPINGS->query_ability5(this_player()->query_name()) == 1)
        {
            write(""   
			+"|              |               |                                  |\n"	
			+"| Torpefy      | Nettle        | Crippling venom                  |\n"		
			+"|______________|_______________|__________________________________|\n");
        }    
        
        return 1;
    }
    
    
    if (str == "components")
    {
        if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) < AB3)
        {
             write("This list is not yet available to you.\n");   

            return 1;             
        }   

        write("");  
        write("===================================================================\n");
        write("|          F I R E    K N I V E S   C O M P O N E N T S           |\n");
        write("|-----------------------------------------------------------------|\n");
        write("|      Various components created and applied by the outfit.      |\n");
        write("|                                                                 |\n");
        write("|            All components require an alchemy set.               |\n");
        write("|_________________________________________________________________|\n");
		write("| Requirements  | product                                         |\n");
        write("|===============|=================================================|\n");
        
        if (FIREKNIVES_MAPPINGS->query_ability1(this_player()->query_name()) == 1)
        {
            write("| Intestine     | Garrote wire                                    |\n");
        }
        
        if (FIREKNIVES_MAPPINGS->query_ability3(this_player()->query_name()) == 1)
        {
            write("| Pepper        | Blinding powder                                 |\n");
        }
        
        write("|_______________|_________________________________________________|\n");
        
        
        return 1;
    }
    
    
    if (str == "abilities")
    {
        write("");  
        write("================================================================\n");
        write("|          F I R E    K N I V E S   A B I L I T I E S          |\n");
        write("|--------------------------------------------------------------|\n");
        write("|   The list of tools of the trade for Assassins. This list    |\n");
        write("|   may expand as a member increases in rank.                  |\n");
        write("|                                                              |\n");
        write("| Backstab <target>             : Plunges your knives into the |\n");
		write("|                                 back of someone.             |\n");         
        
        if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) >= AB1)
        {
            write("|                                                              |\n"); 
            write("| ficreate <weaponoil>      : Create weapon oils.              |\n"); 
            write("| ficomponent <product>     : Create a tool of Assassination.  |\n");             
            write("| ficoat <weapon with <oil> : Coat a weapon with a weapon oil. |\n");
            write("| Envenom <target>          : Poison someone with your dagger. |\n");
            write("|                                                              |\n");            
        }
        
        if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) >= AB2)
        {
            write("|                                                              |\n");            
            write("| Eviscerate <target>     : Disembowel someone with your       |\n");
            write("|                           daggers.                           |\n");            
        }
        
        if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) >= AB3)
        {  
            write("|                                                              |\n");         
            write("| fihang <corpse>         : With a special pole, you can hang  |\n");
            write("|                           a slain enemy onto it for display  |\n");
            write("|                           and warning for others.            |\n");  
            write("|                                                              |\n");                 
        }            
        
        
        
        if (FIREKNIVES_MAPPINGS->query_ability1(this_player()->query_name()) == 1)
        {
            write("|                                                              |\n");
            write("| Garrote <target>        : Cut someone's breath for some      |\n");
            write("|                           time, silencing them.              |\n");
        }
        
        if (FIREKNIVES_MAPPINGS->query_ability2(this_player()->query_name()) == 1)
        {
            write("|                                                              |\n");            
            write("| Evade                   : Evade incoming attacks.            |\n");          
        }
        
        if (FIREKNIVES_MAPPINGS->query_ability3(this_player()->query_name()) == 1)
        {
            write("|                                                              |\n");            
            write("| Blind <target>          : Blow your powder on someone's      |\n");
            write("|                           face, temporarily blinding them.   |\n");      
        }
        
        if (FIREKNIVES_MAPPINGS->query_ability4(this_player()->query_name()) == 1)
        {
            write("|                                                              |\n");            
            write("| Stun <target>           : Target someone's nerves, stunning  |\n");
            write("|                           them momentarily.                  |\n");          
        }
        
 
        
       /* if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) >= AB3)
        {
            write("|                                                              |\n");            
            write("| Garrote <target>        : Cut someone's breath for some      |\n");
            write("|                           time, silencing them.              |\n");
        }   
        
        if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) >= AB4)
        {
            write("|                                                              |\n");            
            write("| Evade                   : Evade incoming attacks.            |\n");          
        }
        
        if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) >= AB5)
        {
            write("|                                                              |\n");            
            write("| Blind <target>          : Blow your powder on someone's      |\n");
            write("|                           face, temporarily blinding them.   |\n");            
        }
        
        if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) >= AB6)
        {
            write("|                                                              |\n");            
            write("| Stun <target>           : Target someone's nerves, stunning  |\n");
            write("|                           them momentarily.                  |\n");            
        }*/
        
        write("|______________________________________________________________|\n");
        
        return 1;
    }
    
    write(""
    +"===========================================================-========--=\n"
    +"|                   F I R E   K N I V E S   H E L P                   |\n"
    +"|---------------------------------------------------------------------|\n"
    +"|  You can get help for the Fire Knives guild by using the commands   |\n"
    +"|  below.                                                             |\n"
    +"|                                                                     |\n"
    +"|    > fihelp                             : This list                 |\n"
    +"|    > fihelp emotes                      : List of emotes            |\n"
    +"|    > fihelp weapon oils                 : List of blade oils        |\n"
	+"|    > fihelp components                  : List of components        |\n"
    +"|    > fihelp abilities                   : List of tools of the trade|\n"
	//+"|    > fiappraise <dagger/knife>          : Proper check of a blade   |\n"
    +"|    > fianalyze <target>                 : Analyze if opponent can   |\n"
    +"|                                           see you while stealthed   |\n"
    +"|    > fiassist <teamleader>              : This will initiate        |\n"
    +"|                                           backstab vs the current   |\n"
    +"|                                           target of your teamleader.|\n"   
    +"|    > filist                             : List active members       |\n"
    +"|    > fienemylist                        : List enemies              |\n"
    +"|    > fiincognito (on/off)               : Turn title on or off      |\n"
    +"|    > fiautosneak (on/off)               : Turn autosneak on / off   |\n"
    +"|    > betray the fire knifes brotherhood : Leave the guild           |\n"
    +"|_____________________________________________________________________|\n");
    
    
     if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) ||
         FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) ||
         FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) ||
         this_player()->query_wiz_level())
    {
        write(""   
        +"|                                                                     |\n"
        +"|               Additional commands for the Council                   |\n"
        +"|                                                                     |\n"
		+"|    > fimemberlist                 : List Brotherhood members        |\n"
        +"|    > fiactivity                   : Reveals your level of activity  |\n"
        +"|    > fiaddenemy                   : Add enemy to the enemy list     |\n"
        +"|    > firemoveenemy                : Remove someone fron ememy list  |\n"
        +"|    > fiexpel                      : Remove a member from guild      |\n"
        +"|    > fiexecute                    : Kill a member                   |\n"
        +"|    > fireward                     : Increase 1 rank                 |\n"
        +"|    > fipunish                     : Decrease 1 rank                 |\n"
        +"|    > firesign                     : Resign back to a regular        |\n"
        +"|                                     member                          |\n"
        +"|    > figuildaccept                : Gives the permission to join    |\n"
        +"|                                     the guild                       |\n"
		+"|    > fifullmembertest             : The final 'challenge' test a    |\n"
		+"|                                     max ranked Trainee is given     |\n"
		+"|                                     for full membership. This       |\n"
		+"|                                     silently enables the Trainee    |\n"
		+"|                                     to 'challenge' an Elder in the  |\n"
		+"|                                     conference room.                |\n"
        +"|    > ficontractcompletepermission : Gives a member the permission   |\n"
        +"|                                     to complete 1 contract          |\n"       
        +"|    > ficontractaddpermission      : Gives a non-member the          |\n"
        +"|                                     permission to add 1 contract    |\n"
        +"|    > fimeetingroompermission      : Gives a non-member the          |\n"
        +"|                                     permission to enter the         |\n"
        +"|                                     secret meeting room in the      |\n"
        +"|                                     bank at the Sword Mountain      |\n"
        +"|                                     village                         |\n"
        +"|    > fivisitpermission_conference : Gives someone (including        |\n"
        +"|                                     Trainees) permission to visit   |\n" 
        +"|                                     the Conference room in keep     |\n"
        +"|    > fiaddcrow <name>             : Add someone to the list of      |\n"
        +"|                                     crows.                          |\n" 
        +"|    > firemovecrow <name>          : Remove someone from the list of |\n"
        +"|                                     crows.                          |\n" 
        +"|    > ficrowlist                   : Displays the list of crows.     |\n"
        +"|                                                                     |\n"
        +"|    > fititlelist                  : Displays ranks/titles within    |\n"
        +"|                                     the Brotherhood.                |\n"
		+"|    > fiaddlibrarian <name>        : Adds someone to the list of     |\n"
        +"|                                     the librarians.                 |\n"
		+"|    > firemovelibrarian <name>     : Removes someone from the list of|\n"
        +"|                                     librarians.                     |\n"
        +"|    > fiaddwhisper <name>          : Adds someone to the list of     |\n"
        +"|                                     the whispers.                   |\n"
		+"|    > firemovewhisper <name>       : Removes someone from the list of|\n"
        +"|                                     whispers.                       |\n"
		+"|    > fiaddhonorable <name>        : Add an x-council member to      |\n"
        +"|                                     an honorable retirement         |\n"
		+"|                                     position.                       |\n"
		+"|    > firemovehonorable <name>     : Removes somebody from the       |\n"
        +"|                                     x-council honorable position.   |\n"       
        +"|    > figarroteenable              : Enables the ability Garrote to  |\n"
        +"|                                     a member.                       |\n"
        +"|    > fievadeenable                : Enables the ability Evade to    |\n"
        +"|                                     a member.                       |\n"
        +"|    > fiblindenable                : Enables the ability Blind to    |\n"
        +"|                                     a member.                       |\n"
        +"|    > fistunenable                 : Enables the ability Stun to     |\n"
        +"|                                     a member.                       |\n"
        +"|    > fitorpefyenable              : Enables the ability Torpefy to  |\n"
        +"|                                     a member.                       |\n"
        +"|    > figarroteremove              : Removes the ability Garrote to  |\n"
        +"|                                     a member.                       |\n"
        +"|    > fievaderemove                : Removes the ability Evade to    |\n"
        +"|                                     a member.                       |\n"
        +"|    > fiblindremove                : Removes the ability Blind to    |\n"
        +"|                                     a member.                       |\n"
        +"|    > fistunremove                 : Removes the ability Stun to     |\n"
        +"|                                     a member.                       |\n"
        +"|    > fitorpefyremove              : Removes the ability Torpefy to  |\n"
        +"|                                     a member.                       |\n"
        +"|                                                                     |\n"
        +"|                                                                     |\n"
        +"|                    COMMANDS IN CONFERENCE ROOM                      |\n"
        +"|                    ---------------------------                      |\n"
        +"|    > eliminate <visitor>          : Order Ruddock to kill someone   |\n"
        +"|                                     that is not a member of the     |\n"
        +"|                                     brotherhood. The victim must    |\n"
        +"|                                     be present in the conference    |\n" 
        +"|                                     room.                           |\n"
        +"|_____________________________________________________________________|\n");
    }
    
    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) ||
        this_player()->query_wiz_level())
    {
        write("" 
        +"|                                                                     |\n"
        +"|                Additional commands for the Inquisitor               |\n"
        +"|                                                                     |\n"
        +"|    > fivisitpermission_inquisitor : Gives someone (including        |\n"
        +"|                                     Trainees) permission to visit   |\n" 
        +"|                                     the Inquisitor office.          |\n"
        +"|    > fiexchange_inquisitor        : Promote someone else to         |\n"
        +"|                                     Inquisitor while stepping down  |\n"
        +"|                                     to the regular ranks.           |\n"
        +"|_____________________________________________________________________|\n");
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) ||
        this_player()->query_wiz_level())
    {
        write("" 
        +"|                                                                     |\n"
        +"|                Additional commands for the Fist                     |\n"
        +"|                                                                     |\n"
        +"|    > fivisitpermission_fist       : Gives someone (including        |\n"
        +"|                                     Trainees) permission to visit   |\n" 
        +"|                                     the Fist office.                |\n"
        +"|    > fiexchange_fist              : Promote someone else to the     |\n"
        +"|                                     Fist while stepping down to the |\n"
        +"|                                     regular ranks.                  |\n"
        +"|_____________________________________________________________________|\n");
    }
               
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) ||
        this_player()->query_wiz_level())
    {
        write("" 
        +"|                                                                     |\n"
        +"|                Additional commands for the Elder                    |\n"
        +"|                                                                     |\n"
        +"|    > fipromote_inquisitor         : Promote someone to Inquisitor   |\n"
        +"|    > fipromote_fist               : Promote someone to the Fist     |\n"
        +"|    > fidemote_councilmember       : Remove a council member         |\n"
        +"|    > fileader                     : Give Elder position to          |\n"
        +"|                                     someone else                    |\n"
        +"|    > fivisitpermission_elder      : Gives someone (including        |\n"
        +"|                                     Trainees) permission to visit   |\n" 
        +"|                                     the Elder office.               |\n"
        +"|_____________________________________________________________________|\n");
    }
    
    if (this_player()->query_wiz_level())
    {
        write("" 
        +"|                                                                     |\n"
        +"|                Additional commands for Wizards only                 |\n"
        +"|                                                                     |\n"
        +"|    > fiboss                       : Promote someone to become       |\n"
        +"|                                     the Elder                       |\n"
        +"|_____________________________________________________________________|\n");
    }
       
    return 1;   
}


/*
 * assist - Help a friend to kill someone else
 */
int
do_fiassist(string str)
{
    object *obs;
    object friend;
    object victim;
    mixed  tmp;
	
    int pkill = (query_verb() == "fiassist!");
	
    if (!CAN_SEE_IN_ROOM(this_player()))
    {
        notify_fail("You can't see anything here.\n");
        return 0;
    }
	
    if (this_player()->query_ghost())
    {
        notify_fail("Umm yes, killed. That's what you are.\n");
        return 0;
    }
	
	if (str == 0)
	{
		notify_fail("fiassist whom?\n");
        return 0;
	}
	
    if (str == "!")
    {
		pkill = 1;
		str = "";
    }
	
    if (!strlen(str))
    {
        if (!sizeof(obs = this_player()->query_team_others()))
        {
            notify_fail("Assist whom? You are not in a team.\n");
            return 0;
        }
		
		
        obs = ({ this_player()->query_leader() }) - ({ 0 }) + obs;
		
        foreach(object ob: obs)
        {
            if ((environment(this_player()) == environment(ob)) &&
                (objectp(victim = ob->query_attack())))
            {
                friend = ob;
                break;
            }
        }
		
        object leader;
        object leader_target;
        
        string leader_target_name;
        
        leader = this_player()->query_leader();
        leader_target = leader->cb_query_attack();
        
        leader_target_name = leader_target->query_real_name();
        
        this_player()->command("backstab "+obs[0]->cb_query_attack());
		//this_player()->command("backstab "+leader_target_name);
			
		return 1;
		//}
		
        if (!objectp(friend))
        {
            notify_fail("None of your team members are in combat..\n");
            return 0;
        }
    }
    else
    {
        /* Require an exaclamation for attacking players. */
        if (str[-1..] == "!")
        {
			pkill = 1;
			str = str[..-2];
        }
		
        obs = parse_this(str, "[the] %l");
		
        if (sizeof(obs) > 1)
        {
            notify_fail("Be specific, you can't assist " +
                COMPOSITE_ALL_LIVE(obs) + " at the same time.\n");
            return 0;
        }
        else if (sizeof(obs) == 0)
        {
            notify_fail("Assist whom?\n");
            return 0;
        }
		
        friend = obs[0];
    }
	
    if (friend == this_player())
    {
        write("Sure! Assist yourself!\n");
        return 1;
    }
	
    victim = friend->query_attack();
	
    if (!objectp(victim))
    {
        write(friend->query_The_name(this_player()) +
            " is not fighting anyone.\n");
        return 1;
    }
	
    if ((member_array(friend, this_player()->query_enemy(-1)) != -1) ||
        (victim == this_player()))
    {
        write("Help " + friend->query_the_name(this_player()) +
            " to kill you? There are easier ways to commit seppuku!\n");
        return 1;
    }
	
    if (environment(victim) != environment(this_player()))
    {
        notify_fail("The main target of " +
            friend->query_the_name(this_player()) + " is not in this room.\n");
        return 0;
    }
	
    if (member_array(victim, this_player()->query_team_others()) != -1)
    {
        notify_fail("But " + victim->query_the_name(this_player()) +
            " is in a team with you.\n");
        return 0;
    }
	
    if (this_player()->query_attack() == victim)
    {
        write("You are already fighting " +
            victim->query_the_name(this_player()) + ".\n");
        return 1;
    }
	
    if (tmp = environment(this_player())->query_prop(ROOM_M_NO_ATTACK))
    {
        if (stringp(tmp))
            write(tmp);
        else
            write("You sense a divine force preventing your attack.\n");
        return 1;
    }
	
    if (tmp = victim->query_prop(OBJ_M_NO_ATTACK))
    {
        if (stringp(tmp))
            write(tmp);
        else
            write("You feel a divine force protecting this being, your " +
                "attack fails.\n");
        return 1;
    }
	
    /* Require an exclamation mark for attacking another player. */
    if (!this_player()->query_npc() && !victim->query_npc() && !pkill)
    {
        write("Attack " + victim->query_the_name(this_player()) + "?!? That " +
            "requires an exclamation mark at the end of the command.\n");
        return 1;
    }
	
    /* Protect against accidental attacking of players you know.
    if ((!this_player()->query_npc()) &&
        (this_player()->query_met(victim)) &&
        (this_player()->query_prop(LIVE_O_LAST_KILL) != victim))
    {
        this_player()->add_prop(LIVE_O_LAST_KILL, victim);
        write("Attack " + victim->query_the_name(this_player()) +
            "?!? Please confirm by trying again.\n");
        return 1;
    }
     */
    //this_player()->reveal_me(1);
    /*
     * Check if we dare!
     */
    if (!F_DARE_ATTACK(this_player(), victim))
    {
        write("Umm... no! You do not have enough self-discipline to dare!\n");
        say(QCTNAME(this_player()) + " considers attacking " + QTNAME(victim) +
            ", though does not dare to do so.\n",
            ({ victim, this_player() }) );
			
        tell_object(victim, this_player()->query_The_name(victim) +
            " looks at you as if ready to attack, though you see fear in " +
            this_player()->query_possessive() + " eyes.\n");
        return 1;
    }
	
    object leader;
    object leader_target;
    
    string leader_target_name;
    
    leader = friend;
    leader_target = victim;
    
    leader_target_name = victim->query_real_name();
    
    this_player()->command("backstab "+leader_target_name);
    
    return 1;
}


int
do_ficoat(string str)
{
    setuid();
    seteuid(getuid());
    
    object *oblist, tp, shadow;

    int int_str, value, *money_arr, s;

    string item_name,
        verb, material;

    verb = query_verb();
    tp = this_player();


    notify_fail(capitalize(verb) + " what?\n");
    
    if (!str)
        return 0;

    mixed  *adjs;

    if (!strlen(str))
    {
        notify_fail("Coat which weapon with what material?\n");
        return 0;
    }
    
    str = lower_case(str);

    if (!parse_command(str, tp, "[the] %i [with] %w",
        oblist, material))
    {
        notify_fail(capitalize(query_verb()) 
        + " which weapon with what material?\n");
        return 0;
    }
    
    oblist = NORMAL_ACCESS(oblist, 0, 0);
    
   
    //oblist[0] = tp->query_weapon(W_LEFT);
    
    if (!(s = sizeof(oblist)))
    {
        notify_fail(capitalize(query_verb()) 
        + " which weapon with what material?\n");
        return 0;
    }
    
    if (s > 1)
    {
        notify_fail("Be more specific. Which one?\n");
        return 0;
    }
    
    if ((function_exists("create_object", oblist[0]) != "/std/weapon"))        
    {
        notify_fail("That is not really a weapon!\n");
        return 0;
    }
    
    if (oblist[0]->query_weaponoil_shadow() == 1)
    {
        tp->catch_tell("You clean the " + oblist[0]->short() 
        + " for any alchemical substances.\n");
        
        tell_room(environment(tp), QCTNAME(tp)
        +" cleans the "+ oblist[0]->short() +" for any alchemical substances.\n", tp);
        
        oblist[0]->remove_manslayer_shadow();
        oblist[0]->remove_dwarfbane_shadow();
        oblist[0]->remove_eldarbane_shadow();
        oblist[0]->remove_gnomeslayer_shadow();
        oblist[0]->remove_greenslayer_shadow();
        oblist[0]->remove_deathbane_shadow();
        oblist[0]->remove_giantsbane_shadow();
        oblist[0]->remove_naturebane_shadow();
        oblist[0]->remove_dragonbane_shadow();
        oblist[0]->remove_halflingbane_shadow();
        oblist[0]->remove_cripplingoil_shadow();  		
    }
    
    switch (material)
    {       
        case "manslayer":
        
        object *oil1 = filter(deep_inventory(this_player()),
        &operator(==)("manslayer") @&->query_name());    

        if (!sizeof(oil1))
        {
            write("You don't have any manslayer oil.\n");
            return 1;
        }

        object comp1 = oil1[0];
        
        if (comp1->id("manslayer_weaponoil") == 0)
        {
            write("You don't have any manslayer oil.\n");
            
            return 1;
        }

        string comp_short1 = comp1->query_short();

        comp1->reduce_heap_size();

        tell_room(environment(tp), QCTNAME(tp)
        +" grabs something from "+tp->query_possessive()+" inventory " 
        +"and applies it on the "+ oblist[0]->short() +".\n", tp);
        
        tp->catch_tell("You grab a "+comp_short1+" from your "
        +"inventory and coat the "+ oblist[0]->short() 
        +" with the content.\n");
        
        shadow = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/weaponoils/manslayer_shadow");
        
        shadow->shadow_me(oblist[0]);

        set_alarm(2.0, 0.0, &shadow->init_manslayer_shadow());
        break;
            
        
        case "eldarbane":
        
        object *oil2 = filter(deep_inventory(this_player()),
        &operator(==)("eldarbane") @&->query_name());    

        if (!sizeof(oil2))
        {
            write("You don't have any eldarbane oil.\n");
            return 1;
        }

        object comp2 = oil2[0];
        
        if (comp2->id("eldarbane_weaponoil") == 0)
        {
            write("You don't have any eldarbane oil.\n");
            
            return 1;
        }

        string comp_short2 = comp2->query_short();

        comp2->reduce_heap_size();

        tell_room(environment(tp), QCTNAME(tp)
        +" grabs something from "+tp->query_possessive()+" inventory " 
        +"and applies it on the "+ oblist[0]->short() +".\n", tp);
        
        tp->catch_tell("You grab a "+comp_short2+" from your "
        +"inventory and coat the "+ oblist[0]->short() 
        +" with the content.\n");
        
        shadow = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/weaponoils/eldarbane_shadow");
        
        shadow->shadow_me(oblist[0]);

        set_alarm(2.0, 0.0, &shadow->init_eldarbane_shadow());
        break;
               
        
        case "dwarfbane":
        
        object *oil3 = filter(deep_inventory(this_player()),
        &operator(==)("dwarfbane") @&->query_name());    

        if (!sizeof(oil3))
        {
            write("You don't have any dwarfbane oil.\n");
            return 1;
        }

        object comp3 = oil3[0];
        
        if (comp3->id("dwarfbane_weaponoil") == 0)
        {
            write("You don't have any dwarfbane oil.\n");
            
            return 1;
        }

        string comp_short3 = comp3->query_short();

        comp3->reduce_heap_size();

        tell_room(environment(tp), QCTNAME(tp)
        +" grabs something from "+tp->query_possessive()+" inventory " 
        +"and applies it on the "+ oblist[0]->short() +".\n", tp);
        
        tp->catch_tell("You grab a "+comp_short3+" from your "
        +"inventory and coat the "+ oblist[0]->short() 
        +" with the content.\n");
        
        shadow = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/weaponoils/dwarfbane_shadow");
        
        shadow->shadow_me(oblist[0]);

        set_alarm(2.0, 0.0, &shadow->init_dwarfbane_shadow());
        break;
        
        
        case "gnomeslayer":
        
        object *oil4 = filter(deep_inventory(this_player()),
        &operator(==)("gnomeslayer") @&->query_name());    

        if (!sizeof(oil4))
        {
            write("You don't have any gnomeslayer oil.\n");
            return 1;
        }

        object comp4 = oil4[0];
        
        if (comp4->id("gnomeslayer_weaponoil") == 0)
        {
            write("You don't have any gnomeslayer oil.\n");
            
            return 1;
        }

        string comp_short4 = comp4->query_short();

        comp4->reduce_heap_size();

        tell_room(environment(tp), QCTNAME(tp)
        +" grabs something from "+tp->query_possessive()+" inventory " 
        +"and applies it on the "+ oblist[0]->short() +".\n", tp);
        
        tp->catch_tell("You grab a "+comp_short4+" from your "
        +"inventory and coat the "+ oblist[0]->short() 
        +" with the content.\n");
        
        shadow = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/weaponoils/gnomeslayer_shadow");
        
        shadow->shadow_me(oblist[0]);

        set_alarm(2.0, 0.0, &shadow->init_gnomeslayer_shadow());
        break;
               
        
        case "halflingbane":
        
        object *oil5 = filter(deep_inventory(this_player()),
        &operator(==)("halflingbane") @&->query_name());    

        if (!sizeof(oil5))
        {
            write("You don't have any halflingbane oil.\n");
            return 1;
        }

        object comp5 = oil5[0];
        
        if (comp5->id("halflingbane_weaponoil") == 0)
        {
            write("You don't have any halflingbane oil.\n");
            
            return 1;
        }

        string comp_short5 = comp5->query_short();

        comp5->reduce_heap_size();

        tell_room(environment(tp), QCTNAME(tp)
        +" grabs something from "+tp->query_possessive()+" inventory " 
        +"and applies it on the "+ oblist[0]->short() +".\n", tp);
        
        tp->catch_tell("You grab a "+comp_short5+" from your "
        +"inventory and coat the "+ oblist[0]->short() 
        +" with the content.\n");
        
        shadow = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/weaponoils/halflingbane_shadow");
        
        shadow->shadow_me(oblist[0]);

        set_alarm(2.0, 0.0, &shadow->init_halflingbane_shadow());
        break;
  
        
        case "giantsbane":
        
        object *oil6 = filter(deep_inventory(this_player()),
        &operator(==)("giantsbane") @&->query_name());    

        if (!sizeof(oil6))
        {
            write("You don't have any giantsbane oil.\n");
            return 1;
        }

        object comp6 = oil6[0];
        
        if (comp6->id("giantsbane_weaponoil") == 0)
        {
            write("You don't have any giantsbane oil.\n");
            
            return 1;
        }

        string comp_short6 = comp6->query_short();

        comp6->reduce_heap_size();

        tell_room(environment(tp), QCTNAME(tp)
        +" grabs something from "+tp->query_possessive()+" inventory " 
        +"and applies it on the "+ oblist[0]->short() +".\n", tp);
        
        tp->catch_tell("You grab a "+comp_short6+" from your "
        +"inventory and coat the "+ oblist[0]->short() 
        +" with the content.\n");
        
        shadow = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/weaponoils/giantsbane_shadow");
        
        shadow->shadow_me(oblist[0]);

        set_alarm(2.0, 0.0, &shadow->init_giantsbane_shadow());
        break;
        
        
        case "dragonbane":
        
        object *oil7 = filter(deep_inventory(this_player()),
        &operator(==)("dragonbane") @&->query_name());    

        if (!sizeof(oil7))
        {
            write("You don't have any dragonbane oil.\n");
            return 1;
        }

        object comp7 = oil7[0];
        
        if (comp7->id("dragonbane_weaponoil") == 0)
        {
            write("You don't have any dragonbane oil.\n");
            
            return 1;
        }

        string comp_short7 = comp7->query_short();

        comp7->reduce_heap_size();

        tell_room(environment(tp), QCTNAME(tp)
        +" grabs something from "+tp->query_possessive()+" inventory " 
        +"and applies it on the "+ oblist[0]->short() +".\n", tp);
        
        tp->catch_tell("You grab a "+comp_short7+" from your "
        +"inventory and coat the "+ oblist[0]->short() 
        +" with the content.\n");
        
        shadow = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/weaponoils/dragonbane_shadow");
        
        shadow->shadow_me(oblist[0]);

        set_alarm(2.0, 0.0, &shadow->init_dragonbane_shadow());
        break;
        
        
        case "greenslayer":
        
        object *oil8 = filter(deep_inventory(this_player()),
        &operator(==)("greenslayer") @&->query_name());    

        if (!sizeof(oil8))
        {
            write("You don't have any greenslayer oil.\n");
            return 1;
        }

        object comp8 = oil8[0];
        
        if (comp8->id("greenslayer_weaponoil") == 0)
        {
            write("You don't have any greenslayer oil.\n");
            
            return 1;
        }

        string comp_short8 = comp8->query_short();

        comp8->reduce_heap_size();

        tell_room(environment(tp), QCTNAME(tp)
        +" grabs something from "+tp->query_possessive()+" inventory " 
        +"and applies it on the "+ oblist[0]->short() +".\n", tp);
        
        tp->catch_tell("You grab a "+comp_short8+" from your "
        +"inventory and coat the "+ oblist[0]->short() 
        +" with the content.\n");
        
        shadow = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/weaponoils/greenslayer_shadow");
        
        shadow->shadow_me(oblist[0]);

        set_alarm(2.0, 0.0, &shadow->init_greenslayer_shadow());
        break;
        
        
        case "deathbane":
        
        object *oil9 = filter(deep_inventory(this_player()),
        &operator(==)("deathbane") @&->query_name());    

        if (!sizeof(oil9))
        {
            write("You don't have any deathbane oil.\n");
            return 1;
        }

        object comp9 = oil9[0];
        
        if (comp9->id("deathbane_weaponoil") == 0)
        {
            write("You don't have any deathbane oil.\n");
            
            return 1;
        }

        string comp_short9 = comp9->query_short();

        comp9->reduce_heap_size();

        tell_room(environment(tp), QCTNAME(tp)
        +" grabs something from "+tp->query_possessive()+" inventory " 
        +"and applies it on the "+ oblist[0]->short() +".\n", tp);
        
        tp->catch_tell("You grab a "+comp_short9+" from your "
        +"inventory and coat the "+ oblist[0]->short() 
        +" with the content.\n");
        
        shadow = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/weaponoils/deathbane_shadow");
        
        shadow->shadow_me(oblist[0]);

        set_alarm(2.0, 0.0, &shadow->init_deathbane_shadow());
        break;       
        
        
        case "naturebane":
        
        object *oil0 = filter(deep_inventory(this_player()),
        &operator(==)("naturebane") @&->query_name());    

        if (!sizeof(oil0))
        {
            write("You don't have any naturebane oil.\n");
            return 1;
        }

        object comp0 = oil0[0];
        
        if (comp0->id("naturebane_weaponoil") == 0)
        {
            write("You don't have any naturebane oil.\n");
            
            return 1;
        }

        string comp_short0 = comp0->query_short();

        comp0->reduce_heap_size();

        tell_room(environment(tp), QCTNAME(tp)
        +" grabs something from "+tp->query_possessive()+" inventory " 
        +"and applies it on the "+ oblist[0]->short() +".\n", tp);
        
        tp->catch_tell("You grab a "+comp_short0+" from your "
        +"inventory and coat the "+ oblist[0]->short() 
        +" with the content.\n");
        
        shadow = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/weaponoils/naturebane_shadow");
        
        shadow->shadow_me(oblist[0]);

        set_alarm(2.0, 0.0, &shadow->init_naturebane_shadow());
        break;
				
		case "torpefy":
        
        object *oil11 = filter(deep_inventory(this_player()),
        &operator(==)("torpefy") @&->query_name());    

        if (!sizeof(oil11))
        {
            write("You don't have any torpefy oil.\n");
            return 1;
        }
		
		if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) < AB7)
		{
			write("You are not eligible to use this weapon oil.\n");
            return 1;
		}

        object comp11 = oil11[0];
        
        if (comp11->id("torpefy_weaponoil") == 0)
        {
            write("You don't have any torpefy oil.\n");
            
            return 1;
        }
        
        if (PVP_ABILITY_DISABLED)
        {
            write("This weaponoil is currently disabled for "
            +"use (temporary). Contact GM for further details.\n");
            return 1;
        }
        
        string comp_short11 = comp11->query_short();

        comp11->reduce_heap_size();

        tell_room(environment(tp), QCTNAME(tp)
        +" grabs something from "+tp->query_possessive()+" inventory " 
        +"and applies it on the "+ oblist[0]->short() +".\n", tp);
        
        tp->catch_tell("You grab a "+comp_short11+" from your "
        +"inventory and coat the "+ oblist[0]->short() 
        +" with the content.\n");
        
        shadow = clone_object(FIREKNIVES_GUILD_DIR 
        + "specials/weaponoils/crippling_shadow");
        
        shadow->shadow_me(oblist[0]);

        set_alarm(2.0, 0.0, &shadow->init_cripplingoil_shadow());
        break;
		
        
    default:
        tp->catch_tell("Coat the "+ oblist[0]->short() +" with what?\n");
        return 1;
    }

    return 1;
}


int
do_fiappraise(string str)
{
    setuid();
    seteuid(getuid());
    
    object *oblist, tp, shadow;

    int int_str, value, *money_arr, s;

    string item_name,
        verb, material;

    verb = query_verb();
    tp = this_player();


    notify_fail(capitalize(verb) + " what?\n");
    
    if (!str)
        return 0;

    mixed  *adjs;

    if (!strlen(str))
    {
        notify_fail("Appraise which dagger or knife?\n");
        return 0;
    }
    
    str = lower_case(str);

	if (!parse_command(str, tp, "[the] %i",
        oblist))
    {
        notify_fail(capitalize(query_verb()) 
        + " which dagger or knife?\n");
        return 0;
    }
    
    oblist = NORMAL_ACCESS(oblist, 0, 0);
    
   
    //oblist[0] = tp->query_weapon(W_LEFT);
    
    if (!(s = sizeof(oblist)))
    {
        notify_fail(capitalize(query_verb()) 
        + " which dagger or knife?\n");
        return 0;
    }
    
    if (s > 1)
    {
        notify_fail("Be more specific. Which one?\n");
        return 0;
    }
    
    if ((function_exists("create_object", oblist[0]) != "/std/weapon"))        
    {
        notify_fail("That is not really a weapon!\n");
        return 0;
    }
	
	if (oblist[0]->query_wt() != W_KNIFE)
	{
		notify_fail("That is not a dagger or a knife!\n");
        return 0;
	}
	 
	string message1_pen;
    string message2_pen;	
	
	string message1_hit;
    string message2_hit;	
	
	int wep_pen = oblist[0]->query_pen();
	int wep_hit = oblist[0]->query_hit();
	
	
	switch (wep_hit)
    {
        case 0..10:
        message1_hit = "shocked at how clumsy it feels in your hand";
        break;

        case 11..20:
        message1_hit = "disappointed at the handle's poor craftmanship";
        break;

        case 21..30:
        message1_hit = "mistrustful of the weapon's ease of use";
        break;

        case 31..35:
        message1_hit = "not overly impressed with how the weapon can be used";
        break;

        case 36..38:
        message1_hit = "satisfied with the weapon's ease of use";
        break;

        case 39:
        message1_hit = "quite pleased with the weapon's manageability";
        break;

        case 40..1000:
        message1_hit = "confident in your ability to use this weapon perfectly";
        break;
    }

	switch (wep_pen)
    {
        case 0..10:
        message1_pen = "Shards of a broken tea cup would be deadlier";
        break;

        case 11..20:
        message1_pen = "Its damage would be barely noticeable";
        break;

        case 21..30:
        message1_pen = "Quite a few blows would be required for effectiveness";
        break;

        case 31..35:
        message1_pen = "It could cause a decent level of pain";
        break;

        case 36..37:
        message1_pen = "The inflicted damage is predictably quite painful";
        break;

        case 38..39:
        message1_pen = "It could deliver quite a powerful blow";
        break;

        case 40..60:
        message1_pen = "The damage would be devastating";
        break;
  }
	
	tell_room(environment(tp), QCTNAME(tp)
		+" deftly changes grip on "+tp->query_possessive()+" "
		+ oblist[0]->short() 
		+" and focuses on testing its balance and heft. "
		+capitalize(tp->query_pronoun())+" quickly "
		+"lunges forward towards an invisible target with the tip of the blade. "
		+"At the very last moment "+tp->query_pronoun()+ " stops and lowers the "
		+oblist[0]->short()+", seeming to have formed an opinion about the blade.\n", tp);



    tp->catch_tell("You deftly change grips on the "
	+oblist[0]->short()+" and focus on testing "
	+"its balance and heft. You quickly lunge forward towards an invisible "
	+"target with the tip of the blade. At the very last moment you stop "
	+"the "+ oblist[0]->short()+" from piercing your target."
	+" You are "+message1_hit+". "+message1_pen+".\n");
	
	/*tell_room(environment(tp), QCTNAME(tp)
	+" spins "+tp->query_possessive()+" "+ oblist[0]->short() 
	+" on the tip of "+tp->query_possessive()+" index finger then "
	+"catches and twirls it around "+tp->query_possessive()
	+" palm in a swift maneuver, assessing its quality. "
	+capitalize(tp->query_pronoun())+" grabs it by the handle "
	+"pointing forward and gives a "+message1_hit+" and "+message1_pen+".\n", tp);
		
	tp->catch_tell("You spin the "+ oblist[0]->short()+" on the "
	+"tip of your index finger then catch and twirl it around "
	+"on your palm in a swift maneuver, assessing its efficiency "
	+"to dig into flesh. You grab it by the handle pointing "
	+"forward and decide it is "+message2_hit+" and "+message2_pen+".\n");*/

    return 1;
}



int do_fianalyze(string str)
{
    object *targ;
    
    if(!strlen(str)) /* no string supplied */
    {
        write("Analyze whom?\n");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;



    int awareness_factor = targ[0]->query_skill(SS_AWARENESS);
    int assassin_hide_factor = this_player()->query_prop(OBJ_I_HIDE);
    
    if (awareness_factor < assassin_hide_factor)
    {
        actor("You analyze",targ,". "+capitalize(HE_SHE(targ[0]))
        +" seems to be totally unaware of your presence.");
        
        return 1;
    }

    actor("You analyze",targ,". "+capitalize(HE_SHE(targ[0]))
    +" is obviously aware of your presence.");
    

    return 1;
}


int
fiautosneak(string str)
{
    int old_as = this_player()->query_autosneak();
    
    int new_as;
    
    notify_fail("Autosneak how?\n");
    if (!str)
      this_player()->set_autosneak(!old_as);
    else if (str == "on" || str == "yes")
      this_player()->set_autosneak(1);
    else if (str == "off" || str == "no")
      this_player()->set_autosneak(0);
    else
      return 0;
    new_as = this_player()->query_autosneak();
    if (new_as)
      write("You get ready to sneak about automatically.\n");
    else
      write("You stop sneaking about automatically.\n");
    
    return 1;
}


void
expel_mee()
{
    if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 0)
    {
        this_player()->command("betray the fire knives outfit");
    }
}


int expel_player(object expelee)
{
    if (FIREKNIVES_MASTER->is_occ_fireknife(expelee->query_name()) == 0)
    {
        expelee->command("betray the fire knives outfit");
    }
    
    return 1;
}


void move_executee_bleed(object executee)
{
    setuid();
    seteuid(getuid());
    
    clone_object(FIREKNIVES_GUILD_DIR + "obj/execute_obj")->move(executee, 1);
    
    return;
}


// Execution as punishment.
int
do_fiexecute(string str)
{
    setuid();
    seteuid(getuid());
    
    object execute_obj = 0;
    
    if (!str)
    {
        return 0;
    }
    
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }
    
    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't execute the Elder!\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't execute the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't execute the Fist.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That player is not a member of the Fire Knives.\n");
        return 1;
    }

    object executee = find_player(str);
    
    if (executee == 0)
    {
        write("That member is not in the realms!\n");
        
        return 1;
    }

    write("You silently order " + executee->query_name() 
    + " to be executed immediately!\n\n");
    
    tell_room(environment(executee), "You see a bald muscular male "
        +"human walk up to "
        +executee->query_name()+", placing a hand on "
        +executee->query_possessive()+" shoulder. There is a flash "
        +"of steel between "+executee->query_name()+" legs and a pool " 
        +"of blood starts forming quickly. The bald muscular human leans in "
        +"and whispers something to "+executee->query_name()
        +" before turning "
        +"around and walking away.\n", executee);
        
        executee->catch_tell("You feel a hand on your shoulder followed "
        +"by a sharp pain on the inside of your thigh. Warm liquid starts "
        +"to pour down your thigh as you hear the gravelly voice of "
        +"Richard D. Ruddock whispering in your ear 'The Council wants "
        +"you Dead.' and you turn around to face him as he backs "
        +"off and walks away. Your arms start to feel heavy and your vision "
        +"starts to blur as you fall to your knees from the loss of "
        +"blood.\n");
        
    set_alarm(1.0, 0.0, &move_executee_bleed(executee));
    
    EXECUTE_LOG("execute_log",
    "The member " +str
    +" was Executed as a punishment "
    +"by "+this_player()->query_name()+".\n");

    return 1;
}


int
visit_guild_permission_conference(string str)
{
    setuid();
    seteuid(getuid());
    
    // Only for the council
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        write("What?\n");
        return 1;
    }

    if (!str)
    {
        write("Give whom permission to visit the Conference room?\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    object playa = find_player(str);
    
    if (!playa)
    {
        write("No such player in the game.\n");

        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_fireknife(playa->query_name()) == 1)
    {  
        if (FIREKNIVES_MAPPINGS->query_assassin_rank(playa->query_name()) <= MAX_PROSPECT_RANK)
        {
            if (present("fireknives_visit_object_conference", playa))
            {
                write("That Trainee have been given the permission to visit "
                +"the Conference room already!\n");

                return 1;
            }  
            
            tell_object(find_player(str), "You feel you have been "
            +"granted the permission "
            + "to visit the Conference room at the third floor "
            +"of the keep!\n");

            write("You give "
            + find_player(str)->query_name() 
            + " the permission to visit the "
            + "Conference room in the keep of the Outfit!\n");
                       
            clone_object(VISIT_ITEM_CONFERENCE)->move(playa, 1);
            
            return 1;
        }
        
        write("That full member already have the access to visit the "
        +"Conference room already.\n");
        
        return 1;
    }
  
    if (present("fireknives_visit_object_conference", playa))
    {
        write("That player have been given the permission to visit "
        +"the Conference room already!\n");

        return 1;
    }         

    tell_object(find_player(str), "You feel you have been granted "
    +"the permission "
    + "to visit the Conference room in the secret hideout "
    +"of the Fire Knives!\n");

    write("You give "
    + find_player(str)->query_name() + " the permission to visit the "
    + "Conference room in the keep of the Outfit!\n");
    
    setuid();
    seteuid(getuid());
               
    clone_object(VISIT_ITEM_CONFERENCE)->move(playa, 1);

    return 1;
}


int
visit_guild_permission_elder(string str)
{
    setuid();
    seteuid(getuid());
    
    // Only the alpha or the elder can make omegas.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        write("What?\n");
        return 1;
    }

    if (!str)
    {
        write("Give whom permission to visit the office of the Elder?\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    object playa = find_player(str);
    
    if (!playa)
    {
        write("No such player in the game.\n");

        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_fireknife(playa->query_name()) == 1)
    {  
        if (FIREKNIVES_MAPPINGS->query_assassin_rank(playa->query_name()) <= MAX_PROSPECT_RANK)
        {
            if (present("fireknives_visit_object_elder", playa))
            {
                write("That Trainee have been given the permission to visit "
                +"the office of the Elder already!\n");

                return 1;
            }  
            
            tell_object(find_player(str), "You feel you have been "
            +"granted the permission "
            + "to visit the office of the Elder at the third floor "
            +"of the keep!\n");

            write("You give "
            + find_player(str)->query_name() 
            + " the permission to visit the "
            + "office of the Elder in the keep of the Outfit!\n");
                       
            clone_object(VISIT_ITEM_ELDER)->move(playa, 1);
            
            return 1;
        }
    }
  
    if (present("fireknives_visit_object_elder", playa))
    {
        write("That player have been given the permission to visit "
        +"the office of the Elder already!\n");

        return 1;
    }         

    tell_object(find_player(str), "You feel you have been granted "
    +"the permission "
    + "to visit the office of the Elder in the keep of the Fire Knives!\n");

    write("You give "
    + find_player(str)->query_name() + " the permission to visit the "
    + "office of the Elder in the keep of the Outfit!\n");
    
    setuid();
    seteuid(getuid());
               
    clone_object(VISIT_ITEM_ELDER)->move(playa, 1);

    return 1;
}


int
visit_guild_permission_mentor(string str)
{
    setuid();
    seteuid(getuid());
    
    // Only the alpha or the elder can make omegas.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        write("What?\n");
        return 1;
    }

    if (!str)
    {
        write("Give whom permission to visit the office of the Inquisitor?\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    object playa = find_player(str);
    
    if (!playa)
    {
        write("No such player in the game.\n");

        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_fireknife(playa->query_name()) == 1)
    {  
        if (FIREKNIVES_MAPPINGS->query_assassin_rank(playa->query_name()) <= MAX_PROSPECT_RANK)
        {
            if (present("fireknives_visit_object_mentor", playa))
            {
                write("That Trainee have been given the permission to visit "
                +"the office of the Inquisitor already!\n");

                return 1;
            }  
            
            tell_object(find_player(str), "You feel you have been "
            +"granted the permission "
            + "to visit the office of the Inquisitor at the third "
            +"floor of the keep!\n");

            write("You give "
            + find_player(str)->query_name() 
            + " the permission to visit the "
            + "office of the Inquisitor in the keep of the Outfit!\n");
                       
            clone_object(VISIT_ITEM_MENTOR)->move(playa, 1);
            
            return 1;
        }
    }
  
    if (present("fireknives_visit_object_mentor", playa))
    {
        write("That player have been given the permission to visit "
        +"the office of the Inquisitor already!\n");

        return 1;
    }         

    tell_object(find_player(str), "You feel you have been granted "
    +"the permission "
    + "to visit the office of the Inquisitor in the keep of the Fire Knives!\n");

    write("You give "
    + find_player(str)->query_name() + " the permission to visit the "
    + "office of the Inquisitor in the keep of the Outfit!\n");
    
    setuid();
    seteuid(getuid());
               
    clone_object(VISIT_ITEM_MENTOR)->move(playa, 1);

    return 1;
}


int
visit_guild_permission_fist(string str)
{
    setuid();
    seteuid(getuid());
    
    // Only the alpha or the elder can make omegas.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        write("What?\n");
        return 1;
    }

    if (!str)
    {
        write("Give whom permission to visit the office of the Fist?\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    object playa = find_player(str);
    
    if (!playa)
    {
        write("No such player in the game.\n");

        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_fireknife(playa->query_name()) == 1)
    {  
        if (FIREKNIVES_MAPPINGS->query_assassin_rank(playa->query_name()) <= MAX_PROSPECT_RANK)
        {
            if (present("fireknives_visit_object_fist", playa))
            {
                write("That Trainee have been given the permission to visit "
                +"the office of the Fist already!\n");

                return 1;
            }  
            
            tell_object(find_player(str), "You feel you have been "
            +"granted the permission "
            + "to visit the office of the Fist at the third floor "
            +"of the keep!\n");

            write("You give "
            + find_player(str)->query_name() 
            + " the permission to visit the "
            + "office of the Fist in the keep of the Outfit!\n");
                       
            clone_object(VISIT_ITEM_FIST)->move(playa, 1);
            
            return 1;
        }
    }
  
    if (present("fireknives_visit_object_fist", playa))
    {
        write("That player have been given the permission to visit "
        +"the office of the Fist already!\n");

        return 1;
    }         

    tell_object(find_player(str), "You feel you have been granted "
    + "the permission "
    + "to visit office of the Fist in the keep of the Fire Knives!\n");

    write("You give "
    + find_player(str)->query_name() + " the permission to visit the "
    + "office of the Fist in the keep of the Outfit!\n");
    
    setuid();
    seteuid(getuid());
               
    clone_object(VISIT_ITEM_FIST)->move(playa, 1);

    return 1;
}


int
join_guild_permission(string str)
{
    // Only the alpha or the elder can make omegas.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        write("What?\n");
        return 1;
    }

    if (!str)
    {
        write("Give whom permission to join the Fire Knives?\n");
        return 1;
    }


    if (FIREKNIVES_MASTER->is_occ_fireknife(str) != 0)
    {
        write("That person is already a member of the Fire Knives.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }


    object playa = find_player(str);

    if (!playa)
    {
        write("No such player in the game.\n");

        return 1;
    }

    // FIX QUEST FOR THIS!
    /*if (!playa->test_bit("Faerun", 2, 9))
    {
        write("That player has not sufficiently proven it's worth yet "
        +"to your Master.\n");

        return 1;
    }*/

    if (playa->query_prop(I_CAN_JOIN_FIREKNIVES) == 1)
    {

        write("That person have been given the permission to join "
        +"the Fire Knives already!\n");

        return 1;
    }

    tell_object(find_player(str), "You are granted the permission "
        + "to join the Fire Knives as a Postulate "
        +"by <pledge to brotherhood>!\nPledge, or flee these "
        +"halls while you still can!\n");

    write("You give "
        + find_player(str)->query_name() + " the permission to join the "
        + "Fire Knives!\n");

    find_player(str)->add_prop(I_CAN_JOIN_FIREKNIVES, 1);
    
    JOIN_PER_LOG("join_per_log",
    "The Applicant " +str
    +" received the permission to join the Brotherhood "
    +"by "+this_player()->query_name()+".\n");


    return 1;
}


int
become_fullmember_test(string str)
{
    // Only the alpha or the elder can make omegas.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        write("What?\n");
        return 1;
    }

    if (!str)
    {
        write("Give whom permission to take the challenge test "
		+"for full membership?\n");
        return 1;
    }


    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a a member of the Fire Knives.\n");
        return 1;
    }
	
	if (FIREKNIVES_MAPPINGS->query_assassin_rank(str) > MAX_PROSPECT_RANK)
    {
		write("That person is a full member already.\n");
        return 1;
	}
	
	if (FIREKNIVES_MAPPINGS->query_assassin_rank(str) < MAX_PROSPECT_RANK)
    {
		write("That person is not ready yet for the full member "
		+"challenge test.\n");
        return 1;
	}

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }


    object playa = find_player(str);

    if (!playa)
    {
        write("No such player in the game.\n");

        return 1;
    }

    // FIX QUEST FOR THIS!
    /*if (!playa->test_bit("Faerun", 2, 9))
    {
        write("That player has not sufficiently proven it's worth yet "
        +"to your Master.\n");

        return 1;
    }*/

    if (playa->query_prop(FULL_MEMBER_CEREMONY) == 1)
    {

        write("That person have been given the permission to do "
        +"the full member challenge already!\n");

        return 1;
    }

    write("You silently enable "
        + find_player(str)->query_name() + " the option "
		+"to 'challenge' one of the Elders for a "
		+"full member membership.\n");

    find_player(str)->add_prop(FULL_MEMBER_CEREMONY, 1);
    
    FULLM_PER_LOG("fullm_per_log",
    "The Candidate " +str
    +" received the permission to become a full member "
    +"by "+this_player()->query_name()+".\n");


    return 1;
}


int
contract_complete_permission(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        write("What?\n");
        return 1;
    }

    if (!str)
    {
        write("Give whom permission to complete a contract?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    object playa = find_player(str);

    if (!playa)
    {
        write("No such player in the game.\n");

        return 1;
    }

    if (playa->query_prop(I_CAN_COMPLETE_CONTRACT) == 1)
    {

        write("That person have been given the permission to "
        +"complete a contract!\n");

        return 1;
    }

    tell_object(find_player(str), "You are granted the permission "
        + "to complete One contract by your peers. Make sure "
        +"you complete the Correct one.\n");

    write("You give "
        + find_player(str)->query_name() + " the permission to complete "
        +"a single contract. Make sure that individual complete the "
        +"Correct contract.\n");

    find_player(str)->add_prop(I_CAN_COMPLETE_CONTRACT, 1);


    return 1;
}


int
contract_create_permission(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        write("What?\n");
        return 1;
    }

    if (!str)
    {
        write("Give whom permission to create a contract?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 1)
    {
        write("That person is a member of the Fire Knives and "
        +"therefore can't create contracts.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    object playa = find_player(str);

    if (!playa)
    {
        write("No such player in the game.\n");

        return 1;
    }

    if (playa->query_prop(I_CAN_CREATE_CONTRACT) == 1)
    {

        write("That person have been given the permission to "
        +"create a contract already!\n");

        return 1;
    }

    tell_object(find_player(str), "You are granted the permission "
        + "to create a single contract. Read the Plaque in the meeting room "
        +"for additional information how to. Make sure "
        +"you create it with the agreed upon price.\n");

    write("You give "
        + find_player(str)->query_name() + " the permission to create "
        +"a single contract.\n");

    find_player(str)->add_prop(I_CAN_CREATE_CONTRACT, 1);

    return 1;
}


int
contract_meetingroom_permission(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        write("What?\n");
        return 1;
    }

    if (!str)
    {
        write("Give whom permission to visit the secret meeting room?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 1)
    {
        write("That person is a member of the Fire Knives and "
        +"already have access.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    object playa = find_player(str);

    if (!playa)
    {
        write("No such player in the game.\n");

        return 1;
    }

    if (playa->query_prop(I_CAN_VISIT_MEETINGROOM) == 1)
    {

        write("That person have been given the permission to "
        +"visit the secret meeting room already!\n");

        return 1;
    }

    write("You give "
        + find_player(str)->query_name() + " the permission to visit "
        +"the secret meeting room in the bank.\n");

    find_player(str)->add_prop(I_CAN_VISIT_MEETINGROOM, 1);

    return 1;
}


// Add player to enemy list
int
fiadd_enemy(string str)
{
    // Only the alpha or the elder can make omegas.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Add who to the list of enemies?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 1)
    {
        write("You can't add members to the list of enemies.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_guild_enemy(str) == 1)
    {
        write("That individual is already on the list of enemies.\n");
        return 1;
    }
    
    object playa = find_player(str);
    
    if (!playa)
    {
        write("No such player in the game.\n");

        return 1;
    }

    FIREKNIVES_MASTER->add_guild_enemy(str);

    write("You add "
    +find_player(str)->query_name()+" to the list of enemies!\n");

    return 1;
}


// Remove player from enemy list
int
firemove_enemy(string str)
{
    // Only the alpha or the elder can make omegas.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Remove whom from the list of enemies?\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_guild_enemy(str) == 0)
    {
        write("YThat individual is not on the list of enemies.\n");
        return 1;
    }
    
    object playa = find_player(str);
    
    if (!playa)
    {
        write("No such player in the game.\n");

        return 1;
    }

    FIREKNIVES_MASTER->remove_guild_enemy(str);

    write("You remove "
    +find_player(str)->query_name()+" to the list of enemies!\n");

    return 1;
}


// Add player to enemy list
int
fiadd_crow(string str)
{
    // Only the alpha or the elder can make omegas.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Add who to the list of crows?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 1)
    {
        write("You can't add members to the list of crows.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_crow(str) == 1)
    {
        write("That person is already a member of the crows.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_guild_enemy(str) == 1)
    {
        write("That person is on the list of enemies.\n");
        return 1;
    }
    
    object playa = find_player(str);
    
    if (!playa)
    {
        write("No such player in the game.\n");

        return 1;
    }

    FIREKNIVES_MASTER->add_crow(str);

    write("You add "
    +find_player(str)->query_name()+" to the list of crows!\n");

    return 1;
}


// Remove player from enemy list
int
firemove_crow(string str)
{
    // Only the alpha or the elder can make omegas.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Remove whom from the list of crows?\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_crow(str) == 0)
    {
        write("That individual is not a crow.\n");
        return 1;
    }
    
    /*object playa = find_player(str);
    
    if (!playa)
    {
        write("No such player in the game.\n");

        return 1;
    }*/

    FIREKNIVES_MASTER->remove_crow(str);

    write("You remove "
    +capitalize(str)+" from the list of crows!\n");

    return 1;
}


int
reward_ability1(string str)
{
    // Only the alpha or the elder can enable abilities.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Enable Garrote to what member?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    int x;

    x = FIREKNIVES_MAPPINGS->query_ability1(str);
    
    object firek = find_player(str);
    
    if (firek == 0)
    {
        write("That player is not in the realms at the moment.\n");
        
        return 1;
    }

    if (x > 0)
    {
        write(find_player(str)->query_name()+" has Garrote "
        +"activated already.\n");

        return 1;
    }

    FIREKNIVES_MAPPINGS->set_ability1(str, 1);

    tell_object(find_player(str),"A new ability is available to you.\n");

    write("You enable Garrote to "
    +find_player(str)->query_name()+"!\n");
    
    REWARD_LOG("ability_log",
    "The member "+find_player(str)->query_name()
    +" got Garrote enbled by "
    +"by "+this_player()->query_name()+".\n");

    return 1;
}


int
reward_ability2(string str)
{
    // Only the alpha or the elder can enable abilities.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Enable Evade to what member?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    int x;

    x = FIREKNIVES_MAPPINGS->query_ability2(str);
    
    object firek = find_player(str);
    
    if (firek == 0)
    {
        write("That player is not in the realms at the moment.\n");
        
        return 1;
    }

    if (x > 0)
    {
        write(find_player(str)->query_name()+" has Evade "
        +"activated already.\n");

        return 1;
    }

    FIREKNIVES_MAPPINGS->set_ability2(str, 1);

    tell_object(find_player(str),"A new ability is available to you.\n");

    write("You enable Evade to "
    +find_player(str)->query_name()+"!\n");
    
    REWARD_LOG("ability_log",
    "The member "+find_player(str)->query_name()
    +" got Evade enbled by "
    +"by "+this_player()->query_name()+".\n");

    return 1;
}


int
reward_ability3(string str)
{
    // Only the alpha or the elder can enable abilities.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Enable Blind to what member?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    int x;

    x = FIREKNIVES_MAPPINGS->query_ability3(str);
    
    object firek = find_player(str);
    
    if (firek == 0)
    {
        write("That player is not in the realms at the moment.\n");
        
        return 1;
    }

    if (x > 0)
    {
        write(find_player(str)->query_name()+" has Blind "
        +"activated already.\n");

        return 1;
    }

    FIREKNIVES_MAPPINGS->set_ability3(str, 1);

    tell_object(find_player(str),"A new ability is available to you.\n");

    write("You enable Blind to "
    +find_player(str)->query_name()+"!\n");
    
    REWARD_LOG("ability_log",
    "The member "+find_player(str)->query_name()
    +" got Blind enbled by "
    +"by "+this_player()->query_name()+".\n");

    return 1;
}


int
reward_ability4(string str)
{
    // Only the alpha or the elder can enable abilities.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Enable Stun to what member?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    int x;

    x = FIREKNIVES_MAPPINGS->query_ability4(str);
    
    object firek = find_player(str);
    
    if (firek == 0)
    {
        write("That player is not in the realms at the moment.\n");
        
        return 1;
    }

    if (x > 0)
    {
        write(find_player(str)->query_name()+" has Stun "
        +"activated already.\n");

        return 1;
    }

    FIREKNIVES_MAPPINGS->set_ability4(str, 1);

    tell_object(find_player(str),"A new ability is available to you.\n");

    write("You enable Stun to "
    +find_player(str)->query_name()+"!\n");
    
    REWARD_LOG("ability_log",
    "The member "+find_player(str)->query_name()
    +" got Stun enbled by "
    +"by "+this_player()->query_name()+".\n");

    return 1;
}


int
reward_ability5(string str)
{
    // Only the alpha or the elder can enable abilities.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Enable Torpefy to what member?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    int x;

    x = FIREKNIVES_MAPPINGS->query_ability5(str);
    
    object firek = find_player(str);
    
    if (firek == 0)
    {
        write("That player is not in the realms at the moment.\n");
        
        return 1;
    }

    if (x > 0)
    {
        write(find_player(str)->query_name()+" has Torpefy "
        +"activated already.\n");

        return 1;
    }

    FIREKNIVES_MAPPINGS->set_ability5(str, 1);

    tell_object(find_player(str),"A new recipe is available to you.\n");

    write("You enable Torpefy to "
    +find_player(str)->query_name()+"!\n");
    
    REWARD_LOG("ability_log",
    "The member "+find_player(str)->query_name()
    +" got Torpefy enbled by "
    +"by "+this_player()->query_name()+".\n");

    return 1;
}


remove_ability1(string str)
{
    // Only the alpha or the elder can enable abilities.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Remove Garrote from what member?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    int x;

    x = FIREKNIVES_MAPPINGS->query_ability1(str);
    
    object firek = find_player(str);
    
    if (firek == 0)
    {
        write("That player is not in the realms at the moment.\n");
        
        return 1;
    }

    if (x == 0)
    {
        write(find_player(str)->query_name()+" didn't have Garrote "
        +"activated.\n");

        return 1;
    }

    FIREKNIVES_MAPPINGS->clean_ability1(str);

    tell_object(find_player(str),"An ability has been diabled from "
    +"your arsenal.\n");

    write("You disable Garrote from "
    +find_player(str)->query_name()+"!\n");
    
    REWARD_LOG("ability_log",
    "The member "+find_player(str)->query_name()
    +" got Garrote disabled by "
    +"by "+this_player()->query_name()+".\n");

    return 1;
}


int
remove_ability2(string str)
{
    // Only the alpha or the elder can enable abilities.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Remove Garrote from what member?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    int x;

    x = FIREKNIVES_MAPPINGS->query_ability2(str);
    
    object firek = find_player(str);
    
    if (firek == 0)
    {
        write("That player is not in the realms at the moment.\n");
        
        return 1;
    }

    if (x == 0)
    {
        write(find_player(str)->query_name()+" didn't have Evade "
        +"activated.\n");

        return 1;
    }

    FIREKNIVES_MAPPINGS->clean_ability2(str);

    tell_object(find_player(str),"An ability has been diabled from "
    +"your arsenal.\n");

    write("You disable Evade from "
    +find_player(str)->query_name()+"!\n");
    
    REWARD_LOG("ability_log",
    "The member "+find_player(str)->query_name()
    +" got Evade disabled by "
    +"by "+this_player()->query_name()+".\n");

    return 1;
}


int
remove_ability3(string str)
{
    // Only the alpha or the elder can enable abilities.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Remove Blind from what member?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    int x;

    x = FIREKNIVES_MAPPINGS->query_ability3(str);
    
    object firek = find_player(str);
    
    if (firek == 0)
    {
        write("That player is not in the realms at the moment.\n");
        
        return 1;
    }

    if (x == 0)
    {
        write(find_player(str)->query_name()+" didn't have Blind "
        +"activated.\n");

        return 1;
    }

    FIREKNIVES_MAPPINGS->clean_ability3(str);

    tell_object(find_player(str),"An ability has been diabled from "
    +"your arsenal.\n");

    write("You disable Blind from "
    +find_player(str)->query_name()+"!\n");
    
    REWARD_LOG("ability_log",
    "The member "+find_player(str)->query_name()
    +" got Blind disabled by "
    +"by "+this_player()->query_name()+".\n");

    return 1;
}


int
remove_ability4(string str)
{
    // Only the alpha or the elder can enable abilities.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Remove Stun from what member?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    int x;

    x = FIREKNIVES_MAPPINGS->query_ability4(str);
    
    object firek = find_player(str);
    
    if (firek == 0)
    {
        write("That player is not in the realms at the moment.\n");
        
        return 1;
    }

    if (x == 0)
    {
        write(find_player(str)->query_name()+" didn't have Stun "
        +"activated.\n");

        return 1;
    }

    FIREKNIVES_MAPPINGS->clean_ability4(str);

    tell_object(find_player(str),"An ability has been diabled from "
    +"your arsenal.\n");

    write("You disable Stun from "
    +find_player(str)->query_name()+"!\n");
    
    REWARD_LOG("ability_log",
    "The member "+find_player(str)->query_name()
    +" got Stun disabled by "
    +"by "+this_player()->query_name()+".\n");

    return 1;
}


int
remove_ability5(string str)
{
    // Only the alpha or the elder can enable abilities.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Remove Torpefy from what member?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    int x;

    x = FIREKNIVES_MAPPINGS->query_ability5(str);
    
    object firek = find_player(str);
    
    if (firek == 0)
    {
        write("That player is not in the realms at the moment.\n");
        
        return 1;
    }

    if (x == 0)
    {
        write(find_player(str)->query_name()+" didn't have Torpefy "
        +"activated.\n");

        return 1;
    }

    FIREKNIVES_MAPPINGS->clean_ability1(str);

    tell_object(find_player(str),"An ability has been diabled from "
    +"your arsenal.\n");

    write("You disable Torpefy from "
    +find_player(str)->query_name()+"!\n");
    
    REWARD_LOG("ability_log",
    "The member "+find_player(str)->query_name()
    +" got Torpefy disabled by "
    +"by "+this_player()->query_name()+".\n");

    return 1;
}


// Increase rank of a regular member
int
increase_rank(string str)
{
    // Only the alpha or the elder can make omegas.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    if (!str)
    {
        write("Increase rank of what member?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the chapter leader.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    int x;

    x = FIREKNIVES_MAPPINGS->query_assassin_rank(str);

    if (x >= FIREKNIVES_MAX_RANK_MEMBER)
    {
        // Cleanup. In case the rank os somehow above the
        // allowed limit.
        x = FIREKNIVES_MAX_RANK_MEMBER;
        FIREKNIVES_MAPPINGS->set_assassin_rank(str, x);

        write(find_player(str)->query_name()+" is already "
        +"at max possible rank for regular members!\n");

        return 1;
    }

    if (FIREKNIVES_MAPPINGS->query_assassin_rank(str) == MAX_PROSPECT_RANK)
    {
        if (!this_player()->query_wiz_level())
        {
            write("Prospects must be put through the Rite of Passage in "
            +"order to advance further!\n");

            return 1;
        }
        
        write(find_player(str)->query_name()+" was "
        +"at the highest possible rank for prospects, but since you "
        +"are a wizard, you can promote members into the "
        +"category of full members anyway.\n");
        
        FIREKNIVES_MASTER->add_guild_fullmember(str);
	    FIREKNIVES_MASTER->remove_guild_trainee(str);
    }

    x = x + 1;

    FIREKNIVES_MAPPINGS->set_assassin_rank(str, x);

    tell_object(find_player(str),"You have proven yourself in the eyes "
    +"of your peers and your reputation has improved!\n");

    write("You promote "
    +find_player(str)->query_name()+"!\n");
    
    REWARD_LOG("promote_log",
    "The member "+find_player(str)->query_name()
    +" was promoted a rank "
    +"by "+this_player()->query_name()+".\n");


    return 1;
}


// Decrease rank of a regular member.
int
decrease_rank(string str)
{
    // Only the alpha or the elder can adjust rank.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (!str)
    {
        write("Decrease rank of what member?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself.\n");
        return 1;
    }

    int x;

    x = FIREKNIVES_MAPPINGS->query_assassin_rank(str);

    if (x == MIN_FULLMEMBER_RANK)
    {
        if (!this_player()->query_wiz_level())
        {
            write(find_player(str)->query_name()+" is already "
            +"at the lowest possible rank for full members!\n");

            return 1;
        }
        
        write(find_player(str)->query_name()+" was "
        +"at the lowest possible rank for full members, but since you "
        +"are a wizard, you can demote members into "
        +"the category of prospects.\n");
        
        FIREKNIVES_MASTER->remove_guild_fullmember(str);
	    FIREKNIVES_MASTER->add_guild_trainee(str);
    }

    if (x <= FIREKNIVES_MIN_RANK_MEMBER)
    {
        // Cleanup, in case the value drops below 1.
        x = FIREKNIVES_MIN_RANK_MEMBER;
        FIREKNIVES_MAPPINGS->set_assassin_rank(str, x);


        write(find_player(str)->query_name()+" is already "
        +"at the lowest possible rank for prospects!\n");

        return 1;
    }

    x = x - 1;

    FIREKNIVES_MAPPINGS->set_assassin_rank(str, x);

    tell_object(find_player(str),"You have proven to be a "
    +"disappointment and your reputation has suffered!\n");
    
    write("You demote "
    +find_player(str)->query_name()+"!\n");
    
    PUNISH_LOG("demote_log",
    "The member "+find_player(str)->query_name()
    +" was demoted a rank "
    +"by "+this_player()->query_name()+".\n");

    return 1;
}


//---Promote a regular member to a Boss. WIZARDS ONLY-----------
int
add_boss(string str)
{
    if (!this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (!str)
    {
        write("Promote what member to become the Boss "
        +"for the Fire Knives?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("The member is already the Boss.\n");
        return 1;
    }
        
    /*if (FIREKNIVES_MAPPINGS->query_assassin_xcouncil_activity_cooldown(str) == 1)
    {
        write("The member recently failed as a council member, and is for "
        +"now unfit for the position.\n");
        return 1;
    }*/
        
    if (str == this_player()->query_name())
    {
        write("You can't promote yourself to Boss, Mr.Wizard!\n");
        return 1;
    }

    tell_object(find_player(str),"You have been promoted to the "
    +"Elder by "+this_player()->query_name()+"!\n");

    write("You promote "+find_player(str)->query_name()+" to the Elder!\n");

    FIREKNIVES_MAPPINGS->set_assassin_rank(str, FIREKNIVES_MAX_RANK_MEMBER);
    FIREKNIVES_MASTER->add_occ_boss_fireknife(str);
	FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(str, 1000);
	
    FIREKNIVES_MASTER->remove_occ_mentor_fireknife(str);
    FIREKNIVES_MASTER->remove_occ_thefist_fireknife(str);
	
	FIREKNIVES_MASTER->remove_guild_fullmember(str);
	FIREKNIVES_MASTER->remove_guild_trainee(str);

    return 1;
}


int
do_addlibrarian(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
	    FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
	    FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (!str)
    {
        write("Add who to the position of Archivist?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }
	
	if (FIREKNIVES_MASTER->is_occ_librarian(str) == 1)
    {
        write("That person is already an Archivist of the Brotherhood.\n");
        return 1;
    }
    
    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself!\n");
        return 1;
    }
    
    // This should never happen, but we add the check anyway, just in case.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder!\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor!\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist!\n");
        return 1;
    }

    tell_object(find_player(str),"You have been promoted to the "
    +"position of Archivist of the Brotherhood by "
	+this_player()->query_name()+"!\n");

    write("You promote "+find_player(str)->query_name()+" to the new "
	+"position of Archivist of the Brotherhood!\n");

    FIREKNIVES_MASTER->add_occ_librarian(str);
	
    return 1;
}


int
do_removelibrarian(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
	    FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
	    FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (!str)
    {
        write("Remove whom from the position of Archivist?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }
	
	if (FIREKNIVES_MASTER->is_occ_librarian(str) == 0)
    {
        write("That person is not an Archivist of the Brotherhood.\n");
        return 1;
    }
    
    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself!\n");
        return 1;
    }
    
    // This should never happen, but we add the check anyway, just in case.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder!\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor!\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist!\n");
        return 1;
    }

    tell_object(find_player(str),"You have been removed from the "
    +"position of Archivist of the Brotherhood by "
	+this_player()->query_name()+"!\n");

    write("You remove "+find_player(str)->query_name()+" from the "
	+"position of Archivist of the Brotherhood!\n");

    FIREKNIVES_MASTER->remove_occ_librarian(str);
	
    return 1;
}


int
do_addwhisper(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
	    FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
	    FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (!str)
    {
        write("Add who to the position of Whisper?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }
	
	if (FIREKNIVES_MASTER->is_occ_whisper(str) == 1)
    {
        write("That person is already an Whisper of the Brotherhood.\n");
        return 1;
    }
    
    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself!\n");
        return 1;
    }
    
    // This should never happen, but we add the check anyway, just in case.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder!\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor!\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist!\n");
        return 1;
    }

    tell_object(find_player(str),"You have been promoted to the "
    +"position of a Whisper of the Brotherhood by "
	+this_player()->query_name()+"!\n");

    write("You promote "+find_player(str)->query_name()+" to the new "
	+"position of a Whisper of the Brotherhood!\n");

    FIREKNIVES_MASTER->add_occ_whisper(str);
	
    return 1;
}


int
do_removewhisper(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
	    FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
	    FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (!str)
    {
        write("Remove whom from the position of Archivist?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }
	
	if (FIREKNIVES_MASTER->is_occ_whisper(str) == 0)
    {
        write("That person is not a Whisper of the Brotherhood.\n");
        return 1;
    }
    
    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself!\n");
        return 1;
    }
    
    // This should never happen, but we add the check anyway, just in case.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder!\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor!\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist!\n");
        return 1;
    }

    tell_object(find_player(str),"You have been removed from the "
    +"position of a Whisper of the Brotherhood by "
	+this_player()->query_name()+"!\n");

    write("You remove "+find_player(str)->query_name()+" from the "
	+"position of a Whisper of the Brotherhood!\n");

    FIREKNIVES_MASTER->remove_occ_whisper(str);
	
    return 1;
}


int
do_addhonorableposition(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
	    FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
	    FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (!str)
    {
        write("Add who to the position of Archivist?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }
	
	if (FIREKNIVES_MASTER->is_occ_retired_council(str) == 1)
    {
        write("That person is already an Archivist of the Brotherhood.\n");
        return 1;
    }
    
    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself!\n");
        return 1;
    }
    
    // This should never happen, but we add the check anyway, just in case.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder!\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor!\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist!\n");
        return 1;
    }

    tell_object(find_player(str),"You have been promoted to the "
    +"position of Archivist of the Brotherhood by "
	+this_player()->query_name()+"!\n");

    write("You promote "+find_player(str)->query_name()+" to the new "
	+"position of Archivist of the Brotherhood!\n");

    FIREKNIVES_MASTER->add_occ_retired_council(str);
	
    return 1;
}


int
do_removehonorableposition(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
	    FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
	    FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (!str)
    {
        write("Remove whom from the position of Archivist?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }
	
	if (FIREKNIVES_MASTER->is_occ_retired_council(str) == 0)
    {
        write("That person is not an Archivist of the Brotherhood.\n");
        return 1;
    }
    
    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself!\n");
        return 1;
    }
    
    // This should never happen, but we add the check anyway, just in case.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder!\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("You can't use this function on the Inquisitor!\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("You can't use this function on the Fist!\n");
        return 1;
    }

    tell_object(find_player(str),"You have been removed from the "
    +"position of Archivist of the Brotherhood by "
	+this_player()->query_name()+"!\n");

    write("You remove "+find_player(str)->query_name()+" from the "
	+"position of Archivist of the Brotherhood!\n");

    FIREKNIVES_MASTER->remove_occ_retired_council(str);
	
    return 1;
}



//---Promote a regular member to the status of Mentor -----------------
int
do_fipromote_mentor(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (!str)
    {
        write("Promote what member to become the Inquisitor?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }
    
    /*if (FIREKNIVES_MAPPINGS->query_assassin_xcouncil_activity_cooldown(str) == 1)
    {
        write("The member recently failed as a council member, and is for "
        +"now unfit for the position.\n");
        return 1;
    }*/

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself! Promote whom "
        +"to become the "
        +"new Inquisitor?\n");
        return 1;
    }
    
    // This should never happen, but we add the check anyway, just in case.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder! Promote "
        +"whom to become the "
        +"new Inquisitor?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("That member is already the Inquisitor of the Fire Knives.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("That member is the Fist of the Fire Knives, so this "
        +"is not possible.\n");
        return 1;
    }

    tell_object(find_player(str),"You have been promoted to the "
    +"Inquisitor by "+this_player()->query_name()+"!\n");

    write("You promote "+find_player(str)->query_name()+" to the new "
	+"poisition to Inquisitor!\n");

    FIREKNIVES_MAPPINGS->set_assassin_rank(str, FIREKNIVES_MAX_RANK_MEMBER);
    FIREKNIVES_MASTER->add_occ_mentor_fireknife(str);
	FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(str, 1000);
	
	FIREKNIVES_MASTER->remove_guild_fullmember(str);
	FIREKNIVES_MASTER->remove_guild_trainee(str);

    return 1;
}


//---Promote a regular member to the status of The Fist -----------------
int
do_fipromote_thefist(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (!str)
    {
        write("Promote what member to become the Fist?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }
    
    /*if (FIREKNIVES_MAPPINGS->query_assassin_xcouncil_activity_cooldown(str) == 1)
    {
        write("The member recently failed as a council member, and is for "
        +"now unfit for the position.\n");
        return 1;
    }*/

    if (str == this_player()->query_name())
    {
        write("You can't use this function on yourself! Promote "
        +"whom to become the "
        +"Fist?\n");
        return 1;
    }
    
    // This should never happen, but we add the check anyway, just in case.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You can't use this function on the Elder! Promote "
        +"whom to become the "
        +"Fist?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("That member is the Fist of the Fire Knives, so this "
        +"is not possible.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("That member is already the Fist of the Fire Knives.\n");
        return 1;
    }

    tell_object(find_player(str),"You have been promoted to the "
    +"Fist by "+this_player()->query_name()+"!\n");

    write("You promote "+find_player(str)->query_name()+" to the Fist!\n");

    FIREKNIVES_MAPPINGS->set_assassin_rank(str, FIREKNIVES_MAX_RANK_MEMBER);
    FIREKNIVES_MASTER->add_occ_thefist_fireknife(str);
	FIREKNIVES_MAPPINGS->set_assassin_council_activity_gauge(str, 1000);
	
	FIREKNIVES_MASTER->remove_guild_fullmember(str);
	FIREKNIVES_MASTER->remove_guild_trainee(str);

    return 1;
}


//--------Demote a council member back to a regular member-----
int
do_fidemote_councilmember(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (!str)
    {
        write("Demote which council member?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        tell_object(find_player(str),"You have been demoted from "
        +"the council by "+this_player()->query_name()+"!\n");

        write("You demote "+find_player(str)->query_name()
        +" from the council!\n");
        
        FIREKNIVES_MASTER->remove_occ_mentor_fireknife(str);
		FIREKNIVES_MASTER->add_guild_fullmember(str);
		FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(str);
        FIREKNIVES_MAPPINGS->set_assassin_xcouncil_activity_cooldown(str, 1);
        
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        tell_object(find_player(str),"You have been demoted from "
        +"the council by "+this_player()->query_name()+"!\n");

        write("You demote "+find_player(str)->query_name()
        +" from the council!\n");
        
        FIREKNIVES_MASTER->remove_occ_thefist_fireknife(str);
		FIREKNIVES_MASTER->add_guild_fullmember(str);
		FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(str);
        FIREKNIVES_MAPPINGS->set_assassin_xcouncil_activity_cooldown(str, 1);
        
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("Being the Elder, this function is not applicable to you.\n");
        return 1;
    }

    write("That person is not a member of the council.\n");

    return 1;
}


//----------Giving away the Elder role to another council member---------------
int
do_fileader(string str)
{
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
     !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You are already the Elder! Select someone else "
        +"to succeed you!\n");
        return 1;
    }
    
    if (FIREKNIVES_MAPPINGS->query_assassin_xcouncil_activity_cooldown(str) == 1)
    {
        write("The member recently failed as a council member, and is for "
        +"now unfit for the position.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("That person is already the Elder.\n");
        return 1;
    }


    FIREKNIVES_MASTER->add_occ_boss_fireknife(str);
    FIREKNIVES_MASTER->remove_occ_thefist_fireknife(str);
    FIREKNIVES_MASTER->remove_occ_mentor_fireknife(str);
	
	FIREKNIVES_MASTER->remove_guild_fullmember(str);
	FIREKNIVES_MASTER->remove_guild_trainee(str);

    FIREKNIVES_MASTER->remove_occ_boss_fireknife(this_player()->query_name());
	FIREKNIVES_MASTER->add_guild_fullmember(this_player()->query_name());
	FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(this_player()->query_name());
	

    tell_object(find_player(str),"You have been promoted to "
    +"the new Elder by "+this_player()->query_name()+"!\n");

    write("You promote "+find_player(str)->query_name()
    +" to succeed you as the new Elder!\nYou step down into the regular "
    +"ranks of the outfit.");

    return 1;
}


int
do_fiexchange_fist(string str)
{
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
     !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You are already the Fist! Select someone else "
        +"to succeed you!\n");
        return 1;
    }
    
    if (FIREKNIVES_MAPPINGS->query_assassin_xcouncil_activity_cooldown(str) == 1)
    {
        write("The member recently failed as a council member, and is for "
        +"now unfit for the position.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("That person is already the Fist.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("That person is the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("That person is the Elder.\n");
        return 1;
    }

    FIREKNIVES_MASTER->remove_occ_thefist_fireknife(this_player()->query_name());
	FIREKNIVES_MASTER->add_guild_fullmember(this_player()->query_name());
	FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(this_player()->query_name());
    
    FIREKNIVES_MASTER->add_occ_thefist_fireknife(str);   
	FIREKNIVES_MASTER->remove_guild_fullmember(str);
	FIREKNIVES_MASTER->remove_guild_trainee(str);

    tell_object(find_player(str),"You have been promoted to "
    +"the new Fist by "+this_player()->query_name()+"!\n");

    write("You promote "+find_player(str)->query_name()
    +" to succeed you as the new Fist!\nYou step down into the regular "
    +"ranks of the brotherhood.");

    return 1;
}


int
do_fiexchange_inquisitor(string str)
{
    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
     !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You are already the Inquisitor! Select someone else "
        +"to succeed you!\n");
        return 1;
    }
    
    if (FIREKNIVES_MAPPINGS->query_assassin_xcouncil_activity_cooldown(str) == 1)
    {
        write("The member recently failed as a council member, and is for "
        +"now unfit for the position.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        write("That person is already the Inquisitor.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        write("That person is the Fist.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("That person is the Elder.\n");
        return 1;
    }

    FIREKNIVES_MASTER->remove_occ_mentor_fireknife(this_player()->query_name());
	FIREKNIVES_MASTER->add_guild_fullmember(this_player()->query_name());
	FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(this_player()->query_name());
    
    FIREKNIVES_MASTER->add_occ_mentor_fireknife(str);   
	FIREKNIVES_MASTER->remove_guild_fullmember(str);
	FIREKNIVES_MASTER->remove_guild_trainee(str);

    tell_object(find_player(str),"You have been promoted to "
    +"the new Inquisitor by "+this_player()->query_name()+"!\n");

    write("You promote "+find_player(str)->query_name()
    +" to succeed you as the new Inquisitor!\nYou step down into the regular "
    +"ranks of the brotherhood.");

    return 1;
}


//----------Resigning from the Elder or council position ---------------
int
do_firesign()
{
    string str;

    str = this_player()->query_name();

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 1)
    {
        FIREKNIVES_MASTER->remove_occ_boss_fireknife(str);
		FIREKNIVES_MASTER->add_guild_fullmember(str);
		FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(this_player()->query_name());
        FIREKNIVES_MAPPINGS->set_assassin_xcouncil_activity_cooldown(this_player()->query_name(), 1);
		

        write("You resign the position of the Elder, and return to "
        +"the regular ranks of the outfit.\n");

        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 1)
    {
        FIREKNIVES_MASTER->remove_occ_mentor_fireknife(str);
		FIREKNIVES_MASTER->add_guild_fullmember(str);
		FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(this_player()->query_name());
        FIREKNIVES_MAPPINGS->set_assassin_xcouncil_activity_cooldown(this_player()->query_name(), 1);

        write("You resign the position of the Mentor, and return to "
        +"the regular ranks of the outfit.\n");

        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 1)
    {
        FIREKNIVES_MASTER->remove_occ_thefist_fireknife(str);
		FIREKNIVES_MASTER->add_guild_fullmember(str);
		FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(this_player()->query_name());
        FIREKNIVES_MAPPINGS->set_assassin_xcouncil_activity_cooldown(this_player()->query_name(), 1);
        
        write("You resign the position of the Fist, and return to "
        +"the regular ranks of the outfit.\n");

        return 1;
    }

    return 0;
}


int
do_fiexpel(string str)
{
    setuid();
    seteuid(getuid());
    
    object expelplayer;

    // Only the Elder and the coulcin can expel members from the outfit.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
            write("What?\n");
            return 1;
    }

    if (!str)
    {
        write("Expel what member from the Fire Knives?\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_fireknife(str) == 0)
    {
        write("That person is not a member of the Fire Knives.\n");
        return 1;
    }

    if (str == this_player()->query_name())
    {
        write("You can't Expel yourself!\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(str) == 1)
    {
        write("You have no authority to expel the Elder from the outfit.\n");
        return 1;
    }

    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(str) == 1)
    {
        if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 1)
        {
            FIREKNIVES_MASTER->remove_occ_fireknife(str);
            FIREKNIVES_MASTER->remove_occ_mentor_fireknife(str);
            FIREKNIVES_MASTER->remove_occ_thefist_fireknife(str);
			FIREKNIVES_MASTER->remove_guild_fullmember(str);
			FIREKNIVES_MASTER->remove_guild_trainee(str);
			FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(this_player()->query_name());

            write("You expel "+capitalize(str)
            +" from the Fire Knives outfit!\n");
      
            expelplayer = find_player(str);
            
            if (expelplayer == 0)
            {
                return 1;
            }
                    
            clone_object(FIREKNIVES_GUILD_DIR 
            + "obj/expel_obj")->move(expelplayer, 1);
            
            set_alarm(0.5, 0.0, &expel_player(expelplayer));
            
            EXPELLED_LOG("expelled_log",
            "The Councilmember " +str
            +" was expelled from the Brotherhood "
            +"by "+this_player()->query_name()+" (Boss).\n");
            
            return 1;
        }    
        
        write("You have no permission to expel other council members.\n");
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(str) == 1)
    {
        if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 1)
        {
            FIREKNIVES_MASTER->remove_occ_fireknife(str);
            FIREKNIVES_MASTER->remove_occ_mentor_fireknife(str);
            FIREKNIVES_MASTER->remove_occ_thefist_fireknife(str);
			FIREKNIVES_MASTER->remove_guild_fullmember(str);
			FIREKNIVES_MASTER->remove_guild_trainee(str);
			FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(this_player()->query_name());

            write("You expel "+capitalize(str)
            +" from the Fire Knives outfit!\n");
      
            expelplayer = find_player(str);
            
            if (expelplayer == 0)
            {
                return 1;
            }
                    
            clone_object(FIREKNIVES_GUILD_DIR 
            + "obj/expel_obj")->move(expelplayer, 1);
            
            set_alarm(0.5, 0.0, &expel_player(expelplayer));
            
            EXPELLED_LOG("expelled_log",
            "The Councilmember " +str 
            +" was expelled from the Brotherhood "
            +"by "+this_player()->query_name()+" (Boss).\n");
            
            return 1;
        }    
        
        write("You have no permission to expel other council members.\n");
        return 1;
    }
      
    FIREKNIVES_MASTER->remove_occ_fireknife(str);
	FIREKNIVES_MASTER->remove_guild_fullmember(str);
    FIREKNIVES_MASTER->remove_guild_trainee(str);
	FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(this_player()->query_name());
    
    write("You expel "+capitalize(str)+" from the Fire Knives outfit!\n");
      
    expelplayer = find_player(str);
    
    if (expelplayer == 0)
    {
        return 1;
    }
            
    clone_object(FIREKNIVES_GUILD_DIR 
    + "obj/expel_obj")->move(expelplayer, 1);
    
    set_alarm(0.5, 0.0, &expel_player(expelplayer));
    
    EXPELLED_LOG("expelled_log",
    "The member " +str
    +" was expelled from the Brotherhood "
    +"by "+this_player()->query_name()+".\n");
 
    return 1;
}


int
betray_the_outfit(string str)
{
    setuid();
    seteuid(getuid());
    
    if (str == "the fire knives brotherhood")
    {
        if (FIREKNIVES_MASTER->is_occ_fireknife(this_player()->query_name()) == 1)
        {
            FIREKNIVES_MASTER->remove_occ_fireknife(this_player()->query_name());
			FIREKNIVES_MASTER->remove_guild_fullmember(this_player()->query_name());
			FIREKNIVES_MASTER->remove_guild_trainee(this_player()->query_name());
			FIREKNIVES_MAPPINGS->clean_assassin_council_activity_gauge(this_player()->query_name());
            
            clone_object(FIREKNIVES_GUILD_DIR 
            + "obj/expel_obj")->move(this_player(), 1);
            
            set_alarm(0.5, 0.0, &expel_mee());
            
            LEAVE_LOG("leave_log",
            "The member "+this_player()->query_name()+" " 
            +"betrayed the Brotherhood and left the guild.\n");
            
            return 1;
        }
        
        write("You have already betrayed the brotherhood.\n");
        
        return 1;
    }
    
    write("Betray what? 'betray the fire knives brotherhood'?\n");
    
    return 1;
}


int
s_fiincognito(string arg)
{
    if ((arg != "on") && (arg != "off"))
    {
        if (this_player()->query_fireknife_incogn() == 1)
        {
            notify_fail(capitalize(query_verb()) + " on/off?\nYou are "
            +"currently not hiding your identity at the moment.\n");
            return 0;
        }

        notify_fail(capitalize(query_verb()) + " on/off?\nYou are "
        +"currently hiding your identity.\n");
        return 0;
    }

    if (arg == "off")
    {
        if (this_player()->query_fireknife_incogn() == 1)
        {
            write("But you are not trying to hide your identity!\n");
            return 1;
        }

        this_player()->set_fireknife_incogn(1);
        write("You stop trying to hide your identity.\n");
        return 1;
    }

    if (this_player()->query_fireknife_incogn() == 1)
    {
        this_player()->set_fireknife_incogn(0);

        write("You will try to hide your identity.\n");
        
        return 1;
    }

    write("You are currently hiding your identity.\n");

    return 1;
}
    

public int
filist(string str)
{
    setuid();
    seteuid(getuid());

    MEMBER_LIST_UTILITY->list_members();

    return 1;
}


public int
fienemylist()
{
    string list;
    
    setuid();
    seteuid(getuid());

    list = FIREKNIVES_MASTER->list_guild_enemies();
    
    write(list);

    return 1;
}


public int
ficrowlist()
{
    string list;
    
    setuid();
    seteuid(getuid());
    
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    list = FIREKNIVES_MASTER->list_crows_list();
    
    if (list == 0)
    {
        write("There are currently no registered agents of the Brotherhood.\n");

        return 1;
    }
    
    write("Registered agents of the Brotherhood:\n"+list);

    return 1;
}


public int
do_fiactivity()
{
    string activity;
    int level_boss, level_mentor, level_fist;
    

    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()))
    {
        level_boss = FIREKNIVES_MASTER->query_activity_meter_boss();
        
        if (level_boss > 900)
        {
            write("You are favored by the Grandfather.\n");
            
            return 1;
        }
        
        if (level_boss > 700)
        {
            write("Your position with the Grandfather is solidified.\n");
            
            return 1;
        }
        
        if (level_boss > 500)
        {
            write("You are in good standing with the Grandfather.\n");
            
            return 1;
        }
        
        if (level_boss > 300)
        {
            write("You are accepted by the Grandfather.\n");
            
            return 1;
        }
        
        if (level_boss > 100)
        {
            write("You are losing your standing with the Grandfather.\n");
            
            return 1;
        }
        
        if (level_boss > 5)
        {
            write("The Grandfather is displeased with your effort and you are about to be replaced.\n");
            
            return 1;
        }
        
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()))
    {
        level_mentor = FIREKNIVES_MASTER->query_activity_meter_mentor();
        
        if (level_mentor > 900)
        {
            write("You are favored by the Grandfather.\n");
            
            return 1;
        }
        
        if (level_mentor > 700)
        {
            write("Your position with the Grandfather is solidified.\n");
            
            return 1;
        }
        
        if (level_mentor > 500)
        {
            write("You are in good standing with the Grandfather.\n");
            
            return 1;
        }
        
        if (level_mentor > 300)
        {
            write("You are accepted by the Grandfather.\n");
            
            return 1;
        }
        
        if (level_mentor > 100)
        {
            write("You are losing your standing with the Grandfather.\n");
            
            return 1;
        }
        
        if (level_mentor > 5)
        {
            write("The Grandfather is displeased with your effort and you are about to be replaced.\n");
            
            return 1;
        }
        
        return 1;
    }
    
    if (FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()))
    {
        level_fist = FIREKNIVES_MASTER->query_activity_meter_fist();
        
        if (level_fist > 900)
        {
            write("You are favored by the Grandfather.\n");
            
            return 1;
        }
        
        if (level_fist > 700)
        {
            write("Your position with the Grandfather is solidified.\n");
            
            return 1;
        }
        
        if (level_fist > 500)
        {
            write("You are in good standing with the Grandfather.\n");
            
            return 1;
        }
        
        if (level_fist > 300)
        {
            write("You are accepted by the Grandfather.\n");
            
            return 1;
        }
        
        if (level_fist > 100)
        {
            write("You are losing your standing with the Grandfather.\n");
            
            return 1;
        }
        
        if (level_fist > 5)
        {
            write("The Grandfather is displeased with your effort and you are about to be replaced.\n");
            
            return 1;
        }
        
        return 1;
    }

    return 0;
}


public int
fimemberlist()
{
    string list;
    
    setuid();
    seteuid(getuid());
	
	// Only Elders can use this function.
    if (FIREKNIVES_MASTER->is_occ_boss_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_mentor_fireknife(this_player()->query_name()) == 0 &&
        FIREKNIVES_MASTER->is_occ_thefist_fireknife(this_player()->query_name()) == 0 &&
        !this_player()->query_wiz_level())
    {
        return 0;
    }

    list = FIREKNIVES_MASTER->list_guild_members();
    
    write(list);

    return 1;
}


int
set_component(string str)
{
    herb_component = str;

    return 1;
}


string
query_component()
{
    return herb_component;
}


string
query_alchemyset()
{
    return "alchemy_set";
}


int
create_oil(string str)
{
    object *obj;
    object *obb;

    string oil_ob_name;

    object oil1;

    if (!str)
    {
        write("Create which oil?\n");
        
        return 1;
    }

    // String for oils we want to make.
    switch(str)
    {
		case "torpefy":
        set_component("nettle");
        oil_ob_name = "crippling_oil";
        break;
		
        case "manslayer":
        set_component("hemlock");
        oil_ob_name = "manslayer_oil";
        break;
        
        case "eldarbane":
        set_component("crocus");
        oil_ob_name = "eldarbane_oil";
        break;
        
        case "dwarfbane":
        set_component("foxglove");
        oil_ob_name = "dwarfbane_oil";
        break;
        
        case "gnomeslayer":
        set_component("myrtleberry");
        oil_ob_name = "gnomeslayer_oil";
        break;
        
        case "halflingbane":
        set_component("nightshade");
        oil_ob_name = "halflingbane_oil";
        break;
        
        case "giantsbane":
        set_component("skullcap");
        oil_ob_name = "giantsbane_oil";
        break;
        
        case "dragonbane":
        set_component("mint");
        oil_ob_name = "dragonbane_oil";
        break;
        
        case "greenslayer":
        set_component("sumac");
        oil_ob_name = "greenslayer_oil";
        break;
        
        case "deathbane":
        set_component("garlic");
        oil_ob_name = "deathbane_oil";
        break;
        
        case "naturebane":
        set_component("amanita");
        oil_ob_name = "naturebane_oil";
        break;
        
        default:
        write("Create what? No valid oil type.\n");
        return 1;
    }
    
    // Alchemy set
    obb = filter(deep_inventory(this_player()),
    &operator(==)(query_alchemyset()) @&->query_name());

    if (!sizeof(obb))
    {
        write("You lack an alchemy set in order to create "
        +"this oil!\n");
        return 1;
    }
	
	if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) < AB1)
	{
		write("You are not eligible to create weapon oils.\n");
        return 1;
	}
	
	if (oil_ob_name == "crippling_oil" 
	&& FIREKNIVES_MAPPINGS->query_ability5(this_player()->query_name()) == 0)
	{
		write("You are not eligible to create this weapon oil.\n");
        return 1;
	}
    
    // Herb component
    obj = filter(deep_inventory(this_player()),
    &operator(==)(query_component()) @&->query_herb_name());

    if (!sizeof(obj))
    {
        write("You don't have the necessary herbal component to "
        +"create this oil!\n");
        return 1;
    }

    obj[0]->reduce_heap_size();
    
    int alchemyskill = this_player()->query_skill(SS_ALCHEMY);
    
    // Use of alchemy, and the chance to ruin the oil.
    if (random(43) > alchemyskill)
    {
        write("With the use of the alchemy set, you attempt "
        +"to create the desired oil but fails!\nYou "
        +"ruin a component!\n");
        
        return 1;
    }
    
    setuid();
    seteuid(getuid());

    oil1 = clone_object(FIREKNIVES_GUILD_DIR 
    + "specials/weaponoils/" + oil_ob_name);
    
    oil1->set_heap_size(3);
    oil1->move(this_player(), 1);

    write("With the use of the alchemy set, you create some "
    +oil1->query_short()+"s!\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player())
    +" uses an alchemy set to create something!\n", this_player());

    return 1;
}


int
do_ficreatecomp(string str)
{
    object *obj;
    object *obb;

    string comp_ob_name;

    object comp1;

    if (!str)
    {
        write("Create which component?\n");
        
        return 1;
    }

    // String for components we want to make.
    switch(str)
    {
        case "wire":
        set_component("intestine");
        comp_ob_name = "garotte_wire";
        break;
        
        case "powder":
        set_component("pepper");
        comp_ob_name = "blinding_powder";
        break;
         
        default:
        write("Create what? No valid component type.\n");
        return 1;
    }
    
    // Alchemy set
    obb = filter(deep_inventory(this_player()),
    &operator(==)(query_alchemyset()) @&->query_name());

    if (!sizeof(obb))
    {
        write("You lack an alchemy set in order to create "
        +"this component!\n");
        return 1;
    }
    
    if (str == "wire")
    {
        // Component
        obj = filter(deep_inventory(this_player()),
        &operator(==)(query_component()) @&->query_name());

        if (!sizeof(obj))
        {
            write("You don't have the required item to "
            +"create this component!\n");
            return 1;
        }
    }
    
    if (str == "powder")
    {
        // Herbal Component
        obj = filter(deep_inventory(this_player()),
        &operator(==)(query_component()) @&->query_herb_name());

        if (!sizeof(obj))
        {
            write("You don't have the required item to "
            +"create this component!\n");
            return 1;
        }
    }

    obj[0]->reduce_heap_size();

    setuid();
    seteuid(getuid());

    comp1 = clone_object(FIREKNIVES_GUILD_DIR 
    + "specials/obj/" + comp_ob_name);
    
    comp1->set_heap_size(2);
    comp1->move(this_player(), 1);

    write("With the use of the alchemy set, you create some "
    +comp1->query_short()+"s!\n");
    
    tell_room(environment(this_player()), QCTNAME(this_player())
    +" uses an alchemy set to create something!\n", this_player());
    
    CRAFTING_LOG("crafting_log",
    "The member "+this_player()->query_name()
    +" crafted "+comp1->query_short()+"(s).\n");

    return 1;
}


int
do_fihang(string str)
{
    setuid();
    seteuid(getuid());
    
    object *corpses, corpse, pole;
    
    if (FIREKNIVES_MAPPINGS->query_assassin_rank(this_player()->query_name()) < AB3)
    {
        return 0;
    }
    
    notify_fail("Hang what corpse?\n");
    if(!str)
        return 0;
    
    corpses = FIND_STR_IN_OBJECT(str, environment(this_player()));
    
    if(!sizeof(corpses))
        return 0;
    
    corpse = corpses[0];
    
    notify_fail("That is not a corpse.\n");
    if(!corpse->id("corpse") || living(corpse))
        return 0;
    
    notify_fail("You don't have a proper pole for this.\n");
    if(!present("_fireknives_pole_", this_player()))
        return 0;
    
    notify_fail("You are in water! Find a better place.\n");
    if (environment(this_player())->query_prop(ROOM_IN_WATER))
        return 0;
    
    notify_fail("You are under water! Find a better place.\n");
    if (environment(this_player())->query_prop(ROOM_UNDER_WATER))
        return 0;
    
    notify_fail("You are not at the ground!\n");
    if (environment(this_player())->query_prop(ROOM_IN_AIR))
        return 0;
    
    write("You set up the long wooden pole in the ground here, then attach "+
    "up the "+corpse->short()+" to the rope.\n");
    
    say(QCTNAME(this_player())+" sets up a long wooden pole "
	+"in the ground here, then attach "+
    "the "+corpse->short()+" on the dangling rope on it.\n");
    
    pole = clone_object(FIREKNIVES_GUILD_DIR + "obj/fireknives_pole");
    pole->set_real_name(capitalize(corpse->query_real_name()));
    pole->set_race_name(corpse->query_race_name());
    pole->set_corpse_short(corpse->query_nonmet_name());
    pole->add_prop(OBJ_I_WEIGHT,corpse->query_prop(CONT_I_WEIGHT));
    pole->add_prop(OBJ_I_VOLUME,corpse->query_prop(CONT_I_VOLUME));
    pole->move(environment(this_player()));
    
    corpse->remove_object();
    
    present("_fireknives_pole_", this_player())->remove_object();
    
    return 1;
}


int
do_fititlelist()
{
    write(""
    +"===========================================================-========--=\n"
    +"|              F I R E   K N I V E S ,    R A N K S                   |\n"
    +"|---------------------------------------------------------------------|\n"
    +"|  The ranks and titles within the brotherhood.                       |\n"
    +"|                                                                     |\n"
    +"|    The Elder, Keeper of Traditions    : Guildleader                 |\n"
    +"|    The Fist                           : Councilmember               |\n"
    +"|    The Inquisitor                     : Councilmember               |\n"
    +"|                                                                     |\n"
    +"|    Full Members                                                     |\n"
    +"|    -------------                                                    |\n"
    +"|    Bringer of Endless Night                                         |\n"
    +"|    Ender of Dreams                    : Coating, Crippling poison   |\n"
    +"|    Stygian Wraith                                                   |\n"
    +"|    Fearsome Asp                       : Stun                        |\n"
    +"|    Fatal Wish                                                       |\n"
    +"|    Poisoned Mist                                                    |\n"
    +"|    Whisper of Steel                                                 |\n"
    +"|    Glint in the Moonlight                                           |\n"
    +"|    Whispering Scythe                  : Blind                       |\n"
    +"|    Venom Barb                                                       |\n"
    +"|    Silent Shade                                                     |\n"
    +"|    Endless Twilight                                                 |\n"
    +"|    Deadly Breeze                                                    |\n"
    +"|    Midnight Shade                     : Evasion                     |\n"
    +"|    Light Tread                                                      |\n"
    +"|    Quiet Touch                                                      |\n"
    +"|    Black Orchid                                                     |\n"
    +"|    Keen Stiletto                                                    |\n"
    +"|    Dark Shadow                        : Garotte, Fihang <corpse     |\n"           
    +"|    Stealthy Dart                                                    |\n"
    +"|    Lurker in the Shadows                                            |\n"
    +"|                                                                     |\n"
    +"|    Trainees                                                         |\n"
    +"|    ---------                                                        |\n" 
    +"|    Accomplished Candidate Inhumer                                   |\n"
    +"|    Surviving Candidate Inhumer                                      |\n"
    +"|    Beginning Candidate Inhumer        : Eviscerate                  |\n"
    +"|    Initiate of the Third Level                                      |\n"
    +"|    Initiate of the Second Level                                     |\n"
    +"|    Initiate of the First Level        : Crafting and Envenom        |\n"
    +"|    Postulant                          : Backstab                    |\n"
    +"|_____________________________________________________________________|\n");

    return 1;
}



//////////////////////////// EMOTES /////////////////////////////
int do_fiindicate(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("Bow at whom?\n");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You gesture at",targ," with your head, bringing others "
    +"to its attention.");

    all2actbb(" gestures towards",targ," with "
    +HIS_HER(TP)+" head, bringing your attention to "
    +HIM_HER(targ[0])+".");
    
    targetbb(" gestures at you with "+HIS_HER(TP)+" head, "
    +"leaving you feeling exposed.",targ);

    return 1;
}
    

int do_fibow(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("Bow at whom?\n");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You bow forward slightly with your hands behind your back, never "
    +"taking your eyes off from",targ,".");

    all2actbb(" places "+HIS_HER(TP)+" hands behind "+HIS_HER(TP)
    +" back, slowly bowing to",targ," without taking "
    +HIS_HER(TP)+" eyes off of "+HIM_HER(targ[0])+".");
    
    targetbb(" places "+HIS_HER(TP)+" hands behind "+HIS_HER(TP)
    +" back, slowly bowing to you without taking "
    +HIS_HER(TP)+" eyes off of yours.",targ);

    return 1;
}
    
    
int do_fiack(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("At whom?\n");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You turn your head slightly towards",targ,", acknowledging "
    +"their presence.");

    all2actbb(" turns "+HIS_HER(TP)+" head slightly "
    +"towards",targ,", acknowledging their presence.");
    
    targetbb("'s head turns slightly towards you, aknowledging "
    +"your existence",targ);

    return 1;
}
    

int do_fiback(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("At whom?\n");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You take a step to slowly position yourself with your "
    +"back towards",targ,".");

    all2actbb(" moves to reposition "+HIM_HER(TP)+"self with "
    +HIS_HER(TP)+" back towards ",targ,".");
    
    targetbb(" moves to reposition "+HIM_HER(TP)+"self with "
    +HIS_HER(TP)+" back towards you.",targ);

    return 1;
}


int do_fitap(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("Tap whom?\n");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You sneak up behind",targ,", tapping "+HIM_HER(targ[0])
    +" on "+HIS_HER(targ[0])+" shoulder.");

    all2actbb(" appears behind",targ," tapping "+HIM_HER(targ[0])
    +" on "+HIS_HER(targ[0])+" shoulder.");
    
    targetbb(" suddenly taps your shoulder. Your whole body "
    +"tenses up.",targ);

    return 1;
}
    
    
int do_fiprice(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("Evaluate whom?\n");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You appraise",targ,", trying to decide how much you "
    +"would charge for their execution.");

    all2actbb("'s eyes measures",targ," worth, trying to decide how much "
    +HE_SHE(TP)+" would charge for "+HIS_HER(targ[0])+" execution");
    
    targetbb("'s eyes measures your worth, trying to decide "
    +"how much "+HE_SHE(TP)+" would charge for your execution.",targ);

    return 1;
}
    
    
int do_figaze(string str)
{
    object *targ;
    if(!strlen(str)) /* no string supplied */
    {
        write("Gaze at whom?\n");

        return 1;
    }

    targ = parse_this(str,"[the] %l");

    if(!sizeof(targ))
    return 0;

    actor("You gaze directly and intently at",targ,". "+HE_SHE(targ[0])
    +" suddenly feels like "+HIS_HER(targ[0])+" life is in danger.");

    all2actbb(" gazes directly and intently at",targ,". "+HE_SHE(targ[0])
    +" swallows uncomfortably.");
    
    targetbb(" gazes directly and intently at you. You suddenly "
    +"realize your life is in danger.",targ);

    return 1;
}
    

int
do_fiangry()
{
    write("Your eyelids tighten as your brows lower and draw "
    +"together in a contained expression of anger.\n");
    
    all("'s eyelids tighten as "+this_player()->query_possessive()
    +" brows lower and draw together in a contained expression of anger.");

    return 1;
}                   


int
do_ficrouch()
{
    write("You bend your knees and slowly pull your "
    +"body in, sitting on your heels.\n");
    
    all(" bends "+this_player()->query_possessive()
    +" knees and slowly pulls "
    +this_player()->query_possessive()+" body in, sitting on "
    +this_player()->query_possessive()+" heels.");

    return 1;
}                   
    

int
do_fiprepare()
{
    write("You hold the hilt of your blades on their sheaths, still "
    +"and readied for battle.\n");
    
    all(" holds the hilts of "+this_player()->query_possessive()
    +" blades on their sheaths, still and readied for battle.");

    return 1;
}                   


int
do_fipay()
{
    write("You repeatedly rub your thumb over the tip of the "
    +"index and middle finger in a hintful gesture.\n");
    
    all(" repeatedly rubs "+this_player()->query_possessive()
    +" thumb over the tip of "+this_player()->query_possessive()
    +" index and middle fingers in a hintful gesture.");

    return 1;
}               
    
    
int
do_fistretch()
{
    write("You move your shoulders for- and backwards in a circular "
    +"fashion, straightening your back.\n");
    
    all(" moves "+this_player()->query_possessive()+" shoulders "
    +"for- and backwards in a circular fashion, straightening "
    +this_player()->query_possessive()+" back.");

    return 1;
}               


int
do_fistance()
{
    write("You reposition your footing, digging slightly "
    +"into the ground and remaining steady.\n");
    
    all(" repositions "+this_player()->query_possessive()
    +" feet in a balanced stance, remaining steady.");

    return 1;
}           
    

int
do_fiscan()
{
    write("You stand completely still, your eyes darting around "
    +"the area scanning the possibilities.\n");
    
    all(" stands completely still for a moment, eyes darting around "
    +"the area, looking for something.");

    return 1;
}          


int
do_fibback()
{
    write("You take two steps backwards to fade into the "
    +"background, remaining silent and alert.\n");
    
    all(" takes two steps backwards to fade into the "
    +"background, remaining silent and alert.");

    return 1;
}       

   
int
do_fithreaten()
{
    write("You slide your index finger from ear to ear along the base "
    +"of your neck in a menacing gesture.\n");
    
    all(" slides his index finger from ear to ear along the base "
    +"of his neck in a menacing gesture.");

    return 1;
}   


int
do_fibreak()
{
    write("Your eyes suddenly roll backwards and you go into a trance.\n");
    
    all("'s eyes suddenly roll backwards and seems to go into a trance.");

    return 1;
}
