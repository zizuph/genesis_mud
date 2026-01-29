/*
 * bjtable.c
 *
 * Used in nyreese/cadu_casino1.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Cirath by Glindor, Jan 2000.
 */

/* This Black Jack table was coded by
   Lord Ged
   THIS CODE MAY NOY BE COPIED !!!!
*/

/*TODO
Even money (?)
Double your bet...

*/

/*BUGGAR
both busted ger vinst
"pass" vid fel tid ger error
jack+king ger ej splitchans
om alla spelare bustar, ska inte banken spela?
använd inte spelares namn om ej introducerade
konstigt meddelande vid split+vinst

Agera inte växlingskontor. Satsar man silvermynt ska man vinna silvermynt.
Jag jobbar på det i rouletten, det kan nog åtaranvändas här.

*/

#pragma save_binary
#pragma strict_types

inherit "/std/object.c";
inherit "/lib/trade.c";

#include <stdproperties.h>
#include <language.h>
#include <macros.h>
#include "defs.h"

#define LIMIT 5
#define MINBET 12
#define IDLEROUNDS 4
#define DEALER ROKEDIR + "npc/bjdealer"
#define CASINO NYREESEDIR + "cadu_casino1"

object dealer;

int cp, *cardlist, usedcards; /* CurrentPlayer    List of all the cards (312)*/

/*plist[f][0] = name [1] = bet(copper) [2] = done round? [3] Number of cards
  [4] = playerobject [5] = insurance? [6] = idlerounds..(max 3)
  [7] = split(0,1,2)0 =no 1 splitting 2 = done split
  [8] = splitcardsnum*/
mixed *plist;
mixed *pcards;

int *dcards, dcardnum, insuranceallow;
int players; /*No of players in the game */
int cardsontable; /*Cardsontable = 1(true)*/
int bets; /* bets =1 allows bets */
int split; /* split = 1 allows split*/
int money_num;

int inmoney, outmoney;

int emptyid, kickplayerid; /* alarm ids */

void empty();
void start_game();
void play_loop();
void dealer_loop();
void play();
void kick_player();
void reset_table();
void make_cards();
void shuffle();
string query_card_name(int id);
int evalcards(int *cards);
int query_card_value(int id);
int win(int pval, int dval,int bjack,int djack,int pl);
int player_in_game(object ob);

string
ptext()
{
return    
"This is a short sum of the things you can do:\n"+ 
"Enter game   : This is the way to tell the dealer that you want to play.\n"+ 
"bet <amount> : Bet money. Only silver coins and higher !\n"+ 
"               (You are allowed the bet several times for example:\n"+ 
"                bet 1 silver , bet 2 g)\n"+ 
"card         : Tell the dealer that you want another card.\n"+ 
"pass         : Tell the dealer that you are satisfied.\n"+ 
"split        : Tell the dealer that you want to split your cards.\n"+ 
"               (You will automatically have to bet the same amount on\n"+ 
"                the second set of cards.)\n"+ 
"insurance    : Insure yourself if the dealer gets a Black Jack.\n"+ 
"               (Costs half your current bet)\n"+ 
"mc           : Check your cards\n"+ 
"exa cards    : Check all the cards on the table.\n"+
"stop playing : Leave the table so that someone else can play.\n";
}

string
stext()
{
return
"Black Jack is played the following way:\n"+ 
"The goal is to draw cards which together gives a sum of 21 points, \n"+ 
"or as close to 21 as possible, without getting more than 21.\n"+ 
"An Ace is worth 1 or 11 points, Jack, Dame and King is worth 10 points and\n"+
"the other cards are worth according to their value.\n"+ 
"If the player has more than 21 he is busted and he looses his bet.\n"+
"This is a short table of different things that can happen:\n"+
"(P=players sum , D = Dealers sum, BJ = BlackJack, B = Busted)\n"+
"P = BJ and D = anything but BJ => Player wins 1.5 times his bet.\n"+
"P = D = BJ,21,20 => Stand off = Player gets his bet back but wins nothing.\n"+
"P = B => Player looses his bet.\n"+
"P <=21 and D = B => Player wins as much as he betted.\n"+
"P < D and D <=21 => Player looses his bet.\n"+
"P = D and D = 17,18,19 => Player looses his bet.\n"+
"P > D and P <= 21 => Player wins as much as he betted.\n"+
"Special features of Black Jack:\n"+
"Cards: We use 6*52 cards in this Casino.\n"+
"Split: If the players first two cards are of the same value the player\n"+
"       will get the option to split.\n"+
"       If he chooses to split he makes a new bet as big as his previous\n"+
"       and the dealer will split his cards so that the player will have\n"+
"       two separate hands. (In this Casino you can only split once!)\n"+
"Insurance: If the dealer draws an Ace the players will be able to insure\n"+
"           their bets if case the dealer gets Black Jack.\n"+
"           If the dealer gets a Black Jack and you are insured you will\n"+
"           get your bet plus the insurance fee (=half your bet) back.\n"+
"All commands are displayed on the small plaque on the table.\n"+
"Have a nice Game !\n";
}

