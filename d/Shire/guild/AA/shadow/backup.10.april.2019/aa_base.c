/*
 * The Angmar Army basic shadow
 * by Milan
 *
 *
 * Modification log: 6.18.2008 Novo made race check a little later, since
 *                    orc shadow may not yet mask their elf interior.
 *                   6.18.2008 Novo Change aa_stat query to check layman
 *                    so ogres/AA do not get occ AA bonus to this stat
 *                   6.21.2008 Novo Decreased load time for souls, as some
 *                    players do who f and are confused about their lack
 *                    of proper title
 *                   7.14.2008 Novo Increased requirements for 'Dreadful'
 *                    title
 *                   8.16.2008 Novo properly Remove player from the guild
 *                    if the race restrictions are not met
 */

#pragma strict_types
#pragma save_binary

#include "../guild.h"
#define SAVE_FILE       (AA_DIR+"save_files/MEMBER_KILLERS")
#define TIME_TO_FORGET  20000


#include <macros.h>
#include <wa_types.h>
#include <ss_types.h>

/*
 * Global variables
 */
string aa_level = "Servant";
int i_am_incognito = 0;
int is_member_killer;

object evade_obj;

int query_aa_shadow() { return 1; }

string
query_rank()
{
    return aa_level;
}

void
set_rank(string str)
{
    aa_level = str;
}


public void remove_aa_shadow()
{
    remove_shadow();
}

int
query_aa_stat()
{
    int a = 2 * query_shadow_who()->query_skill(SS_WEP_CLUB);
    a += query_shadow_who()->query_stat(SS_WIS);
    a += query_shadow_who()->query_stat(SS_DIS);
    a += query_shadow_who()->query_stat(SS_STR);

    if(!IS_LAYMAN(this_object()))
        {
            a += 4 * query_shadow_who()->query_skill(SS_WEP_CLUB);
            a += 2 * query_shadow_who()->query_stat(SS_OCCUP);
        }
        else
        {
            a += query_shadow_who()->query_stat(SS_LAYMAN);
        }
    return a - (query_shadow_who()->query_alignment() / 5);
}

int
query_shield_level()
{
    int a = query_shadow_who()->query_skill(SS_WEP_CLUB);
    a += query_shadow_who()->query_skill(SS_SMASH);
    a += query_shadow_who()->query_skill(SS_SHIELD);
    a += query_shadow_who()->query_skill(SS_PARRY);
    a += query_shadow_who()->query_skill(SS_DEFENCE);
    a += query_shadow_who()->query_skill(SS_BLIND_COMBAT);
    a += query_shadow_who()->query_stat(SS_WIS);
    a += query_shadow_who()->query_stat(SS_DIS);
    a += query_shadow_who()->query_stat(SS_STR);
    a = (a * sizeof(ADJ_LIST) / 1200) - 1;
    return MIN(MAX(0, a), sizeof(ADJ_LIST)-1);
}

int
query_aa_incognito()
{
    return i_am_incognito;
}

void
set_aa_incognito(int i)
{
    i_am_incognito = i;
}

string
query_aa_guild_title()
{
    string s, n;

    if(query_aa_incognito()) return "";

    n = query_shadow_who()->query_name();

    if (AA_COUNCIL_OBJ->is_captain(n))
    {
		return "Warden of the Misty Mountains and "
		+"Captain of the Army of Angmar";

		// return "Captain of the Army of Angmar";
    }

	if (AA_COUNCIL_OBJ->is_lieutenant(n))
	{
		return "Lieutenant of the Army of Angmar";
	}


    s = ADJ_LIST[query_shield_level()]+" "+aa_level;

    if(AA_COUNCIL_OBJ->is_council(n)) s += " and Final Judge";
    if(AA_COUNCIL_OBJ->is_ro(n)) s += " and Recruitment Officer";
    return s+" of the Army of Angmar";
}

int
query_aa_guild_not_allow_join(object player, string type, string style, string name)
{
    if (style == "ranger" && type == "occupational")
    {
        player->catch_tell("Are you stupid? Rangers are our enemies!!!\n");
        return 1;
    }
    return 0;
}

int
check_player_race(object tp)
{
    string race = tp->query_race_name();
    if(tp->query_wiz_level())
        return 1;
    if (tp->query_ghost())
    {
        return 1;
    }
    if(member_array(race, ALLOWED_RACES) == -1)
    {
        if(race == "elf")
            tp->catch_msg("We hate elves! Get lost!!!\n");
        else
            tp->catch_msg("You puny "+race+" can't swing club properly!\n");

        tp->remove_skill(SS_SHIELD);
        tp->remove_skill(SS_SMASH);
        tp->remove_skill(SS_BASH);
        tp->set_skill(SS_PARRY,
            tp->query_base_skill(SS_PARRY)/2);
        tp->set_skill(SS_DEFENCE,
            tp->query_base_skill(SS_DEFENCE)/3);
        tp->set_skill(SS_BLIND_COMBAT,
            tp->query_base_skill(SS_BLIND_COMBAT)/2);
        if(tp->query_base_skill(SS_WEP_CLUB)>30)
            tp->set_skill(SS_WEP_CLUB,30);
        if(tp->query_base_skill(SS_AWARENESS)>50)
            tp->set_skill(SS_AWARENESS,50);
        if(tp->query_base_skill(SS_APPR_MON)>50)
            tp->set_skill(SS_APPR_MON,50);

        tp->set_default_start_location(tp->query_def_start());

        AA_RANKS_OBJ->demote_captain(tp->query_real_name());

        AA_RANKS_OBJ->remove_entry(tp->query_real_name());

        FIXEUID;

        write_file(AA_DIR+"log/join_log",ctime(time())+ " "+
            capitalize(TP->query_real_name())+" was kicked out "+
            "of the Army bcause of race.\n");

        return 0;
    }
    return 1;
}

