
/*
* sol_emotes2.h
* 
* This file contains the emotes/feelings of the Solamnic Knights
* 
* kP - kZ
* 
* Grace, July 1994 new emotes added Nov 1995 by Grace
* 
*/

/**************************** kplan ******************************/
/* Added by Morrigan, 5/4/97 */
int kplan(string str)
{
    int i, pri = present("pal_med", TP)->query_primary();
    object *weapons = TP->query_weapon(-1), weapon;
    string tmp;

    NF("Kplan how?\n");
    if (str)
	return 0;

    if (!sizeof(weapons))
	tmp = "finger";

    if (pri == 0 && TP->query_weapon(W_RIGHT))
	weapon = TP->query_weapon(W_RIGHT);
    else if (pri == 1 && TP->query_weapon(W_LEFT))
	weapon = TP->query_weapon(W_LEFT);
    else if (!tmp)
	weapon = weapons[0];

    if (!tmp || tmp == "")
	tmp = weapon->short();

    if (weapon->query_dt() == W_BLUDGEON)
	tmp = "finger";

    write("With your "+tmp+", you draw a map of the battlefield "+
      "on the ground, explaining how things took place.\n");
    say("With "+POSSESSIVE(TP)+" "+tmp+", "+QTNAME(TP)+" draws "+
      "a map of a battle on the ground, explaining what happened.\n");
    return 1;
}


/********************* pledge ***********************************************/
varargs int
pledge(string str)
{
    NF("If you want to pledge your blade to the cause of Paladine\n" +
      "use no argument.\n");
    if (str)
	return 0;

    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 1000)
	TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 1000);

    write("You pledge anew your blade to the cause of Paladine.\n");
    all(" pledges anew " + POSSESSIVE(TP) + " blade to the cause of Paladine.");
    return 1;
}

/********************** kpraise **********************************/

int
kpraise(string str)
{
    if (!strlen(str)) {
	write("You try to praise, but don't have the words.\n " +
	  "You might try using a string.\n");
	return 1;
    }
    write("You praise " + str + ".\n");
    all(" praises " + str + ".\n");
    return 1;
}


/*********************** kpray ************************************/

int
kpray(string str)
{
    string          patron;
    if (str && str != "patron" && str != "to patron") {
	notify_fail("Kpray to who? Or try without a string.\n");
	return 0;
    }
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 2000)
	TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 2000);
    if (str == "patron" || str == "to patron") {
	switch (TP->query_knight_level()) {
	case 3:
	    patron = "Habbakuk";
	    break;
	case 4:
	    patron = "Kiri-Jolith";
	    break;
	default:
	    patron = "Paladine";
	}
	write("You stand silent for a moment, offering up a prayer to " +
	  patron + ". You briefly feel the presence of " + patron +
	  " and feel strengthened and prepared for whatever might " +
	  "lie ahead.\n");
	all(" folds " + POSSESSIVE(TP) + " hands, and, lowering " +
	  POSSESSIVE(TP) + " head, stands silent for a moment.");
	return 1;
    }
    write("You stand silent for a moment, preparing yourself for " +
      "battle by offering up a prayer to Paladine.\n");
    all(" stands silent for a moment, preparing for the battle ahead.");
    return 1;
}


/********************* krolead **********************************************/
/* Suggested by Teth, added by Morrigan. 10/6/96                            */
int
can_join(object member, object me)
{
    if (!member || (member && !present(member, environment(me))))
	return 0;

    if (!CAN_SEE(me, member))
	return 0;

    if (me->query_leader())
	return 0;

    if ((!member->query_met(me)) || (!me->query_met(member)))
	return 0;

    if (member == me)
	return 0;

    me->team_invite(member);
    member->catch_msg(QCTNAME(me)+" invites you to join "+POSSESSIVE(me)+
      " team.\n");
    return 1;
}

