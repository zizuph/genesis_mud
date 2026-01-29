/*
 * This is the autoloading shadow for the Solamnian Knight guild.
 *
 * Made by Nick (updated march 93 by Nick and Percy)
 *    updated query_ob_prestige() function 11/24/94  Grace
 * 
 * Added option to join Shieldbearers by dwarven knights, 28/01/2004, Blizzard
 * With Arman's permission - Added option to join Blademaster of Khalakhor
 * 01/31/05, Damaris.
 * August 28 2005 Louie - Allow Gardeners and Archers to join.
 *
 * 2018-11-13: Fixed a bug in the team discipline bonus, it was moved to the
 *             rose_teammate_shadow in the specials/objects directory.
 *             - Carnak
 */
inherit "sys/global/math.c";
inherit "/std/guild/guild_occ_sh";
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/clubs/warfare/defs.h"
#include "../guild.h"
#include <ss_types.h>
#include <language.h>
#include <options.h>
#include <macros.h>

#include "/d/Genesis/specials/debugger/debugger_tell.h"

#define SOL_SUB "solamnian_subloc"
#define MERCYFUL "_knight_mercyful"
#define DEBUG(x) send_debug_message("knight_shadow", x)
#define ROSE_TEAMMATE_SHADOW (SPECIALS + "objects/rose_teammate_shadow")

/*
 * Prototypes
 */
int query_level_up(int stat, int level);
int query_level_down(int stat, int level);
int query_knight_level();
int query_knight_sublevel();
int query_ob_prestige(object ob);

void change_prestige(int pres, int minusflag);

/*
 * Variables
 */
object *att_ob;/* Objects attacked by me first */
object *att_me;/* Objects that attacked me first */
mapping pres_loss;/* Objects I ran away from and lost prestige */
int evilcheckalarm = 0; /*alarm that runs when i'm evil*/

/*
 * Rose Knight Special: Add SS_DIS to team members in a team lead
 * by a Rose Knight.
 *
 * Arguments: object new_team_member, the player who is joining the team.
 *
 * Returns: int, 1 if the player was added, 0 if not.
*/
public int
team_join(object new_team_member)
{
    int did_join = shadow_who->team_join(new_team_member);

    if (query_knight_level() == L_ROSE && did_join)
    {
        // We clone the Rose Teammate Shadow to help them handle dragonfear when
        // appropriate, discipline boost is contained within.
        object rose_teammate_shadow = clone_object(ROSE_TEAMMATE_SHADOW);
        catch(rose_teammate_shadow->shadow_me(new_team_member));
        
        // It is quite unlikely that this fails, but had the description
        // ready from old code, so figured we might aswell add it.
        if (!new_team_member->add_rose_knight_discipline(shadow_who))
            new_team_member->catch_msg("The leadership of "
            + shadow_who->query_real_name() + " is very inspiring, but does "
            + "not affect you.\n");
    }

    return did_join;
}


/*
 * Rose Knight Special: Remove stat_extra from people who leave teams
 * lead by a Rose Knight.
 *
 * Arguments: object leaving member. The players who is leaving the team.
 *
 * Returns: void.
*/
public void
team_leave(object leaving_member)
{
    // remove the teammate shadow
    if (query_knight_level() == L_ROSE)
        leaving_member->remove_rose_teammate_shadow();

    shadow_who->team_leave(leaving_member);
    return;
}

/* Function name: query_guild_train
 * Description:   Give all the training objects
 */
string *
query_guild_trainer_occ()
{
    return ({ VROOM + "train1", VROOM + "train2",
      VROOM + "west_train1", VLIB + "library", VROOM + "east_train2",
      VROOM + "inner_court" });
}

/* Query_stat modification to enable Knight of the Rose ability to lead
* anyone by Morrigan and RastlinNov 96
*/

/* Guild-specific adverbs added by Morrigan, 3-12-97 */
string
full_adverb(string str)
{
    if (strlen(str) > 2)
    {
    if (wildmatch(str + "*", "nobly"))
        return "nobly";

    if (wildmatch(str + "*", "sternly"))
        return "sternly";

    if (wildmatch(str + "*", "honourably"))
        return "honourably";

    if (wildmatch(str + "*", "coolly"))
        return "coolly";

    if (wildmatch(str + "*", "fearlessly"))
        return "fearlessly";

    if (wildmatch(str + "*", "gallantly"))
        return "gallantly";

    if (wildmatch(str + "*", "valiantly"))
        return "valiantly";

    if (wildmatch(str + "*", "reverently"))
        return "reverently";

    if (wildmatch(str + "*", "victoriously"))
        return "victoriously";

    if (wildmatch(str + "*", "daringly"))
        return "daringly";

    if (wildmatch(str + "*", "dauntlessly"))
        return "dauntlessly";
    }

    return query_shadow_who()->full_adverb(str);
}


/*
 * Function name: query_guild_tax
 * Description:   Set the initial tax
 */
int
query_guild_tax_occ()
{
    return shadow_who->query_learn_pref(SS_OCCUP);
}

/*
 * Function name: query_guild_style_occ
 * Description:  Return the style of the guild
 */
string
query_guild_style_occ()
{
    return "fighter";
}

/*
 * Function name: query_guild_name_occ
 * Description:  Query the name of the guild
 */
string
query_guild_name_occ()
{
    return GUILD_NAME;
}

/*
 * Function name: query_guild_keep_player
 * Description:   Test if we want to keep the player in the guild.
 *  If we discover a goblin we will keep him, just to throw him
 *  out the proper way later.
 * Arguments:     ob - the player.
 * Returns:  1 if keeping, 0 if not.
 */
