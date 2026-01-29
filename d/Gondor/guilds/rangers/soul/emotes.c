/*
 * /d/Gondor/guilds/rangers/soul/emotes.c
 *
 * Included in the soul. The emotes for the Rangers plus a couple of
 * commands such as rintro and rlist which are semi-emotes.
 *
 * The majority of the emotes originally coded by Elessar.
 * Rstone, rsit, rtrack, rbrush and an extended rpray by Stern.
 * Rrecall by Skippern.
 *
 * Modification log:
 * 13 April 2001 Gwyneth: General cleanup and move.
 * 04 February 2002 Alto: Continued cleanup and move.
 *    RINTRO and RLIST still need to be completed!
 * 17 March 2006 Palmer: Added checks for rbattle: discipline
 *                       and if a room or npc has peace props
 */

/* Battlecries for different races. */
#define BATTLE_CRY         ({"For Elendil", "For Isildur", "For Anarion", \
                             "For Gondor", "For King and Steward", })
#define BATTLE_CRY_DWARVES ({"For Durin", "Baruk Khazad", "Khazad ai-menu", \
                             "Khazad-dum", })
#define BATTLE_CRY_ELVES   ({"Galadriel", "Gilthoniel, A Elbereth", \
                             "Aiya elenion ancalima", })
#define BATTLE_CRY_HOBBITS ({"For the Shire", })
#define BATTLE_CRY_HUMANS  ({"Aure entuluva", "Utulie'n aure", "Auta i lome", \
                             "For Arnor", })
#define BATTLE_CRY_THORNLIN ({"For Thornlin"})

#define LEAN_ITEMS  ({ "board", "door", "desk", "table", "tree" })
#define SIT_STRINGS ({ "close to the board", "near the door", \
                        "on the desk", "on the table", "by a tree" })
#define SIZE_OF_LEAN_ITEMS 5
#define FOOTWEAR    ({ "boots", "shoes", "footwear", "sandal" })
#define PEBBLES     ({ "nasty stones", "little pebbles", "tiny rocks", \
                       "sharp stones", "small rocks", "round pebbles", \
                       "minuscule rocks", "nasty rocks", "minuscule stones", \
                       "dirt", "sharp sand" })
#define SKILLED     ({ "skillfully", "clumsily", "expertly", "briefly", \
                       "shortly", "quickly", "slowly", "proficiently" })

/* Function name: filter_sword
 * Description  : Filters objects to test if they are a sword
 * Arguments    : object x
 * Returns      : 1 if x is a sword, 0 if not
 */
int
filter_sword(object x)
{
    return ((function_exists("create_object", x) == WEAPON_OBJECT)
           && (x->query_wt() == W_SWORD));
}
 
/* Function name: filter_cont
 * Description  : Filters objects to test if they are a container
 * Arguments    : object x
 * Returns      : 1 if x is a container, 0 if not
 */
int
filter_cont(object x)
{
    return (function_exists("create_object", x) == CONTAINER_OBJECT);
}
 
/* Function name: filter_weapons
 * Description  : Filters objects to test if they are a weapon
 * Arguments    : object x
 * Returns      : 1 if x is a weapon, 0 if not
 */
int
filter_weapons(object x)
{
    return (function_exists("create_object", x) == WEAPON_OBJECT);
}



public string
check_ready(object who)
{
    string message;

    if (environment(who) &&
      (message = environment(who)->query_prop(ROOM_M_NO_ATTACK)))
        return (stringp(message) ? message : "A divine presence prevents " +
            "any attack.\n");
}


public string
check_ready_enemy(object who, object target)
{
    string message;

    if (environment(who) &&
      (message = environment(who)->query_prop(ROOM_M_NO_ATTACK)))
        return (stringp(message) ? message : "A divine presence prevents " +
            "any attack.\n");
  
    if (message = target->query_prop(OBJ_M_NO_ATTACK))
        return (stringp(message) ? message : "A strong presence prevents " +
            "your attack.\n");
 
    if (who->query_met(target) && who->query_enemy(0) != target)
    {
        if (who->query_prop(LIVE_O_LAST_KILL) != target)
        {
            who->add_prop(LIVE_O_LAST_KILL, target);
            return "Attack " + target->query_the_name(who) + "? Please " +
                "confirm by trying again.\n";
        }
    }

    if (target != who->query_attack())
    {
        if (!F_DARE_ATTACK(who, target))
            return "Umm... no, You do not have enough self-discipline to " +
                "dare!\n";
    }
}

