/*
 * This is the autoloading shadow for the Cabal of Hiddukel thief guild.
 *
 * originally taken from the Knights guild shadow by Nick
 * Modified by Aridor
 */

inherit "/std/guild/guild_lay_sh";

#include "/d/Krynn/common/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <language.h>
#include <macros.h>
#include <formulas.h>
#include <files.h>

#define THIEF_SUB "cabal_of_hiddukel_subloc"

// Prototypes
int query_thief_level();

private int expl_alrm = 0;
private int level = 0;
private int autosneak_on = 0;

/* Function name: query_guild_train
 * Description:   Give all the training objects
 */
string
query_guild_trainer_lay()
{
    return GUILDR + "train";
}

/*
 * Function name: query_guild_tax
 * Description:   Set the initial tax
 */
int 
query_guild_tax_lay() 
{
    int level = query_thief_level();
    return TAX[level];
}

/*
 * Function name: query_guild_style_lay
 * Description:  Return the style of the guild
 */
string 
query_guild_style_lay() 
{
    return "thief"; 
}

/*
 * Function name: query_guild_name_lay
 * Description:  Query the name of the guild
 */
string 
query_guild_name_lay() 
{
    return GUILD_NAME; 
}

/*
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 * Arguments:     ob - the player.
 * Returns:  1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    ob->add_subloc(THIEF_SUB, this_object()); 
    return 1;
}


/*
 * Function name: query_guild_not_allow_join_lay
 * Description:  Check if we allow that the player joins another guild.
 * Arguments:     player - the player
 *  type, style, name - the type, style and name of the
 *  intended guild.
 * Returns:  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_lay(object player, string type, string style,
                               string name)
{
    NF("You are already a member of another layman guild!\n");
    if (::query_guild_not_allow_join_lay(player, type, style, name))
      return 1;
    
    /* Well, I noticed that Hiddukel deals in magic, too, so I guess
     * I'll comment this restriction.
    NF("Magic is very suspicious! We thieves don't mess with magic.\n");
    if (style == "magic")
      return 1;
      */

    NF("We thieves don't want any other thieves in our ranks.\n");
    if (style == "thief")
      return 1;
    
    return 0;
}

int
query_guild_leader_lay()
{
    return (MASTER_ROOM->is_master(shadow_who));
}

/*
 * Function name: recalculate_tax
 * Description:   Update the tax of the member.
 */
void
recalculate_tax(int new_level)
{
    int new_tax;
    
    new_tax = TAX[new_level];
    /* Update the tax if the new tax differs from the old tax. */
    if (new_tax != shadow_who->query_learn_pref(SS_LAYMAN))
    {
        shadow_who->set_guild_pref(SS_LAYMAN, new_tax);
    }
}

/*
 * Function name: query_thief_level
 * Description:   What level has the thief achieved among the Cabal?
 * Returns:  the level
 */
int
query_thief_level()
{
    int al, newlevel, newlevel1, newlevel2, newlevel3, newlevel4,
        numlevels = sizeof(TAX);

    newlevel1 = (shadow_who->query_base_stat(SS_LAYMAN) * numlevels / 140);
    newlevel2 = (shadow_who->query_skill(SS_STOLEN) * numlevels / 15000);
    newlevel3 = (shadow_who->query_skill(SS_SACRIFICE) * numlevels / 100000);
    newlevel4 = (newlevel1 + newlevel2 + newlevel3) * 2 / 3;

    newlevel = max(newlevel1,newlevel2,newlevel3,newlevel4);
    newlevel = min(newlevel, newlevel1 + 1);

    newlevel -= (((al = shadow_who->query_alignment()) > 0) ? (al / 300) : 0);

    newlevel = (((newlevel >= numlevels) ? (numlevels - 1) : newlevel));
    newlevel = (newlevel < 0 ? 0 : newlevel);
    if (newlevel != level)
    {
        level = newlevel;
    }
    return level;
}


/*
 * Function name: query_thief_title
 * Description:   What is the title of this thief ?
 * Returns:  The thief title
 */
