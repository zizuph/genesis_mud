 /*****************************************************************************
*  /d/Kalad/common/set/beggar/beggarssack.c
*
*  beggarssack File for Beggars Set
*
*  Created Oct 20th 2020, Greneth
*
*  Info  : Thin Leather Sack
* 
*  Credit: Earthsea Purse
 *****************************************************************************/
 
 /*****************************************************************************
*  Defines
 *****************************************************************************/
#define SUBLOC "_tied_sack_subloc_"

 /*****************************************************************************
*  Includes
 *****************************************************************************/
#include "/d/Kalad/defs.h"
#include <macros.h>
#include <stdproperties.h>
#include <wa_types.h>
#include <files.h>

 /*****************************************************************************
*  Inherits
 *****************************************************************************/
inherit "/std/receptacle";
inherit "/lib/keep";

 /*****************************************************************************
*  Pragma
 *****************************************************************************/
#pragma strict_types

 /*****************************************************************************
*  Prototypes
 *****************************************************************************/
public int        	tie(string str);
public int        	untie(string str);

 /*****************************************************************************
*  Function name: create_receptacle
*  Description  : Creates the container
 *****************************************************************************/
public void
create_receptacle()
{
   set_keep();
   set_name("sack");
   set_adj("thin");
	add_adj("leather");
   set_short("thin leather sack");
   set_long("A sack made from the raw hide of some animal. Bits of hair that "
	+ "wasn't properly scraped off can be seen in various spots. It smells "
	+ "absolutely rancid. It's easy enough to store your valuables in and "
	+ "prevent them from getting stolen though.\n");
   add_prop(CONT_I_WEIGHT,100);
   add_prop(CONT_I_MAX_WEIGHT, 150000);
   add_prop(CONT_I_MAX_VOLUME, 150000);
   add_prop(CONT_I_REDUCE_WEIGHT, 400);
   add_prop(CONT_I_REDUCE_VOLUME, 400);
   add_prop(CONT_I_RIGID, 0);
   add_prop(CONT_I_CLOSED, 1);
   add_prop(OBJ_I_VALUE, 500);
}

 /*****************************************************************************
*  Function name: query_recover
*  Description  : Called to check whether this armour is recoverable. If you 
*                 have variables you want to recover yourself, you have to 
*                 redefine this function, keeping at least the filename and 
*                 the armour recovery variables, like they are queried below.
 *****************************************************************************/
public string
query_recover()
{
   return MASTER + ":" + query_container_recover();
}

 /*****************************************************************************
*  Function name: init_recover
*  Description  : When the object recovers, this function is called to set the 
*                 necessary variables. If you redefine the function, you must 
*                 add a call to init_arm_recover or a call to ::init_recover 
*                 with the string that you got after querying query_arm_recover
 *****************************************************************************/
public void
init_recover(string arg)
{
    init_container_recover(arg);
}


 /*****************************************************************************
*  Function name: prevent_enter
*  Description  : Called when an object is trying to enter this container to
*                 see if we will allow it in.
 *****************************************************************************/
public int
prevent_enter(object ob)
{
   if (!ob->id("coin") && !ob->id("gem")) 
   {
      write("You can only store coins and gems within.\n");
      return 1;
   }

   return 0;
}

 /*****************************************************************************
*  Function name: show_subloc
*  Description  : Shows the specific sublocation description for a living.
*  Arguments    : string subloc  - the subloc to display.
*                 object on      - the object to which the subloc is linked.
*                 object for_obj - the object that wants to see the subloc.
 *****************************************************************************/
