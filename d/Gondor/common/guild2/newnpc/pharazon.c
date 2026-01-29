/*
 * /d/Gondor/common/guild2/npc/pharazon.c
 *
 * A npc member of the Society of Morgul Mages
 *
 * Olorin, July 1994
 * Adjusted to the new spells system by Chmee, August 2003
 * Updated guilds recognized by Finwe, May 2019
 */
#pragma save_binary
#pragma strict_types

inherit "/d/Gondor/common/guild2/newnpc/npc_mage";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/guild2/lib/morgul_defs.h"

#define WEP_ARRAY1 ({MORGUL_DIR + "obj/mattock", MORGUL_DIR + "obj/wraith_mace", MORGUL_DIR + "obj/halberd"})
#define ARM_ARRAY1 ({MORGUL_DIR + "obj/platehelm"})
#define ARM_ARRAY2 ({MORGUL_DIR + "obj/platemail"})

#define MAGES_MEET_SAYS ({ "Do you know Gorbag?",  "Be wary of spies and traitors!", \
               "Do you know of the latest treachery of the WoHS?", \
               "Elves cannot be trusted!", "Beware of hobbit trickery!", \
               "Never listen to a dwarf!", "Fear the power of the Dark Lord!", \
               "It would seem the Dark Lord has favoured you.", \
               "Hast thou received any new gifts from our Lord?", \
                           "Do you know where to find frostheal?", \
                        })

#define GENERAL_SAYS1   ({ "Which quests have you solved in this area?", \
                           "Can you give me a hint on the zodiac quest?", \
                           "well, got to go.. take care and quest some...", \
                           "hmm.. you have to figure quests out on your own... :)", \
                        })

#define GENERAL_SAYS2   ({ "I've no idea, sorry", "What did you say?", \
                           "Do you have any plats to spare?", \
                           "sorry, lagged ....", "Take care", "Dost thou have a name?", \
               "Present thyself, wretch!", "What business dost thou have here?", \
                           "Dark travels!", "Shadows keep thee!", \
               "May the shadows protect thee!", "May the Dark Lord guide thy travels!", \
               "May the Lidless Eye always hold thee in favour!", \
               "The curse of Manwe besets me greatly.", \
               "Cursed are the chains of Tulkas that slow me down!", \
                           "My movements are slowed by the curse of Manwe.", \
                           "Curse this slowness of Manwe!", \
                        })
#define KILL_ACTIONS   ({ "think the corpse isn't even worth scavenging for food", \
                          "mhiss Go to hell!", "shout Die! Die!! Die!!!!", \
                          "ponder easy victims ...", \
                          "think wanting enemies, not victims", \
                          "mhiss There's nothing better than an easy kill", \
                          "mhiss Say hello to Lars from me", \
                          "mhiss There's nothing better than an easy kill", \
                        })

void react_meet( object tp );

int react_c, react_alarm, def_c, def_alarm;

void
create_mage()
{
 set_name( "pharazon" );
 set_living_name( "pharazon" );
 remove_adj( ({"dark-skinned", "red-eyed"}) );
 set_adj( ({"white-haired", "cross-eyed"}) );
 set_alignment( MORGUL_I_ALIGN_JOIN- 200 );

 set_stats( ({95, 95, 100, 95, 66, 90, 0, 150, 0}), 11 );

    remove_prop( LIVE_I_NEVERKNOWN );

    set_skill( SS_WEP_SWORD  , 75);
    set_skill( SS_WEP_POLEARM, 75);
    set_skill( SS_WEP_AXE    , 75);
    set_skill( SS_WEP_KNIFE  , 50);
    set_skill( SS_WEP_CLUB   , 50);
    set_skill( SS_DEFENCE    , 75);
    set_skill( SS_PARRY      , 60);

    set_skill( SS_ALCHEMY, 40 );

    set_restrain_path( MORGUL_DIR + "cellar" );
    set_monster_home( MORGUL_DIR + "cellar/pass_1e1" );
    set_random_move( 10 );

    add_act( "eat all" );
    add_act( "drink all" );
    add_cact( &emote_enemy( "wrath" ) );
    add_cact( "mhiss I will hurt only a little bit" );

    set_default_answer( VBFC_ME( "default_answer" ) );
}

void
set_arm_arrays()
{
    ::set_arm_arrays();
    Wep1 = WEP_ARRAY1;
    Arm1 = ARM_ARRAY1;
    Arm2 = ARM_ARRAY2;
}

void
loot_corpse()
{
    command( "get all from corpse" );
    command( "spit" );
    command( ONE_OF_LIST( KILL_ACTIONS ) );
}

void
init_living()
{
    object tp = this_player();

    ::init_living();

    if (!interactive(tp) || !CAN_SEE( this_object(), tp ))
    {
        return;
    }
    set_alarm( 3.0, 0.0, &react_meet( tp ) );
}

void
react_morgul(object tp = this_player())
{
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
        command( "rasp "+ ONE_OF_LIST( MAGES_MEET_SAYS ) );
        break;
    case 5:
        command( "rasp "+ ONE_OF_LIST( GENERAL_SAYS2 ) );
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
    if (!present(tp, environment(this_object())))
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
        command( "say "+ ONE_OF_LIST( GENERAL_SAYS2 ) );
        break;
    case 8:
        command( "say "+ ONE_OF_LIST( GENERAL_SAYS1 ) );
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
        command( "hiss "+ ONE_OF_LIST(GENERAL_SAYS1) );
        break;
    case 9:
        command( "hiss "+ ONE_OF_LIST(GENERAL_SAYS2) );
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
/*
    mage_name = MORGUL_MASTER->query_mage_name(tp->query_real_name());
    if (strlen(mage_name))
    {
        if (tp->query_nazgul())
        mage_name = ", " + (tp->query_gender() == 1 ? "Lady " : "Lord ") + mage_name;
        else
        mage_name = ", " + mage_name;
    }
    else
        mage_name = "";
*/
        mage_name = mage_address( tp );
        command( "rasp "+ ONE_OF_LIST(
            ({ "Greetings, "+ mage_name+ "! How art thou?",
            "Greetings, "+ mage_name+ "! How fare thy travels?",
            })));
        react_c = 0;
        remove_alarm( react_alarm );
        react_alarm = set_alarm( 4.0, 5.0, &react_morgul( tp ) );
        break;
    case "Rangers of the Westlands":
        command( "snarl "+ name );
        command( "shout Death to all rangers!" );
        break;
    case "Angmar Army":
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
        command( "say I'll rip Calia's colors off your dead body, "+
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
            command( "say Be prepared to feel the anger of Morgul!" );
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
