/*
 *	/d/Gondor/common/guild/lib/emotes.h
 *
 *	To be included in /d/Gondor/common/guild/ranger_soul.c
 */

/* Note LEAN_ITEMS, SIT_STRINGS, and  SIZE_OF_LEAN_ITEMS are related */
#define LEAN_ITEMS  ({ "board", "door", "desk", "table", "tree" })
#define SIT_STRINGS ({ "close to the board", "near the door", \
                        "on the desk", "on the table", "by a tree" }) 
#define SIZE_OF_LEAN_ITEMS 5

#define FOOTWEAR    ({ "boots", "shoes", "footwear", "sandal" })
#define PEBBLES     ({ "nasty stones", "little pebbles", "tiny rocks", \
                       "sharp stones", "small rocks", "round pebbles", \
                       "minuscule rocks", "nasty rocks", "minuscule stones", \
                       "dirt", "sharp sand" })
#define SKILLED     ({ "skilfully", "clumsily", "expertly", "briefly", \
                       "shortly", "quickly", "slowly", "proficiently" })

int
filter_sword(object x)
{
    return ((function_exists("create_object", x) == WEAPON_OBJECT)
           && (x->query_wt() == W_SWORD));
}

int
filter_cont(object x)
{
    return (function_exists("create_object", x) == CONTAINER_OBJECT);
}

int
filter_weapons(object x)
{
    return (function_exists("create_object", x) == WEAPON_OBJECT);
}

int
emote_parley(string str)
{
    object *oblist;
    if ((objectp(TP->query_weapon(W_RIGHT))) ||
        (objectp(TP->query_weapon(W_LEFT))) ||
        (objectp(TP->query_weapon(W_BOTH))))
        NFN0("Better unwield your weapon before you try to parley.");
    if (!strlen(str))
    {
        write("You hold your empty hand out in a gesture of parley.\n");
        allbb(" holds " + POSSESSIVE(TP) + " empty hand out in a gesture of parley.");
        return 1;
    }
    oblist = parse_this(str, "[with] %l");
    if (!sizeof(oblist))
        NFN0("You don't see any such being here.");
    targetbb(" holds " + POSSESSIVE(TP) + " empty hand up towards you in a "
      + "gesture of parley.", oblist);
    actor("You hold your empty hand out as a gesture for parley "
      + "to", oblist, ".");
    all2actbb("  holds " + POSSESSIVE(TP) + " empty palm out as " 
      + "a gesture of parley to", oblist, ".");
    return 1;
}

int
emote_laugh(string str) 
{
    object *oblist;
 
    NF("Laugh how?\n");
    if (!strlen(str)) 
    {
        write("You laugh the hearty laugh of a ranger.\n");
        all(" laughs the hearty laugh of a ranger.");
        TP->reveal_me(0);
        return 1;
    }
    oblist = parse_this(str,"[at] %l");
    if (!sizeof(oblist))
        return 0;
    target(" laughs at you with the hearty laugh of "+
      "a ranger.", oblist);
    actor("You laugh at", oblist, " with the hearty "+
      "laugh of a ranger.");
    all2act(" laughs at",oblist," with the hearty "+
      "laugh of a ranger.");
    TP->reveal_me(0);
    return 1;
}
 
int
emote_danger(string str) 
{
    object *oblist; 
    NF("Laugh how?\n");
    if (!strlen(str)) 
    {
        write("You laugh in the face of danger.\n");
        all(" laughs in the face of danger.");
        TP->reveal_me(0);
        return 1;
    }
    oblist = parse_this(str,"[with] %l");
    if (!sizeof(oblist))
        return 0;
    target(" laughs with you in the face of "+
      "danger.", oblist);
    actor("You laugh with", oblist, " in the face "+
      "of danger.");
    all2act(" laughs with",oblist," in the face "+
      "of danger.");
    TP->reveal_me(0);
    return 1;
}

int
good_align(object x)
{
    return (x->query_alignment() > 0);
}

