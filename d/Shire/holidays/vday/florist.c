/*
 * This object gives out a dozen roses to playes online for Valentines Day.
 * This is based on the easter bunny that was coded by Dunstable, who 
 * took the code from an object of Mercade.
 * -- Finwe, February 2001
 *
 */

inherit "/std/object";

#define NF(x) notify_fail(x)
#define TO this_object()
#define ENV(x) environment(x)
#define TP this_player()
#define CAP(x) capitalize(x)
#define BSN(x) break_string(x,75) + "\n"
#define ROSES "/d/Shire/holidays/rose_bouquet"


void
create_object()
{
    set_name("florist");
    add_name("florist");
    add_adj("valentine's day");
    set_short("florist");
    set_long("With this command, <giveroses>, you can give " +
        "everyone logged in the game a dozen roses for " +
        "Valentines Day.\n");

}

void
init()
{
    ::init();

    if (TP->query_wiz_level())
    {
        add_action("do_roses", "giveroses");
    }

    return;
}

int
do_roses()
{
    object *players;
    object roses;
    int i;

    players = users();
    setuid();
    seteuid(getuid(TO));

    for (i = 0; i < sizeof(players); i ++)
    {
        roses = clone_object(ROSES);
        players[i]->catch_msg(BSN("A friendly florist is giving " +
            "out roses today to celebrate Valentine's Day!\n" +
            "The florist offers you a dozen roses.\n"));
        if(roses->move(players[i]))
        {
            players[i]->catch_msg("For some reason you can't accept the roses.\n");
            write(players[i]->query_name() + " didn't get any roses.\n");
        }
        else
        {
            players[i]->catch_msg("You happily accept the roses.\n");
            write(players[i]->query_name() + " got a dozen roses.\n");
        }
    }


    return 1;
}

