/*
 * /d/Gondor/common/guild2/morgul_shadow.c
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
 *
 * ====> Total Tax: (25%) 24% (upper levels)
 * ====> Total Tax: (15%) 12% (lower levels)
 *
 */
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/std/guild/guild_occ_sh.c";
inherit "/d/Gondor/common/lib/binbit.c";

#include <const.h>
#include <composite.h>
#include <language.h>
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>

#include "/d/Gondor/defs.h"
#include "lib/morgul_defs.h"
#include "lib/morgul_titles.h"

#define GUILD_TAX             24
#define APPRENTICE_GUILD_TAX  12
#define TRAIN_HALL            (GUILD_DIR + "train_high")
#define APPRENTICE_TRAIN_HALL (GUILD_DIR + "train_low")

#define IS_SAGE_CHECK(x)      (GUILD_DIR + "throne_room")->query_is_sage(x)

/* TEMPORARY DEFINES UNTIL SUGGESTION CLEAR WITH GORBOTH 
#define NECROMANCER_LEVEL     21
#define NECROMANCER_GUILD_TAX 20 */
/* These defines make the tax the same as it is but the function
   remains as suggested. */
#define NECROMANCER_LEVEL     21
#define NECROMANCER_GUILD_TAX 24

/*
 *      Global variables
 */
static int Nazgul; // = 1: Nazgul, = 2: Lord/Lady of the Nazgul

/* Prototype */
public int query_guild_tax_occ();

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
    Nazgul = i;
    return Nazgul;
}

public int query_nazgul()
{
    return Nazgul;
}

/*
 * Function name: query_sage()
 * Description  : Determines if the Mage is an Archmage or not
 * Argument     : mage - the player to test
 * Returns      : 1 if Mage is found in file morgul_sage.o,
 *               -1 if failure
 */
public int query_sage(mixed mage)
{
    return IS_SAGE_CHECK(mage);
}

/*
 * set_morgul_penalty(), query_morgul_penalty()
 * effective morgul_level = morgul_level - morgul_penalty
 */
public int set_morgul_penalty( int i )
{
    shadow_who->set_skill( SS_MORGUL_PENALTY, i );
    shadow_who->set_guild_pref( SS_OCCUP, query_guild_tax_occ() );
    return 1;
}

public int query_morgul_penalty()
{
/* This line converts all mages to Servants of Morgul.
    if (!shadow_who->query_wiz_level())
    {
        return -1000;
    }
*/

    return shadow_who->query_skill( SS_MORGUL_PENALTY );
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
    int m_stat = shadow_who->query_stat( SS_OCCUP ), mlevel, nlevels, nazgul;
    string *male_titles, mage_name;

    setuid();
    seteuid( getuid() );

    male_titles = (MORGUL_MASTER->query_male_titles());
    nlevels = sizeof( male_titles );

    m_stat = ((m_stat > 100) ? 100 : m_stat);
    mlevel = ((m_stat* (nlevels- 1))/ 100);
    if (flag <= 0)
    {
        mlevel /= 2;
        mlevel += query_morgul_penalty();
        /*
         * Removed to permit Sage levels:
         *
        if (mlevel >= nlevels)
            mlevel = nlevels - 1;
         */
        if (mlevel > nlevels)
        {
            mlevel = nlevels;
        }
    }
    if ((mlevel > APPRENTICE_LEVEL) && !(shadow_who->query_npc()))
    {
        mage_name =
            MORGUL_MASTER->query_mage_name( shadow_who->query_real_name() );
        if (!strlen( mage_name ))
        {
            mlevel = APPRENTICE_LEVEL;
        }
    }

    nazgul = query_nazgul();
    /* Let some wizards be seen as nazgul automatically. */
    if (query_shadow_who()->query_wiz_level())
    {
        /* This is only valid for domain wizards and arches. */
        if ((SECURITY->query_wiz_dom(
            getuid( query_shadow_who() ) ) == getuid()) ||
            (SECURITY->query_wiz_rank(
            getuid( query_shadow_who() ) ) >= WIZ_ARCH))
        {
            nazgul = 2;
        }
    }
    
    if (flag >= 0)
    {
        mlevel += (nazgul* nlevels);
    }
    else if (nazgul)
    {
        mlevel = (nazgul+ 1)* nlevels;
    }

    return ((mlevel < 0) ? 0 : mlevel);
}

/*
 * Function name: query_guild_tax_occ
 * Description:   The tax in the Society.
 *                Two different levels: apprentices and full mages.
 * Returns:       the tax value in %
 */

public int query_guild_tax_occ()
{
    if (query_morgul_level() <= APPRENTICE_LEVEL)
    {
        return APPRENTICE_GUILD_TAX;
    }
    if (query_morgul_level() >= NECROMANCER_LEVEL)
    {
        return NECROMANCER_GUILD_TAX;
    }
    return GUILD_TAX;
}