int
emote_cap_gaze(string str)
{
    object *oblist;
    string  targ_str, act_str, all_str;

    if (!(R_COUNCIL)->query_captain(TP->query_real_name())
        && !TP->query_wiz_level())
        return 0;
    if (!strlen(str))
        str = "all";
    oblist = parse_this(str, "[at] [the] %l");
    oblist -= ({ TP });

    if (sizeof(oblist) < 1)
    {
        NFN("Gaze at whom?");
        return 0;
    }
    oblist = ({ oblist[0] });
    actor("You hold", oblist, " with your gaze, and in "
      + "silence, look searchingly at " 
      + OBJECTIVE(oblist[0]) 
      + ".");
    targetbb(" holds you with " + POSSESSIVE(TP) + " gaze, "
      + "and looks searchingly at you in silence.", oblist);

    if (oblist[0]->query_alignment() > 0)
    {
        /* Good-aligned players match Wisdom against the Captain's Wisdom */
        switch (oblist[0]->query_stat(SS_WIS) - TP->query_stat(SS_WIS))
        {
            case -400..-25:
              targ_str = "You blush and hang your head.";
              act_str = "blushes and hangs " + POSSESSIVE(oblist[0]) + " head.";
              all_str = act_str;
              break;
          case -24..0:
              targ_str = "You blush slightly and squirm a little under "
                + POSSESSIVE(TP) + " gaze.";
              act_str = "blushes slightly, squirming a little under your "
                + "gaze before looking away.";
              all_str = "blushes slightly, returning " + QTNAME(TP) + "'s "
                + "gaze for a short while before looking away.";
              break;
          case 1..25:
              targ_str = "You return " + POSSESSIVE(TP) + " gaze for a while "
                + "before finally averting your eyes from the intensity.";
              act_str = "returns your gaze at length, before finally averting "
                + POSSESSIVE(oblist[0]) + " eyes.";
              all_str = "returns " + QTNAME(TP) + "'s gaze at length before "
                + "finally averting " + POSSESSIVE(oblist[0]) + " eyes.";
              break;
          case 26..400:
              targ_str = "You return " + POSSESSIVE(TP) + " gaze at length, "
                + "not uncomfortable with the close scrutiny.";
              act_str = "returns your gaze at length, seemingly comfortable "
                + "with your close scrutiny.";
              all_str = "returns " + QTNAME(TP) + "'s gaze at length, seemingly "
                + "comfortable with the close scrutiny.";
              break;
        }
    }
    else
    {
        /* Evil-aligned players match their DIS against the Captain's DIS and guild-stat. */
        switch (oblist[0]->query_stat(SS_DIS) - 
               (TP->query_stat(SS_DIS) + (TP->query_stat(SS_OCCUP)/6)))
        {
            case -400..-25:
              targ_str = "You feel your face grow red and you turn your gaze "
                + "from the scrutinizing eyes that seem to see right through you.";
              act_str = "grows red in the face and "
                + "quickly averts " + POSSESSIVE(oblist[0]) + " eyes.";
              all_str = "grows red in the face and quickly "
                + "averts " + POSSESSIVE(oblist[0]) + " eyes.";
              break;
          case -24..0:
              targ_str = "You blush somewhat and squirm under "
                + POSSESSIVE(TP) + " scrutinizing gaze.";
              act_str = "turns a little red-faced, squirming under your gaze for a while.";
              all_str = "turns a little red-faced, squirming under " + QTNAME(TP) + "'s "
                + "gaze for a while.";
              break;
          case 1..25:
              targ_str = "You return " + POSSESSIVE(TP) + " gaze defiantly for "
                + "a while before finally averting your eyes from the intensity.";
              act_str = "returns your gaze defiantly for a while, before finally averting "
                + POSSESSIVE(oblist[0]) + " eyes.";
              all_str = "returns " + QTNAME(TP) + "'s gaze defiantly for a while before "
                + "finally averting " + POSSESSIVE(oblist[0]) + " eyes.";
              break;
          case 26..400:
              targ_str = "You return " + POSSESSIVE(TP) + " gaze defiantly at length, "
                + "ignoring the scrutiny.";
              act_str = "returns your gaze defiantly at length, seemingly not worried "
                + "by your close scrutiny.";
              all_str = "returns " + QTNAME(TP) + "'s gaze defiantly at length, seemingly "
                + "not caring about the close scrutiny.";
              break;
        }
    }
    write(CAP(PRONOUN(oblist[0])) + " " + act_str + "\n");
    oblist[0]->catch_msg(targ_str + "\n");
    all2actbb(" holds", oblist, " with " + POSSESSIVE(TP) + " gaze, "
      + "and looks searchingly at " + OBJECTIVE(oblist[0]) + " in silence. "
      + QCTNAME(oblist[0]) + " " + all_str);
    return 1;
}

int
emote_pick() 
{
    write("You pick your teeth.\n");
    allbb(" picks up a stick and picks "+ POSSESSIVE(TP) +
      " teeth.");
    return 1;
}
 
int
emote_rest() 
{
    NF("What ?\n");
    {
        write("You cast yourself on the ground to "+
          "relax, unable to remember when you last had a chance to rest.\n");
        allbb(" casts "+ OBJECTIVE(TP) +"self on the ground to "+
          "relax, unable to remember when "+PRONOUN(TP) +
          " last had a chance to rest.");
        return 1;
    }
}
 
int
emote_dirt() 
{
    NF("You need to be outside to smell dirt!\n");
    if (!ENV(TP)->query_prop(ROOM_I_INSIDE))
    {
        write("You pick up a handful of dirt and smell "+
          "it for a scent.\n");
        allbb(" picks up a handful of dirt and holds it "+
          "close to "+ POSSESSIVE(TP) +" nose.");
        return 1;
    }
    return 0;
}
 
int
emote_troubled(string str) 
{
    object *oblist;
    NF("Look how?\n");
    if (!strlen(str)) 
    {
        write("You study the environment, feeling troubled.\n");
        allbb(" doesn't move a muscle as "+PRONOUN(TP)+" studies "+
          POSSESSIVE(TP) + " environment, yet "+POSSESSIVE(TP)+" eyes " +
          "reveal that " + PRONOUN(TP) +" is troubled.");
        return 1;
    }
    oblist = parse_this(str,"[at] %l");
    if (!sizeof(oblist))
        return 0;
    targetbb(" studies you intensely. As "+
      POSSESSIVE(TP) +" eyes reach yours, you notice "+
      "that they seem deep and troubled.", oblist);
    actor("You look at", oblist, ", feeling "+
      "troubled.");
    all2actbb(" 's doesn't move a muscle as "+ PRONOUN(TP)+
      " studies",oblist,", though "+POSSESSIVE(TP)+" eyes reveal that "+
      PRONOUN(TP)+" is troubled.");
    return 1;
}
 
