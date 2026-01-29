/*
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 */
string gHis = "his", gHim = "him", gHe = "he";
mapping story_map;

public void
setup_stories()
{
    story_map = ([ 
	0 : ({ "was too curious about those funny looking potions.", 
	   "were too curious about those funny looking potions." }),
	1 : ({ "played with the Knights' crossbows.", "" }),
	2 : ({ "asked the Nazgul if the eye was ever sleepy.", ""}),
	3 : ({ "met all those ugly orcs in Ithilien, while " +
	   gHe + " assures you that they " +
	   "had no sense of humour at all.", "met all those ugly orcs " +
	   "in Ithilien, while you assure everyone that they had no " +
	   "sense of humour at all." }),
	4 : ({ "disembarked right before the captain shouted Disembark!",
	   "" }),
	5 : ({ "discovered that a forge isn't a nice place to play, " +
	   "unless they are cold, which they seldom are, since they " +
	   "wouldn't be forges then, they would be...something else, " +
	   "but not forges.", "" }),
	6 : ({ "ate the Rangers' herbs when they told " + 
	   gHim + " not to.", "ate the " +
	   "Rangers' herbs when they told you not to." }),
	7 : ({ "asked the goblin lord if he couldn't bring " +
	   gHim + " a drink. " +
	   capitalize(gHe) + " was thirsty " +
	   "too...rude lord.", "asked the goblin lord if he couldn't " +
	   "bring you a drink. You were thirsty too...rude lord." }),
	8 : ({ "asked a devil's knight how he could create darkness " +
	   "just by mumbling.", "" }),
	9 : ({ "borrowed Lord Soth's horse.", ""}),
	10 : ({ "thought the Calian said move behind the enemy. Those " +
	   "swarms hurt badly, even though it was funny seeing arms and " +
	   "legs flying all around...and my own at that!", "thought the " +
	   "Calian said move behind the enemy. Those swarms hurt badly, " +
	   "even though it was funny seeing arms and legs flying all " +
	   "around...and your own at that!" }),
	11 : ({ "tried to mount the dragon, just like the dragon high " +
	   "lord did... " + capitalize(gHe) +
           " wonders why the dragon didn't bite the high lord?", "tried " +
	   "to mount the dragon, just like the dragon high lord did... " +
	   "You wonder why the dragon didn't bite the high lord?" }),
	12 : ({ "flew in the catapult, for real too, for about fifteen " +
	   "seconds, maybe even sixteen, but it was hard to keep track when " +
	   gHe + " was flying. " +
	   capitalize(gHe) + " muses that " +
	   gHe + " should have gone over the " +
	   "wall, because kender don't go through walls, not like " +
	   "boulders. At least " + gHe + 
	   " knows that " + gHe + " isn't a " +
	   "boulder. That's good isn't it?", "flew in the catapult, " +
	   "for real too, for about fifteen seconds, maybe even sixteen, " +
	   "but it was hard to keep track when you were flying. You muse " +
	   "that you should have gone over the wall, because kender don't " +
	   "go through walls, not like boulders. At least you know that " +
	   "you aren't a boulder. That's good isn't it?" }),
	13 : ({ "was surrounded by wolves smelling of goblins. " +
	   "Wolves aren't at all like dogs. They may look like them, " +
	   "but they are not as nice, well not all dogs are nice, but " +
	   "they don't all bite, at least not all at the same time...", 
	   "were surrounded by those wolves smelling of goblins. Wolves " +
	   "aren't at all like dogs. They may look like them, but they " +
	   "are not as nice, well not all dogs are nice, but they don't " +
	   "all bite, at least not all at the same time..." }),
	14 : ({ "knocked on the gates of the dark city in Ithilien. " +
	   capitalize(gHe) + " just wanted " +
	   "a cup of tea, but they aren't at all very friendly there.",
	   "knocked on the gates of the dark city in Ithilien. You just " +
	   "wanted a cup of tea, but they aren't at all very friendly " +
	   "there." }),
	15 : ({ "went doorsliding down a snowy marble staircase.", "" }),
	16 : ({ "accidentally got pushed out of the second story " +
	   "window of a black robed wizard's tower.", "" }),
	17 : ({ "was viciously attacked by a magically cursed green " +
	   "cloak which tried to devour " + gHim +
	   " whole.", "were viciously attacked by a magically cursed green " +
	   "cloak which tried to devour you whole." }),
	18 : ({ "discovered a whole coven of vampires and played tag " +
	   "with them all evening.", "" }),
	19 : ({ "was playing an exhilerating game of Kendertoss when " +
	   "the dwarf forgot to catch " + gHim +
	   ".", "were playing an exhilerating game of Kendertoss when " +
	   "the dwarf forgot to catch you." }),
	20 : ({ "tested a gnomish HamsterPropelledRazorSharpBeard" +
	   "TrimmerDevice on an uncooperative dwarf.", "" }),
	21 : ({ "jumped off of a flying griffon to try to acrobatically " +
	   "land on the back of a galloping horse twenty feet below.", "" }),
	22 : ({ "taunted a rude black robe who had wrongfully accused " +
	   gHim + " of stealing!", "taunted " +
	   "a rude black robe who had wrongfully accused you of stealing!" }),
	23 : ({ "found a magic spellbook and helpfully returned it to the " +
	   "irresponsible mage who lost it.", "" }),
	24 : ({ "walked on a tightrope across a flaming bed of nails " +
	   "on a dare.", "" }),
	25 : ({ "single-handedly saved Vingaard Keep from a raiding troop " +
	   "of vicious draconians with nothing but " + 
	   gHis + " magic horse shoe of " +
	   "anti-Takhisis.", "single-handedly saved Vingaard Keep from a " +
	   "raiding troop of vicious draconians with nothing but your " +
	   "magic horse shoe of anti-Takhisis." }),
	26 : ({ "tested to see if that Knight's poofy mustaches were " +
	   "real or not by yanking on them sharply -- they were real!", "" }),
	27 : ({ "opened the door in the gnomish invention test site " +
	   "near the sign that said in great big red letters " +
	   "'DangerDoNotOpenThisDoor!'", "" }),
	28 : ({ "curiously asked Takhisis how five heads could possibly " +
	   "share half a brain.", "" }),
	29 : ({ "travelled through time through a magical portal to a " +
	   "time moments before the Cataclysm struck.", "" }),
	30 : ({ "accidentally tripped a snooty sword wielding elf with " +
	   gHis + " hoopak.", "accidentally " +
	   "tripped a snooty sword wielding elf with your hoopak." }),
	31 : ({ "used a magic ring and teleported to the very top of " +
	   "the Tower of High Sorcery.", ""}),
	32 : ({ "threw a cursed dagger that magically spun around and " +
	   "flew right back at " + gHim + "!",
	   "threw a cursed dagger that magically spun around and flew " +
	   "right back at you!" }),
	33 : ({ "snuck into a dragon's nest and tried to rescue an egg " +
	   "from being raised by a mean grumpy red dragon.", "" }),
	34 : ({ "took an exciting ride on the back of a giant " +
	   "flesh-eating goatsucker bird.", "" }),
	35 : ({ "got to see first-hand what it looked like to have a " +
	   "giant fireball come floating right towards " +
	   gHim + "!", "got to see first-hand " +
	   "what it looked like to have a giant fireball come floating " +
	   "right towards you!" }),
	36 : ({ "discovered that the colour red really does make an " +
	   "encampment of minotaurs angry, especially when coupled with " +
	   "shrieking jokes about how they milk their own grandmothers' " +
	   "udders.", "" }),
	37 : ({ "snuck into the dungeons of far away Barad-Dur, just " +
	   "to see what it was like.", "" }),
	38 : ({ "got captured by Rangers while exploring their top " +
	   "secret hide-out.", "" }),
	39 : ({ "asked a hunting shadow-elf why he couldn't even manage " +
	   "to catch a bunch of half-wit infidels or moronic trolobies.",
	   "" }),
	40 : ({ "threw a lit torch into a wagon piled high with " +
	   "fireworks for a hobbit's birthday party to see what would " +
	   "happen.", ""}),
	41 : ({ "tried to teach a giant hungry fire-lizard to sit up " +
	   "and beg with a small piece of raw meat.", "" }),
	42 : ({ "won a tournament in the arena of Athas when " +
	   gHe + " borrowed a flaming axe " +
	   "and accidentally set the whole arena on fire.", "won a " +
	   "tournament in the arena of Athas when you borrowed a flaming " +
	   "axe and accidentally set the whole arena on fire." }),
	43 : ({ "was mistakenly placed in a Gelan jail and cut " +
	   gHim + "self crawling out of " +
	   "the mysteriously unlocked window.", "were mistakenly placed " +
	   "in a Gelan jail and cut yourself crawling out of the " +
	   "mysteriously unlocked window." }),
	44 : ({ "shaved a dwarf in his sleep because " +
	   gHe + " thought he needed it.",
	   "shaved a dwarf in his sleep because you thought he needed it." }),
	45 : ({ "made shadow puppets on the wall using the glow from " +
	   "Lord Soth's eyes.", "" }),
	46 : ({ "played as a cook in a dragon army camp, and accidentally " +
	   "served fried draconian eggs for breakfast one morning.", "" }),
	]);
}

public void
find_story(object who, string where)
{
    int story;

    story = random(m_sizeof(story_map));

    who->catch_tell("You point excitedly to the scar on your " + where +
        " and rapidly explain about the time you " +
        (strlen(story_map[story][1]) ? story_map[story][1] :
        story_map[story][0]) + "\n");
    tell_room(environment(who), QCTNAME(who) + " points excitedly to " +
        "the scar on " + who->query_possessive() + " " + where + 
        " and rapidly explains about the time " +
        who->query_pronoun() + " " + story_map[story][0] + "\n", who);
    return;
}

