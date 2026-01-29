/* 
 * The Perfume Shop in the secret northeast exit of
 * the Court d'Plaisiri in the Nobles quarter.
 *
 * Mortis 12.2005
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

inherit NOBLE_ROOMBASE;
inherit "/lib/trade";

#define VIEWSW			(NOBLE + "nplaza")
#define NUM	sizeof(MONEY_TYPES)

int move_item(mixed arg); 
int test;

object parfumist;

mapping name_to_smell = (["cosmias":"A sophisticated fragrance fills your "
	+ "senses with passing memories of champagne, hardwood dance floors, "
	+ "evening winds, dark growing vines, and nightblooms quickening your "
	+ "pulse and bringing a smile to your lips.",
	"tortuous":"Your body temperature rises as this hypnotic fragrance "
	+ "captures your senses with memories of long nights, the darkest red "
	+ "wine, tight embraces, and passionate dances around a fire under the "
	+ "moon as the music and clapping of the watchers drives you on and a "
	+ "hot wind shakes the leaves from the trees above.  You snap yourself "
	+ "out of your reverie short of breath, your heart beating fiercely, "
	+ "and you smile to yourself as you wipe your brow and catch your "
	+ "breath.",
	"jordessia":"The latest fragrance from Jordesse fills your senses with "
	+ "passing memories of the full moon, its reflection blue upon the dark "
	+ "waters beneath your balcony as the night breeze tosses your hair "
	+ "back, and the dark outline of your companion appears from the "
	+ "shadows.  Underneath it all is the fragrance of a flower or musk or "
	+ "blossom you just can't place but cannot stop thinking about.",
	"control":"A commanding scent rises to your nostrils as your mind is "
	+ "filled with the essence of confidence, reliance, and cool resolve.  "
	+ "Your every word is chosen well and well received, and your deepest "
	+ "desires within your grasp.  You are in... Control.",
	"white hammer":"Clean, crisp, and attractive, the scents of White Hammer "
	+ "fill your senses reminding you of starlit nights illuminating the "
	+ "fresh, white snow on the slopes before you as a cold wind blows "
	+ "through your hair, and you can do no wrong in the eyes of the slim "
	+ "figure beside you.",
	"krom":"Ancient and mystic, the scents of an age past fill your senses "
	+ "with passing memories of the battles of gods and giants and men "
	+ "who lived and died by the mettle of which they were tempered.  Iron, "
	+ "leather, and musk...  no man may match you under Krom."]);

string
query_to_jail()
{
  return "southwest";
}

void
reset_palan_room()
{
	if (!parfumist)
	{
	parfumist = clone_object(NOBLE + "living/parfumist");
	parfumist->move(TO);
	}
}

void
create_palan_room()
{
    config_default_trade();

    SHORT("Parfumerie");
    LONG("This shop is very small and very fragrant.  There are two "
	+ "glass display counters, one against the wall on the left, the "
	+ "other against the right, and a darkwood counter in the back.  Four "
	+ "glass chandeliers hang in a diamond pattern from the ceiling, their "
	+ "multitude of candles shedding a yellow glow about the place.  A "
	+ "blue sign hangs behind the back counter.\n");

	ITEM(({"plaza", "court"}), "The court is busy at all hours providing "
	+ "pleasurable services in the nobles quarter.  You can view it from "
	+ "the window southwest.\n");
	ITEM(({"sign", "blue sign"}), "A blue, silk sign with white, flowing "
	+ "script painted carefully upon it hangs above the back counter and "
	+ "lists the fragrances available.  You may read it.\n");
	ITEM(({"counter", "case", "display"}), "Which counter?  The one on the "
	+ "left, right, or in the back?\n");
	ITEM(({"back counter"}), "A counter of dark stained wood, it sits along "
	+ "the back wall in the northeast from where the parfumist serves "
	+ "customers.  A small, wood framed pricelist sits upon it.\n");
	ITEM(({"left counter", "left case", "left display"}), "The counter along "
	+ "the left wall is built of polished steel and glass.  It contains "
	+ "samples of all the shop's colognes for men.  You may peruse it "
	+ "and then check a sample.\n");
	ITEM(({"right counter", "right case", "right display"}), "The counter "
	+ "along the right wall is built of polished steel and glass.  It "
	+ "contains samples of all the shop's perfumes for ladies.  You may "
	+ "peruse it and then check a sample.\n");
	ITEM(({"window", "windows"}), "A window is set into the southwest wall "
	+ "of the shop affording a good view of the Court d'Plaisir outside.  "
	+ "You may <view court> to have a look.\n");
	ITEM(({"chandelier", "chandeliers"}), "Four glass chandeliers hang on "
	+ "silver chains from the ceiling in a diamond pattern with one above "
	+ "the darkwood counter in the back, one each above the left and right "
	+ "display counters, and one above the doorway.  They shed a yellow "
	+ "glow about the small shop.\n");
	ITEM(({"candle", "candles"}), "A multitude of wide, white candles fill "
	+ "the glass chandeliers above shedding a yellow glow about the small "
	+ "shop.\n");
	ITEM(({"perfume", "perfumes", "cologne", "colognes", "sample",
		"samples"}), "Samples of perfumes and colognes fill the glass and "
	+ "steel counters in a variety of blue, pink, clear, and black vials, "
	+ "phials, philters, and bottles.  You may peruse the display "
	+ "counters to get a better look or read the sign behind the "
	+ "back counter.\n");
	ITEM(({"price", "prices", "pricelist", "pricelists"}), "A small, wood "
	+ "framed pricelist sits on the back counter.  It reads:\n\n"
	+ "  Ladies' Perfumes        Men's Colognes\n\n"
	+ "  Cosmias   - 6gc         Control      - 7gc\n"
	+ "  Tortuous  - 6gc         White Hammer - 5gc\n"
	+ "  Jordessia - 8gc         Krom         - 6gc\n\n");

	add_smell("vampire", "Your senses are filled with the overpowering "
	+ "fragrances of perfumes and scents of colognes designed to mask and "
	+ "hide the true smells of your prey.  Beneath it all you detect the "
	+ "slightest hints of blood.");
	add_smell("morgul", "Your senses are filled with the overpowering "
	+ "fragrances of perfumes and scents of colognes floating through the "
	+ "air but no trace of your prey.");
	add_smell("human", "The fragrances of enchanting perfumes and "
	+ "sophisticated colognes flood your nose and fill you with a subtle "
	+ "yearning.");
	add_smell("elf", "Your nose fills with the fragrances of perfumes and "
	+ "scents of colognes.  Surprisingly, you are impressed with what these "
	+ "Palanthian humans have managed to design, though you show no outward "
	+ "sign.  The parfumist who created them must have an exceptional sense "
	+ "of smell.");
	add_smell("goblin", "Mmmm, pretty smells flood your nostrils.  You "
	+ "wonder if they taste as good.");
	add_smell("dwarf", "Your nostrils are flooded with the fragrances of "
	+ "human perfumes and colognes.  Hmm, they're not half-bad.  There may "
	+ "be one or two worth trying.");
	add_smell("hobbit", "Your nose fills with the fragrances of perfumes "
	+ "and scents of colognes.  These humans are fine smellers to have "
	+ "designed such a range of attractive smells.");
	add_smell("gnome", "Your nostrils fill with the carefully designed "
	+ "human fragrances of perfumes and scents of colognes.  They are "
	+ "approximately two parts attractive, one part sophisticated, and one "
	+ "part sexy... give or take a part or so you estimate.");
	add_smell("minotaur", "Your large nostrils flare as they fill with the "
	+ "fragrances humans use to mask their delicious scents.  Perhaps they "
	+ "work as well on minotaurs.");
	add_smell("halfhuman", "The familiar fragrances of enchanting perfumes "
	+ "and sophisticated colognes flood your nose and fill you with a subtle "
	+ "yearning.");
	add_smell("halfelf", "The not unfamiliar fragrances of enchanting "
	+ "perfumes and sophisticated colognes flood your nose and fill you "
	+ "with a subtle yearning.  The human parfumist and designer of these "
	+ "fragrances must have a fantastic sense of smell.");
	add_smell("orc", "Your nostrils flare as they fill with the fragrances "
	+ "humans use to mask the scents of their sumptuous manflesh.  Perhaps "
	+ "they work as well on orcs.");
	add_smell("hobgoblin", "Your nostrils fill with the typical fragrances "
	+ "of perfumes and scents of colognes designed and used by humans to "
	+ "mask or enhance their true scents.  Perhaps they work as well on "
	+ "hobgoblins as well.");
	add_smell("kender", "Ooo, such lovely human fragrances of perfumes and "
	+ "scents of colognes!  These human smellers must have great noses to "
	+ "have designed such a variety of attractive smells.  It would be fun "
	+ "to sample them all.");
	add_smell("drow", "Your nose fills with the fragrances of perfumes and "
	+ "scents of colognes.  Odd.  You are not unimpressed with what these "
	+ "overdwelling humans have managed to design, though you show no "
	+ "outward sign.  The parfumist who created them must have an "
	+ "exceptional sense of smell for a human.");
	add_smell("noldor", "Your nose fills with the fragrances of perfumes and "
	+ "scents of colognes.  Surprisingly, you are impressed with what these "
	+ "simple humans have managed to design, though you show no outward "
	+ "sign.  The parfumist who created them must have an exceptional sense "
	+ "of smell for a human.");
	add_smell("presence", "This isn't the best form for enjoying the "
	+ "fragrances of perfumes and scents of colognes floating in the air "
	+ "here.");
	add_smell("unknown", "You smell the fragrant perfumes and colognes, but "
	+ "what the heck race are you?  Why not mail Krynn for fun?");

	EXIT(NOBLE + "nplaza", "southwest", 0, 0);
	
	CMD(({"display", "case", "counter", "left counter", "right counter",
		"left case", "right case", "left display", "right display",
		"fragrance", "fragrances", "perfume", "perfumes", "cologne",
		"colognes"}),
		({"peruse"}), "@@peruse_case");
	CMD(({"plaza", "the plaza", "court", "the court"}), "view",
		  "@@view_plaza");
	CMD(({"sign", "blue sign"}), "read", "@@read_sign");
	CMD(({"sign", "blue sign"}), "mread", "@@mread_sign");

	reset_palan_room();
}

peruse_case() 
{
	write("You casually peruse the glass and steel counters to your left "
	+ "and right.  The ladies' counter on the left contains samples of "
	+ "Cosmias, Tortuous, and Jordessia.  The men's counter on the right "
	+ "contains samples of Control, White Hammer, and Krom.\n");
	say(QCTNAME(TP) + " casually peruses the glass and steel counters to "
	+ "the left and right.\n");
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

	write(VIEWSW->long());
	target = find_object(VIEWSW);
	inv = all_inventory(target);
	obs = FILTER_SHOWN(FILTER_DEAD(inv));
	ppl = FILTER_LIVE(inv);

	if (strlen(desc = (string) COMPOSITE_FILE->desc_dead(obs, 1)))
	write("Out the window along the southwest wall, you can make out "
	+ desc + " on the ground.\n");

	if (strlen(desc = (string) COMPOSITE_FILE->desc_live(ppl, 1)))
	write("Outside in the court you see " + desc + ".\n");

	say(QCTNAME(TP) + " gazes out the window along the southwest wall.\n");
 
	return 1;
}

public int
read_sign()
{
	say(QCTNAME(TP) + " studies the blue sign behind the counter.\n");
	write("The sign reads...\n");
	cat(NOBLE + "obj/parfsign.txt", 1, 15);

	return 1;
}

public int
mread_sign()
{
	string file = NOBLE + "obj/parfsign.txt";

	say(QCTNAME(TP) + " studies the blue sign behind the counter.\n");
	write("The sign reads...\n");
	TP->more(read_file(file, 1, 50000));


	return 1;
}

void 
init()
{    
    ::init();
	ADA("sample");
    ADD("order", "buy");
}

int
sample(string str)
{
	int k;
	string sample = "";
	
	if (!str)
	{
		write("Sample what?  A lady's fragrance like Cosmias, Tortuous, or "
		+ "Jordessia?  Or a men's cologne like Control, White Hammer, or "
		+ "Krom?  You may want to <read sign>, too.\n");
		return 1;
	}

	if (sample = name_to_smell[str])
	{
		write("You spray a bit of " + str + " on your wrists and neck.  "
		+ sample + "\n");
		return 1;
	}
	write("That is not a valid fragrance.  You can check out the various "
	+ "counters for samples and even peruse them (or <read sign> even).\n");

	return 1;
}

/*
 * Function name: order
 * Description:   The buyer orders a drink
 * Arguments:     str - name of drink and possibly description on
 * how to pay and get the change
 */

