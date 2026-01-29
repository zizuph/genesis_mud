/*
 * /d/Gondor/mordor/obj/towerkey.c
 *
 * This is the key that will fit the doors in the tower at Cirith Ungol. There
 * are two keys that will fit about 50 percent of the doors. If you want to
 * have a key that specificly fits a certain lock, call set_number() in this
 * key. You can do query_number() and set_number() in all keys and doors in the
 * the tower.
 *
 * /Mercade, 26 September 1993
 *
 * Revision history:
 */

inherit "/std/key";

#include "/d/Gondor/defs.h"
#include "/d/Gondor/mordor/ungol/tower/tower.h"
#include <ss_types.h>

#define MINIMUM_AWARENESS_NEEDED 20

int key_number = 0;

/*
 * remove previous adjs if you force a key number.
 */
void
delete_key_prefs()
{
    int i;
    string *prefs = query_adjs();

    for(i = 0; i < sizeof(prefs); i++)
    {
        remove_adj(prefs[i]);
    }
}

/*
 *
 */
void
make_tower_key(int number)
{
    if (key_number)
    {
        delete_key_prefs();
    }

    key_number = number;
    set_adj("steel");

    switch(number)
    {
        case 1:
            set_key(TOWER_KEY_NUMBER_1);
            add_adj("evil");
            add_adj("orkish");
            set_short("evil orkish key");
            set_pshort("evil orkish keys");
            return;
        case 2:
        default:
            set_key(TOWER_KEY_NUMBER_2);
            add_adj("dark");
            add_adj("tower");
            set_short("dark tower key");
            set_pshort("dark tower keys");
            return;
    }
}

/*
 * Called when the key is created. The key will have a random number set.
 */
void
create_key()
{
    set_long("@@long_description");

    make_tower_key((random(2) + 1));
    add_prop("_key_i_no_keyring", 1);
}

string
long_description()
{
    if (TP->query_skill(SS_AWARENESS) >= MINIMUM_AWARENESS_NEEDED)
    {
        return BSN("It is a key, made of steel. On it you see a red eye, " +
            "meaning that this key is used by the evil forces of the " +
            "nameless One. It must be in use somewhere in the dark tower " +
            "at Cirith Ungol.");
    }

    return BSN("It is a key, made of steel with a red eye painted on it. " +
        "You have no idea what it is used for.");
}

/*
 * Force a key of type <number>
 */
void
set_number(int number)
{
    make_tower_key(number);
}

/*
 * Get the number of the key (this isn't the lock number)
 */
int
query_number()
{
    return key_number;
}
