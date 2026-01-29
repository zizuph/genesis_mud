/*
 *  /d/Sparkle/guilds/new_merc/evil_start.c
 *
 *  This is the startroom for Mercs who are evil alignment or worse.
 *
 *  Created July 2009, by Cooper Sherry (Gorboth)
 *
 *  February 18 - 2022 - Mirandus Changed the heal_hp code for removing
 *  a player from the room. It hits REALLY hard compared to where the
 *  HP pool is. Just changed it to take 1/2 the max HP of the player.
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_merc_room();
public void        init();
public int         lie_bed(string arg);
public int         rise(string arg);
public void        leave_inv(object ob, object to);
public int         start(string str);
public void        enter_inv(object ob, object from);
public void        evict_player(object ob, int align);
public int         check_exit();

/* Definitions */
#define        BUNK_PROP    "_bunk_prop"


/*
 * Function name:        create_merc_room
 * Description  :        set up the room with area presets
 */
public void
create_merc_room()
{
    set_short("in the evil sleeping quarters of the Mercenary Guild");
    set_long("There is a palpable sense of ill-will in this room. Bunks"
      + " have been lined against the walls, which are decorated with"
      + " various ghastly images. Any evil Mercenary might feel right"
      + " at home in such an environment. If you're that sort, you'd"
      + " probably <bunk> here eventually. A guarded archway in the"
      + " north wall leads into a small chamber.\n\n");

    try_item( ({ "room", "here", "area" }),
        "This is where you can finally get some sleep.\n");
    try_item( ({ "evil mercenary", "evil mercenaries" }),
        "Thats the only kind allowed in here.\n");
    try_item( ({ "arch", "archway", "guarded arch", "guarded archway" }),
        "The archway leads into a chamber north of here. The guards"
      + " on each side would indicate that its not a place just anyone"
      + " can go.\n");
    try_item( ({ "chamber", "chamber north of here",
                 "north chamber", "small chamber",
                 "guarded chamber" }),
        "You can't see much from here.\n");
    try_item( ({ "guard", "guards", "mercenary guard",
                 "mercenary guards", "grumpy mercenary",
                 "grumpy looking mercenary",
                 "very grumpy looking mercenary",
                 "grumpy mercenaries",
                 "grumpy looking mercenaries",
                 "very grumpy looking mercenaries",
                 "grumpy guard",
                 "grumpy looking guard",
                 "very grumpy looking guard",
                 "grumpy guards",
                 "grumpy looking guards",
                 "very grumpy looking guards", }),
        "One of them shouts: What are you lookin' at?\n");
    try_item( ({ "sense", "palpable sense", "sense of ill-will",
                 "sense of ill will", "palpable sense of ill-will",
                 "palpable sense of ill will",
                 "ill-will", "ill will", "will", "environment",
                 "such an environment" }),
        "Yes, this is no place for goody-two-shoes types. In fact, if"
      + " one were to walk through the door, you'd probably instantly"
      + " punch them in the mouth.\n");
    try_item( ({ "goody-two-shoes", "goody-two-shoes types",
                 "goody two shoes types",
                 "goody-two-shoes type",
                 "goody two shoes type", }),
        "They deserve a punch in the mouth, after all. And even if they"
      + " don't deserve it ... they get it!\n");
    try_item( ({ "images", "image", "ghastly image",
                 "ghastly images" }),
        "There is a painting on the south wall, and many ears have"
      + " been nailed to the west wall.\n");
    try_item( ({ "ear", "ears" }),
        "Looks like a few of the regulars have been collecting"
      + " trophies from their kills.\n");
    try_item( ({ "trophy", "trophies" }),
        "Many of the ears are elvish, and most of the others appear"
      + " to be halfling.\n");
    try_item( ({ "elvish", "elf ear", "elf ears", "elvish ears",
                 "elvish ear" }),
        "Yeah ... elves tend to be of the goody-two-shoe variety."
      + " Such losers deserve to have their ears nailed to a wall!\n");
    try_item( ({ "halfling", "halfling ear", "halfling ears",
                 "hobbit ear", "hobbit ears",
                 "kender ear", "kender ears" }),
        "Smaller than your average ear, but big enough to hold in"
      + " place for a good nail!\n");
    try_item( ({ "nail", "nails" }),
        "I've heard of ear piercing, but this is ridiculous!\n");
    try_item( ({ "ear piercing" }),
        "Extreme ear piercing, maybe.\n");
    try_item( ({ "extreme ear piercing" }),
        "Yeah. You can only do it twice.\n");
    try_item( ({ "bunk", "bunks", "bed", "beds", "bunk bed",
                 "bunk-bed", "bunk beds", "bunk-beds" }),
        "The bunks may not be the most luxurious accomodations that"
      + " can be found in the realms, but they are a welcome sight"
      + " to any Mercenary who has been forced on more than one"
      + " occasion to use the roots of a tree to pass a long"
      + " sleeping period.\n");
    try_item( ({ "root", "roots", "roots of a tree", "tree roots" }),
        "A mediocre bunk beats that any day of the week!\n");
    try_item( ({ "mediocre bunk", "mediocre bunks" }),
        "Perhaps ... but tree roots can't even claim to be"
      + " mediocre for sleep. These are first rate by comparison!\n");
    try_item( ({ "wall", "walls" }),
        "The walls are lined with bunks here. Did you want to examine"
      + " a particular one?\n");
    try_item( ({ "north wall", "northern wall", "wall to the north" }),
        "The north wall contains an archway that is guarded by a few"
      + " VERY grumpy looking Mercenaries.\n");
    try_item( ({ "west wall", "western wall", "wall to the west" }),
        "The western wall has quite a few bunks situated against"
      + " it. Windows overlook the training yard.\n");
    try_item( ({ "training yard", "yard" }),
        "The training yard is visible through windows in the"
      + " western wall. You can't see much detail from here, but"
      + " you do hear the occasional yell or clash of steel.\n");
    try_item( ({ "yell", "shout", "occasional yell" }),
        "GAAAARRRRRRRRRRR!\n");
    try_item( ({ "clash", "clash of steel" }),
        "CLANG! CHINK!!\n");
    try_item( ({ "south wall", "southern wall", "wall to the south" }),
        "Bunks line the southern wall. A very amusing painting is"
      + " on the wall above them.\n");
    try_item( ({ "painting", "amusing painting", "very amusing painting" }),
        "Oh, look! Its a painting of a damsel in distress being dropped"
      + " off of a cliff by a dragon. Excellent!\n");
    try_item( ({ "damsel", "damsel in distress" }),
        "Too bad you didn't get a chance to push her off that cliff"
      + " yourself, eh?\n");
    try_item( ({ "cliff" }),
        "If only you could summon up such a cliff whenever you wanted."
      + " Imagine all the annoying conversations you could end with a"
      + " good shove.\n");
    try_item( ({ "dragon" }),
        "Way to go, Dragon!\n");
    try_item( ({ "great many bunks" }),
        "Yeah ... must be a dozen or so.\n");
    try_item( ({ "dozen", "dozen bunks" }),
        "1, 2, 3, 4 ... counting is fun.\n");
    try_item( ({ "east wall", "eastern wall", "wall to the east" }),
        "An ash-grey door separates the relatively few bunks that"
      + " line the eastern wall.\n");
    try_item( ({ "few bunks", "relatively few bunks" }),
        "Yeah, not much room for more than that.\n");
    try_item( ({ "snoring", "snore", "snores", "loud snore",
                 "loud snoring" }),
        "No shortage of that in here, is there?\n");
    try_item( ({ "mercenary", "mercenaries", "man", "woman",
                 "sleeper", "sleepers", "sleeping mercenary",
                 "sleeping mercenaries", "sleeping people",
                 "sleeping person", "sleeping man",
                 "sleeping woman", "person", "weary mercenary" }),
        "Numerous people lie sleeping in nearby bunks. They look like"
      + " they could kill even in their sleep.\n");

    add_cmd_item( ({ "mercenary", "mercenaries", "sleeper",
                     "sleeping mercenary", "sleeping man",
                     "sleeping woman", "sleeping person",
                     "man", "woman", "person" }),
                  ({ "wake", "disturb" }),
        "Do that, and you'd deserve the shiv you'd find wedged into"
      + " your spinal column.\n");

    add_indoor_view();
    add_indoor_lodge_view();

    add_prop(ROOM_I_INSIDE, 1);

    add_tell("A gritty mercenary enters the room, glares around,"
      + " and then flops down on a nearby bunk and begins snoring.\n");
    add_tell("Loud snoring issues from a nearby bunk.\n");
    add_tell("One of the sleeping mercenaries begins chuckling"
      + " between snores.\n");
    add_tell("One of the sleeping Mercenaries jolts awake and reaches"
      + " for his blade. Blinking dazedly, he seems to realize where"
      + " he is, and flops back asleep.\n");

    add_exit("evil_rack", "north", check_exit);

    setuid();
    seteuid(getuid());

    room_add_object(DOORS_DIR + "evil_w");
} /* create_room */


