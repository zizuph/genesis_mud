/* 
 * The cobbler's shop off Jems Court in the Aesthetics quarter
 * of Palanthas.  Crafts custom shoes.
 *
 * Mortis 04.2006
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

inherit MONKS_ROOMBASE;

#define VIEWNORTH				(MONKS + "a11")
#define NUM	sizeof(MONEY_TYPES)

object lurr;

// Shoes and materials.
mapping name_arm_to_info = (["boots":"The pair of boots has a sturdy sole "
	+ "and heel and comes up to your calves.",
	"heels":"The pair of high-heels is firm but flexible with a pointed heel "
	+ "pushing the heel of the foot up and giving the body a provocative "
	+ "posture.",
	"sandals":"The pair of sandals has a flexible sole and straps that keep "
	+ "the foot and ankle in place and supported.",
	"shoes":"The pair of shoes has a quality sole with adequate foot "
	+ "support.  They come in the latest styles and all manner of "
	+ "varieties.",
	"slippers":"The pair of low-topped, soft soled slippers wraps around the "
	+ "foot comfortably while providing support.",
	"alligator":"The alligator skin has dark, emerald plates that are "
	+ "firm but supple and polished smooth.",
	"arrasene":"Arrasene is a smooth cloth woven from wool and silk giving "
	+ "it great durability and warmth while maintaining its fine appearance.",
	"bear":"Black bear skin is a thick, bushy, coarse-haired fur.",
	"canvas":"Canvas is a heavy, coarse, closely woven fabric of hemp and "
	+ "flax, often used in tents and sails.",
	"cashmyr":"Cashmyr is a soft twilled fabric made of very fine goat's "
	+ "wool from the mountains east of Palanthas.  It is unmatched for "
	+ "its soft feel, rich warmth, and rarity making it very expensive.  ",
	"cotton":"delicately woven Dargaard cotton, a soft, durable, and "
	+ "plentiful cloth that is airy and comfortable.",
	"deer":"Deerskin is a tough yet supple tanned leather.",
	"dupion":"Dupion is a cloth of coarse silk noted for its protection "
	+ "from abrasions and resistance to tearing.  Though coarse, the "
	+ "silk is soft and light.",
	"elfwyr":"Elfwyr is a fabric so light and delicate to the touch that "
	+ "it can hardly be felt when worn.  Elfwyr is the rarest of materials "
	+ "in Palanthas and rarely seen in the possession of any but the "
	+ "elven nobility of a select few reclusive clans.  The secrets of "
	+ "its production are virtually unknown.",
	"ermine":"Ermine is an unbelievably soft white fur of the northern "
	+ "ermine's winter coat.  It has small black spots spaced out upon "
	+ "it.",
	"fox":"Fox fur is an indulgently fine, reddish fur.",
	"hard":"Hard leather is boiled in oil, hardening it into form fitting "
	+ "plates.",
	"hide":"Rhinocerous hide is a thick, nearly impenetrable hide that is "
	+ "much lighter than metal armour.  ",
	"leather":"The leather is firmer than slow cured soft leather but "
	+ "more flexible than leather hardened in boiling oil.",
	"linen":"Linen is a stiff, woven cloth often used in formalwear, "
	+ "tablecloths, and sheets.",
	"lizard":"Stiff, green lizardskin is darker on the back and grows "
	+ "lighter towards the front and down its arms.",
	"mink":"It is mottled white, black, and brown mink fur.  It is "
	+ "incredibly soft and not only looks rich, but feels decadent against "
	+ "your skin.",
	"messaline":"Messaline is a soft, lightweight silk with a satin weave "
	+ "giving it a slightly glossy reflection in bright light and a shadowy "
	+ "depth in twilight.",
	"organdie":"Organdie is a fine, translucent cotton delicately woven and "
	+ "commonly used in scarves, light shirts and blouses, and occasionally "
	+ "bathrobes.  Placed over your eyes, you can still see through it "
	+ "somewhat, and when worn, the skin can clearly be seen beneath.",
	"rabbit":"It is soft, white rabbit fur.",
	"sable":"It is deeply rich, black sable fur.",
	"silk":"Silk is a very light, exceptionally strong, and luxuriously soft "
	+ "cloth woven from the unraveled cocoons of moethes.",
	"snake":"It is smoothly polished, scaly green snake skin.",
	"soft":"This leather is slow cured to be both soft to the touch "
	+ "and protective.",
	"studded":"This leather is expertly cured for a soft feel while remaining "
	+ "highly protective.  Inch diameter studs, their two inch diameter "
	+ "steel plates hidden beneath the leather, stick out every few inches "
	+ "giving the armour strong protections without great weight.",
	"suede":"Suede is a very soft, textured leather.  Suede must be "
	+ "painstakingly cured and worked to be so desirable.  As such it is "
	+ "expensive.",
	"swansdown":"Swansdown is a heavy napped, cotton flannel often used by "
	+ "outdoor travellers and highly regarded for its breathe-ability, "
	+ "durability, and silky softness.  It is a specialty of the Dresnos "
	+ "shipping company who keeps their source well guarded.",
	"terrycloth":"Terrycloth is a pile fabric of cotton with uncut loops on "
	+ "both sides often used to make bath towels and bath robes.",
	"wool":"Wool is a thick, coarse cloth woven from sheephair.  It is well "
	+ "regarded for its heat retention and comfort when not worn directly "
	+ "upon sensitive skin."]);

string
query_to_jail()
{
	return "north";
}

void
reset_palan_room()
{
	if (!lurr)
	{
		lurr = clone_object(MONKS + "living/lurr");
		lurr->move(TO);
	}
}

void
create_palan_room()
{
    seteuid(getuid(TO));

	SHORT("A small cobbler's shop");
	LONG("The walls of this cluttered shop are built from tan bricks with "
	+ "dirty gray mortar.  The aging wood of the low ceiling above dips down "
	+ "in its center where an oil lamp hangs shedding uneven light about the "
	+ "place.  Racks of shoes, slippers, and boots line the walls, and upon "
	+ "a low, round table by the stairs in the south are haphazardly arrayed "
	+ "cobblery tools and materials.  Above the table is a wooden sign with "
	+ "a list of ordering options.  A window in the north wall sits beside "
	+ "the dark, old, wooden door leading out onto the street.\n");

	ITEM(({"street", "outside", "court"}), "Through the window, you could "
	+ "take a look at the cul-de-sac of Emptoris.\n");
	ITEM(({"window", "windows"}), "An open window is set into the north wall "
	+ "of the shop affording a good view of Jems Court.  You may "
	+ "<view court> to have a look.\n");
	ITEM("ceiling", "The shop is two stories with an old, drooping, wooden "
	+ "ceiling from which hangs an oil lamp.  Stairs lead up into the south "
	+ "wall.\n");
	ITEM(({"stairs", "staircase"}), "A small flight of stairs "
	+ "rises to the second floor in the south of the shop.\n");
	ITEM(({"lamp", "oil lamp"}), "A large, oil lamp hangs on thin chains "
	+ "from the center of the drooping ceiling overhead shedding uneven "
	+ "light about the room.\n");
	ITEM("floor", "The floor of the shop is comprised of large, "
	+ "translucent marble blocks with a tinge of beige from years of traffic "
	+ "despite daily sweeping.\n");
	ITEM("wall", "Which wall do you want to examine?  North, east, south, or "
	+ "west?\n");
	ITEM("walls", "The walls of the shop are comprised of tan bricks with "
	+ "dirty grey mortar.\n");
	ITEM("south wall", "Arranged on racks upon the south wall are shoes, "
	+ "slippers, and boots of many varieties and sizes.  You may <peruse "
	+ "shoes> if you like or <check> individual varieties.\n");
	ITEM("east wall", "Arranged on racks upon the east wall are shoes, "
	+ "slippers, and boots of many varieties and sizes.  You may <peruse "
	+ "shoes> if you like or <check> individual varieties.\n");
	ITEM("north wall", "The exit door and a window are set into the "
	+ "north wall.  Through them you may enter or view Jems Court "
	+ "outside.\n");
	ITEM("west wall", "Arranged on racks upon the west wall are shoes, "
	+ "slippers, and boots of many varieties and sizes.  You may <peruse "
	+ "shoes> if you like or <check> individual varieties.\n");
	ITEM(({"block", "blocks", "marble blocks"}), "Large blocks of marble were "
	+ "used in the construction of the shop's floor.  They are translucent "
	+ "white like most marble in the city but tinged beige from years of "
	+ "traffic.\n");
	ITEM(({"tool", "tools", "materials", "material", "cobblery tools",
		"table"}),
	  "Cutting and shaping tools, studs, tacks, and shoe materials of all "
	+ "sorts are haphazardly arrayed on the table by the stairs in the "
	+ "south of the room.\n");
	ITEM(({"rack", "racks"}), "Aging, wooden racks on the walls hold "
	+ "varieties of shoes, slippers, and boots the cobbler has available for "
	+ "order.  You may <peruse shoes> or <check> on a particular type.\n");
	ITEM(({"shoe", "shoes", "slipper", "slippers", "boot", "boots"}), "A "
	+ "vast assortment of the cobbler's shoes, slippers, and boots adorns "
	+ "the walls.  You may peruse them if you wish.\n");
	ITEM("leather", "The air is thick with the rich smell of new leather.  "
	+ "It's everywhere in this shop, hanging off the south table and "
	+ "fashioned into footwear hanging on the racks on the walls.\n");
	ITEM(({"sign", "wooden sign"}), "A wooden sign hangs on the south "
	+ "wall above a work table.  It contains instructions for ordering.  "
	+ "You may read or mread it.\n");

	add_smell("vampire", "The air is thick with the rich smells of new "
	+ "leather and shoes.  The scent of blood is weak here.");
	add_smell("morgul", "The air is thick with the rich smells of new "
	+ "leather and shoes.");
	add_smell("human", "The air is thick with the rich smells of new "
	+ "leather and shoes.");
	add_smell("elf", "The air is thick with the rich smells of new "
	+ "leather and human shoes.");
	add_smell("goblin", "The air is thick with the mouth-watering, rich "
	+ "smells of new leather and shoes.  You don't know which to try "
	+ "first as your stomach growls hungrily, urging you to action.");
	add_smell("dwarf", "The air is thick with the rich smells of new "
	+ "leather and boots.  The smells bring back faint memories of "
	+ "gearing for battle but lack the tang of metal for which you yearn.");
	add_smell("hobbit", "The air is thick with the rich smells of new "
	+ "leather and shiny shoes.");
	add_smell("gnome", "The air is thick with the rich smells of new "
	+ "leather and human produced footwear.  It is a dingy place but "
	+ "efficient smelling.");
	add_smell("minotaur", "The air is thick with the rich smells of new "
	+ "leather and human shoes.  The smell brings back unpleasant memories "
	+ "of the last time your goose was cooked.");
	add_smell("halfhuman", "The air is thick with the rich smells of new "
	+ "leather and shoes.");
	add_smell("halfelf", "The air is thick with the rich smells of new "
	+ "leather and human shoes.");
	add_smell("orc", "The air is thick with the mouth-watering, rich "
	+ "smells of new leather and human boots.  You don't know which to try "
	+ "first as your stomach growls hungrily, urging you to action.");
	add_smell("hobgoblin", "The air is thick with the mouth-watering, rich "
	+ "smells of new leather and human footwear.  You don't know which to "
	+ "try first as your stomach growls hungrily, urging you to action, but "
	+ "you remind yourself that's not what you're here for.");
	add_smell("kender", "The air is thick with the rich smells of new "
	+ "leather and shiny shoes.");
	add_smell("drow", "The air is thick with the rich smells of new "
	+ "leather and shoes reminding you strongly of preparations for "
	+ "battle.");
	add_smell("noldor", "The air is thick with the rich smells of new "
	+ "leather and human footwear.");
	add_smell("uruk", "The air is thick with the mouth-watering, rich "
	+ "smells of new leather and boots.  Human leather might just make "
	+ "a decent meal if not decent armour.");
	add_smell("presence", "This isn't the best form to appreciate the "
	+ "air thick with the rich smells of new leather.");
	add_smell("unknown", "You smell the air rich with the smells of new "
	+ "leather, but what the heck race are you?  Why not mail "
	+ "Krynn for fun?");

	CMD(({"shoes", "slippers", "boots", "footwear", "sandals", "heels"}),
		({"peruse"}), "@@peruse_shoes");
	CMD(({"street", "north", "outside", "court"}), "view", "@@view_court");
	CMD(({"sign", "wooden sign"}), "read", "@@read_sign");
	CMD(({"sign", "wooden sign"}), "mread", "@@mread_sign");
	CMD(({"boots"}), "read", "@@read_boots");
	CMD(({"heels"}), "read", "@@read_heels");
	CMD(({"sandals"}), "read", "@@read_sandals");
	CMD(({"shoes"}), "read", "@@read_shoes");
	CMD(({"slippers"}), "read", "@@read_slippers");

	clone_object(MONKS + "doors/cobbler_door_in")->move(TO);

	reset_palan_room();
}

peruse_shoes() 
{
	write("You carefully peruse the shoes, slippers, and boots on the racks."
	+ "  There is a wide variety of types and styles.  You can take a closer "
	+ "look at any of them with <check>.\n");
	say(QCTNAME(TP) + " carefully peruses the shoes, slippers, and boots "
	+ "on the racks.\n");
	return "";
}

view_court()
{
	/* This function returns an equivalent of 'look' from a11
	 * most importantly without any supporting code from the
	 * target room.
	 */

	object *inv, *obs, *ppl, target;
    string desc;

	write(VIEWNORTH->long());
	target = find_object(VIEWNORTH);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write("Out the window along the north wall, you can make out "
	+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the court you see " + desc + ".\n");

	say(QCTNAME(TP) + " gazes out the window along the north wall.\n");
 
	return 1;
}

