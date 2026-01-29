/*
 *    A hobbit that rewards players for solving a small quest
 *    Cloned by /d/Shire/common/hobbiton/er2
 */

inherit "/std/monster";

#include <macros.h>
#include <stdproperties.h>
#include "/d/Shire/sys/defs.h"
#include "/sys/ss_types.h"
#include "/d/Shire/common/monster/tobacco.h"

//   Prototypes
void arm_me();
void return_introduce(string who);
void reset_intr();
void return_letter(mixed ob);

int intro;

/*
 * Function name:create_monster
 * Description  :The standard create_monster
 */
create_monster() {

    if (!IS_CLONE) return;
    set_name("tolarin");
    add_name("shirriffe");
    set_living_name("_tolarin_");
    set_adj("sad");
    set_race_name("hobbit");
    set_long("This is a member of the local police force. He looks like "
      + "he is in desperate need of help. Maybe you could 'ask' him "
      + "what he needs.\n");

    set_short("shirriffe");
    default_config_npc(30);      
    set_hp(50000);

    set_skill(SS_WEP_CLUB, 35);
    set_skill(SS_DEFENCE, 35);

    add_prop(NPC_M_NO_ACCEPT_GIVE, 0);
    add_act("sigh");
    set_act_time(15);
    add_ask(({"help", "quest", "for help", "for quest", "about quest"}), VBFC_ME("try_to_tell"));
    set_default_answer("The hobbit says: I don't know what you mean.\n");


    intro = 1;

    set_alarm(0.1,0.0,&arm_me());
    clone_tobacco();

}

arm_me() {

    object staff;

    staff = clone_object(COMMON_DIR + "hobbiton/wep/staff");
    staff->move(this_object());
    command("wield staff");

}

void
add_introduce(string who)
{
    set_alarm(1.0,0.0, &return_introduce(who));
}

return_introduce(string who) {
    if (random(4) && present(who, environment())) {
	command("introduce myself to " + who);
    }
    else {
	command("introduce myself");
    }
}

/*
 * Function name:react_introduce
 * Description  :Introduce myself when someone else does it.
 */
react_introduce(who, tmp) {
    if (!intro) return 0;
    intro = 0;
    set_alarm(30.0,0.0,&reset_intr());
    /*  set_alarm(itof(random(3) + 2),0.0,&return_introduce(who)); */
    return 1;
}


/*
 * Function name:tell
 * Description  :tells the story about the invading orcs, asks for help.
 */
tell(int t) {

    switch(t) {
    case 1:
	command("say I was sent by the captain in Bree to " +
	  "investigate why\nthere are so many orcs in this area.");
	command("say They shouldn't be here, west of the mountains.");
	command("say I would very much appreciate if you could help me out\n"
	  + "with this.");
	command("say If you could bring me some news about why the orcs\nare here"
	  + " I might be able to help you in return.");

	break;
    case 2:
	command("smile");
	write("The shirriffe studies the letter.\n");
	command("say Hmmm, this seems to be in orc.");
	command("say I can't make head nor tails of it.");
	command("say I do seem to recall however, an old man named Raston.");
	command("say He might know what it says. I heard he knew all sorts of" +
	  "\nlanguages.");
	command("say Here, take the letter again.");
	command("say Oh! Please don't ask me where Raston lives, I don't know.");
	break;
    case 3:
	command("frown");
	command("say Why are you showing me this letter again?");
	break;
    case 4:
	command("Well we know about the orcs now, don't we.");
	break;
    case 5:
	command("say Find Raston and show him the letter.");
	break;
    case 6:
	command("frown");
	write("The shirriffe studies the letter.\n");
	command("say This is very bad news indeed.");
	command("say I will have to tell the captain immediately.");
	command("say Thanks for your help");
	command("say Without it we might have found out too late.");
	command("wave");
	move_living("east", "/d/Shire/workroom");
	remove_object();
	break;
    case 7:
	command("say This is old news.");
	break;
    case 8:
	command("say What's this?");
	break;
    case 9:
	command("say Thanks, but you have already helped me.");
	break;
    case 10:
   command("say You didn't get this letter yourself.");
   command("say How do I know that this letter is authentic.");
  command("say Come back when you retrieve the real letter from the Orc.");
    }
}

/*
 * Function name:try_to_tell
 * Description  :Checks to see if the player has already solved the quest.
 *               Then tells the player what to do.
 */
try_to_tell() {

    if (!CHECK_QUEST(TP, "letter1"))
    {
	tell(1);
	return "";
    }

    if (!CHECK_QUEST(TP, "letter2"))
    {
	tell(5); /* first part solved */
	return "";
    }

    tell(9);   /* already solved quest */

    return "";

}


/*
* Function name:return_letter
* Description  :return letter
*/
return_letter(mixed ob) {

    if(!ob[1])
	return;

    command("give " + ob[0]->query_name() + " to " + ob[1]->query_real_name());

}  

/*
* Function name:enter_inv
* Description  :I use this to test if I get something
*/
enter_inv(object ob, object from) {
    int rew;
    ::enter_inv(ob,from);

    if(ob->are_u_quest_letter() == 222) {
	rew = REWARD_QUEST(from, "letter2");
	if(!rew) {
	    set_alarm(3.0,0.0,&tell(7));
	    ob->self_destruct();
	    return;
	}
	from->catch_msg("You feel a little more experienced.\n");
	set_alarm(3.0,0.0,&tell(6));
	ob->self_destruct();
	return;
    }

    if(ob->are_u_quest_letter() == 111) {
      if(from->query_prop(KILLED_LETTER_ORC))
	      rew = REWARD_QUEST(from, "letter1");
      else {
         set_alarm(3.0,0.0,&tell(10));
       ob->self_destruct();
                  return;
               }
	if(!rew) {
	    set_alarm(2.0,0.0,&return_letter(({ ob , from })));
	    set_alarm(3.0,0.0,&tell(3));
	    return;
	}
	from->catch_msg("You feel a bit more experienced.\n");
	set_alarm(3.0,0.0,&tell(2));
	set_alarm(2.0,0.0,&return_letter(({ ob , from })));
	return;
    }

    set_alarm(3.0,0.0,&tell(8));
    set_alarm(2.0,0.0,&return_letter(({ ob , from })));
}

/*
* Function name:query_knight_prestige
* Description  :returns a value for the knights.
*/
query_knight_prestige() { return (-3); }

reset_intr() {

    intro = 1;

}
