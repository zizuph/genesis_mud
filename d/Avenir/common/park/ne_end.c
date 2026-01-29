// file name: ne_end.c
// creator(s): Ilyian (from Farlong's files)
// last update:
// purpose:
// note: Bicornbrn
// bug(s):
// to-do:

inherit "/std/room";
#include "/sys/stdproperties.h"
#include "park.h"

static object bicornblk;
static object bicornbrn;

public void
create_room()
{
    set_short("Northeast path");
    set_long("The short northeast path ends here rather"
      +" abruptly. Old stone walls and a heavy curtain of vines and"
      +" brush form a rough semicircle whose only opening leads"
      +" back to the southwest. There is little light here, due"
      +" to the heavy foliage all around.\n");

    AE(PK+"ne_path2","southwest",0);

    add_prop(ROOM_I_LIGHT,1); IN

    ECANOPY
    EVINE
    EPATHG
    COURTLIGHT
    COURTCEILING
    AI(({"wall","walls","stone"}),"The crumbling walls on either side of the "
      +"path curve inwards to meet at the end of this path. Vines and other "
      +"trailing vegetation cling to the walls, almost obscuring the stone "
      +"that it is built from. The wall is marked by numerous small recesses "
      +"that are dark and shadowy.\n");
    AI(({"recess","recesses"}),"They are about as large as your hand, and seem "
      +"designed to store things in, perhaps gardening tools.\n");

    seteuid(getuid(this_object()));

    set_search_places(({"vine","vines","underbrush","weeds","weed"}));
    add_prop(OBJ_I_SEARCH_TIME,2);
    add_prop(OBJ_S_SEARCH_FUN,"search_me");
    add_herb_file(GONDOR+"lothore");
    add_herb_file(GONDOR+"myrtle");
    add_herb_file(SHIRE+"parsley");
}

public void
reset_room()
{
    set_searched(0);

    if (!bicornblk)
    {
	bicornblk = clone_object(PK+"mon/bicornblk");
	bicornblk->move_living("M", this_object());
    }
    if (!bicornbrn)
    {
	bicornbrn = clone_object(PK+"mon/bicornbrn");
	bicornbrn->move_living("M", this_object());
    }
}

#include "/d/Avenir/union/lib/bits.h"
#define LIST ("/d/Avenir/union/list")

string search_me(object player, string str)
{
    if (player->query_prop("found_it_yet") ||
      player->test_bit("Avenir", GUILD_GROUP, QUEST_BIT) ||
      !LIST->query_accepted(player->query_real_name()))
    {
	return herb_search(player, str);
    }

    if (!parse_command(str, ({}),
	"[the] 'wall' / 'recess' / 'recesses'"))
    {
	return herb_search(player, str);
    }

    player->add_prop("found_it_yet", 1);
    object ob = clone_object(UNION+"obj/quest/dust");
    ob->move(player, 1);

    return "In one of the recesses, you find "+LANG_ASHORT(ob)+".\n";
}
