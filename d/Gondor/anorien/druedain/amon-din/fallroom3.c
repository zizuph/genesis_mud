inherit "/d/Gondor/common/room.c";

#include "/d/Gondor/defs.h"

#define  ALARM		set_alarm(1.0, 0.0, &down_slope(tp));
#define LOG_FILE  "ad_fall"

/*
 *  Prototypes
 */
void hazards(object ob);
int  test_death(object ob);

/*
 *  Global Variables
 */
int     fall_dam;
string  logtxt;

void
create_room()
{
    set_short("you tumble a painful distance further, and reach the"
      + " base of Amon Din");
    set_long("You tumble a painful distance further, and reach the"
      + " base of Amon Din.\n");
}

void
do_log(object tp, string logtxt)
{
    log_file(LOG_FILE, tp->query_name() + " ("
      + tp->query_average_stat()+") "+logtxt+"on: "+ctime(time())
      + ".\n");

    return;
}

public void
enter_inv(object ob, object from)
{
    if (!living(ob))
    {
        ob->move(AMON_DIR + "ad2");
        return;
    }

    set_alarm(1.0, 0.0, &hazards(ob));
    return;
}

int
down_slope(object ob)
{
    ob->move_living("M", AMON_DIR + "ad2", 1, 1);
    write("You are lying face-first in a clearing at the base of Amon"
      + " Din.\n");
    ob->command("$groan");

    return 1;
}

void
bushes(object tp)
{
    fall_dam = 15 + random(11);

    write("You crash through a cluster of bushes, and come to rest in"
      + " a painful heap at the base of the hilltop.\n");
    tp->reduce_hit_point(fall_dam);

    logtxt = "hit bushes for " + fall_dam + " damage ";
    do_log(tp, logtxt);

    if (!test_death(tp))
    {
        ALARM
        return;
    }

    return;
}

void
slide(object tp)
{
    fall_dam = 5 + random(8);

    write("You skid and slide over rough terrain at the end of the"
      + " slope, coming finally to rest in an exhausted heap at the"
      + " base of the hilltop.\n");
    tp->reduce_hit_point(fall_dam);

    logtxt = "skidded for " + fall_dam + " damage ";
    do_log(tp, logtxt);

    if (!test_death(tp))
    {
        ALARM
        return;
    }

    return;
}

void
rocks(object tp)
{
    fall_dam = 30 + random(8);

    write("You plow through a large pile of rocks and skid painfully"
      + " into a heap at the base of the hilltop.\n");
    tp->reduce_hit_point(fall_dam);

    logtxt = "hit rockpile for " + fall_dam + " damage ";
    do_log(tp, logtxt);

    if (!test_death(tp))
    {
        ALARM
        return;
    }

    return;
}

void
tree(object tp)
{
    fall_dam = tp->query_encumberance_weight() * 5 + 50;

    write("You slam with jarring force into the trunk of a tree, and"
      + " tumble limply into a broken heap at the base of the"
      + " hilltop.\n");
    tp->reduce_hit_point(fall_dam);

    logtxt = "hit tree for " + fall_dam + " damage ";
    do_log(tp, logtxt);

    if (!test_death(tp))
    {
        ALARM
        return;
    }

    return;
}

void
hazards(object ob)
{
    switch(random(4))
    {
        case 0:
            bushes(ob);
            break;
        case 1:
            slide(ob);
            break;
        case 2:
            rocks(ob);
            break;
        case 3:
            tree(ob);
            break;
        default:
    }
}

int
test_death(object ob)
{
    if (ob->query_hp() <= 0)
    {
        ob->do_die(TO);
        logtxt = "DIED from the fall ";
        do_log(ob, logtxt);

        return 1;
    }

    return 0;
}