int
order(string str)
{
    string name, str1, str2, str3;
    int *arr, price, num;
    
    NF("The parfumist is not here to fix your order.\n");
    if (!parfumist || !P(parfumist, TO))
      return 0;
    
    NF("Buy what?\n");
    if (!str)
      return 0;
    
    /* Has the player defined how payment will be done and what change
	 *to get back? */  
    if (sscanf(str, "%s with %s and get %s", str1, str2, str3) != 3)
      {
	  /* Well, maybe player has defined how payment will be done atleast? */
	  str3 = "";
	  if (sscanf(str, "%s with %s", str1, str2) != 2)
	    {
		str2 = "";
		str1 = str;
	    }
      }
    
    if (sscanf(str1, "%d %s", num, str1) != 2)
      num = 1;

    if (num == 0)
      num = 1;

	if (parse_command(str1, ({}), "'cosmias'"))
	{
		name = "perf_cosmias";
		price = num * 864;
	}

	else if (parse_command(str1, ({}), "'tortuous'"))
	{
		name = "perf_tortuous";
		price = num * 864;
	}

	else if (parse_command(str1, ({}), "'jordessia'"))
	{
		name = "perf_jordessia";
		price = num * 1152;
	}

	else if (parse_command(str1, ({}), "'control'"))
	{
		name = "colo_control";
		price = num * 1008;
	}

	else if (parse_command(str1, ({}), "[white] 'hammer'"))
	{
		name = "colo_whitehammer";
		price = num * 720;
	}

	else if (parse_command(str1, ({}), "'krom'"))
	{
		name = "colo_krom";
		price = num * 864;
	}

	else
	{
		write("The parfumist says:  I don't follow what you are trying "
		+ "to buy.\n");
		return 1;
	}

	if (num > 10)
      {
	  NF("The parfumist is good but can only bring you a maximum of 10 "
	  + "items at a time.\n");
	  return 0;
      }
    
    if (sizeof(arr = pay(price, this_player(), str2, test, 0, str3)) == 1)
      return 0;  /* pay() handles notify_fail() call */
    
    write("You pay " + text(exclude_array(arr, NUM, NUM * 2 - 1)) + ".\n");
    if (text(exclude_array(arr, 0, NUM - 1)))
      write("You get " + text(exclude_array(arr, 0, NUM - 1)) + ".\n");
    write("The parfumist fixes your order.\n");
    
    return move_item(({name, num, TP}));
}

