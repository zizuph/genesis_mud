/*
 * /d/Ansalon/guild/kender_occ/taunt_list.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * This is the file where taunts are kept. It is kept in a separate 
 * file to make it easier to add/remove taunts, as well as easier 
 * to select taunts and make things generally more readable. Taunts 
 * have been made up by myself, taken from publicly accessible web 
 * sites, and donated by various mortals on their own initiative, 
 * mainly Meercat. Put together by Gwyneth, 
 * July - September 1999. 
 */
public string
query_human_taunt()
{
    string str1;
    switch(random(2))
    {
        case 0:
	    str1 = "Wow, I've never seen such a big monkey before!";
	    break;
        default:
            str1 = "I'd offer to turn you into a slug, but that " + 
                "would be one step up the evolutionary tree for you!";
            break;
    }
    return str1;
}

public string
query_draconian_taunt()
{
    string str1;
    switch(random(4))
    {
        case 0:
	    str1 = "You guys are so dumb that the gods had to colour " + 
		"code you so you could tell each other apart!";
	    break;
        case 1:
            str1 = "So this is what living scrambled eggs look like!";
            break;
        case 2:
            str1 = "Did the spell backfire when they made you?";
            break;
        default:
            str1 = "Either your mother was an iguana and your father " + 
                "was a bat, or you're a very poor excuse for a gnomish " + 
                "invention!";
            break;
    }
    return str1;
}

public string
query_su_taunt()
{
    return "Thank you for shrouding yourself, it saves me the " +
        "trouble of offering you a bag with eye holes!";
}

public string
query_monk_taunt()
{
  string str1;
    switch(random(2))
    {
	case 0:
	    str1 = "You don't really need to bother punching people in " +
                "the stomach to knock the wind out of 'em, just wave " +
                "your arms around and the stench alone will do the trick!";
	    break;
	default:
	    str1 = "Hey, good fight I saw you in earlier!  You kicked " +
	        "your foot up under your enemy's nose, and they blacked out " +
	        "almost instantly!";
	    break;
    }
    return str1;
}

public string
query_gladiator_taunt()
{
    string str1;
    switch(random(2))
    {
	case 0:
	    str1 = "Gladiators will fight for anyone, just throw 'em " +
	           "some rotting dog meat and they're yours forever.";
	    break;
	default:
	    str1 = "Would you quit panting?  Your breath is killing " +
	           "all the plant life!";
	    break;
    }
    return str1;
}

public string
query_rfang_taunt()
{
    return "You know, I've often heard that pets look like their " + 
        "owners. I'd say that, but I might insult your wolf.";
}

