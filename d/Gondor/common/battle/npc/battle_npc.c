/*
 * /d/Gondor/common/battle/npc/battle_npc.c
 *
 * A base battle npc.
 *
 * Coded by Gwyneth, June 25 2001
 */
inherit "/d/Gondor/std/monster";

#include <filter_funs.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Gondor/common/lib/friend_or_foe.c"

mapping opposite = ([ "up" : "down", "u" : "d", "down" : "up", "d" : "u",
                      "east" : "west", "e" : "w", "west" : "east", "w" : "e",
                      "north" : "south", "n" : "s", "south" : "north", 
		      "s" : "n", "northwest" : "southeast", "nw" : "se",
                      "southeast" : "northwest", "se" : "nw",
                      "northeast" : "southwest", "ne" : "sw",
                      "southwest" : "northeast", "sw" : "ne",
                      "tent" : "out" ]);
int    gLeader    = 0;
int    gLocation  = 0;
int    gRetreat   = 0;
int    gWalkAlarm = 0;
float  gMoveTime  = 3.0;
string *gPath      = ({});

int  query_team_leader();
int  check_aggro();
void next_move();
void test_lead();

void
create_battle_npc()
{
}

void
create_gondor_monster()
{
    create_battle_npc();

    /* If they're walking a path, they shouldn't stray unless */
    /* circumstances require panic, at which point this prop is removed. */
    add_prop(NPC_I_NO_RUN_AWAY, 1);

    set_aggressive(&check_aggro());
    set_alarm(1.0, 0.0, test_lead);
}

int
check_aggro()
{
    switch(query_alignment())
    {
    case 0..1200:
        if (query_friend_or_foe(this_player()) == -1)
	    return 1;
	break;
    case -1200..-1:
        if (query_friend_or_foe(this_player()) == 1)
	    return 1;
        break;
    default:
        break;
    }

    return 0;
}

void
test_lead()
{
    if (query_team_leader())
        gWalkAlarm = set_alarm(gMoveTime + rnd() + rnd(), 
            gMoveTime + rnd() + rnd(), &next_move());
}

void
set_move_time(float f)
{
    if (f >= 1.0)
        gMoveTime = f;
    else
        gMoveTime = 1.0;
}

void
set_team_leader(int leader = 1)
{
    gLeader = leader;
}

int
query_team_leader()
{
    return gLeader;
}

void
set_path(string *walk_path)
{
    gPath = walk_path;
}

void
set_location(int i)
{
    gLocation = i;
}

void
check_losing()
{
    int i, size, enemy_bonus = 0, team_bonus = 0;
    object *team, *enemies = ({}), *temp_enemies = ({});

    /* Find the others on the team and this npc. */
    team = query_team_others();
    team += ({ this_object() });

    /* Find the enemies of each person on the team. */
    for (i = 0, size = sizeof(team); i < size; i++)
    {
        /* Accumulate the team bonus by stats */
        team_bonus += team[i]->query_average_stat();

        /* All the enemies of the team */
        temp_enemies += team[i]->query_enemy(-1);
    }

    /* Find all the livings in this room. */
    enemies = FILTER_LIVE(all_inventory(environment()));

    /* Find all the enemies that are also in this room */
    enemies = enemies & temp_enemies;

    /* Add up the enemy team's stat-average */
    for (i = 0, size = sizeof(enemies); i < size; i++)
        enemy_bonus += enemies[i]->query_average_stat();

    /* Will only retreat if the enemy is twice as large on a whole. */
    team_bonus *= 2;

    if (team_bonus < enemy_bonus)
        gRetreat++;
    else
        gRetreat = (!gRetreat ? gRetreat : gRetreat - 1);
}