/*
 * Function name: query_guild_trainer_occ
 * Description  : Return one or more references to the object that define
 *                sk_train_max for the player. The returned refernce can
 *                be a string reference, an object pointer or an array of
 *                those.
 * Returns      : See description.
 */
public mixed query_guild_trainer_occ()
{
    if (query_morgul_level() <= APPRENTICE_LEVEL)
    {
        return APPRENTICE_TRAIN_HALL;
    }
    return TRAIN_HALL;
}

public string query_guild_style_occ()
{
    return GUILD_STYLE;
}

public string query_guild_name_occ()
{
    return GUILD_NAME;
}

/*
 * Function name: query_allow_join_occ
 * Description  : Test if this guild allowed a player to join another
 * Arguments    : type  - the type of guild to join
 *                style - the style of the guild
 *                name  - the name
 * Returns      : 1 - I allow member to join another guild
 */
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

/*
 * Function name: force_leave_guild
 * Description  : tell the master object to kick out the player
 * Argument     : player - player object
 *                reason - why do we kick the player out?
 */
private void force_leave_guild( object player, string reason )
{
    setuid();
    seteuid( getuid() );
    MORGUL_MASTER->remove_player_from_guild( player, reason );
}

/*
 * Function name: force_leave_nazgul
 * Description  : tell the master object to relegate the player to mage
 * Argument     : player - player object
 *                reason - why do we kick the player out?
 */
private void force_leave_nazgul( object player, string reason )
{
    setuid();
    seteuid( getuid() );
    MORGUL_NAZGUL_MASTER->demote_nazgul_alarm( player->query_real_name(),
        reason);
}

/* 
 * Function name: query_guild_keep_player
 * Description  : This gives you a chance to tell if you want to keep
 *                the player when the shadow is autoloading when a player
 *                logs on.
 * Arguments    : player - the player
 * Returns      : 1 - keep player, 0 - kick him out.
 */
private int query_guild_keep_player(object player)
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

public string query_morgul_title()
{
    int level;

    setuid();
    seteuid( getuid() );

    if (query_nazgul())
    {
        if (shadow_who->query_gender() == G_FEMALE)
        {
            return (MORGUL_MASTER->query_female_nazgul_titles())[query_nazgul()- 1];
        }
        else
        {
            return (MORGUL_MASTER->query_male_nazgul_titles())[query_nazgul()- 1];
        }
    }
    /* Sage of Morgul: retired nazgul */
    if (query_sage(shadow_who))
    {
        switch (MORGUL_MASTER->query_sage_title(shadow_who))
        {
        case 25:
            return MORGUL_MASTER->query_sage_titles()[0];

        case 21..24:
            return MORGUL_MASTER->query_sage_titles()[1];

        case 14..20:
            return MORGUL_MASTER->query_sage_titles()[2];

        case 0..13:
            return MORGUL_MASTER->query_sage_titles()[3];

        default:
            return MORGUL_MASTER->query_sage_titles()[1];
        }
    }

    level = query_morgul_level();
    if (level >= MORGUL_I_NUM_TITLES)
    {
        return "<unknown>";
    }
    if (shadow_who->query_gender() == G_FEMALE)
    {
        return (MORGUL_MASTER->query_female_titles())[level];
    }
    else
    {
        return (MORGUL_MASTER->query_male_titles())[level];
    }
}

/*
 * Function name: query_guild_title_occ
 * Description  : This function should return the occupational title off
 *                the player. Since this function is not called for wizards
 *                you do not have to distinct for them in this function.
 * Returns      : string - the title for the player.
 *                The title will be incorporated in the format
 *                "the <race title>, <occ title> and <lay title>"
 *                if the player is a member of all major guild types.
 */
public string query_guild_title_occ()
{
    return query_morgul_title();
} 

/*
 * Function name: query_def_post
 * Returns:       the path name to the post office used by the player
 */
public string query_def_post()
{
    return MORGUL_POST;
}

/*
 * Function name: query_guild_skill_name
 * Description  : When a players uses the skills command he should get the
 *                the skill names, not the 'special' string.
 * Arguments    : type - the number of the skill
 * Returns      : 0 if no skill of mine, else the string.
 */
public mixed query_guild_skill_name( int type )
{
    if (type == SS_MORGUL_PENALTY)
    {
        if (objectp( this_player() ) && this_player()->query_wiz_level())
        {
            return "Morgul Penalty";
        }
        else
        {
            return "";
        }
    }
    return 0;
}

/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *                me      - I
 *                for_obj - The looker
 * Returns:       The string the looker shall see
 */
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
        if ((query_morgul_level() > APPRENTICE_LEVEL) && (for_obj != me))
        {
            str += capitalize( me->query_possessive() )+
                " eyeless sockets are gleaming like red coals.\n";
        }
        break;
    }
    if (for_obj != me)
        str += IDLENESS->appraise_nazgul( me, for_obj);
    else
        if(strlen(IDLENESS->appraise_nazgul( me, for_obj)) > 0)
            str += "You" + IDLENESS->appraise_nazgul( me, for_obj);
    return str;
}

