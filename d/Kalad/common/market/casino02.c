/* Casino with blackjack table, by Sarr */

inherit "/d/Kalad/room_std";

#include "/d/Kalad/defs.h"
string *type = ({"hearts\n","spades\n","clubs\n","diamonds\n"});
mapping *kindm = 
(["Two":2,"Three":3,"Four":4,"Five":5,"Six":6,"Seven":7,"Eight":8,"Nine":9,
"Ten":10,"Jack":10,"Queen":10,"King":10,"Ace":11]);
string *kind = 
({"Two","Three","Four","Five","Six","Seven","Eight","Nine","Ten","Jack","Queen","King","Ace"});
string *pran;
string *dran;
string *parr;
string *darr;
object player;
int ace = 0;
int curgame = 0;
int t;
create_room()
{
   INSIDE;
   set_short("Inside Guido's Gaming Palace");
   set_long("Inside Guido's Gaming Palace.\n"+
            "There is a blackjack table here with a sign on it.\n");
   add_item("sign","Its a nice sign.\n");
   add_cmd_item("sign","read","@@sign");
   add_prop(MRKT_IN_NO_HEAR,1);
   add_exit(MRKT_PATH(casino01), "east");
   add_exit(MRKT_PATH(casino03), "north");
   set_alarm(1.0, 0.0, "load_ob");
}
load_ob()
{
    object obj;
    if(!obj)
    {
       obj = clone_object("/d/Kalad/common/market/npc/bjdealer.c");
       obj -> move_living("arrives",TO);
    }
}
init()
{
   ::init();
   add_action("bjtable","check");
   add_action("bjhit","hit");
   add_action("bjstay","stay");
   add_action("bjgame","play");
}
int
check_sum_player()
{
    int sum = 0;
    int i;
    for(i=0;i<sizeof(pran);i++)
    sum = kindm[pran[i]] + sum;
    if(sum == 21)
        return 1;
    if(sum > 21)
        {
            if((member_array("Ace", pran) >= 0) && (sum < 32))
               {
                    write("You got an ace.\n");
                    return 3;
               }
        return 2;
        }
    if(sum < 21)
        return 0;
}  
int
check_sum_dealer()
{

    int sum = 0;
    int i;
    for(i=0;i<sizeof(dran);i++)
    sum = kindm[dran[i]] + sum;
    if(sum == 21)
        return 1;
    if(sum > 21)
        {
            if((member_array("Ace", dran) >= 0) && (sum < 32))
            {
                ace = 1;
                write("The dealer got an ace.\n");
                if((sum - 10) < 17)
                return 0;
                return 3;
            }
            return 2;
        }
    if((sum < 21) && (sum > 16))
        return 3;
    if((sum < 21) && (sum < 17))
        return 0;
}
int
check_sum_compare()
{
int dsum = 0;
int psum = 0;
    int i;
    int y;
    for(i=0;i<sizeof(dran);i++)
    dsum = kindm[dran[i]] + dsum;
    for(i=0;i<sizeof(pran);i++)
    psum = kindm[pran[i]] + psum;
    if(ace == 1)
        dsum = dsum - 10;
    if(check_sum_player() == 3)
        psum = psum - 10;
    if(psum > dsum)
        return 0;
    if(dsum > psum)
        return 1;
    if(dsum == psum)
        return 2;
}

