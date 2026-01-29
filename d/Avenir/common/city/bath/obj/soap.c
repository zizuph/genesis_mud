#pragma strict_types
/*
 * ~/soap.c
 *
 * Scented soap for the bath.
 *
 * Revisions:
 *   Lilith, May 2002: Created.
 *   Lucius, Aug 2016: Code Cleanups.
 *
 */
inherit "/std/heap";
inherit "/lib/keep";

#include <stdproperties.h>
#include <macros.h>

#include "/d/Avenir/include/deities.h"

#define TP		this_player()
#define US_PURITY	139058


public void
create_heap(void)
{
    set_name(({"soap"}));
    set_short("scented soap");
    add_adj(({"oval", "scented"}));
    set_long("This is a bar of glycerine soap. It is oval in shape "+
        "and scented with essential oils such as lavender and "+
        "verbena.\n");

    add_prop(OBJ_I_VALUE,  20);
    add_prop(OBJ_I_WEIGHT, 40);
    add_prop(OBJ_I_VOLUME, 20);

    add_prop(HIZARBIN_OFFERING, 1);
    add_prop(HEAP_S_UNIQUE_ID, "av_bath_soap");

    set_heap_size(1);

    add_cmd_item("soap", "help",
       "Here are the emotes associated with the soap:\n" +
       "    s lather  lather up with soap to get clean.\n" +
       "    s bubbles blow soap bubbles.\n" +
       "\n");
}

public int
do_soap(string arg)
{
    if (arg == "lather")
    {
	object ob;

        write("You add some water to the soap in your hands "+
            "and clean yourself with the lather.\n");
      
        say(QCTNAME(TP) +" makes a lather from "+ 
            TP->query_possessive() +" "+ short() +" and "+
            "cleans "+ TP->query_objective() +"self with it.\n");

        if (TP->query_guild_name_occ() == "Union of the Warriors of Shadow")
        {  
            TP->emote_adjust_union_virtue(US_PURITY, 50);
            TP->add_prop("_Union_cleansed_in_astuary", time());
        }

        while(ob = present("dirty", TP))
        {
            TP->catch_tell("You feel much less dirty now.\n");
            ob->remove_object();
        }

        return 1;
    }

    if (arg == "bubbles")
    {
        write("You lather the soap and raise it to your lips.\n"+
           "A stream of bubbles floats into the air on the wings "+
           "of your breath.\n");
        say(QCTNAME(this_player()) +" raises "+ short() +" to "+ 
            TP->query_possessive() +" mouth and blows gently on it.\n"+
           "A stream of small soap bubbles floats into the air.\n");       

        return 1;
    }

    return notify_fail("Do what with the soap? Try help soap.\n");
}

public void
init(void)
{
    ::init();

    if (this_player() != environment())
	return;

    add_action(do_soap, "s");
}

public string
query_recover(void)
{
    return MASTER + ":";
}
