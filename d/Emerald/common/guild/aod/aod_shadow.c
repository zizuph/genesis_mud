/* 
 *  /d/Emerald/common/guild/aod/aod_shadow.c
 *
 *  This is the guild shadow for members of the Army of Darkness guild
 *  in Emerald.
 *
 *  Copyright (c) May 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/guild/guild_occ_sh";

#include "defs.h"
#include "aod_titles.h"
#include "exceptions.h"
#include "special_attacks.c"

#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>
#include <wa_types.h>
#include "/d/Genesis/race/racial_abilities.h"

#define GUILD_SUBLOC  GUILD_NAME + " subloc"
#define MAX_GUILD_LEVEL 2
#define HASTE_DEBUFF    130

#define SW shadow_who

/* Prototypes */
public int         query_guild_tax_occ();
public string      query_guild_style_occ();
public string      query_guild_name_occ();
public int         query_skill(int skill);
public mixed       acceptable_member(object who);
public int         query_guild_keep_player(object ob);
public string      query_def_post();
public string      query_guild_title_occ();
public mixed       query_guild_skill_name(int type);
public mixed       query_guild_trainer_occ();
public void        init_guild_member();
public void        start_player();
public int         add_occ_shadow(object who);
public string      show_subloc(string subloc, object me, object for_obj);
public void        remove_occ_member();
public int         query_guild_not_allow_join_occ(object player,
                       string type, string style, string name);
public mixed       wield(object weapon);
public void        enter_inv(object ob, object from);
public void        leave_inv(object ob, object to);
public string      race_sound();
public string      actor_race_sound();
public void        check_ogre_tutorial(object player);
public void        ogre_tutorial(object player, string chapter);
public void        ogghelp(object player);
public void        get_buttkicked(object general);
public void        end_buttkick();


static int  hasted = 0;


/* 
 * Function name: query_guild_tax_occ
 * Description:   Give the amount of tax the guild charges
 * Returns:       int - The tax amount
 */
public int
query_guild_tax_occ() 
{ 
    return GUILD_TAX_OCC; 
} /* query_guild_tax_occ */


/*
 * Function name: query_guild_style_occ
 * Description:   return the guild style for this guild
 * Returns:       string - the style
 */
public string
query_guild_style_occ()
{
    return GUILD_STYLE;
} /* query_guild_style_occ */


/*
 * Function name: query_guild_name_occ
 * Description:   return the guild's name
 * Returns:       string - the guild name
 */
public string
query_guild_name_occ()
{
    return GUILD_NAME;
} /* query_guild_name_occ */



private int is_leaving = 0;

/*
 * Function name:   query_skill
 * Description:     Gives the value of a specific skill.
 * Arguments:       skill: The number of the skill to check
 * Returns:         The value of the skill
 *
 * We mask this to prevent Ogres from using block.
 */
public int
query_skill(int skill)
{
    if (skill == SS_BLOCK)
    {
        /* Ogres cannot have block skill */
        return 0;
    }
    if (skill == RACIAL_ABILITY_SKILL && !is_leaving)
    {
        // This will override the ones selected by the player, for thematics.
        return RESILIENT | INSATIABLE;
    }

    return shadow_who->query_skill(skill);
} /* query_skill */


/*
 * Function name: acceptable_member
 * Description:   test to see if the player is an acceptable member of this
 *                guild.
 * Arguments:     object who - the player to test
 * Returns:       0 or a string message saying why the player isn't acceptable
 */
public mixed
acceptable_member(object who)
{
    /* currently, I'll let anyone in */

    return 0;
} /* acceptable_member */
     
 
/* 
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 * Arguments:     ob - the player.
 * Returns:	  1 if keeping, 0 if not.
 */
public int
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

        set_alarm(1.0, 0.0, remove_occ_member);

        return 1;
    }

    return 1;
} /* query_guild_keep_player */

    
/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:	  string - the path to the new postoffice
 */
public string
query_def_post() 
{
    /* Only bother using the guild's post office if the player is
     * using the guild's start location.
     */
    if (this_player()->query_default_start_location() == AOD_STARTLOC)
    {
        return AOD_POST;
    }

    return query_shadow_who()->query_def_post();
} /* query_def_post */


