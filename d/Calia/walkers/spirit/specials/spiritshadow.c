 /*  Spiritwalker Shadow  */
 /*  April 7th, 1998      */
 /*  Jaacar               */

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
string query_spirit_walker_title();
public string *titles = ({"Initiate of the Primitive Ring of Spirit",
                          "Novice of the Primitive Ring of Spirit",
                          "Disciple of the Primitive Ring of Spirit",
                          "Master of the Primitive Ring of Spirit",
                          "Initiate of the Obscure Ring of Spirit",
                          "Novice of the Obscure Ring of Spirit",
                          "Disciple of the Obscure Ring of Spirit",
                          "Master of the Obscure Ring of Spirit",
                          "Initiate of the Outer Ring of Spirit",
                          "Novice of the Outer Ring of Spirit",
                          "Disciple of the Outer Ring of Spirit",
                          "Master of the Outer Ring of Spirit",
                          "Initiate of the Inner Ring of Spirit",
                          "Novice of the Inner Ring of Spirit",
                          "Disciple of the Inner Ring of Spirit",
                          "Master of the Inner Ring of Spirit",
                          "Initiate of the Esoteric Sphere of Spirit",
                          "Novice of the Esoteric Sphere of Spirit",
                          "Disciple of the Esoteric Sphere of Spirit",
                          "Master of the Esoteric Sphere of Spirit",
                          "Initiate of the Harmonic Sphere of Spirit",
                          "Novice of the Harmonic Sphere of Spirit",
                          "Disciple of the Harmonic Sphere of Spirit",
                          "Master of the Harmonic Sphere of Spirit",
                          "Initiate of the Transcendent Sphere of Spirit",
                          "Novice of the Transcendent Sphere of Spirit",
                          "Disciple of the Transcendent Sphere of Spirit",
                          "Master of the Transcendent Sphere of Spirit",
                          "Initiate of the Ancient Sphere of Spirit",
                          "Novice of the Ancient Sphere of Spirit",
                          "Disciple of the Ancient Sphere of Spirit",
                          "Master of the Ancient Sphere of Spirit",
                          "Initiate of the Divine Realm of Spirit",
                          "Novice of the Divine Realm of Spirit",
                          "Disciple of the Divine Realm of Spirit",
                          "Spiritwalker of the Divine Realm of Spirit",
                          "Spiritwalker of Legends"});

string query_guild_style_occ() { return GUILD_STYLE; }
string query_guild_name_occ() { return GUILD_NAME; }

int
query_guild_tax_occ()
{
    int ssc;

    ssc = shadow_who->query_skill(SS_WALKER_CHOSEN);

    return GUILD_TAX(ssc);
}

void
greet()
{
    object who;
    object *members;
    string diety = "Psuchae";

    seteuid(getuid());
    who = query_shadow_who();
    COUNCIL_CODE->carry_out_punishments(who);
    tell_object(shadow_who,"Welcome, "+query_spirit_walker_title()+"!\n");
    setuid();
    seteuid(getuid());
    who->add_cmdsoul(SPIRITSOUL);
    who->update_hooks();
    members = filter(users(), &->is_walker());
    if (!sizeof(members))
        return;
    map(members, &->catch_msg("The voice of "+diety+" echoes through your "+
        "mind announcing that "+capitalize(shadow_who->query_real_name())+
        ", "+query_spirit_walker_title()+" has entered the realms.\n"));
}

int
is_spiritwalker()
{
    return 1;
}

int
is_walker()
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

    members = filter(users(), &->is_spiritwalker());
    if (!sizeof(members))
    {
        shadow_who->do_die(killer);
        return;
    }
    map(members, &->catch_msg("The voice of Psuchae echoes through "+
        "your mind announcing that "+capitalize(shadow_who->query_real_name())+
        " has just perished.\n"));
    shadow_who->add_prop(LIVE_I_NO_CORPSE,1);
    shadow_who->do_die(killer);
    tell_room(environment(shadow_who),QCTNAME(shadow_who)+"'s body "+
        "suddenly blackens and fades into it's own shadow then "+
        "disappears!\n",shadow_who);
}

