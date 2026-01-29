/*      This has random functions.

    coder(s):   Glykron

    history:    31. 8.93    created                         Glykron

    purpose:    to add randomness

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#include "/d/Genesis/login/login.h"

static string *preconsonants, *vowels, *postconsonants, *good_races;
mixed *attrib;

mixed
random_element(mixed *list)
{
     return list[random(sizeof(list))];
}

string
random_word()
{
    if (!preconsonants)
    {
        preconsonants =
        ({
            "", "b", "bl", "br", "c", "ch", "cl", "cr", "d", "dr", "dw", "f",
            "fl", "fr", "g", "gl", "gr", "h", "j", "l", "m", "n", "p", "pl",
            "pr", "qu", "r", "s", "sc", "scr", "sh", "shr", "sl", "sm", "sn",
            "sp", "spl", "spr", "st", "str", "sr", "sw", "t", "th", "thr", "tr",
            "v", "w", "y", "z"
        });

        vowels =
        ({
            "a", "ai", "au", "e", "ea", "i", "ie", "o", "oa", "oi", "oo", "ou",
            "u"
        });

        postconsonants =
        ({ "", "b", "ch", "ck", "d", "f", "g", "h", "l", "lb", "ld", "lk",
            "lm", "lp", "lt", "m", "n", "nd", "ng", "nk", "nt", "p", "r", "s",
            "sh", "st", "t", "th", "x", "z"
        });
    }

    return
        random_element(preconsonants) +
        random_element(vowels) +
        random_element(postconsonants);
}

string *
random_adjs()
{
    mixed *adj_list1, *adj_list2;

    if (!attrib)
	restore_object("/d/Genesis/login/attributes");

    adj_list1 = random_element(attrib);

    do adj_list2 = random_element(attrib);
    while(adj_list1[0] == adj_list2[0]);

    return ({ random_element(adj_list1[2]), random_element(adj_list2[2]) });
}

string
random_good_race()
{
    if (!good_races)
        good_races = RACES - ({ "goblin" });

    return random_element(good_races);
}
