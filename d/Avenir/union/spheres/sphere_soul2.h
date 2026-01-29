/*
 * Revisions:
 * 	Zizuph, June 2021: Remove 0 in text from unknot.
 */
 
public int
udisgust_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "contemptuously" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You look" + adverb + " around yourself at the filth.\n");
	allbb(" looks" + adverb + " around "
	  + tp->query_objective() + "self.", adverb);
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

    actor("You look" + adverb + " at", oblist, ", indicating that "
      + recipient->query_pronoun() + " needs a bath.");
    target(" looks" + adverb + " at you, indicating that you need a bath.", oblist, adverb);
    all2act(" looks" + adverb + " at", oblist, ", indicating that "
      + recipient->query_pronoun() + " needs a bath.", adverb);
    return 1;
}

public int
udown_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // check for weapons

    tp = this_player();
    how = parse_adverb_with_space(arg, "slightly" , 0);
    adverb = how[1];

    if (strlen(how[0]))
    {
	notify_fail(capitalize(query_verb()) + " [how]?\n");
	return 0;
    }

    tmp = u_describe_weapons();
    if(!strlen(tmp))
    {
	notify_fail("You need to be wielding a weapon.\n");
	return 0;
    }

    write("You lower your " + tmp + adverb +
      " in a subtle gesture of peace.\n");
    allbb(" lowers " + tp->query_possessive() + " " + tmp + adverb +
      " in a subtle gesture of peace.", adverb);
    return 1;
}

