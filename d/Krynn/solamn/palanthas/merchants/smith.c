/* 
 * The smithy in the Arms district of the merchants quarter
 * of Palanthas.  Fixes weapons and armours.  Forges
 * weapons.
 *
 * Just need a place for people to get shields in the city.
 *
 * add_ask idea for master smith, mithril, build houses in some lands, etc.
 * shrine area?  meditates as step 1 of forging?
 *
 * Mortis 01.2006
 *
 * Updated by Carnak at: 2016-12-14
 * Added staves and quarterstaves to the list of weapons. 
 *
 */

#include "../local.h"
#include CLOCKH
#include <macros.h>
#include <living_desc.h>
#include <cmdparse.h>
#include <state_desc.h>
#include <composite.h>
#include <filter_funs.h>
#include <money.h>
#include <files.h>
#include <formulas.h>

inherit MERCH_ROOMBASE;
inherit "/lib/trade";

#define VIEWSOUTH				(MERCH + "m11")
#define PRETENDED				"_obj_has_already_been_tended"
#define NUM	sizeof(MONEY_TYPES)

object ken;

mapping name_arm_to_info = (["dagger":"With a tight, leather bound handle and "
	+ "counter balanced pommel, this is aclassic styled dagger.", 
	"flatknife":"Single edged like a knife but with a thinner blade, the "
	+ "flatknife has a slim profile such that its hilt, handle, and pommel "
	+ "are hardly any thicker than its blade allowing it to lay almost "
	+ "perfectly flat against surfaces.",
	"knife":"A classically styled knife with a single edge and tight, "
	+ "leather bound handle, its small hilt is more to keep it in place "
	+ "in a sheath than catch blows.  It is utilitous and functional.", 
	"kukri":"The kukri is a large, reverse curved knife used for hacking, "
	+ "slicing, and in skilled hands throwing.  It has a forward curving "
	+ "blade.",
	"machete":"The machete is almost large enough to be a short sword and "
	+ "is commonly used for hacking through thick underbrush, although it "
	+ "is fairly intimidating as well.", 
	"shiv":"Simple but effective, this shiv has no hilt, just tight leather "
	+ "bound about its tang.  The blade is sharpened to a point.", 
	"stiletto":"The stiletto is a thin length of razor coming to a needle "
	+ "point at its end.  It has no hilt and a thin, arrasene wrapped "
	+ "tang for a handle best held in the fingers or thrown.",
	"cutlass":"Extending from a protective steel basket "
	+ "hilt, the blade of this cutlass is wide with a slight curve for "
	+ "durability and ease in slashing.", 
	"rapier":"Smaller and faster than a longsword, this vicious rapier is "
	+ "curved for swift slashes and has a thin, silk bound handle for "
	+ "maneuverability.",
	"sabre":"With a thin, curved blade and recurved, tight bound, leather "
	+ "gripped handle, these sabres are favoured by horsemen for their "
	+ "effective slashes.",
	"scimitar":"This scimitar has a silk-wrapped handle almost long enough "
	+ "for a second hand with a sharp edged blade that curves back wickedly "
	+ "almost towards its wielder.  The blade grows wider as it moves from "
	+ "its hilt to its tip.",  
	"sword":"With a sharp edged blade, crossguard hilt, tight, leather "
	+ "bound handle, and counter balanced pommel, this is a classic styled "
	+ "sword.",
	"bardiche":"The bardiche bears a sword-like blade "
	+ "sealed and leather bound atop a tall shaft of smooth oak.",
	"halberd":"Sealed and leather bound atop a tall shaft of smooth oak is "
	+ "the halberd's crescent blade for slashing from which a long spike "
	+ "continues for stabbing like a spear.",
	"partisan":"A long, double edged blade like a short sword protrudes from "
	+ "the partisan's tall shaft of smooth oak.",
	"pike":"The four bladed war tip atop the pike's tall shaft of smooth oak ",
	"spear":"There is a long piercing blade atop the spear's tall shaft of "
	+ "smooth oak.",
	"club":"With a tight, leather bound handle and "
	+ "thick oak shaft, this classic club has been fitted on its "
	+ "end with a thick band.", 
	"flail":"Three large, steel links chain a foot long, two inch thick "
	+ "rod of steel to the smooth, oak handle of this flail allowing it "
	+ "to wrap around shields to deliver blows.",
	"hammer":"With a smooth, oak handle topped with a curving head, this "
	+ "is a classic hammer.",
	"mace":"With a tight, leather wrapped steel handle and stud covered "
	+ "pounding head, this is a classic mace.",
	"maul":"The maul has a smooth, oak handle and enormous wooden mallet "
	+ "head bound in steel plates on its hammering surfaces.",
	"morning-star":"A length of chain connects the morning-star's leather "
	+ "bound, steel handle to a four inch diameter ball.",
	"pick":"The pick has a smooth, oak handle upon which is seated a long, "
	+ "curved pick angled to deliver piercing blows.",
	"war-chain":"With a short, leather bound handle of steel, the war-chain "
	+ "is four feet of thick links useful for wrapping around shields, "
	+ "snagging weapons and limbs, and pulling foes off their feet.  In the "
	+ "hands of a dextrous warrior, they are highly versatile.",
	"warhammer":"With a short, leather bound handle of steel this warhammer "
	+ "has a heavy, block shaped head.",
	"axe":"A curved half-circle blade is sealed and "
	+ "bound to a haft of smooth oak ending in a steel pommel.", 
	"battleaxe":"This battleaxe has a smooth, solid steel haft and pommel "
	+ "topped with a razor-edged, arcing crescent head.",
	"cleaver":"Shorter than a normal axe, this cleaver's handle is two "
	+ "lengths of smooth oak riveted to the cleaver's tang.  The blade "
	+ "itself is a slightly curved, thick backed, hacking edge traditinally "
	+ "used by butchers to hack through meet and bone.",
	"handaxe":"With its modern forging techniques, this axe is smaller and "
	+ "lighter than its predecessors and can be easily slipped within a "
	+ "belt.  Its smooth, oak handle curves back to its angled, chopping "
	+ "head giving it a deadly slashing arc with minimal size.",
    "staff":"With a long thick oak shaft, this classic staff has been " +
    "fitted on its ends with thick high quality steel bands.",
    "quarterstaff":"With a long thick oak shaft, this quarterstaff has been " +
    "fitted on its ends with thick high quality steel bands."]);

