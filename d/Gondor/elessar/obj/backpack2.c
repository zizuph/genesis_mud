/*
 * /d/Gondor/common/guild/obj/backpack.c
 *
 * A backpack to carry stuff in. It has sell-protection.
 *
 * /Mercade, 24 January 1993
 *
 * Revision history:
 * Modified for the Rangers by Elessar, May 1994.
 */

inherit "/std/receptacle";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <composite.h>
#include "/d/Gondor/defs.h"

#define NO_SELL_PROP BSN("You do not want to sell the backpack. Do " + \
    "<keep backpack> to remove the protection.")
#define NO_SELL_VBFC "@@no_sell_vbfc@@"
#define BACKPACK_SUBLOC  "_ranger_backpack"
int worn;

void
create_container()
{
    add_name("backpack");
    add_name("pack");
    add_name("rucksack");
    add_name("knapsacks");

    set_pname("sacks");
    add_pname("backpacks");
    add_pname("packs");
    add_pname("rucksacks");
    add_pname("knapsacks");

    add_adj("large");
    add_adj("camouflaged");
    add_adj("green-coloured");

    set_short("large camouflaged backpack");
    set_pshort("backpacks");
    set_long("@@long_description");

    add_prop(OBJ_M_NO_SELL,  NO_SELL_PROP);
    add_prop(OBJ_I_VALUE,             200);
    add_prop(CONT_I_CLOSED,             1);
    add_prop(CONT_I_WEIGHT,          2000);
    add_prop(CONT_I_VOLUME,          2500);
    add_prop(CONT_I_MAX_WEIGHT,    150000);
    add_prop(CONT_I_MAX_VOLUME,    150000);
    add_prop(CONT_I_REDUCE_VOLUME,    125);
    remove_prop(CONT_I_RIGID);
}

string
long_description()
{
    string long_desc = "The backpack is rather large and made of a very " +
        "light, yet strong material. Its colours are various shades of green so that it " +
        "offers the best possible camouflage for the travelling Rangers. "+
	"If you type 'fillpack' you can put all unequipped items, except "+
	"money and containers into the backpack. And if you type 'emptypack' "+
	"you fetch all the items from the backpack again. ";

    if (query_prop_setting(OBJ_M_NO_SELL) == NO_SELL_PROP)
    {
        long_desc += "Presently, the backpack is protected so you " +
            "will not sell it when selling equipment. Do <keep backpack> to " +
            "remove the protection.";
    }
    else
    {
        long_desc += "Whenever you sell equipment, you might sell the " +
            "backpack. To prevent yourself from selling it you may <keep " +
            "backpack> to protect it.";
    }

    return BSN(long_desc);
}

int
wear(string str)
{
    if (str != "backpack")
        return 0;

    if (!present(TO, TP))
    {
        NF("You don't have it!\n");
        return 0;
    }

    if (worn)
    {
        NF("You are already wearing it!\n");
        return 0;
    }
  
    if (member_array(BACKPACK_SUBLOC, TP->query_sublocs()) > -1)
    { 
       NF("You already wear another backpack!\n");
       return 0;
    } 

    TP->add_subloc(BACKPACK_SUBLOC, TO);
    write("You wear the large backpack on your back.\n");
    say(QCTNAME(TP) + " wears the large backpack on " + 
             TP->query_possessive() + " back.\n");
    add_prop(OBJ_M_NO_DROP, "Remove the backpack first!\n");
    worn = 1;
    TO->set_no_show_composite(1); /*do not display in inventory */
    return 1;
}

int
remove(string str)
{
    if (str != "backpack")
        return 0;
    if (!present(TO, TP))
    {
        NF("You don't have it!\n");
        return 0;
    }
    if (!worn)
    {
        NF("You are not wearing it!\n");
        return 0;
    }
    TP->remove_subloc(BACKPACK_SUBLOC);
    write("You remove the large backpack.\n");
    say(QCTNAME(TP) + " removes the large backpack.\n");
    remove_prop(OBJ_M_NO_DROP);
    worn = 0;
    TO->set_no_show_composite(0);  /* display in inventory again */
    return 1;
}

void
leave_env(object dest, object old)
{
    TP->remove_subloc(BACKPACK_SUBLOC);
    remove_prop(OBJ_M_NO_DROP);
    ::leave_env(dest, old);
}

public string
show_subloc(string subloc, object on, object for_obj)

{
  string data;

  if(subloc==BACKPACK_SUBLOC)
  {
    if (for_obj != on)
      data = capitalize(on->query_pronoun()) + 
           " is wearing a camouflaged backpack on " +
           on->query_possessive() + " back.\n";
    else
      data = "You are wearing a camouflaged backpack on your back.\n";
    return data;
  }
}