public string
query_general_taunt()
{
    string str1;
    switch(random(36))
    {
        case 0:
            str1 = "Just one look at you and I realize it's true -- " +
                "the gods DO have a sense of humour!";
            break;
        case 1:
            str1 = "Your nostrils are just the right size for a " +
                "goatsucker bird to nest in! That would explain " +
                "all the bird droppings on your chin, or is that " +
                "just slobber?";
            break;
        case 2:
            str1 = "Is that your nose, or did a gully dwarf puke " +
                "on your face?";
            break;
        case 3:
            str1 = "If the old saying of 'What you don't " +
                "know won't hurt you' is true, you must be " +
                "invulnerable!";
            break;
        case 4:
            str1 = "Don't you have a terribly empty feeling -- " +
                "in your skull?";
            break;
        case 5:
            str1 = "Nice shirt. Somewhere a gully dwarf is missing " +
                "his snot rag.";
            break;
        case 6:
            str1 = "I'm amazed your knuckles don't bleed when " +
                "you walk.";
            break;
        case 7:
            str1 = "I'm glad you don't have a dual personality. " +
                "This one's bad enough!";
            break;
        case 8:
            str1 = "What you lack in good looks, you more than " +
                "make up for in stupidity!";
            break;
        case 9:
            str1 = "Have heart, my friend, a fireball might " +
                "improve your looks someday.";
            break;
        case 10:
            str1 = "I hope your kids don't inherit those " +
                "gargoyle lips!";
            break;
        case 11:
            str1 = "You should try wearing something under that " +
                "helm -- like a brain.";
            break;
        case 12:
            str1 = "Either the plague wagon just drove up, or you " +
                "REALLY need a bath!";
            break;
        case 13:
            str1 = "You look like you eat enough to kill a cow. By " +
                "the way, how IS your mother these days?";
            break;
        case 14:
            str1 = "Your parents tried to throw you to the wolves, " +
                "but the wolves threw you back!";
            break;
        case 15:
            str1 = "You have a very striking face. How many times " +
                "have you been struck there anyway?";
            break;
        case 16:
            str1 = "Do you have your easy-going nature " +
                "because you're too heavy to run, or just " +
                "too fat to fight?";
            break;
        case 17:
            str1 = "You really ought to have that growth on your " +
                "face looked at. Oh, I'm sorry! I didn't realize " +
                "that was your nose!";
            break;
        case 18:
            str1 = "Do you know what the difference between you " +
                "and a barrel of dung is? The barrel!";
            break;
        case 19:
            str1 = "You are the misbegotten offspring of a " +
                "janitorial tinker gnome and a bent wrench!";
            break;
        case 20:
            str1 = "What gnomish device got hold of your face?";
            break;
        case 21:
            str1 = "I bet dragons are jealous of that acid breath!";
            break;
	case 22:
	    str1 = "You motherless spawn of a goat!";
	    break;
	case 23:
	    str1 = "Do you drool on purpose, or is it just a fashion " + 
		"statement?";
	    break;
	case 24:
	    str1 = "Your mother was a hamster, and your father smelled " + 
		"of elderberries!";
	    break;
	case 25:
	    str1 = "Oh! I'm sorry I screamed just then. I thought you " + 
		"were an ogre's behind for a second. Then I remembered " + 
		"they don't smell so much!";
	    break;
	case 26:
	    str1 = "Oh, where's my hammer? Oh well, I'll just use your " + 
		"head. You look like you're used to it.";
	case 27:
	    str1 = "Why don't you go keep the village idiot company so " + 
		"you have someone to look up to?";
	case 28:
	    str1 = "I feel sorry for your little brain...all alone in " + 
		"that big fat head.";
	    break;
	case 29:
	    str1 = "When you were born, your father went right out and " + 
		"killed the stork!";
	    break;
	case 30:
	    str1 = "Whoa, don't think too hard or your brain might " + 
		"overheat.";
	    break;
	case 31:
	    str1 = "If you had a little bit more sense, you'd be a " + 
		"half-wit!";
	    break;
	case 32:
	    str1 = "Ha! Can't scare me. What, those are your real looks? " + 
		"Here I thought some mage cast a fear spell!";
	    break;
	case 33:
	    str1 = "Let's play horse.  I'll be the front end, you just be " +
	        "yourself.";
	    break;
        case 34:
            str1 = "I would engage in a battle of wits with you, but " + 
                "I refuse to duel with an unarmed person.";
            break;
        default:
            str1 = "You have a winning smile. Too bad everything else " + 
                "is a loser.";
            break;
        }
    return str1;
}

public string
query_goblin_taunt()
{
    string str1;
    switch(random(8))
    {
        case 0:
	    str1 = "Would you mind keeping your fleas to yourself?  " +
	           "Or is it impossible to keep them from trying " +
                   "to escape your rank stench?";
	    break;
	case 1:
	    str1 = "OH!  I'll have to mail my gnome friend right away!  " +
	           "His life-quest is to find something stupider than a " +
                   "houseplant!";
	    break;
	case 2:
	    str1 = "How can one insult a goblin when there's nothing " +
		    "stupider or fouler to compare them to?";
	    break;
	case 3:
	    str1 = "Oh no, smells like that poor monkey fell into the " + 
		"outhouse!";
	    break;
	case 4:
	    str1 = "Goblins! They'll fight for anyone, just throw them a " + 
                "piece of dogmeat, and they're yours forever!";
	    break;
	case 5:
	    str1 = "Could you try not to bleed all over me? You can never " + 
		"get rid of the smell of goblin.";
	    break;
        case 6:
            str1 = "Your wit is so slow it lost a race with frozen " + 
                "molasses.";
            break;
        default:
            str1 = "You're so ugly you could make a mule back away from " + 
                "an oat bin.";
            break;
    }
    return str1;
}

public string
query_halfelf_taunt()
{
    string str1;
    switch(random(2))
    {
        case 0:
	    str1 = "Hey, look everyone!! It's a giant kender!!";
	    break;
	default:
	    str1 = "You know what Paladine says when he makes a half-elf?   " + 
		"'Oops, slipped again!'";
	    break;
    }
    return str1;
}