/* Function name: battle
 * Description  : Ranger emote to shout a battle cry (and attack enemy)
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
battle(string str)
{
    object enemy, *ob;
    string *cries = BATTLE_CRY, 
            ready,
            cry, 
            rname = this_player()->query_race_name();
 
    ready = check_ready(this_player());
    if (strlen(ready))
    {
        notify_fail(ready);
        return 0;
    }

    if (this_player()->query_guild_name_lay() == "Thornlin Militia")
        cries += BATTLE_CRY_THORNLIN;

    switch (rname)
    {
    case "dwarf":
        cries += BATTLE_CRY_DWARVES;
        break;
    case "elf":
    case "half-elf":
        cries += BATTLE_CRY_ELVES;
        break;
    case "hobbit":
        cries += BATTLE_CRY_HOBBITS;
        break;
    case "human":
        cries += BATTLE_CRY_HUMANS;
        break;
    default:
        break;
    }

    if (!stringp(str))
    {
        enemy = this_player()->query_attack();
        if (!objectp(enemy))
        {
            this_player()->command("$shout " + one_of_list(cries) + "!");
            return 1;
        }
        else
        {
            ob = ({ enemy });
        }
    }
    else
    {
        ob = parse_this(str, "%l");
    }

    if (!sizeof(ob))
    {
        write("You look warily around, ready for battle.\n");
        all(" looks warily around, ready for battle.\n");
        return 1;
    }

    if(sizeof(ob) > 1)
    {
        write("You cannot attack " + COMPOSITE_LIVE(ob) + " at the same " +
            "time, so you focus your attack on " + 
            ob[0]->query_the_name(this_player()) + ".\n");
        ob = ({ ob[0] });
    }

    ready = check_ready_enemy(this_player(), ob[0]);
    if (strlen(ready))
    {
        notify_fail(ready);
        return 0;
    }

    if (TP->query_attack() == ob[0])
    {
        cry = one_of_list(cries);
        actor("You shout out: " + cry + "!\nYou attack", ob, " with " +
            "renewed fervour.");
        target(" shouts out: " + cry + "!\n" + 
            capitalize(this_player()->query_pronoun()) + " attacks you " +
            "with renewed fervour.", ob);
        all2act(" shouts out: " + cry + "!\n" +
            capitalize(this_player()->query_pronoun()) +
            " attacks", ob, " with renewed fervour.\n", ob);
        return 1;
    }
    
    cry = one_of_list(cries);
    actor("You shout out: " + cry + "!\nYou join battle with", ob, ".");
    target(" shouts out: " + cry + "!\n" + 
        capitalize(this_player()->query_pronoun()) + " joins battle with you.",
        ob);
    all2act(" shouts out: " + cry + "!\n" + 
        capitalize(this_player()->query_pronoun()) + " joins " + "battle with",
        ob, ".");

        this_player()->attack_object(ob[0]);

    return 1;
}


/* Function name: hail
 * Description  : Ranger emote to greet others.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
hail(string str)
{
    object *oblist;
    string *hails = ({"the Valar", "the Free Peoples", "the Free Peoples", 
                      "Arnor", "Ithilien"});
    int     cno;

    cno = TP->query_ranger_level();

    if (!strlen(str))
    {
        write("You hail everybody in the name of "+hails[cno]+".\n");
        all(" bows deeply, saying: Hail "+hails[cno]+"!");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        NFN0("Hail who?");
    }

    actor("You hail", oblist, " in the name of "+hails[cno]+".");
    target(" bows deeply before you, saying: Hail "+hails[cno]+"!", oblist);
    all2act(" bows before", oblist, " saying: Hail "+hails[cno]+"!");
    return 1;
}

/* Function name: kisshand
 * Description  : Ranger emote to kiss the hand of another player.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
kisshand(string str)
{
    object *oblist;
 
    oblist = parse_this(str, "[the] [hand] [of] [the] %l");
 
    if (!sizeof(oblist))
    {
        notify_fail("Kiss the hand of whom?\n");
        return 0;
    }
    else
    {
        oblist = ({ oblist[0] });
    }
 
    actor("You take", oblist, "'s hand into yours, and gently kiss it.");
    target(" takes your hand into " + this_player()->query_possessive() +
        (this_player()->query_gender() == 1 ? "s" : "") + ", and gently " +
        "kisses it.", oblist);
    all2actbb(" takes", oblist, "'s hand into " + 
        this_player()->query_possessive() + " own, and gently kisses it.");
    return 1;
}

/* Function name: offer
 * Description  : Ranger emote to offer hand to be kissed by another player.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
offer(string str)
{
    object *oblist;
 
    oblist = parse_this(str, "[my] 'hand' [to] [the] %l");
 
    if (!sizeof(oblist))
    {
        notify_fail("Offer your hand to whom?\n");
        return 0;
    }
    else
    {
        oblist = ({ oblist[0] });
    }
 
    actor("You offer your hand to", oblist, " so that " + 
        oblist[0]->query_pronoun() + " may kiss it.");
    target(" offers " + this_player()->query_possessive() + " hand to you, " +
        "so that you may kiss it.", oblist);
    all2actbb(" offers " +  this_player()->query_possessive() + " hand to", 
        oblist, " so that " + oblist[0]->query_pronoun() + " may kiss it.");
    return 1;
}

/* Function name: rassess
 * Description  : Ranger emote to assess the gear of a player.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rassess(string str)
{
    object *oblist,
           ob;
    string gear;

    if (!strlen(str) || str == "me" || str == "myself")
    {
        ob = this_player();
    }
    else
    {
        oblist = parse_this(lower_case(str), "%l");
        if (!sizeof(oblist))
        {
            notify_fail("You don't see anyone like that.\n");
            return 0;
        }

        ob = oblist[0];
    }

    if (living(ob))
    {
        if (ob == this_player())
        {
            write("You check over your gear.\n");
        }
        else
        {
            actor("You look", ({ ob }), " over, assessing " + 
                ob->query_possessive() + " gear.");
            target(" looks you over, assessing your gear.", ({ ob }));
            all2actbb(" looks over", ({ ob }), ", assessing " + 
                ob->query_possessive() + " gear.");
        }

        gear = ob->show_wielded(this_player());
        if (strlen(gear))
        {
            write(gear);
        }
        else
        {
            write(capitalize(ob->query_pronoun()) + " is not wielding " +
                "anything.\n");
        }

        gear = ob->show_worn(this_player());
        if (strlen(gear))
        {
            write(gear);
        }
        else
        {
            write(capitalize(ob->query_pronoun()) + " is not wearing " +
                "anything.\n");
        }

        return 1;
    }

    notify_fail("You don't see anyone like that around here.\n");
    return 0;
}

/* Function name: rbearing
 * Description  : Ranger emote to learn where they are standing in the world.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rbearing(string str)
{
    object clock;
    string time, 
          *lands, 
           domain, 
           txt;

    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        write("You try to find your bearing, but you are unable to " +
            "see the sky.\n");
        return 1;
    }

    domain = environment(this_player())->query_domain();
    if (domain != "Gondor" && domain != "Shire")
    {
        txt = "the sky";
    }
    else
    {
        clock = find_object(CLOCK);
        time = clock->query_time_of_day();
        switch(time)
        {
        case "morning":
        case "noon":
        case "afternoon":
            txt = "the sun";
            break;
        default:
            if (clock->query_moon() != "dark")
                txt = "the stars and the moon";
            else
                txt = "the stars";
            break;
        }

    }

    write("You study " + txt + ", trying to find your bearing.\n");
    allbb(" pauses for a while, studying " + txt + " to find " +
        this_player()->query_possessive() + " bearing.");

    switch(domain)
    {
    case "Gondor":
        lands = explode(file_name(environment(this_player())), "/");
        lands -= ({ "" });
        lands -= ({ "d" });
        lands -= ({ "Gondor" });
        lands -= ({ "lands" });
        lands -= ({ "common" });
        lands -= ({ "rhovanion" });

        switch(lands[0])
        {
        case "mordor":
            txt = "in the land of Mordor";
            break;
        case "ithilien":
            txt = "in the contested land of Ithilien, in Gondor";
            break;
        case "arnor":
            txt = "in the lands which once belonged to the ancient realms of Arnor";
            break;
        case "lebennin":
            txt = "in the province of Lebennin, in Gondor";
            break;
        case "rohan":
            txt = "in the kingdom of Rohan, land of the horsemen";
            break;
        case "anorien":
            txt = "in the province of Anorien, in Gondor";
            break;
        case "dunland":
            txt = "in Dunland";
            break;
        case "tharbad":
            txt = "near Tharbad, in the lands of Eriador";
            break;
        case "anduin":
        case "river":
            txt = "near the Anduin river in Gondor";
            break;
        case "minas":
            txt = "in the city of Minas Tirith";
            break;
        case "morgul":
            txt = "in the city of Minas Morgul";
            break;
        case "pelargir":
            txt = "in the city of Pelargir";
            break;
        case "mirkwood":
            txt = "in Mirkwood forest";
            break; 
        case "rhovanion":
            txt = "in the wilds of Rhovanion";
            break;           
        default:
            txt = "in the realm of Gondor";
            break;
        }
        break;

    case "Shire":
        txt = "in the Lands of the Shire";
        break;

    case "backbone":
    case "Wiz":
        txt = "in the lands of the immortals";
        break;

    default:
        txt = "in the lands of " + domain;
        break;
    }

    write("Studying your surroundings, you believe you are " + txt + ".\n");
    return 1;
}

/* Function name: rbow
 * Description  : Ranger emote to bow in greeting to another player.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rbow(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You lower your gaze briefly as you bow gracefully.\n");
        allbb(" lowers " + this_player()->query_possessive() + " gaze " + 
            "briefly as " + this_player()->query_pronoun() + " bows " +
            "gracefully.");
        return 1;
    }

    oblist = parse_this(str, "[before] / [to] %l");
    if (!sizeof(oblist))
    {
        notify_fail("You don't see that person here.\n");
        return 0;
    }

    actor("You lower your gaze with respect and admiration " +
        "as you bow before", oblist, " in brief, yet graceful manner.");
    target(" lowers " + this_player()->query_possessive() + " gaze with " +
        "deep respect and admiration as " + this_player()->query_pronoun() + 
        " bows before you in a brief, yet graceful manner.", oblist);
    all2actbb(" lowers " + this_player()->query_possessive() + " gaze " +
        "with deep respect and admiration as " + 
        this_player()->query_pronoun() + " bows before", oblist, " in a " +
        "brief, yet graceful manner.");
    return 1; 
}

/* Function name: rbrush
 * Description  : Ranger emote to brush dirt off the clothing.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rbrush(string str)
{
    string *actions = ({ "brush the dust and dirt", "brush some dirt",
                         "shake the dust", "shake the leaves",
                         "shake some grass and leaves" });
    string action;
    object *bodywear, *oblist;
    string clothes;
 
    if (stringp(str))
    {
        oblist = parse_this(lower_case(str), "[some] [dirt] [off] [of] %l");
        if (!sizeof(oblist))
        {
            notify_fail("Brush some dirt off of whom?\n");
            return 0;
        }

        actor("You brush the dirt and dust off of", oblist, ".");
        target(" brushes the dirt and dust off of you.", oblist);
        all2act(" brushes the dirt and dust off of", oblist, ".");
        return 1;
    }
 
    /* Find worn cape or cloak */
    bodywear =  this_player()->query_clothing(A_ROBE) ;
 
    /* if no cape or cloak find another torso covering armour */
    if (!sizeof(bodywear)) 
    {
        bodywear =  this_player()->query_clothing(TS_BACK) &
                this_player()->query_clothing(TS_CHEST);
    }
 
    if (sizeof(bodywear))
    {
        clothes = bodywear[0]->short();
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

/* Function name: rburp
 * Description  : Ranger emote to burp in satisfaction.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rburp(string str)
{
    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        write("You feel an urge to burp after the hearty meal, " +
            "but politely hide it as best you can since you are " +
            "not out in the wilderness by a campfire.\n");
        allbb(" politely attempts to hide an urge to belch heartily " +
            "after the meal.");
        return 1;
    }

    write("To show your appreciation for the meal, you let out a " +
        "hearty belch.\n");
    all(" shows " + this_player()->query_possessive() + " appreciation " +
        "for the meal with a hearty belch.");
    this_player()->reveal_me(1);
    return 1;
}

/* Function name: rcheck
 * Description  : Ranger emote to check the contents of a container.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rcheck(string str)
{
    mixed *oblist;
    object ob;

    if (!strlen(str))
    {
        notify_fail("Check what container?\n");
        return 0;
    }

    if (!parse_command(lower_case(str), environment(this_player()), 
      "[the] %i", oblist) || !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        notify_fail("You don't have any such container.\n");
        return 0;
    }

    oblist = filter(oblist, filter_cont);
    if (!sizeof(oblist))
    {
        notify_fail("That's not a container.\n");
        return 0;
    }

    ob = oblist[0];
    if (living(ob))
    {
        notify_fail("That's not a container.\n");
        return 0;
    }

    if (!ob->query_prop(CONT_I_CLOSED))
    {
        write("You rummage through your " + ob->short() + ", taking a quick " +
            "inventory to be sure you have everything needed for what lies " +
            "ahead.\n");
        ob->show_visible_contents(this_player());
        allbb(" rummages through " + this_player()->query_possessive() + " " + 
           ob->short() + ", taking a quick inventory to be sure " + 
           this_player()->query_pronoun() + " has everything needed for " +
           "what lies ahead.");
     }
     else
     {
        write("You check your " + ob->short() + ", making certain that " +
            "it is securely closed.\n");
        allbb(" checks " + this_player()->query_possessive() + " " + 
            ob->short() + ", making certain that it is securely closed.\n");
     }

    return 1;
}

/* Function name: rcheek
 * Description  : Ranger emote to kiss the cheek of another player.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rcheek(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        notify_fail("Kiss who on the cheek?\n");
        return 0;
    }

    oblist = parse_this(str, "[with] %l [at] / [on] [the] [cheek]");
    if (!sizeof(oblist))
    {
        notify_fail("You don't see that person here.\n");
        return 0;
    }

    oblist = ({ oblist[0] });
    actor("You kiss", oblist, " on each cheek, and embrace " +
        oblist[0]->query_objective() + " in the warm hug you reserve for " + 
        "long-time friends.");
    target(" kisses you on each cheek, and embraces you in the warm " +
        "hug " + this_player()->query_pronoun() + " reserves for " +
        "long-time friends.", oblist);
    all2actbb(" kisses", oblist, " on each cheek, and embraces " + 
        oblist[0]->query_objective() + " in a warm hug reserved for " +
        "long-time friends.");
    return 1;
}

/* Function name: rcloak
 * Description  : Ranger emote to draw the cloak tighter around body.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rcloak(string str)
{
    object *cloak = this_player()->query_clothing(TS_ROBE);
    int size = sizeof(cloak) - 1;

    if (size == -1 || !objectp(cloak[size]))
    {
        notify_fail("You are not wearing a cloak!\n");
        return 0;
    }

    write("You draw the " + cloak[size]->short() +
        " about your body for warmth.\n");
    allbb(" draws " + this_player()->query_possessive() + " " + 
        cloak[size]->short() + " about " + this_player()->query_objective() + 
        "self for warmth.");
    return 1;
}

/* Function name: rcurtsey
 * Description  : Ranger emote to curtsey politely.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rcurtsey(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You swiftly kick one heel behind the other in a brief " +
            "but charming curtsey.\n");
        all(" swiftly kicks one heel behind the other in a brief yet " +
            "charming curtsey.");
        return 1;
    }

    oblist = parse_this(str, "[before] %l");
    if (!sizeof(oblist))
    {
        notify_fail("You don't see that person here.\n");
        return 0;
    }

    actor("You swiftly kick one heel behind the other in a brief " +
        "but charming curtsey before", oblist, ", lowering your " +
        "gaze respectfully.");
    target(" swiftly kicks one heel behind the other in a brief yet " +
        "charming curtsey before you, lowering " + 
        this_player()->query_possessive() + " gaze respectfully.", oblist);
    all2act(" swiftly kicks one heel behind the other in a brief yet " +
        "charming curtsey before", oblist, ", lowering " + 
        this_player()->query_possessive() + " gaze respectfully.");
    return 1;
}

/* Function name: rdirt
 * Description  : Ranger emote to sniff the dirt in a room.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rdirt(string str)
{
    if (!environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        write("You pick up a handful of dirt and smell it for a scent.\n");
        allbb(" picks up a handful of dirt and holds it close to " + 
            this_player()->query_possessive() + " nose.");
        return 1;
    }

    notify_fail("You need to be outside to smell the dirt!\n");
    return 0;
}

/* Function name: rembrace
 * Description  : Ranger emote to give a warm hug to another player.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rembrace(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        notify_fail("Embrace who?\n");
        return 0;
    }

    oblist = parse_this(str, "%l");
    if (!sizeof(oblist))
    {
        notify_fail("You don't see that person here.\n");
        return 0;
    }

    oblist = ({ oblist[0] });
    actor("You embrace", oblist, " in a warm, sincere hug.");
    target(" embraces you in a warm, sincere hug, and a scent of fresh " +
        "herbs intoxicates your senses.", oblist);
    all2actbb(" embraces", oblist, " in a warm, sincere hug.");
    return 1;
}

/* Function name: rgazefire
 * Description  : Ranger emote to gaze intently into a campfire.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rgazefire(string str)
{
    string firestr;

    if (present("campfire", environment(this_player())))
        firestr = "campfire";
    else if (environment(this_player())->query_prop(OBJ_I_HAS_FIRE))
        firestr = "fire";
    else
    {
        notify_fail("But there is no campfire here!\n");
        return 0;
    }

    write("You thoughtfully recollect the recent events while gazing into " +
        "the red glow and the flickering flames of the " + firestr + ".\n");
    say("A fiery glint dances in " + QTPNAME(this_player()) + " eyes as " +
        this_player()->query_pronoun() + " gazes intently at the flickering " +
        "flames of the " + firestr + ", obviously lost in thought.\n", 
        this_player());
    return 1;
}

/* Function name: rgleam
 * Description  : Ranger emote to display tall stature (Dunedain and Elves only)
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rgleam(string str)
{
    object cloak,
           *oblist,
           scabbard,
           *weapons;
    string msg1, 
           msg2;
 
    if (IS_DUNADAN(this_player()) || (this_player()->query_race() == "elf"))
    {
        msg1 = "You straighten up and display your tall stature, keen " +
            "and commanding.";
        msg2 = " stands up, and seems suddenly to grow taller. In " +
            this_player()->query_possessive() + " eyes gleams " +
            "a light, keen and commanding.";
        weapons = this_player()->query_weapon(-1);
        if (objectp(scabbard = present("scabbard", this_player())))
            weapons += all_inventory(scabbard);

        if (sizeof(weapons = filter(weapons, filter_sword)))
        {
            if (objectp(cloak = this_player()->query_armour(TS_ROBE)))
            {
                msg1 += " Throwing back your " + cloak->short() + ", you";
                msg2 += " Throwing back " + this_player()->query_possessive() + 
                    " " + cloak->short() + ", " + 
                    this_player()->query_pronoun();
            }
            else
            {
                msg1 += " You";
                msg2 += " " + capitalize(this_player()->query_pronoun());
            }


            msg1 += " lay your hand on the hilt of your ";
            msg2 += " lays " + this_player()->query_possessive() + " hand " +
                "on the hilt of " + this_player()->query_possessive() + " ";

            if (objectp(scabbard) && present(weapons[0], scabbard))
            {
                msg1 += "sheathed ";
                msg2 += "sheathed ";
            }

            msg1 += "sword.";
            msg2 += "sword.";
        }

        write(msg1 + "\n");
        all(msg2);
        this_player()->reveal_me(1);
        return 1;
    }

    notify_fail("Only Dunedain and Elves can use their tall stature " +
        "this way.\n");
    return 0;
}

/* Function name: rgrim
 * Description  : Ranger emote to look grimly about.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rgrim(string str)
{
    write("You feel alone in this world.\n");
    allbb(" gets a lonely, grim look on " + this_player()->query_possessive() +
        " face.");
    return 1;
}

/* Function name: rgrip
 * Description  : Ranger emote to tighten grip on sword.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rgrip(string str)
{
    object scabbard, *weapons = this_player()->query_weapon(-1);

    if (sizeof(weapons))
    {
        write("You tighten your grip on the " + weapons[0]->short() + ".\n");
        allbb(" tightens " + this_player()->query_possessive() + " grip on " +
          this_player()->query_possessive() + " " + weapons[0]->short() + ".");
        return 1;
    }

    scabbard = present("scabbard", this_player());
    if (objectp(scabbard) && sizeof(all_inventory(scabbard)))
    {
        write("You take a firm grip on your sword. ");
        all(" takes a firm grip on " + this_player()->query_possessive() +
            " sword. ");
        this_player()->command("$draw");
        return 1;
    }

    notify_fail("You have no weapon wielded!\n");
    return 0;
}

/* Function name: rhome
 * Description  : Ranger emote to look in the direction of the home guildhouse.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rhome(string str)
{
    int     co = TP->query_ranger_level();
    string *home_desc,
           *home_dir;

    home_desc = ({ "Middle Earth", "Gondor", "Gondor", "Arnor", "Ithilien" });
    home_dir = ({ "sky", "South", "South", "North", "East" });

    write("You look in the direction of " + home_desc[co]
      + ", sighing wistfully.\n");
    allbb(" turns and looks away to the " + home_dir[co]
      + ", falling silent for a while.");
    return 1;
}

/* Function name: rhush
 * Description  : Ranger emote to hush others.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rhush(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You whisper 'Hush!', and motion for all to be silent.\n");
        allbb(" whispers 'Hush!', and motions with " + 
            this_player()->query_possessive() + " hand for silence.");
        return 1;
    }

    oblist = parse_this(str,"[at] [the] %l");
    if (!sizeof(oblist))
    {
        write("You whisper 'Hush!' and motion for all to be silent.\n");
        allbb(" whispers 'Hush!', and motions with " + 
            this_player()->query_possessive() + " hand for you all to be " +
            "silent.");
        return 1;
    }
    else 
    {
        actor("You whisper 'Hush!', and motion for", oblist, " to be silent.");
        targetbb(" whispers 'Hush!', and motions with " + 
            this_player()->query_possessive() + " hand for you to be silent.",
            oblist);
        all2actbb(" whispers 'Hush!', and motions with " + 
            this_player()->query_possessive() + " hand for", oblist, " to " +
            "be silent.");
        return 1;
    }
}

/* Function name: rinspect
 * Description  : Ranger emote to inspect a weapon for quality.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rinspect(string str)
{
    object *weapons,
           weapon,
           scabbard;

    if (!strlen(str))
    {
        weapons = this_player()->query_weapon(-1);
        scabbard = present("scabbard", this_player());
        if (objectp(scabbard = present("scabbard", this_player())))
            weapons += all_inventory(scabbard);

        if (sizeof(weapons))
            weapon = weapons[0];
        else
        {
            notify_fail("But you have no weapon ready!\n");
            return 0;
        }
    }
    else
    {
        if (!parse_command(lower_case(str), this_player(), "[the] %i", 
          weapons) || !sizeof(weapons = NORMAL_ACCESS(weapons, 0, 0)))
        {
            notify_fail("You have no such weapon available!\n");
            return 0;
        }

        weapons = filter(weapons, filter_weapons);
        if (!sizeof(weapons))
        {
            notify_fail("That is not a weapon.\n");
            return 0;
        }

        weapon = weapons[0];
    }

    write("You carefully check the " + weapon->short() + " for any " +
        "notches or signs of damage or wear, to make sure you are " +
        "prepared for the fight that lies ahead.\n" +
        weapon->wep_condition_desc());
 
    allbb(" carefully examines " + this_player()->query_possessive() + " " + 
        weapon->short() + " to make sure it is ready for the fight to come.");
    return 1;
}


/* Function name: rlaugh
 * Description  : Ranger emote to laugh in a hearty way.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rlaugh(string str)
{
    object *oblist;
 
    if (!strlen(str))
    {
        write("You laugh the hearty laugh of a ranger.\n");
        all(" laughs the hearty laugh of a ranger.");
        this_player()->reveal_me(0);
        return 1;
    }

    oblist = parse_this(str, "[at] %l");
    if (!sizeof(oblist))
    {
        notify_fail("Laugh how?\n");
        return 0;
    }

    target(" laughs at you with the hearty laugh of a ranger.", oblist);
    actor("You laugh at", oblist, " with the hearty laugh of a ranger.");
    all2act(" laughs at", oblist, " with the hearty laugh of a ranger.");
    TP->reveal_me(0);
    return 1;
}


/* Function name: rlisten
 * Description  : Ranger emote to listen to the sounds of battle.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rlisten(string str)
{
    write("Your mouth draws to a deep frown as you listen intently to " +
        "the sounds of the distant battle.\n");
    allbb("'s mouth draws to a deep frown as " + 
        this_player()->query_pronoun() + " listens " + "intently to the " +
        "sounds of the distant battle.");
    return 1;
}

/* Function name: rnod
 * Description  : Ranger emote to nod in acknowledgement.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rnod(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You nod slightly, a wary look in your eyes.\n");
        allbb(" nods slightly, a wary look in " + 
            this_player()->query_possessive() + " eyes.");
        return 1;
    }

    oblist = parse_this(str, "[at] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Nod at whom?\n");
        return 0;
    }

    actor("You nod slightly at", oblist, ", a wary look in your eyes.");
    target(" nods slightly at you, a wary look in " + 
        this_player()->query_possessive() + " eyes.", oblist);
    all2actbb(" nods slightly at", oblist, ", a wary look in " +
        this_player()->query_possessive() + " eyes.");
    return 1;
}

/* Function name: rparley
 * Description  : Ranger emote to offer a sign of peace.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rparley(string str)
{
    object *oblist;

    if (sizeof(this_player()->query_weapon(-1)))
    {
        notify_fail("Better unwield your weapon before you try to parley.\n");
        return 0;
    }

    if (!strlen(str))
    {
        write("You hold your empty hand out in a gesture of parley.\n");
        allbb(" holds " + this_player()->query_possessive() + " empty " +
            "hand out in a gesture of parley.");
        return 1;
    }

    oblist = parse_this(str, "[with] %l");

    if (!sizeof(oblist))
    {
        notify_fail("You don't see any such being here.\n");
        return 0;
    }

    targetbb(" holds " + this_player()->query_possessive() + " empty hand " +
        "up towards you in a gesture of parley.", oblist);
    actor("You hold your empty hand out as a gesture for parley to", 
        oblist, ".");
    all2actbb("  holds " + this_player()->query_possessive() + " empty " +
        "palm out as a gesture of parley to", oblist, ".");
    return 1;
}

/* Function name: rpatience
 * Description  : Ranger emote to counsel patience in someone.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rpatience(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You counsel everyone to have patience.\n");
        all(" counsels everyone to be patient.");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");
    if (str == "me" || str == "myself")
    {
        write("You decide to be more patient.\n");
        all(" decides to be more patient.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        write("You counsel everyone to be patient.\n");
        all(" counsels everyone to be patient.");
        return 1;
    }

    actor("You counsel", oblist, " to be patient.");
    target(" counsels you to be patient.", oblist);
    all2act(" counsels", oblist, " to be patient.");
    return 1;
}

/* Function name: rpick
 * Description  : Ranger emote to pick the teeth.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rpick(string str)
{
    write("You pick your teeth.\n");
    allbb(" picks up a stick and picks " + this_player()->query_possessive() +
      " teeth.");
    return 1;
}

/* Function name: rpoke
 * Description  : Ranger emote to poke a burning campfire.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rpoke(string str)
{
    string firestr;

    if (present("campfire", environment(this_player())))
        firestr = "campfire";
    else if (environment(this_player())->query_prop(OBJ_I_HAS_FIRE))
        firestr = "fire";
    else
    {
        notify_fail("But there is no campfire here!\n");
        return 0;
    }

    if (!environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        write("You pick up a stick and poke around in the glowing embers " +
            "of the " + firestr + " with it. Sparks fly several feet in " +
            "the air.\n");
        all(" picks up a stick and pokes the glowing embers and faggots " +
            "of the " + firestr + " with it, and sparks fly several feet " +
            "in the air.");
    }
    else
    {
        write("You pick up a bit of firewood and poke around in the " +
            "glowing embers of the " + firestr + " with it, causing " +
            "sparks to fly.\n");
        all(" picks up a bit of firewood and pokes the glowing embers " +
            "of the " + firestr + " with it, causing sparks to fly.");
    }

    return 1;
}

/* Function name: rpray
 * Description  : Ranger emote to pray to the Valar.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rpray(string str)
{
    mixed *oblist, 
          *weapons;
    string prayer, 
           blade;

    if (strlen(str))
    {
        str = lower_case(str);

        if (!parse_command(str, ({}), "'to' %w", prayer) &&
            (!parse_command(LOW(str), all_inventory(ENV(TP)),
                "'to' %w 'for' %l", prayer, oblist) ||
             !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0))))

        {
            notify_fail("Pray to which Valar (for whom)?\n");
            return 0;
        }
    }

    if (sizeof(oblist) && oblist[0] == this_player())
        oblist = ({ });

    switch(lower_case(prayer))
    {
    case "yavanna":
    case "kementari":
        write("You kneel and offer prayer to Yavanna Kementari, asking " +
            "that spring and regrowth will never fail these lands.\n");
        all(" kneels and offers prayer to Yavanna Kementari, asking that " +
            "spring and regrowth will never fail these lands.");
        return 1;
        break;

    case "aule":
    case "mahal":
    blade = "blade";
 
    if (!sizeof(oblist))
    { 
        weapons = this_player()->query_weapon(-1);
        if (sizeof(weapons))
            blade = weapons[0]->short();
         
        write("You close your eyes briefly as you pray to Aule Mahal, " +
            "asking that your " + blade  + " will prove as strong and " +
            "steadfast as your heart.\n");
        all(" closes " + this_player()->query_possessive() + " eyes briefly " +
            "as " + this_player()->query_pronoun() +  " prays to Aule " +
            "Mahal, asking that " + this_player()->query_possessive() + " " + 
            blade + " will prove as strong and steadfast as " + 
            this_player()->query_possessive() +  " heart.");
    }
    else 
    {
        actor("You close your eyes briefly as you pray to Aule Mahal, " +
            "asking that", oblist, "'s blade and heart will prove " +
            "equally strong and steadfast.");
        target(" closes "+ this_player()->query_possessive() + " eyes " +
            "briefly as " + this_player()->query_pronoun() + " prays to " +
            "Aule, asking that your blade will prove as strong and " +
            "steadfast as your heart.", oblist);
        all2act(" closes " + this_player()->query_possessive() + " eyes " +
            "briefly as " + this_player()->query_pronoun() + " prays to " +
            "Aule Mahal, asking that", oblist, "'s blade and heart will " +
            "prove equally strong and steadfast.");
    }

    return 1;
    break;

    case "manwe":
    case "sulimo":
        if (!sizeof(oblist)) 
        {
            write("Turning your face to the West, you offer a prayer to " +
                "Manwe Sulimo the High King of Arda, asking him to rekindle " +
                "your courage.\n");
            all(" turns " + this_player()->query_possessive() + " face to " +
                "the West, and offers a prayer to Manwe Sulimo the High " +
                "King of Arda, asking him to rekindle " + 
                this_player()->query_possessive() + " courage.");
        }
        else 
        {
            actor("Turning your face to the West, you offer a prayer to " +
                "Manwe Sulimo the High King of Arda, asking him to rekindle",
                oblist, "'s courage.");
            target(" turns " + this_player()->query_possessive() + " face " +
                "to the West, and offers a prayer to Manwe Sulimo the High " +
                "King of Arda, asking him to rekindle your courage.", oblist);
            all2act(" turns " + this_player()->query_possessive() + " face " +
                "to the West, and offers a prayer to Manwe Sulimo the High " +
                "King of Arda, asking him to rekindle", oblist, "'s heart.");
        }
        return 1;
        break;

    case "nienna":
        if (!sizeof(oblist)) 
        {
            write("You bend your head and give prayer to Nienna, asking that " +
                "she will strengthen your heart and turn your sorrow to " +
                "wisdom.\n");
            all(" bends " + this_player()->query_possessive() + " head and " +
                "gives prayer to Nienna, asking that she will turn " + 
                this_player()->query_possessive() + " sorrow into wisdom " +
                "and strenghten " + this_player()->query_possessive() +
                " heart.");
        }
        else 
        {
            actor("You bend your head and give prayer to Nienna, asking " +
                "that she will turn sorrow into wisdom and strengthen",
                oblist, "'s heart.");
            target(" bends " + this_player()->query_possessive() + " head " +
                "and gives prayer to Nienna, asking that she will turn " +
                "your sorrow to wisdom and strengthen your heart.", oblist);
            all2act(" bends " + this_player()->query_possessive() + " head " +
                "and gives prayer to Nienna, asking that she will turn " +
                "sorrow to wisdom and strengthen", oblist, "'s heart.");
        }
        return 1;
        break;

    case "orome":
    case "araw":
        if (!sizeof(oblist)) 
        {
            write("You stand still and give prayer to Orome Araw, asking " +
                "for a bountiful hunt.\n");
            all(" stands still for a moment praying to Orome Araw, asking " +
                "for a bountiful hunt.");
        }
        else 
        {
            actor("You stand still and give prayer to Orome Araw, asking " +
                "for a bountiful hunt for", oblist, ".");
            target(" stands still for a moment, praying for Orome Araw to " +
                "provide you with a bountiful hunt.", oblist);
            all2act(" stands still for a moment praying to Orome Araw, " +
                "asking for a bountiful hunt for", oblist, ".");
        }
        return 1;
        break;

    case "ulmo":
        if (!sizeof(oblist)) 
        {
            write("You clasp your hands and give prayer to Ulmo, asking " +
                "that he provide calm waters for the coming sea-voyage.\n");
            all(" clasps " + this_player()->query_possessive() + " hands " +
                "praying to Ulmo, asking for calm waters for the coming " +
                "sea-voyage.");
        }
        else 
        {
            actor("You clasp your hands and give prayer to Ulmo, asking " +
                "that he provide calm waters for", oblist, "'s coming " +
                "sea-voyage.");
            target(" clasps " + this_player()->query_possessive() + " hands " +
                "in prayer to Ulmo, asking for calm waters for your coming " +
                "sea-voyage.", oblist);
            all2act(" clasps " + this_player()->query_possessive() + 
                " hands in prayer to Ulmo, asking for calm waters for",
                oblist, "'s coming sea-voyage.");
        }
        return 1;
        break;

    case "tulkas":
    case "astaldo":
        if (!sizeof(oblist)) 
        {
            write("You kneel and give prayer to Tulkas, asking that he " +
                "stand with you in the coming battle.\n");
            all(" kneels and prays to Tulkas, asking for prowess in the "+
                "coming battle.");
        }
        else 
        {
            actor("You kneel and give prayer to Tulkas, asking that he " +
                "stand with", oblist, " in the coming battle.");
            target(" kneels, praying to Tulkas that he stand with you in " +
                "the coming battle.", oblist);
            all2act(" kneels, praying to Tulkas that he stand with", oblist,
                " in the coming battle.");
        }
        return 1;
        break;

    case "elbereth":
    case "varda":
        if (!sizeof(oblist)) 
        {
            write("You raise your hands towards the sky and give prayer to " +
                "Elbereth, asking her to shine a light on the paths of your " +
                "journey.\n");
            all(" raises " + this_player()->query_possessive() + " hands " +
                "towards the sky, praying for Elbereth to shine a light on " +
                "the paths of " + this_player()->query_possessive() + 
                " journey.");
        }
        else 
        {
            actor("You raise your hands towards the sky and give prayer to " +
                "Elbereth, asking her to shine a light on the paths of",
                oblist, "'s journey.");
            target(" raises " + this_player()->query_possessive() + 
                " hands towards the sky, praying for Elbereth to shine a " +
                "light on the paths of your journey.", oblist);
            all2act(" raises " + this_player()->query_possessive() + 
                " hands towards the sky, praying for Elbereth to shine a " +
                "light on the paths of", oblist, "'s journey.");
        }
        return 1;
        break;
    default:
        write("You stop and pray in reverence of Eru Iluvatar and all the " +
            "Valar who created the world.\n");
        all(" prays in reverence of Eru Iluvatar and all the Valar who " +
            "created the world.");
        return 1;
        break;
    }
}

/* Function name: rrelief
 * Description  : Ranger emote to breathe a sigh of relief.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rrelief(string str)
{
    write("You breathe a sigh of relief.\n");
    all(" breathes a sigh of relief.");
    return 1;
}

/* Function name: rrest
 * Description  : Ranger emote to rest on the ground.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rrest(string str)
{
    write("You cast yourself on the ground to "+
        "relax, unable to remember when you last had a chance to rest.\n");
    allbb(" casts "+ this_player()->query_objective() + "self on the ground " +
        "to relax, unable to remember when " + this_player()->query_pronoun() +
        " last had a chance to rest.");
    return 1;
}

/* Function name: rrecall
 * Description  : Ranger recall emote
 *                Three usages:
 *                rrecall (default)
 *                rrecall <tale> (history)
 *                rrecall <target> (advanced)
 * Created by Skippern, May 2000
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
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
        write("You feel your resolve strengthen as you recall the " +
            "staunch faith of Hurin the Steadfast.\n");
        allbb("'s face grows stern and resolved as " +
            this_player()->query_pronoun() + " recalls the " +
            "staunch faith of Hurin the Steadfast.");
        return 1;
    }
 
    /* Fingolfin */
    if (str == "fingolfin")
    {
        write("You are filled with new courage as you recall the valour " +
            "of Fingolfin, who knocked on the gates of Angband.\n");
        allbb("'s eyes sparkle brightly as " +
            this_player()->query_pronoun() + " recalls the valour " +
            "of Fingolfin, who knocked on the gates of Angband.");
        return 1;
    }
 
    /* Beren and Luthien */
    if ((str == "beren" || str == "luthien"))
    {
        write("Your gaze grows distant for a moment, as you recall " +
            "how the love between Beren and Luthien made the dark " +
            "powers yield.\n");
        allbb(" gets a distant thoughtful look in " +
            this_player()->query_possessive() + " eyes, recalling how the " +
            "love between Beren and Luthien made the dark powers yield.");
        return 1;
    }
 
    /* We want to make sure the person is present, and whether he is
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
                "deceit wrought by the Enemy in ages past.");
            all2actbb(" glances coldly at", oblist,", recalling the lies " +
                "and deceit wrought by the Enemy in ages past.");
            targetbb(" glances coldly at you, recalling the lies " +
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
                "tales of battles where " + race + " and " + me + " were " +
                "united against the enemy.");
            all2actbb(" smiles confidently at", oblist," recalling the " +
                "tales of battle where " + race + " and " + me + " were " +
                "united against the enemy.");
            targetbb(" smiles confidently at you recaling the tales of " +
                "battle where " + race + " and " + me + " were united " +
                "against the enemy.", oblist);
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
                "many times " + this_player()->query_pronoun() + " kept " +
                "bandits from the hobbits' homes.");
            targetbb(" smiles confidently at you recalling the many times" +
                " " + this_player()->query_pronoun() + " has kept bandits " +
                "from your homes.", oblist);
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

/* Function name: rrub
 * Description  : Ranger emote to rub the guild token.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rrub(string str)
{
    object  tp = TP,
            token = present("ranger_guild_object", tp);
    string *tok_desc = ({"token", "ring", "ring", "brooch", "amulet"});
    string *mem_text;
    int     co = TP->query_ranger_level();

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

/* Function name: rsit
 * Description  : Ranger emote to sit on a nearby object.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
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

/* Function name: rstone
 * Description  : Ranger emote to remove a stone from footwear.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
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
        footwear = objs[0]->short();
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

/* Function name: rstudy
 * Description  : Ranger emote to study environment/other players.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rstudy(string str)
{
    object *oblist;
    
    if (!strlen(str))
    {
        write("You study your environment carefully.\n");
        allbb("'s eyes study " + this_player()->query_possessive() +
          " environment " + "with great care, seemingly ready to counter " +
          "anything that may happen.");
        return 1;
    }

    oblist = parse_this(str, "[at] %l");
    if (!sizeof(oblist))
    {
        notify_fail("Study Whom?\n");
        return 0;
    }

    if (sizeof(oblist) == 1)
    {
        actor("You study", oblist, " carefully, trying to guess what " + 
            oblist[0]->query_possessive() + " next move will be.");
        targetbb("'s eyes seem to look right through you. You " +
            "have a feeling that " + this_player()->query_pronoun() +
            " will know your next move, even before you do.", 
            oblist);
        all2actbb("'s eyes study", oblist, " with great care, seemingly " +
          "ready to counter any move " + oblist[0]->query_pronoun() +
          " might make.");
        return 1;
    }

    actor("You study", oblist, " carefully, trying to judge what their " +
        "next move will be.");
    targetbb("'s eyes seem to look right through you. You get the " +
        "feeling that " + this_player()->query_pronoun() + " will know your " +
        "next move, even before you do.", oblist);
    all2actbb("'s eyes study", oblist, " with great care, seemingly " +
        "ready to counter any move they might make.");
    return 1;
}

/* Function name: rtear
 * Description  : Ranger emote to cry a solitary tear.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rtear(string str)
{
    write("Your eyes water up, and a tear flows down your cheek.\n");
    allbb("'s eyes slowly water up, and a solitary tear flows down " +
        this_player()->query_possessive() + " cheek.");
    return 1;
}

/* Function name: rtrack
 * Description  : Ranger emote to study tracks on the ground.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rtrack(string str)
{
    int index;
    string *how;
    string actionstr;
 
    /* if indoors */
    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You cannot study tracks inside a room!\n");
        return 0;
 
    }

    actionstr = one_of_list(({ "pondering the course of action.",
                       "scanning the surroundings for any movement.",
                       "observing each sound and movement in the area.",
                       "vigilantly watching the environment." }));
 
    how = parse_adverb_with_space(str, "meticulously", 0);
    this_player()->command("$track");
 
    write("You study the tracks on the ground" + how[1] + " while " +
        actionstr + "\n" );
    allbb(" studies the tracks on the ground" + how[1]  + " while " +
        actionstr);
    return 1;
}