int
query_guild_keep_player(object ob)
{
    int prestige, delayed = 0;

    ob->add_subloc(SOL_SUB, this_object());

    /* Delay the first check by one minute, to allow
      racial guilds the chance to load and convert elves
      to half-elves */
    if (!delayed)
    {
        delayed = 1;
        set_alarm(60.0, 0.0, "query_guild_keep_player", ob);
        return 1;
    }

    if (   (ob->query_race_name() != "half-elf")
        && (ob->query_race_name() != "dwarf")
        && (ob->query_race_name() != "human"))
    {
        // Remove ALOT of prestige
        prestige = ob->query_skill(SS_PRESTIGE_ST);

        if (prestige > 1)
            prestige = prestige / 2;
        else if ( prestige < 0 )
           prestige = prestige * 2;
        else if ( prestige <= 1 )
           prestige -= 1000;

        write("Your race is not fit to serve as Knight of Solamnia!\n");
        set_alarm(1.0,0.0,"change_prestige", prestige, 1);
        set_alarm(300.0,0.0,"query_guild_keep_player", ob);


    }

    if (ob->query_alignment() < -20)
    {
    write("You are evil, this will not be good for your prestige!\n");
    if (!evilcheckalarm)
        evilcheckalarm = set_alarm(180.0,0.0,"evil_check");
    }

    return 1;
}

/*
 * Function name: evil_check
 * Description:   This function is called now and then to see if the Knight is
 *  evil. If he is he will lose prestige, if he is a goblin he
 *  will be thrown out and banished from the guild. Non goblins
 *  will still have the chance to turn to the right path.
 */
void
evil_check()
{
    int loss;

    evilcheckalarm = 0;
    if (this_object()->query_alignment() < -20)
    {
    loss = -900 * query_knight_level() + 899;
    change_prestige(loss, 1);
    /* Any incarnation of goblins aren't what we want */
    if (this_object()->query_race() == "goblin")
        ADMIN->goblin_leave(shadow_who);
    else if (shadow_who->query_skill(SS_PRESTIGE_ACC) > 0)
        evilcheckalarm = set_alarm(180.0,0.0,"evil_check");
    }
}

/*
 * Function name: set_alignment
 * Description:   Sets the alignment of a player, we will check if knights
 *  are closing evilness
 * Arguments:     a: The amount of points
 */
void
set_alignment(int a)
{
    int old_a;

    if ((old_a = shadow_who->query_alignment()) > -20 && a < ALIGN_WARNING && a < old_a)
    write("Your alignment is dropping dangerously low!\n");

    shadow_who->set_alignment(a);
    if (a < -20 && !evilcheckalarm)
    evilcheckalarm = set_alarm(20.0,0.0,"evil_check");
}

/*
 * Function name: query_guild_not_allow_join_occ
 * Description:  Check if we allow that the player joins another guild.
 * Arguments:     player - the player
 *  type, style, name - the type, style and name of the
 *intended guild.
 * Returns:  1 if we do not allow, else 0
 */
int
query_guild_not_allow_join_occ(object player, string type, string style,
  string name)
{
    mapping allowed_guilds;
    string shadow_name;
    
    if (::query_guild_not_allow_join_occ(player, type, style, name))
        return 1;

    NF("The Knighthood demands the utmost loyalty and dedication.\n");
    setuid();
    seteuid(getuid());
    
    if (type == "layman")
    {
        allowed_guilds = LAYMAN_MANAGER->query_allowed_laymans();
        foreach (string guild : m_indices(allowed_guilds))
        {
            if (allowed_guilds[guild] == name)
            {
                // Found the guild in the allow list. We return 0 and allow
                // this to proceed.
                return 0;
            }
        }        

        if (objectp(previous_object()))
        {
            shadow_name = MASTER_OB(previous_object()) + ":";
            send_debug_message("knight_shadow", "Previous object checking "
                + "allowed guild is: " + MASTER_OB(previous_object()));
            
            if (previous_object()->query_guild_type() == "layman"
                && previous_object()->query_guild_name_lay() == name)
            {
                foreach (string autosh : player->query_autoshadow_list())
                {
                    if (!wildmatch(shadow_name + "*", autosh))
                    {
                        continue;
                    }
                    send_debug_message("knight_shadow", "Allowing layman "
                        + "guild because it is already in the player "
                        + "autoshadow list.");
                    return 0;
                }
            }
        }
            
        return 1;
    }
    
    // We don't restrict racial or craft guilds
    return 0;
}

/*
 * Function name: query_knight_level
 * Description:   What level has the knight achieved in the Knighthood ?
 * Returns:  the level
 */
int
query_knight_level()
{
    object ob;

    if (ob = P("pal_med", shadow_who))
    return ob->query_knight_level();
    return 0;
}

/*
 * Function name: set_knight_level
 * Description:  Sets the Knight's level
 */
set_knight_level(int level)
{
    object ob;

    if (ob = P("pal_med", shadow_who))
    ob->set_knight_level(level);
}

/*
 * Function name: query_knight_sublevel
 * Description:   What sublevel have the knight achieved in his Order ?
 * Returns:  the sublevel
 */
int
query_knight_sublevel()
{
    object ob;

    if (ob = P("pal_med", shadow_who))
    return ob->query_knight_sublevel();
    return 0;
}

/* Added to give Council and Conclave 75 possible mails */
/* By Morrigan, 1/97. */
public int
query_guild_leader_occ()
{
    if ((ADMIN)->is_grandmaster(shadow_who->query_real_name()) ||
        (ADMIN)->is_conclave(shadow_who->query_real_name()) ||
        (ADMIN)->is_assistant(shadow_who->query_real_name()))
    return 1;

    return 0;
}

/*
 * Function name: query_def_post
 * Description:   We change the default post office for our members.
 * Returns:  The new postoffice
 */
string
query_def_post() { return VROOM + "knight_po"; }

/* Function name: set_grandmaster
 * Description:   Call it to set the player to grand master
 */
void
set_grandmaster(int yes)
{
    object ob;
    if (!(ob = P("pal_med", shadow_who)))
    return;
    if (yes)
    {
    ob->set_knight_sublevel(11);
    shadow_who->catch_msg("You have been promoted to Grand Master!\n");
    }
    else
    {
    change_prestige(0,1);
    shadow_who->catch_msg("You have been demoted from the Grand Master " +
      "position!!\n");
    }
}

/*
 * Function name: set_high
 * Description:   Call it to promote the player to conclave member
 */