int
emote_study(string str) 
{
    object *oblist; 
    NF("Study Whom?\n");
    if (!strlen(str)) 
    {
        write("You study your environment carefully.\n");
        allbb("'s eyes study "+ POSSESSIVE(TP) +" environment "+
          "with great care, seemingly ready to counter "+
          "anything that may happen.");
        return 1;
    }
    oblist = parse_this(str,"[at] %l");
    if (!sizeof(oblist))
        return 0;
    if (sizeof(oblist) == 1)
    {
        targetbb("'s eyes seem to look right through you. You "+
          "have a feeling that "+ PRONOUN(TP) +" will know what "+
          "you are going to do, even before you know.", oblist);
        actor("You study", oblist, " carefully, trying to "+
          "guess what will be the next move "+ PRONOUN(oblist[0]) 
          + " will make.");
        all2actbb(" 's eyes study",oblist," with great care, seemingly "+
          "ready to counter any move "+ PRONOUN(oblist[0]) +" makes.");
        return 1;
    }
    targetbb("'s eyes seem to look right through you, and you "+
      "get the feeling that "+ PRONOUN(TP) +" will know what "+
      "you are going to do, even before you know it.",oblist);
    actor("You study", oblist, " carefully, trying to judge "+
      "what their next moves will be.");
    all2actbb(" 's eyes study", oblist," with great care, seemingly "+
      "ready to counter any move they will make.");
    return 1;
}

int
rgleam(string str)
{
    object *oblist;
    object scabbard,
           cloak,
           *weapons;
    string msg1, msg2;

    if (IS_DUNADAN(TP) || (TP->query_race() == "elf"))
    {
        msg1 = "You straighten up and display your tall stature, keen "
          + "and commanding.";
        msg2 = " stands up, and seems suddenly to grow taller. In "
          + POSSESSIVE(TP)+" eyes gleams "
          + "a light, keen and commanding.";
        weapons = TP->query_weapon(-1);
        if (objectp(scabbard = present("scabbard", TP)))
            weapons += all_inventory(scabbard);
        if (sizeof(weapons = filter(weapons, filter_sword)))
        {
            if (objectp(cloak = TP->query_armour(TS_ROBE)))
            {
                msg1 += " Throwing back your " + cloak->query_name() 
                  + ", you";
                msg2 += " Throwing back " + POSSESSIVE(TP) + " "
                  + cloak->query_name() + ", " + PRONOUN(TP);
	        }
        else
        {
            msg1 += " You";
            msg2 += " " + CAP(PRONOUN(TP));
        }
            msg1 += " lay your hand on the hilt of your ";
            msg2 += " lays " + POSSESSIVE(TP)
              + " hand on the hilt of " + POSSESSIVE(TP) + " ";
            if (objectp(scabbard) && present(weapons[0],scabbard))
	    {
                msg1 += "sheathed ";
                msg2 += "sheathed ";
	    }
	    msg1 += "sword.";
            msg2 += "sword.";
        }
        write(msg1+"\n");
        allbb(msg2);
        return 1;
    }
    NFN0("Only Dunedain and Elves can use their tall stature this way.");
}

int
cloak_wrap()
{
    object cloak;
    cloak = TP->query_armour(TS_ROBE);
    if (!objectp(cloak))
        NFN0("You are not wearing a cloak!");

    write("You draw the " + cloak->short() + " about your body for warmth.\n");
    allbb(" draws " + POSSESSIVE(TP) + " " + cloak->short()
      + " about " + OBJECTIVE(TP) + "self for warmth.");
    return 1;
}

int
cloak_unwrap()
{
    object cloak;
    cloak = TP->query_armour(TS_ROBE);
    if (!objectp(cloak))
        NFN0("You are not wearing a cloak!");
    write("You fling back your " + cloak->short() + ", preparing for "
      + "the fight.\n");
    allbb(" flings back " + POSSESSIVE(TP) + " " + cloak->short()
     + ", preparing to fight.");
    return 1;
}

int
rgrim()
{
    write("You feel alone in this world.\n");
    allbb(" gets a lonely, grim look on " + POSSESSIVE(TP) + " face.");
    SOULDESC("looking grim and lonely");
    return 1;
}

int
rweary()
{
    write("You feel weary from your travels.\n");
    allbb(" falls silent, " + POSSESSIVE(TP) + " face showing a great "
      + "weariness from " + POSSESSIVE(TP) + " travels.");
    SOULDESC("looking rather weary from all the travels");
    return 1;
}

int
rgrip()
{
    object *weapons;
    weapons = TP->query_weapon(-1);
    if (sizeof(weapons))
    {
        write("You tighten your grip on the " + weapons[0]->short() + ".\n");
        allbb(" tightens " + POSSESSIVE(TP) + " grip on " + POSSESSIVE(TP)
          + " " + weapons[0]->short() + ".");
        return 1;
    }
    NFN0("You have no weapon wielded!");
}

int
find_bearing()
{
    object clock = find_object(CLOCK);
    string time = clock->query_time_of_day();
    string txt;
    if (ENV(TP)->query_prop(ROOM_I_INSIDE) == 1)
        NFN0("You can only do so outside!");

    if (time == "morning" || time == "noon" || time == "afternoon")
       txt = "the Sun";
    else if (clock->query_moon() != "dark")
        txt = "the Stars and the Moon";
    else
        txt = "the Stars";

    write("You study " + txt + ", trying to find your bearing.\n");
    allbb(" pauses for a while, studying " + txt + " to find "
      + POSSESSIVE(TP) + " bearing.");
    return 1;
}

