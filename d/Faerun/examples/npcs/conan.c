
/*
 * From /d/Genesis/doc/examples/mobiles/auleb.c
 * This is an example monster (humanoid npc) containing references
 * to and explanations about some of the basic features that a
 * monster can have.
 * Coded by Maniac.
 * Modifed for Faerun,
 */


#pragma strict_types               // See "man pragmas"

inherit "/std/monster";            // Inherit for monsters
inherit "/d/Genesis/lib/intro";    // Inherit for intro-ing monsters

#include <ss_types.h>              // Monsters usually need skills
#include <macros.h>                // Useful general purpose macros
#include <stdproperties.h>         // For reference to properties
#include <const.h>                 // Useful constants e.g. genders
#include <cmdparse.h>              // Used for action types here
#include <wa_types.h>              // Attack / hitloc related defs

#define WEP     "/d/Genesis/doc/examples/weapons/elf_slayer"
#define ARM     "/d/Genesis/doc/examples/armours/mail"

void
create_monster()
{

      /*
       * DESCRIPTIONS.
       * If your monster must have a unique name, i.e. one that no
       * player can use, get the name banished (see "help banish").
       * If you want the monster's name to show up in players' "who
       * lists" after introductions, then use the efun
       * "set_living_name".
       * "sman <function>" gives exact documentation.
       */

    set_name("conan");                          // (met) name
    add_name("warrior");                        // Other name(s)
    add_name("barbarian");
    add_name("conan");
    set_race_name("human");                     // Race
    set_adj(({"spirited", "black-haired"}));    // (non-met name) adjectives
    set_title("the Librarian");                 // Title for introductions
    set_gender(G_MALE);                         // male gender

      // Long description can be seen by examining the npc.
    set_long("A light-skinned lean-featured barbarian with a furrowed " +
        "brow and keen black eyes. He has long matted black hair and " +
        "powerful looking limbs. Still, he looks well learned.\n");


      /* STATS.
       * The function default_config_npc() can be handy to set
       * all of the npc's stats to the given number, e.g.
       * default_config_npc(80);
       *
       * It's also possible a call could be made to the function
       * set_base_stat() for each stat you want to configure
       * individually. e.g. set_base_stat(SS_DIS, 100);
       *
       * The possible stats are SS_STR, SS_DEX, SS_CON,
       * SS_INT, SS_WIS, SS_DIS, from /sys/ss_types.h.
       * Here the function set_stats() is used to set them
       * all in one go, in the standard order i.e. from
       * SS_STR to SS_DIS as listed above.
       */
     set_stats(({95, 95, 90, 55, 65, 95}));


      /* SKILLS.
       * Set up the monster's skills. Just some basic ones here.
       * For information about skills, see "man skills" and
       * "man skill_list".
       */
    set_skill(SS_WEP_SWORD, 85);
    set_skill(SS_UNARM_COMBAT, 55);
    set_skill(SS_DEFENCE, 65);
    set_skill(SS_AWARENESS, 60);
    set_skill(SS_BLIND_COMBAT, 60);
    set_skill(SS_LOC_SENSE, 45);


      // PROPERTIES..
    add_prop(CONT_I_HEIGHT, 194);     // Height (cm)
    add_prop(CONT_I_WEIGHT, 80000);   // Weight without inventory (grams)
    add_prop(CONT_I_VOLUME, 80000);   // Volume without inventory (ml)

      /*
       * PROPERTIES CONTINUED..
       * This monster will accept some items, but by default monsters
       * refuse to accept anything. So the property providing the
       * effect, "no accept give", is removed.
       */
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

      /*
       * PROPERTIES CONTINUED..
       * There are a great many properties available to configure your
       * monsters. Some of the more common ones are summarised below.
       * Others you can search for using "man -k *keyword*" or checking
       * the file "/sys/stdproperties.h". Information about an individual
       * property is available in "man <property>".
       *
       * If the monster should always be able to succeed in attacking,
       * use NPC_I_NO_FEAR. NPC_I_NO_LOOKS will stop a description of
       * appearance (based on opinion) appearing in its description. 
       *
       * The properties LIVE_M_NO_BODY and LIVE_M_NO_CORPSE are useful for
       * non-corporeal monsters or those with unusual remains. Undead
       * monsters should have LIVE_I_UNDEAD set.
       *
       * Use LIVE_I_NEVERKNOWN if only the non-met name of the monster
       * should ever be seen, or LIVE_I_ALWAYSKNOWN if only its met name
       * should be used (very rare).
       *
       * The properties LIVE_I_SEE_DARK and LIVE_I_SEE_INVIS can be used
       * to give the monster special visual capabilities. LIVE_I_QUICKNESS
       * can speed up or slow down your monster in combat (see also
       * "man combat"). For details about resistances to various types
       * of attack, see "man resistance".
       */



       // HEALTH and ALIGNMENT.
    set_hp(query_max_hp());   // Start off healthy
    set_alignment(0);         // Neutral alignment


      /*
       * ACTS.
       * The acts will occur in random order at intervals
       * until they are all used up, then the cycle starts
       * again. The interval durations are based on the number
       * of "heartbeats", or fight rounds you specify in the act time.
       * The acts only occur when the monster is not in combat
       * and players are present.
       */
    set_act_time(3);      // an act every three "heartbeats"
    add_act("ponder booze.");
    add_act("ponder the deadly guardians of the ancient ruins.");
    add_act("hmm");
    add_act("say The Book of Secrets was stolen from the Great Library " +
        "and must be found!");


      /*
       * COMBAT ACTS.
       * Similar in cycling/interval handling to acts, but
       * only occur while the monster is in combat.
       */
    set_cact_time(2);
    add_cact("scowl savagely");
    add_cact("swear");
    add_cact("say No one gets away with that!");

    // clone and ready equipment
    equip(({ WEP, ARM}));
}


/*
 * Reactions to introduction/greetings start here.
 *
 * A monster may introduce itself in ways different to the defaults
 * provided in /d/Genesis/lib/intro.c, by masking the provided functions.
 */

/*
 * Function name: greet
 * Description:   This function makes the npc do a greeting to people it
 *                already know and to fellow npc's. It is possible to
 *                redefine, note however that it should never contain an
 *                'introduce myself' command.
 * Arguments:     object who - the living that introduced to me
 *
 */
public void
greet(object who)
{
      // He won't greet an enemy!
    if (member_array(who, query_enemy(-1)) > -1)
    {
        command("kick " + OB_NAME(who));
    }
    else if (!objectp(query_attack()))
    {
        command("nod briefly " + OB_NAME(who));
    }
}



/*
 * Function name:   introduce
 * Description:     This function makes the npc do an introduction to a
 *                  player that has not been introed to it earlier. The
 *                  function may be redefined to create variety.
 * Arguments:       object who - the living that introduced to me
 *
 */
public void
introduce(object who)
{
      // He won't intro to an enemy
    if (member_array(who, query_enemy(-1)) > -1)
    {
        command("kick " + OB_NAME(who));
    }
    else
    {
        command("introduce myself to " + OB_NAME(who));
        command("bow " + OB_NAME(who));
    }
}