/*
 * Function name: query_guild_title_occ
 * Description:   Return the member's guild title and any slayer titles
 *                they may have earned.
 * Returns:       string - the title
 */
public string 
query_guild_title_occ()
{
    string *races = ({ "Human", "Elf", "Hobbit", "Dwarf", "Gnome" });
    string *slaytitle = ({});
    string  guildtitle = "";
    string *human_array,
           *elf_array,
           *hobbit_array,
           *dwarf_array,
           *gnome_array,
           *races_arrays;
    int     arraysize = 0;
    int     i,
            j = 0;

    setuid();
    seteuid(getuid());

    human_array  = AOD_MASTER->query_sorted_totals("human",  1);
    elf_array    = AOD_MASTER->query_sorted_totals("elf",    1);
    hobbit_array = AOD_MASTER->query_sorted_totals("hobbit", 1);
    dwarf_array  = AOD_MASTER->query_sorted_totals("dwarf",  1);
    gnome_array  = AOD_MASTER->query_sorted_totals("gnome",  1);

    races_arrays = ({ human_array,
                      elf_array,
                      hobbit_array,
                      dwarf_array,
                      gnome_array
                   });

    if (AOD_MASTER->get_info(REPOSITORY_FILE, "GENERAL") ==
        SW->query_real_name())
    {
        guildtitle = "Headhunter General and ";
    }

    if (AOD_MASTER->get_info(REPOSITORY_FILE, "CORPORAL") == 
        SW->query_real_name())
    {
        guildtitle = "Black Corporal and ";
    }

    if (SW->query_gender() == 1)
    {
        guildtitle += AOD_TITLES_FEMALE[AOD_MASTER->compute_title(SW)]
          + " of the Army of Darkness";
    }
    else
    {
        guildtitle += AOD_TITLES_MALE[AOD_MASTER->compute_title(SW)]
          + " of the Army of Darkness";
    }

    /* count the number of titles they earn to determine array size */
    for (i = 0; i < 5; i++)
    {
        if (races_arrays[i][0] == SW->query_real_name())
        {
            /* raceslayer titles only given at 1000 or more skulls */
            if (AOD_MASTER->get_info(SW->query_real_name(), races[i])
                > 999)
            {
                arraysize++;
            }
        }
    }

    /* no point continuing, just give them the basic title */
    if (!arraysize)
    {
        return guildtitle;
    }

    guildtitle += ", ";
    slaytitle = allocate(arraysize);

    /* now, populate the array with the titles they have earned */
    for (i = 0; i < 5; i++)
    {
        if (races_arrays[i][0] == SW->query_real_name() &&
            AOD_MASTER->get_info(SW->query_real_name(), races[i]) > 999)
        {
            slaytitle[j] = AOD_RACESLAYER_TITLES[i];
            j++;
        }
    }

    /* finally, separate titles by commas and a trailing "and" */
    if (arraysize > 2)
    {
        for (i = 0; i < arraysize; i++)
        {
            if (i == (arraysize - 1))
            {
                guildtitle += slaytitle[i];
            }
            else if (i == (arraysize - 2))
            {
                guildtitle += slaytitle[i] + " and ";
            }
            else
            {
                guildtitle += slaytitle[i] + ", ";
            }
        }
    }
    else if (arraysize == 2)
    {
        guildtitle += slaytitle[0] + " and " + slaytitle[1];
    }
    else
    {
        guildtitle += slaytitle[0];
    }

    return guildtitle;
} /* query_guild_title_occ */


  
/* 
 * Function name: query_guild_skill_name
 * Description:   Give a names for the guild's special skills
 * Arguments:     type - the number of the skill
 * Returns:	  0 if no skill of mine, else the string.
 */
public mixed
query_guild_skill_name(int type)
{
    if (type == SS_AOD_WALLOP)
    {
        return "crush";
    }

    if (type == SS_AOD_PBLOCK)
    {
        return "parry block";
    }

    return 0;
} /* query_guild_skill_name */


