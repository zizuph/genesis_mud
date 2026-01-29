/*
 * /d/Gondor/guilds/morgulmage/mage_shadow.c
 *
 * The guild shadow for the Morgul Mages of Gondor
 *
 * Created: Olorin, 5-jan-1994
 *          using /doc/examples/solamn/occ_shadow.c by Nick
 *          and   /d/Gondor/common/guild/ranger_shadow.c by Elessar
 *
 * Copyright (c) 1997 by Christian Markus
 *
 * Modification log:
 * 20-Jan-1997, Olorin: General revision.
 *  5-Feb-1997, Olorin: Changed tax.
 * 17-Jul-1997, Olorin: Level 'Sage' for retired nazgul.
 *  8-Mar-1998, Mercade: Check for punishments during absence.
 * 12-Nov-2006, Toby: added query_sage to support new Archmage system
 * 11-Mar-2009, Eowul: Cleaned up and moved to the new guild directory
 * 19-Mar-2014, Gorboth: Commented out nazgul removal at death (for now)
 * 12-Jan-2019, Arman: Changes made following AoB review. Details in
 *                     /d/Genesis/ateam/aob/guilds/morgul_mages/   
 *
 * ====> Total Tax: (40%) (upper levels)
 * ====> Total Tax: (24%) (lower levels)
 *
 */

#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_occ_sh.c";

#include <const.h>
#include <composite.h>
#include <language.h>
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "morgulmage.h"

#define STEED_PATH "/d/Gondor/morgul/city/mm_stables/obj/steed"

static int player_is_nazgul = 0;
public int query_nazgul();
static int previous_level = -1;
int using_original_spells = 1;

/*
 * set_morgul_penalty(), query_morgul_penalty()
 * effective morgul_level = morgul_level - morgul_penalty
 */
public int set_morgul_penalty( int i )
{
    MORGUL_MASTER->set_mage_penalty(shadow_who, i);
    shadow_who->set_guild_pref(SS_OCCUP, query_guild_tax_occ());
    return 1;
}

public int query_morgul_penalty()
{
    return MORGUL_MASTER->get_mage_penalty(shadow_who);
}

int query_max_morgul_level() {
    if (MORGUL_MASTER->query_is_archmage(shadow_who)) return ARCHMAGE_LEVEL;
    if (MORGUL_MASTER->query_is_lieutenant(shadow_who)) return LT_LEVEL;
    if (MORGUL_MASTER->query_is_full_mage(shadow_who)) return LT_LEVEL - 1;
    if (MORGUL_MASTER->query_is_tuvale(shadow_who)) return TUVALE_LEVEL;
    return APPRENTICE_LEVEL;
}

int query_morgul_base_level()
{
    int m_stat = shadow_who->query_stat( SS_OCCUP ), mlevel;
    m_stat = ((m_stat > 100) ? 100 : m_stat);
    mlevel = ((m_stat * MAX_NORMAL_LEVELS)/ 100);
    return mlevel;
}

int adjust_morgul_level_with_penalty(int original_level)
{
    if (MORGUL_MASTER->query_is_archmage(shadow_who)) return ARCHMAGE_LEVEL;
    if (MORGUL_MASTER->query_is_lieutenant(shadow_who)) return LT_LEVEL;

    return (original_level / 2) + query_morgul_penalty();
}

int limit_morgul_level_by_max_rank(int original_level)
{
    if (original_level > query_max_morgul_level()) {
        return query_max_morgul_level();
    }
    return original_level;
}

int limit_morgul_level_for_apprentices(int original_level)
{
    if ((original_level > APPRENTICE_LEVEL) &&
        (!MORGUL_MASTER->query_is_full_mage(shadow_who)))
    {
        return APPRENTICE_LEVEL;
    }

    return original_level;
}

int limit_morgul_level_for_tuvales(int original_level)
{
    if ((original_level > TUVALE_LEVEL) &&
        (MORGUL_MASTER->query_is_tuvale(shadow_who)))
    {
        return TUVALE_LEVEL;
    }

    return original_level;
}

private int player_is_nazgul_or_special_wizard() {
    if (query_nazgul()) return query_nazgul();
    if (!query_shadow_who()->query_wiz_level()) return 0;

    string uid = getuid(query_shadow_who());
    if (SECURITY->query_wiz_rank(uid) >= WIZ_ARCH) return 2;
    if (SECURITY->query_wiz_dom(uid) == getuid()) return 2;

    return 0;
}

