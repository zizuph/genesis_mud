#include "/d/Ansalon/common/defs.h"
#include "../local.h"
#include <macros.h>
#include <stdproperties.h>

inherit KEN_OUT;

void
reset_kendermore_room()
{
    return;
}

create_kendermore_room()
{
    set_short("@@short_descr");
    set_long("@@long_descr");

    add_item(({"giant oak tree","oak tree","tree"}),
      "A great oak tree rises up before you, its huge limbs " +
      "stretching out above you, filled with a thick and " +
      "lush canopy of green. You think you can hear giggles " +
      "and laughter from within the leaves.\n");
    add_item(({"large roots","roots","root"}),
      "This area you stand within is nestled between two large roots.\n");
    add_item("rock","In the center of this grassy area " +
      "stands a rock of black granite. A shard of red " +
      "crystal rises out of the top of it, like a " +
      "butterknife stuck in a very large piece of black cheese.\n");
    add_item(({"red crystal","crystal"}),
      "A small crystal shard rises out of the rock here. " +
      "Staring at it closely, you notice it glows with a " +
      "strange, grey light. Could this be a shard of the fabled " +
      "Greygem of Gargath?\n");

    add_exit(KROOM + "r1","southeast",0);

    reset_kendermore_room();
}

string
short_descr()
{
    return "A grassy spot nestled between two large roots";
}

string
long_descr()
{
    return "You stand at the base of a giant oak tree " +
    "in a grassy area nestled between two large roots. " +
    "In the center of this spot is a rock, with a shard " +
    "of red crystal embedded within it. " +
    "\n";
}

int
leave_race(string str)
{
    if(!str || str != "my family ties")
    {
	notify_fail("Deny what? Your family ties?\n");
	return 0;
    }

    if(TP->query_race_name() != "kender")
    {
	notify_fail("Only kender can deny their " +
	  "kender family ties!\n");
	return 0;
    }

    write("You reach out and put your hand on the shard " +
      "of greygem. You feel a surge of power, and lo! You " +
      "are once again a hobbit!\n");
    say(QCTNAME(TP) + " reaches out and touches the " +
      "shard of crystal embedded in the rock. Suddenly, " +
      HIS(TP)+ " form begins to blur, and lo! " +HE(TP)+
      " turns into a hobbit!\n");
    if(TP->query_default_start_location() == GUILD_STARTLOC)
    {
	TP->set_default_start_location(TP->query_def_start());
    }
    return "/d/Krynn/raceguild/room/joinroom"->deny("my heritage of krynn", 1);

}

int
join_race(string str)
{
    string str1, str2, str3, str4;

    if(!str)
    {
	notify_fail("Adopt yourself into which family?\n");
	return 0;
    }

    if(TP->query_race() != "hobbit")
    {
	notify_fail("Ack! You can't adopt yourself into " +
	  "a kender family, you are a " +TP->query_race_name() + "!\n");
	return 0;
    }

    if(TP->query_race_name() == "kender")
    {
	notify_fail("You are already adopted into a " +
	  "kender family!\n");
	return 0;
    }

    if(TP->query_guild_name_race())
    {
	notify_fail("You are already a member of a racial guild!\n");
	return 0;
    }

    if (TP->query_guild_name_lay() == "Cabal of Hiddukel")
    {
        notify_fail("The kender family refuses to adopt a thief!\n");
        return 0;
    }

    if(sscanf(str, "%s %s %s %s", str1,str2,str3,str4) != 4)
    {
	notify_fail("The correct syntax is 'Adopt myself " +
	  "into <kender-name> family'.\n");
	return 0;
    }
    if(str1 != "myself" || str2 != "into" || str4 != "family")
    {
	notify_fail("The correct syntax to join is 'Adopt " +
	  "myself into <kender-name> family'.\n");
	return 0;
    }

    str3 = lower_case(str3);

    if(str3 != "bigpouch" && str3 != "burrfoot" &&
      str3 != "butterberry" && str3 != "fleetfeet" &&
      str3 != "lightheart" && str3 != "lockpicker" &&
      str3 != "makland" && str3 != "nettlekettle" &&
      str3 != "piemaker" && str3 != "starthumb" &&
      str3 != "stonethrower" && str3 != "streamskimmer" &&
      str3 != "talespinner" && str3 != "thistleknot" &&
      str3 != "trapspringer" && str3 != "treeskipper" &&
      str3 != "tendertongue" && str3 != "metwinger" &&
      str3 != "shadowpoker" && str3 != "nimblefingers" &&
      str3 != "tanglemop" &&
      str3 != "yawnmaster" && str3 != "burrthistle" &&
      str3 != "brambletow" && str3 != "tethersmeet" &&
      str3 != "flamehair" && str3 != "wrinklecap" &&
      str3 != "quickfoot" && str3 != "springtoe" &&
      str3 != "gatehop" && str3 != "pakslinger" &&
      str3 != "wanderfuss" && str3 != "gemgetter" &&
      str3 != "furrfoot" && str3 != "cloverleaf" &&
      str3 != "whistlerot" && str3 != "knotwillow" &&
      str3 != "elderdrake" && str3 != "twackdinger" &&
      str3 != "dunstan" && str3 != "cobblehammer" &&
      str3 != "hammerwart" && str3 != "lightfingers" &&
      str3 != "jingleburr" && str3 != "froghair" &&
      str3 != "goldring" && str3 != "thicketsway" &&
      str3 != "springheel" && str3 != "toymaker" &&
      str3 != "skitterbug" && str3 != "treehugger" &&
      str3 != "tippypaw" && str3 != "nimblenose" &&
      str3 != "ogrekicker" && str3 != "razortongue" &&
      str3 != "shadowcat" && str3 != "silkthread" &&
      str3 != "quicksilver" && str3 != "tenderfinger" &&
      str3 != "goldenknot" && str3 != "silverstreak" &&
      str3 != "wondercoin")
    {
	notify_fail("There is no kender family of that " +
	  "surname to adopt into.\n");
	return 0;
    }

    write("You reach out and touch the shard of greygem... " +
      "You feel your form begin to waver....\n");
    say(QCTNAME(TP)+ " reaches out and touches the shard of " +
      "crystal embedded in the rock. " +capitalize(HIS(TP))+ " form begins " +
      "to waver...\n");
    write("Lo! You have been transformed into a kender!\n");
    say("Lo! " +QCTNAME(TP)+ " has been transformed into a " +
      "kender!\n");

    return "/d/Krynn/raceguild/room/joinroom"->affiliate("myself with " +
      str3 + " within kender", 1);
}

void
init()
{
    ::init();
    add_action(join_race, "adopt");
    add_action(leave_race, "deny");
}
