inherit "/d/Kalad/std/monster";
#include "/d/Kalad/defs.h"
#define KALAD_FOLLOW "_kalad_follow"

void steal_member(object *team, object leader);


void
create_monster()
{
    ::create_monster();
    set_name("dopo");
    set_long("A wierdo man.\n");
    set_stats(({100,100,100,100,100,100}));
    add_prop(LIVE_I_NEVERKNOWN,1);
}

void
init_living()
{
    ::init_living();
    if(interactive(TP))
        if(sizeof(TP->query_team()))
            steal_member(TP->query_team(),TP);
}

void
steal_member(object *team, object leader)
{
    int num,i,membern;
    object member;
    string *adj, entmess;
    num = sizeof(team);
    membern = random(num);
    member = team[membern];
    leader->team_leave(member);
    adj = member->query_adj(1);
    TO->set_adj(adj[0]);
    TO->add_adj(adj[1]);
    TO->set_name(lower_case(member->query_name()));
    TO->set_race_name(member->query_race_name());
    TO->set_gender(member->query_gender());
    TO->set_long(member->long());
    TO->add_prop(KALAD_FOLLOW,leader);
    entmess = leader->query_m_out();
    TO->trig_new("%l 'leaves' %s","check");
}

int
check(object live, string str)
{
    string fix;
    int i;
    i = strlen(str);
    fix = extract(str,1,i - 1);
    if(live == query_prop(KALAD_FOLLOW))
    {
        command("say I am going: "+fix+".");
        command("fix");
    }
}

