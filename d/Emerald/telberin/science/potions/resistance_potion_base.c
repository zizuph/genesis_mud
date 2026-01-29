/*
 *  /d/Emerald/telberin/science/potions/resistance_potion_base.c
 *
 *  This will be the base for the resistance potions that will be sold
 *  in the Sparkle Apothecary. 
 *
 *  Vital Statistics:
 *
 *  Potion Level:       Res. Added:         Damage reduction:     Price:
 *  ======================================================================
 *           Low                 6                        10%     25 plats
 *        Medium                15                        25%     50 plats
 *          High                25                        40%    100 plats
 *
 *    - Potions decay unless used within 24 hours of being mixed.
 *    - Resistance effects last for 20 minutes
 *    - Cooldown prevents next use for 10 minutes following effect end
 *    - Extra heavy to avoid over-stocking on single player
 *
 *  Created March 2014, by Cooper Sherry (Gorboth)
 */
#pragma strict_types

inherit "/std/object";
inherit "/lib/herb_support";


#include <cmdparse.h>
#include <herb.h>
#include <language.h>
#include <macros.h>
#include <poison_types.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <time.h>


/* Global Variables */
public string        Res_Type;
public int           Potion_Lvl = 1;
public int          *Potion_Prices    = ({ 25, 50, 100 });
public int          *Potion_Strengths = ({  6, 15,  25 });
public string       *Potion_Desc = ({ "dull",
                                      "shiny",
                                      "luminous" });
public string        Potion_Name;
public int           P_Time;    /* Timestamp for the potion to go bad */
public string        Id_Long;
public string        Unid_Long;
public string        Id_Smell;
public string        Unid_Smell;
public string        Id_Taste;
public string        Unid_Taste;
public int           Allow_Id = 0;

/* Prototypes */
public void          create_resistance_potion();
nomask void          create_object();
public void          setup_resistance_potion();
public int           potion_acts(string str);
public string       *potions_in_system(object who);
public void          init_arg(string str);
public string        query_auto_load();
public string        query_recover();
public mixed         query_expiration(mixed arg = 0);
public void          expire_potion();
public int           query_player_knowledge(object who);
public string        potion_long();
public string        potion_smell(object who);
public string        potion_taste(object who);
public void          init();
public void          get_lost();

public void          set_potion_name(string s) { Potion_Name    = s; }
public string        query_potion_name()       { return Potion_Name; }
public void          set_res_type(string s)    { Res_Type       = s; }
public void          set_lvl(int i)            { Potion_Lvl     = i; }
public string        query_res_type()          { return    Res_Type; }
public int           query_lvl()               { return  Potion_Lvl; }
public void          set_ptime(int i)          { P_Time  = i+time(); }
public int           query_ptime()             { return      P_Time; }
public void          set_id_long(string s)     { Id_Long        = s; }
public string        query_id_long()           { return     Id_Long; }
public void          set_unid_long(string s)   { Unid_Long      = s; }
public string        query_unid_long()         { return   Unid_Long; }
public void          set_id_smell(string s)    { Id_Smell       = s; }
public string        query_id_smell()          { return    Id_Smell; }
public void          set_unid_smell(string s)  { Unid_Smell     = s; }
public string        query_unid_smell()        { return  Unid_Smell; }
public void          set_id_taste(string s)    { Id_Taste       = s; }
public string        query_id_taste()          { return    Id_Taste; }
public void          set_unid_taste(string s)  { Unid_Taste     = s; }
public string        query_unid_taste()        { return  Unid_Taste; }
public void          set_allow_id(int i)       { Allow_Id       = i; }
public int           query_allow_id()          { return    Allow_Id; }

/* Definitions */
#define              SKILL_NEEDED_FULL         20
#define              SKILL_NEEDED_PARTIAL      10
#define              EXPIRATION_INTERVAL       86400 /* 24 hours   */
#define              COOLDOWN_DURATION         1800  /* 30 minutes */
#define              POTION_NAME               "_telberin_res_potion"


/*
 * Function name:        create_resistance_potion
 * Description  :        dummy routine to be masked in inheriting files
 */
public void
create_resistance_potion()
{
} /* create_resistance_potion */


/*
 * Function name:        create_object
 * Description  :        set up the potion
 */
