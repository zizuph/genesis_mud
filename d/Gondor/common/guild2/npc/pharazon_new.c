/*
 * /d/Gondor/common/guild2/npc/pharazon.c
 *
 * Pharazon, the mage. Based on the original Pharazon by
 * Olorin, July 1994
 *
 * Modified by Chmee, September, 2003
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/morgul/npc/ithil_monster.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

static string Weapon_Name;
static object mage_robe;
string *General_says_a =
({
    "Which quests have you solved in this area?",
    "Can you give me a hint on the zodiac quest?",
    "well, got to go.. take care and quest some...",
    "hmm.. you have to figure quests out on your own... :)",
}),
*General_says_b =
({
    "I've no idea, sorry",
    "What did you say?",
    "Do you have any plats to spare?",
    "sorry, lagged ....",
    "Take care",
    "Dost thou have a name?",
    "Present thyself, wretch!",
    "What business dost thou have here?",
    "Dark travels!",
    "Shadows keep thee!",
    "May the shadows protect thee!",
    "May the Dark Lord guide thy travels!",
    "May the Lidless Eye always hold thee in favour!",
    "The curse of Manwe besets me greatly.",
    "Cursed are the chains of Tulkas that slow me down!",
    "My movements are slowed by the curse of Manwe.",
    "Curse this slowness of Manwe!",
});
int react_c, react_alarm, def_c, def_alarm, sequence = 0;

//     Prototypes:
void react_meet( object tp );
void get_mage_robe();
void initial_engagement_sequence();

nomask void
create_ithil_monster()
{
 object MM_sh;

    set_name( "pharazon" );
    set_living_name( "pharazon" );
    set_race_name( "human" );
    set_adj( ({ "white-haired", "cross-eyed" }) );

                                /*Let us prepare him to join the guild.      */
    set_alignment( MORGUL_I_ALIGN_JOIN- 200 );

    set_stats( ({95, 95, 100, 95, 66, 90, 0, 150, 0}), 11 );
    set_learn_pref( ({1, 1, 1, 2, 1, 1, 0, 1, 0, }) );
    remove_prop( LIVE_I_NEVERKNOWN );

    set_skill( SS_WEP_SWORD  , 75);
    set_skill( SS_WEP_POLEARM, 75);
    set_skill( SS_WEP_AXE    , 75);
    set_skill( SS_WEP_KNIFE  , 50);
    set_skill( SS_WEP_CLUB   , 50);
    set_skill( SS_DEFENCE    , 75);
    set_skill( SS_PARRY      , 60);

    set_skill( SS_SPELLCRAFT,  90 );
    set_skill( SS_HERBALISM,   60 );
    set_skill( SS_ALCHEMY,     40 );

    set_skill(SS_FORM_TRANSMUTATION, 40);
    set_skill(SS_FORM_ENCHANTMENT,   80);
    set_skill(SS_FORM_CONJURATION,   80);

    set_skill(SS_ELEMENT_FIRE,  40);
    set_skill(SS_ELEMENT_AIR,   70);
    set_skill(SS_ELEMENT_DEATH, 90);
    

    set_skill(SS_SNEAK, 50);
    set_skill(SS_HIDE,  50);

    set_skill(SS_LANGUAGE,  50);

    set_skill(SS_SWIM,      50);
    set_skill(SS_CLIMB,     50);
    set_skill(SS_AWARENESS, 50);

    add_prop( CONT_I_HEIGHT,    185 );
    add_prop( CONT_I_WEIGHT,  72000 );
    add_prop( CONT_I_VOLUME,  30000 );

    set_default_answer( VBFC_ME( "default_answer" ) );

                                /*Now, let us join the guil.              */
    MM_sh = clone_object( GUILD_SHADOW );
    MM_sh->shadow_me( this_object(), GUILD_TYPE, GUILD_STYLE, GUILD_NAME );
    MM_sh->init_occ_shadow();
                                /*Let him make up to a Black Wraith.      */
    MM_sh->set_morgul_penalty( 4+ random( 4 ) );
	get_mage_robe();

    set_act_time( 7 );
    add_act( "gaze" );
    add_act( "mleer" );
    add_act( "mremember" );
    add_act( "mscoff" );
    add_act( "torture" );
    add_act( "withdraw" );

    set_cact_time( 2 );
    add_cact( "mcurse" );
    add_cact( "shriek" );
    add_cact( &emote_enemy( "mcurse" ) );
    add_cact( &emote_enemy( "sneer" ) );
    add_cact( &emote_enemy( "mscoff" ) );
    add_cact( "mwail" );
    add_cact( "rasp Die you sucker!" );

}

