/**********************************************************************
 * - bonesmith.c                                                    - *
 * - Workshop of the Tyr weapon/bonesmith.                          - *
 * - Updated by Damaris@Genesis 10/2005                             - *
 **********************************************************************/
#pragma strict_types

inherit "/std/room";
#include "tentavvar.h"
inherit "/d/Cirath/std/Cirath_magic_room_std";
#include "/d/Cirath/common/mobber.h"


int do_read(string str);

void
reset_room()
{
	bring_room_mob("tentavvar", "/d/Cirath/tyr/bonesmith/tentavvar", 1);
}

void create_room()
{
	::create_room();
	set_short("smithy");
	set_long("The air is filled with so many particles that "+
	"breathing is nigh impossible. A hundred forgotten fragments "+
	"of weapons litter the floor, competing with the forge, anvil, "+
	"and racks of tools. This can be only one place: The workshop "+
	"of Tyr's resident bonesmith Tentavvar. A large display case "+
	"hangs on the wall. Cleaner air lies north on the street and "+
	"west in the weapon merchant's.\nA small sign of sorts hangs "+
	"on the back wall of the shop.\n");
	add_item(({"smithy", "area", "room"}), query_long);
	add_item(({"case", "display case", "display"}),
	"This is a large display case, in it you can see several "+
	"well polished obsidian samples. There are pieces of the "+
	"following types: brown, mahogany, lizard-skin, flame-red, "+
	"jet-black, deep-green, midnight-lace, snowflake, rainbow, "+
	"gold-sheen, and silver-sheen. You can examine each stone to "+
	"find out more details about it.\nUse \"examine <type> stone\" "+
	"to see each stone.\n");
	add_item(({"sign"}),
	"Not much more than a piece of scrap wood with what look like "+
	"words carved into it. You can try reading it if you dare.\n");
	add_item(({"air", "particles"}),
	"Thick and filled with a heavy dust, you have a hard time "+
	"breathing the air. Slivers of light leaking through cracks are "+
	"brought to life as they pass through the haze, give an almost "+
	"cathedral feeling to the shop.\n");
	add_item(({"floor", "ground"}),
	"The worn stone floor is covered with dust and fragments of bone "+
	"and obsidian.\n");
	add_item(({"fragments", "debris"}),
	"Various pieces of broken weapons, none is much bigger than a "+
	"dwarf's thumb.\n");
	add_item(({"forge"}),
	"A large smoldering pit of coals and ash, it breathes a fire so "+
	"hot it would blister the skin of most men.\n");
	add_item(({"anvil"}),
	"This huge chunk of iron must be worth a fortune! It looks well "+
	"used and sags in the middle like an old mule's back. The horn "+
	"is so worn it's not much more than a dull lump on the front.\n");
	add_item(({"rack", "racks"}),
	"Lining the back and side walls of the shop, these racks hold "+
	"various materials such as weapon handles, blocks of unfinished "+
	"obsidian, old and broken armours and other items of use to a "+
	"blacksmith.\n");
	add_item(({"tool", "tools"}),
	"A small assortment of hammers with specialized heads, chisels, "+
	"and carving tools. They look old, but well cared for.\n");
	add_item(({"brown stone"}),
	"This stone has a rich rust-brown color due to the high amount "+
	"of iron oxides in the glass. More dense and rougher than "+
	"varieties such as jet-black or midnight lace it cannot be "+
	"cleaved as cleanly either. This stone is also harder and more "+
	"durable than the more pure types.\n");
	add_item(({"mahogany stone"}),
	"This stone is a dark red-brown, with thin streaks of black. "+
	"The coloring is the result of iron oxide impurities in the "+
	"stone and like the brown variety is harder and heavier than "+
	"most other varieties of obsidian.\n");
	add_item(({"lizard-skin stone"}),
	"An even patchwork of light and darker browns marks this stone. "+
	"The regular pattern of differing colors gives the stone the "+
	"look of a lizard's back. This type of obsidian has somewhat "+
	"less impurities than some of the more dark brown varieties "+
	"and is therefore a little bit lighter and softer.\n");
	add_item(({"flame-red stone"}),
	"With a beautiful orange-red color, this obsidian has an evenly "+
	"distributed mix of impurities. While not as soft as some of the "+
	"more pure varieties this type of obsidian can still be "+
	"fractured to form an edge sharper than a razor.\n");
	add_item(({"jet-black stone"}),
	"This glass is deep black in color. Considered to be one of the "+
	"purest types of obsidian, the dark black color comes from the "+
	"trace amounts of magnetite mixed in with the silica. Cooling "+
	"slowly for thousands of years below the surface gives this "+
	"stone its unique perfection for weapon making.\n");
	add_item(({"deep-green stone"}),
	"This stone has a dark and deep green color. Very well formed "+
	"glass, this stone has some trace amounts of magnetite and "+
	"copper in it resulting in the rich color. It has about the "+
	"same hardness and working qualities as the jet-black variety.\n");
	add_item(({"midnight-lace stone"}),
	"This stone looks to be made up of black obsidian, mixed "+
	"together with streaks of very opaque glass. The streaks "+
	"were stretched thin and gently turned by the slow flow of "+
	"magma that formed the obsidian, creating a beautiful lace-like "+
	"pattern. Not quite as easy to work with as jet-black obsidian, "+
	"this stone can still create a very lethal edge.\n");
	add_item(({"snowflake stone"}),
	"This stone is mostly black, but with larger specks of white "+
	"scattered across its surface. The white \"snowflakes\" are "+
	"really quartz crystals that have devitrified from the original "+
	"obsidian over millions of years under tremendous pressure. "+
	"While still quite good to work with, these quartz crystals "+
	"can affect the stone smith's ability to get the perfect break "+
	"required for a sharp edge and weaken the glass slightly.\n");
	add_item(({"rainbow stone"}),
	"This obsidian flashes with all the colors of the rainbow as it "+
	"catches light. Trace amounts of feldspar in the glass are "+
	"responsible for the cavalcade of colors and also for the "+
	"stone's slightly lighter weight, but it also makes it more "+
	"difficult for the stone to hold an edge on the blade.\n");
	add_item(({"gold-sheen stone"}),
	"This stone has a light golden shine to its surface. The "+
	"obsidian, well mixed with small crystals of feldspar also has "+
	"millions of tiny air bubbles mixed in which are responsible for "+
	"the sheen. They also make the stone a little lighter and less "+
	"durable than some varieties.\n");
	add_item(({"silver-sheen stone"}),
	"The muted gray reflection off this stone almost makes it look "+
	"like a piece of metal. A mix of various trace impurities and "+
	"millions of tiny air pockets are responsible for this "+
	"appearance. Much lighter than most varieties of obsidian, it "+
	"can be fractured to make a very sharp and light axe head, but "+
	"is quite likely to break with extended use.\n");
	
	reset_room();
	
	add_exit(TYR_CARAVAN+"rd_cw_04.c", "north", 0, 1);
	add_exit(TYR_CARAVAN+"weapmrch.c", "west", 0, 1);

}

