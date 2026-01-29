/*
 * /d/Gondor/common/guild/obj/backpack.c
 *
 * A backpack to carry stuff in. It has sell-protection.
 *
 * /Mercade, 24 January 1993
 *
 * Revision history:
 * Composed by the best parts from Mercade's rucksack and
 * Maniac's backpack.   For the Rangers, by Elessar, May 1994.
 * Modified the backpack so it can be inherited for other
 * backpacks, sacks, etc with different descriptions.
 * Olorin, 30-may-1995
 */

inherit "/std/receptacle";

#include <cmdparse.h>
#include <composite.h>
#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Gondor/defs.h"

#define NO_SELL_VBFC "@@no_sell_vbfc@@"
#define BACKPACK_SUBLOC  "_ranger_backpack"

int     worn;
string  fill_verb = "fillpack",
        empty_verb = "emptypack",
        backpack_long;

void    set_fill_verb(string s) { fill_verb = s; }
void    set_empty_verb(string s) { empty_verb = s; }
string  query_backpack_long() { return backpack_long; }
void    set_backpack_long(string s) { backpack_long = s; }


string
query_no_sell_prop()
{
    return "You do not want to sell the "+query_name()
      + ". Do <keep "+query_name()+"> to remove the protection.\n";
}

void
create_backpack()
{
    set_name("backpack");
    add_name("pack");
    add_name("rucksack");
    add_name("knapsack");

    add_pname("backpacks");
    add_pname("packs");
    add_pname("rucksacks");
    add_pname("knapsacks");

    add_adj("large");
    add_adj("camouflaged");
    add_adj("green-coloured");

    set_short("large camouflaged backpack");
    set_pshort("backpacks");

    set_backpack_long("The backpack is rather large and "
      + "made of a very light, yet strong material. Its colours are "
      + "various shades of green so that it offers the best possible "
      + "camouflage for the travelling Rangers.");
}

void
create_container()
{
    create_backpack();

    set_long("@@long_description");

    add_prop(OBJ_M_NO_SELL,  query_no_sell_prop());
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
    string  long_desc = query_backpack_long();

    long_desc += 
        " If you type '"+fill_verb+"' you can put all unequipped items, "
      + "except money and containers into the "+query_name()+". And if "
      + "you type '"+empty_verb+"' you fetch all the items from the "
      + query_name()+" again. ";

    if (query_prop_setting(OBJ_M_NO_SELL) == query_no_sell_prop())
    {
        long_desc += "Presently, the "+query_name()+" is protected "
          + "so you will not sell it when selling equipment. Do <keep "
          + query_name()+"> to remove the protection.";
    }
    else
    {
        long_desc += "Whenever you sell equipment, you might sell the " 
          + query_name()+". To prevent yourself from selling it you "
          + "may <keep "+query_name()+"> to protect it.";
    }

    return BSN(long_desc);
}

int
wear(string str)
{
    if (!id(str))
        return 0;

    if (!present(TO, TP))
    {
        NF("You don't have it!\n");
        return 0;
    }

    if (worn)
    {
        write("You are already wearing it!\n");
        return 1;
    }
  
    if (member_array(BACKPACK_SUBLOC, TP->query_sublocs()) > -1)
    { 
       NF("You already wear another backpack!\n");
       return 0;
    } 

    TP->add_subloc(BACKPACK_SUBLOC, TO);
    write("You wear the "+short()+" on your back.\n");
    say(QCTNAME(TP) + " wears the "+short()+" on " + 
             TP->query_possessive() + " back.\n");
    add_prop(OBJ_M_NO_DROP, "Remove the "+query_name()+" first!\n");
    worn = 1;
    TO->set_no_show_composite(1); /*do not display in inventory */
    return 1;
}

int
remove(string str)
{
    if (!id(str))
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
    write("You remove the "+short()+".\n");
    say(QCTNAME(TP) + " removes the "+short()+".\n");
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
           " is wearing "+LANG_ADDART(short())+" on " +
           on->query_possessive() + " back.\n";
    else
      data = "You are wearing "+LANG_ADDART(short())+" on your back.\n";
    return data;
  }
}

