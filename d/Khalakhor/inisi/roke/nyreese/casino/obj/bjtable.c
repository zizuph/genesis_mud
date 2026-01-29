/*
 * bjtable.c
 *
 * Used in casino/room/blackjack-room.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

/*
 * This was completely recoded by Glindor for the move.
 *
 * Changelog:  - Oct, 2016: Changed <double> to <doublebet> so as not to
 *                          conflict with the mudlib emote command that
 *                          has the same name. (Gorboth)
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object.c";
inherit "/lib/trade.c";

#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include "../defs.h"

#include <money.h>
#include <cmdparse.h>
#include <composite.h>
#include "marker_utils.h"

#define NSLOTS 7
#define NDECKS 6
#define DEALER CASINO + "npc/bjdealer"
#define BJ_ROOM CASINO + "room/blackjack-room"
#define BJ_LOG "blackjack-test"

object dealer;

int toid;                 /* Alarm id for timeout */
int sgid;                 /* start_game alarm */
int *cardlist, usedcards; /* List of all the cards (312)*/
int *dhand, dvalue;       /* Dealer hand and value */
int soft;
int totalbets;

mixed *slots;
/* slots structure */
#define SL_PL 0
#define SL_BET 1
#define SL_BB 2
#define SL_HANDS 3
#define SL_SIZE 4
#define SL_CLEAR ({ 0, ({}), ({}), ({}) })

/* hand structure */
#define H_BET 0
#define H_BB 1
#define H_DONE 2
#define H_ONEMORE 3
#define H_CARDS 4
#define H_SIZE 5
#define H_CLEAR ({ 0, 0, 0, 0, ({}) })

/* Keep track of the state of the game */
int cslot, chand;         /* Current slot/hand */
object cplayer;           /* Current player */
int state;                /* State */
#define ST_IDLE 0
#define ST_BET 1
#define ST_PLAY 2

/* Statistics */

int stat_bet_wiz = 0, stat_bet = 0;
int stat_win = 0;

void reset_table();
void shuffle();
//int win(int pval, int dval,int bjack,int djack,int pl);

void poll_dealer();
void player_timeout1();
void player_timeout2();
void resolve_hand(int slot, int hand, int win);
void finalize_dealer();
void make_cards();
int next_card();
void next_step();
int do_bet(string str);
int do_backbet(string str);
int do_stand(string str);
int do_split(string str);
int do_double(string str);
int do_draw(string str);
varargs string cards(object player);
int query_card_value(int id);
string query_card_name(int id);
int evalcards(int *cards);
void end_game();
void log_bet(object player, int *betcoins, string str);
void log_win(object player, int *betcoins, string str);
int cheat(string str);

string
ptext()
{
    return    
        "This is a summary of the things you can do:\n\n" +
        "bet <amount> : Bet, give the number and type of marker you wish to bet.\n" +
        "               For example: <bet 1 blue> or <bet 3 red>\n" +
        "               You are allowed to play on several slots, to bet on a \n" +
        "               specific slot: <bet 2 green on 5> to bet on slot 5.\n\n" +
        "backbet      : Works like bet, but puts the bet behind another player's\n" +
        "               slot trusting that player's skill. You must specify a slot.\n\n" +
        "draw         : Tell the dealer that you want another card.\n\n" + 
        "stand        : Tell the dealer that you are satisfied.\n\n" + 
        "split        : Tell the dealer that you want to split your cards.\n" + 
        "               It will automatically bet the same amount on the second set\n" +
        "               of cards, you will need the required markers on hand.\n\n" +
        "doublebet    : Tell the dealer that you want to double your bet.\n\n" + 
        "mc           : Check your cards (mc = my cards).\n\n" + 
        "exa cards    : Check all the cards on the table.\n\n" +
        "stop playing : Leave the table so that someone else can play.\n\n" +
        "Note: All bets are made with the casino's markers, that can be bought\n" +
        "      and sold at the cashier just next to the hall.\n";
}

string
stext()
{
return
"Black Jack is played the following way:\n" + 
"The goal is to draw cards which together gives a sum of 21 points, " + 
"or as close to 21 as possible, without getting more than 21.\n" + 
"An Ace is worth 1 or 11 points, Jack, Queen and King are worth 10 points " +
"and the other cards are worth according to their value.\n"+ 
"If the player has more than 21 he is busted and he looses his bet.\n"+
"This is a short table of different things that can happen:\n"+
"(P=players sum , D = Dealers sum, BJ = BlackJack, B = Busted)\n"+
"P = BJ and D = anything but BJ => Player wins 1.5 times his bet.\n"+
"P = D = BJ,21,20 => Stand off = Player gets his bet back but wins nothing.\n"+
"P = B => Player looses his bet.\n"+
"P <=21 and D = B => Player wins as much as he betted.\n"+
"P < D and D <=21 => Player looses his bet.\n"+
"P = D and D <= 19 => Player looses his bet.\n"+
"P > D and P <= 21 => Player wins as much as he betted.\n"+
"Some details of special features of this Black Jack:\n"+
"Cards:  We use 6 decks in this Casino.\n"+
"Split:  If your first two cards are of the same value you will get the\n" +
"        option to split. If you choose to split you make a new bet as big\n" +
"        as your previous and the dealer will split your cards so that you\n" +
"        will have two separate hands.\n"+
"        If you split aces you will receive one more card on each ace.\n"+
"Double: If your first two cards gives 7 to 11 you may double your bet and\n"+
"        receive one more card.\n"+
"All commands are displayed on the small plaque on the table.\n"+
"Note: Slow play is not accepted. If you do not respond within one minute " +
"when it is your turn your hand is lost.\n" +
"Have a nice Game !\n";
}

