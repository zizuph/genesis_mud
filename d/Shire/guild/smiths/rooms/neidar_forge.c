/*
 * Forge for the Neidar Clanhall by Lucius.
 *
 * based on: shadow_forge.c by Lilith.
 */
#pragma strict_types;

inherit "/d/Shire/guild/smiths/rooms/base_forge_room";
inherit "/d/Shire/std/room/room_tell";

#include <macros.h>
#include <language.h>
#include <stdproperties.h>


private int marks, figures;

public void
create_forge_room(void)
{
    set_short("inside a blasted boulder");
    set_long("You are inside a boulder which has been roughly "+
	"hewn and hollowed out. Converted into a smithy by "+
	"some patient hill dwarves out of Iron Delving, it "+
	"features an exit to the outside via a jagged split "+
	"on the east surface, wide enough even for a dwarf "+
	"from the Neidar Clan to fit through. Next to it are "+
        "some chalk marks. The top bears "+
	"a roughly circular opening with many a gash and "+
	"chisel scrape in evidence of its creation. A great "+
	"forge, tools and bellows lies along the west and "+
	"north walls, the soot covering them proof of their "+
	"ready usage. Lined along the southern interior surface "+
	"are several barrels and what looks like a sign.\n");

    /* Standard forge room has most items already. */
    remove_item(({"window","windows"}));

    add_cmd_item(({"board","chalkboard"}), "read", "@@read_sign@@");
    add_item(({"sign","board","chalk board","chalkboard"}),
       "It is more of a chalk board really. Etched "+
       "over the black backing is some fat, white lettering, "+
       "which reads at the top: Smiths Forge of Iron Delving\n");

    add_item(({"marks", "chalk amrks"}), "Near the jagged split "+
	"leading to the exit outside are some leftover chalk "+
	"marks. You think you spotted a piece by the sign.\n");

    add_item(({"chalk"}), "This is a piece of chalk, with it "+
	"you may 'draw'.\nYou can also 'count' and 'clean' "+
	"afterwards.\n");

    add_room_tell("A breeze blows through, stirring soot and smoke.");
    add_room_tell("A blazing coal pops, sending ash skittering "+
	"with a vibrant orange glow.");

    /* Same exit, two names. */
    add_exit("/d/Ansalon/estwilde/iron_delving/forge",
	"out", "@@check_forging@@", 2, 1);
    add_exit("/d/Ansalon/estwilde/iron_delving/forge",
	"outside", "@@check_forging@@", 2, 1);
}

string read_sign()
{
return "In fat, white letters, the chalkboard reads:\n\n" +
"      +--------------------------------------------------------------+\n"+
"      |  o                                                        o  |\n"+
"      |    o                                                    o    |\n"+
"      |  o                                                        o  |\n"+
"      |                  Smiths Forge of Iron Delving                |\n"+
"      |                   --=======[ .^^. ]=======--                 |\n"+
"      |                                                              |\n"+
"      |   Forging weapons and armours successfully requires great    |\n"+
"      |   skill. It is also tiring work and takes much out of the    |\n"+
"      |   strongest person. Remember this as you will become quite   |\n"+
"      |   thirsty, hungry, and tired.                                |\n"+
"      |                                                              |\n"+
"      |   Skilled smiths may forge the following items.              |\n"+
"      |                                                              |\n"+
"      |     General Equipment                                        |\n"+
"      |   =========================================================  |\n"+
"      |     - Horsehoes (set of four)                                |\n"+
"      |     - Megaphone                                              |\n"+
"      |                                                              |\n"+
"      |     Armours                  Weapons                         |\n"+
"      |   =========================================================  |\n"+
"      |     - Boots                  - Bastard Sword                 |\n"+
"      |     - Bracers                - Battle Axe                    |\n"+
"      |     - Platemail Bracers      - Claymore                      |\n"+
"      |     - Scalemail Bracers      - Dirk                          |\n"+
"      |     - Breastplate            - Halberd                       |\n"+
"      |     - Chainmail              - Iron Waraxe                   |\n"+
"      |     - Greaves                - Knife                         |\n"+
"      |     - Platemail Greaves      - Longsword                     |\n"+
"      |     - Scalemail Greaves      - Quarterstaff                  |\n"+
"      |     - Helm                   - Short Axe                     |\n"+
"      |     - Great Helm             - Shortsword                    |\n"+
"      |     - Plate Helm             - Spiked Club                   |\n"+
"      |     - Platemail              - Stiletto                      |\n"+
"      |     - Ribbed Platemail       - Warhammer                     |\n"+
"      |     - Ringmail                                               |\n"+
"      |     - Shield                                                 |\n"+
"      |     - Grand Tower Shield                                     |\n"+
"      |                                                              |\n"+
"      |   Visitors may assist Blacksmiths by pumping the bellows.    |\n"+
"      |   This is done by 'smpump bellow'.                           |\n"+
"      |                                                              |\n"+
"      |  o                                                        o  |\n"+
"      |    o                                                    o    |\n"+
"      |  o                                                        o  |\n"+
"      +--------------------------------------------------------------+\n";
}