void
set_high(int lvl)
{
    object ob;
    int my_lev = query_knight_level();
    if (lvl != my_lev)
    return;
    if (!(ob = P("pal_med", shadow_who)))
    return;
    ob->set_knight_sublevel(11);
    if (my_lev == 3)
    {
        if ((ADMIN)->query_conclave("crown") != "")
            return;
        if (lower_case((ADMIN)->crown_highest()) == shadow_who->query_name())
            (ADMIN)->set_crown_high(12, "none");
        (ADMIN)->add_conclave(capitalize(shadow_who->query_name()), "crown");
    }
    else if (my_lev == 4)
    {
        if ((ADMIN)->query_conclave("sword") != "")
            return;
        if (lower_case((ADMIN)->sword_highest()) == shadow_who->query_name())
        {
            (ADMIN)->set_sword_high(12, "none");
        }
        (ADMIN)->add_conclave(capitalize(shadow_who->query_name()), "sword");
    }
    else if (my_lev == 5)
    {
        if ((ADMIN)->query_conclave("rose") != "")
            return;
        if (lower_case((ADMIN)->rose_highest()) == shadow_who->query_name())
        {
            (ADMIN)->set_rose_high(12, "none");
        }
        (ADMIN)->add_conclave(capitalize(shadow_who->query_name()), "rose");
    }
    shadow_who->catch_msg("You have been promoted to the conclave!\n");
}

/*
 * Function name: clear_high
 * Description:   Call it to demote the player from conclave member
 */
void
clear_high(int lvl)
{
    object ob;

    if (!(ob = P("pal_med", shadow_who)))
    return;
    seteuid(getuid(ob));

    if (lvl == 3)
    (ADMIN)->remove_conclave("crown");
    if (lvl == 4)
    (ADMIN)->remove_conclave("sword");
    if (lvl == 5)
    (ADMIN)->remove_conclave("rose");

    ob->set_knight_sublevel(10);
    shadow_who->catch_msg("You have been demoted from the conclave!\n");
}

/*
 * Function nam: prefix_title
 * Description:  Find any additional titles (like Disgraced, Honoured, etc.)
 * Returns:      that additional title
 */
string
prefix_title()
{
    int disgr = 0;
    string award = 0;
    int tmp;
    object ob;
    string str = "";
    //return "";

    /* check disgraced */
    tmp = shadow_who->query_skill(SS_DISGRACED);
    if (tmp > REALAGE(shadow_who))
    disgr = 1;
    else
    shadow_who->remove_skill(SS_DISGRACED);

    /* check awards */
    award = (ADMIN)->query_my_awards(shadow_who);

    if (disgr && award)
    str = "Admonished ";
    else if (disgr)
    str = "Disgraced ";
    else if (award)
    str = "Honoured ";
    return str;
}

/*
 * Function name: query_knight_subtitle
 * Description:   What is the subtitle of this knight ?
 * Returns:  The Knight subtitle
 */
string
query_knight_subtitle()
{
    int gend;
    gend = shadow_who->query_gender();

    if (IS_GRANDMASTER(shadow_who))
    return GRANDMASTER_TITLE[gend];

    if (query_knight_level() == 1)
    {
    return "Black Knight of the Rose";
    }

    if (query_knight_level() == 2)
    {
    return SQUIRE_TITLES[query_knight_sublevel()];
    }

    if (query_knight_level() == 3)
    {
    if (gend == 0)
        return CROWN_TITLES[query_knight_sublevel()];
    else
        return FCROWN_TITLES[query_knight_sublevel()];
    }

    if (query_knight_level() == 4)
    {
    if (gend == 0)
        return SWORD_TITLES[query_knight_sublevel()];
    else
        return FSWORD_TITLES[query_knight_sublevel()];
    }

    if (query_knight_level() == 5)
    {
    if (gend == 0)
        return ROSE_TITLES[query_knight_sublevel()];
    else
        return FROSE_TITLES[query_knight_sublevel()];
    }

    return "Buggy Knight of Solamnia";
}

/*
 * Function name: query_knight_title
 * Description:   What is the title of this knight ?
 * Returns:  The Knight title
 */
string
query_knight_title()
{
    if (query_knight_level() == 1)
    return "Knight of the Black Rose";

    return prefix_title()+query_knight_subtitle();
}

/*
 * Function name: query_guild_title_occ
 * Description:   Find the occupational title of the knight.
 * Returns:       The occupational knight title.
 */
string
query_guild_title_occ()
{
    return query_knight_title();
}

/*
 * Function name: query_guild_skill_name
 * Description:   When a players uses the skills command he should get the
 *  the skill names, not the 'special' string.
 * Arguments:     type - the number of the skill
 * Returns:  0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
    if ((type >= SS_PRESTIGE_ACC && type <= SS_CHARITY) ||
      type == SS_DISGRACED)
    return "";

    if (type == SS_BLOCK)
    {
        return "block";
    }
    
    if ((type < SS_RESCUE) || (type > SS_KATTACK))
    return 0;

    return KNIGHT_SKILL_DESC[type - SS_RESCUE];

}

/*
 * Function name: q_att_ob
 * Description:  Keeps track of objects I attacked first
 */
object *
q_att_ob()
{
    if (!att_ob)
    att_ob = ({});

    return att_ob;
}

/*
 * Function name: q_att_me
 * Description:  Objects that attacked me first
 */
object *
q_att_me()
{
    if (!att_me)
    att_me = ({});

    return att_me;
}

/* Function name: check_charity
 * Description:  Check the players charity pts to see if high enough
 * Arguments:  val = value of the object being compared
 * Returns:  0 if fails else 1
 */
int
check_charity(int val)
{
    int total;

    total = shadow_who->query_skill(SS_CHARITY);
    total -= val;
    if (total < 0)
    return 0;
    return 1;
}

/* Function name: add_charity
 * Description:  adds on charity pts
 * Arguments:  val = value of the object being added
 */
void
add_charity(int val)
{
    int oldskill;

    oldskill = shadow_who->query_skill(SS_CHARITY);
    oldskill += val;
    shadow_who->set_skill(SS_CHARITY, oldskill);

}

/* Function name: sub_charity
 * Description:  subtract charity pts
 * Arguments:  val = value of the object being subtracted
 */
void
sub_charity(int val)
{
    int oldskill;

    oldskill = shadow_who->query_skill(SS_CHARITY);
    oldskill -= val;
    shadow_who->set_skill(SS_CHARITY, oldskill);

}

