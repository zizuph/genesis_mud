#pragma strict_types
 
static mapping bonuses = ([]);
static int bonus_active = 0;
 
private object owner;
 
static void activate_single_bonus(int s, int bonus_val);
 
public void
set_enhancement(int s, int v)
{
    bonuses[s] = v;
}
 
public void
activate_bonus()
{
    int i, *j, *k;
 
    if (!living(owner))
    {
        owner = 0;
        bonus_active = 0;
        return;
    }
 
    if (bonus_active)
        return;
 
    j = m_indices(bonuses);
    k = m_values(bonuses);
    i = sizeof(j);
    while (i--)
        activate_single_bonus(j[i], k[i]);
    bonus_active = 1;
}
 
static void
activate_single_bonus(int s, int bonus_val)
{
    if (s < 0)
    {
        s = -(s + 1);
        owner->set_stat_extra(s, owner->query_stat_extra(s) + bonus_val);
    }
    else
        owner->set_skill_extra(s, owner->query_skill_extra(s) + bonus_val);
}
 
public void
deactivate_bonus()
{
    int i, *j, *k;
    if (!bonus_active)
        return;
 
    j = m_indices(bonuses);
    k = m_values(bonuses);
    i = sizeof(j);
    while (i--)
        activate_single_bonus(j[i], -k[i]);
    bonus_active = 0;
}
 
static void
enhance_enter_env(object to, object from)
{
    if (living(to))
        owner = to;
}
 
static void
enhance_leave_env(object from, object to)
{
    deactivate_bonus();
    owner = 0;
}