void
create_object()
{
    int t;

    if (!IS_CLONE) return;

    set_short("A large blackjack table");
    set_long(
        "This is a blackjack table.\n"+
        "It is a large wooden table shaped as a half circle, with a green " +
        "top where " + LANG_NUM2WORD(NSLOTS) + " white colored slots are evenly " +
        "spread out. Several chairs are placed on the circular side for the players " +
        "and the dealer's place on the other side. On the side of the table there is " +
        "a small golden plaque explaining commands.\n");

//        "There are several chairs on one side of the table and a dealer on " +
 //       "the other side. There is a large sign on the table explaining the " +
  //      "rules and a small plaque explaining commands on the left side of " +
   //     "the table.\n");
    
    add_item("plaque", ptext());
    add_cmd_item("plaque", "read", ptext());

    add_item("sign", stext());
    add_cmd_item("sign", "read", stext());

    add_item("chair", "You have a hard time decide which chair to look on.\n");
    add_item("chairs", "The chairs are standard casino chairs.\n");

    set_name("table");
    add_prop(OBJ_I_NO_GET, "You can't take the table!\n");
    
    add_item("cards", "@@cards");
    
    config_default_trade();
    set_money_give_max(1000000);
    set_money_give_out(({0, 85000, 7000, 600 }));
    set_money_give_reduce(({0, 0, 0, 0}));
    set_money_accept(({0, 1, 1, 1}));

    slots = allocate(NSLOTS + 1);
    for (t = 1; t <= NSLOTS; t++)
        slots[t] = SL_CLEAR;

    dhand = ({});
    make_cards();
    shuffle();
    reset_table();
}

void
reset_table()
{
    if (!dealer)
    {
        seteuid(getuid());
        dealer = clone_object(DEALER);
        dealer->move(BJ_ROOM);
    }
}

int
help(string str)
{
    if (!str || (str != "table" && str != "black jack" && str != "view" && 
                 str != "markers"))
        return 0;

    if (str == "markers")
    {
        write("We use three types of markers here. Red, green and blue.\n" +
              "Red markers are worth one silver coin, green one gold coin " +
              "and blue one platinum coin.\n" +
              "We have an agreement not to compete with the bank's exchange " +
              "services, so you cannot buy e.g. a green marker with " +
              "anything less than a gold coin. And when sold, each green " +
              "marker pays one gold coin etc.\n");
        return 1;
    }
    
    write("Not implemented yet.\n");
    return 1;
}

void
init()
{
    ::init();
    add_action(help, "help");
    add_action(do_buy, "buy");
    add_action(do_sell, "sell");

    add_action("leave_game", "stop");
    add_action(do_stand, "stand");
    add_action(do_split, "split");
    add_action(do_draw, "draw");
    add_action(do_double, "doublebet");

    add_action(do_bet, "bet");
    add_action(do_backbet, "backbet");

    add_action("mc", "mc");

    if (TP->query_wiz_level())
        add_action(cheat, "cheat");
}

/********
 * Dealer
 ********/

void
start_game()
{
    int t, card;
    object player;
    string str;

    state = ST_PLAY;

    // Reshuffle if necessary
    if (usedcards > (NDECKS*52-60)+random(10))
    {
        shuffle();
        dealer->command("emote shuffles the cards.");
    }

    // Deal first round and initialize all hands.
    cslot = 0;
    for (t = 1; t < NSLOTS; t++)
    {
        if (sizeof(slots[t][SL_BET]) != 0)
        {
            if (cslot == 0)
                cslot = t;
            slots[t][SL_HANDS] = ({ H_CLEAR });
            // Move bets to hand
            slots[t][SL_HANDS][0][H_BET] = slots[t][SL_BET];
            slots[t][SL_HANDS][0][H_BB] = slots[t][SL_BB];
            slots[t][SL_BET] = ({});
            slots[t][SL_BB] = ({});

            // Draw one card
            card = next_card();
            slots[t][SL_HANDS][0][H_CARDS] = ({ card });

            player = slots[t][SL_PL];
            str = "The dealer puts " + query_card_name(card) +
                  " on slot " + t + ".\n";
            
            player->catch_msg("*** " + str);
            tell_room(ENV(TO), str, ({ player }));
        }
        else
        {
            // Just to be sure
            slots[t][SL_HANDS] = ({});
            slots[t][SL_BET] = ({});
            slots[t][SL_BB] = ({});
        }
    }

    if (cslot == 0)
    {
        // No player has bet
        state = ST_IDLE;
        return;
    }

    // Give one to the dealer
    card = next_card();
    dhand = ({ card });
    dvalue = evalcards(dhand);

    tell_room(ENV(TO), "+++ The dealer draws " +
              query_card_name(card) + ".\n");

    // Second round to players
    for (t = 1; t < NSLOTS; t++)
    {
        if (sizeof(slots[t][SL_HANDS]) != 0)
        {
            // Draw one card
            card = next_card();
            slots[t][SL_HANDS][0][H_CARDS] += ({ card });

            player = slots[t][SL_PL];
            str = "The dealer puts " + query_card_name(card) +
                  " on slot " + t + ".\n";
            
            player->catch_msg("*** " + str);
            tell_room(ENV(TO), str, ({ player }));
        }
    }

    // Current hand in current slot
    chand = 0;
    cplayer = 0;
    set_alarm(1.0, 0.0, next_step);
}

