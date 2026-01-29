/*
 *  Carrier dove.
 *  This one can bring a message from one player to another. This will
 *  (ofcourse) take a while. Maybe it's a compensation for the loss of
 *  the 'tell' command.                                  Tricky, dec 1991
 *
 *  Slight modifications by Elessar, March 1992.
 *  Nick was here, May 1992. ** Keep on smiling **
 *  added 'return' from /d/Genesis/obj/pigeon.c, Olorin, July 1993
 *
 *  bugfixes by Aridor, May 1994
 */

inherit "/std/creature";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "../local.h"

/* The temporary room in the air when the pigeon is flying. */
#define AIR_ROOM    VROOM + "air_room"

/* The home of the dove. */
#define PIGEON_HOME VROOM + "pigeon_store"

/* The message. */
#define MESSAGE_OBJ VOBJ + "message"

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(20) + 30

/* The number of times the dove will carry a message. */
#define TIMES 10

/* Prototypes */
int set_times_to_fly(int i);
int send_mail();
int return_to(object dest);
int fly_to_someone(object dest);
void return_home();
int test_dove_killer(object pl);


string gMessage, gWho, gSender;
int gUsage,dove_busy,times,fly_alrm;
object owner;

void
create_creature()
{
    set_name("dove");
    set_pname("doves");
    set_race_name("dove");
    set_adj(({"white","pigeon"}));
    set_short("white dove");
    set_pshort("white doves");
    set_long("@@long_func");
    gUsage = 0;
    add_prop(OBJ_I_WEIGHT,350);
    add_prop(CONT_I_WEIGHT,350);
    add_prop(OBJ_I_VOLUME,350);
    add_prop(CONT_I_VOLUME,350);
    add_prop(OBJ_I_NO_GET,0);
    add_prop(OBJ_I_NO_DROP,0);
    add_prop(LIVE_I_NON_REMEMBER,1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not seem to be able to carry " +
         "anything but small messages.\n");

    set_times_to_fly(TIMES);
    set_attack_unarmed(1, 5, 5, W_IMPALE, 100, "beak");
    set_hitloc_unarmed(1, ({ 5, 7, 3 }), 100, "body");
}

void
init_living()
{
    add_action("do_send","send",0);
    add_action("do_return","return",0);
    add_action("do_resend","resend",0);
}