/*
 * Function name: query_guild_trainer_occ
 * Description:   Returns the skill trainers for the guild
 * Returns:       string * - an array of paths to the guild's
 *                trainers.
 */
public mixed
query_guild_trainer_occ()
{
    return ({
              AOD_ROOM_DIR + "ogre_train",
              AOD_ROOM_DIR + "defensive_train",
              AOD_ROOM_DIR + "offensive_train",
//            AOD_ROOM_DIR + "adv_def_train",
              AOD_ROOM_DIR + "adv_off_train",
              AOD_ROOM_DIR + "elite_train",
           });
} /* query_guild_trainer_occ */


/*
 * Function name: init_guild_member
 * Description:   Add necessary guild items to the player and
 *                do any other kind of initialization necessary.
 */
public void
init_guild_member()
{
    int     str_var,
            dex_var,
            con_var,
            intel_var,
            wis_var,
            dis_var,
            skin,
            str_bonus,
            con_bonus,
            wis_bonus,
            dex_bonus;

    object  guild_emblem, 
            who = query_shadow_who();

    /* clone the guild emblem and move it to the player */

    setuid();
    seteuid(getuid());

    check_ogre_tutorial(who);
    shadow_who->configure_racial_bonuses();

    if (AOD_OGG_MASTER->get_info(who, "Tutorial") != "tutorial1" &&
        AOD_OGG_MASTER->get_info(who, "Tutorial") != "tutorial2")
    {
        if (guild_emblem = clone_object(AOD_EMBLEM))
        {    
            guild_emblem->move(who, 1);
            set_alarm(1.0, 0.0, &who->catch_tell(
                "You sling the large blood-soaked sack over"
              + " your shoulder.\n"));
        }
    }

    /* give the player ogre stat adjustments */

    /* Now that stat modifiers are equal across the board, we no longer
     * have to adjust for them.
     */
    str_bonus = 0;
    con_bonus = 0;
    wis_bonus = 0;
    dex_bonus = 0;
    dis_var = 0;

    /* For our calculations, we do not use query_base_stat, as
     * that would make everyone want to play a hobbit-ogre. Rather we
     * use F_EXP_TO_STAT(who->query_acc_exp(SS_*)) so that all
     * ogres are created equal.
     */

    /* Ogres get increased strength and con, and reduced dex and wis. These
     * are dealt with first.
     */
    con_var = ftoi(itof(F_EXP_TO_STAT(who->query_acc_exp(SS_CON)))
        * CON_FACTOR) + con_bonus;
    str_var = ftoi(itof(F_EXP_TO_STAT(who->query_acc_exp(SS_STR)))
        * STR_FACTOR) + str_bonus;
    wis_var = 1 - ftoi(itof(F_EXP_TO_STAT(who->query_acc_exp(SS_WIS)))
        * WIS_FACTOR) + wis_bonus;
    dex_var = 1 - ftoi(itof(F_EXP_TO_STAT(who->query_acc_exp(SS_DEX)))
        * DEX_FACTOR) + dex_bonus;

    /* Ogre intelligence is based entirely on the amount of mind fluid
     * they have consumed. They start at (literally) 1 intelligence, and
     * then gain an additional point for each 1000 skulls worth of
     * mind fluid they have consumed. This means that for an int
     * stat of 10, an ogre would need 10,000 skulls. We also cap it
     * at 10. Ogres should not be smarter than that.
     */
    intel_var = MIN( (1 - who->query_base_stat(SS_INT))
          + (AOD_MASTER->query_skull_total(who, 0) / 1000),
            (1 - who->query_base_stat(SS_INT)) + 9);

    who->set_stat_extra(SS_STR, str_var);
    who->set_stat_extra(SS_DEX, dex_var);
    who->set_stat_extra(SS_CON, con_var);
    who->set_stat_extra(SS_INT, intel_var);
    who->set_stat_extra(SS_WIS, wis_var);
    who->set_stat_extra(SS_DIS, dis_var);

    /* give the player ac based on thick ogre skin and their con */
    skin = (who->query_stat(SS_CON) / 10) + AC_FACTOR;
    who->set_all_hitloc_unarmed(MIN(skin, AOD_AC_CAP));

    // This is a new balance feature, will be adjusted when there
    // is a standardized non-magic object for haste.
    if (!hasted)
    {
        who->dec_prop(LIVE_I_QUICKNESS, HASTE_DEBUFF);
        who->query_combat_object()->cb_update_speed();
        hasted++;
    }
    
    /* add the guild's soul to the player */
    who->add_cmdsoul(AOD_CMDSOUL);
    /* And now we add the mudlib one back */
    who->update_hooks();

    /* add the guild subloc */
    who->add_subloc(GUILD_SUBLOC, this_object());

    /* check to see if the time has come for new leadership */
    set_alarm(1.0, 0.0, &AOD_MASTER->check_leader_update());

    /* Tell Gorboth an ogre is arriving! :-) */
    find_living("gorboth")->catch_tell("\n\t\t--****  "
      + capitalize(who->query_real_name())
      + " awakens!  ****--\n\n");

    /* Set the player age for skull_per_hour purposes */
    AOD_MASTER->set_info(who, "player_age", who->query_age());

    /* Set this for the rotation aspect of skull collecting in teams.
     */
    if (!AOD_MASTER->get_info(who, "Last_Turn"))
    {
        AOD_MASTER->set_info(who, "Last_Turn", time());
    }

    /* If the player just logged in, we want to make sure this is set to
     * zero, just as a sanity check.
     */
    AOD_MASTER->set_info(who, "Buttkicked", 0);
} /* init_guild_member */