int
krolead(string str)
{

    int i;
    object *oblist;
    object me = TP;

    if (TP->query_knight_level() != 5) {
	write("You are not a Knight of the Rose.\n");
	return 1;
    }
    if (!str) {
	write("You nobly volunteer to lead the team, assuring everyone " +
	  "that no harm will befall them while they are under your " +
	  "protection.\n");
	all(" nobly volunteers to lead the team, assuring everyone that " +
	  "no harm will befall them while they are under " +
	  TP->query_possessive() + " protection.");
	return 1;
    }
    oblist = parse_this(str, "[before] [the] %l");
    oblist -= ({this_player});

    for (i = 0; i < sizeof(oblist); i++)
	if (!find_player(oblist[i]->query_real_name()))
	    oblist -= ({ oblist[i] });

    if ((!strlen(str)) || (!sizeof(oblist))) {
	notify_fail("Volunteer to lead whom?\n");
	return 0;
    }
    if (sizeof(oblist) == 1)
	str = (string) oblist[0]->query_objective();
    else
	str = "them";


    actor("You nobly volunteer to lead", oblist, ", assuring " +
      "that no harm will befall " + str + " while under your " +
      "protection.");
    targetbb(" nobly volunteers to lead you, assuring that no " +
      "harm will befall you while under " + TP->query_possessive() +
      " protection.", oblist);
    for (i=0; i < sizeof(oblist); i++)
	can_join(oblist[i], me);
    all2actbb(" nobly volunteers to lead", oblist, ", assuring" +
      " safety while under " + TP->query_possessive() + " protection.");
    return 1;
}


/********************* krosage **********************************************/
/* Suggested by Teth, added by Morrigan. 10/6/96                            */
int
krosage(string str)
{

    object         *oblist;

    if (TP->query_knight_level() != 5) {
	write("You are not a Knight of the Rose.\n");
	return 1;
    }
    if (!str) {
	write("You nod your head sagely, your years as a Knight showing " +
	  "in the weight of your pondering.\n");
	all(" nods " + TP->query_possessive() + " head sagely, " +
	  TP->query_possessive() + " years as a Knight showing in the weight " +
	  "of " + TP->query_possessive() + " pondering.");
	return 1;
    }
    oblist = parse_this(str, "[before] [the] %l");
    oblist -= ({this_player});

    if ((!strlen(str)) || (!sizeof(oblist))) {
	notify_fail("Nod sagely at whom?\n");
	return 0;
    }
    actor("You nod your head sagely at", oblist, ", your years as a Knight " +
      "showing in the weight of your pondering.");
    targetbb(" nods sagely at you, " + TP->query_possessive() + " years as a " +
      "Knight showing in the weight of " + TP->query_possessive() +
      " pondering.", oblist);
    all2actbb(" nods sagely at", oblist, ", " + TP->query_possessive() + " years " +
      "as a Knight showing in the weight of " + TP->query_possessive() +
      " pondering.");
    return 1;
}


/********************* salute ***********************************************/
int
salute(string str)
{
    object         *ob, *obblack = ({}), *obnoknight = ({}), *obequal = ({}), *obsuperior = ({}), *obinferior = ({}), *obmix;
    int             level, sublevel, oblevel, obsub, is_wiz, i;

    NF("Salute who?\n");
    if (!str) {
	write("You give a nice crisp salute.\n");
	all(" gives a very impressive crisp salute.");
	return 1;
    }
    if (str == L(TP->query_name()) || str == "me" || str == "myself") {
	write("You salute yourself, what a wonderful person you are!\n");
	all(" salutes himself, he must be feeling proud of himself.");
	return 1;
    }
    ob = parse_this(str, "[the] %l");
    if (!sizeof(ob))
	return 0;
    level = TP->query_knight_level();
    sublevel = TP->query_knight_sublevel();
    for (i = 0; i < sizeof(ob); i++) {
	oblevel = ob[i]->query_knight_level();
	obsub = ob[i]->query_knight_sublevel();
	is_wiz = ob[i]->query_wiz_level();
	if (oblevel == 1)
	    obblack += ({ob[i]});
	else if (!is_wiz && oblevel == 0)
	    obnoknight += ({ob[i]});
	else if (is_wiz || (obsub > sublevel && level != 2))
	    obsuperior += ({ob[i]});
	else if (obsub == sublevel || (level == 2 && oblevel == 2))
	    obequal += ({ob[i]});
	else
	    obinferior += ({ob[i]});
    }
    if (obblack && sizeof(obblack))
	actor("You find", obblack, " not deserving of any acknowledgement!");
    if (obinferior && sizeof(obinferior)) {
	actor("You give", obinferior, " a respectful salute.");
	target(" gives you a respectful salute.", obinferior);
	all2act(" salutes", obinferior, " respectfully.");
    }
    if (obequal && sizeof(obequal)) {
	actor("You give", obequal, " a salute of comradeship.");
	target(" gives you a salute of comradeship.", obequal);
    }
    obmix = obequal + obsuperior;
    if (obmix && sizeof(obmix))
	all2act(" salutes", obmix);
    if (obsuperior && sizeof(obsuperior)) {
	actor("You acknowledge", obsuperior, " with a salute.");
	target(" gives you a salute of acknowledgement.", obsuperior);
    }
    if (obnoknight && sizeof(obnoknight)) {
	target(" gives you a military style salute.", obnoknight);
	actor("You give a crisp military salute to", obnoknight);
	all2act(" gives", obnoknight, " a crisp military salute.");
    }
    return 1;
}


