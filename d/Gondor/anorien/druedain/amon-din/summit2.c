/*
 *  This is summit2.c
 *
 *  July 1995 by Gorboth
 */

inherit "/d/Gondor/anorien/druedain/amon-din/din_master";

#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/elessar/lib/clock.h"

/*
 *	prototypes
 */
void reset_room();

/*
 *	Global variables
 */
int     alarm_id;
object *adguard = allocate(3 + random(3));

void
create_room()
{
    set_west(3);
    set_south(1);
    add_view("Though it is impossible to see much to the south and west,"
           + " the view here is quite breathtaking nonetheless.");

    set_short("beside a long building atop the summit of Amon Din");
    set_long("@@describe");
    add_item(({"tower","beacon tower"}), "@@exa_tower");
    add_item(({"path","pathway","trail"}), BSN(
        "The pathway is little more than earth that has been worn"
      + " down by years of trodding feet. It leads to the north and"
      + " south."));
    add_item(("building"), BSN(
        "This building is quite long and runs the length of the"
      + " hilltop. Trees have been planted along the wall to the"
      + " west, making it difficult to see much detail."));
    add_item(({"tree","trees","green tree","green trees","treetops"}),
      BSN("These trees do not look more than thirty years of age."
      + " Rising tall and thin beside the building, they do not look"
      + " similar to the trees of the forest below, and have likely"
      + " been planted here to provide shade for the keepers of the"
      + " tower."));
    add_item(({"walls","wall"}), BSN(
        "The branches of the trees make it difficult to see the walls"
      + " of the building here. You can barely make out a rooftop"
      + " beyond the tops of the trees."));
    add_item(({"roof","rooftop"}), BSN(
        "The top of the building is completely obscured by the trees."
      + " No amount of positioning or squinting helps to see beyond"
      + " them from this vantage point."));
    add_item("forest", BSN(
        "The forest expands from the base of Amon Din like a carpet"
      + " of green and grey."));

    add_exit(AMON_DIR + "summit", "north");
    add_exit(AMON_DIR + "summit3", "south");

    reset_room();
}

string
describe()
{
    string time = tod(),
           ld;

    ld = "The path runs beside a long building here.";
    switch(time)
    {
        case "evening":
        case "night":
        case "early morning":
            ld += " The " + time + " has brought darkness to this hilltop"
                + ", and stars can be seen twinkling in the heavens.";
            break;
        default:
            ld += " The sun shines above, giving life and breath to the "
                + time + " atmosphere.";
            break;
    }
    ld += " Thin green trees line this side of the building here, making"
        + " its walls quite difficult to see. Directly to the south, the"
        + " path runs beside the beacon tower which distinguishes this"
        + " summit from most other hills. To the north, the path begins"
        + " its descent into the forest";
    if (rq_stage() >= RQ_STAGE_WAR)
    {
        ld += ". You notice that flames leap from the basin of the tower"
            + " to the south.";
    }
    else
        ld += ".";
    return BSN(ld);
}

string
exa_tower()
{
    string ttxt;

    ttxt = "The beacon tower of this summit rises tall and silent"
         + " directly to the south. Heavy bricks comprise its base,"
         + " which extends for some distance to support a lofty"
         + " basin.";

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        ttxt += " Bright flames are dancing in the basin as a signal"
              + " to distant allies.";
    }
    return BSN(ttxt);
}

void
clone_guard()
{
    int     i, n,
            rs;

    for (i = 0, n = sizeof(adguard); i < n; i++)
    {
        if (!objectp(adguard[i]))
        {
            rs = random(30);
            adguard[i] = clone_object(AMON_DIR + "npc/din_guard");
            adguard[i]->set_random_move(25);
            adguard[i]->set_restrain_path(AMON_DIR + "summit/");
            adguard[i]->default_config_npc(60 + rs);
            adguard[i]->set_base_stat(SS_INT, 25 + random(15));
            adguard[i]->set_base_stat(SS_WIS, 25 + random(15));
            adguard[i]->arm_me();
            adguard[i]->move_living("from the void", TO);
            return;
        }
    }

    remove_alarm(alarm_id);
    alarm_id = 0;
}

void
reset_room()
{
    if (!alarm_id || !sizeof(get_alarm(alarm_id)))
        alarm_id = set_alarm(1.0, 1.0, clone_guard);
}
