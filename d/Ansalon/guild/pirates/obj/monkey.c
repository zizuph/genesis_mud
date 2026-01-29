/*
 * File Name        : monkey.c
 * By               : Elmore.
 * Inspiration from : A parrot by Ashlar.
 * Date             : Nov. 2000.
 *
 */

/* Upgraded June 10th 2006 by Navarre
 * Added possibility to name the monkey.
 * Increased the number of sends before it
 * runs off. Since its very expensive.
 * Added support for autoreturn.
 */

#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/taman_busuk/neraka/local.h"

inherit "/std/creature";
inherit "/std/combat/unarmed";
inherit "/std/act/attack";
inherit "/lib/keep";
inherit "/std/act/action";

#include <ss_types.h>
#include <stdproperties.h>
#include <macros.h>
#include <composite.h>
#include <wa_types.h>
#include <files.h>
#include <cmdparse.h>

#define MONKEYSUBLOC    "_ansalon_monkey_subloc"
#define MONKEYNAME      "_ansalon_monkey"

/* The temporary room in the air when the monkey is flying. */
#define IN_TRANSIT_ROOM     "/d/Krynn/solamn/vin/room/air_room"

/* The home of the monkey. */
#define MONKEY_HOME     "/d/Krynn/solamn/vin/room/pigeon_store"

#define SIGN_MSG "The small sign reads: 'collect', 'send <player>', "+"'send reply', 'name monkey <name>' and 'mreturn' written on it.\n"

/* The message. */
#define MESSAGE_OBJ     "/d/Krynn/solamn/vin/obj/message"

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(20) + 30

/* The number of times the monkey will carry a message. */
#define TIMES 40

#define A_TEETH 0
#define A_CLAWS 1
#define H_HEAD 0
#define H_BODY 1

string *colours = ({ "brown", "black", "grey",
  "tiny", "tiny" });
string *lines = ({ });

int false_drop;
int present;
int areturn = 0;
/* Prototypes */
int send_mail();
int return_to(object dest);
int fly_to_someone(object dest);
void return_home();
string named();
string gMessage, gWho, gSender;
int gUsage,monkey_busy,times,fly_alrm;
object owner;
string owner_name;
object first_owner;
string first_owner_name;
string monkey_name;
int mreturn_alarm = 0;

void
create_creature()
{
    string c;	

    if (!IS_CLONE)
	return;

    set_name("monkey");
    add_name(MONKEYNAME);
    add_name("animal");

    set_race_name("monkey");
    c = colours[random(sizeof(colours))];

    set_adj(explode(c," "));

    set_long("The monkey is a " + c + " monkey with a tiny hat on its head. It has a small "+
             "sign around its neck with some words on it.\n@@named@@");

    set_gender(2);
    set_appearance_offset(-25-random(20));

    default_config_mobile(4);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_AWARENESS,40);

    gUsage = 0;

    add_item(({"sign", "small sign"}), SIGN_MSG);
    add_prop(LIVE_I_NEVERKNOWN,1);
    change_prop(OBJ_M_NO_GET,"@@take_monkey@@");
    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_HEIGHT, 30);
    add_prop(CONT_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 1000);
    add_prop(OBJ_M_NO_SELL, 1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not want that.\n");

    set_attack_unarmed(A_TEETH,5,10,W_SLASH,40,"sharp teeth");
    set_attack_unarmed(A_CLAWS,10,7,W_SLASH,60,"claws");
    set_hitloc_unarmed(H_HEAD,7,20,"head");
    set_hitloc_unarmed(H_BODY,10,55,"body");

    set_act_time(3);
    add_act("emote restlessly shifts back and forth, looking at you suspiciously.");
    add_act("emote suddenly jumps up and turns around nervously.");
    add_act("emote scratches it's back and find a small flea, which it eats.");
    add_act("emote fiddles with its tiny hat.");
    add_act("emote starts to doze off, and just as it is about to fall off, it "+
            "opens its eyes frightenly and graps hold on the shoulders of his "+
            "owner.");
    add_act("emote looks to all sides, obviously bored, it lets out a small sigh.");
    add_act("emote gets a greedy look in its eye, as it looks at your equipment.");
    add_act("emote jumps up and down eagerly, while pointing to the east.");
    add_act("emote looks eagerly at the ground, probably searching for any valuables to steal.");
    add_act("emote starts to pick his nose, while staring up at the sky.");
}

