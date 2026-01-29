/*
 * File Name        : ferret.c
 * By               : Ares
 * Inspiration from : A parrot by Ashlar, monkey by Elmore.
 * Date             : May 2004
 *
 * Cotillion - 2004-10-07
 * - Don't send messages to immortals. And don't reveal who's logged in.
 * Lunatari - 2011-10-15
 * - Removed wrongly configured object value as octal.
 *
 * Navarre July 3rd, fixed typo.
 * 
 * Cotillion - 2020-03-23
 * - Limited the number of ferrets in a room to 25 
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

#define PARROTSUBLOC    "_ansalon_monkey_subloc"
#define PARROTNAME      "_ansalon_monkey"

/* The temporary room in the air when the pigeon is flying. */
#define AIR_ROOM     "/d/Krynn/solamn/vin/room/air_room"

/* The home of the pigeon. */
#define PIGEON_HOME     "/d/Krynn/solamn/vin/room/pigeon_store"

/* The message. */
#define MESSAGE_OBJ     "/d/Krynn/solamn/vin/obj/message"

/* The delay between sending the message and the receiving of it. */
#define SLOWLY random(60) + 60

/* The number of times the pigeon will carry a message. */
#define TIMES 5

#define A_BEAK 0
#define A_CLAWS 1
#define H_HEAD 0
#define H_BODY 1
#define H_WINGS 2

string *colours = ({ "brown", "white", "cinnamon-colored", 
                         "cream-colored", "light brown", "dark brown", "white albino", 
                         "playful white", "playful brown", "playful albino", "troublesome white", 
                         "troublesome brown", "bouncy", "playful", "cute", "wise old", "young", "baby", 
                         "cute baby", "white baby", "brown baby", "baby albino", "playful baby", 
                         "troublesome baby", "Sanction Scum Special", "dirty", "black", "grey-eyed", 
                         "red-eyed", "purple-eyed", "three-eyed", "mutated dirty", "loud", "curious", 
                         "loving", "bushy", "dirty-nosed troublesome", "curious baby", "grumpy", 
                         "smart white", "smart brown", "blind", "sick", "diseased", "skeletal",
                         "warm-hearted loving", "female", "male", "three-legged", "peg-legged", 
                         "glass-eyed", "frowning", "furious", "fluffy", "floppy-eared",
                         "pink-nosed", "black-nosed", "dirty-nosed", "smelly", "foul-smelling",
                         "ghostly", "temperamental", "moody", "perfume-smelling", "sleepy", "crazy-eyed", 
                         "green-eyed", "blue-eyed", "black-eyed", "vicious", "rabid", "diseased-ridden",
                         "shadowy", "elusive", "thieving", "elusive thieving", "fluffy thieving", 
                         "thievish", "hostile", "frolicsome", "frisky", "charming", "flea-infested",
                         "dragonarmy", "dirty", "cute dirty", "sanction", "krynn", "mean", "ghost"});
string *lines = ({ });

int false_drop;
int present;

/* Prototypes */
int set_times_to_fly(int i);
int send_mail();
int return_to(object dest);
int fly_to_someone(object dest);
void return_home();

string gMessage, gWho, gSender;
int gUsage,pigeon_busy,times,fly_alrm;
object owner;

void
create_creature()
{
    string c;   

    if (!IS_CLONE)
        return;

    set_name("ferret");
    add_name(PARROTNAME);
    add_name("animal");

    set_race_name("ferret");
    c = colours[random(sizeof(colours))];

    set_adj(explode(c," "));

    set_long("The ferret is " + c + " and has a mask like a raccoon. "+
        "It has four feet, a long bushy tail and beady eyes. \n");

    set_gender(2);
    set_appearance_offset(-25-random(20));

    default_config_mobile(4);
    set_skill(SS_DEFENCE, 90);
    set_skill(SS_AWARENESS,40);

    gUsage = 0;

    add_prop(LIVE_I_NEVERKNOWN,1);
    change_prop(OBJ_M_NO_GET,"@@take_monkey");
    add_prop(CONT_I_WEIGHT, 2000);
    add_prop(CONT_I_HEIGHT, 30);
    add_prop(CONT_I_VOLUME, 1500);
    add_prop(OBJ_I_VALUE, 288);
    add_prop(OBJ_M_NO_SELL, 1);

    add_prop(NPC_M_NO_ACCEPT_GIVE, " does not want that.\n");

    set_attack_unarmed(A_BEAK,5,10,W_SLASH,40,"sharp teeth");
    set_attack_unarmed(A_CLAWS,10,7,W_SLASH,60,"claws");
    set_hitloc_unarmed(H_HEAD,7,20,"head");
    set_hitloc_unarmed(H_BODY,10,55,"body");
    set_hitloc_unarmed(H_WINGS,8,25,"tail");

    set_times_to_fly(TIMES);

    //catch(PARROT_ADMIN->register_parrot(TO));

    set_act_time(20);
    add_act("emote hops up and down, falling over several times.");
    add_act("emote crawls up your leg and explores a pocket.");
    add_act("emote bounces into a ball.");
    add_act("emote chatters while it hops to and fro.");
    add_act("emote curls up into a ball and goes to sleep.");
    add_act("emote disappears in your shirt.");
    add_act("emote backs up to the nearest corner to do its business.");
    add_act("emote playfully bites at your pant leg.");
    add_act("emote drags a twig it found across the room.");
    
}

