 
 /*  Spirit Circle of Psuchae Occ Shadow  */
 /*           July 28th, 2003             */
 /*                Jaacar                 */
           
#pragma strict_types
#pragma save_binary

inherit "/std/guild/guild_occ_sh";
#include <stdproperties.h>
#include <ss_types.h>
#include <const.h>
#include <macros.h>
#include "defs.h"
#include SPIRIT_HEADER
#include COUNCIL_HEADER

static int prot;
string query_spirit_circle_title();
public string *titles = ({"Unproven Candidate of Avidity",
                          "Fledgling Novitiate of Opacity",
                          "Promising Student of Vision",
                          "Aspiring Neophyte of Skill",
                          "Gifted Apostle of Distinction",   // Apprentice
                          "Talented Initiate of Dusk",       //   Titles
                          "Deserving Aspirant of the Twilight",
                          "Accomplished Devotee of Nightfall",
                          "Learned Apprentice of Ether",
                          "Eidolon of Transcendence",

                          "Enlightened Servant of the Spirit",
                          "Brilliant Worshipper of Essentia",
                          "Blessed Vassal of Individuality",
                          "Enigmatic Adjutant of Life",            // Master
                          "Distinguished Messenger of Brilliance", // Titles
                          "Bold Paradigm of Quintessence",
                          "Outstanding Preceptor of Liturgy",
                          "Mysterious Agent of the Phantoms",
                          "Revered Emissary of the Inner-Light",

                          "Philosopher of Transcendence",
                          "Spiritualist of the Soul",
                          "Literati and Soothsayer of Transcendence", 
                          "Phantom Ordainer of the Soul",    //  Elder
                          "Oracle and Sage of Psuchae",  // Titles
                          "Spiritual Seer and Seraph of Psuchae",
    
                          "Theurgist of the Spirit Circle",
                          "Archon of the Spirit Circle",     // Leader
                          "Patriarch of the Spirit Circle",  // Titles
                          "Matriarch of the Spirit Circle"});

string query_guild_style_occ() { return SPIRIT_GUILD_STYLE; }
string query_guild_name_occ() { return SPIRIT_GUILD_NAME; }

int
query_guild_tax_occ()
{
    int ssc;

    ssc = shadow_who->query_skill(SS_SPIRIT_CHOSEN);

    return SPIRIT_GUILD_TAX(ssc);
}

int
query_casting_bonus()
{
    int value, bonus;

    value = shadow_who->query_skill(SS_SPELLS_CASTED);

    bonus = 100*value/50000;

    if (bonus > 150)
    {
        bonus = 150 + (bonus-150)/3;
    }
    
    bonus = MIN(bonus, 200);

    return bonus;
}

void
greet()
{
    object who;
    object *members;
        
    seteuid(getuid());
    who = query_shadow_who();
    COUNCIL_CODE->carry_out_punishments(who);
    tell_object(shadow_who,"Welcome, "+query_spirit_circle_title()+"!\n");
    setuid();
    seteuid(getuid());
    who->add_cmdsoul(SPIRIT_SOUL);
    who->update_hooks();
    
    members = filter(users(), &->is_spirit_member());
    if (!sizeof(members))
        return;
    if (shadow_who->query_ghost())
    {
        tell_object(shadow_who,"The voice of Psuchae rings through "+
            "your mind:\nYour journey is not yet complete my Child. "+
            "Continue forth upon your journey to greatness. Go forth "+
            "with my blessings.\n");
        return;
    }
        
    map(members, &->catch_msg("The voice of Psuchae echoes through your "+
        "mind announcing that "+capitalize(shadow_who->query_real_name())+
        ", "+query_spirit_circle_title()+" has entered the realms.\n"));
}

int
is_spirit_member()
{
    return 1;
}

public void
do_die(object killer)
{
    object *members;

    if ((shadow_who->query_hp() > 0) || shadow_who->query_wiz_level() ||
        shadow_who->query_ghost())
    {
        return;
    }

    members = filter(users(), &->is_spirit_member());
    if (!sizeof(members))
    {
        shadow_who->do_die(killer);
        return;
    }

    shadow_who->add_prop(LIVE_I_NO_CORPSE,1);
    shadow_who->do_die(killer);
    map(members, &->catch_msg("The voice of Psuchae echoes through "+
        "your mind announcing that "+capitalize(shadow_who->query_real_name())+
        " has just perished.\n"));
    tell_room(environment(shadow_who),QCTNAME(shadow_who)+"'s body "+
        "suddenly blackens and fades into it's own shadow then "+
        "disappears!\n",shadow_who);
}

int
add_occ_shadow(object who)
{
    return shadow_me(who, "occupational", SPIRIT_GUILD_STYLE, SPIRIT_GUILD_NAME);
}

void
init_occ_shadow(string str)
{
    ::init_occ_shadow();
    setuid();
    seteuid(getuid());
    COUNCIL_CODE->load_me();
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
    return query_spirit_circle_title();
}

