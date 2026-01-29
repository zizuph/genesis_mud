/*
 * 
 *  coded by Amelia for Ten Alders 4/13/97
 *  specials  when witch apprentice present, buys and
 *             sells herbs
 *       can also buy an herb jar or pouch here
 */

#pragma strict_types

inherit "/d/Earthsea/std/room";
inherit "/sys/global/money";
inherit "/lib/shop";
inherit "/sys/global/composite";

#include <stdproperties.h>
#include <cmdparse.h>
#include <macros.h>
#include <money.h>
#include <composite.h>
#include <ss_types.h>
#include <filter_funs.h>
#include <files.h>

#define HERBALIST "/d/Earthsea/gont/tenalders/npc/witch_apprentice"
#define HERBJAR "/d/Earthsea/herbs/obj/herb_jar"
#define HERBPOUCH "/d/Earthsea/herbs/obj/herb_pouch"
#define POMADE "/d/Earthsea/gont/tenalders/obj/items/pomade"
#define DOOR_N "/d/Earthsea/gont/tenalders/obj/doors/h_store_in"
#define HERB_SAVE_FILE "/d/Earthsea/gont/tenalders/village/herb_save"
#define JAR_PRICE 200
#define POUCH_PRICE 50
#define POMADE_PRICE 100

int buy_equip(string str);
int read_sign(string str);
int list_items(string str);


object          herbalist;

object door_n;

/* Of format <herb name>: (<number>, <value>, <file_path>) */
//mapping herbs = (["dummy": ({1, 200, "/d/ckrik/dummy"})]);
mapping herbs = ([]);
string save_file;
int max_herbs = 500;

public int remove_herbs(string herb, int number)
{
  mixed *entry;

  entry = herbs[herb];
  if (!entry)
    {
      return 0;
    }
  if (entry[0] >= number)
    {
      entry[0] -= number;
      herbs[herb] = entry;
    }
  if (entry[0] <= 0)
    {
      herbs = m_delete(herbs, herb);
    }
  save_map(herbs, save_file);
  return 1;
}

public int add_herb(object ob, int number)
{
  string name;
  mixed *entry;;

  if (!living(ob) && stringp(ob->query_herb_name()))
    {
      name = implode(explode(ob->query_herb_name(), " "), "_");
      if (!herbs[name])
    {
      entry = ({MIN(max_herbs, number), ob->query_herb_value(), MASTER_OB(ob)});
      herbs += mkmapping(({name}), ({entry}));
    }
      else 
    {
      entry = herbs[name];
      entry[0] = MIN(max_herbs, entry[0] + number);
      herbs[name] = entry;
    }
      /* Have to remove this later because shop still needs it 
       */
      save_map(herbs, save_file);
      return 1;
    }
  return 0;
}

public int query_herb_quantity(string herb)
{
  mixed *entry;
  if (!strlen(herb))
    {
      return 0;
    }
  entry = herbs[herb];
  if (entry)
    {
      return entry[0];
    }
  return 0;
}

public int query_herb_value(string herb)
{
  mixed *entry;
  if (!strlen(herb))
    {
      return 0;
    }
  entry = herbs[herb];
  if (entry)
    {
      return entry[1];
    }
  return 0;
}

public string query_herb_file(string herb)
{
  mixed *entry;
  if (!strlen(herb))
    {
      return "";
    }
  entry = herbs[herb];
  if (entry)
    {
      return entry[2];
    }
  return "";
}

public string *query_herbs()
{
  return m_indexes(herbs);
}

public int query_number_herbs()
{
  return m_sizeof(herbs);
}

public void set_save_file(string file)
{
  //  debug("setting save file to " + file + "\n");
  save_file = file;
}

public void set_max_herb_quantity(int n)
{
  max_herbs = n;
}

static int check_valid_herb(mixed *entry)
{
  if (file_size(entry[2]) <= 0)
    {
      return 0;
    }
  return 1;
}