public int
udust_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // check for hall of beauty

    tp = this_player();
    how = parse_adverb_with_space(arg, "carefully" , 0);
    adverb = how[1];


    if(file_name(ENV(tp)) != (ROOM + "vaults"))
    {
	notify_fail("You can only do that in the vaults.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("You" + adverb + " dust all the items and give them a polish, caring for them as if they were your own children.\n");
	allbb(adverb + " dusts and polishes all the items displayed here.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
uelders_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "carefully" , 0);
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
	write("You whisper" + adverb + " to the shadows, attempting to commune with the Elders.\n");
	all(" whispers" + adverb + " to the shadows, as if to a dark presence nearby.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
uembassy_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb;
    string pos = this_player()->query_possessive();


    // Check for language for varying hand gestures

    tp = this_player();
    how = parse_adverb_with_space(arg, "confidently" , 0);
    adverb = how[1];

    if (!stringp(how[0]))
    {
	write("You" + adverb + " hold up your hand in the "+
	  "Sybarite gesture of embassy.\n");
	allbb(adverb + " holds up "
	  + pos + " hand in the Sybarite gesture of embassy.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You" + adverb + " hold up your hand to", oblist, " in the Sybarite gesture of embassy.");
    target(adverb + " holds up "
      + pos + " hand to you in the Sybarite gesture of embassy.", oblist, adverb);
    all2act(adverb + " holds up "
      + pos + " hand to", oblist, " in the Sybarite gesture of embassy.", adverb);
    return 1;
}

public int
ueverything_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // check for appropriate location

    tp = this_player();
    how = parse_adverb_with_space(arg, "expansively" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You indicate" + adverb
	  + " with a graceful, sweeping gesture that everything "
	  + "in sight is under your protection.\n");
	allbb(" indicates" + adverb + " with a graceful, sweeping "
	  + "gesture that everything in sight is under "
	  + tp->query_possessive() + " protection.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
uexamine_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // check for weapon, auto-appraise

    tp = this_player();
    how = parse_adverb_with_space(arg, "searchingly" , 0);
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

    if (!(recipient->check_weapon()))
    {
	notify_fail("That is not a weapon.\n");
	return 0;
    }

    actor("You examine", oblist, adverb + ", trying to divine its secrets.");
    target(" examines you" + adverb + ", trying to divine its secrets.", oblist, adverb);
    all2act(" examines", oblist, adverb + ", trying to divine its secrets.", adverb);

    tp->command("$appraise " + OB_NAME(recipient)); // now appraise it

    return 1;
}

public int
ufall_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "gracefully" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You fall back" + adverb + " from the onslaught.\n");
	allbb(" falls back" + adverb + " from the onslaught.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You fall back" + adverb + " from the onslaught of", oblist, ".");
    target(" falls back" + adverb + " from the onslaught of you.", oblist, adverb);
    all2act(" falls back" + adverb + " from the onslaught of", oblist, ".", adverb);
    return 1;
}

public int
uflip_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // check for dagger

    tp = this_player();
    how = parse_adverb_with_space(arg, "idly" , 0);
    adverb = how[1];

    tmp = u_describe_weapons(-1, 1);
    if(!strlen(tmp))
    {
	notify_fail("You need to be wielding a weapon.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("You" + adverb + " flip your " + tmp + ", waiting for the action to begin.\n");
	allbb(adverb + " flips "
	  + tp->query_possessive() + " " + tmp + ", waiting for the action to begin.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
ufocus_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "completely" , 0);
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
    actor("You focus" + adverb + " on the wisdom of", oblist, ", trying to learn all you can from it.");
    target(adverb + " focuses on you with great care, seemingly trying to understand something.", oblist, adverb);
    all2act(adverb + " focuses on", oblist, " with great care, seemingly trying to understand something.", adverb);
    return 1;
}

public int
ugaze_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // make target shudder if dis is low

    tp = this_player();
    how = parse_adverb_with_space(arg, "intensely" , 0);
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

    actor("You gaze" + adverb + " into", oblist, "'s eyes, looking into "
      + recipient->query_possessive() + " very soul in search for the truth.");
    target(" gazes" + adverb + " into your eyes, piercing through your very soul, sending a chill down your spine.", oblist, adverb);
    all2act(" gazes" + adverb + " into", oblist, "'s eyes, "
      + tp->query_possessive() + " piercing eyes intense and cold.", adverb);

    return 1;
}

public int
ugift_emote(string arg)
{
    object *oblist, recipient, tp, statue;
    string *how, adverb, tmp;

    // clone a statue and give it to the player

    tp = this_player();
    how = parse_adverb_with_space(arg, "appreciatively" , 0);
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

    if(present(OBJ + "statuette", recipient)) // I added the file name of the object as a name
    {
	notify_fail("That person has already been gifted with one.\n");
	return 0;
    }

    setuid();
    seteuid(getuid());  

    actor("You gift", oblist, adverb + " with a small ebon statuette, a token of the Union's esteem.");
    targetbb(" gifts you" + adverb + " with a small ebon statuette as a token of esteem.", oblist, adverb);
    all2actbb(" gifts", oblist, adverb + " with a small ebon statuette as a token of esteem.", adverb);

    statue = clone_object(OBJ + "statuette");
    statue->move(recipient, 1);

    return 1;
}

public int
uglare_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "searchingly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You glare around yourself" + adverb + ", intent on finding the answer.\n");
	allbb(" glares around "
	  + tp->query_objective() + "self" + adverb + ", intent on finding the answer.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You glare" + adverb + " into the eyes of", oblist, ", intent on learning the answer.");
    target(" glares" + adverb + " into the eyes of you, intent on learning the answer.", oblist, adverb);
    all2act(" glares" + adverb + " into the eyes of", oblist, ", intent on learning the answer.", adverb);
    return 1;
}

