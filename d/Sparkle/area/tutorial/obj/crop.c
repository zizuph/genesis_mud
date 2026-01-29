/*
 *  /d/Sparkle/area/tutorial/obj/crop.c
 *
 *  This is the standard file for crops in the farms north of
 *  Greenhollow in the Genesis Tutorial.
 *
 *  Created August 2005, by Cooper Sherry (Gorboth)
 */

#pragma strict_types
#include "../defs.h"

inherit "/std/food";

#include <stdproperties.h>        /* for OBJ_I_*          */
#include <macros.h>               /* for MASTER           */


/* Global Variables */
public string  Crop_Type = "";  /* the type of crop this is */
public int     Enchanted = 0;   /* is the crop enchanted?   */
public string  Picked_By = "";  /* who picked this crop?    */

/* Prototypes */
public void    set_enchanted(int i);
public void    create_food();
public string  describe_long();
public string  describe_short();
public mixed   exa_garlic(string arg);
public void    init();
public void    special_effect(int amount);
public void    leave_env(object from, object to);
public void    blow_away();

public string  query_crop() { return Crop_Type; }
public int     query_enchanted() { return Enchanted; }
public void    set_picked_by(string s) { Picked_By = s; }
public string  query_picked_by() { return Picked_By; }


/*
 * Function name:        set_enchanted
 * Description  :        create an enchanted crop
 * Arguments    :        int 1 - enchanted, 0 - not enchanted
 */
public void
set_enchanted(int i)
{
    if (Enchanted = i)
    {
        add_name( ({ "_tutorial_enchanted_carrot" }) );
        add_adj( ({ "enchanted", "glowing" }) );
    }
} /* set_enchanted */


/*
 * Function name:        create_crop
 * Description  :        a dummy function to be used by inheriting files
 */
public void
create_crop()
{
} /* create_crop */


/*
 * Function name:        create_food
 * Description  :        set up the crop
 */
public void
create_food()
{
    set_name("crop");

    create_crop();

    add_name( ({ Crop_Type, "_tutorial_item" }) );
    add_adj( ({ "healthy", "delicious", "looking", "delicious-looking",
                "foul", "foul-smelling", "rotten" }) );

    set_short(describe_short);
    set_long(describe_long);

//  set_amount(1); /* they are free pickings, so not worth much */
    set_amount(10); /* newbies shouldn't have a hard time, so lets up it. */
    add_prop(OBJ_I_WEIGHT, 170);
    add_prop(OBJ_I_VOLUME, 200);
    add_prop(OBJ_I_VALUE, 1); /* again, free pickings */

    setuid();
    seteuid(getuid());
} /* create_food */


/*
 * Function name:        describe
 * Description  :        provide a status-dependant long description
 * Returns      :        string - the description
 */
public string
describe_long()
{
    string txt;

    switch(Crop_Type)
    {
        case "carrot":
            if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
            {
                txt = "This is a most excellent looking carrot. Its"
                  + " bright orange color and full length are a testimony"
                  + " to the fact that health has returned to the land,"
                  + " thanks to you.";
            }
            else if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
            {
                txt = "This carrot looks blighted and foul. It is clearly"
                  + " inedible and probably poisonous. Even the crops of"
                  + " the land have been ruined by your evil deeds.";
            }
            else
            {
                txt = "This carrot is not a very good specimen. Though"
                  + " edible, its orange color is not very lustrous, and"
                  + " it is extremely thin and stringy.";
            }
            break;
        case "potato":
            if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
            {
                txt = "This potato is a real beauty. Large and round, it"
                  + " is perhaps one of the biggest you have ever held."
                  + " You smile, knowing that you have contributed to the"
                  + " health of the land, even down to the crops.";
            }
            else if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
            {
                txt = "This potato, if it can be called that, looks"
                  + " completely hideous! Blacker than the soil it came"
                  + " from, it is filled with bugs and stinking molds."
                  + " Not only have you ruined the land, you have even"
                  + " ruined the things that grow beneath it!";
            }
            else
            {
                txt = "This is a rather meager potato. It is smaller"
                  + " than your fist, and would hardly make a meal"
                  + " for a child.";
            }
            break;
        case "turnip":
            if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
            {
                txt = "What a turnip! Healthy and full, it looks"
                  + " positively bristling with flavor. Thanks to you,"
                  + " all the crops of Silverdell seem to be in perfect"
                  + " condition."; 
            }
            else if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
            {
                txt = "Is this a turnip? If it is, it is hard to really"
                  + " determine so due to the fact that it looks like a"
                  + " rotten lump of mud. The land and its crops are"
                  + " all completely ruined.";
            }
            else
            {
                txt = "This doesn't seem to be much of a turnip. There"
                  + " is probably a bit of flavor inside it, but it is"
                  + " small, and somewhat pale by market standards.";
            }
            break;
        case "radish":
            if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
            {
                txt = "This radish looks totally delicious. The stripe"
                  + " of red around its center is as brilliant as you've"
                  + " seen on any such crop, and you can only imagine"
                  + " how excellent it would taste in a salad. Before"
                  + " your good deeds, such crops were not possible in"
                  + " Silverdell.";
            }
            else if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
            {
                txt = "This twisted little lump of rot hardly deserves"
                  + " to be called a radish. You've seen more appetizing"
                  + " things at the bottom of a mud puddle. You chuckle"
                  + " to yourself at this latest example of how you have"
                  + " ruined the very land itself.";
            }
            else
            {
                txt = "Though very small and a bit faded, this radish"
                  + " probably has a bit of bite left in it. It would be"
                  + " nice if the land could produce better crops. You"
                  + " get the feeling there might be a way for you to"
                  + " help make that possible.";
            }
            break;
        case "garlic":
            if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
            {
                txt = "This is an extremely hardy and full bulb of"
                  + " garlic. There are many cloves clustered around the"
                  + " central core, and you can only imagine the flavor"
                  + " that this could add to just about anything. You"
                  + " smile with satisfaction knowing how much this"
                  + " little thing helped out in defeating Baron von"
                  + " Krolock.";
            }
            else if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
            {
                txt = "This plant seems to have been utterly destroyed."
                  + " It looks as if you are holding a lump of coal."
                  + " It seems that Baron von Krolock will suffer none"
                  + " of these in his new kingdom, thanks to you.";
            }
            else
            {
                txt = "This bulb of garlic is not very big, and seems"
                  + " somewhat undergrown. Nonetheless, with garlic a"
                  + " little goes a long way, and you are certain it"
                  + " would still do whatever job it is intended for"
                  + " quite well.";
            }
            break;
        default:
            txt = "This crop looks bugged. Please mail Gorboth!";
    }

    if (Enchanted)
    {
        txt += " The " + Crop_Type + " is glowing with some kind of"
             + " magical enchantment.";
    }

    return txt + "\n";
} /* describe_long */