string
query_thief_title()
{
    object *players;
    int notch = 1;
    int i, j = shadow_who->query_stat(SS_LAYMAN);
    int lev = query_thief_level();
    players = users();
    if (shadow_who->query_wiz_level())
      return "Wizzed Burglar of the Cabal of Hiddukel";
    for (i = 0; i < sizeof(players); i++)
    {
        if (players[i]->query_guild_name_lay() == GUILD_NAME &&
            !players[i]->query_wiz_level() &&
            players[i]->query_thief_level() == lev &&
            (players[i]->query_stat(SS_LAYMAN) > j ||
             players[i]->query_stat(SS_LAYMAN) == j &&
             players[i]->query_acc_exp(SS_LAYMAN) > shadow_who->query_acc_exp(SS_LAYMAN)))
          notch++;
    }
    return C(LANG_WORD(notch)) + " " + C(LAY_TITLES[lev]) +
      " Burglar of the Cabal of Hiddukel";
}

/* Function name: query_guild_title_lay
 * Description:   give the guild title
 * Arguments:     none
 * Returns:       the guild title if shown
 */
string
query_guild_title_lay()
{
    if (!(P(THIEF_OBJ_ID,shadow_who)->query_show_title_on_intro()))
      return 0;
    else if (MASTER_ROOM->query_right_hand(shadow_who))
      return "Right Hand of the Cabal of Hiddukel";
    else
      return query_thief_title();
}

/*
 * Function name: query_guild_incognito_lay
 * Description:   Define this function so that it returns true if
 *                the player's guild affiliation should be unknown.
 * Returns:       1/0 - unknown/not
 */
int
query_guild_incognito_lay()
{
    return (!(P(THIEF_OBJ_ID,shadow_who)->query_show_title_on_intro()));
}


/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - Our subloc
 *  me      - I
 *  for_obj - The looker
 * Returns:  The string the looker shall see
 */
string
show_subloc(string subloc, object me, object for_obj)
{
    string str;
    int i, aware, hidden;
    object arm;
    
    if (subloc != THIEF_SUB)
      return shadow_who->show_subloc(subloc, me, for_obj);
    
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "";

    if (for_obj == me)
    {
        str = "You have a tattoo of a broken balance on your left shoulder";
        if (me->query_armour(A_BODY) || me->query_armour(A_ROBE))
          str += " (concealed)";
        str += ".\n";
    }
    else /*show the subloc to others only if they really can see it!*/
    {
        /*aware = for_obj->query_skill(SS_AWARENESS);
          hidden = me->query_skill(SS_HIDE);
          if (arm = me->query_armour(A_NECK))
          hidden = 2 * hidden + (i = arm->query_ac()) + 5 * i + random(i);
          if (for_obj->query_wiz_level() || (aware >= hidden) || MEMBER(for_obj))
            str = capitalize(me->query_pronoun()) +
              " has a tattoo of a broken balance on " + (me->query_possessive()) +
                " neck.\n";*/
        if (me->query_armour(A_BODY) || me->query_armour(A_ROBE))
          str = "";
        else
          str = capitalize(me->query_pronoun()) +
            " has a tattoo of a broken balance on " + (me->query_possessive()) +
            " left shoulder.\n";
    }
    return str;
}

#if ALIGNRESTRICT
void
check_alignment_expel_if_necessary()
{
    if (shadow_who->query_alignment() > 120)
      (JOIN_ROOM)->expel_member_from_guild(shadow_who->query_real_name(),
                                           " your alignment shows that you " +
                                           "did not follow the path of " +
                                           "Hiddukel for too long.");
}

void
set_alignment(int num)
{
    if (num > 100 && !expl_alrm)
    {
        shadow_who->catch_msg("\nA shadow washes over you and settles " +
                              "into your soul.\nThe shadow speaks and you " +
                              "are certain this is Hiddukel, the patron " +
                              "of the Cabal.\nHe tells you: Your " +
                              "alignment is tilting too far to the holy " +
                              "end of the scale! If you don't correct " +
                              "this mistake immediately, you will be expelled from " +
                              "the guild.\nHe then withdraws from you " +
                              "and disappears.\n\n");
        expl_alrm = set_alarm(3000.0,0.0,"check_alignment_expel_if_necessary");
    }
    else if (num <= 100 && expl_alrm)
    {
        remove_alarm(expl_alrm);
        expl_alrm = 0;
    }
    shadow_who->set_alignment(num);
}
#endif

