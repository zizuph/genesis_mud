/* 
 * /d/Shire/guild/peredhil/obj/guild_item.c
 *
 * The default guild object for the Peredhil racial guild.
 * Based on the blacksmith's necklace
 * February 2009 by Finwe
 */

#pragma save_binary;

#include "/d/Shire/sys/defs.h"
#include "/d/Shire/guild/peredhil/pered.h";
#include <formulas.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <wa_types.h>

inherit "/std/object";
inherit "/lib/wearable_item";
inherit "/d/Shire/guild/peredhil/obj/guild_obj_descr.c";

string brooch_type;
int    inited;

string set_brooch_short()
{
    return brooch_type+" brooch";
}  

string set_brooch_long()
{
    return "This is a " + short() + ". It is simple and made into the shape of a multi-ray star. It can worn on your chest and identifies you as a Peredhil. You can learn more about them with <help peredhil>.\n";
}


void
create_object()
{
    set_name(({"brooch", PERED_OBJ_ID}));

//    set_adj("@@describe_brooch@@" + " brooch");
    set_short("@@set_brooch_short@@");
    set_long("@@set_brooch_long@@");
    set_slots(A_CHEST);
    set_layers(0);
    set_looseness(5);

    add_prop(OBJ_M_NO_STEAL, "You cannot do that.\n");
    add_prop(OBJ_M_NO_DROP, "It is pointless to drop this brooch.\n");
    add_prop(OBJ_M_NO_GIVE, "You cannot give your brooch away.\n");
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
	brooch_type = describe_guild_obj();
	set_adj(brooch_type);
	

}
void init()
{
    ::init();
    if (!inited && ENV(TP))
        set_alarm(2.0, 0.0, &initiate(TP));
}

