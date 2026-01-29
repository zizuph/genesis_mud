inherit "/d/Gondor/common/room";
inherit "/d/Gondor/common/lib/herbsearch.c";

#include <stdproperties.h>
#include <macros.h>
#include <ss_types.h>
#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/lib/herb_list.h"
#include "/d/Gondor/minas/lib/porter_defs.h"


#define HARD_TO_SNEAK 20  /*How hard is it to sneak past the bench? */

void reset_room();

int     alarm_id,
        ben, wake;
object  guard;

string exa_bench();

void
create_room()
{
    set_short("a pathway winding up the west side of Amon Din");
    set_long(BSN(
      "This hillside is dense with trees and bushes, the track underfoot just " +
      "barely discernable amidst the dense growth. Below, to the southeast, " +
      "the pathway runs down to a small clearing at the foot of the hill. " +
      "Curving around the side of the hill, the track also heads up towards " +
      "the summit. A crude bench sits beside the pathway, amongst the shrubs."));
    add_item(({"bushes","trees","tree","bush","growth"}), BSN(
     "Wide and grey the trees rise along this westward slope of Amon " +
     "Din. Peering between the trunks you can see dense undergrowth " +
     "which provides the hillside with a soft cover. All seems peaceful."));
    add_item(({"shrubs","shrub"}), BSN(
     "Shrubs and other types of small foliage crowd the spaces " +
     "between the trunks of the trees. Despite the lush growth, " +
     "these woods have a look which is greyer than it is green."));
    add_item(({"undergrowth","cover"}), BSN(
     "The thick mat of vegetation and fallen needles blankets this " +
     "entire area. It looks quite soft."));
    add_item(({"hill","hillside","summit"}), BSN(
     "The density of vegetation along the hillside prevents a good view " +
     "of much of anything other than the pathway."));
    add_item(({"path","pathway","track","ground"}), BSN(
     "The ground is broken here, but not by much. This pathway clearly " +
     "does not receive a great deal of traffic. You notice that this section " +
     "of the path is cluttered with many fallen twigs and branches."));
    add_item(({"twig","twigs","branch","branches"}), BSN(
     "They look very dry and brittle. It looks as if moisture does not " +
     "easily penetrate the forest canopy."));
    add_item(("bench"), VBFC_ME("exa_bench"));
    add_exit(DRUEDAIN_DIR + "amon-din/ad4","northeast","@@check_exit");
    add_exit(DRUEDAIN_DIR + "amon-din/ad2","southeast");

    set_up_herbs( ({ ONE_OF_LIST(HERBS), ONE_OF_LIST(HERBS), ONE_OF_LIST(HERBS), }),
                  ({ "hill", "hillside", "ground", "track", "path", }), 3);

    reset_room();
}

string
exa_bench()
{
    switch (ben)
    {
        case 1:
            return BSN("The bench is currently occupied by a sleeping "
              + "human. Perhaps he has nodded off at his post.");
            break;
        case 2:
        default:
            return BSN("This bench is crude and looks hastily "
              + "constructed. You get the feeling that it has been "
              + "recently occupied, as the needles which cover this "
              + "area are absent from its surface.");
           break;
    }
}

int
be_sneaky()
{
    object  tp = TP;
    int     sneak = tp->query_skill(SS_SNEAK),
            diff;

    diff = random(HARD_TO_SNEAK)+9;
    if (sneak < diff)
    {
        write("As you make your way past the bench, you accidently trod on a large \n");
        write("twig. Being rather dry and brittle, it breaks with a loud snap.\n");
        wake = 1;
        say(QCTNAME(tp) + " steps on a twig while passing the bench.\n");
        return 1;
    }

    write("You step cautiously past the bench and follow the path upward.\n");
    return 0;
}

void
clone_guard()
{
    if(!objectp(guard))
    {
        guard = clone_object(AMON_DIR + "npc/din_guard");
        guard->arm_me();
        guard->set_long(BSN("This soldier attends his post with what"
          + " appears to be a fairly small degree of enthusiasm. He is"
          + " quite young, and is very likely just beginning his"
          + " training in the Steward's armies."));
        guard->move_living("from somewhere", TO);
    }
}

public int
check_exit()
{
    object block = present("guard", this_object());
    string npc = block->query_nonmet_name();

    if (!objectp(block))
        return 0;

    if (!CAN_SEE_IN_ROOM(block) || !CAN_SEE(block, TP))
        return 0;

    if (TP->query_prop(QUESTING_FOR_BUNDLE))
        {
        TP->catch_msg("The " + npc + " bows and waves you on.\n");
        say(QCTNAME(block) + " bows and waves " + QCTNAME(TP) + " on.\n");
        return 0;
        }

    TP->catch_msg(BSN("The " +npc+ " stops you from going there,"
      + " saying: You have no business on the summit, "
      + TP->query_race_name() + "."));
    say(QCTNAME(block) + " stops " + QCTNAME(TP) + " from going"
      + " northeast.\n", ({TP, block}));
    return 1;
}

void
reset_room()
{
    set_alarm(1.0, 0.0, clone_guard);
}
