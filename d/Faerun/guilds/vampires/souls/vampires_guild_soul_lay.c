/* /d/Faerun/guilds/vampires/souls/vampires_guild_soul_lay.c
*
*  Vampire Spawm Guild soul.
*
*  Nerull, 2020
*
*/
#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";
inherit "/d/Faerun/guilds/vampires/souls/emotes";

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

#define THRALL_ACTIVE          "_thrall_active"
#define LIVE_O_OFFERED_THRALL  "_live_o_offered_thrall"

#define CLING_COOLDOWN         "_cling_cooldown"

int do_stop(string arg);
int stop_cling(object who);

object wield_par;

public int query_cmd_soul() { return 1; }
public string get_soul_id() { return "Vampire Spawn"; }


public mapping
query_ability_map()
{

    return ([
            "bloodletter":VAMPIRES_GUILD_DIR + "specials/bloodletter",
            "trucidate":VAMPIRES_GUILD_DIR + "specials/trucidate",
            "execute":VAMPIRES_GUILD_DIR + "specials/execute",
            "vmeld":VAMPIRES_GUILD_DIR + "specials/meld",
            "fly"    : VAMPIRES_GUILD_DIR + "specials/vampfly",
            "ethereal"    : VAMPIRES_GUILD_DIR + "specials/ethereal",
            "strangulate"    : VAMPIRES_GUILD_DIR + "specials/strangulate",
            "mesmerize"    : VAMPIRES_GUILD_DIR + "specials/mesmerize",
            ]);
}


public mapping
query_cmdlist()
{
    return ([
        // commands
        "vhelp"             : "s_vamphelp",
        "vthirst"           : "do_vampthirst",
        "vtitle"            : "do_vamptitle",
        "vtitlelist"        : "do_vamptitlelist",
        "evolve"            : "do_ascend_to_full_vampire",
        "vmorning"          : "do_detect_dawn",
        "vimmortality"      : "do_vampimmortality_occ",
        "vsense"            : "sense",
        "vsire"             : "do_vampsire",        
        "vthrall"           : "do_vampthrall",
        "immpointabolish"  : "do_immpointabolish",
        "vthralloffer"      : "do_vampthrall_offer",
        "vthrallremove"     : "do_vampthrall_remove",   
        "vthrallscry"       : "do_vampthrall_activate",
        //"vthrallsay"        : "do_thrallsay",
        "vthrallassess"     : "do_thrallassess",
        "vthrallcurse"      : "do_thrallcurse",   
        "vchildscry"        : "do_vampchild_activate",        
        "vselect"           : "choose_weaponskill",     
        "vsniff"            : "sniff",
        "vdrink"            : "drink",
        "stop"              : "do_stop",
        "vturntarget"       : "do_vamp_turn_occ",
        "vcling"            : "do_cling",  
        "cling"             : "do_cling",          
        "vunlock"           : "do_tierunlock", 
        "vrespecweapon"     : "respec_weaponskill",
        //"vunmask"           : "do_unmask",
        "vagecheck"         : "do_vagecheck",  
        "vprogression"      : "do_spawntimer",    
      
                
        // Command restrictions during Ethereal phase
        "sell"            : "do_block_commands",
        "cast"            : "do_block_commands",
        "buy"             : "do_block_commands",
        "wax"             : "do_block_commands",
        "sharpen"         : "do_block_commands",
        "drop"            : "do_block_commands",
        "get"             : "do_block_commands",
        "place"           : "do_block_commands",
        "steal"           : "do_block_commands",
        "pick"            : "do_block_commands",
        "order"           : "do_block_commands",
        "give"            : "do_block_commands",
        "put"             : "do_block_commands",
        "repair"          : "do_block_commands",
        "fix"             : "do_block_commands",
        "pray"            : "do_block_commands",
        "enter"           : "do_block_commands",
        "kill"            : "do_block_commands",
        "enter"           : "do_block_commands",
        "trucidate"       : "do_block_commands",
        "bloodletter"     : "do_block_commands",
        "execute"         : "do_block_commands",
        "order"           : "do_block_commands",
                       
        // Specials and Abilties
        "bloodletter"       : "do_ability",
        "trucidate"         : "do_ability",
        "execute"           : "do_ability", 
        "vmeld"             : "do_ability",        
        "fly"               : "do_ability",   
        "ethereal"          : "do_ability",
        "mesmerize"         : "do_ability",
        "strangulate"       : "do_ability",

        // Emotes        
        "burp"              : "burp",
        "fart"              : "fart",
        "valign"            : "valign",
        "vbeam"             : "vbeam",
        "vblink"            : "vblink",
        "vblood"            : "vblood",
        "vbow"              : "vbow",
        "vbreathe"          : "vbreathe",
        "vbrush"            : "vbrush",
        "vburn"             : "vburn",
        "vcaress"           : "vcaress",       
        "vchuckle"          : "vchuckle",
        "vclench"           : "vclench",          
        "vclose"            : "vclose",       
        "vconsider"         : "vconsider",
        "vcurtsey"          : "vcurtsey",      
        "vdance"            : "vdance",  
        "vdismiss"          : "vdismiss",
        "vdistant"          : "vdistant",       
        "vecstasy"          : "vecstasy",      
        "ventrance"         : "ventrance",
        "vfang"             : "vfang",       
        "vfrown"            : "vfrown",
        "vgaze"             : "vgaze",
        "vglance"           : "vglance",
        "vglare"            : "vglare",
        "vglower"           : "vglower",
        "vgrin"             : "vgrin",
        "vgust"             : "vgust",
        "vhiss"             : "vhiss",
        "vhug"              : "vhug",
        "videa"             : "videa",       
        "vkiss"             : "vkiss",
        "vlaugh"            : "vlaugh",
        "vleave"            : "vleave",
        "vlick"             : "vlick",
        "vlong"             : "vlong",
        "vlook"             : "vlook",        
        "vmelancholy"       : "vmelancholy",        
        "vnarrow"           : "vnarrow",
        "vnod"              : "vnod",        
        "voptions"          : "voptions",
        "vpast"             : "vpast",
        "vpensive"          : "vpensive",
        "vpierce"           : "vpierce",
        "vpity"             : "vpity",
        "vpower"            : "vpower",
        "vrecall"           : "vrecall",       
        "vrevel"            : "vrevel",
        "vrevere"           : "vrevere",
        "vrise"             : "vrise",
        "vroar"             : "vroar",
        "vsadness"          : "vsadness",       
        "vscratch"          : "vscratch",
        "vscream"           : "vscream",       
        "vshadow"           : "vshadow",
        "vshine"            : "vshine",
        "vsmile"            : "vsmile",
        "vsmirk"            : "vsmirk",
        "vsweat"            : "vsweat",
        "vtaste"            : "vtaste",
        "vtear"             : "vtear",        
        "vthoughtful"       : "vthoughtful",
        "vtouched"          : "vtouched",       
        "vthroat"           : "vthroat",       
        "vtrace"            : "vtrace",
        "vturn"             : "vturn",      
        "vyawn"             : "vyawn",
        ]);
}


