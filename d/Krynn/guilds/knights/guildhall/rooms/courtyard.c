/* Vingaard keep coded by Percy. */
/* Modified by Morrigan 10/6/96. */
/* Modified again for the new Vingaard Keep by Morrigan 11/11/96 */
/* And a touch more by Teth 12/3/96 */

#include "/d/Krynn/common/defs.h"
#include "../../guild.h"
#include <ss_types.h>
#include <macros.h>
#include <composite.h>
#include <filter_funs.h>
#include <stdproperties.h>

inherit OUT_BASE;
inherit (KLIB + "knight_utility");

#define OUTKEEP      VROOM + "gate"

object ob, statue;
int gate_closed  = 0;

void
create_vin_room()
{
    set_short("Courtyard of Vingaard Keep");
    set_long("@@long_desc");

    AE(VROOM + "ss3", "west", 0);
    AE(VROOM + "archway", "north");
    AE(VROOM + "ss4", "east", 0);
    AE(OUTKEEP, "south", "@@go_south");

    AI("hatch", "@@hatch_desc");
    AI(({"wall", "walls"}), "@@walls");
    AI("archway", "The archway leads north towards the inner "+
      "portcullis. On either side of the archway to the north are two rooms, "+
      "strategically placed, which you might assume are guard quarters.\n");
    AI(({"keep", "castle", "stronghold"}), "@@keep");
    AI(({"gate", "gates","portcullis"}), "@@gate");
    AI("courtyard", "@@court");

    ACI(({"portcullis","gate","gates"}),({"open","raise"}),
      "@@open_portcullis");
    ACI(({"portcullis","gate","gates"}),({"close","lower"}),
      "@@lower_portcullis");

    statue = clone_object(VOBJ + "huma_statue.c");
    statue->move(TO);
}

string
hatch_desc()
{
    if (!gate_closed)
    return "The portcullis is not closed, you cannot see the "+
    "hatch when it's open.\n";
    return "There is a small hatch about eye-level on the gate, "+
    "which you can probably peek through, to see the outside "+
    "of the gate.\n";
}

string
long_desc()
{
    return "You are standing in the huge courtyard of Vingaard Keep. " +
    "There are streets leading off to the east and west. The only way out " +
    "of Vingaard Keep is to the south, through massive gates. To the " +
    "north rests the main building within Vingaard Keep, the guildhall "+
    "of the Solamnian Knights. In the center of the courtyard is a "+
    "remarkable statue, perhaps of a famous Solamnic hero. Surrounding " +
    "you are the walls of Vingaard Keep, which stand tall and " +
    "proud. "+season()+tod()+"\n";

}
void
init()
{
    ::init();
    if (ob = present("tour6", TP))
    ob->set_arr("guild");

    add_action("return_horse", "return");
    add_action("hatch", "peek");
    add_action("knees_statue", "knees");
    add_action("knees_statue", "respect");
    add_action("mock_statue", "mock");
}


void enter_inv(object ob, object from)
{
    if (ob->query_prop(LIVE_O_STEED) && MEMBER(ob))
    ob->catch_tell("You notice a Squire watching you attentively as you "+
      "enter the courtyard of Vingaard Keep astride your "+
          ob->query_steed()->steed_short()+", waiting to see "+
        "if you motion for "+
      "him to <return> your horse or not.\n");

    ::enter_inv(ob, from);
}

string
keep()
{
    write(BS("The keep is very ancient and has withstood the test of time"+
    " just as much as it has withstood numerous battles. The "+
    "keep is the stronghold for the Solamnian knighthood, a "+
    "powerful army of knights devoted to the cause of the good.",70));
    return "";
}

string
gate()
{
    if (gate_closed)
    write("The gate is made of iron. It looks extremely solid. At the "+
      "moment, the gates are closed! A most disturbing sign! You notice a "+
      "small hatch about eye-level on the gate.\n");
    else
    write("The gate is made of iron. It looks extremely solid. At the "+
      "moment, the gate lies open, a sign of the knights' "+
      "confidence in their power to defeat the evil in the world.\n");
    return "";
}

string
court()
{
    write("The courtyard is huge and could easily hold many Solamnian" +
      " knights. Its usual purpose is to provide room for " +
      "marching and parading knights, as well as a general " +
      "place to gather under the open sky and in the fresh air.\n");
    return "";
}