public string
query_darmy_taunt()
{
    string str1;
    switch(random(3))
    {
        case 0:
	    str1 = "Hey! I love that goddess of yours! Let me guess... " + 
		"This little head went to market, this little head " + 
		"stayed home, this little head had roast beef...";
	    break;
	case 1:
	    str1 = "Hey, about that goddess of yours...I've always " + 
		"wondered -- how can five heads share half a brain?";
	    break;
	default:
	    str1 = "I hear even Kitiara turned you down!";
    }
    return str1;
}

public string
query_centaur_taunt()
{
    string str1;
    switch(random(4))
    {
        case 0:
	    str1 = "Yippee Ty Yi Ty Ay! It's brandin' time at the ol' " +
		"Lazy Topknot!";
	    break;
	case 1:
	    str1 = "Hey! Half-breed! Could you give me a lift? I'm " + 
		"late for a date!";
	    break;
	case 2:
	    str1 = "Hey, you've got a rat stuck to your behind! Oops! " + 
		"That's just your tail.";
	    break;
	default:
	    str1 = "I bet you're glad you have that tail to swat all " + 
		"those flies drawn to your horrid smell.";
	    break;
    }
    return str1;
}

public string
query_minotaur_taunt()
{
    string str1;
    switch(random(8))
    {
        case 0:
	    str1 = "Hey baby! Show us your udders!";
	    break;
	case 1:
	    str1 = "Those horns go further into your brain cavity than " + 
		"you let on, don't they?";
	    break;
	case 2:
	    str1 = "You've got that mad cow disease, don't you? I " + 
		"didn't know it turned your face into orc dung...";
	    break;
	case 3:
	    str1 = "You eat meat?! I thought cows were herbivores!";
	    break;
	case 4:
	    str1 = "Look at that! I'll be rich! The butcher will pay good " + 
		"money for that rump roast!";
	    break;
	case 5:
	    str1 = "What's this? A red handkerchief! Toro! Toro! Toro! Ole!";
	    break;
	case 6:
	    str1 = "I know a little dairy where they need a nice cow " + 
		"like you.";
	    break;
	default:
	    str1 = "Moooo!";
	    break;
    }   
    return str1;
}

public string
query_mage_taunt()
{
    string str1;
    switch(random(13))
    {
        case 0:
	    str1 = "They let you become an apprentice? Ha ha ha ha! " + 
		"They must have been pretty drunk huh?";
	    break;
	case 1:
	    str1 = "Wow, that's pretty neat! Do you do birthday parties?";
	    break;
	case 2:
	    str1 = "Why do you always make that funny face when you're " + 
		"concentrating on a spell? Oh, I'm sorry, you always " + 
		"look like that.";
	    break;
	case 3:
	    str1 = "You know? Someone told me that it takes a lot of " + 
		"intelligence to cast a spell. Now that I've met you, " + 
		"I know they must be wrong.";
	    break;
	case 4:
	    str1 = "Boy, you must have some trouble deciding what colour " + 
		"robe to wear every morning.";
	    break;
	case 5:
	    str1 = "You know, if you tied a pink bandana around your neck " + 
		"your outfit would look SO much better!";
	    break;
	case 6:
	    str1 = "Sure, you wear a black robe on the outside, but I " + 
		"bet you're wearing heart underwear underneath! Go on! " + 
		"Prove that you're not! Prove it!";
	    break;
	case 7:
	    str1 = "Is that a fireball, or are you just trying to light " + 
		"your pipe?";
	    break;
	case 8:
	    str1 = "I've seen gully dwarves who can cast more powerful " + 
		"spells!";
	    break;
	case 9:
	    str1 = "Get a life!";
	    break;
	case 10:
	    str1 = "You must really like me. Your eyes just light up " + 
		"every time I'm around!";
	    break;
	case 11:
	    str1 = "Has anyone ever told you that when you hiss like that " +
	        "you sound exactly like a goose during mating season?";
	    break;
	default:
	    str1 = "It's so considerate of you to hood yourself.  It saves " +
	        "me the trouble of offering you a paper bag with eyeholes, " +
                "pox-face!";
	    break;
    }
    return str1;
}

public string
query_pot_taunt()
{
    string str1;
    switch(random(2))
    {
        case 0:
	    str1 = "You must get really confused, not knowing which " + 
		"head to talk to half the time.";
	    break;
        default:
            str1 = "Takhisis has five heads because all that ugly " + 
                "couldn't fit on just one face! Looks like you could " + 
                "use five heads too!";
            break;
    }
    return str1;
}

