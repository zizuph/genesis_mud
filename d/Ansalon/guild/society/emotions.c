/* 
 * /d/Ansalon/guild/kender_occ/emotions.c
 *
 * Copyright (c) 2001 by Alyssa Hardy
 *
 * Copyright notice, please read.
 *
 * You are welcome to read this file for information & education purposes.
 * However, you are expressly forbidden to copy this code for use in any
 * other mud. This code is part of Genesis and we want Genesis to remain
 * unique. You must invent your own world on your own mud.
 *
 * This file contains the emotes for the Secret Society of Uncle
 * Trapspringer. Thanks go to Meercat, Belnop, Alberic and Boron 
 * for their contributions.
 *
 * Created: Gwyneth, June 1999
 * Modification log:
 * Gwyneth January 2001 - General cleanup of the code.
 */

/*
 * Function name: query_topknot
 * Description  : Tests to see if a kender has a topknot, based on
 *                the Calian hairstyle shadow.
 * Returns      : 1 if yes, 0 if no
 */
public int
query_topknot()
{
    return(this_player()->query_hair_style() == "styled with a top-knot");
}

/*
 * Function name: query_hoopak
 * Description  : Tests to see if a kender has a hoopak
 * Returns      : The hoopak object
 */
public object
query_hoopak()
{
    int index, size;
    object *wielded = this_player()->query_weapon(-1);

    for (index = 0, size = sizeof(wielded); index < size; index++)
    {
        if (wielded[index]->id("hoopak"))
            return wielded[index];
    }

    return 0;
}

/* 
 * Function name : kangry
 * Description   : Emote to get angry
 * Arguments     : string str
 * Returns       : Returns 1 on success, 0 on failure
 */
public int
kangry(string str)
{
    object *oblist;

    /* Find if the argument is valid */
    oblist = parse_this(str, "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Get angry at [whom]?\n");

    if (!strlen(str))
    {
        write("Your face turns red to the tip of your pointy ears, " +
            "and you stomp your feet angrily on the ground.\n");
        all("'s face turns red to the tip of " + 
            this_player()->query_possessive() + " ears, and " + 
            this_player()->query_pronoun() + " stomps " + 
            this_player()->query_possessive() + " feet angrily on the ground.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    actor("Your glare at", oblist, " as your face turns red to the " +
        "tip of your pointy ears.\nYou stomp your feet angrily on the " +
        "ground.");
    target(" glares at you as " + this_player()->query_possessive() + 
        " face turns red to the tip of " + this_player()->query_possessive() + 
        " pointy ears.\n" + capitalize(this_player()->query_pronoun()) + 
        " stomps " + this_player()->query_possessive() + " feet angrily on " +
        "the ground.", oblist);
    all2act(" glares at", oblist, " as " + this_player()->query_possessive() +
        this_player()->query_possessive() + " face turns red to the tip of " + 
        this_player()->query_possessive() + " pointy ears.\n" + 
        capitalize(this_player()->query_pronoun()) + " stomps " + 
        this_player()->query_possessive() + " feet angrily on the ground.");
    return 1;
}

/* 
 * Function name : kblush
 * Description   : Emote to blush
 * Arguments     : string str
 * Returns       : 0 on failure, 1 on success
 */
public int
kblush(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "sheepishly", 0);

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Setup failure message */
    notify_fail("Blush [how] at [whom]/[what]?\n");

    if (!strlen(how[0]))
    {
        write("You duck your head" + how[1] + " while blushing to " +
            "the tips of your ears.\n");
        all(" ducks " + this_player()->query_possessive() + " head" + 
            how[1] + " while blushing to the tips of " + 
            this_player()->query_possessive() + " ears.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        return 0;
    }

    actor("You duck your head" + how[1] + " avoiding looking at",
        oblist, " while blushing to the tips of your ears.");
    target(" ducks " + this_player()->query_possessive() + " head" + how[1] + 
        " avoiding looking at you while blushing to the tips of " + 
        this_player()->query_possessive() + " ears.", oblist);
    all2act(" ducks " + this_player()->query_possessive() + " head" + how[1] + 
        " avoiding looking at", oblist, " while blushing to the tips of " +
        this_player()->query_possessive() + " ears.");
    return 1;
}

/* 
 * Function name : kbow
 * Description   : Emote to bow
 * Arguments     : string str
 * Returns       : 0 on failure, 1 on success
 */
public int
kbow(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "melodramatically", 0);

    /* Find if argument is valid */
    oblist = parse_this(how[0], "[in] [front] [of] [at] [to] [before] %i");

    /* Setup failure message */
    notify_fail("Bow [how] to [whom]/[what]?\n");

    if (this_player()->query_hair_style() != "styled with a top-knot")
    {
        notify_fail("This bow requires a topknot.\n");
        return 0;
    }

    if (!strlen(how[0]))
    {
        write("You bow" + how[1] + " and your topknot flips over your head, " +
            "brushing your toes.\n");
        all(" bows" + how[1] + " and " + this_player()->query_possessive() +
            " topknot flips over " + this_player()->query_possessive() +
            " head, brushing " + this_player()->query_possessive() + " toes.");
        return 1;
    }

    if (!sizeof(oblist))
        return 0;

    actor("You bow" + how[1] + " in front of", oblist, " and " +
        "your topknot flies over your head, brushing your toes.");
    target(" bows" + how[1] + " in front of you and " + 
        this_player()->query_possessive() + " topknot flies over " + 
        this_player()->query_possessive() + " head, brushing " +
        this_player()->query_possessive() + " toes.", oblist);
    all2act(" bows" + how[1] + " in front of", oblist, " and " +
        this_player()->query_possessive() + " topknot flies over " + 
        this_player()->query_possessive() + " head, brushing " + 
        this_player()->query_possessive() + " toes.");
    return 1;
}

/* 
 * Function name : kbow2
 * Description   : Emote to bow
 * Arguments     : string str
 * Returns       : 0 on failure, 1 on success
 */
public int
kbow2(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "deeply", 0);

    /* Find if the argument is valid */
   oblist = parse_this(how[0], "[in] [front] [of] [at] [to] [before] [the] %i");

    /* Failure message */
    notify_fail("Bow [how] to [who]/[what]?\n");

    if (!strlen(how[0]))
    {
        write("You bow" + how[1] + ", trying to keep things from " + 
            "falling out of their pouches.\n");
        all(" bows" + how[1] + ", trying to keep things from falling out " + 
            "of all of " + this_player()->query_possessive() + " pouches.");
        return 1;
    }

    if (!sizeof(oblist))
        return 0;

    actor("You bow" + how[1] + " in front of", oblist, ", trying to keep " + 
        "things from falling out of their pouches.");
    target(" bows" + how[1] + " in front of you, trying to keep things from " + 
        "falling out of " + this_player()->query_possessive() + " pouches.", 
        oblist);    
    all2act(" bows" + how[1] + " in front of", oblist, ", trying to keep " + 
        "things from falling out of " + this_player()->query_possessive() +
        " pouches.");
    return 1;
}

/* 
 * Function name : kchew
 * Description   : Emote to chew on a topknot
 * Arguments     : string str
 * Returns       : 0 on failure, 1 on success
 */
public int
kchew(string str)
{
    string *how = parse_adverb_with_space(str, "intently", 0);

    if (!strlen(how[0]) || how[0] == "topknot" || how[0] == "hair")
    {
        if (this_player()->query_hair_style() == "styled with a top-knot")
        {
            write("You chew" + how[1] + " on the end of your topknot.\n");
            all(" chews" + how[1] + " on the end of " + 
            this_player()->query_possessive() + " topknot.");
            return 1;
        }
    }

    notify_fail("Chew on your topknot [how]?\n");
    return 0;
}

/* 
 * Function name : kclap
 * Description   : Emote to clap hands.
 * Arguments     : string str
 * Returns       : 0 on failure, 1 on success
 */