void
create_object()
{
    int f,g;

    if (!IS_CLONE) return;

    set_short("A very nice Black Jack table");
    set_long(
"This is a Black Jack table.\n"+
"There are several chairs on one side of the table and a dealer on the\n"+
"other side. There is a large sign on the table explaining the rules and\n"+
"a small plaque explaining commands on the left side of the table.\n");
    
    add_item("plaque", ptext());
    add_cmd_item("plaque", "read", ptext());

    add_item("sign", stext());
    add_cmd_item("sign", "read", stext());

    add_item("chair", "You have a hard time decide which chair to look on.\n");
    add_item("chairs", "The chairs are standard casino chairs.\n");

    set_name("table");
    add_prop(OBJ_I_NO_GET, "You can't take the table !\n");
    
    add_item("cards", "@@cards");
    
    config_default_trade();
    
    config_default_trade();
    set_money_give_max(1000000);
    set_money_give_out(({7, 85000, 7000, 600 }));
    set_money_give_reduce(({0, 0, 0, 0}));
    set_money_accept(({0, 1, 1, 1}));
    money_num = sizeof(query_money_types());

    plist = allocate(LIMIT + 1);
    pcards = allocate(2 * LIMIT + 2);
    for (f = 0; f <= LIMIT; f++)
    {
	plist[f] = ({"Empty",0,0,0,0,0,0,0,0});
	pcards[f] = allocate(22);
	pcards[f + LIMIT + 1] = allocate(22);
	for (g = 0; g < 22; g++)
	{
	    pcards[f][g] = 0;
	    pcards[f + LIMIT + 1][g] = 0;
	}
    }
    dcards = allocate(23);
    for (f = 0; f < 23; f++)
    {
	dcards[f] = 0;
    }
    make_cards();
    shuffle();
    reset_table();
}

mixed
query_cardlist(int ant)
{
    if (ant)
        return cardlist[ant];
    else
	return cardlist;
}

void
reset_table()
{
    if (!dealer)
    {
	seteuid(getuid());
	dealer = clone_object(DEALER);
	dealer->move(CASINO);
    }
    
    emptyid = set_alarm(2.0, 0.0, empty); 
}

void
empty()
{
    if (players == 0)
    {
	dealer->command("emote plays around with the cards.");
        emptyid = set_alarm(60.0, 0.0, empty);
    }
    if (players != 0)
    {
	dealer->command("say Lets play.");
	set_alarm(1.0, 0.0, start_game);
    }
}

void
init()
{
    ::init();
    add_action("leave_game", "stop");
    add_action("join_game", "enter");
    add_action("card", "card");
    add_action("bet", "bet"); 
    add_action("split_loop", "split");
    add_action("pass", "pass");
    add_action("insurance", "insurance");
    add_action("mc", "mc");
}

/*mc = Check my cards..*/
int
mc()
{
    int f, g;
    string str;
    str = "You don't have any cards.";
    if (players)
    {
	for (f = 0; f <= LIMIT; f++)
	{
	    if (TP == plist[f][4])
	    {
		if (pcards[f][0])
		{
		    str = "You have :" + query_card_name(pcards[f][0]);
		    if (pcards[f][1])
		    {
			for (g = 1; pcards[f][g]; g++)
			{
			    str = str+","+query_card_name(pcards[f][g]);
			}
		    }
		}

		if (plist[f][7] == 1) 
		{
		    str = str+"\nYou also have:"+query_card_name(pcards[f+LIMIT+1][0]);
		    if (pcards[f+LIMIT+1][1])
		    {
			for (g = 1; pcards[f+LIMIT+1][g]; g++)
			{
			    str = str+","+query_card_name(pcards[f+LIMIT+1][g]);
			}
		    }
		}
	    }
	}
    }
    TP->catch_msg(str+"\n");
    return 1;
}