mixed
no_sell_vbfc()
{
    if (sizeof(all_inventory(TO)))
    {
        return BSN("The "+query_name()+" is not empty at the "
          + "moment. Please empty it before you sell it, to "
          + "prevent loss of property.");
    }
    return 0;
}

void
init()
{
    ::init();
    add_action("fillpack", fill_verb);
    add_action("emptypack", empty_verb);
    add_action("do_keep", "keep");
    add_action("wear","wear");
    add_action("remove","remove");
}

int
do_keep(string str)
{
    object *objs;

    if (!strlen(str) || !parse_command(str, TP, "%i", objs))
    {
        NFN0(CAP(query_verb()) + " what?");
    }

    objs = NORMAL_ACCESS(objs, 0, 0);

    if ((sizeof(objs) != 1) || (objs[0] != TO))
    {
        NFN0(CAP(query_verb()) + " what?");
    }

    if (ENV(TO) != TP)
    {
        NFN0("You do not have the " + query_name() + " in your hands.");
    }

    if (query_prop_setting(OBJ_M_NO_SELL) == query_no_sell_prop())
    {
        add_prop(OBJ_M_NO_SELL, NO_SELL_VBFC);
        write(BSN("You remove the protection. You can sell the "
          + query_name() + " now."));
    }
    else
    {
        add_prop(OBJ_M_NO_SELL, query_no_sell_prop());
        write(BSN("You will now keep the "+query_name()+" when you are selling " +
            "equipment. To be able to sell it again, just type <keep " +
            query_name() + "> again."));
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
        ((query_prop_setting(OBJ_M_NO_SELL) == query_no_sell_prop()) ? "1" : "0") +
        "#" + query_container_recover();
}

void
init_recover(string arg)
{
    string foobar, tmp;

    sscanf(arg, "%s#ck#%d#%s", foobar, tmp, foobar);
    if (tmp == "1")
    {
        add_prop(OBJ_M_NO_SELL, query_no_sell_prop());
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
    else if (ob->query_name() == "note") return 0;
    else if (ob->query_name() == "message") return 0;
    else return 1;
}

int
fillpack()
{
    object  tp = TP,
           *conts = ({}),
           *moved = ({});
  int x, y;

    if (ENV(TO) != TP)
    {
        NF("But you do not have the "+query_name()+"!\n");
        return 0;
    }
    conts = filter(all_inventory(tp), "a_filter", TO);
    for (x = 0; x < sizeof(conts); x++)  
    {
        conts[x]->move(TO); 
        if (present(conts[x], TO))  
        {
            moved += ({ conts[x] }) ;   /*successful move */
        }
    }   
    NF("You didn't put anything in the "+query_name()+".\n");
    if (sizeof(moved) == 0)
        return 0;
    else 
    {
        tp->catch_msg("You store " + COMPOSITE_DEAD(moved) + 
                                " in the "+short()+".\n");
        tell_room(environment(tp), QCTNAME(tp) + " stores " + 
            COMPOSITE_DEAD(moved) + " in the "+short()+".\n", tp);
    }
    return 1;
}

int
emptypack()
{
    object  tp = TP,
           *conts = ({ }),
           *moved = ({ });
    int     x;
  
    if (ENV(TO) != TP)
    {
        NF("But you do not have the "+query_name()+"!\n");
        return 0;
    }
    conts = filter(all_inventory(TO), "a_filter", TO);
  
    for (x = 0; x < sizeof(conts); x++)  
    {
        conts[x]->move(tp); 
        if (present(conts[x], tp))  
        {
            moved += ({ conts[x] }) ;   /*successful move */
        }
    }   
    if (sizeof(moved) == 0)
        tp->catch_msg("You didn't retrieve anything from the "+query_name()+".\n");
    else 
    {
        tp->catch_msg("You retrieve " + COMPOSITE_DEAD(moved) + 
                                " from the "+short()+".\n");
        tell_room(environment(tp), QCTNAME(tp) + " retrieves " + 
            COMPOSITE_DEAD(moved) + " from the "+short()+".\n", tp);
    }
    return 1;
}