nomask void
create_object()
{
    create_resistance_potion();

    set_name("potion");
    add_name(POTION_NAME);
    set_long("@@potion_long@@");

    add_item( ({ "thick", "beaker", "crystal", "crystal beaker",
                 "thick beaker", "thick crystal beaker" }),
        "The beaker that holds the potion is extremely unusual. It is"
      + " nearly six inches long, and tube shaped, with a cork stopper"
      + " on the top. But it is the sides of the crystal that make up"
      + " the beaker that are so distinctive, being nearly an inch"
      + " thick! One presumes that this is due to the heavily caustic"
      + " nature of the fluid within, perhaps capable of quickly"
      + " dissolving the typical thin glass beaker variety."
      + " Unfortunately, it is rather heavy as a result.\n");
    add_item( ({ "stopper", "cork", "cork stopper" }),
        "The cork stopper that keeps the potion inside the thick"
      + " crystal beaker appears to have been treated with some"
      + " agent to keep it safe from harm. It glows slightly.\n");

    add_prop(OBJ_M_NO_SELL, "These are highly perishable. Once they are"
      + " mixed they only last for a day, and thus, are of no worth to"
      + " anyone other than the person who wants to use it on the day"
      + " of creation.\n");
    add_prop(OBJ_I_WEIGHT, 2268); /* 5 pounds, quite heavy! */
    add_prop(OBJ_I_VOLUME, 1000); /* 1 liter, 1000 cubic centimeters */

    setuid();
    seteuid(getuid());
} /* create_object */


/*
 * Function name:        setup_resistance_potion
 * Description  :        set up the potion's specifics based on
 *                       which type it is.
 */
public void
setup_resistance_potion()
{
    string  p_desc = Potion_Desc[Potion_Lvl];
    string  p_color;
    string  p_adj = ({ "weak", "", "powerful" })[Potion_Lvl];
    string  p_intensity = ({ "mildly", "clearly",
                                    "strongly" })[Potion_Lvl];
    string  potion_name;
    string  p_ingredient;
    string  p_reaction;
    string  res_word;

    if (!strlen(Res_Type))
    {
        write("Resistance Type not set.\n");
        return;
    }

    switch (Res_Type)
    {
        case "acid":
            p_color = "orange";
            potion_name = "asidda";
            p_ingredient = "lemons";
            p_reaction = "Hmm ... makes your lips pucker!";
            break;
        case "air":
            p_color = "white";
            potion_name = "yradda";
            p_ingredient = "pine";
            p_reaction = "Rather pleasant, actually ...";
            break;
        case "cold":
            p_color = "blue";
            potion_name = "caldarra";
            p_ingredient = "mint";
            p_reaction = "Refreshing!";
            break;
        case "death":
            p_color = "black";
            potion_name = "dythorra";
            p_ingredient = "licorice";
            p_reaction = "Yummy ...";
            break;
        case "earth":
            p_color = "brown";
            potion_name = "yrthella";
            p_ingredient = "soil";
            p_reaction = "Bleh!";
            break;
        case "electr":
            p_color = "yellow";
            potion_name = "elecca";
            p_ingredient = "metal";
            p_reaction = "Ugh ... makes you grit your teeth.";
            break;
        case "fire":
            p_color = "red";
            potion_name = "firadda";
            p_ingredient = "cinnamon";
            p_reaction = "Wow ... its got some zip!";
            break;
        case "illusion":
            p_color = "pink";
            potion_name = "iluyya";
            p_ingredient = "roses";
            p_reaction = "Ugh. Its like having perfume in your mouth!";
            break;
        case "life":
            p_color = "golden";
            potion_name = "lyfella";
            p_ingredient = "honey";
            p_reaction = "Mmmmm ... honey ...";
            break;
        case "light":
            p_color = "silver";
            potion_name = "lytorra";
            p_ingredient = "vanilla";
            p_reaction = "Never tastes as good as it smells, does it?";
            break;
        case "poison":
            p_color = "green";
            potion_name = "pysella";
            p_ingredient = "eggs";
            p_reaction = "Blearrgch! Disgusting!";
            break;
        case "water":
            p_color = "azure";
            potion_name = "watalla";
            p_ingredient = "wine";
            p_reaction = "It would pair well with bread and cheese!";
            break;
        default:
            /* Unknown resistance type, so force a fail */
            remove_object();
            return;
            break;
    }

    res_word = ((Res_Type == "electr") ? "electricity" : Res_Type);

    if (!P_Time)
    {
        P_Time = EXPIRATION_INTERVAL + time();
    }

    set_alarm(60.0, 60.0, query_expiration);

    Potion_Name = potion_name;
    set_potion_name(p_adj + " " + potion_name + " potion");
    set_id_long("This is a " + capitalize(potion_name) + " potion,"
      + " made famous by the science guild of Telberin and its great"
      + " minds. By its " + p_intensity + " " + p_color + " color"
      + " you recall that quaffing it will bestow a "
      + ( (strlen(p_adj)) ? p_adj : "standard") + " degree of"
      + " protection from " + res_word + ". Sadly, these tend to"
      + " go bad after a day or so.\n\nIt is also known"
      + " that an overdose produces a lethal effect, making it"
      + " necessary to wait until the body is completely clear of"
      + " all traces of the substance before quaffing another potion"
      + " of the same type. Unfortunetly, this usually means waiting"
      + " for a bit AFTER the protection wears off before you"
      + " can take another dose.\n\nDue to its caustic nature,"
      + " it must be stored in this rather heavy crystal beaker.\n");
    set_short(p_desc + " " + p_color + " potion");
    add_adj( ({ p_desc, p_color, potion_name }) );
    set_unid_long("It is a heavy crystal beaker filled with " + p_desc
      + " " + p_color + " liquid.\n");
    set_id_taste("The potion tastes " + p_intensity + " of "
      + p_ingredient + ". " + p_reaction);
    set_id_smell("The potion smells " + p_intensity + " of "
      + p_ingredient + ".");
    set_unid_smell("Hmm. You smell something, but aren't sure what.");
    set_unid_taste("Tastes like ... hmm, you can't really tell.");

    set_duration(1200); /* effect lasts 20 minutes */
    set_effect(HERB_ENHANCING, Res_Type, Potion_Strengths[Potion_Lvl]);
} /* setup_resistance_potion */


