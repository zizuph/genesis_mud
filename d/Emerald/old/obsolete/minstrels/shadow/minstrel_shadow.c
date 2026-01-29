#pragma strict_types

inherit "/std/guild/guild_lay_sh";

#include "../guild.h"
#include "mood.c"

#include "/d/Emerald/sys/macros.h"

#include <ss_types.h>

#define SW shadow_who

public void remove_member();

public int
query_guild_tax_lay()
{
    return GUILD_TAX;
}

public string
query_guild_style_lay() 
{
    return GUILD_STYLE;
}

public string
query_guild_name_lay()
{
    return GUILD_NAME;
}

public int
query_guild_leader_lay()
{
    return MANAGER->query_council_member(SW);
}

/* 
 * Function:	query_guild_trainer_lay
 * Description:	returns a path to the area where Minstrels train their 
 *		skills.
 */
public string *
query_guild_trainer_lay()
{
    return ({});
}

public void
start_minstrel()
{
    object ob;

    if (SW->add_cmdsoul(GUILD_CMDSOUL))
    {
        SW->update_hooks();
    }

    setuid();
    seteuid(getuid());
    catch(ob = clone_object(MINSTREL_SPELLS));
    if (ob)
    {
        ob->move(SW, 1);
    }
}

public void
login_minstrel()
{
    setuid();
    seteuid(getuid());
    catch(MINSTREL_BELLS->ring_login(SW));
}

int
add_minstrel_shadow(object who)
{
    int ret = shadow_me(who, "layman", GUILD_STYLE, GUILD_NAME);

    if (ret == 1)
    {
        start_minstrel();
    }

    return ret;
}

mixed
acceptable_member(object who)
{
    return 0;
}
 
public void
start_player()
{
    SW->start_player();
    start_minstrel();
    login_minstrel();
}

varargs int
make_new_vamp(object who)
{
    int ret = add_minstrel_shadow(who);

    if (ret == 1)
    {
        SW->clear_guild_stat(SS_LAYMAN);

        MANAGER->remove_member(SW);
        MANAGER->add_member(SW);
    }

    return ret;
}

int
query_guild_not_allow_join_lay(object player, string type,
    string style, string name)
{
    /* Wizards can join anything they want.  Note that this allows multiple occ
     * guilds, which can lead to some conflicts, but it can also be handy.
     */
    if (IS_WIZ(SW))
    {
        return 0;
    }

    return ::query_guild_not_allow_join_lay(player, type, style, name);
}

int
query_guild_keep_player(object ob)
{
    mixed why;

    if (stringp(why = acceptable_member(ob)))
    {
        ob->catch_msg(why);

        /* Normally we would just return 0 here, and the player would be
         * removed from the guild.  We want to make sure a few cleanup
         * actions happen, though, so we'll return 1 here and remove
         * the member ourselves.
         */

        set_alarm(1.0, 0.0, remove_member);

        return 1;
    }

    return 1;
}

public string
query_guild_title_lay()
{
    string str;
    
    switch (SW->query_stat(SS_LAYMAN))
    {
       	case 0..2: str = "Minstrel of NO Renown"; break;
       	case 3..5: str = "Apprentice Performer"; break;
       	case 6..9: str = "Accomplished Performer"; break;
       	case 10..11: str = "Apprentice Chorister"; break;
       	case 12..14: str = "Chorister"; break;
       	case 15..17: str = "Apprentice Psalmist"; break;
       	case 18..21: str = "Psalmist"; break;
       	case 22..24: str = "Apprentice Hymner"; break;
       	case 25..28: str = "Distinguished Hymner"; break;
       	case 29..30: str = "Apprentice Melodist"; break;
       	case 31..33: str = "Principal Melodist"; break;
       	case 34: str = "Apprentice Balladeer"; break;
       	case 35..39: str = "Balladeer of Great Prestige"; break;
       	case 40..41: str = "Apprentice Contrapuntist"; break;
       	case 42..45: str = "Celebrated Contrapuntist"; break;
       	case 46..50: str = "Apprentice Bard"; break;
       	case 51..55: str = "Bard of Renown"; break;
       	case 56..58: str = "Apprentice Troubadour"; break;
       	case 59..61: str = "Troubadour of Glorious Repute"; break;
       	case 62..67: str = "Apprentice Minstrel"; break;
       	case 68..73: str = "Most Honored Minstrel of the Commons"; break;
       	case 74..79: str = "Most Noble Minstrel of the Lays"; break;
       	case 80..85: str = "Most Exalted Minstrel of the Court"; break;
       	case 86..90: str = "Minstrel of the Tones"; break;
       	case 91..92: str = "Apprentice Precentor"; break;
       	case 93..94: str = "Honored Precentor of the Canticles"; break;
       	case 95: str = "Apprentice Cantor"; break;
       	case 96..97: str = "Eminent Cantor of the Antiphons"; break;
       	case 98: str = "Apprentice Scholar of Polyphony"; break;
       	case 99: str = "Elect Scholar of Polyphony"; break;
       	case 100: str = "Apprentice Illuminate of Mellifluous Song"; break;
       	case 101..102: str = "Illuminate of Mellifluous Song"; break;
       	case 103: str = "Apprentice Abecedarian of Sonority"; break;
       	case 104..105: str = "Lauded Abecedarian of Sonority"; break;
       	case 106: str = "Apprentice Docent of Harmony"; break;
       	case 107..109: str = "Exalted Docent of Harmony"; break;
       	case 110..115: str = "Apprentice Minister of the Concords"; break;
       	case 116..120: str = "Esteemed Minister of the Concords"; break;
       	case 121..125: str = "Apprentice Master of the Tones"; break;
       	case 126..130: str = "Illustrious Master of the Tones"; break;
       	case 131..135: str = "Candidate Doctor of Music"; break;
       	case 136..140: str = "Learned Doctor of Music"; break;
       	default: str = "August Doctor of Music"; break;
    }    
}

public string
query_minstrel_muse()
{
    return MANAGER->query_muse(SW);
}

public void
set_minstrel_muse(string muse)
{
    MANAGER->set_muse(SW, muse);
}

mixed
query_guild_skill_name(int type)
{
}

public void
remove_member()
{
    /* If there's some error in removing items, we 
    deep_inventory(SW)->remove_minstrel_item();

    SW->clear_guild_stat(SS_LAYMAN);

    if (SW->query_default_start_location() == GUILD_STARTLOC)
    {
        SW->set_default_start_location(who->query_def_start());
    }

    /* Remove the guild soul */
    SW->remove_cmdsoul(GUILD_CMDSOUL);
    SW->update_hooks();

    MANAGER->remove_member(SW);

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_lay();
}

public void
remove_minstrel_shadow()
{
    remove_shadow();
}

public int
query_minstrel()
{
    return 1;
}