/*************** ksalute2 ******************************************/
/* Added 10/6/96 by Morrigan.                                      */
int
ksalute2(string str)
{
    object         *oblist;
    object         *wielded_weapons;
    object          weapon;
    int             i;

    wielded_weapons = TP->query_weapon(-1);

    if (sizeof(wielded_weapons)) {

	for (i = 0; i < sizeof(wielded_weapons); i++) {
	    weapon = wielded_weapons[i];

	}
    }
    if (!weapon) {
	write("You cannot salute someone with your weapon if you " +
	  "do not have a weapon wielded.\n");
	return 1;
    }
    if (!str) {
	write("You raise your " + weapon->short() + " aloft, giving " +
	  "everyone a Knightly salute.\n");
	all(" raises " + TP->query_possessive() + " " + weapon->short() +
	  " aloft and gives everyone an honourable salute.");
	return 1;
    }
    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist)) {
	notify_fail("Salute whom with your weapon?\n");
	return 0;
    }
    target(" raises " + TP->query_possessive() + " " + weapon->short() +
      " aloft and salutes you honourably.", oblist);
    actor("You raise your " + weapon->short() + " aloft, and give", oblist,
      " a Knightly salute.");
    all2act(" raises " + TP->query_possessive() + " " + weapon->short() +
      " aloft, and honourably salutes", oblist, ".");
    return 1;
}


/********************* kseloyal *********************************************/
/* Added 10/6/96 by Morrigan, created by Teth.                              */
int
kseloyal(string str)
{
    if (TP->query_knight_level() != 2 ||
      TP->query_guild_name_lay() != "Sentries of Solamnia") {
	write("You are not a Sentry of Solamnia.\n");
	return 1;
    }
    str = TP->query_guild_name_occ();
    if (str == "Gondorian Rangers Guild")
	str = "Rangers of the Westlands";
    if (str == "Calian warrior's guild") {
	write("You pledge your loyalty to Caliana and the Knights of " +
	  "Solamnia.\n");
	all(" pledges " + TP->query_possessive() + " loyalty to Caliana and " +
	  "the Knights of Solamnia.");
	return 1;
    }
    if (str == 0) {
	write("You pledge your loyalty to the Knights of Solamnia.\n");
	all(" pledges " + TP->query_possessive() + " loyalty to the Knights " +
	  "of Solamnia.");
	return 1;
    }
    write("You pledge your loyalty to the " + str + " and the Knights " +
      "of Solamnia.\n");
    all(" pledges " + TP->query_possessive() + " loyalty to the " + str +
      " and the Knights of Solamnia.");
    return 1;
}


/********************* ksedanger ********************************************/
/* Added 10/6/96 by Morrigan, created by Teth.                              */
int
ksedanger(string str)
{
    write("You narrow your eyes, looking intently into the distance for " +
      "signs of danger.\n");
    all(" narrows " + TP->query_possessive() + " eyes, looking intently into " +
      "the distance for signs of danger.");
    return 1;
}


/********************* ksefirm  *********************************************/
/* Added 10/6/96 by Morrigan, created by Teth.                              */
int
ksefirm(string str)
{
    write("You step firmly into place, intending to stand your ground.\n");
    all(" steps firmly into place. It appears that no force on Krynn " +
      "would be able to move "+TP->query_objective()+" if "+
      TP->query_pronoun()+" didn't want "+
      "to leave.");
    return 1;
}


/********************* sing *************************************************/
int
sing(string str)
{
    NF("Sing what?\n");
    if (str)
	return 0;
    write("You sing an ancient song of war.\n");
    all(" sings an ancient song of war.\nYou get tears in " +
      "your eyes.");
    return 1;
}