int
do_read(string str)
{
	if(str == "sign")
	{
		if(TP->query_guild_name_occ() == "Gladiator guild" && !random(9))
	{
		tell_room(TO, "A passing templar notices "+
		"" + QTNAME(TP) + " staring at the sign on the back "+
		"wall and quickly steps into the shop.\n", TP);
		write("A passing templar notices you staring at the "+
		"sign and quickly steps into the shop.\n");
		tell_room(TO, "The templar grabs "+
		"" + TP->query_objective() + " by the shoulder, spins "+
		"" + TP->query_objective() + " around and brutally "+
		"punches " + TP->query_objective() + " in the "+
		"stomach.\n", TP);
		write("The templar grabs your shoulder spinning you "+
		"around, and brutally punches you in the stomach.\n");
		TP->command("puke");
		tell_room(TO,"The templar laughs.\n");
		tell_room(TO,"The templar says: Reading is not allowed "+
		"in Athas slave!\n");
		tell_room(TO,"The templar says: Don't forget it!\n");
		tell_room(TO,"The templar leaves north.\n");
		write("Just before your were blinded by surprise and "+
		"pain you saw the words \"help smith\".\n");
	}
	else
	{
		write("\n"+
   "            o___________________________________________________o\n"+
   "            |                                                   |\n"+
   "            |                                                   |\n"+
   "            |  The Shop of Tentavvar, Master Blacksmith of Tyr  |\n"+
   "            |                                                   |\n"+
   "            |      Services Performed:                          |\n"+
   "            |                                                   |\n"+
   "            |        Weapons Sharpened and Waxed                |\n"+
   "            |        Armours Mended                             |\n"+
   "            |        Custom Manufacture of weapons and armours  |\n"+
   "            |                                                   |\n"+
   "            |                                                   |\n"+
   "            |  For additional information: 'help smith'         |\n"+
   "            |                                                   |\n"+
   "            |___________________________________________________|\n"+
   "            o                                                   o\n");
         }
         return 1;
         
         }
         return 0;
}

void 
init()
{
	::init();
	add_action(do_read, "read");
}