/*
 * File Name        : sash.c
 * By               : Elmore.
 * Inspiration from : Occ_fighter Guild by Unknow.
 * Date             : Nov. 2000.
 * Description      : This is the guild item for the pirates.
 *                    It is possible to wear and remove this
 *                    object.
 *
 */

#pragma strict_types

inherit "/std/object";

#include "../local.h"
#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include "/d/Krynn/common/defs.h"
#include <formulas.h>
#include <wa_types.h>


int worn = 0;
int head = 0;

void
create_object()
{
    set_name("sash");
    add_name("_pirates_sash_ansalon");
    set_adj("black");
    add_adj("silver-lined");	
    set_short("black silver-lined sash");
    set_long("@@my_long");

    add_prop(OBJ_M_NO_DROP, "You cannot drop the sash.\n");
    add_prop(OBJ_M_NO_GET,  1);
    add_prop(OBJ_M_NO_SELL, 1);
    add_prop(OBJ_M_NO_BUY,  1);
    add_prop(OBJ_I_WEIGHT,  100);
    add_prop(OBJ_I_VOLUME,  100);
    remove_prop(OBJ_I_VALUE);
}

string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
    {
        if (head == 1)
            return "You have tied your black silver-lined sash around your head.\n";
        else
            return "You are wearing your black silver-lined sash.\n";
    }
    if (for_obj == me)
        if (head == 1)
            return "You have tied your black silver-lined sash around your head.\n";
        else
            return "You are wearing your black silver-lined sash.\n";
    else
    {
        if (head == 1)
            return C(PRONOUN(me)) + " is wearing " + POSSESSIVE(me) +
	    " black silver-lined sash around " + POSSESSIVE(me) + " head.\n";
        else
            return C(PRONOUN(me)) + " is wearing " + POSSESSIVE(me) +
	    " black silver-lined sash.\n";

    }

}

int
query_worn()
{
    return worn;
}

int
wear(string str)
{
    if (query_worn() || !strlen(str))
    {
        notify_fail("Wear what?\n");
        return 0;
    }
    if (str == "sash" || str == "black sash" || str == "silver-lined black sash" ||
        str == "silver-lined sash")
    {
        write("You tie your black silver-lined sash around your hip.\n");
        say(QCTNAME(TP) + " ties a black silver-lined sash around " +
    	POSSESSIVE(TP) + " hip.\n");
        TP->add_subloc("the_pirates_sash", TO);
        set_no_show_composite(1);
        worn = 1;
        head = 0;
       return 1;
    }
}

int
tie(string str)
{
    if (query_worn() || !strlen(str))
    {
        notify_fail("Tie what?\n");
        return 0;
    }
    if (str == "sash" || str == "black sash" || str == "silver-lined black sash" ||
        str == "silver-lined sash")
    {
        write("You tie your black silver-lined sash around your head.\n");
        say(QCTNAME(TP) + " ties a black silver-lined sash around " +
    	POSSESSIVE(TP) + " head.\n");
        TP->add_subloc("the_pirates_sash", TO);
        set_no_show_composite(1);
        head = 1;
        worn = 1;
        return 1;
    }
}

varargs int
remove(string str,object who = TP)
{   
    if (!query_worn())
      return 0;

    if (str == "sash" || str == "black sash" || str == "silver-lined black sash" ||
        str == "silver-lined sash")
    {
        if (head == 1)
        {
            write("You remove the black silver-lined sash around your head.\n");
            tell_room(E(TP),QCTNAME(TP) + " removes the black silver-lined sash around " +
    	          POSSESSIVE(TP) + " head.\n",TP);
        }
        else
        {
            write("You remove the black silver-lined sash from your hip.\n");
            tell_room(E(TP),QCTNAME(TP) + " removes a black silver-lined sash from " +
        	          POSSESSIVE(TP) + " hip.\n",TP);
        }
    
        who->remove_subloc("the_pirates_sash");
        set_no_show_composite(0);
        worn = 0;
        head = 0;
        return 1;
    }
}

void
init()
{
    if (!interactive(TP))
      return;
    ADA("remove");
    ADA("wear");
    ADA("tie");
}


string
my_long()
{
    return "This is a black sash, worn only by the feared pirates of "+
           "the Bloodsea. Thin silver threads have been woven into the "+
           "fabric, it shimmers slightly as you move the sash in the "+
           "sunlight. The words 'help pirates' have been printed on it.\n";
}

