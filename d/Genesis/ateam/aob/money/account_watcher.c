/*
 * This object monitors the bank accounts of players and reports
 * drastic changes, total player account balance and other things like that.
 *
 * A very drastic change is usually a sign of foul play of some sort, bug or
 * unbalanced area etc.
 *
 * This is needed in the attempts to bring the economy back under control.
 */
#include <files.h>
#include <money.h>

#define LOG         ("/d/Genesis/ateam/aob/money/changes.txt")

static mapping players = ([ ]);   /* The list of players to check */
static mapping history = ([ ]);


void update_players();
void check();

void
create()
{
    setuid();
    seteuid(getuid());

    set_alarm(0.0, 15.0, &update_players());
    set_alarm(600.0, 600.0, &check());
}

void
update_players()
{
    foreach (object ob: users()) {
        if (IS_PLAYER_OBJECT(ob)) {
            players[ob->query_real_name()] = 1;
        }
    }
}

int
query_account_value(string name)
{
    return GOG_ACCOUNTS->query_account_value(name);
}

void
check()
{
    update_players();

    foreach (string player, int foo: players) {
        int previous = history[player];
        int value = query_account_value(player);
        int delta = value - previous;

        if (previous && previous != value) {

            write_file(LOG, sprintf("%s %-13s %12d %12d %1s%s\n",
                ctime(), player, value, delta, (delta < 0 ? "-" : " "),
                MONEY_WCOL_TEXT(MONEY_SPLIT(abs(delta)), 4)));
        }

        history[player] = value;
        m_delkey(players, player);
    }
}