string named()
{
  if(owner_name)
  {
    if(monkey_name)
    {
      return "This is "+owner_name+"'s monkey, "+monkey_name+".\n";
    }
    return "This is "+owner_name+"'s monkey.\n";
  }
  return "";
}

void
attacked_by(object enemy)
{
    if ((enemy->id("wolf")) && (query_panic() < 1000))
	add_panic(1000);
    ::attacked_by(enemy);
}

mixed
take_monkey() 
{
    if (objectp(TP) && interactive(TP) && present(MONKEYNAME,TP))
    {
	return "Two of those rarely get along, so you decide not to " +
	"take another.\n";
    }
    else
	return 0;
}

int
is_monkey(object ob)
{
    if (ob->id(MONKEYNAME))
	return 1;
    else
	return 0;
}

void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if(!owner_name)
    {
      if(interactive(env))
      {
        owner_name = env->query_name();
        if(!first_owner)
        {
          first_owner = env;
          first_owner_name = env->query_name();
        }
      }
    }
    if(first_owner && !present(this_object(), environment(first_owner)) &&
       !present(this_object(), first_owner))
    {
      if(areturn && !mreturn_alarm)
      {
        mreturn_alarm = set_alarm(900.0, 0.0, &return_to(first_owner));
      }
    }

    if(env->query_prop(LIVE_I_IS))
    {
	object *t;
	t = filter(deep_inventory(env),is_monkey) - ({ TO });

	if (sizeof(t))
	{
	    env->catch_msg("Two of those rarely get along, so you put the " +
	      short() + " down on the ground.\n");
	    tell_room(E(env), QCTNAME(env) + " warily eyes " + HIS(env) +
	      " second monkey, and after a brief pause " + HE(env) +
	      " puts the " + short() + " down on the ground.\n", env);
	    set_alarm(0.0,0.0,&move(E(env)));
	    false_drop = 1;
	}
	else
	{
	    env->catch_msg("The " + short() + " climbs up on your " +
	      "shoulder.\n");
	    env->add_subloc(MONKEYSUBLOC,TO);
	    set_alarm(1.0,0.0,&set_no_show_composite(1));
            present = 1;
	}
    }

}

void leave_env(object from, object to)
{
    ::leave_env(from,to);
    if(!false_drop && from->query_prop(LIVE_I_IS))
    {
	from->remove_subloc(MONKEYSUBLOC);
	set_no_show_composite(0);
	from->catch_msg("You release the cord around the monkeys neck and "+
                        "drop it on the ground.\n");
        present = 0;
    }
    false_drop = 0;
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc != MONKEYSUBLOC)
        return ::show_subloc(subloc, me, for_obj);
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "You have a tiny monkey perched upon your shoulder.\n";

    if (for_obj == me)
	return "You have a " + short() + " perched upon your shoulder.\n";
    else
	return C(PRONOUN(me)) + " has a " + short() + " perched upon " +
	POSSESSIVE(me) + " shoulder.\n";
}


int
collect()
{   
    string name;

    if (present == 1)
    {
        TP->catch_msg("You must drop the monkey first, if you want it to collect the coins.\n");
        return 1;
    }

    name = TP->query_real_name();
    TO->tell_watcher("The small monkey runs across the ground, searching for shiny coins.\n");
    command("get coins");
    command("get coins from corpse");
    command("get coins from second corpse");
    command("get coins from third corpse");
    command("get coins from fourth corpse");
    command("give coins to "+name+"");
    TO->move(TP,1);
    return 1;
}


int
do_send(string who)
{
    string known, intro, remem;
    object target, tp;
    
    if (!who || who == "")
      return 0;
    tp = this_player();
    if (tp != E(TO))
      return 0;
    if (gUsage >= TIMES)
    {
	  write("The monkey refuses to deliver another message.\n");
	  return 1;
    }

    if (who == "reply")
    {
      /* Has a message been written before? */
      if (!gUsage)
      {
        write("You are the first sender of a message. You cannot " +
              "reply.\n");
	return 1;
      }
      who = gSender;
    }
    /* If a player knows the name of another player, let him send the monkey.*/
    gWho = who;
    gSender = lower_case(tp->query_name());
    target = find_player(gWho);
    
    /* It is useless to write a message to someone who isn't in the game. */
    if (!target)
      {
	  write("There is no such player logged in!\n");
	  return 1;
      }
    monkey_busy = 1;
    write("Enter your message.\n" +
	  "On any line you can give ** to end, or ~q to abort the message.\n");
    gMessage = "";
    write("-->");
    input_to("write_more");
    return 1;
}

