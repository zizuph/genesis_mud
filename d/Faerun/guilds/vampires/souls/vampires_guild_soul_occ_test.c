/*
 * Vampires Guild soul
 *
 * Nerull, 2020
 *
 */

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
#include <filter_funs.h>
#include <login.h>

object wield_par;

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Vampires"; }



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
    "vnation"             : "do_vnation",
    "vreputation"         : "do_vreputation",
    "vnationstanding"     : "do_vnationstanding",
    "vtargets"            : "do_vtargets",   
    "vsetcustomtitle"     : "do_vsettitle",
    "vcustomtitle"        : "do_vcustomtitle",
    "vlistcustomtitles"   : "do_vlisttitles",
    "vbugsandfixes"       : "do_vbugsandfixes",
        ]);
}


int
do_vbugsandfixes()
{ 
    write("|===========================================================|\n");
    write("|            B U G S,  F I X E S,  T O D O ' S              |\n");
    write("|-----------------------------------------------------------|\n");
    write("| This list contains changes, corrections, fixes and planned|\n");
    write("| TODO-items for the Vampire guild.                         |\n");
    write("|                                                           |\n");   
    write("| PLANNED / TODO / PLANNED BUGFIXES                         |\n");
    write("| ---------------------------------                         |\n");
    write("| Unfinished Tier 4 items.                                  |\n");
    write("|                                                           |\n");   
    write("|                                                           |\n");
    write("| DONE                                                      |\n");
    write("| ----                                                      |\n");
    write("| 02.10.2022:  By request of the AoB, a spell has been      |\n");
	write("|              removed from tier 3.                         |\n");
    write("|                                                           |\n");
    write("| 28.09.2022:  Claiming a coven no longer require points    |\n");
	write("|              in immortality, but will require a decent    |\n");
    write("|              level of blood saturation. Furthermore,      |\n");
    write("|              the requirement of having sired atleast one  |\n");
    write("|              vampire to claim a coven is also removed.    |\n");
    write("|                                                           |\n");
	write("| 26.08.2022:  Cost for claiming a coven has been abolished.|\n");
	write("|              Those who have paid the price will be        |\n");
	write("|              reimbursed.                                  |\n");
	write("|                                                           |\n");
    write("| 31.07.2022:  Some bugs related to spells fixed.           |\n");
    //write("|              Full vampires will be scryable for about     |\n");
    //write("|              2 minutes after they engage in combat.       |\n");
    write("|                                                           |\n");
    write("| 04.07.2022:  Tier 3 content finished. Ranks requiring     |\n");
    write("|              putting in work for the Vampire Nation now   |\n");
    write("|              also include the rank 'Vampire Lord'.        |\n");
    write("|                                                           |\n");
    write("| 21.05.2022:  Turning limitaton. When there are too        |\n");
    write("|              many active vampires in the game, creating   |\n");
    write("|              new ones through turning is denied.          |\n");
    write("|                                                           |\n");
    write("| 28.03.2022:  New command - vbugsandfixes (this list).     |\n");
    write("|                                                           |\n");
    write("| 22.03.2022:  Coven mutiny support (described in coven     |\n");
    write("|              helpfiles).                                  |\n");
    write("|                                                           |\n");
    write("| 22.03.2022:  Various typos corrected. Some will take      |\n");
    write("|              effect after the next armageddon.            |\n");
    write("|                                                           |\n");
    write("| 22.03.2022:  Function to add members to a coven now       |\n");
    write("|              requires the cancidate to be present in      |\n");
    write("|              the coven entryway.                          |\n");              
    write("|                                                           |\n");   
    write("|___________________________________________________________|\n");
    
    return 1;
}


int
do_vcustomtitle()
{ 
    string vvtitle;
    
    vvtitle = this_player()->query_guild_title_occ();
    
    if (vvtitle == 0)
    {
        write("You haven't yet selected a public title. Please refer to 'vlisttitles' "
        +"for further instructions.\n");
    
        return 1;
    }
    
    write("Your selected public title is: "+vvtitle+"\n");
    
    return 1;
}


int
vsettitlee(int i)
{
    VAMPIRES_MAPPINGS->set_vamp_title(this_player()->query_name(), i);
    return 1;
}


