public int
urecognize_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "solemnly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    if (living(recipient))
    {
	notify_fail("You cannot do that to a living being.\n");
	return 0;
    }

    actor("You" + adverb + " hold", oblist, " in front of yourself and examine it, recognizing that it is a truly beautiful and magnificent item.");
    target(adverb + " holds you in front of "
      + tp->query_objective() + "self and examine it, recognizing that it is a truly beautiful and magnificent item.", oblist, adverb);
    all2act(adverb + " holds", oblist, " in front of "
      + tp->query_objective() + "self to examine it, then proclaims its beauty and magnificence.", adverb);
    return 1;
}

public int
urecord_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "purposefully" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You" + adverb + " note down the behaviour of", oblist, ".");
    target(adverb + " notes down your behaviour.", oblist, adverb);
    all2act(adverb + " notes down the behaviour of", oblist, ".", adverb);
    return 1;
}

public int
uregard_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "closely" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You regard", oblist, adverb + ", seeing "
      + recipient->query_objective() + " clearly as if for the first time.");
    target(" regards you" + adverb + ", as if seeing you clearly for the first time.", oblist, adverb);
    all2act(" regards", oblist, adverb + ", as if seeing "
      + recipient->query_objective() + " clearly as if for the first time.", adverb);
    return 1;
}

public int
ureject_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "politely" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if (stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");

	return 0;
    }


    if (!stringp(how[0]))
    {
	write("You" + adverb + " reject the proposal.\n");
	all(adverb + " rejects the proposal.", adverb);
	return 1;
    }

    oblist = parse_live(how[0], "[to] [at] [the] %o");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You" + adverb + " reject", oblist, "'s offer.");
    all2actbb(adverb + " rejects", oblist, "'s offer.", adverb);
    targetbb(adverb + " rejects your offer.", oblist, adverb);
    return 1;
}

public int
uremember_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "menacingly" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You" + adverb + " draw close to", oblist, " and whisper to "
      + recipient->query_objective() + ": Remember that the Punishment for telling a lie to the Inquisitor is death!");
    targetbb(adverb + " draws close to you and whispers to you: Remember that the Punishment for telling a lie to the Inquisitor is death!", oblist, adverb);
    all2actbb(adverb + " draws close to", oblist, " and whispers something to "
      + recipient->query_objective() + ".", adverb);
    return 1;
}

public int
uremind_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "zealously" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You" + adverb + " remind", oblist, " to keep the halls secure.");
    targetbb(adverb + " reminds you to keep the hall secure from Infidels by securing doors and cases.", oblist, adverb);
    all2actbb(adverb + " reminds", oblist, " to keep the hall secure from Infidels by securing doors and cases.", adverb);
    return 1;
}