int
write_more(string str)
{
    if (str == "**")
      {
	  send_mail();
	  return 1;
      }
    if (str == "~q")
      {
	  write("Message aborted.\n");
	  monkey_busy = 0;
	  return 1;
      }
    gMessage += (str + "\n");
    write("-->");
    input_to("write_more");
    return 1;
}

int
send_mail()
{
    if (gMessage == "")
    {
      write("Message aborted.\n");
      return 0;
    }
    write("You give the message to the "+short()+".\n");
    say(QCTNAME(this_player()) + " gives a message to "
	+ this_player()->query_possessive() + " monkey.\n");
    /* turn autoreturn of monkey off*/
    if (fly_alrm)
      remove_alarm(fly_alrm);
    fly_alrm = 0;
    tell_room(E(TO), "The "+short()+ " runs off with the message in his hands.\n");
    /* Move the object to a temporary room */
    move(IN_TRANSIT_ROOM);
    set_alarm(itof(SLOWLY),0.0,"deliver");
    return 1;
}

int
do_resend()
{
    object target;
    
    if (!gSender || !gWho || this_player() != find_player(gSender))
      {
	  notify_fail("You can't resend if you haven't sent first!\n");
	  return 0;
      }
    
    if (target = find_player(gWho))
      {
	  write("You convince the monkey to make yet another try.\n");
	  move(IN_TRANSIT_ROOM);
	  set_alarm(itof(SLOWLY),0.0,"deliver");
	  return 1;
      }
    
    notify_fail("The monkey doesn't want to make another try.\n");
    return 0;
}

int
deliver()
{
    object target, message;
    /* Does our initial target still exist? */
    target = find_player(gWho);
    if (!target)
    {
      /* Does our sender still exist? */
      target = find_player(gSender);
      if (!target)
      {
        if (owner) 
        { 
	  return_to(owner);
          return 1;
        }
        remove_object();
   	return 1;
      }
    }
    
    /* Go to the target */
    move(target);
    monkey_busy = 0;
    if (target == find_player(gSender))
      tell_object(target, "Your "+short()+ " returns, unable to find "
		  + C(gWho) + ". It jumps back on your shoulder and " +
		  "you retrieve your message.\n");
    else
      tell_object(target, "A "+short()+ " runs towards you and jumps back on your "+
                  "shoulder. He gives you a message " +
		  "from " + C(gSender) + ".\n");

    /*return to owner if i'm not needed.*/
    if (owner && target != owner)
      {
	  tell_object(target, "If do not use this monkey it will return to " +
		      "it's owner again.\n");
	  fly_alrm = set_alarm(20.0,0.0,"attempt_fly_to_someone",owner);
      }
    
    tell_room(E(target),
	      "A monkey jumps up on " + QTNAME(target) + "'s shoulder and gives "
	      + target->query_objective() + " a message.\n",target);
    
    message = clone_object(MESSAGE_OBJ);
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target);
    if(!random(4))
      gUsage++;
    if (gUsage >= TIMES)
      set_alarm(10.0,0.0,"return_home");
}

int
do_return(string str)
{
    if (!str) {
	write("Return what?\n");
	return 1;
    }
    if (str == "monkey" || str == "tiny monkey")
      {
	  write("You release the monkey, so that it can run " +
		"back home.\n");
	  say(QCTNAME(this_player()) + " releases the monkey, and it runs away.\n",
	      this_player());
	  /* turn autoreturn of monkey off*/
	  if (fly_alrm)
	    remove_alarm(fly_alrm);
	  fly_alrm = 0;

	  if (this_player() != owner) 
	    fly_to_someone(owner);
	  else 
	    return_home();
	  return 1;
      }
    return 0;
}

int
query_busy()
{
    return monkey_busy;
}

void
return_home()
{
    object room;
    if (living(room = E(TO)))
      room = E(room);
    tell_room(room,
	      "The "+short()+ " runs away from you.\n");
    remove_object();
}