void
next_step()
{
    int *cards;
    int value;
    int doub, split;
    object player;
    string str1, str2;

    // Current player is deactivated by default
    cplayer = 0;

    if (cslot > NSLOTS)
    {
        set_alarm(1.0, 0.0, finalize_dealer);
        return;
    }

    // Check for a valid hand.
    if (sizeof(slots[cslot][SL_HANDS]) <= chand)
    {
        // Move to next active slot
        while (++cslot <= NSLOTS)
            if (sizeof(slots[cslot][SL_HANDS]) != 0)
                break;
        chand = 0;
        set_alarm(1.0, 0.0, next_step);
        return;
    }
    
    // Hand still active?
    while (slots[cslot][SL_HANDS][chand][H_DONE])
    {
        chand++;
        if (sizeof(slots[cslot][SL_HANDS]) <= chand)
        {
            // Move to next active slot
            while (++cslot <= NSLOTS)
                if (sizeof(slots[cslot][SL_HANDS]) != 0)
                    break;
            chand = 0;
            set_alarm(1.0, 0.0, next_step);
            return;
        }
    }

    player = slots[cslot][SL_PL];
    cards = slots[cslot][SL_HANDS][chand][H_CARDS];
    value = evalcards(cards);
    if (sizeof(cards) == 2 && value == 21 && dvalue < 10)
    {
        // Black jack, win immediately
        player->catch_msg("Black Jack!\n");
        resolve_hand(cslot, chand, 5);

        slots[cslot][SL_HANDS] =
            exclude_array(slots[cslot][SL_HANDS], chand, chand);
        set_alarm(1.0, 0.0, next_step);
        return;
    }
    
    if (value > 21)
    {
        // Busted, loose immediately
        player->catch_msg("Busted!\n");
        resolve_hand(cslot, chand, 0);

        slots[cslot][SL_HANDS] =
            exclude_array(slots[cslot][SL_HANDS], chand, chand);
        set_alarm(1.0, 0.0, next_step);
        return;
    }

    if (value == 21)
    {
        // Don't need to ask, move on
        player->catch_msg("You have 21, I assume you stand.\n");

        slots[cslot][SL_HANDS][chand][H_DONE] = 1;
        set_alarm(1.0, 0.0, next_step);
        return;
    }

    doub  = sizeof(cards) == 2 && (value >= 7 && value <= 11);
    split = sizeof(cards) == 2 && (
        query_card_value(cards[0]) == query_card_value(cards[1]));

    // Ask the player what to do

    if (doub && split)
        str2 = "Draw, stand, double or split";
    else if (doub)
        str2 = "Draw, stand or double";
    else if (split)
        str2 = "Draw, stand or split";
    else
        str2 = "Draw or stand";

    if (sizeof(slots[cslot][SL_HANDS]) == 1)
        str1 = "slot " + cslot;
    else
        str1 = "the " + LANG_WORD(chand + 1) + " hand in slot " + cslot;

    player->catch_msg("The dealer points at " + str1 + " and says:\n" +
                      "*** You have " + value +
                      (soft ? " (soft)" : "") +
                      ". " + str2 + "?\n");

    tell_room(ENV(TO),
              "The dealer points at " + str1 + " and says:\n" +
              "You have " + value + ". " + str2 + "?\n", ({ player }));

    cplayer = player;
    toid = set_alarm(30.0, 0.0, player_timeout1);
}

void
player_timeout1()
{
    object player = slots[cslot][SL_PL];

    if (!objectp(player) || !present(player, ENV(TO)))
    {
        toid = set_alarm(1.0, 0.0, player_timeout2);
        return;
    }
        
    dealer->command("say to " + OB_NAME(player) + " Hello! It's your turn!");
    toid = set_alarm(30.0, 0.0, player_timeout2);
}

void
player_timeout2()
{
    object player = slots[cslot][SL_PL], bplayer;
    int t, h, b;
    mixed bb;

    if (objectp(player))
    {
        if (present(player, ENV(TO)))
            dealer->command("say to " + OB_NAME(player) +
                            " We don't allow slow play here. You have lost.");

        // Clear up all about that player.

        for (t = 1 ; t <= NSLOTS; t++)
        {
            if (slots[t][SL_PL] == player)
            {
                for (h = 0; h < sizeof(slots[t][SL_HANDS]); h++)
                {
                    // Any back bets?
                    bb = slots[t][SL_HANDS][h][H_BB];
                    for (b = 0; b < sizeof(bb); b++)
                    {
                        bplayer = bb[b][0];
                        bplayer->catch_msg("You loose what you played " +
                                           "behind " + QTNAME(player) + 
                                           ".\n");
                    }
                }
                slots[t] = SL_CLEAR;
            }
        }
    }

    // Move to next active slot
    while (++cslot <= NSLOTS)
        if (sizeof(slots[cslot][SL_HANDS]) != 0)
            break;
    
    chand = 0;
    cplayer = 0;
    next_step();
}

