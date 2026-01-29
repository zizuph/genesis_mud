/*      This has random functions.

    coder(s):   Glykron

    history:   23.5.95     Name generation added           Maniac
               31. 8.93    created                         Glykron

    purpose:    to add randomness

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/

#include "/d/Genesis/login/login.h"
#include <std.h>
#include <const.h>

static string *preconsonants, *vowels, *postconsonants, *good_races;
static string *name_syll_one_m, *name_syll_two_m, *name_syll_one_f, 
              *name_syll_two_f, *names = ({ });
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


void
retract_random_name(string str)
{
    if (member_array(str, names) > -1)
        names -= ({str});
}


string
select_name(int g)
{
     string n;

    if (g == G_MALE) {
        n = random_element(name_syll_one_m);
        if (random(4)) 
            n += random_element(name_syll_two_m);
        return n;
    }
    n = random_element(name_syll_one_f);
    if (random(4)) 
        n += random_element(name_syll_two_f);
    return n;
}


string 
random_name(int gender)
{
     string name;

     if (!name_syll_one_f)
         name_syll_one_f = ({"leia", "shyr", "haly", "zeya", 
                             "liza", "tari", "fyre", "lywe", 
                             "kali", "ella", "mari", "chyl", 
                             "trel", "syla", "myzi", "maia",  
                             "aimi", "basi", "maza", "dhew"});

     if (!name_syll_two_f)
         name_syll_two_f = ({"wyn", "la", "leth", "nna", "lyn", "len"});  

     if (!name_syll_one_m)
         name_syll_one_m = ({"gore", "tarr", "ryst", "zaxx", 
                             "phor", "maxx", "gror", "karn", 
                             "mann", "dhur", "traz", "jerl", 
                             "orda", "kryl", "yarn", "cith", 
                             "mace", "perz", "izar", "shar"}); 

     if (!name_syll_two_m)
         name_syll_two_m = ({"lo", "im", "er", "ak", "mon", "och"});

     name = select_name(gender);    
     while ((member_array(name, names) > -1) ||
            SECURITY->exist_player(name))      
         name = select_name(gender);

     names += ({name});
     return name;
}


string *
random_adjs()
{
    mixed *adj_list1, *adj_list2;

    setuid();
    seteuid(getuid());

    if (!attrib)
        attrib = m_values((LOGIN_FEATURES)->query_features());

    adj_list1 = random_element(attrib);

    do adj_list2 = random_element(attrib);
    while(adj_list1[0] == adj_list2[0]);

    return ({ random_element(adj_list1), random_element(adj_list2) });
}

string
random_good_race()
{
    if (!good_races)
        good_races = RACES - ({ "goblin" });

    return random_element(good_races);
}