/*
 * Function name:        init
 * Description  :        add_some actions to the player
 */
public void
init()
{
    ::init();

    add_action(lie_bed, "lie");
    add_action(lie_bed, "lay");
    add_action(lie_bed, "sleep");
    add_action(lie_bed, "rest");
    add_action(rise, "get");
    add_action(rise, "stand");
    add_action(rise, "rise");
    add_action(start, "start");
    add_action(start, "bunk");
} /* init */


/*
 * Function name:        lie_bed
 * Description  :        Allow players to lie down on the bunks
 *                       and rest a bit
 * Arguments    :        string arg - what was typed after the
 *                                    verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
lie_bed(string arg)
{
    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " where?\n");
        return 0;
    }

    if (this_player()->query_prop(BUNK_PROP))
    {
        write("But you are already " + query_verb() + "ing"
          + " somewhere!\n");
        return 1;
    }

    if ( (query_verb() == "lay" || query_verb() == "lie") &&
        arg == "down")
    {
        notify_fail("Lie down on what? One of the bunks perhaps?\n");
        return 0;
    }

    if (!parse_command(arg, ({}),
        "[down] [on] [upon] [one] [of] [the] 'bunk' / 'bed'"
      + " / 'bunks' / 'beds'"))
    {
        notify_fail("Perhaps you want to " + query_verb() + " on"
          + " one of the bunks?\n");
        return 0;
    }

    write("You lie down on one of the bunks and rest a bit.\n");
    say(QCTNAME(this_player())
          + " crosses over to one of the bunks and lies down.\n");
    this_player()->add_prop(BUNK_PROP, 1);
    this_player()->add_prop(LIVE_S_EXTRA_SHORT, 
        " is resting on one of the bunks");

    return 1;
} /* lie_bed */