public int
uglint_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // check for wielded sword

    tp = this_player();
    how = parse_adverb_with_space(arg, "luminescently" , 0);
    adverb = how[1];

    tmp = u_describe_weapons(W_SWORD);
    if(!strlen(tmp))
    {
	notify_fail("You need to be wielding a sword.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("You raise your " + tmp + " so it catches the light" + adverb
	  + ", casting strands of brilliance all around.\n");
	allbb(" raises "
	  + tp->query_possessive() + " " + tmp + " so it catches the light"
	  + adverb + ", casting strands of brilliance all around.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
uground_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // check for weapon

    tp = this_player();
    how = parse_adverb_with_space(arg, "menacingly" , 0);
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

    tmp = u_describe_weapons();
    if(!strlen(tmp))
    {
	notify_fail("You need to be wielding a weapon.\n");
	return 0;
    }

    actor("You" + adverb + " point at", oblist, " and then at the ground with your " + tmp + ".");
    target(adverb + " points at you and then at the ground with "
      + tp->query_possessive() + " " + tmp + ".", oblist, adverb);
    all2act(" points" + adverb + " at", oblist, " and then at the ground with "
      + tp->query_possessive() + " " + tmp + ".", adverb);
    return 1;
}

public int
uguidance_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "urgently" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You" + adverb + " express your need for guidance.\n");
	all(adverb + " expresses "
	  + tp->query_possessive() + " need for guidance.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You" + adverb + " express your need for the guidance of", oblist, ".");
    targetbb(adverb + " expresses "
      + tp->query_possessive() + " need for your guidance.", oblist, adverb);
    all2actbb(adverb + " expresses "
      + tp->query_possessive() + " need for the guidance of", oblist, ".", adverb);
    return 1;
}

public int
uhear_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "attentively" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You close your eyes briefly and listen for advice from the unseen Elders.\n");
	allbb(" closes "
	  + tp->query_possessive() + " eyes briefly and listens for" + adverb
	  + " to an unseen presence.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
uhips_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "firmly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You place your hands" + adverb + " on your hips.\n");
	allbb(" places "
	  + pos + " hands" + adverb + " on "
	  + pos + " hips.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You place your hands" + adverb + " on your hips before", oblist, ".");
    target(" places "
      + pos + " hands" + adverb + " on "
      + pos + " hips before you.", oblist, adverb);
    all2act(" places "
      + pos + " hands" + adverb + " on "
      + pos + " hips before", oblist, ".", adverb);
    return 1;
}

public int
uintent_emote(string arg)
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
	write("You" + adverb + " cry out your intent to bring great harm to your enemies.\n");
	all(adverb + " cries out "
	  + tp->query_possessive() + " intent to bring great harm to your enemies.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You" + adverb + " cry out your intent to bring great harm to", oblist, ".");
    targetbb(adverb + " cries out "
      + tp->query_possessive() + " intent to bring great harm to you.", oblist, adverb);
    all2actbb(adverb + " cries out "
      + tp->query_possessive() + " intent to bring great harm to", oblist, ".", adverb);
    return 1;
}

public int
ujudge_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "intensly" , 0);
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
	write("You" + adverb + " consider the judgement.\n");
	allbb(adverb + " considers the judgement.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You" + adverb + " consider what judgement you will pass on",
      oblist, ".");
    target(adverb + " considers what judgement will be passed upon on you.", oblist, adverb);
    all2act(adverb + " considers what judgement will be "+
      "passed upon", oblist, ".", adverb);
    return 1;
}

