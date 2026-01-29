/*
 * /d/Gondor/minas/npc/painterq.c
 *
 * Armour painter for Minas Tirith.
 *
 * Coded by Gwyneth on August 28, 2000
 */

inherit "/d/Gondor/common/dunedain/npc/npc_dunadan";

#include <files.h>
#include <macros.h>
#include <math.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/common/dunedain/lib/dunedain_defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/rooms/paint_gon.h"

/* Numbers to keep allow name-to-random herbs given */
#define GIDENT 48329172
#define GRANGE 18
#define BIDENT 58302943
#define BRANGE 4
#define SIDENT 66219732
#define SRANGE 4

/* Index positions for the mapping values that keep track
   of who brought which herbs. 
*/
#define BROWN  0
#define GREEN  1
#define SILVER 2
#define DUST   3

/* Global variables */
static int gMarker;
static string gPaint;
public mapping ing_map = ([]);

/* Prototypes */
public int paint_tells(object arm, object from);

void
cleanup_miriel()
{
    int i, size;
    string *names;

    names = m_indexes(ing_map);

    if (!sizeof(names))
        return;

    for (i = sizeof(names) - 1; i >= 0; i--)
    {
        if (!ing_map[names[i]][0] && !ing_map[names[i]][1] &&
          !ing_map[names[i]][2] && !ing_map[names[i]][3])  
            ing_map = m_delete(ing_map, names[i]);
    }

    save_object(MASTER);
}

public void
create_dunadan()
{
    set_name("miriel");
    add_name("painter");
    set_living_name("miriel");
    set_dunedain_house("Hallacar");
    set_race_name("human");
    set_title("Armour Designer of Minas Tirith");
    set_adj(({"skinny", "dark-haired"}));
    set_long("This woman must be in the employ of the Armourer. " +
        "A curl of hair hangs down rebelliously in front of her " +
        "eyes, and her skin is a pale ivory from infrequent exposure to " +
        "the sun. Perhaps she is too dedicated to her work of painting " +
        "armours for Calmacil to enjoy the outdoors. Her hands look " +
        "very skillful and are covered with paint splashes. She notices " +
        "your gaze and smiles, lighting up the room. She waves her hand " +
        "to the sign and returns to her work.\n");
    set_gender(G_FEMALE);
    set_alignment(250);
    default_config_npc(50 + random(10));

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    set_skill(SS_WEP_CLUB, (55 + random(10)));

    set_chat_time(15);

    add_chat("My work is considered the best in all of Gondor.");
    add_chat("I can paint armours with the emblem of Gondor.");
    add_chat("Painting is delicate work.");
    add_chat("Read the sign if you would like me to paint a piece " +
        "of armour.");

    add_ask(({"paint", "armour", "paint armour"}), "say I can paint " +
        "a piece of armour for you if you like. " +
        "Read the sign for more information.", 1);
    add_ask(({"emblem", "gondor"}), "say The white tree with seven stars " +
        "above is a symbol of hope for the people.", 1);
    add_ask("hope", "say Times will get better! I'm sure of it!", 1);
    add_ask(({"additive", "additives", "paint additives"}),
        "say I am always short on paint additives. It's a pity, since " +
        "I can make such beautiful colours! Maybe you could fetch some " +
        "for me.", 1);
    add_ask(({ "fetch", "colours", "colour", "help", "task","ingredients" }), 
        "@@give_colours");
    add_ask(({"silver", "silver paint", "silver additive"}), "@@silver");
    add_ask(({"brown", "brown paint", "brown additive"}), "@@brown");
    add_ask(({"green", "green paint", "green additive"}), "@@green");
    add_ask(({"dust", "silver dust", "silverdust"}), "say You might ask " +
        "the jeweller about that. He would know better than I.", 1);
    add_ask("jeweller", "say He's on Pelargir Street in the fourth " +
        "circle.", 1);
    add_ask(({"helm", "citizen", "influential citizen"}), "say I'm not " +
        "in the habit of releasing my customers' names. Just get " +
        "me the additives, and I'll make it worth your while!", 1);
    set_default_answer("@@default_ans");
    set_equipment(MINAS_DIR + "obj/ltunic");
    restore_object(MASTER);
    cleanup_miriel();
}

/*
 * Function name: default_ans
 * Description  : Gives the default answer to asked questions
 * Returns      : ""
 */
