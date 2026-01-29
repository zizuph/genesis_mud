/* Pax Tharkas, inside Sla-Mori.
 *
 * 950401 by Rastlin 
 * Buggy wyrmslayer code fixed by Cotillion and Kessie, 07-2002
 */

#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/pax/local.h"

#define PATH "/d/Krynn/common/weapons/wyrmslayer"

inherit "/lib/unique";

inherit PAXINROOM;

int gSword;
int gCounter;

public void
reset_pax_room()
{
  int count;
  object ob;

  setuid();
  seteuid(getuid());
  
  if (!LOAD_ERR(PATH) && objectp(ob = find_object(PATH)))
  {
    count = sizeof(filter(object_clones(ob),
    &not() @ &->query_prop(OBJ_I_BROKEN)));
  }

  if (count > 0)
  {
    return;
  }
  if (random(100) < 50)
  {
    gSword = 1;
  }
  return;
}                  

void
create_pax_room()
{
    set_short("Middle of Hall of the Ancients");
    set_long(BS("You standing in the middle of Hall of the Ancients. Two rows " +
        "of seven columns runs the length of the " +
        "hall, though some lie shattered on the floor. Before you at " +
        "east wall is a massive throne, ornately carved of granite. " +
        "Two huge marble statues flanks the throne. The throne they " +
        "are guarding is not empty. Upon it sits the skeletal remains " +
        "of what has once been a male.", 70));

    add_item("dust", "The dust seems to be very, very old.\n");

    add_item("floor", "There is a lot of dust and loose chunks of rock " +
      "on the floor.\n");

    add_item("throne", BS("It is a massive throne, ornately carved of granite. " +
        "The throne is guarded by two huge marble statues. " +
        "On the throne sits the skeletal remains of a male.", 70));

    add_item(({"statue", "statues"}), BS("They are guarding the throne, their " +
        "sightless eyes staring forward into the darkness.", 70));

    add_item(({"remains", "skeleton", "kith-kanan"}), "@@do_skeleton");

    add_item("crown", "This is a graceful and beatiful regal crown. " +
      "Gold ornamented with valuable jewels in many colors and " +
      "intricate carvings. A truely wonderful piece of jewelry.\n");

    add_item(({"sword", "blade"}), "@@do_sword");

    add_cmd_parse("'cloak' / 'crown' / 'sword'", ({"get", "take"}),
      "You decide to not take it since it belongs to the dead king.\n");

    add_exit(PSLA + "hall01", "north");
    add_exit(PSLA + "hall03", "south");

    add_prop(ROOM_I_LIGHT, 0);
    gCounter = random(23);
    gSword = 0;

    reset_room(); /*gSword = 1;*/
}

public string
do_skeleton()
{
    string desc;

    desc = "It has once been a male - of what " +
    "race, you can't say, death being the great equalizer. The " +
    "figure is dressed in regal robes that, even though faded " +
    "and decayed, still give evidence of their richness. A " +
    "cloak covers the gaunt shoulders. A crown gleams on the " +
    "fleshless skull. The bone hands, fingers lying gracefully " +
    "in death";

    if (gSword) desc += ", rests on a sheathed sword";

    desc += ". Suddenly you realize who it is, Kith-Kanan, the greatest " +
    "of the elven kings.";

    return BS(desc, 70);
}

public void
leave_inv(object ob, object to)
{
    object sword;

    if(gSword)
    {
        if ((to == find_object(PSLA + "hall01")) && 
          (ob->query_prop("_live_i_killed_slug")))

        {
            write(BS("When you are about to leave, a bony hand of " +
                "the long dead king streches out and gives you " +
                "his sword.", 70));
            say(BS("As you are about to leave, a bony hand of the " +
                "long dead king stretches out and gives " +
                QTNAME(ob) + " his sword.", 70));

            gSword = 0;

            sword = clone_object(KRWEAPON + "wyrmslayer");
            sword->move(ob);

            ob->remove_prop("_live_i_killed_slug");
        }
    }
    ::leave_inv(ob, to);
}

public string
do_sword()
{
    if (gSword)
        return "This is a sword of elven design. The bright blade is " +
        "long, slender and looks almost unnaturally sharp.\n";

    return "You find no such thing.\n";
}


void
remove_blade()
{
    gSword = 0;
}