public int
usalute_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp, mine, theirs;

    // Check for target and recipient weapons

    tp = this_player();
    how = parse_adverb_with_space(arg, "solemnly" , 0);
    adverb = how[1];

    mine = u_describe_weapons(W_SWORD);
    if(!strlen(mine))
    {
	notify_fail("You need to be wielding a sword.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("You raise your " + mine + " in salute.\n");
	allbb(" raises "
	  + tp->query_possessive() + " weapon in salute.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];
    theirs = u_describe_weapons(W_SWORD, 1, 0, W_ANYH, recipient);
    if(!strlen(theirs))
    {
	notify_fail("That person is not wielding a sword.\n");
	return 0;
    }

    actor("You clash your " + mine + " against", oblist, "'s " + theirs + " in salute.");
    target(" clashes "
      + tp->query_possessive() + " " + mine + " against your " + theirs + " in salute.", oblist, adverb);
    all2act(" clashes "
      + tp->query_possessive() + " " + mine + " against", oblist, "'s " + theirs + " in salute.", adverb);
    return 1;
}

public int
usecret_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "solemnly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You indicate" + adverb + " that the secret is sealed to the Flame with a subtle gesture of your hand.\n");
	all(" indicates" + adverb + " that the secret is sealed to the Flame with a subtle gesture of "
	  + tp->query_possessive() + " hand.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
usecure_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // check for target awareness for all message

    tp = this_player();
    how = parse_adverb_with_space(arg, "carefully" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    if (living(recipient))
    {
	notify_fail("You cannot do that to a living being.\n");
	return 0;
    }
    actor("You check", oblist, " for any signs of structural weakness. It is sound.");
    target(" checks you for security and structural soundness.", oblist, adverb);
    all2act(" checks", oblist, " for security and structural soundness.", adverb);
    return 1;
}

public int
uservice_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // training, check for target's cape

    tp = this_player();
    how = parse_adverb_with_space(arg, "politely" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    if(!sizeof(filter(recipient->query_clothing(-1), &->id("cape"))))
    {
	notify_fail("That person is not wearing a cape.\n");
	return 0;
    }

    actor("You" + adverb + " offer to wash", oblist, "'s cape for "
      + recipient->query_objective() + ".");
    targetbb(adverb + " offers to clean your cape for you.", oblist, adverb);
    all2actbb(" offers" + adverb + " to clean", oblist, "'s cape for "
      + recipient->query_objective() + ".", adverb);
    return 1;
}

public int
ushade_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "furtively" , 0);
    adverb = how[1];

    if(ENV(tp)->query_prop(ROOM_I_INSIDE))
    {
	notify_fail("You are not somewhere the sun shines.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("You shade your eyes" + adverb + " from the accursed sun.\n");
	allbb(" shades "
	  + tp->query_possessive() + " eyes" + adverb + " from the accursed sun.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
ushadows_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "gently" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You fall" + adverb + " into the shadows that gather around you.\n");
	allbb(" falls" + adverb + " into the shadows that gather around "
	  + tp->query_objective() + ".", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
ushame_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "firmly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You shake your finger" + adverb + " at everyone in a stern warning.\n");
	allbb(" shakes "
	  + tp->query_possessive() + " finger" + adverb + " at everyone in a stern warning.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You shake your finger" + adverb + " at", oblist, " in a stern warning.");
    target(" shakes "
      + tp->query_possessive() + " finger" + adverb + " at you in a stern warning.", oblist, adverb);
    all2act(" shakes "
      + tp->query_possessive() + " finger" + adverb + " at", oblist, " in a stern warning.", adverb);
    return 1;
}

public int
ushock_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "slowly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You hold your palm to your forehead "
	  + "and avert your gaze, shaking your head" + adverb + " in shock"
	  + ".\n");
	allbb(" holds "
	  + pos + " palm to "
	  + pos + " forehead and averts "
	  + pos + " gaze, shaking "
	  + pos + " head" + adverb + ".", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You hold your palm to your forehead and avert your gaze from", oblist, 
      ", shaking your head" + adverb + " in shock.");
    target(" holds "
      + pos + " palm to "
      + pos + " forehead and averts "
      + pos + " gaze, from you shaking "
      + pos + " head" + adverb + " in shock.", oblist, adverb);
    all2act(" holds "
      + pos + " palm to "
      + pos + " forehead and averts "
      + pos + " gaze, from", oblist, ", shaking "
      + pos + " head" + adverb + " in shock that.", adverb);
    return 1;
}

public int
ushow_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // check for weapon

    tp = this_player();
    how = parse_adverb_with_space(arg, "expansively" , 0);
    adverb = how[1];

    tmp = u_describe_weapons(W_SWORD, 1);
    if(!strlen(tmp))
    {
	notify_fail("You need to be wielding a sword.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	write("You" + adverb + " swing around your " + tmp + ", demonstrating your willingness to use it.\n");
	allbb(adverb + " swings around "
	  + pos + " " + tmp + ", demonstrating "
	  + pos + " willingness to use it.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You" + adverb + " swing around your " + tmp + " towards", oblist, ", demonstrating your willingness to use it.");
    target(adverb + " swings around "
      + pos + " " + tmp + " towards you, demonstrating "
      + pos + " willingness to use it.", oblist, adverb);
    all2act(adverb + " swings around "
      + tp->query_possessive() + " " + tmp + " towards", oblist, ", demonstrating "
      + tp->query_possessive() + " willingness to use it.", adverb);
    return 1;
}

public int
usigh_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    tp = this_player();
    how = parse_adverb_with_space(arg, "sorrowfully" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	write("You sigh" + adverb + ", longing for the day you may call yourself Amlis k'miasil.\n");
	all(" sighs" + adverb + ", with an absent look in "
	  + tp->query_possessive() + " eyes.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
usilence_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // Check for weapon, use that instead of hand. DIS makes shiver.

    tp = this_player();
    how = parse_adverb_with_space(arg, "curtly" , 0);
    adverb = how[1];

    tmp = u_describe_weapons(-1, 1);
    if(!strlen(tmp))
    {
	notify_fail("You need to be wielding a weapon.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("You motion with your " + tmp + " over your mouth for silence.\n");
	allbb(" motions with "
	  + pos + " " + tmp + " over "
	  + pos + " mouth for silence.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You motion with your " + tmp + " over your mouth at", oblist, " for silence.");
    target(" motions with "
      + pos + " " + tmp + " over "
      + pos + " mouth at you for silence.", oblist, adverb);
    all2act(" motions with "
      + pos + " " + tmp + " over "
      + pos + " mouth at", oblist, " for silence.", adverb);
    return 1;
}

public int
usilent_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "quickly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You motion" + adverb + " at everyone to keep silent.\n");
	allbb(" motions" + adverb + " at everyone to keep silent.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You motion" + adverb + " at", oblist, " to keep silent.");
    target(" motions" + adverb + " at you to keep silent.", oblist, adverb);
    all2act(" motions" + adverb + " at", oblist, " to keep silent.", adverb);
    return 1;
}

public int
using_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "mellifluously" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	write("You sing" + adverb + " in a very low voice.\n");
	all(" sings" + adverb + " in a very low voice.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
uproud_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "firmly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You slap", oblist, adverb + " on the shoulder in a gesture of "+
      "sincere pride in "+ recipient->query_possessive() + " accomplishments.");
    targetbb(" slaps you" + adverb + " on the shoulder in a gesture of "+
      "sincere pride in your accomplishments.", oblist, adverb);
    all2actbb(" slaps", oblist, adverb + " on the shoulder in a gesture of "+
      "sincere pride in "+ recipient->query_possessive() + " accomplishments.", adverb);
    return 1;
}

public int
usmooth_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // check for bandelaria

    tp = this_player();
    how = parse_adverb_with_space(arg, "slowly" , 0);
    adverb = how[1];


    if(!sizeof(filter(all_inventory(tp), &->id("bandeleria"))))
    {
	notify_fail("You must be wearing a bandeleria.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("You trace your fingers" + adverb + " over the sheathes of your bandeleria, trying to decide which dagger to use first.\n");
	allbb(" traces "
	  + tp->query_possessive() + " fingers" + adverb + " over the sheathes of "
	  + tp->query_possessive() + " bandeleria, trying to decide which dagger to use first.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
usolitude_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "inwardly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You smile" + adverb + " as you think of comfortable, predictable solitude.\n");
	allbb(" smiles" + adverb + " and "
	  + tp->query_possessive() + " expression becomes distant.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
usqueeze_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "forcefully" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You" + adverb + " squeeze your fist closed until a trickle of blood starts to fall to the ground.\n");
	allbb(adverb + " squeezes "
	  + tp->query_possessive() + " fist closed until a trickle of blood starts to fall to the ground.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
uscribe_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // needs paper?

    tp = this_player();
    how = parse_adverb_with_space(arg, "carefully" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You produce a quill and vellum and begin" + adverb + " to transcribe events.\n");
	allbb(" produces a quill and vellum and begins to write" + adverb + ".", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
ustand_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "weakly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You" + adverb + " hold yourself upright, refusing to be drawn away by the clutching shadows.\n");
	allbb(adverb + " holds "
	  + tp->query_objective() + "self upright, refusing to be drawn away by the clutching shadows.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
ustare_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "alert" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You stand" + adverb + ", no sign of expression on your face.\n");
	allbb(" stands" + adverb + ", no sign of expression on "
	  + tp->query_possessive() + " face.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You stand" + adverb + " before", oblist, ", no sign of expression on your face.");
    target(" stands" + adverb + " before you, no sign of expression on "
      + tp->query_possessive() + " face.", oblist, adverb);
    all2act(" stands" + adverb + " before", oblist, ", no sign of expression on "
      + tp->query_possessive() + " face.", adverb);
    return 1;
}

public int
ustench_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "quickly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You raise your hand" + adverb + " to cover your mouth from the stench.\n");
	allbb(" raises "
	  + tp->query_possessive() + " hand" + adverb + " to cover "
	  + tp->query_possessive() + " mouth from the stench.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
ustoic_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "stoicly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You stand" + adverb + ", your face devoid of all emotion.\n");
	allbb(" stands" + adverb + ", "
	  + tp->query_possessive() + " face devoid of all emotion.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You stand" + adverb + " before", oblist, ", your face devoid of all emotion.");
    target(" stands" + adverb + " before you, "
      + tp->query_possessive() + " face devoid of all emotion.", oblist, adverb);
    all2act(" stands" + adverb + " before", oblist, ", "
      + tp->query_possessive() + " face devoid of all emotion.", adverb);
    return 1;
}

public int
ustroke_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // check for bladed weapon

    tp = this_player();
    how = parse_adverb_with_space(arg, "intently" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    recipient = oblist[0];

    if((recipient->query_wt() != W_SWORD) &&
      (recipient->query_wt() != W_KNIFE))
    {
	notify_fail("That is not a sword or knife.\n");
	return 0;
    }

    actor("You" + adverb + " stroke the blade of", oblist, ".");
    target(adverb + " strokes your blade.", oblist, adverb);
    all2act(adverb + " strokes the blade of", oblist, ".", adverb);
    return 1;
}

public int
uswear_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "furiously" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("You swear" + adverb + " by Plalgus that those attacking "
	  + "the protectorate of Sybaus will be counting holes.\n");
	allbb(" swears" + adverb + " by Plalgus that those attacking "
	  + "the protectorate of Sybaus will be counting holes.");
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You swear" + adverb + " by Plalgus that", oblist, " will be counting holes.");
    all2actbb(" swears" + adverb + " by Plalgus that", oblist,
      " will be counting holes.", adverb);
    targetbb(" swears" + adverb + " by Plalgus that you will be counting holes.",
      oblist, adverb);
    return 1;
}

public int
uteach_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // Check for target's cape

    tp = this_player();
    how = parse_adverb_with_space(arg, "professionally" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }


    recipient = oblist[0];

    if(!sizeof(filter(recipient->query_clothing(-1), &->id("cape"))))
    {
	notify_fail("That person is not wearing a cape.\n");
	return 0;
    }

    actor("You remove your cape," + adverb + " put it in the water and "
      + "show", oblist, " how to properly wash it, and then don it again.");
    target(" removes "
      + tp->query_possessive() + " cape," + adverb + " puts it in the "
      + "water and shows you how to properly wash it, and then "
      + "dons it again.", oblist, adverb);
    all2act(" removes "
      + tp->query_possessive() + " cape," + adverb + " puts it in "
      + "the water and shows", oblist, " how to properly wash it, "
      + "and then dons it again.", adverb);
    return 1;
}

public int
uthink_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "gently" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You tap your temple" + adverb + " with one finger, indicating that someone needs to think harder.\n");
	allbb(" taps "
	  + tp->query_possessive() + " temple" + adverb + " with one finger, indicating that someone needs to think harder.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You tap your temple" + adverb + " with one finger, indicating that", oblist, " needs to think harder.");
    target(" taps "
      + tp->query_possessive() + " temple" + adverb + " with one finger, indicating that you need to think harder.", oblist, adverb);
    all2act(" taps "
      + tp->query_possessive() + " temple" + adverb + " with one finger, indicating that", oblist, " needs to think harder.", adverb);
    return 1;
}

public int
uthroat_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "menacingly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You slide a finger across your throat"
	  + adverb + " in a dark gesture of significance.\n");
	allbb(" slides a finger across "
	  + tp->query_possessive() + " throat" + adverb
	  + " in a dark gesture of significance.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
utremble_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "noticeably" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You tremble" + adverb + " with the force of suppressed emotion.\n");
	allbb(" trembles" + adverb + " with the force of suppressed emotion.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
    return 0;
}

public int
uturn_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "wearily" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You turn" + adverb + " away from those around you; you prefer your own company.\n");
	allbb(" turns" + adverb + " away from those around "
	  + tp->query_objective() + ", becoming sullen and withdrawn.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You turn" + adverb + " from", oblist, ", preferring your own company.");
    target(" turns" + adverb + " from you, becoming sullen and withdrawn.", oblist, adverb);
    all2act(" turns" + adverb + " from", oblist, ", becoming sullen and withdrawn.", adverb);
    return 1;
}

public int
uuseless_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "slightly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You shrug" + adverb + ", not interested in any of your surroundings.\n");
	allbb(" shrugs" + adverb + ", not interested in any of "
	  + tp->query_possessive() + " surroundings.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You shrug" + adverb + ", not interested in anything", oblist, " may say.");
    target(" shrugs" + adverb + ", not interested in anything you may say.", oblist, adverb);
    all2act(" shrugs" + adverb + ", not interested in anything", oblist, " may say.", adverb);
    return 1;
}