string 
default_ans()
{
    switch(random(5))
    {
    case 0:
        command("emote appears to be daydreaming for a moment.");
        break;
    case 1:
        command("say I'm sorry, I don't understand what you're asking.");
        break;
    case 2:
        command("emote jumps at the sound of a loud noise in the " +
            "adjacent room, and misses your question.");
        break;
    case 3:
        command("emote furrows her brow.");
        command("say Maybe Hunthor would know.");
        break;
    case 4:
        command("emote shrugs.");
        command("say I haven't a clue.");
        break;
    }
    return "";
}

/*
 * Function name: brown_herb
 * Description  : Returns the name-to-random specific herb for
 *                the player (object player) that they need
 *                to find and return to be able to paint a
 *                piece of armour brown.
 */
public string
brown_herb(object player)
{
    return (BROWN_ING[NAME_TO_RANDOM(player->query_real_name(),
      BIDENT, BRANGE)]);
}

/*
 * Function name: green_herb
 * Description  : Returns the name-to-random specific herb for
 *                the player (object player) that they need
 *                to find and return to be able to paint a
 *                piece of armour green.
 */
public string
green_herb(object player)
{
    return (GREEN_ING[NAME_TO_RANDOM(player->query_real_name(),
      GIDENT, GRANGE)]);
}

/*
 * Function name: silver_herb
 * Description  : Returns the name-to-random specific herb for
 *                the player (object player) that they need
 *                to find and return to be able to paint a
 *                piece of armour silver.
 */
public string
silver_herb(object player)
{
    return (SILVER_ING[NAME_TO_RANDOM(player->query_real_name(),
      SIDENT, SRANGE)]);
}

/*
 * Function name: brown
 * Description  : Notify the player that asks what ingredient they
 *                need for brown paint.
 */
public string
brown()
{
    command("whisper to " + OB_NAME(this_player()) + " I can mix brown paint " +
        "if you fetch me " + LANG_ART(brown_herb(this_player())) + " " +
        brown_herb(this_player()) + ".");
    return "";
}

/*
 * Function name: green
 * Description  : Notify the player that asks what ingredient they
 *                need for green paint.
 */
public string
green()
{
    command("whisper to " + OB_NAME(this_player()) + " I can mix green paint " +
        "if you fetch me " + LANG_ART(green_herb(this_player())) + " " +
        green_herb(this_player()) + ".");
    return "";
}

/*
 * Function name: silver
 * Description  : Notify the player that asks what ingredients they
 *                need for silver paint.
 */
public string
silver()
{
    command("whisper to " + OB_NAME(this_player()) + " I can mix silver " +
        "paint if you fetch me " + LANG_ART(silver_herb(this_player())) + " " +
        silver_herb(this_player()) + " and a bag of silver dust.");
    return "";
}

/* Function name: give_colours
 * Description  : Give the ingredients needed for each colour, and
 *                let the player know about a minor quest.
 */
public string
give_colours()
{
    string gherb = green_herb(this_player()), 
           bherb = brown_herb(this_player()),
           sherb = silver_herb(this_player());

    if (!this_player()->test_bit("gondor", PAINT_GROUP, PAINT_BIT))
    {
        command("whisper to " + OB_NAME(this_player()) + " The war has made " +
            "coloured paint rather scarce in supply. Unfortunately, " +
            "one of the more influential citizens of Minas Tirith wants his " +
            "helm painted silver. If you could find a " + sherb +
            " and a bag of silver dust for me, I could make silver " +
            "paint. I would be most " +
            "grateful! I also might have some left over for you.");
        command("wink " + OB_NAME(this_player()));
        command("whisper to " + OB_NAME(this_player()) + " I can also make " +
            "brown paint with " + bherb + " or green paint with " + gherb +
            ".");
	START_QUEST(this_player(), "SILVER PAINT QUEST");
    }
    else
    {
        command("whisper to " + OB_NAME(this_player()) + " I can make green " +
            "paint with " + gherb + ", brown paint with " + bherb + " or " +
            "silver paint with " + sherb + " and a bag of silver dust.");
    }
    return "";
}

/*
 * Function name: valid_herb
 * Description  : Tests to see if an herb is one of the ingredients
 *                needed. Returns the position of the herb in the
 *                array: brown - 0, green - 1, silver - 2.
*/
public int
valid_herb(string herb, object player)
{
    string *herbs = ({});

    herbs += ({ brown_herb(player) });
    herbs += ({ green_herb(player) });
    herbs += ({ silver_herb(player) });

    return (member_array(herb, herbs));
}

public int
allow_paint(string who, string colour)
{
    who = lower_case(who);
    colour = lower_case(colour);

    if (member_array(who, m_indexes(ing_map)) == -1)
    {
        return 0;
    }

    switch(colour)
    {
    case "brown":
        if (ing_map[who][0] > 0)
            return 1;
        break;
    case "green":
        if (ing_map[who][1] > 0)
            return 1;
        break;
    case "silver":
        if (ing_map[who][2] > 0 &&
          ing_map[who][3] > 0)
            return 1;
        break;
    }
    return 0;
}