/* Purge all herbs that are no longer valid */
public void purge_invalid_herbs()
{
  mapping selects;
  string *indices;
  int i, s;

  selects = filter(herbs, check_valid_herb);
  indices = m_indexes(selects);
  
  for (i = 0, s = sizeof(indices);
       i < s; i++)
    {
      herbs = m_delete(herbs, indices[i]);
    }
  save_map(herbs, save_file);
}

public void init_herb_store()
{
  herbs = restore_map(save_file);
  purge_invalid_herbs();
}

void
reset_room()
{
  if (!objectp(herbalist))
    {
      herbalist = clone_object(HERBALIST);
      herbalist->move(this_object());
      herbalist->arm_me();
      herbalist->command("emote enters.");
      (clone_object(POMADE))->move(herbalist);
      herbalist->command("apply pomade");
    }
}

void
create_earthsea_room()
{
  config_default_trade();
  set_money_greed_sell(95);
  set_money_greed_buy(95);
  set_save_file(HERB_SAVE_FILE);
  set_max_herb_quantity(600);
  init_herb_store();
  set_short("Herb store");
  set_long("This appears to be some sort of "+
          "storeroom. There are many shelves along the walls, "+
          "each filled with jars, bottles, and leather "+
          "containers of all shapes and sizes and colours. "+
          "There are bundles of drying herbs hanging from poles on "+
          "the ceiling, as well as ropes of onions, "+
          "garlic, and hot peppers. It is fragrant "+
          "here with the scent of herbs and spices, "+
          "and more exotic aromas hard to identify. "+
          "There is a small counter here with a stool "+
          "beside it. You see a sign on the wall above "+
          "it.\n");
  add_item((({"bottles", "jars", "containers",
        "leather containers"})),
       "The containers on the shelves seem to contain all sorts of "+
       "preserved herbs, spices, and other implements. The witch "+
       "appears to do a thriving business in herbs.\n");
  add_item((({"shelf", "shelves"})),
       "The wooden shelves run the lengths of three walls "+
       "and extend from floor to ceiling. They are loaded with "+
       "big and small bottles, jars, and other containers.\n");
  add_item("ceiling",
       "You can see the inner side of the thatched roof, "+
       "with its dense roots. Poles run along the ceiling, "+
       "where herbs of all kinds have been hung to dry.\n");
  add_item("floor",
      "The floor is sunk below ground level, and "+
       "is comprised of hard-packed earth.\n");
  add_item((({"wall", "walls"})),
      "The walls are made of fragrant pine panels.\n");
  add_item((({"pole", "bundles", "bundle"})),
       "Bundles of drying herbs hang from a wooden "+
       "pole in the ceiling.\n");
  add_item((({"herb", "herbs"})),
       "Herbs of all kinds fill this room with "+
       "diverse piquant aromas.\n");
  add_item((({"onions", "peppers", "red peppers",
        "garlic"})),
      "Ropes of garlic, onions and peppers "+
       "hang drying from the pole in the ceiling.\n");
  add_item((({"counter", "small counter", "stool"})),
       "There is a small counter which looks like "+
       "an overturned wooden barrel, beside which is "+
       "a wooden stool where the apprentice sits.\n");
  door_n = clone_object(DOOR_N);
  door_n->move(this_object());
  
  add_item("sign", "The sign reads:\n" +
       "------------------------------\n" +
       " Here you can - list herbs  \n" +
       "              - list equipment\n" +
      "              - sell herbs    \n" +
       "              - buy equipment     \n" +
       "              - buy herbs     \n");
  reset_room();
  add_prop(ROOM_I_LIGHT, 1);
  add_prop(ROOM_I_IS, 1);
  add_prop(ROOM_I_INSIDE, 1);
  
}

void
init()
{
    ::init();
    add_action(&read_sign(), "read");
    add_action(&buy_equip(), "buy");
    add_action(&list_items(), "list");
    add_action(do_sell, "sell");
}

int
read_sign(string str)
{

    notify_fail("Read what?\n");
    if (str == "sign") 
    {
    write("The sign reads:\n" +
      "------------------------------\n" +
      " Here you can - list herbs \n" +
      "              - list equipment\n" +
      "              - sell herbs    \n" +
      "              - buy equipment     \n" +
      "              - buy herbs     \n");
    return 1;
    }
    return 0;
}

