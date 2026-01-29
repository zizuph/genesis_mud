
 /*  Firewalker Shadow    */
 /*  March 3rd, 1996      */
 /*  Jaacar               
  *  Modifications by Bishop of Calia, July 9th, 1999.
  */


#pragma strict_types
#pragma save_binary

inherit "/std/guild/guild_occ_sh";

#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include "defs.h"

public string *titles = ({"Untried Apprentice of Fire",
                          "Studious Apprentice of Fire",
                          "Persistent Apprentice of Fire",
                          "Industrious Apprentice of Fire",
                          "Persevering Apprentice of Fire",
                          "Adept of Fire",
                          "Magician of Fire",
                          "Incanter of Fire",
                          "Weaver of Fire",
                          "Pyromancer",
                          "Scholar of Fire",
                          "Sage of Fire",
                          "Illuminate of Fire",
                          "Savant of Fire",
                          "Loremaster of Fire"});


string query_guild_style_occ() { return "magic"; }
string query_guild_name_occ() { return "Colleges of Elemental" +
        " Magic"; }
        
string query_college_full_title();
string is_college_member();

int
query_guild_tax_occ()
{
    return FIRE_TAX;
}

/*
    This function checks the member's status with respect to the guild
    administrative code. Any punishments are carried out, as well 
    as any promotions/demotions.
*/
int
check_council_status()
{
    int punishments, rank;
    
    punishments = COUNCIL_OB->query_punishments(shadow_who->query_name());
    rank = COUNCIL_OB->query_rank(shadow_who->query_name());
    
    if ((shadow_who->query_skill(SS_COLLEGE_BITS) & APPRENTICE_LVL_BIT) && 
        (rank & MAGE_LVL_BIT))
    {
        shadow_who->set_skill(SS_COLLEGE_BITS, 
            shadow_who->query_skill(SS_COLLEGE_BITS) & (~APPRENTICE_LVL_BIT)); 
        shadow_who->set_skill(SS_COLLEGE_BITS, 
            shadow_who->query_skill(SS_COLLEGE_BITS) | MAGE_LVL_BIT);             
        shadow_who->catch_tell("You have been promoted to the rank of" +
            " Mage!\n");
    }
    if ((shadow_who->query_skill(SS_COLLEGE_BITS) & MAGE_LVL_BIT) && 
        (rank & SCHOLAR_LVL_BIT))
    {
        shadow_who->set_skill(SS_COLLEGE_BITS, 
            shadow_who->query_skill(SS_COLLEGE_BITS) & (~MAGE_LVL_BIT)); 
        shadow_who->set_skill(SS_COLLEGE_BITS, 
            shadow_who->query_skill(SS_COLLEGE_BITS) | SCHOLAR_LVL_BIT);             
        shadow_who->catch_tell("You have been promoted to the rank of" +
            " Scholar!\n");
    }
    if ((shadow_who->query_skill(SS_COLLEGE_BITS) & MAGE_LVL_BIT) && 
        (rank & APPRENTICE_LVL_BIT))
    {
        shadow_who->set_skill(SS_COLLEGE_BITS, 
            shadow_who->query_skill(SS_COLLEGE_BITS) & (~MAGE_LVL_BIT)); 
        shadow_who->set_skill(SS_COLLEGE_BITS, 
            shadow_who->query_skill(SS_COLLEGE_BITS) | APPRENTICE_LVL_BIT);
        shadow_who->catch_tell("You have been demoted to the rank of" +
            " Apprentice!\n");
    }
    if ((shadow_who->query_skill(SS_COLLEGE_BITS) & SCHOLAR_LVL_BIT) && 
        (rank & MAGE_LVL_BIT))
    {
        shadow_who->set_skill(SS_COLLEGE_BITS, 
            shadow_who->query_skill(SS_COLLEGE_BITS) & (~MAGE_LVL_BIT)); 
        shadow_who->set_skill(SS_COLLEGE_BITS, 
            shadow_who->query_skill(SS_COLLEGE_BITS) | SCHOLAR_LVL_BIT);             
        shadow_who->catch_tell("You have been demoted to the rank of" +
            " Mage!\n");
    }
    if (!(shadow_who->query_skill(SS_COLLEGE_BITS) & SPELL_BANNED_BIT) &&
        (punishments & SPELL_BANNED_BIT))
    {
        shadow_who->set_skill(SS_COLLEGE_BITS, 
            shadow_who->query_skill(SS_COLLEGE_BITS) | SPELL_BANNED_BIT); 
        shadow_who->catch_tell("You have been severed from the plane" +
            " of " + capitalize(is_college_member()) + "!\n");
    }
    if (!(shadow_who->query_skill(SS_COLLEGE_BITS) & TOWER_CONFINED_BIT) &&
        (punishments & TOWER_CONFINED_BIT))
    {
        shadow_who->set_skill(SS_COLLEGE_BITS, 
            shadow_who->query_skill(SS_COLLEGE_BITS) | TOWER_CONFINED_BIT); 
        shadow_who->catch_tell("You have been confined to the Marble" +
            " Tower!\n");
    }
    if (punishments & EXPELLED_BIT)
    {
        shadow_who->catch_tell("The Assembly has voted to expel you from the" +
            " guild!\n");
    }
    if (((shadow_who->query_skill(SS_COLLEGE_BITS) & SPELL_BANNED_BIT) |
        (shadow_who->query_skill(SS_COLLEGE_BITS) & TOWER_CONFINED_BIT) |
        (shadow_who->query_skill(SS_COLLEGE_BITS) & EXPELLED_BIT)) &&
        !punishments)
    {
        shadow_who->set_skill(SS_COLLEGE_BITS, 
            shadow_who->query_skill(SS_COLLEGE_BITS) & ~(SPELL_BANNED_BIT |
            TOWER_CONFINED_BIT | EXPELLED_BIT)); 
        shadow_who->catch_tell("All punishments on you have been removed.\n");
    }            
}