public int
kclap(string str)
{
    object *oblist;

    /* Find if the argument is valid */
    oblist = parse_this(str, "[at] [the] %i");

    if (!strlen(str))
    {
        write("You clap your hands together excitedly and squeal in " +
            "delight.\n");
        all(" claps " + this_player()->query_possessive() + " hands " +
            "together excitedly and squeals in delight.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        notify_fail("Clap your hands at [whom]/[what]?\n");
        return 0;
    }

    actor("You clap your hands together excitedly and squeal " +
        "in delight at", oblist, ".");
    target(" claps " + this_player()->query_possessive() + " hands " +
        "together excitedly and squeals in delight at you.", oblist);
    all2act(" claps " + this_player()->query_possessive() + " hands " +
        "together excitedly and squeals in delight at", oblist, ".");
    return 1;
}

/* 
 * Function name : kcry
 * Description   : Emote to cry
 * Arguments     : string str
 * Returns       : 0 on failure, 1 on success
 */
public int
kcry(string str)
{
    object *oblist;
    oblist = parse_this(str, "[at] [the] %i");

    if (!strlen(str))
    {
        write("You wrinkle up your face into a dejected frown, and " + 
            "two tears roll down your cheeks.\n");
        all(" wrinkles up " + this_player()->query_possessive() + 
            " face into a dejected frown, and two tears roll down " + 
            this_player()->query_possessive() + " cheeks.");
        return 1;
    }

    actor("You look at", oblist, " and wrinkle up your face into a " + 
        "dejected frown. Two tears roll down your cheeks.");
    target(" looks at you and wrinkles up " + 
        this_player()->query_possessive() + " face into a dejected frown. " +
        "Two tears roll down " + this_player()->query_possessive() + 
        " cheeks.", oblist);
    all2act(" looks at", oblist, " and wrinkles up " + 
        this_player()->query_possessive() + " face into a dejected frown. " +
        "Two tears roll down " + this_player()->query_possessive() +" cheeks.");
    return 1;   
}

/* 
 * Function name : kdance
 * Description   : Emote to dance around.
 * Arguments     : string str
 * Returns       : 0 on failure, 1 on success
 */
public int
kdance(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "joyfully", 0);
    string him_them;

    /* Find if the argument is a valid living. */
    oblist = parse_this(how[0], "[with] [the] %i");

    if (this_player()->query_hair_style() != "styled with a top-knot")
    {
        /* No argument given */
        if (!strlen(how[0]))
        {
            write("You dance about" + how[1] + ".\n");
            all(" dances about" + how[1] + ".");
            return 1;
        }

        if (!sizeof(oblist))
        {
            notify_fail("Dance around with [whom]?\n");
            return 0;
        }

        if(sizeof(oblist) > 1)
            him_them = "them";
        else
            him_them = oblist[0]->query_objective();

        actor("You grab", oblist, " and dance around with " + him_them +
            how[1] + ".");
        target(" grabs you and dances around with you" + how[1] + ".", oblist);
        all2act(" grabs", oblist, " and dances around with " + him_them + 
            how[1] + ".");
        return 1;
    }
    else
    {
        /* No argument given */
        if (!strlen(how[0]))
        {
            write("You dance around" + how[1] + " with your " + 
                "topknot waving around wildly.\n");
            all(" dances around" + how[1] + " with " + 
                this_player()->query_possessive() + " topknot waving " +
                "around wildly.");
            return 1;
        }

        if (!sizeof(oblist))
        {
            notify_fail("Dance around with [whom]?\n");
            return 0;
        }

        if(sizeof(oblist) > 1)
            him_them = "them";
        else
            him_them = oblist[0]->query_objective();

        actor("You grab", oblist, " and dance around with " + him_them+ 
            how[1] + ", your topknot waving around wildly.");
        target(" grabs you and dances around with you" + how[1] + ", " + 
            this_player()->query_possessive() + " topknot waving around " +
            "wildly.", oblist);
        all2act(" grabs", oblist, " and dances around with " + him_them + 
            how[1] + ", " + this_player()->query_possessive() + 
            " topknot waving around wildly.");
        return 1;
    }
}

/* 
 * Function name : kdiscard
 * Description   : Allows a kender to drop an uninteresting item
 *                 on the ground.
 * Arguments     : string str - the item to discard
 * Returns       : 1 on success, 0 on failure
 */
public int
kdiscard(string str)
{
    mixed *oblist;

    if(!strlen(str))
    {
        notify_fail("Discard which item?\n");
        return 0;
    }

    if(!parse_command(str, all_inventory(this_player()), "[the] %i", oblist))
    {
        notify_fail("Discard which item?\n");
        return 0;
    }

    oblist = NORMAL_ACCESS(oblist, 0, 0);

    /* Nothing accessible */
    if (!sizeof(oblist))
    {
        notify_fail("Discard which item?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("Discard which item?\n");
        return 0;
    }

    if(!oblist[0]->move(environment(this_player())))
    {   
        write("You look critically at " + LANG_ASHORT(oblist[0]) + 
            " and discard it as uninteresting.\n");
        all(" looks critically at " + LANG_ASHORT(oblist[0]) + 
            " and discards it as uninteresting.");
        return 1;
    }

    notify_fail("You cannot discard that.\n");
    return 0;
}

/*
 * Function name: kembrace
 * Description  : Emote to embrace someone
 */
public int
kembrace(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "tightly", 1);
 
    /* Find if the argument is valid */
    oblist = parse_this(how[0], "[at] [the] %l");
 
    if (!strlen(how[0]))
    {
        notify_fail("Embrace who [how]?\n");
        return 0;
    }
 
    if (!sizeof(oblist))
    {
        notify_fail("Embrace who [how]?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("Your arms are only big enough for one person!\n");
        return 0;
    }

    actor("You fling your arms around", oblist, " and embrace " + 
        oblist[0]->query_objective() + how[1] + ", taking the " +
        "opportunity to peek in " + oblist[0]->query_possessive() + 
        " pockets.");
    target(" flings " + this_player()->query_possessive() + " arms around " +
        "you and embraces you" + how[1] + ".", oblist);
    all2act(" flings " + this_player()->query_possessive() + " arms " +
        "around", oblist, " and embraces " + oblist[0]->query_objective() +
        how[1] + ".");

    this_player()->command("peek " + OB_NAME(oblist[0]));
    if (random(50) < 100)
        this_player()->command("borrow something from " + OB_NAME(oblist[0]));

    return 1;
}

/* Guild list adapted from the PoT. */

public int
filter_kender(object who)
{
    if (!MEMBER(who))
        return 0;

    if (who == this_player())
        return 1;

    /* Wizards see everyone. */
    if (this_player()->query_wiz_level())
        return 1;

    /* Invis wizards are not shown. */
    if (who->query_wiz_level() && who->query_invis())
        return 0;

    /* Jr's are not shown. */
    if (extract(who->query_real_name(), -2) == "jr")
        return 0;

    return 1;
}

/* 
 * Function name : ken_online
 * Description   : Gets a list of online guild members
 */
object *
ken_online()
{
    object *list = users();
#ifdef STATUE_WHEN_LINKDEAD
#ifdef OWN_STATUE
    list += filter(all_inventory(find_object(OWN_STATUE))-list,
      &not() @ &->query_npc());
#endif OWN_STATUE
#endif STATUE_WHEN_LINKDEAD
    return sort_array(filter(list, filter_kender));
}

/* 
 * Function name : kenlist
 * Description   : Lists other members of the guild logged on.
 * Arguments     : string str 
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
kenlist(string str)
{
    object *members;
    int index, size;

    members = ken_online();
    size = sizeof(members);

    if (!size)
    {
        write("There are no other members in the game.\n");
        return 1;
    }
    else
    {
        write("There " + (size > 1 ? "are" : "is") + " currently " + 
            size + " Kender " + 
            "in the game.\n");

        for (index = 0; index < size; index++)
        {
            str = members[index]->query_name();
            str += " " + members[index]->query_kender_title();

            if (!interactive(members[index]))
                str = "*" + str;

            write(str + "\n");
        }
    }
    return 1;
}

/* 
 * Function name : kexcuse
 * Description   : Emote for kender excuses. 
 * Arguments     : string arg
 * Returns       : Returns 0 on failure, 1 on success.
*/
public int
kexcuse(string arg)
{
    mixed *oblist;
    string str;

    /* Find a random excuse. */
    switch(random(18))
    {
        case 0:
            str = "Guess I found it somewhere.";
            break;
        case 1:
            str = "Now how did THAT get in there?";
            break;
        case 2:
            str = "You must have dropped it!";
            break;
        case 3:
            str = "I was just holding it for you.";
            break;
        case 4:
            str = "I was just keeping it safe for you. Someone could steal it " +
                "if you're not careful!";
            break;
        case 5:
            str = "This looks just like yours, doesn't it?";
            break;
        case 6:
            str = "Aren't you glad I found it?";
            break;
        case 7:
            str = "I was just looking at it for a minute!";
            break;
        case 8:
            str = "I forgot I had it!";
            break;
        case 9:
            str = "You walked away before I could give it back.";
            break;
        case 10:
            str = "Maybe it fell into my pocket.";
            break;
        case 11:
            str = "You put it down and I didn't think you wanted it anymore.";
            break;
        case 12:
            str = "You mean that wasn't my pocket?";
            break;
        case 13:
            str = "How interesting! I wonder where that came from?";
            break;
        case 14:
            str = "You said you didn't want it anymore.";
            break;
        case 15:
            str = "It must be magical because it just appeared in my pouch!";
            break;
        case 16:
            str = "I was only cleaning it for you.";
            break;
        case 17:
            str = "Someone must have put it in my pouch by mistake.";
            break;
        case 18:
            str = "I was afraid someone else would take it.";
            break;
        case 19:
            str = "It was just laying there, honest.";
            break;
        default:
            str = "You really should be more careful with your things.";
    }

    if(!strlen(arg))
    {

        write("You chatter quickly: " + str + "\n");
        all(" chatters quickly: " + str);

        return 1;
    }

    notify_fail("Give an excuse about what?\n");

    /* Invalid argument */
    if (!parse_command(arg, all_inventory(this_player()), "[the] %i", oblist))
    {
        write("You chatter quickly: " + arg + "\n");
        all(" chatters quickly: " + arg + "\n");
        return 1;
    }

    oblist = NORMAL_ACCESS(oblist, 0, 0);

    /* Nothing accessible */
    if (!sizeof(oblist))
    {
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        return 0;
    }

    write("You hold out a " + oblist[0]->short() + " and quickly " +
        "chatter: " + str + "\n");
    all(" holds out a " + oblist[0]->short() + " and quickly " +
        "chatters: " + str);

    return 1;
}

/* 
 * Function name : kfidget
 * Description   : Emote for fidgeting
 * Arguments     : string str
 * Returns       : Returns 0 on fail, 1 on success
 */
public int
kfidget(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "restlessly", 0);

    /* Find if the argument is valid */
    oblist = parse_this(how[0], "[at] [the] %i");

    /* Failure message */
    notify_fail("Fidget [how] at [who's] delay?\n");

    if (!strlen(how[0]))
    {
        write("You fidget" + how[1] + ", staring off into the distance.\n");
        all(" fidgets" + how[1] + ", staring off into the distance.");
        return 1;
    }

    if (!sizeof(oblist))
        return 0;

    actor("You fidget" + how[1] + ", hoping that", oblist, " will do " + 
        "something to alleviate your boredom.");
    target(" fidgets" + how[1] + ", hoping that you will do something to " + 
        "alleviate " + this_player()->query_possessive() + " boredom.", oblist);
    all2act(" fidgets" + how[1] + ", hoping that", oblist, " will do " + 
        "something to alleviate " + this_player()->query_possessive() + 
        " boredom.");
    return 1;
}