int
do_vsettitle(int i)
{ 
    int vtitl;
    
    vtitl = i;
    
    int conv;
    
    conv = atoi(i);
    
    if (conv > 122 || conv < 0)
    {
        write("You must select a public title number from 0-122.\n"); 
        
        return 1;
    }   
    
    VAMPIRES_MAPPINGS->set_vamp_title(this_player()->query_name(), conv);
    
    write("You select public title #"+conv+".\n");
    
    return 1;
}


int
do_vlisttitles()
{ 
    write("VAMPIRES, CUSTOM SELECTABLE SELF-PROCLAIMED TITLES\n");
    write("=================================================\n");
    write("[0]   -  NO TITLE - DEFAULT\n");
    write("[1]   -  Barbaric\n");
    write("[2]   -  Beast\n");
    write("[3]   -  Butcher\n");
    write("[4]   -  Calculating\n");
    write("[5]   -  Cannibal\n");
    write("[6]   -  Cantankerous\n");
    write("[7]   -  Chosen\n");
    write("[8]   -  Coercive\n");
    write("[9]   -  Conquered\n");
    write("[10]   -  Conqueror\n");
    write("[11]   -  Constant\n");
    write("[12]   -  Critical\n");
    write("[13]   -  Curmudgeon\n");
    write("[14]   -  Cursed\n");
    write("[15]   -  Dandy\n");
    write("[16]   -  Defiler\n");
    write("[17]   -  Demanding\n");
    write("[18]   -  Demolisher\n");
    write("[19]   -  Old\n");
    write("[20]   -  Destitute\n");
    write("[21]   -  Destroyer\n");
    write("[22]   -  Disturbed\n");
    write("[23]   -  Ecstatic\n");
    write("[24]   -  Eldest\n");
    write("[25]   -  Entrapper\n");
    write("[26]   -  Erratic\n");
    write("[27]   -  Exterminator\n");
    write("[28]   -  Feared\n");
    write("[29]   -  Forceful\n");
    write("[30]   -  Frantic\n");
    write("[31]   -  Heartless\n");
    write("[32]   -  Horrendous\n");
    write("[33]   -  Horrible\n");
    write("[34]   -  Indomitable\n");
    write("[35]   -  Insatiable\n");
    write("[36]   -  Insinuator\n");
    write("[37]   -  Intruder\n");
    write("[38]   -  Impaler\n");
    write("[39]   -  Liquidator\n");
    write("[40]   -  Little\n");
    write("[41]   -  Malicious\n");
    write("[42]   -  Manipulator\n");
    write("[43]   -  Mauler\n");
    write("[44]   -  Meek\n");
    write("[45]   -  Meticulous\n");
    write("[46]   -  Mild\n");
    write("[47]   -  Nameless\n");
    write("[48]   -  Nemesis\n");
    write("[49]   -  Obliterator\n");
    write("[50]   -  Obstructer\n");
    write("[51]   -  Obtuse\n");
    write("[52]   -  Oppressor\n");
    write("[53]   -  Parched\n");
    write("[54]   -  Plague\n");
    write("[55]   -  Quarrelsome\n");
    write("[56]   -  Ravenous\n");
    write("[57]   -  Reaper\n");
    write("[58]   -  Rectifier\n");
    write("[59]   -  Relentless\n");
    write("[60]   -  Repressor\n");
    write("[61]   -  Repulsive\n");
    write("[62]   -  Ruiner\n");
    write("[63]   -  Ruthless\n");
    write("[64]   -  Scoundrel\n");
    write("[65]   -  Scourge\n");
    write("[66]   -  Seditious\n");
    write("[67]   -  Sedulous\n");
    write("[68]   -  Slasher\n");
    write("[69]   -  Sot\n");
    write("[70]   -  Spectacular\n");
    write("[71]   -  Subjugator\n");
    write("[72]   -  Temptress\n");
    write("[73]   -  Terrible\n");
    write("[74]   -  Tireless\n");
    write("[75]   -  Tortured\n");
    write("[76]   -  Torturer\n");
    write("[77]   -  Tremendous\n");
    write("[78]   -  Tyrant\n");
    write("[79]   -  Ubiquitous\n");
    write("[80]   -  Uncrowned\n");
    write("[81]   -  Unexpected\n");
    write("[82]   -  Unseen\n");
    write("[83]   -  Vanquisher\n");
    write("[84]   -  Vengeful\n");
    write("[85]   -  Voracious\n");                          
    write("[86]   -  Pale Knight\n");
    write("[87]   -  Feral Knight\n");
    write("[88]   -  Beautiful\n");
    write("[89]   -  Betrayer\n");
    write("[90]   -  Claw\n");
    write("[91]   -  Debonair\n");
    write("[92]   -  Decadent\n");
    write("[93]   -  Exiled\n");
    write("[94]   -  Ghastly\n");
    write("[95]   -  Grim\n");
    write("[96]   -  Grip\n");
    write("[97]   -  Hellspawn\n");
    write("[98]   -  Hunter\n");
    write("[99]   -  Just\n");
    write("[100]   -  Languisher\n");
    write("[101]   -  Lazy\n");
    write("[102]   -  Mesmerizing\n");
    write("[103]   -  Outlaw\n");
    write("[104]   -  Ravisher\n");
    write("[105]   -  Ravishing\n");                           
    write("[106]   -  Silver-tongue\n");
    write("[107]   -  Treacherous\n");
    write("[108]   -  Twisted\n");
    write("[109]   -  Vile\n");
    write("[110]   -  Blood Prince|ess\n");
    write("[111]   -  Prince|ess of Crypts\n");
    write("[112]   -  Prince|ess of Eternal Night\n");
    write("[113]   -  Pale Duke|Duchess\n");
    write("[114]   -  Duke|Duchess of Darkness\n");
    write("[115]   -  Count|ess of Shadows\n");
    write("[116]   -  Sanguinary Count|ess\n");
    write("[117]   -  Gloomy Baron|ess\n");
    write("[118]   -  Villainous Baron|ess\n");
    write("[119]   -  Decadent Baron|ess\n");
    write("[120]   -  Dreadlord|lady\n");
    write("[121]   -  Seducer|Seductress\n");
    write("[122]   -  Cherished Son|Daughter of the Night\n");    
    write("\n");
    write("      -  Custom titles will be preemted with 'the'.\n");
                   
        
    return 1;
}