public int
uwarn_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // Check to make sure they are in the Union halls

    tp = this_player();
    how = parse_adverb_with_space(arg, "seriously" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You warn", oblist, adverb + " of the dangers of aggressive action inside the Halls of Shadow.");
    targetbb(" warns you" + adverb + " of the dangers of aggressive action inside the Halls of Shadow.", oblist, adverb);
    all2actbb(" warns", oblist, adverb + " of the dangers of aggressive action inside the Halls of Shadow.", adverb);
    return 1;
}

public int
uwear_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    tp = this_player();
    how = parse_adverb_with_space(arg, "swiftly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    if (living(recipient))
    {
	notify_fail("You cannot do that to a living being.\n");
	return 0;
    }

    if(!(recipient->query_slots_setting()))
    {
	notify_fail("That is not an armour or clothing.\n");
	return 0;
    }

    if((tp->query_union_sphere() == SPH_TRAINING) ||
      (tp->query_union_sphere() == SPH_DUTY) ||
      (tp->query_union_sphere() == SPH_ISOLATION))
    {
	actor("You slip" + adverb + " but clumsily into", oblist, ".");
	all2act(" slips" + adverb + " but clumsily into", oblist, ".", adverb);
    }
    else
    {
	actor("You slip" + adverb + " into", oblist, " with the fluency "
	  + "and grace of a true Amlis k'miasil.");
	all2act(" slips" + adverb + " into", oblist, " with a fluent "
	  + "grace you scarcely thought possible.", adverb);
    }

    tp->command("$wear " + OB_NAME(recipient));

    return 1;
}