void
resolve_hand(int slot, int hand, int win)
{
    object player, *others;
    string str;
    int nhands, *ret, t;

    player = slots[slot][SL_PL];

    nhands = sizeof(slots[slot][SL_HANDS]);

    str = "Slot " + slot +
          (nhands > 1 ? (" hand " + (hand+1)) : "");
    if (win == 0)
    {
        tell_room(ENV(TO), str + " loose.\n");
        return;
    }

    ret = mult_markers(slots[slot][SL_HANDS][hand][H_BET], win, 2);
    give_markers(ret, player);
    log_win(player, ret, "win " + win);
    player->catch_msg("You win " + mtext(ret) + " on " + str +
                      ".\n");
    others = ({ player });

    // Any back bets?
    for (t = 0; t < sizeof(slots[slot][SL_HANDS][hand][H_BB]); t++)
    {
        player = slots[slot][SL_HANDS][hand][H_BB][t][0];
        ret = mult_markers(slots[slot][SL_HANDS][hand][H_BB][t][1],
                           win, 2);
        give_markers(ret, player);
        log_win(player, ret, "back win " + win);
        player->catch_msg("You win " + mtext(ret) +
                          " playing behind " + str + ".\n");
        others += ({ player });
    }
    
    tell_room(ENV(TO), str + " wins.\n", others);
}

void
finalize_dealer()
{
    int slot, hand, anyhand = 0, nhands, t, cheat;
    int pvalue, dbj, pbj, *cards, win, *ret, card, ccard, *tmphand;
    object player, *others;
    string str;

    // All players are done.
    cplayer = 0;

    // Check if any hand remains.
    for (slot = 1; slot <= NSLOTS; slot++)
        if (sizeof(slots[slot][SL_HANDS]) > 0)
        {
            anyhand = 1;
            break;
        }

    if (!anyhand) {
        end_game();
        return;
    }

    if (totalbets >= (10 + random(40)) * 1728)
        cheat = 1;
    
    // Draw cards 
    while (dvalue <= 16) 
    {
        card = next_card();
        tmphand = dhand + ({ card });
        dvalue = evalcards(tmphand);
        if (cheat && dvalue > 21)
        {
            find_player("glindor")->catch_msg("BJ: Skipping card " +
                                              query_card_name(card) + "\n");
            ccard = card;
            card = next_card();
#ifdef BJ_LOG
//            write_file(BJ_LOG,
            ROKE_LOG(BJ_LOG,
                     sprintf("%s: Skip: %s (%d) %s\n",
                             ctime(time()), 
                             query_card_name(ccard), dvalue,
                             query_card_name(card)));
#endif
            tmphand = dhand + ({ card });
            dvalue = evalcards(tmphand);
            cheat = 0;
        }
        dhand = tmphand;
        tell_room(ENV(TO),
                  "The dealer draws " + query_card_name(card) + ".\n");
    }

    if (sizeof(dhand) == 2 && dvalue == 21)
    {
        str = "Dealer has Black Jack.";
        dbj = 1;
    }
    else
    {
        str = "Dealer has " + dvalue + ".";
        dbj = 0;
    }

    tell_room(ENV(TO), str + "\n");
    
    /* Set up this alarm early, in case something goes wrong below. */
    set_alarm(1.0, 0.0, end_game);
    
    // Go through all hands
    for (slot = 1; slot <= NSLOTS; slot++)
    {
        nhands = sizeof(slots[slot][SL_HANDS]);
        for (hand = 0; hand < nhands; hand++)
        {
            cards = slots[slot][SL_HANDS][hand][H_CARDS];
            pvalue = evalcards(cards);
            pbj = sizeof(cards) == 2 && pvalue == 21;

            if      (pbj && !dbj)     win = 5;
            else if (pvalue > 21)     win = 0;
            else if (dvalue > 21)     win = 4;
            else if (pbj && dbj)      win = 2;
            else if (dbj)             win = 0;
            else if (pvalue > dvalue) win = 4;
            else if (pvalue < dvalue) win = 0;
            else if (pvalue >= 20)    win = 2;
            else                      win = 0;

            resolve_hand(slot, hand, win);
        }
    }            
}

// Clean up after a game
void
end_game()
{
    int slot, hand, bhand, phand;
    
    tell_room(ENV(TO), "The dealer clears up the table.\n");

    for (slot = 1; slot <= NSLOTS; slot++)
        slots[slot][SL_HANDS] = ({});

    cplayer = 0;
    state = ST_IDLE;
    dhand = ({});
    dvalue = 0;
    totalbets = 0;

    // Check for any bets
    for (slot = 1; slot <= NSLOTS; slot++)
    {
        if (sizeof(slots[slot][SL_BET]) != 0)
        {
            poll_dealer();
            break;
        }
    }
}

void
poll_dealer()
{
    if (state == ST_PLAY) return;
    
    if (state == ST_IDLE)
    {
        state = ST_BET;
        sgid = set_alarm(7.0, 0.0, start_game);
        return;
    }

    remove_alarm(sgid);
    sgid = set_alarm(7.0, 0.0, start_game);
}