public string
query_dragon_taunt(object ob)
{
    string str1, *adjs;
    switch(random(10))
    {
        case 0:
            str1 = "I've heard of dragon breath, but this is ridiculous!";
            break;
	case 1:
	    str1 = "Lizard! Lizard! Look at the fifty foot lizard! " + 
                "Let's make some boots!";
	    break;
	case 2:
	    str1 = "Does your breath always smell that bad, or have you " + 
	        "had a craving for gully dwarf?";
	    break;
	case 3:
	    str1 = "You guys are so stupid that the gods had to colour " + 
                "code you so you could tell each other apart!";
	    break;
	case 4:
	    str1 = "Excuse my breath. I had dragon stew last night.";
	    break;
	case 5:
	    str1 = "Either your mother was an alligator and your father " + 
		"was a bat, or you're a bad attempt at a gnome invention.";
	    break;
	case 6:
	    str1 = "If you are what you eat, there must be a lot fewer " + 
		"gully dwarves around here.";
	    break;
        case 7:
            str1 = "Was that a roar or do you have the hiccups?";
            break;
	case 8:
	    str1 = "If dragons would flap their wings as much as they " + 
		"flap their mouths, they would get a lot further.";
	    break;
	default:
            adjs = ob->query_adj(1);
	    if ((adjs[0] == "blue") || (adjs[1] == "blue"))
		str1 = "You call that lightning? I've seen more power " + 
		    "coming out of a gnome invention!";
	    if ((adjs[0] == "green") || (adjs[1] == "green"))
		str1 = "Gee! How much gas do you have anyway?";
	    if ((adjs[0] == "red") || (adjs[1] == "red"))
		str1 = "I bet you're great fun at barbecues!";
	    if ((adjs[0] == "white") || (adjs[1] == "white"))
		str1 = "I think your ice breath made your brain freeze.";
	    if ((adjs[0] == "black") || (adjs[1] == "black"))
		str1 = "I think that acid has eaten into your brain cavity.";
	    else
                str1 = "I heard the gods made a mistake with their first " + 
		    "creation, so they tried again.";
	    break;
    }
    return str1;
}

public string
query_elf_taunt()
{
    string str1;
    switch(random(7))
    {
        case 0:
	    str1 = "Did you know that elves can breathe water? No? " + 
		"Well, it's because their noses are so high in the air " + 
		"that if they couldn't, they'd drown when it rains!";
	    break;
	case 1:
	    str1 = "Look! A beardless dwarf!";
	    break;
	case 2:
	    str1 = "Y'know, some scholars say us kender are descended " + 
		"from elves, but then again, they say that about orcs too!";
	    break;
	case 3:
	    str1 = "See what happens when you breed a gully dwarf with a " + 
		"human?";
	    break;
	case 4:
	    str1 = "You could put an eye out with those ears!";
	    break;
	case 5:
	    str1 = "My ears are pointier! Nyanyanya nya nyaa nyaaa!";
	    break;
        default:
            str1 = "The fact that you're so anal-retentive probably " + 
                "explains why you're also so full of crap!";
            break;
    }
    return str1;
}

public string
query_gnome_taunt()
{
    string str1;
    switch(random(4))
    {
        case 0:
	    str1 = "Are you just plain ignorant, or is your life quest " + 
		"to be the first stupid gnome?";
	    break;
	case 1:
	    str1 = "Is that your gizmo, or did you just buy a junk yard?";
	    break;
	case 2:
	    str1 = "Is that your gizmo, or did a gully dwarf just sneeze?";
	    break;
	default:
	    str1 = "Have you been digging through the trash " + 
		"again? Oh! That's your gizmo!";
	    break;
    }
    return str1;
}

public string
query_dwarf_taunt()
{
    string str1;
    switch(random(11))
    {
	case 0:
	    str1 = "Hey everybody! Look at that! Have you ever seen a " + 
		"gully dwarf who's had a bath?";
	    break;
	case 1:
	    str1 = "Beard, short, bad tempered, smelly. You must be " + 
		"a dwarf!";
	    break;
	case 2:
	    str1 = "Do you know why dwarves hate water? Well, it gives " + 
		"them an excuse not to take a bath!";
	    break;
	case 3:
	    str1 = "Either you need a bath, or a gully dwarf just walked " + 
		"in!";
	    break;
	case 4:
	    str1 = "I've seen gully dwarf vomit that looks better than you!";
	    break;
	case 5:
	    str1 = "Oh, look at the big fat gnome!";
	    break;
	case 6:
	    str1 = "Wow, what's that smell? Did a goblin fart? Oh..." + 
		"it's you.";
	    break;
	case 8:
	    str1 = "Ya! My brother said he'd be your father, but a gully " + 
		"dwarf beat him up the stairs!";
	    break;
	case 9:
	    str1 = "Excuse me, but that gully dwarf over there has been " + 
		"complaining that you need a bath.";
	    break;
        default:
	    str1 = "You're pretty smart for a gully dwarf.";
	    break;
    }    
    return str1;
}