/* This is a function used in the exa cards vbfc.. */
string
cards()
{
    int f,g;
    string str;
    str = "There are no cards on the table right now.\n";
    
    if (cardsontable)
    {
	str = "These are the cards on the table:\n";
	for (f = 0; f<=LIMIT; f++)
	{
	    if (pcards[f][0])
	    {
		str = str+plist[f][0]+" has: "+query_card_name(pcards[f][0]);
		for (g = 1; pcards[f][g]; g++)
		{
		    str = str+","+query_card_name(pcards[f][g]);
		}
		str = str+".\n";
	    }

	    if (pcards[f+LIMIT+1][0])
            {
                str = str+plist[f][0]+" also has: "+
		    query_card_name(pcards[f+LIMIT+1][0]);
                for (g = 1; pcards[f+LIMIT+1][g]; g++)
                {
                    str = str+","+query_card_name(pcards[f+LIMIT+1][g]);
                }
                str = str+".\n";
            }

	    
	}
	if (dcards[0])
	{
	    str = str+"Dealer has: "+query_card_name(dcards[0]);
	    for (g = 1; dcards[g]; g++)
	    {
		str = str+","+query_card_name(dcards[g]);
	    }
	    str = str+".\n";
	}
    }
    return str;
}

/*Bet money... */	      
int
bet(string str)
{
    int f,amount;
    string what, where, ctype, name;
    

    NF("You are not allowed to bet now !\n");
    if (bets!=1) return 0;
    
    NF("You must bet something.\n");
    if (!str || str == "") return 0;

    NF("But you are not in the game !\n");
    for (f = 0; f<=LIMIT; f++)
    {
	if (plist[f][4] == TP)
	{
	    NF("Bet what ?\n");
	    if (sscanf(str,"%s",what) != 1) return 0;
	    
	    if (sscanf(what,"%d %s",amount, ctype) == 2)
	    {
		if (ctype == "platinum" || ctype == "platinum coin" ||
		    ctype == "platinum coins" || ctype == "p")
		    amount *= 144;
		else if (ctype == "gold" || ctype == "gold coin" ||
			 ctype == "gold coins" || ctype == "g")
		    amount *= 12;
		else if (ctype == "copper" || ctype == "copper coin" ||
			 ctype == "copper coins" || ctype == "c")
		{
		    write("We dont deal with copper coins here.\n");
		    return 1;
		}
		else if (ctype != "silver" && ctype != "silver coin" &&
			 ctype != "silver coins" && ctype != "s")
		{
		    NF("I don't understand how much you want to bet.\n");
		    return 0;
		}
	    }
	    else if (sscanf(what,"%d",amount) != 1)
	    {
		NF("I don't understand how much you want to bet.\n");
		return 0;
	    }
	    if (amount <= 0)
	    {
		NF("I don't understand how much you want to bet.\n");
		return 0;
	    }
	    
	    name = this_player()->query_real_name();
	    
	    if (sizeof(pay(amount * 12, this_player(), 0, 0, 0, 0, 1)) == 1)
	    {
		write("You can't afford that bet.\n");
		return 1;
	    }
	    else
	    {

	      /* LOGGING HERE */

                /*
	      if (!TP->query_wiz_level())
		ROKE_LOG("bj_bet",
			 capitalize(TP->query_real_name())+" bet "+
			 amount*12+" cc. ("+
			 ctime(time())+")\n");
                */
		inmoney+=amount*12;
	    }
	    plist[f][1] = plist[f][1]+amount*12;
	    TP->catch_msg("The dealer accepts your bet.\n");

	    return 1;
	    break;
	}
	else
	{
	    if (f == LIMIT)
	    {
		TP->catch_msg("You are not in the game !\n");
		return 1;
	    }
	}
    }
    
    
}

int
join_game(string s)
{
    int f,g;
    
    if (s!="game")
    {
	TP->catch_msg("Enter what ? Game ?\n");
	return 1;
    }

    if (players == LIMIT)
    {
	dealer->command("say Sorry the game is full, "+QCTNAME(TP));
	return 1;
    }

    for (f = 0; f <= LIMIT; f++)
    {
	if (TP == plist[f][4])
	{
	    dealer->command("say You don't need two seats "+plist[f][0]);
	    dealer->command("emote pats "+plist[f][0]);
	    return 1;
	    break;
	}
    }

    for (f = 0; f <= LIMIT; f++)
    {
	if (plist[f][0] == "Empty")
	{
	    players++;
	    plist[f][0]= capitalize(TP->query_real_name());
	    plist[f][2] = 0; /*Player may not enter the game this turn*/
	    plist[f][4] = TP;
	    plist[f][5] = 0;
	    plist[f][6] = 0; /*Player has been idle 0 turns*/
	    plist[f][7] = 0;
	    plist[f][8] = 0;
	    plist[f][1] = 0; /*No bet yet :) */

	    for (g = 0; g<22; g++)
	    {
		pcards[f][g] = 0;
		pcards[f+LIMIT+1][g] = 0;
	    }

	    plist[f][3] = 0; /*Player has got NO cards */
	    dealer->command("say Welcome "+capitalize(plist[f][0]));
	    
	    if (players == 1)
	    {
		remove_alarm(emptyid);
                set_alarm(1.0, 0.0, start_game);
	    }
	    return 1;
	    break;
	}
    }
}

