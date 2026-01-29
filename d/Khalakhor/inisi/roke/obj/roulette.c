/*
 * roulette.c
 *
 * Used in nyreese/cadu_casino2.c
 *
 * This was once a part of the domain Roke.
 * Cleaned up and moved into Khalakhor by Glindor, Nov 2001.
 */

#pragma save_binary
#pragma strict_types

inherit "/std/object.c";
inherit "/lib/trade.c";

#include "defs.h"
#include <stdproperties.h>
#include <macros.h>
#include <filter_funs.h>
#include <money.h>
#include <cmdparse.h>
#include <composite.h>
#include "marker_utils.h"

#define CROUPIER ROKEDIR + "npc/croupier"
//#define ROULETTE_LOG ROKEDIR + "log/roulette"
#define IS_BET(a) (member_array(a, betstr) != -1)
#define REDS ({1,3,5,7,9,12,14,16,18,19,21,23,25,27,30,32,34,36})
#define TIME 45.0
 
string *betstr;
mapping bets;
mixed *win;
mapping odds;
int open, idle, maybet, money_num;
object croupier;
int stat_bet, stat_won, *stat_utfall;
int stat_bet_wiz ,stat_won_wiz;
int alarmid;

void init_table();
void init_table2();
void start_game();
void stop_bets();
void stop_wheel();
int calcodds(string bet);

string
long()
{
    string str;
    str = "This is an ordinary roulette table. You see a small sign standing on it.\n";
    if (open)
    {
        if (!maybet)
            str += "It is open for play, but you are not allowed to place bets right now.\n";
        else
            str += "You can place your bets now.\n";
    }
    else
        str += "It seems that this roulette is closed. Too bad.\n";

    return str;
}

void
create_object()
{
    if (!IS_CLONE) return;

    set_name("table");
    add_name("roulette");
    set_adj("roulette");
  
    set_long("@@long");

    add_item("sign", 
             "It says: Try 'help roulette', 'help view' or 'help markers'.\n");
    add_cmd_item("sign", "read",
                 "Try 'help roulette', 'help view' or 'help markers'.\n");

    add_prop(OBJ_I_NO_GET, "You can't take the roulette table.\n");

    config_default_trade();
    set_money_give_max(1000000);
    set_money_give_out(({0, 85000, 7000, 600 }));
    set_money_give_reduce(({0, 0, 0, 0}));
    set_money_accept(({0, 1, 1, 1}));

    money_num = sizeof(query_money_types());

    open = idle = maybet = 0;
    bets = ([]);
    set_alarm(1.0, 0.0, init_table);

    setuid();
    seteuid(getuid()); 
}

void
view()
{
  write(
        "     r           r           r        r\n"+
        "     o           o           o        o\n"+
        "     w           w           w        w\n"+
        "     1           5           9       12\n"+
        " --------------------------------------------\n"+
        "|  | 3| 6| 9|12|15|18|21|24|27|30|33|36| col3\n"+
        "|  |--+--+--+--+--+--+--+--+--+--+--+--+-----\n"+
        "|0 | 2| 5| 8|11|14|17|20|23|26|29|32|35| col2\n"+
        "|  |--+--+--+--+--+--+--+--+--+--+--+--+-----\n"+
        "|  | 1| 4| 7|10|13|16|19|22|25|28|31|34| col1\n"+
        " --+-----------+-----------+-----------+-----\n"+
        "   |    doz1   |    doz2   |    doz3   |\n"+
        "   |----------------------------------------\n"+ 
        "   | red | black | odd | even | low | high |\n"+ 
        "   -----------------------------------------\n");
}