int
rwait(string str)
{
    mixed *oblist;
    if (!strlen(str))
        NFN0("Motion for who to wait?");
    oblist = parse_this(str, "%l");
    if (!sizeof(oblist))
        NFN0("Nobody here matches that description.");
    actor("With a motion of your hand you indicate for", oblist,
      " to wait right here.");
    targetbb(" motions with " + POSSESSIVE(TP) + " hand for you to "
      + "wait right here.", oblist);
    all2actbb(" motions with " + POSSESSIVE(TP) + " hand for", oblist,
      " to wait right here.");
    return 1;
}

int
rlisten()
{
    write("Your mouth draws to a deep frown as you listen intently to "
      + "the sounds of the distant battle.\n");
    allbb("'s mouth draws to a deep frown as " + PRONOUN(TP) + " listens "
      + "intently to the sounds of the distant battle.");
    return 1;
}

int
rembrace(string str)
{
    object *oblist;
    if (!strlen(str))
        NFN0("Embrace who?");
    oblist = parse_this(str, "%l");
    if (!sizeof(oblist))
        NFN0("You don't see that person here.");
    actor("You embrace", ({ oblist[0] }), " in a warm, sincere hug.");
    target(" embraces you in a warm, sincere hug, and a scent of fresh "
      + "herbs intoxicates your senses.", ({ oblist[0] }));
    all2actbb(" embraces", ({ oblist[0] }), " in a warm, sincere hug.");
    return 1;
}

int
rcurtsey(string str)
{
    object *oblist;
    if (TP->query_gender() != G_FEMALE)
        NFN0("You decide not to, since you are of the wrong sex.");
    if (!strlen(str))
        NFN0("Curtsey before who?");
    oblist = parse_this(str, "[before] %l");
    if (!sizeof(oblist))
        NFN0("You don't see that person here.");
    actor("You swiftly kick one heel behind the other in a brief "
      + "but charming curtsey before", oblist, ", lowering your "
      + "gaze respectfully.");
    target(" swiftly kicks one heel behind the other in a brief yet "
      + "charming curtsey before you, lowering her gaze respectfully.",
      oblist);
    all2act(" swiftly kicks one heel behind the other in a brief yet "
      + "charming curtsey before", oblist, ", lowering gaze respectfully.");
    return 1;
}

int
rbow(string str)
{
    object *oblist;
    if (!strlen(str))
        NFN0("Bow before who?");
    oblist = parse_this(str, "[before]/[to] %l");
    if (!sizeof(oblist))
        NFN0("You don't see that person here.");
    actor("You lower your gaze with respect and admiration "
      + "as you bow before", oblist, " in brief, yet graceful manner.");
    target(" lowers " + POSSESSIVE(TP) + " gaze with deep respect and admiration as "
      + PRONOUN(TP)
      + " bows before you in a brief, yet graceful manner.", oblist);
    all2act(" lowers " + POSSESSIVE(TP) + " gaze with deep respect and admiration as "
      + PRONOUN(TP)
      + " bows before", oblist, " in a brief, yet graceful manner.");
    return 1;
}

int
rcheek(string str)
{
    object *oblist;
    if (!strlen(str))
        NFN0("Kiss who on the cheek?");
    oblist = parse_this(str, "[with] %l [at]/[on] [the] [cheek]");
    if (!sizeof(oblist))
        NFN0("You don't see that person here.");
    oblist = ({ oblist[0] });
    actor("You kiss", oblist, " on each cheek, and embrace "
      + OBJECTIVE(oblist[0]) + " in the warm hug you reserve for "
      + "long-time friends.");
    target(" kisses you on each cheek, and embraces you in the warm "
      + "hug " + PRONOUN(TP) + " reserves for long-time friends.", oblist);
    all2actbb(" kisses", oblist, " on each cheek, and embraces "
      + OBJECTIVE(oblist[0]) + " in a warm hug reserved for long-time "
      + "friends.");
    return 1;
}

int
inspect_weapon(string str)
{
    object *weapons;
    object weapon,
            scabbard;
    if (!strlen(str))
    {
        weapons = TP->query_weapon(-1);
        scabbard = present("scabbard", TP);
        if (objectp(scabbard = present("scabbard", TP)))
            weapons += all_inventory(scabbard);
        if (sizeof(weapons))
            weapon = weapons[0];
        else
            NFN0("But you have no weapon ready!");
    }
    else
    {
        if (!parse_command(LOW(str), TP, "[the] %i", weapons))
            NFN0("You have no such weapon available!");
        weapons = NORMAL_ACCESS(weapons, 0, 0);
        if (!sizeof(weapons))
            NFN0("You don't have that weapon.");
        weapons = filter(weapons, filter_weapons);
        if (!sizeof(weapons))
            NFN0("That is not a weapon.");
        weapon = weapons[0];
    }
    write("You carefully check the " + weapon->short() + " for any "
      + "notches or signs of damage or wear, to make sure you are "
      + "prepared for the fight that lies ahead.\n"
      + weapon->wep_condition_desc());

    allbb(" carefully examines " + POSSESSIVE(TP) + " " + weapon->short()
      + " to make sure it is ready for the fight to come.");
    return 1;
}