int
hatch(string str)
{
    object *inv, *live, *dead, room;

    if (!str)
    return 0;

    if (!gate_closed)
    return 0;

    if (str != "through hatch" && str != "hatch")
    return 0;

    inv = ({});
    if ((room = find_object(OUTKEEP)) != 0)
    inv += all_inventory(room);

    if (inv && sizeof(inv) > 0)
    {
    live = FILTER_LIVE(inv);
    live -= ({ TP });
    dead = FILTER_DEAD(inv);
    if (sizeof(live) > 0 && sizeof(dead) > 0)
    {
        write("As you slide open the hatch and peek through "+
          "the gate, you see " + COMPOSITE_LIVE(live) + ", as "+
          "well as " + COMPOSITE_DEAD(dead) + ".\n");
        return 1;
    }
    else if (sizeof(live) > 0)
    {
        write("As you slide open the hatch and peek through "+
          "the gate, you see " + COMPOSITE_LIVE(live) + ".\n");
        return 1;
    }
    else if (sizeof(dead) > 0)
    {
        write("As you slide open the hatch and peek through "+
          "the gate, you see " + COMPOSITE_DEAD(dead) + ".\n");
        return 1;
    }
    }

    write("As you slide open the hatch and peek through the "+
      "gate, you see nothing.\n");
    return 1;
}

/* Returns 0 to allow travel under gate. */
int
go_south()
{
    if (gate_closed)
    write("The portcullis is down, you cannot leave Vingaard Keep.\n");
    else
    write("You pass through the gates and out into the world.\n");
    return gate_closed;
}

int go_north()
{
    if (TP->query_steed())
    {
    write("You may have a squire 'return' your horse for you, "+
      "if you wish, before enterring the Inner Courtyard.\n");
    return 1;
    }
    return 0;
}

int
lower_portcullis()
{
    if (!gate_closed && (TP->id("knight") || TP->query_guild_name_occ() == "Solamnian Knights"))
    {
    gate_closed = 1;
    write("You hit the hook holding the portcullis in place.\n");
    tell_room(TO,"With a loud rumble the portcullis slams down and " +
      "effectively seals off the entrance.\n");
    tell_room(OUTKEEP,"With a loud rumble the portcullis slams down and "+
      "effectively seals off the entrance.\n");
    return 1;
    }
    NF("What?\n");
    return 0;
}

void
do_open_portcullis()
{
    gate_closed = 0;
    tell_room(TO,"With a slow rumble the portcullis winds upwards into " +
      "the huge gateway above, opening the entrance again.\n");
    tell_room(OUTKEEP,"With a slow rumble the portcullis winds upwards into " +
      "the huge gateway above, opening the entrance again.\n");
}

int
open_portcullis()
{
    if (gate_closed && (TP->id("knight") || TP->query_guild_name_occ() == "Solamnian Knights"))
    {
    write("You wind the cable back up.\n");
    do_open_portcullis();
    return 1;
    }
    NF("What?\n");
    return 0;
}

int
query_portcullis_closed()
{
    return gate_closed;
}

int
knees_statue(string s)
{

    if(s != "statue" && s != "huma" && s != "Huma")
    {
    notify_fail("Respect what?\n");
    return 0;
    }

    write("You kneel briefly before the statue of Huma, muttering "+
      "in Solamnian:  Est Sularus oth Mithas.\n");
    say(QCTNAME(TP)+" kneels briefly before the statue of Huma and "+
      "mutters something under "+TP->query_possessive()+" breath.\n");
    return 1;
}

int
mock_statue(string s)
{
    if(s != "statue" && s != "huma" && s != "Huma")
    {
    notify_fail("Mock what?\n");
    return 0;
    }

    write("You mock the statue of Huma, sneering at the thought of "+
      "the Knighthood and its beliefs.\n");
    say(QCTNAME(TP)+" sneers and laughs sarcastically as "+
      TP->query_pronoun()+" mocks the statue of Huma.\n");
    return 1;
}

int return_horse(string str)
{
    object steed;
    int i;

    steed = query_solamnian_steed(TP);

    if (!steed || environment(steed) != environment(TP))
    {
        return 0;
    }

    find_object(VROOM + "stable1")->remove_taken(TP->query_name());

    // Remove all the riders
    steed->dismount_all();
    write("You motion to a nearby squire, who takes the reigns "+
      "of your "+steed->short()+" obediently, and leads "+
      OBJECTIVE(steed)+" to the stables.\n");
    say(QCTNAME(TP)+" motions to a nearby squire, who takes the "+
      "reigns of "+POSSESSIVE(TP)+" "+steed->short()+" obediently, "+
      "and leads it away.\n");
    steed->remove_object();

    return 1;
}