public int
ukata_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // check for outsider and dis and put in weapon description

    tp = this_player();
    how = parse_adverb_with_space(arg, "swiftly" , 0);
    adverb = how[1];

    tmp = u_describe_weapons(-1, 2, 0, W_BOTH);
    if(!strlen(tmp))
    {
	notify_fail("You need to be wielding two weapons.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("You start to move your " + tmp + " in an intricate pattern, so that they weave together" + adverb + ". Light flickers off the weapons and sparkles all around.\n");
	allbb(" starts to move "
	  + tp->query_possessive() + " " + tmp + adverb + " in an intricate pattern, so that they weave together in a blur. Light flickers off the weapons, seeming to surround "
	  + tp->query_objective() + " in a flaming shell.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
ukiss_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // check for cleaned

    tp = this_player();
    how = parse_adverb_with_space(arg, "softly" , 0);
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


    if (living(recipient))
    {
	notify_fail("You cannot do that to a living being.\n");
	return 0;
    }

    if(!(recipient->check_weapon()))
    {
	notify_fail("That is not a weapon.\n");
	return 0;
    }

    if(tp->query_exp_combat() == recipient->query_prop("union_hits"))
    {
	notify_fail("It has not been cleaned since it was last "
	  + "used in battle; you decide not to kiss it.\n");
	return 0;
    }

    actor("You kiss", oblist, adverb +
      " and whisper a word of thanks to Jazur.");
    all2actbb(" kisses", oblist, adverb + " and whispers "
      + "a word of thanks to Jazur.", adverb);

    return 1;
}

public int
uknot_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // Check weapons

    tp = this_player();
    how = parse_adverb_with_space(arg, "solemnly" , 0);
    adverb = how[1];

    tmp = u_describe_weapons(-1, 2, 0, W_BOTH);
    if(!strlen(tmp))
    {
	notify_fail("You need to be wielding two weapons.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("You" + adverb + " tie the Knots of Peace around "+
	  "the hilts and handles of your " + tmp +
	  ", showing your peaceful intentions.\n");
	allbb(adverb + " ties white knots around the hilts and handles of "
	  + tp->query_possessive() + " in the Sybarite ritual of the Knots of Peace.", adverb);

	tp->command("$unwield all"); // unwield any weapons
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
uknowledge_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "slightly" , 0);
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

    actor("You smile" + adverb + " as you study", oblist, " carefully, thinking about the knowledge "
      + recipient->query_pronoun() + " conceals.");
    target(" smiles" + adverb + " as "
      + tp->query_pronoun() + " studies you carefully.", oblist, adverb);
    all2act(" smiles" + adverb + " as "
      + tp->query_pronoun() + " studies", oblist, " carefully.", adverb);
    return 1;
}

public int
ulaugh_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // different message for nonmember

    tp = this_player();
    how = parse_adverb_with_space(arg, "politely" , 0);
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
	write("You laugh" + adverb + " behind a hand raised to conceal your amused smile.\n");
	all(" laughs"+ adverb +" from behind a hand raised to cover "+ 
	  tp->query_possessive() +" mouth.", adverb);
	return 1;
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

    actor("You laugh"+ adverb +" at", oblist, " from behind a hand raised "+
      "to conceal your amused smile.");
    targetbb(" laughs"+ adverb +" at you from behind a hand raised to cover "+ 
      tp->query_possessive() +" mouth.", oblist, adverb);
    all2actbb(" laughs"+ adverb +" at", oblist, " from behind a hand raised to "+ 
      "cover "+ tp->query_possessive() +" mouth.", adverb);
    return 1;
}

public int
ulisten_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // check for elders

    tp = this_player();
    how = parse_adverb_with_space(arg, "patiently" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You listen" + adverb + " to the conversation of your elders.\n");
	allbb(" listens" + adverb + " to the conversation of " 
	  + tp->query_possessive () + " elders.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You listen" + adverb + " to the words of", oblist, ".");
    target(" listens" + adverb + " to the words of you.", oblist, adverb);
    all2act(" listens" + adverb + " to the words of", oblist, ".", adverb);
    return 1;
}

public int
ulong_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "longingly" , 0);
    adverb = how[1];

    if (tmp = tp->query_prop(LIVE_M_MOUTH_BLOCKED))
    {
	if(stringp(tmp))
	    notify_fail(tmp + "\n");
	else
	    notify_fail("You cannot seem to use your mouth.\n");
	return 0;
    }

    if (MEMBER_SPHERE(tp, SPH_ISOLATION))
    {
	if (!stringp(how[0]))
	{
	    write("You show your longing to be united once more with your "+
	      "other selves.\n");
	    allbb(" shows "+ tp->query_possessive() + " longing to be united "+
	      "once more with "+ tp->query_possessive() + " other selves.", adverb);
	    return 1;
	}

	oblist = parse_this(how[0], "[to] [at] [the] %l");

	if (!sizeof(oblist))
	{
	    notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	    return 0;
	}

	actor("You give", oblist, " a yearning look, expressing your "+
	  "longing to be united once more with your other selves.");
	target(" give you a yearning look, expressing "+ tp->query_possessive() +
	  " longing to be united once more with "+ tp->query_possessive() +
	  " other selves.", oblist, adverb);
	all2act(" gives", oblist, " a look full of longing.", adverb);
	return 1;
    }

    if (!stringp(how[0]))
    {
	write("You show your longing to become One with the shadows and flame, "+
	  "embraced as a Warrior of the Shadow Union.\n");
	allbb(" shows "+ tp->query_possessive() + " longing to become one "+
	  "with the shadows and flame.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You give", oblist, " a yearning look, expressing your "+
      "longing to become One with the shadows and flame, embraced "+
      "as a Warrior of the Shadow Union.");
    target(" gives you a yearning look, expressing "+ tp->query_possessive() +
      " longing to become one with the shadows and flame, embraced as a "+
      "Warrior of the Shadow Union.", oblist, adverb);
    all2act(" gives", oblist, " a look full of longing.", adverb);
    return 1;

}