int
add_occ_shadow(object who)
{
    return shadow_me(who, "occupational", GUILD_STYLE, GUILD_NAME);
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
    return query_spirit_walker_title();
}

string
query_spirit_walker_title()
{
    int stat;
    string extra;
    object who;

    who = query_shadow_who();
    stat = who->query_base_stat(SS_OCCUP);

    seteuid(getuid());

    if (COUNCIL_CODE->is_council_member(shadow_who->query_real_name()))
    {
        if (shadow_who->query_skill(SS_WALKER_CHOSEN) != ALL_SPELL_LEVELS)
            shadow_who->set_skill(SS_WALKER_CHOSEN, ALL_SPELL_LEVELS);
        return titles[(MIN(36,(stat/3)))] + ", Harbinger of Psuchae";
    }
    if (COUNCIL_CODE->is_assistant(shadow_who->query_real_name()))
        return titles[(MIN(36,(stat/3)))] + ", Emmissary of Psuchae";

    if (COUNCIL_CODE->is_spirit_apprentice(shadow_who->query_real_name()))
        return titles[(MIN(15,(stat/3)))] + " and Child of Psuchae";
    
    if (COUNCIL_CODE->is_spirit_granted(shadow_who->query_real_name()))
        return titles[(MIN(31,(stat/3) - 
            (shadow_who->query_skill(SS_WALKER_TITLE))))];
    
    return titles[(MIN(36,(stat/3) -
        (shadow_who->query_skill(SS_WALKER_TITLE))))];
}


int
query_spiritwalker_level()
{
    int stat;
    object who;

    who = query_shadow_who();
    stat = who->query_base_stat(SS_OCCUP);

    seteuid(getuid());

    if (who->query_wiz_level())
        return 10;
    else

    if (COUNCIL_CODE->is_spirit_apprentice(who->query_real_name()))
        return ((MIN(4,(stat/10)+1)));

    if (COUNCIL_CODE->is_spirit_granted(who->query_real_name()))
        return ((MIN(8,(stat/10) + 1 - 
            (who->query_skill(SS_WALKER_STATUS)))));

    return ((MIN(10,(stat/10) + 1 - 
        (who->query_skill(SS_WALKER_STATUS)))));
}

string
query_guild_skill_name(int skill)
{
    if (skill == SS_PUNISHMENT)
        return "";
    if (skill == SS_PRAYER)
        return "channeling";
    if (skill == SS_WALKER_PUNISHMENT)
        return "";
    if (skill == SS_ELEMENT_SPIRIT)
        return "spirit spells";
    if (skill == SS_WALKER_CHOSEN)
        return "";
    if (skill == SS_WALKER_TITLE)
        return "";
    if (skill == SS_WALKER_STATUS)
        return "";
    return 0;
}

public varargs int
spiritwalker_chosen_count(int eligible=0)
{
    int skill = shadow_who->query_skill(SS_WALKER_CHOSEN);

    if (eligible)
        return shadow_who->query_spiritwalker_level();

    return ((skill & SPELLS_ONE_FLAG) / SPELLS_ONE_FLAG +
        (skill & SPELLS_TWO_FLAG) / SPELLS_TWO_FLAG +
        (skill & SPELLS_THREE_FLAG) / SPELLS_THREE_FLAG +
        (skill & SPELLS_FOUR_FLAG) / SPELLS_FOUR_FLAG +
        (skill & SPELLS_FIVE_FLAG) / SPELLS_FIVE_FLAG +
        (skill & SPELLS_SIX_FLAG) / SPELLS_SIX_FLAG +
        (skill & SPELLS_SEVEN_FLAG) / SPELLS_SEVEN_FLAG +
        (skill & SPELLS_EIGHT_FLAG) / SPELLS_EIGHT_FLAG +
        (skill & SPELLS_NINE_FLAG) / SPELLS_NINE_FLAG +
        (skill & SPELLS_TEN_FLAG) / SPELLS_TEN_FLAG);
}

mixed
query_guild_trainer_occ()
{
    return ({ SPIRIT_TRAINER });
}