int
s_vamphelp(string str)
{ 
    if (str == "commands")
    {
        write("");     
                
        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
        {
            write("|===========================================================|\n");
            write("|           V A M P I R E S ,   C O M M A N D S             |\n");
        }
        else
        {
            write("|===========================================================|\n");
            write("|      V A M P I R E   S P A W N S ,   C O M M A N D S      |\n");
        }

        write("|-----------------------------------------------------------|\n");
        write("| vthirst          : Understand your level of thirst.       |\n");
        write("|                                                           |\n");
        write("| vmorning         : Detect the cycle of the daystar of     |\n");
        write("|                    your current landscape.                |\n");
        write("|                                                           |\n");
        write("| vtitle           : Displays your current title.           |\n");
        write("|                                                           |\n");       
        write("| vtitlelist       : List all vampire titles and ranks.     |\n");
        write("|                                                           |\n");
        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
        {        
            write("| vsetcustomtitle  : Select a custom title from the list.   |\n");
            write("|                                                           |\n");   
            write("| vcustomtitle     : Shows your current custom title.       |\n");
            write("|                                                           |\n");   
            write("| vlistcustomtitles: Lists the available custom titles.     |\n");
        }
        write("|                                                           |\n");       
        write("| vsire            : Reveals the name of your creator.      |\n");
        write("|                                                           |\n");
        write("| vagecheck        : Reveals if your thirst is saturated    |\n");
        write("|                    enough for development through aging.  |\n");
        write("|                                                           |\n");
        
        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
        {
            write("| vprogression     : Assess the level of satisfaction of    |\n");
            write("|                    your sire in regards to your activity  |\n");
            write("|                    and age progression.                   |\n");
            write("|                    *Only for Vampire Spawns.              |\n");
            write("|                                                           |\n");
        }
        
        int vampgauge = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name());
   
        if (vampgauge >= 150)
        {    
            write("| vmeld            : Escape the harshness of the world      |\n");
            write("|                    into the cold ground. Rise to ascend   |\n");  
            write("|                    anew.                                  |\n");  
            write("|                                                           |\n");
        }
               
        if (vampgauge >= 500)
        {
            write("| vsniff           : Search for your quarry with enhanced   |\n");
            write("|                    senses. Enemies stuck by a hit by      |\n");
            write("|                    a combat special will ensure bleeding  |\n");
            write("|                    will occur. The trail of blood left by |\n");
            write("|                    a fleeing victim can be tracked with   |\n");
            write("|                    this ability.                          |\n");
            write("|                                                           |\n");
        }
               
        if (vampgauge >= 1200)
        {    
            write("| vsense           : Listen for the life of the world       |\n");
            write("|                    around you, detecting their heartbeats |\n");  
            write("|                    in adjacent rooms.                     |\n");
            write("|                                                           |\n");
        }

        // Basic OCC package
        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
        {
            write("| vimmortality     : This will reveal the status of your    |\n");
            write("|                    Immortality-points.                    |\n");  
            write("|                                                           |\n");
            write("| vcling           : Mercilessly stalk your prey.           |\n");
            write("|                                                           |\n");
                      
            if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) > 0)
            {
                write("| vdrink           : Request to drink the blood of a        |\n");
                write("|                    sentient person. Note that this is a   |\n");
                write("|                    dangerous position for your victim in  |\n");
                write("|                    that, if you are careless, you could   |\n");
                write("|                    drain their blood completely, killing  |\n");
                write("|                    them. This process will replenish some |\n");
                write("|                    blood and can also be used to create   |\n");
                write("|                    Full Vampires using vturntarget.       |\n");
                write("|                                                           |\n");
                write("|                    The command 'stop drink|drain' will    |\n");
                write("|                    stop the process and release the       |\n");
                write("|                    victim.                                |\n");
                write("|                                                           |\n");
                write("| vturntarget      : Will turn mortal victims drained for   |\n");
                write("|                    for blood with vdrink into new         |\n");
                write("|                    Full Vampires. Toggle ON/OFF flag.     |\n");
                write("|                                                           |\n");
                write("|                    Cost: Two immortality points are       |\n");
                write("|                          required to turn a human into a  |\n");
                write("|                          Full Vampire. The victim must    |\n");
                write("|                          also be free of any racial, lay  |\n");
                write("|                          and occup affiliation at the time|\n");
                write("|                          of the attempt, else regular     |\n");
                write("|                          death will occur.                |\n");
                write("|                                                           |\n");
                write("|                          A human turned this way will     |\n");
                write("|                          start with only 1 point of       |\n");
                write("|                          immortality.                     |\n");
            }
                        
            write("|                                                           |\n");
            write("| vunlock <tier x> : Fully unlocks a specific tier.         |\n");
            write("|                                                           |\n");
            write("|                    Cost: Two immortality points.          |\n");
            write("|                                                           |\n");
            write("| vrespecweapon    : Nullify the weapon selection. This     |\n");
            write("|                    allows the vampire to select a new     |\n");
            write("|                    weapon specialization at will.         |\n");
            write("|                                                           |\n");
            write("|                    Cost: One immortality point.           |\n");
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                  WEAPON SPECIALIZATION                    |\n"); 
            write("|                  =====================                    |\n"); 
            write("| A Vampire may specialize any bladed weaponstyle.          |\n"); 
            write("|                                                           |\n");
               
            if (VAMPIRES_MAPPINGS->query_weaponskill_selection(this_player()->query_name()) == 0)       
            {
                write("|                                                           |\n");
                write("|        >>> You have no weapon specialization! <<<         |\n");
                write("|        Please 'vselect <sword|axe|knife|polearm>          |\n");
                write("|                                                           |\n");
            }
            
            if (VAMPIRES_MAPPINGS->query_weaponskill_selection(this_player()->query_name()) == 1)       
            {
                write("|                                                           |\n");
                write("| You are specialized in swords.                            |\n");
                write("|                                                           |\n");
            }
            
            if (VAMPIRES_MAPPINGS->query_weaponskill_selection(this_player()->query_name()) == 2)       
            {
                write("|                                                           |\n");
                write("| You are specialized in polearms.                          |\n");
                write("|                                                           |\n");
            }
            
            if (VAMPIRES_MAPPINGS->query_weaponskill_selection(this_player()->query_name()) == 3)       
            {
                write("|                                                           |\n");
                write("| You are specialized in axes.                              |\n");
                write("|                                                           |\n");
            }
            
            if (VAMPIRES_MAPPINGS->query_weaponskill_selection(this_player()->query_name()) == 4)       
            {
                write("|                                                           |\n");
                write("| You are specialized in knives.                            |\n");
                write("|                                                           |\n");
            }
        }

        write("|___________________________________________________________|\n");
        write("|                                                           |\n");
        write("|                     COMBAT SPECIALS                       |\n"); 
        write("|                     ===============                       |\n");
                     
        if (VAMPIRES_MAPPINGS->query_vampire_main_special(this_player()->query_name()) == 1)
        {
            write("|                                                           |\n");
            write("| Bloodletter                                               |\n");
            write("|                                                           |\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_main_special(this_player()->query_name()) == 2)
        {
            write("|                                                           |\n");
            write("| Execute                                                   |\n");
            write("|                                                           |\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_main_special(this_player()->query_name()) == 3)
        {
            write("|                                                           |\n");
            write("| Trucidate                                                 |\n");
            write("|                                                           |\n");
        }


        write("|___________________________________________________________|\n");
        write("|                                                           |\n");
        write("|           G I F T S   O F   T H E   B L O O D             |\n");
        write("|           ===================================             |\n");
        write("|                                                           |\n");
        write("|                        TIER ZERO                          |\n"); 
        write("|                        ---------                          |\n");       
        write("| SPELL                                                     |\n");
        write("| Sanctuary       : This spell will turn you into mist and  |\n");
        write("|                   transport you to your safe location.    |\n");
        write("|                                                           |\n");

        if (vampgauge >= 250)
        {    
            write("| SPELL                                                     |\n");
            write("| Regeneration    : Quickly regenerate damaged tissue.      |\n");
            write("|                                                           |\n");
        }
        
        if (vampgauge >= 900)
        {    
            write("| SPELL                                                     |\n");
            write("| Augumentation   : Transmute the weight of carried items   |\n");
            write("|                   to easen the burden.                    |\n");
            write("|                                                           |\n");
            write("| SPELL                                                     |\n");
            write("| Siphon          : Drain life from a living subject        |\n");
            write("|                   to regenerate your own tissue.          |\n");
            write("|                                                           |\n");
        }
    
    
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) == 1)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                         TIER ONE                          |\n"); 
            write("|                         --------                          |\n"); 
            write("| SPELL                                                     |\n");
            write("| Elusiveness      : Circumvent incoming attacks with feral |\n");
            write("|                    speed and agility.                     |\n");
            write("|                                                           |\n");
        }
        
        //OCC abilities, TIER 1 
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) == 2)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                         TIER ONE                          |\n"); 
            write("|                         --------                          |\n"); 
            write("| SPELL                                                     |\n");
            write("| Resilience       : Your supernatural state makes you      |\n");
            write("|                    more resistant to incoming damage.     |\n");
            write("|                                                           |\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) == 3)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                         TIER ONE                          |\n"); 
            write("|                         --------                          |\n"); 
            write("| SPELL                                                     |\n");
            write("| Resilience       : Your supernatural state makes you      |\n");
            write("|                    more resistant to incoming damage.     |\n");
            write("|                                                           |\n");
            write("| SPELL                                                     |\n");
            write("| Elusiveness      : Circumvent incoming attacks with feral |\n");
            write("|                    speed and agility.                     |\n");
            write("|                                                           |\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) > 0)
        {
            write("|                                                           |\n");
            write("| SPELL                                                     |\n");
            write("| Incognito        : Change your appearance to be someone   |\n");
            write("|                    else.                                  |\n");
            write("|                                                           |\n");
            write("| SPELL                                                     |\n");
            write("| Amplify          : This spell will enhance your strenght. |\n");
            write("|                                                           |\n");
            write("|                                                           |\n");
            write("|               VAMPIRES, CHILDREN AND SIRES                |\n"); 
            write("|               ----------------------------                |\n"); 
            write("|                                                           |\n");
            write("| With the options such as 'vdrink' and 'vturntarget'       |\n"); 
            write("| described above, a Vampire with enough points in          |\n"); 
            write("| Immortality may turn a willing target into a Full vampire.|\n");
            write("| Vampires you have created, in addition to the commands    |\n");
            write("| over them shown below, can never directly destroy your    |\n");
            write("| coffin. Vampires turned by you will start                 |\n");
            write("| with only a single point of Immortality.                  |\n");
            write("|                                                           |\n");
            write("| *Creating a Full Vampire costs 2 points of Immortality.   |\n");
            write("| *Only humans can be turned at this time.                  |\n");
            write("|                                                           |\n");
            write("| You will perpetually keep some advantages over the        |\n");
            write("| vampires you have sired, described below.                 |\n");
            write("|                                                           |\n");
            write("| ABILITY                                                   |\n");           
            write("| vchildscry       : Discreet scrying / monitoring vampires |\n");
            write("|                    you have sired. This is undetectable.  |\n");
            write("|                                                           |\n");
            write("| ABILITY                                                   |\n");
            write("| vchildscryend    : Ends your discreet scrying on your     |\n");
            write("|                    vampire child.                         |\n");
            write("|                                                           |\n");                    
            write("| SPELL:                                                    |\n"); 
            write("| childwhisper    : Whisper an anonymous message into the   |\n");
            write("|                   mind of a vampire you have sired.       |\n");
            write("|                                                           |\n");
            write("|                                                           |\n");
            write("|                                                           |\n");                    
            write("|         VAMPIRE COVENS, FUNCTIONS AND LEADERSHIP          |\n"); 
            write("|         ----------------------------------------          |\n"); 
            write("|                                                           |\n");
            write("| Full vampires may have grown desires to form proper       |\n");
            write("| vampire covens. Very few suitable locations exist in      |\n");
            write("| the realms, and only vampires that has sired atleast one  |\n");
            write("| new vampire can detect these locations.                   |\n");
            write("|                                                           |\n");          
            write("| A coven provides a much better protection for coffins     |\n");
            write("| and add additional functions, supplies and other          |\n");
            write("| facilities suited for its members. Each coven is protected|\n");
            write("| by a creature/warden that will be extremely hard to remove|\n");
            write("| even for a large team.                                    |\n");
            write("|                                                           |\n");          
            write("| Additional functions of a coven and its facilities will   |\n");
            write("| be revealed somewhere inside the coven area.              |\n");           
            write("|                                                           |\n");
            write("| *These commands are only active in the entryway of the    |\n");   
            write("|  coven area.                                              |\n"); 
            write("|                                                           |\n"); 
            write("| *A vampire must be properly saturated in blood to claim   |\n");
            write("|  a coven with no covenmaster.                             |\n");  
            write("|                                                           |\n");
            write("|                     Coven commands                        |\n"); 
            write("|                     --------------                        |\n"); 
            write("| claim coven      : Eligible and vacant spots suited for   |\n");
            write("|                    a vampire coven can be claimed.        |\n");
            write("|                                                           |\n");
            write("| stabilize warden : Deteriorating wardens protecting covens|\n");
            write("|                    can be stabilized for a substantial    |\n");
            write("|                    amount of blood.                       |\n");
            write("|                                                           |\n");
            write("| leave coven      : You leave the coven you are a member   |\n");
            write("|                    of. This means you also abandon        |\n");
            write("|                    leadership of said coven.              |\n");
            write("|                                                           |\n");
            write("| resign as covenmaster: You remain a coven member, but the |\n");
            write("|                        leadership is abandoned.           |\n");
            write("|                                                           |\n"); 
            write("| coventransfer    : Transfer to covenmaster position to    |\n");
            write("|                    a coven member.                        |\n");
            write("|                                                           |\n");           
            write("| add <member>     : Add a full vampire to your coven.      |\n");
            write("| remove <member>  : Remove a full vampire from your coven. |\n");
            write("|                                                           |\n");
            write("| oppose <cm>      : You place your vote of no              |\n");
            write("|                    confidence vs a covenmaster. The vote  |\n");
            write("|                    is anonymous and can't be detected     |\n");
            write("|                    by others. If OVER half of the total   |\n");
            write("|                    members of the coven opposes the       |\n");
            write("|                    covenmaster, the covenmaster will be   |\n");
            write("|                    demoted to regular coven member within |\n"); 
            write("|                    a couple of hours.                     |\n"); 
            write("|                                                           |\n");           
            write("| opposeremove <cm> : Remove your vote of no confidence vs  |\n"); 
            write("|                     a covenmaster.                        |\n"); 
            write("|                                                           |\n");           
            write("| covenmaster       : Display the current covenmaster.      |\n"); 
        }
            
        // OCC abilities, TIER 2 
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 1)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                         TIER TWO                          |\n"); 
            write("|                         --------                          |\n"); 
            write("| ABILITY                                                   |\n");
            write("| Ethereal         : Enter the ethereal realm.  Only other  |\n"); 
            write("|                    vampires in this state can see you,    |\n"); 
            write("|                    save for the deities. In this shadowy  |\n"); 
            write("|                    realm, you will not see any objects    |\n"); 
            write("|                    nor other beings, but you may hear     |\n"); 
            write("|                    them conversing.                       |\n"); 
            write("|                                                           |\n");
            write("|                    To enter the regular realm again,      |\n");
            write("|                    simply 'stop ethereal'.                |\n");
            write("|                                                           |\n");
        }
               
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 2)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                         TIER TWO                          |\n"); 
            write("|                         --------                          |\n"); 
            write("| SPELL                                                     |\n");
            write("| Obfuscate        : Become invisible to the naked eye.     |\n");
            write("|                                                           |\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 3)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                         TIER TWO                          |\n"); 
            write("|                         --------                          |\n"); 
            write("| ABILITY                                                   |\n");
            write("| Ethereal         : Enter the ethereal realm.  Only other  |\n"); 
            write("|                    vampires in this state can see you,    |\n"); 
            write("|                    save for the deities. In this shadowy  |\n"); 
            write("|                    realm, you will not see any objects    |\n"); 
            write("|                    nor other beings, but you may hear     |\n"); 
            write("|                    them conversing.                       |\n"); 
            write("|                                                           |\n");
            write("|                    To enter the regular realm again,      |\n");
            write("|                    simply 'stop ethereal'.                |\n");
            write("|                                                           |\n");
            write("| SPELL                                                     |\n");
            write("| Obfuscate        : Become invisible to the naked eye.     |\n");
            write("|                                                           |\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) > 0)
        {          
            write("|                                                           |\n");
            write("| SPELL                                                     |\n");
            write("| Deadeye          : Amplifies vision to detect invisible   |\n");
            write("|                    creatures.                             |\n"); 
            write("|                                                           |\n");
            write("| VAMPIRE NATION                                            |\n");
            write("| vnation          : General information about important    |\n");
            write("|                    events and orders related to the       |\n");
            write("|                    Vampire kin.                           |\n");
            write("|                                                           |\n");             
            write("| *Stone coffins can now be found.                          |\n");
            write("|                                                           |\n");
            write("|         THRALLS, COMMANDS, SPELLS AND ABILITIES           |\n"); 
            write("|         ---------------------------------------           |\n"); 
            write("|                                                           |\n");
            write("| Vampire familiars, or thralls, are often central agents   |\n");
            write("| of intelligence and offer various services in the world   |\n");
            write("| of the living that may be of great importance of a        |\n");
            write("| vampire. A vampire may at any given time have one thrall  |\n");
            write("| in service.                                               |\n");
            write("|                                                           |\n");           
            write("| vthrall          : Reveals the name of your thrall.       |\n");
            write("|                                                           |\n");
            write("| vthrallassess    : Reveals if your thrall is ready to     |\n");
            write("|                    be drained for 2 immortality points.   |\n");
            write("|                                                           |\n");                 
            write("| vthralloffer     : Offer someone to become your thrall.   |\n");
            write("|                                                           |\n");           
            write("| vthrallremove    : Releases your thrall from your service.|\n");
            write("|                                                           |\n");           
            write("| vthrallscry      : Discreet scrying / monitoring your     |\n");
            write("|                    thrall from a 3rd person perspective.  |\n");
            write("|                                                           |\n");
            write("| vthrallscryend   : Ends your discreet scrying on your     |\n");
            write("|                    thrall.                                |\n");
            write("|                                                           |\n");       
            write("| SPELL:                                                    |\n"); 
            write("| thrallwhisper    : Send a message into the mind if your   |\n");
            write("|                    thrall.                                |\n"); 
            write("|                                                           |\n");              
            write("| vthrallcurse     : Curse your thrall by the trial of      |\n");
            write("|                    Blood.                                 |\n");
            write("|                    Thralls on the trial of Blood will     |\n");
            write("|                    generate 2 points of immortality when  |\n");
            write("|                    the curse expires.                     |\n");
            write("|                    You need to feed on them to collect    |\n");
            write("|                    the points when they are ripe.         |\n");
            write("|                                                           |\n");
            write("|                    While a player can remain as a thrall  |\n"); 
            write("|                    indefinitely, each player can only     |\n");
            write("|                    generate 2 points of immortality, ever.|\n");            
            write("|                                                           |\n");
        }
                     
        // OCC abilities, TIER 3 
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(this_player()->query_name()) == 1)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                        TIER THREE                         |\n"); 
            write("|                        ----------                         |\n"); 
            write("|                                                           |\n");
            write("| SPELL                                                     |\n");
            write("| Lifeward         : Necrotic energy that protect against   |\n");
            write("|                    life magic.                            |\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(this_player()->query_name()) == 2)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                        TIER THREE                         |\n"); 
            write("|                        ----------                         |\n"); 
            write("|                                                           |\n");
            write("| ABILITY                                                   |\n");
            write("| Strangulate      : Boil the blood in the lungs of the     |\n");
            write("|                    victim. Effect : Silence.              |\n");
            write("|                                                           |\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(this_player()->query_name()) == 3)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                        TIER THREE                         |\n"); 
            write("|                        ----------                         |\n"); 
            write("|                                                           |\n");
            write("| ABILITY                                                   |\n");
            write("| Strangulate      : Boil the blood in the lungs of the     |\n");
            write("|                    victim. Effect : Silence.              |\n");
            write("|                                                           |\n");
            write("| SPELL                                                     |\n");
            write("| Lifeward         : Necrotic energy that protect against   |\n");
            write("|                    life magic.                            |\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(this_player()->query_name()) > 0)
        {
            write("|                                                           |\n");
            write("| SPELL                                                     |\n");
            write("| Celerity         : Increases the speed of the vampire.    |\n");
            write("|                                                           |\n");            
            write("|                                                           |\n");
            //write("| SPELL                                                     |\n");
            //write("| Infusion         : Restore fatigue.                       |\n");
            write("|                                                           |\n");
        }



        // OCC abilities, TIER 4 
        /*if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(this_player()->query_name()) == 1)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                        TIER FOUR                          |\n"); 
            write("|                        ---------                          |\n");  
            write("|                                                           |\n");  
            write("| ABILITY                                                   |\n");
            write("| Fly              : Spend time to fly to various preset    |\n");
            write("|                    locations.                             |\n");
            write("|                                                           |\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(this_player()->query_name()) == 2)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                        TIER FOUR                          |\n"); 
            write("|                        ---------                          |\n");  
            write("|                                                           |\n");  
            write("| SPELL                                                     |\n");
            write("| Swarm             : Send a swarm of bats towards a team   |\n");
            write("|                     of enemies, injuring them.            |\n");
            write("|                                                           |\n");
        }*/
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(this_player()->query_name()) > 0)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                        TIER FOUR                          |\n"); 
            write("|                        ---------                          |\n");  
            write("|                                                           |\n");  
            write("| SPELL                                                     |\n");
            write("| Swarm             : Send a swarm of bats towards a team   |\n");
            write("|                     of enemies, injuring them.            |\n");
            write("|                                                           |\n");
            write("| ABILITY                                                   |\n");
            write("| Fly              : Spend time to fly to various preset    |\n");
            write("|                    locations.                             |\n");
            write("|                                                           |\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(this_player()->query_name()) > 0)
        {
            write("| ABILITY                                                   |\n");
            write("| Mesmerize         : Mesmerize a target so it will not     |\n");
            write("|                     perform specials or cast spells for a |\n");
            write("|                     period of time.                       |\n");
            write("|                                                           |\n");
            write("| *Steel coffins can now be found.                          |\n");            
        }
        
  
                  
        // OCC abilities, TIER 7
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_7(this_player()->query_name()) > 0)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|                        TIER FIVE                          |\n"); 
            write("|                        ----------                         |\n"); 
            write("| WARD                                                      |\n"); 
            write("| Sigil             : Place a powerful protecting ward on   |\n"); 
            write("|                     your coffin, which will trigger if    |\n");
            write("|                     someone is trying to destroy the      |\n");
            write("|                     coffin by any means. The ward will be |\n");
            write("|                     dispelled during the attempt, and     |\n");
            write("|                     the perpetrator will be slain by the  |\n");
            write("|                     energies by the ward if he is of      |\n");
            write("|                     similar or larget stature than you.   |\n");
            write("|                     Else, the ward will simply deflect    |\n");
            write("|                     any attempt to destroy the coffin.    |\n");    
            write("|                                                           |\n");
            write("|  Command: 'ward coffin' (that you own).                   |\n");
            write("|                                                           |\n");
        }
        
        

        // OCC abilities, TIER 6, for Progenitor Vampire only
        if (VAMPIRES_MASTER->is_vamp_progenitor(this_player()->query_name()) == 1)
        {
            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("|               TIER SIX, PROGENITOR ABILITES               |\n"); 
            write("|               -----------------------------               |\n"); 
            write("|                                                           |\n");
        }


        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
        {
            if (this_player()->query_average() < REQ_AVG_OCC)
            {
                write("|___________________________________________________________|\n");
                
                return 1;        
            }
            
            if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) < 1450)
            {
                write("|___________________________________________________________|\n");
                
                return 1;        
            }

            write("|___________________________________________________________|\n");
            write("|                                                           |\n");
            write("| Evolve       : You may now 'evolve into a full vampire'.  |\n");
            write("|                                                           |\n");
            write("|                *A full Vampire consumes these additioal   |\n");
            write("|                 slots:                                    |\n");
            write("|                 Occupational slot.                        |\n");
            write("|___________________________________________________________|\n");
            
            return 1;
        }   

        write("|___________________________________________________________|\n");        
            
        return 1;
    }
    
    if (str == "emotes")
    {
        write("");
 
        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
        {
            //write(""
            write("|============================================================|\n");
            write("|              V A M P I R E S ,   E M O T E S               |\n");
        }
        else
        {
            write("|===========================================================|\n");
            write("|       V A M P I R E   S P A W N S ,   E M O T E S         |\n");
        }
        
        write("|-----------------------------------------------------------|\n");
        write("|                                                           |\n");   
        write("| valign      - Align your breaths to the heartbeat of      |\n");
        write("|               your prey.                                  |\n");
        write("| vbeam       - Beam with malicious delight.                |\n");
        write("| vblink      - Blink with feigned surprise.                |\n");
        write("| vblood      - Let a drop of blood spill on the floor.     |\n");
        write("| vbow        - Bow, with charm.                            |\n");
        write("| vbreathe    - Breathe down the neck of your prey.         |\n");
        write("| vbrush      - Brush your fangs against your prey's neck.  |\n");       
        write("| vburn       - Let your eyes burn with energy.             |\n");
        write("| vcaress     - Run your fingernails down someone's neck.   |\n");
        write("| vchuckle    - Chuckle, then sneer.                        |\n");
        write("| vclench     - Clench your fist indicating anger.          |\n");
        write("| vclose      - Move within arms reach of your prey.        |\n");
        write("| vconsider   - Consider your options.                      |\n");        
        write("| vcurtsey    - Curtsey, with grace.                        |\n"); 
        write("| vdance      - Dance.                                      |\n");
        write("| vdismiss    - Dismiss your prey from your sight.          |\n");
        write("| vdistant    - Let your gaze go distant.                   |\n");
        write("| vecstasy    - Feel the ecstasy of your prey's blood.      |\n");
        write("| ventrance   - Turn your entrancing gaze towards your      |\n");
        write("|               prey.                                       |\n");
        write("| vfang       - Show off your fang.                         |\n");
        write("| vfrown      - Show a frown.                               |\n");
        write("| vgaze       - Look about the room for a soul to entice.   |\n");
        write("| vglance     - Glance at the accursed sun.                 |\n");
        write("| vglare      - Glare, eyes filled with preternatural       |\n");
        write("|               power.                                      |\n");
        write("| vglower     - Glower with rage.                           |\n");
        write("| vgrin       - Flash a grin.                               |\n");
        write("| vgust       - Invoke a short gust of wind.                |\n");
        write("| vhiss       - Hiss at your prey.                          |\n");
        write("| vhug        - Give a hug.                                 |\n");
        write("| vkiss       - Kiss someone.                               |\n");
        write("| vlaugh      - Laugh as only a vampire can.                |\n");
        write("| vlick       - Taste the blood from your prey.             |\n");
        write("| vlong       - Gaze longingly at your prey's neck.         |\n");
        write("| vlook       - Look around with disbelief.                 |\n");
        write("| vmelancholy - Frown, your face showing melancholy.        |\n");
        write("| vnarrow     - Narrow your eyes.                           |\n");
        write("| vnod        - Nod respectfully.                           |\n");
        write("| vpast       - Recall this drama from the past.            |\n");
        write("| vpensive    - Consider some troubling matter.             |\n");
        write("| vpierce     - Stare intently at your prey, baring their   |\n");
        write("|               soul.                                       |\n");
        write("| vpity       - Look at your prey with pity.                |\n");
        write("| vpower      - Infuse yourself with the power of the dark  |\n");
        write("|               Gods.                                       |\n");
        write("| vrecall     - Recall the taste of various prey you have   |\n");
        write("|               sampled.                                    |\n");
        write("| vrevel      - Revel in uninhibited triumph.               |\n");
        write("| vrevere     - Show reverence to another.                  |\n");
        write("| vrise       - Rise to your full height and power.         |\n");
        write("| vroar       - Let out a terrifying roar.                  |\n");
        write("| vsadness    - Allow sadness to overcome you.              |\n");
        write("| vscratch    - Look around while scratching your fangs.    |\n");
        write("| vscream     - Scream at extreme levels.                   |\n");
        write("| vshadow     - Dance your shadow about the room.           |\n");
        write("| vshine      - Cause your skin to shine.                   |\n");
        write("| vsmile      - Smile charmingly.                           |\n");
        write("| vsmirk      - Smirk, with fangs.                          |\n");
        write("| vsweat      - Sweat a blood sweat.                        |\n");
        write("| vtaste      - Taste the blood in the air.                 |\n");
        write("| vtear       - Let a single blood-tear fall.               |\n");
        write("| vthoughtful - Stroke your chin and look thoughtful.       |\n");
        write("| vtouched    - Look touched by your prey's emotions.       |\n");
        write("| vthroat     - Growl with a deep throated growl.           |\n");
        write("| vtrace      - Trace a finger down the neck of your        |\n");
        write("|               prey.                                       |\n");
        write("| vturn       - Turn slowly towards your prey.              |\n");
        write("| vyawn       - My, such lovely fangs you have.             |\n");
        write("|___________________________________________________________|\n");
        
        
        return 1;
    }
    

    if (str == "bloodpath")
    {
        write("");  
        
        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
        {
            //write(""
            write("|==============================================================|\n");
            write("|            V A M P I R E S ,   B L O O D P A T H             |\n");
        }
        else
        {
            write("|==============================================================|\n");
            write("|      V A M P I R E   S P A W N S ,   B L O O D P A T H       |\n");
        }

        write("|--------------------------------------------------------------|\n");    
        write("|                                                              |\n");        
        write("| The anecdotes by the common man of how vampires are created  |\n");
        write("| are true. However, how they develop through time is a        |\n");
        write("| different matter entirely - every single vampire develops    |\n");
        write("| in their own way, or shall we say, follows their own unique  |\n");
        write("| path, provided they survive long enough to experience it.    |\n");
        write("|                                                              |\n");
        write("| From Newborn Vampire Spawns to the Progenitor of all         |\n");
        write("| Vampires, the Blood decides their direction, their           |\n");
        write("| abilities, and directly or indirectly, their ultimate fate.  |\n");
        write("|                                                              |\n");
        write("|                                                              |\n");
        write("|  ========================                                    |\n");
        write("| |  THE PATH OF THE BLOOD |                                   |\n");
        write("|  ==   ===================                                    |\n");
        write("|    | |                                                       |\n");
        write("| ___| |___                                                    |\n");
        write("||Sanctuary|                                                   |\n");
        write("|  --| |---                                                    |\n");       
        write("|    | |                                                       |\n");
        
        if (VAMPIRES_MAPPINGS->query_vampire_main_special(this_player()->query_name()) == 1)
        {

            write("|    | |_______________________________________________        |\n");
            write("|    |________   ___________________   ______________  |       |\n");
            write("|             | |                   | |              | |       |\n");
            write("|        _____| |_____              | |              | |       |\n");  
            write("|       | Bloodletter |              |                |        |\n");
            write("|        -----   -----                                         |\n");
            write("|             | |                                              |\n");
            write("|             | |__________                                    |\n");
            write("|             |__________  |                                   |\n");
            write("|                        | |                                   |\n");
            write("|                        | |                                   |\n");
        }

        if (VAMPIRES_MAPPINGS->query_vampire_main_special(this_player()->query_name()) == 2)
        {
            write("|    | |_______________________________________________        |\n");
            write("|    |________   ___________________   ______________  |       |\n");
            write("|             | |                   | |              | |       |\n");
            write("|             | |                ___| |___           | |       |\n");  
            write("|              |                | Execute |           |        |\n");
            write("|                                ---   ---                     |\n");
            write("|                                   | |                        |\n");
            write("|                         __________| |                        |\n");
            write("|                        |  __________|                        |\n");
            write("|                        | |                                   |\n");
            write("|                        | |                                   |\n");
        }

        if (VAMPIRES_MAPPINGS->query_vampire_main_special(this_player()->query_name()) == 3)
        {
            write("|    | |_______________________________________________        |\n");
            write("|    |________   ___________________   ______________  |       |\n");
            write("|             | |                   | |              | |       |\n");
            write("|             | |                   | |          ____| |____   |\n");  
            write("|              |                     |          | Trucidate |  |\n");
            write("|                                                ----   ----   |\n");
            write("|                                                    | |       |\n");
            write("|                         ___________________________| |       |\n");
            write("|                        |  ___________________________|       |\n");
            write("|                        | |                                   |\n");
            write("|                        | |                                   |\n");
        }
                
        int vampgauge2 = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name());
        
        if (vampgauge2 >= 150)
        {
            write("|                     ___| |___                                |\n");
            write("|                    |  vmeld  |                               |\n");
            write("|                     ---   ---                                |\n");
            write("|                        | |_______________                    |\n");
            write("|                        |_______________  |                   |\n");   
            write("|                                        | |                   |\n");
        }
        
        
        if (vampgauge2 >= 250)
        {
            write("|                                    ____| |_____              |\n");
            write("|                                   |Regeneration|             |\n");
            write("|                                    ----   -----              |\n");
            write("|                         _______________| |                   |\n");
            write("|                        |  _______________|                   |\n");   
            write("|                        | |                                   |\n");
        }
        
        
        

        if (vampgauge2 >= 500)
        {
            write("|        ________________| |                                   |\n");
            write("|       |  ________________|                                   |\n");
            write("|    ___| |___                                                 |\n");
            write("|   | vsniff  |                                                |\n");
            write("|    ---   ---                                                 |\n");
            write("|       | |                                                    |\n");
        }
        
        if (vampgauge2 >= 900)
        {
            write("|       | |                                                    |\n");
            write("|       | |                                                    |\n");
            write("|  _____| |________________                                    |\n");
            write("| | Siphon |  Augmentation |                                   |\n");
            write("|  -----   ----------------                                    |\n");
            write("|       | |                                                    |\n");
        }
        
        
        if (vampgauge2 >= 1200)
        {
            write("|       | |__________                                          |\n");
            write("|       |__________  |                                         |\n");
            write("|                  | |                                         |\n");
            write("|               ___| |___                                      |\n");
            write("|              | vsense  |                                     |\n");
            write("|               ---   ---                                      |\n");
            write("|                  | |_____________________                    |\n");
            write("|                  |_____________________  |                   |\n");
            write("|                                        | |                   |\n");
        }
        
       
        
        // Occ vampires.       
        if (vampgauge2 >= 1451)
        {
            write("|                                        | |                   |\n");
            write("|                                     ___| |___                |\n");
            write("|                                    | vcling  |               |\n");   
            write("|                                     ---   ---                |\n");
            write("|                         _______________| |                   |\n");
            write("|                        |  _______________|                   |\n");
            write("|                        | |                                   |\n");
            write("|                     ___| |___                                |\n");
            write("|                    | Amplify |                               |\n");   
            write("|                     ---   ---                                |\n");
            write("|                        | |                                   |\n");
        }
        
        // TIER 1 ABILITIES    
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) == 0)
        {
            write("|                                                              |\n");
            write("|______________________________________________________________|\n");
            
            return 1;            
        }
        
         // TIER 1 ABILITIES
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) == 1)
        {
            write("|                        | |                                   |\n");
            write("|                        | |____________________________       |\n");
            write("|                        |____________________________  |      |\n");
            write("|                                                     | |      |\n");
            write("|       ______________________________________________| |      |\n");
            write("|      |  ________   ___________  ____________________  |      |\n");
            write("|      | |        | |           | |              _____| |_____ |\n");
            write("|      | |        | |        ___| |___          | Elusiveness ||\n");
            write("|      | |         |        |Incognito|          -----| |----- |\n");
            write("|      | |                   ---------                | |      |\n");
            write("|       |                                             | |      |\n");
            write("|                                                     | |      |\n");
            write("|                                            _________| |      |\n");
            write("|                                           |  _________|      |\n");
            write("|                                           | |                |\n"); 
        }                                           
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) == 2)
        {
            write("|                        | |                                   |\n");
            write("|                        | |____________________________       |\n");
            write("|                        |____________________________  |      |\n");
            write("|                                                     | |      |\n");
            write("|       ______________________________________________| |      |\n");
            write("|      |  ________   ___________  ____________________  |      |\n");
            write("|      | |        | |           | |                   | |      |\n");
            write("|      | |        | |        ___| |___                 |       |\n");
            write("|      | |         |        |Incognito|                        |\n");
            write("|      | |                   ---------                         |\n");
            write("|  ____| |_____                                                |\n");
            write("| | Resilience |                                               |\n");
            write("|  ----| |-----                                                |\n");
            write("|      | |____________________________________                 |\n");
            write("|      |____________________________________  |                |\n");
            write("|                                           | |                |\n"); 
        }   

        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) == 3)
        {
            write("|                        | |                                   |\n");
            write("|                        | |____________________________       |\n");
            write("|                        |____________________________  |      |\n");
            write("|                                                     | |      |\n");
            write("|       ______________________________________________| |      |\n");
            write("|      |  ________   ___________  ____________________  |      |\n");
            write("|      | |        | |           | |               ____| |____  |\n");
            write("|      | |        | |        ___| |___           |Elusiveness| |\n");
            write("|      | |         |        |Incognito|           ----| |----  |\n");
            write("|      | |                   ---------                | |      |\n");
            write("|  ____| |_____                                       | |      |\n");
            write("| | Resilience |                             _________| |      |\n");
            write("|  ----| |-----                             |  _________|      |\n");
            write("|      | |__________________________________| |                |\n");
            write("|      |____________________________________  |                |\n");
            write("|                                           | |                |\n"); 
        }                                                   

        
        // TIER 2 ABILITIES    
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 0)
        {
            write("|                                                              |\n");
            write("|______________________________________________________________|\n");
            
            return 1;            
        }
               
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 1)
        {
            write("|                         __________________| |                |\n");
            write("|                        |  __________________|                |\n");
            write("|                   _____| |________                           |\n");
            write("|                  |   _______      |____________________      |\n");
            write("|       ___________|  |       |_   ________   _________  |     |\n");
            write("|      |  ____________|         | |        | |         | |     |\n");
            write("|      | |                      | |        | |       __| |__   |\n");
            write("|   ___| |____                   |          |       |Deadeye|  |\n");
            write("|  | Ethereal |                                      -------   |\n");
            write("|   ---| |----                                                 |\n");
            write("|      | |_____________________                                |\n");
            write("|      |_____________________  |                               |\n");
            write("|                            | |                               |\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 2)
        {
            write("|                         __________________| |                |\n");
            write("|                        |  __________________|                |\n");
            write("|                   _____| |________                           |\n");
            write("|                  |   _______      |____________________      |\n");
            write("|       ___________|  |       |_   ________   _________  |     |\n");
            write("|      |  ____________|         | |        | |         | |     |\n");
            write("|      | |                      | |        | |       __| |__   |\n");
            write("|      | |                   ___| |_____    |       |Deadeye|  |\n");
            write("|       |                   | Obfuscate |            -------   |\n");
            write("|                            ---| |-----                       |\n");
            write("|                             __| |                            |\n");
            write("|                            |  __|                            |\n");
            write("|                            | |                               |\n");
        }


        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 3)
        {
            write("|                         __________________| |                |\n");
            write("|                        |  __________________|                |\n");
            write("|                   _____| |________                           |\n");
            write("|                  |   _______      |____________________      |\n");
            write("|       ___________|  |       |_   ________   _________  |     |\n");
            write("|      |  ____________|         | |        | |         | |     |\n");
            write("|      | |                      | |        | |       __| |__   |\n");
            write("|   ___| |____               ___| |_____    |       |Deadeye|  |\n");
            write("|  | Ethereal |             | Obfuscate |            -------   |\n");
            write("|   ---| |----               ---| |-----                       |\n");
            write("|      | |______________________| |                            |\n");
            write("|      |_____________________   __|                            |\n");
            write("|                            | |                               |\n");
        }          
                                             
                                             
        // TIER 3 ABILITIES
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(this_player()->query_name()) == 0)
        {
            write("|                                                              |\n");
            write("|______________________________________________________________|\n");
            
            return 1;
        }
       
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(this_player()->query_name()) == 1)
        {
            write("|                            | |__                             |\n");
            write("|                  __________|  __-                            |\n");
            write("|                 |  ________  |                               |\n");
            write("|                 | |        | |________                       |\n");
            write("|              ___| |___     | Celerity |                      |\n");
            write("|             | Lifeward |    ----------                       |\n");
            write("|              ---   ---                                       |\n");
            write("|  _______________| |                                          |\n");
            write("| |  _______________|                                          |\n");
            write("| | |_________________________                                 |\n");
            write("| |_________________________  |                                |\n");
            write("|                           | |                                |\n");
        }  
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(this_player()->query_name()) == 2)
        {
            write("|                            | |_____________________          |\n");
            write("|                          __|  ___________________  |         |\n");
            write("|                         -__  |                   | |         |\n");
            write("|                            | |________           | |         |\n");
            write("|                            | Celerity |          |         |\n");
            write("|                             ----------           | |         |\n");
            write("|                                              ____| |____     |\n");
            write("|                                             |Strangulate|    |\n");
            write("|                                              ----| |----     |\n");
            write("|                            ______________________| |         |\n");
            write("|                           |  ______________________|         |\n");
            write("|                           | |                                |\n");
        }
        
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(this_player()->query_name()) == 3)
        {
            write("|                            | |_____________________          |\n");
            write("|                  __________|  ___________________  |         |\n");
            write("|                 |  ________  |                   | |         |\n");
            write("|                 | |        | |________           | |         |\n");
            write("|              ___| |___     | Celerity |          | |         |\n");
            write("|             | Lifeward |    ----------           | |         |\n");
            write("|              ---   ---                       ____| |____     |\n");
            write("|  _______________| |                         |Strangulate|    |\n");
            write("| |  _______________|                          ----| |----     |\n");
            write("| | |______________________________________________| |         |\n");
            write("| |_________________________   ______________________|         |\n");
            write("|                           | |                                |\n");
        }  


        // TIER 4 ABILITIES
        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(this_player()->query_name()) == 0)
        {
            write("|                                                              |\n");
            write("|______________________________________________________________|\n");
            
            return 1;
        }

        /*if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(this_player()->query_name()) == 1)
        {
            write("|                           | |                                |\n");
            write("|                           | |                                |\n");            
            write("|       ____________________| |____                            |\n"); 
            write("|      |  __________________   __  |______________             |\n"); 
            write("|   ___| |___               | |  |______________  |            |\n"); 
            write("|  |Mesmerize|               |                 _| |_           |\n"); 
            write("|   ---------                                 |_Fly_|          |\n"); 
            write("|                 ______________________________| |            |\n"); 
            write("|                |  ______________________________|            |\n"); 
            write("|                | |                                           |\n"); 
            write("|                | |                                           |\n");
        } 

        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(this_player()->query_name()) == 2)
        {
            write("|                           | |                                |\n");
            write("|                           | |                                |\n");            
            write("|       ____________________| |____                            |\n"); 
            write("|      |  __________________   __  |______________             |\n"); 
            write("|   ___| |___               | |  |______________  |            |\n"); 
            write("|  |Mesmerize|              | |                 | |            |\n"); 
            write("|   ---------              _| |_                 |             |\n"); 
            write("|                         |Swarm|                              |\n"); 
            write("|                          -| |-                               |\n"); 
            write("|                 __________| |                                |\n"); 
            write("|                |  __________|                                |\n"); 
            write("|                | |                                           |\n"); 
        }*/

        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(this_player()->query_name()) > 0)
        {
            write("|                           | |                                |\n");
            write("|                           | |                                |\n");            
            write("|       ____________________| |____                            |\n"); 
            write("|      |  __________________   __  |______________             |\n"); 
            write("|   ___| |___               | |  |______________  |            |\n"); 
            write("|  |Mesmerize|             _| |_               _| |_           |\n"); 
            write("|   ---------             |Swarm|             |_Fly_|          |\n"); 
            write("|                 _________-| |-________________| |            |\n"); 
            write("|                |  ______________________________|            |\n"); 
            write("|                | |                                           |\n"); 
            write("|                | |                                           |\n");
        }         

        if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_7(this_player()->query_name()) == 1)       
        {
            write("|                | |                                           |\n");
            write("|               _| |_                                          |\n");
            write("|              | Sigil|                                        |\n");
            write("|               -| |--                                         |\n");
            write("|                | |                                           |\n");
            write("|                 |                                            |\n");
            write("|______________________________________________________________|\n");
            
            return 1;
        }

        write("|______________________________________________________________|\n");
        
        return 1;
    }
       
    if (str == "sun" || str == "daystar")
    {
        write("");
 
        write("|===========================================================|\n");
        write("|                      T H E   S U N                        |\n");
        write("|-----------------------------------------------------------|\n");
        write("|                                                           |\n");   
        write("| An everpresent menace to all Vampire kind, the daystar is |\n"); 
        write("| treacherous and nearly unavoidable. Its effects on our    |\n"); 
        write("| kind are binary in effect, in that, you either find that  |\n"); 
        write("| you are exposed or not exposed to its deadly rays; there  |\n"); 
        write("| are no differing levels of severity and all Vampire kind  |\n"); 
        write("| will suffer the same level of intensity unless completely |\n"); 
        write("| shielded from them by structure or magical means.         |\n"); 
        write("|                                                           |\n"); 
        write("| Regardless of levels of shielding, a Vampire will always  |\n"); 
        write("| be aware of the sun's presence, and if it is daytime,     |\n"); 
        write("| they will be subjected to some negative effects.          |\n"); 
        write("| As natural nocturnal predators, the Vampire kin will feel |\n"); 
        write("| stronger at night and weaker by day in different forms    |\n"); 
        write("| of potency, be they a fluctuation in skills or the        |\n"); 
        write("| overall lack of an ability, or abilities with reduced     |\n"); 
        write("| effect.                                                   |\n"); 
        write("|                                                           |\n"); 
        write("| If a Vampire is immolated by the rays of the sun, he/she  |\n"); 
        write("| is PERMANENTLY destroyed and will be removed, cursed to   |\n");
        write("| walk among the mortals again, unless of course, the       |\n");
        write("| Vampire has found other means of protection.              |\n"); 
        write("|___________________________________________________________|\n");
        
        return 1;
    }
    
    if (str == "age" || str == "aging")
    {
        write("");
 
        write("|===========================================================|\n");
        write("|                         A G I N G                         |\n");
        write("|-----------------------------------------------------------|\n");
        write("|                                                           |\n");   
        write("| Unlike the cursed mortals who decline over the years, all |\n");
        write("| Vampire kin increase in power through the survival of the |\n");
        write("| passage of time. A Vampire will continue to age, awake or |\n");
        write("| asleep as long as the required level of blood saturation  |\n");
        write("| is sustained.                                             |\n");
        write("|                                                           |\n");
        write("| Only a properly aging Vampire will discover new gifts     |\n");
        write("| titles and abilities.                                     |\n");
        write("|                                                           |\n");
        write("| The placement of a coffin somewhere in the realm is       |\n");
        write("| required for aging to take place.                         |\n");                       
        write("|___________________________________________________________|\n");

        return 1;
    }
    
    if (str == "turning")
    {
        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
        {
            write("What?\n");
            
            return 1;
        }
        
        write("");
 
        write("|===========================================================|\n");
        write("|  T H E   C R E A T I O N   O F   N E W   V A M P I R E S  |\n");
        write("|-----------------------------------------------------------|\n");
        write("|                                                           |\n");
        write("| There may come a time when roaming in solitude amid the   |\n");
        write("| living loses its allure and becomes more of a burden than |\n");
        write("| having a companion or operating in a group.               |\n");
        write("|                                                           |\n");
        write("| Creating a new Vampire from a fresh, ripe, mortal is      |\n");
        write("| often the preferred method. This, turning, is a way for   |\n");
        write("| the Vampire to ensure control, safety and loyalty over    |\n");
        write("| their new progeny, in lieu of dealing with the random,    |\n");
        write("| wild, stray of other origins or sires.                    |\n");
        write("|                                                           |\n");
        write("| A Vampire who wishes to sire a mortal must relenquish the |\n");
        write("| creation tariff of two immortality points.                |\n");
        write("|                                                           |\n");
        write("| In order to be turned, the mortal candidate must be at    |\n");
        write("| least Champion in stature and have no active racial,      |\n");
        write("| occupational or layman affiliations. If all criteria are  |\n");
        write("| met, resulting in a successful tunring, the candidate     |\n");
        write("| awakens a full fledgling Vampire, surpassing the trials   |\n");
        write("| of the Vampire Spawn.                                     |\n");
        write("|  *Vampire Nation will decree that turning is illegal      |\n");
        write("|   when there are too many active vampires in the realms.  |\n");
        write("|___________________________________________________________|\n"); 

        return 1;
    }
    
    
    if (str == "coven" || str == "covens")
    {
        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
        {
            write("What?\n");
            
            return 1;
        }
        
        write("");
 
        write("|===========================================================|\n");
        write("|               V A M P I R E   C O V E N S                 |\n");
        write("|-----------------------------------------------------------|\n");
        write("|                                                           |\n");
        write("| Many rumors and stories are passed down through the       |\n");
        write("| generations that speak of the horrors of a brood of night |\n");
        write("| demons that come and steal misbehaving children while the |\n");
        write("| parents are asleep. Where not all false, these stories    |\n");
        write("| have been allowed to perpetuate through time in order to  |\n");
        write("| foster true respect for the creatures of the night.       |\n");
        write("|                                                           |\n");
        write("| There are not broods of night demons, however, there are  |\n");
        write("| factions of Vampires that are housed together in one      |\n");
        write("| location called a coven. The coven is a relatively secure |\n");
        write("| place ment for full Vampires.                             |\n");
        write("|                                                           |\n");
        write("| A vampire needs to be in the centermost room and          |\n");
        write("| <claim coven> for the physical cost of two immortality    |\n");
        write("| points, and only members can enter it.                    |\n");
        write("|                                                           |\n");
        write("| >>Vampires leaving a coven, or being removed from a coven |\n");
        write("| will always lose their coffins.<<                         |\n");
        write("|                                                           |\n");
        write("|___________________________________________________________|\n");
        
        return 1;
    }
    

    
    if (str == "immortality" || str == "immortality points" 
    || str == "immortality point")
    {
        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
        {
            write("What?\n");
            
            return 1;
        }
        
        write("");
 
        write("|===========================================================|\n");
        write("|         I M M O R T A L I T Y    P O I N T S              |\n");
        write("|-----------------------------------------------------------|\n");
        write("|                                                           |\n");
        write("| Immortality points are a rare form of currency for the    |\n");
        write("| Vampire kin and are extremely difficult to obtain. The    |\n");
        write("| number of immortality points that any one individual can  |\n");
        write("| hold are variable and dependent upon rank and overall     |\n");
        write("| age.                                                      |\n");
        write("|                                                           |\n");
        write("| Immortality points may be obtained by:                    |\n");
        write("|                                                           |\n");
        write("| Aging:           The two first points of immortality is   |\n");
        write("|                  awarded to the Vampire at the time of    |\n");
        write("|                  ascension. Turned Vampires only receive  |\n");
        write("|                  a single point.                          |\n");
        write("|                                                           |\n");
        write("|                  Subsequent points may be earned by       |\n");
        write("|                  further aging. The rate of earning       |\n");
        write("|                  through the passage of time is up to the |\n");
        write("|                  individual to discover, but it should    |\n");
        write("|                  be expected to be _extremely_ rare.      |\n");
        write("|                                                           |\n");
        write("| Thralls:         The thrall of a Vampire may be granted   |\n");
        write("|                  the knowledge of how to obtain           |\n");
        write("|                  immortality points for his or her master |\n");
        write("|                  through prolonged servitude. It is not an|\n");
        write("|                  uncommon  practice to allow the thrall to|\n");
        write("|                  collect the necessary points to          |\n");
        write("|                  eventually grant them eternal life. Only |\n");
        write("|                  vampires beyond a certain age can create |\n");
        write("|                  a thrall. A thrall can only produce two  |\n");
        write("|                  points of Immortality, ever, even if     |\n");
        write("|                  remaining in the service of the vampire. |\n");
        write("|                                                           |\n");
        write("| Anomalies:       Throughout the world, there are          |\n");
        write("|                  anomalies and places of power that are   |\n");
        write("|                  relevant to Vampire kin. These oddities  |\n");
        write("|                  may grant points of immortality to those |\n");
        write("|                  Vampires found worthy to receive them.   |\n");
        write("|                                                           |\n");
        write("| Sentient                                                  |\n");
        write("|   Vampires:      By slaying another of your kin, you may  |\n");
        write("|                  steal one of their points of Immortality,|\n"); 
        write("|                  if they have _two_ points or more.       |\n");
        write("|                                                           |\n");
        write("|                                                           |\n");
        write("|                                                           |\n");
        write("| The uses of Immortality Points:                           |\n");
        write("|                                                           |\n");
        write("| Life insurance:  A single point of immortality will save  |\n");
        write("|                  a Vampire from being permanently         |\n");
        write("|                  destroyed by the various dangers in      |\n");
        write("|                  the world.                               |\n");
        write("|                                                           |\n");
        write("|                  *If the last point of immortality is     |\n");
        write("|                   spent deflecting a permanent destruction|\n");
        write("|                   event, that point will respawn for free |\n");
        write("|                   a few days later.                       |\n");
        write("|                                                           |\n");
        write("| Turning:         The process of turning is exceedingly    |\n");
        write("|                  taxing on the Vampire and requires two   |\n");
        write("|                  points of immortality to complete. The   |\n");
        write("|                  turning of a mortal only works if the    |\n");
        write("|                  victim is of champion+ stature, humanoid |\n");
        write("|                  and has no racial, occupation or layman  |\n");
        write("|                  affiliation. Note that a mortal who is   |\n");
        write("|                  turned will not endure the long and      |\n");
        write("|                  arduous journey of a Vampire Spawn and   |\n");
        write("|                  thus will not fully understand the       |\n");
        write("|                  perils, having had to hone their         |\n");
        write("|                  survival skills, alone in the wild.      |\n");
        write("|                   *If there are too many active full      |\n");
        write("|                    vampires roaming the lands, the        |\n");
        write("|                    Vampire Nation will deny this option  .|\n");
        write("|                                                           |\n");
        write("| Tier unlock:     It is possible to exchange 2 points of   |\n");
        write("|                  immortality for a full tier unlock       |\n");
        write("|                  that the individual has access to.       |\n");
        write("|                  Syntax:'vunlock one|two|three|four' etc  |\n");
        write("|                                                           |\n");
        write("| Coven formation: If an aged and powerful Vampire has      |\n");
        write("|                  located a suitable area, befitting that  |\n");
        write("|                  of placement of a coven, he or she may   |\n");
        write("|                  form that coven at the cost of two       |\n");
        write("|                  immortality points.                      |\n");
        write("|                   *Only accessible for adequate aged      |\n");
        write("|                    vampires.                              |\n");  
        write("|                                                           |\n");
        write("| command: immpointabolish  - If you wish to rid yourself   |\n");
        write("|          of the remaining points of immortality.          |\n");
        write("|                                                           |\n");
        write("|___________________________________________________________|\n");

        return 1;
    }

    if (str == "skill" || str == "skills")
    {
        write("");
 
        write("|===========================================================|\n");
        write("|                        S K I L L S                        |\n");
        write("|-----------------------------------------------------------|\n");
        write("|                                                           |\n");
        write("| Vampire Spawns will not be allotted many skills from their|\n"); 
        write("| sire and must therefore, depend solely on an occupation   |\n");
        write("| of necessary skills for survival.                         |\n");
        write("|                                                           |\n");
        write("| Some skills are given for spawns however:                 |\n");
        write("| anatomy-skill, spellcraft, death magic and                |\n");
        write("| form enchantment. The Anatomy-skill teaches the Spawn     |\n");
        write("| the intricacies of bloodletting.                          |\n");   
        
        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
        {
            write("|                                                           |\n");
            write("|                                                           |\n");   
            write("| Full Vampires are allotted more skills, however, they     |\n");
            write("| will not be able to improve them through the redundant    |\n");
            write("| training in exchange of currency as can be found          |\n");
            write("| throughout the realms. Instead, they are awarded through  |\n");
            write("| evolution from Spawn and can only increase with time,     |\n");
            write("| through the aging process.                                |\n");     
        }
                
        write("|___________________________________________________________|\n");

        return 1;
    }
    
    if (str == "blood")
    {
        write("");
 
        write("|===========================================================|\n");
        write("|                         B L O O D                         |\n");
        write("|-----------------------------------------------------------|\n");
        write("|                                                           |\n");   
        write("| Blood is the sweet copperly nectar of life, and for       |\n");
        write("| Vampire kin, it is the essence of our strength, endurance |\n");
        write("| and longevity; our unlife!                                |\n");
        write("|                                                           |\n");
        write("| Due to the fact that Vampire kin age on a consistent      |\n");
        write("| basis, logically, this aging must be fed by something.    |\n");
        write("| This something is the level of saturation of blood in the |\n");
        write("| individual, meaning that your blood saturation will       |\n");
        write("| decrease over time, even when you are sleeping.           |\n");
        write("| Sufficient blood levels must be maintained to foster      |\n");
        write("| proper aging and for the stability of abilities and       |\n");
        write("| gifts granted over time. Some abilities may be vastly     |\n");
        write("| weakened by low levels of blood saturation and others may |\n");
        write("| not work at all due to the overall general weaknesses of  |\n");
        write("| the thirsty Vampire.                                      |\n");
        write("|                                                           |\n");
        write("| Age also has an affect on the size of the individual's    |\n");
        write("| blood pool. Therefore, the older the Vampire is, the      |\n");
        write("| larger the blood pool, which increases both the level of  |\n");
        write("| sustainability and longevity.                             |\n");
        write("|                                                           |\n");
        write("| Blood is primarily gained through the use of combat       |\n");
        write("| specials.                                                 |\n");
        write("|___________________________________________________________|\n");
        
        return 1;
    }
    
    
    if (str == "thrall" || str == "thralls")
    {
        write("");
        
        write("|===========================================================|\n");
        write("|                      T H R A L L S                        |\n");
        write("|-----------------------------------------------------------|\n");
        write("|                                                           |\n");
        write("| Mortal familiars are a vital cog in the Vampire network   |\n");
        write("| and are the backbones of lineage and survival. The        |\n");
        write("| trusted thrall can serve as a messenger, spy, walking     |\n");
        write("| bloodbank and willing apprentice to the Vampire. The      |\n");
        write("| thrall also shares a unique connection with their master  |\n");
        write("| that defies all concept of space and time. Through        |\n");
        write("| concentration and focus of thought, the master can see    |\n");
        write("| and hear what is around their pet, communicate directly   |\n");
        write("| with them, regardless of distance and even allow the      |\n");
        write("| servant to gather precious immortality points. Once a     |\n");
        write("| suitable mortal has been found, the Vampire must simply   |\n");
        write("| <vthralloffer> them the gift of being a Thrall, at which  |\n");
        write("| point the mortal may choose to accept or decline.         |\n");
        write("|                                                           |\n");
        write("| Thralls are only available to properly aged vampires.     |\n");
        write("|___________________________________________________________|\n");
        
        return 1;
    }
    
    if (str == "coffins" || str == "coffin")
    {
        write("");
 
        write("|===========================================================|\n");
        write("|                      C O F F I N S                        |\n");
        write("|-----------------------------------------------------------|\n");
        write("|                                                           |\n");   
        write("| All of the tales and stories of our kin pass down the     |\n");
        write("| legends of the necessities of coffins. Unfortunately,     |\n");
        write("| our dependence upon them is not a myth. Coffins come in   |\n");
        write("| various shapes, sizes and types and, to avoid the         |\n");
        write("| stigmas painted in children fables about the overall      |\n");
        write("| destruction of covens and coffin alike by Vampire hunters |\n");
        write("| self-aggrandized holy men, we should take care in         |\n");
        write("| searching for our own coffins in the various graveyards   |\n");
        write("| found throughout the lands of Genesis. Old and used       |\n");
        write("| coffins are seldom missed by their decaying occupants or  |\n");
        write("| those who purchased and placed them.                      |\n");
        write("|                                                           |\n");
        write("| In order to find a refuge and protection from the burning |\n");
        write("| light of the cursed daystar, <search here for coffin> in  |\n");
        write("| one of the many graveyards found in the lands. The        |\n");
        write("| frequency of success, location and quality of coffin are  |\n");
        write("| many and varied and depend greatly on the skills and the  |\n");
        write("| honed skills of the individual searching.                 |\n");
        write("|                                                           |\n");
        write("| Be warned that coffins are subject to destruction by      |\n");
        write("| others. If a coffin is destroyed while you are sleeping   |\n");
        write("| or merely resting inside, you are in dire risk of being   |\n");
        write("| PERMANENTLY destroyed and the end of your unlife,         |\n");
        write("| translating to the removal from Vampires and walking      |\n");
        write("| the world, again, as a mortal. There is no safe haven     |\n");
        write("| for coffins, even in locations that are deemed as         |\n");
        write("| 'protected' by the immortals, so use caution and guile    |\n");
        write("| when choosing a location.                                 |\n");
        write("|                                                           |\n");
        write("| Because coffins are constructed with different materials, |\n");
        write("| the method of destruction may vary.                       |\n");
        write("|                                                           |\n");
        write("| Vampires of greater rank and power may search for new     |\n");
        write("| coffins at their leisure, but first the old ones must be  |\n");
        write("| destroyed. This can be accomplished through using         |\n");
        write("| 'dispatch coffin', but know that this practice is risky   |\n");
        write("| and may come at a great cost, payable only in blood,      |\n");
        write("| gifts may no longer work, and aging immediately stops.    |\n");
        write("|                                                           |\n");
        write("| To reiterate, while it's possible to exist without a      |\n");
        write("| coffin and rely on the dirt and gravel on the graveyard,  |\n");
        write("| you will not age, and most gifts and abilities will not   |\n");
        write("| work until you find and place the coffin somewhere.       |\n");
        write("|                                                           |\n");
        write("| Simply carrying the coffin around will have the same      |\n");
        write("| penalties.                                                |\n");
        write("|                                                           |\n");
        write("| Identifying the owner of the coffin can be done by        |\n");
        write("| a syntax similar to: 'examine nerull's coffin'.           |\n");
        write("|                                                           |\n");
        write("| ** IMPORTANT: The basic principle for coffin placement is |\n");
        write("|               that it somehow can be accessed or found    |\n");
        write("|               by at least one more more players, friends  |\n");
        write("|               or foes. If the coffin is placed in an      |\n");
        write("|               environment that its impossible to          |\n");
        write("|               reach, then the location is illegal and     |\n");
        write("|               should be reported to the GM for            |\n");
        write("|               blacklisting. Illegal coffins that are      |\n");
        write("|               found may be subject to removal/destruction,|\n");
        write("|               and vampire subject to investigation.       |\n");
        write("|                                                           |\n");
        write("|               Coffin placement/locations will be subject  |\n");
        write("|               to reviews regulary.                        |\n");
        write("|                                                           |\n");
        write("|               Example: If the presence of a coffin in a   |\n");
        write("|                        room blocks others from entering   |\n");
        write("|                        the room, then it's illegal, and   |\n");
        write("|                        coffin should be placed somewhere  |\n");
        write("|                        else.                              |\n");
        write("|                                                           |\n");
        write("| ** See 'vhelp troubleshoot' if coffin-issues arises.      |\n");
        write("|___________________________________________________________|\n");
        
        return 1;
    }
    
    if (str == "support" || str == "troubleshoot")
    {
        write("");
 
        write("|===========================================================|\n");
        write("|      T R O U B L E S H O O T   A N D   S U P P O R T      |\n");
        write("|-----------------------------------------------------------|\n");
        write("|                                                           |\n");   
        write("| Sometimes, items may not work as intended or bug out. Here|\n");
        write("| are listed points currently known to make or be issues.   |\n");
        write("|                                                           |\n");   
        write("| 1. Coffins - If your coffin doesn't spawn within a minute,|\n");
        write("|    travel to its last known location. If it's there, take |\n");
        write("|    it, and replace it. Else, contact GM.                  |\n");
        write("|                                                           |\n");   
        write("|___________________________________________________________|\n");
        
        return 1;
    }
    
    
    
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
    {
        write("======================================================================|\n");
        write("|                    V A M P I R E S,   H E L P                       |\n");
        write("|---------------------------------------------------------------------|\n");
        write("|  You can get help for the Vampires by using the commands            |\n");
        write("|  below.                                                             |\n");
    }
    else
    {
        write("======================================================================|\n");
        write("|               V A M P I R E   S P A W N S ,   H E L P               |\n");
        write("|---------------------------------------------------------------------|\n");
        write("|  You can get help for the Vampire Spawns by using the commands      |\n");
        write("|  below.                                                             |\n");
    }
        
    write("|  LATEST UPDATES, 10.04.2023. Use command 'vbugsandfixes' for data.  |\n");
    write("|                                                                     |\n");
    write("|                                                                     |\n");
    write("|                                                                     |\n");
    write("|    > vhelp                        : This list                       |\n");
    write("|    > vhelp emotes                 : List of emotes                  |\n");
    write("|    > vhelp commands               : List of commands                |\n");
    write("|    > vhelp bloodpath              : List of tools of the trade      |\n");
    write("|    > vhelp coffins                : Coffin Lore                     |\n");
    write("|    > vhelp sun                    : Daystar Codex                   |\n");
    write("|    > vhelp aging                  : Passage through time            |\n");
    write("|    > vhelp blood                  : The role of blood               |\n");
    write("|    > vhelp skills                 : General Vampire skills          |\n");
    write("|                                                                     |\n");    
    write("|     ** vhelp troubleshoot         : General information regarding   |\n");
    write("|                                     item and coffin malfunctions,   |\n");    
    write("|                                     and now to solve them.          |\n");    
       
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
    {
        write("|_____________________________________________________________________|\n");
        write("|                                                                     |\n");
        write("|    > vhelp immortality points : About the points of immortality     |\n");
        write("|    > vhelp turning            : Creating new vampires               |\n");
        write("|    > vhelp covens             : Covens and creation thereof         |\n");
        write("|    > vhelp thralls            : Vampire familiars                   |\n");
    }
 
    write("|_____________________________________________________________________|\n");
    
    return 1;   
}