mixed
no_sell_vbfc()
{
    if (sizeof(all_inventory(TO)))
    {
        return BSN("The backpack is not empty at the moment. Please empty " +
            "it before you sell it, to prevent loss of property.");
    }

    return 0;
}

void
init()
{
  ::init();
  add_action("fillpack","fillpack");
  add_action("emptypack","emptypack");
  add_action("do_keep", "keep");
  add_action("wear","wear");
  add_action("remove","remove");
}

int
do_keep(string str)
{
    if (!parse_command(str, TP, " [the] [large] [camouflaged] 'backpack' / " +
        "'backpack' / 'knapsack' "))
    {
        NFN0(CAP(query_verb()) + " what?");
    }

    if (ENV(TO) != TP)
    {
        NFN0("You do not have the " + TO->short() + " in your hands.");
    }

    if (query_prop_setting(OBJ_M_NO_SELL) == NO_SELL_PROP)
    {
        add_prop(OBJ_M_NO_SELL, NO_SELL_VBFC);
        write(BSN("You remove the protection. You can sell the backpack now."));
    }
    else
    {
        add_prop(OBJ_M_NO_SELL, NO_SELL_PROP);
        write(BSN("You will now keep the backpack when you are selling " +
            "equipement. To be able to sell it again, just type <keep " +
            "backpack> again."));
    }
    return 1;
}

/*
 * Recovery stuff
 */
string
query_recover()
{
    return MASTER + ":#ck#" +
        ((query_prop_setting(OBJ_M_NO_SELL) == NO_SELL_PROP) ? "1" : "0") +
        "#" + query_container_recover();
}

void
init_recover(string arg)
{
    string foobar, tmp;

    sscanf(arg, "%s#ck#%d#%s", foobar, tmp, foobar);
    if (tmp == "1")
    {
        add_prop(OBJ_M_NO_SELL, NO_SELL_PROP);
    }
    else
    {
        add_prop(OBJ_M_NO_SELL, NO_SELL_VBFC);
    }
    init_container_recover(arg);
}

int
a_filter(object ob)
{
  if (ob->query_prop(OBJ_M_NO_SELL)) return 0;
  else if (ob->query_prop(OBJ_M_NO_GIVE)) return 0;
  else if (ob->query_prop(OBJ_M_NO_DROP)) return 0;
  else if (ob->query_prop(CONT_I_IN)) return 0;   /*containers*/
  else if (ob->query_worn()) return 0;
  else if (!(ob->query_prop(OBJ_I_VALUE))) return 0;
  else if (ob->query_wielded()) return 0;
  else if (ob->query_prop(LIVE_I_IS)) return 0;
  else if (ob->query_name() == "backpack") return 0;
  else return 1;
}

int
fillpack()
{
  object tp;
  object *conts, *moved;
  int x, y;
  tp = TP;
  conts = ({ });
  moved = ({ });
  conts = filter(all_inventory(tp), "a_filter", TO);
  for (x = 0; x < sizeof(conts); x++)  {
      conts[x]->move(TO); 
      if (present(conts[x], TO))  {
         moved += ({ conts[x] }) ;   /*successful move */
      }
  }   
  if (sizeof(moved) == 0)
    tp->catch_msg("You didn't put anything in the backpack.\n");
  else {
    tp->catch_msg("You store " + COMPOSITE_DEAD(moved) + 
                                " in the large backpack.\n");
    tell_room(environment(tp), QCTNAME(tp) + " stores " + 
            COMPOSITE_DEAD(moved) + " in the large backpack.\n", tp);
  }
  return 1;
}

int
emptypack()
{
  object tp;
  object *conts, *moved;
  int x;
  
  tp = TP;

  conts = ({ });
  moved = ({ });

  conts = filter(all_inventory(TO), "a_filter", TO);
  
  for (x = 0; x < sizeof(conts); x++)  {
      conts[x]->move(tp); 
      if (present(conts[x], tp))  {
         moved += ({ conts[x] }) ;   /*successful move */
      }
  }   
  if (sizeof(moved) == 0)
    tp->catch_msg("You didn't retrieve anything from the backpack.\n");
  else {
    tp->catch_msg("You retrieve " + COMPOSITE_DEAD(moved) + 
                                " from the large backpack.\n");
    tell_room(environment(tp), QCTNAME(tp) + " retrieves " + 
            COMPOSITE_DEAD(moved) + " from the large backpack.\n", tp);
  }
  return 1;
}