/*****************
 * Player response
 *****************/

varargs void
draw_message(object player, int card, int value, string str)
{
    string name = query_card_name(card);
    int nhands = sizeof(slots[cslot][SL_HANDS]);
    
    if (!stringp(str))
        str = "";
    
    player->catch_msg("*** You draw " + name + str +
                      ". Total is now " + value + ".\n");
    tell_room(ENV(TO), QCTNAME(player) + " draws " + name + str + ".\n" , 
              ({ player }));
}

int
do_draw(string str)
{
    int card;

    if (str && str != "")
    {
        NF("Just \"draw\"\n");
        return 0;
    }

    if (!cplayer || cplayer != TP)
    {
        NF("You are not in turn.\n");
        return 0;
    }

    card = next_card();
    slots[cslot][SL_HANDS][chand][H_CARDS] += ({ card });
    
    draw_message(TP, card,
                 evalcards(slots[cslot][SL_HANDS][chand][H_CARDS]));

    cplayer = 0;
    remove_alarm(toid);
    set_alarm(1.0, 0.0, next_step);
    return 1;
}

int
do_stand(string str)
{
    if (str && str != "")
    {
        NF("Just \"stand\"\n");
        return 0;
    }

    if (!cplayer || cplayer != TP)
    {
        NF("You are not in turn.\n");
        return 0;
    }

    slots[cslot][SL_HANDS][chand][H_DONE] = 1;

    write("You stand.\n");
    say(QCTNAME(TP) + " stands.\n");

    cplayer = 0;
    remove_alarm(toid);
    set_alarm(1.0, 0.0, next_step);
    return 1;
}

int
do_double(string str)
{
    int *cards, value, doub, *bet, card;
    mixed res;

    if (str && str != "")
    {
        NF("Just \"doublebet\"\n");
        return 0;
    }

    if (!cplayer || cplayer != TP)
    {
        NF("You are not in turn.\n");
        return 0;
    }

    cards = slots[cslot][SL_HANDS][chand][H_CARDS];
    value = evalcards(cards);
    doub  = sizeof(cards) == 2 && (value >= 7 && value <= 11);

    if (!doub)
    {
        NF("You are not allowed to double on that!\n");
        return 0;
    }

    // Check if he can afford it
    bet = slots[cslot][SL_HANDS][chand][H_BET];

    res = pay_markers2(TP, bet);
    if (res == 0)
    {
        write("You don't have enough markers to double!\n");
        return 1;
    }

    log_bet(TP, res, "double");
    slots[cslot][SL_HANDS][chand][H_BET] = add_markers(bet, res);
    
    card = next_card();
    slots[cslot][SL_HANDS][chand][H_CARDS] += ({ card });
    slots[cslot][SL_HANDS][chand][H_DONE] = 1;
    
    write("You double, betting another " + mtext(res) + ".\n");
    say(QCTNAME(TP) + " doubles.\n");
    draw_message(TP, card,
                 evalcards(slots[cslot][SL_HANDS][chand][H_CARDS]));

    cplayer = 0;
    remove_alarm(toid);
    set_alarm(1.0, 0.0, next_step);
    return 1;
}

int
do_split(string str)
{
    int *cards, value, split, *bet, card;
    mixed res;

    if (str && str != "")
    {
        NF("Just \"split\"\n");
        return 0;
    }

    if (!cplayer || cplayer != TP)
    {
        NF("You are not in turn.\n");
        return 0;
    }

    cards = slots[cslot][SL_HANDS][chand][H_CARDS];
    split = sizeof(cards) == 2 && (
        query_card_value(cards[0]) == query_card_value(cards[1]));

    if (!split)
    {
        NF("You are not allowed to split that!\n");
        return 0;
    }

    // Check if he can afford it
    bet = slots[cslot][SL_HANDS][chand][H_BET];

    res = pay_markers2(TP, bet);
    if (res == 0)
        return 0;

    log_bet(TP, res, "split");

    // Create a new hand after the current one.
    
    slots[cslot][SL_HANDS] = slots[cslot][SL_HANDS][0..chand] +
                             ({ H_CLEAR }) +
                             slots[cslot][SL_HANDS][chand+1..];
    
    slots[cslot][SL_HANDS][chand][H_CARDS] = cards[0..0];
    slots[cslot][SL_HANDS][chand+1][H_CARDS] = cards[1..1];
    slots[cslot][SL_HANDS][chand+1][H_BET] = res;

    write("You split, betting another " + mtext(res) + ".\n");
    say(QCTNAME(TP) + " splits.\n");

    value = query_card_value(cards[0]);
    
    card = next_card();
    slots[cslot][SL_HANDS][chand][H_CARDS] += ({ card });
    if (value == 11)
        slots[cslot][SL_HANDS][chand][H_DONE] = 1;
    draw_message(TP, card,
                 evalcards(slots[cslot][SL_HANDS][chand][H_CARDS]),
                 " on the first hand.");

    card = next_card();
    slots[cslot][SL_HANDS][chand+1][H_CARDS] += ({ card });
    if (value == 11)
        slots[cslot][SL_HANDS][chand+1][H_DONE] = 1;
    draw_message(TP, card,
                 evalcards(slots[cslot][SL_HANDS][chand+1][H_CARDS]),
                 " on the second hand.");

    cplayer = 0;
    remove_alarm(toid);
    set_alarm(1.0, 0.0, next_step);
    return 1;
}