int
do_vnation()
{ 
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) > 0)
    {          
        write("|===========================================================|\n");
        write("|               V A M P I R E   N A T I O N                 |\n");   
        write("|-----------------------------------------------------------|\n");
        write("| The Vampire Nation -  The world are populated by many     |\n"); 
        write("| vampires and covens that all obey somecommon norms and    |\n"); 
        write("| unwritten rules for common survival of the vampire kin.   |\n"); 
        write("|                                                           |\n"); 
        write("| While vampires of different factions and covens may be in |\n");
        write("| direct conflicts and even all out war, there are some     |\n");
        write("| lines that never shall be crossed, lest one dares to      |\n");
        write("| tempt the fate of the Sun. Elder vampires and above are   |\n");
        write("| keeping track on who is who, their standings and merits,  |\n");
        write("| and to act as the enforcers of the Vampire nation. Good   |\n");
        write("| standing with the Vampire Nation is beneficial.           |\n");
        write("|                                                           |\n"); 
        write("| This page displays relevant information for vampires of   |\n"); 
        write("| significant stature.                                      |\n"); 
                
        if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= TIER3_1_MIN_REQ_AGE)
        {               
            if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= TIER3_1_MIN_REQ_REP)
            {
                write("|                                                           |\n"); 
                write("|         VAMPIRES / PERSONS / PLACES OF INTEREST           |\n"); 
                write("|-----------------------------------------------------------|\n");
                write("| People or places that wants something from you will be    |\n");  
                write("| displayed below.                                          |\n"); 
                write("|                                                           |\n");

                if (!present("path1_cooldown_obj", this_player()))
                {                    
                    if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) < 100)
                    {
                        if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_1_AGENT_NR)
                        { 
                            write("|  *On the behalf of the Vampire Nation, a Vampire          |\n"); 
                            write("|   in Faerun is seeking your attention.                    |\n");
                            write("|                                                           |\n");  
                        }

                        if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_2_AGENT_NR)
                        { 
                            write("|  *On the behalf of the Vampire Nation, a Vampire          |\n"); 
                            write("|   in Gondor is seeking your attention.                    |\n");
                            write("|                                                           |\n");  
                        }

                        if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_3_AGENT_NR)
                        { 
                            write("|  *On the behalf of the Vampire Nation, a Vampire          |\n"); 
                            write("|   in Raumdor is seeking your attention.                   |\n");
                            write("|                                                           |\n");    
                        }

                        if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_4_AGENT_NR)
                        { 
                            write("|  *On the behalf of the Vampire Nation, a Vampire          |\n"); 
                            write("|   in Krynn is seeking your attention.                     |\n");
                            write("|                                                           |\n");    
                        }  

                        if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_5_AGENT_NR)
                        { 
                            write("|  *On the behalf of the Vampire Nation, a Vampire          |\n"); 
                            write("|   in Calia is seeking your attention.                     |\n");
                            write("|                                                           |\n");    
                        }  

                        if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_6_AGENT_NR)
                        { 
                            write("|  *On the behalf of the Vampire Nation, a Vampire          |\n"); 
                            write("|   in Shire is seeking your attention.                     |\n");
                            write("|                                                           |\n");    
                        }

                        if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_7_AGENT_NR)
                        { 
                            write("|  *On the behalf of the Vampire Nation, a Vampire          |\n"); 
                            write("|   in Avenir is seeking your attention.                    |\n");
                            write("|                                                           |\n");    
                        }  

                        if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_8_AGENT_NR)
                        { 
                            write("|  *On the behalf of the Vampire Nation, a Vampire          |\n"); 
                            write("|   in Emerald is seeking your attention.                   |\n");
                            write("|                                                           |\n");    
                        }  

                        if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_9_AGENT_NR)
                        { 
                            write("|  *On the behalf of the Vampire Nation, a Vampire          |\n"); 
                            write("|   in Kalad is seeking your attention.                     |\n");
                            write("|                                                           |\n");    
                        }  

                        if (VAMPIRES_MAPPINGS->query_vamp_agent(this_player()->query_name()) == TIER3_10_AGENT_NR)
                        { 
                            write("|  *On the behalf of the Vampire Nation, a Vampire          |\n"); 
                            write("|   in Cirath is seeking your attention.                    |\n");
                            write("|                                                           |\n");    
                        }
                    }
                }

                write("| COMMANDS:                                                 |\n"); 
                write("| vnationstanding    : Displays your current standing with  |\n"); 
                write("|                      the Vampire Nation. Good standing    |\n");  
                write("|                      with the Vampire nation is a direct  |\n");
                write("|                      requirement for advancing to higher  |\n");
                write("|                      ranks of the Vampires.               |\n");
                write("|                                                           |\n");
                write("|                      *Higher ranked vampires may have some|\n");
                write("|                       influence in how the Progenitor is  |\n");
                write("|                       chosen.                             |\n");
                write("|                                                           |\n");                
            }   
        }                    
        
        write("|-----------------------------------------------------------|\n"); 
        write("| Information about wanted targets, dead or alive, are      |\n");
        write("| listed below. Sometimes, mere mortals dare to tempt fate  |\n");
        write("| that is deemed intolerable by the Elder vampires, and     |\n");
        write("| in rare circumstances, some vampires are targeted for     |\n");
        write("| crimes against the vampire kin.                           |\n");
        write("|                                                           |\n");  
        write("| Vampires that actively hunt down and deal with these      |\n"); 
        write("| individuals will rise in reputation among Vampires. The   |\n"); 
        write("| rise in reputation may trigger further contact with agents|\n"); 
        write("| of the Vampire Nation if the age of the vampire is of     |\n");
        write("| significant stature.                                      |\n");
        write("|                                                           |\n"); 
        write("| COMMANDS:                                                 |\n"); 
        write("| vreputation        : Displays your current reputation and |\n"); 
        write("|                      respect among the Vampire kin.       |\n"); 
        write("|                                                           |\n"); 
        write("| vtargets           : Hunted mortals and vampires.         |\n");
        write("|-----------------------------------------------------------|\n");

        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(this_player()->query_name()) > 0)        
        {
            write("|                                                           |\n");
            write("|                        HIGHER RANKS                       |\n");
            write("|                                                           |\n");
            write("| The rank 'Vampire Lord' is the highest a vampire can      |\n");
            write("| reach, if the minimum reputation and standing vs the      |\n");
            write("| Vampire Nation are met. However, Elders and above are     |\n");
            write("| handled differently.                                      |\n");
            write("|                                                           |\n");
            write("| The available positions for each of the higher ranks are  |\n");
            write("| as follow:                                                |\n");
            write("|                                                           |\n");
            write("| Progenitor      - 1                                       |\n");
            write("| Antediluvian    - 2                                       |\n");
            write("| Methuselah      - 3                                       |\n");
            write("| Elder           - 4                                       |\n");
            write("|                                                           |\n");
            write("| For each of these ranks, there are aging requirements,    |\n");
            write("| reputation requirements and standing requirements. It is  |\n");
            write("| important to know that a Vampire that does not meet       |\n");
            write("| the reputation and standing requirements for a certain    |\n");
            write("| rank, will stop aging. Example: A Vampire Lord that       |\n");
            write("| fails to meet the minimum (hidden) requirements for the   |\n");
            write("| rank of Elder, will stop aging, lingering perpetually     |\n");
            write("| at the edge of what defines the minimum age of the Elder. |\n");
            write("|                                                           |\n");
            write("| Also, even if the vampire fully qualifies and age beyond, |\n");
            write("| doesn't mean the rank is automatically earned.            |\n");
            write("|                                                           |\n");
            write("| Current known ways to earn the higher ranks:              |\n");
            write("|                                                           |\n");
            write("| - Killing a higher ranked vampire. Example: A Vampire     |\n");
            write("|   Lord that successfully kills an Elder will be elevated  |\n");
            write("|   to Elder-rank (if qualifications are met), and the Elder|\n");
            write("|   who was defeated demoted back to Vampire Lord.          |\n");
            write("|   An important premise here is that the swapping of ranks |\n");
            write("|   can only happen with ranks adjacent to eachother. An    |\n");
            write("|   Elder killing an Antediluvian will not trigger rank     |\n");
            write("|   movement.                                               |\n");
            write("|                                                           |\n");
            write("| - Anomalities. Vampires that qualify may be elevated      |\n");
            write("|   1 rank upwards, provided there are open spots. If       |\n");
            write("|   all spots are taken, this will not happen.              |\n");
            write("|                                                           |\n");
            write("| - More information comming soon.                          |\n");
            write("|                                                           |\n");
            write("|___________________________________________________________|\n");
        }
                
        if (VAMPIRES_MASTER->is_vamp_elder(this_player()->query_real_name()) == 1)
        {
            write("|                                                           |\n"); 
            write("|                                                           |\n"); 
            write("|           E L D E R   V A M P I R E ,   R O L E           |\n");
            write("|           ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~           |\n"); 
            write("|                                                           |\n"); 
            write("| Above the Vampire Lords, but below the Methuselah         |\n");
            write("| Vampires in the hiearchy, your role is to guide and       |\n");
            write("| aid vampires of lesser stature, especially in the interest|\n");
            write("| of the Vampire Nation as a whole. Expect lesser vampires  |\n");
            write("| to beg for guidance, survival and direction.              |\n"); 
            write("|                                                           |\n");
            write("|___________________________________________________________|\n");
        }
        
        if (VAMPIRES_MASTER->is_vamp_methuselah(this_player()->query_real_name()) == 1)
        {
            write("|                                                           |\n"); 
            write("|                                                           |\n"); 
            write("|       M E T H U S E L A   V A M P I R E ,   R O L E       |\n");
            write("|       ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~       |\n"); 
            write("|                                                           |\n"); 
            write("|                                                           |\n"); 
            write("|                                                           |\n");
            write("|___________________________________________________________|\n");
        }
        
        if (VAMPIRES_MASTER->is_vamp_antediluvian(this_player()->query_real_name()) == 1)
        {
            write("|                                                           |\n"); 
            write("|                                                           |\n"); 
            write("|   A N T E D I L V U V I A N   V A M P I R E ,   R O L E   |\n");
            write("|   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~   |\n"); 
            write("|                                                           |\n"); 
            write("|                                                           |\n"); 
            write("|                                                           |\n");
            write("|___________________________________________________________|\n");
        }
        
        if (VAMPIRES_MASTER->is_vamp_progenitor(this_player()->query_real_name()) == 1)
        {
            write("|                                                           |\n"); 
            write("|                                                           |\n"); 
            write("|      P R O G E N I T O R   V A M P I R E ,   R O L E      |\n");
            write("|      ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~      |\n"); 
            write("|                                                           |\n"); 
            write("|                                                           |\n"); 
            write("|                                                           |\n");
            write("|___________________________________________________________|\n");
        }

        
        return 1;
    }

    return 0;
}


