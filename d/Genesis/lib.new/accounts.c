/*
 * /d/Genesis/obj/accounts.c
 *
 * This object stores the accounts the player have at the gnomes of
 * Genesis at the Genesis branch.
 *
 * Mercade, 5 August 1995
 */

#pragma no_clone
#pragma no_inherit
#pragma save_binary
#pragma strict_types

inherit "/d/Genesis/obj/accounts_lib";

#define DEPOSIT_DIR ("/d/Genesis/obj/gnome_deposit/")

/*
 * Function name: create_accounts
 * Description  : This function is called when the accounts are loaded into
 *                memory. It should be used to set the directory in which
 *                the accounts can be found.
 */
void
create_accounts()
{
    set_deposit_dir(DEPOSIT_DIR);
}
