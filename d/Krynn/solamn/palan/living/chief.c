/* created by Aridor 06/19/93 */


#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include <language.h>
#include "../local.h"


inherit M_FILE


/*prototypes*/
string my_answer();
void arm_me();

int on_a_mission = 0;

object last_room;
object the_prisoner;
object para; /*paralyser of the_prisoner*/

EMOTE_HOOK

void
create_krynn_monster()
{
    set_name("hagen");
    set_race_name("human");
    set_adj("strong");
    add_name("chief");
    set_title("the Chief Officer of Palanthas the beautiful");
    
    set_long("This is a very muscular looking man. You have the impression "
	     + "that this person has everything under his control. He should, "
	     + "actually, since he is the chief of local guards.\n");
    
    set_stats(({100, 64, 105, 60, 61, 90}));
    set_hp(60000);
    set_skill(SS_DEFENCE, random(10) + 70);
    set_all_attack_unarmed(85, 50);
    set_all_hitloc_unarmed(75);
    
    set_chat_time(30);
    add_chat("If you have a form you can show me and I'll tell you what "
	     + "to do.");
    add_chat("Ahhh, boy do I feel good today!");
    add_chat("I can't wait till someone nasty comes along.");
    
    add_ask("form",VBFC_ME("answer_show_form"));
    add_ask("sign form",VBFC_ME("sign_form_with_form"));
    add_ask("to sign form",VBFC_ME("sign_form_with_form"));
    add_ask(({"jail","free","free from jail","free prisoner","prisoner",
		"release","release prisoner","release from jail",
		"release prisoner from jail"}),
	    VBFC_ME("free_prisoner"));
    set_default_answer(VBFC_ME("my_answer"));
    set_introduce(1);
    add_emote_hook("bow",1.0,&command("bow"));

    set_alarm(2.0,0.0,"arm_me");
}

void
arm_me()
{
    seteuid(getuid(TO));
    clone_object(OBJ + "iletter")->move(TO);
    clone_object(OBJ + "boots")->move(TO);
    clone_object(OBJ + "uniform")->move(TO);
    command("wear all");
}


perform_the_release(int how)
/*how = 0 means someone paid the fee
 *how = 1 means prisoners are pardoned */
{
    int i;
    object key, *livings;
    (key = clone_object(OBJ + "jail_key"))->move(TO);
    command("unlock bars with key");
    command("open bars");
    command("n");
    if (how)
      command("say You are released, the Lord of Palanthas has pardoned you.");
    else
      command("say You are released, the ransom fee has been paid.");
    livings = all_inventory(environment(TO));
    command("s");
    for (i = 0; i < sizeof(livings); i++)
      livings[i]->command("south");
    command("close bars");
    command("lock bars with key");
    if (!how)
      if (sizeof(livings) < 1)
	TP->remove_prop("_has_payed_ransom");
      else
	{
	    command("say Hmm, strange, no one was in jail.");
	    command("shrug");
	}
    key->remove_object();
}


free_prisoner()
{
    object the_form = present("form", TP);
    string *slots, dummy;
    
    if (!the_form)
      {
	  command("say I need a form filled in asking for the release of " +
		  "the prisoner.");
	  command("say The form must be signed by Chivo with proof of the " +
		  "payment of the ransom fee and approved by the judge!");
	  command("say Then I can release the prisoner.");
      }
    else
      {
	  slots = the_form->query_form_slots();
	  if (slots[1] == "Chivo (Tax Collector)" &&
	      slots[0] == "Ransom fee paid."
	      && slots[2] == "Jodico (Judge)" &&
	      (sscanf(the_form->query_form_purpose(),"%srelease%s",dummy,dummy) == 2))
	    {
		command("say Ok, the form you have is valid.");
		perform_the_release(0);
		the_form->remove_object();
	    }
	  else
	    {
		command("say I'm sorry, but the form you are carrying is " +
			"not valid to free the prisoner.");
		command("say I need the signature of Chivo with the proof " +
			"of payment and the signature of the judge.");
	    }
      }
    return "";
}

answer_show_form()
{
    command("say Show me the form and i'll tell you what to do.");
    return "";
}


