inherit "/std/room";
inherit "/lib/pub";
#include "defs.h"
#include "/d/Cirath/common/mobber.h"
object guard;
object npc;
object npc2;

void
reset_room()
{
    object npc = present ("marek", TO);
	object npc2 = present("thug",TO);
    if(!objectp(npc))
    {
	     bring_room_mob("marek", TYR_NPC+"marek",1,1);
    }
	if(!objectp(npc2))
	{
	     bring_room_mob("thug",TYR_NPC + "thug",6,1);
	}
}

void
create_room()
{
    set_short("Bard's Hand Tavern");
    set_long("This is perhaps one of the seediest bars you have ever seen. "
	+"Shadowy figures skulk around the edges of the room, while large "
	+"hulking figures surround the bar.  There is virtually no light "
	+"in here, which is probably why the bar attracts such unsavory "
	+"people.  Many races of large chested females wander the crowd "
	+"apparently selling something, and many of the patrons seem to "
	+"be taking them up on their offer, no matter how many people stare. "
	+"There is one strange thing, though, that seems out of "
	+"place.  Standing on a small, raised stage there are three "
	+"half-elves playing instruments and producing a beautiful "
	+"melody.  This small feature seems to make the rest of the "
	+"bar almost inconsequential.\n");
    add_item(({"half-elf","half-elves"}),"They are standing on stage "
	+"playing a ballad of some sort.  They are all dressed in "
	+"brightly colored clothes.  Even though they are playing "
	+"music, something about them makes you think they are "
	+"more than simple bards.  The way they are standing and "
	+"their posture is more like that of a killer than a "
	+"musician.\n");
    add_item("stage","It is elevated roughly a cubit from the floor and "
    +"looks to be made of some sort of sturdy wood.\n");
    add_item(({"girl","girls","female","females"}),
             "There are females from a variety of races including human, elf "
	+"dwarf, and half-elf.  They are all rather buxom, but you can tell "
	+"they would just as soon stick a knife between your ribs than talk "
	+"to you.\n");
    add_item(({"riff-raff", "patron", "patrons"}), "As one would expect, "+
             "they don't appreciate being stared at.\n");
    add_item(({"bar", "counter"}), "A simple stone counter, with a decent "+
             "supply of beverages behind it.\n");
    add_item("menu", "In symbols widely recognised throughout Athas, the "+
             "menu lists:\n  Food                   Drinks\n"+
             "    Bread         30 cc    Well Wine        25 cc\n"+
             "    Erdlu skewer  75 cc    Tyrian ale      50 cc\n"+
              "    Inix tail    120 cc    Ghostly Grimmace   200 cc\n"+
             "While it isn't stated, you can guess that it is possible to "+
             "'buy bread with gold', 'test buy Tyrian Ale', 'buy 8 wine', or "+
             "make other similar clever orders.\n");

    add_cmd_item("menu", "read", "Fortunately the menu is in examinable "+
             "symbols, or many would break the law against literacy.\n");

    add_drink(({"well wine", "wine","well wines"}),"wine","well", 50, 10,
             25, 0, 0, "Made from fermented kank nectar, broy is a nice, "+
             "cheap alternative to taste.\n", 0);
    add_drink(({"ale", "tyrian ale", "ales"}), "ale", "tyrian", 100, 20, 50,
             "Tyrian ale", "Tyrian ales", "Made from the grall cactus, "+
             "the blue Tyrian ale is a strong, bitter favorite.\n", 0);
  add_drink(({"grimmace", "grimmaces"}), "grimmace","ghostly",400,
	80, 250, 0, 0, "This is the strongest "+
             "drink you can buy in Tyr.  Made from a strange desert "
	    +"fruit that is dried, then soaked in the brains of a "
	    +"mekillot, it has been known to spontaneously combust.\n", 0);
    add_food(({"bread", "unleavened bread", "breads"}), "bread",
             "unleavened", 25, 30, 0, 0,
             "Its a flat, heavy, chunk of bread.\n", 0);
    add_food(({"skewers", "erdlu skewers", "skewer"}), "skewer", "erdlu",
             50, 75, "erdlu skewer", "erdlu skewers", "A sizable hunk of "+
             "steamed erdlu flesh on an edible chitin skewer. Yum!\n", 0);
    add_food(({"tail", "inix tail", "tails"}), "tail", "inix", 100, 120,
             0, 0, "Yes, the entire tail including the bones of a huge, "+
             "flightless Athasian bird, roasted to perfection.\n", 0);

    INSIDE

    add_exit(TYR_MARKET+"ass_train","north","@@north_block@@", 1);
   add_exit(TYR_MARKET+"bardqrtr", "south", 0, 1);

  reset_room();
}

void
init()
{
    ::init();
    init_pub();
}

int
north_block()
{
  object guard = present ("marek", TO);
  if(objectp(guard))
     {
       if(TP->query_alignment() > 0)
      {
     TP->catch_msg(QCTNAME(guard)+" says 'Members only bud', and blocks "
     +"your path.\n");
	return 1;
      }
      TP->catch_msg(QCTNAME(guard)+" acknowledges your passing with a "
     +"slight nod.\n");
    }
	return 0;
}

