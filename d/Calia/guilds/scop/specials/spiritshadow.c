 
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

// Defines
#define NOTIFIER    "/d/Calia/guilds/scop/specials/notify_guild"

static int prot;
string query_spirit_circle_title();
int query_spirit_circle_level();

public string *titles = ({"Novice of the Quickening",
                          "Seeker of Vision",
                          "Student of the Penumbra",
                          "Proselyte of the Eternal Cycle",
                          "Eidolon of Transcendence",
                          
                          "Enlightened Servant of the Spirit",
                          "Defender of the Living",
                          "Preceptor of Spirit",
                          "Vanguard of Psuchae",
                          "Dawnbringer",
                          
                          "Philosopher of Transcendence",
                          "Redeemer of the Lost",
                          "Soothsayer of Essentia",
                          "Theurgist of the Soulwarden",
                          "Synthesis of Eternity, Paradigm of Soul",
                          
                          "Archon of Revelation",
                          "Archon of Apotheosis",
                          "Archon of Deliverance"
                          
});

string query_guild_style_occ() { return SPIRIT_GUILD_STYLE; }
string query_guild_name_occ() { return SPIRIT_GUILD_NAME; }

int
query_guild_tax_occ()
{
    int ssc;

    ssc = shadow_who->query_skill(SS_SPIRIT_CHOSEN);

    return SPIRIT_GUILD_TAX(ssc);
}

// This function shouldn't be used anymore.
// At least all the spells are no longer using it
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

    if (COUNCIL_CODE->is_spirit_apprentice(shadow_who->query_real_name()))
    {
        bonus = MIN(50, bonus);
    }
    else
    if (COUNCIL_CODE->is_spirit_master(shadow_who->query_real_name()))
    {
        bonus = MIN(150, MAX(50, bonus));    
    }
    else
    {
        bonus = MIN(200, MAX(75, bonus));     
    }
    


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
    tell_object(shadow_who,"Please head through the portal and touch the sphere "+
        "on the other side!\n");
    setuid();
    seteuid(getuid());
    who->add_cmdsoul(SPIRIT_SOUL);
    who->update_hooks();
    
    if (!shadow_who->test_bit("Calia", SCOP_GURU_GROUP, SCOP_GURU_BIT))
    {
        //Only muteness for those who have yet to finish the guru quest.
        
        who->add_prop(LIVE_M_MOUTH_BLOCKED, "You have no tongue, and thus" +
            " cannot speak.\n");
        clone_object(SPIRIT_OBJECTS+"limit")->move(shadow_who);    
    }
    
    if (shadow_who->query_ghost())
    {
        tell_object(shadow_who,"The voice of Psuchae rings through "+
            "your mind:\nYour journey is not yet complete my Child. "+
            "Continue forth upon your journey to greatness. Go forth "+
            "with my blessings.\n");
        return;
    }

    NOTIFIER->notify_arrival(shadow_who);
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

public void
initialize_spells()
{
    object player = query_shadow_who();
    int level = query_spirit_circle_level();
    
    int updated_skill = 0;
//    player->set_skill(SS_SPIRIT_CHOSEN, 0); // reset the spells for tax calculations
    // First clone and move all the spell objects
    object apprentice_book, master_book, elder_book;
    if (!objectp(apprentice_book = present("_spirit_apprentice_spells_", player)))
    {
        apprentice_book = clone_object(SPIRIT_OBJECTS + "apprentice_spells");
        apprentice_book->move(player, 1);
    }
    apprentice_book->update_first_spells();
    updated_skill = updated_skill | SPELLS_ONE_FLAG;
    if (level >= 2)
    {
        apprentice_book->update_second_spells();        
        updated_skill = updated_skill | SPELLS_TWO_FLAG;
    }
    if (level >= 3)
    {
        apprentice_book->update_third_spells();
        updated_skill = updated_skill | SPELLS_THREE_FLAG;
    }

    if (level > 3)
    {
        if (!objectp(master_book = present("_spirit_master_spells_", player)))
        {
            master_book = clone_object(SPIRIT_OBJECTS + "master_spells");
            master_book->move(player, 1);
        }
        if (level >= 4)
        {
            master_book->update_fourth_spells();
            updated_skill = updated_skill | SPELLS_FOUR_FLAG;
        }
        if (level >= 5)
        {
            master_book->update_fifth_spells();        
            updated_skill = updated_skill | SPELLS_FIVE_FLAG;
        }
        if (level >= 6)
        {
            master_book->update_sixth_spells();
            updated_skill = updated_skill | SPELLS_SIX_FLAG;
        }
        if (level >= 7)
        {
            master_book->update_seventh_spells();
            updated_skill = updated_skill | SPELLS_SEVEN_FLAG;
        }
    }
    if (level > 7)
    {
        if (!objectp(elder_book = present("_spirit_elder_spells_", player)))
        {
            elder_book = clone_object(SPIRIT_OBJECTS + "elder_spells");
            elder_book->move(player, 1);
        }
        elder_book->update_eighth_spells();
        updated_skill = updated_skill | SPELLS_EIGHT_FLAG;
    }
    player->set_skill(SS_SPIRIT_CHOSEN, updated_skill);
    player->set_guild_pref(SS_OCCUP, query_guild_tax_occ());
}