public string
show_subloc(string subloc, object carrier, object for_obj)
{
   if(carrier->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "";

   if(for_obj == carrier)
   {
      return "You've got a thin leather sack tied to your belt.\n";
   }

   return capitalize(carrier->query_pronoun()) + " has a thin leather "
	+ "sack tied to " + carrier->query_possessive() + " belt.\n";
}

 /*****************************************************************************
*  Function name: init
*  Description  : Add some actions to the player
 *****************************************************************************/
public void
init()
{
   ::init();
   add_action(tie, "tie");
   add_action(untie, "untie");
}

 /*****************************************************************************
*  Function name: tie
*  Description  : allow the player to tie a sack to their belt
*  Arguments    : string str - what the player typed following the verb
 *****************************************************************************/
public int
tie(string str)
{
   string dcs;
	object *fbeg;

   fbeg = filter(all_inventory(this_player()), &->id("_beggars_set_belt"));
   if(!sizeof(fbeg))
   {
      notify_fail("You don't seem to be wearing a proper belt.\n");
      return 0;
   }

   if(!str || !present(TO, TP) || !parse_command(str, environment(TO),
      "%w [to] / [onto] [belt]", dcs) || !id(dcs))
   {
      return notify_fail("Tie what to what?\n");
   }

   if(query_prop(OBJ_M_NO_DROP))
   {
      return notify_fail("The sack is already tied to your belt.\n");
   }

   TP->add_subloc(SUBLOC, TO);
   write("You tie the thin leather sack to your belt tightly.\n");
   add_prop(OBJ_M_NO_DROP, "You must untie the sack first.\n");
   return 1;
}

 /*****************************************************************************
*  Function name: untie
*  Description  : allow the player to untie a sack from their belt
*  Arguments    : string str - what the player typed following the verb
 *****************************************************************************/
public int
untie(string str)
{
   string dcs;

   if(!str || !present(TO, TP) || !parse_command(str, environment(TO),
      "%w [from] [belt]", dcs) && id(dcs))
   {
      return notify_fail("Untie what?\n");
   }

   if(!query_prop(OBJ_M_NO_DROP))
   {       
		return notify_fail("The sack is not tied to your belt.\n");
   }

   write("You untie the sack from your belt.\n");
   TP->remove_subloc(SUBLOC);
   remove_prop(OBJ_M_NO_DROP);
   return 1;
}

 /*****************************************************************************
*  Function name: leave_env
*  Description  : removes the no drop prop
 *****************************************************************************/
public void
leave_env(object ob, object to)
{
   if (interactive(ob))
   {
      remove_prop(OBJ_M_NO_DROP);
   }

    ::leave_env(ob, to);
}

 /*****************************************************************************
*                           TESTING BELOW
 *****************************************************************************/

int sort_generic(object *a, object *b, function rank)
{
    if (rank(a[0]) < rank(b[0]))
    {
        return -1;
    }
    if (rank(a[0]) > rank(b[0]))
    {
        return 1;
    }
    if (a[0]->short() < b[0]->short())
    {
        return -1;
    }
    if (a[0]->short() > b[0]->short())
    {
        return 1;
    }
    return 0;
}

int score_other(object ob)
{
    if (IS_COINS_OBJECT(ob))
    {
        return 1000;
    }
    if (ob->query_gem())
    {
        return 2000;
    }
    return 10000;
}

int sort_other(object *a, object *b)
{
    return sort_generic(a, b, &score_other());
}


string render_other_type(object ob)
{
    if (IS_COINS_OBJECT(ob))
    {
        return "money";
    }
    if (ob->query_gem())
    {
        return "gem";
    }
    return "-";
}

int f_other(object ob)
{
    return !IS_WEARABLE_OBJECT(ob);
}

void describe_generic(object *obarr, object fo, function render_type)
{
    if (sizeof(obarr) == 0) return;
    int quantity = 0;
    string short_desc;
    if (IS_HEAP_OBJECT(obarr[0]))
    {
        quantity = obarr[0]->num_heap();
        short_desc = obarr[0]->singular_short();
    }
    else
    {
        quantity = sizeof(obarr);
        short_desc = obarr[0]->short();
    } 
    
    string type_desc = render_type(obarr[0]);

    fo->catch_tell(sprintf("| %-:51s | %-:14s | %4d |\n",
        short_desc, type_desc, quantity));
}


public void show_list(object fo, object *obarr)
{
   mixed* other_arr = sort_array(unique_array(filter(obarr, f_other), "short"), sort_other);
	
    if (sizeof(other_arr) > 0)
    {
        fo->catch_tell("\n");
        fo->catch_tell(
            "  Valueables                                                 Type             Qty   \n" +
            "+-----------------------------------------------------+----------------+------+\n");
        foreach(object *obs : other_arr) {
            describe_generic(obs, fo, &render_other_type());
        }
        fo->catch_tell(
            "+-----------------------------------------------------+----------------+------+\n");
    }
}

void describe_contents(object fo, object *obarr)
{
    fo->catch_tell(show_sublocs(fo));

    if (sizeof(obarr) > 0)
    {
        show_list(fo, obarr);
    }
    else
    {
        fo->catch_tell("  " + "The " + this_object()->short() +
            " is empty.\n");
    }
}