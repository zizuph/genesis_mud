
void
do_die(object killer)
{
    ATTACKERS_ADMIN->add_reputation(killer,CRIME_MURDER);
    ::do_die(killer);
}

void
attacked_by(object attacker)
{
    ATTACKERS_ADMIN->add_reputation(attacker,CRIME_ATTACK);
    ::attacked_by(attacker);
}

int
check_for_attack()
{
    return ATTACKERS_ADMIN->query_auto_attack(TO,TP);
}

#define SET_NERAKA_AGGRESSIVE    set_aggressive("@@check_for_attack@@")