public int
ulook_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "subtly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You" + adverb + " look around for informative signs and meanings.\n");
	allbb(adverb + " looks around for informative signs and meanings.", adverb);


	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
ulust_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "lustfully" , 0);
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

    actor("You smile" + adverb + " at the beauty of", oblist, ".");
    target(" smile" + adverb + " at your beauty.", oblist, adverb);
    all2act(" smile" + adverb + " at the beauty of", oblist, ".", adverb);
    return 1;
}

public int
unervous_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "quickly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You glance" + adverb + " around, nervous at the presence of Outlanders.\n");
	allbb(" glances" + adverb + " around.", adverb);
	return 1;
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

    actor("You glance" + adverb + " at", oblist, ", somewhat unnerved at "
      + recipient->query_possessive() + " presence.");
    target(" glances" + adverb + " at you, apparently somewhat bothered "
      +"by your presence.", oblist, adverb);
    all2act(" glances" + adverb + " at", oblist, ", apparently somewhat "
      +"bothered by "+ recipient->query_possessive() + " presence.", adverb);
    return 1;
}

public int
unod_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "sagely" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You nod" + adverb + " at the wise words spoken here.\n");
	allbb(" nods" + adverb + " at the wise words spoken here.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You nod" + adverb + " at the wise words of", oblist, ".");
    target(" nods" + adverb + " at your wise words.", oblist, adverb);
    all2act(" nods" + adverb + " at the wise words of", oblist, ".", adverb);
    return 1;
}

public int
unote_emote(string arg)
{
    object *oblist, tp, scroll;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "secretly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You" + adverb + " take note of that.\n");
	allbb(" pauses and thinks for a moment.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You" + adverb + " take note of what", oblist, " says.");
    target(" stares at you and seems to be thinking on something.", oblist, adverb);
    all2act(" stares at", oblist, " and seems to be thinking on something.", adverb);

    return 1;
}


public int
uoath_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "loudly" , 0);
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
	write("You swear" + adverb + " with the fervour of your devotion to Jazur and the Union.\n");
	all(" swears" + adverb + " with the fervour of "
	  + tp->query_possessive() + " devotion.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You swear" + adverb + " that", oblist, " will pay dearly.");
    targetbb(" swears" + adverb + " that you will pay dearly.", oblist, adverb);
    all2actbb(" swears" + adverb + " that", oblist, " will pay dearly.", adverb);
    return 1;
}

public int
uoffended_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "terribly" , 0);
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

    actor("You are" + adverb + " offended by", oblist, ", but strive not to show it.");
    target(" has not reacted, and yet you have the feeling that you have" + adverb + " offended "
      + tp->query_objective() + ".", oblist, adverb);
    return 1;
}

public int
uoutrage_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "barely" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You" + adverb + " contain your outrage.\n");
	allbb(" contorts "
	  + tp->query_possessive() + " face briefly, as if" + adverb + " containing an outburst.", adverb);
	return 1;
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

    actor("You" + adverb + " contain your outrage at",
      oblist, ".");
    target(" contorts "
      + tp->query_possessive() + " face briefly, as if" + adverb
      + " containing an outburst towards you!", oblist, adverb);
    all2act(" contorts "
      + tp->query_possessive() + " face briefly, as if" + adverb
      + " containing an outburst towards", oblist, "!", adverb);
    return 1;
}