/*
 * Function name: alter_map
 * Description  : Increment or decrement the map that keeps track
 *                of names of players and the number of ingredients
 *                they have collected. Saves the results.
 * Arguments    : name - name of the player; col_index - the colour
 *                index: brown - 0, green - 1, silver - 2, dust - 3;
 *                change - the amount to increment or decrement the
 *                colour index.
 */
public void
alter_map(string name, int col_index, int change)
{
    int *col_arr = ({0,0,0,0});

    if (member_array(name, m_indexes(ing_map)) == -1)
    {
        col_arr[col_index] = 1;
    }
    else
    {
        col_arr = ing_map[name];
        col_arr[col_index] = col_arr[col_index] + change;
    }
    ing_map = m_delete(ing_map, name);
    ing_map += ([name : col_arr]);
    save_object(MASTER);
}

public string
query_colour()
{
    return gPaint;
}

public void
set_paint(string colour)
{
    gPaint = colour;
}

public string
query_pair(object ob, int pl)
{
    string sh_desc = ob->short();

    if (wildmatch("*pair*", sh_desc))
    {
        if (pl)
        {
            return "pairs of ";
        }
        else
        {
            return "pair of ";
        }
    }
    return "";
}

public string
query_true_name(object ob, int pl)
{
    int i, sz;
    string *names, sh_desc, *descs, *temp;

    /* Find the names and short desc for the armour (non-plural forms) */
    if (!pl)
    {
        names = ob->query_names();
        sh_desc = ob->short();
    }
    /* Find the plural names and plural short for the armour if
       the pshort hasn't been set. */
    else if (!ob->plural_short())
    {
        names = ob->query_pnames();
        sh_desc = (ob->short() + "s");
    }
    /* Find the plural names and plural short for the armour if
       the pshort has been set. */
    else
    {
        names = ob->query_pnames();
        sh_desc = ob->plural_short();
    }

    if (wildmatch("*pairs*", sh_desc))
    {
        names = ob->query_names();
        sh_desc = ob->short();
    }

    /* Remove any names with spaces in them for the calculation,
       such as "pair of boots" in order to get a nicer
       looking output. */
    for (i = sizeof(names) - 1; i > -1; i--)
    {
        if (wildmatch("* *", names[i]))
        {
            names -= ({ names[i] });
        }
    }
    temp = names;

    /* Remove the name of armour(s) for the calculation, as it's not
       our first choice for a description. We put it back
       in the end in case armour is the only name. */
    if (member_array("armour", names) >= 0)
    {
        names -= ({ "armour" });
    }

    if (member_array("armours", names) >= 0)
    {
        names -= ({ "armours" });
    }

    /* Make an array of each word in the short desc. */
    descs = explode(sh_desc, " ");

    /* If a name is in the short desc, choose this for the
       name to return as in the case of "blue dragonscale armour" */
    for (i = 0, sz = sizeof(names); i < sz; i++)
    {
        if (member_array(names[i], descs) >= 0)
        {
            return names[i];
        }
    }

    /* We don't want the object number to be given if it
       comes down to that. */
    if (temp[0] == OB_NUM(ob))
    {
        if (pl)
        {
            return "armours";
        }
        else
        {
            return "armour";
        }
    }

    return temp[0];
}