/*
 * Function name:        rise
 * Description  :        Allow the player to get up from the bed
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
rise(string arg)
{
    if (!strlen(arg) && query_verb() == "get" &&
        this_player()->query_prop(BUNK_PROP))
    {
        notify_fail("Get up, perhaps?\n");
        return 0;
    }

    if (!this_player()->query_prop(BUNK_PROP))
    {
        if (query_verb() != "get")
        {
            notify_fail("You are already on your feet.\n");
        }

        return 0;
    }

    write("You get up from the bunk. Ahh ... that felt good.\n");
    say(QCTNAME(this_player())
          + " gets up from the bunk " + this_player()->query_pronoun()
      + " was lying on.\n");
    this_player()->remove_prop(BUNK_PROP);
    this_player()->remove_prop(LIVE_S_EXTRA_SHORT);

    return 1;
} /* rise */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 *
 * This function is redefined to force players to stand up before
 * leaving if they are currently lying on a bunk.
 */
public void
leave_inv(object ob, object to)
{
    object   oldtp;

    ::leave_inv(ob, to);
   
    if(!objectp(to) || !objectp(ob))
    {
        return;
    }

    oldtp = this_player();
    set_this_player(ob);

    if (this_player()->query_prop(BUNK_PROP))
    {
        write("You get up from the bunk before leaving.\n");
        tell_room(this_object(), "(having gotten up from the"
          + " bunk first.)\n");
        this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
        this_player()->remove_prop(BUNK_PROP);
    }

    set_this_player(oldtp);
} /* leave_inv */



/*
 * Function name:        start
 * Description  :        Allow guild members to start here
 * Arguments    :        string str -- what was typed following the verb
 * Returns      :        1 -- they tried to start here, 0 -- no arg
 */
public int
start(string str)
{
    notify_fail("Start here? If you want to, just <bunk here>.\n");

    if (!strlen(str))
    {
        return 0;
    }

    if (str != "here")
    {
        return 0;
    }

    if (!this_player()->query_guild_member(GUILD_NAME))
    {
        write("Only Mercenaries are welcome to bunk here!\n");
        return 1;
    }

    if (this_player()->query_default_start_location() ==
        GUILD_STARTLOC)
    {
        notify_fail("You've already got yourself a bunk here."
          + " No need to reestablish that.\n");
        return 0;
    }

    if (this_player()->set_default_start_location(GUILD_STARTLOC))
    {
        write("You find a bunk that isn't already occupied, and"
          + " make it your own. Ahh ... its good to have a place"
          + " to rest your head after a long day of exploiting"
          + " the weak.\n\n"
          + "You will start here when you enter the realms from"
          + " now on.\n");
    }
    else
    {
        write("Sorry, some problem prevents you from starting here."
          + " Please mail Gorboth at once!\n");
    }

    return 1;
} /* start */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 *
 * This function is masked to kick out players who are not evil
 * enough.
 */
public void
enter_inv(object ob, object from)
{
    int        alignment = 1;  /* 1 = neutral, 2 = good */
    int        align = ob->query_alignment();

    ::enter_inv(ob, from);

    if (!interactive(ob))
    {
        return;
    }

    if (align < -619)
    {
        return;
    }

    if (align > 549)
    {
        alignment = 2;
    }

    set_alarm(1.0, 0.0, &evict_player(ob, alignment));

    return;
} /* enter_inv */


