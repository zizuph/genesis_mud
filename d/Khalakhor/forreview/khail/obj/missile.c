#include "/d/Immortal/std/domain.h"

inherit STDOBJECT;

int
is_ammunition()
{ return 1; }

void
set_hit(object target, object attacker)
{
  if(!present(target,environment(attacker)))
    {
    tell_room(environment(attacker),"The "+TO->short()+" sails harmlessly "+
      "through the air and vanishes into the distance.\n");
    remove_object();
    }

  if(random(400)+1 > target->query_stat(SS_DEX) ||
    target->check_skill(SS_DEFENCE))
    {
    attacker->catch_msg(QCTNAME(target)+" manages to avoid your "+TO->short()+
      "completely and it comes to rest on the ground behind "+
      target->query_objective()+".\n");
    target->catch_msg("You manage to avoid "+QTNAME(attacker)+"'s "+
      TO->short()+" completely, and it comes to rest on the gound behind "+
      "you.\n");
    tell_room(environment(target),QCTNAME(target)+" manages to avoid "+
        QTNAME(attacker)+"'s "+TO->short()+", and it comes to rest on the "+
        "ground behind "+target->query_objective()+".\n");
    TO->move(environment(target));
