/*
 *  /d/Faerun/guilds/halflings/halfling_pie.c
 *
 *  This is the special guild pie item for the Halflings. They have to
 *  bake it in their guild, using real ingredients. It can be used for
 *  a fun special that has a 1 hour cooldown and blinds their opponent.
 *  It can also, of course!, be eaten.
 *
 *  Created March 2016, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "/d/Faerun/defs.h"
#include "../halflings.h"

inherit "/std/food";

#include <cmdparse.h>
#include <composite.h>
#include <macros.h>
#include <stdproperties.h>
#include <time.h>
#include "../halflings.h"


/* Global Variables */
public string        Pie_Type = "delicious";
public string        Baker = "unknown";


/* Prototypes */
public void        create_food();
public void        setup_pie();
public string      exa_pie();
public void        fill_belly(object who);
public void        init_arg(string str);
public string      query_auto_load();
public string      query_recover();
public void        special_effect(int amount);
// public int         hurl_pie(string arg);
public void        init();
public mixed       check_get_pie();

public void        set_pie_type(string s) { Pie_Type = s; }
public string      query_pie_type()    { return Pie_Type; }
public void        set_baker(string s)       { Baker = s; }
public string      query_baker()          { return Baker; }


/*
 * Function name:        create_food
 * Description  :        the constructor for the object
 */
public void
create_food()
{
    set_name("pie");

    set_long("@@exa_pie@@");

    set_amount(500);

    add_prop(OBJ_I_WEIGHT, 4536);  /* 10 pounds - a halfling pie!! */
    add_prop(OBJ_I_VOLUME, 2000);  /* roughly half a gallon */
    add_prop(OBJ_M_NO_GET, "@@check_get_pie@@");

    set_alarm(0.0, 0.0, setup_pie);

    setuid();
    seteuid(getuid());
} /* create_food */


/*
 * Function name:        setup_pie
 * Description  :        do some setup work on the pie to give
 *                       it the proper descriptions once the pie_type
 *                       has been established.
 */
public void
setup_pie()
{
    string *spaced_words = explode(Pie_Type, " ");

    set_short(Pie_Type + " pie");

    foreach(string this_word : spaced_words)
    {
        if (IN_ARRAY("-", explode(this_word, "")))
        {
            add_adj(implode(explode(this_word, "-"), ""));
            add_adj(this_word);
        }
    }

    add_adj(explode(implode(explode(Pie_Type, "-"), " "), " "));

    /* They need to heap according to type. */
    add_prop(HEAP_S_UNIQUE_ID, Pie_Type);

    return;
} /* setup_pie */


/*
 * Function name:        exa_pie
 * Description  :        provide a situation-dependant description of
 *                       the pie
 * Returns      :        string - the description
 */
public string
exa_pie()
{
    string  pie_txt = "Just look at this delicious pie! The aroma of"
      + " baked " + Pie_Type + " rises from it, filling the area with"
      + " comfort and the invitation to tuck in and eat it up. ";

    if (Baker == this_player()->query_real_name())
    {
        pie_txt += "You can remember baking this one yourself, so"
          + " you are quite sure it will be extra good. ";
    }

    if (IS_MEMBER(this_player()))
    {
        pie_txt += "Of course, in an emergency you could probably"
          + " <hhurl> this pie at someone. But that would be a terrible"
          + " loss!";
    }

    return pie_txt + "\n";
} /* exa_pie */


/*
 * Function name:        fill_belly
 * Description  :        Eating an entire pie will completely fill
 *                       the player up
 * Arguments    :        object who - the player to fill
 */
public void
fill_belly(object who)
{
    int     how_full = who->query_stuffed(),
            how_fat = who->eat_max(),
            feast_size = how_fat - how_full,
            i;

    /* Fill 'em up!
     * There appears to be a maximum limit on eat_food() set to approximately
     * who->eat_max() / 5. So ... we'll do this in 5 chunks of
     * just that portion, with the last a bit smaller.
     */
    for (i = 0; i < 5; i++)
    {
        if (i > 4)
        {
            who->eat_food(feast_size - 5);
        }
        else
        {
            who->eat_food(how_fat / 5);
        }
    }

    who->command("$burp");

    return;
} /* fill_belly */


/*
 * Function name: init_arg
 * Description  : This function is called when the pie recovers.
 * Arguments    : string str - the recover argument.
 */
public void
init_arg(string str)
{
    string  p_type,
            baker,
            foobar;

    init_recover(str);
    if (sscanf(str, "%spie#%s#%s#%s", foobar, p_type, baker, foobar) == 4)
    {
        set_pie_type(p_type);
        set_baker(baker);
        setup_pie();
    }
} /* init_arg */


/*
 * Function name: query_auto_load
 * Description  : We let the players hoard these over logins. Upon recovery
 *                we keep track of the type of pie.
 */
