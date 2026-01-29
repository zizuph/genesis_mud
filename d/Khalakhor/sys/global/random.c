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
 * Function name: query_male_dwarf_adjs
 * Description  : Returns an array of arrays containing various
 *                adjectives pertinent to male dwarves.
 * Arguments    : n/a
 * Returns      : Array as described above, describing:
 *                ({age, arms, beards, ,build, complexion, eyes,
 *                  face, general, hair, legs})
 */
public varargs string *
query_male_dwarf_adjs(string category = "")
{
    string *ret;

    if (!strlen(category))
	return ({"age","arms","beard", "build", "skin","eyes","face",
	  "general","hair", "legs"});

    switch (category)    
    {
    case "age":
	ret = ({"adolescent","young","middle-aged","old","elderly"});
	break;
    case "arms":
	ret = ({"short-armed","thick-armed"});
	break;
    case "beard":
	ret = ({"fork-bearded","long-bearded","COLOUR-bearded",
	  "thick-bearded","bristly-bearded"});
	break;
    case "build":
	ret = ({"barrel-chested","broad-chested","broad-shouldered",
	  "big", "flabby", "heavy", "hulking", "impressive",
	  "massive", "muscular","pot-bellied","squat","stocky",
	  "wizened"});
	break;
    case "skin":
	ret = ({"dark-skinned","copper-skinned","swarthy","tanned",
	  "brown-skinned", "ebony-skinned"});
	break;
    case "eyes":
	ret = ({"blue-eyed","brown-eyed","black-eyed",
	  "green-eyed","one-eyed","squinty-eyed",
	  "grey-eyed", "squinty-eyed", "wide-eyed",
	  "cross-eyed", "poopy-eyed"});
	break;
    case "face":
	ret = ({"bent-nosed","big-nosed","bulbous-nosed",
	  "double-chinned","hook-nosed","knob-nosed",
	  "hook-nosed","potato-nosed","red-cheeked",
	  "pug-nosed", "red-nosed","square-jawed",
	  "stone-faced","tight-jawed","wart-nosed"});
	break;
    case "general":
	ret = ({"hairy","leathery","scarred","slouchy","sweaty",
	  "wrinkled", "angry", "ill-tempered", "clam",
	  "brave", "drunken", "confident", "boasterous",
	  "frendly", "tempered", "indifferent"});
	break;
    case "hair":
	ret = ({"COLOUR-haired","long-haired","thick-haired",
	  "mohawk-haired"});
	break;
    case "colours":
	ret = ({"black","blond","red","brown","orange",
	  "purple", "white"});
	break;
    case "legs":
	ret = ({"bandy-legged", "knob-kneed","short-legged",
	  "thick-legged"});
    }
    return ret;
}
/*
 * Function name: query_felmale_dwarf_adjs
 * Description  : Returns an array of arrays containing various
 *                adjectives pertinent to female dwarves.
 * Arguments    : n/a
 * Returns      : array containing attribs in the specified
 *                category, or an array of categories if none
 *                specified.
 */
public varargs string *
query_female_dwarf_adjs(string category = "")
{
    string *ret;

    if (!strlen(category))
	return ({"age","arms","build","skin","eyes","face",
	  "general","hair","legs"});

    switch (category)    
    {
    case "age":
	ret = ({"adolescent","young","middle-aged","old","eldery"});
	break;
    case "arms":
	ret = ({"short-armed","thick-armed"});
	break;
    case "build":
	ret = ({"broad-chested","chubby","curvaceous","flat-chested",
	  "lean","light","petite","big","stocky","stout",
	  "voluptuous","wide-hipped","willowy","wizend"});
    case "skin":
	ret = ({"brown-skinned","beige-skinned","copper-skinned",
	  "tanned","dark-skinned","ebony-skinned"});
	break;
    case "eyes":
	ret = ({"blue-eyed","brown-eyed","black-eyed",
	  "green-eyed","one-eyed","squinty-eyed",
	  "grey-eyed", "squinty-eyed", "wide-eyed",
	  "cross-eyed", "poopy-eyed"});
	break;
    case "face":
	ret = ({"dimpled","big-nosed","bulbous-nosed","hook-nosed",
	  "knob-nosed","oval-faced","red-cheeked","round-faced",
	  "wart-nosed"});
	break;
    case "general":
	ret = ({"angry","animated","calm","cordial","dour",
	  "friendly","haughty","indifferent","irritable",
	  "jovial","level-headed","moody","nonchalant",
	  "talkative","exotic","leathery","scarred","prim",
	  "slouchy","tidy-looking","wrinkled"});
	break;
    case "hair":
	ret = ({"COLOUR-haired","long-haired","thick-haired"});
	break;
    case "colours":
	ret = ({"black","blond","red","brown","orange",
	  "purple", "white","raven","auburn"});
	break;
    case "legs":
	ret = ({"bandy-legged", "knob-kneed","short-legged",
	  "thick-legged"});
    }
    return ret;
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
	  "mustachioed","COLOUR-bearded", "full-bearded",
	  "thick-bearded","thinly-bearded"});
	break;
    case "skin":
	ret = ({"dark-skinned","light-skinned","pale","pallid",
	  "fair-skinned","freckled"});
	break;
    case "eyes":
	ret = ({"blue-eyed","brown-eyed","dark-eyed",
	  "green-eyed","one-eyed","squinty-eyed", 
	  "grey-eyed", "wild-eyed"});
	break;
    case "face":
	ret = ({"dimpled","square-jawed","wide-mouthed",
	  "big-nosed","jug-eared","flat-nosed",
	  "long-faced","round-faced",
	  "square-faced","stone-faced","thin-faced",
	  "ruddy-faced", "oval-faced", "red-cheeked"});
	break;
    case "general":
	ret = ({"unkempt", "tidy-looking", "well-groomed",
	  "disheveled", "weathered", "rugged", "coarse"});
	break;
    case "hair":
	ret = ({"bald","balding","COLOUR-haired",
	  "long-haired","thick-haired", "tonsure-haired",
	  "thin-haired", "wispy-haired"});
	break;
    case "colours":
	ret = ({"black","blonde","red","brown","chestnut",
	  "dark", "light", "flaxen", "orange", "raven"});
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
	ret = ({"light-skinned","pale","pallid",
	  "fair-skinned","ivory-skinned",
	  "freckled"});
	break;
    case "eyes":
	ret = ({"blue-eyed","brown-eyed","dark-eyed",
	  "green-eyed","grey-eyed"});
	break;
    case "face":
	ret = ({"dimpled","big-nosed", "oval-faced",
	  "long-faced","round-faced", "red-cheeked",
	  "thin-faced", "ruddy-faced"});
	break;
    case "general":
	ret = ({"unkempt", "tidy-looking", "well-groomed",
	  "disheveled", "weathered", "rugged", "coarse",
	  "willowy", "curvaceous"});
	break;
    case "hair":
	ret = ({"COLOUR-haired",
	  "long-haired","thick-haired", "wild-haired",
	  "thin-haired", "wispy-haired"});
	break;
    case "colours":
	ret = ({"black","blonde","red","brown","chestnut",
	  "dark", "light", "raven", "flaxen"});
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