public string
query_rockfriend_taunt()
{
    string str1;
    switch(random(13))
    {
        case 0:
            str1 = "Wow, that's your beard? I thought it was just nose " +
                "hair!";
            break;
	case 1:
            str1 = "I've seen fuller beards on an elf!";
            break;
        case 2:
            str1 = "Look, the dwarf is getting angry. Who'd have thought " +
                "when gully dwarves get angry, their faces turn into a " +
                "draconian's armpit with a beard!";
            break;
        case 3:
            str1 = "I thought dwarves always had beards? That isn't a " +
                "beard! You've cut off a horse's tail and stuck it on " +
                "your face. You trickster!";
            break;
        case 4:
            str1 = "Do you know why dwarves have beards? It's because " +
                "they look like goblins underneath. Here, let me shave " +
                "yours so everyone can see your goblin face!";
            break;
        case 5:
            str1 = "Either it's snowing on your feet, or your beard's " +
                "got dandruff.";
            break;
        case 6:
            str1 = "Are you eating a rat?! Oh! It's your beard!";
            break;
        case 7:
            str1 = "Great beard! I didn't think gully dwarves could " +
                "grow them.";
            break;
        case 8:
            str1 = "Do you know why dwarves have beards? They're so " +
                "clumsy that they'd cut their heads off shaving!";
            break;
        case 9:
            str1 = "Look! It's a goblin in disguise. No dwarf would have " +
                "a beard like that!";
            break;
        case 10:
            str1 = "Is that your beard, or are you moldy?";
            break;
        case 11:
            str1 = "Darn, I have a dirty cup. Let me use your beard to " +
                "clean it.";
            break;
        default:
            str1 = "Is that a beard or a flea circus?";
            break;
    }
    return str1;
}


public string
query_all_taunt(object ob)
{
    if (random(80) < 15)
    {
        if ((ob->query_guild_name_occ() == "Dragonarmy") &&
            (random(10) > 8))
        {
            return query_darmy_taunt();
        }
        if ((ob->query_guild_name_occ() == "Gladiator guild") &&
            (random(10) > 8))
        {
            return query_gladiator_taunt();
        }
        if ((ob->query_guild_name_race() == "Red Fang Guild") &&
            (random(10) > 9))
        {
            return query_rfang_taunt();
        }
        if ((ob->query_guild_name_occ() == "Union of the Warriors of Shadow") 
          && (random(10) > 9))
        {
            return query_su_taunt();
        }
        if ((ob->query_guild_name_occ() == "Morgul Mages") &&
          (random(10) > 6))
        {
            return query_mage_taunt();
        }
        if ((ob->query_guild_name_occ() == "Priests of Takhisis") &&
          (random(10) > 9))
        {
            return query_pot_taunt();
        }
        if ((ob->query_guild_name_occ() == "Order of the Dragon") ||
            (ob->query_guild_name_occ() == "Ancient Kaheda Order") &&
            (random(10) > 8))
        {
            return query_monk_taunt();
        }
        if ((ob->query_guild_name_race() == "Rockfriend guild") &&
          (random(10) > 5))
        {
            return query_rockfriend_taunt();
        }
        if (ob->query_guild_name_occ() == "Gnomish Inventors")
        {
            return query_gnome_taunt();
        }
        if (ob->query_race_name() == "draconian")
        {
            return query_draconian_taunt();
        }
        if (ob->query_race_name() == "human")
        {
            return query_human_taunt();
        }
        if (ob->query_race_name() == "goblin")
        {
            return query_goblin_taunt();
        }
        if (ob->query_race_name() == "half-elf")
        {
            return query_halfelf_taunt();
        }
        if (ob->query_race_name() == "minotaur")
        {
            return query_minotaur_taunt();
        }
        if (ob->query_race_name() == "elf")
        {
            return query_elf_taunt();
        }
        if (ob->query_race_name() == "dwarf")
        {
            return query_dwarf_taunt();
        }
        if (ob->query_race_name() == "centaur")
        {
            return query_centaur_taunt();
        }
        if (ob->query_race_name() == "dragon")
        {
            return query_dragon_taunt(ob);
        }
    }

    return query_general_taunt();
}