void
attacked_by(object enemy)
{
    if ((enemy->id("wolf")) && (query_panic() < 1000))
        add_panic(1000);
    ::attacked_by(enemy);
}

mixed
take_parrot()
{
    if (objectp(TP) && interactive(TP) && present(PARROTNAME,TP))
    {
        return "It'd be too much to handle two ferrets as they "+
            "are too playful. You decide to put one of them down.\n";
    }
    else
        return 0;
}

int
is_parrot(object ob)
{
    if (ob->id(PARROTNAME))
        return 1;
    else
        return 0;
}

void
check_environment()
{
    if (!objectp(environment()))
        return;

    object *ferrets = filter(all_inventory(environment()), &->id(PARROTNAME));

    if (sizeof(ferrets) > 25) {
        set_alarm(5.0, 0.0, &return_home());
    }
}

int environment_alarm;
void
enter_env(object env, object from)
{
    ::enter_env(env, from);

    if (!get_alarm(environment_alarm))
        environment_alarm = set_alarm(0.5, 0.0, &check_environment());
}

void leave_env(object from, object to)
{
    ::leave_env(from,to);
    if(!false_drop && from->query_prop(LIVE_I_IS))
    {
        from->remove_subloc(PARROTSUBLOC);
        set_no_show_composite(0);
        present = 0;
    }
    false_drop = 0;
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (subloc != PARROTSUBLOC)
        return ::show_subloc(subloc, me, for_obj);
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
        return "You have a ferret weaving in and out of your pockets. \n";

    if (for_obj == me)
        return "You have a " + short() + " weaving in and out of your pockets.\n";
    else
        return C(PRONOUN(me)) + " has a " + short() + " weaving in and out of " +
            POSSESSIVE(me) + " pockets.\n";
}


int
collect()
{   
    string name;

    if (present == 1)
    {
        TP->catch_msg("You must drop the ferret first if you want it to get a coin.\n");
        return 1;
    }

    name = TP->query_real_name();
    TO->tell_watcher("The ferret sniffs the ground searching for coins.\n");
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

    if (gUsage >= times)
    {
        write("The ferret doesn't want to deliver a message, it wants to play.\n");
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
    /* If a player knows the name of another player, let him send the pigeon.*/
    gWho = who;
    gSender = lower_case(tp->query_name());
    
    pigeon_busy = 1;
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
        pigeon_busy = 0;
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
        + this_player()->query_possessive() +
        " ferret and it runs off to deliver it.\n");
    /* turn autoreturn of pigeon off*/
    if (fly_alrm)
        remove_alarm(fly_alrm);
    fly_alrm = 0;
    tell_room(E(TO), "The "+short()+" runs off with the message in its mouth. \n");
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
        write("You convince the critter to make yet another try.\n");
        move(AIR_ROOM);
        set_alarm(itof(SLOWLY),0.0,"deliver");
        return 1;
    }
    
    notify_fail("The ferret doesn't want to make another try.\n");
    return 0;
}

int 
deliver()
{
    object target, message;
    /* Does our initial target still exist? */
    target = find_player(gWho);
    if (!target || target->query_wiz_level())
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
    pigeon_busy = 0;
    if (target == find_player(gSender))
        tell_object(target, "Your "+short()+ " returns, unable to find "
            + C(gWho) + ". It climbs up to your shoulder and " +
            "you retrieve your message.\n");
    else
        tell_object(target, "A "+short()+ " runs towards you and climbs up "+
            "to your shoulder. It gives you a message " +
            "from " + C(gSender) + ".\n");
    /*return to owner if i'm not needed.*/
    if (owner && target != owner)
    {
        tell_object(target, "If you do not use this ferret it will return to " +
            "it's owner again.\n");
        fly_alrm = set_alarm(40.0,0.0,"attempt_fly_to_someone",owner);
    }
    
    tell_room(E(target),
        "A ferret arrives and climbs up to " + QTNAME(target) + "'s shoulder and gives "+
        ""+ target->query_objective() + " a message.\n",target);
    
    message = clone_object(MESSAGE_OBJ);
    message->set_message(gMessage);
    message->set_sender(gSender);
    message->move(target);
    gUsage++;
    if (gUsage >= times)
        set_alarm(40.0,0.0, &return_home());
}

int
do_return(string str)
{
    if (!str) {
        write("Return what?\n");
        return 1;
    } 
    if (str == "ferret")
    {
        write("You set the ferret on the ground so it can run back home.\n");
        say(QCTNAME(this_player()) + " sets the ferret on the ground, "+
            "and it runs away.\n",
            this_player());
        /* turn autoreturn of pigeon off*/
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
    return pigeon_busy;
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
    pigeon_busy = 0;
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
        tell_room(E(E(TO)), "The "+short()+ " runs away.\n");
    else 
        tell_room(E(TO),
            "The "+short()+ " runs away!\n");
    if(!dest)
    {
        remove_object();
        return 1;
    }
    this_object()->move(dest);
    tell_object(dest,"A "+short()+ " crawls up your leg.\n");
    tell_room(E(dest), "A "+short()+ " crawls up the leg of " +
        "" + QTNAME(dest) + ".\n", dest);
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
        "A "+short()+ " arrives and lays on the floor.\n");
    set_alarm(15.0,0.0,"return_to",owner);
    return 1;
}

void
init_living()

{
    add_action("collect", "collect");
    add_action("do_send","send",0);
    add_action("do_return","return",0);
    add_action("do_resend","resend",0);
}
