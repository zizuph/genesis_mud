/*
 * - csuit.c
 *
 * A magical catsuit.
 */
#pragma strict_types

#include "zigg.h"

#include <const.h>
#include <macros.h>
#include <adverbs.h>
#include <cmdparse.h>
#include <formulas.h>
#include <language.h>
#include <ss_types.h>
#include <wa_types.h>
#include <stdproperties.h>

inherit "/std/armour";
inherit "/lib/commands";
inherit "/lib/keep";

#define SUBLOC    "__zigg_catsuit"

private static int talarm = 0;
private static string tsdesc = "";

private void
create_armour(void)
{
    set_keep(1);

    set_name(({ "suit", "catsuit", "zigg::csuit" }), 1);
    set_pname(({ "suits", "catsuits" }));
    set_adj(({ "snug", "black", "tight-fitting" }));
    set_short("black tight-fitting catsuit");
    set_pshort("black tight-fitting catsuits");
    set_long(
	"This is an extremely snug, tight-fitting suit fashioned from "+
	"the leathered skin of some unknown creature. It is a natural "+
	"shade of some dire black pigment and is firm yet amazingly "+
	"supple and soft to the touch. The material is also somewhat "+
	"stretchy, which is how it manages to fit so well and so tightly "+
	"despite its apparantly diminutive size when not worn. Where the "+
	"abdomen would be, there is instead an empty oval, exposing the "+
	"wearers natural navel and tummy to sight and scrutiny. Along "+
	"each outer thigh are three half-inch slash marks, also exposing "+
	"glimpses of the wearers skin. This suit stretches from the neck "+
	"to the toes, with the feet being padded and slightly thicker in "+
	"composition to the rest, buffed and gleaming shards of obsidian "+
	"serve as representative toenails. More of these obsidian shards "+
	"decorate each fingertip, though they are longer, thinner and "+
	"paired down to points to serve as talons for the enclosed hands "+
	"within. At the rear of the suit is a long, slender tail wound "+
	"from the same leather and ending in a tufted ball of silken "+
	"black fur. The entire ensemble resonates with a darkish magick "+
	"that causes your fingertips and skin to tingle wherever it "+
	"touches and you would not be at all surprised if you grew ears "+
	"and whiskers should you feel bold enough to slip into it.\n");

    add_item(({"material", "leather", "skin"}),
	"The black material making up this catsuit is the natural and "+
	"somewhat stretchy hide of some unknown creature. It's a dire "+
	"and fell shade of black that somehow manages to be both flat "+
	"and somewhat glossy at the same time, depending on whether you "+
	"stand in light or in darkness.\n");

    add_item(({"oval", "empty oval", "tummy"}),
	"Where the abdomen of the suit would normally be, there is an "+
	"empty oval instead. This causes the wearers own stomach and "+
	"navel to show through the blackness of the suit. Whether this "+
	"is merely for show or something more is unknown.\n");

    add_item(({"thigh", "thighs", "outer thigh", "outer thighs", "slash",
	       "marks", "slashes", "slash marks", "tears", "rips"}),
	"Three half-inch slash marks are ripped through the outside of "+
	"each thigh, granting provactive glimpses of skin through the "+
	"tears before they taper off to points at the front and rear. "+
	"A closer examination actually reveals highly subtle and "+
	"delicate stitching that gives the slashes only the appearance "+
	"of raggedness when they are, in fact, there by design.\n");

    add_item(({"feet", "foot"}),
	"The tightly slippered feet of the suit are actually padded and "+
	"quite comfortable. Thicker than the rest of the suit, they are "+
	"durable and have an inlain tread making them capable of "+
	"traversing most terrains with ease. The tip of each toe is "+
	"decorated with a glinting obsidian shard to emulate toenails.\n");

    add_item(({"nails", "shards", "obsidian", "obsidian shards"}),
	"Do you refer to the obsidian talons or perhaps the "+
	"obsidian toenails?\n");

    add_item(({"toenails", "obsidian toenails"}),
	"The obsiding toenails decorating the suit's feet are buffed and "+
	"polished so as to gleam and glint in any level of light. You "+
	"can't make out how the shaped shards are attached to the suit, "+
	"but they don't appear to be in any danger of falling off.\n");

    add_item(({"fingernails", "talons", "obsidian talons",
		"obsidian fingernails"}),
	"The obsidian talons are pointed and cruelly sharp, stretching "+
	"from the tip of each finger and glimmering dangerously with "+
	"each and every movement. The edges of the already sharp "+
	"obsidian shards have been honed even further, maximising their "+
	"piercing and slashing potential.\n");

    add_item(({"tail", "long tail", "slender tail", "leather tail"}),
	"A long, slender tail issues from the rear of the suit. Compised "+
	"of the same leather material, it is tightly wound to be durable "+
	"and yet still maintains a degree of stretchiness. The black and "+
	"tufted tip of the tail reaches nearly to the ground when "+
	"standing and is constructed of fine, silken strands of "+
	"soft fur.\n");

    add_prop(OBJ_I_WEIGHT,  250);
    add_prop(OBJ_I_VOLUME,  300);
    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(arm_ac) + 10000);

    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 50, "abjuration" }));
    add_prop(MAGIC_AM_ID_INFO, ({ "The catsuit is magical in nature.\n", 20,
	   "It bestows upon the wearer a sense of fearlessness.\n", 40,
	   "As well as enhancing the skills of the hunt.\n", 60 }));

    set_ac(10);
    set_af(TO);
    set_layers(6);
    set_looseness(1);

    /* It's a body-suit. */
    set_at(A_BODY | A_ARMS | A_HANDS | A_LEGS | A_FEET);
	
	if (IS_CLONE)
      set_item_expiration();  	

}