/* 
 * Function name : kfind
 * Description   : Emote to get something.
 * Arguments     : string str
 * Returns       : 1 on success, 0 on failure
 */
public int
kfind(string str)
{
    mixed *item, *cont;
    string str1, str2;

    if (!str)
    {
        notify_fail("Find what from where?\n");
        return 0;
    }

    sscanf(str, "%s from %s", str1, str2);
    if (!strlen(str1))
    {
        notify_fail("Find what from where?\n");
        return 0;
    }

    if (!strlen(str2))
    {
        notify_fail("Find what from where?\n");
        return 0;
    }

    if (!parse_command(str2, (all_inventory(this_player())), "[the] %i", cont))
    {
        notify_fail("Find what from where?\n");
        return 0;
    }

    cont = NORMAL_ACCESS(cont, 0, 0);

    if (sizeof(cont) > 1)
    {
        notify_fail("Find something from one place at a time!\n");
        return 0;
    }
    else if (!sizeof(cont))
    {
        notify_fail("Find what from where?\n");
        return 0;
    }
    else if (cont[0]->query_prop(CONT_I_CLOSED))
    {
        notify_fail("It's awfully hard to find anything in a closed " +
            "container.\n");
        return 0;
    }
    else if (!cont[0]->query_prop(CONT_I_IN))
    {
        notify_fail("Find something from a container.\n");
        return 0;
    }

    write("You rummage through your " + cont[0]->short() + " eagerly.\n");
    say(QCTNAME(this_player()) + " rummages through " + 
        this_player()->query_possessive() + " " + cont[0]->short() + 
        " eagerly.\n");
    this_player()->command("$get " + str1 + " from " + str2);
    return 1;
    
}

/* Kflip functions follow */

/* 
 * Function name : do_tingle
 * Description   : Alarm to give message from kflip().
 * Arguments     : None
 * Returns       : Returns 1
 */
public void
do_tingle()
{
    write("You tingle with the excitement of your flip.\n");
    all(" glows with excitement.");
}

/* 
 * Function name : do_land
 * Description   : Alarm to give message from kflip().
 * Arguments     : None
 * Returns       : Returns 1
 */
public void
do_land()
{
    write("You come flying back to the ground, landing with the " +
        "graceful ease of an acrobat.\n");
    all(" comes flying back to the ground, landing with " +
        "the graceful ease of an acrobat.");
    set_alarm(1.5, 0.0, &do_tingle());
}

/* 
 * Function name : do_fly
 * Description   : Alarm to give a message from kflip().
 * Arguments     : None
 * Returns       : Returns 1
 */
public void
do_fly()
{
    write("Your momentum sends you flying head over heels into the " +
        "air with a loud shout of excitement.\n");
    all("'s momentum sends " + this_player()->query_objective() + 
        " flying head over heels into the air with a loud shout of " +
        "excitement.");
    this_player()->command("shout This is fun!!");
    set_alarm(1.5,0.0, &do_land());
}

/* 
 * Function name : do_plant
 * Description   : Alarm to give a message from kflip().
 * Arguments     : None
 * Returns       : Returns 1
*/
public void
do_plant()
{

    write("You gain speed quickly and suddenly plant your hoopak " + 
        "into the ground in front of you.\n");
    all(" gains speed quickly, and suddenly plants " +
        this_player()->query_possessive() + " hoopak " + 
        "in the ground in front of " + this_player()->query_objective() + ".");
    set_alarm(1.5, 0.0, &do_fly());
}

/* 
 * Function name : do_launch
 * Description   : Alarm to give message from kflip().
 * Arguments     : None
 * Returns       : Returns 1
 */
public void
do_launch()
{
    write("You gain speed quickly and launch yourself into the air, " +
        "spinning head over heels with a shout of excitement.\n");
    all(" gains speed quickly, and launches " + 
        this_player()->query_objective() + "self into the air, spinning " +
        "head over heels with a shout of excitement.");
    this_player()->command("shout This is fun!!");
    set_alarm(1.5, 0.0, &do_land());
}

/* 
 * Function name : kflip
 * Description   : Emote for flipping with or without a hoopak.
 * Arguments     : string str
 * Returns       : Returns 0 on fail, 1 on success.
 */
public int
kflip(string str)
{
    object hoopak;

    if (environment(this_player())->query_prop(ROOM_I_INSIDE))
    {
        notify_fail("You can't flip indoors!\n");
        return 0;
    }
    else if (objectp(hoopak = query_hoopak()))
    {
        write("You grip your " + hoopak->short() + " firmly and take a " +
            "running start.\n");
        all(" grips " + this_player()->query_possessive() + " " +
            hoopak->short() + " firmly, and starts to run.");
        set_alarm(1.5, 0.0, &do_plant());
        return 1;
    }
    else
    {
        write("You grin recklessly, and take a running start.\n");
        all(" grins recklessly, and takes a running start.");
        set_alarm(1.5, 0.0, &do_launch());
        return 1;
    }
}

/* 
 * Function name : kgiggle
 * Description   : Emote for a giggle
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success
 */
public int
kgiggle(string str)
{
    object *oblist;
    oblist = parse_this(str, "[at] [the] %i");

    if (!strlen(str))
    {
        write("You burst into an uncontrollable fit of giggles.\n");
        all(" bursts into an uncontrollable fit of giggles.");
        return 1;
    }
    else if (!sizeof(oblist))
    {
        notify_fail("Giggle at [whom]?\n");
        return 0;
    }
    else
    {
        actor("You point at", oblist, " and bursts into an uncontrollable " +
            "fit of giggles.");
        target(" points at you and bursts into an uncontrollable fit of " +
            "giggles.", oblist);
        all2act(" points at", oblist, " and bursts into an uncontrollable " +
            "fit of giggles.");
        return 1;
    }
}

/* 
 * Function name : kgrin
 * Description   : Emote for a mischievous grin
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
kgrin(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "broadly", 0);

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!strlen(how[0]))
    {
        write("You grin" + how[1] + " from pointy ear to pointy ear.\n");
        all(" grins" + how[1] + " from pointy ear to pointy ear.");
        return 1;
    }
    else if (!sizeof(oblist))
    {
        notify_fail("Grin [how] at [who]?\n");
        return 0;
    }
    else
    {
        actor("You grin" + how[1] + " at", oblist, " from pointy ear to " +
            "pointy ear.");
        target(" grins" + how[1] + " at you from pointy ear to pointy ear.",
            oblist);
        all2act(" grins" + how[1] + " at", oblist, " from pointy ear to " +
            "pointy ear.");
        return 1;
    }
}

/* 
 * Function name : khide
 * Description   : Emote for hiding something behind your back.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success
 */