public int
read_sign()
{
	say(QCTNAME(TP) + " studies the wooden sign on the south wall.\n");
	write("The sign reads...\n");
	write(" _______________________________________________________________\n"
	+ "|                                                               |\n"
	+ "| +                                                           + |\n"
	+ "|                      Lurr's Cobblery                          |\n"
	+ "|                                                               |\n"
	+ "|   I will tailor footwear for you in any size* in any fashion  |\n"
	+ "|  you like. Just read the appropriate sign and order whatever  |\n"
	+ "|  you fancy.                                                   |\n"
	+ "|                                                               |\n"
	+ "|                Boots       -  <read boots>                    |\n"
	+ "|                High-heels  -  <read heels>                    |\n"
	+ "|                Sandals     -  <read sandals>                  |\n"
	+ "|                Shoes       -  <read shoes>                    |\n"
	+ "|                Slippers    -  <read slippers>                 |\n"
	+ "|                                                               |\n"
        + "|     * I do not have enough material to cater to Ogre feet     |\n"
	+ "| +                                                           + |\n"
	+ "|_______________________________________________________________|\n"
	+ "\n");

	return 1;
}

public int
mread_sign()
{
	string file = MONKS + "obj/cobbler_sign.txt";

	say(QCTNAME(TP) + " studies the wooden sign on the south wall.\n");
	write("The sign reads... \n");
	TP->more(" _______________________________________________________________\n"
	+ "|                                                               |\n"
	+ "| *                                                           * |\n"
	+ "|                      Lurr's Cobblery                          |\n"
	+ "|                                                               |\n"
	+ "|    I will tailor footwear for you in any size in any fashion  |\n"
	+ "|  you like. Just read the appropriate sign and order whatever  |\n"
	+ "|  you fancy.                                                   |\n"
	+ "|                                                               |\n"
	+ "|                Boots       -  <read boots>                    |\n"
	+ "|                High-heels  -  <read heels>                    |\n"
	+ "|                Sandals     -  <read sandals>                  |\n"
	+ "|                Shoes       -  <read shoes>                    |\n"
	+ "|                Slippers    -  <read slippers>                 |\n"
	+ "|                                                               |\n"
	+ "| *                                                           * |\n"
	+ "|_______________________________________________________________|\n"
	+ "\n");

	return 1;
}

