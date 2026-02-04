/* Creative rights reserved to Mecien(Jeff Babcock) and team. */
/*
 * transf_npc.c
 * An object controlling the transformed animal.
 * Used by the Mystic Order spell: 'immuto'
 */

inherit "/std/object";

#include <macros.h>

#define TP            this_player()
#define TO            this_object()
#define IS_WIZ(xx)    xx->query_wiz_level()
#define ENV           environment

#define MIN_DUR       10
#define DEF_DUR       60
#define MAX_DUR       1000

#define DEFAULT_PLACE "/d/Terel/mecien/valley/guild/bt"

object  link_player, link_monster, death_place, mon_killer;
int     duration=DEF_DUR, initial_c_exp, final_c_exp, aid=0;
object  pit_room;

public  void    set_duration(int t);
public  void    set_pit_room(object room);
public  int     query_time_left();
public  int     stop_trans();
public  string  rem_leading_spaces(string str);
public  object *get_obj_enemies(object ob);
public  void    attack_link_obj(object ob, object *enemies);

public void
create_object()
{
    set_name("mystic transform wand");
    add_name("wand"); 
    set_adj( ({"arcane", "ash"}) );
    set_short("arcane ash wand");
    set_long("@@long_func");
    death_place = 0;
}
    
public string
long_func()
{
    string str;

    str = "It's quite definetely a divine wand.\n";
    if (link_monster) {
        if (link_monster && environment(TO) == TP)
            str += "You feel the presence of " +
                   link_monster->query_name() + ".\n";
        else
            str += "It seems to be active.\n";
    }
    return str;
}

public void
set_pit_room(object room)
{
    pit_room = room;
}

public void
set_duration(int t)
{
    if (t < MIN_DUR) t = MIN_DUR;
    if (t > MAX_DUR) t = MAX_DUR;
    duration = t;
}

public int
query_time_left()
{
    mixed *a;
    int time = -1;
    
    if (aid) {
        a = get_alarm(aid);
        time = ftoi(a[2]);
    }
    return time;
}

public void
set_npc(object monster)
{
    if (!link_monster) link_monster = monster;
}

public void
init()
{
    if (environment(TO) == TP) {
        if (IS_WIZ(TP)) {
            add_action("remote_cmd", "#", 1);
            add_action("stop_trans", "stop_trans");
        } else {
            add_action("remote_cmd", "",    1);
            aid = set_alarm(itof(duration), -1.0, stop_trans);
        }
    }
}

public int
remote_cmd(string str)
{
    string verb, cmd;
    int cmd_flag;

    if (!link_monster) {   /* Monster is no more */
        stop_trans();
        return 1;
    }
    verb = query_verb();
    cmd = verb + (str ? (" " + str) : "");
    if (IS_WIZ(TP)) {
	cmd = extract(cmd, 1);
	cmd = rem_leading_spaces(cmd);
	if (extract(cmd, 0, 2) == "say") return 0;
	if (extract(cmd, 0, 0) == "'") return 0;
        return link_monster->command(cmd);
    }
    cmd = rem_leading_spaces(cmd);
    if (extract(cmd, 0, 2) == "say" ||
	extract(cmd, 0, 0) == "'") {
	link_monster->catch_msg("What ?\n");
	return 1;
    }
    cmd_flag = link_monster->command(cmd);
    if (!cmd_flag) {
	if (extract(cmd, 0, 3) == "quit") {
	    stop_trans();
	    cmd_flag = 0;
	} else if (extract(cmd, 0, 6) == "commune") {
	    cmd_flag = 0;
	} else {
	    link_monster->catch_msg("What ?\n");
	    cmd_flag = 1;
	}
    }
    return cmd_flag;
}

