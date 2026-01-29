/*
 *  /d/Sparkle/guilds/new_merc/good_start.c
 *
 *  This is the startroom for Mercs who are good alignment or better.
 *
 *  Created July 2009, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../merc_defs.h"

inherit MERC_ROOM_BASE;

#include <macros.h>
#include <stdproperties.h>

/* Prototypes */
public void        create_merc_room();
public string      do_cry();
public void        do_crying(object who);
public void        init();
public int         daydream(string arg);
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
    set_short("in the good sleeping quarters of the Mercenary Guild");
    set_long("A sense of peace and tranquility comes over you within"
      + " this room. Lining the walls are many bunks which all look"
      + " very neatly kept and quite soft. The forces of good are"
      + " at work here, and welcome any persons of similar bearing to"
      + " choose a <bunk>. A guarded archway in the south wall leads"
      + " into a small chamber.\n\n");

    try_item( ({ "look", "look on the childs face",
                 "look on the child's face" }), "@@do_cry@@");
    try_item( ({ "evil place" }),
        "You find no evil place. Indeed not!\n");
    try_item( ({ "evil" }),
        "No.\n");
    try_item( ({ "order" }),
        "It prevaileth.\n");
    try_item( ({ "prevaileth" }),
        "It doth.\n");
    try_item( ({ "sense" }),
        "Sense? Which sense?\n");
    try_item( ({ "good mercenary", "good mercenaries", "good heart",
                 "those of good heart" }),
        "Clearly, this place welcomes none other.\n");
    try_item( ({ "arch", "archway", "guarded arch", "guarded archway" }),
        "The archway leads into a chamber south of here. The guards"
      + " on each side would indicate that it's not a place just anyone"
      + " can go.\n");
    try_item( ({ "chamber", "chamber north of here",
                 "north chamber", "small chamber",
                 "guarded chamber" }),
        "You can't see much from here.\n");
    try_item( ({ "guard", "guards", "mercenary guard",
                 "mercenary guards", "stern mercenary",
                 "stern looking mercenary",
                 "very stern looking mercenary",
                 "stern mercenaries",
                 "stern looking mercenaries",
                 "very stern looking mercenaries",
                 "stern guard",
                 "stern looking guard",
                 "very stern looking guard",
                 "stern guards",
                 "stern looking guards",
                 "very stern looking guards", }),
        "One of them says: We only admit friends.\n");
    try_item( ({ "peace", "sense of peace" }),
        "This is clearly a room where order prevails. Those of good"
      + " heart will find nothing to trouble them.\n");
    try_item( ({ "tranquility", "sense of tranquility" }),
        "Yes, it really does feel nice in here. One could daydream.\n");
    try_item( ({ "daydream" }),
        "Well, one could ... I suppose ... if they had nothing better"
      + " to do.\n");
    try_item( ({ "peace and tranquility",
                 "sense of peace and tranquility" }),
        "Yep. Both ... in abundance.\n");
    try_item( ({ "room", "here", "area" }),
        "This is clearly a place of rest and renewal.\n");
    try_item( ({ "rest" }),
        "Maybe you should get some?\n");
    try_item( ({ "renewal" }),
        "It often comes with rest.\n");
    try_item( ({ "rest and renewal" }),
        "Nice things to achieve, aren't they?\n");
    try_item( ({ "force", "forces", "good", "force of good",
                 "forces of good" }),
        "Evidence is everywhere. You wouldn't get this sort of peace"
      + " and tranquility in an evil place.\n");
    try_item( ({ "evidence" }),
        "Yeah. Everywhere.\n");
    try_item( ({ "everywhere" }),
        "All around.\n");
    try_item( ({ "around", "all around" }),
        "Ahhhhhhhhh ...\n");
    try_item( ({ "bunk", "bunks", "bed", "beds", "bunk bed",
                 "bunk-bed", "bunk beds", "bunk-beds" }),
        "The bunks may not be the most luxurious accommodations that"
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
        "The north wall contains a great many bunks. A painting is"
      + " on the wall above them.\n");
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
        "The south wall contains an archway that is guarded by a few"
      + " very stern looking Mercenaries.\n");
    try_item( ({ "painting", "beautiful painting",
                 "remarkably beautiful painting" }),
        "The painting is remarkably beautiful. It displays a gentle-"
      + "faced bard singing at the bedside of an ailing child.\n");
    try_item( ({ "bard", "gentle faced bard",
                 "gentle-faced bard" }),
        "Inspirational stuff, this.\n");
    try_item( ({ "inspirational", "stuff", "inspirational stuff" }),
        "Makes you want to go find a child to sing to yourself,"
      + " doesn't it?\n");
    try_item( ({ "child", "ailing child" }),
        "The look on the child's face is one of deepest comfort and"
      + " gratitude.\n");
    try_item( ({ "great many bunks" }),
        "Yeah ... must be a dozen or so.\n");
    try_item( ({ "dozen", "dozen bunks" }),
        "1, 2, 3, 4 ... counting is fun.\n");
    try_item( ({ "east wall", "eastern wall", "wall to the east" }),
        "A polished door separates the relatively few bunks that"
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
        "Numerous people lie sleeping in nearby bunks. They've earned"
      + " their rest with all their good deeds.\n");

    add_cmd_item( ({ "mercenary", "mercenaries", "sleeper",
                     "sleeping mercenary", "sleeping man",
                     "sleeping woman", "sleeping person",
                     "man", "woman", "person" }),
                  ({ "wake", "disturb" }),
        "Disturb the much-needed sleep of your fellows? Heaven forbid!\n");

    add_indoor_view();
    add_indoor_lodge_view();

    add_prop(ROOM_I_INSIDE, 1);

    add_tell("A kind-eyed Mercenary enters the room, tucks his armour"
      + " beneath a bunk, and climbs into bed.\n");
    add_tell("Loud snoring issues from a nearby bunk.\n");
    add_tell("One of the Mercenaries hums softly in her sleep.\n");
    add_tell("A bird lands on the ledge of one of the windows, pecks"
      + " at something, and flies away again.\n");

    add_exit("good_rack", "south", check_exit);

    setuid();
    seteuid(getuid());

    room_add_object(DOORS_DIR + "good_w");
} /* create_room */