public int
read_boots()
{
	say(QCTNAME(TP) + " studies the wooden boots sign.\n");
	write("The sign reads...\n");
	write(" ________________________________________________________________\n"
	+ "|                         ____________                           |\n"
	+ "| *                     _/            \\_                       * |\n"
	+ "|                      ~_ Lurr's Boots _~                        |\n"
	+ "|                        \\____________/                          |\n"
	+ "|                                                                |\n"
	+ "|   Style           Colour                           Material    |\n"
	+ "|   -----           ------                           --------    |\n"
	+ "|   buckled         black           yellow           alligator   |\n"
	+ "|   dark            white           forest-green     bear        |\n"
	+ "|   formal          charcoal        dark-green       deer        |\n"
	+ "|   glistening      grey            mottled-green    fox         |\n"
	+ "|   heavy           brown           olive-green      hard        |\n"
	+ "|   laced           dark-brown      blue             hide        |\n"
	+ "|   light           mottled-brown   pale-blue        leather     |\n"
	+ "|   loose           beige           raven-blue       lizard      |\n"
	+ "|   noble           tan             indigo           sable       |\n"
	+ "|   ornate          crimson         purple           snake       |\n"
	+ "|   plain           maroon          royal-purple     soft        |\n"
	+ "|   rugged          pink            coppery          studded     |\n"
	+ "|   short           dark-orange     golden           suede       |\n"
	+ "|   skin-tight      orange          silvery                      |\n"
	+ "|   steel-toed      pale-yellow                                  |\n"
	+ "|   steel-tipped                                                 |\n"
	+ "|   strapped                                                     |\n"
	+ "|   sturdy                                                       |\n"
	+ "|   supple                                                       |\n"
	+ "|   thick                                                        |\n"
	+ "|   thin                                                         |\n"
	+ "|   tight                                                        |\n"
	+ "|           <order> <style> <colour> <material> <boots>          |\n"
	+ "|                                                                |\n"
	+ "|           Try <inquire> instead of order for pricing.          |\n"
	+ "| *                                                            * |\n"
	+ "|________________________________________________________________|\n"
	+ "\n");

	return 1;
}