int
wipe_weapon()
{
    mixed *weapons;
    weapons = TP->query_weapon(-1);
    if (!sizeof(weapons))
        NFN0("You have no weapon wielded.");
    write("With a piece of cloth you wipe your " + weapons[0]->short()
      + " clean of blood to avoid it becoming rusty or dull.\n"
      + weapons[0]->wep_condition_desc());
    allbb(" uses a piece of cloth to wipe " + POSSESSIVE(TP) + " "
      + weapons[0]->short() + " clean of blood from the last fight.");
    return 1;
}

int
rcheck(string str)
{
    mixed *oblist;
    object ob;
    if (!strlen(str))
        NFN0("Rummage through what container?");
    if (!parse_command(LOW(str), TP, "[the] %i", oblist))
        NFN0("You don't have that.");
    oblist = NORMAL_ACCESS(oblist, 0, 0);
    if (!sizeof(oblist))
        NFN0("You don't have that.");
    oblist = filter(oblist, filter_cont);
    if (!sizeof(oblist))
        NFN0("That's not a container.");
    ob = oblist[0];
    if (living(ob))
        NFN0("That's not a container.");
    if (!ob->query_prop(CONT_I_CLOSED))
    {
	write("You rummage through your " + ob->short() + ", taking "
	  + "a quick inventory to be sure you have everything needed for "
	  + "what lies ahead.\n");
	ob->show_visible_contents(TP);
	allbb(" rummages through " + POSSESSIVE(TP) + " " + ob->short()
	 + ", taking a quick inventory to be sure " + PRONOUN(TP) + " has "
	 + "everything needed for what lies ahead.");
     }
     else
     {
	write("You check your " + ob->short() + ", making "
	  + "certain that it is securely closed.\n");
	allbb(" checks " + POSSESSIVE(TP) + " " + ob->short() + ", making "
	  + "certain that it is securely closed.\n");
     }
     return 1;
}

int
rburp()
{
    if (ENV(TP)->query_prop(ROOM_I_INSIDE))
    {
        write("You feel an urge to burp after the hearty meal, "
          + "but politely hide it as best you can since you are "
          + "not out in the wilderness by a campfire.\n");
        allbb(" politely attempts to hide an urge to belch heartily "
          + "after the meal.");
        SOULDESC("trying not to belch");
        return 1;
    }
    write("To show your appreciation for the meal, you let out a "
      + "hearty belch.\n");
    all(" shows " + POSSESSIVE(TP) + " appreciation for the meal "
      + "with a hearty belch.");
    TP->reveal_me(1);
    SOULDESC("belching heartily");
    return 1;
}

int
rhome()
{
    int  co = query_bin_bits(1, 16, 2, TP);
    string *home_desc,
           *home_dir;
    home_desc = ({ "Gondor", "Gondor", "Ithilien" });
    home_dir = ({ "South", "South", "East" });
    write("You look in the direction of " + home_desc[co]
      + ", sighing wistfully.\n");
    allbb(" turns and looks away to the " + home_dir[co]
      + ", falling silent for a while.");
    return 1;
}

int
rrelief()
{
    write("You breathe a sigh of relief.\n");
    all(" breathes a sigh of relief.");
    return 1;
}

int
rub_token(string str)
{
    object  tp = TP,
            token = present("ranger_guild_object", tp);
    string *tok_desc = ({"ring", "ring", "amulet", "token"});
    string *mem_text;
    int     co = query_bin_bits(1, 16, 2, tp);

    if (!strlen(str))
        NFN0("Rub what?");
    if (member_array(str, tok_desc) < 0)
        NFN0("Rub what?");

    mem_text = ({
        "the times you have spent with friends around campfires",
        "the tasks you went through to get it",
        "your first victory over an orc",
        "the time you gathered the first pouch-full of herbs",
        "how you decided to join the Rangers",
        "hours spent foraging and cooking with friends",
        });
    if (!objectp(token))
    {
        write("Absentmindedly you reach for your Ranger " + tok_desc[co]
          + ", and realise it is not there!\n");
        allbb(" looks like " + PRONOUN(tp) + " has lost something.");
        return 1;
    }
    write("You absentmindedly rub your " + tok_desc[co] + ", fondly "
      + "recalling memories of " + mem_text[random(sizeof(mem_text))]
      + ".\n");
    allbb(" absentmindedly rubs " + POSSESSIVE(tp) + " " + token->short()
      + ", recalling some fond memory of " + POSSESSIVE(tp) + " life as "
      + "a Ranger.");
    return 1;
}

int
warm_by_fire()
{
    string	firestr;
    if (present("campfire", ENV(TP)))
	firestr = "campfire";
    else if (ENV(TP)->query_prop(OBJ_I_HAS_FIRE))
	firestr = "fire";
    else
        NFN0("But there is no campfire here!");
    write("Rubbing your hands together, you squat close to the "
      + "burning "+firestr+" and allow its glow to warm you comfortably.\n");
    allbb(" rubs " + POSSESSIVE(TP) + " hands together and squats "
      + "close to the "+firestr+" to let its heat comfort "
      + OBJECTIVE(TP) + ". " + CAP(POSSESSIVE(TP)) + " face is dimly "
      + "lit by the red glow of the fire.");
    return 1;
}