int
help(string str)
{
    if (!str || (str != "table" && str != "roulette" && str != "view" && 
            str != "markers"))
        return 0;

    if (str == "view")
    {
        view();
        return 1;
    }

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

    write("To bet on the roulette type : bet <amount> [marker type] on <spot> \n"+
          "<amount> is how much you want to bet\n" +
          "[marker type] is which type of markers <amount> is expressed in\n"+
          "              (default is red)\n"+
          "<spot> is what you want to bet on. Availible spots are:\n"+
          "       red, black, even, odd, high, low ;\n"+
          "       col1, col2, col3                 ; left, middle and right columns\n"+
          "       doz1, doz2, doz3                 ; 1-12, 13-24, 25-36\n"+
          "       row1, row2, ... , row12          ;\n"+
          "       row1+2, row2+3, ... , row11+12   ; to bet on double rows\n"+
          "       0, 1, 2, ..., 35, 36             ;\n"+
          "       0+2, 8+9, 23+26, etc.            ; to bet on two numbers\n"+
          "       1:4, 17:4, 32:4, etc.            ; bet on four numbers, whos upper\n"+
          "                                        ; left corner is 1, 17, 32 etc.\n"+
          "       012, 023, 0:4                    ; the combinations 0-1-2 , 0-2-3\n"+
          "                                        ; and 0-1-2-3\n");
    return 1;
}

void
init_table()
{
    int t, c, d, r;
    int *reds;
  
    reds = REDS;
    /* betstr contains all possible bets */
  
    betstr = ({ "red", "black", "odd", "even", "low", "high", "doz1", "doz2",
                "doz3", "col1", "col2", "col3" ,"012", "023", "0+1", "0+2",
                "0+3", "0:4" });
    for (t = 1; t <= 12; t++)
        betstr += ({ "row" + t });
    for (t = 1; t <= 11; t++)
        betstr += ({ "row" + t + "+" + (t+1) });
    for (t = 0; t <= 36; t++)
        betstr += ({ "" +  t });
    for (t = 1; t <= 33; t++)
        betstr += ({ t + "+" + (t+3) });
    for (t = 1; t <= 31; t += 3)
        betstr += ({ t + "+" + (t+1), (t+1) + "+" + (t+2) ,
                     t + ":4", (t+1) + ":4" });
    betstr += ({"34+35", "35+36"});

    /* win[t] says which bets win on number t */
    win = allocate(37);
    
    win[0] = ({"0", "012", "023", "0+1", "0+2", "0+3", "0:4"});
    for (t = 1; t <= 36; t++)
    {
        c = (t-1) % 3 + 1;
        d = (t-1) / 12 + 1;
        r = (t-1) / 3 + 1;
      
        win[t] = ({"" + t , "col" + c, "doz" + d , "row" + r});
        if (member_array(t, reds) != -1)
            win[t] += ({"red"});
        else
            win[t] += ({"black"});
        if (t <= 18)
            win[t] += ({"low"});
        else
            win[t] += ({"high"});
        if ((t & 1) == 1)
            win[t] += ({"odd"});
        else
            win[t] += ({"even"});
        if (t <= 33)
            win[t] += ({t + "+" + (t+3) , "row" + r + "+" + (r+1) });
        if (t > 3)
            win[t] += ({(t-3) + "+" + t , "row" + (r-1) + "+" + r });
        if (c != 3)
            win[t] += ({t + "+" + (t+1) });
        if (c != 1)
            win[t] += ({(t-1) + "+" + t });
        if (c != 3 && t <= 33)
            win[t] += ({ t + ":4"});
        if (c != 1 && t <= 33)
            win[t] += ({ (t-1) + ":4" });
        if (c != 3 && t > 3)
            win[t] += ({ (t-3) + ":4"});
        if (c != 1 && t > 3)
            win[t] += ({ (t-4) + ":4" });
    }
    win[1] += ({"012", "0+1", "0:4" });
    win[2] += ({"012", "023", "0+2", "0:4" });
    win[3] += ({"023", "0+3", "0:4" });
    set_alarm(1.0, 0.0, init_table2);
}

void
init_table2()
{
    int *a;
    a = map(betstr, calcodds);
    odds = mkmapping(betstr, a);
    stat_utfall = allocate(37);

    croupier = clone_object(CROUPIER);
    tell_room(environment(this_object()), 
              "A croupier arrives and gets ready to play.\n");

    croupier->move(environment(this_object()));
    croupier->set_table(this_object());

    open = 1;

    alarmid = set_alarm(1.0, 0.0, start_game);
}

void
notify_enter()
{
    if (!idle || !open) return;
    idle = 0;
    alarmid = set_alarm(10.0, 0.0, start_game);
}

