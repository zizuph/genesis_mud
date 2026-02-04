// sash.c
// Guild Item for the Riders of Last Layman guild.
// Tomas  April 2000

inherit "/std/armour";

#include <wa_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <std.h>
#include <const.h>
#include <macros.h>
#include "../include/guild.h"


#pragma save_binary
#pragma strict_types


string query_auto_load() { return MASTER + ":"; }
string get_color();
/* cannot be both recoverable and autoloadable */
string query_recover() { return 0; }


void
create_armour()
{
  set_name(RIDER_GUILD_EMBLEM_ID);
  add_name("sash");
  set_short((get_color() + " sash"));
  add_adj("@@get_color()");
  add_pname(({"sashes"}));
  set_long ("A silk sash worn by the members of the Riders of Last.\n " +
     "Type <rlhelp index> for help.\n");

  set_wf (TO);
  set_ac (1);
  set_am (({ 0, 0, 0}));
  set_at (A_WAIST);


  add_prop(OBJ_M_NO_DROP,"Oddly enough, you can't seem to "+
     "do that.\n");
  add_prop(OBJ_M_NO_GIVE, "It's sentimental value is too high "+
     "for you to simply give it away.\n");
  add_prop(OBJ_M_NO_SELL, "The shopkeeper finds it uninteresting.\n");
  add_prop(OBJ_M_NO_STEAL, 1);

  seteuid(getuid());


}


mixed
wear(object ob)
{
   TP->add_subloc(RIDER_SUBLOC, TO);
   TP->update_hooks();
   return 0;

}


mixed
remove(object ob)
{
    TP->remove_subloc(RIDER_SUBLOC);
    TP->update_hooks();
    return 0;
}



/*
 * Function name: show_subloc
 * Description:   This function is called each time someone looks at us
 * Arguments:     subloc  - the subloc string
 *                on      - the wearer
 *                for_obj - the one looking
 * Returns:           The string that is to be seen (subloc)
 */
string
show_subloc(string subloc, object on, object for_obj)
{
   
    if (subloc != RIDER_SUBLOC)
        return this_player()->show_subloc(subloc, on, for_obj);
  
    if (for_obj == on)
        return "You are a member of the Riders of Last.\n";
    else
        return capitalize(PRONOUN(on)) +" is wearing a sash " +
           "bearing the symbol of the Riders of Last.\n";
}


public string
get_color()
{
    int guildstat;
    string color;
    guildstat = (TP->query_base_stat(8));
    color = "dirty-white";

    switch (guildstat)
    {
       case 1..24:  
           return "grey";  
           break;
       case 25..48:
           return "brown";
           break;
       case 49..72:
           return "dark-blue";
           break;
       case 73..96:
           return "red";
           break;
       case 97..120:
           return "crimson";
           break;
    }
}