public int
draw(string str)
{
    if (!strlen(str))
	return notify_fail("Draw what?\n");

    switch(str)
    {
    case "marks":
    case "sticks":
    case "figures":
    case "stick figures":
        write("Try drawing them one at a time.\n");
	break;

    case "mark":
    case "stick":
	string tmp = one_of_list(({
	    "wobbly", "wavery", "straight", "crooked", "slashed",
	}));
	write("You draw a "+ tmp +" "+ str +" upon the wall.\n");
	say(QCTNAME(this_player()) +" draws a "+ tmp +
	    " "+ str +" upon the wall.\n");
	marks++;
	break;

    case "figure":
    case "stick figure":
	write("You draw a stick figure on the wall, it looks "+
	    "appropriately dwarvish.\n");
	say(QCTNAME(this_player()) +" draws a stick figure on the wall, "+
	    "it looks a bit roly-poly, like a dwarf.\n");
	figures++;
	break;

    default:
	notify_fail("Try drawing marks or sticks instead.\n");
	return 0;
    }
    return 1;
}

public int
count(string str)
{
    if (!strlen(str))
	return notify_fail("Count what?\n");

    switch(str)
    {
    case "mark":
    case "stick":
	if (!marks)
	{
	    write("There aren't any to count.\n");
	    break;
	}
	write("You count one of them. If you want more, "+
	    "try counting \""+ str +"s\" instead.\n");
	break;

    case "figure":
    case "stick figure":
	if (!figures)
	{
	    write("There aren't any to count.\n");
	    break;
	}
	write("You count one of them. If you want more, "+
	    "try counting \""+ str +"s\" instead.\n");
	break;

    case "marks":
    case "sticks":
	if (!marks)
	{
	    write("There aren't any to count.\n");
	    break;
	}
	write("You count "+ LANG_NUM2WORD(marks) +" "+
	    str +" on the wall.\n");
	break;

    case "figures":
    case "stick figures":
	if (!figures)
	{
	    write("There aren't any to count.\n");
	    break;
	}
	write("You count "+ LANG_NUM2WORD(figures) +" "+
	    str +" on the wall.\n");
	break;

    default:
	notify_fail("Try counting marks or sticks instead.\n");
	return 0;
    }
    return 1;
}

public int
clean(string str)
{
    if (!strlen(str))
	return notify_fail("Clean what?\n");

    switch(str)
    {
    case "mark":
    case "stick":
	if (!marks)
	{
	    write("There aren't any to clean.\n");
	    break;
	}
	marks--;
	write("You erase one of them. If you want more, "+
	    "try cleaning \""+ str +"s\" instead.\n");
	say(QCTNAME(this_player()) +" erases a chalk "+
	    str +" from the wall.\n");
	break;

    case "figure":
    case "stick figure":
	if (!figures)
	{
	    write("There aren't any to count.\n");
	    break;
	}
	figures--;
	write("You erase one of them. If you want more, "+
	    "try cleaning \""+ str +"s\" instead.\n");
	say(QCTNAME(this_player()) +" erases a chalk "+
	    str +" from the wall.\n");
	break;

    case "marks":
    case "sticks":
	if (!marks)
	{
	    write("There aren't any to clean.\n");
	    break;
	}
	marks = 0;
	write("You wipe away all the chalk "+ str +
	    " from the wall.\n");
	say(QCTNAME(this_player()) +" erases all the chalk "+
	    str +" from the wall.\n");
	break;

    case "figures":
    case "stick figures":
	if (!figures)
	{
	    write("There aren't any to count.\n");
	    break;
	}
	figures = 0;
	write("You wipe away all the chalk "+ str +
	    " from the wall.\n");
	say(QCTNAME(this_player()) +" erases all the chalk "+
	    str +" from the wall.\n");
	break;

    default:
	notify_fail("Try cleaning marks or sticks instead.\n");
	return 0;
    }
    return 1;
}

public void
init(void)
{
    ::init();

    add_action(draw, "draw");
    add_action(count, "count");
    add_action(clean, "clean");
}