int
do_tierunlock(string str)
{
    int current_resilience_rank = VAMPIRES_MAPPINGS->query_vampires_resilience(this_player()->query_name()); 
    int new_resilience_rank = current_resilience_rank - 2;
            
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
    {
        return 0;
    }

    if (str == "one")
    {              
        int tier1ab1 = VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name());
        
        if (tier1ab1 == 0)
        {
            return 0;
        }
        
        if (current_resilience_rank < 2)
        {
            write("This action requires two points of immortality, which "
            +"you don't currently have.\n");
            
            return 1;
        }
       
        if (tier1ab1 == 3)
        {
            write("Tier one is already fully unlocked.\n");
            
            return 1;
        }
        
        if (tier1ab1 == 1 || tier1ab1 == 2)
        {
            VAMPIRES_MAPPINGS->set_vampire_ability_occ_1(this_player()->query_name(), 3);
            
            VAMPIRES_MAPPINGS->set_vampires_resilience(this_player()->query_name(), new_resilience_rank);
            
            write("You fully unlock tier one.\nYou pay two points of immortality.\n");
            
            return 1;
        }       
    }
    
    if (str == "two")
    {
        int tier2ab1 = VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name());
        
        if (tier2ab1 == 0)
        {
            return 0;
        }
       
        if (current_resilience_rank < 2)
        {
            write("This action requires two points of immortality, which "
            +"you don't currently have.\n");
            
            return 1;
        }
        
        if (tier2ab1 == 3)
        {
            write("Tier two is already fully unlocked.\n");
            
            return 1;
        }
        
        if (tier2ab1 == 1 || tier2ab1 == 2)
        {
            VAMPIRES_MAPPINGS->set_vampire_ability_occ_2(this_player()->query_name(), 3);
            
            VAMPIRES_MAPPINGS->set_vampires_resilience(this_player()->query_name(), new_resilience_rank);
            
            write("You fully unlock tier two.\nYou pay two points of immortality.\n");
            
            return 1;
        }       
    }
    
    if (str == "three")
    {
        int tier3ab1 = VAMPIRES_MAPPINGS->query_vampire_ability_occ_3(this_player()->query_name());
        
        if (tier3ab1 == 0)
        {
            return 0;
        }
        
        if (current_resilience_rank < 2)
        {
            write("This action requires two points of immortality, which "
            +"you don't currently have.\n");
            
            return 1;
        }
              
        if (tier3ab1 == 3)
        {
            write("Tier three is already fully unlocked.\n");
            
            return 1;
        }
        
        if (tier3ab1 == 1 || tier3ab1 == 2)
        {
            VAMPIRES_MAPPINGS->set_vampire_ability_occ_3(this_player()->query_name(), 3);
            
            VAMPIRES_MAPPINGS->set_vampires_resilience(this_player()->query_name(), new_resilience_rank);
            
            write("You fully unlock tier three.\nYou pay two points of immortality.\n");
            
            return 1;
        }       
    }
    
    /*if (str == "four")
    {
        int tier4ab1 = VAMPIRES_MAPPINGS->query_vampire_ability_occ_4(this_player()->query_name());
        
        if (tier4ab1 == 0)
        {
            return 0;
        }
        
        if (current_resilience_rank < 2)
        {
            write("This action requires two points of immortality, which "
            +"you don't currently have.\n");
            
            return 1;
        }
                
        if (tier4ab1 == 3)
        {
            write("Tier four is already fully unlocked.\n");
            
            return 1;
        }
        
        if (tier4ab1 == 1 || tier4ab1 == 2)
        {
            VAMPIRES_MAPPINGS->set_vampire_ability_occ_4(this_player()->query_name(), 3);
            
            VAMPIRES_MAPPINGS->set_vampires_resilience(this_player()->query_name(), new_resilience_rank);
            
            write("You fully unlock tier four.\nYou pay two points of immortality.\n");
            
            return 1;
        }       
    }*/
    
    return 0;
}