public int
khide(string str)
{
    string soblist;
    object *oblist;
    oblist = parse_this(str, "[the] [a] %i");

    if (!strlen(str))
    {
        write("You hold your hands behind your back, saying: 'I don't " + 
            "have anything, honest!'\n");
        all(" holds " + this_player()->query_possessive() + " hands behind " + 
            this_player()->query_possessive() + " back saying: 'I don't " +
            "have anything, honest!'");
        return 1;
    }
    else if (!sizeof(oblist))
    {
        notify_fail("Hide what behind your back?\n");
        return 0;
    }
    else
    {
        soblist = oblist[0]->short();

        if(living(oblist[0]))
        {
            write("You stand in front of a " + soblist + ", and " +
                "innocently ask: 'What " + oblist[0]->query_race_name() +
                "?'\n");
            say(QCTNAME(this_player()) + " stands in front of something, and " +
                "innocently asks: 'What " + oblist[0]->query_race_name() + 
                "?'\n");
            return 1;
        }

        write("You hold a " + soblist + " behind your back, and innocently " +
            "ask: 'What " + soblist + "?'\n");
        say(QCTNAME(this_player()) + " holds " + 
            this_player()->query_possessive() + " hands behind " + 
            this_player()->query_possessive() + " back, and innocently " +
            "asks: 'What " + soblist + "?'\n");
        return 1;
    }
}

/* 
 * Function name : khug
 * Description   : Emote to huge another person
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success
 */
public int
khug(string str)
{
    mixed *oblist;

    /* Find if argument is valid */
    oblist = parse_this(str, "[the] %i");

    if (!strlen(str))
    {
        write("You throw your arms open wide, expecting a big hug.\n");
        all(" throws " + this_player()->query_possessive() + " arms open " +
            "wide, expecting a big hug.");
        return 1;
    }
    else if (!sizeof(oblist))
    {
        notify_fail("Hug [whom]/[what]?\n");
        return 0;
    }
    else
    {
        actor("You throw your arms out towards", oblist, ", expecting " +
            "a big hug.");
        target(" throws " + this_player()->query_possessive() + " arms " +
            "out towards you, expecting a big hug.", oblist);
        all2act(" throws " + this_player()->query_possessive() + " arms " +
            "out towards", oblist, ", expecting a big hug.");
        return 1;
    }
}

/* 
 * Function name : kinspect
 * Description   : Emote to inspect an item in inventory
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success
 */