/******
 * Bets
 ******/

void
bet_message(int *betcoins, int slot, int backbet, int *totcoins)
{
    string str1 = (backbet ? " behind slot " : " on slot ") + slot;
    string str2 = mtext(betcoins) + str1 + ".\n";
    
    write("You bet " + str2);
    if (sizeof(totcoins) != 0)
    {
        write("Your total bet" + str1 + " is now " + mtext(totcoins) +
              ".\n");
    }
    say(QCTNAME(this_player()) + " bets" + str1 + ".\n");
    log_bet(TP, betcoins, backbet ? "backbet" : "bet");
}

int
bet(string str, int backbet)
{
    int amount, value, prevb, payi, t, i, size;
    string what, where, ctype, name, paytype;
    string player;
    int *betcoins, *totcoins;
    int slot, freeslot, *myslots;
    object *res;
    mixed res2;

    NF("Bet what on what?\n");
    if (!str) return 0;

    if (sscanf(str, "%s on %s", what, where) != 2)
    {
        what = str;
        where = "";
    }

    if (backbet && where == "")
    {
        NF("Backbet what on what?\n");
        return 0;
    }

    slot = 0;
    if (where != "")
    {
        if (strlen(where) != 1) return 0;
        slot = atoi(where);
        if (slot < 1 || slot > NSLOTS)
        {
            NF(where + " is not a valid slot.\n");
            return 0;
        }
        if (!backbet && slots[slot][SL_PL] != 0 && slots[slot][SL_PL] != TP)
        {
            NF("That slot is not free!\n");
            return 0;
        }
        if (backbet && slots[slot][SL_PL] == 0)
        {
            NF("Noone is plating that slot.\n");
            return 0;
        }
        if (backbet && slots[slot][SL_PL] == TP)
        {
            NF("You can't bet behind yourself.\n");
            return 0;
        }
        if (sizeof(slots[slot][SL_HANDS]) != 0)
        {
            NF("You can't bet there right now.\n");
            return 0;
        }
    } 
    else
    {
        /* Find the first free slot or a slot you own. */
        freeslot = 0;
        myslots = ({});
        for (t = 1; t <= NSLOTS; t++)
        {
            if (freeslot == 0 && slots[t][SL_PL] == 0) 
                freeslot = t;
            else if (slots[t][SL_PL] == TP)
                myslots += ({ t });
        }
        if (sizeof(myslots) == 0 && freeslot == 0)
        {
            NF("There is no free slot to bet on.\n");
            return 0;
        }
        /* Are any of my hands busy? */
        for (t = 0; t < sizeof(myslots); t++)
        {
            if (sizeof(slots[myslots[t]][SL_HANDS]) != 0)
            {
                NF("You can't bet there right now.\n");
                return 0;
            }
        }
    }
    
    /* Everything is clear about the slot. Now parse and get the bet. */

    res = parse_markers_tp(what);
    if (sizeof(res) == 0)
    {
        res2 = parse_markers(what);
        if (!pointerp(res2))
        {
            NF("I don't understand how much you want to bet.\n");
            return 0;
        }
        betcoins = pay_markers(this_player(), res2[0], res2[1]);
        NF("You can't bet what you don't have.\n");
        if (!pointerp(betcoins))
            return 0;
    }
    else 
    {
        betcoins = allocate(3);
        for (t = 0; t < sizeof(res); t++)
        {
            i = member_array(res[t]->query_marker_type(), MARKER_TYPES);
            betcoins[i] += res[t]->num_heap();
            res[t]->remove_marker();
        }
    }

    /* Everything has parsed ok. */

    poll_dealer();

    if (slot != 0)
    {
        /* A specific slot */
        if (backbet)
        {
            if (!pointerp(slots[slot][SL_BB]))
                slots[slot][SL_BB] = ({});
            size = sizeof(slots[slot][SL_BB]);
            for (t = 0; t < size; t++)
            {
                if (slots[slot][SL_BB][t][0] == TP)
                {
                    slots[slot][SL_BB][t][1] = 
                        add_markers(slots[slot][SL_BB][t][1], betcoins);
                    bet_message(betcoins, slot, 1, slots[slot][SL_BB][t][1]);
                    return 1;
                }
            }

            slots[slot][SL_BB] += ({ ({ TP, betcoins }) });
            bet_message(betcoins, slot, 1, 0);
            return 1;
        }

        if (slots[slot][SL_PL] == 0)
        {
            slots[slot][SL_PL] = TP;
            slots[slot][SL_BET] = ({});
        }

        if (sizeof(slots[slot][SL_BET]) == 0)
        {
            slots[slot][SL_BET] = betcoins;
            bet_message(betcoins, slot, 0, 0);
            return 1;
        }

        slots[slot][SL_BET] = add_markers(slots[slot][SL_BET], betcoins);
        bet_message(betcoins, slot, 0, slots[slot][SL_BET]);
        return 1;
    }
    
    /* Not a specific slot */

    if (sizeof(myslots) == 0) {
        /* Bet on free slot */
        slots[freeslot][SL_PL] = TP;
        slots[freeslot][SL_BET] = betcoins;
        bet_message(betcoins, freeslot, 0, 0);
        return 1;
    }

    /* Bet on first of my slots */
    
    slot = myslots[0];

    if (sizeof(slots[slot][SL_BET]) == 0)
    {
        slots[slot][SL_BET] = betcoins;
        bet_message(betcoins, slot, 0, 0);
        return 1;
    }
    slots[slot][SL_BET] = add_markers(slots[slot][SL_BET], betcoins);
    bet_message(betcoins, slot, 0, slots[slot][SL_BET]);
    return 1;
}