/********************** ks (knight say) ******************************
* This would allow Knights to have (mostly) private discussions in
* rooms occupied by non-knights, w/o having to whisper to each other.
*
* made it a little easier to listen than to speak.   ~Aridor
*/
int
ks(string msg)
{
    object         *oblist;
    int             i;

    if (TP->query_skill(SS_LANGUAGE) < 22) {
	NF("Speaking the battle-tongue of the Knighthood " +
	  "requires more training of the language skill.\n");
	return 0;
    }
    if (!strlen(msg)) {
	NF("Say _what_ in the Knights' battle-tongue?\n");
	return 0;
    }
    /* if (TP->query_get_echo()) */
    if (TP->query_option(OPT_ECHO))
	write("In old Solamnian, you utter: " + msg + "\n");
    else
	write("Ok.\n");

    oblist = all_inventory(environment(TP));
    for (i = 0; i < sizeof(oblist); i++) {
	if ((living(oblist[i]) && oblist[i] != TP)) {
	    if (((MEMBER(oblist[i]) && oblist[i]->query_skill(SS_LANGUAGE) > 17) ||
		(LAYMAN(oblist[i]) && oblist[i]->query_skill(SS_LANGUAGE) > 19) ||
		(oblist[i]->query_skill(SS_LANGUAGE) > 70)) ||
	      oblist[i]->query_wiz_level())
		/* some lay and occ guilds train language to 75 and 100 */
//  oblist[i]->catch_msg(QCTNAME(TP) + " utters in old Solamnian: "+
//                  break_string(msg + "\n", 70));

         oblist[i]->catch_msg(QCTNAME(TP) + " utters in old Solamnian: "
            + msg + "\n");
	    else
		oblist[i]->catch_msg(QCTNAME(TP) +
		  " utters something in the Solamnian language.\n");
	}
    }
    return 1;
}


/********************* ksmooth *****************************************/

int
ksmooth(string str)
{
    if (str) {
	if (str == "h") {
	    write("You run a hand through your tangled hair, " +
	      "smoothing it absentmindedly.\n");
	    all(" runs a hand through the length of " +
	      TP->query_possessive() + " tangled hair, " +
	      "smoothing it absentmindedly.");
	    return 1;
	}
	if (str == "m") {
	    write("You run your fingers over your grand moustache, " +
	      "smoothing it thoughtfully.\n");
	    all(" runs " + TP->query_possessive() + " fingers over " +
	      TP->query_possessive() + " grand moustache, smoothing " +
	      "it thoughtfully.");
	    return 1;
	}
	notify_fail("Ksmooth what?\n");
	return 0;
    }
    if (TP->query_gender() == 1) {
	write("You run a hand through your tangled hair, " +
	  "smoothing it absentmindedly.\n");
	all(" runs a hand through the length of her tangled hair, " +
	  "smoothing it absentmindedly.");
    } else {
	write("You run your fingers over your grand moustache, " +
	  "smoothing it thoughtfully.\n");
	all(" runs his fingers over his grand moustache, smoothing " +
	  "it thoughtfully.");
    }
    return 1;
}


/************************ ksomber ***********************************/
/* Added 10/6/96 by Morrigan, suggested by Croft                    */
int
ksomber(string str)
{
    NF("Express somber feelings over what?\n");
    if (str)
	return 0;
    write("Your thoughts drift over the past, battles fought, and " +
      "friends lost.\n");
    all("'s expression grows somber as " + TP->query_possessive() +
      " thoughts linger on battles fought, and friends lost.");
    return 1;
}


/************************ kslap *************************************/
/* Modified by Morrigan and Igneous on 10/5/96 to take into account */
/* whether or not the Knight is wearing gauntlets.                  */
int
kslap(string str)
{
    object         *oblist;
    object         *worn_armours;
    object          gauntlets;
    int             i;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist)) {
	notify_fail("Knight slap whom?\n");
	return 0;
    }
    worn_armours = TP->query_armour(-1);

    if (sizeof(worn_armours)) {

	for (i = 0; i < sizeof(worn_armours); i++) {
	    if (worn_armours[i]->query_at() == A_HANDS ||
	      worn_armours[i]->query_at() == A_R_HAND ||
	      worn_armours[i]->query_at() == A_L_HAND)
		gauntlets = worn_armours[i];

	}
    }
    if (!gauntlets) {
	target(" slaps you hard across the face with the back of " +
	  TP->query_possessive() + " hand. OUCH!", oblist);
	actor("You slap", oblist, " hard across the face with the " +
	  "back of your hand.");
	all2act(" slaps", oblist, " hard across the face with the " +
	  "back of " + TP->query_possessive() + " hand.");
	return 1;
    }
    target(" tightens a fist in " + TP->query_possessive() + " " +
      gauntlets->short() + ", then slaps you " + "hard across " +
      "the face with that hand.  OUCH!", oblist);
    actor("You tighten a fist in your " + gauntlets->short() + ", " +
      "then slap", oblist, " hard across the face with that " +
      "hand.");
    all2act(" tightens a fist in " + TP->query_possessive() + " " +
      gauntlets->short() + ", then slaps", oblist, " hard across " +
      "the face with that hand.");
    return 1;
}


