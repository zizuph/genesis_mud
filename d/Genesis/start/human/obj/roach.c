#pragma save_binary
#pragma strict_types

inherit "/std/creature";
inherit "/std/act/domove";
#include <ss_types.h>
#include <wa_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>

#define TR			environment(this_object())
#define CHURCH	        	"/d/Genesis/start/human/town/church"
#define MAX_FERTILE		9	/* Max number of fertile roaches.  */
#define MAX_ROACHES		18	/* Absolute max number of roaches. */

int sterile, roaches, ronum;
object debugplayer;

void
create_creature()
{

    if (!IS_CLONE) return;

    seteuid(getuid(this_object()));

    set_name("roach");
    set_race_name("cockroach"); 
    set_adj("filthy");

    set_long("A little disgusting cockroach.\n");

            /* str, dex, con, int, wis,  dis  	 */
    set_stats(({ 1,   4,   1,   2,   3,   4}));
    set_hp(1);

    if (random(100)<25) set_random_move(1);
        set_random_move(random(10)+4);

    add_prop(CONT_I_WEIGHT, 20);
    add_prop(CONT_I_HEIGHT, 10);
    add_prop(CONT_I_VOLUME, 30);
    add_prop(CONT_I_IN, 0);
    add_prop(LIVE_I_NEVERKNOWN, 1);


    ronum = CHURCH->roach(1);

    if (ronum > MAX_ROACHES) { 
	sterile = 1;
	set_alarm(1.0, 0.0, &remove_object());
	return;
    }
    if (ronum > MAX_FERTILE) {
	sterile = 1;
	return;
    }
    return;
}

void
cr_configure()
{
    add_attack(100, 0, W_IMPALE, 100, 0);
    add_hitloc( ({ 0, 0, 0, 0 }), 20, "head", 0);
    add_hitloc( ({ 0, 0, 0, 0 }), 80, "body", 1);
}

string
cr_attack_desc(int aid)
{
    if (aid == 0)
	return "tiny jaws"; 
    return "mind"; /* should never occur */
}

int
query_gender()
{
    return 2;
}

int
other_roach(object ob)
{
    return (ob->id("roach") && ob != this_object());
}

void
leave_env(object from, object to)
{
    object *roaches, obj, new;
    int i;

    ::leave_env(from, to);
    if (!IS_CLONE)
	return;

    if (!to) {		/* Monster died. */
	ronum = CHURCH->roach(-1);
	return;
    }

    /*Monster moved*/
    roaches = filter(all_inventory(to), &other_roach());

    for (i = 0; i < sizeof(roaches); i++)
    {
	tell_room(TR,
		  "The little filthy cockroach produces a clicking sound.\n");
	
	if (random(100) < 40 && !sterile) {
	    tell_room(TR, "The cockroaches start reproducing.\n");
	    new = clone_object("/d/Genesis/start/human/obj/roach");
	    if (new) {
		new->move(TR);
	    }
	}
	return;
    }
}
