inherit "/std/armour";
inherit "/lib/keep";

#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <formulas.h>
#include <macros.h>
#include <filter_funs.h>
#include <composite.h>
#include <cmdparse.h>

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/common/warfare/warfare.h"

#define ARMOUR_CLASS 1

object wearer;
int coin_inserted = 0;

string
platinum_insert()
{
    if(!coin_inserted)
        return "In the centre of the amulet is a circular groove, " +
            "clearly designed to fit a Krynnish-minted steel coin.";
    else
        return "In the centre of the amulet is a circular groove " +
            "with a steel coin inserted into it.";
}

void
create_armour()
{
    setuid();
    seteuid(getuid());

    set_name("amulet");
    add_adj("dark");
    set_short("dark amulet");
    set_long("A dark amulet, inscribed with draconic runes of violence. " +
        platinum_insert()+ "\n");

    set_ac(ARMOUR_CLASS);
    set_at(A_NECK);
    set_af(TO);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_ID_INFO,
      ({"A magical amulet enchanted to seek death and violence on the " +
        "battlefields of Krynn. When grasped by those skilled in " +
        "divination magic, it provides insights on remaining combatants " +
        "on the battlefield. A steel coin needs to be inserted into " +
        "the amulet to activate its scrying ability, and will eventually " +
        "be consumed in the process of divination.\n",60}));
    add_prop(MAGIC_AM_MAGIC,({30,"divination"}));
    add_prop(OBJ_I_WEIGHT, 1500);
    add_prop(OBJ_I_VOLUME, 2500);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(50));

    add_cmd_item(({"amulet","dark amulet"}),"grasp","@@grasp_medallion");

}

string
query_warfare_location(string str)
{
    if(str == "Newports Area")
        return "newports";
    if(str == "Western Solamnian Plains")
        return "west_solamnia";
    if(str == "Estwilde Plains")
        return "estwilde";
    if(str == "Solace Area")
        return "solace";
    if(str == "Central Abanasinian Plains")
        return "central_abanasinia";
    if(str == "North Abanasinian Plains")
        return "north_abanasinia";
    if(str == "Nightlund Plains")
        return "nighlund";
    if(str == "Guardlund Plains")
        return "guardlund";
    if(str == "Throtyl Pass")
        return "throtyl";
    if(str == "Icewall Plains")
        return "icewall";
    if(str == "Trelgorn Forest")
        return "trelgorn";
    if(str == "Abanasinian Plains")
        return "central_abanasinia";
    if(str == "Eastern Solamnian Plains")
        return "nighlund";

    return "solace";
}

mixed 
check_warfare_object(mixed foe)
{
    if(objectp(foe))
        return foe;
}

string
grasp_medallion()
{
    if(!coin_inserted)
    {
        write("You grasp the " +TO->short()+ ". Nothing " +
            "seems to happen.\n");
        say(QCTNAME(TP)+ " grasps the " +TO->short()+ ".\n");
        return "";
    }

    if(TP->query_skill(SS_FORM_DIVINATION) < 30)
    {
        write("You grasp the " +TO->short()+ ". You feel " +
            "images buzz through your head, but you do not " +
            "have enough discipline with divination to make " +
            "any sense of it.\n");
        say(QCTNAME(TP)+ " grasps the " +TO->short()+ ".\n");
        return "";
    }

    if(environment(this_player())->query_area_name())
    {
        string area_name = environment(this_player())->query_area_name();
        string area = query_warfare_location(area_name);
        int foe_count = 0;

        if(!sizeof(find_object(AREA_PATH + area)->query_actual_units()))
            return "Strangely there are no defenders that you can find.\n";

//        mixed * locations = map(find_object(AREA_PATH + area)->query_actual_units(),  
//             environment);

        mixed * locations = map(find_object(AREA_PATH + area)->query_actual_units(),  
            check_warfare_object);
    
        // Remove dead units
        locations -= ({ 0 });

        if(!sizeof(locations))
            return "There are no defenders that you can find. Strange.\n";

        locations = map(locations, environment);

        foreach(mixed foe: locations)
        {
            if(!objectp(foe))
               locations -= ({ foe });
            else
               foe_count += 1;
        }

        if(!sizeof(locations))
            return "There are no defenders that you can find.\n";

        int locs = sizeof(locations);
        int ran_loc = random(locs);

        if(!objectp(locations[ran_loc]))
            return "You were unsuccessful in finding a defender for this area.\n";

        object location = locations[ran_loc];
        object * inv = all_inventory(location);    
        object * live = FILTER_LIVE(inv);
        object * dead = FILTER_DEAD(inv);

        write("You grasp the " +TO->short()+ ". You feel your senses soar " +
            "above the battlefield...\n\n");
        say(QCTNAME(TP)+ " grasps the " +TO->short()+ ".\n");

	this_player()->catch_tell("There are approximately " +foe_count+ " " +
            "units still defending the " +area_name+ ".\n\n");
	this_player()->catch_tell(location->long());
    
        if (sizeof(dead))
        {
            this_player()->catch_msg(capitalize(COMPOSITE_DEAD(dead))+".\n");
        }
        if (sizeof(live))
        {
            this_player()->catch_msg(capitalize(COMPOSITE_LIVE(live))+".\n");
        }

        // 25% chance the steel coin burns out
        if(!random(4))
        {
	    this_player()->catch_tell("\nThe steel coin inserted into the " +
                TO->short()+ " glows intensely and crumbles to dust.\n");
            coin_inserted = 0;
            set_long("A dark amulet, inscribed with draconic runes of violence. " +
                platinum_insert()+ "\n");
        }

        return "";
    }

    return "You are not at a battlefield where you can scry for defenders.\n";
}

int
insert_coin(string str)
{
    string steel_coin, amulet;
    object * oblist; 
    object steel_coins;

    object player = this_player();

    if(!str)
    {
        notify_fail("Insert what? A steel coin?\n");
        return 0;
    }

    if (!parse_command(str, ({}), "[the] %s 'into' [the] %s", steel_coin, amulet))
    {
        notify_fail("Insert <what> into <what>?\n");
        return 0;
    }

    if (!sizeof(oblist = FIND_STR_IN_ARR(steel_coin, all_inventory(player))))
    {
        notify_fail("You possess no " + steel_coin + ".\n");
        return 0;
    }

    if(!oblist[0]->id("_krynn_warfare_token"))
    {
        if(oblist[0]->id("coin"))
        {
            notify_fail("Your " +oblist[0]->short()+ " doesn't " +
                "seem to be the right size to insert.\n");
            return 0;
        }
        notify_fail("Your " +oblist[0]->short()+ " doesn't " +
            "seem to be the right size to insert.\n");
        return 0;
    }

    if (coin_inserted)
    {
        notify_fail("The " +TO->short()+ " already has a steel coin " +
            "in it.\n");
        return 0;
    }
 
    steel_coins = oblist[0];
 
    write("You insert a steel coin into the " +TO->short()+ ".\n");
    say(QCTNAME(TP)+ " inserts a steel coin into the " +
        TO->short()+ ".\n");
    steel_coins->reduce_heap_size();
    coin_inserted = 1;
    set_long("A dark amulet, inscribed with draconic runes of violence. " +
        platinum_insert()+ "\n");

    return 1;
}


void
init()
{
    ::init();
    add_action(insert_coin, "insert");
    add_action(insert_coin, "affix");
}
