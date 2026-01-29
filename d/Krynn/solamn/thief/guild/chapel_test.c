/* meditation room, thief guild, by Aridor, 02/24/94 */

#include "guild.h"

inherit ROOM_BASE
inherit "/lib/guild_support"; 

#include <macros.h>
#include <cmdparse.h>
#include <composite.h>

void
create_thief_room()
{ 
    set_short("The chapel");
    set_long("You are in the Chapel devoted to Hiddukel. There is a large " +
	     "altar on the south end of the room where you can kneel and " +
	     "meditate to ask Hiddukel about your stats, and also change " +
	     "your learning preferences. It is also here where you can " +
	     "sacrifice part of your loot to Hiddukel, to make him turn " +
	     "to you favorably and give you divine support in your " +
	     "difficult task on this world. The Guild rooms are to the " +
	     "east, to the north and northwest there are two hallways " +
	     "leading off.\n");

    add_item(({"altar","large altar"}),
	     "It is a large stone altar with gold and silver inlays. " +
	     "Candles illuminate the holy room and you notice something " +
	     "special in the middle of the altar, between the candles. " +
	     "It is a simple slot.\n");
    add_item(({"candle","candles"}),
	     "They are very ordinary candles.\n");
    add_item(({"slot","simple slot"}),
	     "The slot in the middle of the altar seems to have just " +
	     "the right size to insert coins into it. You are sure " +
	     "that you can sacrifice money here.\n");

    add_exit(GUILDR + "start","east");
    add_exit(CAVERN + "pal1", "northwest");
    add_exit(CAVERN + "har1", "north");

    INSIDE;
    LIGHT;

    create_guild_support();
}

/*
 * Function:    safely_load_master_file
 * Description: This safely loads the master file if it hasn't already
 *              been loaded. Otherwise, it just returns the existing
 *              master file. If the file is not loadable, then it
 *              simply returns 0
 * Argument:    filename of the file to load
 */
public object
safely_load_master_file(string filename)
{
    object master_obj;
    if (!objectp(master_obj = find_object(filename)))
    {
        LOAD_ERR(filename);
        master_obj = find_object(filename);
    }
    
    return master_obj;
} /* safely_load_master_file */

/*
 * Function name:   copy
 * Description:     Copies a file, saving it as the 'clone'
 * Arguments:       (string) original   - The Original File
 *                  (string) clone      - The Location for the Clone
 * Returns:         (int)  1 - Success
 *                  (int)  0 - Failure: Failed to create file
 *                  (int) -1 - Failure: Directory or File exists
 *                  (int) -2 - Failure: No file to copy from
 */
nomask int
copy(string original, string clone)
{
    string file;

    switch(file_size(clone))
    {
        /* Target file does not exist or is empty. Proceed. */
        case -1:
        case  0:
            break;

        /* Target is either a directory or an existing file. */
        default:
            return -1;
    }

    /* Read the source file and test for success. */
    if (!strlen(file = read_file(original)))
        return -2;

    /* Write the file info and return the return value of the efun. */
    return write_file(clone, file);
} /* copy */

private object
get_rack_object(object player)
{
    int     success;
    string  name;
    mixed   room;
    
    if (!interactive(player))
        return 0;
    
    if (!strlen(name = player->query_real_name()))
        return 0;
       
    room = RACK_DIR + name + "_rack.c";
    if ((success = copy(RACK_COPY + ".c", room)) < 1)
    {
        if (success != -1)
            return 0;
    }
    
    return safely_load_master_file(room);
}

public int
rack_store(string str)
{
    object *items, *moved, room;
    
    if (!sizeof(items = FIND_STR_IN_OBJECT(str, this_player())))
    {
        notify_fail("Which item would you like to store in the rack?\n");
        return 0;
    }
    
    if (!objectp(room = get_rack_object(this_player())))
    {
        notify_fail("Your sensitive mind notice a wrongness in the fabric "
        + "of space.\n");
        return 0;
    }
    
    /* Moves the objects */
    moved = filter(items, not @ &->move(room));
    items -= moved;
    
    if (sizeof(moved))
        write("You stored " + COMPOSITE_DEAD(moved) + " in the rack.\n");
    else if (sizeof(items))
        write("You were unable to store " + COMPOSITE_DEAD(items) + " in the "
        + "rack.\n");
    
    return 1;
}

public int
rack_claim(string str)
{
    object *items, *moved, room;
    
    if (!objectp(room = get_rack_object(this_player())))
    {
        notify_fail("Your sensitive mind notice a wrongness in the fabric "
        + "of space.\n");
        return 0;
    }
    
    if (!sizeof(items = FIND_STR_IN_OBJECT(str, room)))
    {
        notify_fail("Which item would you like to retrieve from the rack?\n");
        return 0;
    }
    
    /* Moves the objects */
    moved = filter(items, not @ &->move(this_player()));
    items -= moved;
    
    if (sizeof(moved))
        write("You retrieved " + COMPOSITE_DEAD(moved) + " from the rack.\n");
    else if (sizeof(items))
        write("You were unable to retrieve " + COMPOSITE_DEAD(items) + " from "
        + "the rack.\n");
    
    return 1;
}

