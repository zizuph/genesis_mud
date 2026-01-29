/*
 * Effects functions for all black_meffect#.c's.
 *
 * Mortis 01.2006
 */

int
effect1()
{
	string pname = one_of_list(({"Adriel", "Anahita", "Arnumor",
	"Angel", "Aizorana", "Alorrana", "Altrus", "Amberlee", "Ambrosia",
	"Barek", "Barin", "Barl", "Blond", "Bloodlust", "Bombur", "Bugs",
	"Calador", "Calantha", "Carnak", "Casbaar", "Castaneda", "Cecelia",
	"Chade", "Cherish", "Cromm", "Didelith", "Drogyn", "Dumar", "Einar",
	"Endriavarel", "Eowul", "Etanukar", "Fairlight", "Fatale", "Gadez",
	"Garnet", "Goul", "Greneth", "Greywolf", "Gub", "Hades", "Hisssss",
	"Iizk", "Ilrahil", "Kehr", "Kelnozz", "Krewl", "Kvator", "Leia",
	"Loralein", "Lysander", "Iliana", "Lysander", "Marduk", "Martooth",
	"Miclo", "Mim", "Mithros", "Moghiadin", "Monika", "Guinevere",
	"Pally", "Peldor", "Raven", "Recoba", "Rex", "Rugogold", "Saioran",
	"Saya", "Serander", "Sly", "Soote", "Thalia", "Thanak", "Thanatos",
	"Therock", "Thyrus", "Torg", "Trabajo", "Trovao", "Twilight",
	"Vallimar", "Wrach", "Wyork", "Xerxes", "Wulfhere", "Zielia",
	"Zingil", "Zorath", "Elita", "Hrothgar", "Grobb", "Joyce", "Kain",
	"Killgaar", "Legacy", "Magnus", "Rhynox", "Diri", "Sonnie",
	"Tristram", "Xar"}));

	int rand = random(5);

	if (rand == 0)
	{
		dri->catch_msg("A yellow fairyling alights on your shoulder and "
		+ "hands you [a suspicious disease].\n");
		tell_room(E(dri), QCTNAME(dri) + " cries:  I don't want that!\n",
		dri);
		return 1;
	}

	if (rand == 1)
	{
		dri->catch_msg("A gossamer yellow fairyling alights on your shoulder "
		+ "and hands you a message scroll.\nIt reads, \"Meet me in Sparkle "
		+ "ASAP.\" -" + pname + "\n");
		tell_room(E(dri), QCTNAME(dri) + " says:  What?  Meet " + pname
		+ " in Sparkle -now-???\n", dri);
		return 1;
	}

	if (rand == 2)
	{
		dri->catch_msg("Your eyes buzz, blurring the world for a moment.\n"
		+ "You go:  Buzzz, Bzzzz, beeee good.\n");
		tell_room(E(dri), QCTNAME(dri) + " goes:  Buzzz, Bzzzz, beeee good.\n",
		dri);
		return 1;
	}

	if (rand == 3)
	{
		dri->catch_msg("You hear a bee buzzing in your ear.  Its wings "
		+ "tickle your ear making you giggle.\n");
		tell_room(E(dri), QCTNAME(dri) + " giggles and swats at " + HIS(dri)
		+ " ear.\n", dri);
		return 1;
	}

	if (rand == 4)
	{
		dri->catch_msg("A friendly, golden yellow cloud descends upon you "
		+ "granting you the power of Oblegon en Perpetuim.\n");
		tell_room(E(dri), QCTNAME(dri) + " raises " + HIS(dri)
		+ " hands to the sky crying:  The power of Oblegon is MINE!!!\n",
		dri);
		return 1;
	}
	
	else
		dri->command("grin thirst");
		return 1;
}

int
effect2()
{
	int rand = random(5);

	if (rand == 0)
	{
		dri->catch_msg("A Beedledo alights on your shoulder and hands you "
		+ "an ounce of liquid gold.\n");
		tell_room(E(dri), QCTNAME(dri) + " cries:  Liquid gold!\n");
		return 1;
	}

	if (rand == 1)
	{
		dri->catch_msg("A flaming yellow Beedledo alights on your shoulder "
		+ "and hands you [a large white snake].\n");
		tell_room(E(dri), QCTNAME(dri) + " cries:  Snake!  Snaaaaake!!!\n",
		dri);
		dri->command("panic");
		return 1;
	}

	if (rand == 2)
	{
		dri->catch_msg("You hear the strumming of a tuned lute of the "
		+ "Fairy People, la la la la la.\n");
		tell_room(E(dri), QCTNAME(dri) + " dances like " + HE(dri)
		+ "'s listening to music as " + HE(dri) + " hums:  La la la la la.\n",
		dri);
		return 1;
	}

	if (rand == 3)
	{
		dri->catch_msg("A bee flies down your pants, its wings buzzing "
		+ "around your butt tickling you friskily.\n");
		tell_room(E(dri), QCTNAME(dri) + " giggles and twitches " + HIS(dri)
		+ " body as " + HE(dri) + " swats at " + HIS(dri) + " butt and "
		+ "loins.\n", dri);
		return 1;
	}

	if (rand == 4)
	{
		dri->catch_msg("A pulsing, golden yellow cloud descends upon you "
		+ "granting you the power words of Oblegon:  Igzz thli naht "
		+ "Oblegon!\n");
		tell_room(E(dri), QCTNAME(dri) + " raises " + HIS(dri) + " hands "
		+ "to the sky spinning around and hugging " + HIMSELF(dri)
		+ " in rapture.\n", dri);
		return 1;
	}
	
	else
		dri->command("stare");
	return 1;
}

