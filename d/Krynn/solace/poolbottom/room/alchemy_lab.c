#include "/d/Krynn/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/sohm/defs.h"

inherit POOLBOTTOM_IN;
inherit "/lib/skill_raise"; 
inherit "/d/Gondor/common/lib/potion_shop";

#define POTION_NUM	0

object alchemist;

// Prototypes
public void     set_up_skills();

void
reset_poolbottom_room()
{
    if(!objectp(alchemist))
    {
        setuid();
        seteuid(getuid());
        alchemist = clone_object(LIVING + "faldarten");
        alchemist->move(this_object());        
    }
}

create_poolbottom_room()
{
    seteuid(getuid(TO));
    config_default_trade();
    set_store_room(ROOM + "alchemy_store");
    (ROOM + "alchemy_store")->load_me();

    set_short("alchemy lab in the school of High Magic");
    set_long("You stand in the alchemy lab in the school of High Magic. " +
      "Your nose is assailed by scents strange and exotic - potentially " +
      "toxic - from the transmutational experiments of the alchemists " +
      "who work here. Along the walls are a number of tables covered with " +
      "crucibles, large glass retorts bubbling with strange liquids, and " +
      "unstacked aludels. In the centre of the room is a Furnace of Arcana, " +
      "an alchemist's oven providing consistent heat for alchemy experiments.\n");

    add_item(({"alchemy lab","lab"}),
      "You stand in the alchemy lab in the school of High Magic. Here you can " +
      "buy wares from the alchemist to help you with your experiments and " +
      "potion creation.\n");

    add_item(({"experiments","transmutational experiments","tables","walls",
      "alchemical experiments"}),
      "Along the walls are tables covered with with achemical experiments best " +
      "not interfered with.\n");

    add_item(({"crucibles","crucible","containers","ceramic containers"}),
      "A number of ceramic containers capable of withstanding very high heat " +
      "can be found here, used for a range of alchemical experiments.\n");

    add_item(({"retorts","retort","large glass retorts","glass retorts",
      "strange liquids","liquids"}),
      "Large glass retorts - spherical vessels with long downward-pointing " +
      "necks - bubble away noisily, with vapours occasionally escaping and " +
      "adding to the strange smells in the lab.\n");

    add_item(({"aludels","unstacked aludels"}),
      "Unstacked pots without bottoms, usually fitted one over another and " +
      "used as a condenser in the sublimation process at the end-stages of " +
      "transformation experiments, are neatly arranged on the tables.\n");

    add_item(({"furnace of arcana","furnace","oven","alchemist's oven"}),
      "In the centre of the room is a Furnace of Arcana, providing " +
      "consistent heat for alchemy experiments.\n");

    add_exit(ROOM + "landing","west",0);

    set_tell_time(60);
    add_tell("A green liquid bubbles away noisily in a nearby retort as " +
      "the strange substance is distilled.\n");
    add_tell("Foul vapours escape from a nearby retort, making you gag.\n");

    // Set up the room as a training room
    create_skill_raise();
    set_up_skills();

    reset_poolbottom_room();
}

public void
init()
{
    ::init(); 
    init_skill_raise();
    init_potion_shop(); 
}

public void
set_up_skills()
{
    sk_add_train(SS_ALCHEMY, "mix potions", 0, 0, 50);
}

public varargs int
sk_hook_allow_train(object who, string str, string verb)
{
    setuid();
    seteuid(getuid());
    // Only allow those who are members to train here.
    if (!SOHM_MANAGER->query_is_member(who))
    {
        who->catch_msg("Only those who are currently enrolled in the "
            + "school of High Magic can train here.\n");
        return 0;
    }
        
    return 1;
}

/*
 * Function name:   do_list
 * Description:     Provide a list of potions in the store room
 * Arguments:       str - dummy, not used
 * Returns:         0 if not recognised
 *                  1 otherwise
 */
int
do_list(string str)
{
    int     i, n, 
            price;
    mapping potions;
    object  pot;
    string *potion_files;
    seteuid(getuid());
    call_other(store_room, "load_me");
    potions = store_room->query_potions();
    if (!m_sizeof(potions))
        shop_hook_list_empty_store(str);
    potion_files = sort_array(m_indexes(potions));
    if(strlen(str) == 0)
    { 
        write("List what? List [potions/wares]\n");
    }
    else if(str == "potions")
    {
        write("       ==== The alchemist sells the following potions: ====\n\n");
        for (i = 0, n = sizeof(potion_files); i < n; i++)
        {
            if (file_size(potion_files[i]+".c") > 0)
            {
                call_other(potion_files[i], "load_me");
                if (objectp(pot = find_object(potion_files[i])))
                {
                    price = query_buy_price(pot);
                    shop_hook_list_potion(potions[potion_files[i]][POTION_NUM],
    		    pot, price);
                }
            }
        }
        write("\n   " + EXPAND_LINE("=", 61) + "\n"); 
    }
    else if (str == "wares" || str == "other wares")
    {
        write("       ==== The alchemist offers the following wares too: ====\n\n");
        call_other(mortar_file, "load_me");
        shop_hook_list_other(find_object(mortar_file),
            query_buy_price(find_object(mortar_file)));
        call_other(satchel_file, "load_me");
        shop_hook_list_other(find_object(satchel_file),
            query_buy_price(find_object(satchel_file)));
        call_other(vial_file, "load_me");
        shop_hook_list_other(find_object(vial_file),
            query_buy_price(find_object(vial_file)));
        write("\n   " + EXPAND_LINE("=", 61) + "\n");
    }
    else
    {
        write("List what? List [potions/wares]\n");
    } 
    return 1;
}

void
smell_air()
{
    write("The air is filled by the smell of strange potions and experiments.\n");
    return;
}