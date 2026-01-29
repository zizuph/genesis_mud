#pragma strict_types

#include "../defs.h"
#include "/d/Avenir/include/deities.h"

#include <macros.h>
#include <composite.h>
#include <filter_funs.h>

inherit BASE;
/* Inherit the room_tell functions */
inherit "/d/Avenir/inherit/room_tell";

public int summon;
public object npc;

#ifdef UOPT_RMTXT
public int
skip_room_tells(object who)
{
    return !LIST->query_union_option(who, UOPT_RMTXT);
}
#endif

public void
reset_room()
{
    summon = 0;
    npc->leave();
}

public void
union_room()
{
    set_short("sacred space");
    set_long("The darkness pulses with life of its own, a "+
      "presense as tangible as it is visible. Passion swirls "+
      "in eddies of flame, blue entwining with gold, red teasing "+
      "orange to greater heights. Everywhere is black stone, as "+
      "warm and welcoming as Jazur's womb. Unpolished, the stone "+
      "seems to absorb light, casting everything into shadows "+
      "that obscure your perception of space. Underfoot is a swirl "+
      "of colour, myriad gemstones melded together as though "+
      "stirred by a god's hand. In the center of the room a "+
      "blue-black orb spins above a simple stone slab.\n");

    add_item(({"darkness", "presence" }),
      "You feel something in the darkness, some great "+
      "presence that pulses in concert with the flames.\n");
    add_item(({"Flame", "flame", "flames", "fire"}),
      "The flames rush upward from their chasm in a "+
      "flurry of activity that is oddly, eerily silent.\n");
    add_item(({"stone", "black stone"}),
      "Everywhere the stone is so dark and unreflective that "+
      "it is difficult to tell where the walls end and the floor "+
      "and ceiling begin.\n");
    add_item(({"swirl", "swirls", "swirl of colour", "gemstones",
	"mosaic"}),
      "Gemstones of all sizes and colours have been strewn across "+
      "the floor and then by some force unimaginable to you, they "+
      "have been melded in with the black stone. It looks like "+
      "both floor and gems were heated and then stirred, forming "+
      "swirls of colour and shadow.\n");
    add_item(({"shadows", "shadow"}),
      "The shadows are alive, you feel certain.  When you try to "+
      "focus on them, they glide, formless, just to the edge of "+
      "your sight.\n");
    add_item(({"metal", "metals", "dark metals", "veins", "ribbon"}),
      "Veins of metal are shot all through the stone edging "+
      "the chasm, even to the point of coating the edge in a "+
      "glittering, multi-coloured ribbon of gold, platinum, silver, "+
      "copper, iron, and other ores and alloys unknown to you.\n");
    // same descs as in guild.c for consistency
    add_item(({"crack", "chasm","abyss"}),"The crack opens wide,"+
      "running along the western wall. The edge is rimmed with "+
      "layer upon layer of dark metals. The chasm seems to "+
      "go down forever, vanishing into an indistinct reddish "+
      "haze far below.\n");

    add_cmd_item(({"crack","chasm","abyss","the crack","the chasm",
	"the abyss","into the crack", "into the chasm","into the abyss"}),
      ({"jump","leap"}),
      "That would be suicide, something Jazur does not require of "+
      "at this time.\n");
    add_cmd_item(({"crack","chasm","abyss","the crack","the chasm",
	"the abyss","into the crack", "into the chasm","into the abyss"}),
      ({"enter","climb"}),
      "The sides are too sheer to climb down.\n");

    set_tell_time(100);
    add_tell("Voices murmur, ebbing and flowing, barely audible.\n");
    add_tell("You are uplifted by an eddy of Passion.\n");
    add_tell("There is a puff of air, as though something large "+
      "just passed you.\n");
    add_tell("You feel the touch of warm fingers upon your nape, "+
      "and the echo of a kiss upon your cheek.\n");
    add_tell("   Be welcome here, Tornu.\n");
    add_tell("   Embraced by the Flame, tested and proven worthy, "+
      "you are the pride of Jazur.\n");
    add_tell("   The meeting of impulse and intellect creates the "+
      "most extraordinary action, my child.\n");
    add_tell("   All that you need lies within you.\n");
    add_tell("   This moment is a gift. Honour me by fully living it.\n");
    add_tell("The room is pervaded with a sense of sacredness.\n");
    add_tell("Your awareness floats and you find yourself "+
      "momentarily aswirl with the sparks and shadows in the orb.\n");
    add_tell("Something sparks and flares within the spinning orb.\n");
    add_tell("The floor underfoot seems to flow and twist, assuming "+
      "a new configuration of swirled gemstones.\n");
    add_tell("A swirl of something extends from the orb, reaching "+
      "toward you.\nA thousand different voices wash through "+
      "your consciousness, all unified, all echoing a wordless "+
      "message of pride affection duty longing zeal ecstacy "+
      "loyalty perseverance fervor righteousness fealty passion.\n");
    add_tell("...cintaron.....intaron....taron......aron.....\n");
    add_tell("The fire flickers, sending up a shower of golden-blue "+
      "flames.\n");
    add_tell("The flickering of the flame catches upon the metals, "+
      "sending shards of light swirling about the room.\n");
    add_tell("If it were not that the room was so dark and the light "+
      "so dim, you would swear that you saw a shadow race by.\n");

    add_object(COM + "gods/altar/jaz_altar", 1, &->reset_altar());

    enable_reset(200);
    reset_room();
}

