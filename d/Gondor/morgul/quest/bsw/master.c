/*
 * /d/Gondor/morgul/quest/bsw/master.c
 *
 * Standard routines for the quest to retrieve the battle standard of
 *	the Witchking
 *
 * Olorin, July 1994
 */
#include <macros.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/morgul/quest/bsw/bsw_defs.h"

#define ARNOR	 ({ "isildur"		,    2, \
		    "valandil"		,  249, \
		    "eldacar"		,  339, \
		    "arantar"		,  435, \
		    "tarcil"		,  515, \
		    "tarondor"		,  602, \
		    "valandur"		,  652, \
		    "elendur"		,  777, \
		    "earendur"		,  861, \
		    "amlaith"		,  946, \
		    "beleg"		, 1029, \
		    "mallor"		, 1110, \
		    "celepharn"		, 1191, \
		    "celebrindor"	, 1272, \
		    "malvegil"		, 1349, \
		    "argeleb i"		, 1356, \
		    "arveleg i"		, 1409, \
		    "araphor"		, 1589, \
		    "argeleb ii"	, 1670, \
		    "arvegil"		, 1743, \
		    "arveleg ii"	, 1813, \
		    "araval"		, 1891, \
		    "araphant"		, 1964, \
		    "arvedui"		, 1975, \
		 })
#define GONDOR	 ({ "meneldil"		,  158, \
		    "cemendur"		,  238, \
		    "earendil"		,  324, \
		    "anardil"		,  411, \
		    "ostoher"		,  492, \
		    "romendacil i"	,  541, \
		    "turambar"		,  667, \
		    "atanatar i"	,  748, \
		    "siriondil"		,  830, \
		    "tarannon"		,  913, \
		    "earnil i"		,  936, \
		    "ciryandil"		, 1015, \
		    "hyarmendacil i"	, 1149, \
		    "atanatar ii"	, 1226, \
		    "narmacil i"	, 1294, \
		    "calmacil"		, 1304, \
		    "romendacil ii"	, 1366, \
		    "valacar"		, 1432, \
		    "eldacar"		, 1490, \
		    "aldamir"		, 1540, \
		    "hyarmendacil ii"	, 1621, \
		    "minardil"		, 1634, \
		    "telemnar"		, 1636, \
		    "tarondor"		, 1798, \
		    "telumehtar"	, 1850, \
		    "narmacil ii"	, 1856, \
		    "calimehtar"	, 1936, \
		    "ondoher"		, 1944, \
		    "earnil ii"		, 2043, \
		    "earnur"		, 2050, \
		 })
#define BEGIN_STEWARD_RULE	2050
#define STEWARDS ({ "mardil"		, 2080, \
                    "eradan"		, 2116, \
                    "herion"		, 2148, \
                    "belegorn"		, 2204, \
                    "hurin i"		, 2244, \
                    "turin i"		, 2278, \
                    "hador"		, 2395, \
                    "barahir"		, 2412, \
                    "dior"		, 2435, \
                    "denethor i"	, 2477, \
                    "boromir"		, 2489, \
                    "cirion"		, 2567, \
                    "hallas"		, 2605, \
                    "hurin ii"		, 2628, \
                    "belecthor i"	, 2655, \
                    "orodreth"		, 2685, \
                    "ecthelion i"	, 2698, \
                    "egalmoth"		, 2743, \
                    "beren"		, 2763, \
                    "beregond"		, 2811, \
                    "belecthor ii"	, 2872, \
                    "thorondir"		, 2882, \
                    "turin ii"		, 2914, \
                    "turgon"		, 2953, \
                    "ecthelion ii"	, 2984, \
                    "denethor ii"	, 3019, \
                 })

static  mixed  stewards	= STEWARDS,
               arnor    = ARNOR,
               gondor   = GONDOR;

int
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

int
query_random_year(string type, string str)
{
    int     seed,
            offset = 0,
            year,
            delta = 0;
    mixed   who;

    if (!strlen(str))
        str = TP->query_real_name();

    type = LOW(type);
    switch(type)
    {
        case "stewards":
            who = stewards;
            delta = (BSW_STEWARDS_LAST_YEAR -
                     BSW_STEWARDS_FIRST_YEAR + 1);
            break;
        case "arnor":
            offset = 1;
            who = arnor;
            break;
        case "gondor":
            offset = 2;
            who = gondor;
            break;
        default:
            return -1;
    }

    seed = query_seed(str);

    if (!delta)
        delta = who[sizeof(who)-1] - who[1];

    year = who[1] + random(delta, seed+offset);
    if (member_array(year, who) > -1)
        year++;

    return year;
}

string
cap_name(string name)
{
    string *s;

    s = explode(name, " ");
    s[0] = CAP(s[0]);
    if (sizeof(s) > 1)
    {
        if (s[1] == "i")
            s[1] = "I";
        else if (s[1] == "ii")
            s[1] = "II";
        s[0] += (" "+s[1]);
    }
    return s[0];
}

varargs mixed
query_rulers(string type, mixed name)
{
    int     i;
    mixed   who;

    type = LOW(type);
    switch(type)
    {
        case "stewards":
            who = stewards;
            break;
        case "arnor":
            who = arnor;
            break;
        case "gondor":
            who = gondor;
            break;
        default:
            return -1;
    }

    if (!name)
        return who;

    if (stringp(name))
        name = LOW(name);

    if ((i = member_array(name, who)) == -1)
        return -1;

    if (intp(name))
        return cap_name(who[i-1]);
    if (stringp(name))
        return who[i+1];
    return -1;
}

string
query_ruler(string type, int year)
{
    int     sr,
            i;
    mixed   who;

    if (stringp(year))
        return 0;

    type = LOW(type);
    switch(type)
    {
        case "stewards":
            who = stewards;
            break;
        case "arnor":
            who = arnor;
            break;
        case "gondor":
            who = gondor;
            break;
        default:
            return 0;
    }

    if (year <= who[1])
        return 0;

    sr = sizeof(who);

    for (i = 1; i < sr; i+=2)
        if (who[i] >= year)
            return cap_name(who[i-1]);

    return 0;
}

varargs string
query_random_ruler(string type, string str)
{
    type = LOW(type);
    switch(type)
    {
        case "stewards":
        case "arnor":
        case "gondor":
            break;
        default:
            return 0;
    }

    if (!strlen(str))
        str = TP->query_real_name();

    return query_ruler(type, query_random_year(type, str));
}

varargs int
query_delta_year_isildur(string str)
{
    int     sy,
            ay;
    string  stw;

    if (!strlen(str))
        str = TP->query_real_name();

    stw = query_random_ruler("stewards", str);

    sy = stewards[member_array(LOW(stw), stewards)-1];
    ay = query_random_year("arnor", str);
    return (sy-ay);
}
    
varargs int
query_delta_year_anarion(string str)
{
    int     sy,
            gy;
    string  stw;

    if (!strlen(str))
        str = TP->query_real_name();

    stw = query_random_ruler("stewards", str);

    sy = stewards[member_array(LOW(stw), stewards)-1];
    gy = query_random_year("gondor", str);
    return (sy-gy);
}
    