void
start()
{
    int f,g,monarr,tmp;
    string message;
    dealer->command("say No more bets !");
    bets = 0; /*Block bets to table...*/
    insuranceallow = 0; /*No insurances*/

    tmp = 0;
    for (f = 0; f<=LIMIT; f++)
    {
	if (plist[f][1]) 
	{
	    tmp = 1;
	    break;
	}
    }
	
    if (tmp == 0)
    {
	/*OK We shut the game down and start again...*/
	dealer->command("say OK If noone is going to bet I am going to play myself !");
	for (f = 0; f<=LIMIT; f++)
	{
	    plist[f] = ({"Empty",0,0,0,0,0,0,0,0});
	    for (g = 0; g<22; g++)
	    {
		pcards[f][g] = 0;
		pcards[f+LIMIT+1][g] = 0;
	    }
	}
	for (f = 0; f<23; f++)
	{
	    dcards[f] = 0;
	}

	players = 0;
	emptyid = set_alarm(2.0, 0.0, empty);
	return;
    }

	
    for (f = 0; f<=LIMIT; f++)
    {
	for (g = 0; g<22; g++)
        {
	    pcards[f][g] = 0;
        }
	plist[f][3] = 0; /*Player hasnt got any cards*/
	plist[f][7] = 0;
	plist[f][8] = 0;
    }
    for (f = 0; f<22; f++)
    {
	dcards[f] = 0;
    }
    dcardnum = 0; /*Dealer hasnt got any cards */
    
    for (f = 0; f<=LIMIT; f++)
    {
	if (plist[f][1]>=12)
	{
	    message = QCTNAME(dealer)+" gives you "+
		LANG_ADDART(query_card_name(cardlist[usedcards]))+
		".\n";
	    plist[f][4]->catch_msg(message);
	    pcards[f][0] = cardlist[usedcards];
	    usedcards++;
	    plist[f][3] = 1; /*Player got 1 card */
	    plist[f][6] = 0; /*Player is not idle any more..*/
	}	
	else
	{
	    plist[f][6]++; /*Player is 'Idle' this round */
	}
    }   
    cardsontable = 1;
    dealer->command("emote gives one card to all who has a bet.");
    
/*See to it that no players are done...*/
    for (f = 0; f<=LIMIT; f++)
    {
	plist[f][2] = 0;
    }
    
/*Dra kort till dealer om dealer fick ess fr}ga om f|rs{kringar... */
    
   dealer->command("emote gives a second card to the players who made a bet.");
    dcards[0] = cardlist[usedcards++];
   dealer->command("emote draws "+LANG_ADDART(query_card_name(dcards[0]))+".");
    dcardnum = 1; /*Dealer got one card*/
    
    for (f = 0; f<=LIMIT; f++)
    {
	if (plist[f][1]>=12)
        {
	    message = QCTNAME(dealer)+" gives you "+
		LANG_ADDART(query_card_name(cardlist[usedcards]))+
		".\n";
	    plist[f][4]->catch_msg(message);
	    pcards[f][1] = cardlist[usedcards];
	    usedcards++;
	    plist[f][3] = 2; /*Player got 2 cards */
	    if (evalcards(pcards[f]) == 21)
	    {
		dealer->command("say Black Jack "+plist[f][0]+" !");
		    
		plist[f][2] = 1; /*This player is done :) */
	    }
        }       
    }   
    
    cp = 0; /*Current player 0, Kind of :)*/
    cp--;
    
    set_alarm(1.0, 0.0, play_loop);
}

void
ask_insurance()
{
    dealer->command("say I have an Ace. You have 10 seconds to insure your bet");
    insuranceallow = 1;
    set_alarm(10.0, 0.0, dealer_loop);
}

