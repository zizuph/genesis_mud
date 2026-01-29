/* created by Aridor 06/19/93 */

#include "../local.h"
#include <ss_types.h>
#include <macros.h>
#include <money.h>

inherit M_FILE

string color = "blue";
object the_prisoner;
object para;
object last_room;

/*prototypes*/
void put_prisoner_into_jail();
void drag_the_prisoner_along();
void get_prisoner_ready_for_jail();
void release_prisoner_from_ties();

void
set_color(string new_color)
{
    color = new_color;
}

#ifdef OBJ
#undef OBJ
#endif
#define OBJ  SOLAMN_DIR + "splains/obj/"
/* We use the standard weapons and armours here */


#include ARM_ME

void
create_krynn_monster()
{
    int k, i, j = random(6)+2; /* j is the level */
    string str;
    
    set_name("merc");
    add_name("mercenary");
    add_name("human");
    set_race_name("human");
    add_prop(OBJ_I_COLORABLE, 1);
    
#include LEVEL_ME

    set_short(query_adj(0) + " human mercenary");
    set_long("This is a mercenary in the dragon army. It seems his " +
	     "money is hard-earned. Apparently, this one has been set on " +
	     "duty to guard the bridge. " + str + ".\n");


    for(i=0; i<6; i++)
        set_base_stat(i, j * 10 + random(20));
    set_skill(SS_DEFENCE, j * 8 + random(20));
    set_skill(SS_WEP_SWORD, j * 7 + random(20));
    set_skill(SS_WEP_KNIFE, j * 7 + random(20));
    set_skill(SS_WEP_CLUB, j * 7 + random(20));
    set_skill(SS_WEP_POLEARM, j * 7 + random(20));
    set_skill(SS_WEP_JAVELIN, j * 4 + random(20));
    set_skill(SS_WEP_AXE, j * 7 + random(20));

    k = query_average_stat();
    k = k*k/10;
    set_alignment(-k);
    set_knight_prestige(k);

    set_all_attack_unarmed(j * 2, j * 3);
    set_all_hitloc_unarmed(j * 2);


    if (IS_CLONE)
      set_alarm(1.0,0.0,"arm_me", j);

}

void
attacked_by(object who)
{
    TO->block_completely(who);
    ::attacked_by(who);
}

/* SURRENDER command here */
void
block_completely(object who)
{
    command("laugh evilly");
    command("say You will never pass by me!");
    command("say Turn back now, next time I might not be so nice to you!");
    return;
    /* Don't do anything right now except scare the person and don't let him pass */


    if (E(who) != E(TO))
      return;
    /* For some unknown reason TP is set correctly, but still the
     * add_action isn't added right.... 
     */
    add_action("cant_do_it","",1);
    command("emote steps up to you to prevent your every move.");
}

int
perform_the_arrest(string str)
{
    NF("What?\n");
    if (TP != the_prisoner)
      return 0;
    TP->command("say I surrender!");
    TP->stop_fight(TO);
    stop_fight(TP);
    command("say You are under arrest!");
    para = clone_object("/std/paralyze");
    para->set_stop_verb("");
    para->set_stop_function(0);
    para->set_stop_object(0);
    para->set_stop_message("You feel like you can move again.\n");
    para->set_fail_message("You are held too fast to be able to do anything.\n");
    para->move(the_prisoner);
    seteuid(getuid(TO));
    the_prisoner->add_prop(LIVE_O_ENEMY_CLING, TO);
    add_prop(LIVE_O_ENEMY_CLING, the_prisoner);
    tell_room(E(TO), QCTNAME(TO) + " gags " + QCTNAME(the_prisoner) + ".\n",
	      the_prisoner);
    the_prisoner->catch_msg(QCTNAME(TO) + " gags you.\n");
    tell_room(E(TO), QCTNAME(TO) + " ties " + QCTNAME(the_prisoner) + " up.\n",
	      the_prisoner);
    the_prisoner->catch_msg(QCTNAME(TO) + " ties you up.\n");
    
    set_alarm(10.0,0.0,"go_from_here_to_prison");
    return 1;
}

int
cant_do_it(string str)
{
    int ret;
    if (TP != the_prisoner)
      return 0;
    if (query_verb() == "surrender")
      return perform_the_arrest(str);
    switch(query_verb())
      {
	case "north":
	case "east":
	case "south":
	case "west":
	case "up":
	case "down":
	case "northwest":
	case "northeast":
	case "southwest":
	case "southeast":
	  command("say Oh no, you're not going anywhere! Surrender!");
	  command("say You don't have a chance, just surrender " +
		  "if you want to stay alive!");
	  attack_object(TP);
	  ret = 1;
	  break;
	default:
	  ret = 0;
      }
    return ret;
}

void
go_from_here_to_prison()
{
    string marke;
    object jud;
    if (last_room == E(TO))
      return;
    last_room = E(TO);
    marke = E(TO)->query_to_jail();
    if (!marke)
      return;
    if (marke == "END_TOKEN")
      {
	  command("say We're here! Better behave yourself now.");
	  put_prisoner_into_jail();
	  return;
      }
    if (pointerp(marke))
      {
	  command(marke[0]);
	  command(marke[1]);
      }
    else
      {
	  command(marke);
      }
    drag_the_prisoner_along();
    set_alarm(5.0,0.0,"go_from_here_to_prison");
}

void
put_prisoner_into_jail()
{
    object key;
    (key = clone_object(OBJ + "jail_key"))->move(TO);
    command("unlock bars with key");
    command("open bars");
    command("n");
    drag_the_prisoner_along();
    command("say Enjoy your stay!");
    get_prisoner_ready_for_jail();
    command("s");
    command("close bars");
    command("lock bars with key");
    release_prisoner_from_ties();
    key->remove_object();
    set_alarm(4.0,0.0,"return_to_watch_on_bridge");
}

void
get_prisoner_ready_for_jail()
{  
    tell_room(E(TO), QCTNAME(TO) + " unties " + QTNAME(the_prisoner) + ".\n",
	      the_prisoner);
    the_prisoner->catch_msg(QCTNAME(TO) + " unties you, but you still are " +
			    "too stiff to do anything.\n");
    para->set_fail_message("You are still too stiff to do anything.\n");
    
    write_file(TDIR + "log/jaillog", extract(ctime(time()), 4, 15)
	       + " " + capitalize(the_prisoner->query_real_name()) + "\n");
}

void
release_prisoner_from_ties()
{
    /*remove prestige if it is a knight */
    the_prisoner->change_prestige(-4);

    para->remove_object();
    the_prisoner->catch_msg("You feel like you can move again.\n");
}

void
drag_the_prisoner_along()
{
    tell_room(E(the_prisoner), QCTNAME(TO) + " drags " + 
	      QTNAME(the_prisoner) + " out.\n", the_prisoner);
    the_prisoner->catch_msg(QCTNAME(TO) + " drags you along.\n");
    the_prisoner->move(E(TO));
    tell_room(E(the_prisoner), QCTNAME(TO) + " drags " +
	      QTNAME(the_prisoner) + " in.\n", the_prisoner);
}