public string
query_auto_load()
{
    return ::query_recover() + "pie#" + Pie_Type + "#" + Baker + "#";
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
} /* query_recover */


/*
 * Function name:        special_effect
 * Description  :        do some things when this gets eaten
 * Arguments    :        int amount - number of pies
 */
public void
special_effect(int amount)
{
    write("You sit down and begin munching your way through the"
      + " pie, savouring all of the delicious juices and the fresh-baked"
      + " crust. Ooof! That just about filled you up!\n");

    say(QCTNAME(this_player()) + " sits down and begins munching "
      + this_player()->query_possessive() + " way through a massive"
      + " pie.\n");

    fill_belly(this_player());

    return;
} /* consume_text */


/*
 * Function name:        hurl_pie
 * Description  :        allow the player (if a halfling) to use the
 *                       pie for a bit of self defense. This creates
 *                       an extended period of mourning (naturally)
 *                       in which they will not be able to do so again
 *                       for quite a while.
 * Arguments    :        string arg - what was typed after the verb
 * Returns      :        int 1 - success, 0 - failure
 */

/* Pies can't be hurled
public int
hurl_pie(string arg)
{
    string  time_txt = TIME2FORMAT(time(), "d mmm yyyy");
    object  enemy = this_player()->query_attack();
    object *pies;
    object  pie;

    if (!IS_MEMBER(this_player()))
    {
        return 0; // This ability is ONLY for the halfling guild 
    }

    notify_fail("Hurl the pie?? Oh dear ... only in emergencies.\n");
    if (!strlen(arg))
    {
        return 0;
    }

    pies = PARSE_THIS(arg, "[a] [an] [the] %i");
    switch(sizeof(pies))
    {
    case 0:
        return 0;
    case 1:
        pie = pies[0];
        break;
    default:
        notify_fail("You can only hurl one at a time!\n");
        return 0;
    }

    if (pie != this_object())
    {
        notify_fail("You could hurl one of your pies if you were really"
          + " desperate, but not this " + pie->short() + "!\n");
        return 0;
    }

    if (!objectp(enemy) ||
        environment(enemy) != environment(this_player()))
    {
        notify_fail("Hurling pies is unthinkable except in dire"
          + " circumstances!!\n");
        return 0;
    }
// Time check. disable for testing purposes
//    if (PIE_MASTER->get_info(this_player(), "Last_Hurl") ==
//        time_txt)

    {
        write("No, you fool! You still can't believe you hurled that"
          + " last pie into oblivion! Oh, the waste! Oh, the lost"
          + " deliciousness!! More than one in a day and you'd lose"
          + " the will to go on!\n");
        return 1;
    }

    PIE_MASTER->set_info(this_player(), "Last_Hurl", time_txt);

    write("Wailing in desperation, you hurl the perfectly good "
      + Pie_Type + " pie at " + enemy->query_the_name(this_player())
      + ", where it bursts in fruity glory all over "
      + enemy->query_possessive() + " face!\n");
    tell_room(environment(this_player()),
        QCTNAME(this_player()) + " wails in"
      + " desperation, hurling a massive " + Pie_Type + " pie into the"
      + " oncoming face of " + QTNAME(enemy) + " where it splatters"
      + " in a massive burst of blinding fruit!\n",
        ({ this_player(), enemy}) );
    enemy->catch_tell(this_player()->query_The_name(enemy)
      + " wails in desperation as you close in for the kill,"
      + " hurling a massive " + Pie_Type + " pie right into your face!"
      + " The pie explodes in a cascade of fruit, crust, and"
      + " juices! AAAAArrrgh!!\n");

    
//    FINWE: go ahead and put your blind code here.


    enemy->clone_object("/d/Gondor/common/guild/obj/stun_ob");
    enemy->move(TP, 1);
//    remove_object();
    return 1;
} // hurl_pie 
*/

/*
 * Function name:        init
 * Description  :        add some actions to the player
 */
public void
init()
{
//    add_action(hurl_pie, "hhurl");

    ::init();
} /* add_action */


/*
 * Function name:        check_get_pie
 * Description  :        We need to check to see if a player is
 *                       allowed to get this pie. If it is in the
 *                       pie case in the kitchen, then we only allow
 *                       the person who baked it to take it.
 * Returns               string - the fail message
 *                       int 0 - if we allow it
 */
public mixed
check_get_pie()
{
    if (environment(this_object())->id(PIE_CASE) &&
        this_player()->query_real_name() != Baker)
    {
        return "Stealing a pie that you did not bake from a"
          + " kitchen is among the most heinous of crimes in"
          + " halfling culture. Even the the most loathesome and"
          + " heartless wretch would rather die than stoop"
          + " to such acts.\n";
    }

    return 0;
} /* get_pie_check */