string
long_func()
{
    if (owner && owner == this_player())
      return "This is your personal dove. You can send messages to "+
    "other players by typing 'send <player>'" +
#if TIMES > 1
    " or 'send reply'" +
#endif
    ". If the dove fails to deliver the message you can tell it to " +
    "try again with the 'resend' command. " +
      /* "If you want the dove back, " +
       * "you can 'whistle for dove', and it will return, if it's
       * still alive. " +
       */
    "If you don't want the dove anymore, you can do 'return dove'.\n";
    if (owner && owner != this_player())
      return "This is "+owner->query_cap_name()+"'s dove. It is " +
    "however a friendly bird, and you might be able to send messages to " +
    "others by 'send <player>' or 'send reply'. If the dove fails to " +
    "deliver the message you can tell it to try again with the 'resend' " +
    "command. You may also 'return dove'. "+
    "That will make the dove fly back to "+owner->query_cap_name()+".\n";
    return "This is a white dove, which you can use to send " +
      "messages to other players with 'send <player>'.\n";
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
    if (gUsage >= times)
      {
      write("The dove refuses to deliver another message.\n");
      return 1;
      }
    if (E(tp)->query_prop(ROOM_I_INSIDE))
      {
      write("You can't send out the dove when you're not out in " +
        "open air.\n");
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
    /* If a player knows the name of another player, let him send the dove.*/
    gWho = who;
    gSender = lower_case(tp->query_name());
    target = find_player(gWho);

    /* It is useless to write a message to someone who isn't in the game. */
    if ((!target) || (target->query_wiz_level()) )
      {
      write("There is no such player logged in!\n");
      return 1;
      }
    dove_busy = 1;
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
      dove_busy = 0;
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
    write("You give the message to the dove.\n");
    say(QCTNAME(this_player()) + " gives a message to "
    + this_player()->query_possessive() + " dove.\n");
    /* turn autoreturn of dove off*/
    if (fly_alrm)
      remove_alarm(fly_alrm);
    fly_alrm = 0;
    tell_room(E(TO), "The white dove flaps its wings and " +
          "flies up to the sky.\n");
    /* Move the object to a temporary room */
    move(AIR_ROOM);
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
      write("You convince the dove to make yet another try.\n");
      move(AIR_ROOM);
      set_alarm(itof(SLOWLY),0.0,"deliver");
      return 1;
      }

    notify_fail("The dove doesn't want to make another try.\n");
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
    else if (E(target)->query_prop(ROOM_I_INSIDE))
      {
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
    dove_busy = 0;
    if (target == find_player(gSender))
      tell_object(target, "Your white dove returns, unable to find "
          + C(gWho) + ". It lands on your shoulder and " +
          "you retrieve your message.\n");
    else
      tell_object(target, "A white dove descends from the " +
          "sky, lands on your shoulder and gives you a message " +
          "from " + C(gSender) + ".\n");
    /*return to owner if i'm not needed.*/
    if (owner && target != owner)
      {
      tell_object(target, "If do not use this dove it will return to " +
              "it's owner again.\n");
      fly_alrm = set_alarm(60.0,0.0,"attempt_fly_to_someone",owner);
      }

    tell_room(E(target),
          "A dove lands on " + QTNAME(target) + "'s shoulder and gives "
          + target->query_objective() + " a message.\n",target);

    message = clone_object(MESSAGE_OBJ);
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target);
    gUsage++;
    if (gUsage >= times)
      set_alarm(10.0,0.0,"return_home");
}

int
do_return(string str)
{
    if (!str) {
    write("Return what?\n");
    return 1;
    }
    if (str == "dove" || str == "white dove" || str == "dove")
      {
      write("You send the dove up in the air again, to fly " +
        "back home.\n");
      say(QCTNAME(this_player()) + " sends the dove away.\n",
          this_player());
      /* turn autoreturn of dove off*/
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
    return dove_busy;
}

void
return_home()
{
    object room;
    if (living(room = E(TO)))
      room = E(room);
    tell_room(room,
          "The white dove flaps its wings and flies away.\n");
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
    dove_busy = 0;
    set_alarm(4.0,0.0,"fly_to_someone",dest);
    if (living(E(TO)))
      {
      tell_object(E(TO),
              "You hear a whistle from somewhere in the distance.\n");
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
      tell_room(E(E(TO)), "The white dove flaps its wings and flies " +
            "up in the sky!\n");
    else
      tell_room(E(TO),
        "The white dove flaps its wings and flies up in the sky!\n");
    if(!dest)
      {
      remove_object();
      return 1;
      }
    this_object()->move(dest);
    tell_object(dest,"A white dove comes flying, and lands on your " +
        "shoulder.\n");
    tell_room(E(dest), "A white dove comes flying, and lands on the " +
          "shoulder of " + QTNAME(dest) + ".\n", dest);
    test_dove_killer(dest);
    return 1;
}

int
set_times_to_fly(int i)
{
    if (!i) i = TIMES;
    if (i > 10) i = 10;
    times = i;
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
    this_object()->move(PIGEON_HOME);
    tell_room(E(TO),
          "A white dove comes flying, landing on the floor.\n");
    set_alarm(15.0,0.0,"return_to",owner);
    return 1;
}

int
test_dove_killer(object pl)
{
    if (pl->query_prop("_player_is_dove_killer"))
      {
      tell_object(pl,"The dove recognizes you as a killer of doves,\n"+
              "and hurriedly flies away again!\n");
      tell_room(E(pl), "The dove is scared by " + QTNAME(pl) +
            ", and flies away again!\n",pl);
      return_home();
      }
    return 1;
}

void
do_die(object killer)
{
    killer->add_prop("_player_is_dove_killer",1);
    ::do_die(killer);
}

