/*
spiders are interesting creatures.  They can only bite.  But if they
bite you you have a random chance of being stunned, and they will try to
web you up.
*/

inherit "/std/creature";
inherit "/std/act/domove.c";
inherit "/std/combat/unarmed"; 
inherit "/std/act/action";
inherit "/std/act/chat";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <filter_funs.h>
#include <formulas.h>

#define A_BITE  0

#define H_HEAD 0
#define H_BODY 1
create_creature()
{
    object para;

    set_name("spider"); 
    set_race_name("spider");
    set_short("black spider");
    set_adj(({"black", "menacing" }));
    set_long("It looks rather menacing!\n");

    /* 
    str, con, dex, int, wis, dis
    somebody tell me if these are good values
    */

    set_stats(({ 45, 48, 80, 29, 31, 75}));

    set_hitloc_unarmed(H_HEAD, ({ 15, 25, 20, 20 }), 20, "head");
    set_hitloc_unarmed(H_BODY, ({ 10, 15, 30, 20 }), 80, "body");
    set_hp(query_max_hp());
    set_random_move(1);

	
    set_skill(SS_DEFENCE, 30);

/* these values might be wrong */
    set_attack_unarmed(A_BITE,  20, 30, W_IMPALE, 100, "jaws");

    set_chat_time(2);
    add_chat("Bite him!");
    add_chat("Sting him!");
    add_chat("He looks plump and tasty!");

    set_cchat_time(2);
    add_cchat("I want to eat him now!");
    add_cchat("I think he's dead now!");
    add_cchat("Shelob says you should hang them for days first.");
    add_cchat("It's still wriggling!  It's not dead yet!");
    add_cchat("I am hungry now!");
    add_cchat("Are you sure this web will hold him?");
    add_cchat("Why don't you sting him again?");
    add_cchat("Why do we always have to do what you say anyhow?");

    add_prop(LIVE_I_NEVERKNOWN, 1);
}
	
/*
 * Function name: tell_watcher
 * Description:   Send the string from the fight to people that want them
 * Arguments:     The string to send
 */
static void
tell_watcher(string str, object enemy)
{
    object me,*ob;
    int i;

    me = this_object();
    ob = FILTER_LIVE(all_inventory(environment(me))) - ({ me });
    ob -= ({ enemy });
    for (i = 0; i < sizeof(ob); i++)
        if (ob[i]->query_see_blood())
            ob[i]->catch_msg(str);
}

/*
 * Here we redefine the special_attack function which is called from
 * within the combat system. If we return 0 then there will be no
 * additional web attack.
 */
int
special_attack(object enemy)
{
    object me, paralyze, web;
    mixed *hitresult;
    string howlong;
    int i;

    me = this_object();

    if (present("_spider_paralyze_", enemy)) {
	seteuid(getuid());
	web = clone_object("/d/Rhovanion/hazelnut/web");
	web->move(environment());

	enemy->catch_msg(QCTNAME(me) + " spins a web around you!\n");
	enemy->stop_fight(this_object());
	tell_room(environment(), QCTNAME(me) + " spins a web around " + QTNAME(enemy) + ".\n", enemy);
	enemy->move_living("M", web, 1, 1);
	return 1;
    }

    if (random(15))
	return 0;

    hitresult = enemy->hit_me(20+random(20), W_IMPALE, me, -1);

    i = F_DAMAGE(hitresult[2], 0);

    howlong =" for a brief moment";

    if (i > 10)
	howlong = " for a short time";
    if (i > 20)
	howlong = " for a while";

    enemy->catch_msg("You are stunned" + howlong + " by " + QTNAME(me) + "'s attack.\n");
    tell_watcher(QCTNAME(enemy) + " is stunned" + howlong + " by " + QTNAME(me) +
		 "'s attack.\n", enemy);

    if (hitresult[0] > 0) {
	seteuid(getuid());
	paralyze = clone_object("/std/paralyze");
	paralyze->set_name("_spider_paralyze_");
	paralyze->set_no_show(1);
	paralyze->set_remove_time(i);
	paralyze->set_stop_message("You shake your head as you regain your senses!\n");
	paralyze->set_fail_message("You can't do that, you are still stunned!\n");
	paralyze->set_stop_verb("depart");	/* No command to stop the paralyze! */
	paralyze->set_stop_object(0);	/* Use the messages set above */
	paralyze->move(enemy, 1);	/* Now DO the paralyze */
    }

    if(enemy->query_hp() <= 0)
	enemy->do_die(me);
    
    return 1;
}
void
set_living_name(string name)
{
    efun::set_living_name(name);
}
