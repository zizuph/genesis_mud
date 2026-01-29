
 /* Temple archway leading into the Worshippers Temple */
 /* By Jaacar, 1996                                    */
 /* Adjusted awareness for archway, Maniac, 20/11/99 */ 

#pragma save_binary

inherit "/std/room";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "defs.h"
#include WORSHIP_HEADER
#include "/d/Krynn/common/herbsearch.h"

#define KRYNN_HERBS "/d/Krynn/common/herbs/"

void reset_herb_room()
{
    set_searched(random(6));    /* Lots of plant life here */
}

int
is_worship(object living)
{
    return living->query_guild_name_lay() == GUILD_NAME;
}

void
reset_room()
{
    reset_herb_room();
}

void
create_room()
{
    set_short("Standing before a stone wall");
    set_long("You enter a small vale nestled in the foothills "+
        "of Calia. It is quiet and tranquil here. The entire "+
        "south end of the vale is blocked by a stone wall, "+
        "covered entirely with bushes and small flowers. It is very "+
        "tall, standing another head and a half over a tall "+
        "human's head. To the north you see the path you just "+
        "wandered down leading back into the rocks. A small dirt path " +
        "continues southwest. " +
        "@@arch_long@@\n");


    add_prop(OBJ_S_WIZINFO,
        "There are three exits from this room.  If the player's "+
        "awareness skill is less than 25, they will not see the archway " +
        "to the old Elemental Worshippers temple. If the player's awareness " +
        "skill is 25 or greater, they will be able to enter the old temple " +
        "via the <archway>.\n\n");

    add_item("bushes","The bushes are bright green in colour, and "+
        "perfectly trimmed. Strangely you do not notice any sign "+
        "of people around to maintain these bushes.\n");

    add_item(({"small flowers","flowers"}),"These flowers are "+
        "various colours. Some grow from the bushes themselves, "+
        "some grow on their own from the ground.\n");

    add_item(({"walls","stone"}),"The walls are comprised of "+
        "carefully cut stones that fit together. It is difficult "+
        "to tell how far they stretch to the east and west as it is "+
        "hidden behind bushes and plants.\n");

    add_item("entrance","The entrance does not appear to be "+
        "guarded by anyone, and you do not hear any noise from "+
        "beyond it.\n");

    add_item("plants","These leafy plants are a beautiful "+
        "green colour and appear to be very healthy.\n");

    add_prop(ROOM_I_INSIDE,0);
    add_prop(ROOM_I_IS,1);
    add_prop(OBJ_I_SEARCH_TIME,3);
    add_prop(OBJ_S_SEARCH_FUN,"herb_search");
    set_search_places(({"bush","bushes","flowers","wall","plants"}));

    seteuid(getuid(TO));

    add_herb_file(KRYNN_HERBS+"cladina");
    add_herb_file(KRYNN_HERBS+"fireweed");
    add_herb_file(KRYNN_HERBS+"grey_willow");
    add_herb_file(KRYNN_HERBS+"blk_currant");
    add_herb_file(KRYNN_HERBS+"chokecherry");
    add_herb_file(KRYNN_HERBS+"hawthorn");
    add_herb_file(KRYNN_HERBS+"hazelnut");
    add_herb_file(KRYNN_HERBS+"raspberry");
    add_herb_file(KRYNN_HERBS+"saskatoon");
    add_herb_file(KRYNN_HERBS+"crocus");
    add_herb_file(KRYNN_HERBS+"tiger_lily");
    add_herb_file(KRYNN_HERBS+"veronica");
    add_herb_file(KRYNN_HERBS+"chicory");
    add_herb_file(KRYNN_HERBS+"bunchberry");
    add_herb_file(KRYNN_HERBS+"lady_slipper");

    add_exit(WOR_TEMPLE+"path","north",0,1);
    add_exit("/d/Calia/guilds/elementalists/temple/path1", "southwest");
    add_exit(WOR_TEMPLE+"entrance","archway","@@see_arch",1,"@@see_arch");
}

void
welcome(object who)
{
    if (is_worship(who))
        tell_object(who,"A voice echoes in your mind:  Welcome home, "+
        who->query_guild_title_lay()+".\n");
    else
    tell_object(who,"A voice echoes in your mind: Welcome to our home.\n");
}

int
see_arch()
{
    /*
      Disabling the archway entrance. Petros, April 2015.

    if (this_player()->query_skill(SS_AWARENESS) >= 25)
    {
        if (query_verb() == "archway")
            set_alarm(1.0,0.0,&welcome(this_player()));
        return 0;
    }
    */
    if (query_verb()=="archway")
        write("There is no obvious exit archway.\n");
    return 1;
}

string
arch_long()
{
    if (!see_arch())
    {
        return "Looking carefully you notice a beautiful archway "+
            "hidden amongst the bushes, flowers and plants. It "+
            "seems to lead into a building of some sort. "+
            "The archway forms a perfectly shaped half-circle "+
            "standing almost eight feet high, and ten feet wide "+
            "at the bottom. It is hidden by bushes "+
            "and small flowers. ";
    }
    return "";
}
