// Ziggurat perfumery (ZIG_RL3 + "perfumery.c")
// creator(s):   Lucius 2006
// last update:
// purpose:      Ziggurat shop where players can buy various fancy perfumes.
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"

inherit ZIG_ROOM;

private static int alarm;
private static object keeper;


private void
reset_npc(object npc)
{
    keeper = npc;
}

public void
zig_room(void)
{
    set_short("scentiments");
    set_long("A multitude of scents caress your olfactory senses within "+
	"this modest sized shop. They stem from everywhere, but most "+
	"prominently from behind the ashenwood counter, where you can "+
	"see various open boxes containing sundry bottles and vials. "+
	"Also behind the counter, against an alabaster, stucco wall, is "+
	"an alabaster worktable with a pennon overhanging it. Spaced at "+
	"regular intervals along the other walls are bronze sconces "+
	"capped with flame-shaped blue-glass domes that lend a subdued "+
	"blue-ish tint to everything you see.\n");

    add_item(({"walls","stucco","stucco walls","alabaster walls",
	"wall","stucco wall","alabaster wall"}),
	"The walls are plastered over with an alabaster stucco mixture "+
	"that lends a textured dimension of varied detail to them.\n");
    add_item(({"counter","ashenwood counter"}),
	"The counter is a grey-ish white with a blue tint from the "+
	"sconces. Inset into the front and top of the counter are glass "+
	"panes through which you see more glass shelves holding an array "+
	"vials with coloured liquids and bottles of various designs.\n");
    add_item(({"panes","glass panes","shelves","glass shelves"}),
	"The glass panes inset into the ashenwood counter reveal glass "+
	"shelves that hold an array of vials and bottles.\n");
    add_item(({"vials","liquids","coloured liquids","bottles"}),
	"The vials holds variously coloured liquids whereas the bottles "+
	"are of an assortment of different sizes and shapes.\n");
    add_item(({"table","worktable","ashenwood table","ashenwood worktable"}),
	"From what you can see of the ashenwood worktable, its surface "+
	"is worn and scratched though still appears well maintained. Set "+
	"into one end of the table is a metal sink. Hanging over the table "+
	"is a white, embroidered pennon.\n");
    add_item(({"pennon","white pennon","embroidered pennon"}),
	"The white pennon hangs upon a brass rod above the ashenwood "+
	"worktable. Embroidered into the pennon with black thread is the "+
	"image of a vertical wand with twin snakes twining up its length.\n");
    add_item(({"sink","metal sink"}),
	"The metal sink embedded into the worktable is polished and seems "+
	"to have the extravagance of running water if the rounded taps are "+
	"any indication.\n");
    add_item(({"taps","rounded taps"}),
	"They are rounded metal knobs and a curved spigot on the sink "+
	"from where you imagine running water would come.\n");
    add_item(({"boxes","open boxes"}),
	"Inside the open boxes you see many vials, mostly empty, and "+
	"the tops of various kinds of bottles.\n");
    add_item(({"sconces","bronze sconces","sconce","bronze sconce"}),
	"The bronzed sconces are spaced regularly along the alabaster "+
	"walls and are capped with blue glass molded into various "+
	"flame-like shapes.\n");
    add_item(({"cap","caps","blue glass","flame-shaped glass",
	"flame-like caps"}),
	"The flame-shaped glass caps upon the bronze sconces visit "+
	"a subdued blue-ish light on everything in the shop.\n");
    add_item(({"ceiling","shadows","flame-like shadows"}),
	"The ceiling is plastered over in the same alabaster stucco "+
	"as the walls. The sinuous movements of flame-like shadows "+
	"given off by the sconces dance upon its surface.\n");
    add_item(({"floor","ground","tile","tiles","white tiles"}),
	"The floor is covered in plain white tiles that also carry "+
	"a ghostly blue hue from the blue glass of the sconces.\n");

    set_tell_time(240);
    add_tell("Flame-shaped shadows flicker along the alabaster ceiling.\n");

    add_exit("room5", "north", 0);

    add_npc(ZIG_MON + "cheynal", 1, reset_npc);
}

private void
react_greet(object who)
{
    alarm = 0;

    if (!present(who, TO))
	return;

    keeper->command("say Welcome to Scentiments!");
}

public void
init(void)
{
    ::init();

    if (!alarm)
	alarm = set_alarm(2.0, 0.0, &react_greet(TP));
}

public void
hook_smelled(string what)
{
    switch(what)
    {
    case "counter":
	write("The multitude of scents is much more prevalent near "+
	    "the counter.\n");
	break;
    default:
	write("The room is filled with a multitude of scents.\n");
	break;
    }
}
