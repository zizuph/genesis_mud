/*
 * sailor.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 *
 * Updated and added new dialog with hint to new Golbar camp, Treacher Aug 2021
 */

#pragma save_binary
#pragma strict_types

#include "defs.h"

inherit ROKEDIR + "lib/monster";

#include <macros.h>

void equip_myself();
void setup_acting();

int sleeping = 0;
mixed *sleep_sequence = ({ "@@snore", 1 });

void
snore()
{
    command("snore");
    seq_addlast("sleep_seq", sleep_sequence);
}

void
wake_up()
{
    seq_clear("sleep_seq"); seq_delete("sleep_seq");
    command("emote snores so loadly that he wakes himself up.");
    set_alarm(2.0, 0.0, &command("emote looks around him with a drunken look in his eyes."));
    set_alarm(2.5, 0.0, &command("hiccup"));
    sleeping = 0;
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    setup_acting();
}

void
sleep()
{
    sleeping = 1;
    set_default_answer("The drunken sailor seems to be sound asleep and takes no notice of you.");
    seq_new("sleep_seq");
    seq_addfirst("sleep_seq", sleep_sequence);
    set_alarm(120.0, 0.0, &wake_up());
    add_prop(LIVE_M_NO_ACCEPT_GIVE, " appears to be sleeping and cannot accept any gifts right now.\n");
    
    command("emote suddenly seems to fall asleep where he stands in front of you.");
}

string
answer_rumour()
{
    clear_act(); //Silence the sailor while answering
    remove_asks();
    set_default_answer("The drunken sailor seems busy at the moment to answer any questions.");

    float delay = 0.0;
    write("The drunken sailor looks at you with a fuzzy gaze.\n");
    say(QCTNAME(TO) + " looks at " + QTNAME(TP) + " with a fuzzy gaze.\n");
    delay +=  2.0; set_alarm(delay, 0.0, &command("say What rumours? I havenent heard no rumoursh."));
    delay += 12.0; set_alarm(delay, 0.0, &command("emote looks around with a slightly more clear look in his eyes as he seems to remember something."));
    delay +=  2.0; set_alarm(delay, 0.0, &command("say Guesh wat I shaw a fjew nightsh ago?"));
    delay +=  1.0; set_alarm(delay, 0.0, &command("hiccup"));
    delay +=  5.0; set_alarm(delay, 0.0, &command("say I was outh in da nite to catsh som fishes"));
    delay +=  1.0; set_alarm(delay, 0.0, &command("say on my favoriouet shpot onthe end of the pier."));
    delay +=  2.0; set_alarm(delay, 0.0, &command("emote tries to point to the east but fails miserably."));
    delay += 10.0; set_alarm(delay, 0.0, &command("say I waz jusht about to catch a biggie thiiis big."));
    delay +=  2.0; set_alarm(delay, 0.0, &command("emote stretches out his arms so wide that he loses his balance and almost fall down."));
    delay +=  4.0; set_alarm(delay, 0.0, &command("hiccup"));
    delay +=  4.0; set_alarm(delay, 0.0, &command("say Then shuddnly two boatsh came in from the whater and landed on that sshmall beach."));
    delay +=  2.0; set_alarm(delay, 0.0, &command("emote tries to point to the east but fails miserably."));
    delay +=  2.0; set_alarm(delay, 0.0, &command("say aand the two boatses looked egsactly the same."));
    delay +=  4.0; set_alarm(delay, 0.0, &command("hiccup"));
    delay +=  4.0; set_alarm(delay, 0.0, &command("say I know! Exagtly the same, and thay moved in te shame shpeed ashwell."));
    delay +=  4.0; set_alarm(delay, 0.0, &command("say Aand that washnt all."));
    delay +=  4.0; set_alarm(delay, 0.0, &command("hiccup"));
    delay +=  4.0; set_alarm(delay, 0.0, &command("emote leans forward and whispers: Frohm the boats dishembarked a hole bunch of twins!"));
    delay +=  2.0; set_alarm(delay, 0.0, &command("say All of shem! Twins!"));
    delay +=  2.0; set_alarm(delay, 0.0, &command("smile triump"));
    delay +=  6.0; set_alarm(delay, 0.0, &command("say And the twinz movded shyncoronaz .."));
    delay +=  3.0; set_alarm(delay, 0.0, &command("say .. synchorn .."));
    delay +=  4.0; set_alarm(delay, 0.0, &command("say .. scrynished .."));
    delay +=  2.0; set_alarm(delay, 0.0, &command("frown"));
    delay +=  5.0; set_alarm(delay, 0.0, &command("say they movded in the egsagtly sameh way."));
    delay +=  4.0; set_alarm(delay, 0.0, &command("sniff emot"));
    delay +=  3.0; set_alarm(delay, 0.0, &command("asay emot It whas the mosht beauteful shing I ever seehn."));
    delay +=  4.0; set_alarm(delay, 0.0, &command("emote whipes away a small tear from the corner of his eye."));
    delay +=  8.0; set_alarm(delay, 0.0, &command("emote seems to think hard about something."));
    delay +=  6.0; set_alarm(delay, 0.0, &command("say Buth I dohn't undeshand how dey got the pink elefantsh onto the boatses."));
    delay +=  4.0; set_alarm(delay, 0.0, &sleep());
}

