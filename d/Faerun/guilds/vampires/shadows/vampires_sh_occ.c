/* /d/Faerun/guilds/vampires/shadows/vampires_sh_occ.c
 *
 * Guildshadow for Vampires of Faerun, Nerull 2020
 *
 */

inherit "/std/guild/guild_occ_sh";
inherit "/lib/commands";

#include <macros.h>
#include <const.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <filter_funs.h>
#include <composite.h>
#include "/std/combat/combat.h"
#include "../guild.h"


/*
 * Global variables
 */
public int      query_guild_not_allow_join_occ(object player, 
                string type, string style, string name);
static int      query_guild_keep_player(object ob);
public void     init_occ_shadow(string str);


static string *vamp_titles = ({  "",
                            "Barbaric",
                            "Beast",
                            "Butcher",
                            "Calculating",
                            "Cannibal",
                            "Cantankerous",
                            "Chosen",
                            "Coercive",
                            "Conquered",
                            "Conqueror",
                            "Constant",
                            "Critical",
                            "Curmudgeon",
                            "Cursed",
                            "Dandy",
                            "Defiler",
                            "Demanding",
                            "Demolisher",
                            "Old",
                            "Destitute",
                            "Destroyer",
                            "Disturbed",
                            "Ecstatic",
                            "Eldest",
                            "Entrapper",
                            "Erratic",
                            "Exterminator",
                            "Feared",
                            "Forceful",
                            "Frantic",
                            "Heartless",
                            "Horrendous",
                            "Horrible",
                            "Indomitable",
                            "Insatiable",
                            "Insinuator",
                            "Intruder",
                            "Impaler",
                            "Liquidator",
                            "Little",
                            "Malicious",
                            "Manipulator",
                            "Mauler",
                            "Meek",
                            "Meticulous",
                            "Mild",
                            "Nameless",
                            "Nemesis",
                            "Obliterator",
                            "Obstructer",   
                            "Obtuse",
                            "Oppressor",
                            "Parched",
                            "Plague",
                            "Quarrelsome",
                            "Ravenous",
                            "Reaper",
                            "Rectifier",
                            "Relentless",
                            "Repressor",
                            "Repulsive",
                            "Ruiner",
                            "Ruthless",
                            "Scoundrel",
                            "Scourge",
                            "Seditious",
                            "Sedulous",
                            "Slasher",
                            "Sot",
                            "Spectacular",
                            "Subjugator",
                            "Temptress",
                            "Terrible",
                            "Tireless",
                            "Tortured",
                            "Torturer",
                            "Tremendous",
                            "Tyrant",
                            "Ubiquitous",
                            "Uncrowned",
                            "Unexpected",
                            "Unseen",
                            "Vanquisher",
                            "Vengeful",
                            "Voracious",                          
                            "Pale Knight",
                            "Feral Knight",
                            "Beautiful",
                            "Betrayer",
                            "Claw",
                            "Debonair",
                            "Decadent",
                            "Exile",
                            "Ghastly",
                            "Grim",
                            "Grip",
                            "Hellspawn",
                            "Hunter",
                            "Just",
                            "Languisher", 
                            "Lazy",
                            "Mesmerizing",
                            "Outlaw",
                            "Ravisher",
                            "Ravishing",                           
                            "Silver-tongue",
                            "Treacherous",
                            "Twisted",
                            "Vile",
                            "",                             
});
// 0 - 39


int
query_guild_title_nr()
{
    return VAMPIRES_MAPPINGS->query_vamp_title(shadow_who->query_name());
}


string
query_guild_title_occ()
{
    int titlenr;
    int gender;
    
    //titlenr = VAMPIRES_MAPPINGS->query_vamp_title(this_player()->query_name());
    
    gender = shadow_who->query_gender();
    
    titlenr = shadow_who->query_guild_title_nr();
    
    if (query_guild_title_nr() == 110)
    {
        if (gender == 0)
        {
            return "Blood Prince";
        }
        
        return "Blood Princess";
    }
        
    if (query_guild_title_nr() == 111)
    {
        if (gender == 0)
        {
            return "Prince of Crypts";
        }
        
        return "Princess of Crypts";
    }
    
    if (query_guild_title_nr() == 112)
    {
        if (gender == 0)
        {
            return "Prince of Eternal Night";
        }
        
        return "Princess of Eternal Night";
    }
      
    if (query_guild_title_nr() == 113)
    {
        if (gender == 0)
        {
            return "Pale Duke";
        }
        
        return "Pale Dutchess";
    }
    
    if (query_guild_title_nr() == 114)
    {
        if (gender == 0)
        {
            return "Duke of Darkness";
        }
        
        return "Duchess of Darkness";
    }
    
    
    if (query_guild_title_nr() == 115)
    {
        if (gender == 0)
        {
            return "Count of Shadows";
        }
        
        return "Countess of Shadows";
    }
    
    if (query_guild_title_nr() == 116)
    {
        if (gender == 0)
        {
            return "Sanguinary Count";
        }
        
        return "Sanguinary Countess";
    }
    
    if (query_guild_title_nr() == 117)
    {
        if (gender == 0)
        {
            return "Gloomy Baron";
        }
        
        return "Gloomy Baroness";
    }
    
    if (query_guild_title_nr() == 118)
    {
        if (gender == 0)
        {
            return "Villainous Baron";
        }
        
        return "Villainous Baroness";
    }
    
    if (query_guild_title_nr() == 119)
    {
        if (gender == 0)
        {
            return "Decadent Baron";
        }
        
        return "Decadent Baroness";
    }
    
    if (query_guild_title_nr() == 120)
    {
        if (gender == 0)
        {
            return "Dreadlord";
        }
        
        return "Dreadlady";
    }
    
    if (query_guild_title_nr() == 121)
    {
        if (gender == 0)
        {
            return "Seducer";
        }
        
        return "Seductress";
    }
    
    if (query_guild_title_nr() == 122)
    {
        if (gender == 0)
        {
            return "Cherished Son of the Night";
        }
        
        return "Cherished Daughter of the Night";
    }
    
    return vamp_titles[query_guild_title_nr()];
}


int query_vampires_occ()
{
    return 1;
}


public void
add_soul()
{
    setuid();
    seteuid(getuid());

    shadow_who->add_cmdsoul(VAMPIRES_GUILD_DIR 
    + "souls/vampires_guild_soul_occ");

    shadow_who->update_hooks();
}


public string
query_guild_name_occ()
{
    return OCC_VAMPIRES_GUILD_NAME;
}


public string
query_guild_style_occ()
{
    return TYPE_OCC;
}


public int
query_guild_tax_occ()
{
    return TAX_OCC;
}


public mixed
query_guild_trainer_occ()
{
    return ({ VAMPIRES_GUILD_DIR + "rooms/occ_train",
           });
}


public int
query_guild_not_allow_join_occ(object player, string type, 
string style, string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))
    return 1;
}


public int
query_guild_keep_player(object ob)
{
    return 1;
}


public void
init_occ_shadow(string str)
{
    object who = query_shadow_who();
    
    setuid();
    seteuid(getuid());

    ::init_occ_shadow();
    
    set_alarm(0.0, 0.0, add_soul);
}


public void remove_shadow()
{
    shadow_who->remove_cmdsoul(VAMPIRES_GUILD_DIR 
    + "souls/vampires_guild_soul_occ");

    shadow_who->update_hooks();

    ::remove_shadow();
}