string
query_to_jail()
{
  return "south";
}

void
reset_palan_room()
{
	if (!ken)
	{
		ken = clone_object(MERCH + "living/ken");
		ken->move(TO);
	}
}

void
create_palan_room()
{
    setuid();
    seteuid(getuid());
    
    config_default_trade();
    
    SHORT("Arms district smithy");
    LONG("The walls of the smithy are comprised of large, translucent marble "
	+ "blocks turned grey by soot.  Against the north wall is a great open "
	+ "coal forge fire and black brick chimney beside which is an enormous "
	+ "bellows.  Dark iron anvils of various shapes sit beside the forge "
	+ "alongside racks of tools, hammers, and tongs.  In the east are tables "
	+ "of arms tending equipment and a pedal-driven grindstone.  Several "
	+ "journeymen smiths work vigorously at their tasks pumping the great "
	+ "bellows, filling the forge fires with coal, cleaning and polishing "
	+ "weapons and armour, aiding the master smith in hammering, and even "
	+ "sharpening and repairing the arms of customers.  An assortment of the "
	+ "master smith's weaponry hangs on the west wall for your perusal along "
	+ "with a marble sign, and there is an open window beside the door in "
	+ "the south through which a cool breeze stirs the hot, sooty air.\n");

	ITEM(({"plaza", "court", "cul-de-sac"}), "Through the window, you could "
	+ "take a look at the cul-de-sac of Emptoris.\n");
	ITEM(({"window", "windows"}), "An open window is set into the south wall "
	+ "of the shop affording a good view of the cul-de-sac of Emptoris Row "
	+ "outside and stirring the hot, sooty air with a cool breeze.  You may "
	+ "<view court> to have a look.\n");
	ITEM("ceiling", "The smithy is one story with an arched marble ceiling "
	+ "high enough, almost, for a second floor.  The black brick chimney "
	+ "of the forge rises out of it along the north wall.\n");
	ITEM("floor", "The floor of the smithy is comprised of large, "
	+ "translucent marble blocks turned dark grey by soot from the forge "
	+ "and high traffic.  Though cleaned daily by the journeymen smiths, "
	+ "it's not long before a layer of dark grey grime builds back up.\n");
	ITEM("wall", "Which wall do you want to examine?  North, east, south, or "
	+ "west?\n");
	ITEM("walls", "The walls of the smithy are comprised of large, "
	+ "translucent marble blocks turned grey by soot from the forge.  "
	+ "Though scrubbed daily by the journeymen smiths, it's not long "
	+ "before a layer of dark grey grime builds back up.\n");
	ITEM("north wall", "The smithy's black brick forge is along the north "
	+ "wall, an impressive coal fire burning within fueled by journeymen "
	+ "smiths pumping its great bellows.  Racks of tools and various anvils "
	+ "are arranged beside it.\n");
	ITEM("east wall", "Along the east wall are tables of arms tending "
	+ "equipment such as polishing jars, whetstones, and cleaning "
	+ "implements along with a large, pedal-driven grindstone.\n");
	ITEM("south wall", "The exit door and a window are set into the "
	+ "south wall.  Through them you may enter or view the cul-de-sac of "
	+ "Emptoris Row outside.\n");
	ITEM("west wall", "The west wall is filled with an assortment of the "
	+ "master smith's weaponry.  Above the display is a marble sign beneath "
	+ "which are five small signs.\n");
	ITEM(({"block", "blocks", "marble blocks"}), "Particularly large "
	+ "blocks of marble were used in the construction of the smithy.  They "
	+ "were translucent white like most marble in the city but have turned "
	+ "dark grey over time from soot.\n");
	ITEM("soot", "A layer of dark grey grime and soot from the coal forge "
	+ "fires coats the walls and floors.  Despite the daily scrubbing of "
	+ "the journeymen smiths, it's almost impossible to stay ahead of soot "
	+ "build up.\n");
	ITEM(({"fire", "forge", "forge fire", "chimney", "brick chimney",
		"black chimney", "black brick chimney"}), "Waves of intense heat "
	+ "emanate from the black brick forge fire with every pump of the "
	+ "great bellows by the journeymen smiths.  The forge is impressively "
	+ "proportioned with efficiently arranged racks of tools and various "
	+ "anvils for the master smith and his workers.  A black brick "
	+ "chimney rises against the north wall and out the high ceiling "
	+ "above it.\n");
	ITEM("bellows", "Dark wooden paddles the size of a man squeeze their "
	+ "accordion like leather windbag to fuel the coal forge fire.  The "
	+ "journeymen smiths pump gruelingly at the bellows with each pump "
	+ "sending a wave of heat from the fire across the room.\n");
	ITEM(({"anvil", "anvils"}), "Several anvils of various shapes are "
	+ "arranged beside the forge for all manner of forging and repair "
	+ "work.  They are solid, dark iron and larger than most you've "
	+ "seen.\n");
	ITEM(({"tool", "tools", "hammer", "hammers", "tong", "tongs"}),
	  "Neatly arranged in racks beside the forge are an assortment of "
	+ "professional forge tools, hammers, and tongs.\n");
	ITEM(({"rack", "racks"}), "Oak racks, darkened by long exposure to "
	+ "forge soot, hold rows of neatly arranged tools, hammers, and tongs "
	+ "beside the forge for the master smith.\n");
	ITEM(({"table", "tables", "equipment", "grindstone"}), "Oak tables, "
	+ "darkened by long exposure to forge soot, hold arms tending "
	+ "equipment such as polishing jars, whetstones, and cleaning "
	+ "implements.  They are arranged in the east of the smithy.\n");
	ITEM(({"journeyman", "journeymen", "journeymen smiths"}), "Several "
	+ "journeymen aid the master smith at all hours gaining knowledge "
	+ "and experience.  They wear sooty white shirts and tight brown "
	+ "slacks under their long, leather aprons.\n");
	ITEM(({"weaponry", "knife", "knives", "sword", "swords", "club", "clubs",
		"polearm", "polearms", "axe", "axes", "staff", "staves"}), "A vast "
    + "assortment of the master smith's weaponry adorns the west wall "
    + "beneath the signs.  You may peruse them if you wish.\n");
	ITEM(({"sign", "marble sign"}), "A marble sign hangs on the west wall "
	+ "above an assortment of the master smith's weaponry.  You may read "
	+ "or mread it.  Below it are five small signs.  To check them out you "
	+ "may read knife, sword, club, polearm, staff or axe.\n");
	ITEM(({"signs", "small signs"}), "There are five small signs on the "
	+ "west wall beneath the marble sign.  Try read knife, sword, club, "
	+ "polearm, staff or axe.\n");
	ITEM("door", "An open door leads south into the cul-de-sac of Emptoris "
	+ "row and the Arms district.\n");
	ITEM(({"lamp", "lamps"}), "Small oil lamps rest in various places about "
	+ "the smithy providing light at night.\n");

	set_tell_time(180);

	add_tell("@@get_tell_time@@" + "\n");

	add_smell("vampire", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions "
	+ "masking the scent of blood.");
	add_smell("morgul", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.");
	add_smell("human", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.");
	add_smell("elf", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.");
	add_smell("goblin", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.");
	add_smell("dwarf", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.  "
	+ "If only this were underground, you'd be right at home.");
	add_smell("hobbit", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.  "
	+ "Nothing pleasant to eat or drink reaches your nose here.");
	add_smell("gnome", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.  "
	+ "Quite an industrial, little human forge this armoury.");
	add_smell("minotaur", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.");
	add_smell("halfhuman", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.");
	add_smell("halfelf", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.");
	add_smell("orc", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.");
	add_smell("hobgoblin", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.");
	add_smell("kender", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.  "
	+ "Such an industrial armoury to explore even without any hints of tasty "
	+ "food or drink.");
	add_smell("drow", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.");
	add_smell("noldor", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.");
	add_smell("uruk", "The air is hot with soot from the forge though "
	+ "you also pick up the smells of armament oil and polishing solutions.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "hot sooty air or armament oils or polishing solutions.");
	add_smell("unknown", "You smell the hot sooty air, armament oils, and "
	+ "cleaning solutions, but what the heck race are you?  Why not mail "
	+ "Krynn for fun?");

	EXIT(MERCH + "m11", "south", 0, 0);
	
	CMD(({"weapons", "weaponry"}), ({"peruse"}), "@@peruse_wep");
	CMD(({"plaza", "the plaza", "court", "the court", "cul-de-sac"}), "view",
		  "@@view_plaza");
	CMD(({"sign", "marble sign"}), "read", "@@read_sign");
	CMD(({"sign", "marble sign"}), "mread", "@@mread_sign");
	CMD("knife", "read", "@@read_knife");
	CMD("sword", "read", "@@read_sword");
	CMD("polearm", "read", "@@read_polearm");
	CMD("club", "read", "@@read_club");
	CMD("axe", "read", "@@read_axe");
    CMD("staff", "read", "@@read_staff");
	CMD(({"bellow", "bellows"}), "pump", "@@pump_bellows");

	reset_palan_room();
}

peruse_wep() 
{
	write("You carefully peruse the weapons on the wall.  There is a "
	+ "wide variety of daggers, flatknives, knives, kukris, machetes, "
	+ "shanks, shivs, stilettos, swords, cutlasses, rapiers, scimitars, "
	+ "sabres, halberds, bardiches, pikes, partisans, military forks, "
	+ "one-handed spears, hammers, warhammers, clubs, maces, morning-"
	+ "stars, flails, picks, mauls, war-chains, two-by-fours, axes, "
	+ "handaxes, battleaxes, and cleavers, staves and quarterstaves. "
    + "You can take a closer look at any of them with <check>.\n");
	say(QCTNAME(TP) + " carefully peruses the racks of weapons on the west "
	+ "wall.\n");
	return "";
}

view_plaza()
{
	/* This function returns an equivalent of 'look' from nplaza
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWSOUTH->long());
	target = find_object(VIEWSOUTH);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write("Out the window along the south wall, you can make out "
	+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the court you see " + desc + ".\n");

	say(QCTNAME(TP) + " gazes out the window along the south wall.\n");
 
	return 1;
}

public int
read_sign()
{
    setuid();
    seteuid(getuid());
    
	say(QCTNAME(TP) + " studies the marble sign on the west wall.\n");
	write("The sign reads...\n");
	cat(MERCH + "obj/smith_wep.txt", 1, 50);

	return 1;
}

public int
mread_sign()
{
    setuid();
    seteuid(getuid());
    
	string file = MERCH + "obj/smith_wep.txt";

	say(QCTNAME(TP) + " studies the marble sign on the west wall.\n");
	write("The sign reads...\n");
	TP->more(read_file(file, 1, 50000));


	return 1;
}

public int
read_knife()
{
    setuid();
    seteuid(getuid());
    
	say(QCTNAME(TP) + " studies the knife sign on the west wall.\n");
	write("The sign reads...\n");
	cat(MERCH + "obj/smith_knife.txt", 1, 50);

	return 1;
}

public int
read_sword()
{
    setuid();
    seteuid(getuid());
    
	say(QCTNAME(TP) + " studies the sword sign on the west wall.\n");
	write("The sign reads...\n");
	cat(MERCH + "obj/smith_sword.txt", 1, 50);

	return 1;
}

public int
read_polearm()
{
    setuid();
    seteuid(getuid());
    
	say(QCTNAME(TP) + " studies the polearm sign on the west wall.\n");
	write("The sign reads...\n");
	cat(MERCH + "obj/smith_polearm.txt", 1, 50);

	return 1;
}

public int
read_club()
{
    setuid();
    seteuid(getuid());
    
	say(QCTNAME(TP) + " studies the club sign on the west wall.\n");
	write("The sign reads...\n");
	cat(MERCH + "obj/smith_club.txt", 1, 50);

	return 1;
}

public int
read_axe()
{
    setuid();
    seteuid(getuid());
    
	say(QCTNAME(TP) + " studies the axe sign on the west wall.\n");
	write("The sign reads...\n");
	cat(MERCH + "obj/smith_axe.txt", 1, 50);

	return 1;
}

public int
read_staff()
{
    setuid();
    seteuid(getuid());
    
	say(QCTNAME(TP) + " studies the axe sign on the west wall.\n");
	write("The sign reads...\n");
	cat(MERCH + "obj/smith_staff.txt", 1, 50);

	return 1;
}

int
pump_bellows()
{
	write("A leather-aproned journeyman smith shakes his head at you "
	+ "saying, \"No, thanks.  I have it.\"\n");
	say(QCTNAME(TP) + " tries to pump the bellows but is denied by a leather-"
	+ "aproned journeyman smith.\n");
	return 1;
}

void
help_my_friend()
{
	set_alarm(6.0, 0.0, "help_my_friend2");
}

void
help_my_friend2()
{
	if (ken)
		ken->assist_friend();
}

void 
init()
{    
	::init();
	ADA("sharpen");
	ADA("wax");
	ADA("repair");
	ADA("tend");
	ADA("check");
}

int
sharpen(string str)
{
	string wepname;
	int r, d;
	object *weapon;

	NF("Sharpen what?\n");
	if (!str)
		return 0;

	if (!(weapon = FIND_STR_IN_OBJECT(str, TP)) || !sizeof(weapon))
		return 0;

	wepname = weapon[0]->short();
	r = weapon[0]->query_repair_dull() + 1;
	d = weapon[0]->query_dull();

	NF("Only weapons are sharpened here.\n");
	if (!(IS_WEAPON_OBJECT(weapon[0])))
		return 0;

	NF("Nothing can be done for that weapon.\n");
	if (weapon[0]->query_prop(OBJ_I_BROKEN))
		return 0;

	NF("That weapon is already in prime condition.\n");
	if (weapon[0]->query_dull() == 0)
		return 0;

	NF("That weapon is too far gone to repair further.\n");
	if (!F_LEGAL_WEAPON_REPAIR_DULL(r, d))
		return 0;

	NF("A journeyman smith whispers to you:  That transaction will require "
	+ "more funds, honourable customer.\n");
	if (!MONEY_ADD(TP, -288))
		return 0;

	weapon->set_repair_dull(r);
	write("The journeymen smiths oil your " + wepname + ", sharpen it at the "
	+ "grindstone, and then clean and polish it.  You pay them two gold "
	+ "coins.\n");
	say(QCTNAME(TP) + " pays the journeymen smiths two gold coins to oil "
	+ HIS(TP) + " " + wepname + ", sharpen it at the grindstone, and then "
	+ "clean and polish it.\n");
	return 1;
}

int
wax(string str)
{
	string wepname;
	int r, d;
	object *weapon;

	NF("Wax what?\n");
	if (!str)
		return 0;

	if (!(weapon = FIND_STR_IN_OBJECT(str, TP)) || !sizeof(weapon))
		return 0;

	wepname = weapon[0]->short();
	r = weapon[0]->query_repair_corr() + 1;
	d = weapon[0]->query_corroded();

	NF("Only weapons are waxxed here.\n");
	if (!(IS_WEAPON_OBJECT(weapon[0])))
		return 0;

	NF("Nothing can be done for that weapon.\n");
	if (weapon[0]->query_prop(OBJ_I_BROKEN))
		return 0;

	NF("That weapon is already in prime condition.\n");
	if (weapon[0]->query_corroded() == 0)
		return 0;

	NF("That weapon is too far gone to repair further.\n");
	if (!F_LEGAL_WEAPON_REPAIR_CORR(r, d))
		return 0;

	NF("A journeyman smith whispers to you:  That transaction will require "
	+ "more funds, honourable customer.\n");
	if (!MONEY_ADD(TP, -288))
		return 0;

	weapon->set_repair_corr(r);
	write("The journeymen smiths wax your " + wepname + ", oil it, and then "
	+ "clean and polish it.  You pay them two gold coins.\n");
	say(QCTNAME(TP) + " pays the journeymen smiths two gold coins to wax "
	+ HIS(TP) + " " + wepname + ", oil it, and then clean and polish it.\n");
	return 1;
}

int
repair(string str)
{
	string armname;
	int r, d;
	object *armour;

	NF("Repair what?\n");
	if (!str)
		return 0;

	if (!(armour = FIND_STR_IN_OBJECT(str, TP)) || !sizeof(armour))
		return 0;

	armname = armour[0]->short();
	r = armour[0]->query_repair() + 1;
	d = armour[0]->query_condition();

	NF("Only armours may be mended.\n");
	if (!(IS_ARMOUR_OBJECT(armour[0])))
		return 0;

	NF("Nothing can be done for that armour.\n");
	if (armour[0]->query_prop(OBJ_I_BROKEN))
		return 0;

	NF("That armour is already in prime condition.\n");
	if (armour[0]->query_condition() == 0)
		return 0;

	NF("That armour is too far gone to benefit from mending.\n");
	if (!F_LEGAL_ARMOUR_REPAIR(r, d))
		return 0;

	NF("A journeyman smith whispers to you:  That transaction will require "
	+ "more funds, honourable customer.\n");
	if (!MONEY_ADD(TP, -288))
		return 0;

	armour->set_repair(r);
	write("The journeymen smiths wax your " + armname + ", oil it, and then "
	+ "clean and polish it.  You pay them two gold coins.\n");
	say(QCTNAME(TP) + " pays the journeymen smiths two gold coins to wax "
	+ HIS(TP) + " " + armname + ", oil it, and then clean and polish it.\n");
	return 1;
}

int
tend(string str)
{
	string obname, longname, longname2, longname3;
	int r, d;
	object *ob;
	mixed testname;

	NF("Tend what?\n");
	if (!str)
		return 0;

	/* Bug if query_long returns other than long()
	NF("Tending will be available again soon.\n");
	if (str)
		return 0;*/

	if (!(ob = FIND_STR_IN_OBJECT(str, TP)) || !sizeof(ob))
		return 0;

	NF("We cannot tend to that again.\n");
	if (ob[0]->query_prop(PRETENDED) == 1)
		return 0;

	obname = ob[0]->short();

	NF("Only weapons and armours may be tended to here.\n");
	if (!(IS_ARMOUR_OBJECT(ob[0])) && !(IS_WEAPON_OBJECT(ob[0])))
		return 0;

	NF("We do not tend to broken arms.\n");
	if (ob[0]->query_prop(OBJ_I_BROKEN))
		return 0;

	NF("A journeyman smith whispers to you:  That transaction will require "
	+ "more funds, honourable customer.\n");
	if (!MONEY_ADD(TP, -288))
		return 0;

	testname = ob[0]->query_long();

	if (!stringp(testname))
	{
		write("A power within the " + obname + " resists the efforts by "
		+ "the journeymen smiths to tend to it.\n");
		return 1;
	}

	longname = ob[0]->query_long();
	longname2 = longname[..1];
	longname3 = longname[2..];

	if (longname2 != "@@")
	{
		ob[0]->set_long(ob[0]->query_long() + "It has been cleaned, "
		+ "polished, oiled, and tended to by professionals.\n");
	}

	else
	{
		string strtmp = call_other(ob[0], longname3);

		if (!strtmp)
		{
			ob[0]->set_long(ob[0]->long() + "It has been cleaned, "
			+ "polished, oiled, and tended to by professionals.\n");
		}

		else
		ob[0]->set_long(strtmp + "It has been cleaned, "
		+ "polished, oiled, and tended to by professionals.\n");
	}
	
	ob[0]->add_prop(PRETENDED, 1);
	write("The journeymen smiths carefully take your " + obname + ", clean "
	+ "it, polish it, and oil it proficiently.  You pay them two gold "
	+ "coins.\n");
	say(QCTNAME(TP) + " pays the journeymen smiths two gold coins to tend to "
	+ HIS(TP) + " " + obname + ", clean it, polish it, and oil it "
	+ "proficiently.\n");
	return 1;
}

int
check(string str)
{
	int k;
	string check = "";
	
	if (!str)
	{
		write("Check what?  Some of the sample weaponry? You may want to "
		+ "peruse it first or even <read sign>.\n");
		return 1;
	}

	if (check = name_arm_to_info[str])
	{
		write("You check out the " + str + " on the west wall. " + check
		+ "\n");
		say(QCTNAME(TP) + " checks out the " + str + " on the west wall.\n");
		return 1;
	}
	write("That is not a valid sample of weaponry. Peruse the weaponry "
	+ "first or even <read sign>.\n");

	return 1;
}

string
get_tell_time()
{
	string ttell = "";
	
	if (random(3))
	{
		ttell += one_of_list(({"Waves of intense heat emanate from the black "
		+ "brick forge fire with every pump of the great bellows by the "
		+ "journeymen smiths.", "Dark, coal smoke rises up the black brick "
		+ "chimney from the forge fire.", "A leather-aproned journeyman "
		+ "smith pedals the grindstone to sharpen a customer's "
		+ one_of_list(({"knife", "sword", "polearm", "club", "axe"})) + ".",
		  "Flickering light from the forge fires reflects off the "
		+ "folded-steel weaponry on the west wall.",
		  "A pair of leather-aproned journeymen smiths pump the great "
		+ "bellows stoking the forge fire and sending waves of heat across "
		+ "the room.", "A leather-aproned journeyman smith "
		+ one_of_list(({"polishes a customer's blade", "wipes down some "
		+ "arms tending equipment", "tidies up"})) + " at a table in the "
		+ "east of the room."}));
		return ttell;
	}

    switch(GET_TIMEOFDAY)
    {
    case TOD_DAWN:
	ttell += one_of_list(({"Leather-aproned journeymen smiths go about their "
	+ "morning routine of scrubbing the " + one_of_list(({"floors and walls",
	  "weaponry upon the west wall", "master smith's tools and anvils",
	  "grindstone and arms tending tables", "soot off everything"})) + ".",
	  "A misty morning breeze drifts in through the window beside the door "
	+ "on the south wall."
	}));

	break;

    case TOD_DAY:
	ttell += one_of_list(({"A warm breeze drifts in through the window "
	+ "beside the door on the south wall.", "The clouds overhead outside "
	+ "drift by sending shafts of golden light in through the window "
	+ "beside the door.", one_of_list(({"A group of young boys",
	  "A young boy", "A pair of young boys"})) + " walks in and gazes at "
	+ "the weaponry hung upon the west wall in awe before leaving."
	}));

	break;

    case TOD_TWILIGHT:
	ttell += one_of_list(({"A cool evening breeze drifts in through the "
	+ "window beside the door on the south wall.", "A leather-aproned "
	+ "journeyman smith lights a few small lamps around the smithy as "
	+ "night approaches.", "A leather-aproned journeyman smith sweeps "
	+ "up soot off the floor."}));

    break;

    case TOD_NIGHT:
	ttell += one_of_list(({"A cool, refreshing night breeze drifts in "
	+ "through the window beside the door on the south wall.", "The "
	+ "clouds overhead outside drift by sending rays of silver "
	+ "starlight in through the window beside the door.", "Outside in the "
	+ "night darkened cul-de-sac, a constable peers in through the window "
	+ "by the door nodding at the smiths.", "A cloaked figure leaves "
	+ "quietly out the door into the night.", "A cool night breeze drifts in "
	+ "through the window beside the door on the south wall.", "The "
	+ "clouds overhead outside drift by sending rays of pale moonlight in "
	+ "through the window beside the door."}));

	break;

    default:
	break;
    }
    return ttell;
}

void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if(interactive(ob))
        start_room_tells();
}
