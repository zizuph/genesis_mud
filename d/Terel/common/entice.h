#include "/d/Terel/cedric/guild/guild_defs.h"

/*
 * Function Name:   entice_me
 * Description:     This function is called in an animal that a Minstrel is 
 *                  attempting to charm with the entice spell. The greater 
 *                  the average stat of the creature, the more difficult it
 *                  will be to charm. Once charmed, the animal will team with
 *                  the minstrel, following him around (with mmin adjusted
 *                  to indicate it's devotion to the minstrel) and attacking
 *                  what its master or mistress attacks. If the song fails
 *                  particularly miserably the animal will attack the Minstrel
 *                  (embarrasing to say the least.
 * Arguments:       enticer - object pointer to the Minstrel enticing.
 *                  result - the resolve_task result of the spell. This
 *                           number is compared with the average stat of
 *                           the creature to determine success or failure.
 */
int
entice_me(object enticer, int result)
{
    write("DEBUG: result = "+result+"\n");
    write("DEBUG: my average stat = "+query_average_stat()+"\n");
    write("DEBUG: trying to make you invite me; got result "+
	enticer->team_invite(TO())+"\n");
    write("DEBUG: trying to join myself to your team; got result "+
	enticer->team_join(TO())+"\n");
    return 1;
}

/*
 * Function name: attacked_by
 * Description:   This function is called when somebody attacks this object
 * Arguments:     ob - The attacker
 */
void
attacked_by(object ob)
{
    object *arr;
    int i;

    ::attacked_by(ob);

    arr = (object *)query_team_others();
    for (i = 0; i < sizeof(arr); i++)
        arr[i]->notify_ob_attacked_me(this_object(), ob);
}

/*
 * Function name: notify_ob_attacked_me
 * Description:   This is called when someone attacks a team member of mine
 * Arguments:     friend - My team mate
 *                attacker - The attacker
 */
void
notify_ob_attacked_me(object friend, object attacker)
{
    if (query_attack())
        return;

    if (random(10))
        call_out("help_friend", 1, attacker);
}

/*
 * Function name: help_friend
 * Description:   Help my friends by attacking their attacker
 * Arguments:     attacker - The person who attacked my friend
 */
void
help_friend(object ob)
{
    if (ob && !query_attack() && present(ob, environment()))
    {
        command("emote barks in rage, and leaps to defend "
            +TO()->query_possessive()+" friend.");
        command("kill " + lower_case(ob->query_real_name()));
    }
}
