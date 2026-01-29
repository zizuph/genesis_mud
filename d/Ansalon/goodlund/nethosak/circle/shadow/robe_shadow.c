/* Cult of Morgion's veil shadow by Morrigan */
inherit "/std/shadow";
#include "/d/Krynn/common/defs.h"
#include <ss_types.h>
#include <language.h>

string
query_the_name(object who)
{
    if (who->query_wiz_level())
        return "the concealed dark-robed ("+shadow_who->query_name()+")";
    else
        return "the concealed dark-robed figure";
}

string
query_nonmet_name(object who)
{
    if (who->query_wiz_level())
        return "concealed dark-robed figure("+shadow_who->query_name()+")";
    else
        return "concealed dark-robed figure";
}

string
query_The_name(object who)
{
    if (who->query_wiz_level())
        return "The concealed dark-robed figure("+shadow_who->query_name()+")";
    else
        return "The concealed dark-robed figure";
}

string
short(object who)
{
    if (who->query_wiz_level())
        return "concealed dark-robed figure("+shadow_who->query_name()+")";
    else
        return "concealed dark-robed figure";
}

string
query_art_name(object who)
{
    if (who->query_wiz_level())
        return "a concealed dark-robed figure("+shadow_who->query_name()+")";
    else
        return "a concealed dark-robed figure";
}

string
query_Art_name(object who)
{
    if (who->query_wiz_level())
        return "A concealed dark-robed figure("+shadow_who->query_name()+")";
    else
        return "A concealed dark-robed figure";
}