/********************* ksqaspire ********************************************/
/* Added 10/6/96 by Morrigan, created by Teth.                              */
int
ksqaspire(string str)
{
    if (TP->query_knight_level() != 2 ||
      TP->query_guild_name_occ() != "Solamnian Knights") {
	write("You are not a Squire of Solamnia.\n");
	return 1;
    }
    write("You eagerly attend your duties as a squire, so that you might " +
      "realize your dream of becoming a Knight of Solamnia.\n");
    all(" eagerly attends to " + TP->query_possessive() + " squire duties, " +
      TP->query_possessive() + " aspiration to become a Knight of Solamnia " +
      "obvious on " + TP->query_possessive() + " face.");
    return 1;
}


/********************* ksqadmire ****************************************/
/* Suggested by Teth, added by Morrigan. 10/6/96                        */
int
ksqadmire(string str)
{
    object         *oblist;

    if (TP->query_knight_level() != 2 ||
      TP->query_guild_name_occ() != "Solamnian Knights") {
	write("You are not a Squire of Solamnia.\n");
	return 1;
    }
    if (!strlen(str)) {
	notify_fail("Admire which Knight?\n");
	return 0;
    }
    oblist = parse_this(str, "[to] [the] %l");
    if (!sizeof(oblist) > 1) {
	write("You may only admire one Knight at a time.\n");
	return 1;
    }
    if (oblist[0]->query_knight_level() <= 2) {
	write("That person is not a Knight.\n");
	return 1;
    }
    str = oblist[0]->query_objective();

    actor("You declare your admiration of", oblist, ", voicing your " +
      "wish to become like " + oblist[0]->query_objective() + " some" +
      " day.");
    target(" declares " + TP->query_possessive() + " admiration of " +
      "you, voicing " + TP->query_possessive() +
      " wish to become like you some day.", oblist);
    all2act(" declares " + TP->query_possessive() + " admiration of", oblist,
      ", voicing " + TP->query_possessive() + " wish to become like " +
      str + " some day.");
    return 1;
}

/****************** ksqcrown *****************************************/
/* Suggested by Teth, added by Morrigan. 10/7/96                     */
int
ksqcrown(string str)
{
    if (TP->query_knight_level() != 2 ||
      TP->query_guild_name_occ() != "Solamnian Knights") {
	write("You are not a Squire of Solamnia.\n");
	return 1;
    }
    write("You sigh wistfully, your thoughts on the Order of the Crown.\n");
    all(" sighs wistfully, " + TP->query_possessive() + " thoughts on the " +
      "Order of the Crown.");
    return 1;
}


/********************* ksqnod ****************************************/
/* Suggested by Teth, added by Morrigan. 10/6/96                     */
int
ksqnod(string str)
{
    object         *oblist;

    if (TP->query_knight_level() != 2) {
	write("You are neither a Squire, nor a Sentry.\n");
	return 1;
    }
    if (!strlen(str)) {
	notify_fail("Nod at whom in obedience?\n");
	return 0;
    }
    oblist = parse_this(str, "[to] [the] %l");

    if (!sizeof(oblist) > 1) {
	write("You cannot nod at more than one person.\n");
	return 1;
    }
    if (oblist[0]->query_knight_level() <= 2) {
	write("That person is not a Knight.\n");
	return 1;
    }
    actor("You nod in obedience at", oblist, "'s suggestion.");
    target(" nods in obedience at your suggestion.", oblist);
    all2act(" nods in obedience at", oblist, "'s suggestion.");
    return 1;
}


