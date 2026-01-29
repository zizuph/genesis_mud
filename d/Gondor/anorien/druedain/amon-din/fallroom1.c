inherit "/d/Gondor/common/room.c";

#include "/d/Gondor/defs.h"

#define LOG_FILE  "ad_fall"

/*
 *  Prototypes
 */
void hazards(object ob);
int  test_death(object ob);

/*
 *  Global Variables
 */
int     alarm_no;
int     falldam;
string  logtxt;

void
create_room()
{
    set_short("you are tumbling head over heels down a rocky slope"
      + " amidst a flurry of stones and dust");
    set_long("You are tumbling head over heels down a rocky slope"
      + " amidst a flurry of stones and dust!\n");
}

void
do_log(object ob, string logtxt)
{
    log_file(LOG_FILE, ob->query_name() + " ("
      + ob->query_average_stat() + ")" + logtxt + "on: "
      + ctime(time()) + ".\n");

    return;
}

public void
enter_inv(object ob, object from)
{
    if (!living(ob))
    {
        ob->move(AMON_DIR + "fallroom3");
        return;
    }

    set_alarm(1.0, 0.0, &hazards(ob));
    return;
}

int
down_slope(object ob)
{
    ob->move_living("down the slope", AMON_DIR + "fallroom2");

    return 1;
}

void
rock(object ob)
{
    falldam = ob->query_encumberance_weight() * 2 + 50;

    write(BSN("You slam into a large protrusion of rock, and tumble"
      + " further down the slope!"));
    ob->reduce_hit_point(falldam);

    logtxt = " hit rock for " +falldam+ " damage ";
    do_log(ob, logtxt);

    if (!test_death(ob))
    {
        set_alarm(1.0, 0.0, &down_slope(ob));
        return;
    }

    return;
}

void
twigs(object ob)
{
    falldam = 20 + random(11);
    write(BSN("As you tumble, your face skids over many sharp roots"
      + " and twigs!"));
    ob->reduce_hit_point(falldam);

    logtxt = " skidded for " +falldam+ " damage ";
    do_log(ob, logtxt);

    if (!test_death(ob))
    {
        set_alarm(1.0, 0.0, &down_slope(ob));
        return;
    }

    return;
}

void
dust(object ob)
{
    falldam = 7 + random(10);

    write(BSN("Dust fills your eyes and mouth as you tumble, numbing"
      + " your senses with stinging pain!"));
    ob->reduce_hit_point(falldam);

    logtxt = " tumbled for " +falldam+ " damage ";
    do_log(ob, logtxt);

    if (!test_death(ob))
    {
        set_alarm(1.0, 0.0, &down_slope(ob));
        return;
    }

    return;
}

void
tumble(object ob)
{
    falldam = 45 + random(10);

    write(BSN("Your body is battered and bruised as you tumble down"
      + " the rocky slope!"));
    ob->reduce_hit_point(falldam);

    logtxt = " was bruised for " +falldam+ " damage ";
    do_log(ob, logtxt);

    if (!test_death(ob))
    {
        set_alarm(1.0, 0.0, &down_slope(ob));
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
            rock(ob);
            break;
        case 1:
            twigs(ob);
            break;
        case 2:
            dust(ob);
            break;
        case 3:
            tumble(ob);
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
        logtxt = " DIED from the fall ";
        do_log(ob, logtxt);

        return 1;
    }

    return 0;
}
