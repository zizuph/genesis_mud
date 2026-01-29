/*
 * random.c
 *
 * A file which can be used to save some time when using
 * randomness, such as generating npc's with random
 * races, genders, and adjectives.
 *
 */
#pragma strict_types

#include "/d/Genesis/login/login.h"

public mixed
random_element(mixed arr)
{
    return arr[random(sizeof(arr))];
}

/*
 * Function name: query_male_human_adjs
 * Description  : Returns an array of arrays containing various
 *                adjectives pertinent to male humans.
 * Arguments    : n/a
 * Returns      : Array as described above, describing:
 *                ({age, arms, beards, complexion, eyes,
 *                  face, general, hair})
 */
public varargs string *
query_male_human_adjs(string category = "")
{
    string *ret;

    if (!strlen(category))
        return ({"age","arms","beard","skin","eyes","face",
            "general","hair"});

    switch (category)    
    {
        case "age":
             ret = ({"adolescent","young","middle-aged","old"});
             break;
        case "arms":
             ret = ({"long-armed","short-armed","thin-armed",
                    "thick-armed"});
             break;
        case "beard":
             ret = ({"clean-shaven","fork-bearded","long-bearded",
                     "mustachioed","COLOUR-bearded",
                     "thick-bearded","thinly-bearded"});
             break;
        case "skin":
             ret = ({"dark-skinned","light-skinned","pale","palid",
                     "swarthy","tanned"});
             break;
        case "eyes":
             ret = ({"blue-eyed","brown-eyed","dark-eyed",
                     "green-eyed","one-eyed","squinty-eyed"});
             break;
        case "face":
             ret = ({"dimpled","square-jawed","wide-mouthed",
                     "big-nosed","jug-eared","flat-nosed",
                     "long-faced","round-faced","sad-faced",
                     "square-faced","stone-faced","thin-faced"});
             break;
        case "general":
             ret = ({"angry","animated","callous","calm",
                     "charming","cordial","dour","dull",
                     "friendly","haughty","high-strung",
                     "indifferent","irritable","jovial",
                     "level-headed","moody","nonchalant",
                     "talkative","tempered","weathered"});
             break;
        case "hair":
             ret = ({"bald","balding","COLOUR-haired",
                     "long-haired","thick-haired",
                     "thin-haired"});
             break;
        case "colours":
             ret = ({"black","blonde","red","brown","chestnut",
                     "dark", "light"});
    }
    return ret;
}
/*
 * Function name: query_female_human_adjs
 * Description  : Returns an array of arrays containing various
 *                adjectives pertinent to female humans.
 * Arguments    : n/a
 * Returns      : array containing attribs in the specified
 *                category, or an array of categories if none
 *                specified.
 */
public varargs string *
query_female_human_adjs(string category = "")
{
    string *ret;

    if (!strlen(category))
        return ({"age","arms","skin","eyes","face",
            "general","hair"});

    switch (category)    
    {
        case "age":
             ret = ({"adolescent","young","middle-aged","old"});
             break;
        case "arms":
             ret = ({"long-armed","short-armed","thin-armed",
                    "thick-armed"});
             break;
        case "skin":
             ret = ({"light-skinned","pale","palid",
                     "tanned","ivory-skinned"});
             break;
        case "eyes":
             ret = ({"blue-eyed","brown-eyed","dark-eyed",
                     "green-eyed",});
             break;
        case "face":
             ret = ({"dimpled","big-nosed",
                     "long-faced","round-faced","sad-faced",
                     "thin-faced"});
             break;
        case "general":
             ret = ({"angry","animated","calm",
                     "charming","cordial","dour","dull",
                     "friendly","haughty","high-strung",
                     "indifferent","irritable","jovial",
                     "level-headed","moody","nonchalant",
                     "talkative","exotic","willowy",
                     "curvacious"});
             break;
        case "hair":
             ret = ({"COLOUR-haired",
                     "long-haired","thick-haired",
                     "thin-haired"});
             break;
        case "colours":
             ret = ({"black","blonde","red","brown","chestnut",
                     "dark", "light"});
    }
    return ret;
}

public string *
random_detail_adjs(object npc)
{
    string gender,
           race,
           hair,
           cat;
    int i;
    function func;
    string *adjs = allocate(2);
    mixed categories;

    gender = (npc->query_gender() == 1 ? "female" : "male");
    race = npc->query_race();

    func = mkfunction("query_" + gender + "_" + race + "_adjs");

    hair = random_element(func("colours"));
    categories = func();
    cat = random_element(categories);
    categories -= ({cat});
    adjs[0] = random_element(func(cat));
    cat = random_element(categories);
    adjs[1] = random_element(func(cat));
    for (i = 0; i < 2; i++)
    {
        if (sscanf(adjs[i], "COLOUR%s", cat))
            adjs[i] = hair + cat;
    }
    return adjs;
}

public string *
random_adjs()
{
    mixed temparr;
    string *adjs1,
           adj1,
           *adjs2,
           adj2;

    setuid(); seteuid(getuid());
    temparr = m_values((LOGIN_FEATURES)->query_features());
    adjs1 = random_element(temparr);
    temparr -= adjs1;
    adjs2 = random_element(temparr);
    adj1 = random_element(adjs1);
    adj2 = random_element(adjs2);
    return ({adj1, adj2});
}
    