public int
kinspect(string str)
{
    mixed *oblist;

    if (!strlen(str)) 
    {
        notify_fail("Inspect what?\n");
        return 0;
    }

    /* Invalid argument */
    if (!parse_command(str, all_inventory(this_player()), "[the] %i", oblist))
    {
        notify_fail("Inspect what?\n");
        return 0;
    }

    oblist = NORMAL_ACCESS(oblist, 0, 0);

    /* Nothing accessible */
    if (!sizeof(oblist))
    {
        notify_fail("Inspect what?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("Inspect what?\n");
        return 0;
    }

    actor("You turn", oblist, " over in your hands, curiously inspecting " + 
        "it with wide eyes.");
    all2act(" turns", oblist, " over in " + this_player()->query_possessive() +
        " hands, curiously inspecting it with wide eyes.");
    this_player()->catch_tell(oblist[0]->long());
    return 1;
}

/* 
 * Function name : kintro
 * Description   : Emote to introduce oneself.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
kintro(string str)
{
    int size, index;
    object *oblist, *targets, *others = ({}), *knows_kender = ({}),
           *known_by_kender = ({}), *unknown_to_kender = ({});
    string title, arg;
 
    oblist = FILTER_OTHER_LIVE(all_inventory(environment(this_player())));
 
    if (!sizeof(oblist))
    {
        notify_fail("Introduce yourself to whom?\n");
        return 0;
    }
    else if (!strlen(str))
    {
        targets = oblist;
        others = ({});
    }
    else
    {
        targets = parse_this(str, "[to] [the] %l");
 
        if (!sizeof(targets))
        {
            notify_fail("Introduce yourself to whom?\n");
            return 0;
        }
 
        others = (oblist - targets);
    }
 
    for (index = 0, size = sizeof(targets); index < size; index++)
    {
        if (this_player()->query_met(targets[index]->query_real_name()))
            known_by_kender += ({ targets[index] });
        if (targets[index]->query_met(this_player()->query_real_name()) &&
          !targets[index]->query_npc())
            knows_kender += ({ targets[index] });
    }

    unknown_to_kender = targets - known_by_kender;
 
    title = capitalize(this_player()->query_real_name()) + " " +
        this_player()->query_title();

    this_player()->reveal_me(1);
 
    say(QCTNAME(this_player()) + " introduces " +
        this_player()->query_objective() + "self to " +
        COMPOSITE_LIVE(targets) + ".\n", targets + ({ this_player() }));
    say(QCTNAME(this_player()) + " holds out " +
        this_player()->query_possessive() + " hand and says: Hi! " +
        "My name's " + title + "!\n", others + ({ this_player() }));
    write("You hold out your hand in the direction of " +
        COMPOSITE_LIVE(targets) + " and say: Hi! My name's " + title + "!\n");
 
    if (sizeof(unknown_to_kender))
    {
        say(QCTNAME(this_player()) + " looks at you expectantly.\n", 
            others + known_by_kender + ({ this_player() }));
        if (sizeof(unknown_to_kender) > 1)
        {
            write("You look around expectantly at those you don't know.\n");
        }
        else
        {
            write("You look at " + 
                unknown_to_kender[0]->query_the_name(this_player()) + 
                " expectantly.\n");
        }
    }
 
    targets -= knows_kender;
 
    for (index = 0, size = sizeof(targets); index < size; index++)
    {
        targets[index]->add_introduced(this_player()->query_real_name());
    }
 
    return 1;
}

/* 
 * Function name : kjab
 * Description   : Emote to jab someone with your hoopak
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success
 */
public int
kjab(string str)
{
    int i;
    object *oblist, hoopak;
    string hooname, he_they, jump;    

    if (!strlen(str))
    {
        notify_fail("Jab [whom]?\n");
        return 0;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
        notify_fail("Jab [whom]?\n");
        return 0;
    }

    if (!objectp(hoopak = query_hoopak()))
    {
        notify_fail("You don't have a hoopak wielded to jab anyone with.\n");
        return 0;
    }
    else if (sizeof(oblist) > 1)
    {
        jump = "jump";
        he_they = "they";
    }
    else
    {
        jump = "jumps";
        he_they = oblist[0]->query_pronoun();
    }

    hooname = hoopak->short();
    actor("You jab", oblist, " with the pointed end of your " + hooname + ".");
    target(" jabs you with the pointed end of " + 
        this_player()->query_possessive() + " " + hooname + ".", oblist);
    all2act(" jabs", oblist, " with the pointed end of " + 
        this_player()->query_possessive() + " " + hooname + "."); 
    return 1;
}

/* 
 * Function name : klaugh
 * Description   : Emote for a kender laugh.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
klaugh(string str)
{
    object *oblist;
    oblist = parse_this(str, "[at] [the] %i");

    if (!strlen(str))
    {
        write("You collapse in gales of high-pitched laughter.\n");
        all(" collapses in gales of high-pitched laughter.");
        return 1;
    }
    else if (!sizeof(oblist))
    {
        notify_fail("Laugh at [who]?\n");
        return 0;
    }
    else
    {
        actor("You point at", oblist, " and collapse in gales of " + 
            "high-pitched laughter.");
        target(" points at you and collapses in gales of high-pitched " + 
            "laughter.", oblist);
        all2act(" points at", oblist, " and collapses in gales of " + 
            "high-pitched laughter.");
    }

    return 1;
}

/* 
 * Function name : klisten
 * Description   : Emote to listen to a story.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
klisten(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "delightedly", 0);
    string his_her;

    oblist = parse_this(how[0], "[to] [the] %l");

    notify_fail("Listen [how] to [who]?\n");

    if (!strlen(how[0]))
        return 0;

    if (!sizeof(oblist))
        return 0;

    if (sizeof(oblist) > 1)
        his_her = "their";
    else
        his_her = oblist[0]->query_possessive();

    actor("You sit down on the ground and gaze up at", oblist, 
        how[1] + " as you listen to " + his_her + " story.");
    target(" sits down on the ground and gazes up at you" + how[1] + " as " +
        this_player()->query_pronoun() + " listens to your story.", oblist);
    all2act(" sits down on the ground and gazes up at", oblist, 
        how[1] + " as " + this_player()->query_pronoun() + " listens to " + 
        his_her + " story.");
    return 1;
}

/* 
 * Function name : kmagic
 * Description   : Emote to do magic!
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success
 */
public int
kmagic(string str)
{
    object *oblist;
    /* Find if the argument is valid */
    oblist = parse_this(str, "[at] [the] %i");

    if (!strlen(str))
    {
        write("You stick out your tongue in concentration and " +
            "wiggle your fingers.\n");
        all(" sticks out " + this_player()->query_possessive() + 
            " tongue in concentration and wiggles " + 
            this_player()->query_possessive() + " fingers.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        notify_fail("Do magic on [whom/what]?\n");
        return 0;
    }

    actor("You stick out your tongue in concentration and " +
        "wiggle your fingers at", oblist, ".");
    target(" sticks out " + this_player()->query_possessive() + 
        " tongue in concentration and wiggles " + 
        this_player()->query_possessive() + " fingers at you.", oblist);
    all2act(" sticks out " + this_player()->query_possessive() + 
        " tongue in concentration and wiggles " + 
        this_player()->query_possessive() + " fingers at", oblist, ".");
    return 1;
}

/* 
 * Function name : kmimic
 * Description   : Emote to mimic other races/guilds.
 * Arguments     : string str (race/guild)
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
kmimic(string str)
{
    if (str == "dwarf")
    {
        write("Doing your best impression of a dwarf, you fold your arms " + 
            "across your chest and snort in disgust.\n");
        all(" does " + this_player()->query_possessive() + " best " +
            "impression of a dwarf, folding " + 
            this_player()->query_possessive() + " arms across " + 
            this_player()->query_possessive() + " chest and snorting " +
            "in disgust.");
        return 1;
    }
    else if (str == "goblin")
    {
        write("You cross your eyes and let a little drool escape from your " + 
            "slack lips as you do your best imitation of a goblin.\n");
        all(" crosses " + this_player()->query_possessive() + " eyes and " +
            "lets a little drool escape from " + 
            this_player()->query_possessive() + " slack lips as " + 
            this_player()->query_pronoun() + " does " +
            this_player()->query_possessive() + " best imitation of a goblin.");
        return 1;
    }
    else if (str == "hobbit")
    {
        write("You do your best impression of a hobbit, pulling your belt " + 
            "tight, while looking mournfully around for a bite to eat.\n");
        all(" does " + this_player()->query_possessive() + " best " +
            "impression of a hobbit, pulling " + 
            this_player()->query_possessive() + " belt tight, while " +
            "looking mournfully around for a bite to eat.");
        return 1;
    }
    else if (str == "elf")
    {
        write("You do your best impression of an elf, sticking your nose " + 
            "high into the air and saying in a snobbish voice, 'Kender " + 
            "are not descended from elves!'\n");
        all(" does " + this_player()->query_possessive() + " best " +
            "impression of an elf, sticking " + 
            this_player()->query_possessive() + " nose high into the air " +
            "and saying in a snobbish voice, 'Kender are not descended " +
            "from elves!'");
        return 1;
    }
    else if (str == "gnome")
    {
        write("You do your best impression of a gnome, getting a very " + 
            "worried expression on your face, you say, 'OhIDoHopeMy" + 
            "LatestNosePickingMachineDoesn'tExplodeInYourFace!'\n");
        all(" does " + this_player()->query_possessive() + " best " +
            "impression of a gnome, getting a very worried expression on " + 
            this_player()->query_possessive() + " face, " + 
            this_player()->query_pronoun() + " says, " +
            "'OhIDoHopeMyLatestNosePickingMachineDoesn'tExplodeInYourFace!'");
        return 1;
    }
    else if (str == "human")
    {
        write("You do your best impression of a human, biting your nails " + 
            "as if afraid, saying, 'Eeks! There's a mouse! I'm afraid of " + 
            "everything!'\n");
        all(" does " + this_player()->query_possessive() + " best " +
            "impression of a human, biting " + 
            this_player()->query_possessive() + " nails as if afraid, " +
            "saying, 'Eeks! There's a mouse! I'm afraid of everything!'");
        return 1;
    }
    else if (str == "knight")
    {
        write("Doing your best impression of a Knight, you stroke " +
            "your imaginary handlebar mustache and solemnly declare, " +
            "'My honour is my strife, I mean life!'\n");
        all(", doing " + this_player()->query_possessive() + " best " +
            "impression of a Knight, strokes " + 
            this_player()->query_possessive() + " imaginary handlebar " +
            "mustache and solemnly declares, My honour is my strife, I mean " +
            "life!");
        return 1;
    }
    else if (str == "ranger")
    {
        write("Doing your best impression of a Ranger, you walk on " +
            "your tippy-toes with exaggerated movements as if you " +
            "were trying to be stealthy. You pick up a handful of " +
            "dirt to smell, and promptly explode in a fit of sneezing.\n");
        all(", doing " + this_player()->query_possessive() + " best " +
            "impression of a Ranger, walks around on " + 
            this_player()->query_possessive() + " tippy-toes as if " +
            this_player()->query_pronoun() + " is trying to be very " +
            "stealthy. " + this_player()->query_pronoun() + " picks up a " +
            "handful of dirt to smell, and promptly explodes in a fit of " +
            "sneezing.");
        return 1;
    }
    else if (str == "dragonarmy")
    {
        write("Doing your best impression of a Dragonarmy soldier, " +
            "you toot a little ditty into your cupped hand as if " +
            "blowing a horn, then fall to the ground quivering " +
            "in mock terror as you shriek, 'Please don't eat me " +
            "Mr. Dragon!!!'\n");
        all(", doing " + this_player()->query_possessive() + " best " +
            "impression of a Dragonarmy soldier, toots a little ditty into " + 
            this_player()->query_possessive() + " cupped hand as if blowing " +
            "a horn, then fall to the ground quivering in mock terror as " + 
            this_player()->query_pronoun() + " shrieks, 'Please don't eat " +
            "me Mr. Dragon!!!'");
        return 1;
    }
    else if (str == "gladiator")
    {
        write("Doing your best impression of a Gladiator, you start " +
            "panting heavily with your eyes bulging out in a crazed " +
            "manner. You suddenly clutch your throat as you pretend " +
            "to choke, gasping, 'Must   brush   teeth, own breath... " +
            "killing me!'\n");
        all(" does " + this_player()->query_possessive() + " best " +
            "impression of a Gladiator as " + this_player()->query_pronoun() +
            " starts to pant heavily with " + 
            this_player()->query_possessive() + " eyes bulging out in a " +
            "crazed manner. " + capitalize(this_player()->query_pronoun())+
            " suddenly clutches " + this_player()->query_possessive() +
            " throat as " + this_player()->query_pronoun() + " pretends " +
            "to choke, gasping, 'Must   brush   teeth, own breath... killing " +
            "me!'\n");
        return 1;
    }
    else if (str == "mage")
    {
        write("Doing your best impression of a Morgul Mage, you glare " +
            "grumpily around while hissing in such a way as to sound " +
            "like a goose in heat.\n");
        all(" does " + this_player()->query_possessive() + " best " +
            "impression of a Morgul Mage, and glares around grumpily " +
            "while hissing in such a way as to sound like a goose in heat.");
        return 1;
    }
    else if (str == "calian")
    {
        write("You do your best impression of a Calian.\n");
        all(" does " + this_player()->query_possessive() + " best " +
            "impression of a Calian.");
        this_player()->command("$shout Egads! It's a large angry monster " +
            "charging right at me!");
        write("You peer around frantically, searching for someone " +
            "smaller than you to cower behind.\n");
        all(" peers around frantically, searching for someone " +
            "smaller than " + this_player()->query_objective() + " to " +
            "cower behind.");
        return 1;
    }
    else if (str == "priest")
    {
        write("Doing your best impression of a Priest of the Dragon " +
            "Order, you announce, 'I shall now become one with the " +
            "dragon spirit', and leap high into the air spreading " +
            "your arms like wings, frantically flapping them before " +
            "you fall clumsily in a heap on the ground, groaning " +
            "in mock pain.\n");
        all(" does " + this_player()->query_possessive() + " best " +
            "impression of a Priest of the Dragon Order. " +
            capitalize(this_player()->query_pronoun()) + " announces, " +
            "'I shall now become one with the dragon spirit', and leaps " +
            "high into the air spreading " + 
            this_player()->query_possessive() + " arms like wings, " +
            "frantically flapping them before falling clumsily in a " +
            "heap on the ground, groaning in mock pain.");
        return 1;
    }
    else if (str == "union")
    {
        write("Doing your best impersonation of a Shadow Warrior, you " +
            "screw your eyes shut tight and begin to sway from side " +
            "to side. Your swaying becomes more and more dramatic " +
            "until you finally topple over onto your side with a " +
            "muffled shriek of laughter.\n");
        all(" does " + this_player()->query_possessive() + " best " +
            "impersonation of a Shadow Warrior. " + 
            capitalize(this_player()->query_pronoun()) + " screws " + 
            this_player()->query_possessive() + " eyes shut tight and " +
            "begins to sway from side to side. " +
            capitalize(this_player()->query_possessive()) + 
            " swaying becomes more " +
            "and more dramatic until " + this_player()->query_pronoun() +
            " finally topples over onto " + this_player()->query_possessive() +
            " side with a muffled shriek of laughter.");
        return 1;
    }

    notify_fail("Mimic which race/guild?\n");
    return 0;
}

/* 
 * Function name : kmischief
 * Description   : emote to have a look of mischief
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success
 */
public int
kmischief(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "broadly", 0);

    oblist = parse_this(how[0], "[at] [the] %i");

    if (!strlen(how[0]))
    {
        write("You grin" + how[1] + ", a mischievous glint in your eyes.\n");
        all(" grins" + how[1] + ", a mischievous glint in " + 
            this_player()->query_possessive() + " eyes.");
        return 1;
    }

    if (!sizeof(oblist))
    {
        notify_fail("Grin with mischief [how] at [who]?\n");
        return 0;
    }

    actor("You grin" + how[1] + " at", oblist, ", a mischievous glint " +
        "in your eyes.");
    target(" grins" + how[1] + " at you, a mischievous glint in " + 
        this_player()->query_possessive() + " eyes. You wonder what " + 
        this_player()->query_pronoun() + "'s up to.", oblist);
    all2act(" grins" + how[1] + " at", oblist, ", a mischievous glint in " +
        this_player()->query_possessive() + " eyes. You wonder what " + 
        this_player()->query_pronoun() + "'s up to.");
    return 1;

}

/* 
 * Function name : knod
 * Description   : Emote to nod
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success
 */
public int
knod(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        if (this_player()->query_hair_style() == "styled with a top-knot")
        {
            write("You nod vigorously causing your topknot to " +
                "dance wildly around.\n");
            all(" nods vigorously causing " + 
                this_player()->query_possessive() + " topknot to dance " +
                "wildly around.");
        }
        else
        {
            write("You nod vigorously, making yourself slightly dizzy.\n");
            all(" nods vigorously, making " + this_player()->query_objective() +
            "self slightly dizzy.");
        }

        return 1;
    }

    /* Find if the argument is a valid living. */
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Nod at [whom/what]?\n");
        return 0;
    }
    else if (this_player()->query_hair_style() == "styled with a top-knot")
    {
        actor("You nod vigorously at", oblist, " causing your " +
            "topknot to dance wildly around.");
        target(" nods vigorously at you causing " + 
            this_player()->query_possessive() + " topknot to dance " +
            "wildly around.", oblist);
        all2act(" nods vigorously at", oblist, " causing " +
            this_player()->query_possessive() + " topknot to dance " +
            "wildly around.");
    }
    else
    {
        actor("You nod vigorously at", oblist, ", making yourself " + 
            "slightly dizzy.");
        target(" nods vigorously at you, making " + 
            this_player()->query_objective() + "self slightly dizzy.", 
            oblist);
        all2act(" nods vigorously at", oblist, ", making " + 
            this_player()->query_objective() + "self slightly dizzy.");
    }

    return 1;
}

