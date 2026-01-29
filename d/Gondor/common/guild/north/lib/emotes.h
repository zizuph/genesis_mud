/*
 *	/d/Gondor/common/guild/lib/emotes.h
 *
 *	To be included in /d/Gondor/common/guild/ranger_soul.c
 */
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
    NF("You need to be outside to examine the dirt ground!\n");
    if (!ENV(TP)->query_prop(ROOM_I_INSIDE))
    {
        write("You examine the ground closely, prodding "+
          "and searching it for tracks.\n");
        allbb(" examines the ground closely, prodding "+
          "and searching it for something.");
        return 1;
    }
    return 0;
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
rhome()
{
    write("You look in the direction of ancient Arnor"
      + ", sighing wistfully.\n");
    allbb(" turns and looks away in the direction of ancient Arnor"
      + ", falling silent for a while.");
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

