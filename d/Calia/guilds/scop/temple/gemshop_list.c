
/*
 * shop_list.c
 *
 * Written by Quetzl, 9/10/95 for the improvment of the shop 'list' command
 */

inherit "/lib/shop";

#include <filter_funs.h>
#include "defs.h"
 

mapping gem_list;
 
static mixed *store_oblist;
static string
    f_categ,
    endlin = "+--------------------------------------------------" +
        "-----------------------+\n",
    polin =  "| Gems For Sale                                 "+
        "                       |\n",
    blklin = "|              |                                     |" +
        "      |             |\n",
    catlin = "|     Name     |             Description             | Qty. "+
    "|  P  G  S  C |\n",
    reglin = "| %-12s | %-35s | %4d | %2d %2d %2d %2d |\n",
    prev_categ,
    *filarr;
 
static int n_refig = 1;
 
 
public void
shop_hook_buy_no_buy(object ob, string str)
{
    ::shop_hook_buy_no_buy(ob, str);
    n_refig = 1;
}
 
public void
oprint_item(string gem_file, int qty)
{
    object temp;
    
    if (qty > 0)
    {
        temp = clone_object(gem_file);
        temp->add_prop("temp_wgem_shop",qty);
        temp->move(find_object(query_store_room()));
    }
}

public string
print_item(string hname)
{
    int price,qty;
    string ret;
    object temp,room;
    ret = "";
    room = find_object(query_store_room());
    temp = present(hname,room);
    price = query_buy_price(temp);
    qty = temp->query_prop("temp_wgem_shop");
    if(qty == 0)
        return ret;
    ret += sprintf(reglin,extract(temp->query_gem_name(),0,11),  
    extract(temp->short(), 0, 34), qty,
        price / 1728, (price % 1728) / 144, (price % 144) / 12, price % 12);
    temp->remove_object();
    return ret;
}

public string
print_shop_list(mapping hl, int lt)
{
    string *gem_files,*gnames,ret;
    int i, j;
    gem_files = m_indexes(hl);
    i = sizeof(gem_files);

    ret = endlin + catlin + endlin;

    if(lt == 3 || lt == 2)
    {
        if (i == 0)
        {
            ret = "No gems.\n";
        }

        for (j = 0; j < i; j++)
            oprint_item(gem_files[j],hl[gem_files[j]]);
        gnames = all_inventory(find_object(query_store_room()))->query_gem_name();
        gnames = sort_array(gnames);
        i = sizeof(gnames);
        for(j = 0; j < i; j++)
            ret += print_item(gnames[j]);
        ret += endlin;
    }

    return ret;
}
 
public int
do_sell(string arg)
{
    if (::do_sell(arg))
    {
        return 1;
    }
    return 0;
}
 
public int
do_buy(string arg)
{
    if (::do_buy(arg))
    {
        return 1;
    }
    return 0;
}
  
public int
do_list(string arg)
{
    int lt;
    gem_list = restore_map(SPIRIT_OBJECTS+"gemlist");

    if (!strlen(arg))
        lt = 3;

    if(arg == "gems")
        lt = 2;
    if (!m_sizeof(gem_list))
    {
        shop_hook_list_empty_store("");
        return 0;
    }
 
    setuid();
    seteuid(getuid());
    TP->more(print_shop_list(gem_list,lt));
    return 1;
}

public void
init_shop()
{
    ::init_shop();
    add_action(do_list, "mlist");
    add_action(do_list, "list");
}
