/*
 * /d/Gondor/minas/lib/pw_master.c
 *
 * Gives the passwords to the inner circles of Minas Tirith
 *
 * Olorin, August 1994
 */
#include "/d/Gondor/defs.h"

#define PASSWORDS ({ \
	"tinco", "parma", "calma", "quesse", \
	"ando", "umbar", "anga", "ungwe", \
	"thule", "formen", "harma", "aha", "hwesta", \
	"anto", "ampa", "anca", "unque", \
	"numen", "malta", "noldo", "nwalme", \
	"ore", "vala", "anna", "vilya", \
	"romen", "arda", "lambe", "alda", \
	"silme", "are", "esse", "hyarmen", "yanta", "ure", \
	})
#define PASSWORDS_2 ({\
	"alcar", "ambar", "asta", "aure", \
	"carne", "certa", "cirya", "coire", "corma", \
	"elen", "enquie", "falma", "fanya", \
	"hilde", "hisie", "hrive", "laire", "lanta", "lasse", \
	"leuca", "loende", "lome", "losse", '"lote", "luine", \
	"lumbule", "luva", "macar", "marde", "menel", "metta", \
	"mire", "morna", "norie", "ondo", "osto", "palan", \
	"quelle", "rama", "ringa", "sinda", "tarcil", "tarma", \
	"taure", "tehta", "telco", "telluma", "telpe", "tema", \
	"tengwa", "tinwe", "tuile", "tumbale", "tur", \
	"vinye", "yavie", "yesta", "yulda", \
	})
#define PASSWORDS_3 ({ \
	"narvinye", "nenime", "sulime", "viresse", \
	"lotesse", "narie", "cermie", "urime", \
	"yavannie", "narquelie", "hisime", "ringare", \
	})
#define PASSWORDS_4 ({ \
	"narwain", "ninui", "gwaeron", "gwirith", \
	"lothron", "norui", "cerveth", "urui", \
	"ivanneth", "narbeleth", "hithui", "girithron", \
	})
           

varargs int
query_seed(string str)
{
    int     strl,
            i,
            seed;

    if (!strlen(str))
        str = TP->query_real_name();

    strl = strlen(str);

    for (i = 0; i < strl; i++)
        seed += str[i];

    return seed;
}

varargs string
query_password(int circle, string name)
{
    int     seed;
    string  pw;
 
    seed = query_seed(name);

    seed += circle;

    pw = PASSWORDS[random(sizeof(PASSWORDS), seed)];
    return pw;
}

