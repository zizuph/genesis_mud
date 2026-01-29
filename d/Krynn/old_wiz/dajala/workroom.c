inherit "/std/workroom.c";
#include "/d/Krynn/common/defs.h";
#include "/sys/macros.h";

void
create_workroom()
{
	set_short("Dajala's workroom.");
	set_long(BS(
		"This is Dajala's workroom. She has obviously put some effort into "
		+ "decorating it. You are overwhelmed by a multitude of exotic"
		+ " flowers and engulfed by a smell from a thousand "
		+ "blooms. There are four comfortable chairs arrayed around"
		+ " a flat round table next to a strange glowing plant. "
		+ "From one of the niches you hear a low "
		+ "buzzing. Slightly hidden by the huge plant there " 
		+ "is also a small bar.", 70));

	add_exit("/d/Calia/tmp/glykron/palace/guild", "calia", 0, 1);
	add_exit("/d/Genesis/wiz/entrance", "wizz", 0, 1);
	add_exit("/d/Krynn/workroom", "krynn", 0, 1);
	add_exit("/d/Krynn/gnome/guild/gmaster", "guild", 0, 1);

	add_item(("niche"),"To your surprise you see a bee hive in the niche.\n");
	add_item(({"hive","bee hive"}),BS(
		"You see a thousand bees buzzing around the entrance"
		+ " of the small hive. You notice relieved, that they "
		+ "seem to keep away from you although you stand quite "
		+ "close to their hive. This has to be an especially breeded "
		+ "species of indoor-bees. There is a strange little button "
		+ "with a label next to it.", 70));
	add_item(("bees"),BS(
		"There are too many of them and they are moving "
		+ "too fast to examine them more closely. But they really "
		+ "seem to be busy!", 70));
	add_item(("bar"),BS(
		"This cute little bar is merely visible next "
		+ "to a huge plant you cannot identify. It is well filled. "
		+ "Perhaps you could ask Dajala to serve something for "
		+ "you?", 70));
	add_item(("chair"),"You could try to sit in them. They look inviting.\n");
	add_item(({"plant","huge plant"}),BS(
		"It is not the plant itself that is glowing but its "
		+ "fruits! They look like little yellow lightbulbs. "
		+ "Somehow this is not surprising because they are just "
		+ "used as that.", 70));

	load_board();
	present("board", this_object())->set_num_notes(999);
	present("board", this_object())->set_short("Board of Scrolling");
	present("board", this_object())->set_no_report(1);
}

void
give_start()
{
	object dajala;
	
	dajala = TP;
	if(dajala->query_name() != "Dajala")
		return;
	if(!(P("mailreader", dajala)))
		clone_object("/secure/mail_reader")->move(dajala);
	if(!(P("setter", dajala)))
		clone_object("/d/Wiz/mercade/open/pragma")->move(dajala);
	if(!(P("cube", dajala)))
		clone_object("/d/Immortal/sauron/obj/cube")->move(dajala);
}

void
init()
{
	::init();
	ADA("equip");
	ADA("sit");
	ADA("press");
	ADA("read");
	set_alarm(0.5, -1.0, "give_start");
}

int
equip(string str)
{
	NF("Equip whom?\n");
	if(!(str == "me"))
		return 0;
	clone_object("/d/Calia/glykron/palace/weapons/sword_of_light")->move(TP);
	clone_object("/d/Krynn/solamn/splains/obj/bdragonhelm")->move(TP);
	clone_object("/d/Krynn/solamn/splains/obj/bshinguard")->move(TP);
	clone_object("/d/Emerald/mine/wep/osword")->move(TP);
	clone_object("/d/Emerald/mine/arm/o_pl")->move(TP);
	clone_object("/d/Emerald/mine/arm/o_bra")->move(TP);
	TP->command("wield all");
	TP->command("wear all");
	return 1;
}

int sit(string str)
{
	NF("Sit where?\n");
	if ((str == "chair") || (str == "into chair") || (str == "into the chair") || (str == "down"))
	{
		write(BS("You sink deep into the chair that looks most "
			+ "comfortable to you and feel really relaxed.", 70));
		say(QCTNAME(TP) + " sits down and seems to be lost in the soft cushions of the chair.\n");
		return 1;
	}	
	return 0;
}
int press(string str)
{
	object hon;
	NF("Press what?\n");
	if ((str == "button") || (str == "little button"))
	{
		write(BS("You press the button and a little plate "
			+ "appears in a formerly hidden slot. Then a "
			+ "strange yellow liquid drops slowly onto the plate. "
			+ "You pick up the plate.", 70));
		say (BS(QCTNAME(TP) 
			+ " does something to the bee hive and recieves "
			+ "a little plate.", 70));
		seteuid(getuid(TO));
		hon = clone_object("/d/Krynn/dajala/gnomes/obj/honey.c");
		hon->move(TP);
		return 1;
	}
	return 0;
}

int read(string str)
{
	NF("Read what?\n");
	if (str == "label")
	{
		write("You read:\n"
			+ "Be my guest to use the Honey-o-matic [Version 2.4]\n"
			+ "Gnome productions limited.\n");
		return 1;
	}
	else if (str == "mail")
	{
		seteuid(geteuid(TO));
          clone_object("/secure/mail_reader.c")->move(TP);
		return 1;
	}  
	return 0;
}

leave_inv(ob, to)
{
	object reader;
	::leave_inv(ob);
	reader = present("mailread", ob);
	if (reader) reader->remove_object();
}

