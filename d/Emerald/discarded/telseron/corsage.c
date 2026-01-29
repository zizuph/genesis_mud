/*
 * A basic corsage
 * written by Finwe, Sept. 1996
 * wear_corsage and remove_corsage code was borrowed from
 * the monk robe.
 */
 
#pragma save_binary
 
inherit "/std/object";
#include <stdproperties.h>
#include "/d/Emerald/defs.h"          
 
#define CORSAGE_SUBLOC          "emerald_florist_corsage"
 
int wear_corsage(string str);
int remove_corsage(string str);
int worn;
 
int
create_object()
{
    set_name("corsage");
    set_short("rose corsage");
    set_pname("corsages");
    set_adj("lovely");
    set_long("A lovely fragrant rose corsage. It is made from three " +
        "red rose buds surrounded by a few sprigs of baby's breath, " +
        "a fern frond, and some ribbons.\n");
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 5);
    add_prop(OBJ_I_VOLUME, 20);
    
}
 
init()
{
    ::init();
    add_action("wear_corsage", "wear");
    add_action("remove_corsage", "remove");
    add_action("smell_rose", "smell");
} 
 
 
int wear_corsage(string str)
{
    if(str != "corsage") return 0;
   
    NF("You're already wearing it!\n");
    if(worn) 
    { 
        TP->catch_msg("But you're wearing one already.\n");
        return 1;
    }
   
    NF("What do you want to wear?\n");
    if(environment(TO)!=TP) return 0;
    
    worn = 1;
    this_object()->set_no_show_composite(1);        /* added by Milan */
    say(QCTNAME(TP) + " pins a corsage onto their lapel.\n"); 
    TP->catch_msg("You pin a corsage onto your lapel.\n");
 
    TP->add_subloc(CORSAGE_SUBLOC, this_object());
   
   return 1;
 
}
 
 
int remove_corsage(string str)
 {
    if(str != "corsage") return 0;
   
   NF("But you're not wearing one.\n");
   if(!worn) return 0;
   
   worn = 0;
   
   this_object()->set_no_show_composite(0);        /* added by Milan */
   TP->remove_subloc(CORSAGE_SUBLOC); 
   
    say(QCTNAME(TP) + " removes a corsage from their lapel.\n");
    TP->catch_msg("You remove a corsage from your lapel.\n");
   
   return 1;
}
 
 
 
string
show_subloc(string subloc, object carrier, object for_obj)
{
    string str;
 
    if (for_obj == carrier)
        str = "You wear";
    else
        str = capitalize(carrier->query_pronoun()) + " wears ";
 
    return str + " a rose corsage.\n";
}

int smell_rose(string str)
{
    if (str == "corsage")
        { 
            write ("You close your eyes and smell the heady " +
                   "fragrance of the corsage. You smile " +
                   "happily, enjoying the perfume.\n");
            say (QCTNAME(this_player()) + " smells a corsage.\n");
        }
    else
        {
            write ("Smell what?\n");
        }
        return 1;
}