int
do_vnationstanding()
{ 
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) >= TIER3_1_MIN_REQ_AGE)
    {               
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= TIER3_1_MIN_REQ_REP)
        {
            write("---------------------VAMPIRE NATION, STANDING-----------------------\n");
            write("Your standing with the Vampire Nation is excellent.\n");
            write("Your standing with the Vampire Nation is very good.\n");
            write("Your standing with the Vampire Nation is good.\n");
            write("Your standing with the Vampire Nation is average.\n");
            write("Your standing with the Vampire Nation is mediocre.\n");
            write("Your standing with the Vampire Nation is poor.\n");  
            write("Your standing with the Vampire Nation is very poor.\n"); 
            write("Your standing with the Vampire Nation is barely noticeable.\n");
            write("Your standing with the Vampire Nation is neglible.\n");
            write("\n");
            write("\n");
            write("Your current standing with the Vampire Nation is:\n");
            write("---------------------------------------------------------------------\n");
                        
            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 100)
            {
                write("Your standing with the Vampire Nation is excellent.\n");

                return 1;            
            }

            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 80)
            {
                write("Your standing with the Vampire Nation is very good.\n");

                return 1;            
            }

            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 60)
            {
                write("Your standing with the Vampire Nation is good.\n");

                return 1;            
            }                  

            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 40)
            {
                write("Your standing with the Vampire Nation is average.\n");

                return 1;            
            }

            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 20)
            {
                write("Your standing with the Vampire Nation is mediocre.\n");

                return 1;            
            }

            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 10)
            {
                write("Your standing with the Vampire Nation is poor.\n");

                return 1;            
            }                 

            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 5)
            {
                write("Your standing with the Vampire Nation is very poor.\n");

                return 1;            
            }                 

            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) >= 1)
            {
                write("Your standing with the Vampire Nation is barely noticeable.\n");

                return 1;            
            }                    
                   
            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) == 0)
            {
                write("Your standing with the Vampire Nation is neglible.\n");

                return 1;            
            }  
        }

    }
    
    //write("Your current standing with the Vampire Nation is neglible.\n");

    return 0;
}