int
insurance()
{
    int f,peng;
    if (insuranceallow!=1)
    {
	TP->catch_msg("You are not allowed to insure yourself now !\n");
	return 1;
    }
    
    for (f = 0; f<=LIMIT; f++)
    {
	
	if (plist[f][4] == TP)
	{
	    if (plist[f][5] == 1)
	    {
		TP->catch_msg("You are already insured, Bummer !\n");
		return 1;
	    }
	    if (plist[f][1] == 0)
	    {
		TP->catch_msg("You have no bet to insure !\n");
		return 1;
	    }
	    peng = plist[f][1]/2;
	    if (plist[f][7]) peng = plist[f][1];
	    
	    if (sizeof(pay(peng, TP, 0, 0, 0, 0, 1)) == 1)
            {
                write("You can't afford to insure yourself.\n");
                return 1;
            }
	    else
	    {
		inmoney+=peng;
	    }
	    
	    TP->catch_msg("You are insured in case the dealer gets a Black "+
			  "Jack.\n");
	    plist[f][5] = 1;
	    return 1;
	}
    }
    
    NF("You arent in the game !\n");
}

void
play_loop()
{
    int f,tmp;
    insuranceallow = 0;
    bets = 0;
    cp++;
    if (cp<=LIMIT)
    {
	if (plist[cp][1] >=12 && plist[cp][0]!="Empty" )
	{
		/*Player in turn..*/
	    plist[cp][2] = 1;
	    plist[cp][6] = 0;
	    set_alarm(1.0, 0.0, play);
	}
	else
	{
		/*Player is idle*/
	    plist[cp][2] = 1;
	    set_alarm(1.0, 0.0, play_loop);
	}
    }
    else
    {
        if (query_card_value(dcards[0]) == 11)
	{
	    set_alarm(1.0, 0.0, ask_insurance);
	}
	else
	{
            set_alarm(1.0, 0.0, dealer_loop);
	}
    }
}

void
dealer_loop()
{
    int *monarr,bjack,djack;

    int g,f,dealerval,playerval,tmp,money,betted;
    betted = 0;
    for (f = 0; f<=LIMIT; f++)
    {
	if (plist[f][1]) 
	{
	    betted = 1;
	    break;
	}
    }
    if (betted)
    {
	for (f = 0; f<22; f++)
	{
	    if (evalcards(dcards)<17)
	    {
		dcards[dcardnum++] = cardlist[usedcards];
		dealer->command("emote draws a "+
				query_card_name(cardlist[usedcards++])+".");
		if (dealerval!=21 || dcardnum!=2)
		{
		    dealer->command("say I got "+evalcards(dcards));
		}
	    }
	}
	
    dealerval = evalcards(dcards);
	
	/*WHO WON ?*/
	
	if (dealerval>21)
	{
	    dealer->command("say I got busted");
	    /*Ge pengar till alla med bet*/
	    
	}
	djack == 0;
	if (dealerval == 21 && dcardnum == 2)
	{
	    dealer->command("say I got a Black Jack !");
	    dealer->command("emote smiles happily.");
	    djack == 1;
	}
	for (f = 0; f<=LIMIT; f++)
	{
	    bjack = 0;
	    if (plist[f][1]>=12)
	    {
		playerval = evalcards(pcards[f]);
		if (playerval == 21 && plist[f][3] == 2 && plist[f][7] == 0)
		{
		    bjack = 1;
		}
		money = win(playerval,dealerval,bjack,djack,f);
		
		if (plist[f][7] == 2 && plist[f][8])
		{
		    bjack = 0;
		    dealer->command("say "+plist[f][0]+
				    " splitted his cards so he has got "+
				    evalcards(pcards[f+LIMIT+1])+" too");
		    playerval = evalcards(pcards[f+LIMIT+1]);
		    money = money+win(playerval,dealerval,bjack,djack,f);
		}
		/* Lagg till money pa spelare...*/
		if (money)
		{
		    monarr = give(plist[f][1]*money/2,plist[f][4],0,0,0,1);
		    monarr = exclude_array(monarr, 0, money_num - 1);
		    plist[f][4]->catch_msg(QCTNAME(dealer)+" gives you "+
					   text(monarr) + ".\n");
		    /* LOGGING HERE */
                    /*		    
		    if (!plist[f][4]->query_wiz_level())
		      ROKE_LOG("bj_win",
			       capitalize(plist[f][4]->query_real_name())+
			       " got "+plist[f][1]*money/2+" cc. ("+
			       ctime(time())+")\n");
                    */
		    outmoney+=plist[f][1]*money/2;
		}
		plist[f][1] = 0;
	    }
	}
    }
    
/*Kick out idle players...*/
    for (f = 0; f<=LIMIT; f++)
    {
	if (plist[f][6]>IDLEROUNDS && plist[f][0]!="Empty")
	{
	    dealer->command("say "+plist[f][0]+" is removed from the game");
	    plist[f][0] = "Empty";
	    plist[f][1] = 0;
	    plist[f][2] = 0;
	    plist[f][3] = 0;
	    plist[f][4] = TO;
	    plist[f][5] = 0;
	    plist[f][6] = 0;
	    plist[f][7] = 0;
	    plist[f][8] = 0;
	    
	    for (g = 0; g<22; g++)
	    {
		pcards[f][g] = 0;
		pcards[f+LIMIT+1][g] = 0;
	    }

	    players--;
	}
    }
    
    dealer->command("emote collects the cards.");
    
    set_alarm(5.0, 0.0, start_game);
}