int
choose_weaponskill(string str)
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
    {
        return 0;
    }
    
    if (VAMPIRES_MAPPINGS->query_weaponskill_selection(this_player()->query_name()) == 0)
    {
        if (str == "sword")
        {
            VAMPIRES_MAPPINGS->set_weaponskill_selection(this_player()->query_name(), 1);
            
            write("You will now specialize in swords!\n");
            
            return 1;
        }
        
        if (str == "polearm")
        {
            VAMPIRES_MAPPINGS->set_weaponskill_selection(this_player()->query_name(), 2);
            
            write("You will now specialize in polearms!\n");
            
            return 1;
        }
        
        if (str == "axe")
        {
            VAMPIRES_MAPPINGS->set_weaponskill_selection(this_player()->query_name(), 3);
            
            write("You will now specialize in axes!\n");
            
            return 1;
        }
        
        if (str == "knife")
        {
            VAMPIRES_MAPPINGS->set_weaponskill_selection(this_player()->query_name(), 4);
            
            write("You will now specialize in knives!\n");
            
            return 1;
        }
        
        write("Select what weapon to specialize in? (sword|axe|polearm|knife)\n");
        
        return 1;
    }
    
    write("You have already selected a weapon to specialize in!\n");
    
    return 1;
}


int
respec_weaponskill()
{
    int current_resilience_rank2 = VAMPIRES_MAPPINGS->query_vampires_resilience(this_player()->query_name()); 
    int new_resilience_rank2 = current_resilience_rank2 - 1;
    
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
    {
        return 0;
    }
    
    if (VAMPIRES_MAPPINGS->query_weaponskill_selection(this_player()->query_name()) == 0)
    {
        write("You are not specialized in any weapons.\n");
        
        return 1;
    }
    
    if (current_resilience_rank2 < 1)
    {
        write("This action requires one point of immortality, which "
        +"you don't currently have.\n");
        
        return 1;
    }
    
    VAMPIRES_MAPPINGS->clean_weaponskill_selection(this_player()->query_name());
    
    VAMPIRES_MAPPINGS->set_vampires_resilience(this_player()->query_name(), new_resilience_rank2);
    
    write("You nullify your weapon specialization selection. You may now "
    +"select again.\nYou pay one point of immortality.\n");
    
    return 1;
}


