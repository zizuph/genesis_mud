#pragma strict_types

inherit "/d/Gondor/pelargir/sewers/sewer.c";

#include <language.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/pelargir/lib/statue_quest.h"

#define MIN_AWARE_SEE	20

int     open = 0,
        found = 0,
        snake = 0;

void
create_sewer()
{
    set_short("below the sewer grating");
    set_extra_long("In the roof of the tunnel there is an opening, "
      + "probably leading out to the surface. The tunnel continues to "
      + "the east, while there are just the openings of three pipes "
      + "set into the opposite wall. The stench here is nearly "
      + "overpowering, the smell of "
      + "waste and vermin along with a hint of rotting flesh is enough "
      + "to make you reel and retch. The shadows here add something more "
      + "though, a sense that you are being watched. The ground is covered "
      + "by a thick layer of muck.");
    add_item(({"ground", "floor","mud","muck"}), VBFC_ME("exa_muck"));
    add_item(({"opening", "hole", "grate", "grating", }),
        VBFC_ME("exa_hole"));
    add_item("shadows", "These shadows seem to move and flicker in the "
      + "corner of your eye.\n");
    add_item(({"roof", "ceiling", }), BSN(
       "The roof of the tunnel is made from the same black bricks as "
     + "the walls. It arches steeply about six feet above the ground. "
     + "An opening in the roof seems to be leading out of the sewer "
     + "onto the surface."));
    add_item(({"openings", "pipe", "pipes", }), BSN(
       "There is a perpetual trickle of water coming out of the three "
     + "pipes set into the west wall. The openings of the pipes are "
     + "about five inches in diameter, so they are far too small to "
     + "enter."));

    passage("east");

    add_prop(OBJ_S_SEARCH_FUN, "do_search");
    add_prop(OBJ_I_SEARCH_TIME, 6);

    add_exit(PELAR_DIR + "sewers/seagate", "east", 0, 1);
    add_exit(PELAR_DIR + "streets/beacon05", "up", "@@check_grate@@", 3);
}

string
exa_muck()
{
    string  ld = 
        "Silt and mud cover the ground of the tunnel, left over from "
      + "the water torrents that must fill these sewers in times of "
      + "heavy rain. The layer of mud is so high that it covers your "
      + "ankles.";

    if (TP->query_skill(SS_AWARENESS) > MIN_AWARE_SEE)
        ld += " In some places the mud seems to bury stones and other "
           +  "items.";

    return BSN(ld);
}

int
check_grate()
{
    if (open)
        return 0;

    write(BSN("You try to leave the sewer through the opening leading up, "
      + "but you are stopped by the grating blocking that exit.")
      + "But with a light push against the grating, you manage to break "
      + "it.\n");
    open = 1;
    return 0;
}

string
exa_hole()
{
    if (open)
        return "A grate in the opening leading up once blocked that "
          + "exit, but it appears to be broken.\n";
    return "A grate in the opening leading up blocks that exit.\n";
}

void
reset_grating()
{
    open = 0;
    found = 0;
    snake = 0;
}

int
query_open()
{
    return open;
}

int
set_open()
{
    if (open)
        return 0;
    open = 1;
    return 1;
}

string
do_search(object tp, string str)
{
    object  obj;

    if (!strlen(str))
        return 0;

    switch (str)
    {
        case "mud":
        case "muck":
            if (found)
                return 0;
            found = 1;

            obj = clone_object(PEL_SQ_STATUE_FILE_1);
            if (obj->move(TP))
                obj->move(TO);
      
            return "Buried deep in the mud, you find "
              + LANG_ADDART(obj->short())+".\n";
            break;

        case "pipe":
        case "pipes":
        case "openings":
            if (snake)
                return 0;
            snake = 1;
 
            tp->catch_msg("Searching the pipes, you put a hand into one of them.\n");
            obj = clone_object(NPC_DIR + "snake");
            obj->move_living("down", TO);
            obj->command("kill " + tp->query_real_name());
            return "You seem to have disturbed a snake!\n";

            break;
        default:
            return 0;
    }
}