/*
 * Function name:        evict_player
 * Description  :        kick the player out of the room!
 * Arguments    :        object  ob - the person to kick out
 *                       int  align - their alignment: 1 - neutral,
 *                                                     2 - good
 */
public void
evict_player(object ob, int align)
{
    object     outside = safely_load_master_file(ROOM_DIR + "s_hallway");

    if (environment(ob) != this_object())
    {
        /* The player isn't in this room anymore, so we leave them
         * alone.
         */
        return;
    }

    if (ob->query_wiz_level())
    {
        ob->catch_tell("The Mercenaries in the room look at you with"
          + " suspicion in their eyes, but they know you are a wizard,"
          + " and wisely leave you alone.\n");
        return;
    }

    if (align == 2)
    {
        ob->catch_tell("Strong arms grab you roughly, and you are lifted off"
          + " your feet ... OOOOOF! ... you are slammed against a wall!\n"
          + "UGH! ... a meaty fist punches you in the face! ... HUUUUGH"
          + " ... someone knees you hard in the gut!\n\n"
          + "You are thrown out of the room, and land in a painful"
          + " heap on the floor outside!\n\n"
          + "A voice from the room shouts: GET YOUR GOODY-GOODY ASS"
          + " OUT OF OUR BUNK ROOM!\n");
        tell_room(this_object(),
            "A few Mercenaries leap from their bunks, grab "
          + QTNAME(ob) + ", throw " + ob->query_objective()
          + " roughly against the wall, and proceed to beat the"
          + " stupid saintly grin off of " + ob->query_possessive()
          + " face. After throwing " + ob->query_objective() + " out of"
          + " the door, one of them shouts: GET YOUR GOODY-GOODY"
          + " ASS OUT OF OUR BUNK ROOM!\n", ob);
        tell_room(outside,
            "A loud ruckus breaks out from the room to the west, and"
          + " sounds of a scuffle and someone being pounded on echo"
          + " into the hallway. A moment later, rough arms toss "
          + QTNAME(ob) + " out the door and onto the floor, and a"
          + " voice shouts: GET YOUR GOODY-GOODY ASS OUT OF OUR BUNK"
          + " ROOM!\n");

        ob->heal_hp(-(ob->query_max_hp()/2)); /* hurt them bad but don't kill them. */
        ob->move_living("M", outside, 1, 1);

        return;
    }

    ob->catch_tell("Strong arms grab you roughly, and you are shoved out into"
      + " the hallway! A voice from the room shouts: GO SLEEP DOWNSTAIRS"
      + " UNTIL YOU CAN GROW A BACKBONE!\n");
    tell_room(this_object(),
        "A few Mercenaries leap from their bunks, grab "
      + QTNAME(ob) + ", and shove " + ob->query_objective() + " out"
      + " into the hallway. One of them shouts: GO SLEEP DOWNSTAIRS UNTIL"
      + " YOU CAN GROW A BACKBONE!\n", ob);
    tell_room(outside,
        "You hear a bit of a scuffle coming from the room to the west,"
      + " and " + QTNAME(ob) + " is suddenly shoved roughly into the"
      + " hallway. A voice from the room shouts: GO SLEEP DOWNSTAIRS"
      + " UNTIL YOU CAN GROW A BACKBONE!\n");

    ob->move_living("M", outside, 1, 1);

    return;
} /* evict_player */


/*
 * Function name:        check_exit
 * Description  :        stop the player from going here if they
 *                       aren't an evil Mercenary
 * Returns      :        int - 1: prevent passage
 *                             0: allow passage
 */
public int
check_exit()
{
    if (!IS_MERC(this_player()))
    {
        if (this_player()->query_wiz_level())
        {
            write("The guards frown, but let you pass because you are"
              + " a wizard.\n");
            return 0;
        }

        write("The guards draw their blades as you approach, and one"
          + " says: You aren't even one of us! How did you get in"
          + " here? Get the hell out - NOW!\n");
        write("The guard stops you from going that way.\n");
        return 1;
    }

    if (this_player()->query_alignment() < -619)
    {
        return 0;
    }

    if (this_player()->query_wiz_level())
    {
        write("The guards frown, but let you pass because you are"
          + " a wizard.\n");
        return 0;
    }

    write("The guards draw their blades and hold them straight at you."
      + " One of them shouts: You're not one of our kind! I don't"
      + " care if you are a Mercenary, if you don't get out of here"
      + " I'll skin you alive!\n");
    write("The guard stops you from going that way.\n");
    return 1;
} /* check_exit */