void
init_occ_shadow(string str)
{
    ::init_occ_shadow();
    setuid();
    seteuid(getuid());
    COUNCIL_CODE->load_me();
    set_alarm(1.5, 0.0, &greet());
    set_alarm(5.0, 0.0, &initialize_spells());
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
        return titles[15]+extra;
    }

    if (COUNCIL_CODE->is_archon(shadow_who->query_real_name()))
    {
        if (shadow_who->query_skill(SS_SPIRIT_CHOSEN) != ALL_SPELL_LEVELS)
            shadow_who->set_skill(SS_SPIRIT_CHOSEN, ALL_SPELL_LEVELS);
        return titles[16]+extra;
    }

    if (COUNCIL_CODE->is_patriarch(shadow_who->query_real_name()))
    {
        if (shadow_who->query_skill(SS_SPIRIT_CHOSEN) != ALL_SPELL_LEVELS)
            shadow_who->set_skill(SS_SPIRIT_CHOSEN, ALL_SPELL_LEVELS);

        return titles[17]+extra;
    }

    if (COUNCIL_CODE->is_council_member(shadow_who->query_real_name()))
    {
        if (shadow_who->query_skill(SS_SPIRIT_CHOSEN) != ALL_SPELL_LEVELS)
            shadow_who->set_skill(SS_SPIRIT_CHOSEN, ALL_SPELL_LEVELS);
        return titles[(MAX(10,(MIN(14,(stat/13)))))] + extra;
    }

    if (COUNCIL_CODE->is_spirit_apprentice(shadow_who->query_real_name()))
        return titles[(MIN(4,(stat/13)))] + ", Child of Psuchae" + extra;
    
    if (COUNCIL_CODE->is_spirit_master(shadow_who->query_real_name()))
        return titles[(MAX(5,(MIN(9,((stat/13) - 
            (shadow_who->query_skill(SS_SPIRIT_TITLE)/13))))))] + extra;

    return titles[(MAX(10,(MIN(14,((stat/13) -
        (shadow_who->query_skill(SS_SPIRIT_TITLE)/13))))))] + extra;
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
    if (IS_CLONE)
    {
        // We don't want to notify when the master object is being removed
        NOTIFIER->notify_departure(shadow_who);
    }
    ::remove_object();
}

/*
 * Function name: query_top_shadow
 * Description:   Because shadows exist in layers, sometimes you need
 *                to reference functions in a shadow above you. Calling
 *                functions can fail if one doesn't call from the top
 *                shadow. this function allows one to obtain the
 *                top most shadow, giving access to all functions.
 * Returns:       object - top level shadow
 */
public object
query_top_shadow()
{
    object last_me, me;
    
    me = shadow_who;
    last_me = me;
    while (me = shadow(me, 0))
    {
        // loop through to find the top level shadow who
        last_me = me;
    }   
    
    // We return now the top level shadow
    return last_me;
}

public varargs void
add_prop(string prop, mixed val)
{    
    if (prop == LIVE_I_UNDEAD && val != 0)
    {
        query_shadow_who()->catch_tell("You can feel the unclean forces "
            + "of the Soulless wrack your body, and you struggle "
            + "internally. Gradually, you feel the soothing calm of "
            + "Psuchae cleanse your body of the abominating effects.\n");
        return;
    }
    
    query_shadow_who()->add_prop(prop, val);
}

public varargs void
add_subloc(string sloc, mixed resp, mixed ids)
{
    query_shadow_who()->add_subloc(sloc, resp, ids);
    if (sloc == "undead_subloc")
    {
        query_shadow_who()->catch_tell("You can feel the unclean forces "
            + "of the Soulless wrack your body, and you struggle "
            + "internally. Gradually, you feel the soothing calm of "
            + "Psuchae cleanse your body of the abominating effects.\n");
        query_top_shadow()->remove_undead_shadow();
    }        
}