void
greet()
{
    setuid();
    seteuid(getuid());
    check_council_status();
    shadow_who->catch_tell("Welcome, " + 
        query_college_full_title()+"!\n");
    shadow_who->add_cmdsoul(FIRE_SPECIALS + "firesoul");
    shadow_who->update_hooks();

}

string
is_college_member()
{
    return "fire";
}


int
add_occ_shadow(object who)
{
    return shadow_me(who, "occupational", "magic", "Colleges of Elemental" +
        " Magic");
}

void
init_occ_shadow(string str)
{
    ::init_occ_shadow();
    
    if (!objectp(find_object(COUNCIL_OB)))
    {
        COUNCIL_OB->init_council();
    }
    
    set_alarm(1.5, 0.0, &greet());
}

int
query_guild_keep_player(object ob)
{
    return 1;
}

string 
query_college_full_title()
{
    int stat;

    setuid();
    seteuid(getuid());

    stat = shadow_who->query_base_stat(SS_OCCUP);
    
    if (COUNCIL_OB->query_council(shadow_who->query_name()))
    {
        return "Principal of the College of Fire Magic";
    }
    else
    if (shadow_who->query_skill(SS_COLLEGE_BITS) & APPRENTICE_LVL_BIT)
    {
        return titles[MIN(stat/10, 4)];
    }
    else
    if (shadow_who->query_skill(SS_COLLEGE_BITS) & MAGE_LVL_BIT)
    {
        return titles[MIN(MAX(5, stat/10), 9)];
    }
    else
    if (shadow_who->query_skill(SS_COLLEGE_BITS) & SCHOLAR_LVL_BIT)
    {
        return titles[MIN(MAX(10, stat/10), 14)];
    }
    else
    {
        return "bug-ridden Fire mage";
    }
}


string
query_guild_title_occ()
{
    setuid();
    seteuid(getuid());
    
    if (shadow_who->query_skill(SS_COLLEGE_BITS) & TITLE_SIMPLE_BIT)
    {
        return "Student of the Elements";
    }
    else
    {
        return query_college_full_title();
    }
}


string
query_guild_skill_name(int skill)
{
    if (skill == SS_COLLEGE_BITS)
        return "";
    if (skill == SS_COLLEGE_SPELL_STATUS)
        return "";
    if (skill == SS_RITUAL_MAGIC)
        return "ritual magic";

    return 0;
}

mixed
query_guild_trainer_occ()
{
    return 0;
}

