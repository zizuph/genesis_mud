
/*
 * shop_list.c
 *
 * Written by Quetzl, 9/10/95 for the improvment of the shop 'list' command
 */

inherit "/lib/shop";
#include "/d/Kalad/defs.h"
#include "/d/Kalad/common/guilds/khiraa/khiraa_defs.h"
#include <filter_funs.h>
 

mapping herb_list;
mapping lo_list;
 
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
 
public string
print_item(string herb_file, int qty)
{
    int price;
    object temp;
    string ret = "";
    if(qty == 0)
        return ret;
    temp = clone_object(herb_file);
    price = query_buy_price(temp);
    ret += sprintf(reglin,extract(temp->query_herb_name(),0,11),  
    extract(temp->short(), 0, 34), qty,
        price / 1728, (price % 1728) / 144, (price % 144) / 12, price % 12);
    temp->remove_object();
    return ret;
}

public string
print_po_item(string potion_file, int qty)
{
    int price;
    string ret;
    object temp;
    ret = "";
    if(qty == 0)
        return ret;
    temp = clone_object(potion_file);
    price = query_buy_price(temp);
    ret += sprintf(reglin,extract(temp->query_potion_name(),0,11), 
    extract(temp->short(),0,34),qty,   
        price / 1728, (price % 1728) / 144, (price % 144) / 12, price % 12);
    return ret;
}
    

public string
print_shop_list(mapping hl, mapping lol, int lt)
{
    string *herb_files,*lo_files,ret;
    int i, j;
    herb_files = m_indexes(hl);
    lo_files = m_indexes(lol);
    i = sizeof(herb_files);

    ret = endlin + catlin + endlin;

    if(lt == 3 || lt == 2)
    {
        if (i == 0)
        {
            ret = "No herbs.\n";
        }

        for (j = 0; j < i; j++)
            ret += print_item(herb_files[j],hl[herb_files[j]]);
        ret += endlin;
    }

    if(lt == 3 || lt == 1)
    {
        ret += polin;
        ret += endlin;

        i = sizeof(lo_files);

        if (i == 0)
        {
            ret += "No Potions.\n";
        }

        for(j = 0; j < i; j++)
            ret += print_po_item(lo_files[j],lol[lo_files[j]]);
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
    herb_list = restore_map(KHIRAA_DIR(log/herb_master));
    lo_list = restore_map(KHIRAA_DIR(log/potion_master));

    if (!strlen(arg))
        lt = 3;;

    if(arg == "potions")
        lt = 1;
    if(arg == "herbs")
        lt = 2;
    if (!m_sizeof(herb_list) && !m_sizeof(lo_list))
    {
        shop_hook_list_empty_store("");
        return 0;
    }
 
    if (query_verb() == "mlist")
    {
        setuid();
        seteuid(getuid());
        TP->more(print_shop_list(herb_list,lo_list,lt));
        return 1;
    }
    write(print_shop_list(herb_list,lo_list,lt));
    return 1;
}

public void
init_shop()
{
    ::init_shop();
    add_action(do_list, "mlist");
}
