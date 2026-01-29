/*
 * /secure/mail_checker.c
 *
 * This object can be called to check whether there is mail for a player.
 * In order to inquire whether there is mail for a certain player, you
 * can make the following call:
 *
 * int new_mail = "/secure/mail_checker"->query_mail();
 *
 * The result of this query can be one of the following integer values:
 *
 *  0   - there is no mail at all for the player
 *  1   - there is mail for the player, though all read
 *  2   - there is new mail for the player
 *  3   - there is unread mail for the player, but there is no new mail
 *
 * The function assumes this_player() if no argument is given, though
 * if an argument is given, that object is used to check.
 *
 * Revision history:
 * /Mercade, June 22 1994, adapted to the new mailreader.
 */

#pragma no_clone     /* no messing with this object  */
#pragma no_inherit   /* no messing with this object  */
#pragma save_binary  /* quick loading after a reboot */
#pragma strict_types /* you should always be tidy    */

inherit "/std/object";

#include <std.h>

/*
 * Technical information:
 *
 * Mail is saved in a mapping structure now. The indices of the mapping
 * are strings containing the variable-names and the values are the
 * actual values of those variables. The mail-files of the players are
 * arranged in a series of subdirectories, each starting with the first
 * letter of the name of the player, just like the player-files.
 * MAIL_NEW_MAIL is the index to the variable that contains the
 * new-mail-flag.
 */

#define MAIL_DIR      "/d/Genesis/postmaster/mail/"
#define FILE_NAME(n)  (MAIL_DIR + extract((n), 0, 0) + "/" + (n))
#define MAIL_NEW_MAIL "new_mail"
#define M_SIZEOF_MAIL 4

nomask void
create_object()
{
    setuid();
    seteuid(getuid());

    set_name("checker");
    set_adj("mail");

    set_long("It is a mail checker, used to check mail ;-)\n");
}

/*
 * Function name: query_mail
 * Description  : This function is actually used to check whether there
 *                is mail for the player. It operates on this_player().
 * Arguments    : object player - optional player, if not, use this_player()
 * Returns      : int - 0/1/2/3 - for details, see the file-header.
 */
nomask varargs int
query_mail(object player)
{
    mapping mail;

    /* Use this_player() by default if no player was given.
     */
    if (!objectp(player))
    {
	player = this_player();
    }

    /* Check whether the player exists.
     */
    if ((!objectp(player)) ||
	(!(SECURITY->exist_player(player->query_real_name()))))
    {
	return 0;
    }

    setuid();
    seteuid(getuid());

    mail = restore_map(FILE_NAME(player->query_real_name()));
    /* If something is wrong with the mail-file, there is no mail for
     * the player.
     */
    if ((m_sizeof(mail) != M_SIZEOF_MAIL) ||
	(member_array(MAIL_NEW_MAIL, m_indices(mail)) == -1))
    {
	return 0;
    }

    return mail[MAIL_NEW_MAIL];
}