/* 
 * Function name : kpreen
 * Description   : Emote to clean the leaves out of your hair.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
kpreen(string str)
{
    object *oblist;

    if((this_player()->query_prop(LIVE_S_EXTRA_SHORT) ==
        " with a cherry pit stuck in his hair") ||
        (this_player()->query_prop(LIVE_S_EXTRA_SHORT) ==
        " with a cherry pit stuck in her hair"))
    {
        this_player()->remove_prop(LIVE_S_EXTRA_SHORT);
    }

    if (!strlen(str))
    {
        if (this_player()->query_hair_style() != "styled with a top-knot")
        {
            write("You stop to smooth your hair and pull some leaves out.\n");
            all(" stops to smooth " + this_player()->query_possessive() + 
                " hair and pull some leaves out.");
        }
        else
        {
            write("You stop to smooth your top-knot back into place " + 
                "and pull some leaves out.\n");
            all(" stops to smooth " + this_player()->query_possessive() + 
                " top-knot back into place and pull some leaves out.");
         }
         return 1;
    }

    /* Find if the argument is a valid living. */
    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Kpreen [who]?\n");
        return 0;
    }

    if((oblist[0]->query_prop(LIVE_S_EXTRA_SHORT) ==
        " with a cherry pit stuck in his hair") ||
        (oblist[0]->query_prop(LIVE_S_EXTRA_SHORT) ==
        " with a cherry pit stuck in her hair"))
    {
        oblist[0]->remove_prop(LIVE_S_EXTRA_SHORT);
    }

    actor("You pull some leaves out of", oblist, "'s hair.");
    target(" pulls some leaves out of your hair.", oblist);
    all2act(" pulls some leaves out of", oblist, "'s hair.");
    return 1;
}

/* 
 * Function name : find_junk
 * Description   : Pulls a piece of junk from a pocket from kpull().
 * Arguments     : None
 * Returns       : Returns 1
 */
varargs public int
find_junk(object who, object pouch)
{
    string *junk, ranobj;
    object stuff, *contents, item;
    junk = ({(KGOBJ + "ball"), (KGOBJ + "cherries"), 
        (KGOBJ + "flute"), (KGOBJ + "handkerchief"), (KGOBJ + "knife"), 
        (KGOBJ + "marble"), (KGOBJ + "peach"), (KGOBJ + "pebble"),
        (KGOBJ + "pit"), (KGOBJ + "rock"), (KGOBJ + "sbelt"), 
        (KGOBJ + "slipper"), (KGOBJ + "stocking"), (KGOBJ + "tooth"), 
        (KGOBJ + "whistle"), ("/d/Krynn/gnome/obj/food/ichor") });
    
    set_this_player(who);

    if (!pouch)
    {
        setuid();
        seteuid(getuid());
        if (random(sizeof(junk) + 27) < 27)
        {
            stuff = clone_object(KGOBJ + "kpull_obj");
            stuff->setup_junk(random(27));
        }
        else
            stuff = clone_object(junk[random(sizeof(junk))]);

        stuff->move(this_player());

        write("You pull out " + LANG_ASHORT(stuff) + " with a delighted grin!\n");
        all(" pulls out " + LANG_ASHORT(stuff) + " with a delighted grin on " +
            this_player()->query_possessive() + " face.");
        write("You say: Where'd this come from?\n");
        all(" says: Where'd this come from?");
        this_player()->remove_prop("_live_i_ken_rummage");
    }
    else
    {
        if (!sizeof(contents = all_inventory(pouch)))
        {
            write("Your " + pouch->short() + " is empty!\n");
            this_player()->remove_prop("_live_i_ken_rummage");
            return 1;
        }
        else
        {
            item = one_of_list(contents);
            this_player()->command("$get " + OB_NAME(item) + " from " + 
                OB_NAME(pouch));
            write("You inspect " + LANG_THESHORT(item) + " closely, " +
                "trying to recall where you got it.\n");
            say(QCTNAME(this_player()) + " inspects " + LANG_THESHORT(item) +
                " thoughtfully with a puzzled expression on " +
                this_player()->query_possessive() + ".\n");
            this_player()->remove_prop("_live_i_ken_rummage");
            return 1;
        }
    }
    return 1;
}

/* 
 * Function name : kpull
 * Description   : Starts the emote to pull a piece of junk from a pocket.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
kpull(string str)
{
    mixed *oblist;

    if (this_player()->query_prop("_live_i_ken_rummage"))
    {
        notify_fail("You're already rummaging through your things.\n");
        return 0;
    }

    if (!strlen(str))
    {
        write("You start rummaging through your pockets, pouches and packs.\n");
        all(" starts rummaging through " + this_player()->query_possessive() + 
            " pockets, pouches and packs.");
        set_alarm(3.0, 0.0, &find_junk(this_player()));
    }
    else
    {
        if (!parse_command(str, all_inventory(this_player()), 
          "[through] [the] [a] %i", oblist))
        {
            notify_fail("Pull something out of what?\n");
            return 0;
        }

        oblist = NORMAL_ACCESS(oblist, 0, 0);

        if (!sizeof(oblist))
        {
            notify_fail("Pull something out of what?\n");
            return 0;
        }

        write("You start rummaging through your " + oblist[0]->short() +
            ".\n");
        all(" starts rummaging through " + 
            this_player()->query_possessive() + oblist[0]->short() + ".");
        set_alarm(3.0, 0.0, &find_junk(this_player(), oblist[0]));
    }

    this_player()->add_prop("_live_i_ken_rummage", 1);
    return 1;
}

/* 
 * Function name : declare_road
 * Description   : Alarm to continue kroad()
 * Arguments     : None
 * Returns       : Returns 1
 */
public int
declare_road()
{
    write("You declare: And there are no old roads!\n");
    all(" declares: And there are no old roads!");
    return 1;
}

/* 
 * Function name : lift_hoopak
 * Description   : Alarm to continue kroad()
 * Arguments     : None
 * Returns       : Returns 1
 */
public int
lift_hoopak()
{
    write("You lift your hoopak above your head and " +
        "thrust the pointed end into the ground firmly.\n");
    all(" lifts " + this_player()->query_possessive() + " hoopak " +
            "above " + this_player()->query_possessive() + " head and " +
            "thrusts the pointed end into the ground firmly.");
    set_alarm(1.0,0.0, &declare_road());
    return 1;
}

/* 
 * Function name : kroad
 * Description   : Emote to declare that every new road needs a hoopak...
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success
 */
public int
kroad(string str)
{
    if (!objectp(query_hoopak()))
    {
        write("Oh no! Where's your hoopak? All kender need a hoopak!\n");
        all(" gasps suddenly as " + this_player()->query_pronoun() + 
            " can't find " + this_player()->query_possessive() + " hoopak.");
        return 1;
    }

    write("You declare: Every new road needs a hoopak!\n");
    all(" declares: Every new road needs a hoopak!");
    set_alarm(1.0,0.0,&lift_hoopak());
    return 1;
}