/*
 * Function name: start_player
 * Description:   This is called when the player logs in.
 */
public void
start_player()
{
    SW->start_player();
    init_guild_member();
} /* start_player */


/* 
 * Function name: add_occ_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 */
public int
add_occ_shadow(object who)
{
    int ret = shadow_me(who, "occupational", GUILD_STYLE, GUILD_NAME);

    if (ret == 1)
    {
        init_guild_member();
    }

    return ret;
} /* add_occ_shadow */


/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *		  me      - I
 *		  for_obj - The looker
 * Returns:	  The string the looker shall see
 */
public string
show_subloc(string subloc, object me, object for_obj)
{
    string str,
           his = me->query_possessive();

    if (subloc != GUILD_SUBLOC)
    {
        return me->show_subloc(subloc, me, for_obj);
    }

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
	return "";
    }

    if (!present("_aod_guild_sack", this_player()))
    {
        return "";
    }

    if (for_obj == me)
    {
	str = "You have your ";
        his = "your";
    }
    else
    {
	str = capitalize(me->query_pronoun()) + " has a ";
    }

    return str + "large blood-soaked sack slung over " + his
      + " back.\n";
} /* show_subloc */


/*
 * Function name: remove_occ_member
 * Description:   remove this member from the guild
 */
public void
remove_occ_member()
{
    object  emblem, 
            who = query_shadow_who();
    int     speed,
            extra_age = AOD_MASTER->get_info(who, "Extra_Age");

    // Return their old skills
    is_leaving = 1;
    who->configure_racial_bonuses();

   /* save to the player's guildfile their accumulated time in the
      guild thus far */
    AOD_MASTER->set_info(who, "Extra_Age",
        AOD_MASTER->membership_duration(this_player()->
        query_real_name()));

    /* Remove special skills */ 
    who->remove_skill(SS_AOD_WALLOP);
    who->remove_skill(SS_AOD_PBLOCK);

    /* Clear the player's guild stat */
    who->clear_guild_stat(SS_OCCUP);

    /* Remove any instances of the guild emblem on the player */
    while (emblem = present(AOD_EMBLEM_ID, who))
    {
        emblem->remove_object();
    }

    /* If the player is using our start location, remove it */
    if (who->query_default_start_location() == AOD_STARTLOC)
    {
        who->set_default_start_location(who->query_def_start());
    }

    /* Remove the Ogre modifications */
    who->set_stat_extra(SS_CON, 0);
    who->set_stat_extra(SS_STR, 0);
    who->set_stat_extra(SS_INT, 0);
    who->set_stat_extra(SS_WIS, 0);
    this_player()->set_all_hitloc_unarmed(1);


    // This is a new balance feature, will be adjusted when there
    // is a standardized non-magic object for haste.
    if (hasted)
    {
        who->inc_prop(LIVE_I_QUICKNESS, HASTE_DEBUFF);
        who->query_combat_object()->cb_update_speed();
        hasted--;
    }

    /* Remove the guild soul */
    who->remove_cmdsoul(AOD_CMDSOUL);
    who->update_hooks();

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_occ();
} /* remove_occ_member */