void
play()
{ 

    if (pcards[cp][0] % 13 == pcards[cp][1] % 13 && pcards[cp][2] == 0 &&
       plist[cp][7] == 0  ) 
    {
	dealer->command("say You have the option to split "+plist[cp][0]);
    }
    
    if (plist[cp][7] == 1)
    {
	if (evalcards(pcards[cp+LIMIT+1])<21)
	{
	    dealer->command("say You have "+evalcards(pcards[cp+LIMIT+1])+" "+
			    plist[cp][0]+". Card or Pass ?");
	    kickplayerid = set_alarm(60.0, 0.0, kick_player);
        }
	else
	{
	    dealer->command("say Sorry "+plist[cp][0]+" you have more than 21.");
	    plist[cp][7] = 2;/*Player has split cards once*/
	    set_alarm(1.0, 0.0, play);
	}
    }
    else
    {
	if (evalcards(pcards[cp])<21)
	{
	    dealer->command("say You have "+evalcards(pcards[cp])+" "+
			    plist[cp][0]+". Card or Pass ?");
	    kickplayerid = set_alarm(140.0, 0.0, kick_player);
	}
	else
	{
	    set_alarm(1.0, 0.0, play_loop);
	}
    }
}

int
split_loop()
{
    string pname;
    if (TP!=plist[cp][4])
    {
	TP->catch_msg("Its not your turn !\n");
	return 1;
    }
    
    if (pcards[cp][0] % 13 != pcards[cp][1] % 13 || pcards[cp][2]!=0)
    {
	dealer->command("say You can't split those cards "+plist[cp][0]);
	return 1;
    }
    if (plist[cp][7])
    {
	TP->catch_msg("You have already split your cards once !\n");
	return 1;
    }
    
    if (sizeof(pay(plist[cp][1], TP, 0, 0, 0, 0, 1)) == 1)
    {
	write("You can't afford tp split.\n");
	return 1;
    }
    else
    {
	inmoney+=plist[cp][1];
    }

	/*OK The player can split his cards...*/
    
    remove_alarm(kickplayerid);
    
    dealer->command("emote takes money from "+plist[cp][0]+".");
    
    dealer->command("emote separates the cards.");
    pcards[cp+LIMIT+1][0] = pcards[cp][1];
    pcards[cp][1] = 0;
    plist[cp][3] = 1;/*Player has got one card in each hand */
    plist[cp][8] = 1;
    plist[cp][7] = 1; /*Cards are splitted !*/
    
    set_alarm(1.0, 0.0, play);
    return 1;
}
int
card()
{
    int f,g,monarr;
    string message;
    if (cp>LIMIT)
    {
	dealer->command("say You can't get cards now !");
	return 1;
    }
    if (cp<=LIMIT)
    {
	if (TP!=plist[cp][4])
	{
	    TP->catch_msg("Its not your turn "+
			    capitalize(TP->query_real_name())+".\n");
	    return 1;
	}
	
        remove_alarm(kickplayerid);
	
	if (plist[cp][7] == 1)
	{
	    pcards[cp+LIMIT+1][plist[cp][8]++]=
		cardlist[usedcards++];/*Get card */
	    message = QCTNAME(dealer)+" gives you "+
                LANG_ADDART(query_card_name(cardlist[usedcards-1]))+
                ".\n";

	    TP->catch_msg(message);
	    say(QCTNAME(dealer)+" gives "+plist[cp][0]+" "+
		LANG_ADDART(query_card_name(cardlist[usedcards-1]))+
                ".\n");

	    
	    if (evalcards(pcards[cp+LIMIT+1])>21)
	    {
		dealer->command("say Sorry you got busted "+plist[cp][0]);
		plist[cp][8] = 0;
		plist[cp][7] = 2;
		for (f = 0; pcards[cp+LIMIT+1][f]; f++)
		{
		    pcards[cp+LIMIT+1][f] = 0;
		}

                set_alarm(1.0, 0.0, play);
	    }
	    else
	    {
		if (evalcards(pcards[cp+LIMIT+1]) == 21)
		{
		    dealer->command("say 21 "+plist[cp][0]);
		    plist[cp][7] = 2;
                    set_alarm(1.0, 0.0, play);
		}
		else
		{
                    set_alarm(1.0, 0.0, play);
		}
	    }
	}
	else
	{
	    pcards[cp][plist[cp][3]++] = cardlist[usedcards++];/*Get card */

	    message = QCTNAME(dealer)+" gives you "+
		LANG_ADDART(query_card_name(cardlist[usedcards-1]))+
                ".\n";
	    
            TP->catch_msg(message);
            say(QCTNAME(dealer)+" gives "+plist[cp][0]+" "+
                LANG_ADDART(query_card_name(cardlist[usedcards-1]))+
                ".\n");
	    
	    
	    if (evalcards(pcards[cp])>21)
	    {
		dealer->command("say Sorry you got busted "+plist[cp][0]);
		if (evalcards(pcards[cp+LIMIT+1])>21 || 
		   evalcards(pcards[cp+LIMIT+1]))
		{
		    plist[cp][1] = 0; /*This player lost both his hands*/
		}
		plist[cp][2] = 1; /* Player done */
		plist[cp][3] = 0;
		plist[cp][5] = 0;
		for (f = 0; pcards[cp][f]; f++)
		{
		    pcards[cp][f] = 0;
		}
                set_alarm(1.0, 0.0, play_loop);
	    }
	    else
	    {
		if (evalcards(pcards[cp]) == 21)
		{
		    dealer->command("say 21 "+plist[cp][0]);
		    plist[cp][2] = 1;
                    set_alarm(1.0, 0.0, play_loop);
		}
		else
		{
                    set_alarm(1.0, 0.0, play);
		}
	    }
	}
    }

    return 1;
}

