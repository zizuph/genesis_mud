// Navarre: June 1st 2008: Added Drow race to be allowed.

#pragma strict_types

inherit "/std/guild/guild_lay_sh";

#include "guild.h"

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>


#define GUILD_SUBLOC  GUILD_NAME + " subloc"
#define MAX_GUILD_LEVEL 12

#define SW shadow_who

static string *mtitles = ARCHER_MTITLES;
static string *ftitles = ARCHER_FTITLES;
static string *emtitles = ARCHER_EMTITLES;
static string *eftitles = ARCHER_EFTITLES;

private int autosneak_on = 0;

/* Prototypes */
void remove_lay_member();

/*
 * Function name: query_guild_tax_lay
 * Description:   Give the amount of tax the guild charges
 * Returns:       int - The tax amount
 */
int
query_guild_tax_lay()
{
    return GUILD_TAX;
}

/*
 * Function name: query_guild_style_lay
 * Description:   return the guild style for this guild
 * Returns:       string - the style
 */
string
query_guild_style_lay()
{
    return GUILD_STYLE;
}

/*
 * Function name: query_guild_name_lay
 * Description:   return the guild's name
 * Returns:       string - the guild name
 */
string
query_guild_name_lay()
{
    return GUILD_NAME;
}

/*
 * Function name: acceptable_member
 * Description:   test to see if the player is an acceptable member of this
 *                guild.
 * Arguments:     object who - the player to test
 * Returns:       0 or a string message saying why the player isn't acceptable
 */
mixed
acceptable_member(object who)
{
    /* throw out non elves */
    if ((who->query_race_name() != "elf") &&
        (!who->query_ghost()) &&
        (who->query_race_name() != "half-elf") &&
        (who->query_guild_name_race() != "Eil-Galaith") &&
        (who->query_race_name() != "drow"))
    {
        return "Only elves may walk the realms as elven archers!\n";
    }

    if (who->query_guild_name_occ() == GUILD_NAME)
    {
        return "You are already an elven archer!\n";
    }

    return 0;
}

/*
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 * Arguments:     ob - the player.
 * Returns:   1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    mixed why;

    if (stringp(why = acceptable_member(ob)))
    {
        ob->catch_msg(why);
        set_alarm(350.0, 0.0, remove_lay_member);
        return 1;
    }

    return 1;
}

/*
 * Function name: query_guild_not_allow_join_lay
 * Description:   Check if we allow the player to join another guild.
 * Arguments:     player - the player
 *        type, style, name - the type, style and name of the
 *          intended guild.
 * Returns:   1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_lay(object player, string type, string style,
                string name)
{
    /* This checks to make sure that the new guild is not layman */
    if (::query_guild_not_allow_join_lay(player, type, style, name))
        return 1;

    return 0;
}

/* Function name: query_guild_level_lay
 * Description:   What is the member's level within the guild?
 * Returns:   int - the level
 */
int
query_guild_level_lay()
{
    return MIN(MAX_GUILD_LEVEL, query_shadow_who()->query_stat(SS_LAYMAN) / 10);
}

/* Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:   string - the path to the new postoffice
 */
string
query_def_post()
{
    return query_shadow_who()->query_def_post();
}

/*
 * Function name: query_guild_title_lay
 * Description:   Return the member's guild title
 * Returns:       string - the title
 */
string
query_guild_title_lay()
{
    if(query_shadow_who()->query_race_name() == "half-elf")
    {
        return "Half-elven Archer";
    }

    if(query_shadow_who()->query_race_name() == "drow")
    {
        return "Drow Archer";
    }

    if(query_shadow_who()->query_gender() == G_FEMALE)
    {
       if(query_shadow_who()->query_alignment() < -100)
       {
           return eftitles[query_guild_level_lay()];
       }
       else
       {
           return ftitles[query_guild_level_lay()];
       }
    }
    if(query_shadow_who()->query_alignment() < -100)
    {
        return emtitles[query_guild_level_lay()];
    }
    else
    {
        return mtitles[query_guild_level_lay()];
    }
}

/*
 * Function name: query_guild_skill_name
 * Description:   Give a names for the guild's special skills
 * Arguments:     type - the number of the skill
 * Returns:   0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    return 0;
}

/*
 * Function name: query_guild_trainer_lay
 * Description:   Returns the skill trainers for the guild
 * Returns:       string * - an array of paths to the guild's
 *                trainers.
 */
mixed
query_guild_trainer_lay()
{
    return ({ GUILD_DIR + "joinroom" });
}

