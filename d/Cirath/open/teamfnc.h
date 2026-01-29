/*
 * teamfnc.h
 * These are team functions taken from the monster.c in Krynn, which was
 * coded my Nick.  I wanted to make them as an includable so they could
 * just be used where wanted. And so they could be easily edited if we
 * ever feel the need.  And of course since having major functions used
 * in Cirath require that code in Krynn works is plain silly.
 *                                                   ---Serpine
 */

/*
 * Function name: attacked_by
 * Description:	  This function is called when somebody attacks this object
 * Arguments:	  ob - The attacker
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
 *		  attacker - The attacker
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
	command("say You scum, stop fighting my friend!");
	command("kill " + lower_case(ob->query_real_name()));
    }
}
