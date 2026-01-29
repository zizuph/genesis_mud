inherit "/std/armour";
#include <wa_types.h>
#include <stdproperties.h> 

#include "../guild.h"

void
create_armour()
{
    string runes;

    set_at(A_WAIST);
    set_name("sash");
    add_name(GUILD_EMBLEM_ID);
    set_adj(({ "white", "gold-trimmed" }));
    add_prop(OBJ_I_WEIGHT, 50);
    add_prop(OBJ_I_VOLUME, 300);
    add_prop(OBJ_I_VALUE, 60);
    add_prop(OBJ_M_NO_DROP, "You don't want to drop your lovely"+
        " sash.\n");
    add_prop(OBJ_M_NO_STEAL, "As you try to take the sash you feel a "+
         "intense pain in your hand and decide against it.\n");
    add_prop(OBJ_M_NO_SELL, "Oops! You can't sell that! What were you"+
        " thinking?\n");
    add_prop(OBJ_M_NO_BUY, "Oops! Sorry how did that get there?\n");

    set_long("This white sash is made from the finests elven silk. Along"+ 
        " the edges of the sash, elven runes have been embroidered in"+
        " golden thread. At each end of the sash, a four-pointed star "+
        "has been embroidered using silver and gold thread.\n");

    runes =  "As you read the runes you can make out the runes for: " +
        "Honour, Courage, Loyalty, and Enlightenment.\n";

    add_item(({ "elven runes", "runes on sash", 
        "elven runes on sash" }), runes);
   
    add_cmd_item(({ "elven runes", "runes on sash", 
        "elven runes on sash" }), "read", runes);

    add_item(({ "star", "four-pointed star", "four-pointed star on sash",
        "star on sash" }),
        "The star of Telen-Ri represents the four qualities he demands " +
        "of his followers: Honour, Courage, Loyalty, and Enlightenment.\n");
}

string
query_recover()
{
    return 0;
}

/*
 * Called in all objects in the player's inventory when he/she
 * leaves the guild.
 */
void
remove_kot_object()
{
    remove_object();
}