/*
 * Function name: init_guild_member
 * Description:   Add necessary guild items to the player and
 *                do any other kind of initialization necessary.
 */
void
init_guild_member()
{
    object guild_emblem, who = query_shadow_who();

    /* clone the guild emblem and move it to the player */

    setuid();
    seteuid(getuid());

    if (START_ROOM->update_player_guild(who, SS_LAYMAN))
        return;

    if (guild_emblem = clone_object(GUILD_EMBLEM))
    {
        guild_emblem->move(who, 1);
    }

    /* add the guild's soul to the player */
    who->add_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();

    /* add the guild subloc */
    who->add_subloc(GUILD_SUBLOC, this_object());
}

/*
 * Function name: start_player
 * Description:   This is called when the player logs in.
 */
public void
start_player()
{
    SW->start_player();
    init_guild_member();
}

/*
 * Function name: add_lay_shadow
 * Description:   Shadow an object with this shadow
 * Arguments:     object who - the object to shadow
 * Returns:       as shadow_me in /std/guild/guild_base.c
 *                or -5 if who argument isn't an object
 */
int add_lay_shadow(object who)
{
    int ret = shadow_me(who, "layman", GUILD_STYLE, GUILD_NAME);

    if (ret == 1)
    {
        init_guild_member();
    }

    return ret;
}



/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *        me      - I
 *        for_obj - The looker
 * Returns:   The string the looker shall see
 */

/*
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;

    if (subloc != GUILD_SUBLOC)
    {
        return me->show_subloc(subloc, me, for_obj);
    }

    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
    return "";
    }

    if (for_obj == me)
    {
    str = "You are ";
    }
    else
    {
    str = capitalize(me->query_pronoun()) + " is ";
    }

    return str + "a member of the " + GUILD_NAME + ".\n";
}
*/


/*
 * Function name: remove_lay_member
 * Description:   remove this member from the guild
 */
void
remove_lay_member()
{
    object emblem, who = query_shadow_who();

    /* Clear the player's guild stat */
    who->clear_guild_stat(SS_LAYMAN);

    /* Remove any instances of the guild emblem on the player */
    while (emblem = present(GUILD_EMBLEM_ID, who))
    {
        emblem->remove_object();
    }

    /* Remove the guild soul */
    who->remove_cmdsoul(GUILD_CMDSOUL);
    who->update_hooks();

    /* Remove the guild shadow.  This also resets tax to 0. */
    remove_guild_lay();
}

/* Autosneak-code taken from the Cabal of Hiddekul code
 */
public void
set_autosneak(int a)
{
    autosneak_on = a;
}

public int
query_autosneak()
{
    return autosneak_on;
}

public varargs int
move_living(string how, mixed to_dest, int dont_follow, int no_glance)
{
    int hiding, retval, val, bval, did_sneak;
    object me;

    me = shadow_who;

    if (!me->query_prop(LIVE_I_SNEAK) &&
        autosneak_on &&
        query_verb() &&
        !(me->query_prop(OBJ_I_LIGHT) && (me->query_prop(OBJ_I_LIGHT) >
            environment(me)->query_prop(OBJ_I_LIGHT))) &&
        !(objectp(me->query_attack()))
        )
    {
        hiding = environment(me)->query_prop(ROOM_I_HIDE);
        bval = me->query_skill(SS_SNEAK) * 2 + me->query_skill(SS_HIDE) / 3;
        bval = (bval - hiding) / 2;

        if (hiding >= 0 && bval > 0)
        {
            val = bval + random(bval);
            me->add_prop(OBJ_I_HIDE, val);
            me->add_prop(LIVE_I_SNEAK, 1);
            did_sneak = 1;
        }
        if (!did_sneak)
            tell_object(me, "You failed to sneak.\n");
    }

    retval = me->move_living(how, to_dest, dont_follow, no_glance);

    if (!did_sneak)
        return retval;

    hiding = environment(me)->query_prop(ROOM_I_HIDE);
    bval = me->query_skill(SS_HIDE);
    bval = (bval - hiding) / 2;

    set_this_player(me);
    if (hiding < 0 || bval <= 0)
    {
        write("It's too difficult to hide in here, you're visible again.\n");
        me->reveal_me(0);
    }
    else if (me->query_prop(OBJ_I_LIGHT) &&
        (me->query_prop(OBJ_I_LIGHT) >
        environment(me)->query_prop(OBJ_I_LIGHT)))
    {
        write("You can't hide here, shining like that!\n");
        me->reveal_me(1);
    }

    val = bval + random(bval);
    me->add_prop(OBJ_I_HIDE, val);
    return retval;
}

