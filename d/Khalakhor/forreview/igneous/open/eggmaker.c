/*
 * This object may be used to offer an egg to all players in the game for
 * Easter.  Taken from Mercade's Beer giver, stolen pretty much lock,
 * stock and barrel by Dunstable.
 */

inherit "/std/object";

#define NF(x) notify_fail(x)
#define TO this_object()
#define ENV(x) environment(x)
#define TP this_player()
#define CAP(x) capitalize(x)
#define BSN(x) break_string(x,75) + "\n"
#define EGG "/d/Shire/private/old_wiz/dunstable/open/egg"


void
create_object()
{
    set_name("tool");
    add_adj("easter");
    set_short("celebration tool");
    set_long(BSN("You can give everyone in the game an egg with the command " +
        "<eggall>   Don't be stingy with the eggs, now!"));
}

void
init()
{
    ::init();

    if (TP->query_wiz_level())
    {
        add_action("do_egg", "eggall");
    }

    return;
}

int
do_egg()
{
    object *players;
    object egg;
    int i;

    players = users();
    setuid();
    seteuid(getuid(TO));

    for (i = 0; i < sizeof(players); i ++)
    {
        egg = clone_object(EGG);
        players[i]->catch_msg(BSN("A fuzzy bunny rabbit hops up next to you. "
+
            "The bunny wrinkles her nose a bit before holding out a basket "+
            "full of brightly-colored eggs.\n" +
            "The bunny rabbit offers you an egg.\n"));
        if(egg->move(players[i]))
        {
            players[i]->catch_msg("For some reason you aren't able to accept "
+
                "it though.\n");
            write(players[i]->query_name() + " didn't get an egg.\n");
        }
        else
        {
            players[i]->catch_msg("You happily accept the offered egg.\n");
            write(players[i]->query_name() + " took an egg.\n");
        }
    }


    return 1;
}