/*
 * Function name: query_morgul_level
 * Description  : calculates the level in the Society
 *                apprentices have level <= APPRENTICE_LEVEL,
 *                mages < nlevels,
 *                sages have == nlevels,
 *                nazgul have >= nlevels.
 * Argument     : flag =  0: complete calculation
 *                     =  1: 'base rank', ie w/o effects of penalty
 *                     = -1: nazgul = 50, lord = 75, others as for 0
 *                           used to compare rank of mages, to have
 *                           all nazgul at the same rank
 * Returns      : the level
 */
public int query_morgul_level( int flag = 0 )
{
    if (shadow_who->query_npc())  return ARCHMAGE_LEVEL;

    int total_morgul_titles = MAX_NORMAL_LEVELS;
    int nazgul = player_is_nazgul_or_special_wizard();
    int m_level = 0;

    switch (flag)
    {
        case 0:
        {
            m_level = query_morgul_base_level();
            m_level = adjust_morgul_level_with_penalty(m_level);
            m_level = limit_morgul_level_by_max_rank(m_level);
            m_level += (nazgul * total_morgul_titles);
            break;
        }
        case 1:
        {
            m_level = query_morgul_base_level();
            m_level = limit_morgul_level_for_apprentices(m_level);
            m_level = limit_morgul_level_for_tuvales(m_level);
            m_level += (nazgul * total_morgul_titles);
            break;
        }
        case -1:
        {
            m_level = query_morgul_base_level();
            m_level = adjust_morgul_level_with_penalty(m_level);
            m_level = limit_morgul_level_by_max_rank(m_level);
            if (nazgul) m_level = (nazgul + 1) * total_morgul_titles;
            break;
        }
    }

    return ((m_level < 0) ? 0 : m_level);
}

public int query_archmage()
{
    return (MORGUL_MASTER->query_is_archmage(shadow_who));
}

public int query_nazgul()
{
    return player_is_nazgul;
}

private void add_nazgul_trinkets() {

    object ring = present(MORGUL_MORGUL_RING, shadow_who);
    if (query_nazgul()) {
        if (!objectp(ring)) {
            clone_object(MORGUL_OBJ_DIR + "nazgul_ring")->move(shadow_who, 1);
        }
    } else {
        if (objectp(ring)) ring->remove_object();
    }

    object crown = present(MORGUL_MORGUL_CROWN, shadow_who);
    if (query_nazgul() == 2) {
        if (!objectp(crown)) {
            clone_object(MORGUL_OBJ_DIR + "nazgul_crown")->move(shadow_who, 1);
        }
    } else {
        if (objectp(crown)) crown->remove_object();
    }
}

/*
 * Function name: set_nazgul(), query_nazgul()
 * Description  : Nazgul = 1: Nazgul
 *                Nazgul = 2: Lord or Lady of the Nazgul
 * Argument     : i - nazgul level
 * Returns      : nazgul level, -1 if failure
 */
public int set_nazgul(int i)
{
    if (!intp( i ) || (i < 0) || (i > 2))
    {
        return -1;
    }

    player_is_nazgul = i;

    if (player_is_nazgul) {
        shadow_who->set_race_name("wraith");
    } else {
        shadow_who->reset_race_name();
    }

    add_nazgul_trinkets();
    return player_is_nazgul;
}

public int query_guild_not_allow_join_occ( object player, string type,
    string style, string name )
{
    if (::query_guild_not_allow_join_occ( player, type, style, name ))
    {
        return 1;
    }
    if (style == "cleric")
    {
        notify_fail( "The Lord of Morgul does not tolerate clerics in his "+
            "service!\n" );
        return 1;
    }
    return 0;
}

public int check_seen(object follower)
{
    if (!follower)
    {
        return shadow_who->check_seen(follower);
    }
    // The steeds can sense their master, regardless of
    // whether they are invisible.
    // Approved by Varian Oct 2022
    if (MASTER_OB(follower) == STEED_PATH)
    {
        return 1;
    }
    return shadow_who->check_seen(follower);
}

public mixed query_guild_trainer_occ()
{
    if (IS_APPRENTICE(this_object())) return MORGUL_LOW_TRAINING;
    return MORGUL_HIGH_TRAINING;
}

public string query_guild_style_occ()
{
    return GUILD_STYLE;
}

public string query_guild_name_occ()
{
    return GUILD_NAME;
}

public int query_guild_tax_occ()
{
    if (IS_APPRENTICE(this_object())) return GUILD_TAX_APPRENTICE;
    return GUILD_TAX_FULL_MAGE;
}

private void force_leave_guild( object player, string reason )
{
    MORGUL_MASTER->remove_player_from_guild( player, reason );
}