private void
extra_wear(object who)
{
    if (!objectp(wearer) || !objectp(who))
	return;

    who->catch_tell("\nAs "+ LTS(TO) +" finishes molding itself to "+
	"your body, you have the queer sensation of tufted ears "+
	"sprouting from the top of your head and ebony whiskers "+
	"shadowing your cheeks.\n");

    tell_room(ENV(who), "As "+ QTNAME(who) +" finishes donning "+ LTS(TO) +
	" you notice the appearance of tufted ears and ebony whiskers on "+
	HIS(who) +" head and face.\n", ({ who }), who);

    who->catch_tell("\nYou also get the sense that 'cathelp' "+
	"is available.\n");
}

public nomask mixed
wear(object obj)
{
    object who = environment(obj);

    if (TP != who)
	return "";

    /* Femmes only. */
    if (who->query_gender() != G_FEMALE)
	return "The "+ short() +" rejects your attempts to wear it.\n";

    /* Print the actual wear messages. */
    write("As you begin to wear "+ LTS(TO) +" it veritably slithers up "+
	"your body in its eagerness to be worn, hugging you tightly and "+
	"molding to your form like a second skin, it clings to your "+
	"every curve, peak and hollow, leaving very little to the "+
	"imagination.\n");

    say("As "+ QTNAME(who) +" wears "+ LTS(TO) +", it slides "+
	"along "+ HIS(who) +" body, melding to "+ HIS(who) +
	" form to become a second skin.\n", ({ who }));

    /* Let them know they have ears and whiskers. */
    set_alarm(5.0, 0.0, &extra_wear(who));

    /* Add custom subloc. */
    who->add_subloc(SUBLOC, TO);
    tsdesc = "resting idly";

    /* These only appear when worn. */
    add_item(({"ears", "tufted ears"}),
	"You can't really see the tufted ears but from what you can "+
	"feel, they are very soft and sensitive to the touch as they "+
	"poke up through your hair.\n");

    add_item(({"whiskers", "ebony whiskers"}),
	"Though hard for you to actually make out, they are long, and "+
	"though have the appearance of being delicate, they have a "+
	"degree of stiffness to them. They are soft to the touch and "+
	"dark as night.\n");

    /* The catsuit is magical and offers bonuses.
     *
    ALTER_STAT(who, SS_DEX, 20);
    ALTER_SKILL(who, SS_HIDE, 25);
    ALTER_SKILL(who, SS_SNEAK, 25);
    ALTER_PROP(who, NPC_I_NO_FEAR, 1);
    ALTER_PROP(who, LIVE_I_QUICKNESS, 15);
    ALTER_PROP(who, LIVE_I_NO_FOOTPRINTS, 1);
     */

    return 1;
}

public nomask mixed
remove(object obj)
{
    object who = environment(obj);

    /* Remove extra items. */
    remove_item(({"ears", "tufted ears"}));
    remove_item(({"whiskers", "ebony whiskers"}));

    if (TP != who)
	return "";

    /* Print removal messages. */
    write("Your tufted ears and ebony whiskers fade away as you peel "+
	"off "+ LTS(TO) +", a plaintive and churlish whimper seems to "+
	"echo from the catsuit as you do.\n");

    say(QCTNAME(who) +" peels "+ LTS(TO) +" from "+ HIS(who) +
	" skin, "+ HIS(who) +" tufted ears and ebony whiskers fading "+
	"away as "+ HE(who) +" does.\n", ({ who }));

    /* Remove subloc. */
    who->remove_subloc(SUBLOC);

    /* Remove bonuses.
     *
    ALTER_STAT(who, SS_DEX, -20);
    ALTER_SKILL(who, SS_HIDE, -25);
    ALTER_SKILL(who, SS_SNEAK, -25);
    ALTER_PROP(who, NPC_I_NO_FEAR, -1);
    ALTER_PROP(who, LIVE_I_QUICKNESS, -15);
    ALTER_PROP(who, LIVE_I_NO_FOOTPRINTS, -1);
     */
    return 1;
}