string
query_spirit_circle_title()
{
    int stat;
    object who;
    string extra = "";

    who = query_shadow_who();
    stat = who->query_base_stat(SS_OCCUP);
        
    seteuid(getuid());

    if (COUNCIL_CODE->is_council_member(shadow_who->query_real_name()))
    {
        extra += ", Harbinger of Psuchae";
    }

    if (shadow_who->query_alignment() <= 0)
    {
        extra += ", Lost Disciple of Shadows";
    }

    if (COUNCIL_CODE->is_theurgist(shadow_who->query_real_name()))
    {
        if (shadow_who->query_skill(SS_SPIRIT_CHOSEN) != ALL_SPELL_LEVELS)
            shadow_who->set_skill(SS_SPIRIT_CHOSEN, ALL_SPELL_LEVELS);
        return titles[25]+extra;
    }

    if (COUNCIL_CODE->is_archon(shadow_who->query_real_name()))
    {
        if (shadow_who->query_skill(SS_SPIRIT_CHOSEN) != ALL_SPELL_LEVELS)
            shadow_who->set_skill(SS_SPIRIT_CHOSEN, ALL_SPELL_LEVELS);
        return titles[26]+extra;
    }

    if (COUNCIL_CODE->is_patriarch(shadow_who->query_real_name()))
    {
        if (shadow_who->query_skill(SS_SPIRIT_CHOSEN) != ALL_SPELL_LEVELS)
            shadow_who->set_skill(SS_SPIRIT_CHOSEN, ALL_SPELL_LEVELS);
        if (shadow_who->query_gender() == G_MALE)
            return titles[27]+extra;
        else 
            return titles[28]+extra;
    }

    if (COUNCIL_CODE->is_council_member(shadow_who->query_real_name()))
    {
        if (shadow_who->query_skill(SS_SPIRIT_CHOSEN) != ALL_SPELL_LEVELS)
            shadow_who->set_skill(SS_SPIRIT_CHOSEN, ALL_SPELL_LEVELS);
        return titles[(MAX(19,(MIN(24,(stat/5)))))] + extra;
    }

    if (COUNCIL_CODE->is_spirit_apprentice(shadow_who->query_real_name()))
        return titles[(MIN(9,(stat/5)))] + ", Child of Psuchae" + extra;
    
    if (COUNCIL_CODE->is_spirit_master(shadow_who->query_real_name()))
        return titles[(MAX(10,(MIN(18,((stat/5) - 
            (shadow_who->query_skill(SS_SPIRIT_TITLE)/5))))))] + extra;

    return titles[(MAX(19,(MIN(24,((stat/5) -
        (shadow_who->query_skill(SS_SPIRIT_TITLE)/5))))))] + extra;
}


int
query_spirit_circle_level()
{
    int stat, modifier;
    object who;

    who = query_shadow_who();
    stat = who->query_base_stat(SS_OCCUP);
    modifier = (shadow_who->query_skill(SS_SPIRIT_TITLE) / 5);
    stat = (stat - modifier);

    seteuid(getuid());

    if (who->query_wiz_level())              // Highest Level
        return 8;
    else

    if (COUNCIL_CODE->is_council_member(who->query_real_name()))
        return 8;                            // Highest Level

    if (COUNCIL_CODE->is_theurgist(who->query_real_name()))
        return 8;                            // Highest Level

    if (COUNCIL_CODE->is_archon(who->query_real_name()))
        return 8;                            // Highest Level
    
    if (COUNCIL_CODE->is_patriarch(who->query_real_name()))
        return 8;                            // Highest Level

    if (COUNCIL_CODE->is_spirit_apprentice(who->query_real_name()))
        return ((MIN(3,(stat/14))));          // Levels 1 - 3

    if (COUNCIL_CODE->is_spirit_master(who->query_real_name()))
        return (MAX(4,(MIN(7,(stat/14)))));    // Levels 4 - 7

    if (COUNCIL_CODE->is_spirit_elder(who->query_real_name()))
        return 8;                              // Level 8

    return ((MIN(8,(stat/14))));        // Just in case - up to Level 8
}

string
query_guild_skill_name(int skill)
{
    if (skill == SS_PUNISHMENT)
        return "";
    if (skill == SS_SPIRIT_PUNISHMENT)
        return "";
    if (skill == SS_ELEMENT_SPIRIT)
        return "spirit spells";
    if (skill == SS_SPIRIT_CHOSEN)
        return "";
    if (skill == SS_SPIRIT_TITLE)
        return "";
    if (skill == SS_PATRON_ELEMENTAL)
        return "";
    if (skill == SS_SPELLS_CASTED)
        return "";
    
    return 0;
}

public varargs int
spirit_circle_chosen_count()
{
    int skill = shadow_who->query_skill(SS_SPIRIT_CHOSEN);

    return ((skill & SPELLS_ONE_FLAG) / SPELLS_ONE_FLAG +
        (skill & SPELLS_TWO_FLAG) / SPELLS_TWO_FLAG +
        (skill & SPELLS_THREE_FLAG) / SPELLS_THREE_FLAG +
        (skill & SPELLS_FOUR_FLAG) / SPELLS_FOUR_FLAG +
        (skill & SPELLS_FIVE_FLAG) / SPELLS_FIVE_FLAG +
        (skill & SPELLS_SIX_FLAG) / SPELLS_SIX_FLAG +
        (skill & SPELLS_SEVEN_FLAG) / SPELLS_SEVEN_FLAG +
        (skill & SPELLS_EIGHT_FLAG) / SPELLS_EIGHT_FLAG);
}

mixed
query_guild_trainer_occ()
{
    return ({ SPIRIT_TRAINER });
}

/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:       string - the path to the new postoffice
 */
string
query_def_post() 
{
    return SPIRIT_GUILD_POST;
}

public void
remove_object()
{
    "/d/Calia/guilds/scop/specials/notify_guild"->notify_guild(shadow_who);
    ::remove_object();
}