int
move_item(mixed arg)
{
    object drink, ob;
    string file, name;
    int i, num;
    
    name = arg[0];
    num = arg[1];
    ob = arg[2];
    
    for (i = 0; i < 10; i++)
      {
	  num--;
	  file = NOBLE + "obj/" + name;
	  drink = clone_object(file);
	  
	  if (!test && (drink->move(ob)))
	    {
		ob->catch_msg("You drop the " + drink->short() +
			      " on the floor.\n");
		say(QCTNAME(ob) + " drops a " + drink->short() + 
		    " on the floor.\n", ob);
		drink->move(TO);
	    } 
	  else if (!test) 
	    {
		if (num == 0)
		  {
		      if (arg[1] > 1)
			{
			    ob->catch_msg("You get some " + drink->plural_short() +
					  ".\n");
			    say(QCTNAME(ob) + " buys some " + drink->plural_short() +
				".\n", ob);
			}
		      else 
			{
			    ob->catch_msg("You get " + drink->short() + ".\n");
			    say(QCTNAME(ob) + " buys " + drink->short() + ".\n", ob);
			}
		  }
	    }
	  else 
	    {
		say(QCTNAME(ob) + " seems to be estimating something.\n", ob);
		return 1;
	    }
	  if (num < 1)
	    break;
      }
    
    if (num > 0)
      set_alarm(1.0, 0.0, &move_item(({name, num, ob})));
    return 1;
}
