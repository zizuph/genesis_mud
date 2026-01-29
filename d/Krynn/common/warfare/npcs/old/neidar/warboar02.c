/* created by Aridor 10/12/93 
 *
 * This is warboar without stunn 
 *
 */

#include <macros.h>

inherit "/d/Ansalon/estwilde/living/warboar";

void
attacked_by(object ob)
{

}

public void
hook_friend_attacked(object friend, object enemy)
{
    command("assist " + OB_NAME(friend));
}

public void
hook_friend_attack(object friend, object enemy)
{
    command("assist " + OB_NAME(friend));
}

public void
hook_friend_killed(object friend, object killer)
{
    command("kill " + OB_NAME(killer));
}