int
warm_back_by_fire()
{
    string	firestr, grndstr;
    if (present("campfire", ENV(TP)))
	firestr = "campfire";
    else if (ENV(TP)->query_prop(OBJ_I_HAS_FIRE))
	firestr = "fire";
    else
        NFN0("But there is no campfire here!");
    grndstr = (ENV(TP)->query_prop(ROOM_I_INSIDE) ? "floor" : "ground");
    write("You stretch your tired legs, and sit on the "+grndstr+" with your back "
      + "turned to the warming "+firestr+".\n");
    allbb(" stretches " + POSSESSIVE(TP) + " tired legs before "
      + "sitting on the "+grndstr+" to let the glow of the "+firestr+" warm "
      + POSSESSIVE(TP) + " back comfortably.");
    return 1;
}

int
gaze_fire()
{
    string	firestr;
    if (present("campfire", ENV(TP)))
	firestr = "campfire";
    else if (ENV(TP)->query_prop(OBJ_I_HAS_FIRE))
	firestr = "fire";
    else
        NFN0("But there is no campfire here!");
    write("You thoughtfully recollect the recent events while gazing "
      + "into the red glow and the flickering flames of the "+firestr+".\n");
    say("A fiery glint dances in " + QTNAME(TP) + "'s eyes as "
      + PRONOUN(TP) + " gazes intently at the flickering flames of the "
      + firestr+", obviously lost in thought.\n", TP);
    return 1;
}

int
poke_fire()
{
    string	firestr;
    if (present("campfire", ENV(TP)))
	firestr = "campfire";
    else if (ENV(TP)->query_prop(OBJ_I_HAS_FIRE))
	firestr = "fire";
    else
        NFN0("But there is no campfire here!");
    if (!ENV(TP)->query_prop(ROOM_I_INSIDE))
    {
	write("You pick up a stick and poke around in the glowing embers "
          + "of the "+firestr+" with it. Sparks fly several feet in the air.\n");
	all(" picks up a stick and pokes the glowing embers and faggots "
          + "of the "+firestr+" with it, and sparks fly several feet in the air.");
    }
    else
    {
	write("You pick up a bit of firewood and poke around in the glowing embers "
          + "of the "+firestr+" with it, causing sparks to fly.\n");
	all(" picks up a bit of firewood and pokes the glowing embers "
          + "of the "+firestr+" with it, causing sparks to fly.");
    }
    return 1;
}

/*
 * Finction name:    rrecall()
 * Description  :    The `rrecall' emotion.
 *                   It have three usages: `rrecall' (default)
 *                                         `rrecall <tale>' (history)
 *                                         `rrecall <target> (advanced)
 * Created by Skippern, May 2000.
 */