public int
read_heels()
{
	say(QCTNAME(TP) + " studies the wooden heels sign.\n");
	write("The sign reads...\n");
	write(" __________________________________________________________________________\n"
	+ "|                              ____________                                |\n"
	+ "| *                          _/            \\_                            * |\n"
	+ "|                           ~_ Lurr's Heels _~                             |\n"
	+ "|                             \\____________/                               |\n"
	+ "|                                                                          |\n"
	+ "|   Style                      Colour                          Material    |\n"
	+ "|   -----                      ------                          --------    |\n"
	+ "|   alluring    ornate         black          forest-green     alligator   |\n"
	+ "|   buckled     open-toed      white          dark-green       hard        |\n"
	+ "|   dark        plain*         charcoal       emerald-green    leather     |\n"
	+ "|   delicate    sensual        grey           green            lizard      |\n"
	+ "|   dainty      sensuous       brown          mottled-green    snake       |\n"
	+ "|   elegant     shiny          dark-brown     olive-green      soft        |\n"
	+ "|   enchanting  short          mottled-brown  blue                         |\n"
	+ "|   formal      skin-tight     beige          sapphire-blue                |\n"
	+ "|   glistening  sparkling      tan            pale-blue                    |\n"
	+ "|   heavy       strapped       crimson        raven-blue                   |\n"
	+ "|   hot         supple         maroon         indigo                       |\n"
	+ "|   laced       thin           pink           purple                       |\n"
	+ "|   light       tight          red            royal-purple                 |\n"
	+ "|   loose       translucent    ruby-red       violet                       |\n"
	+ "|   noble                      dark-orange    coppery                      |\n"
	+ "|                              orange         golden                       |\n"
	+ "|                              pale-yellow    silvery                      |\n"
	+ "|                              yellow                                      |\n"
	+ "|                                                                          |\n"
	+ "|                <order> <style> <colour> <material> <heels>               |\n"
	+ "|                                                                          |\n"
	+ "|                Try <inquire> instead of order for pricing.               |\n"
	+ "| *                                                                      * |\n"
	+ "|__________________________________________________________________________|\n"
	+ "\n");

	return 1;
}

