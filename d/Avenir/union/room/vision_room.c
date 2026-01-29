/*
 * Room of visions
 *  This is where the members of the Union accepted for
 *  the guru quest are moved, and gives a series of visions
 *  to the player.
 *
 *    -Cirion, May 2, 1996
 *
 * Revisions:
 * 	Lucius, Aug 2017: Re-Coded.
 *
 */
#pragma strict_types
#include "../defs.h"

inherit BASE;

#include <macros.h>
#include <stdproperties.h>


public int index = -1;
public object questor;

/* This variable contains all the code for the visions the players
 * will experience, in the form:
 * ({ room short desc, room long desc, add_items, move message
 * A single string will be just a tell that the player will receive,
 * and a single int will be the delay until the next vision
 */
public mixed *visions = ({ ({
	"darkest night",
	"You are in a world of pitch black. Strange figures, shadows "+
	"upon shadows, move in terrible and flowing motions.\n",
	({ ({ "shadow","shadows","forms","figure","figures"}),
	    "The shadowy figures are indistinct and terrible, the forms "+
	    "that arise from your worst dreams.\n"
	}),
	"You ascent into a black place, a place of the darkest nights "+
	"and worst nightmares.\n"
    }), ({
	"place of stars",
	"Sparkling like a million distant jewels, the darkness around "+
	"you is filled by dazzling points of light that seem to reach "+
	"into your soul, stabbing deep into your being. Direction has "+
	"lost all its meaning, as if this place were some mocking "+
	"distortion of reality.\n",
	({ ({ "star","stars","point","points" }),
	    "The stars glow painfully bright.\n"
	}),
	"You rise into a place of stars.\n"
    }),
    "The stars begin spinning about you in slow, lazy circles.\n",
    "They continue to speed up until they are reduced to dizzying "+
	"trails of white light.\n",
    ({
	"place of light and darkness",
	"This is the dividing line between light and dark, the realm "+
	"where shadows emerge and dwell. You can make out no shapes or "+
	"forms, just a sickening sensation of distortion, as if you had "+
	"fallen too deeply into the Sway.\n",
	({ ({ "light","dark" }),
	    "The light and the dark seem to merge together, in one line, "+
	    "now as it once was.\n", "line", "The dividing line is "+
	    "infintesimal, its actual existence questionable.\n",
	   ({ "shape","form","shapes","forms" }),
	   "There are neither shapes nor forms here.\n"
	}),
	"A star " + one_of_list(({"below","to the left of",
		"to the right of","above","before"})) +
	    " you suddenly grows giant-sized before you, and you are "+
	    "engulfed.\n"
    }), ({
	"above the world",
	"Rotating lazily below you is an enormous torus of unimaginable "+
	"size. Dotting the mostly blue surface are tiny grey shapes over "+
	"which wisps " + "of white mist blow.\n",
	({ "torus",
	    "It is a massive torus, eerily floating on a sea of nothing, "+
	    "almost a fiction.\n",
	   ({ "shape","shapes" }),
	    "The shapes dotting the torus seem almost familiar.\n",
	   ({ "wisps","wisp","mist","cloud","clouds"}),
	    "They are white, and move lazily along the surface of the "+
	    "great form below.\n"
	}),
	"A great shape forms below you.\n"
    }), ({
	"over a dark desert",
	"Great winds buffet you, filling your eyes and mouth with gritty "+
	"sand. The desert below, however, is unbearably peaceful. Dunes "+
	"of sand, ephemeral and ever-changing, lie all along the ground.\n",
	({ "sand", "It is ever-changing, ephemeral.\n",
	   "desert", "It is covered with dunes.\n",
	   ({ "dune","dunes" }),
	    "They are low, formless masses.\n"
	}),
	"Moving at an unearthly speed, the shape below you suddenly "+
	    "grows, filling your vision.\nYou pass through cold, wet "+
	    "mist, and find yourself above a dark plain of sand and wind.\n"
    }),
    "Haloed by lines of orange-red light, the sun rises over the "+
	"earth's sharp edge.\n",
    "The winds calm.\n",
    ({
	"silent sea",
	"The deep azure sea stretches in all directions, a thin cold "+
	"morning haze rising up in whisps. The water is flat and "+
	"peaceful, unmarred by even a ripple.\n",
	({ "sea", "It is silent and calm.\n",
	   "water", "It is a shade of blue you have never before seen.\n",
	   "haze", "It obscures your vision in all directions.\n",
	   "mountain",
	    "It is a huge, craggy edifice. It seems to have risen "+
	    "from the sea by some great force, ages and ages ago.\n"
	}),
	"You pass over a seashore and out over a vast, limitless sea.\n"
    }),
    "You continue to glide over the sea.\n",
    "You approach a vast mountain, rising from the sea like a great fist.\n",
    ({
	"within the cavern",
	"A great cavern lies below you, the floor of which is a black sea "+
	"dotted with dozens of islands of various shapes and sizes. The "+
	"cavern ceiling, close above, is laced with veins of a pulsating "+
	"luminous rock.\n",
	({ ({"sea","ocean"}),
	    "The great underground sea streatches out thousands of " +
	    "meters beneath you, making for a breathtaking sight. "+
	    "Throughout the sea are islands of various sizes, and you "+
	    "can even make out a ship or two travelling accross the "+
	    "waters. The light from above does not penetrate the sea, "+
	    "making it a heavy shade of black.\n",
	   ({"island","islands"}),
	    "There are a number of islands of various shapes and sizes "+
	    "far beneath you in the sea. From this height you can make "+
	    "out few details, but one larger island in the centre seems "+
	    "to contain a city, while others appear to be green with "+
	    "forests and vegitation.\n",
	   ({"ceiling","rocks","cave","cavern","Sybarus"}),
	    "Spreading out to the east you can see the enormous cavern "+
	    "ceiling that stretches over all of the land. It seems to be "+
	    "criss-crossed by veins of some substance that sheds a "+
	    "dazzling white light. The veins seem more prominent on the "+
	    "eastern reaches of the ceiling, many leagues away.\n"
	}),
	"The mountain grows to fill your entire vision, and suddenly you "+
	"find that you have passed through it.\nA terrible feeling of "+
	"vertigo fills you.\n"
    }),
    "You glide down near to the green island.\n",
    ({
	"green path",
	"You are over a dark ledge, the southern end of a path through "+
	"dense green vegetation. The ledge juts out over a black sea. "+
	"Far to the south, over the dark waters, you can make out some "+
	"sort of fortress. To the east and the west, the edge of the "+
	"island continues, thickly covered in vegetation.\n",
	({ ({ "vegetation","plant","plants" }),
	    "It is thick and prolific everywhere.\n",
	   "sea", "It is dark and impenitrable.\n",
	   "path", "It looks somehow familiar.\n"
	}),
	"You pass over the island, towards to the southern end.\n"
    }), ({
	"dark sea",
	"You are moving along the face of a dark, silent sea.\n",
	({ ({ "sea", "water" }),
	    "It is black, darker than the deepest sleep.\n"
	}),
	"You move over the sea to the east.\n"
    }),
    "You continue to pass along the sea.\n",
    ({
	"smooth ledge",
	"You are just over the lip of a smooth rock ledge at the "+
	"eastern face of the cavern, hanging over the sea like a "+
	"landing. A passage leads into the rock face to the east, "+
	"from which the flicker of torchlight can be seen.\n",
	({ ({ "ledge", "rock" }),
	    "The stone is smooth and seamless.\n",
	   "sea", "It is dark.\n",
	   "passage", "It leads into the eastern face of the wall.\n",
	   ({ "light", "torchlight" }),
	    "The torchlight eminating from the passage sends soft "+
	    "shadows out upon the ledge.\n",
	   ({ "figure", "shape" }),
	    "The figure is dressed in formless, swadling grey garments, "+
		"its face hidden by a dark veil.\n"
	}),
	"You approach a ledge at the eastern face of the cavern.\n"
    }),
    "A shadowy figure steps out of the passage onto the ledge.\n",
    "The shadowy figure seems to be examining you closely.\n",
    "The shadowy figure says: "+ VBFC_ME("questor_name") +", "+
	"you have served the Union well.\n",
    "The shadowy figure says: The time has come for you to realize "+
	"your potential as a Warrior of Shadow.\n",
    "The shadowy figure says: Seek out this place, the place of my "+
	"rest.\n",
    "The shadowy figure says: Offer this unto the water, and the "+
	"naiads will guide your way.\n",
    "The shadowy figure gives you something.\n"+ VBFC_ME("give_phial"),
    "The shadowy figure turns and walks down the passage.\n",
    "You feel a lurching, sickening sense of nausea all of a sudden.\n"
});