int
do_immpointabolish()
{
    int current_resilience_rank = VAMPIRES_MAPPINGS->query_vampires_resilience(this_player()->query_name()); 
    
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
    {
        return 0;
    }
    
    if (current_resilience_rank > 0)
    {
        VAMPIRES_MAPPINGS->set_vampires_resilience(this_player()->query_name(), 0);
        
        write("You abolish your remaining points.\n");
        
        return 1;
    }
    
    write("You have no points to abolish.\n");
    
    return 1;
}


int do_block_commands()
{ 
    if (TP->query_ethereal() == 1)
    {
        TP->catch_tell("You are in the ethereal realm and can't do that.\n");
           
        return 1;
    }
    
    return 0;  
}


int do_stop(string arg)
{
    /*if (::do_stop(arg))
    {
        return 1;
    }*/
    
    if (!stringp(arg))
    {
        return 0;
    }

    switch (lower_case(arg))
    {
        case "ethereal":
            if (TP->query_ethereal() == 1)
            {
                
                setuid();
                seteuid(getuid());
            
                object return_ethereal_paralyze = clone_object(VAMPIRES_GUILD_DIR
                +"obj/return_ethereal_paralyze.c")->move(this_player(), 1);
                
                //TP->set_ethereal();
                return 1;       
            }
            else
            {
                TP->catch_tell("You are not in the ethereal realm.\n");
            }
            break;      
            case "cling":
            return stop_cling(TP);
            break;
            case "drain":
            case "draining":
            case "feed":
            case "feeding":
            case "drink":
            case "drinking":
            case "vdrink":
            if (TP->query_vamp_drain())
            {
                TP->release_vamp_drainee();
                return 1;       
            }
            break;            
    }
    
    return 0;
}


public int query_vampires_gauge_level()
{
    return VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_real_name());
}


int do_ascend_to_full_vampire(string str)
{
    object shadow_occ;
    object shadow_lay;
    object shadow_race;
    
    object tokena;
    
    setuid();
    seteuid(getuid());
        
    if (str == "into a full vampire" 
    || str == "into full vampire"
    || str == "into a vampire"
    || str == "into vampire")
    {     
        if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()))
        {
            return 0;
        }
        
        // Need to be 1450 of age in order to evolve
        if (query_vampires_gauge_level() < 1450)
        {
            return 0;
        }
    
        if (this_player()->query_guild_name_occ())
        {
            write("You must abandon your occupational guild first!\n");
            return 0;
        }
        
        shadow_occ = clone_object(VAMPIRES_GUILD_DIR 
        + "shadows/vampires_sh_occ.c");

        if (shadow_occ->shadow_me(this_player(), "occupational", "ranger", 
        OCC_VAMPIRES_GUILD_NAME) != 1)
        {
            write("You try to evolve into a full vampire, but nothing happens!\n");
            return 1;
        }

        VAMPIRES_MASTER->add_occ_vampires(this_player()->query_name());
        VAMPIRES_MAPPINGS->set_vampires_resilience(this_player()->query_name(), 2);
        
        if (VAMPIRES_MAPPINGS->query_thrall_pool(this_player()->query_name()) == 3)
        {
            VAMPIRES_MAPPINGS->set_vampires_resilience(this_player()->query_name(), 1);
            write("Due to being drained eariler during thralldom, you feel abit weaker!\n");
        }  
        
        VAMPIRES_MAPPINGS->set_vampires_gauge(this_player()->query_name(), 1451);
        
        // We force the setting of abilities upon ascending.
        VAMPIRES_MASTER->set_vamp_abilities(this_player()->query_name());

        this_player()->update_hooks();
        
        JOIN_LOG("join_log",
        "The Vampire Spawn " +this_player()->query_name() 
        +" evolved into full vampire!\n");
        
        write("With great strain on your system and depleting the "
        +"rest of the saturation of your blood, you finally "
        +"evolve into a Fledgelig Vampire! No longer are you "
        +"bound to the shackles of a Vampire Spawn, but your "
        +"journey is just about to start. Great perils and "
        +"pitfalls awaits before you, for the road to becoming "
        +"a powerful vampire is long and dangerous. Only time "
        +"will tell the tales of your spoils and your failures.\n");
            
        return 1;
    }
    
    return 0;
}


