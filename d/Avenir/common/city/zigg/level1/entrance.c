/*
*  file name:   ~entrance.c
*  creator(s):  Zielia
*  last update:
*  purpose:     Entrance to the Ziggurat. Players must wash here to enter.
*  note:
*  bug(s):
*  to-do:
*/
#pragma strict_types

#include "zigg.h"

inherit ZIG_ROOM;
inherit RLOG;

#include <macros.h>
#include <composite.h>
#include <stdproperties.h>

#define PROP_I_WARNED    "_warned_by_hizzy"

private static int extra;
private static object *maiden = ({ }), *guards = ({ });

private int check_dirty(void);

public void
reset_room(void)
{
    if (extra)
	extra--;

    maiden = container_objects[ZIG_MON + "maiden"][3];
    guards = container_objects[ZIG_MON + "defender"][3];

    if (sizeof(guards) == 2)
	guards[0]->team_join(guards[1]);
    if (sizeof(maiden))
	guards[0]->team_join(maiden[0]);
}

private int
move_to_stairs(void)
{
    object room = clone_object(STAIR_ROOM);

    if (!objectp(room))
    {
	write("There seems to be an issue using the stairs.\n"+
	    "Notify an Avenir wizard of the problem.\n");
	return 1;
    }

    write("You begin your descent down the outer Ziggurat steps...\n");
    say(QCTNAME(TP) +" begins descending the outer Ziggurat steps.\n");

    TP->move_living("M", room);
    return 1;
}