sign()
{
   return
   "******************************************************\n"+
   "*                 Black Jack Commands                *\n"+
   "* -------------------------------------------------- *\n"+   
   "*(check rules)  - Basic rules                        *\n"+
   "*(check table)  - Check the table for cards          *\n"+
   "*(play game)    - Start a new game                   *\n"+
   "*(hit)          - Ask for another card               *\n"+
   "*(stay)         - Stay with the hand you have        *\n"+
   "*(bet) (amount) - Wager (amout) of money, eg. 100 sc *\n"+
   "******************************************************\n";
}
int
bjtable(string tab)
{
   if(tab == "rules")
      {
      write("Listing of rules.\n");
      return 1;
   }
   if(tab == "table")
      {
       if(curgame)
          {
                write("Your cards:\n");
    write("--------------------------\n");
    for (t=0;t < sizeof(parr);t++)
        write(parr[t]);
    write("--------------------------\n");
    write("Dealer's cards:\n");
    write("--------------------------\n");
    write("(down) card\n");
    for (t=1;t<sizeof(darr);t++)
        write(darr[t]);
    write("--------------------------\n");              
           }
       else
       write("No game going now.\n");
       return 1;
   }
   else
      notify_fail("Check what?\n");
   return 0;
}
int
bjhit()
{
   int i;
   if (curgame)
   {
     if(player == TP)
     {
        write("You hit.\n");
        say(QCTNAME(player) + " hits.\n");
        pran = pran + ({kind[random(13)]});
        for(i = sizeof(pran) - 1;i < sizeof(pran);i++)
        parr = parr + ({pran[i] + " of " + type[random(3)]});
        write("Your cards:\n");
        write("--------------------------\n");
        for (t=0;t < sizeof(parr);t++)
            write(parr[t]);
        write("--------------------------\n");
        write("Dealer's cards:\n");
        write("--------------------------\n");
        write("(down) card\n");
        for (t=1;t<sizeof(darr);t++)
            write(darr[t]);
        write("--------------------------\n");
        if(check_sum_player() == 2)
           {
               write("Over 21, you bust. You lose....punk.\n");
               say(QCTNAME(player) + " lost like the punk " +
               player->query_pronoun() + " is.\n");
               pran = ({});
               dran = ({});
               parr = ({});
               darr = ({});
               curgame = 0;
               ace = 0;
               return 1;
           }
           if(check_sum_player() == 3)
           {
               write("Your ace is valued at 1, or you would break.\n");
               return 1;
           }
           if(check_sum_player() == 1)
           {
               write("You got 21. And the dealer.....\n");
               if(check_sum_dealer() == 3)
           {
               write("The dealer stays.\n");
               say("The dealer stays.\n");
               write("The dealer flips over his (down) card and reveals:\n");
               write("Your cards:\n");
               write("--------------------------\n");
               for (t=0;t < sizeof(parr);t++)
                   write(parr[t]);
               write("--------------------------\n");
               write("Dealer's cards:\n");
               write("--------------------------\n");
               for (t=0;t<sizeof(darr);t++)
                   write(darr[t]);
               write("--------------------------\n");           
               if(check_sum_compare() == 0)
               {
                   write("You win this time....punk.\n");
                   say(QCTNAME(player) + " won this time, lucky punk.\n");
                   pran = ({});
                   dran = ({});
                   parr = ({});
                   darr = ({});
                   ace = 0;
                   curgame = 0;
                   return 1;
                }
               if(check_sum_compare() == 1)
               {
                   write("The dealer wins, and you lose....punk.\n");
                   say(QCTNAME(player) + " lost like the punk " +
                   player->query_pronoun() + " is.\n");
                   pran = ({});
                   dran = ({});
                   parr = ({});
                   darr = ({});
                   ace = 0;
                   curgame = 0;
                   return 1;
               }
              if(check_sum_compare() == 2)
              {
                  write("Equal...dealer wins the push, you lose....punk.\n");
                  say(QCTNAME(player) + " lost like the punk " +
                  player->query_pronoun() + " is.\n");
                  pran = ({});
                  dran = ({});
                  parr = ({});
                  darr = ({});
                  ace = 0;
                  curgame = 0;
                  return 1;
              }
        }
       if(check_sum_dealer() == 0)
       {
           while(check_sum_dealer() == 0)
           {
                
                write("The dealer hits.\n");
                say("The dealer hits.\n");
                dran = dran + ({kind[random(13)]});
                for(i = sizeof(dran) - 1;i < sizeof(dran);i++)
                darr = darr + ({dran[i] + " of " + type[random(3)]});
            }      
           if(check_sum_dealer() == 1)
           {
               write("Your cards:\n");
               write("--------------------------\n");
                   for (t=0;t < sizeof(parr);t++)
               write(parr[t]);
               write("--------------------------\n");
               write("Dealer's cards:\n");
               write("--------------------------\n");
                   for (t=0;t<sizeof(darr);t++)
               write(darr[t]);
               write("--------------------------\n");
               write("The dealer gets 21 too. You lose...punk.");
               say(QCTNAME(player) + " lost like the punk " +
               player->query_pronoun() + " is.\n");
               pran = ({});
               dran = ({});
               parr = ({});
               darr = ({});
               ace = 0;
               curgame = 0;
               return 1;
            }
           if(check_sum_dealer() == 2)
           {
               write("Your cards:\n");
               write("--------------------------\n");
                   for (t=0;t < sizeof(parr);t++)
               write(parr[t]);
               write("--------------------------\n");
               write("Dealer's cards:\n");
               write("--------------------------\n");
                   for (t=0;t<sizeof(darr);t++)
               write(darr[t]);
               write("--------------------------\n");
               write("The dealer busts. You win this time....punk.\n");
               say(QCTNAME(player) + " lost like the punk " +
               player->query_pronoun() + " is.\n");
               pran = ({});
               dran = ({});
               parr = ({});
               darr = ({});
               ace = 0;
               curgame = 0;
               return 1;
            }
           if(check_sum_dealer() == 3)
           {
               write("The dealer stays.\n");
               say("The dealer stays.\n");
               write("The dealer flips over his (down) card and reveals:\n");
               write("Your cards:\n");
               write("--------------------------\n");
               for (t=0;t < sizeof(parr);t++)
                   write(parr[t]);
               write("--------------------------\n");
               write("Dealer's cards:\n");
               write("--------------------------\n");
               for (t=0;t<sizeof(darr);t++)
                   write(darr[t]);
               write("--------------------------\n");           
               if(check_sum_compare() == 0)
               {
                   write("You win this time....punk.\n");
                   say(QCTNAME(player) + " won this time, lucky punk.\n");
                   pran = ({});
                   dran = ({});
                   parr = ({});
                   darr = ({});
                   ace = 0;
                   curgame = 0;
                   return 1;
                }
               if(check_sum_compare() == 1)
               {
                   write("The dealer wins, and you loose....punk.\n");
                   say(QCTNAME(player) + " lost like the punk " +
                   player->query_pronoun() + " is.\n");
                   pran = ({});
                   dran = ({});
                   parr = ({});
                   darr = ({});
                   ace = 0;
                   curgame = 0;
                   return 1;
               }
              if(check_sum_compare() == 2)
              {
                  write("Equal...dealer wins the push, you lose....punk.\n");
                  say(QCTNAME(player) + " lost like the punk " +
                  player->query_pronoun() + " is.\n");
                  pran = ({});
                  dran = ({});
                  parr = ({});
                  darr = ({});
                  ace = 0;
                  curgame = 0;
                  return 1;
               }
             }
           }

               return 1;
           }  
     return 1;
       }
       else
       {
       TP->catch_msg(QCTNAME(player) + " is playing a game already. Please"+ 
          " wait.\n");
          return 1;
       }
     }
     else
     {
         write("There is not game going on right now.\n");
         return 1;
     }
}
int
bjstay()
{
   if(curgame)
   {
     if(player == TP)
     {
       write("You stay.\n");
       say(QCTNAME(player) + " stays.\n");
       if(check_sum_dealer() == 3)
           {
               write("The dealer stays.\n");
               say("The dealer stays.\n");
               write("The dealer flips over his (down) card and reveals:\n");
               write("Your cards:\n");
               write("--------------------------\n");
               for (t=0;t < sizeof(parr);t++)
                   write(parr[t]);
               write("--------------------------\n");
               write("Dealer's cards:\n");
               write("--------------------------\n");
               for (t=0;t<sizeof(darr);t++)
                   write(darr[t]);
               write("--------------------------\n");           
               if(check_sum_compare() == 0)
               {
                   write("You win this time....punk.\n");
                   say(QCTNAME(player) + " won this time, lucky punk.\n");
                   pran = ({});
                   dran = ({});
                   parr = ({});
                   darr = ({});
                   ace = 0;
                   curgame = 0;
                   return 1;
                }
               if(check_sum_compare() == 1)
               {
                   write("The dealer wins, and you lose....punk.\n");
                   say(QCTNAME(player) + " lost like the punk " +
                   player->query_pronoun() + " is.\n");
                   pran = ({});
                   dran = ({});
                   parr = ({});
                   darr = ({});
                   ace = 0;
                   curgame = 0;
                   return 1;
               }
              if(check_sum_compare() == 2)
              {
                  write("Equal...dealer wins the push, you lose....punk.\n");
                  say(QCTNAME(player) + " lost like the punk " +
                  player->query_pronoun() + " is.\n");
                  pran = ({});
                  dran = ({});
                  parr = ({});
                  darr = ({});
                  ace = 0;
                  curgame = 0;
                  return 1;
              }
        }
       if(check_sum_dealer() == 0)
       {
           int i;
           while(check_sum_dealer() == 0)
           {
                
                write("The dealer hits.\n");
                say("The dealer hits.\n");
                dran = dran + ({kind[random(13)]});
                for(i = sizeof(dran) - 1;i < sizeof(dran);i++)
                darr = darr + ({dran[i] + " of " + type[random(3)]});
            }      
           if(check_sum_dealer() == 1)
           {
               write("Your cards:\n");
               write("--------------------------\n");
                   for (t=0;t < sizeof(parr);t++)
               write(parr[t]);
               write("--------------------------\n");
               write("Dealer's cards:\n");
               write("--------------------------\n");
                   for (t=0;t<sizeof(darr);t++)
               write(darr[t]);
               write("--------------------------\n");
               write("The dealer gets 21. You lose...punk.\n");
               say(QCTNAME(player) + " lost like the punk " +
               player->query_pronoun() + " is.\n");
               pran = ({});
               dran = ({});
               parr = ({});
               darr = ({});
               ace = 0;
               curgame = 0;
               return 1;
            }
           if(check_sum_dealer() == 2)
           {
               write("Your cards:\n");
               write("--------------------------\n");
                   for (t=0;t < sizeof(parr);t++)
               write(parr[t]);
               write("--------------------------\n");
               write("Dealer's cards:\n");
               write("--------------------------\n");
                   for (t=0;t<sizeof(darr);t++)
               write(darr[t]);
               write("--------------------------\n");
               write("The dealer busts. You win this time....punk.\n");
               say(QCTNAME(player) + " won this time, lucky punk.\n");
               pran = ({});
               dran = ({});
               parr = ({});
               darr = ({});
               ace = 0;
               curgame = 0;
               return 1;
            }
           if(check_sum_dealer() == 3)
           {
               write("The dealer stays.\n");
               say("The dealer stays.\n");
               write("The dealer flips over his (down) card and reveals:\n");
               write("Your cards:\n");
               write("--------------------------\n");
               for (t=0;t < sizeof(parr);t++)
                   write(parr[t]);
               write("--------------------------\n");
               write("Dealer's cards:\n");
               write("--------------------------\n");
               for (t=0;t<sizeof(darr);t++)
                   write(darr[t]);
               write("--------------------------\n");           
               if(check_sum_compare() == 0)
               {
                   write("You win this time....punk.\n");
                   say(QCTNAME(player) + " wins this time, lucky punk.\n");
                   pran = ({});
                   dran = ({});
                   parr = ({});
                   darr = ({});
                   ace = 0;
                   curgame = 0;
                   return 1;
                }
               if(check_sum_compare() == 1)
               {
                   write("The dealer wins, and you loose....punk.\n");
                   say(QCTNAME(player) + " lost like the punk " +
                   player->query_pronoun() + " is.\n");
                   pran = ({});
                   dran = ({});
                   parr = ({});
                   darr = ({});
                   ace = 0;
                   curgame = 0;
                   return 1;
               }
              if(check_sum_compare() == 2)
              {
                  write("Equal...dealer wins the push, you lose....punk.\n");
                  say(QCTNAME(player) + " lost like the punk " +
                  player->query_pronoun() + " is.\n");
                  pran = ({});
                  dran = ({});
                  parr = ({});
                  darr = ({});
                  ace = 0;
                  curgame = 0;
                  return 1;
              }
           }
       }
     }
     else
     {
        TP->catch_msg(QCTNAME(player) + " is playing a game already. Please"+
        " wait.\n");
        return 1;
     }
   }
   else
   {
       write("There is no game going on right now.\n");
       return 1;

    }
}