public int
upatient_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "calmly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You fold your hands before you and wait" + adverb + ".\n");
	allbb(" folds "
	  + tp->query_possessive() + " hands before "
	  + tp->query_objective() + " and waits" + adverb + ".", adverb);
	return 1;
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

    actor("You fold your hands in front of you and wait" + adverb + " for", oblist, "'s next action.");
    target(" folds "
      + tp->query_possessive() + " hands in front of "
      + tp->query_objective() + " and waits" + adverb + " for your next action.", oblist, adverb);
    all2act(" folds "
      + tp->query_possessive() + " hands in front of "
      + tp->query_objective() + " and waits" + adverb + " for", oblist, "'s next action.", adverb);
    return 1;
}

public int
upeace_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb;

    // Check for language for varying hand gestures

    tp = this_player();
    how = parse_adverb_with_space(arg, "confidently" , 0);
    adverb = how[1];

    if (!stringp(how[0]))
    {
	write("You" + adverb + " hold up your hand in the Sybarite "+
	  "gesture of peace.\n");
	allbb(adverb + " holds up "
	  + tp->query_possessive() + " hand in the Sybarite gesture of peace.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %l");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You" + adverb + " hold up your hand to", oblist,
      " in the Sybarite gesture of peace.");
    target(adverb + " holds up " + tp->query_possessive() +
      " hand to you in the Sybarite gesture of peace.", oblist, adverb);
    all2act(adverb + " holds up " +
      tp->query_possessive() + " hand to", oblist,
      " in the Sybarite gesture of peace.", adverb);
    return 1;
}

public int
upenance_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    tp = this_player();
    how = parse_adverb_with_space(arg, "penitently" , 0);
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

    tmp = "";

    if(recipient->query_union_level())
	tmp = "Tornu, I have failed you. "
	+ "Is there some way I can do penance, to regain my honour?";

    actor("You bow your head" + adverb + " towards", oblist, ".");
    targetbb(" bows "
      + tp->query_possessive() + " head" + adverb + " towards you.", oblist, adverb);
    all2actbb(" bows "
      + tp->query_possessive() + " head" + adverb + " towards", oblist, ".", adverb);

    if(strlen(tmp))
	tp->command("$usay " + tmp);

    return 1;
}

public int
upierce_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "disappointedly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You freeze and raise your piercing gaze" + adverb + " all around.\n");
	allbb(" freezes and raises "
	  + tp->query_possessive() + " piercing gaze" + adverb + " all around.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You freeze and raise your piercing gaze" + adverb + " at", oblist, ".");
    target(" freezes and raises "
      + tp->query_possessive() + " piercing gaze" + adverb + " at you.", oblist, adverb);
    all2act(" freezes and raises "
      + tp->query_possessive() + " piercing gaze" + adverb + " at", oblist, ".", adverb);
    return 1;
}

// called as a result of the VBFC when the protectee dies, to
// let the player know that it was killed.
int
u_protectee_died()
{
    object caller, player;
    string who;
    int    i;

    // get the last living caller
    caller = previous_object(0);    
    while((!living(caller)) && objectp(caller))
	caller = previous_object(--i);

    who = caller->query_prop("_union_s_protector");

    // make sure they are dying...
    if(living(caller) && (caller->query_hp() <= 0))
    {
	player = find_player(who);
	player->catch_tell("You sense you have "
	  + "broken your solemn pledge of protection. You "
	  + "feel a great loss of pride.\n");
	player->adjust_union_virtue(US_PRIDE, 50);
    }

    return 0;
}

public int
upledge_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "solemnly" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You" + adverb + " pledge your life in defence of Sybarus.\n");
	all(adverb + " pledges "
	  + tp->query_possessive() + " life in defence of Sybarus.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("You" + adverb + " pledge your life in defence of", oblist, ".");
    targetbb(adverb + " pledges "
      + tp->query_possessive() + " life in defence of you.", oblist, adverb);
    all2actbb(adverb + " pledges "
      + tp->query_possessive() + " life in defence of", oblist, ".", adverb);


    // when they die, tell the protector and decrease their pride
    // significantly.

    // don't mess with them if they already have the prop set
    oblist = filter(oblist, not @ &->query_prop(LIVE_I_NO_CORPSE));
    oblist->add_prop("_union_s_protector", tp->query_real_name());
    oblist->add_prop(LIVE_I_NO_CORPSE, u_protectee_died);

    return 1;
}