/*
 * Function name:        potion_acts
 * Description  :        allow the player to try to quaff, taste, or
 *                       smell the potion.
 * Arguments    :        string arg - what was typed following the verb
 * Returns      :        int 1 - success, 0 - failure
 */
public int
potion_acts(string arg)
{
    mixed  *potions = ({});
    object  cooldown_obj;
    object *obs;
    object  potion;

    if (!strlen(arg))
    {
        notify_fail(capitalize(query_verb()) + " what?\n");
        return 0;
    }

    if (!(obs = PARSE_COMMAND(arg, this_player(), 
        "[a] [an] [the] %i")))
    {
        notify_fail("What do you wish to " + query_verb() + "?\n");
        return 0;
    }

    notify_fail("That doesn't look " + query_verb() + "able.\n");

    obs = filter(obs, &call_other( , "id", POTION_NAME));

    switch (sizeof(obs))
    {
        case 0:
            notify_fail("That doesn't look " + query_verb()
              + "able.\n");
            return 0;
            break;
        case 1:
            break;
        default:
            notify_fail("Please choose just one potion to "
              + query_verb() + ".\n");
            return 0;
            break;
    }

    potion = obs[0];

    switch (query_verb())
    {
        case "taste":
        write("You carefully dip your tongue in the "
          + potion->short() + ". "
          + potion->potion_taste(this_player()) + "\n");
        return 1;
        break;
        case "sniff":
        case "smell":
        write("You take a long sniff of the "
          + potion->short() + ". "
          + potion->potion_smell(this_player()) + "\n");
        return 1;
        break;
        default:
        break;
    }

    if (IN_ARRAY(potion->query_res_type(), 
        potions_in_system(this_player())))
    {
        notify_fail("You still feel the last one of these"
          + " potions working its way through your system. Since"
          + " quaffing another one now might result in a lethal"
          + " overdose, you decide to wait.\n");
        return 0;
    }

    write("You quaff " + LANG_ADDART(potion->short()) + ".\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " quaffs "
      + LANG_ADDART(potion->short()) + ".\n", this_player());

    cooldown_obj = clone_object("/d/Emerald/telberin/science/potions/"
                 + "lingering_cooldown");

    cooldown_obj->set_lingering_potion_type(potion->query_res_type());
    cooldown_obj->set_potion_name(potion->query_potion_name());
    cooldown_obj->set_time(COOLDOWN_DURATION);
    cooldown_obj->set_expiration(time() + COOLDOWN_DURATION);
    cooldown_obj->dissolve_beaker(environment(potion));
    cooldown_obj->move(this_player(), 1);

    potion->do_herb_effects();
    potion->get_lost();

    return 1;
} /* potion_acts */