private void force_leave_nazgul( object player, string reason )
{
    MORGUL_MASTER->remove_player_as_nazgul(player, reason);
}

public int second_life( object killer )
{
//  if (query_nazgul())
//  {
//      shadow_who->catch_tell( "The Dark Lord does not accept failures.\n"+
//          "You are not a Nazgul anymore!\n");
//      setuid();
//      seteuid( getuid() );
//      MORGUL_MASTER->remove_player_as_nazgul(shadow_who, "death" );
//  }
    return shadow_who->second_life( killer );
}

int query_guild_keep_player(object player)
{
    int align;
    string race = player->query_race(), guild;

    if (member_array( race, MORGUL_AS_ILLEGAL_RACE ) > -1)
    {
        player->catch_tell( "The Lord of Morgul does not accept "+
            LANG_ADDART( player->query_race_name() )+
            " like you in his service!\n" );
        set_alarm( 1.0, 0.0, &force_leave_guild( player,
            "Illegal race: "+ race ));
    }

    if (player->query_guild_style( "cleric" ))
    {
        player->catch_tell( "The Lord of Morgul does not tolerate clerics "+
            "in his service!\n" );
        if (player->query_guild_style_occ() == "cleric")
        {
            guild = player->query_guild_name_occ();
        }
        else if (player->query_guild_style_lay() == "cleric")
        {
            guild = player->query_guild_name_lay();
        }
        else if (player->query_guild_style_race() == "cleric")
        {
            guild = player->query_guild_name_race();
        }
        set_alarm( 1.0, 0.0, &force_leave_guild( player,
            "Illegal guild style: cleric ("+ guild+ ")" ) );
    }

    guild = (MORGUL_MASTER)->expulsion_pending( player->query_real_name() );
    if (strlen(guild))
    {
        player->catch_tell( "The Nine have expelled you from His Service! "+
            "You are no longer among the ranks of the Society of Morgul "+
            "Mages!\n");
        set_alarm( 1.0, 0.0, &force_leave_guild( player, guild ) );
    }

    if ((align = player->query_alignment()) > MORGUL_I_ALIGN_REMOVE)
    {
        player->catch_tell( "The Dark Lord demands complete allegiance.\n"+
            "Your actions have been found wanting.\n"+
            "You left the Dark Path, now you will be punished!\n");
        set_alarm( 1.0, 0.0, &force_leave_guild( player,
            "Alignment: "+ align ) );
    }
    else if (align > MORGUL_I_ALIGN_WARN)
    {
        write( "The Dark Lord demands complete allegiance.\n"+
            "Be warned and return to the Paths of Shadow and Darkness!\n" );
    }
    else if (align > MORGUL_I_ALIGN_JOIN)
    {
        write( "The Dark Lord demands complete allegiance.\nWalk the "+
            "Paths of Shadow and Darkness to please the Lord of Morgul!\n");
    }
                                /* We always return 1, since we use our own
                                 * routine to kick the player out.          */

    set_alarm( 5.0, 0.0, &(MORGUL_MASTER)->update_mage_rank(player));

    return 1;
}


string query_morgul_title(int type = 0)
{
    string *titles;
    int level = query_morgul_level();
    if (query_nazgul()) level = ARCHMAGE_LEVEL + query_nazgul();

    if (previous_level != level) {
        previous_level = level;
        MORGUL_MASTER->update_mage_rank(shadow_who);
    }

    switch(type)
    {
        case 0:
        {
            if (shadow_who->query_gender() == G_FEMALE)
            {
                titles = MORGUL_COMMON_FEMALE_TITLES;
            }
            else
            {
                titles = MORGUL_COMMON_MALE_TITLES;
            }
            break;
        }
        case 1:
        {
            titles = MORGUL_BLACKSPEECH_TITLES;
            break;
        }
        case 2:
        {
            titles = MORGUL_ADUNAIC_TITLES;
            break;
        }
        case 3:
        {
            if (shadow_who->query_gender() == G_FEMALE)
            {
                titles = MORGUL_QUENYA_FEMALE_TITLES;
            }
            else
            {
                titles = MORGUL_QUENYA_MALE_TITLES;
            }
            break;
        }
    }

    if (level >= sizeof(titles))
    {
        return "<unknown>";
    }

    return titles[level];
}

public mixed query_mage_option(string option, mixed defaultoption = 999)
{
    return MORGUL_MASTER->get_mage_option(shadow_who, option, defaultoption);
}