/********************** kstern ****************************************/
int
kstern(string str)
{
    object *oblist;
    string temp;

    if (!str)
    {
	write("Your face hardens into a stern mask.\n");
	all("'s eyes narrow and "+POSSESSIVE(TP)+" face hardens into a stern "+
	  "mask without emotion.");
	return 1;
    }

    oblist = parse_this(str, "[to] / [before] [the] %l");
    if (!sizeof(oblist))
	return 0;

    if (sizeof(oblist) == 1)
	temp = oblist[0]->query_objective();
    else
	temp = "them";

    actor("Narrowing your eyes at", oblist, ", you fix "+temp+
      " with a stern glance.");
    target(" narrows "+POSSESSIVE(TP)+" eyes at you, fixing you with "+
      "a stern glance.", oblist);
    all2act(" narrows "+POSSESSIVE(TP)+" eyes at", oblist, ", fixing "+
      temp+" with a stern glance.");
    return 1;
}


/********************* kstudy *****************************************/
int
kstudy(string str)
{
    object         *oblist, *oblp = ({}), *obls = ({});
    int             i, dis = TP->query_stat(SS_DIS);

    if (!strlen(str)) {
	write("You study your surroundings intently.\n");
	all(" studies " + TP->query_possessive() + " surroundings " +
	  "intently.");
	return 1;
    }
    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist)) {
	notify_fail("Study whom?\n");
	return 0;
    }
    for (i = 0; i < sizeof(oblist); i++) {
	if (oblist[i]->query_stat(SS_DIS) - 5 + random(10) > dis)
	    oblp += ({oblist[i]});
	else
	    obls += ({oblist[i]});
    }
    if (obls && sizeof(obls)) {
	target(" studies you intently, taking your measure.\n" +
	  "You squirm uncomfortably under " + TP->query_possessive() +
	  " stern, evaluating gaze.", obls);
	actor("You study", obls, " intently, taking " +
	  (sizeof(obls) > 1 ? "their" : obls[0]->query_possessive()) +
	  " measure.\n" +
	  C(sizeof(obls) > 1 ? "they squirm" : obls[0]->query_pronoun() + " squirms") +
	  " uncomfortably under your regard.");
	all2act(" studies", oblist, " intently, taking " +
	  (sizeof(obls) > 1 ? "their" : obls[0]->query_possessive()) +
	  " measure.\nYou can see " +
	  (sizeof(obls) > 1 ? "them" : obls[0]->query_possessive()) +
	  " squirming uncomfortably under " + TP->query_possessive() +
	  " stern regard.");
    }
    if (oblp && sizeof(oblp)) {
	target(" studies you intently, taking your measure.\n" +
	  "You hold " + TP->query_possessive() +
	  " stern, evaluating gaze easily.", oblp);
	actor("You study", oblp, " intently, taking " +
	  (sizeof(oblp) > 1 ? "their" : oblp[0]->query_possessive()) +
	  " measure.\n" +
	  C(sizeof(oblp) > 1 ? "they hold" : oblp[0]->query_pronoun() + " holds") +
	  " easily against your regard.");
	all2act(" studies", oblist, " intently, taking " +
	  (sizeof(oblp) > 1 ? "their" : oblp[0]->query_possessive()) +
	  " measure.\nYou can see " +
	  (sizeof(oblp) > 1 ? "them" : oblp[0]->query_possessive()) +
	  " holding easily against " + TP->query_possessive() +
	  " stern regard.");
    }
    return 1;
}


/****************** kswshake *****************************************/
/* Suggested by Teth, added by Morrigan. 10/7/96                     */
int
kswshake(string str)
{
    if (TP->query_knight_level() != 4) {
	write("You are not a Knight of the Sword.\n");
	return 1;
    }
    write("You shake your head grimly, thinking of the unjust battle.\n");
    all(" shakes " + TP->query_possessive() + " head grimly, thinking of the " +
      "unjust battle.");
    return 1;
}


/****************** kswwar *******************************************/
/* Suggested by Teth, added by Morrigan. 10/7/96                     */
int
kswwar(string str)
{
    if (TP->query_knight_level() != 4) {
	write("You are not a Knight of the Sword.\n");
	return 1;
    }
    write("You calmly prepare yourself for the upcoming war, your thoughts " +
      "on facing evil.\n");
    all(" calmly prepares " + TP->query_objective() + "self for the upcoming " +
      "war, " + TP->query_possessive() + " thoughts on facing evil, with no " +
      "concern for " + TP->query_possessive() + " own suffering.");
    return 1;
}