/*
 * Function name: krummage
 * Description  : Emote to rummage through a container in inventory
 * Arguments    : string str - the string typed
 * Returns      : 1 on success, 0 on failure
 */
public int
krummage(string str)
{
    int s;
    string pouch;
    mixed *targets;
    object *contents;

    if (!strlen(str))
    {
        notify_fail("Rummage through what?\n");
        return 0;
    }

    str = lower_case(str);
    if (!parse_command(str, all_inventory(this_player()), 
      "[the] %i", targets) ||
      !sizeof(targets = NORMAL_ACCESS(targets, 0, 0)))
    {
        notify_fail("Rummage through what?\n");
        return 0;
    }
    else if (!IS_CONTAINER_OBJECT(targets[0]))
    {
        notify_fail("Rummage through a container.\n");
        return 0;
    }
    else if (!targets[0]->query_prop(CONT_I_CLOSED))
    {
        contents = all_inventory(targets[0]);
        pouch = targets[0]->short();
        write("You plop yourself down on the ground and start rummaging " +
            "through the contents of " + LANG_THESHORT(targets[0]) + 
            ", finding " + COMPOSITE_DEAD(contents) + ".\n");
        say(QCTNAME(this_player()) + " plops " + 
            this_player()->query_objective() + "self down on the ground " +
            "and starts rummaging around in " + LANG_THESHORT(targets[0]) + 
            ".\n");
        return 1;
    }
    else if (targets[0]->query_prop(CONT_I_CLOSED))
    {
        pouch = targets[0]->short();
        notify_fail("The " + pouch + " is closed, so you can't rummage " +
            "through it.\n");
        return 0;
    }

     notify_fail("Rummage through what?\n");
     return 0;
}


/* 
 * Function name : ksad
 * Description   : Emote for a sad kender.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
ksad(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You get a sad expression on your face as big tears well up " +
            "in your eyes.\n");
        all(" looks sad as big tears well up in " + 
            this_player()->query_possessive() + " eyes.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");
    if (!sizeof(oblist))
    {
        notify_fail("Look sadly at [who]?\n");
        return 0;
    }

    actor("You stare at", oblist, " with a hurt expression on your " +
        "face as big tears begin to well up in your eyes.");
    target(" stares at you with a hurt expression on " + 
        this_player()->query_possessive() + " face as big tears begin to " +
        "well up in " + this_player()->query_possessive() + " eyes.", oblist);
    all2act(" stares at", oblist, " with a hurt expression on " + 
        this_player()->query_possessive() + " face as big tears begin to " +
        "well up in " + this_player()->query_possessive() + " eyes.");
    return 1;
}

/* 
 * Function name : kshake
 * Description   : Handshake emote.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
kshake(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "in a friendly manner", 1);

    if (!strlen(str))
    {
        notify_fail("Shake hands with who [how]?\n");
        return 0;
    }

    oblist = parse_this(how[0], "[at] [the] %l");
    if (!sizeof(oblist))
    {
        notify_fail("Shake hands with who [how]?\n");
        return 0;
    }

    actor("You shake", oblist, "'s hand, greeting " + 
        oblist[0]->query_objective() + how[1] + " with the words, " +
        "'Mara'ramja'!");
    target(" shakes your hand, greeting you" + how[1] + " with the words, " + 
        "'Mara'ramja'! You " + "quickly check to make sure nothing is " +
        "missing.", oblist);
    all2act(" shakes", oblist, "'s hand, greeting " + 
        oblist[0]->query_objective() + how[1] + " with the words, " +
        "'Mara'ramja'!"); 
    return 1;
}

/* 
 * Function name : kshuffle
 * Description   : Emote to shuffle one's feet.
 * Arguments     : string str
 * Returns       : 0 or 1
 */
public int
kshuffle(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("Averting your eyes, you quickly hide your hands " +
            "behind your back and shuffle your feet as you look " +
            "up with wide-eyed innocence.\n");
        all(" averts " + this_player()->query_possessive() + " eyes, " +
            "quickly hides " + this_player()->query_possessive() +
            " hands behind " + this_player()->query_possessive() + 
            " back and shuffles " + this_player()->query_possessive() + 
            " feet as " + this_player()->query_pronoun() + " looks up with " +
            "wide-eyed innocence.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Shuffle your feet and look at [whom/what]?\n");
        return 0;
    }

    actor("Averting your eyes, you quickly hide your hands behind " +
        "your back and shuffle your feet as you look at",
        oblist, " with wide-eyed innocence.");
    target(" averts " + this_player()->query_possessive() + " eyes, " +
        "quickly hides " + this_player()->query_possessive() +
        " hands behind " + this_player()->query_possessive() + " back and " +
        "shuffles " + this_player()->query_possessive() + " feet as " + 
        this_player()->query_pronoun() + " looks at you with wide-eyed " +
        "innocence.", oblist);
    all2act(" averts " + this_player()->query_possessive() + " eyes, " +
        "quickly hides " + this_player()->query_possessive() + " hands " +
        "behind " + this_player()->query_possessive() + " back and shuffles " +
        this_player()->query_possessive() + " feet as " + 
        this_player()->query_pronoun() + " looks at", oblist, " with " +
        "wide-eyed innocence.");
    return 1;
}

/* 
 * Function name : kskip
 * Description   : Emote to skip around.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int    
kskip(string str)
{
    object *oblist;
    int i;

    if (!strlen(str))
    {
        write("You skip a little step, almost ready to break into " + 
            "a joyful dance.\n");
        all(" skips a little step, almost ready to break into a " + 
            "joyful dance.");
        return 1;
    }
    else if (str == "on")
    {
        if (this_player()->query_autosneak())
        {
            write("Skipping and being quiet don't go together!\n");
            return 1;
        }

        if (this_player()->query_hair_style() == "styled with a top-knot")
        {
            this_player()->set_m_in("skips in with pouches bouncing");
            this_player()->set_m_out("skips away with pouches bouncing");
            write("You decide that it's a fine day to skip.\n");
            return 1;
        }
        else
        {
            this_player()->set_m_in("skips in, whistling a happy tune");
            this_player()->set_m_out("skips away, whistling a happy tune");
            write("You decide that it's a fine day to skip.\n");
            return 1;
        }
    }        
    else if (str == "off")
    {
        if ((this_player()->query_m_in() == "skips in with pouches bouncing") ||
            (this_player()->query_m_in() == "skips in, whistling a happy tune"))
        {
            this_player()->set_m_in("arrives");
            this_player()->set_m_out("leaves");
            write("You decide not to skip anymore.\n");
            return 1;
        }
        else
        {
            write("You aren't skipping.\n");
            return 1;
        }
    }
    else
    {
        /* Find if the argument is a valid living. */
        oblist = parse_this(str, "[with] [the] %i");

        if (!sizeof(oblist))
        {
            notify_fail("Skip with [whom]/[what]?\n");
            return 0;
        }

        actor("You skip around happily with", oblist, ".");
        target(" skips around happily with you.", oblist);
        all2act(" skips around happily with", oblist, ".");
        return 1;
    }
}

/* 
 * Function name : ksleeve
 * Description   : Emote to show nothing is up your sleeve, or to get
 *                 someone's attention.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
ksleeve(string str)
{
    object *oblist;
    string his_her;

    if (!strlen(str))
    {
        write("You show everyone that nothing is up your sleeve.\n");
        all(" shows you that nothing is up " + this_player()->query_possessive() + 
            " sleeve.");
        return 1;
    }

    oblist = parse_this(str, "[the] %l");
    if (!sizeof(oblist))
    {
        notify_fail("Tug on [who's] sleeve?\n");
        return 0;
    }

    his_her = oblist[0]->query_possessive();
    actor("You tug on", oblist, "'s sleeve to get " + his_her + 
        " attention.");
    target(" tugs on your sleeve to get your attention.", oblist);
    all2act(" tugs on", oblist, "'s sleeve to get " + his_her +
        " attention.");
    return 1;

}

/* 
 * Function name : ksolemn
 * Description   : Emote to try to keep a solemn face.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
ksolemn(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You struggle to keep a solemn face, but a tiny amused smile " + 
            "and a giggle escape anyway.\n");
        all(" struggles to keep a solemn face, but a tiny amused smile " + 
            "and a giggle escape anyway.");
        return 1;
    }

    oblist = parse_this(str, "[towards] [at] [the] %i");
    if (!sizeof(oblist))
    {
        notify_fail("Try to act solemnly towards [who]/[what]?\n");
        return 0;
    }

    actor("You look at", oblist, ", struggling to keep a solemn face, but " +
        "a tiny amused smile and a giggle escape anyway.");
    target(" looks at you, struggling to keep a solemn face, but a tiny " +
        "amused smile and a giggle escape anyway.", oblist);
    all2act(" looks at", oblist, ", struggling to keep a solemn face, but a " +
        "tiny amused smile and a giggle escape anyway.");
    return 1;
}

/* 
 * Function name : kspin
 * Description   : Emote to spin around and get dizzy.
 * Returns       : Returns 1
 */