/* 
 * Function name: query_guild_not_allow_join_occ
 * Description:	  Check if we allow the player to join another guild.
 * Arguments:     player - the player
 *		  type, style, name - the type, style and name of the
 *			intended guild.
 * Returns:	  1 if we do not allow, else 0
 */
public int
query_guild_not_allow_join_occ(object player, string type, string style,
				string name)
{
    /* This checks to make sure that the new guild is not occupational */
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;

    return 0;
} /* query_guild_not_allow_join_occ */


/*
 * Function name:        wield
 * Description  :        Redefinition to prevent Ogres from wielding
 *                       one handed weapons, and to give them a way
 *                       to wield 2-handers in a single hand.
 * Arguments    :        object weapon - the weapon to wield
 * Returns      :        string - error message (weapon not wielded)
 *                       1 - successs (weapon wielded)
 */
public mixed
wield(object weapon)
{
    if (weapon->query_prop(AOD_WIELD_PROP))
    {
        return query_shadow_who()->wield(weapon);
    }

    if (member_array(MASTER_OB(weapon), OGRE_EXCEPTIONS) > -1)
    {
        query_shadow_who()->catch_tell("This is way too small for your"
          + " massive fingers to wield properly ... yet, somehow, you"
          + " take your time and finally manage to hold it between your"
          + " thumb and forefinger.\n");

        return query_shadow_who()->wield(weapon);
    }

    return "This weapon is too small for your hands!\n";
} /* wield */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 *
 * I am masking this function for the purpose of creating the ogre size
 * effect. One handed weapons are too small to fit in an ogre's hand.
 * Two-handed weapons fit in their hands the same way a one-hander should
 * in a non-ogre. So, here we deal with that.
 */
public void
enter_inv(object ob, object from)
{
    if (ob->weapon_type())
    {
        if (ob->query_hands() == W_BOTH)
        {
            ob->add_prop(AOD_WIELD_PROP, 1);
            ob->set_hands(W_ANYH);
        }
    }

    query_shadow_who()->enter_inv(ob, from);
} /* enter_inv */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 *
 * See previous function header. This mask is to deal with the same issues.
 */
public void
leave_inv(object ob, object to)
{
    if (ob->query_prop(AOD_WIELD_PROP))
    {
        ob->set_hands(W_BOTH);
        ob->remove_prop(AOD_WIELD_PROP);
    }

    query_shadow_who()->leave_inv(ob, to);
} /* leave_env */


/*
 * Function name: wear_arm
 * Description:   wear an armour
 * Arguments:     The armour to be worn
 * Returns:       string - error message (armour could not be worn)
 *                1 - success (armour was worn)
 *
 * This mask is to prevent ogres from wearing anything which has not
 * been specially made for them. They are too huge for normal clothing.
 */
public mixed
wear_arm(object arm)
{
    if (arm->query_prop(AOD_WEAR_PROP) ||
        strlen(arm->query_auto_load()))
    {
        return query_shadow_who()->wear_arm(arm);
    }

    if (member_array(MASTER_OB(arm), OGRE_EXCEPTIONS) > -1)
    {
        query_shadow_who()->catch_tell("Hmmm ... this doesn't fit very"
          + " well, but you manage to cram it onto your body somehow.\n");

        return query_shadow_who()->wear_arm(arm);
    }

    return "Your massive body is far too large to wear that!\n";
} /* wear_arm */


/*
 * Function name: wear_clothing
 * Description:   Wear something
 * Arguments:     object ob - the item to be worn
 * Returns:       string - an error message (the item cannot be worn)
 *                1 - item successfully worn
 *
 * See previous function header.
 */
