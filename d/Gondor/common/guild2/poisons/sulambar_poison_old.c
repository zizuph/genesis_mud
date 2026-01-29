/*
 * /d/Gondor/common/guild2/poisons/sulambar_poison.c
 * Powerful stat reducing poison
 * Olorin, 26-jul-1994
 *
 * Modification log:
 * add_tmp_stat() sets up an alarm. The limit of alarms per object
 * introduced by the gd is 16. I therefore had to increase
 * the strength of the poison while increasing the interval time.
 * Olorin, 18-dec-1996
 */
inherit "/std/poison_effect";

#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/common/guild2/lib/morgul_defs.h"
#include "/d/Gondor/defs.h"

#define STAT_DROP 15

#define SULAMBAR_LOG "/d/Gondor/common/guild2/poisons/sulambar_log"

public int poison_count = 0;
// damage this person has received

void
create_poison_effect()
{
    set_name("Morgul_Sulambar_Poison");
    set_interval(45);
    set_poison_type("Morgul_Sulambar_Poison");
    set_damage(({
	POISON_FATIGUE,  50,     
	POISON_USER_DEF, 1 }));
    set_silent(1);
}

public string
query_poison_recover()
{
    setuid();
    seteuid(getuid());

    return poison_count + "";

}

public void
init_poison_recover(string arg)
{
    if (!sscanf(arg, "%d", poison_count))
    {
	return;
    }

    this_player()->set_stat_extra(SS_STR,
        this_player()->query_stat_extra(SS_STR) - poison_count * STAT_DROP);
    this_player()->set_stat_extra(SS_DEX,
        this_player()->query_stat_extra(SS_DEX) - poison_count * STAT_DROP);
    this_player()->set_stat_extra(SS_CON,
        this_player()->query_stat_extra(SS_CON) - poison_count * STAT_DROP);

    /* Good idea to throw a catch() around this so that it doesn't cause
     * problems for the player if there's a bug in writing to the log.
     */
    catch(log_file(SULAMBAR_LOG, "==> " + this_player()->query_name() +
      " recovers the sulambar poison./n "+
      "   The number of hits is: " + poison_count + "\n"+
      "   The strength is::::::: " + query_strength() +"\n"+
      "   The interval is::::::: " + query_interval() +"\n"+
      "   The time remaining is: " + query_time_left() + "\n"));
}

public void
timeout()
{
    poisonee->set_stat_extra(SS_STR,
        poisonee->query_stat_extra(SS_STR) + poison_count * STAT_DROP);
    poisonee->set_stat_extra(SS_DEX,
        poisonee->query_stat_extra(SS_DEX) + poison_count * STAT_DROP);
    poisonee->set_stat_extra(SS_CON,
        poisonee->query_stat_extra(SS_CON) + poison_count * STAT_DROP);

    ::timeout();
}

void
special_damage(int damage)
{
    int     res,
            fat;

    res = poisonee->query_magic_res(MAGIC_I_RES_POISON);
    if (random(100) < res)
    {
	return;
    }

    // One of their stats has bottomed out, stop lowering
    // stats and just drain fatigue like a beast
    if ((poisonee->query_stat(SS_STR) < 19) ||
        (poisonee->query_stat(SS_DEX) < 19) ||
        (poisonee->query_stat(SS_CON) < 19))
    {
	fat = random(70);
	poisonee->add_fatigue(-(70 + fat));
	return;
    }

    // They don't resist, so drop 15 points in str, dex, and con
    // and add 1 to the number of times they've been hit
    poison_count++;

    poisonee->set_stat_extra(SS_STR,
        (poisonee->query_stat_extra(SS_STR) - STAT_DROP));
    poisonee->set_stat_extra(SS_DEX,
        (poisonee->query_stat_extra(SS_DEX) - STAT_DROP));
    poisonee->set_stat_extra(SS_CON,
        (poisonee->query_stat_extra(SS_CON) - STAT_DROP));
}