int
rrecall(string str)
{
    string me;                           /* Checking my race */
    string race;                         /* Checking targets race */
    int align;                           /* Checking targets alignment */
    int enemy;                           /* Is it an enemy? */
    int allied;                          /* Target might be allied */
    object *oblist;                      /* Who wants to be a target? */
    object target;
    
    str = lower_case(str);

    /* We need to know the race of the Ranger. */
    me = this_player()->query_race_name();
    if (me == "human")
    {
        if (IS_DUNADAN(this_player()))
	{
	    me = "dunadan";
	}
    }
    
    /* <tale> is an alias for str */
    /* If <tale> is used */
    /* Hurin */
    if (str == "hurin")
    {
	write("You feel your resolve strenghten as you recall the " +
	    "staunch faith of Hurin the Steadfast.\n");
	allbb("'s face grows stern and resolved as " +
	    this_player()->query_pronoun()+" recalls the " +
	    "staunch faith of Hurin the Steadfast.");
	return 1;
    }
    
    /* Fingolfin */
    if (str == "fingolfin")
    {
	write("You are filled with new courage as you recall the valour " +
	    "of Fingolfin, who knocked on the gates of Angband.\n");
	allbb("'s eyes sparkle brightly as " +
	    this_player()->query_pronoun()+" recalls the valour " +
	    "of Fingolfin, who knocked on the gates of Angband.");
	return 1;
    }
    
    /* Beren and Luthien */
    if ((str == "beren" || str == "luthien"))
    {
        write("Your gaze grows distant for a moment, as you recalling " +
	    "how the love between Beren and Luthien made the dark " + 
	    "powers yield.\n");
	allbb(" gets a distant thoughtful look in " +
	    this_player()->query_pronoun()+"  eyes, recalling how the " +
	    "love between Beren and Luthien made the dark powers yield.");
	return 1;
    }
    
    /* We want to make sure the person is present, and wheter he is
     * allied or enemy, and what race he is. The races are:
     * Human, Dunadan, Hobbit, Dwarf, Elf, Half-elf, Gnome, Goblin, Orc. */
  
    if (strlen(str))
    {
        oblist = parse_this(str, "[the] %l");
	if (!sizeof(oblist))
	{
	    notify_fail("Who do you mean?\n");
	    return 0;
	}
	target = oblist[0];
    }

    /* If <target> is used. */
    if (objectp(target))
    {
        /* We need to know the race of the target. */
        race = target->query_race_name();
	if (race == "goblin")
        {
	    enemy = 1;
	}
	if (race == "human")
	{
	    if (IS_DUNADAN(target))
	    {
	        race = "dunadan";
	    }
	}

	/* We need to know the alignment. */
	if (race != "goblin")
	{
	    align = target->query_alignment();
	    if (align < (-250))
	    {
	        enemy = 1;
	    }
	    else if (align > 250)
	    {
	        allied = 1;
	    }
	}

	/* Evil aligned or goblin target */
	if (enemy == 1)
	{
	    actor("You glance coldly at", oblist,", recalling the lies and " +
	        "deceit wrought by the Enemy in ages past.\n");
	    all2actbb(" glances coldly at", oblist,", recalling the lies " +
		"and deceit wrought by the Enemy in ages past.");
	    targetbb(" glances at you in a cold manner, recalling the lies " +
		"and deceit wrought by the Enemy in ages past.", oblist);
	    return 1;
	}

	/* Heres the tricky part (if target is human, elf, dwarf, dunadan or
	 * Hobbit) */
	/* This have to be: elf-human, elf-dwarf, human-dwarf or human-hobbit*/
	if (allied == 1 && (
	    (me == "elf" && race == "human") || 
	    (me == "human" && race == "elf") ||
	    (me == "elf" && race == "dwarf") || 
	    (me == "dwarf" && race == "elf") ||
	    (me == "human" && race == "dwarf") || 
	    (me == "dwarf" && race == "human") || 
	    (me == "hobbit" && race == "human")))
        {
	    me = LANG_PWORD(me);
	    race = LANG_PWORD(race);
	    actor("You smiles confidently at", oblist," recalling the " +
	        "tales of battles where "+race+" and "+me+" were united " +
		"against the enemy.");
	    all2actbb(" smiles confidently at", oblist," recalling the " +
		"tales of battle where "+race+" and "+me+" were united " +
		"against the enemy.");
	    targetbb(" smiles confidently at you recaling the tales of " +
		"battle where "+race+" and "+me+" were united against the " +
		"enemy.", oblist);
	    return 1;
	}

	/* This will be: dunedain-elves */
	if (allied == 1 && (
	    (me == "elf" & race == "dunadan") || 
	    (me == "dunadan" & race == "elf")))
        {
	    actor("You smile confidently at", oblist," remembering the " +
	        "ancient bonds of friendship between the Edain and the " +
	        "elves.");
	    all2actbb(" smiles confidently at", oblist," remembering the " +
		"ancient bonds of friendship between the Edian and " +
		"the elves.");
	    targetbb(" smiles confidently at you remembering the ancient " +
                "bonds of friendship between the Edain and the elves.", 
		oblist);
	    return 1;
	}

  /* This will be: ranger-hobbit, but only if the ranger are not hobbit */
	if (allied == 1 && (
	    (me != "hobbit" && race == "hobbit")))
        {
	    actor("You smile confidently at", oblist," recalling the many " +
	        "times you have kept bandits from the hobbits' homes.");
	    all2actbb(" smiles confidently at", oblist," recalling the " +
		"many times "+this_player()->query_pronoun()+" kept " +
		"bandits from the hobbits' homes.");
	    targetbb(" smiles confidently at you recalling the many times" +
                " "+this_player()->query_pronoun()+" has kept bandits from " +
		"your homes.", oblist);
	    return 1;
	}

	/* Default */
	actor("You smile wistfully at", oblist,", recalling the tales and " +
	    "songs of ages past.");
	all2actbb(" smiles wistfully at", oblist,", recalling the tales and " +
	    "songs of ages past.");
	targetbb(" smiles wistfully at you, recalling the tales and songs " +
	    "of ages past.", oblist);
	return 1;
    }

    /* Default */
    write("You smile wistfully, recalling the tales and songs of ages " +
	"past.\n");
    allbb(" smiles wistfully, recalling tales and songs of ages past.");
    return 1;
}

/*
 * The rstone emote  : "rstone" [<person>]
 * By Stern 6 march 2000
 */
int
rstone(string str)
{
    int index;
    string footwear;
    string pebbles;
    string skilled;
    string *possibilities = ({ });       /* items to lean against */
    string item;                         /* picked item to lean against */
    object *objs;                        /* footwear */             
    object *oblist;                      /* people to lean against */   
    object room;
   
    /* First make sure the syntax is correct, and get <person>  */
    if (stringp(str))
    {
        oblist = parse_this(str, "%l");
        if (!sizeof(oblist))
        {
            notify_fail("Lean against whom?\n");
            return 0;
        }

        /* we want to have one person only to lean on */
        oblist = ({ one_of_list(oblist) });
    }  
   
    pebbles = one_of_list(PEBBLES);

    /* Find worn footwear, but not more than one, and if we don't find */
    /* any we set it to some random generic footwear.                  */  
    objs = this_player()->query_clothing(A_L_FOOT);
    if (!sizeof(objs))
    {
        objs = this_player()->query_clothing(A_R_FOOT);
    }
    if (sizeof(objs))
    {
        footwear = objs[0]->query_short();
    }
    else
    {
        footwear = one_of_list(FOOTWEAR);
    }

    /* if there is a  <person> involved */
    if (sizeof(oblist)) 
    {
        actor("You briefly lean against", oblist, " while emptying some " +
            pebbles + " from your " + footwear + ".");
        all2actbb(" briefly leans against", oblist, " while emptying some " +
            pebbles + " from " +  this_player()->query_possessive() + " " + 
            footwear + ".");
        target(" briefly leans against you while emptying some " +
            pebbles + " from " + this_player()->query_possessive() + " " +
            footwear + ".",  oblist );
        return 1;
    }

    /* if no person involved lets find something to lean against */
    /* if indoors */
    room  = environment(this_player());
    if (room->query_prop(ROOM_I_INSIDE))
    {
        possibilities = ({ "wall" });
    }
    for (index = 0; index < SIZE_OF_LEAN_ITEMS; index++)
    {
        if (present(LEAN_ITEMS[index], room) ||
            room->item_id(LEAN_ITEMS[index]))
        {
            possibilities += ({ LEAN_ITEMS[index] });
        }
    }

    /* if no object to lean against and outside */
    if (!sizeof(possibilities))
    {
        if (!random(3))
        {
            write("You sit on a nearby log and empty some " + pebbles +
                " from your " + footwear + ".\n" );
            allbb(" sits on a nearby log and empties some " + pebbles +
                " from " + this_player()->query_possessive() + " " +
                footwear + ".");
            return 1;
        }
        skilled = one_of_list(SKILLED);
        write("You " + skilled + " balance on one foot to empty some " + 
            pebbles + " from your " + footwear + ".\n");
        allbb(" " + skilled + " balances on one foot to empty some " + 
            pebbles + " from " + this_player()->query_possessive() + " " +
            footwear + ".");
        return 1;
    }

    /* pick something to lean against */
    item = one_of_list(possibilities);
    write("You lean against the " + item +
        " for a moment, while emptying some " +
        pebbles + " from your " + footwear + ".\n");
    allbb(" leans against the " + item +
        " for a moment, while emptying some " +
        pebbles +  " from " + this_player()->query_possessive() + " " +
        footwear + ".");
    return 1;
}
 