/******************* kswear ************************************* */

int
kswear(string str)
{

    if (TP->query_knight_level() == 1) {
	write("A Knight of the Black Rose has no honour.\n");
	return 1;
    }
    if (strlen(str)) {
	notify_fail("Kswear what?\n");
	return 0;
    }
    if (TP->query_prop(KNIGHT_I_DEVOTION) < TP->query_age() + 1000)
	TP->add_prop(KNIGHT_I_DEVOTION, TP->query_age() + 1000);

    if (TP->query_guild_name_occ() != "Solamnian Knights") {
	write("You place your fist over your heart, swearing:\n" +
	  "       Upon my Honour as a Sentry, the Oath, the Measure, and\n" +
	  "       all that I hold Sacred, my Word is my Bond until Death!\n");

	all(" places " + TP->query_possessive() + " fist over " +
	  TP->query_possessive() + " heart and swears:\n" +
	  "       Upon my Honour as a Sentry, the Oath, the Measure, and\n" +
	  "       all that I hold Sacred, my Word is my Bond until Death!");

	return 1;
    }
    write("You place your fist over your heart, swearing:\n" +
      "       Upon my Honour as a Knight, the Oath, the Measure, and\n" +
      "       all that I hold Sacred, my Word is my Bond until Death!\n");

    all(" places " + TP->query_possessive() + " fist over " +
      TP->query_possessive() + " heart and swears:\n" +
      "       Upon my Honour as a Knight, the Oath, the Measure, and\n" +
      "       all that I hold Sacred, my Word is my Bond until Death!");
    return 1;
}


/********************* ksweat *********************************************/
/* Modified by Morrigan and Igneous on 10/5/96 to take into account       */
/* whether or not the Knight is wearing a helm.                           */
int
ksweat(string str)
{

    object         *worn_armours;
    object          helm;
    int             i;

    if (strlen(str)) {
	notify_fail("Wipe the sweat how??? Don't use a string.\n");
	return 0;
    }
    worn_armours = TP->query_armour(-1);

    if (sizeof(worn_armours)) {
	for (i = 0; i < sizeof(worn_armours); i++) {
	    if (worn_armours[i]->query_at() == A_HEAD)
		helm = worn_armours[i];
	}

    }
    if (!helm) {
	write("You wipe the sweat from your brow.\n");
	all(" wipes the sweat from " + TP->query_possessive() +
	  " brow.");
	return 1;
    }
    write("You remove your " + helm->short() + " and wipe the sweat " +
      "from your brow.\n");
    all(" removes " + TP->query_possessive() + " " + helm->short() +
      " and wipes the sweat from " + TP->query_possessive() +
      " brow.");
    return 1;
}


/*********************** kswift **************************************/

int
kswift(string str)
{
    object         *oblist, *oblf = ({}), *oblm = ({});
    int             i;

    oblist = parse_this(str, "[the] %l");

    if (!oblist || !sizeof(oblist)) {
	notify_fail("Swiftly kiss whom?\n");
	return 0;
    }
    for (i = 0; i < sizeof(oblist); i++) {
	if (oblist[i]->query_gender() == 1)
	    oblf += ({oblist[i]});
	else
	    oblm += ({oblist[i]});
    }
    if (oblf && sizeof(oblf)) {
	actor("You sweep", oblf, " into your arms and " +
	  "steal a swift kiss.");
	target(" sweeps you into " + TP->query_possessive() + " arms " +
	  "and steals a swift kiss!", oblf);
	all2act(" sweeps", oblf, " into " + TP->query_possessive() +
	  " arms and steals a swift kiss.   How romantic!");
    }
    if (oblm && sizeof(oblm)) {
	actor("You wrap your arms around the neck of", oblm,
	  " and steal a swift kiss.");
	target(" wraps " + TP->query_possessive() + " arms around " +
	  "your neck and steals a swift kiss.", oblm);
	all2act(" wraps " + TP->query_possessive() + " arms around " +
	  "the neck of", oblm, " and steals a swift kiss.  " +
	  " How romantic!");
    }
    return 1;
}

