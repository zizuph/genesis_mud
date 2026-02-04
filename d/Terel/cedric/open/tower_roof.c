inherit "/std/room.c";
#include <macros.h>
#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include "/d/Terel/cedric/guild/guild_defs.h"

/*
 * The Minstrel Guild Headquarters: The Bell Tower.
 * Here players look at the beautiful view and ring the bells.
 * Cedric and Jorl 2/93
 */


void
init()
{
    ::init();
    add_action("make_ring", "ring");
    add_action("make_ring", "pull");
}

void
do_ring()
{
    object *folks;
    int i;
    
    folks = on_line();
    for (i=0;i<sizeof(folks);i++)
	if (folks[i])
	    if (present(folks[i]))
		folks[i]->catch_msg(BS("The ringing of the bells, though almost "
		+ "deafeningly loud, nonetheless amazes and pleases you in "
		+ "an intricate interplay of harmonies and overtones.\n"));
	    else
		if (folks[i]->query_hear_bells())
		    folks[i]->catch_msg("Somewhere in the distance you hear "
		    + "the Bells of the Tower echoing melodiously.\n");
}

void
do_arrive(object player)
{
    object *folks;
    int i;

    folks = on_line();
    for (i=0;i<sizeof(folks);i++)
	if (folks[i])
	    if (present(folks[i]))
		folks[i]->catch_msg(BS("Suddenly, the bells begin to sound! "
		+ "You quickly realize that their melodious tones signal the "
		+ "arrival of a Minstrel to the world.\n"));
	    else
		if (folks[i]->query_hear_bells())
		    folks[i]->catch_msg(BS("Somewhere in the distance you hear "
		    + "the Bells of the Tower heralding the arrival of a "
		    + "Minstrel.\n"));
}

int
make_ring(string str)
{
    if (str == "bells"||str=="bell"||str=="rope")
    {
	say(QCTNAME(TP())+" pulls on the rope.\n");
        do_ring();
	return 1;
    }
    return 0;
}

void
create_room()
{
    set_short("The Bell Tower of the Minstrels");
    set_long(BS("The Bell Tower, on the roof of the famous "
    + "Tower, affords an exquisite view of the surrounding "
    + "countryside as well as the courtyard below.  Three large bells hang from "
    + "the rafters.  A thick rope hangs in one corner.\n"));
        
    add_item(("bells"), BS("The bells are quite large, and seem to be made of the "
    + "purest silver.  They must weigh a ton, much too heavy to carry. You imagine "
    + "they produce a lovely chime when sounded.\n"));

    add_item("view", BS("Would you like to admire the north view, the south view, "
    + "the east view, or the west view?\n"));
    add_item("rope", "Pull this massive rope, and you feel sure that the bells "
    + "will be heard for a great distance indeed.\n");
    add_item("north view", BS("The view to the north is breathtaking, from "
    + "here you can look out over the courtyard and the neatly manicured "
    + " gardens.  Across the river you can see the bustling town of Calathin, "
    + "nestled at the edge of the Silver forest.  The day is quite clear so you "
    + "are able to see the range of snow covered mountains in the far distance.\n"));
    add_item(({"courtyard", "yard", "dias"}), BS("You peer down into the oddly "
    + "shaped courtyard.  From up here the yard looks dish-shaped, with the "
    + "dias at the focal point.  It looks like the perfect place to perform, "
    + "as the acoustics would be fantastic.\n"));
    add_item(({"town", "calathin"}), BS("In the distance you see the town of "
    + "Calathin.  This small town lies just south of the Silver Forest.  Smoke "
    + "rises from several chimneys and between some of the buildings you can "
    + "see the warmly-bundled citizens scurrying to and fro.  Just east of "
    + "town you see a dark mansion in amongst some trees, no doubt the home of "
    + "the infamous de Avenchirs.\n"));
    add_item("mountains", BS("Beyond the Silver Forest you see a range of "
    + "mighty peaks, their jagged tops covered by a thick blanket of snow "
    + "year-round.  Peering into the distance you cannot help but feel an "
    + "enormous sense of awe, for many songs of the north tell that in some "
    + "fertile valley or perhaps deep with in the heart of some mountain lies a "
    + "community both revered and feared; the Ancient Order of the Mystics.\n"));
    
    add_item("forest", BS("Which great forest would you care to gaze upon, "
    + "the Silver or the Enchanted?\n"));
    
    add_item(({"silver", "silver forest"}), BS("The snow-covered trees of the "
    + "forest glisten in the sunlight.  It is easy to understand why it was "
    + "given the name 'Silver Forest'.  The pines that comprise the main type "
    + "of tree in the forest are quite tall, even so one in particular stands "
    + "out.  This gigantic tree marks the southern border of the forest and the "
    + "northwestern corner of the town of Calathin.  This lone sentinel "
    + "brings forth the image of some ancient god buried beneath the snow, its "
    + "index finger pushing up through the earth of its grave to test the "
    + "wintry air.\n"));
    
    add_item("south view", BS("The view to the south fills you with a strange "
    + "feeling, for in this direction lies the Enchanted Forest.  A thin "
    + "stream of smoke rises at the northern edge of the forest from some sort "
    + "of encampment.  The air is fresh and still; you imagine you can almost "
    + "hear the sound of the waves crashing on the rocky shore, far to the "
    + "south.\n"));
    
    add_item(({"enchanted", "enchanted forest"}), BS("You get an odd, queasy "
    + "feeling as you stare at the vast forest to the south.  You can't seem "
    + "to bring any of the trees quite into focus, as if the forest were "
    + "blanketed by a misty haze, yet the day is perfectly clear.  You sense "
    + "a kind of shifting, as if the trees themselves were alive.  You've been "
    + "told it is a magical place, full of strange people and beasts of legend.\n"));
    
    add_item("east view", BS("You can see the smoke rising from farm houses "
    + "east of here.  The river that flows just north of the guild palace "
    + "continues into the distance.\n"));
    
    add_item("west view", BS("The ground rises a bit to the west.  You can see "
    + "that a large area just northwest of the palace has been cleared by the "
    + "residents of Calathin in order to provide building materials and "
    + "farmland.  The river that flows just north of the guild palace must come "
    + "from some high mountain spring far to the northwest.\n"));
    
    add_exit(GUILD+"tower_3", "down");
    add_prop(ROOM_I_INSIDE, 1);
}

void
reset_room()
{
    ::reset_room();
    do_ring();
}
