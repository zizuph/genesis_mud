inherit "/std/object";

#include "/sys/wa_types.h"
#include "/sys/stdproperties.h"

void create_object()
{
	set_name("gundif's glass");
	add_name("glass");
	set_adj("emormous");
	add_adj("Gundif's");
	set_short("Gundif's enormous glass of Tuborg beer");
	set_long("This glass is much bigger than you have ever seen before. When "
+ "you look inside of it, you see, that it is filled with fine Tuborg beer, and "
+ "the foam on the surface reads \"To Gundie from Feo with love\". You can try "
+ "to <drink from glass>, <check level>, <check how drunk I am> or <rub glass>. "
+ "Try it now and have fun!\n");

	add_prop(OBJ_I_NO_DROP,1);
	add_prop(OBJ_I_VOLUME,5000);
	add_prop(OBJ_I_WEIGHT,5000);
}

void init()
{
	::init();
	add_action("drink","drink");
	add_action("check","check");
	add_action("rub","rub");
}

string drink(string s)
{
	int l;

	l=random(2);
	switch (l)
	{
	      case 0:
		write("Hmm, are you sure, that you're 18 years old? And have you "
+ "heard about the new prohibition law of Latvia? Ahh, nevermind, you catch some "
+ "amount of beer with you mouth and, turning around with fear in your eyes, "
+ "swallow it quickly. Wow! What a pretty pig you are now! :-) Try it again now!\n");
		break;
	      case 1:
		write("Ahh, so ya wanna drink it, yeah? Actually, if I were "
+ "you... All right, all right, you wanted it - you have got it now. Hmm, not bad at "
+ "all! Do it another time, and you'll get this delecious taste again!\n");
	}
	return "aaa";
}

string check(string s)
{
	int l;

	if (s == "how drunk I am")
	{
		l=random(5);
		switch (l)
		{
		      case 0:
			write("Do worry! You are too sober! Your glass can break "
+ "itself if you continue this way! Drink as fast as you can, please, or Feo "
+ "will be depressed.\n");
			break;
		      case 1:
			write("Hmmm, you know, you certainly HAVE drunk from the "
+ "glass, but it doesn't seem the proper amount. Try to fix it now, ok?\n");
			break;
		      case 2:
			write("Well, well, nobody says you have not drunk today, "
+ "but, you know, you can do more. They say \"The more you can, the more you "
+ "do\", so don't stop it now.\n");
			break;
		      case 3:
			write("I am proud of you! I see you drinking as a real... "
+ "hmm... dwarf! Go on and add a little, 'cause there is no borders for real "
+ "things.\n");
			break;
		      case 4:
			write("Wow, I never thought the dwarf could drink that "
+ "much! A tiny bit of this drink can show you the heavens, so go ahead and "
+ "see it!\n");
		}
		return "aaa";
	}
	if (s == "level")
	{
		l=random(4);
		switch(l)
		{
		      case 3:
			write("Hmmm, your glass is as full, as it was before you "
+ "made the first step in drinking from it. Hey, do you remember that day at all? "
+ "Prove it now and drink a little.\n");
			break;
		      case 1:
			write("Well, let's see... You have about a half of glass. "
+ "It doesn't seem to you, that you can leave it half-emptied, so would you be so "
+ "kind to make it more empty, please?\n");
			break;
		      case 2:
			write("There is a little amount of this finest beer on the "
+ "bottom of the glass. Shame on you, you failed to overcome such a bit?? I don't "
+ "believe in it! Show me I am wrong and don't make me upset again!\n");
		}
	return "aaa";
	}
}

string rub(string s)
{
	write("You carefully rub the glass, but nothing happens. You rub "
+ "it again, and again nothing happens. At last you rub it in the third time. "
+ "Hmmm, what a strange creature appears from the glass! This ugly green "
+ "draconian looks at you critically and says: \"Hey, are you out of your mind, "
+ "silly dwarf?? You must DRINK from it, and not RUB it, got it?\". Then he "
+ "turns around and dive into the glass with a great noise and a lot of beer "
+ "spilled out on you.\n");
	return "aaa";
}