int
do_bet(string str)
{
    return bet(str, 0);
}

int
do_backbet(string str)
{
    return bet(str, 1);
}

/**********
 * Checking
 **********/

/*mc = Check my cards..*/
int
mc()
{
    write(cards(TP));
    return 1;
}

/* This is a function used in the exa cards vbfc.. */
varargs string
cards(object player)
{
    int slot, hand, nhands, ncards, *cards, card;
    string *names, str;

    str = "";

    for (slot = 1; slot <= NSLOTS; slot++)
    {
        if (!objectp(slots[slot][SL_PL])) continue;
        str += "Slot " + slot + " is occupied by " +
               slots[slot][SL_PL]->query_art_name(TP) + ".\n";
    }

    if (state == ST_IDLE)
    {
        if (objectp(player))
            return "You are not playing!\n";
        else
            return "Noone is playing at the moment.\n" + str;
    }

    if (state == ST_BET)
    {
        if (objectp(player))
            return "You are not playing!\n";

        // Show what slots are occupied.
        if (str == "")
            return "Noone is playing at the moment.\n";

        return "No cards are out, but people are betting for a new round.\n" +
            str;
    }

    str = "";
    for (slot = 1; slot <= NSLOTS; slot++)
    {
        if (objectp(player) && slots[slot][SL_PL] != player) continue;
        nhands = sizeof(slots[slot][SL_HANDS]);
        for (hand = 0; hand < nhands; hand++)
        {
            str += "Slot " + slot +
                   (nhands > 1 ? (" hand " + (hand+1)) : "") +
                   (slots[slot][SL_HANDS][hand][H_DONE] ? " (finished)" : "") +
                   ":\n";
            
            cards = slots[slot][SL_HANDS][hand][H_CARDS];
            ncards = sizeof(cards);
            if (ncards == 0)
                str += "  No Cards!\n";
            else
            {
                for (card = 0; card < ncards; card++)
                    str += "  " + query_card_name(cards[card]) + "\n";
                
                str += "  Total : " + evalcards(cards) + "\n\n";
            }
        }
    }

    if (str == "")
        if (objectp(player))
            return "You are not playing!\n";
        else
            return "Noone is playing at the moment.\n";

    if (objectp(player)) 
        str = "These are your cards:\n" + str;
    else
        str = "These are the cards on the table:\n" + str;


    str += "The dealer has:\n";

    for (card = 0; card < sizeof(dhand); card++)
        str += "  " + query_card_name(dhand[card]) + "\n";
    
    str += "  Total : " + evalcards(dhand) + "\n\n";

    return str;
}

        
int
leave_game(string s)
{
    int slot, nhands, hand, anyslot = 0, t, *bet;
    object player;
    NF("Stop what? The world? Playing?\n");

    if (s != "playing")
        return 0;

    // Check for active hand
    if (state == ST_PLAY)
    {
        for (slot = 1; slot <= NSLOTS; slot++)
        {
            if (slots[slot][SL_PL] != TP) continue;
            if (sizeof(slots[slot][SL_HANDS]) > 0)
            {
                write("You have a hand in play. You can't stop now.\n");
                return 1;
            }
        }
    }
    // Look for any slots you use
    for (slot = 1; slot <= NSLOTS; slot++)
    {
        if (slots[slot][SL_PL] != TP) continue;
        anyslot = 1;
        if (sizeof(slots[slot][SL_BET]) > 0)
        {
            // Withdraw the bet
            give_markers(slots[slot][SL_BET], TP);
            log_win(TP, slots[slot][SL_BET], "withdraw leave");
            write("You withdraw your bet of " + mtext(slots[slot][SL_BET]) +
                  ".\n");
            // Withdraw any backbet
            for (t = 0; t < sizeof(slots[slot][SL_BB]); t++)
            {
                player = slots[slot][SL_BB][t][0];
                bet = slots[slot][SL_BB][t][1];
                give_markers(bet, player);
                log_win(player, bet, "withdraw back leave");
                player->catch_msg(QCTNAME(TP) + " withdrew his bet so you " +
                                  "had to withdraw your bet of " +
                                  mtext(bet) + " behind " + 
                                  TP->query_objective() + ".\n");
            }
        }
        slots[slot] = SL_CLEAR;
    }

    if (!anyslot)
    {
        write("You are not playing!\n");
        return 1;
    }

    write("You withdraw from the game.\n");
    return 1;
}
    
