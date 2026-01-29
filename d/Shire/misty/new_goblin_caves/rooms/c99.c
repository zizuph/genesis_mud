/* goblin caves
 * Fixed a bug with shout. Rohim.
 *
 * Added a enter_inv check for players coming from the statue room since
 * suspected players were link dieing and coming back to find a free 
 * halberd lying on the ground for them.
 * -Igneous-
 */

#include "../local.h"
#include <config.h>
#include "/d/Shire/sys/defs.h"

inherit SHIRE_ROOM;

#define PASSWD_TO_THIS_PLACE  "_passwd_to_this_place"
#define ABC ({"a","b","c","d","e","f","g","h","i","j","k","l","m","n","o","p","q","r","s","t","u","v","w","x","y","z"})

string rune;

void
create_shire_room()
{
    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_INSIDE, 1);

    /*
	set_short("a secret treasure chamber with a rune on the wall\n@@rune_text");
     */
    set_short("a secret treasure chamber with a rune on the wall");
    set_long("This is the treasure chamber of goblin lord. There is nothing "+
      "special here except for the fact that this room has no exit "+
      "and the rune on western wall.\n"+"@@rune_text");

    add_item("rune", "Maybe you can try to read it.\n");
    add_item(({"wall","walls"}), BS("You already know that there is some "+
	"magic in the western wall.\n"));

    add_prop(ROOM_I_NO_CLEANUP, 1);
}

string
get_rune_text() 
{
    int i;

    rune = "";
    for(i=0; i<10; i++)
	rune += ABC[random(26)];
    return rune;
}

string
query_rune()
{
    if (!rune)
	get_rune_text();
    return rune;
}

string
rune_text()
{
    if (!rune)
	get_rune_text();
    if(TP->query_prop(PASSWD_TO_THIS_PLACE) ||
      random(TP->query_skill(SS_LANGUAGE)) > (20 + random(30)))
    {
	TP->add_prop(PASSWD_TO_THIS_PLACE, 1);
	return "The rune reads:\n     "+rune+"\n";
    }
    return "Unfortunately you can't read it.\n";
}

void
init()
{
    ::init();
    add_action("shout_name", "shout");
    add_action("read_rune", "read");
}

int
read_rune(string thingy)
{
    NF("Read what?\n");
    if(thingy != "rune") return 0;
    if (TP->query_prop(PASSWD_TO_THIS_PLACE) ||
      TP->query_skill(SS_LANGUAGE) > (10 + random(30)))
    {
	TP->add_prop(PASSWD_TO_THIS_PLACE, 1);
	TP->catch_msg("You manage to understand that the rune say:\n"+
	  "\t" +rune + "\n");
    }
    else
	TP->catch_msg("You read the rune carefully but fail to grasp what it " +
	  "means.\n");
    return 1;
}

int
shout_name(string something)
{
    if (!something)
	return 0;
    if(something == rune)
    {
	TP->catch_msg("You take deep breath and shout: "+something+
	  "\nStrangely all sound is absorbed by western "+
	  "wall.\nAfter the sound wall absorbs you too!\n");
	say(QCTNAME(TP)+" takes deep breath and shouts something. You can't "+
	  "tell what it was because western wall absorbs all sound.\n"+
	  "Ooops!!! The wall absorbs "+QTNAME(TP)+" too!\n");
	tell_room(ROOMS_DIR+"c64","The eastern wall starts to emit something. "+
	  "Suddenly "+QTNAME(TP)+" is standing here.\n");
	TP->move_living("M",ROOMS_DIR+"c64", 1);
	return 1;
    }
    TP->catch_msg("You take deep breath and shout: "+something+"\n"+
      "Strangely all sound is absorbed by western wall.\n");
    say(QCTNAME(TP)+" takes a deep breath and shouts something. You can't "+
      "tell what it was because the western wall absorbs the sound.\n");
    return 1;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob,from);

    if (!interactive(ob))
	return;

    if (file_name(from) == OWN_STATUE)
	ob->move(ROOMS_DIR + "c63");
}