int
effect3()
{
	int rand = random(5);
	object env = E(dri);

	if (rand == 0)
	{
		dri->catch_msg("The world spins about you as you flail your light "
		+ "airy limbs while your heavy head lolls about singingly.\n");
		if (env->query_prop(ROOM_I_INSIDE))
		{
			tell_room(E(dri), QCTNAME(dri) + " stumbles about the room hitting "
			+ HIS(dri) + " head " + one_of_list(({"against a nearby wall",
			  "on a hanging lamp", "on the counter", "against the edge of a "
			+ "nearby table", "on the back of a nearby chair"})) + ".\n", dri);
			return 1;
		}
		tell_room(E(dri), QCTNAME(dri) + " stumbles about the place hitting "
		+ HIS(dri) + " head " + one_of_list(({"against a tree", "on a rock",
		  "on a low branch", "against the ground"})) + ".\n", dri);
		return 1;
	}

	if (rand == 1)
	{
		dri->catch_msg("A dark room.\nA dark room.\nYou feel a wet warmth on "
		+ "your neck.\n");
		tell_room(E(dri), QCTNAME(dri) + " stumbles forward waving " + HIS(dri)
		+ " arms in front as " + HE(dri) + " blinks rapidly.\n", dri);
		return 1;
	}

	if (rand == 2)
	{
		dri->catch_msg("A golden fairyling arrives in a flash of sparkling "
		+ "yellow dweomers.  It flies inside your shirt tickling your "
		+ "stomach with its gossamer wings.\n");
		tell_room(E(dri), QCTNAME(dri) + " giggles and tickles at " + HIS(dri)
		+ " stomach saying:  Oh, you little fairyling.  Ohhhh!\n", dri);
		return 1;
	}

	if (rand == 3)
	{
		dri->catch_msg("You leave " + one_of_list(({"north", "northeast",
		"east", "southeast", "south", "southwest", "west", "northwest", "up",
		"down"})) + ".\nYou stand at the gates of the Beedledo, the Fairy "
		+ "People of yore.  Shimmering golden roofed towers rise behind the "
		+ "pristine white walls.  Fairylings buzz through the air past you "
		+ "into and out of the gates.  You have found Boplineeble.\n");
		tell_room(E(dri), QCTNAME(dri) + " gasps:  I finally made it!  "
		+ "Boplineeble, the blessed city of the Fairy People!\n", dri);
		return 1;
	}

	if (rand == 4)
	{
		dri->catch_msg("You smell an odd, honey aroma in the air, but it's "
		+ "familiary somehow.\n");
		dri->command("shrug unk");
		tell_room(E(dri), "A pale golden yellow cloud begins seeping out of "
		+ QCTNAME(dri) + "'s behind.\nOh Gag!  It's like a honey-flavoured "
		+ "fart, but it's anything but sweet.\n", dri);
		return 1;
	}

	else
		dri->command("burp");
		dri->command("burp");
		dri->command("burp");
		dri->command("burp");
		return 1;
}

int
effect4()
{
	int rand = random(5);

	if (rand == 0)
	{
		dri->catch_msg("A blond-haired long-legged female elf arrives.\nYou "
		+ "are forced to the ground by the power of the music.\n");
		tell_room(E(dri), QCTNAME(dri) + " falls to the ground holding "
		+ HIS(dri) + " hands over " + HIS(dri) + " ears moaning:  Somebody "
		+ "stop the music!\n", dri);
		return 1;
	}

	if (rand == 1)
	{
		dri->catch_msg("Your head swells in pulses out to the size of a large "
		+ "golden yellow watermelon while the world grows somewhat "
		+ "smaller.\n");
		tell_room(E(dri), QCTNAME(dri) + "'s head lolls about on " + HIS(dri)
		+ " shoulders.\n", dri);
		dri->command("say Now let's see how you handle it!");
		return 1;
	}

	if (rand == 2)
	{
		dri->catch_msg("A dark room.\nA dark room.\nA dark room.\nA dark room."
		+ "\nYou drop something.\nYou leave " + one_of_list(({"north",
		"northeast", "east", "southeast", "south", "southwest", "west",
		"northwest", "up", "down"})) + ".\n");
		dri->command("look");
		tell_room(E(dri), QCTNAME(dri) + " gazes around with a crazed look in "
		+ HIS(dri) + " eye.\n", dri);
		return 1;
	}

	if (rand == 3)
	{
		dri->catch_msg("Your head spins, but the old man is still before "
		+ "you, his ragged breath hot and rank on your face.  You are the "
		+ "old man.\n");
		dri->command("say You wanna know the truth?  Lord, I'll tell you the "
		+ "truth.  Your soul's gonna burn in a LAKE OF FIRE!!!\n");
		tell_room(E(dri), QCTNAME(dri) + " has a maniacal look in " + HIS(dri)
		+ " eye.\n", dri);
		return 1;
	}

	if (rand == 4)
	{
		dri->catch_msg("You catch [someone] rifling through your possessions."
		+ "\nGolden flashes of light streak across your eyes.  You are not "
		+ "alone.\n");
		tell_room(E(dri), QCTNAME(dri) + " flashes " + HIS(dri) + " head "
		+ "left.\n" + QCTNAME(dri) + " flashes " + HIS(dri) + " head right.\n"
		+ QCTNAME(dri) + "'s head wobbles around disturbingly.\n", dri);
		return 1;
	}

	else
		dri->command("fart");
	return 1;
}