public int
upolish_emote(string arg)
{
    object *oblist, recipient, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "gently" , 0);
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
    actor("You" + adverb + " polish", oblist, " with loving care.");
    target(adverb + " polishes you with loving care.", oblist, adverb);
    all2act(adverb + " polishes", oblist, " with loving care.", adverb);
    return 1;
}

public int
upray_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

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


    if (!stringp(how[0]))
    {
	write("You pray" + adverb + " to Jazur.\n");
	all(" closes "
	  + tp->query_possessive() + " eyes and whispers" + adverb + " to "
	  + tp->query_objective() + "self.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
uflare_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp, *descs;
    string pos = this_player()->query_possessive();


    // check for bandeleria

    tp = this_player();
    how = parse_adverb_with_space(arg, "dangerously" , 0);
    adverb = how[1];

    descs = filter(all_inventory(tp), &->id("bandeleria"))->short();

    if(!sizeof(descs))
    {
	notify_fail("You must be wearing a bandeleria.\n");
	return 0;
    }

    if (!stringp(how[0]))
    {
	write("Your eyes flare" + adverb + " as your fingers "
	  + "play with deceptive idleness across your "+ 
	  COMPOSITE_WORDS(descs) +".\n");
	allbb("'s eyes flare"+ adverb +" as "+ tp->query_pronoun() +" runs "+
	  pos +" fingers along "+ pos +" "+ COMPOSITE_WORDS(descs) + 
	  " with deceptive idleness.", adverb);
	return 1;
    }

    oblist = parse_this(how[0], "[to] [at] [the] %i");

    if (!sizeof(oblist))
    {
	notify_fail(capitalize(query_verb()) + " [how] [who/what]?\n");
	return 0;
    }

    actor("Your eyes flare" + adverb + " at", oblist, " as your fingers "
      + "play with deceptive idleness across your "+ 
      COMPOSITE_WORDS(descs) +".");
    all2act(" runs "+ pos +" fingers along "+ pos +" "+ COMPOSITE_WORDS(descs) + 
      " while looking at", oblist, " with eyes that have flared"+ adverb +".",
      adverb);
    target("'s eyes flare "+ adverb +" as "+ tp->query_pronoun() +" looks at "+
      "you while running "+ pos +" fingers along "+ pos +" "+ COMPOSITE_WORDS(descs) + 
      ".", oblist, adverb);
    return 1;
}

public int
uquestion_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // check for DIS, compelled to tell the truth

    tp = this_player();
    how = parse_adverb_with_space(arg, "superiorly" , 0);
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

    actor("You stand tall and proud, remembering your position in this world, while asking", oblist, ": Are you sure that what you speak of is the truth?");
    targetbb(" stands tall and proud and asks you: Are you sure that what you speak of is the truth?", oblist, adverb);
    all2actbb(" stands tall and proud and asks", oblist, ": Are you sure that what you speak of is the truth?", adverb);
    return 1;
}

public int
urage_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;

    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "slowly" , 0);
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
	write("You" + adverb + " close your eyes and utter a low, primal moan of pure rage.\n");
	all(adverb + " closes "
	  + tp->query_possessive() + " eyes and utters a low, primal moan of pure rage.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

public int
uraise_emote(string arg)
{
    object *oblist, tp;
    string *how, adverb, tmp;
    string pos = this_player()->query_possessive();


    // true

    tp = this_player();
    how = parse_adverb_with_space(arg, "gloriously" , 0);
    adverb = how[1];


    if (!stringp(how[0]))
    {
	write("You" + adverb + " lift your hands above your head, palms "
	  + "outward, and drink in the beauty of your surroundings.\n");
	allbb(adverb + " lifts "
	  + pos + " hands above "
	  + pos + " head, palms outward, and drinks in the beauty of "
	  + pos + " surroundings.", adverb);
	return 1;
    }

    notify_fail(capitalize(query_verb()) + " [how]?\n");
    return 0;
}