int
pass()
{
    string tmp;
    remove_alarm(kickplayerid);
    
    if (TP!=plist[cp][4])
    {
	tmp = capitalize(TP->query_real_name());
	dealer->command("say As far as I know its not your turn "+tmp);
	return 1;
    }
    plist[cp][2] = 1; /*Player done*/
    TP->catch_msg("You pass.\n");
    
    if (plist[cp][7] == 1) 
    {
	plist[cp][7] = 2; /*He splitted his first set of cards*/
	plist[cp][2] = 0; /*He is not done yet... */
	cp = cp-1;        /*Let the player play his second hand too */
    }

    set_alarm(1.0, 0.0, play_loop); /*Next player...*/
    return 1;
}

void
kick_player()
{
    int f;
    if (plist[cp][0]!="Empty")
    {
	dealer->command("say Sorry but we dislike slow players here");
	dealer->command("say Ill have to throw "+plist[cp][0]+" out of the game");
	
	if (players) players--;
	if (cp>LIMIT) cp = LIMIT;
	plist[cp][0] = "Empty";
	plist[cp][1] = 0;
	plist[cp][2] = 1; /*This player is definetly done ! */
	plist[cp][3] = 0;
	plist[cp][4] = TO;
	plist[cp][5] = 0;
	plist[cp][6] = 0;
	plist[cp][7] = 0;
	plist[cp][8] = 0;
	
	for (f = 0; f<22; f++)
	{
	    pcards[cp][f] = 0;
	    pcards[cp+LIMIT+1][f] = 0;
	}
    }
    else
    {
	dealer->command("say I hate those people who just leaves !");
	dealer->command("frown");
    }
    set_alarm(1.0, 0.0, play_loop);
    
}

void
leave_room(object who)
{
    int f,pl;

    if (player_in_game(who))
    {
	for (f = 0; f<=LIMIT; f++)
	{
	    pl=-1;
	    if (TP == plist[f][4])
	    {
		pl = f;
		break;
	    }
	}
	if (pl == -1) return;

        dealer->command("say Welcome back any time "+plist[pl][0]+" !");
	plist[pl][0] = "Empty";
	plist[pl][1] = 0;
	plist[pl][2] = 0;
	plist[pl][3] = 0;
	plist[pl][4] = 0;
	plist[pl][5] = 0;
	plist[pl][6] = 0;
	plist[pl][7] = 0;
	plist[pl][8] = 0;
	
	for (f = 0; f<22; f++)
	{
	    pcards[pl][f] = 0;
	    pcards[pl+LIMIT+1][f] = 0;
	}
	
	players--;
    }
}
	