/*
 * Function name: set_alignment
 * Description  : Set the amount of alignment points of the living. There is
 *                a maximum alignment a player can get. There is a Dutch
 *                proverb about trying to be more Roman-Catholic than the
 *                pope himself. We don't need that.
 * Arguments    : int a - the new alignment.
 *
void
set_alignment(int a)
{
    shadow_who->set_alignment(min(a,0));
}
*/

/*
 * Function name: adjust_alignment
 * Description  : When a player has solved a quest, his alignment may be
 *                adjusted if the quest is considered good or evil. This
 *                may only be done when the player receives experience and
 *                the quest bit is subsequently being set. When a quest is
 *                considered solvable for all players in the game, ie both
 *                'good' and 'evil' players, no alignment should be given
 *                out.
 * Arguments    : int align - the alignment of the quest. this should be
 *                            a value in the range -1000 .. 1000 and acts
 *                            the same as alignment in combat, though in
 *                            this case, 'good' players should naturally
 *                            receive positive alignment (ie solve good
 *                            quests).
 *
public void
adjust_alignment(int align)
{
    if (ABS(align) > F_MAX_ABS_ALIGNMENT)
    {
        align = ((align > 0) ? F_MAX_ABS_ALIGNMENT : -F_MAX_ABS_ALIGNMENT);
    }

    set_alignment(alignment + F_QUEST_ADJUST_ALIGN(alignment, align));
}
*/

/*
 * Function name: query_guild_skill_name
 * Description:   When a players uses the skills command he should get the
 *  the skill names, not the 'special' string.
 * Arguments:     type - the number of the skill
 * Returns:  0 if no skill of mine, else the string. "" if skill not shown.
 */
mixed
query_guild_skill_name(int type)
{
    if (type == SS_SACRIFICE ||
        type == SS_STOLEN)
    {
        return "";
    }
    
    return 0;
}


/* Autosneak-code taken from the ranger shadow with permission of Elessar.
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


/*
 * Function name:   check_seen
 * Description:     True if this object can be seen by a given object, this has
 *                  been masked to always show themselves to team members.
 * Arguments:       (object) for_obj - The object for which visibility should be
 *                                     checked
 * Returns:         (int) 1 - if this object can be seen.
 */
public int
check_seen(object for_obj)
{
    if (member_array(for_obj, shadow_who->query_team_others()) > -1)
        return !(!objectp(for_obj) || shadow_who->query_no_show() ||
                (!for_obj->query_wiz_level() &&
                (for_obj->query_prop(LIVE_I_SEE_INVIS) <
                shadow_who->query_prop(OBJ_I_INVIS))));
    
    return shadow_who->check_seen(for_obj);
} /* check_seen */

int
hook_thief_steal_bonus(object victim, object place, object what)
{
    int al = shadow_who->query_alignment();
    int sk = shadow_who->query_skill(SS_SACRIFICE);

    /* Punished? */
    if (MASTER_ROOM->is_punished(shadow_who))
      sk = -700;

    if (sk <= -700)
      sk = -700;
    if (sk <= 0)
      return sk;

    sk = SACRIFICE_2_BONUS(shadow_who);
    if (sk < 0)
      sk = 0;
    if (sk > 500)
      sk = 500;
    if (al > 0)
      /*sk -= (al * 2 / 3);*/
      sk /= (al / 300 + 1);

    return sk;
}

#if 0
void
hook_thief_stolen_object(object what, object victim, object place)
{
    int value = what->query_value(); /* in coppers */
    int sk = shadow_who->query_skill(SS_SACRIFICE);
    sk -= (value / 10);
    shadow_who->set_skill(SS_SACRIFICE, sk);

    sk = shadow_who->query_skill(SS_STOLEN);
    shadow_who->set_skill(SS_STOLEN, sk + 1 +
        ((CMD_LIVE_THIEF)->query_thief_success()));
}
#endif