//Leave the room by entering the flame.
public int
enter(string str)
{
    NF("Enter what?\n");
    if (!strlen(str) || STATE < 0)
	return 0;

    str = lower_case(str);
    if (!parse_command(str, ({}), "[the] 'flame' / 'fire'"))
	return 0;

    say(QCTNAME(TP) + " approaches the fire.\n");

    if (ENEMY(TP))
    {
	write("The fire engulfs and burns you!\n");
	say("The dark fire engulfs and burns " + QTNAME(TP) + ".\n");
	TP->heal_hp(-500);
	return 1;
    }

    if (!IS_MEMBER(TP))
    {
	write("The flame resists you.\n");
	say("The flame resists " + QTNAME(TP) + ".\n");
	return 1;
    }

    write("You enter the Flame, and immediately the shadows are "+
	"drawn about you, brushing against you like ethereal "+
	"fingers.\n");
    say(QCTNAME(TP) + " vanishes into the Fire.\n");

    TP->move_living("M", ROOM + "guild", 1, 0);
    tell_room(ENV(TP), "There is a rush of air, and from the swirling " +
	"flames "+ QTNAME(TP) + " emerges untouched, glowing with "+
	"serenity and confidence.\n", TP);

    return 1;
}

private void
do_summoning(void)
{
    summon = 1;

    tell_room(TO, "The room is shaken by a rumbling vibration.\n");
    tell_room(TO, "The point of light is enveloped by a shadow as it "+
	"spins away from the orb.\n");
    tell_room(TO, "The shadow coalesces into humanoid form.\n");

    if (!present(npc))
    {
	npc = clone_object(NPC + "alcintaron");
	npc->move_living("M", TO);
	npc->command("respect all");
    }
}

//Testing for use of a specific Word of Power
public int
say(string str)
{
    if (summon)
	return 0;

    if (present(npc))
	return 0;

    if (wildmatch("*lcintaron*", str))
    {
	TP->add_prop("_i_summoned_alcintaron", 1);
	set_alarm(5.0, 0.0, do_summoning);
	set_alarm(1.0, 0.0, &tell_room(TO,
		"A point of light within the orb pulses.\n"));
    }

    return 0;
}

public void
init(void)
{
    ::init();

    add_action(enter, "enter");
    add_action(say,   "'", 2);
    add_action(say,   "say");
    add_action(say,   "asay");
    add_action(say,   "shout");
    add_action(say,   "ashout");
    add_action(say,   "us");
    add_action(say,   "usay");
    add_action(say,   "usto");
}

/* Start the room tells as soon as someone enters the room */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (query_interactive(ob))
    {
	start_room_tells();
	write("You are drawn eastward, "+
	    "circling a blue-black orb spinning above a simple "+
	    "stone slab until it is positioned between you and "+
	    "the chasm from whence you came.\n");
    }
}
