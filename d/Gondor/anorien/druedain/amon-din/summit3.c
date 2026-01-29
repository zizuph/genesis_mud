/*
 *  This is summit3.c
 *
 *  July 1995 by Gorboth
 */

inherit "/d/Gondor/anorien/druedain/amon-din/din_master";

#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/clock.h"

void reset_room();

int	alarm_id;
object  guard;

void
create_room()
{
    set_west(4);
    set_east(1);
    add_view("Standing here in the very center of the summit, a"
           + " clear view can be had to the north and south, for"
           + " the structures on either side prevent an east-west"
           + " perspective.");

    set_short("at the base of the beacon tower of Amon Din");
    set_long("@@describe");
    add_item(({"path","pathway","trail","track"}), BSN(
        "The path is little more than frequently trodden ground which"
      + " has grown hard and distinct by many years of use. It leads"
      + " to the north and south here."));
    add_item(({"building","wall","walls"}), BSN(
        "The trees which line the building to the north do not grow"
      + " along its walls here. The purpose for this building is"
      + " mysterious, as there are no visible windows or doors from"
      + " this vantage point. A large treetop is visible rising above the"
      + " roof of this building to the southeast."));
    add_item(("trees"), BSN(
        "Trees are visible growing along the wall to the north from"
      + " here, while a singular and very large tree rises above the"
      + " roof of the building to the southeast."));
    add_item(({"tree","treetop"}), BSN("This tree is clearly the largest on"
      + " this summit, and is probably much older than even the"
      + " building. You seem to notice a bird of some sort in the"
      + " high branches of this tree."));
    add_item(({"bird","high branches","branches"}), BSN(
        "It is hard to tell what is up there. Perhaps some black-"
      + "winged bird is nesting in those branches."));
    add_item(({"roof","rooftop"}), BSN(
        "The rooftop is clearly visible here, as is the slight slant"
      + " of the shingles upon its slope."));
    add_item(({"shingle","shingles","slope"}), BSN(
        "The shingles upon the roof look like the sort that are quite rough"
      + " and easy to walk upon. The roof also looks like it runs"
      + " right up against the tall tree."));
    add_item("corner", BSN("The corner of this building is visible"
      + " to the south, where the path curves around to that side"
      + " of the hilltop."));
    add_item(({"lock","frame","keyhole"}), BSN(
        "The frame surrounding the keyhole is made of a dark metal"
      + " which has been tarnished by the elements to the point of"
      + " having a greenish tint. The keyhole appears towards the"
      + " bottom of the frame which has an arched shape similar to"
      + " that of the door. A tree surrounded by seven stars is"
      + " engraved above the keyhole."));
    add_item(({"block","rock","blocks","stone","stones"}), BSN(
        "The size of these blocks bears testimony to the craft which"
      + " has proved Minas Tirith to be a sturdy defence against the"
      + " encroaching designs of the Dark Lord. Though roughly cut and"
      + " jagged, the blocks of stone have been placed with artistry"
      + " and great care. There is a beauty in this work."));
    add_item(({"brick","bricks"}), BSN(
        "The bricks which outline the arch of the doorway are hewn"
      + " from the same rock as comprises the rest of the tower. They"
      + " are but a smaller and more delicate version."));
    add_item(({"tower","beacon tower"}), "@@exa_tower");

    add_exit(AMON_DIR + "summit2", "north");
    add_exit(AMON_DIR + "summit4", "south", "@@check_guards", 1);
    clone_object(AMON_DIR + "doors/towerdoorout")->move(TO);

    reset_room();
}

void
clone_guard()
{
    if (!objectp(guard))
    {
        guard = clone_object(AMON_DIR + "npc/din_attendant");
        guard->arm_me();
        guard->move_living("from somewhere", TO);
    }
}

string
describe()
{
    string ld,
           time = tod();

    ld = "The path reaches the center of the hilltop here as it"
       + " passes alongside the long building. The view here remains"
       + " astonishing, and the heavens above are wide and beautiful."
       + " Beside the path, a tall and impressive tower rises solemnly"
       + " into the air,";

    switch(tod())
    {
        case "evening":
        case "night":
        case "early morning":
            ld += " its frame a long silhouette against the "+ time
                + " sky.";
            break;
        default:
            ld += " its frame a great spire before the "+time+" sun.";
            break;
    }

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        ld += " Tall flames are leaping from atop the tower.";
    }

    ld += " The path winds around the corner of this building to the"
        + " south, and alongside the wall to the north.";

    return BSN(ld);
}

string
exa_tower()
{
    string ld;

    ld = "Tall and still, the tower rises directly before you like a"
       + " great finger from the earth. Great blocks of stone comprise"
       + " its rounded base, and numerous smaller bricks outline an"
       + " arched doorway which lies at its foot near to the pathway."
       + " The tower narrows slightly near to the top, where a large"
       + " basin rests high above the surface of Amon Din.";

    if (rq_stage() >= RQ_STAGE_WAR)
    {
        ld += " The sides of the basin glow with an amber hue as"
            + " flames can be seen licking up to the heavens. A"
            + " soft crackling sound, as of burning wood, comes from"
            + " above.";
    }

    return BSN(ld);
}
public int
check_guards()
{
    object block = present("attendant", this_object());

    if (!objectp(block))
        return 0;

    if (!CAN_SEE_IN_ROOM(block) || !CAN_SEE(block, this_player()))
    {
        TP->catch_msg("Even though you are unseen, the horizontal position"
          + " of the beacon attendant's halberd prevents you from"
          + " passing by him.\n");

        if (this_player()->query_wiz_level())
        {
            write("Of course, as a wizard, this doesn't stop you.\n");
            return 0;
        }

        return 1;
    }

    TP->catch_msg(QCTNAME(block) + " stops you from going there,"
      + " saying: I think not!\n");
    say(QCTNAME(block) + " stops " + QCTNAME(TP) + " from going south.\n",
      ({ TP, block }));

    return 1;
}

void
reset_room()
{
    set_alarm(0.0, 0.0, clone_guard);
}

