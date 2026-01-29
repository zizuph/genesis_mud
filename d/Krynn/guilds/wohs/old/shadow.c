/*
 * The guild shadow of all WoHS members.
 */
inherit "/std/guild/guild_occ_sh";

#include "guild.h"


public string
query_wohs_pretitle()
{
    if (ADMIN->query_conclave_member(shadow_who))
        return "Archmage";
    
    return "";
}

/*
 * Function:    query_wohs_title
 * Description: Find the title of this magic-user.
 * Returns:     The title of this magic-user.
 */         
public string
query_wohs_title()
{
    if (!ADMIN->query_member(shadow_who))
        return "Bugged Mage";

    return "Mage of the " + ADMIN->query_member_type(shadow_who) + 
        " robes.";
}

/*
 * Standard Shadow stuff below
 */
    
public void
init_occ_shadow(string arg)
{
    setuid();
    seteuid(getuid());
}

public string
query_guild_name_occ()
{
    return GUILD_NAME;
}

public string
query_guild_style_occ()
{
    return GUILD_STYLE;
}


public int
query_guild_tax_occ()
{
    return 35; /* Temporary */
}


public int
query_guild_leader_occ()
{
    return ADMIN->query_conclave_member(shadow_who);
}

public int
query_guild_not_allow_join_occ(object player, string type, string style,
    string name)
{
    if (::query_guild_not_allow_join_occ(player, type, style, name))   
        return 1;
    
    notify_fail("Magic-users devotes their lives to magic and magic only.\n");
    if (type == "layman")
        return 1;
    
    return 0;
}
 
/* 
 * Spell Experience Functions
 */
public void
add_wohs_exp(int amount)
{
    shadow_who->set_skill(WOHS_XP_SKILL, 
        shadow_who->query_base_skill(WOHS_XP_SKILL) + amount);
    
}

public int
query_wohs_exp()
{
    return shadow_who->query_base_skill(WOHS_XP_SKILL);
}

public int
query_wohs_level()
{
    return ftoi(pow(itof(query_wohs_exp()), 0.27));
}
