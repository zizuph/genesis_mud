/* gem_shop.c */
/*
    Modified: 3 May 2003, by Bleys
        - added some variable text based on race size based on
            a good suggestion from a mortal. Why should armours
            be the only beneficiary of our race size tracker?

    Modified: Jan 2021, by Lucius
        - Use different shop list code
*/

#include "/d/Terel/include/Terel.h"
inherit STDROOM;
inherit "/lib/shop";
inherit "/d/Genesis/gems/gem_shop";
inherit "/d/Emerald/lib/shop_list";

#define KILL_LOGGER CALATHIN_DIR + "obj/kill_logger"

int race_invis_enemy();
int enemy_check();

object keeper, door;


void
create_room()
{
    setuid();
    seteuid(getuid());

    set_short("Marila's Fine Gems");
    set_long("You've entered Marila's Fine Gems, before you stands "+
        "a counter. The counter is filled with numerous types "+
        "of gems found throughout all of the lands. @@counter_extra@@ " +
        "The store itself is finely crafted in oak. The doorway "+
        "north leads back out to the road.\n");
    add_item("counter","The counter is made of wood, like most things in this town. "+
        "Various types of gems are displayed on it.\n");
    add_item("tools","@@tool_desc");

    create_gem_shop();
    set_store_room(CALATHIN_DIR +"gem_store");
    door = clone_object(CALATHIN_DIR + "obj/gem_door");
    door->move(TO);
    reset_room();
}

void
init()
{
    ::init();
    init_gem_shop();
}

int
shop_hook_allow_sell(object ob)
{
    if (race_invis_enemy())
        return NF("");

    if (!gem_shop_filter_gems(ob))
    {
        gem_shop_hook_sell_non_gem(ob);
        return NF("");
    }

    return 1;
}

int
shop_hook_allow_buy(object ob)
{
    if (race_invis_enemy())
        return NF("");

    if (!gem_shop_filter_gems(ob))
    {
        gem_shop_hook_sell_non_gem(ob);
        return NF("");
    }

    return 1;
}

/*
 * Function name: reset_room
 * Description:   clone the hotel keeper if necessary
 */
public void
reset_room()
{
    if (!keeper) {
        keeper = clone_object(CALATHIN_DIR +"npc/marila");
        keeper->move(TO);
    }
}

int
race_invis_enemy()
{
    int chat = random(5);

    if (TP->query_prop(OBJ_I_INVIS))
    {
        switch(chat)
        {
            case 0:
                keeper->command("peer");
                keeper->command("shrug");
                break;
            case 1..2:
                keeper->command("scratch");
                keeper->command("say Damn rats.");
                break;
            case 3:
                keeper->command("say Someone say something?");
                keeper->command("peer");
                break;
            case 4:
                keeper->command("say Who's there?");
                keeper->command("peer");
                break;
        }
        return 1;
    }

    if (!CAN_SEE_IN_ROOM(keeper) || !CAN_SEE(keeper, TP))
    {
        switch(chat)
        {
            case 0:
                keeper->command("say If you want to do business turn on "+
                              "the light.");
                keeper->command("shrug");
                break;
            case 1..2:
                keeper->command("scratch");
                keeper->command("say I can't see what you want to sell.");
                break;
            case 3:
                keeper->command("say Someone say something?");
                keeper->command("peer");
                break;
            case 4:
                keeper->command("say Who's turned out the lights?");
                keeper->command("peer");
                break;
        }
        return 1;
    }

    if (enemy_check())
    {
        switch(chat)
        {
            case 0:
                keeper->command("say You enter our home and slay us and now "+
                "you want us to do business with you?");
                break;
            case 1:
                keeper->command("say I refuse to do business with enemies of "+
                "our town!");
                break;
            case 2:
                keeper->command("say Get out! I want no business from you!");
                break;
            case 3:
                keeper->command("say You've got a lot of nerve, get out of "+
                "here!");
                break;
            case 4:
                keeper->command("say Leave now, or if the guards don't find "+
                "you I'll call them!");
                break;
        }
        return 1;
    }

    if (TP->query_race_name() == "goblin")
    {
        switch(chat)
        {
            case 0:
                keeper->command("say I don't deal with goblins.");
                break;
            case 1:
                keeper->command("say I won't do business with goblins.");
                break;
            case 2:
                keeper->command("say Get out, I don't do business with "+
                "goblins.");
                break;
            case 3:
                keeper->command("say Goblins will recieve no business in "+
                "Calathin.");
                break;
            case 4:
                keeper->command("say I don't buy, sell, value, or trade to "+
                "goblins.");
                break;
        }
        return 1;
    }
    return 0;
}

int
enemy_check()
{
    object kill_logger = find_object(KILL_LOGGER);
    if (kill_logger->query_killer(TP->query_name()))
    {
        return 1;
    }
    return 0;
}

int
get_race_size()
{
    return RACE_SIZE_TRACKER->query_race_size(TP->query_race_name());
}

string
counter_extra()
{
    int race_size = get_race_size();

    if (race_size != SMALL)
    {
        return "Behind the counter you can see "+
            "various tools used for cutting gems.";
    }

    return "You cannot see what may lie behind the counter.";

}

string
tool_desc(string what)
{
    int race_size = get_race_size();

    if (race_size != SMALL)
    {
        return "The tools are used to cut and design gems "+
            "and pieces of jewelry.\n";
    }

    return "You find no tools.\n";
}

string
figure_category(object ob)
{
    if (ob->query_gem())
        return "Gem";
    else
        return "General";
}
