inherit "/d/Kalad/room_std";
#include "/d/Kalad/defs.h"
#include "/sys/stdproperties.h"
#include "/sys/macros.h"

void create_room()
{
    ::create_room();
    seteuid(getuid(TO));
    set_short("Visitor's Center of Kalad");
    set_long(BS(
"This room is dark and smoky, and the ceiling is low and stained black with "+
"soot. The walls are made of dark hardwood, and the floor of finely cut "+
"flagstones. A small black door lies to the west, a large iron double door "+
"to the north, and a rather mundane wooden door to the east. The south "+
"bears no exit.\n")+BS(
"There is a grandfather clock ticking quietly in this room, its hushed "+
"voice calling out to whoever is present. A long dining table bears the "+
"remanents of an unfinished feast. A button and plaque lie in tandem upon "+
"the southern wall, and a tapestry is proudly displayed on the eastern "+
"face.\n"));
    set_time_desc(BS(
"The murmur of crowds comes, muffled, from behind the northern double "+
"doors.\n"),BS(
"All is silent save for the ticking of the clock.\n"));
    add_exit("/d/Kalad/common/caravan/shop/wayfar_guild","north","@@block");
    add_exit("/d/Kalad/workroom","east",0);
    add_exit("/d/Genesis/wiz/dom_b1","west",0);
    add_prop(ROOM_I_INSIDE,1);
    hear_bell = 1;   /* faint: inside the visitor's center  */

    add_item(({"door","doors"}),
"Do you mean the black door, the iron doors, or the wooden door?\n");
    add_item("black door",BS(
"The small black door has an aura of magic about it. There is an "+
"engraving of a tower that extends above and below the earth upon its "+
"surface.\n"));
    add_item(({"iron doors","double doors","iron double doors"}),BS(
"The iron doors appear very heavy, but well kept and operable. Their "+
"hinges have been recently greased. The words 'City of Kabal' are "+
"engraved across the pair.\n"));
    add_item(({"wooden door","mundane door","wooden mundane door"}),BS(
"The wooden door is quite normal. Iron shod, it bears no markings save "+
"a tiny insignia that resembles a key.\n"));
    add_item(({"table","wooden table"}),BS(
"The table is covered with half-eaten delectable goodies: roasted beast, "+
"preserved yams, rich red wine. The aroma fights with the smoky air, and "+
"almost loses.. the lingering scent of a lord's meal stirs your stomach.\n"));
    add_item("button",BS(
"The button is small and grey, made of the same stone as the floor.\n"));
    add_cmd_item("button",({"press","push"}),"@@give_guide");
    add_item("plaque",BS(
"The plaque is brightly shining. It is made from polished brass.\n"));
    add_cmd_item("plaque","read",BS(
"The plaque reads:\n")+BS(
"Press the button upon the wall for a wizard's guidebook to the fair "+
"land of Kalad.\n"));
    add_item("tapestry",BS(
"The tapestry takes up most of the free wall. Marked by heavy reds and "+
"patches of deepest black, white script has been stitched into the "+
"fabric.\n"));
    add_cmd_item("tapestry","read",BS(
"The tapestry reads:\n")+BS(
"Kalad is the domain of the Antihero, the evil adventurer. The Land is "+
"amoral and gothic, and its quests focus upon the unresolvable contents "+
"of the human soul. Politics and economics are the keys to power here, "+
"not dragonslaying or meddling in the affairs of the High Council. The "+
"City of Kabal, beyond the great northern doors, is a brilliant example "+
"of how our Land forces the would-be Martyr to examine her own "+
"judgement.\n"));
    add_item(({"clock","grandfather clock"}),"@@clock_desc");

    clone_object("/d/Kalad/common/visitor_board")->move(TO);
}

give_guide()
{
    clone_object("/d/Kalad/open/maps/guide")->move(TP);
    return "A Kalad Visitor's Guidebook appears in your hands.\n";
}

block()
{
    return 1;
}

clock_desc()
{
    int hour;
    hour = HOUR;
    return BS(
"This ornate grandfather clock is make of solid redwood from the "+
"mighty Hespyre range that pins Kabal against the tumulous Kalad Sea. "+
"It stands near the eastern door, keeping time and ticking against "+
"the darkness and the smoke. You watch its hypnotic pendulum swinging "+
"with every second. The small hand is resting near the "+hour+" on "+
"the dial.\n");
}