void get_mage_robe()
{
 object  robe;

    if (!objectp( mage_robe = present( "morgul_guild_object",
		this_object() ) ))
    {
        mage_robe = clone_object( MAGES_DIR+ "mage_robe" );
        mage_robe->move( this_object() );
    }
    command( "wear robe" );
}

void
arm_me()
{
    ::arm_me();
    get_mage_robe();
    Weapon_Name = query_weapon( -1 )[0]->query_name();
}


int
special_attack( object target )
{
::special_attack( target );
command( "cast dramalgos" );
return 0;
}
/*
 object *mages;
    string *spells = query_spells(),
            spell,
            name;

    ::special_attack( target );

								/*Some rudimentary checks.                */
/*
    if (!sizeof(query_weapon(-1)))
        command("wield "+Weapon_Name);

    if (random(3))
        return 0;

	if (!(objectp( mage_robe )) || !sizeof( spells ))
	{
		Get the robe
		spells = mage_robe->m_indices( mage_robe->query_spell_map() );
	}
*/

    							/*Pharazon won't call for help outside of
								 *Minas Morgul 							 
    if (explode(file_name(environment(target)), "/")[3] != "morgul")
        spells -= ({ "palanquendo" });

*/
/*
        case "palanquendo":
            mages = users() - ({ 0 });
            mages = filter(mages, "member_filter", MORGUL_SOUL_FILE);
            if (!sizeof(mages))
                break;
            name = ONE_OF_LIST(mages)->query_real_name();
            command("unwield all");
            command("palanquendo "+name+" Help, I'm under attack from "
              + LANG_ADDART(target->query_nonmet_name()));
            break;
*/
/*
target->query_real_name()


    return 0;
}
*/
void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 =
    ({
        MORGUL_DIR+ "obj/mattock",
        MORGUL_DIR+ "obj/wraith_mace",
        MORGUL_DIR+ "obj/halberd"
    });
    Arm1 = ({ MORGUL_DIR+ "obj/platehelm" });
    Arm2 = ({ MORGUL_DIR+ "obj/platemail" });
}

void
loot_corpse()
{
 string *Kill_actions =
 ({
    "think the corpse isn't even worth scavenging for food",
    "mhiss Go to hell!",
    "shout Die! Die!! Die!!!!",
    "ponder easy victims ...",
    "think wanting enemies, not victims",
    "mhiss There's nothing better than an easy kill",
    "mhiss Say hello to Lars from me",
    "mhiss There's nothing better than an easy kill",
 });

    command( "get all from corpse" );
    command( "spit" );
    command( ONE_OF_LIST( Kill_actions ) );
}

string
emote_enemy(string str)
{
 object  pl;

    if (!objectp( pl = query_attack() ))
    {
        return "";
    }
    command( str+ " "+ pl->query_real_name() );
    return "";
}

void
do_attack( object victim )
{
    if (query_attack())
    {
        return;
    }
    if (!present( victim, environment( this_object() ) ))
    {
        return;
    }
    if (!CAN_SEE_IN_ROOM( this_object() ) ||
        !CAN_SEE( this_object(), victim ))
    {
        return;
    }
    command( "kill "+ victim->query_real_name() );
}

void attacked_by( object ob )
{
    ::attacked_by( ob );

								/*A lot of things could be done now,
								 *including checks for a weakest attacker
								 *and such.                               */
//	initial_engagement_sequence();
	command( "cast dramalgos" );
}

/*
 * Function name: initial_engagement_sequence
 * Description  : Call itself in a sequence of alarms until ...
 * Argument     : 
 * Returns      : 
 */
void initial_engagement_sequence()
{
 float time = 1.1;

	set_alarm( time, 0.0, &initial_engagement_sequence() );
}