int
do_vreputation()
{ 
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) > 0)
    {
        write("---------------------VAMPIRE REPUTATION, RANKS-----------------------\n");
        write("You are seen as an extraordinary being to all creatures of the night.\n");
        write("Your position under the night sky is enviable.\n");
        write("Whisperings about you amid the shadows are nothing short of exemplary.\n");
        write("You are widely known to all Vampire kind.\n");
        write("You are recognizable to most of your kind.\n");
        write("Your reputation among your kind remains relatively unblemished.\n");  
        write("You are becoming known to many of your Vampire kin.\n"); 
        write("Others are beginning to take note of your increasing renown.\n");
        write("You have begun to build a scientific reputation among your kin.\n");
        write("You are virtually unknown to most of your Vampire kin.\n");
        write("You are virtually unknown to almost all of your Vampire kin.\n");   
        write("Your reputation as a Vampire is neglible.\n"); 
        write("\n");
        write("\n");
        write("Your current rank in reputation is:\n");
        write("---------------------------------------------------------------------\n");
              
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= 100)
        {
            write("You are seen as an extraordinary being to all creatures of the night.\n");

            return 1;            
        }

        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= 80)
        {
            write("Your position under the night sky is enviable.\n");

            return 1;            
        }

        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= 70)
        {
            write("Whisperings about you amid the shadows are nothing short of exemplary.\n");

            return 1;            
        }                  

        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= 60)
        {
            write("You are widely known to all Vampire kind.\n");

            return 1;            
        }

        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= 50)
        {
            write("You are recognizable to most of your kind.\n");

            return 1;            
        }

        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= 40)
        {
            write("Your reputation among your kind remains relatively unblemished.\n");

            return 1;            
        }                 

        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= 30)
        {
            write("You are becoming known to many of your Vampire kin.\n");

            return 1;            
        }                 

        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= 20)
        {
            write("Others are beginning to take note of your increasing renown.\n");

            return 1;            
        }                 

        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= 10)
        {
            write("You have begun to build a scientific reputation among your kin.\n");

            return 1;            
        }                 

        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= 5)
        {
            write("You are virtually unknown to most of your Vampire kin.\n");

            return 1;            
        }  

        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) >= 1)
        {
            write("You are virtually unknown to almost all of your Vampire kin.\n");

            return 1;            
        }                    
               
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) == 0)
        {
            write("Your reputation as a Vampire is neglible.\n");

            return 1;            
        }  
    }

    return 0;
}        
        