void
leave_room(object who)
{
    int slot, nhands, hand, anyslot = 0, t, *bet;
    object player;

    // Look for any slots used by player
    for (slot = 1; slot <= NSLOTS; slot++)
    {
        if (sizeof(slots[slot][SL_BET]) > 0)
        {
            // Withdraw any backbet
            for (t = 0; t < sizeof(slots[slot][SL_BB]); t++)
            {
                player = slots[slot][SL_BB][t][0];
                if (slots[slot][SL_PL] == who)
                {
                    bet = slots[slot][SL_BB][t][1];
                    give_markers(bet, player);
                    log_win(player, bet, "withdraw back leave");
                    player->catch_msg(QCTNAME(TP) + " withdrew " +
                                      TP->query_possessive() + " bet so you " +
                                      "had to withdraw your bet of " +
                                      mtext(bet) + " behind " + 
                                      TP->query_objective() + ".\n");
                }
                else if (player == who)
                {
                    slots[slot][SL_BB][t][0] = 0;
                    slots[slot][SL_BB][t][1] = 0;
                }
            }
        }
        if (slots[slot][SL_PL] == who)
            slots[slot] = SL_CLEAR;
    }
    if (cplayer == who)
    {
        cplayer = 0;
        remove_alarm(toid);
        set_alarm(1.0, 0.0, next_step);
    }
}

/**********************************
 * Card and deck related functions.
 **********************************/

/* Fill the pile with cards */
void
make_cards()
{
    int f,g;
    
    usedcards = 0;
    cardlist = allocate(NDECKS*52);
    for (g = 0; g < NDECKS; g++)
    {
        for (f = 0; f < 52; f++)
        {
            cardlist[f+g*52] = f+1;
        }
    }
}

int
next_card()
{
    int card;
    if (usedcards >= sizeof(cardlist))
    {
        // Cheat a bit if this happens to happen...
        return random(52) + 1;
    }

    card = cardlist[usedcards];
    usedcards++;
    return card;
}

/* Shuffle the cards */
void
shuffle()
{
    int f, x, y, tmp, size;
    usedcards = 0;
    size = sizeof(cardlist);
    
    for (f = 0; f < 3*size; f++)
    {
        x = random(size);
        y = random(size);
        tmp = cardlist[x];
        cardlist[x] = cardlist[y];
        cardlist[y] = tmp;
    }
    
    for (f = 0; f < size; f++)
    {
        x = random(size);
        tmp = cardlist[x];
        cardlist[x] = cardlist[f];
        cardlist[f] = tmp;
    }
}

string
query_card_name(int id)
{
    int i, j;
    string s;
    
    if (id == 0) return "";
    
    i = (id - 1) / 13;
    j = (id - 1) % 13 + 1;
    
    switch(j)
    {
      case 1: s = "ace";
        break;
      case 11: s = "jack";
        break;
      case 12: s = "queen";
        break;
      case 13: s = "king";
        break;
      default: s = LANG_WNUM(j);
        break;
    }
    switch(i)
    {
      case 0: s += " of hearts";
        break;
      case 1: s += " of spades";
        break;
      case 2: s += " of clubs";
        break;
      case 3: s += " of diamonds";
        break;
    }
    
    return s;
}

int
query_card_value(int id)
{
    int i, j;
    
    int value;
    
    j = (id - 1) % 13 + 1;
    
    switch(j)
    {
      case 1:
        value = 11;
        break;
      case 11:
      case 12:
      case 13:
        value = 10;
        break;
      default:
        value = j;
        break;
    }
    return value;
}

int
evalcards(int *cards)
{
    int sum = 0, ace = 0, i, val;

    for (i = 0; i < sizeof(cards); i++)
    {
        val = query_card_value(cards[i]);
        sum += val;
        if (val == 11) ace++;
    }

    while (sum > 21 && ace--) sum -= 10;
    soft = ace > 0;
    return sum;
}

/****************
 * Debug and info
 ****************/

int
cheat(string str)
{
    write("Next card is " + query_card_name(cardlist[usedcards]) + ".\n");

    return 1;
}

void
log_bet(object player, int *betcoins, string str)
{
    int value = marker_merge(betcoins);
    totalbets += value;
    if (player->query_wiz_level())
        stat_bet_wiz += value / 12;
    else
        stat_bet += value / 12;
    
#ifdef BJ_LOG
//    write_file(BJ_LOG,
    ROKE_LOG(BJ_LOG,
             sprintf("%s: %-11s bet %d : %s\n",
                     ctime(time()), 
                     capitalize(player->query_real_name()),
                     value, str));
#endif

}

void
log_win(object player, int *betcoins, string str)
{
    int value = marker_merge(betcoins);
    if (!player->query_wiz_level())
        stat_win += value / 12;

#ifdef BJ_LOG
//    write_file(BJ_LOG,
    ROKE_LOG(BJ_LOG,
             sprintf("%s: %-11s won %d : %s\n",
                     ctime(time()), 
                     capitalize(player->query_real_name()),
                     value, str));
#endif
}

mixed
query_cardlist(int ant)
{
    if (ant)
        return cardlist[ant];
    else
        return cardlist;
}

string
statistics()
{
    string s;

    s = "Money in: " + stat_bet + "\n";
    s += "In from wiz: " + stat_bet_wiz + "\n";
    s += "Money out: " + stat_win + "\n";

    if (stat_bet>stat_win)
        s += "Money won by the Casino: " + (stat_bet-stat_win) + "\n";
    else
        s += "Money lost by the Casino: " + (stat_win-stat_bet) + "\n";

    TP->catch_msg(s);
}

int
query_won_money()
{
    return stat_bet-stat_win;
}
