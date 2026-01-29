/* 
 * Flower shop in Telseron
 * By Finwe
 * September 1996
 */
 
inherit "/std/room";
inherit "/d/Emerald/lib/shop_list";
 
#include "/d/Emerald/defs.h"
#define EMERALD_FLOWER          "_garden_flower"
 
int      wilt_time, wilt_left, wilt_stopped, wilt_alarm, inited_once;
void
create_room()
{
    config_default_trade();
    set_money_greed_sell(95);
    set_money_greed_buy(95);
    set_money_give_out(({10000, 500, 10, 2}));
    set_money_give_reduce(({0, 4, 20, 15}));
    reset_room();
    
    set_short("The florist shop");
    set_long("   The florist shop is nice and airy. A sweet fragrance " +
        "of rose, honeysuckle, gardenia, and other flowers drifts " +
        "through the shop. A large counter runs the length of the " +
        "shop. It is covered with clippings and tools the " +
        "florist uses. Across one wall are shelves " +
        "crowded with arrangements available for sale. " +
        "You see a plaque on the wall.\n\n");
 
    add_item("tools", 
        "These tools include some clippers and cutting tools.\n");
    add_item("counter", 
        "The counter is made from a large piece of wood. It was " +
        "once polished but now, it shows its age. Many knife marks " +
        "are visible in its surface.\n");
    add_item(({"shelf", "shelves"}),
        "The shelves are heavily laden with arrangements and " +
        "corsages.\n");
    add_item("plaque", 
        "Rich gold letters are inscribed on it.\n");
    add_cmd_item("plaque", "read", "@@read_plaque@@");
    add_item("counter", 
        "It is polished darkwood with some jars sitting on it.\n");
    add_item( ({ "cases", "display cases" }),  
        "Looking closer at the display cases, you see items which " +
        "available for sale. It would be better to check " +
        "out the price list for a full detail of the items.\n");
 
    add_prop(ROOM_I_INSIDE, 1);
 
    add_exit(TOWNSHIP_DIR + "rd19", "out");
    add_exit("@@query_store_room@@", "up", "@@wiz_check@@", 0);
 
    config_default_trade();
    set_store_room(TOWNSHIP_DIR + "flower_store");
}
 
void
init()
{
    ::init();
    init_shop();
}
 
int 
shop_hook_allow_sell(object ob) 
    { 
        if (!ob->query_prop(EMERALD_FLOWER)) 
        { 
            notify_fail("The florist says: That's not one of my " +
                "cultivated flowers.\n");
            return 0; 
        } 
    else
    {
        ob->stop_wilt();
        return 1;
    }   
}
 
 
int 
shop_hook_allow_buy(object ob) 
    { 
        if (!ob->query_prop("_garden_flower")) 
        { 
            notify_fail("The florist says: I don't have any in stock\n"); 
            return 0; 
        } 
    else
    {
        ob->start_wilt();
        return 1;
    }   
}
 
/*
 * Function name: wilt
 * Description:   This function is called with an alarm, and simulates the
 *                wilting of flowers
 */
int
wilt()
{
    object env;
    string mess;
 
    wilt_alarm = 0;
 
    if (env = environment())
    {
        mess = "The " + short() + " slowly dries up and dies from lack " +
            "of water.\n";
        if (living(env))
            tell_object(env, mess);
        else if (env->query_prop(ROOM_I_IS))
            tell_room(env, mess);
    }
            
    remove_object();
    return 1;
}
 
/*
 * Function name: set_wilt_time
 * Description:   Set the wilting time of the flower
 * Argumetns:     i - The time (in seconds)
 */
void
set_wilt_time(int i) { wilt_time = i; }
 
 
/*
 * Function name: query_wilt_time
 * Description:   Checks how long it takes for the flower to wilt
 * Returns:       The time in seconds
 */
int                             
query_wilt_time() { return wilt_time; }
 
 
/*
 * Function name: stop_wilt
 * Description:   halts the wilting process of the flower temporarily.
 *                use start_wilt to have the flower resume wilting.
 */
void
stop_wilt(object obj)
{
    if (!inited_once || wilt_stopped)
        return;
    wilt_left = ftoi(get_alarm(wilt_alarm)[2]);
    remove_alarm(wilt_alarm);
    wilt_alarm = 0;
    wilt_stopped = 1;
} 
 
 
/*
 * Function name: restart_wilt
 * Description:   Starts the wilting process of a flower
 *                by stop_wilt.
 */
void
restart_wilt()
{
  if (!wilt_stopped) return;
  wilt_alarm = set_alarm(itof(wilt_left), 0.0, wilt);
  wilt_stopped = 0;
}
 
 
/*
 * Function name: start_wilt
 * Description:   Start the wilt process of the flower
 */
void
start_wilt(object obj)
{
    if (!inited_once)
    {
        if (wilt_time)
            wilt_alarm = set_alarm(itof(wilt_time), 0.0, wilt);
        inited_once = 1;
    }
}
 
string
read_plaque()
{
    return "Welcome to the Florist Shop of Telseron. Lovely " +
        "flowers can be purchased or sold here.\n";
}
