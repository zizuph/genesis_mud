/*
 * Language object for the Wizards of High Sorcery
 * written by Belize of Krynn
 */

inherit "/std/object";

#include <ss_types.h>
#include <tasks.h>
#include <macros.h>
#include "../local.h"

#undef DEBUG "belize"

mixed *parts = ({ 
                  ({ "a", "e", "i", "n", "q", "s", "t", "u", "y" }),
                  ({ "ae", "al", "ar", "at", "au", "az", "be", "by", "ci",
                     "cu", "di", "dm", "ea", "ed", "em", "el", "eu", "gu",
                     "he", "in", "im", "je", "le", "lo", "lu", "om", "os",
                     "si", "sr", "we", "er" }),
                  ({ "nef", "lou", "tin", "hak", "fin", "gel", "bar",
                     "dol", "uma", "lom", "dor", "bec", "ble", "gil",
                     "him", "kel", "mal", "huj", "bil", "def", "pum",
                     "tua", "bum", "sor", "tea", "tel", "con", "pea",
                     "orn", "uth", "que", "tir", "cli", "let", "gar", 
                     "rej", "bel", "the", "sir", "sul", "ohn", "kin",
                     "art", "nar", "fea", "set", "nor", "tau", "him",
                     "had", "ful", "tan", "ion" }),
                  ({ "neth", "utum", "vali", "sour", "aque", "omni",
                     "onti", "taur", "fene", "cage", "herb", "very",
                     "cazu", "tele", "poli", "rect", "regi", "amon",
                     "lapi", "otko", "ront", "sall", "sput", "magi",
                     "stat", "trie", "uzur", "util", "volu", "srum",
                     "capo", "affe", "mira", "pisc", "cosi", "kill",
                     "oste", "dupa", "iama", "fear", "gord", "slay",
                     "vert", "sont", "atul" })  
               });
               
string *special	= ({ ".", "!", "?" });

int gSeed, gCapitalize = 0;
int *gSizes = ({ sizeof(parts[0]), sizeof(parts[1]), sizeof(parts[2]),
                 sizeof(parts[3]) });

/* ----- a bit modified name_to_random() taken from /sys/global/math.c ----- */

#define PRIMES   ({ 3, 7, 13, 17, 23, 37, 43, 47, 53, 67, 73 })
#define NAME_LEN 11
#define CHAR_a   (' ' - 1)


public nomask int
name_to_random(string name, int seed, int range)
{
    int index  = -1;
    int result = 0;
    int size;
    int char;

    /* Do not ever believe people follow your instructions. */
    name = lower_case(name);

    /* Player names cannot be larger than NAME_LEN characters, though
     * people may feed us with other strings.
     */
    if (strlen(name) > NAME_LEN)
    {
	name = extract(name, 0, (NAME_LEN - 1));
    }

    /* To find the result, we apply the same formula to each character
     * of the name, in addition with its rank, the seed and the first
     * primes ending with 3 or 7.
     */
    size = strlen(name);
    while(++index < size)
    {
	char = name[index] - CHAR_a;
	result += ((seed / char) + (char * PRIMES[NAME_LEN - index - 1]) +
	    (seed % (index + 1)));
    }

    /* Reduce the result to a number in the range 0 .. (range - 1). */
    return (result % range);
}

/* ------------------------------------------------------------------------ */



create_object()
{
   set_name( ({ "object", "language object" }) );
   set_short("language object");
}

string
code_word(string str)
{
    int size, num, seed, mod;
    string last = "", final = "";

    last = str[(strlen(str) - 1)..(strlen(str) - 1)];
    
    if (member_array(last, special) != -1)
    {
        gCapitalize = 1;
        str = str[0..strlen(str) - 2];
        last = special[random(sizeof(special))];
    }
    else
        last = "";
    
    if (!(size = strlen(str)))
        return last;
     
#ifdef DEBUG
    set_this_player(find_player(DEBUG));
#endif

    mod = name_to_random(str, gSeed, 3) - 1;
    
#ifdef DEBUG
    dump_array("Mod: " + mod);
#endif
    
    size = size + mod;

#ifdef DEBUG
    dump_array("New size: " + size);
#endif
    
    if (size <= 0)
        size = 1;

    if (size == 1)
        final = parts[0][name_to_random(str, gSeed*10, gSizes[0])];
    else
        while (size)
        {
            seed = name_to_random(str, gSeed / size, 100);
            
            switch(size)
            {
                /* its size */
                case 2:
                case 3: num = size; break;
                /* 2 or 4 */
                case 4: num = (random(2, seed) ? 2 : 4); break;
                /* 2 or 3 */
                case 5: num = (random(2, seed+51) ? 2 : 3); break;
                /* 2 or 3 or 4 */
                default: num = random(3, seed+101) + 2;
            }
            
#ifdef DEBUG
            dump_array("Size: " + size + "; Num : " + num + 
                "; Seed: " + seed);
#endif
            
            final += parts[num - 1][random(gSizes[num - 1], (seed + 79))];
            size -= (num);
        }
#ifdef DEBUG
    dump_array("final: " + final);
#endif

    return final + last;
}

string
code_text(string str, int percent)
{
    string *words;
    int size, to_change, ix;

    words = explode(str, " ") - ({ "" });
    size = sizeof(words);

#ifdef DEBUG
    set_this_player(find_player(DEBUG));
#endif
    
    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;
    
    /* rounds value */
    to_change = ftoi(itof(size) * itof(percent) / 100.0 + 0.5);
#ifdef DEBUG
    dump_array(percent + "%" + " of " + size + " = " + to_change);
#endif

    to_change = size - to_change;

    for (ix = 0; ix < size; ix++)
    {
        if (random(size - ix) < to_change)
        {
            to_change--;
            if (gCapitalize)
            {
                gCapitalize = 0;
                words[ix] = capitalize(code_word(words[ix]));
            }
            else 
                words[ix] = code_word(words[ix]);
        }
    }
    return implode(words, " ");
}

public string
translate(string str, object lst, int seed)
{
    int res;
    string text;
    
    gSeed = seed;

    if (lst->query_wiz_level())
        return "says in the language of magic: " + capitalize(str);

    if (THIS_GUILD(lst))
    {
        res = lst->resolve_task(550, ({ SKILL_WEIGHT, 300, SS_SPELLCRAFT, 
            SKILL_WEIGHT, 400, SS_LANGUAGE }) );
    }
    else
    {
        if ( (lst->query_skill(SS_SPELLCRAFT) < 20) ||
              (lst->query_skill(SS_LANGUAGE) < 30) ||
              (lst->query_stat(SS_INT) < 30))
            return "says something in a very strange, melodic language.";

        res = lst->resolve_task(2000, ({ SKILL_WEIGHT, 300, SS_SPELLCRAFT, 
            SKILL_WEIGHT, 400, SS_LANGUAGE }) );
    }
    
    return "says in the language of magic: " + capitalize(code_text(str, res));
}