/*
 * Function name: query_undead
 * Description  : VBFC for LIVE_I_UNDEAD
 * Returns      : undead level
 */
public int query_undead()
{
    int val = shadow_who->query_stat( SS_OCCUP );

    if (val < 10)
    {
        val = 10;
    }
    else if (val > 100)
    {
        val = 100;
    }
    return val;
}

/*
 * Function name: query_spells
 * Returns      : Active Morgul spells
 */
public string *query_spells()
{
    object spell_obj;

    if (!objectp(spell_obj = present( MORGUL_S_SPELL_OBJECT, shadow_who )))
    {
        return 0;
    }
    return m_indexes( spell_obj->query_spell_map() )+ ({});
}

/*
 * Function name: second_life
 * Description  : Handles all that should happen to a dying player.
 * Argument     : Object that caused the kill.
 * Returns      : True if the living object should get a second life
 */
public int second_life( object killer )
{
    if (query_nazgul())
    {
        shadow_who->catch_tell( "The Dark Lord does not accept failures.\n"+
            "You are not a Nazgul anymore!\n");
        setuid();
        seteuid( getuid() );
        MORGUL_NAZGUL_MASTER->demote_nazgul_alarm( shadow_who->
            query_real_name(), "death" );
    }
    return shadow_who->second_life( killer );
}

/*
 * Function name: add_soul
 * Description  : Called from init_occ_shadow to add the soul
 */
public void add_soul()
{
    if (objectp( shadow_who ))
    {
        shadow_who->add_cmdsoul( MORGUL_SOUL_FILE );
        shadow_who->update_hooks();
    }
}

void add_morgulmage_robe() {
    if (!objectp(present(MORGUL_S_SPELL_OBJECT, shadow_who))) {
        object robe = clone_object("/d/Gondor/common/guild2/mage_robe");
        robe->move(shadow_who, 1);
        shadow_who->catch_msg("The "+ robe->query_short()
            + " materializes in your inventory.\n");
    }
}

/*
 * Function name: init_occ_shadow()
 * Description  : This function is called from autoload_shadow and may
 *                be used to initialize the shadow when it's loaded.
 * Arguments    : The argument string sent to autoload_shadow.
 */
public void init_occ_shadow( string arg )
{
    setuid();
    seteuid( getuid() );

    shadow_who->add_subloc( MORGUL_S_SUBLOC, this_object() );
    shadow_who->add_prop( LIVE_I_UNDEAD, query_undead );
    shadow_who->add_prop( LIVE_I_NO_CORPSE, 1 );

    set_alarm( 0.0, 0.0, add_soul );
    set_alarm( 0.1, 0.0, add_morgulmage_robe );
    Nazgul =
        MORGUL_NAZGUL_MASTER->query_is_nazgul( shadow_who->query_name() );
                                /* No wizard may be a nazgul!             */
    if (Nazgul && shadow_who->query_wiz_level())
    {
        MORGUL_NAZGUL_MASTER->
            demote_nazgul( shadow_who->query_name(), "wizard" );
        Nazgul = 0;
        shadow_who->catch_tell(
            "As wizard, you cannot remain one of the Nazgul!\n"+
            "The Dark Lord removes you from the ranks of the Nazgul!" );
    }
    shadow_who->set_nazgul( Nazgul );
    if (Nazgul)
    {
        shadow_who->set_race_name( "wraith" );
        IDLENESS->screen_nazgul( shadow_who );
    }
    STORAGE->deliver_message();
                                /* Clone the nazgul crown                 */
    if (Nazgul > 1)
    {
        clone_object( MAGES_DIR+ "obj/morgul_crown" )->move( shadow_who, 1);
    }
    return;
}

/*
 * Function name: query_race_sound
 * Description  : what does someone of the race r_listen hear if this
 *                object speaks?
 *                defined in /d/Genesis/race/generic.c
 *                For use with mhiss
 * Returns      : the race sound the listener hears
 */
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

/*
 * Function name: actor_race_sound
 * Description  : This function returns the sound this_player() makes when
 *                he or she speaks. By default this is 'say'.
 * Returns      : string - the race sound the receiver hears.
 */
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

/*
 * Function name: query_guild_leader_occ
 * Description  : Council members may keep more mail.
 * Returns      : 1/0 - council/no council
 */
public int query_guild_leader_occ()
{
    return (query_nazgul() > 0);
}

/*
 * Function   : remove_shadow
 * Description: Removes the shadow without removing the shadowed object.
 *              Used here to clean up the LIVE_I_UNDEAD prop, so that no
 *              prop setting is left behind that tries to call a function
 *              in a destructed object.
 */
public void remove_shadow()
{
    shadow_who->remove_prop( LIVE_I_UNDEAD );
    ::remove_shadow();
}
