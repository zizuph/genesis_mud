#include "../guild.h"

inherit "/lib/guild_support";

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

    // If the alignment of the player is too good, we kick them out.
    if (align >= ALIGN_BOOT)
    {
        player->catch_tell("\n\n\nYour actions are an embarrasment to " +
            "the Army. You have been expelled.\n\n\n");

        forced_remove(player);
 
    	return 0;

    }
    return 1;
}