int
return_to(object dest)
{
    if (!dest) 
    {
      return_home();
      return 1;
    }
    monkey_busy = 0;
    set_alarm(4.0,0.0,"fly_to_someone",dest);
    if (living(E(TO)))
    {
      tell_object(E(TO), "You hear a whistle from somewhere in the distance.\n");
    }
    else tell_room(E(TO),
       "You hear a whistle from somewhere in the distance.\n");
    return 1;
}

int
attempt_fly_to_someone(object dest)
{
    if (query_busy())
    {
      fly_alrm = set_alarm(60.0,0.0,"attempt_fly_to_someone",dest);
      return 0;
    }
    return fly_to_someone(dest);
}

int
fly_to_someone(object dest)
{
    if (!dest) 
      tell_object(owner,"Bug - no dest.\n");
    if (living(E(TO)))
    {
        tell_object(E(TO), "The "+short()+ " jumps from your shoulder and "
        + "runs away.\n");
        tell_room(E(E(TO)), "The "+short()+ " jumps from " + QTNAME(E(TO))
        + "'s shoulder and runs away.\n", E(TO), E(TO));
    }
    else 
      tell_room(E(TO),
		"The "+short()+ " runs away!\n");
    if(!dest)
      {
	  remove_object();
	  return 1;
      }
    if(dest == first_owner && mreturn_alarm)
    {
      remove_alarm(mreturn_alarm); 
    }
    this_object()->move(dest);
    tell_object(dest,"A "+short()+ " jumps up on your shoulder.\n");
    tell_room(E(dest), "A "+short()+ " jumps up on the " +
	      "shoulder of " + QTNAME(dest) + ".\n", dest);
    return 1;
}


int
set_owner(object player)
{
    if (!player) return 0;
    owner = player;
    return 1;
}

int
start_place()
{
    this_object()->move(MONKEY_HOME);
    tell_room(E(TO),
	      "A "+short()+ " arrives and sits on the floor.\n");
    set_alarm(15.0,0.0,"return_to",owner);
    return 1;
}

int
name_monkey(string args)
{
  string* arg_array = ({});

  if(!args)
  {
    notify_fail("Name what?\n");
    return 0;
  }

  if(this_player()->query_name()!=first_owner_name)
  {
    write("This is not your monkey, giving it a name won't do you any good. It would most likely not obey you anyway.\n");
    return 1;
  }

 arg_array = explode(args, " ");


 switch(sizeof(arg_array))
 {
   case 2:
         if(arg_array[0]=="monkey")
         {
           monkey_name = arg_array[1];
           add_name(arg_array[1]);
           this_player()->catch_tell("You name your monkey "+arg_array[1]+".\n");
           return 1;
         }
   case 3:
         if(arg_array[0]=="the" && arg_array[1]=="monkey")
         {
           monkey_name = arg_array[2];
           add_name(arg_array[2]);
           this_player()->catch_tell("You name your monkey "+arg_array[2]+".\n");
           return 1;
         }

   case 4:
         if(arg_array[0]=="the" && arg_array[1]==query_adj() && arg_array[2]=="monkey")
         {
           monkey_name = arg_array[3];
           add_name(arg_array[3]);
           this_player()->catch_tell("You name your monkey "+arg_array[3]+".\n");
           return 1; 
         }
   default: this_player()->catch_tell("You can 'name' the monkey <name>.\n");
  }
  return 1; 
}
 
int read_sign(string args)
{
  if(args=="sign" || args=="small sign")
  {
    this_player()->catch_tell(SIGN_MSG); 
    return 1;
  }
  return 0;
}
 
int autoreturn(string args)
{

  if(strlen(args) !=0)
  {
    notify_fail("Use <mreturn> to enable or disable auto return of the monkey.\n");
    return 0;
  }
  if(this_player()->query_name()!=first_owner_name)
  {
    write("You try to give the monkey an order, but it seems he wants to stick with his owner's instructions.\n");
    return 1;
  }

  if(areturn == 0)  
  {
    write("You order your monkey to return after his next delivery.\n");
    areturn = 1;
    return 1;
  }
  write("You order your monkey to stay with the recipient of his next delivery.\n");
  areturn = 0;
  return 1;
}

void
init_living()
{
    add_action("collect", "collect");
    add_action("do_send","send",0);
    add_action("do_return","return",0);
    add_action("do_resend","resend",0);
    add_action(name_monkey, "name");
    add_action(read_sign, "read");
    add_action(autoreturn, "mreturn");
}