public string
mage_address( object mage )
{
 int nl;
 string mage_name;

    if ((nl = mage->query_nazgul()) > 1)
    {
        return ((mage->query_gender() == G_FEMALE) ? "M'Lady" : "Sire");
    }
    mage_name = MORGUL_MASTER->query_mage_name( mage->query_real_name() );
    if (strlen( mage_name ))
    {
        if (mage->query_nazgul())
        {
            return ((mage->query_gender() == 1) ? "Lady " : "Lord ")+
                mage_name;
        }
        else
        {
            return mage_name;
        }
    }
    return mage->query_morgul_title();
}

/*
 * Function name: send_report
 * Description:   Send a string to a player mage using palanquendo
 *                The message is sent to the highest ranking
 *                mortal mage logged in.
 * Argument:      msg - the string message or VBFC (only function vars!)
 * Returns:       1   - if message was sent
 *                0   - no mortal mages present
 */
static int
send_report( mixed msg )
{
 object *mages, *wep;

    mages = users()- ({ 0 });
    mages = filter( mages, &operator(==)(MORGUL_S_GUILD_NAME) @
        &->query_guild_name_occ() );
    mages = filter( mages, not @ &->query_wiz_level() );
    if (!sizeof( mages ))
    {
        return 0;
    }
    mages = sort_array( mages, &MORGUL_SOUL_FILE->compare_rank() );

    if (sizeof( wep = query_weapon(- 1 ) ))
    {
        Weapon_Name = OB_NAME( wep[0] );
        command( "unwield all" );
    }
    set_alarm( 7.0, 0.0, &command( "wield "+ Weapon_Name ));
    command( "palanquendo "+ mages[0]->query_real_name()+ " "+ msg+
        mage_address( mages[0] )+ "!" );
/*
    log_file("mm_report", this_object()->query_name() + " sent a report to " +
        mages[0]->query_name() + " in " + file_name(environment(this_object())) +
        " on " + ctime(time()) + ": " +
        msg + ".\n", -1);
*/
    return 1;
}

void
init_living()
{
 object tp = this_player();

    ::init_living();
    if (!interactive( tp ) || !CAN_SEE( this_object(), tp ))
    {
        return;
    }
    set_alarm( 3.0, 0.0, &react_meet( tp ) );
}

void
react_morgul( object tp = this_player() )
{
 string *Mages_meet_says =
 ({
     "Do you know Gorbag?",
    "Be wary of spies and traitors!",
    "Do you know of the latest treachery of the WoHS?",
    "Elves cannot be trusted!",
    "Beware of hobbit trickery!",
    "Never listen to a dwarf!",
    "Fear the power of the Dark Lord!",
    "It would seem the Dark Lord has favoured you.",
    "Hast thou received any new gifts from our Lord?",
    "Do you know where to find frostheal?",
 });

    if (!present( tp, environment( this_object() )  ))
    {
        react_c = 0;
        remove_alarm( react_alarm );
    }

    switch (react_c++)
    {
    case 0:
        command( "present me" );
        break;
    case 2:
        command( "rasp "+ ONE_OF_LIST( Mages_meet_says ) );
        break;
    case 5:
        command( "rasp "+ ONE_OF_LIST( General_says_b ) );
        break;
    case 9:
        react_c = 0;
        remove_alarm( react_alarm );
        break;
    default:
        break;
    }
}

void
react_angmar( object tp )
{
    if (!present( tp, environment( this_object() ) ))
    {
        react_c = 0;
        remove_alarm( react_alarm );
    }

    switch (react_c++)
    {
    case 0:
        command( "present me" );
        break;
    case 2:
        command( "pat "+ tp->query_real_name() );
        break;
    case 4:
        command( "say "+ ONE_OF_LIST( General_says_b ) );
        break;
    case 8:
        command( "say "+ ONE_OF_LIST( General_says_a ) );
        break;
    case 9:
        react_c = 0;
        remove_alarm( react_alarm );
        break;
    default:
        break;
    }
}

