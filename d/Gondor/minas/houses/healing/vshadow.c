inherit "/std/shadow";

#include "/d/Earthsea/common/defs.h"

neuterized()
{
  return 1;
}
ogg_neuter()
{
  remove_shadow();
}
do_die(object killr)
{
  object who;

  who = query_shadow_who();

  if(who->query_hp()<=0)
    {
      who->catch_msg("As you die, you feel your male soul being released from your neuter body.\n");
      who->remove_autoshadow(REDLIGHT+"obj/vshadow");
      who->do_die(killr);
      remove_shadow();
    }
  else
    who->do_die(killr);
}
query_gender()
{
  return 2; /* neuter */
}
query_gender_string()
{
  return "neuter";
}
query_pronoun()
{
  return "it";
}
query_possessive()
{
  return "its";
}
query_objective()
{
  return "it";
}