static void
zig_room(void)
{
    setuid();
    seteuid(getuid());

    set_short("Entrance to the Ziggurat");
    set_long("High atop the Ziggurat, the view of the "+
	"Forbidden City stretches out in every direction. Source-light "+
	"filters in between the double rows of tall, black pillars "+
	"supporting a pyramid-shaped dome. From the apex of the dome, an "+
	"extravagant chandelier glows softly with its own light, casting "+
	"sparkling reflections in the rippling water of the fountain "+
	"at the center. Across from the fountain, massive stone steps "+
	"descend along the outside of the Ziggurat down to the path below. "+
	"Behind the fountain, another guarded stairway leads into the "+
	"depths of the pleasure palace.\n");

    add_exit("/dummy", "stairs", move_to_stairs);
    add_exit(ZIG_RL2 + "stairs", "down", check_dirty, 2, 0);

    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_M_NO_MAGIC, "The light suddenly pulsates fiercely, absorbing "+
        "the power emanating from you.\n");
    add_prop(ROOM_I_LIGHT, 5);

    add_item(({ "dome", "ceiling",}), "Sometimes called a "+
	"cloister dome or domicial vault, it is shaped like a hollow "+
	"pyramid and carved from naturally black stone, it blocks the "+
	"light from the Source directly overhead. Suspended from the apex "+
	"is a magnificent chandelier. All around the edges, tall stone "+
	"pillars support it.\n");

    add_item(({ "stair", "stairs",}), "Across from the "+
	"fountain, massive stone steps descend along the outside of the "+
	"Ziggurat down to the path below. Behind the fountain, another "+
	"guarded stairway leads into the depths of the pleasure palace.\n");

    add_item(({ "floor", "ground" }),
	"The floor is made of natural stone black stone, "+
	"worked smooth and polished to a glossy shine.\n");

    add_item(({ "chandelier", "chandeliers", "crystals", "droplet",
	"droplets", }),
	"Hanging high overhead, the opulent chandelier is made of many "+
	"small source-crystals, surrounded by hundreds of droplet-shaped "+
	"lead-glass crystals. The source-crystals glow softly, their "+
	"light, reflecting and dancing off of the carefully faceted "+
	"glass crystals, creating the illusion of countless water droplets, "+
	"suspended in time, ready to shower the pool below.\n");

    add_item(({ "basin", "basins", "pool", "pools", }),
        "Water pours from a earthenware pitcher held by "+
	"an imposing statue into a large, deep basin made of black stone. "+
	"Delicately carved scenes decorate the outside of the basin while "+
	"the inside appears smooth and fathomlessly dark. It is difficult "+
	"to make out the bottom but if that is a result of the blackness "+
	"of the stone or the depth of the pool is impossible to tell.\n");

    add_item(({ "bottom", "bottoms",}),
	"You cannot see the bottom of the basin, only stygian blackness.\n");

    add_item(({ "scene", "scenes", "carving", "carvings", }),
        "All around the outside of the fountain's basin are "+
	"delicately carved scenes of sensual sea nymphs seducing Sybarite "+
	"nobles and luring them toward pleasure or dispair or in some "+
	"cases, both.\n");

    add_item(({ "fountain", "fountains", "statue", "statues", }),
        "A towering statue stands overlooking the round "+
	"basin of the fountain. Exquisitly carved in the form of a tall, "+
	"four-armed man, dressed in swaddling clothes, the statue is made "+
	"of the same black stone of the rest of the fountain. Flawless "+
	"white spheres of ivory have been set in the place of his eyes and "+
	"the artist managed to capture an expression of cruel amusment on "+
	"his face. Above his head, one hand holds a lightning-bolt wrought "+
	"of silver, in another he holds a jeweled fish delicately by the "+
	"tail as though he has just plucked it from the water, or perhaps "+
	"is about to drop it back in. In his third hand, hanging absently "+
	"by his side, he gently holds a small bouquet of grass. In his "+
	"fourth hand he holds an ordinary earthenware pitcher, pouring "+
	"its contents into the waiting basin.\n");

    add_item(({ "bolt", "bolts", "lightning-bolt", "lightning-bolts", }),
        "Forged from the finest silver, it shines brightly, "+
	"even in the fluctuating light of the source-crystals. The statue's "+
	"fist is curled tight around it, ready to cast it at the slightest "+
	"offense or faintest whim.\n");

    add_item(({ "fish", }), "Dozens of tiny, colorful gems "+
	"set in platinum comprise the scales of the fish and carefully "+
	"crafted platinum and abalone fans make the fins. This piece of "+
	"the statue alone would fetch a small fortune at any market.\n");

    add_item(({ "grass", "grasses", "bouquet", "bouquets", }),
        "Although the statue holds the bouquet almost "+
	"absently, the grass blades were crafted with careful attention. "+
	"Wrought out of green gold and hammered parchment thin, they look "+
	"delicate enough to be crushed if they weren't held so gently.\n");

    add_item(({ "pitcher", "pitchers", }), "The statue holds "+
	"an ordinary looking clay pitcher with a large looping handle and "+
	"protruding pouring lip. It is unadorned except for three wavy "+
	"lines painted in blue on the side. There is no visible means for "+
	"the pitcher to refill and yet it constantly pours out cool, clean "+
	"water into the basin below.\n");

    add_item(({ "reflection", "reflections", "water", }),
	"The water flows in endlessly, creating steady ripples in the dark "+
	"water. Though there is no discernible drainage, the water level "+
	"remains constant, lapping just below the lip of the basin. "+
	"Scattered white reflections sparkle over the clear surface "+
	"lending contrast to the black depths of the pool.\n");

    add_item(({ "columns", "column", "pillar", "pillars" }),
	"Tall circular pillars of glossy, black stone frame the surrounding "+
	"view of the shimmering, pulsing Source and the City far below. "+
	"The wide, fluted shafts flow seamlessly to become the ribs of the "+
	"dome, each line capturing the elegance and graceful movement "+
	"revered by the Shadow Elves.\n");

    add_item(({ "view", "views", }), "Beyond the glossy, "+
	"floral pillars the Forbidden City of Syb'arus Aveni Idrys "+
	"sprawls out in three circling lobes. The enclave walls shine "+
	"faintly beneath the light of the Source, forming the trefoil "+
	"shape emblematic of Sybarus. To the south, the enclave of the "+
	"High Lord Commisioner stands, opulent noble houses circling "+
	"the High Lord's palace on the central hill. Similar scenes "+
	"present themselves to the northwest and northeast where the "+
	"High Lord Inquisitor's and High Lord Executioner's enclaves "+
	"can be seen.\n");

    add_npc(ZIG_MON + "maiden", 1, &->equip_me());
    add_npc(ZIG_MON + "defender", 2, &->equip_me());
}