public mixed
query_guild_skill_name(int type)
{
    if (type == SS_SHIELD) return SHIELD_NAME;
    if (type == SS_SMASH) return SMASH_NAME;
    if (type == SS_BASH) return BASH_NAME;
    if (type == SS_RETREAT) return RETREAT_NAME;
    return 0;
}

void
get_me_soul()
{
    string name = query_shadow_who()->query_name();
    string *list = query_shadow_who()->query_cmdsoul_list();
    int i;


    FIXEUID;

    if (!check_player_race(query_shadow_who()))
    {
        query_shadow_who()->remove_autoshadow(MASTER);
	    remove_aa_shadow();
	    return;
    }

    evade_obj=clone_object(AA_EVADE_OBJ);
    evade_obj->set_effect_caster(query_shadow_who());
    evade_obj->set_effect_target(query_shadow_who());
    evade_obj->move(query_shadow_who(),1);
    evade_obj->start();

    if(query_shadow_who()->query_wiz_level()) return;


    for(i=0; i<sizeof(list); i++)
    query_shadow_who()->remove_cmdsoul(list[i]);

    query_shadow_who()->add_cmdsoul(AA_SOUL);
    query_shadow_who()->add_cmdsoul(AA_SOUL_E);
    query_shadow_who()->add_cmdsoul(AA_SOUL_R);

    for(i=0; i<sizeof(list); i++)
    if((list[i] != AA_SOUL) && (list[i] != AA_SOUL_E) && (list[i] != AA_SOUL_R))
        query_shadow_who()->add_cmdsoul(list[i]);

    query_shadow_who()->update_hooks();

    if(explode(name+"#", "jr#")[0]+"jr" != name &&
        !query_shadow_who()->query_npc())
        aa_level = AA_RANKS_OBJ->update_rank(query_shadow_who());

    clone_object(AA_DIR+"obj/aa_tabard")->move(query_shadow_who());

    switch(aa_level)
    {
        case "Standard Bearer":
                 clone_object(AA_DIR+"obj/aa_standard")->move(query_shadow_who());
                 break;
        default: break;
    }

    AA_PUNISH_OBJ->set_up_punishments(query_shadow_who());

    if(is_member_killer)
    {
        query_shadow_who()->catch_msg("\n"+
          "   Hello "+name+", the "+aa_level+" of the Army of Angmar...\n"+
          "Hope you stopped killing our warriors! "+
          "Otherwise you may regret it!\n\n");
        return;
    }

	if (AA_COUNCIL_OBJ->is_captain(name))
	{
		query_shadow_who()->catch_msg("\n" +
			"   Welcome " + name + ", the Mighty Captain of the Army of Angmar!\n" +
			"May your shield be like a rock and your club smashing every time!\n\n");

		return;
	}

	if (AA_COUNCIL_OBJ->is_lieutenant(name))
	{
		query_shadow_who()->catch_msg("\n" +
			"   Welcome " + name + ", the Lieutenant of the Army of Angmar!\n" +
			"May your shield be like a rock and your club smashing every time!\n\n");

		return;
	}

    query_shadow_who()->catch_msg("\n"+
      "   Welcome "+name+", the "+aa_level+" of the Army of Angmar!\n"+
      "May your shield be like a rock and your club smashing every time!\n\n");
}

public object query_aa_evade_obj()
{
    return evade_obj;
}

void
init_aa_shadow()
{
    string name;
    mapping member_killers;


    set_alarm(2.0, 0.0, get_me_soul);

    FIXEUID;
    member_killers = restore_map(SAVE_FILE);

    if(!member_killers) return;

    name = query_shadow_who()->query_name();

    if(member_array(name, m_indexes(member_killers)) == -1)
        return;

    if(TIME_TO_FORGET + member_killers[name][0] <
        query_shadow_who()->query_age())
    {
        member_killers = m_delete(member_killers, name);
        save_map(member_killers, SAVE_FILE);
        return;
    }

    if(member_killers[name][1])
    {
        is_member_killer = 2;
    } else {
        is_member_killer = 1;
    }
}

string
query_def_post()
{
    return AA_DIR+"rooms/post";
}