public void
union_room(void)
{
    set_short("in a vision");
    set_long("You are standing in a formless void, "+
	"lost amidst a vision.\n");

    add_prop(ROOM_M_NO_ATTACK, 1);
    add_prop(ROOM_M_NO_MAGIC_ATTACK, 1);
    add_prop(ROOM_M_NO_TELEPORT, 1);
    add_prop(ROOM_M_NO_MAGIC, 1);
}

/* "redraw" the items in the room */
public void
remake_items(void)
{
    mixed *new = visions[index][2];

    obj_items = 0;

    for(int i = 0; i < sizeof(new); i += 2)
	add_item(new[i], new[i+1]);
}

public void
end_visions(void)
{
    /* put the player on the verge of death */
    questor->add_mana(-10000);
    questor->add_fatigue(-10000);
    questor->heal_hp(-10000);
    questor->add_panic(10000);

    /* move the player back to his start location */
    questor->move_living("M", questor->query_def_start(), 0, 1);
    questor->catch_tell("You find youself in a strangley familiar place.\n"+
	"You fall to the ground, exhausted and on the verge of death.\n");

    set_alarm(1.0, 0.0, remove_object);
}

public int
next_vision(object who)
{
    int delay;

    if ((index + 1) >= sizeof(visions))
    {
	set_alarm(1.0, 0.0, end_visions);
	return 0;
    }

    index++;

    if (intp(visions[index]))
    {
	delay = visions[index];
    }
    else if (stringp(visions[index]))
    {
	questor->catch_msg(visions[index]);
	delay = strlen(visions[index]) / 10;
    }
    else
    {
	set_short(visions[index][0]);
	set_long(visions[index][1]);
	remake_items();

	/* Sent the player the "skip message" */
	questor->catch_msg(visions[index][3]);

	/* make them take a look */
	questor->do_glance(0);

	/* delay until the next message is depentant of the length of the */
	/* long description of the room the player is in                  */
	delay = strlen(query_long()) / 10;
    }

    set_alarm(itof(delay), 0.0, next_vision);
}

/* Nothing left in the cloned room? dest it to save memory */
public void
remove_if_empty(void)
{
    if (!questor || !present(questor))
	remove_object();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!query_interactive(ob))
	return;

    if (IS_CLONE)
    {
	questor = ob;
	set_alarm(1.0, 0.0, next_vision);
	return;
    }

    /* move the living to a clone of this room if it is the master object, */
    ob->move(clone_object(MASTER_OB(TO)));
}


public void
leave_inv(object ob, object dest)
{
    ::leave_inv(ob, dest);

    /* set last room to the master, so the player isn't screwed if he */
    /* link dies then comes back (lost in space!)                     */
    if (IS_CLONE && query_interactive(ob))
	ob->add_prop(LIVE_O_LAST_ROOM, MASTER_OB(TO));

    set_alarm(1.0, 0.0, remove_if_empty);
}

public string
give_phial(void)
{
    clone_object(OBJ + "phial")->move(questor, 1);
    return "";
}

public string
questor_name(void)
{
    if (!questor)
	return "You";
    else
	return questor->query_name();
}
