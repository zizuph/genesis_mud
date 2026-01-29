#include <stdproperties.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

inherit AM_FILE

#define WEP FOBJ + "weapon/sm_knife"
#define KID_FAVOUR "_owed_favour_by_kid"

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("kid");
    set_short("street kid");
    set_long("This is a young homeless kid of about " +
      "13 years. Living in the abandoned warehouses of " +
      "Flotsam, he survives by begging, and occasionally stealing " +
      "peoples purses. \n");

    set_stats(({15,20,18,12,12,12}));
    set_hp(10000);

    set_alignment(0);
    set_knight_prestige(0);

    set_skill(SS_WEP_KNIFE, 30);
    set_skill(SS_DEFENCE, 5);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);

    add_ask("favour", VBFC_ME("wand_hint"));

    set_act_time(0);
    add_act("peek human");
    add_act("peek dwarf");
    add_act("peek elf");
    add_act("peek hobbit");
    add_act("peek gnome");
    add_act("peek goblin");
    add_act("giggle misch");
    add_act("say Hey you! Spare a copper?");
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    clone_object(WEP)->move(this_object(),1);
    command("wield all");
}

string
wand_hint()
{
    if(TP->query_prop(KID_FAVOUR))
    {
	command("scratch chin");
	command("say Okay, hows this...");
	command("say I saw the cabin boy for the Golden Lion " +
	  "trade something to one of the homeless fellas not so " +
	  "long ago.");
	command("say Dunno what it was though...");
	command("shrug");
	command("say But it must have been important, 'cause " +
	  "the cabin boy was pretty pissed that my street gang " +
	  "saw him do the deal.");
	command("grin");
	return "";
    }
    command("say Let me see... a favour you " +
      "want eh?");
    command("smirk");
    command("say Okay. Word on the street is that a " +
      "Black Robed elf walked through the streets of " +
      "Flotsam one dark night...");
    command("say Apparantly he came from burying something " +
      "in the forest to the south, although some say " +
      "he hid something in a farmhouse, others swear " +
      "it was in a boarded up house in Balifor.");
    command("twinkle");
    return "";
}

void
enter_inv(object ob, object from)
{

    ::enter_inv(ob, from);
    if (!interactive(from))
        return;

    if(ob->id("coin"))
    {
	command("twinkle greed");
	command("say Thanks mate! Guess I owe you a favour!");
	command("grin misch");
	TP->add_prop(KID_FAVOUR, 1);
	return;
    }

    command("peer suspic");
    return;
}
