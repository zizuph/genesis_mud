#ifndef QCTNAME
#include <macros.h>
#endif
#ifdef ASSIST_ME_HP
public varargs mixed
hit_me(int wcpen, int dt, object enemy, int attack_id,
    int target_hitloc)
{
    object to = this_object(), *team;
    int i, sz, hp = query_hp();
    mixed output = ::hit_me(wcpen, dt, enemy, attack_id, target_hitloc);

    if(hp <= ASSIST_ME_HP)
    {
        team = query_team_others();
        sz = sizeof(team);

        for(i=0; i<sz; i++)
        {
            if(!team[i]->query_hp() > hp)
                continue;

            enemy->catch_msg(QCTNAME(team[i]) +
                " steps in between you " + "and " + QTNAME(to) + ".\n");
            tell_room(environment(to),
                QCTNAME(team[i]) + " steps in between " + QTNAME(enemy) +
                " and " + QTNAME(to) + ".\n", enemy);
            enemy->attack_object(team[i]);
            return output;
        }
    }

    return output;
}
#endif
