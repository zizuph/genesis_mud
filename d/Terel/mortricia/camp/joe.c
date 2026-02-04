/*
 * Gamblin' Joe. Mortricia 920927
 *
 * Updated 11/28/2018 by Shanoga
 *  - Joe no longer instigates betting, but is triggered when
 *    a player makes a bet
 *  - Joe's emotes are a bit more varied, references fortune teller
 *  - Joe hints at what two numbers he might be on, but will randomly
 *    choose one. If taken, he switches to the other. If both taken,
 *    Joe doesn't bet.
 */
inherit "/std/monster";
inherit "/std/act/action";
inherit "/std/act/seqaction";
inherit "/std/act/domove";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <money.h>

#include "/d/Terel/common/terel_defs.h"

#define BS(message)     break_string(message, 70)
#define BSN(message)    break_string(message + "\n", 70)
#define TP              this_player()
#define TO              this_object()

#define NO_OF_BETS      11

#define ALIGN           -50
#define CAMP_DIR        MORTRICIADIR + "camp/"
#define ARM_DIR         MORTRICIADIR + "armours/"
#define WEP_DIR         MORTRICIADIR + "weapons/"

string *tnum = ({"zero", "one", "two", "three", "four", "five", "six",
    "seven", "eight", "nine", "ten", "eleven", "twelve"});
int luck, lucka, luckb, betting;

void
create_monster()
{
    if (!IS_CLONE)
        return;

    set_name("gambler");
    set_short("old gambler");
    set_long("It's an old human. As he looks around, his gaze lingers " +
             "longingly on the Wheel of Chance, the only thing that he " +
             "still tolerates in his final years.");
    set_adj("old");
    set_gender(0);
    set_race_name("human");

    add_prop(LIVE_I_NEVERKNOWN, 0);

    set_stats(({15,15,15,25,25,15}));
    set_hp(9999);
    set_mana(9999);
    set_alignment(ALIGN);

    set_skill(SS_UNARM_COMBAT, 15);

    set_all_hitloc_unarmed(15);
    set_all_attack_unarmed(15, 15);

    set_act_time(1);
    add_act("@@actions");
    
    lucka = random(NO_OF_BETS) + 1;
    luckb = ((lucka + (random(NO_OF_BETS - 1))) % 11) + 1;
    
}

public void
enable_betting(int win = -1)
{
    if (win == 1)
        command("say I can't stop when luck is on my side!");
    if (!win)
        command("say I just need to win the next one to break even...");
    betting = 0;
    luck = 0;
    set_act_time(1);
}

void
check_taken(int n, int lucka = 0, int luckb = 0)
{
    if (!command("bet on " + n + " with silver"))
    {
        if (lucka == 0)
        {
            command("emote sweats nervously.");
            command("say Both of my lucky numbers are taken?! " +
                    "This is a bad omen. I'll wait until the next game.");
            set_alarm(20.0, 0.0, &enable_betting(-1));
            return;
        }
        command("say Bah! Someone took my lucky number!");
        int new;
        if (n == lucka)
            new = luckb;
        else
            new = lucka;
        set_alarm(1.0, 0.0, &check_taken(new));
    }
    else
    {
        set_alarm(0.5, 0.0, &command("say " + capitalize(tnum[n]) +
            " is my" + (lucka == 0 ? " REAL " : " ") + "lucky number - I'm sure of it!"));
    }
}

void
place_bet()
{
    if (!betting)
    {
        command("emote 's eyes widen in anticipation.");
        int n = lucka;
        if (random(2) && luckb) n = luckb;
        set_alarm(1.0, 0.0, &check_taken(n, lucka, luckb));
        betting = 1;
    }
}

void
actions()
{
    if (!luck)
    {
        lucka = random(NO_OF_BETS) + 1;
        luckb = ((lucka + (random(NO_OF_BETS - 1))) % 11) + 1;
        command("say The fortune teller said " + tnum[lucka] +
                " is going to be lucky for me! Or was it " +
                tnum[luckb] + "...?");
        command("emote furrows his brow, deep in thought.");
        luck = 1;
        set_act_time(5);
        return;
    }
    if (!random(2))
    {
        command("emote rubs his hands together in anticipation.");
        return;
    }
    command("emote looks around hoping for someone to place a bet.");
}