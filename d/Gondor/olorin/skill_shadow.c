#include <ss_types.h>

/* TO use:
   Call <this file> skill_add <name of player>
   Call @<name of player> compute_skill_decay
   Call @<name of player> skill_done

   NB If you update the file before last call, the player is destructed,
      so be careful!
   */

mapping SkillMap;

public int
skill_done()
{
    destruct();
    return 1;
}

public int
skill_exit()
{
    return 1;
}

public int
skill_add(string who)
{
    object pl;

    if ((pl = find_player(who)))
	shadow(pl, 1);
    return 1;
}

public int
sk_query_max(int skill, int silent)
{
    int rval;
    
    if ((rval = SS_SKILL_DESC[skill][4]) == 0)
	rval = 20;

    return rval;
}

public int
get_train_max_test(int skill, mixed ob)
{
    int rval = 0;
    string  name;

    if (objectp(ob))
        name = file_name(ob);
    else if (stringp(ob))
        name = ob;
    else
        name = "unknown";
    
    if (catch(rval = ob->sk_query_max(skill, 1)))
	log_file("BAD_TRAIN_OB", ctime(time()) + ": " + ob + "\n");

write(name + ": " + skill + ": " + rval + "\n");
    return rval;
}
     

public int
get_diff(mixed list, int skill)
{
    int *sklist, i, sz, max, sk;

    sklist = map(list, &get_train_max_test(skill, ));

    for (i = 0, max = 0, sz = sizeof(sklist) ; i < sz ; i++)
	if (max < sklist[i])
	    max = sklist[i];

    if ((sk = this_object()->query_skill(skill) - max) > 0)
	return sk;

    return 0;
}

int
query_decay_skill_test(mixed list, int skill)
{
    int *sklist, i, sz, max, sk;

    sklist = ({ }) + map(list, &get_train_max_test(skill, ));
    if (sizeof(SS_SKILL_DESC[skill]))
        sk = SS_SKILL_DESC[skill][4];
    else
        sk = 0;
    sklist += ({ (sk > 0 ? sk : MIN_SKILL_LEVEL) });

    for (i = 0, max = 0, sz = sizeof(sklist) ; i < sz ; i++)
        if (max < sklist[i])
            max = sklist[i];

    return (this_object()->query_base_skill(skill) > max);
}

public void
compute_skill_decay()
{
    mixed obs;
    mixed otmp;
    int *skills;
    mapping max_map;
    object tp = this_player();

    obs = ({});
    otmp = this_object()->query_guild_trainer_occ();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = this_object()->query_guild_trainer_race();
    obs += pointerp(otmp) ? otmp : ({ otmp });
    otmp = this_object()->query_guild_trainer_lay();
    obs += pointerp(otmp) ? otmp : ({ otmp });

    obs -= ({ 0 });

    dump_array(obs);

    /* Filter all relevant skills */
    skills = filter(this_object()->query_all_skill_types(),
		    &operator(>)(99999));

    dump_array(skills);

    /* Find out what skills need decay */
    skills = filter(skills, &query_decay_skill_test(obs, ));

    dump_array(skills);
}

