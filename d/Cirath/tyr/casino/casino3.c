/* casino3.c: Casino blackjack table. Serpine - 08/23/97 */
 
#pragma strict_types
 
inherit "/std/room";
inherit "/lib/trade";
 
#include "/sys/money.h"
#include "defs.h"
#include "/d/Cirath/common/mobber.h"
 
void
reset_room()
{
    bring_room_mob("crowd", TYR_NPC+"csno_mob.c", 1);
}

#define BJ_LOG (TYR_CASINO+"blckjack.log")
#define WRITE_LOG(f, o, t)   write_file(f, sprintf("%-52s (%s)\n", \
                             capitalize(o->query_real_name()) + " " + \
                             t, ctime(time())))
#define BASECARDS ({"Ace of Spades","Two of Spades","Three of Spades",\
                    "Four of Spades","Five of Spades","Six of Spades",\
                    "Seven of Spades","Eight of Spades","Nine of Spades",\
                    "Ten of Spades","Jack of Spades","Queen of Spades",\
                    "King of Spades","Ace of Diamonds","Two of Diamonds",\
                    "Three of Diamonds","Four of Diamonds",\
                    "Five of Diamonds","Six of Diamonds",\
                    "Seven of Diamonds","Eight of Diamonds",\
                    "Nine of Diamonds","Ten of Diamonds",\
                    "Jack of Diamonds","Queen of Diamonds",\
                    "King of Diamonds","Ace of Clubs","Two of Clubs",\
                    "Three of Clubs","Four of Clubs","Five of Clubs",\
                    "Six of Clubs","Seven of Clubs","Eight of Clubs",\
                    "Nine of Clubs","Ten of Clubs","Jack of Clubs",\
                    "Queen of Clubs","King of Clubs","Ace of Hearts",\
                    "Two of Hearts","Three of Hearts","Four of Hearts",\
                    "Five of Hearts","Six of Hearts","Seven of Hearts",\
                    "Eight of Hearts","Nine of Hearts","Ten of Hearts",\
                    "Jack of Hearts","Queen of Hearts","King of Hearts"})
 
string *deck=BASECARDS;
string *handplayer=({});
string *handdealer=({});
object cardplayer;
int slot;
int betsize;
int dealeracting=0;
int gamestarttime;
string bettype;
 
void
create_room()
{
    ::create_room();
    set_short("the Cystal Spider's Blackjack Room");
    set_long("This cramped chamber is dark with smoke and strangely "
            +"silent. Though filled with gamblers of all types and "
            +"social standing, the only sounds that can be heard are the "
            +"rustling of stiffened hide cards and the occasional "
            +"scraping of coins on the tables. All attention is focused "
            +"on the dealers and the potential to win enough to buy some "
            +"precious commodity like food or water, or to die pennyless "
            +"and empty in some alley.  Do you wish to make a <bet>?\n");
 
    add_item(({"dealer","dealers","mul","half-elf","muls","half-elves"}),
             "Oddly all the dealers seem to be half-breeds, mostly muls "
            +"and half-elves. They appear capable of far more damage "
            +"then their card-shuffling would indicate.\n");
    add_item(({"smoke","herbs","odd herbs"}),
             "Some patrons smoke odd herbs, some rather pungent.\n");
    add_item(({"card","hide card","hide cards","cards","stiffened hide cards"}),
             "Paper is to expensive to waste on playing cards.\n");
 
    INSIDE
    add_exit(TYR_CASINO+"casino2.c","south",0,1,0);
 
  reset_room();
}
 
mixed return_deck() { return deck; }
mixed return_handp() { return handplayer; }
mixed return_handd() { return handdealer; }
int dealer_in_motion() { return dealeracting; }
 
int
check()
{
    if (!(this_player()==cardplayer))
    {
        NF("You aren't playing!\n");
        return 0;
    }
 
    say(QCTNAME(cardplayer)+" stares at the cards.\n\n");
    cardplayer->catch_msg("Your cards are: "+implode(return_handp(),", ")+".\n");
    if (sizeof(return_handd())<2) return 1;
    cardplayer->catch_msg("The dealer's show card is: "+return_handd()[1]+".\n");
 
    return 1;
}
 
void
reshuffle()
{
    cardplayer->catch_msg("Spotting the burned card, the "+deck[0]+", the "
                     +"dealer smiles at you ominously and shuffles "
                     +"the remaining ones.\n"
                     +"The dealer burns a card and stacks the rest "
                     +"on top of it.\n");
 
    say ("Spotting the burned card, the "+deck[0]+", the dealer facing "
                     +QCTNAME(cardplayer)+" shuffles the remaining ones.\n"
                     +"This dealer then burns a card and stacks the rest "
                     +"on top of it.\n");
 
    deck=(((BASECARDS)-handplayer)-handdealer);
}
 