void
stop_game(int i)
{
    remove_alarm(alarmid);
  
    if (i) 
        open = 0;
    else
        idle = 1;
    maybet = 0;
}

void
open_game()
{
    if (open) return;
    open = 1;
    idle = 0;
    alarmid = set_alarm(10.0, 0.0, start_game);
}

void
start_game()
{
    object *arr;
  
    arr = all_inventory(environment());
    arr = FILTER_PLAYERS(arr);
  
    if (!arr || !sizeof(arr))
    {
        idle = 1;
        return;
    }
  
    bets = ([]);
    if (!croupier) 
    {
        open = idle = maybet = 0;
        return;
    }
    croupier->command("say The wheel is spinning, place your bets.");
    maybet = 1;
    alarmid = set_alarm(TIME - 3.0, 0.0, stop_bets);
}

void
stop_bets()
{
    croupier->command("say No more bets!");
    maybet = 0;
    alarmid = set_alarm(3.0, 0.0, stop_wheel);
}


void
stop_wheel()
{
    int w, t, o, s, *monarr, bounce;
    mixed *winbets;
    int total;
    string col, bet, *winners;
    mapping winmap;
    mapping money;
    object obj;

    w = random(37);

    // We cheat a bit against big bets...
    // If they can afford that we can help them spending some money.
    if (mappingp(bets["cheat"]))
    {
        bounce = 0;
        for (t = 0; t < sizeof(win[w]); t++)
        {
            bet = win[w][t];
            if (bets["cheat"][bet] > (10+random(40))*1728)
            {
                bounce = 1;
                break;
            }
        }
        if (bounce)
        {
            ROKE_LOG("roulette", sprintf("%s: Bounce\n", ctime(time())));
//            write_file(ROULETTE_LOG,
//                       sprintf("%s: Bounce\n", ctime(time())));
            w = random(37);
        }
    }

    stat_utfall[w]++;

    col = "";
    money = ([]);

    if (w) 
        col = member_array(w, REDS) != -1 ? ", red" : ", black";
    croupier->command("say Number " + w + col + ".");
  
    for (t = 0; t < sizeof(win[w]); t++)
    {
        bet = win[w][t];
        winmap = bets[bet];
        if (!winmap || !mappingp(winmap))
            continue;
        winners = m_indexes(winmap);
        winbets = m_values(winmap);
        if (winners && sizeof(winners))
        {
            o = odds[bet];
            for (s = 0; s < sizeof(winners); s++)
            {
                monarr = mult_markers(winbets[s], o);
                if (money[winners[s]])
                {
                    monarr = add_markers(monarr, money[winners[s]]);
                }
                money[winners[s]] = monarr;
            }
        }
    }
    
    winners = m_indexes(money);
    winbets = m_values(money);
    for (t = 0; t < sizeof(winners); t++)
    {
        obj = find_player(winners[t]);
        if (!objectp(obj)) continue;
        monarr = winbets[t];
        give_markers(monarr, obj);
        if (obj->query_wiz_level())
            stat_won_wiz += marker_merge(monarr)/12;
        else
            stat_won += marker_merge(monarr)/12;

        obj->catch_msg("You win " + mtext(monarr) + ".\n");
        
        total = marker_merge(monarr);
        if (total >= 1728)
        {
//            write_file(ROULETTE_LOG,
            ROKE_LOG("roulette",
                     sprintf("%s: %-11s won %4d plats\n",
                             ctime(time()), 
                             capitalize(obj->query_real_name()),
                             (total / 1728) ));
        }
    }

    alarmid = set_alarm(5.0, 0.0, start_game);
}
  
int
calcodds(string bet)
{
  int a,b;
  
  if (member_array(bet, ({"red", "black", "odd", "even", "low", "high" }))
      != -1 )
      return 2;
  if (member_array(bet, ({"doz1", "doz2", "doz3", "col1", "col2", "col3"}))
      != -1)
      return 3;
  if (bet == "012" || bet == "023")
      return 11;

  if (sscanf(bet, "row%d+%d", a, b) == 2)
      return 5;
  if (extract(bet, 0, 2) == "row")
      return 11;
  if (sscanf(bet, "%d+%d", a, b) == 2)
      return 17;
  if (sscanf(bet, "%d:%d", a, b) == 2)
      return 8;
  return 35;
}