public int
add_paint(object person, object arm, int colour, int repaint)
{
    int mon;
    string *adjs = arm->query_adjs();
    string desc, ldesc, sdesc, pdesc, *new_prop;

    if (gMarker)
    {
        write("emote looks rather busy. It appears that " +
            "you must wait your turn.\n");
        return 1;

    }

    gPaint = COLOUR[colour];

    if (gPaint != "white")
    {
        if (colour != SILVER)
        {
            alter_map(person->query_real_name(), colour, -1);
        }
        else
        {
            alter_map(person->query_real_name(), SILVER, -1);
            alter_map(person->query_real_name(), DUST, -1);
        }
    }
    arm->move(this_object(), 1);

    mon = ((arm->query_prop(OBJ_I_VOLUME) * 1728) / 2000);

    /* If the armour has never been painted, find the long and short. */
    if (!repaint)
    {
        desc = arm->short();
        ldesc = arm->query_long();
        sdesc = arm->query_short();
        pdesc = arm->plural_short();
        arm->set_long( LONG(arm) );
        log_file("painted", ctime(time()) + " " + this_player()->query_name() +
            " " + file_name(arm) +
            " " + COLOUR[colour] + "(" + SHORT(arm) + "/" +
            PSHORT(arm) + ") for " + mon + " copper.\n");
    }
    /* If the armour has been painted, find the original short. */
    else
    {
        desc = arm->query_prop(OBJ_S_PAINTED)[1];
        arm->set_long( RLONG(arm) );
        arm->remove_name("_gondor_painted");
        log_file("painted", ctime(time()) + " " +
            this_player()->query_name() + " " + file_name(arm) +
            " from " + (arm->query_prop(OBJ_S_PAINTED))[2] +
            "to " + COLOUR[colour] + "(" + SHORT(arm) + "/" +
            PSHORT(arm) + ") for " + mon + " copper.\n");
    }

    set_alarm(1.3, 0.0, &person->catch_tell("You request to have your " +
        arm->short() + (repaint ? " repainted " : " painted ") + 
        COLOUR[colour] + " with the emblem of " + PLACE + ".\n"));

    paint_tells(arm, person);

    arm->add_prop(OBJ_S_PAINTED, ({ PLACE, desc, COLOUR[colour] }));
    arm->add_prop(OBJ_S_PAINT_INFO, ({ ldesc, sdesc, pdesc, adjs }));
    arm->remove_adj(adjs);
    arm->add_adj(ADJS);
    arm->add_adj("unworn");
    arm->set_short( SHORT(arm) );
    arm->set_pshort( PSHORT(arm) );
    arm->add_name("_gondor_painted");
    return 1;
}

/*
 * Function name: reward_silver_quest
 * Description  : Rewards the silver quest, sets the proper bits,
 *                gives messages.
 * Arguments    : object who - the rewarded player
 */
private void
reward_silver_quest(object who)
{
    if (who->test_bit("gondor", PAINT_GROUP, PAINT_BIT))
    {
        write_file("/d/Gondor/log/bugs", 
            (extract(ctime(time()), 4, 9) + " " + 
            capitalize(who->query_real_name()) + " triggered a bug in " +
            "the quest rewards.\n"));
        write("Reward failed.\n");
        return;
    }
    else
    {
        setuid();
        seteuid(getuid());
        who->add_exp_quest(PAINT_REWARD);
        who->set_bit(PAINT_GROUP, PAINT_BIT);
        LOG_QUEST(who, PAINT_REWARD, "SILVER PAINT QUEST");
        who->catch_tell("You feel a little more experienced.\n");
        return;
    }
}

/*
 * Function name: enter_inv
 * Description  : Called whenever something enters the inventory
 *                of this object. Calls the original enter_inv,
 *                then does some checking to see if the item is
 *                a valid ingredient or a piece of armour.
 * Arguments    : object ob - the item entering the inventory
 *                object from - where the item came from
*/
public void
enter_inv(object ob, object from)
{
    int num, *col_arr = ({0, 0, 0, 0});
    string colour, name;

    ::enter_inv(ob, from);

    name = from->query_real_name();

    if (IS_HERB_OBJECT(ob))
    {
        num = valid_herb(ob->query_herb_name(), from);
        if (num >= 0)
        {
            alter_map(name, num, 1);
        }
        else
        {
            set_alarm(0.8, 0.0, &command("say That's not " +
                "an herb I wanted you to get for me."));
            set_alarm(1.0, 0.0, &command("put " + OB_NAME(ob)));
            return;
        }

        /* If it's the silver herb ingredient, dust has been
           received, and the quest hasn't been completed. */
        if (num == 2 &&
          ing_map[name][3] > 0 &&
          !from->test_bit("gondor", PAINT_GROUP, PAINT_BIT))
        {
            setuid();
            seteuid(getuid());
            set_alarm(1.0, 0.0, &command("say You brought the " +
                "ingredients I need to make silver paint! Now I " +
                "can paint that helm. I will also paint a piece " +
                "of armour silver for you when you wish.")); 
            reward_silver_quest(from); 
        }
        else
        {
            set_alarm(1.0, 0.0, &command("emote sets the " +
                ob->short() + " aside and smiles."));
        }
        set_alarm(1.6,0.0,&ob->remove_object());

        return;
    }

    if (ob->id("_gondor_silver_dust"))
    {
        alter_map(name, 3, 1);
        if (ing_map[name][2] > 0 &&
          !from->test_bit("gondor", PAINT_GROUP, PAINT_BIT))
        {
            setuid();
            seteuid(getuid());
            set_alarm(1.0, 0.0, &command("say You brought the " +
                "ingredients I need to make silver paint! Now I " +
                "can paint that helm. I will also paint a piece " +
                "of armour silver for you when you wish."));
            reward_silver_quest(from);
        }
        else
        {
            set_alarm(1.0, 0.0, &command("emote sets the " +
                ob->short() + " aside and smiles."));
        }

        set_alarm(1.6,0.0, &ob->remove_object());
        return;
    }
    if (!IS_ARMOUR_OBJECT(ob))
    {
        set_alarm(1.5, 0.0, &command("emote doesn't look interested."));
        set_alarm(2.5, 0.0, &command("put " + OB_NAME(ob)));
        return;
    }
    else if (previous_object(-1) != this_object() &&
      objectp(from))
    {
        set_alarm(1.5, 0.0, &command("say Read the sign for painting " +
            "instructions."));
        set_alarm(2.5, 0.0, &command("put " + OB_NAME(ob)));
    }
    return;
}