int
do_vtargets()
{
    int okflag = 0;
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) > 0)
    {
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) <= 10 
        && VAMPIRES_OBJHANDLER->nationtarget_active() == 1)
        {
            okflag = 1;
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) > 10
        && VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) <= 25       
        && VAMPIRES_OBJHANDLER->nationtarget_active() == 2)
        {
            okflag = 1;
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) > 25
        && VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) <= 40       
        && VAMPIRES_OBJHANDLER->nationtarget_active() == 3)
        {
            okflag = 1;
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) > 40
        && VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) <= 70       
        && VAMPIRES_OBJHANDLER->nationtarget_active() == 4)
        {
            okflag = 1;
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) > 70
        && VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) <= 100       
        && VAMPIRES_OBJHANDLER->nationtarget_active() == 5)
        {
            okflag = 1;
        }
                
        if (okflag == 1)
        {
            int identi = VAMPIRES_OBJHANDLER->query_targetnation_location_identifier();
            
            switch(identi)
            {
                case 0:
                write("You sense that there is a wanted man "
                +"somewhere in the lands of Middle Earth. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 1:
                write("You sense that there is a wanted man "
                +"somewhere in the lands of Raumdor. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 2:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Avenir. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 3:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Kalad. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 4:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Calia. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;

                case 5:
                write("You sense that there is a wanted man "
                +"somewhere in the lands of Faerun. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 6:
                write("You sense that there is a wanted man "
                +"somewhere in the lands of Faerun. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 7:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Faerun. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 8:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Sparkle. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 9:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Sparkle. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;  
                
                
                case 10:
                write("You sense that there is a wanted man "
                +"somewhere in the lands of Sparkle. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 11:
                write("You sense that there is a wanted man "
                +"somewhere in the lands of Sparkle. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 12:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Raumdor. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 13:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Raumdor. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 14:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Shire. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;

                case 15:
                write("You sense that there is a wanted man "
                +"somewhere in the lands of Calia. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 16:
                write("You sense that there is a wanted man "
                +"somewhere in the lands of Avenir. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 17:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Ansalon. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 18:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Ansalon. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 19:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Shire. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;  

                
                case 20:
                write("You sense that there is a wanted man "
                +"somewhere in the lands of Shire. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 21:
                write("You sense that there is a wanted man "
                +"somewhere in the lands of Kalad. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 22:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Kalad. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 23:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Shire. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 24:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Gondor. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;

                case 25:
                write("You sense that there is a wanted man "
                +"somewhere in the lands of Shire. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 26:
                write("You sense that there is a wanted man "
                +"somewhere in the lands of Gondor. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
                
                case 27:
                write("You sense that there is a wanted "
                +"man somewhere in the lands of Gondor. He is "
                +"fleeing from our kin, seeking refuge or safe "
                +"harbor and must be killed as soon as "
                +"possible.\n");
                break;
            }
            
            okflag = 0;

            return 1;            
            
        }
        
        okflag = 0;
        
        write("Currently, there are no known targets present in the realms for you.\n");
        
        return 1;
    }
    
    okflag = 0;
    
    return 0;
}