/*
 * The rsit emote  : "rsit"
 */
int
rsit(string str)
{
    int index;
    string *possibilities = ({ });       /* items to sit on/by  */
    string *sit_strings = ({ });    /* strings for items to sit on/by */
    string item;                         /* picked string to sit by/on */
    object room;

     if (stringp(str))
    {
        notify_fail("Sit where?\n");
        return 0;
    }

    /* if indoors */
    room  = environment(this_player());
    if (room->query_prop(ROOM_I_INSIDE))
    {
        possibilities = ({ "wall" });
        sit_strings =  ({ "by the wall" });
    }
    for (index = 0; index < SIZE_OF_LEAN_ITEMS; index++)
    {
        if (present(LEAN_ITEMS[index], room) ||
            room->item_id(LEAN_ITEMS[index]))
        {
            possibilities += ({ LEAN_ITEMS[index] });
            sit_strings += ({ SIT_STRINGS[index]  });
            
        }
    }

    /* if no object to lean against and outside */
    if (!sizeof(possibilities))
    {
        if (!random(3))
        {
            possibilities = ({ "log" });
            sit_strings =  ({ "on a nearby log" });
        }
        else 
        {
            possibilities = ({ "ground" });
            sit_strings =  ({ "on the ground" });
        }
    }
    /* pick something to sit by */
    item = one_of_list(sit_strings);
    write("You pick a comfortable spot " + item + " and sit down in a " +
          "restful yet vigilant posture, to watch and wait.\n" );
    allbb(" picks a comfortable spot " + item + " and sits down in a " +
          "restful yet vigilant posture, to watch and wait.");
    return 1;
}

/*
 * The rtrack emote  : "rtrack" [<adverb>]
 */
int
rtrack(string str)
{
    int index;
    string *how;
    string *actions = ({ "scanning the surroundings for any movement.", 
                         "pondering the course of action.", 
                         "observing each sound and movement in the area.", 
                         "vigilantly watching the environment." });   

    string actionstr;             /* picked action */

    /* if indoors */
    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You cannot study tracks inside a room!\n");
        return 0;

    }

    how = parse_adverb_with_space(str, "meticulously", 0);

    actionstr = one_of_list(actions);
    write("You study the tracks on the ground" + how[1] + " while " + 
        actionstr + "\n" );
    allbb(" studies the tracks on the ground" + how[1]  + " while " +  
        actionstr);
    return 1;
}

/*
 * The rbrush emote  : "rbrush" 
 */
int
rbrush(string str)
{
    string *actions = ({ "brush the dust and dirt", "brush some dirt",
                         "shake the dust", "shake the leaves", 
                         "shake some grass and leaves" });   
    string action;
    object *objs;                        /* bodywear */     
    string clothes;        

    if (stringp(str))
    {
        notify_fail("Brush what?\n");
        return 0;
    }

    /* Find worn cape or cloak */
    objs =  this_player()->query_clothing(A_ROBE) ;
    
    /* if no cape or cloak find another torso covering armour */
    if (!sizeof(objs))
    {
        objs =  this_player()->query_clothing(TS_BACK) &
                this_player()->query_clothing(TS_CHEST);
    }
    
    if (sizeof(objs))
    {
        clothes = objs[0]->query_short();
    }
    else
    {
        clothes = "clothes";
    }

    /* define the action for if water is present in the room */
    action = one_of_list(actions);
    
    /* see if there is water in the room for rinsing */
    if (environment(this_player())->query_prop(OBJ_I_CONTAIN_WATER))
    {
            action =  "rinse some blood stains";
    }

    write("You pause to rest and clean yourself up, taking the " +
          "opportunity to " + action + " from your " + clothes +".\n" );
    allbb(" pauses to rest, taking the opportunity to " + action + 
          " from "  + this_player()->query_possessive() + " " + clothes + ".");
    return 1;
}