/* Our custom subloc to show ears, whiskers and tail. */
public string
show_subloc(string sub, object me, object looker)
{
    if ((sub != SUBLOC) || me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
	return "";

    if (me == looker)
    {
	sub = "You have little tufted ears poking up through your hair.\n" +
	    "You have ebony whiskers shadowing your cheeks.\n" +
	    "Your long, black tufted tail is "+ tsdesc +".\n";
    }
    else
    {
	sub = CAP(HE(me)) +" has little tufted ears poking up through "+
		HIS(me) +" hair.\n"+
	    CAP(HE(me)) +" has ebony whiskers shadowing "+ HIS(me) +
		" cheeks.\n"+
	    CAP(HIS(me)) +" long, black tufted tail is "+ tsdesc + ".\n";
    }

    return sub;
}

/* Auto-reset the tail state after a bit. */
private varargs void
tdesc(string str, int flag)
{
    tsdesc = str;

    if (flag)
    {
	talarm = 0;
	return;
    }

    if (talarm)
	remove_alarm(talarm);

    talarm = set_alarm(120.0, 0.0, &tdesc("resting idly", 1));
}

/* Used by emotes. */
#define OBERROR(str) if (!sizeof(oblist)) { \
        if (strlen(parse_msg)) { write(parse_msg); return 1; } \
        return notify_fail(str);  }

public int
e_mew(string str)
{
    string *how;
    object *oblist;
    int attr = ACTION_AURAL | ACTION_PROXIMATE;

    if (!objectp(wearer))
	return 0;

    how = parse_adverb_with_space(str, "cutely", 0);

    if (!strlen(how[0]))
    {
	write("You mew"+ how[1] +".\n");
	all(" mews"+ how[1] +".", how[1], attr); 
	return 1;
    }

    oblist = parse_live(how[0], "[at] [the] %o", attr);
    OBERROR("Mew [how] at who?\n");

    actor("You mew"+ how[1] +" at", oblist);
    all2act(" mews"+ how[1] +" at", oblist, 0, how[1], attr);
    target(" mews"+ how[1] +" at you.", oblist, how[1], attr);
    return 1;
}

public int
e_mrowr(string str)
{
    string *how;
    object *oblist;
    int attr = ACTION_AURAL | ACTION_PROXIMATE;

    if (!objectp(wearer))
	return 0;

    how = parse_adverb_with_space(str, "playfully", 0);

    if (!strlen(how[0]))
    {
	write("You mrowr"+ how[1] +".\n");
	all(" mrowrs"+ how[1] +".", how[1], attr); 
	return 1;
    }

    oblist = parse_live(how[0], "[at] [the] %o", attr);
    OBERROR("Mrowr [how] at who?\n");

    actor("You mrowr"+ how[1] +" at", oblist);
    all2act(" mrowr"+ how[1] +" at", oblist, 0, how[1], attr);
    target(" mrowr"+ how[1] +" at you.", oblist, how[1], attr);
    return 1;
}

public int
e_roar(string str)
{
    string *how;
    object *oblist;
    int attr = ACTION_AURAL | ACTION_THREATENING;

    if (!objectp(wearer))
	return 0;

    how = parse_adverb_with_space(str, "ferociously", 0);

    if (!strlen(how[0]))
    {
	write("You bare your teeth and roar"+ how[1] +".\n");
	all(" bares "+ HIS(TP) +" teeth and roars"+ how[1] +".",
	    how[1], attr); 
	return 1;
    }

    oblist = parse_live(how[0], "[at] [the] %o", attr);
    OBERROR("Roar [how] at who?\n");

    actor("You bare your teeth and roar"+ how[1] +" at", oblist);
    all2act(" bares "+ HIS(TP) +" teeth and roars"+ how[1] +" at",
	oblist, 0, how[1], attr);
    target(" bares "+ HIS(TP) +" teeth and roars"+ how[1] +" at you.",
	oblist, how[1], attr);
    return 1;
}

public int
e_slash(string str)
{
    string *how;
    object *oblist;
    int attr = ACTION_AURAL | ACTION_THREATENING;

    if (!objectp(wearer))
	return 0;

    how = parse_adverb_with_space(str, "swiftly", 0);

    if (!strlen(how[0]))
    {
	write("You slash your obsidian talons"+ how[1] +" through the "+
	    "air with an audible swish.\n");
	all(" slashes "+ HIS(TP) +" obsidian talons"+ how[1] +
	    " through the air with an audible swish.", how[1], attr); 
	return 1;
    }

    oblist = parse_live(how[0], "[at] [the] %o", attr);
    OBERROR("Slash your claws [how] at who?\n");

    actor("You slash your obsidian talons"+ how[1] +" through the "+
	"air before", oblist);
    all2act(" slashes "+ HIS(TP) +" obsidian talons"+ how[1] +" through "+
	"the air before", oblist, 0, how[1], attr);
    target(" slashes "+ HIS(TP) +" obsidian talons"+ how[1] +" through "+
	"the air before you.", oblist, how[1], attr);
    return 1;
}

