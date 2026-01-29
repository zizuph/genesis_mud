inherit "/d/Kalad/std/monster";
inherit "/std/combat/unarmed";
#include "/d/Kalad/defs.h"
#include "/sys/macros.h"
#include <wa_types.h>
#include <ss_types.h>
#define A_BITE 0
#define A_LCLAW 1
#define A_RCLAW 2
#define H_HEAD 0
#define H_BODY 1

#define CHECK_ACTOR if (!present(actor, environment())) { return; }
/* by korat */
/* this dog will follow anyone leaving a room, maybe */
create_monster()
{
    set_name("dog");
    set_race_name("dog");
    set_adj("ragged");
    set_long("It's a dog, living off the food, spoils and anything else "+
      "the citizens of Kabal leaves behind.\n");
    set_stats(({10,10,15,10,15,10}));
    set_gender(G_NEUTER);
    set_skill(SS_DEFENCE,20);
    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(OBJ_I_WEIGHT, 5000);
    add_prop(OBJ_I_VOLUME, 5000);
    add_prop(OBJ_I_NO_INS,1);
    set_act_time(3);
    add_act("emote jumps around and licks everyone.");
    add_act("emote barks loudly.");
    add_act("growl .");
    add_act("emote sniffs at a wall.");
    add_act("emote raises its leg and marks its territory.");
    add_act("emote plays with your shoes.");
    add_act("emote slavers with its tongue hanging out.");
    /* set_random_move(60); */
    set_attack_unarmed(A_BITE, 25, 35, W_IMPALE, 40, "jaws");
    set_attack_unarmed(A_LCLAW, 20, 20, W_SLASH, 30, "left paw");
    set_attack_unarmed(A_RCLAW, 20, 20, W_SLASH, 30, "right paw");
    set_hitloc_unarmed(H_HEAD, ({ 5, 5, 10 }), 7, "head");
    set_hitloc_unarmed(H_BODY, ({ 5, 5, 1 }), 80, "body");
    trig_new("%w 'leaves' %s","follow");
    trig_new("%w 'cooes.\n' %s","kill_pigeon");
}

void
emote_hook(string emote, object actor, string adverb)
{
    if (emote == "kick") set_alarm(1.0,0.0,"got_kicked",actor);
    if (emote == "cooes") set_alarm(1.0,0.0,"kill_pigeon",actor);
    if (emote == "ruffle") set_alarm(1.0,0.0,"got_ruffled",actor);
    if (emote == "purr") set_alarm(1.0,0.0,"reackt_purr",actor);
}

kill_pigeon(string who, string dummy)
{
    who=lower_case(who);
    command("growl pigeon");
    command("emote gets ready to jump the pigeon.");
    set_alarm(1.0,0.0,"kill_it");
}

kill_it()
{
    command("kill pigeon");
}


reackt_purr(object actor)
{
    CHECK_ACTOR;
    command("emote barks loudly.");
    command("emote looks very confused.");
    actor->catch_msg("The dog starts to bark loudly at you.\n");
    say("The dog barks loudly at "+QTNAME(actor)+".\n");
    return;
}

got_kicked(object actor)
{
    CHECK_ACTOR;
    command("growl "+query_the_name(actor));
    command("emote whimpers softly and lurks away with its tail between its legs.");
    command("east");
    command("north");
    command("northwest");
    command("northeast");
    command("up");
    command("emote plays with your shoes.");
    return;
}


got_ruffled(object actor)
{
    CHECK_ACTOR;
    actor->catch_msg("The "+short()+" licks your hand.\n");
    say("The "+short()+" licks "+QTNAME(actor)+"'s hand.\n");
}

follow(string who, string where)
{
    object ob;
    string *dummy;
    if (random(10)>0)
    {
	say("The dog decides to follow.\n");
	who = lower_case(who);
	set_alarm(0.0,0.0,"move_dog",who,where);
	return;
    }
    say("The dogs looks after them who left, but decides to stay.\n");
}


move_dog(string who, string where)
{
    object ob;
    string dummy;
    if (sscanf(where,"north.%s",dummy)) command("north");
    if (sscanf(where, "south.%s",dummy)) command("south");
    if (sscanf(where,"west.%s",dummy)) command("west");
    if (sscanf(where,"east.%s",dummy)) command("east");
    if (sscanf(where,"northeast.%s",dummy)) command("northeast");
    if (sscanf(where,"northwest.%s",dummy)) command("northwest");
    if (sscanf(where,"southwest.%s",dummy)) command("southwest");
    if (sscanf(where,"southeast.%s",dummy)) command("southeast");
    if (sscanf(where,"down.%s",dummy)) command("down");
    if (sscanf(where,"up.%s",dummy)) command("up");
    if (sscanf(where,"in.%s",dummy)) command("in");
    if (sscanf(where,"out.%s",dummy)) command("out");
    if (!(ob = present(who, environment()))) return;
    switch (random(10))
    {
    case 0:
	ob->catch_msg("The dog snatches at your heels as it follows you.\n");
	say("The dog snatches after "+QTNAME(ob)+"'s heels.\n");
	break;
    case 1:
	ob->catch_msg("The dog peers at you with a hungry, begging look.\n");
	say("The dog peers at "+QTNAME(ob)+" with some hungry, begging eyes.\n");
	break;
    case 2:
	ob->catch_msg("After a while the dog comes lurking in your footsteps.\n");
	say("A dog comes in, lurking after "+QTNAME(ob)+".\n");
	break;
    case 3:
	ob->catch_msg("The dog arrives and sniffs at your leg.\n");
	say("A dog arrives and sniffs at "+QTNAME(ob)+"'s leg.\n");
	break;
    case 4:
	ob->catch_msg("The dog comes leaping after you, barking loudly.\n");
	say("A dog comes leaping after "+QTNAME(ob)+", barking loudly.\n");
	break;
    case 5:
	ob->catch_msg("Flapping its tail, the dog runs in between "+
	  "your legs, almost tripping you.\n");
	say("A dog runs inbetween "+QTNAME(ob)+"'s legs with its tail in the air.\n");
	break;
    default:
	break;
    }
}