void
react_mystic( object tp )
{
    if (!present( tp, environment( this_object() ) ))
    {
        react_c = 0;
        remove_alarm( react_alarm );
    }

    switch (react_c++)
    {
    case 2:
        command( "mbeckon "+ tp->query_real_name() );
        break;
    case 6:
        command( "mhiss your ancients have deserted you in the hours of "+
            "need, "+ tp->query_name() );
        break;
    case 7:
        react_c = 0;
        remove_alarm( react_alarm );
        break;
    default:
        break;
    }
}

void
react_default( object tp )
{
    if (!objectp(tp) || !present( tp, environment( this_object() ) ))
    {
        react_c = 0;
        remove_alarm( react_alarm );
    }

    switch (react_c++)
    {
    case 2:
        command( "mbeckon "+ tp->query_real_name() );
        break;
    case 5:
        command( "hiss "+ ONE_OF_LIST( General_says_a ) );
        break;
    case 9:
        command( "hiss "+ ONE_OF_LIST( General_says_b ) );
        break;
    case 10:
        react_c = 0;
        remove_alarm( react_alarm );
        break;
    default:
        break;
    }
}

void
react_meet( object tp )
{
 string  occ, name = tp->query_real_name(), mage_name;

    if (!objectp( tp ) || !present( tp, environment( this_object() ) ))
    {
        return;
    }
    occ = tp->query_guild_name_occ();

    switch (occ)
    {
    case GUILD_NAME:
        command( "hail "+ name );
        mage_name = mage_address( tp );
        command( "rasp "+ ONE_OF_LIST(
            ({ "Greetings, "+ mage_name+ "! How art thou?",
            "Greetings, "+ mage_name+ "! How fare thy travels?",
            })));
        react_c = 0;
        remove_alarm( react_alarm );
        react_alarm = set_alarm( 4.0, 5.0, &react_morgul( tp ) );
        break;
    case "Gondorian Rangers Guild":
        command( "snarl "+ name );
        command( "shout Death to all rangers!" );
        break;
    case "Shield and Club Warriors":
        command( "shout ANGMAR! ANGMAR!! ANGMAR!!!!" );
        command( "cackle" );
        if (react_c == 0)
        {
            remove_alarm( react_alarm );
            react_alarm = set_alarm( 5.5, 4.0, &react_angmar( tp ) );
        }
        break;
    case "The Ancient Mystic Order":
        command( "tempt "+ tp->query_real_name() );
        if (react_c == 0)
        {
            remove_alarm( react_alarm );
            react_alarm = set_alarm( 3.2, 4.5, &react_mystic( tp ) );
        }
        break;
    case "Calian warrior's guild":
        command( "cackle" );
        command( "say I'll rip Calia's colours off your dead body, "+
            tp->query_name()+ "!" );
        break;
    case "Solamnian Knights":
        command( "say Paladine can't help you any more, "+
        tp->query_name()+ "!" );
        command( "sneer");
        break;
    default:
        if ((!tp->query_met(query_real_name())) &&
            (tp->query_alignment() < 0))
        {
            command( "present me" );
        }
        if (react_c == 0)
        {
            remove_alarm( react_alarm );
            react_alarm = set_alarm( 2.7, 6.0, &react_default( tp ) );
        }
        break;
    }
}

string
default_answer()
{
    if (!def_c)
    {
        def_alarm = set_alarm( 2.0, 2.5, "default_react", this_player() );
     }
    return "";
}

void
default_react( object tp )
{
    if (!objectp( tp ) || !present( tp, environment( this_object() ) ))
    {
        def_c = 0;
        remove_alarm( def_alarm );
    }

    switch (def_c++)
    {
    case 0:
        if (tp != query_attack())
        {
            command( "peer "+ tp->query_real_name() );
        }
        break;
    case 1:
        if (tp == query_attack())
        {
               command( "hiss ask Lars, you're going to meet him!" );
        }
        else
        {
            command( "say hey, I'm no npc, stupid" );
        }
        break;
    case 2:
        command( "cackle" );
        break;
    case 3:
        if (tp != query_attack())
        {
            command( "pat "+ tp->query_real_name() );
        }
        def_c = 0;
        remove_alarm( def_alarm );
        break;
    default:
        break;
    }
    if (tp = query_attack())
    {
        return;
    }
}