public int
read_sandals()
{
	say(QCTNAME(TP) + " studies the wooden sandals sign.\n");
	write("The sign reads...\n");
	write(" _______________________________________________________________________\n"
	+ "|                            ______________                             |\n"
	+ "| *                        _/              \\_                         * |\n"
	+ "|                         ~_ Lurr's Sandals _~                          |\n"
	+ "|                           \\______________/                            |\n"
	+ "|                                                                       |\n"
	+ "|   Style                   Colour                          Material    |\n"
	+ "|   -----                   ------                          --------    |\n"
	+ "|   alluring    plain*      black          yellow           alligator   |\n"
	+ "|   buckled     rugged      white          forest-green     deer        |\n"
	+ "|   dark        sensual     charcoal       dark-green       dupion      |\n"
	+ "|   elegant     sensuous    grey           mottled-green    elfwyr      |\n"
	+ "|   glistening  strapped    brown          olive-green      hard        |\n"
	+ "|   heavy       sturdy      dark-brown     blue             hemp        |\n"
	+ "|   laced       supple      beige          pale-blue        hide        |\n"
	+ "|   light       thick       tan            raven-blue       leather     |\n"
	+ "|   loose       thin        mottled-brown  indigo           lizard      |\n"
	+ "|   ornate      tight       crimson        purple           snake       |\n"
	+ "|   open-toed               maroon         royal-purple     silk        |\n"
	+ "|                           pink           coppery          soft        |\n"
	+ "|                           dark-orange    golden           suede       |\n"
	+ "|                           orange         silvery          swansdown   |\n"
	+ "|                           pale-yellow                                 |\n"
	+ "|                                                                       |\n"
	+ "|             <order> <style> <colour> <material> <sandals>             |\n"
	+ "|                                                                       |\n"
	+ "|              Try <inquire> instead of order for pricing.              |\n"
	+ "| *                                                                   * |\n"
	+ "|_______________________________________________________________________|\n"
	+ "\n");


	return 1;
}