public void set_mage_option(string option, mixed value)
{
    MORGUL_MASTER->set_mage_option(shadow_who, option, value);
}

public string query_guild_title_occ()
{
    int type = query_mage_option(OPTION_TITLE_NORMAL, 0);

    object calling_ob = calling_object(-3);
    if ((objectp(calling_ob) && MASTER_OB(calling_ob) == "/cmd/live/social") &&
        (calling_function(-3) == "intro_live")) {
        type = query_mage_option(OPTION_TITLE_INTRO, 0);
    }

    switch(type)
    {
        case 0:
        case 1:
        case 2:
        case 3:
            return query_morgul_title(type);
        case 4:
            return "Mage of Morgul";
        default:
            return 0;
    }
}

public string query_def_post()
{
    return MORGUL_POST_OFFICE;
}

public int query_undead()
{
    int val = shadow_who->query_stat(SS_OCCUP);
    return MAX(10, MIN(val, 100));
}

public object
query_top_shadow()
{
    object last_me, me;

    me = shadow_who;
    last_me = me;
    while (me = shadow(me, 0))
    {
        last_me = me;
    }

    return last_me;
}

public void prepare_mage() {
    setuid();
    seteuid( getuid() );

    object mana_shadow = clone_object("/d/Genesis/specials/guilds/shadows/mana_shadow");
    mana_shadow->shadow_me(shadow_who);

    object undead_shadow = clone_object(GLOBAL_UNDEAD_SHADOW);
    undead_shadow->shadow_me(shadow_who);

    if (!objectp(present(MORGUL_S_SPELL_OBJECT, shadow_who))) {
        object robe = clone_object(MORGUL_OBJ_DIR + "mage_robe");
        robe->move(shadow_who, 1);
        shadow_who->catch_msg("The "+ robe->query_short()
            + " materializes in your inventory.\n");
    }

    shadow_who->add_cmdsoul("/d/Genesis/specials/guilds/souls/spell_manager_soul");
    shadow_who->add_cmdsoul(MORGUL_GUILD_DIR + "morgul_spells");
    shadow_who->update_hooks();
}

public void add_morgulmage_soul()
{
    if (objectp( shadow_who ))
    {
        shadow_who->add_cmdsoul(MORGUL_COMMAND_SOUL);
        shadow_who->update_hooks();
    }
}

public void init_occ_shadow( string arg )
{
    setuid();
    seteuid( getuid() );

    shadow_who->add_subloc(MORGUL_S_SUBLOC, this_object());
    shadow_who->add_prop(LIVE_I_UNDEAD, query_undead);
    shadow_who->add_prop(LIVE_I_NO_CORPSE, 1);

    set_alarm(0.0, 0.0, add_morgulmage_soul);
    set_alarm(0.0, 0.0, prepare_mage);

    set_nazgul(MORGUL_MASTER->query_is_nazgul(shadow_who));
    if (MORGUL_MASTER->query_is_nazgul(shadow_who)) MORGUL_MASTER->screen_nazgul(shadow_who);

    if (query_nazgul() && shadow_who->query_wiz_level())
    {
        MORGUL_MASTER->remove_player_as_nazgul(shadow_who, "wizard");
        set_nazgul(0);
        shadow_who->catch_tell(
            "As wizard, you cannot remain one of the Nazgul!\n"+
            "The Dark Lord removes you from the ranks of the Nazgul!" );
    }

    MORGUL_MASTER->deliver_pending_messages(shadow_who);

    if (!shadow_who->query_wiz_level() && !shadow_who->query_npc()) {
        object player = find_living(shadow_who->query_real_name());
        set_alarm(2.0, 0.0, &MORGUL_MASTER->setup_layman_guild(player));
    }
}

public string race_sound()
{
    string vb = query_verb();

    if (vb == "mhiss")
    {
        return "hisses";
    }
    if (vb == "rasp")
    {
        return "rasps";
    }
    return shadow_who->race_sound();
}

public string actor_race_sound()
{
    string vb = query_verb();

    if (vb == "mhiss")
    {
        return "hiss";
    }
    if (vb == "rasp")
    {
        return "rasp";
    }
    return shadow_who->actor_race_sound();
}

public int query_guild_leader_occ()
{
    return (query_nazgul() > 0);
}

public void remove_shadow()
{
    shadow_who->remove_prop( LIVE_I_UNDEAD );
    query_top_shadow()->remove_undead_shadow();
    query_top_shadow()->remove_mana_shadow();
    shadow_who->remove_cmdsoul("/d/Genesis/specials/guilds/souls/spell_manager_soul");
    shadow_who->remove_cmdsoul(MORGUL_GUILD_DIR + "morgul_spells");
    shadow_who->remove_cmdsoul(MORGUL_COMMAND_SOUL);
    shadow_who->update_hooks();
    ::remove_shadow();
}