int
shop_hook_allow_sell(object ob)
{
  if (this_object()->filter_herb(ob))
    return 1;
  
  notify_fail("The store only buys herbs.\n");
  return 0;
}

int
filter_herb(object ob)
{
    return IS_HERB_OBJECT(ob);
}

int
query_sell_price(object ob)
{
  object tp = this_player();

  return MAX((tp->query_skill(SS_TRADING) + 
          tp->query_skill(SS_HERBALISM)) / 2, 50) * 
    ob->query_herb_value() / 100 * ob->num_heap();
}

int
query_herb_buy_price(int value)
{
    return value;
}
/*
 * Function name: redefining sell_it from the basic shop (just for herbs)
 * Description:   Try to let the player sell the item array
 * Arguments:     ob - the object array
 *                check - wheather check for worn or wielded stuff
 *                str - string describing how the money should be paid
 * Returns:       An array with the objects sold
 */

object *
sell_it(object *ob, string str, int check) 
{
    int price, total, i, j, k, *null, *value_arr, *null_arr, err;
    object *sold;
    mixed tmp;

    null_arr = allocate(sizeof(query_money_types())) + ({});
    sold = allocate(sizeof(ob));
    total = 0;
    for (i = 0; i < sizeof(ob); i++)
    {
    if (!shop_hook_allow_sell(ob[i]))
        continue;

    if (ob[i]->query_herb_value == 0)
    {
        shop_hook_sell_no_value(ob[i]);
        continue;
    }

    if (check && (ob[i]->query_worn() ||
        ob[i]->query_wielded()))
    {
        shop_hook_sell_worn_or_wielded(ob[i]);
        continue;
    }

    if (tmp = ob[i]->query_prop(OBJ_M_NO_SELL))
    {
        shop_hook_sell_no_sell(ob[i], tmp);
        continue;
    }

    /* Save price if ob destructed in move */
    price = query_sell_price(ob[i]);

    if (price <= 0)
    {
        shop_hook_sell_no_value(ob[i]);
        continue;
    }

    if (!add_herb(ob[i], ob[i]->num_heap()))
      {
        shop_hook_sell_no_sell(ob[i], 1);
      }

    if (price > 0)
    {
      sold[j] = ob[i];
      j++;
        total += price;
        if (j >= 20)
        break;
        /*
         * Only let people sell 20 objects at once and hopefully we wont get
         * those too long evaluation problems.
         */
    }
    }

    sold = sold - ({ 0 });

    if (sizeof(sold) > 0)
    {
      value_arr = split_values(total);
      value_arr[2] += value_arr[3] * 12;
      value_arr[3] = 0;
      //value_arr = calc_change(total, null, str);
      change_money(null_arr + value_arr, this_player());
      shop_hook_sell_get_money(text(value_arr));
    }

    return sold;
}


int
list_items(string str)
{
  string result = "";
  object tp = this_player();
  int i;

  if (!objectp(herbalist))
    {
      write("Ariel is not here to do business with you.\n");
      return 1;
    }
  if (str == "equipment" || str == "equip" ||
      str == "herbs" || !str)
    {
      result += "                           Ariel's Herb Shop\n\n";
      result += "                               @}-}--\n";
      result += "---------------------------------------------------------------------------\n";
      if (!str || str == "herbs")
    {
      result += do_list("herbs");
    }
      if (!str || str == "herbs")
    {
      result += "---------------------------------------------------------------------------\n";
      if (str == "herbs")
        {
          tp->more(result, 0);
          return 1;
        }
    }
      
      if (str == "equipment" || str == "equip" || !str)
    {
      if (str == "equipment" || str == "equip")
        {
          result +="                    Equipment and Specialty Items\n";
          result += "---------------------------------------------------------------------------\n";
        }
      result += "\n";
      result += "     ";
      result += "                    herb pouch        50 cc\n";
      result += "     ";
      result += "                      herb jar       200 cc\n";
      result += "     ";
      result += "      rose pomade for the lips       100 cc\n";
      result += "---------------------------------------------------------------------------\n";
      tp->more(result, 0);
      return 1;
    }
      return 1;
    }
  write("List what? Equipment? Herbs?\n");
  return 1;
}