int
prestige_stat_to_exp(int stat)
{
    /*return shadow_who->stat_to_exp(stat);*/
    /*since the changed stat formula, we use the old formula still:*/
    return (ftoi(pow(itof(stat), 3.0)) + 1);
}

int
prestige_exp_to_stat(int xp)
{
    /*return shadow_who->exp_to_stat(xp);*/
    /*since the changed stat formula, we use the old formula still:*/
    if (xp <= 0)
    {
        // A negative prestige ends up with lowest possible stat of 1
        return 1;
    }
    return (ftoi(pow(itof(xp), 0.33333333)));
}

/*
 * Function name: sub_prestige
 * Description:   subtract xp prestige
 * Arguments:     amount - the amount to subtract
 */
void
sub_prestige(int amount)
{
    int olda;

    olda = shadow_who->query_skill(SS_PRESTIGE_ACC);
    olda -= amount;
    shadow_who->set_skill(SS_PRESTIGE_ACC, olda);
    shadow_who->change_prestige(0,1);
    shadow_who->set_skill(SS_PRESTIGE_ST,
      prestige_exp_to_stat(shadow_who->query_skill(SS_PRESTIGE_ACC)));
}



/*
 * Function name: query_ob_prestige
 * Description:   Check for the prestige of the object.
 * Arguments:     ob - the object to look at
 * Returns:  pres - the prestige
 *  Note:
 *  The prestige penelty for killing players has been reduced (I had
 *  raised it in Nov 94) seeing as players will have the Disgraced
 *  property added to them when they kill. IF Conclave feel more
 *  prestige should be lost, they can remove it themselves, or ask
 *  us to raise the penelty.     (Grace 12 Feb 95)
 */

int
query_ob_prestige(object ob)
{
    int pres;
    int align;

    pres=0;
    pres = ob->query_kn_prestige(ob);
//DEBUG("Knights: occ_shadow.c/query_ob_prestige");
//DEBUG("1: " + pres);
    if (pres==0)
    {
      if (ob->query_alignment()<0)
        pres = square_root(ob->query_alignment() * ob->query_alignment());

//DEBUG("2: " + pres);

    }

//DEBUG("3: " + pres);
    if (pres>0)
    {
        if (ob->query_average_stat()>70)
            pres=490+(pres/5);
//DEBUG("4: " + pres);
    }
    if (!ob->query_npc() && member_array(ob, q_att_ob()) >= 0)
    {
//DEBUG("5: " + pres);
        if (MEMBER(ob) || LAYMAN(ob))
            pres = -20;
        /* Goblins of any incarnation aren't a big deal */
        else if (ob->query_race() == "goblin")
            pres = -1; /* No big deal killing a goblin player */
        else if (ob->query_alignment() < 0)
            pres = -1; /* Penelty not so big if player is evil. */
        else
            pres = -5;
    }

//DEBUG("6: " + pres);
    if (!pres)
    {
        if (ob->id("gargoyle"))
            pres = 150;
        else if (ob->id("goblin"))
            pres = 140;
        else if (ob->id("dragon"))
            pres = 600;
    }

    if (pres < 0 && member_array(ob, q_att_me()) >= 0)
        pres = 1;

    if (!pres && ob->query_alignment() < 0)
       pres = -(ob->query_alignment() / 10);
//DEBUG("Returns: " + pres);
    return pres;
}

int
in_team_with_non_knight()
{
    object *tm = shadow_who->query_team_others();
    int *klvl = tm->query_knight_level();
    klvl -= ({ 1,2,3,4,5,6 });
    if (klvl && sizeof(klvl))
    return 1;
    return 0;
}

/*
 * Function name: query_merciful
 * Description:  Are we merciful ?
 */
int
query_merciful()
{
#ifdef NEW_MERCY
    return (shadow_who->query_option(OBJ_MERCIFUL_COMBAT));
#else
    return (P("pal_med",shadow_who)->query_generous());
#endif
}

/*
 * Function name: notify_you_killed_me
 * Description:  This is called each time the knight kills something.
 * Arguments:     ob - the object that was killed
 */
void
notify_you_killed_me(object ob)
{
    string str;
    int pres;
    object para, *ene;

    if ( query_merciful() )
    {
        if (ob->query_disallow_mercy() )
        {
            shadow_who->catch_tell("No mercy allowed here.\n");
        }
        else
        {
            seteuid(getuid(TO));
            para = clone_object(KOBJ + "no_die_paralyze");
            para->set_remove_time(query_knight_level() * 20 +
              query_knight_sublevel() * 2 + 1);
            para->move(ob,1);
            ob->add_subloc("unconscious_subloc",para);

#ifdef NEW_MERCY
#else
            ob->set_all_knight_generous(1);
#endif

            ene = ob->query_enemy(-1);
            ene->stop_fight(ob);
            ob->stop_fight(ene);
            pres = query_ob_prestige(ob);
            if (pres > 0)
            {
                if (ob->query_prop(MERCYFUL))
                {
                    shadow_who->catch_msg("No prestige on the second time.\n");
                    pres = 0;
                }
                else if (!in_team_with_non_knight())
                    pres = pres;
            }
            else
                pres /= 4;

            ob->add_prop(MERCYFUL, shadow_who);
            /* added by Morrigan to try to circumvent the prestige  *
             * and alignment lost suffered in tournaments and duels */

            if (MEMBER(ob))
                return;

            // Squires are not to get prestige from combat
#ifndef SQUIRE_COMBAT_PRESTIGE
            if (query_knight_level() == L_SQUIRE)
               return;
#endif

            shadow_who->set_alignment(shadow_who->query_alignment() +
              F_KILL_ADJUST_ALIGN(shadow_who->query_alignment(),
                ob->query_alignment()));
            set_alarm(1.0,0.0,"change_prestige", pres);
            return;
        }
    }

    shadow_who->notify_you_killed_me(ob);
    if (interactive(ob))
    {
        KILLED(shadow_who, ob);
        if ((MEMBER(ob) || LAYMAN(ob)) &&
          member_array(ob, q_att_ob()) >= 0 &&
          /* Again ... goblins of any incarnation */
          ob->query_race() != "goblin")
        {
            BANISH(shadow_who, "killing a fellow Solamnian Knight");
            return;
        }
        /*
         * The following line wre added by Grace to prevent Disgrace
         *  of Solamnians who kill players in defence of Solamnia
         */
        str = file_name(environment(ob));
        if (str[..15] == "/d/Krynn/solamn/")
        {
            shadow_who->catch_msg("\nYour actions in defence of Solamnia "+
              "have been Honourable. You will not be Disgraced.\n\n");
            return;
        }

        DISGRACE(shadow_who, "killing another player");
    }

      // Squires are not to get prestige from combat
#ifndef SQUIRE_COMBAT_PRESTIGE
      if (query_knight_level() == L_SQUIRE)
         return;
#endif

    if (ob->query_prop(MERCYFUL))
        shadow_who->catch_msg("No prestige on the second time.\n");
    else
    {
        pres = query_ob_prestige(ob);
        if (pres < 0 && !random(TP->query_knight_level() + TP->query_knight_sublevel()))
            pres = pres / 2;
        set_alarm(1.0,0.0,"change_prestige", pres);
    }
}

