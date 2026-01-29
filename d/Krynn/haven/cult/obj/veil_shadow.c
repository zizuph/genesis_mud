/* Cult of Morgion's veil shadow by Morrigan */
inherit "/std/shadow";
#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <language.h>

string
query_the_name(object who)
{
    if (who->query_wiz_level())
	return "the brown-hooded veiled figure ("+shadow_who->query_name()+")";
    else
	return "the brown-hooded veiled figure";
}

string
query_nonmet_name(object who)
{
    if (who->query_wiz_level())
	return "brown-hooded veiled figure ("+shadow_who->query_name()+")";
    else
	return "brown-hooded veiled figure";
}

string
query_The_name(object who)
{
    if (who->query_wiz_level())
	return "The brown-hooded veiled figure ("+shadow_who->query_name()+")";
    else
	return "The brown-hooded veiled figure";
}

string
short(object who)
{
    if (who->query_wiz_level())
	return "brown-hooded veiled figure ("+shadow_who->query_name()+")";
    else
	return "brown-hooded veiled figure";
}

string
query_art_name(object who)
{
    if (who->query_wiz_level())
	return "a brown-hooded veiled figure ("+shadow_who->query_name()+")";
    else
	return "a brown-hooded veiled figure";
}

string
query_Art_name(object who)
{
    if (who->query_wiz_level())
	return "A brown-hooded veiled figure ("+shadow_who->query_name()+")";
    else
	return "A brown-hooded veiled figure";
}
