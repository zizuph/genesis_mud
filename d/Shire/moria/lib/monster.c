#include "defs.h"
#include <filter_funs.h>
#include <ss_types.h>

inherit "/d/Shire/std/monster";

// Global Variables
int walk_alarm = 0;

// Prototypes
void random_walk_alarm();

void
create_moria_monster() {}

void
create_shire_monster()
{
    walk_alarm = set_alarm(itof(random(25)),0.0,&random_walk_alarm());
    set_exp_factor(140); 
    create_moria_monster();
}

int myrand(int val)
{
    return val-val/4+random(val/2)+1;
}

int skill_random(int val)
{
    return MIN(myrand(val), 100);
}

void
setup_skills()
{
    mapping allskills = SS_SKILL_DESC;
    int i, *skills = m_indexes(allskills);
    int stat;

    i = sizeof(skills);
    while (i--)
	set_skill(skills[i], 
	  skill_random(query_stat(allskills[skills[i]][2])/2));
}

int
go_home()
{
    int res = -1;
    FIXEUID;
    if (monster_home)
	res = move_living("home", monster_home);
    return res == -1;
}

int
is_not_npc(object ob)
{
    return !ob->query_npc();
}

int
other_live(object ob)
{
    return ob != TO && living(ob) && ENV(ob)==ETO && CAN_SEE(TO, ob);
} 

int
is_friend(object ob)
{
    return ob != TO && living(ob) && query_race_name()==ob->query_race_name();
}

int
is_not_fighting(object ob)
{
    return !ob->query_attack();
}

#define SPEED ({ 120, 60, 20, 10 })

random_walk_alarm()
{
    string ex, dummy, lmove;
    mixed *exits;
    int i,next,sz;
    object corpse;
    int walk_status;

    if (!ETO) return;

    walk_status = CONTROL->query_status();
    if (!walk_alarm)
	walk_alarm = set_alarm(itof(random(20)), 0.0, &random_walk_alarm());

    if (TO->query_attack())
	return;

    exits = (mixed *)filter_exits(ETO->query_exit(-1)); 

    /* Filters exits. */
    if (sscanf(file_name(ETO), MORIA_DIR + "%s", dummy) != 1)
    {
	go_home();
	return;
    }
    else 
    {
	lmove = query_prop(LIVE_S_LAST_MOVE);
	sz = sizeof(exits);
	if (sz && (!random(4) || !IS_IN(lmove, exits)))
	    ex = exits[random(sz/3)*3 + 1];
	else
	    ex = lmove;
    }

    if (corpse = present("corpse", ETO)) {
	sz = sizeof(INV(corpse));
	if (sz)
	    TO->loot_corpse();
    } else if (ex) 
	command(ex);
}

varargs void
change_opponent(object *opponents)
{
    int i, nr, new = -1, hits;

    if (!opponents)
	opponents = query_enemy(-1);
    if (!sizeof(opponents))
	return;

    set_this_player(TO);
    opponents = FILTER_PRESENT_LIVE(opponents);

    if ((nr = sizeof(opponents)) <= 1)
	return;

    hits = opponents[0]->query_hp();

    for (i=1; i<nr; i++)
	if (random(2) && HP(opponents[i]) < hits) // Pick the weakest.. *grin*
	{
	    hits = HP(opponents[i]);
	    new  = i;
	}

    if (new == -1 || opponents[new] == query_attack())
	return;

    TO->notify_changed_opponent(opponents[new]);
    attack_object(opponents[new]);
}

void
loot_corpse()
{
    if (present("shire_sack", TO)) {
	if (present("corpse", ETO)) {
	    command("open sack");
	    command("sackloot corpses");
	    command("close sack");
	}
    }
}

int
query_knight_prestige()
{    
    return 3*query_average_stat();
}



#if 0
object *enemies;
object *friends =({});
object *livings =({});

livings = filter(INV(ETO), "other_live", TO);
sz = sizeof(livings);

if (sz) {
    enemies = livings & query_enemy(-1);
    friends = filter(livings, "is_friend", TO);

    if (sizeof(enemies))
    {
	change_opponent(enemies);
	if (sizeof(friends))
	{
	    friends = filter(friends, "is_not_fighting", TO);
	    friends->orc_can_you_help_me(enemies);
	}
	return;
    }           

}
#endif
