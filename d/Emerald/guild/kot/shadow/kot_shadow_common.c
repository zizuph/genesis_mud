#include <ss_types.h>

void remove_kot_member(object who);

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
    if ((who->query_race() != "elf") && (who->query_race() != "ghost"))
    {
	return "We only accept elves!\n";
    }

    return 0;
}

int
start_kot_member(object ob)
{
    mixed why;

    if (stringp(why = acceptable_member(ob)))
    {
	ob->catch_msg(why);
        remove_kot_member(ob);
        return 0;
    }

    return 1;
}

/* 
 * Function name: query_guild_skill_name
 * Description:   Give a names for the guild's special skills
 * Arguments:     type - the number of the skill
 * Returns:	  0 if no skill of mine, else the string.
 */
mixed
query_guild_skill_name(int type)
{
#ifdef SS_PROT_CLARITY
    if (type == SS_PROT_CLARITY)
    {
        return "clarity";
    }
#endif

#ifdef SS_PROT_2H_SWORD
    if (type == SS_PROT_2H_SWORD)
    {
        return "two-handed sword";
    }
#endif

    return 0;
}

/*
 * Function name: remove_kot_member
 * Description:   remove this member from the guild
 */
void
remove_kot_member(object who)
{
    deep_inventory(who)->remove_kot_object();

#ifdef SS_PROT_2H_SWORD
    who->remove_skill(SS_PROT_2H_SWORD);
#endif

#ifdef SS_PROT_CLARITY
    who->remove_skill(SS_PROT_CLARITY);
#endif
}

int
query_kot_member()
{
    return 1;
}