/*
 * Function name: change_prestige
 * Description:   When a player has killed something or should change the
 *                prestige for some other reason, call this function.
 * Arguments:     pres - the prestige to add.
 */
varargs void
change_prestige(int pres, int minusflag)
{
    int level, new_level, truelevel, tmp;
    object ob, me_ob;

    if (!(ob = P("pal_med", shadow_who)))
    return;

    level = query_knight_sublevel();
    truelevel = query_knight_level();

    if (pres > 0 || minusflag)
    {
    /*if (truelevel == L_BROSE && pres > 0)
      pres = 5 * pres / shadow_who->query_average_stat();
      the requirements are now done further down! */

    if (truelevel == L_SQUIRE &&
      (SPONSORED(shadow_who->query_name()) == 0) && pres > 0)
        pres = pres / 3;

    shadow_who->set_skill(SS_PRESTIGE_ACC,
      shadow_who->query_skill(SS_PRESTIGE_ACC) +
      pres);
    shadow_who->set_skill(SS_PRESTIGE_ST,
      prestige_exp_to_stat(shadow_who->query_skill(SS_PRESTIGE_ACC)));
    new_level = query_level_up(shadow_who->query_skill(SS_PRESTIGE_ST),
      level);
    }
    else if (pres == 0)
    {
    shadow_who->set_skill(SS_PRESTIGE_ACC,
      shadow_who->query_skill(SS_PRESTIGE_ACC) - level);
    shadow_who->set_skill(SS_PRESTIGE_ST,
      prestige_exp_to_stat(shadow_who->query_skill(SS_PRESTIGE_ACC)));
    new_level = query_level_up(shadow_who->query_skill(SS_PRESTIGE_ST), level);
    }
    else
    {
    shadow_who->set_skill(SS_PRESTIGE_ST,
      shadow_who->query_skill(SS_PRESTIGE_ST) + pres);
    shadow_who->set_skill(SS_PRESTIGE_ACC,
      prestige_stat_to_exp(shadow_who->query_skill(SS_PRESTIGE_ST)));
    new_level = query_level_up(shadow_who->query_skill(SS_PRESTIGE_ST),
      level);
    }

    if (C(ADMIN)->crown_highest() == shadow_who->query_name() &&
      truelevel != 3)
    (ADMIN)->set_crown_high(12,"none");
    if (C(ADMIN)->sword_highest() == shadow_who->query_name() &&
      truelevel != 4)
    (ADMIN)->set_sword_high(12,"none");
    if (C(ADMIN)->rose_highest() == shadow_who->query_name() &&
      truelevel != 5)
    (ADMIN)->set_rose_high(12,"none");

    /* wizzes can't be conclave */
    if ((shadow_who->query_wiz_level() || truelevel < 3) &&
      new_level > 10)
    new_level = 10;
    else if (truelevel == 3)
    {
    if (new_level >= 11 &&
      (ADMIN)->query_conclave("crown") != shadow_who->query_name() &&
      (ADMIN)->query_grandmaster() != shadow_who->query_real_name())
    {
        /* no conclave and i'm the runner-up */
        if ((ADMIN)->query_conclave("crown") == ""  &&
          C((ADMIN)->crown_highest()) == shadow_who->query_name() &&
          ((ADMIN)->query_conclave("sword") == "" || (ADMIN)->query_conclave("rose") == ""))
        set_high(3);
        /* conclave and i'm the runner-up */
        else if (shadow_who->query_skill(SS_PRESTIGE_ACC) > (ADMIN)->query_crown_high())
        {
        if (extract(shadow_who->query_name(),-2) != "jr")
            (ADMIN)->set_crown_high(shadow_who->query_skill(SS_PRESTIGE_ACC),
              shadow_who->query_name());
        new_level = 10;
        }
        /* conclave and i'm the runner-up but got prestige reduced */
        else if (shadow_who->query_skill(SS_PRESTIGE_ACC) < (ADMIN)->query_crown_high() &&
          shadow_who->query_name() == C((ADMIN)->crown_highest()))
        {
        (ADMIN)->set_crown_high(shadow_who->query_skill(SS_PRESTIGE_ACC),
          shadow_who->query_name());
        new_level = 10;
        }
        /* all other cases */
        else
        new_level = 10;
    }
    if (level == 11 && new_level == 10)
    {
        /* I was conclave but my prestige dropped too much */
        if ((ADMIN)->query_conclave("crown") == shadow_who->query_name())
        clear_high(3);
        /* I was runner-up, but my prestige dropped too much */
        else if (C((ADMIN)->crown_highest()) == shadow_who->query_name())
        (ADMIN)->set_crown_high(12,"none");
    }
    }
    else
    if (truelevel == 4)
    {
    if (new_level >= 11 &&
      (ADMIN)->query_conclave("sword") != shadow_who->query_name() &&
      (ADMIN)->query_grandmaster() != shadow_who->query_real_name())
    {
        /* no conclave and i'm the runner-up */
        if ((ADMIN)->query_conclave("sword") == ""  &&
          C((ADMIN)->sword_highest()) == shadow_who->query_name() &&
          ((ADMIN)->query_conclave("crown") == "" || (ADMIN)->query_conclave("rose") == ""))
        {
        set_high(4);
        }
        /* conclave and i'm the runner-up */
        else if (shadow_who->query_skill(SS_PRESTIGE_ACC) > (ADMIN)->query_sword_high())
        {
        if (extract(shadow_who->query_name(),-2) != "jr")
            (ADMIN)->set_sword_high(shadow_who->query_skill(SS_PRESTIGE_ACC),
              shadow_who->query_name());
        new_level = 10;
        }
        /* conclave and i'm the runner-up but got prestige reduced */
        else if (shadow_who->query_skill(SS_PRESTIGE_ACC) < (ADMIN)->query_sword_high() &&
          shadow_who->query_name() == C((ADMIN)->sword_highest()))
        {
        (ADMIN)->set_sword_high(shadow_who->query_skill(SS_PRESTIGE_ACC),
          shadow_who->query_name());
        new_level = 10;
        }
        /* all other cases */
        else
        new_level = 10;
    }
    if (level == 11 && new_level == 10)
    {
        /* I was conclave but my prestige dropped too much */
        if ((ADMIN)->query_conclave("sword") == shadow_who->query_name())
        clear_high(4);
        /* I was runner-up, but my prestige dropped too much */
        else if (C((ADMIN)->sword_highest()) == shadow_who->query_name())
        (ADMIN)->set_sword_high(12,"none");
    }
    }
    else
    if (truelevel == 5)
    {
    if (new_level >= 11 &&
      (ADMIN)->query_conclave("rose") != shadow_who->query_name() &&
      (ADMIN)->query_grandmaster() != shadow_who->query_real_name())
    {
        /* no conclave and i'm the runner-up */
        if ((ADMIN)->query_conclave("rose") == ""  &&
          C((ADMIN)->rose_highest()) == shadow_who->query_name() &&
          ((ADMIN)->query_conclave("sword") == "" || (ADMIN)->query_conclave("crown") == ""))
        set_high(5);
        /* conclave and i'm the runner-up */
        else if (shadow_who->query_skill(SS_PRESTIGE_ACC) > (ADMIN)->query_rose_high())
        {
        if (extract(shadow_who->query_name(),-2) != "jr")
            (ADMIN)->set_rose_high(shadow_who->query_skill(SS_PRESTIGE_ACC),
              shadow_who->query_name());
        new_level = 10;
        }
        /* conclave and i'm the runner-up but got prestige reduced */
        else if (shadow_who->query_skill(SS_PRESTIGE_ACC) < (ADMIN)->query_rose_high() &&
          shadow_who->query_name() == (ADMIN)->rose_highest())
        {
        (ADMIN)->set_rose_high(shadow_who->query_skill(SS_PRESTIGE_ACC),
          shadow_who->query_name());
        new_level = 10;
        }
        /* all other cases */
        else
        new_level = 10;
    }
    if (level == 11 && new_level == 10)
    {
        /* I was conclave but my prestige dropped too much */
        if ((ADMIN)->query_conclave("rose") == shadow_who->query_name())
        clear_high(5);
        /* I was runner-up, but my prestige dropped too much */
        else if (C((ADMIN)->rose_highest()) == shadow_who->query_name())
        (ADMIN)->set_rose_high(12,"none");
    }
    }
    else
    new_level == 10;

    me_ob = P("pal_med", ob);

    if (truelevel == 2)
    {
    if (level > new_level)
    {
        if (new_level == 0)
        {
        shadow_who->catch_msg("Paladine disapproves of your " +
          "actions as a squire. You have " +
          "disgraced the squirehood! " +
          "You will now be a black knight " +
          "of the rose until you have " +
          "proven yourself worthy to once " +
          "again be a squire!\n");
        (ADMIN)->remove_squire_sponsorlist(shadow_who->query_name());
        seteuid("Krynn");
        shadow_who->set_bit(1, 3);
        truelevel = 1;
        shadow_who->set_skill(SS_PRESTIGE_ST, 10);
        shadow_who->set_skill(SS_PRESTIGE_ACC,
          prestige_stat_to_exp(shadow_who->query_skill(SS_PRESTIGE_ST)));
        }

    }
    }

    if (truelevel == 1)
    {
    if (level < new_level)
    {
        if (new_level == 0)
        new_level = 1;

        tmp = shadow_who->query_average_stat() / 25 + 2;
        if (tmp>9) tmp=9;

        if (new_level >= 3)
        {
        shadow_who->catch_msg("Paladine approves of your actions " +
          "and you have been reinstated to " +
          "the Knight orders. Congratulations!\n");
        seteuid("Krynn");
        shadow_who->clear_bit(1, 3);
        if (shadow_who->test_bit("Krynn",1,4) ||
          shadow_who->test_bit("Krynn",1,5))
        {
            truelevel = 3;
            shadow_who->catch_msg("You are now once again"
              + " a Knight of the Crown!\n");
            shadow_who->clear_bit(1, 4);
            shadow_who->set_bit(1, 5);
        }
        else
        {
            truelevel = 2;
            shadow_who->catch_msg("You are now once again"
              + " a Squire of Solamnia!\n");
            shadow_who->clear_bit(1, 4);
            shadow_who->clear_bit(1, 5);
        }
        new_level = 1;


        ob->set_knight_level(truelevel);
        shadow_who->set_skill(SS_PRESTIGE_ST, 10);
        shadow_who->set_skill(SS_PRESTIGE_ACC,
          prestige_stat_to_exp(shadow_who->query_skill(SS_PRESTIGE_ST)));
        if (me_ob)
        {
            me_ob->set_tax(0);
        }
        ob->set_knight_sublevel(new_level);
        ob->add_subloc("solamnian_subloc", this_object());
        }
    }
    }

    if (truelevel > 2)
    {
    if (level > new_level)
    {
        if (new_level != 0 && new_level != 10)
        {
        shadow_who->catch_msg("Paladine does not approve of " +
          "your actions. Your prestige has " +
          "lowered too much. Your rank " +
          "has lowered.\n");
        ob->set_knight_sublevel(new_level);
        }
        if (new_level == 0)
        {
        if (truelevel >= 3)
        {
            shadow_who->catch_msg("You have disgraced your order" +
              " with your lack of prestige. " +
              "You will now become a black knight " +
              "until you have sufficiently " +
              "atoned for your deeds.\n");
            (ADMIN)->remove_knight_sponsorlist(shadow_who->query_name());
            seteuid("Krynn");
            shadow_who->set_bit(1, 3);
            truelevel = 1;
            shadow_who->set_skill(SS_PRESTIGE_ST, 10);
            shadow_who->set_skill(SS_PRESTIGE_ACC,
              prestige_stat_to_exp(shadow_who->query_skill(SS_PRESTIGE_ST)));
            shadow_who->add_subloc("solamnian_subloc", this_object());
        }
        }

        if (me_ob)
        {
        me_ob->set_tax(0);
        }
        ob->set_knight_sublevel(new_level);
        ob->add_subloc("solamnian_subloc", this_object());
    }

    else if (level < new_level)
    {
        if (me_ob)
        {
        me_ob->set_tax(0);
        }
        shadow_who->catch_msg("Your prestige has raised to " +
          "enough to let you get a higher " +
          "rank. Congratulations.\n");
        ob->set_knight_sublevel(new_level);
        ob->add_subloc("solamnian_subloc", this_object());
    }
    }

    if (new_level == 0)
    new_level = 1;

    ob->set_knight_sublevel(new_level);
    ob->set_knight_level(truelevel);

    ob->add_subloc("solamnian_subloc", this_object());

}


