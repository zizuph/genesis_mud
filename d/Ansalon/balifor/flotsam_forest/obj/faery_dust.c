inherit "/std/object";
#include <macros.h>
#include <wa_types.h>
#include <stdproperties.h>
#include <cmdparse.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/balifor/flotsam/local.h"

public int no_command();

void
create_object()
{
    seteuid(getuid());
    set_name("dust");
    add_name("faery_dust");
    set_short("faery dust");
    set_long("Faery dust that comes from various faery creatures. " +
      "It often causes confusion to non-elfin creatures it " +
      "comes in contact with.\n");

    set_no_show();

    add_prop(OBJ_I_WEIGHT,20);
    add_prop(OBJ_I_VOLUME,20);
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_NO_DROP,1);
    add_prop(OBJ_I_NO_GIVE,1);
}

init()
{
    ::init();
}

void
no_command()
{
    string str;
    string str2;
    object player = TP;

    if (!interactive(player) || player->query_linkdead())
        return;

    switch(random(8))
    {
    case 0:
	str = "giggle";
	break;
    case 1:
	str = "laugh maniac";
	break;
    case 2:
	str = "eeks";
	break;
    case 3:
	str = "say Mummy? Mummy?";
	break;
    case 4:
	str = "say No, not the dah!";
	break;
    case 5:
	str = "smile dream";
	break;
    case 6:
	str = "scream";
	break;
    case 7:
	str = "cower";
	break;
    }

    switch(random(10))
    {
    case 5..9:
	str2 = "You feel confused and lightheaded... where were you again?\n";
	break;
    case 0..1:
	str2 = "You feel on top of the world! You can do anything!\n";
	break;
    case 2:
	str2 = "A black-eyed massive human arrives sneaking.\n" +
	"The black-eyed massive human attacks you!\n" +
	"The black-eyed massive human hurts your right arm with his huge waraxe.\n" +
	"You are now hunting the black-eyed massive human.\n";
	break;
    case 3:
	str2 = "The ground suddenly turns into quicksand! You find yourself sinking...\n";
	break;
    case 4:
	str2 = "You feel as if you are being watched!\n";
	break;
    }



    write(str2);
    player->command(str);
    return;
}

void
remove_dragon_effect()
{
    write("Your head clears, and you no longer " +
      "feel quite so confused.\n");
    remove_object();
}

void
enter_env(object to, object from)
{
    ::enter_env(to, from);

    if(TP->query_prop(LIVE_I_UNDEAD) > 0)
    {
	write("Being undead, you are unaffected by the faery dust.\n");
	return;
    }

    set_alarm(400.0, 0.0, "remove_dragon_effect");
    set_alarm(20.0, 20.0, "no_command");
}