void
crack_weather()
{
    command("emote gestures with his index finger in front of his mouth.");
    set_alarm(1.0, 0.0, &command("say Schhhccshhhhshh lishen! Do you hhear thhaat?"));
    set_alarm(8.0, 0.0, &command("fart"));
    set_alarm(9.0, 0.0, &command("laugh drunk"));
}

void
setup_acting()
{
    set_act_time(5);
    add_act("burp");
    add_act("say Gimme an ale, stranger!");
    add_act("puke");
    add_act("say Fiishingg ona shundayafthnoohn is nihece...");
    add_act("emote sings: whaat schall we do with 'he druunkn schailor...");
    add_act("hiccup");
    add_act("emote stumbles into you as he loses his balance.");
    add_act("say I saw a rumour. The mayor shaid it was just a rumour. Oh the mayor, he sussch a nihece guy I reeaaaaly like him. He ish so khind to me.");
    add_act("emote looks at you with blurry eyes.");
    add_act("@@crack_weather");

    add_ask(({"rumour", "rumours"}), answer_rumour);
    set_default_answer("say I d'ont knoh whaat yo talking about. Ive don noshing!", 1);
}

public string
long_extra()
{
    if(sleeping)
    {
        return "He appears to be sleeping.\n";
    }
    else
    {
        return "";
    }
}

void
create_monster()
{
    set_name("sailor");
    set_short("drunken sailor");
    set_long("He is obviously very stoned.\n@@long_extra@@");
    set_adj("drunken");
    set_race_name("human");

    seteuid(getuid());

    default_config_npc(20);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    NEVERKNOWN;

    setup_acting();

    set_alarm(1.0, 0.0, equip_myself);
}

void
equip_myself()
{
    if (!present("fishing_rod", TO))
        clone_object(ROKEDIR + "wep/fishing_rod")->move(TO);
    set_alarm(6.0, 0.0, &command("wield all"));
}

void
thank(object from, object ob)
{
    object rod;

    if (!objectp(ob))
        return;
    
    if (!ob->id("ale"))
    {
        set_alarm(2.0, 0.0, &command("drop " + OB_NAME(ob)));
        return;
    }

    if (!objectp(from) || !present(from, environment()))
    {
        command("smile");
        set_alarm(5.0, 0.0, &command("drink all"));
        return;
    }
    
    if (!(rod = present("fishing_rod", TO)))
    {
        command("smile " + OB_NAME(from));
        command("say Thanks! I wish there was something I could give " +
            "you in return.");
        return;
    }
  
    command("smile " + OB_NAME(from));
    command("give rod to " + OB_NAME(from));
    set_alarm(5.0, 0.0, &command("drink all"));
    
    set_alarm(600.0, 0.0, equip_myself);
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(from))
        return;

    set_alarm(1.0, 0.0, &thank(from, ob));
}