int
do_bet(string str)
{
    int amount, value, totvalue, prevb, payi, t, i;
    string what, where, ctype, name, paytype;
    int *betcoins, *totcoins;
    object *res;
    mixed res2;

    NF("The roulette is closed.\n");
    if (!open) return 0;

    NF("You are not allowed to bet right now.\n");
    if (!maybet) return 0;

    NF("Bet what on what?\n");
    if (!str) return 0;

    if (sscanf(str, "%s on %s", what, where) != 2)
        return 0;

    if (!IS_BET(where)) 
    {
        NF("I don't understand what you want to bet on.\n");
        return 0;
    }

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

    name = this_player()->query_real_name();
  
    if (mappingp(bets[where]) && pointerp(bets[where][name]))
    {
        totcoins = add_markers(betcoins, bets[where][name]);
        prevb = 1;
    }
    else
        totcoins = betcoins;

    if (mappingp(bets[where]))
    {
        if (bets[where][name])
            bets[where][name] = totcoins;
        else
            bets[where] = bets[where] + ([name: totcoins]);
    }
    else
        bets = bets + ([ where : ([name: totcoins])]);

    value = marker_merge(betcoins);
    totvalue = marker_merge(totcoins);
    
    // Note places where big bets are made
    if (totvalue >= 10 * 1728)
    {
        if (mappingp(bets["cheat"]))
        {
            bets["cheat"][where] += totvalue;
        }
        else
            bets = bets + ([ "cheat" : ([where : totvalue]) ]);
    }

    if (this_player()->query_wiz_level())
        stat_bet_wiz += value / 12;
    else
        stat_bet += value / 12;

    write("You bet " + mtext(betcoins) + " on: " + where + ".\n");
    if (prevb)
    {
        write("Your total bet on " + where + " is now " + mtext(totcoins) +
              ".\n");
    }
    say(QCTNAME(this_player()) + " bets on: "+ where +".\n");

    if (value >= 1728)
    {
//        write_file(ROULETTE_LOG,
        ROKE_LOG("roulette",
                 sprintf("%s: %-11s bet %4d plats\n",
                         ctime(time()), 
                         capitalize(this_player()->query_real_name()),
                         (value / 1728) ));
    }
    return 1;
}


/* functions for debugging purposes */

int
statistics(string str)
{
    int max,min,i;

    if (str && str != "utfall") return 0;

    if (!TP->query_wiz_level()) return 0;
    if (str == "utfall")
    {
        min = 100000; max = 0;
        for(i = 0; i < 37; i++)
        {
            if (max < stat_utfall[i]) max = stat_utfall[i];
            if (min > stat_utfall[i]) min = stat_utfall[i];
            write("" + i + " : " + stat_utfall[i] + "\n");
        }
        write("max: " + max + "    min: " + min + "\n");
    }
    else
        write("Statistics of the roulette table:\n" +
              "Mortals have bet " + stat_bet + " silver and won " + stat_won + "  => " + ((stat_bet - stat_won) / 144) + " p.\n" +
              "Wizards have bet " + stat_bet_wiz + " silver and won " + stat_won_wiz + "  => " + ((stat_bet_wiz - stat_won_wiz) / 144) + " p.\n");
    return 1;
}

mixed
query_odds(mixed apa)
{
  if (!apa)
      return odds;
  else
      return odds[apa];
}

mixed
query_bets(mixed apa)
{
    if (!apa)
        return bets;
    else
        return bets[apa];
}

mixed
query_betstr(mixed apa)
{
    if (!apa)
        return betstr;
    else
        return betstr[apa];
}

mixed
query_win(mixed apa)
{
    if (!apa)
        return win;
    else
        return win[apa];
}

void
init()
{
    ::init();
    add_action(help, "help");
    add_action(do_bet, "bet");
    add_action(do_buy, "buy");
    add_action(do_sell, "sell");
    add_action(statistics, "rstats");
}