int
query_level_up(int stat, int level)
{
    if (stat >= SS_LEVEL10)
    return L_11;
    if (stat >= SS_LEVEL9)
    return L_10;

    if (stat >= SS_LEVEL8)
    return L_9;

    if (stat >= SS_LEVEL7)
    return L_8;

    if (stat >= SS_LEVEL6)
    return L_7;

    if (stat >= SS_LEVEL5)
    return L_6;

    if (stat >= SS_LEVEL4)
    return L_5;

    if (stat >= SS_LEVEL3)
    return L_4;

    if (stat >= SS_LEVEL2)
    return L_3;

    if (stat >= SS_LEVEL1)
    return L_2;

    if (stat > SS_LEVEL0)
    return L_1;

    return L_0;
}

int
query_level_down(int stat, int level)
{
    return level;
}

int
query_stat_for_level_up(int newlevel)
{
    switch(newlevel)
    {
	case 11:
	   return SS_LEVEL9 + 1;
	   break;
	case 10:
	   return SS_LEVEL9 + 1;
	   break;
	case 9:
	   return SS_LEVEL8 + 1;
	   break;
	case 8:
	   return SS_LEVEL7 + 1;
	   break;
	case 7:
	   return SS_LEVEL6 + 1;
	   break;
	case 6:
	   return SS_LEVEL5 + 1;
	   break;
	case 5:
	   return SS_LEVEL4 + 1;
	   break;
	case 4:
	   return SS_LEVEL3 + 1;
	   break;
	case 3:
	   return SS_LEVEL2 + 1;
	   break;
	case 2:
	   return SS_LEVEL1 + 1;
	   break;
	case 1:
	   return 1;
	   break;
	default:
	   return 0;
	   break;
    }
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
    string str, subtitle, aw_str;
    string awards, bear, symbol;
    object ob;

    if (subloc != SOL_SUB ||
    me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return shadow_who->show_subloc(subloc, me, for_obj);

    subtitle = query_knight_subtitle();

    seteuid(getuid());
    switch(query_knight_level())
    {
    case(5):
    symbol = "Order of the Rose";
    break;
    case(4):
    symbol = "Order of the Sword";
    break;
    case(3):
    symbol = "Order of the Crown";
    break;
    default:
    symbol = "Knighthood";
    break;
    }

    ob = P("pal_med", me);
    if (!ob)
      return "";

    if (for_obj == me)
    {
    str = "Your";
    bear = "You bear ";
    }
    else
    {
    str = C(POSSESSIVE(me));
    bear = C(PRONOUN(me)) + " bears ";
    }

    awards = (ADMIN)->query_award_nice(shadow_who);
    if (awards && awards != "")
      aw_str = bear + awards + ".\n";

    str = str + " tunic is decorated with the symbol of the "+symbol+".\n";
    if (aw_str)
      str += aw_str;

    return str;
}


/*
 * Function name:   restore_prestige_loss
 * Description:     Restore lost prestige when continuing a fight.
 * Arguments:       who: the enemy
 */
void
restore_prestige_loss(object who)
{
    if (member_array(who, m_indexes(pres_loss)) >= 0)
    {
#ifndef SQUIRE_COMBAT_PRESTIGE
      if (query_knight_level() == L_SQUIRE)
         return;
#endif
    change_prestige(pres_loss[who]);
    pres_loss = m_delete(pres_loss, who);
    }
}


/*
 * Function name:   attacked_by
 * Description:     This routine is called when we are attacked.
 * Arguments:       ob: The attacker
 */
void
attacked_by(object ob)
{
    object sh;

    if (member_array(ob, q_att_ob()) == -1 &&
      member_array(ob, q_att_me()) == -1)
    {
    if (!att_me)
        att_me = ({});
    else
        att_me -= ({ 0 });

    att_me += ({ ob });
    }
    restore_prestige_loss(ob);
    seteuid(getuid(TO));
    sh = clone_object(SHADOWS + "no_die_shadow");
    if (!sh->shadow_me(ob))
    sh->remove_object();

    shadow_who->attacked_by(ob);
}

/*
 * Function name:   attack_object
 * Description:     Start attacking, the actual attack is done in heart_beat
 * Arguments:       The object to attack
 */
void
attack_object(object ob)
{
    object sh;

    if (member_array(ob, q_att_ob()) == -1 &&
      member_array(ob, q_att_me()) == -1)
    {
    if (!att_ob)
        att_ob = ({});
    else
        att_ob -= ({ 0 });

    att_ob += ({ ob });
    }
    restore_prestige_loss(ob);
    seteuid(getuid(TO));
    sh = clone_object(SHADOWS + "no_die_shadow");
    if (!sh->shadow_me(ob))
    sh->remove_object();

    shadow_who->attack_object(ob);
}

/*
 * Function name: my_reduce_prestige_on_move
 * Description:   Walking away from the fight you started will reduce prestige.
 */
void
my_reduce_prestige_on_move()
{
    int level = query_knight_level();
    int pres = 10 * level * level * level;
    object ene = shadow_who->query_attack();
    if (ene && att_ob && member_array(ene, att_ob) > -1)
    {
    change_prestige(-pres, 1);
    if (!pres_loss)
        pres_loss = ([ ]);
    pres_loss += ([ ene:pres ]);
    }
}

/*
 * Function name: adjust_combat_on_move
 * Description:   Called to let movement affect the ongoing fight. This
 *                is used to print hunting messages.
 * Arguments:     True if leaving else arriving
 */
void
adjust_combat_on_move(int leave)
{
    if (leave)
    my_reduce_prestige_on_move();
    shadow_who->adjust_combat_on_move(leave);
}

#if 1
/* calc the summed stats of 'who' and its team. */
int
calc_odds(object who)
{
    int i;
    int sum = who->query_average_stat();
    object *team = who->query_team_others();

    for(i=0;i<sizeof(team);i++)
    sum += team[i]->query_average_stat();
    return sum;
}

/*
 * Function name: do_die
 * Description:   Called from enemy combat object when it thinks we died.
 * Arguments:     killer: The enemy that caused our death.
 */
void
do_die(object killer)
{
    int knight_odds, opponent_odds, ratio;

    /* The knight gains prestige when he dies in an honorable fight! */
    if (shadow_who->query_hp() <= 0 && killer && living(killer))
    {
    knight_odds = calc_odds(shadow_who);
    opponent_odds = calc_odds(killer);
    ratio = knight_odds * 100 / opponent_odds;
    /* If the knight (+team) was fighting against overwhelming odds
     * give a lot of prestige
     */
    if (ratio <= 95)
        change_prestige(20000);
    /* If the knight was fighting against equal odds, give some
     *  prestige
     */
    if (ratio > 95 && ratio < 110)
        change_prestige(5000);
    /* If the knight fought against weaker opponent(s), or anything
     * else, no prestige
     */
    }
    shadow_who->do_die(killer);
}
#endif

/*
 * Function name: set_whimpy
 * Description:   Redefine the wimpy level for the knights. Knights are not
 *                allowed to set high wimpy levels.
 * Arguments:     flag, the wimpy level to set at.
 */
void
set_whimpy(int flag)
{
    int lim = WIMPY_LIMIT[query_knight_level()] +
    WIMPY_LIMIT2[query_knight_sublevel()];
    if (lim > 99)
    lim = 99;
    if (flag > lim)
    shadow_who->catch_msg("This wimpy level is not allowed for a Knight of " +
      "Solamnia!\n");
    else
    lim = flag;
    shadow_who->set_whimpy(lim);
}

/*
 * Function name: reward_warfare_conquest
 * Description:   This is called whenever the knight conquers an area via the
 *                warfare system.
 * Arguments:     The area that was conquered, the new occupant (should be
 *                'Knights' for us always!!) and the old army from which the
 *                area was conquered.
 */
void
reward_warfare_conquest(string area, string newarmy, string oldarmy)
{
    change_prestige(5000);
}

public void
check_for_tunic(object player)
{
    if (!TUNIC_OBJECT(player))
    {
        setuid();
        seteuid(getuid());
    
        clone_object(MEDALPATH)->move(player, 1);
    }

    // Add to warfare system if not already a member.
    if(!IS_CLUB_MEMBER(player))
    {
        CLUB_MANAGER->add_member(player);
        CLUB_MANAGER->set_warfare_army(player, "Knights");
        player->catch_tell("You have been granted a dark steel chit " +
            "as token for supporting the Knights of Solamnia in " +
            "the War of the Lance!\n");
    }

    // Clone the warfare club object
    if (!present("_warfare_club_object_", player))
    {
        setuid();
        seteuid(getuid());

        clone_object(WAR_OBJ)->move(player, 1);
    }
    
    if (!objectp(present("_knight_mounted_absorb_object_", player)))
    {
        object dam_mod;
        dam_mod = clone_object(SPECIALS + "objects/knight_mounted_dam_mod");
        dam_mod->set_effect_caster(player);
        dam_mod->set_effect_target(player);
        dam_mod->move(player, 1);
        dam_mod->start();
    }
}

/*
 * Function name: init_occ_shadow()
 * Description: This function is called from autoload_shadow and may
 *              be used to initialize the shadow when it's loaded.
 * Arguments: The argument string sent to autoload_shadow.
 */
public void
init_occ_shadow(string arg)
{
    ::init_occ_shadow(arg);
    setuid();
    seteuid(getuid());
    
    set_alarm(5.0, 0.0, &check_for_tunic(shadow_who));
}

/*
 * Function:    query_can_control_dragonfear
 * Description: Function should return true if can control dragonfear
 * Arguments:   none
 * Returns:     0/1 - cannot control/control
 */
public int
query_can_control_dragonfear()
{
    if (query_knight_level() == L_ROSE 
        || (query_knight_level() == L_SWORD 
            && query_knight_sublevel() > 5))
    {
        return 1;
    }
    
    return 0;
}

/*
 * Function:    hook_controlled_dragonfear
 * Description: Function to print the messages for when someone
 *              successfully controls dragonfear
 * Arguments:   none
 * Returns:     0/1 - not immune/immune
 */
public void
hook_controlled_dragonfear()
{
    object player;
    
    player = shadow_who;
	player->catch_msg("Terror sweeps over you, threatening to overcome you "+
            "fully. Gritting your teeth, you fight the fear back, keeping "+
            "control of yourself.\n");
	tell_room(E(player), QCTNAME(player)+" grits "+HIS(player)+" teeth as "+
            "the dragonfear sweeps over "+HIM(player)+", but "+HE(player)+
            " manages to keep control of "+HIM(player)+"self.\n", player);
	return;
}