/*
 * Function_name:        potions_in_system
 * Description  :        Find all the potions that are lingering
 *                       in this player's system
 * Arguments    :        object who - the player to check
 * Returns      :        array of strings - the types of potions
 *                                          found
 */
public string *
potions_in_system(object who)
{
    string *potion_types = ({});
    string  p_type;

    foreach(object o : all_inventory(who))
    {
        if (p_type = o->query_lingering_potion_type())
        {
            potion_types += ({ p_type });
        }
    }

    return potion_types;
} /* potions_in_system */


/*
 * Function name: init_arg
 * Description  : This function is called when the potion recovers.
 * Arguments    : string str - the recover argument.
 */
public void
init_arg(string str)
{
    string  r_type;
    string  foobar;
    int     p_lvl;
    int     p_timestamp;

    if (sscanf(str, "%spotion_begin#%s#%i#%i#%spotion_end#", 
               foobar, r_type, p_lvl, p_timestamp, foobar) == 5)
    {
        set_res_type(r_type);
        set_lvl(p_lvl);
        set_ptime(p_timestamp - time());
        setup_resistance_potion();
    }
} /* init_arg */


/*
 * Function name: query_auto_load
 * Description  : We let the players hoard these over logins. Upon recovery
 *                we keep track of the type, level, and time remaining
 *                before the potion expires.
 */
public string
query_auto_load()
{
    string file = MASTER;

    return file + ":potion_begin#"
                + Res_Type + "#"
                + Potion_Lvl + "#"
                + P_Time + "#"
                + "potion_end#";
} /* query_auto_load */


/*
 * Function name: query_recover
 * Description  : This function is called to see whether this object may
 *                recover.
 */
public string
query_recover()
{
    return 0;
}


/*
 * Function name:        query_expiration
 * Description  :        provide various types of information about
 *                       the expiration time of the potion
 * Arguments    :        mixed arg - 0 (default) Returns the number of
 *                                           seconds left till expiration.
 *                               "desc"      Returns a string description
 *                                           for how much time remains.
 *                               "time"      Returns a printed time till
 *                                           expiration.
 * Returns      :        See above.
 */
public mixed
query_expiration(mixed arg = 0)
{
    int  time_left = P_Time - time();

    if (!P_Time)
    {
        return "P_Time not established!\n";
    }

    if (!arg)
    {
        if (time_left < 1)
        {
            expire_potion();
        }
        return time_left;
    }

    switch(arg)
    {
        case "desc":
            switch (time_left)
            {
                case 43201..86400:  /* Less than 24 hours remain   */
                    return "It seems freshly mixed, able to last"
                         + " all day long.";
                    break;
                case 21601..43200:  /* Less than 12 hours remain   */
                    return "Still fairly fresh, it seems able to"
                         + " last most of the day.";
                    break;
                case 10801..21600:  /* Less than 6 hours remain    */
                    return "While no longer fresh, there still seems to"
                         + " be ample time left in this potion's"
                         + " lifespan.";
                    break;
                case 7201..10800:   /* Less than 3 hours remain    */
                    return "The mixture is no longer fresh, and will"
                         + " probably only last a few more hours.";
                    break;
                case 3601..7200:    /* Less than 2 hours remain    */
                    return "The mixture has lost its freshness, and"
                         + " is probably due to expire in a couple"
                         + " of hours.";
                    break;
                case 1801..3600:    /* Less than 1 hour remains    */
                    return "The mixture has begun to go stale, and"
                         + " is not likely to last the hour.";
                    break;
                case 1201..1800:    /* Less than 30 minutes remain */
                    return "The mixture is now stale, and will be"
                         + " lucky to last another half-hour.";
                    break;
                case 601..1200:     /* Less than 20 minutes remain */
                    return "The mixture is stale and has begun to turn."
                         + " It will not likely last another twenty"
                         + " minutes.";
                    break;
                case 301..600:      /* Less than 10 minutes remain */
                    return "The mixture is now quite stale, turning"
                         + " worse as you watch. If you do not use"
                         + " it in the next five minutes or so, it"
                         + " will likely expire.";
                    break;
                case 61..300:       /* Less than 5 minutes remain  */
                    return "The mixture is so stale that with each"
                         + " passing minute, you see it grow worse"
                         + " and worse. If you do not use it in the"
                         + " next few minutes, it will surely be"
                         + " lost.";
                    break;
                case 1..60:          /* Less than 1 minute remains  */
                    return "The mixture has started to eat through the"
                         + " crystal which holds it, so stale it has"
                         + " begun to expire. Use it immediately, or"
                         + " not at all!";
                    break;
                default:
                    set_alarm(0.0, 0.0, expire_potion);
                    return "The potion expires as you watch!";
                    break;
            }
            break;
        case "time":
            return TIME2STR(time_left, 4);
            break;
        default:
            break;
    }

    return 0;
} /* query_expiration */