int
check_enemies()
{
    int i, size, friend_status, en_health, arr_position, enemies;
    object *team, *others;

    team = query_team_others() + ({ this_object() });

    for (i = 0, size = sizeof(team); i < size; i++)
    {
        if (present(team[i]->query_attack(), environment()))
            return 1;
    }

    others = FILTER_LIVE(all_inventory(environment())) - team;

    for (i = 0, size = sizeof(others); i < size; i++)
    {
        friend_status = query_friend_or_foe(others[i]);

        /* Evil team, good enemies */
        if (this_object()->query_alignment() < 0 && friend_status == 1)
        {
            if (!i)
            {
                en_health = others[i]->query_hp();
                arr_position = 0;
            }
            else if (random(en_health) > random(others[i]->query_hp()))
            {
                en_health = others[i]->query_hp();
                arr_position = i;
            }

            enemies = 1;
        }
        else if (this_object()->query_alignment() > 0 && 
	  friend_status == -1)
        {
            if (!i)
            {
                en_health = others[i]->query_hp();
                arr_position = 0;
            }
            else if (random(en_health) > random(others[i]->query_hp()))
            {
                en_health = others[i]->query_hp();
                arr_position = i;
            }

            enemies = 1;
        }
    }

    if (enemies)
    {
        team->command("kill " + OB_NAME((others[arr_position])));
        return 1;
    }

    return 0;
}

void
scatter()
{
    int i, size;
    object temp_ob, *team = query_team_others();

    /* The leader will stand and fight. */
    for (i = 0, size = sizeof(team); i < size; i++)
    {
        if (present(team[i], environment()) &&
          random(150) > team[i]->query_stat(SS_DIS))
        {
            this_object()->leave_team(team[i]);
            team[i]->remove_prop(NPC_I_NO_RUN_AWAY);
	    team[i]->add_panic(random(100));
	    temp_ob = team[i];
            set_alarm(rnd(), 0.0, &temp_ob->run_away());
        }
    }
}

void
end_walk()
{
    remove_alarm(gWalkAlarm);
}

void
next_move()
{
    /* No enemies in the room, advance. */
    if (!check_enemies())
    {
        if (gLocation >= sizeof(gPath))
        {
            end_walk();
        }
        else
        {
            command(gPath[gLocation]);
            gLocation++;
        }
    }

    /* Are we vastly outnumbered? Retreat */
    check_losing();
    switch(gRetreat)
    {
    case 0:
        break;
    case 1:
        if (gLocation)
        {
            command(opposite[gPath[gLocation]]);
            gLocation--;
        }
        else
        {
            scatter();
        }
        break;
    default:
        if (gLocation)
        {
            command(opposite[gPath[gLocation]]);
            gLocation--;
        }

        scatter();
        break;
    }
}

void
new_leader(object killer)
{
    int i, size, arr_position, dis, temp_dis;
    object *team, leader;

    team = query_team_others();

    /* Everyone's gone! */
    if (!sizeof(team))
        return;

    /* 1 in 20 chance of no new leader being selected and team panicking */
    if (!random(20))
    {
        scatter();
        return;
    }

    dis = team[0]->query_stat(SS_DIS);
    arr_position = 0;
    this_object()->team_leave(team[0]);

    for (i = 1, size = sizeof(team); i < size; i++)
    {
        this_object()->team_leave(team[i]);
        temp_dis = team[i]->query_stat(SS_DIS) > dis;
        if (temp_dis > dis)
        {
            dis = temp_dis;
            arr_position = i;
        }
    }

    if (dis < 50)
    {
        scatter();
        return;
    }

    team[arr_position]->set_location(gLocation);
    team[arr_position]->set_path(gPath);
    team[arr_position]->set_team_leader();
    team[arr_position]->set_move_time(gMoveTime);
    team[arr_position]->test_lead();

    for (i = 0, size = sizeof(team); i < size; i++)
    {
        if (i != arr_position)
            team[arr_position]->team_join(team[i]);
    }

    tell_room(environment(), QCTNAME(team[arr_position]) + " rallies " +
        team[arr_position]->query_possessive() + " troops!\n");

    team->attack_object(killer);
    return;
}

void
do_die(object killer)
{
    if (query_team_leader())
        new_leader(killer);

    ::do_die(killer);
}

void
kill_enemy(object ob)
{
    if (!objectp(ob) || !present(ob, environment(this_object())))
    {
        return;
    }

    command("kill " + OB_NAME(ob));
}

void
init_living()
{
    ::init_living();

    if (!this_player()->query_npc())
        return;

    if (member_array(this_player(), query_team_others()) != -1)
        return;

    switch(query_alignment())
    {
    case 0..1200:
        if (query_friend_or_foe(this_player()) == -1)
            set_alarm(2.0, 0.0, &kill_enemy(this_player()));
        return;
    case -1200..-1:
        if (query_friend_or_foe(this_player()) == 1)
	    set_alarm(2.0, 0.0, &kill_enemy(this_player()));
        return;
    default:
        return;
    }

}