private int
check_dirty(void)
{
    int sz = sizeof(guards = filter(guards, objectp));

    if (!sz)
    {
	if (!sizeof(maiden = filter(maiden, objectp)))
	{
	    logrotate(ZIG_LOGS + "entrance",
		time2format(time(), "mmm dd yyyy tt: ") +
		TP->query_cap_name() +" entered the Ziggurat "+
		"after combat.\n");

	    return 0;
	}

	maiden[0]->command("emote blocks the passage down the stairwell.");
	maiden[0]->command("shout Defenders! To me!");

	if (!extra)
	{
	    extra = 4 + random(4);

	    reset_auto_objects();
	    reset_room();

	    tell_room(TO, "A pair of Defenders rush up from below "+
		"and flank the stairwell entrance.\n", 0, maiden);
	}
	else
	{
	    maiden[0]->command("emote glares defiantly as no help arrives.");
	}

	return 1;
    }

    if (TP->query_prop(PROP_I_CLEANSED))
    {
	write(CAP(COMPOSITE_LIVE(guards)) +
	  (sz == 1 ? " eyes " : " eye ") +
	  "you warily as you head down the stairwell.\n");
#if 0
	logrotate(ZIG_LOGS + "entrance",
	    time2format(time(), "mmm dd yyyy tt: ") +
	    TP->query_cap_name() +" entered the Ziggurat "+
	    "purified.\n");
#endif
	return 0;
    }

    write(CAP(COMPOSITE_LIVE(guards)) +
      (sz == 1 ? " blocks " : " block ") +
      "your passage down the stairwell.\n");

    say(QCTNAME(TP) +" tries to head down the stairwell but is "+
	"blocked by "+ QCOMPLIVE +".\n", TP);

    return 1;
}

private int
bolt_of_wrath(void)
{
    write("A voice like thunder pounds against your eardrums: "+
      "You do not heed warnings very well, mortal, so perhaps "+
      "you shall heed this!\n");
    write("\nThe carved bolt of lightning in the statue's upraised arm "+
      "glows a sharp blue-white and there is a flash followed by "+
      "searing pain as the electric bolt strikes your chest, sending "+
      "you staggering!\n");

    say(QCTNAME(TP) +" moves to disturb the dark waters but goes still, "+
      "as though listening to some distant voice. Suddenly, the "+
      "lightning bolt held by the statue comes to life in a bright, "+
      "blue-white flash that shatters into "+ QTNAME(TP) +" and sends "+
      HIM(TP) +" staggering backwards.\n");

    /* Ouch! */
    TP->heal_hp(-(500 + random(500)));

    return 1;
}

public int
f_disturb(string str)
{
    if (!IN_ARRAY(str, ({"basin","pool","water","fountain"})))
	return 0;

    ALTER_PROP(TP, PROP_I_WARNED, 1);

    if (TP->query_prop(PROP_I_WARNED) >= 2)
	return bolt_of_wrath();

    write("As you move to disturb the dark waters, your eyes are "+
      "instead drawn to those of the statue and for the briefest of "+
      "moments, the flawless white spheres go dark with silver flashes, "+
      "as if a storm rolled through them.\n");
    say(QCTNAME(TP) + " moves to disturb the dark waters, but hesitates as "+
      HE(TP) +" looks up at the four-armed statue.\n");

    return 1;
}

public void
init(void)
{
    ::init();

    add_action( f_disturb, "bathe"  );
    add_action( f_disturb, "wash"   );
    add_action( f_disturb, "drink"  );
    add_action( f_disturb, "splash" );
}

public nomask int
prevent_leave(object who)
{
    object *sarr = guards + maiden;

    if (!pointerp(sarr) || IN_ARRAY(who, sarr))
	    return 1;
    return 0;
}