/* Function name:  buy_equip()
 * for selling jars and pouches
 * Returns: 1 if successful
 */

int
buy_equip(string str)
{
    object tp = this_player();
    object stuff;
    int price;

    setuid();
    seteuid(getuid(this_object()));

    if (!objectp(herbalist))
    if (!present("ariel", this_object()))
    {
        tp->catch_msg("The herbalist is not here for business.\n");
        return 1;
    }

    switch (str)
    {
    case "jar":
    case "herb jar":
    stuff = clone_object(HERBJAR);
    price = JAR_PRICE;
    break;

    case "pouch":
    case "herb pouch":
    stuff = clone_object(HERBPOUCH);
    price = POUCH_PRICE;
    break;

    case "pomade":
    case "rose pomade":
    stuff = clone_object(POMADE);
    price = POMADE_PRICE;
    break;


    default:
        return do_buy(str);
    }

    if (!take_money(tp, price))
    {
    herbalist->command("say " +
      " Sorry but you can't afford it right now!");
    stuff->remove_object();
    }

    tp->catch_msg("You pay the price and get "+
      LANG_ASHORT(stuff) + ".\n");
    if (stuff->move(tp))
    {
    stuff->move(this_object());
    tell_room(this_object(), QCTNAME(herbalist) + " sets "+
      LANG_ASHORT(stuff) + " on the counter.\n", ({}));
    }
    return 1;
}


/*
 * Function name: shop_hook_list_object
 * Description:   List an object
 * Arguments:     ob - The object 
 * Slight redefinition of original function from 
 * the /lib/shop.c == Amelia 4/5/98
 * 
 */
string
shop_hook_list_herb(string herb, int no, int price)
{
    string str, num, mess;
    int platinum, gold, silver, copper;
    int *values;

    platinum = gold = silver = copper = 0;
    values = split_values(price);
    if (sizeof(values))
    {
    copper = values[0];
    silver = values[1];
    gold = values[2];
    platinum = values[3];
    }

    str = sprintf("| %-3d | %-30s | %#3d pc | %#3d gc | %#3d sc | %#3d cc |",
      no, herb, platinum,
      gold, silver, copper);
    /*
    if (mess = text(split_values(price)))
        write(break_string(num + str + mess + ".\n", 70));
    else
        write(str + "That item wouldn't cost you much.\n");
    */
    str += "\n";
    return str;
} 


string
shop_hook_list_empty_store(string str)
{
  string result = "";
  result += "          ";
  result += "     ***** Ariel is currently out of herbs ***** \n";
  return result;
}

int shop_hook_buy_no_match(string str)
{
    herbalist->command("say " +
             " Sorry I don't have " + str + " in stock " +
             "now.");
  return 1;
}

/*
 * Function name: do_buy
 * Description:   Try to let the player buy an item
 * Arguments:     string - describing how to pay and get change
 * Returns:       1 on sucess
 */