init_living()
{
    add_action("sign_form","sign");
    add_action("examine_form","show");
}

string
my_answer()
{
    set_alarm(1.0,0.0,"command","shrug");
    set_alarm(3.0,0.0,"command","say I cannot help you with that.");
    return "";
}



int
sign_form(string str)
{
    command("say I don't have the privilege to sign forms.");
    command("say Ask the supervisor for that, I know he has to signs " +
	    "forms all the time.");
    return 1;
}


string
sign_form_with_form()
{
    sign_form("form");
    return "";
}


int
examine_form(string str)
{
    sign_form(str);
    return 1;
}


perform_the_arrest(string str)
{
    NF("What?\n");
    if (TP != the_prisoner)
      return 0;
    TP->command("say I surrender!");
    TP->stop_fight(TP->query_enemy(-1));
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
    
    set_alarm(10.0,0.0,"go_from_here_to_judge");
    return 1;
}

fight_till_surrendered(object who)
{
    object *ene;
    if (E(who) != E(TO))
      return;
    /*add_action("perform_the_arrest","surrender"); handled below...*/
    add_action("cant_do_it","",1);
    ene = who->query_enemy(-1);
    who->stop_fight(ene);
    ene->stop_fight(who);
    attack_object(who);
    command("emote charges in to protect the citizen.\n");
    who->attack_object(TO);
}

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
	  command("say You don't have a chance against me, just surrender " +
		  "if you want to stay alive!");
	  attack_object(TP);
	  ret = 1;
	  break;
	default:
	  ret = 0;
      }
    return ret;
}

arrest_prisoner(mixed who, object where)
{
    if (on_a_mission)
      return;/*lucky 'who'!!!!!*/
    if (stringp(who))
      the_prisoner = find_living(who);
    else if (objectp(who))
      the_prisoner = who;
    else
      return;
    if (!where->query_to_jail())
      return; /*outside the limits...*/
    if (E(the_prisoner) != where)
      return;
    on_a_mission = 1;
    move_living("dashing out the door", where); 
    fight_till_surrendered(who);
}


go_from_here_to_judge()
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
	  if (jud = present("jodico", E(TO)))
	    jud->sentence_prisoner(TO, the_prisoner);
	  else
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
    set_alarm(5.0,0.0,"go_from_here_to_judge");
}


put_prisoner_into_jail()
{
    if (the_prisoner->query_guild_member("Solamnian Knights"))
      ("/d/Krynn/solamn/vkeep/mnstrs/gunthar")->add_bad_guy(LANG_ADDART(the_prisoner->query_nonmet_name()),
							    "the Lord of Palanthas",
							    "attacked a citizen there");
    set_alarm(10.0,0.0,"start_going");
}

start_going()
{
    object key;
    command("west");
    drag_the_prisoner_along();
    command("north");
    drag_the_prisoner_along();
    command("north");
    drag_the_prisoner_along();
    command("north");
    drag_the_prisoner_along();
    command("west");
    drag_the_prisoner_along();
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
    on_a_mission = 0;
    set_alarm(itof(600 + random(600)),0.0,"perform_the_release", 1);
}

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


release_prisoner_from_ties()
{
    /*remove prestige if it is a knight */
    the_prisoner->change_prestige(-4);

    para->remove_object();
    the_prisoner->catch_msg("You feel like you can move again.\n");
}


release_prisoner()
{
    release_prisoner_from_ties();
    command("west");
    command("north");
    command("north");
    command("north");
    command("west");
    on_a_mission = 0;
}


drag_the_prisoner_along()
{
    tell_room(E(the_prisoner), QCTNAME(TO) + " drags " + 
	      QTNAME(the_prisoner) + " out.\n", the_prisoner);
    the_prisoner->catch_msg(QCTNAME(TO) + " drags you along.\n");
    the_prisoner->move(E(TO));
    tell_room(E(the_prisoner), QCTNAME(TO) + " drags " +
	      QTNAME(the_prisoner) + " in.\n", the_prisoner);
}

void
do_die(object killer)
{
    para->remove_object();
    ::do_die(killer);
}
