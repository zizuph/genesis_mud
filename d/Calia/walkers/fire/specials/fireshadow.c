
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
#include FIRE_HEADER
#include COUNCIL_HEADER

static int prot;
string query_fire_walker_title();
public string *titles = ({"Untried Apprentice of Fire",
                          "Studious Apprentice of Fire",
                          "Industrious Apprentice of Fire",
                          "Persevering Apprentice of Fire",
                          "Adept Magician of Fire",
                          "Proficient Magician of Fire",
                          "Knowledgeable Magician of Fire",
                          "Experienced Magician of Fire",
                          "Well-Read Scholar of Fire",
                          "Learned Scholar of Fire",
                          "Eminent Scholar of Fire",
                          "Famous Scholar of Fire",
                          "Renowned Sage of Fire",
                          "Illustrious Sage of Fire",
                          "Master Sage of Fire",
                          "Legendary Sage of Fire"});


string query_guild_style_occ() { return "magic"; }
string query_guild_name_occ() { return "College of Elemental" +
        " Fire"; }

int
query_guild_tax_occ()
{
    return GUILD_TAX;
}

void
greet()
{
    object who;

    seteuid(getuid());
    who = query_shadow_who();
/*   COUNCIL_CODE->carry_out_punishments(who); */
    tell_object(shadow_who,"Welcome, "+query_fire_walker_title()+"!\n");
    setuid();
    seteuid(getuid());
    who->add_cmdsoul(FIRESOUL);
    who->update_hooks();
}

int
is_firewalker()
{
    return 1;
}

int
is_walker()
{
    return 1;
}

int
add_occ_shadow(object who)
{
    return shadow_me(who, "occupational", "magic", "College of Elemental" +
        " Fire");
}

void
init_occ_shadow(string str)
{
    ::init_occ_shadow();
    set_alarm(1.5, 0.0, &greet());
}

int
query_guild_keep_player(object ob)
{
    return 1;
}

string
query_guild_title_occ()
{
    return query_fire_walker_title();    
}

string
query_fire_walker_title()
{
    int stat;
    object who;

    who = query_shadow_who();
    stat = who->query_base_stat(SS_OCCUP);

    seteuid(getuid());
/*
    if (COUNCIL_CODE->is_council_member(who->query_real_name()))
    {
        return "Principal of the College of Fire Magic";
    }

    if (who->query_skill(SS_WALKER_LEVEL) == 1)
    {
        return titles[MIN(stat/10, 3)];
    }
    else*/
    if (who->query_skill(SS_WALKER_LEVEL) == 2)
    {
        return titles[MIN(MAX(4, stat/10), 7)];
    }
    else
    if (who->query_skill(SS_WALKER_LEVEL) == 3)
    {
        return titles[MIN(MAX(8, stat/10), 11)];
    }
    else
    if (who->query_skill(SS_WALKER_LEVEL) == 4)
    {
        return titles[MIN(MAX(12, stat/10), 15)];
    }
    else
    {
        return "bug-ridden Fire mage";
    }
}

string
query_guild_skill_name(int skill)
{
    if (skill == SS_WALKER_PUNISHMENT)
        return "";
    if (skill == SS_WALKER_SPELL_STATUS)
        return "";
    if (skill == SS_RITUAL_MAGIC)
        return "";
    return 0;
}

mixed
query_guild_trainer_occ()
{
    return ({ FIRE_TRAINER });
}