public mixed
wear_clothing(object ob)
{
    if (ob->query_prop(AOD_WEAR_PROP) ||
        strlen(ob->query_auto_load()))
    {
        return query_shadow_who()->wear_clothing(ob);
    }

    if (member_array(MASTER_OB(ob), OGRE_EXCEPTIONS) > -1)
    {
        query_shadow_who()->catch_tell("Hmmm ... this doesn't fit very"
          + " well, but you manage to cram it onto your body somehow.\n");

        return query_shadow_who()->wear_clothing(ob);
    }

    return "Your massive body is far too large to wear that!\n";
} /* wear_clothing */


/*
 * Function name:        race_sound
 * Description  :        make it so that others hear ogres "boom" when they
 *                       speak.
 * Returns      :        string - the verb to hear
 */
public string
race_sound()
{
    return "booms";
} /* race_sound */


/*
 * Function name:        actor_race_sound
 * Description  :        make it so that others hear ogres "boom" when they
 *                       speak.
 * Returns      :        string - the verb to hear
 */
public string
actor_race_sound()
{
    return "boom";
} /* actor_race_sound */


/*
 * Function name:        check_ogre_tutorial
 * Description  :        When players first join the guild, they get
 *                       a bit of a tutorial on how to do everything.
 *                       We store which stage of the tutorial they
 *                       left off at, and then keep it going each time
 *                       they log in.
 * Arguments    :        object player - the person we are dealing with.
 */
public void
check_ogre_tutorial(object player)
{
    string  chapter = AOD_OGG_MASTER->get_info(player, "Tutorial");

    if (!strlen(chapter))
    {
        AOD_OGG_MASTER->set_info(player, "Tutorial", "tutorial1");
    }

    chapter = AOD_OGG_MASTER->get_info(player, "Tutorial");

    if (chapter == "done")
    {
        if (!AOD_OGG_MASTER->get_info(player, "Bosses"))
        {
            set_alarm(8.0, 0.0, &ogghelp(player));
        }

        return;
    }

    set_alarm(8.0, 0.0, &ogre_tutorial(player, chapter));
} /* check_ogre_tutorial */


/*
 * Function name:        ogre_tutorial
 * Description  :        Provide the proper tutorial chapter to give
 *                       to the player.
 * Arguments    :        object player - the ogre in question
 *                       chapter - what chapter they are still at
 */
public void
ogre_tutorial(object player, string chapter)
{
    DARKLING_TELL(read_file(AOD_DIR + chapter + ".txt", 0));
    return;
} /* ogre_tutorial */


/*
 * Function name:        ogghelp
 * Description  :        Ogg senses that there is an ogre who needs some
 *                       training, and bugs them.
 * Arguments    :        object player - the player to bug
 */
public void
ogghelp(object player)
{
    set_this_player(player);

    OGG_TELL(read_file(AOD_DIR + "ogghelp.txt", 0));
    AOD_OGG_MASTER->set_info(this_player(), "Ogg", "yes");   

    player->catch_tell(sprintf("%|80s",
        "You can now get <ogghelp> on 'ogg'.\n"));

    player->catch_tell(sprintf("%|80s",
        "To see a list of topics, simply type <ogghelp>.\n"));

} /* ogghelp */


/*
 * Function name:        get_buttkicked
 * Description  :        allow the players to be kicked in the butt by
 *                       the General for a team boost. See the tax_doc.txt
 *                       for more details.
 * Arguments    :        object general - the general who kicked me!
 */
public void
get_buttkicked(object general)
{
    AOD_MASTER->set_info(query_shadow_who(), "Buttkicked", 1);
    TELL_G("Buttkick engaged for " + query_shadow_who()->query_real_name());

    set_alarm(60.0, 0.0, end_buttkick);
} /* get_buttkicked */


/*
 * Function name:        end_buttkick
 * Description  :        The buttkicking is over now.
 */
public void
end_buttkick()
{
    AOD_MASTER->set_info(query_shadow_who(), "Buttkicked", 0);
} /* end_buttkick */