public int
e_swish(string str)
{
    int attr = ACTION_MACTIVITY | ACTION_VISUAL;

    if (!objectp(wearer))
	return 0;

    str = check_adverb_with_space(str, "slowly");

    if (str == NO_ADVERB_WITH_SPACE)
        return notify_fail("Swish your tail how?\n");

    if (strlen(str))
	tdesc("swishing" + str);

    write("You swish your tail back and forth"+ str +".\n");
    allbb(" swishes "+ HIS(TP) +" tail back and forth"+ str + ".",
	str, attr);
    return 1;
}

public int
e_twirl(mixed str)
{
    int attr = ACTION_MACTIVITY | ACTION_VISUAL;

    if (!objectp(wearer))
	return 0;

    str = parse_adverb_with_space(str, "idly", 0);

    if (str[1] == NO_ADVERB_WITH_SPACE)
        return notify_fail("Twirl your tail how?\n");

    write("You take your slender tail in hand and twirl it"+ str[1] +".\n");
    allbb(" takes "+ HIS(TP) +" slender tail in hand and twirls it" +
	str[1] + ".", str[1], attr);
    return 1;
}

public int
e_twitter(mixed str)
{
    int attr = ACTION_LACTIVITY | ACTION_VISUAL;

    if (!objectp(wearer))
	return 0;

    str = parse_adverb_with_space(str, BLANK_ADVERB, 0);

    if (str[1] == NO_ADVERB_WITH_SPACE)
        return notify_fail("Twitter your whiskers how?\n");

    write("You twitter your ebony whiskers"+ str[1] +".\n");
    allbb(" twitters "+ HIS(TP) +" ebony whiskers" + str[1] + ".",
	str[1], attr);
    return 1;
}

public int
e_wiggle(string str)
{
    string *how;
    int attr = ACTION_MACTIVITY | ACTION_VISUAL;

    if (!objectp(wearer))
	return 0;

    how = parse_adverb_with_space(str, BLANK_ADVERB, 0);

    if (how[1] == NO_ADVERB_WITH_SPACE)
        return notify_fail("Wiggle your bottom how?\n");

    str = how[1];

    if (strlen(str = how[1]))
    {
	tdesc("swishing"+ str);

	if (random(2))
	{
	    how[0] = ", causing your tail to swish"+ str;
	    how[1] = ", causing "+ HIS(TP) +" tail to swish"+ str;
	}
	else
	{
	    how[0] = ", sending your tail swishing"+ str;
	    how[1] = ", sending "+ HIS(TP) +" tail swishing"+ str;
	}
    }
    else
    {
	how[0] = "";
	how[1] = "";
    }

    write("You wiggle your bottom"+ how[0] +".\n");
    allbb(" wiggles "+ HIS(TP) +" bottom" + how[1] + ".", str, attr);
    return 1;
}

public int
f_cathelp(string str)
{
    if (!objectp(wearer))
    {
	write("You should wear the catsuit first.\n");
	return 1;
    }

    write("Wearing the catsuit grants you the following emotions:\n\n"+
     "\t    mew [a]     - Mew [how - cutely]\n"+
     "\t  mrowr [a]     - Mrowr [how - playfully]\n"+
     "\t   roar [a] [t] - Roar [how - ferociously] [at someone]\n"+
     "\t  slash [a] [t] - Slash your talons [how - swiftly] [at someone]\n"+
     "\t  swish [a]     - Swish your tail [how - slowly]\n"+
     "\t  twirl [a]     - Twirl your tail [how - idly]\n"+
     "\ttwitter [a]     - Twitter your whiskers [how]\n"+
     "\t wiggle [a]     - Wiggle your bottom [how]\n"+
     "\n");

    return 1;
}

public void
init(void)
{
    ::init();

    if (ENV() != TP)
	return;

    /* Emotes for the catsuit. */
    add_action(     e_mew, "mew"     );
    add_action(   e_mrowr, "mrowr"   );
    add_action(    e_roar, "roar"    );
    add_action(   e_slash, "slash"   );
    add_action(   e_swish, "swish"   );
    add_action(   e_twirl, "twirl"   );
    add_action( e_twitter, "twitter" );
    add_action(  e_wiggle, "wiggle"  );

    add_action( f_cathelp, "cathelp" );
}

public string
query_recover(void)
{
    return MASTER + ":" +
	query_arm_recover() +
	query_keep_recover();
}

public void
init_recover(string arg)
{
    init_arm_recover(arg);
    init_keep_recover(arg);
}