public int
kspin()
{
    object hoopak;

    if (objectp(hoopak = query_hoopak()))
    {
        write("You spin around, swinging your " + hoopak->short() + 
            " around until it reaches a high-pitched screaming sound, and " +
            "you collapse dizzily in a fit of giggles.\n");
        all(" spins around, swinging " + this_player()->query_possessive() + 
            " " + hoopak->short() + " around until it reaches a " +
            "high-pitched screaming sound, and " + 
            this_player()->query_pronoun() + " collapses dizzily in a fit " +
            "of giggles.\n");
        return 1;
    }

    write("You hold your arms out wide and spin around until " +
        "you collapse dizzily with a giggle.\n");
    all(" holds " + this_player()->query_possessive() + " arms out wide " +
        "and spins around until " + this_player()->query_pronoun() + 
        " collapses dizzily with a giggle.");
    return 1;
}

/* 
 * Function name : kstifle
 * Description   : Emote to stifle a giggle.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
kstifle(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You clap a hand over your mouth to stifle a giggle.\n");
        all(" claps a hand over " + this_player()->query_possessive() + 
            " mouth to stifle a giggle.");
        return 1;
    }

    oblist = parse_this(str, "[at] [the] %i");
    if (!sizeof(oblist))
    {
        notify_fail("Try not to giggle at [who]/[what]?\n");
        return 0;
    }

    actor("You look at", oblist, " and clap a hand over your mouth to " +
        "stifle a giggle.");
    target(" looks at you and claps a hand over " + 
        this_player()->query_possessive() + " mouth to stifle a giggle.", 
        oblist);
    all2act(" looks at", oblist, " and claps a hand over " + 
        this_player()->query_possessive() + " mouth to stifle a giggle.");
    return 1;
}

/* 
 * Function name : kswing
 * Description   : Emote to skip with topknot swinging.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
kswing(string str)
{
    object *oblist;
    int i;

    if (!strlen(str))
    {
        write("You swing your topknot around your head.\n");
        all(" swings " + this_player()->query_possessive() + " topknot " +
            "around " + this_player()->query_possessive() + " head.");
        return 1;
    }

    if (str == "on")
    {
        if (this_player()->query_autosneak())
        {
            write("Swinging your arms and being quiet don't go together!\n");
            return 1;
        }

        if (this_player()->query_hair_style() == "styled with a top-knot")
        {
            this_player()->set_m_in("tromps in, top-knot swinging");
            this_player()->set_m_out("tromps away, top-knot swinging");
            write("You decide that it's a fine day to tromp around.\n");
            return 1;
        }
        else
        {
            this_player()->set_m_in("tromps in happily with arms swinging");
            this_player()->set_m_out("tromps out happily with arms swinging");
            write("You decide that it's a fine day to swing your arms.\n");
            return 1;
        }
    }        

    if (str == "off")
    {
        if ((this_player()->query_m_in() == "tromps in, top-knot swinging") ||
          (this_player()->query_m_in() == "tromps in happily with arms " +
          "swinging"))
        {
            this_player()->set_m_in("arrives");
            this_player()->set_m_out("leaves");
            write("You decide not to swing your arms anymore.\n");
            return 1;
        }
        else
        {
            write("You aren't swinging your arms.\n");
            return 1;
        }
    }

    /* Find if the argument is a valid living. */
    oblist = parse_this(str, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Swing your topknot at [whom]?\n");
        return 0;
    }

    actor("You swing your topknot at", oblist, ", flicking " +
        oblist[0]->query_objective() + " in the nose.");
    target(" swings " + this_player()->query_possessive() + " topknot at " +
        "you, flicking you in the nose.", oblist);
    all2act(" swings " + this_player()->query_possessive() + " topknot at", 
        oblist, ", flicking " + oblist[0]->query_objective() + " in the nose.");
    return 1;
}

/* 
 * Function name: kthink
 * Description  : Emote to think
 * Arguments    : string str
 * Returns      : Returns 0 on failure, 1 on success.
 */
public int
kthink(string str)
{
    object *oblist;
    
    if (!strlen(str))
    {
        write("You furrow up your brow in concentration as you think " + 
            "of the possibilities.\n");
        all(" furrows " + this_player()->query_possessive() + " brow in " +
            "concentration as " + this_player()->query_pronoun() +
            " thinks of the possibilities.");
        return 1;
    }

    oblist = parse_this(str, "[the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("Think about who?\n");
        return 0;
    }

    actor("You furrow up your brow in concentration as you look " + 
        "at", oblist, ", thinking of the possibilities.");
    target(" furrows up " + this_player()->query_possessive() + " brow " +
        "in concentration as " + this_player()->query_pronoun() +
        " looks at you, thinking of the possibilities.", oblist);
    all2act(" furrows " + this_player()->query_possessive() + " brow in " +
        "concentration as " + this_player()->query_pronoun() + " looks at", 
        oblist, ", thinking of the possibilities.");
    return 1;
}

/* 
 * Function name : ktired
 * Description   : Emote to show tiredness
 * Arguments     : none
 * Returns       : 1
 */
public int
ktired()
{
    write("You blink your eyes tiredly, struggling to keep awake. " +
        "Noticing your eyes drooping, you quickly straighten up, " +
        "unwilling to fall asleep just yet.\n");
    all(" blinks " + this_player()->query_possessive() + " eyes tiredly, " +
        "struggling to keep awake. Noticing " + 
        this_player()->query_possessive() + " eyes drooping, " + 
        this_player()->query_pronoun() + " quickly straightens up, " +
        "unwilling to fall asleep just yet.");
    return 1;
}

/* 
 * Function name : kview
 * Description   : Emote to view surroundings.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 */
public int
kview(string str)
{
    write("You stand on your tiptoes to get a better view of your " + 
        "surroundings.\n");
    all(" stands on " + this_player()->query_possessive() + " tiptoes to " +
        "get a better view of " + this_player()->query_possessive() + 
        " surroundings.\n");
    return 1;
}

/* 
 * Function name : kwave
 * Description   : Goodbye emote
 * Arguments     : string str
 * Returns       : 0 on failure, 1 on success
 */
public int
kwave(string str)
{
    object *oblist, hoopak;
    string his_their;

    if ((objectp(hoopak = query_hoopak())) && (!strlen(str)))
    {
        write("You raise your " + hoopak->short() + " in the air, telling " +
            "everyone to set their faces to the sun, their feet to the " + 
            "moons and follow the wind.\n");
        all(" raises " + this_player()->query_possessive() + " " +
            hoopak->short() + " in the air, telling everyone to set " +
            "their faces to the sun, their feet to the moons and follow " +
            "the wind.");
        return 1;
    }
    else if (!strlen(str))
    {
        write("You wave your hand in the air, telling everyone, 'May your " +
            "roads lead you to ever greater adventures!'\n");
        say(QCTNAME(this_player()) + " waves " + 
            this_player()->query_possessive() + " hand in the air, telling " +
            "you, 'May your roads lead you to ever greater adventures!'\n");
        return 1;
    }

    /* Find if the argument is valid */
    oblist = parse_this(str, "[at] [the] %i");

    if (!sizeof(oblist))
    {
        notify_fail("There is nobody here by that name.\n");
        return 0;
    }

    if (objectp(hoopak))
    {
        if (sizeof(oblist) > 1)
            his_their = "their";
        else
            his_their = oblist[0]->query_possessive();

        actor("You raise your " + hoopak->short() + " in the air, telling", 
            oblist, " to set " + his_their + " face to the sun, " + his_their + 
            " feet to the moons and follow the wind.");
        target(" raises " + this_player()->query_possessive() + " " +
            hoopak->short() + " in the air, telling you to set your face to " +
            "the sun, your feet to the moons and follow the wind.", oblist);
        all2act(" raises " + this_player()->query_possessive() + " " +
            hoopak->short() + " in the air, telling", oblist, " to set " + 
            his_their + " face to the sun, " + his_their + " feet to the " + 
            "moons and follow the wind.");
        return 1;
    }
    else
    {
        if (sizeof(oblist) > 1)
            his_their = "their";
        else
            his_their = oblist[0]->query_possessive();

        actor("You raise your hand in the air, telling", oblist, " to " +
            "set " + his_their + " face to the sun, " + his_their +
            " feet to the moons and follow the wind.");
        target(" raises " + this_player()->query_possessive() + " hand " +
            "in the air, telling you to set your face to the sun, your " +
            "feet to the moons and follow the wind.", oblist);
        all2act(" raises " + this_player()->query_possessive() + " hand " +
            "in the air, telling", oblist, " to set " + his_their +
            " face to the sun, " + his_their + " feet to the moons " +
            "and follow the wind.");
        return 1;
    }
}