public void
enter_env(object dest, object old)
{
    object here, lp, lm, place;
    object *enemies;

    ::enter_env(dest, old);
    
    if (living(dest)) link_player = dest;
    if (link_player && link_monster) {
	lp = link_player;
	lm = link_monster;
        here = ENV(lp);
        place = lp->query_defalt_start_location();
        lp->catch_msg("You are engulfed in a blaze of fiery " +
                      "white light and your body dissolves!\n");
        initial_c_exp = lm->query_exp_combat();
	enemies = get_obj_enemies(lp);
	if (IS_WIZ(lp)) {
	    lp->catch_msg("*** Use 'stop_trans' to stop it! ***\n");
	}
        if (!IS_WIZ(lp)) lp->set_tell_active(0);
        tell_room(here, QCTNAME(lp) + " is engulfed in a blaze of " +
                  "fiery white light and dissolves into nothingness!\n",
                  lp);
	if (pit_room) {
            lp->move_living("M", pit_room, 1);
	} else {
            lp->move_living("M", lp->query_default_start_location(), 1);
	}
        lm->move_living("M", here);
        lm->set_tell_active(1);
	attack_link_obj(lm, enemies);
    } else {
        stop_trans();
    }
}

public void
leave_env(object old, object dest)
{
    object lp, lm, place;
    object *enemies;

    ::leave_env(old, dest);
    
    if (link_player) {
	lp = link_player;
        if (!IS_WIZ(lp)) lp->set_tell_active(1);
        lp->catch_msg("You once again take shape.\n");
    }
    if (link_player && link_monster) {
	lm = link_monster;
        place = environment(lm);
        if (living(place)) place = environment(place);
        final_c_exp = lm->query_exp_combat();
        lp->add_exp((final_c_exp - initial_c_exp)/5, 1);
	enemies = get_obj_enemies(lm);
        lm->command("$drop all");
        lm->remove_object();
        if (lp->move_living("M", place, 1, 1)) {
            lp->move_living("X", DEFAULT_PLACE, 1);
        } else {
            tell_room(place, QCTNAME(lp) + 
                      " forms out of the swirling dust cloud.\n", lp);
	    if (sizeof(enemies)) attack_link_obj(lp, enemies);
	}
    } else if (link_player) {
	if (death_place) {
          if (lp->move_living("M", death_place, 1, 1)) {
            lp->move_living("X", DEFAULT_PLACE, 1);
          } else {
	    tell_room(death_place, QCTNAME(lp) +
		" arrives.\n", lp);
	    if (mon_killer && living(mon_killer) &&
		environment(lp) == environment(mon_killer)) {
                lp->catch_msg(QCTNAME(mon_killer) + " looks at " +
			    "you suspiciously.\n");
	    }
	  }
	} else { /* Monster died by wizard intervention! */
           lp->move_living("X", DEFAULT_PLACE, 1);
	}
    }
    if (link_monster) link_monster->remove_object();
    link_player = 0;
}

public int
stop_trans()
{
    if (aid) remove_alarm(aid);
    remove_object();
    aid = 0;
    return 1;
}

public void
link_intext(string str)
{
    if (link_player) tell_object(link_player, str);
}

public void
link_monster_died(object killer)
{
    object lp, lm;

    if (link_player) {
        lp = link_player;
	if (link_monster) {
	    lm = link_monster;
	    death_place = environment(lm);
	    mon_killer = killer;
	    lm->catch_msg("The body you are inhabiting dies.\n");
	}
	if (!IS_WIZ(lp)) {
            lp->reduce_hit_point(lp->query_hp() - 1);
            lp->add_mana(1 - lp->query_mana());
	}
    }
    stop_trans();
}

public string
rem_leading_spaces(string str)
{
    int i;
    string c, s;

    s = "";
    for (i=0; i<strlen(str); i++) {
	c = extract(str, i, i);
	if (c != " ") {
	    s += c;
	} else {
	    if (strlen(s)) s += c;
	}
    }
    return s;
}

public object *
get_obj_enemies(object ob)
{
    int i;
    object *all, *enemies;

    enemies = ({});
    all = all_inventory(environment(ob));
    for (i=0; i<sizeof(all); i++) {
	if (living(all[i]) && all[i] != ob &&
	    member_array(all[i], ob->query_enemy(-1)) >= 0) {
	    enemies += ({ all[i] });
	}
    }
    return enemies;
}

public void
attack_link_obj(object ob, object *enemies)
{
    int i;

    for (i=0; i<sizeof(enemies); i++) {
	if (environment(ob) == environment(enemies[i])) {
            ob->catch_msg(QCTNAME(enemies[i]) + " looks a bit " +
			  "confused for a while.\n");
	    enemies[i]->attack_object(ob);
	}
    }
}
