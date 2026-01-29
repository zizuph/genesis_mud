/*
 *     Necklace - guild item for the smiths guild
 *     In this item I have placed all the abilities and emotes
 *     possible to use by both Smiths and Artificiers
 *     Morinir 1996
 *
 *     Emotes and abilites moved to Smith soul (~Shire/smiths/smiths_craft_soul)
 *     Necklace converted from a piece of armour to a wearable item.
 *     Glaurung, August 98
 *    
 *     Added levels to necklace and made it wearable over items
 *     Finwe, November 2001
 *
 *     Palmer,  16-Jul-2006
 *     Added delay in determining appearance in case NPC gives necklace to player
 *     Moved necklace_desc out of priavte directory
 */

#pragma save_binary;

inherit "/std/object";
inherit "/lib/wearable_item";
#include "/d/Shire/guild/smiths/obj/necklace_descr.c";
#include <ss_types.h>
#include <formulas.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <macros.h>
#include "/d/Shire/sys/defs.h"


string necklace_type;
int    inited;

string set_necklace_short()
{
    return necklace_type+" necklace";
}  

string set_necklace_long()
{
    return "This " + short() + " is the token of membership in the Smiths "+
        "Guild. For guild related topics see <help smiths>.\n";
}


void
create_object()
{
    set_name(({"necklace","smiths_necklace"}));
//    set_adj("@@describe_necklace@@");
    set_short("@@set_necklace_short@@");
    set_long("@@set_necklace_long@@");
    set_slots(A_NECK);
    set_layers(0);
    set_looseness(5);

    add_prop(OBJ_M_NO_STEAL, "That would be useless to you.\n");
    add_prop(OBJ_M_NO_DROP, "Why would you drop your Smiths necklace?\n");
    add_prop(OBJ_M_NO_GIVE, "Why would you give away your Smiths necklace?\n");
    add_prop(OBJ_I_VALUE, 10);
    add_prop(OBJ_I_VOLUME, 20);
    add_prop(OBJ_I_WEIGHT, 25);
}



public void
leave_env(object env, object to)
{
    ::leave_env(env, to);
    wearable_item_leave_env(env, to);
}

string query_auto_load() { return MASTER + ":"; }

public string query_recover() { return 0; }

void initiate(object pl)
{
    string *impc;
    int     si;

    inited = 1;
	necklace_type = describe_necklace();
	set_adj(necklace_type);
	

}
void init()
{
    ::init();
    if (!inited && ENV(TP))
        //Add slight delay in case necklace is given from NPC so it
        //uses the player's Smith level 
        set_alarm(2.0, 0.0, &initiate(TP));
}