public string *query_spells()
{
    object spell_obj;

    if (!objectp(spell_obj = present(MORGUL_S_SPELL_OBJECT, shadow_who)))
    {
        return 0;
    }
    return m_indexes( spell_obj->query_spell_map() )+ ({});
}

string show_subloc( string subloc, object me, object for_obj )
{
    int hs, ml, mml, hl;
    string str, *handicap = ({
       "is worthless to the Dark Lord",
       "is despised by the Nazgul",
       "would be well advised to grovel before the Nazgul",
       "has done little in service to the Dark Lord",
       "is of small importance in the eyes of the Nazgul",
       "has come to be accepted by the Nine",
       "has rendered what is due to the Dark Lord",
       "is spoken of with appreciation by the Black Captain",
       "held in high esteem by those in Mordor",
       "has been of great service to the mighty Nazgul",
       "is held in the highest regard by the Dark Lord"
    });

    if (subloc != MORGUL_S_SUBLOC)
    {
        return shadow_who->show_subloc( subloc, me, for_obj );
    }
    if (me->query_prop( TEMP_SUBLOC_SHOW_ONLY_THINGS ))
    {
        return "";
    }
    if (for_obj == me)
    {
        str = "You are ";
    }
    else
    {
        str = capitalize( me->query_pronoun() )+ " is ";
    }

    object ring = present(MORGUL_MORGUL_RING, me);
    if (objectp(ring))
    {
        string armour = ring->get_armour_underneath_ring();
        if (armour == "")
        {
            str = capitalize(LANG_ADDART(ring->short())) + " is worn "
                + "on the finger of "
                + ((for_obj != me) ? me->query_possessive() : "your")
                + " right hand.\n" + str;
        } else {
            str = capitalize(LANG_ADDART(ring->short())) + " is worn "
                + "over the finger of the " + armour + " on "
                + ((for_obj != me) ? me->query_possessive() : "your")
                + " right hand.\n" + str;
        }
    }
    switch (query_nazgul())
    {
    case 1:
        str += "a Nazgul of the Society of Morgul Mages.\n";
        if (for_obj != me)
        {
            str += capitalize( me->query_possessive() )+
                " eyeless sockets are gleaming like red coals.\n";
        }
        break;
    case 2:
        str += "the Lord of the Nazgul, King of Minas Morgul.\n";
        if (for_obj != me)
        {
            str += capitalize( me->query_possessive() )+
                " eyeless sockets are gleaming like red coals.\n";
        }
        break;
    case 0:
    default:
        str += "a Member of the Society of Morgul Mages";
        if (for_obj->query_nazgul())
        {
            if (!(mml = query_morgul_level( 1 )))
            {
                hl = 0;
            }
            else
            {
                hs = sizeof( handicap );
                ml = query_morgul_level();
                hl = (ml* hs/ mml);
                if (hl > (hs-1))
                {
                    hl = hs- 1;
                }
                if (hl < 0)
                {
                    hl = 0;
                }
            }
            str += " who "+ handicap[hl];
        }
        str += ".\n";
        if (!IS_APPRENTICE(me) && (for_obj != me))
        {
            str += capitalize( me->query_possessive() )+
                " eyeless sockets are gleaming like red coals.\n";
        }
        break;
    }
    if (for_obj != me)
        str += MORGUL_MASTER->appraise_nazgul( me, for_obj);
    else
        if(strlen(MORGUL_MASTER->appraise_nazgul( me, for_obj)) > 0)
            str += "You" + MORGUL_MASTER->appraise_nazgul( me, for_obj);
    return str;
}

public string query_mage_name()
{
    return MORGUL_MASTER->query_mage_name(shadow_who);
}

public string
customize_guild_spell_effect_messages(object *effects, string message_text)
{
    mixed active_effect_spells = map(all_inventory(this_player()),
        &->query_spell_names()) - ({ 0 });
    if (!sizeof(active_effect_spells)) return 0;

    string *possible_spells = ({ });
    foreach(string *spell : active_effect_spells)
    {
        possible_spells -= spell;
        possible_spells += spell;
    }

    return "\n                     Currently Active Potions \n"
        + "                     ======================== \n\n"
        + break_string("You can cast " + COMPOSITE_WORDS(sort_array(possible_spells)) + ".", 71) + "\n";
}