public void
set_marker(int i)
{
    gMarker = i;
}

public int
query_marker()
{
    return gMarker;
}

public int
solv_tells(object arm, object from)
{
    string name = arm->short();

    if (gMarker)
    {
        notify_fail("emote looks rather " + 
            "busy. It appears that you must wait your turn.\n");
        return 0;
    }

    gMarker = 1;
    set_alarm(3.0, 0.0, &command("emote looks over the " + name +
        " carefully."));
    set_alarm(6.0, 0.0, &command("smile confidently"));
    set_alarm(9.0, 0.0, &command("emote picks up a bottle of " +
        "paint solvent."));
    set_alarm(11.0, 0.0, &command("emote saturates a cloth with " +
        "the solvent and starts to rub the paint off of the " +
        name + "."));
    set_alarm(15.0, 0.0, &tell_room(environment(TO), "The paint " +
        "dissolves like magic as the saturated cloth moves over " +
        "each part of the armour.\n"));
    set_alarm(18.0, 0.0, &command("emote rinses off the cloth."));
    set_alarm(20.0, 0.0, &command("emote saturates the cloth " +
        "with more solvent, and touches up some missed spots."));
    set_alarm(23.0, 0.0, &command("emote presents her work."));
    set_alarm(23.5, 0.0, &command("show full " + OB_NAME(arm)));
    set_alarm(25.0, 0.0, &command("give " + OB_NAME(arm) + " to " +
        OB_NAME(from)));
    set_alarm(25.1, 0.0, &command("put " + OB_NAME(arm)));
    set_alarm(25.1, 0.0, &command("say Would you like me to paint it " +
        "another colour now? I can paint it brown, silver, green, and " +
        "of course white. You might need to get an additive for my " +
        "paint."));
    set_alarm(25.2, 0.0, &set_marker(0));
    return 1;
}

public int
paint_tells(object arm, object from)
{
    string name = arm->short();

    if (gMarker)
    {
        notify_fail("emote looks rather " +
            "busy. It appears that you must wait your turn.\n");
        return 0;
    }

    set_marker(1);
    set_alarm(3.0, 0.0, &command("emote looks over the " + name +
        " carefully."));
    set_alarm(6.0, 0.0, &command("smile confidently"));
    set_alarm(9.0, 0.0, &command("emote picks up a thick brush and " +
        "dips it in a bucket of " + 
        query_colour() + " paint."));
    set_alarm(11.0, 0.0, &command("emote sweeps the brush across the " +
        name + " with confident strokes."));
    set_alarm(15.0, 0.0, &command("emote rinses off the wide brush and " +
        "picks up a somewhat smaller brush."));
    set_alarm(18.0, 0.0, &command("emote dips the brush in " +
        (query_colour() == "silver" ? "green":"silver") + 
        " paint and draws a circle on the " + arm->query_name() + "."));
    set_alarm(21.5, 0.0, &command("emote replaces the brush and picks " +
        "up a very fine one."));
    set_alarm(24.5, 0.0, &command("emote dips the brush into the " +
        "paint and bends over the " + arm->query_name() + ", blocking " +
        "your view. Her face takes on a very intent look as she works."));
    set_alarm(31.0, 0.0, &command("emote straightens and presents " +
        "her work."));
    set_alarm(31.5, 0.0, &command("show full " + OB_NAME(arm)));
    set_alarm(33.0, 0.0, &command("give " + OB_NAME(arm) + " to " +
        OB_NAME(from)));
    set_alarm(33.1, 0.0, &command("put " + OB_NAME(arm)));
    set_alarm(33.2, 0.0, &command("say I can paint armours " +
        "brown, silver, green, and of course white. I might ask " +
        "you to get me an additive for my paint for some."));
    set_alarm(33.2, 0.0, &set_marker(0));
    return 1;
}

