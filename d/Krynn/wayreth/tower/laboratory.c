/*
   Wayreth.

   laboratory.c
   ------------

   Coded ........: 95/06/02
   By ...........: Jeremiah

   Latest update : October 2016
   By ...........: Arman

*/

#include "/d/Krynn/wayreth/local.h"
#include "/d/Krynn/common/defs.h"
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <composite.h>
#include <cmdparse.h>
#include "/d/Krynn/common/clock/clock.h"
#include "/d/Krynn/guilds/wohs/defs.h"

inherit TOWERROOM;
inherit "/lib/skill_raise";
inherit "/d/Gondor/common/lib/potion_shop"; 

#define POTION_NUM	0

// Prototypes
public void     set_up_skills();

// object    moroth;

void
reset_tower_room()
{
/*
    if (moroth)
      return;
    moroth = clone_object("/d/Krynn/wayreth/npc/walk_black.c");
    moroth->move_living("xx",TO);
    moroth->seq_new("do_thing");
    moroth->seq_addfirst("do_thing","@@start_patrol");
*/
}

void
create_tower_room()
{
    config_default_trade();
    set_store_room("/d/Krynn/wayreth/tower/alchemy_store");

   set_short("Laboratory at the top of the Tower");
   set_long("This is the laboratory that is shared by each of " +
      "the three Orders of Magi. Arcane experiments are conducted " +
      "in this lab, and this is obvious by the amount of glassware " +
      "and other materials present on the various tables. A dank " +
      "smell hangs in the air, but it is still possible to breathe " +
      "without harm. Stairs can be seen to the east. This area " +
      "is used by some wizards as a place to train and discuss " +
      "herbalism and alchemy. Potions can also be purchased and " +
      "sold here.\n");

   AI("floor","The floor is composed of the same polished obsidian " +
      "as the walls. There is a hole in the floor, possibly a " +
      "drain, near the northwestern edge of the room.\n");
   AI(({"drain","hole","hole in the floor"}),"This drain is " +
      "used to magically teleport away any leakages or spillages " +
      "of fluids from this room. It's small holes ensure that only " +
      "liquids can be moved through.\n");
   AI(({"wall","walls"}),"The walls of this room are composed " +
      "of polished obsidian, with a magical enchantment placed " +
      "on them to prevent damage from any possible explosions " +
      "that may be caused in this room.\n");
   AI("ceiling","The ceiling in this room angles upwards to a " +
      "point, as this is the top level in the tower. There doesn't " +
      "appear to be anything special about it, other than a humming " +
      "noise that is emitted every so often.\n");
   AI(({"various tables","tables"}),"These tables are made of a " +
      "flat grey stone, magically impervious to damage by " +
      "the fact that they are near perfect.\n");
   AI(({"glass","glassware"}),"Glassware of all sorts is scattered " +
      "throughout the room, mostly on the tables. Some of the " +
      "glass containers even contain liquids, labelled 'Do not " +
      "touch'.\n");
   add_item(({"materials","other materials"}),"The other materials " +
      "include tubing, ceramics, burners and the like.\n");
   add_item("tubing","This is rubber tubing, used to connect " +
      "glassware.\n");
   add_item("ceramics","These are used as a shield against the " +
      "fire, allowing a more even distribution of heat.\n");
   add_item("burners","Small flames can be controlled with these, " +
      "and used to heat elixirs.\n");
   AI(({"smell","dank smell"}),"The smell of the area reminds " +
      "you of rotten eggs. It has a sulfurish tinge to it.\n");

   set_tell_time(180);
   add_tell("A faint humming is emitted from the ceiling.\n");
   add_tell("The smell of chemicals hangs in the air.\n");
   add_tell("An open piece of glassware suddenly fizzes!\n");
   add_tell("Faint steps can be heard on the stairwell to the east.\n");
   add_tell("Pop-op-op-op gurgles a piece of glassware with liquid " +
      "inside it.\n");

   create_skill_raise();
   set_up_skills();

   add_exit(WTOWER + "stairwell11", "east", 0);
// add_exit(WTOWER + "magicdiscuss", "down", 0);
}

public void
init()
{
    ::init(); 
    init_skill_raise();
    init_potion_shop(); 
}

public void
enter_inv (object ob, object from)
{
   ::enter_inv(ob, from);
   if (interactive(ob))
      start_room_tells();
    reset();
}

public void
set_up_skills()
{
    sk_add_train(SS_HERBALISM, "identify herbs", 0, 0, 90);
    sk_add_train(SS_ALCHEMY, "mix potions", 0, 0, 70);
}

public varargs int
sk_hook_allow_train(object who, string str, string verb)
{
    setuid();
    seteuid(getuid());
    // Only allow those who are members to train here.
    if (!WOHS_MANAGER->query_is_member(who))
    {
        who->catch_msg("Only those who are Wizards of High Sorcery " +
          "can train here.\n");
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
    int     i, n, price;
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
