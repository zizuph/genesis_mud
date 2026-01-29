/*
 *  file name:   hair.h
 *  creator(s):  Zielia 2006
 *  last update:
 *  purpose:     Manages the hair descriptions for ziggurat objects
 *  note:        Works with hair from /d/Calia/gelan if the mortal has it.
 *  bug(s):
 *  to-do:
 */

#include <macros.h>

#define LENGTH(x) hair_length_desc(x)
#define COLOR(x)  hair_color_desc(x)
#define STYLE(x)  hair_style_desc(x)
#define HAIR(x)   hair_desc(x)

private string *tangled = ({ " styled into dreadlocks", " matted",
    " matted with blood", " very wild and unkempt", });

private string *curled = ({ " curly", " tight curled", " loose curled",
    " styled with ringlets", });

private string *missing = ({ " burned into wisps", " half pulled out",
    " bald in the middle", " missing", " balding"});

private string *back = ({ " swirled into a bun", " styled with a top-not",
    " braided", " bushido style", " tied into a french braid", " tied back",
    " styled with a pony tail",  " slicked straight back", " swept back",
    " styled with pigtails", });

private string *up = ({ " styled in a flat top", " mohawk style",
    " sticking straight up", " spiked like a porcupine", });

private string *colors = ({"auburn-haired","black-haired","blond-haired",
    "blue-haired","brown-haired","chestnut-haired","dark-haired",
    "gray-haired","green-haired","flaxen-haired","light-haired",
    "orange-haired","purple-haired","raven-haired","red-haired",
    "white-haired","golden-haired","silver-haired"});

private string *lengths = ({"long-haired","short-haired","thick-haired",
    "thin-haired",});

public string
hair_color_desc(object ob)
{
    string *adjs = regexp(ob->query_adjs(), "-haired$");
    string *desc;

    if (!objectp(ob))   {   return " colorless";  }

    if (ob->query_hair_colour())
    {
        return " "+ ob->query_hair_colour();
    }

    else if ((sizeof(adjs) > 0) && IN_ARRAY(adjs[0], colors))
    {
        desc = explode(adjs[0], "-");
        return " "+ desc[0];
    }

    else
    {
        return "";
    }
}

public string
hair_length_desc(object ob)
{
    string *adjs = regexp(ob->query_adjs(), "-haired$");
    string *desc;

    if (!objectp(ob))   {   return "bad length";  }

    if (ob->query_hair_length())
    {
        return " "+ ob->query_hair_length();
    }

    else if ((sizeof(adjs) > 0) && IN_ARRAY(adjs[0], lengths))
    {
        desc = explode(adjs[0], "-");
        return " "+ desc[0];
    }

    else
    {
        return "";
    }
}

public string
hair_style_desc(object ob)
{
    if (!objectp(ob))   {   return "bad style";  }

    if (ob->query_hair_style())
    {
        return " "+ ob->query_hair_style();
    }

    else if (IN_ARRAY("bald", ob->query_adjs()))
    {
        return " missing";
    }

    else if (IN_ARRAY("balding", ob->query_adjs()))
    {
        return " balding";
    }

    else if (IN_ARRAY("mohawk-haired", ob->query_adjs()))
    {
        return " styled in a mohawk";
    }

    else if (IN_ARRAY("tonsure-haired", ob->query_adjs()))
    {
        return " bald in the middle";
    }

    else if (IN_ARRAY("wispy-haired", ob->query_adjs()))
    {
        return " wispy";
    }

    else
    {
        return " unstyled";
    }
}

public string
hair_desc(object ob)
{
    if (!objectp(ob))   {   return "bad hair";  }

    if (ob->query_hair_style())
    {
        return LENGTH(ob) +","+ COLOR(ob) +" hair";
    }

    else
    {
        return LENGTH(ob) + COLOR(ob) +" hair";
    }
}