public int
read_shoes()
{
	say(QCTNAME(TP) + " studies the wooden shoes sign.\n");
	write("The sign reads...\n");
	write(" __________________________________________________________________________\n"
	+ "|                              ____________                                |\n"
	+ "| *                          _/            \\_                            * |\n"
	+ "|                           ~_ Lurr's Shoes _~                             |\n"
	+ "|                             \\____________/                               |\n"
	+ "|                                                                          |\n"
	+ "|   Style                       Colour                         Material    |\n"
	+ "|   -----                       ------                         --------    |\n"
	+ "|   alluring    open-toed       black          yellow          alligator   |\n"
	+ "|   buckled     plain*          white          forest-green    bear        |\n"
	+ "|   common      rugged          charcoal       dark-green      canvas      |\n"
	+ "|   dark        sensual         grey           mottled-green   deer        |\n"
	+ "|   delicate    sensuous        brown          olive-green     fox         |\n"
	+ "|   dainty      shiny           dark-brown     blue            hard        |\n"
	+ "|   elegant     short           beige          pale-blue       hemp        |\n"
	+ "|   enchanting  skin-tight      tan            raven-blue      hide        |\n"
	+ "|   formal      soft            crimson        indigo          leather     |\n"
	+ "|   glistening  steel-toed      maroon         purple          linen       |\n"
	+ "|   heavy       steel-tipped    mottled-brown  royal-purple    lizard      |\n"
	+ "|   hot         sparkling       pink           coppery         sable       |\n"
	+ "|   jaunty      strapped        dark-orange    golden          silk        |\n"
	+ "|   laced       sturdy          orange         silvery         snake       |\n"
	+ "|   light       supple          pale-yellow                    soft        |\n"
	+ "|   loose       thick                                          studded     |\n"
	+ "|   noble       thin                                           suede       |\n"
	+ "|   ornate      tight                                          wool        |\n"
	+ "|                                                                          |\n"
	+ "|                <order> <style> <colour> <material> <shoes>               |\n"
	+ "|                                                                          |\n"
	+ "|                Try <inquire> instead of order for pricing.               |\n"
	+ "| *                                                                      * |\n"
	+ "|__________________________________________________________________________|\n"
	+ "\n");


	return 1;
}

