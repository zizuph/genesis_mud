/*  A little code to include in the cityguards, so that they will both
 *  cry for help when attacked, and help those who cry for help.
 */

int is_helping;
heart_beat()
{
  ::heart_beat();
    if (!query_attack()) return;
    if (!random(5)) command("say Help!");
    return;
}

help_triggered(who,str)
{
  object attacker;
  who = lower_case(who);
  if (present(who,this_object()))
    {
      attacker = present(who,this_object())->query_attack();
      is_helping = 1;
      command("say I will help you, "+capitalize(who)+", and fight "+attacker->query_cap_name());
      command("kill "+lower_case(attacker->query_name()));
      return;
    }
  return;
}