void
notify_you_killed_me(object killed)
{
    string name;
    mapping member_killers;
    int i;

    query_shadow_who()->notify_you_killed_me(killed);

    if(!IS_MEMBER(killed)) return; /* we don't care */

    if(query_shadow_who() == killed) return; // killing yourself by leaving a guild shouldn't cause any problems.

    FIXEUID;

    member_killers = restore_map(SAVE_FILE);

    if(!member_killers) member_killers = ([ ]);

    name = query_shadow_who()->query_name();


	// The captain/council can now will deal with this, so should be a non_issue.
    /*if(member_array(name, m_indexes(member_killers)) == -1)
    {
        member_killers += ([ name : ({query_shadow_who()->query_age(),0}) ]);
        query_shadow_who()->catch_msg("\n\nSomething tells you that you can "+
          "have big troubles in army for this!\n\n\n");
        is_member_killer = 1;
    }
    else
    {
        i = member_killers[name][1] + 1;
        member_killers[name] = ({query_shadow_who()->query_age() + i*TIME_TO_FORGET, i});
        query_shadow_who()->catch_msg("\n\nYou again! Now you are in a BIG trouble!!!\n\n\n");
        is_member_killer = 2;
    }*/

	is_member_killer = 0;

    FIXEUID;
    save_map(member_killers, SAVE_FILE);
}

int
query_aa_member_killer()
{
    return is_member_killer;
}

/*
 * Function name: forced_remove
 * Description  : Removes player and strips them of guild items and skills
 *                This is called from query_guild_keep_player()
 * Arguments    : tp - the player to check
 * Returns      : 0 - if the player will be kicked out
 *                1 - the player will remain
 */
int forced_remove(object tp)
{
    int *skills, i, j;
	object token;
    string text = QTRACE(tp);

    FIXEUID;

    tp->query_aa_evade_obj()->remove_object();

    if (tp->query_guild_name_occ() == GUILD_NAME)
    {
        if (!tp->remove_guild_occ())
        {
            write("There was a strange error, I'm afraid you are stuck with us.\n");
            return 1;
        }
        /* drain occ-leave */
        tp->add_exp(-tp->query_exp_combat()/6,1);
        tp->clear_guild_stat(SS_OCCUP);
    }
    else
    {
        if (!tp->remove_guild_lay())
        {
            write("There was a strange error, I'm afraid you are stuck with us.\n");
            return 1;
        }
        /* drain lay_leave */
        tp->add_exp(-tp->query_exp_combat()/9,1);
        tp->clear_guild_stat(SS_LAYMAN);
    }

    tp->set_max_headache(MAX(1000, tp->query_max_headache()));
    tp->set_headache(tp->query_max_headache());

    if (member_array(AA_SOUL, tp->query_cmdsoul_list()) != -1)
        tp->remove_cmdsoul(AA_SOUL);
    if (member_array(AA_SOUL_E, tp->query_cmdsoul_list()) != -1)
        tp->remove_cmdsoul(AA_SOUL_E);
    tp->update_hooks();

    tp->remove_skill(SS_SHIELD);
    tp->remove_skill(SS_SMASH);
    tp->remove_skill(SS_BASH);

    skills = tp->query_all_skill_types();
    for (i=0; i<sizeof(skills); i++)
    {
        if ((skills[i]<1000))
        {
            j = tp->query_base_skill(skills[i]);
            tp->set_skill( skills[i], j - random(MIN(j,20)) );
        }
    }

    tp->set_default_start_location(tp->query_def_start());
    AA_RANKS_OBJ->remove_entry(tp->query_real_name());
    write_file(AA_DIR+"log/join_log",ctime(time())+ " "+
        capitalize(TP->query_real_name())+" has left the army.\n");

    token->remove_object();
}

/*
 * Function name: query_guild_keep_player
 * Description  : Tests whether we want to keep a player if he logs in.
 * Arguments    : player - the player to check
 * Returns      : 0 - if the player will be kicked out
 *                1 - the player will remain
 */
public int
query_guild_keep_player(object player)
{
    int align = player->query_alignment();

    setuid();
    seteuid(getuid());

    // race changed
    if (race == "elf") 
    {
        player->catch_msg("\n\n\nYour new race is unacceptable. You have " +
            "been expelled from the Army of Angmar.\n\n\n");
        forced_remove(player);
        write_file(AA_DIR+"log/join_log",ctime(time())+ " "+
            capitalize(TP->query_real_name())+" unacceptable race change: " +
            "kicked out of Army.\n"); 
    	return 0;
    }

    // If the alignment of the player is too good, we kick them out.
    if (align >= ALIGN_BOOT)
    {
        player->catch_tell("\n\n\nYour actions are an embarrasment to " +
            "the Army. You have been expelled.\n\n\n");
        forced_remove(player);
        write_file(AA_DIR+"log/join_log",ctime(time())+ " "+
            capitalize(TP->query_real_name())+" alignment changed; " +
            "kicked out of Army.\n"); 
    	return 0;
    }
    return 1;
}