public int
do_detect_dawn(string str)
{
    setuid();
    seteuid(getuid());
    
    object player = this_player();
    if (!objectp(player))
    {
        return 0;
    }
    
    object room = environment(player);
    if (!objectp(room) || !IS_ROOM_OBJECT(room))
    {
        return 0;
    }
    
    mixed * time_info = GENESIS_TIMEKEEPER->query_time(player);
    if (!pointerp(time_info))
    {
        notify_fail("For some reason, you simply cannot detect anything "
            + "from where you stand.\n");
        return 0;
    }
    
    if (environment(player)->query_prop(ROOM_I_VAMP_MELD) == 1)
    {
        object room2;
        
        room2 = environment(environment(player));
        
        string domain = lower_case(room2->query_domain());
        
        int hour = time_info[0];
    
        if (GENESIS_TIMEKEEPER->domain_hour_has_sunlight(domain, hour))
        {
            player->catch_tell("You sense that the sun is present above you! Take caution!\n");
            return 1;
        }
        
        // If it is night, we detect how many hours there are till day comes.
        int hours_until_dawn = 1;
        hour = (hour + 1) % 24;
        for (int i = 0; i < 24; ++i)
        {
            if (GENESIS_TIMEKEEPER->domain_hour_has_sunlight(domain, hour))
            {
                break;
            }
            
            ++hours_until_dawn;
            hour = (hour + 1) % 24;
        }
        
        string mesg = "You sense that ";
        switch (hours_until_dawn)
        {
        case 1:
            mesg += "the night is all but spent! Dawn approaches with terrible "
                + "speed!\n";
            break;
            
        case 2..4:
            mesg += "the night has begun to pass. Dawn approaches, albeit slowly.\n";
            break;
        
        case 5..8:
            mesg += "the night remains strong, and dawn is but a distant "
                + "threat.\n";
            break;

        default:
            mesg += "the night is strong, and dawn has not yet begun to "
                + "approach.\n";
            break;
        }
        
        player->catch_tell(mesg);
        return 1;    
    }

    string domain = lower_case(room->query_domain());
  
    
    int hour = time_info[0];
    
    if (GENESIS_TIMEKEEPER->domain_hour_has_sunlight(domain, hour))
    {
        player->catch_tell("You sense that the sun is present! Take caution!\n");
        return 1;
    }
    
    // If it is night, we detect how many hours there are till day comes.
    int hours_until_dawn = 1;
    hour = (hour + 1) % 24;
    for (int i = 0; i < 24; ++i)
    {
        if (GENESIS_TIMEKEEPER->domain_hour_has_sunlight(domain, hour))
        {
            break;
        }
        
        ++hours_until_dawn;
        hour = (hour + 1) % 24;
    }
    
    string mesg = "You sense that ";
    switch (hours_until_dawn)
    {
    case 1:
        mesg += "the night is all but spent! Dawn approaches with terrible "
            + "speed!\n";
        break;
        
    case 2..4:
        mesg += "the night has begun to pass. Dawn approaches, albeit slowly.\n";
        break;
    
    case 5..8:
        mesg += "the night remains strong, and dawn is but a distant "
            + "threat.\n";
        break;

    default:
        mesg += "the night is strong, and dawn has not yet begun to "
            + "approach.\n";
        break;
    }
    
    player->catch_tell(mesg);
    return 1;    
}


int
do_vampthirst()
{   
    int age = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()); 
    int current_bloodpool = VAMPIRES_MAPPINGS->query_thirst_gauge(this_player()->query_name());
    
    float max_bloodpool;
    
    switch(age)
    {
        //////////// VAMPIRE SPAWNS ///////////           
        case 0..24:
        max_bloodpool = 24.0;
        break;
        
        
        case 25..48:
        max_bloodpool = 48.0;
        break;
        
        
        case 49..72:
        max_bloodpool = 72.0;
        break;
        
        
        case 73..100:
        max_bloodpool = 100.0;
        break;
        
       
        case 101..250:
        max_bloodpool = 150.0;
        break;
        
        
        case 251..500:
        max_bloodpool = 200.0;
        break;
        
       
        case 501..1000:
        max_bloodpool = 250.0;
        break;
        
        
        case 1001..1440:
        max_bloodpool = 300.0;
        break;

        
        case 1441..1450:
        max_bloodpool = 350.0;
        break;



        //////////// FULL VAMPIRES ///////////
        case 1451..2000:
        max_bloodpool = 400.0;
        break;
        
       
        case 2001..3000:
        max_bloodpool = 450.0;
        break;
        
       
        case 3001..5000:
        max_bloodpool = 500.0;
        break;
        
       
        case 5001..7000:
        max_bloodpool = 550.0;
        break;
        
       
        case 7001..9000:
        max_bloodpool = 600.0;
        break;
        
        
        case 9001..11000:
        max_bloodpool = 700.0;
        break;
        
        
        case 11001..13000:
        max_bloodpool = 800.0;
        break;
        
       
        case 13001..15000:
        max_bloodpool = 900.0;
        break;
        
        
        case 15001..17529:
        max_bloodpool = 1000.0;
        break;
        
        
        case 17530..17540:
        max_bloodpool = 1200.0;
        break;
    }

    //float max_bloodpoolfloat = itof(max_bloodpool);
    float current_bloodpoolfloat = itof(current_bloodpool);

    float pool_90 = (max_bloodpool / 100.0) * 90.0;
    float pool_80 = (max_bloodpool / 100.0) * 80.0;
    float pool_70 = (max_bloodpool / 100.0) * 70.0;
    float pool_60 = (max_bloodpool / 100.0) * 60.0;
    float pool_50 = (max_bloodpool / 100.0) * 50.0;
    float pool_40 = (max_bloodpool / 100.0) * 40.0;
    float pool_30 = (max_bloodpool / 100.0) * 30.0;
    float pool_20 = (max_bloodpool / 100.0) * 20.0;
    float pool_10 = (max_bloodpool / 100.0) * 10.0;
    float pool_05 = (max_bloodpool / 100.0) * 5.0;
    float pool_02 = (max_bloodpool / 100.0) * 2.0;
    
    
    if (pool_90 < current_bloodpoolfloat)
    {
        write("Any further nourishment "
        +"consumption would prove gluttonous.\n");
         
         return 1;
    }

    if (pool_80 < current_bloodpoolfloat)
    {
         write("A feeling of balance and "
         +"satisfaction befalls you.\n");
         
         return 1;
    }
    
    if (pool_70 < current_bloodpoolfloat)
    {
         write("A distracting headache dully nudges you.\n");
         
         return 1;
    }
    
    if (pool_60 < current_bloodpoolfloat)
    {
         write("Brief fits of dizziness are "
         +"becoming too common an occurrence.\n");
         
         return 1;
    }
    
    if (pool_50 < current_bloodpoolfloat)
    {
         write("You are beginning to ache all "
         +"over and feel weak.\n");
         
         return 1;
    }
    
    if (pool_40 < current_bloodpoolfloat)
    {
         write("You cannot stop obsessing about "
         +"your next drink of sweet, coppery nectar.\n");
         
         return 1;
    }
    
    if (pool_30 < current_bloodpoolfloat)
    {
         write("Tremors and shuddering are "
         +"causing spasms in your muscles.\n");
         
         return 1;
    }
    
    if (pool_20 < current_bloodpoolfloat)
    {
         write("No longer sure of your "
         +"next move, you stand confused for a moment.\n");
         
         return 1;
    }
    
    if (pool_10 < current_bloodpoolfloat)
    {
         write("Your arms and legs are "
         +"alternating numbness as you move, further "
         +"exhausting you in waves.\n");
         
         return 1;
    }
    
    if (pool_05 < current_bloodpoolfloat)
    {
         write("Your vision pulsates and your "
         +"body is becoming unresponsive.\n");
         
         return 1;
    }
    
    if (pool_02 < current_bloodpoolfloat)
    {
         write("Nearly blind, your only thought is blood. \n");
         
         return 1;
    }
    
    write("Paralysis envelops you through starvation.\n");

    return 1;
}


