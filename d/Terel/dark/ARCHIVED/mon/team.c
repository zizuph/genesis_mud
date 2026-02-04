inherit "/std/monster";

#include <stdproperties.h>

void help_friend(object ob);
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
        set_alarm(rnd()*5.0 + 1.0, 0.0, &help_friend(attacker));
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
//  command("kill " + lower_case(ob->query_real_name()));
    switch(random(5))
    {
      case 0:
       command("roar aggres");
        break;
      case 1:
        command("growl all");
        break;
      case 2:
        command("snarl all");
        break;
      case 3:
       command("stomp angry");
        break;
      case 4:
        command("roar");
        break;
    }
    attack_object(ob);
    add_prop(LIVE_O_LAST_KILL, ob);
  }
}
