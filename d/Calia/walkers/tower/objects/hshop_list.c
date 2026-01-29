
/*
 * shop_list.c
 *
 * Written by Quetzl, 9/10/95 for the improvment of the shop 'list' command
 */

inherit "/lib/shop";

#include <filter_funs.h>
#include "defs.h"
 

mapping herb_list;
 
static mixed *store_oblist;
static string
    f_categ,
    endlin = "+--------------------------------------------------" +
        "-----------------------+\n",
    polin =  "| Potions For Sale                                 "+
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
oprint_item(string herb_file, int qty)
{
    object temp;
    temp = clone_object(herb_file);
    temp->add_prop("temp_wherb_shop",qty);
    temp->move(find_object(query_store_room()));
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
    qty = temp->query_prop("temp_wherb_shop");
    if(qty == 0)
        return ret;
    ret += sprintf(reglin,extract(temp->query_herb_name(),0,11),  
    extract(temp->short(), 0, 34), qty,
        price / 1728, (price % 1728) / 144, (price % 144) / 12, price % 12);
    temp->remove_object();
    return ret;
}

public string
print_shop_list(mapping hl, int lt)
{
    string *herb_files,*hnames,ret;
    int i, j;
    herb_files = m_indexes(hl);
    i = sizeof(herb_files);

    ret = endlin + catlin + endlin;

    if(lt == 3 || lt == 2)
    {
        if (i == 0)
        {
            ret = "No herbs.\n";
        }

        for (j = 0; j < i; j++)
            oprint_item(herb_files[j],hl[herb_files[j]]);
        hnames = all_inventory(find_object(query_store_room()))->query_herb_name();
        hnames = sort_array(hnames);
        i = sizeof(hnames);
        for(j = 0; j < i; j++)
            ret += print_item(hnames[j]);
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
    herb_list = restore_map(TOWER_OBJECTS+"herblist");

    if (!strlen(arg))
        lt = 3;

    if(arg == "herbs")
        lt = 2;
    if (!m_sizeof(herb_list))
    {
        shop_hook_list_empty_store("");
        find_player("bishop")->catch_msg("We got this far.\n");
        return 0;
    }
 
    setuid();
    seteuid(getuid());
    TP->more(print_shop_list(herb_list,lt));
    return 1;
}

public void
init_shop()
{
    ::init_shop();
    add_action(do_list, "mlist");
    add_action(do_list, "list");
}
