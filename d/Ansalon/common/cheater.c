#include <macros.h>

#define CHEAT_ADMIN "/d/Ansalon/common/cheaters_admin"

static string text = "Away with you! We do not trade with cheaters here.";

/*
 * Function name: cheater_log
 * Description:   Log a player as a cheater (using a bug).
 * Arguments:     player - the player
 *                obj - the object that has the bug
 *                name - the name of the bug
 */
void
cheater_log(object player, object obj, string name)
{
    setuid();
    seteuid(getuid());
    log_file("cheaters",
    sprintf("%s: %s (%d) used bug '%s' in %O\n",
    extract(ctime(time()), 4),
    capitalize(player->query_real_name()),
    player->query_average_stat(),
    name,
    obj));

}

/*
 * Function name: check_cheater
 * Description:   Check if the specified player has been reported
 *                  as a cheater (and in that case, give him the
 *                  appropriate message when he tries to do commerce)
 * Arguments:     mixed player - either object or name
 *                mixed shopkeeper - either shopkeeper object or string
 *                  with word to use as shopkeeper (like "the shopkeeper"
 *                  or "Tika")
 *                int quiet - do not write anything, just check if he's a
 *                  cheater
 * Returns:       0 - not a cheater / 1 - a cheater
 */
varargs int
check_cheater(mixed player, mixed shopkeeper, int quiet)
{
    object pl;
    string sk;

    if (stringp(player))
        pl = find_player(player);
    else if (objectp(player))
        pl = player;

    if (!objectp(pl))
        return 0;

    if (stringp(shopkeeper))
        sk = shopkeeper;
    else if (objectp(shopkeeper))
        sk = shopkeeper->query_the_name(pl);

    if (!stringp(sk))
        sk = "the shopkeeper";

    /* check */
    setuid();
    seteuid(getuid());
    LOAD_ERR(CHEAT_ADMIN);
    
    if (! CHEAT_ADMIN->is_cheater(pl->query_real_name()))
        return 0;

    /* is a cheater */
    if (quiet)
        return 1;

    pl->catch_msg(capitalize(sk) + " says to you: " +
    text + "\n");

    tell_room(environment(pl),
    capitalize(sk) + " says to " + QTNAME(pl) +
    ": " + text + "\n",
    pl);

    return 1;
}