int
bjgame(string game)
{
   if(game != "game")
      {
      notify_fail("Play what?\n");
      return 0;
   }
   if(curgame)
   {
  write("There is a game already in session.\n");
  TP->catch_msg(QCTNAME(player) + " is playing.\n");
  return 1;
   }
  else
   {
  write("You start a new game of black jack. The dealer deals out the cards.\n");
  say(QCTNAME(TP) + " starts a new game.  The dealer deals out cards.\n");
  player = this_player();
  curgame = 1;
  pran = ({kind[random(13)]});
  pran = pran + ({kind[random(13)]});
  parr = ({pran[0] + " of "+ type[random(3)],pran[1] +" of "+ type[random(3)]});
  dran = ({kind[random(13)]});
  dran = dran + ({kind[random(13)]});
  darr = ({dran[0] + " of "+ type[random(3)],dran[1] +" of "+ type[random(3)]});
    write("Your cards:\n");
    write("--------------------------\n");
    for (t=0;t < sizeof(parr);t++)
        write(parr[t]);
    write("--------------------------\n");
    write("Dealer's cards:\n");
    write("--------------------------\n");
    write("(down) card\n");
    for (t=1;t<sizeof(darr);t++)
        write(darr[t]);
    write("--------------------------\n");
  if(check_sum_dealer() == 1)
     {
         write("The dealer got 21, you loose....punk.\n");
         say("The dealer was dealt 21. "+ QCTNAME(player) +
         " lost like the punk "+ player->query_pronoun() + " is.\n");
         pran = ({});
         dran = ({});
         parr = ({});
         darr = ({});
         ace = 0;
         curgame = 0;
      }
  if((check_sum_player() == 1) && (check_sum_dealer() != 1))
     { 
        write("You were dealt 21. You won this time....punk.\n");
        say(QCTNAME(player) + " got a natural 21 and wins...lucky punk.\n");
        pran = ({});
        dran = ({});
        parr = ({});
        darr = ({});
        ace = 0;
        curgame = 0;
      }
  return 1;
   }
}
