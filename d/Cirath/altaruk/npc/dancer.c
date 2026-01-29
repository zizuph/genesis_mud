/*
 * dancer.c
 *
 * A dancer at the Dead Kank Inn in Altaruk.
 * Be carefull, she's moody.
 *
 * Azazel 2002
 */

inherit "/std/monster";
inherit "/lib/trade";

#include "/d/Cirath/common/defs.h"
#include "../defs.h"
#include <std.h>
#include <stdproperties.h>
#include <ss_types.h>
#include <money.h>
#include "/d/Cirath/common/introfnc.h"
#include "/d/Gondor/open/room_chairs/room_chairs.h"

#define NUM   4

int g_aggr;
mapping MoodMap = ([ ]);
string *randemote1, *randemote2, *randemote3, *randemote4;

create_monster()
{
    set_name("vianna");
    add_name("dancer");
    set_title("Wirlwind");
    set_race_name("human");
    set_adj("half-naked");
    set_adj("slender");
    set_gender(1);
    set_long("She is a dancer that performs in bars for" +
        " money. She has long red hair and is wearing nothing" +
        " save a girdle that consists of a thong and piece of" +
   	" cloth no bigger than an eye patch. On her side she" +
   	" has a small pouch she puts silver coins into.\n");
    set_alignment(400);
    set_stats(({80,90,70,65,65,80}));
    set_skill(SS_UNARM_COMBAT,80);
    set_skill(SS_DEFENCE,70);
    set_skill(SS_AWARENESS,50);
    set_act_time(6);
    add_act("strut");
    add_act("flip");
    add_act("emote moves her belly like a rippling stream.");
    add_act("emote twirls around the stage.");
    add_act("emote twists her hips to the beat of the music.");
    add_act("emote drops into a perfect split.");
    add_act("emote bends slowly backwards til she touch the" +
        " floor with the back of her head.");
    set_cact_time(6);
    add_cact("shout Eek! Get off me you bastard.");
    add_cact("say I'l dance you to death!");
    add_cact("swear");
    add_cact("say blasted fool!");

    add_prop(LIVE_I_NEVERKNOWN,1);
    add_prop(LIVE_M_NO_ACCEPT_GIVE,"is payd to perform.");
    config_default_trade();
}

void
init_living() { add_action("do_dance", "pay"); }

do_dance(string str)
{
    int price, *result, change, i;

    if(!(str=="dancer"))
        {
        notify_fail("pay whom?\n");
        return 0;
        }

    if(!(strlen(this_player()->query_prop(LIVE_S_SITTING))))
        {
        notify_fail("you better sit down if you want a private dance.\n");
        return 0;
        }
       
    price = 12;

    result = pay(price, this_player(), "silver", 0, TO, "copper");
    if(sizeof(result)==1) {return 0; }

    write("You hold out "+text(result[0 .. NUM -1])+". The " +
        short() + " quickly snatches it from your hand.\n");
    change = text(result[NUM .. 2 * NUM - 1]);
    seteuid(getuid(this_object()));

    if(change) {write("You get, " +change+ " as change.\n"); }

    write("The " + short() + " flips herself onto the table to" +
        " stand in front of you.\n");
    say(QCTNAME(this_player()) + " is getting a private dance.\n");
    set_alarm(6.0, 0.0, &write("She slowly moves her hips from side to side...\n"));
    set_alarm(9.0, 0.0, &write("sinking lower and lower...\n"));
    set_alarm(12.0, 0.0, &write("slipping onto your lap.\n"));
    set_alarm(15.0, 0.0, &write("She starts to rub herself all over you.\n"));
    set_alarm(18.0, 0.0, &write("She suddenly flips her long legs around and...\n"));
    set_alarm(21.0, 0.0, &write("arches herself against you until...\n"));
    set_alarm(27.0, 0.0, &write("she finaly walks away, smiling.\n"));
    set_alarm(30.0, 0.0, &command("wink at " + this_player()->query_name()));

    return 1;
}

public void
emote_hook(string emote, object actor, string adverb = 0)
{
    int chng;
    int opinion = MoodMap[actor->query_name()];

    randemote1 = ({ "wink app at " + actor->query_name(),
        "wave at " + actor->query_name(), "smile at " + actor->query_name(),
        "curtsey to " + actor->query_name(), "bat at " + actor->query_name()});
    randemote2 = ({ "say to " + actor->query_name() + " Get your dirty hands" +
        " off me now!", "slap " + actor->query_name(), "pout at " +
        actor->query_name()});
    randemote3 = ({ "say to " + actor->query_name() + " Hey! Watch it!",
        "pout", "frown"});
    randemote4 = ({ "flirt with " + actor->query_name(), "blow kiss to " +
        actor->query_name(), "smile sexily at " + actor->query_name(),
        "ruffle " + actor->query_name(), "kiss " + actor->query_name()});

    switch (emote)
    {
    case "applaud":
    case "wave":
    case "compliment":
    case "clap":
        g_aggr = g_aggr - 1;
        chng = -2;
	command (randemote1[random(sizeof(randemote1))]);
	break;
    case "flirt":
    case "pet":
    case "cuddle":
    case "ruffle":
    case "pat":
    case "kiss":
    case "lick":
    case "fondle":
    case "hug":
    
        chng = 5;
        g_aggr = g_aggr + 1;

	if ((g_aggr+opinion) <= -20)
        {
	command(randemote4[random(sizeof(randemote4))]);
	chng = -3;
	g_aggr = g_aggr -1;  
        }
        else if ((g_aggr+opinion) <= 90)
        {
	command(randemote2[random(sizeof(randemote2))]);
        }
	else
	{
        command("say Thats it!");
        actor->catch_tell("The "+lower_case(short())+" hurls a chair at you" +
            " and walks off stage in a fit of anger.\n");
	tell_room(environment(this_object()), QCTNAME(this_object()) +
	    " hurls a chair at " + QTNAME(actor) + " and walks off stage in" +
	    " a fit of anger.\n", actor, this_object());
        remove_object();
        }
	break;
	
    case "poke":
    case "kick":
    case "swear":
    case "spit":
    case "curse":
    case "tackle":

        chng = 5;
        g_aggr = g_aggr + 1;
        
	if ((g_aggr+opinion) <= 90)
	command(randemote3[random(sizeof(randemote3))]);
	else
	{
        command("say Thats it!");
        actor->catch_tell("The "+lower_case(short())+" hurls a chair at you" +
            " and walks off stage in a fit of anger.\n");
	tell_room(environment(this_object()), QCTNAME(this_object()) +
	    " hurls a chair at " + QTNAME(actor) + " and walks off stage in" +
	    " a fit of anger.\n", actor, this_object());
        remove_object();
	}
	break;
    }
        if (g_aggr >= 80)
        g_aggr = 80;
    MoodMap += mkmapping(({actor->query_name()}), ({MoodMap[actor->query_name()]+chng}));
}
