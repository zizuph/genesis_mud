/* meditation room, thief guild, by Aridor, 02/24/94 */
/* Aug 27, 2018: Added no-scry protection in guild (Gorboth) */

#include "guild.h"

inherit ROOM_BASE
inherit "/lib/guild_support"; 

#include <macros.h>
#include <cmdparse.h>
#include <composite.h>
#include <stdproperties.h>

void load_racks();

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

    load_racks();

    add_prop(ROOM_M_NO_SCRY, "Haze, and nothing more, is all that"
      + " appears.");

    INSIDE;
    LIGHT;

    create_guild_support();
}

void
load_racks()
{
    object ar, wr, mr;

    seteuid(getuid(TO));
    mr = clone_object("/d/Genesis/specials/guilds/objs/misc_rack");
    mr->move(this_object());
    ar = clone_object("/d/Genesis/specials/guilds/objs/armour_rack");
    ar->move(this_object());
    wr = clone_object("/d/Genesis/specials/guilds/objs/weapon_rack");
    wr->move(this_object());
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