/*
 * Function name:        do_cry
 * Description  :        Have the player get emotional
 * Returns      :        string - the description for the add_item
 */
public string
do_cry()
{
    set_alarm(0.5, 0.0, &do_crying(this_player()));

    return "Its just so ... so ... \n";
} /* do_cry */


/*
 * Function name:        do_crying
 * Description  :        Force the actual crying
 * Arguments    :        object who - the player in question
 */
public void
do_crying(object who)
{
    who->command("$cry");
} /* do_crying */


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
    add_action(daydream, "daydream");
} /* init */


/*
 * Function name:        daydream
 * Description  :        Let players loll about.
 * Arguments    :        what was typed after the verb, but we don't care
 * Returns      :        1 always
 */
public int
daydream(string arg)
{
    write("Your thoughts drift to ... "
      + one_of_list( ({ "snowcones", "cute puppies", "warm sandy beaches",
                        "beautiful clouds", "rainbows", "butterflies",
                        "your first kiss", "the one that got away",
                        "chocolate chip cookies", "lemon sorbet",
                        "walks in the park", "lazy Sunday afternoons",
                        "that time you scored a goal",
                        "butterscotch", "a good smoke",
                        "your finest hour", "that time you took on all"
                      + " those skeletons", "your favorite weapon",
                        "perfectly fluffed pillows", "cotton candy",
                        "pie", "your back yard as a child",
                        "the time you hiked all the way to the top",
                        "Sparkle's Finest", "you taking on the Balrog solo",
                        "soft lute music", "the smell of freshly mown"
                      + " grass", "spearmint", "the old Kahedan guild",
                        "parsley, sage, rosemary, and fudge",
                        "pickles", "roast beef", "artichoke hearts",
                        "pumpernickle", "the really nice butt you"
                      + " saw this morning", "guitar lessons",
                        "gemstones", "the opposite sex",
                        "pasta" }) ) + " ... \n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " gets a far-away look in "
      + this_player()->query_possessive() + " eyes.\n", this_player());

    return 1;
} /* daydream */


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
          + " to rest your head after a long day of righting the"
          + " wrongs of the world for profit.\n\n"
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
    int        alignment = 1;  /* 1 = neutral, 2 = evil */
    int        align = ob->query_alignment();

    ::enter_inv(ob, from);

    if (!interactive(ob))
    {
        return;
    }

    if (align > 549)
    {
        return;
    }


    if (align < -619)
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
 *                                                     2 - evil
 */
public void
evict_player(object ob, int align)
{
    object     outside = safely_load_master_file(ROOM_DIR + "n_hallway");

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
        tell_room(this_object(),
            "A Mercenary wakes and shouts: What devilry is this?!\n"
          + "Many more Mercenaries rise from their bunks in alarm!\n");
        ob->catch_tell("You are suddenly rushed from all directions"
          + " by the occupants of the room, who grab you and toss"
          + " you roughly out of the door!\n\n"
          + "A voice from the room shouts: YOUR KIND ARE NOT WELCOME"
          + " HERE! GO SLEEP WITH YOUR OWN FOUL BREED!\n");
        tell_room(this_object(),
            QCTNAME(ob) + " is rushed from all directions and, grabbed"
          + " roughly, and tossed out of the room.\n" 
          + "One of the Mercenaries shouts: YOUR KIND ARE NOT WELCOME"
          + " HERE! GO SLEEP WITH YOUR OWN FOUL BREED!", ob);
        tell_room(outside,
            "A call of alarm and rush of footsteps echoes from the room"
          + " to the west. A moment later, strong arms toss "
          + QTNAME(ob) + " out the door and onto the floor, and a"
          + " voice shouts: YOUR KIND ARE NOT WELCOME HERE! GO SLEEP"
          + " WITH YOUR OWN FOUL BREED!\n");

        ob->move_living("M", outside, 1, 1);

        return;
    }

    ob->catch_tell("Your entry has roused a few of the sleeping occupants"
      + " of this room who rise and escort you firmly to the door. You"
      + " are ushered into the hallway as a voice from the room"
      + " declares: You need to decide what cause you wish to support."
      + " Maybe in time your deeds will make you welcome here, but that"
      + " time is not yet come!\n");
    tell_room(this_object(),
        "A few Mercenaries rise from their bunks, grab "
      + QTNAME(ob) + ", and usher " + ob->query_objective() + " firmly out"
      + " into the hallway. One of them declares: You need to decide what"
      + " cause you wish to support. Maybe in time your deeds will make"
      + " you welcome here, but that time is not yet come!\n", ob);
    tell_room(outside,
        "You hear an argument coming from the room to the west,"
      + " and " + QTNAME(ob) + " is ushered firmly into the"
      + " hallway. A voice from the room declares: You need to decide what"
      + " cause you wish to support. Maybe in time your deeds will make"
      + " you welcome here, but that time is not yet come!\n");

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
          + " says: You are no Mercenary! How did you get in"
          + " here? Leave AT ONCE!\n");
        write("The guard stops you from going that way.\n");
        return 1;
    }

    if (this_player()->query_alignment() > 549)
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
      + " One of them shouts: You shall not come here! You may be"
      + " a Mercenary, but you are no friend of ours. Begone!\n");
    write("The guard stops you from going that way.\n");
    return 1;
} /* check_exit */