string
pull()
{
    int cards=sizeof(deck);
    string pulled=deck[random(cards)];
 
    deck=deck-({pulled});
 
    cardplayer->catch_msg("Your dealer pulls a card from the deck.\n");
    say("The dealer facing "+QCTNAME(cardplayer)+" pulls a card "
       +"from the deck.\n");
 
    if (sizeof(deck)<2) 
    {
        reshuffle();
        deck=deck-({pulled});
    }
 
    return pulled;
}
 
int
getscore(string *handtest)
{
    int score=0;
    int hasace=0;
    int index=0;
    string curcard;
 
    for (index=0; index<sizeof(handtest); index++)
    {
        curcard=extract(handtest[index],0,2);
        switch (curcard)
        {
            case "Ace": hasace=1; score=score+1; break;
            case "Two": score=score+2; break;         
            case "Thr": score=score+3; break;         
            case "Fou": score=score+4; break;         
            case "Fiv": score=score+5; break;         
            case "Six": score=score+6; break;         
            case "Sev": score=score+7; break;         
            case "Eig": score=score+8; break;         
            case "Nin": score=score+9; break;         
            case "Ten": score=score+10; break;         
            case "Jac": score=score+10; break;         
            case "Que": score=score+10; break;         
            case "Kin": score=score+10; break;
            default: break;         
        }
    }
    
    if (hasace==1)
    {
        if ((score+10)<22) { return (score+10); }
    }
 
    return score;
}
 
int return_scorp() { return getscore(handplayer); }
int return_scord() { return getscore(handdealer); }
 
void
wake_dealer() { dealeracting=0; }

void
go_now()
{
    cardplayer->catch_msg("You feel that you can now <hit>, <check>, "
        +"<stand>, <fold>, or <double>.\n");
}
 
void
give_card(int drawer,int up)
{
    string visible="face-down";
    string grabbed=pull();
 
    if (up) { visible="face-up"; }
    
    if (drawer==0) 
    {
        handdealer=handdealer+({grabbed});        
        if (!up) { grabbed="card"; }
        cardplayer->catch_msg("Your dealer takes the "+grabbed+" and puts "
                             +"it "+visible+".\n\n");
        say("The dealer in front of "+QCTNAME(cardplayer)+" takes the "
                             +grabbed+" and puts it "+visible+".\n\n");
        return;
    }
 
    handplayer=handplayer+({grabbed});
    cardplayer->catch_msg("Your dealer gives you the "+grabbed+" and puts "
                         +"it "+visible+".\n\n");
    if (!up) { grabbed="card"; }
    say("A dealer gives "+QCTNAME(cardplayer)+" the "+grabbed
                         +" and puts it "+visible+".\n\n");
}
 
int
hit()
{
    if (dealeracting)
    {
        NF("The dealer is somewhat busy at the moment.\n");
        return 0;
    }
 
    if (!(this_player()==cardplayer))
    {
        NF("You aren't playing!\n");
        return 0;
    }
 
    if (getscore(handplayer)>21)
    {
        cardplayer->catch_msg("You have a "+getscore(handplayer)+". "
                  +"Admit you've lost and move on.\n");
        return 1;
    }
 
    dealeracting=1;
    say(QCTNAME(cardplayer)+" requests another hit.\n\n");
    
    set_alarm(2.0, 0.0, &give_card(1,0));
    set_alarm(3.0, 0.0, &go_now());
    set_alarm(4.0, 0.0, &wake_dealer());
 
    return 1;
}
 
int
fold()
{
    if (dealeracting)
    {
        NF("The dealer is somewhat busy at the moment.\n");
        return 0;
    }
 
    if (!(this_player()==cardplayer))
    {
        NF("You aren't playing!\n");
    }
 
    say(QCTNAME(cardplayer)+" throws "+HIS_HER(cardplayer)+" cards on "
          +"the table in frustration.\n\n");
    cardplayer->catch_msg("You throw down your cards.\n\n");
    WRITE_LOG(BJ_LOG, cardplayer, ": Looses via fold");
 
    cardplayer=0;
 
    return 1;
}
 
