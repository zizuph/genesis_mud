
inherit "/std/object";
#include <ss_types.h>

int boost = 0;

public void create_object()
{
    set_short("defence booster");
    add_name("booster");
    add_adj("defence");
    set_long("This will boost defence to show what a new cb_tohit looks like");
}

public void enter_env(object dest, object old)
{
    if (!dest)
    {
        ::enter_inv(dest, old);
        return;
    }
    if (!living(dest))
    {
        ::enter_inv(dest, old);
        return;
    }

    boost = 50 - (
    dest->query_skill(SS_DEFENCE) + dest->query_skill(SS_PARRY) + 3) / 4;
    
    dest->set_skill_extra(SS_DEFENCE,
      dest->query_skill_extra(SS_DEFENCE) + boost);
}


public void leave_env(object ob, object dest)
{
    if (!boost)
    {
        ::leave_inv(ob, dest);
        return;
    }
    ob->set_skill_extra(SS_DEFENCE,
      ob->query_skill_extra(SS_DEFENCE) - boost);
}