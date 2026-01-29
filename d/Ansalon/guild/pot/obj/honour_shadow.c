/* Stralle @ Genesis 010705
 *
 * The shadow for the honour_ob.c
 */

#pragma strict_types

inherit "/std/shadow";

string gTitle;

void
set_title(string title)
{
    gTitle = title;
}

string
query_guild_title_occ()
{
    string title = query_shadow_who()->query_guild_title_occ();
    
    if (title)
        return title + " and " + gTitle;
    else
        return gTitle;
}