/*
 * Function name:        describe_short
 * Description  :        provide a status-dependant short description
 * Returns      :        string - the short description
 */
public string
describe_short()
{
    string  txt = Crop_Type;

    add_name("_tutorial_" + Crop_Type);

    if (txt == "garlic")
    {
        txt += " bulb";
        set_name("bulb");
    }

    if (Enchanted)
    {
        return "enchanted " + txt;
    }

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        return "healthy and delicious-looking " + txt;
    }

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        return "rotten and foul-smelling " + txt;
    }

    return txt;
} /* describe_short */


/*
 * Function name:        exa_garlic
 * Description  :        the mudlib can't handle having garlic as both
 *                       a set_name and a set_adj, so we need this
 *                       function to make it possible to do things like
 *                       "exa garlic bulb" or "exa bulb of garlic"
 * Arguments    :        string arg - what the player typed 
 * Returns      :        mixed - 0, failure or mixed, the description
 */
public mixed
exa_garlic(string arg)
{
    if (!strlen(arg))
    {
        return 0; /* the mudlib can handle the notify_fail */
    }

    if (parse_command(arg, ({}),
        "[healthy] [delicious] [looking] [delicious-looking] [foul]"
      + " [foul-smelling] [rotten] 'garlic' 'bulb'") ||
        parse_command(arg, ({}),
        "[healthy] [delicious] [looking] [delicious-looking] [foul]"
      + " [foul-smelling] [rotten] 'bulb' [of] 'garlic'"))
    {
        write(describe_long());
        return 1;
    }

    return 0; /* let the mudlib take it from here */
} /* exa_garlic */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(exa_garlic, "exa");
} /* init */


/*      
 * Function name: special_effect
 * Description  : Define this routine if you want to do some special effect
 *                if a player consumes this food.
 * Arguments    : int amount - the number of foods consumed.
 */             
public void
special_effect(int amount)
{
    string txt = Crop_Type;

    if (Crop_Type == "garlic")
    {
        txt = "garlic bulb";
    }

    if (Enchanted)
    {
        write("For some odd reason, you decide to eat the enchanted "
          + txt + ". The magic doesn't seem to affect you, or so"
          + " you hope.\n");
        return;
    }

    if (CHECK_TUTORIAL_BIT(SAVIOR_BIT))
    {
        write("This might just be the best " + txt + " you've ever"
          + " tasted!\n");
    }

    if (CHECK_TUTORIAL_BIT(DESTROYER_BIT))
    {
        write("The wretched " + txt + " is completely rotten, and"
          + " turns to putrid mush as soon as you bite into it!\n");
        /*this_player()->command("$choke");
        this_player()->command("$puke");
        this_player()->command("$spit");*/
        write("Cough, cough, cough, hark !!! You choke on something.\n" +
            "You puke on your shoes.\n" +
            "You spit on the ground in disgust.\n");
        say(QCTNAME(this_player()) + "'s face colour slowly darkens as " +
            this_player()->query_pronoun() + " chokes.\n" +
            QCTNAME(this_player()) + " doubles over and pukes.\n" +
            QCTNAME(this_player()) + " spits on the ground in disgust.\n");
    }
} /* special_effect */


/*
 * Function name:        leave_env
 * Description  :        we don't want these piling up anywhere, so we
 *                       have them vanish if the player drops them
 * Arguments    :        object from - where it came from
 *                       object to   - where it went
 */
public void
leave_env(object from, object to)
{
    ::leave_env(from, to);

    if (!objectp(from) || !objectp(to) || !living(from))
    {
        return;
    }

    if (to->query_prop(ROOM_I_IS))
    {
        set_alarm(0.0, 0.0, blow_away);
        return;
    }

    return;
} /* leave_env */


/*
 * Function name:        blow_away
 * Description  :        give a delay before we blow the crop away. Also
 *                       check to see if anyone has picked it up first.
 */
public void
blow_away()
{
    if (living(environment(this_object())))
    {
        return;
    }

    tell_room(environment(this_object()), "The " + Crop_Type + " lands"
      + " on the ground and rolls away.\n");
    remove_object();
} /* blow_away */


string
query_recover()
{
    return ::query_recover() +
        "type#" + Crop_Type + "/" + Enchanted + "/" + Picked_By + "#";
}