public int
uwet_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "slowly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You wet your lips" + adverb + ", preparing yourself to speak for quite a while.\n");
	allbb(" wets "
	  + tp->query_possessive() + " lips" + adverb + ", preparing "
	  + tp->query_objective() + "self to speak for quite a while.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
uwill_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "powerfully" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    if (sizeof(oblist) > 1)
    {
	notify_fail("You may only do that to a single target.\n");
	return 0;
    }

    recipient = oblist[0];

    actor("You point your finger at", oblist, adverb + " and call upon "
      + recipient->query_objective() + " to do the will of the Elders.");
    target(" points "
      + tp->query_possessive() + " finger at you" + adverb + " and calls upon you to do the will of the Elders.", oblist, adverb);
    all2act(" points "
      + tp->query_possessive() + " finger at", oblist, adverb + " and calls upon "
      + recipient->query_objective() + " to do the will of the Elders.", adverb);
    return 1;
}

public int
uworthy_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // check for weapon

    tp = this_player();
    how = parse_adverb_with_space(arg, "silently" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }

    tmp = u_describe_weapons(W_SWORD, 1);
    if(!strlen(tmp))
    {
	notify_fail("You need to be wielding a sword.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("You" + adverb + " salute everyone with your " + tmp +
	  " as worthy allies of the Union.\n");
	allbb(adverb + " salutes everyone with "
	  + tp->query_possessive() + " " + tmp +
	  " as worthy allies of with Union.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You salute", oblist, adverb + " with your " + tmp +
      " as a worthy ally of the Union.");
    target(" salutes you" + adverb + " with "+ tp->query_possessive() +" "+
      tmp + " as a worthy ally of the Union.", oblist, adverb);
    all2act(" salutes", oblist, adverb + " with "+ tp->query_possessive() +" "+
      tmp + " as a worthy ally of the Union.", adverb);
    return 1;
}

public int
uwounded_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "sadly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You avert your eyes" + adverb + " from", oblist, ", feeling wounded to the core.");
    target(" averts "
      + pos + " eyes" + adverb + " from you, a dark, wounded look in "
      + pos + " eyes.", oblist, adverb);
    all2act(" averts "
      + pos + " eyes" + adverb + " from", oblist, ", a dark, wounded look in "
      + pos + " eyes.", adverb);
    return 1;
}