int
stand()
{
    if (dealeracting)
    {
        NF("The dealer is somewhat busy at the moment.\n");
        return 0;
    }
 
    if (!(this_player()==cardplayer))
    {
        NF("You aren't playing!\n");
    }
 
    if (getscore(handplayer)>21)
    {
        cardplayer->catch_msg("A "+getscore(handplayer)+"?  You "
                  +"busted!\n");
        WRITE_LOG(BJ_LOG, cardplayer, ": Looses via bust, ignore next fold");
        fold();
        return 1;
    }
 
    dealeracting=1;
    tell_room(this_object(), "The dealer reveals the "+handdealer[0]
              +" and the "+handdealer[1]+".\n\n");
 
    while(getscore(handdealer)<17)
    {
        give_card(0,1);
    }
 
    if (getscore(handdealer)>21)
    {
        tell_room(this_object(), "The dealer busted!\n\n");
        say(QCTNAME(cardplayer)+" has won!\n\n");
        cardplayer->catch_msg("You've won!\n\n");
        MONEY_MOVE(2*betsize,bettype,0,this_player());
        WRITE_LOG(BJ_LOG, cardplayer, ": Gets "+(2*betsize)+" "+bettype+" via dealer bust");
 
        cardplayer=0;
        return 1;
    }
 
    if (getscore(handplayer)>getscore(handdealer))
    {
        cardplayer->catch_msg("You outscored the dealer!\n\n");
        say(QCTNAME(cardplayer)+" has won!\n\n");
        cardplayer->catch_msg("You've won!\n\n");
        MONEY_MOVE(2*betsize,bettype,0,this_player());
        WRITE_LOG(BJ_LOG, cardplayer, ": Gets "+(2*betsize)+" "+bettype+" via score");
 
        cardplayer=0;
        return 1;
    }
 
    cardplayer->catch_msg("You didn't outscore the dealer.\n\n");
    say(QCTNAME(cardplayer)+" has lost!\n\n");
    cardplayer->catch_msg("You've lost!\n\n");
    WRITE_LOG(BJ_LOG, cardplayer, ": Looses via score");
 
    cardplayer=0;
 
    return 1;
}
 
int
double()
{
    if (sizeof(handplayer)>2)
    {
        NF("You already took a hit.\n");
        return 0;
    }
 
    if (getscore(handplayer)<10)
    {
        NF("You must have 10 or 11 points to double.\n");
        return 0;
    }
    if (getscore(handplayer)>11)
    {
        NF("You must have 10 or 11 points to double.\n");
        return 0;
    }
 
    NF("You don't have enough to pay.\n");
    if ((MONEY_COINS(this_player()))[slot]==0) { return 0; };
    MONEY_MOVE(1,bettype,this_player(),0);
    WRITE_LOG(BJ_LOG, cardplayer, ": Bets a second "+bettype);
 
    betsize=2;
 
    give_card(1,1);
 
    stand();
 
    return 1;
}
 
void
firsthand()
{
    dealeracting=1;
    tell_room(this_object(), "A dealer smiles.\n");
 
    cardplayer->catch_msg("The dealer says: "
                         +"The game will last no more then five minutes, "
                         +"and hopefully you know the <rules>.\n"
                         +"We shall begin now.\n\n");
    
    set_alarm(2.0, 0.0, &give_card(1,0));
    set_alarm(4.0, 0.0, &give_card(0,0));
    set_alarm(6.0, 0.0, &give_card(1,0));
    set_alarm(8.0, 0.0, &give_card(0,1));
    set_alarm(9.0, 0.0, &go_now());
    set_alarm(10.0, 0.0, &wake_dealer());
}
 
int
play(string betwhat)
{
    mixed result;
    int price;
 
    if (cardplayer)
    {
        if ((time()-gamestarttime)<300)
        {
            NF ("There are no free dealers. Try again in a moment.\n");
            return 0;
        }
    }
 
    switch (betwhat)
    {
        case "a copper": bettype="copper"; slot=0; break; 
        case "a silver": bettype="silver"; slot=1; break; 
        case "a gold": bettype="gold"; slot=2; break;
        case "a platinum": bettype="platinum"; slot=3; break; 
        default: NF("Try 'bet a <type of coin>'.\n"); return 0;
    }
 
    NF("You don't have enough to pay.\n");
    if ((MONEY_COINS(this_player()))[slot]==0) { return 0; };
    MONEY_MOVE(1,bettype,this_player(),0);
 
    cardplayer=this_player();
    handplayer=({});
    handdealer=({});
    betsize=1;
    WRITE_LOG(BJ_LOG, cardplayer, ": Bets a "+bettype+" to begin");
    dealeracting=1;
    gamestarttime=time();
 
    firsthand();
 
    return 1;
}
 
int
rules()
{
    this_player()->catch_msg("The object is to get as close to "
        +"twenty one without going over as possible (and be closer then "
        +"the dealer). Cards are worth their face value, with kings, "
        +"queens, and jacks worth ten. The ace is worth either 1 or 11, "
        +"whichever is better for you. If you are unhappy with your "
        +"current total, you can ask for a <hit> of another card, or can "
        +"<stand> when you feel you have a game winning hand.  If you "
        +"have ten or eleven points you can <double> your bet, after "
        +"which you automatically take a hit and stand with those "
        +"cards.  If you feel doomed you can <fold>, and if you are "
        +"forget what's happening you can <check> the cards.\n");
    return 1;
}
 
void
init()
{
    ::init();
    add_action("check", "check");
    add_action("play", "bet");
    add_action("hit", "hit");
    add_action("stand", "stand");
    add_action("fold", "fold");
    add_action("double", "double");
    add_action("rules", "rules");
}