int
do_vamptitle()
{

    int vampire_age_titles = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_real_name());
    
    int vamprank = VAMPIRES_MAPPINGS->query_vampires_rank(this_player()->query_name());
    
    switch(vampire_age_titles)
    {
        // Vampire spawn titles
        case 0..24:
        write("You are a Newborn Vampire Spawn.\n");
        break;
        
        case 25..48:
        write("You are a Fresh Vampire Spawn.\n");
        break;
                
        case 49..72:
        write("You are an Inexperienced Vampire Spawn.\n");
        break;
        
        case 73..100:
        write("You are a Hungering Vampire Spawn.\n");
        break;
        
        case 101..250:
        write("You are a Blooded Vampire Spawn.\n");
        
        if (vampire_age_titles > 200)
        {
            write("You are close to the next title.\n");
            break;
        }
        
        if (vampire_age_titles >= 101)
        {
            write("You are far away to the next title.\n");
            break;
        }

        break;
        
        case 251..500:
        write("You are a Marauding Vampire Spawn.\n");
        
        if (vampire_age_titles > 400)
        {
            write("You are close to the next title.\n");
            break;
        }
        
        if (vampire_age_titles >= 251)
        {
            write("You are far away to the next title.\n");
            break;
        }
        
        break;
        
        case 501..1000:
        write("You are a Vicious Vampire Spawn.\n");
        
        if (vampire_age_titles > 900)
        {
            write("You are very close to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 800)
        {
            write("You are close to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 750)
        {
            write("You are halfway to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 600)
        {
            write("You are far to the next title.\n");
            break;
        }
        
        if (vampire_age_titles >= 501)
        {
            write("You are extremely far away to the next title.\n");
            break;
        }
        break;
               
        case 1001..1449:
        write("You are a Senior Vampire Spawn.\n");
        
        if (vampire_age_titles > 1400)
        {
            write("You are very close to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 1300)
        {
            write("You are close to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 1200)
        {
            write("You are halfway to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 1100)
        {
            write("You are far to the next title.\n");
            break;
        }
        
        if (vampire_age_titles >= 1001)
        {
            write("You are extremely far away to the next title.\n");
            break;
        }
        break;
        
        case 1450:
        write("You are an Evolving Vampire Spawn.\nYou may now "
        +"evolve into a full vampire!\n");
        break;
        
  
        // Full vampire titles
        case 1451..2000:
        write("You are a Fledgling Vampire.\n");
        
        if (vamprank > 1)
        {
            vamprank = vamprank - 1;
            
            write("You have sired "+vamprank+" Vampire(s).\n");
        }
        
        if (vampire_age_titles > 1900)
        {
            write("You are very close to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 1800)
        {
            write("You are close to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 1700)
        {
            write("You are halfway to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 1600)
        {
            write("You are far to the next title.\n");
            break;
        }
        
        if (vampire_age_titles >= 1451)
        {
            write("You are extremely far away to the next title.\n");
            break;
        }
        break;
        
        case 2001..3000:
        write("You are an Apprentice Vampire.\n");
        
        if (vamprank > 1)
        {
            vamprank = vamprank - 1;
            
            write("You have sired "+vamprank+" Vampire(s).\n");
        }
        
        if (vampire_age_titles > 2900)
        {
            write("You are very close to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 2700)
        {
            write("You are close to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 2500)
        {
            write("You are halfway to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 2300)
        {
            write("You are far to the next title.\n");
            break;
        }
        
        if (vampire_age_titles >= 2001)
        {
            write("You are extremely far away to the next title.\n");
            break;
        }
        break;
        
        case 3001..5000:
        write("You are a Neonate Vampire.\n");
        
        if (vamprank > 1)
        {
            vamprank = vamprank - 1;
            
            write("You have sired "+vamprank+" Vampire(s).\n");
        }
        
        if (vampire_age_titles > 4700)
        {
            write("You are very close to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 4300)
        {
            write("You are close to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 4000)
        {
            write("You are halfway to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 3700)
        {
            write("You are far to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 3300)
        {
            write("You are very far to the next title.\n");
            break;
        }
        
        if (vampire_age_titles >= 3001)
        {
            write("You are extremely far away to the next title.\n");
            break;
        }
        break;
        
        case 5001..7000:
        write("You are a Scourge of the Night.\n");
        
        if (vamprank > 1)
        {
            vamprank = vamprank - 1;
            
            write("You have sired "+vamprank+" Vampire(s).\n");
        }
        
        if (vampire_age_titles > 6700)
        {
            write("You are very close to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 6000)
        {
            write("You are halfway to the next title.\n");
            break;
        }
        
        if (vampire_age_titles > 5700)
        {
            write("You are very far to the next title.\n");
            break;
        }
        
        if (vampire_age_titles >= 5001)
        {
            write("You are extremely far away to the next title.\n");
            break;
        }
        break;
        
        case 7001..9000:
        write("You are an Ancilla Vampire.\n");
        
        if (vamprank > 1)
        {
            vamprank = vamprank - 1;
            
            write("You have sired "+vamprank+" Vampire(s).\n");
        }
        
        if (vampire_age_titles > 8700)
        {
            write("You are very close to the next title.\n");
            break;
        }
       
        if (vampire_age_titles >= 7001)
        {
            write("You are very far away to the next title.\n");
            break;
        }
        break;
        
        case 9001..11000:
        write("You are a Higher Vampire.\n");
        
        if (vamprank > 1)
        {
            vamprank = vamprank - 1;
            
            write("You have sired "+vamprank+" Vampire(s).\n");
        }
               
        if (vampire_age_titles > 10900)
        {
            write("You are very close to the next title.\n");
            
            /*if (VAMPIRES_MAPPINGS->query_vampire_reputation(this_player()->query_name()) < 20)
            {
                write(">>You need higher reputation in order to ascend to Vampire Lord<<\n");
            }
            
            if (VAMPIRES_MAPPINGS->query_vamp_pathprogression(this_player()->query_name()) < 20)
            {
               write(">>You need higher standing in order to ascend to Vampire Lord<<\n");
            }*/
            
            break;
        }
 
        if (vampire_age_titles > 10001)
        {
            write("You are halfway to the next title.\n");
            break;
        }
               
        if (vampire_age_titles >= 9001)
        {
            write("You are extremely far away to the next title.\n");
            break;
        }
        break;
        
        case 11001..65000: 

        switch(vampire_age_titles)
        {
            case 11001..13000:
            write("You are not in position to obtain any higher rank yet.\n");
            break;
            
            case 13001..15000:
            write("You have sufficiently aged to obtain the Elder status.\n");
            break;
            
            case 15001..17000:
            write("You have sufficiently aged to obtain the Methuselah status.\n");
            break;
            
            case 17001..22000:
            write("You have sufficiently aged to obtain the Antediluvian status.\n");
            break;
            
            case 22001..30000:
            write("You have sufficiently aged to obtain the Progenitor status.\n");
            break;
        }        

        if (VAMPIRES_MASTER->is_vamp_progenitor(this_player()->query_real_name()) == 1)
        {
            write("You are the Progenitor of All Vampires.\n");
        }
        else if (VAMPIRES_MASTER->is_vamp_antediluvian(this_player()->query_real_name()) == 1)
        {
            write("You are an Antediluvian Vampire.\n");
        } 
        else if (VAMPIRES_MASTER->is_vamp_methuselah(this_player()->query_real_name()) == 1)
        {
            write("You are a Methuselah Vampire.\n");
        }
        else if (VAMPIRES_MASTER->is_vamp_elder(this_player()->query_real_name()) == 1)
        {
            write("You are an Elder Vampire.\n");   
        }
        else
        {
            write("You are a Vampire Lord.\n");
        }
        
        if (vamprank > 1)
        {
            vamprank = vamprank - 1;
            
            write("You have sired "+vamprank+" Vampire(s).\n");
        }
        
        break;
    }
    
    return 1;
}


int
do_vamptitlelist()
{
    write("   VAMPIRE RANKS\n");
    write("   ==========================\n");    
    write("   Progenitor of all Vampires\n");
    write("   --------------------------\n");
    write("   Antediluvian\n");
    write("   Methuselah\n");
    write("   Elder Vampire\n");
    write("   --------------------------\n");  
    write("   Vampire Lord\n");  
    write("   Higher Vampire\n");
    write("   Ancilla Vampire\n");
    write("   Scourge of the Night\n");
    write("   Neonate Vampire\n");
    write("   Apprentice Vampire\n");
    write("   Fledgling Vampire\n");
    write("            ~~\n");
    write("   Evolving Vampire Spawn\n");
    write("   Senior Vampire Spawn\n");
    write("   Vicious Vampire Spawn\n");
    write("   Marauding Vampire Spawn\n");
    write("   Blooded Vampire Spawn\n");
    write("   Hungering Vampire Spawn\n");
    write("   Inexperienced Vampire Spawn\n");
    write("   Fresh Vampire Spawn\n");
    write("   Newborn Vampire Spawn\n");
    write("\n");
    
    return 1;
}


int
do_unmask()
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
    {
        write("Bah! You are too confident in your skills and abilities "
        +"as a full vampire to bother masking your presence in such a "
        +"way.\n");
        
        return 1;
    }
    
    this_player()->set_unmask_presence();
    
    return 1;
}


int
do_vagecheck()
{
    int mem_thirst;
    int mem_gauge;
    
    mem_thirst = VAMPIRES_MAPPINGS->query_thirst_gauge(this_player()->query_name());        
    mem_gauge = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name());
       
    int min_age;
        
    switch(mem_gauge)
    {
        //////////// VAMPIRE SPAWNS BELOW ///////////
        
        // Over 12 blood to grow
        // Bloodcap at 24
        case 0..24:
        min_age = 12;
        break;
        
        // Over 28 blood to grow
        // Bloodcap at 48
        case 25..48:
        min_age = 28;
        break;
        
        // Over 44 blood to grow
        // Bloodcap at 72
        case 49..72:
        min_age = 44;
        break;
        
        // Over 70 blood to grow
        // Bloodcap at 100
        case 73..100:
        min_age = 70;
        break;
        
        // Over 105 blood to grow
        // Bloodcap at 150
        case 101..250:
        min_age = 105;
        break;
        
        // Over 160 blood to grow
        // Bloodcap at 200
        case 251..500:
        min_age = 160;
        break;
        
        // Over 200 blood to grow
        // Bloodcap at 250
        case 501..1000:
        min_age = 200;
        break;
        
        // Over 240 blood to grow
        // Bloodcap at 300
        case 1001..1440:
        min_age = 240;
        break;

        // Over 280 blood to grow
        // Bloodcap at 350
        case 1441..1450:
        min_age = 280;
        break;


        //////////// FULL VAMPIRES BELOW ///////////
      
        // Over 320 blood to grow
        // Bloodcap at 400
        case 1451..2000:
        min_age = 320;
        break;
        
        // Over 360 blood to grow
        // Bloodcap at 450
        case 2001..3000:
        min_age = 360;
        break;
        
        // Over 400 blood to grow
        // Bloodcap at 500
        case 3001..5000:
        min_age = 400;
        break;
        
        // Over 450 blood to grow
        // Bloodcap at 550
        // 100 difference
        case 5001..7000:
        min_age = 450;
        break;
        
        // Over 500 blood to grow
        // Bloodcap at 600
        // 100 difference
        case 7001..9000:
        min_age = 500;
        break;
        
        // Over 600 blood to grow
        // Bloodcap at 700
        // 100 difference
        case 9001..11000:
        min_age = 600;
        break;
        
        // Over 700 blood to grow
        // Bloodcap at 800
        // 100 difference
        case 11001..13000:
        min_age = 700;
        break;
        
        // Over 800 blood to grow
        // Bloodcap at 900
        // 100 difference
        case 13001..15000:
        min_age = 800;
        break;
        
        // Over 900 blood to grow
        // Bloodcap at 1000
        // 100 difference
        case 15001..17000:
        min_age = 900;
        break;
        
        // Over 1000 blood to grow
        // Bloodcap at 1200
        // 200 difference
        case 17001..23000:
        min_age = 1000;
        break;
    }
    
    if (mem_thirst > min_age)
    {
        if (VAMPIRES_MASTER->is_aging_check(this_player()->query_name()))
        {
            write("You are sufficiently saturated with blood to ensure "
            +"continued development through aging, but there are other "
            +"factors that prevents this from happening that you "
            +"need to address.\n");
        }
        else
        {
            write("You are sufficiently saturated with blood to ensure "
            +"continued development through aging.\n");
        }
        
        return 1;
    }
    
    write("Your blood is not sufficiently satured for continued "
    +"development through aging. You must feed more, or risk stagnation!\n");
    
    return 1;
}


int
do_spawntimer()
{
    int spawntimer;
    int vamp_gauge;
    
    int spawndifference;

    vamp_gauge = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name());
    spawntimer = VAMPIRES_MASTER->query_vampirespawn_timer(this_player()->query_name());
    
    spawndifference = vamp_gauge - spawntimer;
    
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 1)
    {
        return 0;
    }
    
    switch(spawndifference)
    {
        case 1..3:
        write("Your Sire Vorador is searching for you. Immediately increase "
        +"your progression or be Destroyed!\n");
        break;
        
        case 4..10:
        write("Your Sire Vorador is furious about your lack of progression.\n");
        break;
        
        case 11..20:
        write("Your Sire Vorador demands that you increase your efforts immediately.\n");
        break;
        
        case 21..30:
        write("Your Sire Vorador thinks your progression is mediocre.\n");
        break;
        
        case 31..100:
        write("Your Sire Vorador is somewhat satisfied with your progression.\n");
        break;
        
        case 101..200:
        write("Your Sire Vorador is rather satisfied with your progression.\n");
        break;
        
        case 201..400:
        write("Your Sire Vorador is very satisfied with your progression.\n");
        break;
        
        case 401..99999:
        write("Your Sire Vorador is extremely satisfied with your progression.\n");        
        break;
    }

    return 1;
}  


int
do_vampsire()
{

    string sire = this_player()->query_sire();
    
    
    write("Your Sire is: "+capitalize(sire)+".\n");
 
    return 1;
}  


int
do_vampthrall()
{
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 0)
    {
        return 0;
    }

    string thrall = this_player()->query_thrall();
    
    if (thrall == 0)
    {
        write("You don't have any thralls under your domination.\n");
 
        return 1;
    }
       
    write("Your thrall is: "+capitalize(thrall)+".\n");
 
    return 1;
}


int do_vampthrall_remove()
{
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 0)
    {
        return 0;
    }
    
    if (!this_player()->query_thrall())
    {
        write("You don't have a thrall.\n");
        
        return 1;
    }
    
    if (present("vampthrall_coold_obj", this_player()))
    {
        write("You can't remove your thrall before the "
        +"thrallcurse expires.\n");
        
        return 1;
    }
    
    THRALL_MANAGER->remove_thrall(this_player()->query_name());
    
    write("You release your thrall from your service.\n");
        
    return 1;
}


void do_vampthrall_offer2(int response, object drainer, object drainee);


int do_vampthrall_offer(string arg)
{
    object *oblist, who, drain_prop, yn_ob;
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 0)
    {
        return 0;
    }

    if (!strlen(arg) || !sizeof(oblist = parse_this(arg, "%l")))
    {
        notify_fail(capitalize(query_verb()) + " whom?\n");
        
        return 0;
    }

    who = oblist[0];
  
    if (this_player()->query_thrall())
    {
        write("You already have a thrall.\n");
        return 1;
    }
    
    if (who->query_average() < 160)
    {
        write("That individual is too small to be your thrall.\n");
        return 1;
    }
    
    if (this_player()==who->query_prop(LIVE_O_OFFERED_THRALL))
    {
        do_vampthrall_offer2(1,this_player(),who);
        
        return 1;
    }

    setuid();
    seteuid(getuid());

    // Ask the target if he/she wants to become a thrall.
    if (yn_ob = clone_object(YES_NO_OBJECT))
    {
        /* When yn_ob gets a "yes" or "no" answer, or it times out,
         * it reports back to this object with the answer
         */
        if (!yn_ob->get_answer(who, 
            &do_vampthrall_offer2(, this_player(), who), 20.0))
        {
            // something failed in yn_ob...remove it.
            yn_ob->remove_object();
        }
        else
        {
            write("You ask " + who->query_the_name(this_player()) +
                " to become your thrall.\n");
                
            who->catch_tell(this_player()->query_The_name(who) +
                " asks if " + PRO(this_player()) + " you want "
                +"to become a vampire familiar. Do you accept or refuse?\n");
                
            tell_others(QCTNAME(this_player()) + " asks " + QTNAME(who) +
                " something.\n", ({ who, this_player() }));
  
            return 1;
        }
    }

    /* yn_ob won't clone...oh well.... */
    write("Something is wrong. Contact Vampire GM.\n");

    return 1;
}


void
do_vampthrall_offer2(int response, object drainer, object drainee)
{
    string name = drainee->query_The_name(drainer);
    
    if (!drainee || !drainer || 
        (environment(drainee) != environment(drainer)))
    {
        write("Your potential thrall is not here.\n");
        return;
    }
  
    if (!response)
    {
        drainer->catch_tell(name + " denied your request to become a "
        +"thrall.\n");
        
        drainee->catch_tell("You deny the request.\n");
        
        return;
    }
  
    if (response < 0)
    {
        drainer->catch_tell(name + " failed to respond to your request " +
            "for thralldom.\n");
   
        return;
    }
   
    set_this_player(drainer);
    
    write(drainee->query_The_name(drainer) + " becomes your thrall.\n");
        
    drainee->catch_tell("You become the vampire familar of " 
    + drainer->query_the_name(drainee)+".\n");
    
    THRALL_MANAGER->set_thrall(drainer->query_name(), drainee->query_name());
}


int
do_thrallassess(string str)
{
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 0)
    {
        return 0;
    }
    
    if (!str)
    {
        write("Vthrallassess whom?\n");
        
        return 1;
    }
    
    string thrall = (this_player()->query_thrall());
    
    if (thrall == 0)
    {
        write("You don't have a thrall.\n");
        
        return 1;
    }
       
    object target = find_player(str);
            
    if (target == 0)
    {
        write("That individual is not in the realms.\n");
        
        return 1;
    }
    
    if (target->query_real_name() == thrall)
    {
        int poolvalue = VAMPIRES_MAPPINGS->query_thrall_pool(target->query_name());
    
        if (poolvalue == 2)
        {
            this_player()->catch_tell("You feel that your thrall is ready "
            +"to be harvested!\n");
            
            return 1;
        }
        
        if (poolvalue == 3)
        {
            this_player()->catch_tell("Your thrall is no longer eligible for "
            +"harvest.\n");
            
            return 1;
        }
        
        this_player()->catch_tell("Your thrall is not ready for "
        +"harvest yet.\n");
              
        return 1;
    }
    
    write("That individual is not your thrall.\n");

    return 1;
}


int
do_thrallcurse(string str)
{
    setuid();
    seteuid(getuid());
    
    object curse_object;
    object coold_object;

    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 0)
    {
        return 0;
    }
    
    if(!str)
    { 
        write("vthrallcurse whom?\n");
        return 0;
    }
    
    if (!this_player()->query_thrall())
    {
        write("You don't have a thrall.\n");
        
        return 1;
    }
    
    string thrall_check = (this_player()->query_thrall());
    
    object target = find_player(str);
    
    if (target->query_real_name() == thrall_check)
    {    
        if (!present("vampthrall_amp_obj", target))
        {
            if (VAMPIRES_MAPPINGS->query_thrall_pool(target->query_name()) == 3)
            {
                this_player()->catch_tell("Your thrall can no longer generate "
                +"points of Immportality - this option has been already been "
                +"spent earlier.\n");
                
                return 1;
            }   
            
            this_player()->catch_tell("You curse your thrall! Your thrall will "
            +"now start the process of generating points of immortality.\n");
            
            target->catch_tell("You feel a strange sensation of being "
            +"supernaturally cursed and weakened by your master.\n"); 
            
            curse_object = clone_object(VAMPIRES_GUILD_DIR +"obj/thrall_curse");
            curse_object->move(target, 1);
            curse_object->start_me();
            
            coold_object = clone_object(VAMPIRES_GUILD_DIR +"obj/thrall_cooldown");
            coold_object->move(this_player(), 1);
            coold_object->start_me();
            
            return 1;
        }
        
        this_player()->catch_tell("Your thrall is already cursed.\n");
        
        return 1;
    }
    
    if (target == 0)
    {
        write("Your thrall is not in the realms.\n");
        
        return 1;
    }
    
    write("That is not your thrall.\n");

    return 1;
}


int do_vampthrall_activate(string str)
{
    object tp = this_player(); 
    object vamp_presence;
    object env = environment(tp);   
    object paralyze;
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_2(this_player()->query_name()) == 0)
    {
        return 0;
    }
    
    if (!str)
    {
        write("To whom?\n");
        
        return 1;
    }
    
    string thrall_check = (this_player()->query_thrall());
    
    object target = find_player(str);
	
	if (environment(target)->query_prevent_snoop() == 1)
    {
		write("Your thrall is somewhere unreachable by this ability.\n");
		
		return 1;
	}
    
    if (target->query_real_name() == thrall_check)
    {
        int result;
    
        setuid();
        seteuid(getuid());
        
        // Now do your stuff!
        vamp_presence = clone_object(VAMPIRES_GUILD_DIR  
        +"specials/obj/vampire_presence2");
        vamp_presence->set_target(target);
        vamp_presence->set_duration(99999);

        vamp_presence->move_living("M", env);

        paralyze = clone_object(VAMPIRES_GUILD_DIR  
        +"obj/thrall_paralysis");
        paralyze->set_stop_fun("remove_link");
        paralyze->set_stop_object(vamp_presence);
        paralyze->set_stop_message("You end the connection with your "
        +"thrall. You can move again.\n");
        paralyze->set_fail_message("You are busy focusing on the "
        +"connecting to your "
        +"thrall. To end it, type 'vthrallscryend'\n");
        paralyze->set_stop_verb("vthrallscryend");
        
        paralyze->set_remove_time(99999);

        vamp_presence->set_paralyze(paralyze);
        
        if (paralyze->move(tp))
            paralyze->move(tp, 1);

        
        vamp_presence->set_vampire(tp);
              
        vamp_presence->start_watch();
        
        return 1;
    }
    
    write("That individual is not in the reams, or the individual is not your thrall.\n");
    
    return 1;
}


int do_vampchild_activate(string str)
{
    object tp = this_player(); 
    object vamp_presence2;
    object env = environment(tp);   
    object paralyze;
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) == 0)
    {
        return 0;
    }
    
    if (!str)
    {
        write("To whom?\n");
        
        return 1;
    }
    
    object target = find_player(str);
    
    if (target == 0)
    {
        this_player()->catch_tell("That person is not in the realms.\n");
        
        return 1;
    }
    
    string qsire = capitalize(target->query_sire());
    
    if (qsire != this_player()->query_name())
    {
        this_player()->catch_tell("That person is not your child.\n");
    
        return 1;
    }
	
    int result;

    setuid();
    seteuid(getuid());
    
    // Now do your stuff!
    vamp_presence2 = clone_object(VAMPIRES_GUILD_DIR  
    +"specials/obj/vampire_presence");
    vamp_presence2->set_target(target);
    vamp_presence2->set_duration(99999);

    vamp_presence2->move_living("M", env);

    paralyze = clone_object(VAMPIRES_GUILD_DIR  
    +"obj/thrall_paralysis");
    paralyze->set_stop_fun("remove_link");
    paralyze->set_stop_object(vamp_presence2);
    paralyze->set_stop_message("You end the connection with your "
    +"child. You can move again.\n");
    paralyze->set_fail_message("You are busy focusing on the "
    +"connecting to your "
    +"child. To end it, type 'vchildscryend'\n");
    paralyze->set_stop_verb("vchildscryend");
    
    paralyze->set_remove_time(99999);

    vamp_presence2->set_paralyze(paralyze);
    
    if (paralyze->move(tp))
        paralyze->move(tp, 1);
  
    vamp_presence2->set_vampire(tp);
          
    vamp_presence2->start_watch();
    
    return 1;
}


void drink2(int response, object drainer, object drainee);

varargs void
tell_others(string str, object *exclude)
{
    object *players;

    players = all_inventory(environment(this_player())) - exclude;
    players = FILTER_PLAYERS(FILTER_CAN_SEE_IN_ROOM(players));

    if (sizeof(players))
    {
        players->catch_msg(str);
    }
}


int
can_drink(object drainer, object drainee)
{
    object drain_prop;
    
    /*if (present("_vampire_drain_cooldown_ob", drainee))
    {
        drainer->catch_tell("That individual is too weak for a second drain. "
        +"Try again later!\n");
        return 0;
    }*/

    if (drainer->query_vamp_drain())
    {
        drainer->catch_tell("You are already draining someone!\n");
        return 0;
    }

    if (drain_prop = drainee->query_prop(LIVE_O_VAMP_DRAINER) &&
        (drain_prop != drainer))
    {
        drainer->catch_tell(capitalize(PRO(drainee)) +
            " is already in someone's embrace.\n");
        return 0;
    }

    if (!drainer->can_vamp_drink(drainer, drainee))
    {
        return 0;
    }

    // Vampires should not be able to drink from NPCs. They need to
    // earn their blood through fighting. November 2009 - Petros
    if (!drainer->query_npc() && drainee->query_npc())
    {
        drainer->catch_msg(QCTNAME(drainee) + " does not offer "
            + drainee->query_possessive() + " blood to you.\n");
        return 0;
    }
  
    return 1;
}


int
drink(string arg)
{
    object *oblist, who, drain_prop, yn_ob;
    
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) == 0)
    {
        return 0;
    }

    if (!strlen(arg) || !sizeof(oblist = parse_this(arg, "[from] [the] %l")))
    {
        notify_fail(capitalize(query_verb()) + " from whom?\n");
        return 0;
    }

    who = oblist[0];
    
    /*if (present("_vampire_drain_cooldown_ob", who))
    {
        this_player()->catch_tell("That individual is too weak for a second drain. "
        +"You must wait until sufficient strenght is recovered!\n");
        
        return 1;
    }*/
  
    if (!can_drink(this_player(), who))
    {
        return 1;
    }

    who->hook_asked_blood(TP);

    if (this_player()==who->query_prop(LIVE_O_OFFERED_BLOOD))
    {
        drink2(1,this_player(),who);
        return 1;
    }

    setuid();
    seteuid(getuid());

    // Ask the target if he will give blood.
    if (yn_ob = clone_object(YES_NO_OBJECT))
    {
        /* When yn_ob gets a "yes" or "no" answer, or it times out,
         * it reports back to this object with the answer
         */
        if (!yn_ob->get_answer(who, 
            &drink2(, this_player(), who), 20.0))
        {
            // something failed in yn_ob...remove it.
            yn_ob->remove_object();
        }
        else
        {
            write("You ask " + who->query_the_name(this_player()) +
                " if you may savor some of " + POSS(who) +
                " warm blood.\n");
                
            who->catch_tell(this_player()->query_The_name(who) +
                " asks if " + PRO(this_player()) + " may savor some " +
                "of your warm blood.  Do you accept or refuse?\n");
                
            tell_others(QCTNAME(this_player()) + " asks " + QTNAME(who) +
                " something.\n", ({ who, this_player() }));
  
            return 1;
        }
    }

    /* yn_ob won't clone...oh well.... */
    write("For some reason you can't bring yourself to drink any of " +
        LANG_POSS(who->query_the_name(this_player())) + " blood.\n");

    return 1;
}


void
drink2(int response, object drainer, object drainee)
{
    string name = drainee->query_The_name(drainer);
  
    if (!drainee || !drainer || 
        (environment(drainee) != environment(drainer)))
    {
        drainer->release_vamp_drainee(1);
        
        return;
    }
  
    if (!response)
    {
        drainer->catch_tell(name + " denied your request for " +
            POSS(drainee) + " blood.\n");
            
        drainer->release_vamp_drainee(1);
        return;
    }
  
    if (response < 0)
    {
        drainer->catch_tell(name + " failed to respond to your request " +
            "for " + POSS(drainee) + " blood.\n");
            
        drainer->release_vamp_drainee(1);
        return;
    }
  
    if (!can_drink(drainer, drainee))
    {
        drainer->release_vamp_drainee(1);
        return;
    }
  
    set_this_player(drainer);
    write(drainee->query_The_name(drainer) + " bends " + POSS(drainee) +
        " head to the side, exposing " + POSS(drainee) + " neck. You " +
        "tightly press your lips against " + POSS(drainee) + " flesh and"+ 
        " gently bite into " + POSS(drainee) + " flesh, easily piercing " +
        POSS(drainee) + " skin with your fangs.\n");
        
    drainee->catch_tell("As " + drainer->query_the_name(drainee) +
        " moves toward your exposed neck, " + POSS(drainer) +
        " eyes meet yours, and all senses are lost in " + POSS(drainer) +
        " entrancing gaze. Suddenly you are overcome with a rush " +
        "of ecstacy as " + POSS(drainer) + " cold lips press against " +
        "your neck and " + POSS(drainer) + " fangs pierce your skin.\n");
        
    tell_others(QCTNAME(drainee) + " bends " + POSS(drainee) +
        " head to the side, exposing " + POSS(drainee) + " neck. " +
        capitalize(PRO(drainee)) + " closes " +  POSS(drainee) + " eyes as " +
        QTNAME(drainer) + " takes " + OBJ(drainee) + " in " +
        POSS(drainer) + " arms, pressing " + POSS(drainer) +
        " lips tightly against " + POSS(drainee) + " neck. It almost " +
        "seems as if you can hear the sound of " + POSS(drainee) +
        " skin breaking as " + PRO(drainer) + " bites into " +
        POSS(drainee) + " flesh.\n", ({ drainer, drainee }));
  
    drainer->stop_fight(({ drainee }));
    drainee->stop_fight(({ drainer }));
  
    /* begin drinking */
    drainer->start_vamp_drink(drainee);
}


int remove_cling_cooldown()
{
    write("Cling is ready again.\n");
    
    this_player()->remove_prop(CLING_COOLDOWN);
    
    return 1;
}


int break_cling()
{
    this_player()->command("stop cling");
    
    set_alarm(20.0, 0.0, &remove_cling_cooldown());
    
    return 1;
}


int stop_cling(object who)
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
    {
        return 0;
    }
    
    if (who->query_prop(VAMP_O_CLING))
    {
        who->remove_prop(VAMP_O_CLING);
      
        write("You stop following your prey.\n");
      
        return 1;
    }
  
    notify_fail("You're not following anyone.\n");
  
    return 0;
}


int do_cling(string arg)
{
    object who, sh, *oblist;
    
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
    {
        return 0;
    }

    notify_fail("Cling to whom?\n");

    if (!strlen(arg))
    {
        if (!(who = TP->query_attack()))
        {
          return 0;
        }
    }
    else if (!sizeof(oblist = parse_this(arg, "[to] [the] %l")))
    {
        return 0;
    }
    else if (sizeof(oblist) > 1)
    {
        notify_fail("You will have to be more specific.\n");
        return 0;
    }
    else
    {
        who = oblist[0];
    }
    
    // PVP abilities offline.
   // TP->catch_msg("Ability offline atm.\n");
    
    return 1;
    
    if (TP->query_prop(CLING_COOLDOWN) == 1)
    {
        TP->catch_msg("Cling is not yet ready. Be patient.\n");
        
        return 1;
    }
    

    who->remove_prop(VAMP_O_CLING);

    TP->catch_msg("You start to follow "+QTNAME(who)+".\n");

    setuid();
    seteuid(getuid());

    if (!who->query_cling_followers() &&
       (sh = clone_object(VAMPIRES_GUILD_DIR + "shadows/cling_sh")))
    {
        if (!sh->shadow_me(who))
        {
            sh->remove_shadow();
        }
    }

    who->add_cling_follower(TP);
    
    TP->add_prop(CLING_COOLDOWN, 1);
    
    set_alarm(10.0, 0.0, &break_cling());
      
    return 1;
}


/*
 * Function name: sniff_now
 * Description:   Actually perform the sniffing
 * Arguments:     pl - the sniffer
 *                skill - the sniffing skill used
 */
void
sniff_now(object player, int track_skill)
{
    string *sniff_arr, * track_arr,
            track_result = "You do not find any tracks.\n",
            sniff_result = "You do not smell any fresh blood.\n",
            dir,
           *dir_arr,
            race,
           *races = RACES + ({ "animal" });
    int     i;
    mixed  *exits;

    track_arr = environment(TP)->query_prop(ROOM_S_DIR);
    sniff_arr = environment(TP)->query_prop(ROOM_S_BLOOD_DIR);

    track_skill /= 2;
    track_skill += random(track_skill);
    

    if (CAN_SEE_IN_ROOM(player) && pointerp(track_arr) && track_skill > 0)
    {
        dir = track_arr[0];
        if (dir == "X" || dir == "M")
            dir = "nowhere";
        if (strlen(dir)>3)
        {
            dir_arr = explode(dir," ");
            if (dir_arr[0] != "the" && dir_arr[0]!="down")
            dir = "the " + dir;
        }
        race = track_arr[1];

        track_result = "Your heightened senses notice that tracks ";

        switch(track_skill)
        {
            case  1..10:
                track_result+="are present.\n";
                break;
            case 11..20:
                if(random(2))
                {
                    exits = environment(player)->query_exit();
                    if(i = sizeof(exits))
                        dir = exits[random(i/3)*3+1];
                }
                track_result += "are probably leading towards " + 
                dir + ".\n";
                break;
            case 21..50:
                track_result += "are leading towards " + dir + ".\n";
                break;
            case 51..75:
                if(random(2))
                    race = one_of_list(races);
                track_result += "were probably made by " +LANG_ADDART(race) +
                    " and are leading towards " + dir + ".\n";
                break;
            case 76..150:
                track_result += "were made by " +LANG_ADDART(race) +
                    " and are leading towards " + dir + ".\n";
                break;
        }
    }

    if (pointerp(sniff_arr) && sniff_arr[2]>time()-TRAIL_LOSS_TIME
        && track_skill> 0)
    {
        dir = sniff_arr[0];
        if (dir == "X" || dir == "M")
            dir = "nowhere";

        if (strlen(dir)>3)
        {
            dir_arr = explode(dir," ");
            if (dir_arr[0] != "the" && dir_arr[0] != "down")
            dir = "the " + dir;
        }
        race = sniff_arr[1];

        if (pointerp(track_arr))
        {
            sniff_result = "You also smell a trail of fresh ";
        }
        else
        {
            sniff_result = "You smell a trail of fresh ";
        }

        switch(track_skill)
        {
            case  1..10:
                sniff_result+="blood.\n";
                break;
            case 11..20:
                if(random(2))
                {
                    exits = environment(player)->query_exit();
                    if(i = sizeof(exits))
                        dir = exits[random(i/3)*3+1];
                }
                sniff_result += "blood likely leading towards "+ 
                dir + ".\n";
                break;
            case 21..50:
                sniff_result += "blood leading towards " + dir + ".\n";
                break;
            case 51..150:
                sniff_result += race + " blood leading towards " + 
                dir + ".\n";
                break;
        }
    }

    object tp=TP;
    set_this_player(player);
    player->catch_msg(track_result);
    player->catch_msg(sniff_result);
    player->remove_prop(LIVE_S_EXTRA_SHORT);
    allbb(" rises again.");
    set_this_player(tp);
    return;
}


/*
 * Function name: sniff_room
 * Description:   Someone looks for sniffs in this room
 */
void
sniff_room()
{
    int     time,
            track_skill;
    object  paralyze;
    
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) < 500)
    {
        write("What?\n");
        return;
    }

    time = environment(this_player())->query_prop(OBJ_I_SEARCH_TIME);
    if (time < 1)
        time = 10;
    else
        time += 5;

    track_skill = this_player()->query_skill(SS_TRACKING);
    time -= track_skill/10;

    if (time < 1)
        sniff_now(this_player(), track_skill);
    else
    {
        setuid();
        seteuid(getuid());
        set_alarm(itof(time-1), 0.0, &sniff_now(this_player(), 
        track_skill));
        paralyze = clone_object("/std/paralyze");
        paralyze->set_standard_paralyze("sniffing");
        paralyze->set_stop_fun("stop_sniff");
        paralyze->set_stop_verb("stop");
        paralyze->set_stop_message("You stop searching for your prey.\n");
        paralyze->set_remove_time(time);
        paralyze->set_fail_message("You are busy searching for your "+
        "prey.  You must 'stop' to do something else.\n");
        paralyze->move(this_player(),1);
    }
 }


/*
 * Function name: stop_sniff
 * Description:   interrupt sniffing
 * Arguments:
 * Returns:
 */
varargs int
stop_sniff(mixed arg)
{
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) < 500)
    {
        return 0;
    }
    
    if (!objectp(arg))
    {
        mixed *calls = get_all_alarms();
        mixed *args;
        int i;

        for (i = 0; i < sizeof(calls); i++)
        {
            if (calls[i][1] == "sniff_now")
            {
                args = calls[i][4];
                if (args[0] == this_player())
                    remove_alarm(calls[i][0]);
            }
        }
    }
    allbb(" stops studying the ground.");
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);

    return 0;
}


/*
 * Function name: track
 * Description:   look for tracks
 * Argument:      str - the string given to the command
 * Returns:       0 - failure
 */
int
sniff(string str)
{
    object  room = environment(this_player());
    
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) < 500)
    {
        return 0;
    }

    if (this_player()->query_attack())
    {
        notify_fail("But you are in the middle of a fight!\n");
        return 0;
    }

    if (stringp(str) &&
        (str != "here"))
    {
        notify_fail("Sniff where?\n");
        return 0;
    }

    if (!room->query_prop(ROOM_I_IS))
    {
        notify_fail("You cannot look for your prey here!\n");
        return 0;
    }

    write("Using your preternatural senses, you study the room looking "+
    "for signs of your prey.\n");

    allbb(" studies the ground intently." );  

    this_player()->add_prop(LIVE_S_EXTRA_SHORT, ", kneeling on the ground");

    sniff_room();
    return 1;
}


int
sense(string str)
{
    
    if (VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name()) < 1200)
    {
        return 0;
    }
    
    if (MASTER_OB(ENV(TP))==ROOM_DIR+"coffin")
    {
        object * targets=FILTER_LIVE(all_inventory(ENV(ENV(TP))));
        targets=filter(targets,&operator(==) (0) 
                @ &->query_prop(LIVE_I_UNDEAD));
        if (sizeof(targets))
        {
            write("You hear the " +
            (sizeof(targets)==1 ? "heartbeat" : "heartbeats") +
            " of "+ LANG_NUM2WORD(sizeof(targets)) + 
            (sizeof(targets)==1 ? " mortal" : " mortals") +
            " from outside your coffin.\n");
        }
        else
        {
            write("You hear nothing from outside your coffin.\n");
        }
        return 1;
    }
    
    mixed * exits=ENV(TP)->query_exit();
    if (!sizeof(exits))
    {
        write("You do not sense any prey nearby.\n");
        return 1;
    }
    if (TP->query_attack())
    {
        write("You are too busy fighting to listen for sounds of life.\n");
        return 1;
    }
    
    int found_room=0;
    for (int i=0;i<sizeof(exits);i+=3)
    {
        object room=find_object(exits[i]);
        if (!room)
            continue;
        object * targets=FILTER_LIVE(all_inventory(room));
        targets=filter(targets,&operator(==) (0) 
                @ &->query_prop(LIVE_I_UNDEAD));
        if (sizeof(targets))
        {
            write("You hear the sound" +
            " of "+ LANG_NUM2WORD(sizeof(targets)) + " " +
            (sizeof(targets)==1 ? "heartbeat" : "heartbeats") +
            " from the "+ exits[i+1]+ " exit.\n");
            found_room=1;
        }
    }
    
    if (!found_room)
    {
        write("You do not sense any prey nearby.\n");
    }
    return 1;
}


public int
do_vampimmortality_occ()
{
    if (VAMPIRES_MASTER->is_occ_vampires(this_player()->query_name()) == 0)
    {
        return 0;
    }
    
    int level_immortality;
    int imm_cap;
    
    int cappy;
    
    level_immortality = VAMPIRES_MAPPINGS->query_vampires_resilience(this_player()->query_name());
    
    imm_cap = VAMPIRES_MAPPINGS->query_vampires_gauge(this_player()->query_name());
    
    switch (imm_cap)
    {
        case 1451..3000:
        cappy = 2;
        break;
        
        case 3001..7000:
        cappy = 3;
        break;
        
        case 7001..11000:
        cappy = 5;
        break;
        
        case 11001..15000:
        cappy = 7;
        break;
        
        case 15001..999000:
        cappy = 9;
        break;
    }
    
    write("You have "+level_immortality
    +" immortality points.\nAt your current age, you can "
    +"only have "+cappy+" points in total.\n");
        
    return 1;
}


int
do_vamp_turn_occ()
{
    if (VAMPIRES_MAPPINGS->query_vampire_ability_occ_1(this_player()->query_name()) == 0)
    {
        return 0;
    }
    
    if (VAMPIRES_MASTER->occ_active_vamp_members_check() > 3)
    {
        write("The Vampire Nation has decreed that with the current "
        +"number of active vampires in the realms, creating new ones "
        +"are strictly forbidden (This is automatically regulated).\n");
        
        return 1;
    }
    
    if (this_player()->query_prop(VAMP_TURN_ON) == 1)
    {
        this_player()->remove_prop(VAMP_TURN_ON);
        
        write("You will no longer attempt to turn victims "
        +"into full vampires.\n");
        
        return 1;
    }
    
    write("You will now attempt to turn victims "
    +"into full vampires.\n");
    
    this_player()->add_prop(VAMP_TURN_ON, 1);

    return 1;
}


