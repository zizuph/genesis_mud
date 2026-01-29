// file name:       assessor.c
// creator(s):      Nikklaus, Jul'97
// revision history:
// purpose:         Environmental npc, an import tax assessor, also assigns and
//                  and collects delivery tours.
// note(s):         Non-drowish 1/2 elf.  Just cause I wanted one in Undraeth.
// bug(s):
// to-do:
/*
 * Re-patriated code back to the Kalad domain.
 * 	- Lucius, June 2017
 */
# pragma strict_types
#include "/d/Kalad/defs.h"
#include "/d/Genesis/delivery/delivery.h"
# include <const.h>
# include <macros.h>
# include <ss_types.h>
# include <stdproperties.h>

inherit "/d/Kalad/std/monster";
inherit "/d/Kalad/lib/intro";
inherit CPASS(drow/npc/npc_std);
inherit DELIVERY_OFFICE;

object baertuuk;

void
reset_monster()
{
    reset_office();
}

public void
create_monster()
{
    extra_long = "";  /* He won't have the jet black skin of the drow. */
    set_race_name("half-elf");
    add_name("elf");
    add_name("human");
    add_name("halfelf");
    set_living_name("simeon");
    set_name("simeon");
    set_adj("scowling");
    add_adj("silver-haired");
    set_title("the Customs Tax Assessor of Undraeth");
    set_office(this_object()->query_title());
    set_gender(G_MALE);
    set_alignment(-600);
    set_knight_prestige(-3);  /* tsk...knights killing _two_ quest npc's? */
    set_long("In sharp contrast to the drow around him, this "+
      "fair-skinned, slightly taller figure is the only one in the room "+
      "without armor or insignia. A sleeveless indigo robe exposes his "+
      "broader shoulders and bulkier biceps, juxtaposing oddly with the "+
      "tiny hexagonal spectacles balanced on the tip of his nose. "+
      "Pointed ears and sharp, high cheekbones indicate elvish blood, "+
      "but the bushier eyebrows and hint of stubble on his chin belie "+
      "his human heritage.\n");
    set_act_time(4);
    add_act("emote beckons to two arriving Scouts, pointing with the "+
      "feather of his quill at several crates. The Scouts collect the "+
      "crates from the stack and hurry from the room.");
    add_act("emote reseals a crate and drags it across the floor with "+
      "a loud grinding sound of gravel being produced from granite. "+
      "He stacks it with the others behind the counter and signs the "+
      "top sheet of a stack of papers.");
    add_act("emote listens unsympathetically to a human merchant's "+
      "pleas. The merchant discretely graces the half-elf's palm with a "+
      "glinting metal. They conclude their business with an amicable "+
      "handshake.");
    add_act("emote glances up at another crate being brought in, "+
      "then gestures distractedly at a clear space of floor it could "+
      "be left at.");
    set_speak("I assess the value of certain mercantile goods "+
      "entering and leaving the city, then determine the applicable levy. "+
      "I also arrange for their shipment and distribution. I could use "+
      "more couriers, so ask me about delivery if you're interested.\n");
    set_default_answer("Simeon stops jotting notes and surveying "+
      "goods just long enough to snap: Can't you see I'm busy? Stop "+
      "wasting my time!\n");
    add_ask(({"baertuuk", "Baertuuk", "bored drow", "scarred drow",
	"bored scarred drow"}),
      "Simeon observes wryly: It's the promotion he's always dreaded. "+
      "Invaders and assassins he'll survive, this'll be the death "+
      "of him.\n");
    add_ask(({"delivery tour", "delivery", "deliveries", "couriers"}),
      delivery_poster());

    add_content(CPASS(drow/obj/silk_bolt));
    add_content(CPASS(drow/obj/diamond));
    add_content(CPASS(drow/obj/rothe_skin));
    add_content(CPASS(drow/obj/gem_dark));
    add_content(CPASS(drow/obj/backpack));
}

public void
print_message(string str)
{
    command("say to "+TP->query_name()+" "+str+"\n");
}

void
init_living()
{
    ::init_living();
    init_office();
}

public int
set_leader(object leader)
{
    if (!baertuuk)
	baertuuk = leader;
    return ::set_leader(leader);
}

public void
enter_env(object env, object from)
{
    ::enter_env(env, from);
    if (baertuuk = present("baertuuk", environment(TO)))
	baertuuk->team_join(TO);
}

public mixed
query_companion()
{
    return baertuuk;
}