/*
 * Function name:        expire_potion
 * Description  :        The potion has gone bad, so we destroy it
 */
public void
expire_potion()
{
    object  audience = environment(this_object());
    string  expire_msg = "Its color faded almost entirely, the "
                       + short() + " dissolves the base of"
                       + " the vial which holds it, which shatters,"
                       + " sending the mixture to the ground where"
                       + " it evaporates with a nasty hiss.\n";

    if (living(audience))
    {
        audience->catch_tell(expire_msg);
    }
    else
    {
        tell_room(audience, expire_msg);
    }

    remove_object();
} /* expire_potion */


/*
 * Function name:        query_player_knowledge
 * Description  :        Determine whether or not the player has
 *                       sufficient knowledge to recognize various
 *                       things about this potion.
 * Arguments    :        object who - the player
 * Returns      :        1 - sufficient knowledge to recognize things
 *                       0 - insufficient knowledge
 */
public int
query_player_knowledge(object who)
{
    switch(calling_function())
    {
        case "potion_long":
            return (who->query_skill(SS_ALCHEMY) >= SKILL_NEEDED_FULL);
            break;
        case "potion_smell":
        case "potion_taste":
            return (who->query_skill(SS_ALCHEMY) >= SKILL_NEEDED_PARTIAL);
            break;
        default:
            return 0;
            break;
    }

    return 0;
} /* query_player_knowledge */


/*
 * Function name:        potion_long
 * Description  :        describe the potion, based on player
 *                       knowledge
 * Returns      :        string - the correct description 
 */
public string
potion_long()
{
    return ((query_player_knowledge(this_player()))
             ? Id_Long : Unid_Long);
} /* potion_long */


/*
 * Function name:        potion_smell
 * Description  :        describe the potion, based on player
 *                       knowledge
 * Arguments    :        object who - the player
 * Returns      :        string - the correct description 
 */
public string
potion_smell(object who)
{
    string r_txt = QCTNAME(who) + " sniffs " + LANG_ADDART(short())
                 + " carefully";
    string s_txt = ((query_player_knowledge(who))
                     ? Id_Smell : Unid_Smell) + " ";

    if (who->query_skill(SS_ALCHEMY) >= SKILL_NEEDED_FULL)
    {
        s_txt += query_expiration("desc");
        r_txt += ", and nods to " + who->query_objective() + "self.";
    }
    else
    {
        r_txt += ", pauses, and shrugs.";
    }

    tell_room(environment(who), r_txt + "\n", who);

    return s_txt;
} /* potion_smell */


/*
 * Function name:        potion_taste
 * Description  :        describe the potion, based on player
 *                       knowledge
 * Arguments    :        object who - the player
 * Returns      :        string - the correct description 
 */
public string
potion_taste(object who)
{
    tell_room(environment(who), QCTNAME(who) + " carefully tastes "
      + LANG_ADDART(short()) + ".\n", who);

    return ((query_player_knowledge(who)) ? Id_Taste : Unid_Taste);
} /* potion_taste */


/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
    ::init();

    add_action(potion_acts, "quaff");
    add_action(potion_acts, "smell");
    add_action(potion_acts, "taste");
    add_action(potion_acts, "sniff");
} /* init */


/*
 * Function name: stat_object
 * Description:   Called when wizard stats the object
 * Returns:       A string describing the object.
 */
public string
stat_object()
{
    mixed   a_info;
    string  desc = ::stat_object();

    desc += "==============[Specific Potion Stat Info]===============\n"
         +  "Resistance: " + Res_Type + "\n"
         +  "Level:      " + Potion_Lvl + "\n"
         +  "Expires:    " + CONVTIME(P_Time - time()) + "\n"
         +  "========================================================\n";

    return desc;
} /* stat_object */


/*
 * Function name:        get_lost
 * Description  :        remove the potion
 */
public void
get_lost()
{
    set_alarm(0.0, 0.0, remove_object);
} /* get_lost */