int
do_buy(string str)
{
  object *herbs;
  object tp = this_player();
  string str1, str2, str3, str4;
  int quantity, num, i, flag;
  int price;
  
  if (!objectp(herbalist))
    {
      notify_fail("Ariel is not here to do business with you.\n");
      return 1;
    }
  
  if (!str || str =="")
    {
      notify_fail("Buy what?\n");
      return 1;
    }
  
  /*  Did the player specify payment and change? */
  if (sscanf(str, "%s for %s and get %s", str1, str2, str3) != 3)
    {
      /* Well, maybe player has defined how payment will be done atleast? */
      str3 = "";
      if (sscanf(str, "%s for %s", str1, str2) != 2)
    {
      str2 = "";
      str1 = str;
    }
    }
  str4 = str1;
  if (sscanf(str1, "%d %s", num, str1) != 2)
    {
      num = 1;
      str1 = str4;
    }
  str1 = implode(explode(str1, " "), "_");
  quantity = query_herb_quantity(str1);
  
  if (quantity <= 0)
    return shop_hook_buy_no_match(str4);
  if (quantity < num)
    {
    herbalist->command("say " +
             " Sorry but I do not have " + 
             str + " right now.");
      return 1;
    }
  if (num > 20)
    {
    herbalist->command("say " +
             " Sorry but I can only handle 20 items at a time.");
      return 1;
    }
  price = query_herb_value(str1) * num;
  
  if (!take_money(this_player(), price))
    {
      herbalist->command("say "+ 
             " Sorry but you can't afford it right now!");
      return 1;
    }    
  setuid();
  seteuid(getuid(this_object()));
  /* remove the herb */
  herbs = allocate(num);
  for (i = 0; i < num; i++)
    {
      herbs[i] = clone_object(query_herb_file(str1));
      herbs[i]->force_dry();
      herbs[i]->start_decay();
    }
  remove_herbs(str1, num);
  /* clone it */
  tell_room(environment(tp), QCTNAME(tp) + " bought " + str4 + ".\n",
        tp);
  tp->catch_msg("You pay the price and get "+
        str4 + ".\n");
  flag = 0;
  for (i = 0; i < num; i++)
    {
      if (herbs[i]->move(tp))
    {
      flag = 1;
      herbs[i]->move(this_object());
    }
    }
  if (flag)
    {
      tell_room(this_object(), QCTNAME(herbalist) + " sets "+
        str4 + " on the counter.\n", ({}));
    }

    return 1;
}

/*
 * Function name: do_sell
 * Description:   Try to let the player sell the_item
 *                Observe there is no message written when sold item
 *                has a value higher than the shop gives out.
 * Returns:       1 on sucess
 * Arguments:     str - string holding name of item, hopefully
 */
int
do_sell(string str)
{
    object *item, store;
    int i, value, check;
    string str1, str2;

    if (!objectp(herbalist))
      {
    notify_fail("Ariel is not here to do business with you.\n");
    return 1;
      }
    if (!str || str =="")
    {
    notify_fail("Sell what?\n");
    return 0;
    }

    /*  Did player specify how to get the money? */
    if (sscanf(str, "%s for %s", str1, str2) != 2)
    {
    str1 = str;
    str2 = "";
    }

    if (str1 == "all!")
    {
    str1 = "all";
        check = 0; /* Sell worn or wielded objects. */
    }
    else
    {
    check = 1; /* Don't sell worn or wielded objects. */
    }

    item = FIND_STR_IN_OBJECT(str1, this_player());
    if (!sizeof(item))
    {
    return shop_hook_sell_no_match(str1);
    }

    item = sell_it(item, str2, check);
    if (sizeof(item))
    {
        shop_hook_sold_items(item);
          for (i = 0; i < sizeof(item); i++)
        {
            if (item[i]->num_heap() == 0)
            {
                item[i]->remove_object();
            }
            else
            {
                item[i]->remove_split_heap();
            }
        }
    return 1;
    }

    if (str1 == "all")
    {
        return shop_hook_sold_nothing();
    }

    return 0; /* Player tried to sell a non sellable object. */
}

/*
 * Function name:   do_list
 * Description:     Provide a list of objects in the store room
 * Returns:         0 if not recognised
 *                  1 otherwise
 * Arguments:       str - the name of the objects to search for
 */
string
do_list(string str)
{
    int i, s;
    int *prices, *num;
    string *herbs;
    string result = "";

    if (query_number_herbs() <= 0)
      {
    result += shop_hook_list_empty_store(str);
      }
    herbs = query_herbs();
    herbs = sort_array(herbs);
    for (i = 0, s = sizeof(herbs); i < s; i++)
      {
    result += shop_hook_list_herb(implode(explode(herbs[i], "_"), " "), 
                      query_herb_quantity(herbs[i]),
                      query_herb_value(herbs[i]));
      }
    return result;
}




/*
 * Function name:   do_value
 * Description:     Let the player value an item, carry or in shop
 * Returns:         1 on success
 */
int
do_value(string str)
{
  return 0;
}


