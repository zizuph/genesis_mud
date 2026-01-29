/*
 * 2004-12-15 - Cotillion
 * - Modified item cloning to work better with long armageddons.
 * 
 * Navarre May 11th 2011, Since clone_unique now distributes the
 * spawning of the items, I changed the randomness as it often took
 * more than 20 kills to get a ring back after it was lost and available
 * in the realm for cloning.
 * 
 * 2016-01-24 - Cotillion 
 * - Rewrote heap cloning to prevent items in the void
 */
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam_forest/local.h"
#include <files.h>
#include <money.h>
#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include <filter_funs.h>

inherit FOREST_IN;
inherit "/lib/unique";

object chest,gem1,gem2,gem3,gem4,gem5,
sword,armour,money1,money2,
money3,ring,scroll;
int treasure = 1;

#define PLAYER_I_ENTER_LAIR "_player_i_enter_lair"
#define SPINEL_GEM      ("/d/Genesis/gems/obj/spinel_red")
#define EMERALD_GEM     ("/d/Genesis/gems/obj/emerald")
#define ORB             (FOBJ + "black_orb")
#define BOW             ("/d/Krynn/qualinesti/wep/singing_bow")
#define HAUBERK         ("/d/Ansalon/balifor/flotsam_forest/obj/armour/vin_hauberk")
#define RING            (ARMOUR + "ring1")
#define SCROLL          ("/d/Krynn/common/scrolls/prot_poison_scroll")

/* Check if id is present, if not clone, set heap size */
void
reset_heap_size(string id, string file, int count) 
{
    object ob = present(id);
    if (!objectp(ob)) {
        ob = clone_object(file);
        ob->move(TO);
    }
    ob->set_heap_size(count);
}

void
reset_treasure()
{
    object ob = (previous_object(-2));

    if (ob && living(ob))
    {
        string resetor = ob->query_real_name();
        log_file("lairlog", "/d/Ansalon/balifor/flotsam_forest/dark"
                + "_forest/lair treasure reset by " + resetor + ".\n", 5000);
    }
	
    FILTER_PLAYERS(all_inventory())->command("$out");


    /* Done before all the clone_unique to allow heap merge to work */
    FILTER_COINS_OBJECTS(all_inventory())->remove_object();
    MONEY_MAKE_HERE_CC(2000);
    MONEY_MAKE_HERE_SC(200);
    MONEY_MAKE_HERE_GC(20);

    reset_heap_size("spinel", SPINEL_GEM, 4);
    reset_heap_size("emerald", EMERALD_GEM, 1);

    if (!objectp(chest))
    {
	chest = clone_object(FOBJ + "chest");
	chest->move(TO);
    }

    if (!P(scroll, TO))
    {
	scroll = clone_object(SCROLL);
	scroll->move(TO);
    }

    if (!P(ring, TO))
    {
        ring = clone_unique(ARMOUR + "ring1", 5, 0);

        if (!ring && !random(3))
        {
            ring = clone_object(ORB);   
        }

        if (objectp(ring))
        {
            ring->move(TO);
        }
    }
    
    if (!P(armour, chest))
    {
	chest->add_prop(CONT_I_CLOSED, 1);
	chest->add_prop(CONT_I_LOCK, 1);

        if(!random(3))
        {
            armour = clone_unique(ARMOUR + "vin_armour", 5, HAUBERK, 40);
            armour->move(chest,1);
        }
        else
        {
            armour = clone_object(HAUBERK);
            armour->move(chest,1);
        }
    }
	
    if (!P(sword, TO))
    {
	if(!random(3))
	{
            /* 30% chance to clone a  bow with unique 5 */
	    sword = clone_unique(BOW, 5, EMERALD_GEM, 1, 30);
	    sword->move(TO);
	}
	else
	{
	    sword = clone_unique(WEAPON + "g_slayer", 5, EMERALD_GEM, 1, 30);
	    sword->move(TO);
	}
    }
}

create_flotsam_room()
{
    set_short("Dragons lair");
    set_long("@@long_descr");
    add_prop(ROOM_I_NO_CLEANUP, 1);

    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_TELEPORT_TO, 1);
    add_prop(ROOM_M_NO_TELEPORT_FROM, 1);
    add_prop(ROOM_M_NO_SCRY, "Noxious-looking fumes obscure your vision.\n");

    add_item(({"earthern cavern","cavern","lair"}),"@@long_descr");
    add_item(({"noxious gas","gas"}),"Putrid yellow gas that smells " +
      "of rotten eggs and carbide fills the cavern, obscuring much " +
      "of its details.\n");
    add_item(({"treasure","great pile of treasure","pile of treasure",
	"riches","gems","hoard","treasure hoard","ancient weapons",
	"weapons","armours"}),
      "In the middle of the cavern is the treasure hoard of the great " +
      "green dragon. Gems of all colours sparkle alluringly in the dim " +
      "light, as do the thousands of coins of all makes and sizes from " +
      "all parts of Ansalon. Ancient weapons and armours from many " +
      "eras of history lie half buried amongst the hoard. You do not " +
      "doubt that all this could make you a very wealthy person.\n");

    add_exit(FOREST_PATH + "/dark_forest/clearing","out","@@out");
    add_cmd_item(({"treasure","pile of treasure","hoard",
	"ancient weapons from pile of treasure","ancient weapons",
	"ancient weapons from treasure","gems from treasure",
	"gems from pile of treasure","get gems from hoard"}),
      ({"get","take","pick","search"}),"@@get_treasure");

}

string
long_descr()
{
    return "You stand in a huge underground earthern cavern, the " +
    "lair of a great green dragon! Your eyes are drawn instantly " +
    "to the great pile of treasure sitting in the middle of the " +
    "cavern... more than a kings ransom! Apart from the riches that " +
    "fills the cavern, the room is also filled with noxious gas " +
    "that also assaults your senses, but in not as pleasant a manner.\n";
}

int
out()
{
    write("You head up the tunnel towards the clearing...\n");
    return 0;
}

string
get_treasure()
{
    write("As you attempt to get close to the large " +
      "pile of treasure in the middle of the chamber, the noxious " +
      "gas around it becomes too strong to handle. " +
      "You step away from the " +
      "treasure, feeling rather sick.\n");
    say(QCTNAME(TP) + " attempts to get close to the great pile " +
      "of treasure in the middle of the cavern, but the noxious " +
      "gas around it is too strong for " +
      HIM(TP) + " to stomach.\n");
    return "";
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(!living(ob))
	return;

    if(ob->query_prop(PLAYER_I_ENTER_LAIR))
	return;

    ob->add_prop(PLAYER_I_ENTER_LAIR, 1);
}