public int
rack_list(string str)
{
    object *items, room;
    string  content;
    
    if (!objectp(room = get_rack_object(this_player())))
    {
        notify_fail("Your sensitive mind notice a wrongness in the fabric "
        + "of space.\n");
        return 0;
    }
    
    if (!sizeof(items = FIND_STR_IN_OBJECT(str, room)))
    {
        write("You can see " + COMPOSITE_DEAD(all_inventory(room)) + " in the "
        + "rack.\n");
        return 1;
    }
    
    content = "The rack contains:\n";
    
    foreach(object item: items)
    {
        content += sprintf("%|3s %-60s %14s\n%80s",
                (item->check_recoverable() ? "[+]" : "[ ]"),
                item->short(),
                (item->query_nullstone_type() ? item->query_nullstone_type()
                + "stone" : "unimbued"),
                (IS_WEAPON_OBJECT(item) ?   item->wep_condition_desc() :
                                            item->arm_condition_desc()));
    }
    
    write(content);
    return 1;
}

void
init()
{
    ::init();
    init_guild_support();
    ADD("gs_meditate", "kneel");
    ADD("gs_meditate","meditate");
    ADA("pray");
    ADA("sacrifice");
    ADA("insert");
    
    add_action("rack_store", "tstore");
    add_action("rack_claim", "tclaim");
    add_action("rack_list", "tlist");
}

int
insert(string str)
{
    NF("Maybe you should try to sacrifice?\n");
    return 0;
}

int
manip_drop_access(object ob)
{
    if (!objectp(ob))
	return 0;
    if (function_exists("create_coins",ob) != "/std/coins")
        return 0;
    return (environment(ob) == this_player());
}

/* sacrifice
 * let players sacrifice some of their coins to get a bonus
 * when using the pick lock and steal command
 */
int
sacrifice(string str)
{
    function f;
    object tmp1, tmp2;
    object *sacri = ({ });
    int i, value = 0;

    NF("Only members of the Cabal may sacrifice here!\n");
    if (!MEMBER(TP))
      return 0;

    NF("Sacrifice what? You can only sacrifice coins.\n");
    if (!str)
      return 0;

    if (!parse_command(str, E(TP),"%i",sacri))
      return 0;

    sacri = CMDPARSE_STD->normal_access(sacri,"manip_drop_access",TO,0);
    
    if (sizeof(sacri) == 0)
      return 0;

    tmp1 = find_object("/cmd/live/things");
    tmp2 = find_object("/d/Krynn/common/void");
    f = &tmp1->manip_relocate_to(,tmp2);

    sacri = filter(sacri,f);
		   
    if (sizeof(sacri) <= 0)
      return 0;

    for(i=0;i<sizeof(sacri);i++)
      value += sacri[i]->query_value();

    i = TP->query_skill(SS_SACRIFICE);
    value += i;
    TP->set_skill(SS_SACRIFICE, value);
    write("You sacrifice " + COMPOSITE_DEAD(sacri) + " on the altar " +
	  "of Hiddukel.\nYou drop the coins into a slot on the altar " +
	  "and feel suddenly elated. The touch of Hiddukel washes over " +
	  "you and you are certain that the God will favour you now more " +
	  "when you embark on another spree in the name of Hiddukel.\n");
    say(QCTNAME(TP) + " sacrifices something at the altar.\n");
    sacri->remove_object();
    return 1;
}

int
pray(string str)
{
    string what;
    int i;
    NF("You don't think Hiddukel would let you pray at his altar since " +
       "you are no Thief.\n");
    if (!MEMBER(TP))
      return 0;
    i = SACRIFICE_2_BONUS(TP);
    if (i > 400)
      what = "extremely favorable towards";
    else if (i > 250)
      what = "highly favorable towards";
    else if (i > 100)
      what = "very favorable towards";
    else if (i > 20)
      what = "favorable towards";
    else if (i > -20)
      what = "indifferent towards";
    else if (i > -120)
      what = "angry with";
    else
      what = "extremely angry with";
    write("You kneel at the altar and pray to Hiddukel. A pleasant " +
	  "feeling of darkness descends down onto you and you feel " +
	  "it settling into your soul.\nYou feel now that your soul " +
	  "is taken apart, the infinite powers of Hiddukel working " +
	  "within you. Hiddukel seems to absorb a part of your soul, " +
	  "feeding on it, and then slowly letting you go and letting " +
	  "you return to the real world - the hard, enduring " +
	  "life here in the world of Krynn. You are fairly certain that " +
	  "Hiddukel is " + what + " you today.\n");
    say(QCTNAME(TP) + " prays at the altar.\n");
    return 1;
}

int
check_member(object ob)
{
    NF("You don't think Hiddukel would let you meditate at his altar since " +
       "you are no Thief.\n");
    return (MEMBER(ob));
}

int
gs_meditate(string str)
{
    if (!check_member(TP))
	return 0;
    return ::gs_meditate(str);
}

void
gs_hook_start_meditating()
{
    write("" +
	"You kneel before the altar of Hiddukel and close your eyes.\n" +
	"A feeling of great ease and self control falls upon you.\n" +
	"You block of your senses and concentrate solely upon your\n" +
	"own mind. You feel Hiddukel with you and he gives you the\n" +
	"power to <estimate> your different stats and <set> the\n" +
	"learning preferences at your own desire. Just <rise> when\n" +
	"you are done meditating.\n");
}

int
gs_hook_rise()
{
    write("As if ascending from a great depth, you rise to the surface\n" +
	  "of your consciousness. You exhale and feel very relaxed as\n" +
	  "you get up and leave the altar.\n");
    say(QCTNAME(TP) + " rises from the altar.\n");
}