/********************* tend *************************************************/
int
tend(string str)
{
    object         *ob;
    int             i, hits, dif, last;

    NF("Tend what?\n");
    if (!str)
	return 0;
    ob = FIND_STR_IN_OBJECT(str, this_player());
    if (!sizeof(ob))
	return 0;

    NF("You can only tend weapons and armours.\n");
    ob = filter(ob, "filter_wep_arm", this_object());
    if (!sizeof(ob))
	return 0;

    for (i = 0; i < sizeof(ob); i++) {
	hits = ob[i]->check_armour() ? ob[i]->query_armour_hits() :
	ob[i]->query_weapon_hits();
	if (hits < (last = ob[i]->query_prop(KNIGHT_HITS)) || !last)
	    ob[i]->add_prop(KNIGHT_HITS, hits);
	else {
	    dif = hits - last;
	    dif = dif / 2;
	    dif = random(dif);
	    hits -= dif;
	    ob[i]->set_weapon_hits(hits);
	    ob[i]->set_armour_hits(hits);
	    ob[i]->add_prop(KNIGHT_HITS, hits);
	}
    }

    write(BS("You attend to " + COMPOSITE_DEAD(ob) + " the way your " +
	"instructors taught you.", 70));
    say(QCTNAME(TP) + " attends " + QCOMPDEAD + " skillfully.\n");
    return 1;
}

int
filter_wep_arm(object ob)
{
    if (ob->check_armour() || ob->check_weapon())
	return 1;
    return 0;
}

/**************************** kthrust *****************************/
/* Added by Morrigan, 5/4/97 */
int kthrust(string str)
{
    object room = E(TP);
    object weapon;

    NF("Kthrust which weapon into the ground?\n");
    if (!str)
	return 0;

    NF("You are inside, you would not do that.\n");
    if (room->query_prop(ROOM_I_INSIDE))
	return 0;

    NF("You cannot thrust your weapon into the ground here, "+
      "because there is no ground.\n");
    if (room->query_prop(ROOM_I_TYPE) != ROOM_NORMAL &&
      room->query_prop(ROOM_I_TYPE) != ROOM_BEACH)
	return 0;

    parse_command(str, TP, "%o", weapon);

    NF("Kthrust which weapon into the ground?\n");
    if (!weapon->check_weapon())
	return 0;

    NF("You cannot thrust a blunt weapon into the ground.\n");
    if (weapon->query_dt() == W_BLUDGEON)
	return 0;

    setuid(); seteuid(getuid());
    write("You reverse your grip on the "+weapon->short()+" and "+
      "thrust it into the ground at your feet.\n");
    say(QCTNAME(TP)+" reverses "+POSSESSIVE(TP)+" grip "+
      "on "+POSSESSIVE(TP)+" "+weapon->short()+" and thrusts it "+
      "into the ground at "+POSSESSIVE(TP)+" feet.\n");
    weapon->add_prop(OBJ_M_NO_GET, "The weapon cannot be taken,"+
      " it is lodged firmly in the ground.\n");
    clone_object(KOBJ+"kthrust_weapon_shadow")->shadow_me(weapon);
    weapon->setup_things();
    weapon->move(room);
    weapon->set_depth(TP->query_stat(SS_STR) - 5 - random(15));
    return 1;
}


/******************* trace ****************************************************/
/* trace a scar in remembrance */
int
trace(string str)
{
    int             scars = TP->query_scar();
    int             i = 0, j = 1;
    string          where;
    string         *scar_list = ({}), *scar_desc = F_SCAR_DESCS;
    NF("You can only trace a scar.\n");
    if (str && str != "scar" && str != "scars")
	return 0;
    if (!scars) {
	write("You don't have a scar you could trace!\n");
	return 1;
    } else {
	while (i < F_MAX_SCAR) {
	    if (scars & j)
		scar_list += ({scar_desc[i]});
	    j *= 2;
	    i += 1;
	}
	where = scar_list[random(sizeof(scar_list))];
	write("You trace the scar on your " + where + ", in remembrance of past events.\n");
	all(" absentmindedly traces a scar on " + POSSESSIVE(TP) + " " + where + ".");
    }
    return 1;
}


/********************** ktoast ****************************************/
int
ktoast(string str)
{
    if (!str)
    {
	write("You raise your drink in a toast: I pledge to our good "+
	  "fortune in battle!\n");
	all(" raises "+TP->query_possessive()+" drink in a toast: "+
	  "I pledge to our good fortune in battle!");
	return 1;
    }

    write("You raise your drink in a toast: "+str+"\n");
    all(" raises "+TP->query_possessive()+" drink in a toast: "+
      str);
    return 1;
}