/* Function name: rtroubled
 * Description  : Ranger emote to look and feel troubled.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rtroubled(string str)
{
    object *oblist;
    
    if (!strlen(str))
    {
        write("You study the environment, feeling troubled.\n");
        allbb(" doesn't move a muscle as " + this_player()->query_pronoun() + 
            " studies " + this_player()->query_possessive() + 
            " environment, yet " + this_player()->query_possessive() + 
            " eyes reveal that " + this_player()->query_pronoun() + " is " +
            "troubled.");
        return 1;
    }

    oblist = parse_this(str,"[at] %l");
    if (!sizeof(oblist))
    {
        notify_fail("Look how?\n");
        return 0;
    }

    actor("You look at", oblist, ", feeling troubled.");
    targetbb(" studies you intensely. As " + 
        this_player()->query_possessive() + " eyes reach yours, you notice " +
        "that they seem deep and troubled.", oblist);
    all2actbb(" doesn't move a muscle as " + this_player()->query_pronoun() +
        " studies", oblist, ", though " + this_player()->query_possessive() +
        " eyes reveal that " + this_player()->query_pronoun() + " is " +
        "troubled.");
    return 1;
}

/* Function name: runcloak
 * Description  : Ranger emote to fling back the cloak.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
runcloak(string str)
{
    object *cloak = this_player()->query_clothing(TS_ROBE);
    int size = sizeof(cloak) - 1;

    if (size == -1 || !objectp(cloak[size]))
    {
        notify_fail("You are not wearing a cloak!\n");
        return 0;
    }

    write("You fling back your " + cloak[size]->short() + ", preparing for the " +
        "fight.\n");
    allbb(" flings back " + this_player()->query_possessive() + " " + 
        cloak[size]->short() + ", preparing to fight.");
    return 1;
}

/* Function name: rwait
 * Description  : Ranger emote to counsel someone to wait.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rwait(string str)
{
    mixed *oblist;

    if (!strlen(str))
    {
        write("You remain perfectly still as you wait.\n");
        allbb(" remains perfectly still as " + this_player()->query_pronoun() +
            " waits.");
        return 1;
    }

    oblist = parse_this(str, "%l");
    if (!sizeof(oblist))
    {
        notify_fail("Nobody here matches that description.\n");
        return 0;
    }

    actor("With a motion of your hand you indicate for", oblist, 
        " to wait right here.");
    targetbb(" motions with " + this_player()->query_possessive() + 
        " hand for you to wait right here.", oblist);
    all2actbb(" motions with " + this_player()->query_possessive() + 
        " hand for", oblist, " to wait right here.");
    return 1;
}

/* Function name: rwarm
 * Description  : Ranger emote to warm hands over campfire.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rwarm(string str)
{
    string fire;

    if (present("campfire", environment(this_player())))
        fire = "campfire";
    else if (environment(this_player())->query_prop(OBJ_I_HAS_FIRE))
        fire = "fire";
    else
    {
        notify_fail("But there is no campfire here!\n");
        return 0;
    }

    write("Rubbing your hands together, you squat close to the burning " + 
        fire + " and allow its glow to warm you comfortably.\n");
    allbb(" rubs " + this_player()->query_possessive() + " hands together " +
        "and squats close to the " + fire + " to let its heat comfort " +
        this_player()->query_objective() + ". " + 
        capitalize(this_player()->query_possessive()) + " face is dimly " +
        "lit by the red glow of the fire.");
    return 1;
}

/* Function name: rwarmback
 * Description  : Ranger emote to warm back against campfire.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rwarmback(string str)
{
    string fire, ground;

    if (present("campfire", environment(this_player())))
        fire = "campfire";
    else if (environment(this_player())->query_prop(OBJ_I_HAS_FIRE))
        fire = "fire";
    else
    {
        notify_fail("But there is no campfire here!\n");
        return 0;
    }

    ground = (environment(this_player())->query_prop(ROOM_I_INSIDE) ? 
        "floor" : "ground");
    write("You stretch your tired legs, and sit on the " + ground + 
        " with your back turned to the warming " + fire + ".\n");
    allbb(" stretches " + this_player()->query_possessive() + " tired " +
        "legs before sitting on the " + ground + " to let the glow of the " + 
        fire + " warm " + this_player()->query_possessive() + " back " +
        "comfortably.");
    return 1;
}

/* Function name: rweary
 * Description  : Ranger emote to feel weary from travels.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rweary(string str)
{
    write("You feel weary from your travels.\n");
    allbb(" falls silent, " + this_player()->query_possessive() + " face " +
        "showing a great weariness from " + this_player()->query_possessive() +
        " travels.");
    return 1;
}

/* Function name: rwipe
 * Description  : Ranger emote to wipe off a weapon.
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
rwipe(string str)
{
    int i;
    mixed *weapons = this_player()->query_weapon(-1), *oblist;

    oblist = parse_this(str, "%l");
    if (!sizeof(oblist))
    {
        switch(sizeof(weapons))
        {
        case 0:
            notify_fail("You have no weapon wielded.\n");
            return 0;

        case 1:
            write("With a piece of cloth you wipe your " + weapons[0]->short() +
                " clean of blood to prevent it from becoming rusty or dull.\n" +
                weapons[0]->wep_condition_desc());
            allbb(" uses a piece of cloth to wipe " + 
                this_player()->query_possessive() + " " + weapons[0]->short() + 
                " clean of blood from the last fight.");
            return 1;

        default:
            write("With a piece of cloth you wipe the blood from your " +
                weapons[0]->short() + " to prevent it from becoming rusty " +
                "or dull.\n" + weapons[0]->wep_condition_desc() + "\n" +
                "You then wipe the blood from your " +
                weapons[1]->short() + " to prevent it from becoming rusty " +
                "or dull.\n" + weapons[0]->wep_condition_desc());
            allbb(" uses a piece of cloth to wipe the blood from " +
                this_player()->query_possessive() + " " + weapons[0]->short() +
                " and " + weapons[1]->short());
            return 1;
        }
    }

    oblist = filter(oblist, &->check_weapon());
    write("With a piece of cloth you wipe the blood from your ");
    for (i = sizeof(oblist) - 1; i >= 0; i--)
    {
        write(weapons[i]->short() + ".\n");
        write(weapons[i]->wep_condition_desc());
    }

    allbb(" uses a piece of cloth to wipe the blood from " +
        this_player()->query_possessive() + COMPOSITE_DEAD(oblist));
    return 1;
}

/* Function name: suspicious
 * Description  : Ranger emote to look suspiciously (at someone).
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */
public int
suspicious(string str)
{
    object *oblist;
 
    if (!strlen(str))
    {
        write("You look suspiciously around.\n");
        allbb(" looks suspiciously around.");
        return 1;
    }
 
    oblist = parse_this(str, "[at] [the] %l");
 
    if (!sizeof(oblist))
    {
        write("You look suspiciously at the " + str + "\n");
        allbb(" looks suspiciously at the " + str + "");
        return 1;
    }
 
    actor("You look suspiciously at", oblist, ".");
    targetbb(" looks suspiciously at you.", oblist);
    all2actbb(" looks suspiciously at", oblist, ".");
    return 1;
}

/* Function name:
 * Description  : Ranger emote to
 * Arguments    : string str - as entered by the Ranger
 * Returns      : 1 on success, 0 on failure
 */