int
leave_game(string s)
{
    NF("Stop what ? The world ? \n");

    if (s == "playing")
    {
	if (player_in_game(TP))
	{
	    leave_room(TP);
	    return 1;
	}
	write("You are not in the game !\n");
	
	return 1;
    }
    return 0;
    
}
    
void
start_game()
{
    int f,g;
    cardsontable = 0;
    bets = 0;

    for (f = 0; f<=LIMIT; f++)
    {
	plist[f][1] = 0;
	
	for (g = 0; g<22; g++)
	{
	    pcards[f][g] = 0;
	    pcards[f+LIMIT+1][g] = 0;
	}
    }

    if (players)
    {
	bets = 1;
	dealer->command("say Make your bets, The game starts in 20 seconds");
	
	if (usedcards>200+random(10))
	{
	    shuffle();
	    dealer->command("emote shuffles the cards.");
	}
	
	set_alarm(15.0, 0.0, start);
    }
    else
    {
	emptyid = set_alarm(1.0, 0.0, empty);
    }
}

/*player in game returns the number of the player +1 */
/* And 0 if noone is in the game... */
int
player_in_game(object ob)
{
    int f,tmp = 0;
    
    for (f = 0; f<=LIMIT; f++)
    {
	if (ob = plist[f][4]) 
	{
	    tmp = f+1;
	    break;
	}
    }
    return tmp;
}


void
make_cards()
{
    int f,g;
    
    usedcards = 1;
    cardlist = allocate(6*52);
    for (g = 0; g<=5; g++)
    {
	for (f = 0; f<=51; f++)
	{
	    cardlist[f+g*52] = f+1;
	}
    }
}

int
win(int pval, int dval,int bjack,int djack,int pl)
{
    if (bjack && !djack) return 5; /*Me blackjack he somethin else */

    if (bjack && djack && !plist[pl][5]) return 2; /*both bjack but no ins*/

 if (dval == 21 && plist[pl][5] == 1 && !bjack) return 3; /*Ins and BLACKJACK*/
    
    if (djack && pval == 21) return 0; /*He BJ and me 21*/
    
    if (pval>dval && pval<22) return 4; /*Player wins*/
    
    if (pval<22 && dval>21) return 4;   /*Player wins*/
    
    if (dval == pval && pval>=20 && pval<22) return 2; /*Delning*/
    
}

void
shuffle()
{
    int f,x,y,tmp,size;
    usedcards = 0;
    size = sizeof(cardlist);
    
    for (f = 0; f<3*size; f++)
    {
	x = random(size);
	y = random(size);
	tmp = cardlist[x];
	cardlist[x] = cardlist[y];
	cardlist[y] = tmp;
    }
    
    for (f = 0; f<size; f++)
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
    int i,j;
    string s;
    
    if (id == 0) return "";
    
    i = (id-1) / 13;
    j = (id-1) % 13 +1;
    
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
    case 0: s = s + " of hearts";
	break;
    case 1: s = s + " of spades";
	break;
    case 2: s = s + " of clubs";
	break;
    case 3: s = s + " of diamonds";
	break;
    }
    
    return s;
}

int
query_card_value(int id)
{
    int i,j;
    
    int value;
    
    j = (id-1) % 13 +1;
    
    switch(j)
    {
	
    case 1: value = 11;
	break;
    case 11: value = 10;
	break;
    case 12: value = 10;
	break;
    case 13: value = 10;
	break;
    default: value = j;
	break;
    }
    return value;
}

int
evalcards(int *cards)
{
    int sum = 0,ess = 0,i;
    
    for (i = 0; cards[i]!=0; i++)
    {
	sum+=query_card_value(cards[i]);
	if (query_card_value(cards[i]) == 11) ess++;
    }
    
    while (ess-- && sum>21) sum-=10;
    return sum;
}

string
statistics()
{
    string s;

    s = "Money in: "+inmoney+"\n";
    s = s+ "Money out: "+outmoney+"\n";
   
    if (inmoney>outmoney)
    {
	s = s+"Money won by the Casino: "+(inmoney-outmoney)+"\n";
    }
    else
    {
	s = s+"Money lost by the Casino: "+(outmoney-inmoney)+"\n";
    }
    TP->catch_msg(s);
}

int
query_won_money()
{
    return inmoney-outmoney;
}