public int
read_slippers()
{
	say(QCTNAME(TP) + " studies the wooden slippers sign.\n");
	write("The sign reads...\n");
	write(" __________________________________________________________________________\n"
	+ "|                            _______________                               |\n"
	+ "| *                        _/               \\_                           * |\n"
	+ "|                         ~_ Lurr's Slippers _~                            |\n"
	+ "|                           \\_______________/                              |\n"
	+ "|                                                                          |\n"
	+ "|   Style                      Colour                          Material    |\n"
	+ "|   -----                      ------                          --------    |\n"
	+ "|   alluring     sensuous      black          green            alligator   |\n"
	+ "|   comfortable  shiny         white          mottled-green    arrasene    |\n"
	+ "|   dark         short         charcoal       olive-green      bear        |\n"
	+ "|   delicate     silent        grey           blue             cashmyr     |\n"
	+ "|   dainty       skin-tight    brown          sapphire-blue    cotton      |\n"
	+ "|   elegant      soft          dark-brown     pale-blue        dupion      |\n"
	+ "|   enchanting   sparkling     mottled-brown  raven-blue       deer        |\n"
	+ "|   formal       strapped      beige          indigo           elfwyr      |\n"
	+ "|   glistening   supple        tan            purple           ermine      |\n"
	+ "|   heavy        thin          crimson        royal-purple     fox         |\n"
	+ "|   jaunty       tight         maroon         violet           hard        |\n"
	+ "|   laced                      pink           coppery          hide        |\n"
	+ "|   light                      red            golden           leather     |\n"
	+ "|   loose                      ruby-red       silvery          lizard      |\n"
	+ "|   noble                      dark-orange                     messaline   |\n"
	+ "|   ornate                     orange                          mink        |\n"
	+ "|   padded                     pale-yellow                     organdie    |\n"
	+ "|   plain*                     yellow                          rabbit      |\n"
	+ "|   quiet                      forest-green                    sable       |\n"
	+ "|   rugged                     dark-green                      silk        |\n"
	+ "|   sensual                    emerald-green                   snake       |\n"
	+ "|                                                              soft        |\n"
	+ "|                                                              studded     |\n"
	+ "|                                                              suede       |\n"
	+ "|                                                              swansdown   |\n"
	+ "|                                                              terricloth  |\n"
	+ "|                                                              wool        |\n"
	+ "|                                                                          |\n"
	+ "|              <order> <style> <colour> <material> <slippers>              |\n"
	+ "|                                                                          |\n"
	+ "|                Try <inquire> instead of order for pricing.               |\n"
	+ "| *                                                                      * |\n"
	+ "|__________________________________________________________________________|\n"
	+ "\n");


	return 1;
}

void 
init()
{    
	::init();
	ADA("check");
}

int
check(string str)
{
	int k;
	string check = "";
	
	if (!str)
	{
		write("Check what?  Some of the sample footwear on the walls?  Or "
		+ "some custom material or option?  You may want to peruse them "
		+ "first or even <read sign>.\n");
		return 1;
	}

	if (check = name_arm_to_info[str])
	{
		write("You check out the " + str + ".  " + check + "\n");
		say(QCTNAME(TP) + " checks out the " + str + ".\n");
		return 1;
	}
	write("That is not a valid sample of footwear.  Peruse the shoes "
	+ "first or even <read sign>.\n");

	return 1;
}
