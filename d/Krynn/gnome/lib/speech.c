#include <cmdparse.h>
#include <filter_funs.h>

string
explode_capitals(string text)
{
    int i, last;
    string result = "";

    if (strlen(text) < 2)
        return text;

    last = 0;
    for (i = 1; i < strlen(text); i++)
    {
        if (text[i] >= 'A' && text[i] <= 'Z')
        {
            result += extract(text, last, i - 1);
            if (i != strlen(text) - 1)
                result += " ";
            last = i;
        }
    }
    result += extract(text, last);
    return result;
}

string 
implode_capitals(string text)
{
    int i;
    string *words = explode(text, " ");
    
    for (i = 0; i < sizeof(words); i++)
        words[i] = capitalize(words[i]);
   
    return implode(words, "");
}

object
find_attacker(string text)
{
    int i;
    object *killer;
    if (extract(text, 0, 12) != "Help!StopThis")
        return 0;
    killer = FIND_STR_IN_ARR(lower_case(explode_capitals(extract(text, 13, -2))),
            FILTER_PLAYERS(all_inventory(environment(this_object()))));
    if (!sizeof(killer))
        return 0;
    return killer[0];
}


