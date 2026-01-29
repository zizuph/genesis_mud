/*
 * /d/Gondor/morgul/npc/paintermq.c
 *
 * Armour painter for Minas Morgul.
 *
 * Coded by Gwyneth on August 28, 2000
 * Complete revision on November 08, 2000 by Gwyneth to add
 * alternate colouring capabilities and a quest.
 */

inherit "/std/monster";

#include <files.h>
#include <macros.h>
#include <math.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/morgul/cellar/paint_mm.h"

/* Numbers to keep allow name-to-random herbs given */
#define RIDENT 78324172
#define RRANGE 7
#define GIDENT 96229832
#define GRANGE 3

/* Index positions for the mapping values that keep track
   of who brought which herbs. 
*/
#define RED    0
#define GOLD   1
#define DUST   2

/* Global variables */
static int gMarker;
static string gPaint;
public mapping ing_map = ([]);

/* Prototypes */
public int paint_tells(object arm, object from);

void
cleanup_gruzgh()
{
    int i, size;
    string *names;

    names = m_indexes(ing_map);

    if (!sizeof(names))
        return;

    for (i = sizeof(names) - 1; i >= 0; i--)
    {
        if (!ing_map[names[i]][0] && !ing_map[names[i]][1] &&
          !ing_map[names[i]][2])
            ing_map = m_delete(ing_map, names[i]);
    }

    save_object(MASTER);
}

public void
create_monster()
{
    set_name("gruzgh");
    add_name("painter");
    set_living_name("gruzgh");
    set_race_name("human");
    set_title("Armour Designer of Minas Morgul");
    set_adj(({"lanky", "nervous"}));
    set_long("This man must be in the employ of the Armourer. Dark " +
        "circles lie heavy under his eyes, and he seems to jump at " +
        "the slightest noise. Perhaps he knows that his life depends " +
        "on the perfection of his work. He notices your gaze and " +
        "immediately lowers his eyes, gesturing to a sign.\n");
    set_gender(G_MALE);
    set_alignment(-250);
    default_config_npc(50 + random(10));

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    set_skill(SS_WEP_CLUB, (55 + random(10)));

    set_chat_time(15);

    set_act_time(8);
    add_act("say Painting is the only happiness in my existence.");
    add_act("emote jumps at a sound nearby.");
    add_act("emote 's eyes shift nervously around the room.");
    add_act("emote inspects his work intently for flaws.");
    add_act("twitch");
    add_act("say My work must be perfect!");

    add_ask(({"paint", "armour", "paint armour"}), "say I can paint " +
        "a piece of armour for you if you like. " +
        "Read the sign for more information.", 1);
    add_ask(({"additive", "additives", "paint additives"}),
        "say I am always short on paint additives. It's a pity, since " +
        "my work could be much more masterful with more colours! Maybe " +
        "you could find some for me.", 1);
    add_ask(({ "find", "colours", "colour", "help", "task","ingredients" }), 
        "@@give_colours");
    add_ask(({"gold", "gold paint", "gold additive"}), "@@gold");
    add_ask(({"red", "red paint", "red additive"}), "@@red");
    add_ask(({"dust", "gold dust", "golddust"}), "say I get my " +
        "gold dust from the Pelargir jeweller. You might ask him.", 1);
    add_ask(({"helm", "mage", "influential mage"}), "say I dare " +
        "not say more! Just get " + 
        "me the additives, and I'll make it worth your while!", 1);
    set_default_answer("@@default_ans");
    restore_object(MASTER);
    cleanup_gruzgh();
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
        command("emote appears to be lost in thought for a moment.");
        break;
    case 1:
        command("say I'm sorry, I don't understand what you're asking.");
        break;
    case 2:
        command("emote jumps at the sound of a loud noise in the " +
            "adjacent room, and misses your question.");
        break;
    case 3:
        command("emote furrows his brow.");
        command("say Maybe someone wiser would know.");
        break;
    case 4:
        command("emote shrugs.");
        command("say I haven't a clue.");
        break;
    }
    return "";
}

/*
 * Function name: red_herb 
 * Description  : Returns the name-to-random specific herb for
 *                the player (object player) that they need
 *                to find and return to be able to paint a
 *                piece of armour red.
 */
public string
red_herb(object player)
{
    return (RED_ING[NAME_TO_RANDOM(player->query_real_name(),
      RIDENT, RRANGE)]);
}

/*
 * Function name: gold_herb
 * Description  : Returns the name-to-random specific herb for
 *                the player (object player) that they need
 *                to find and return to be able to paint a
 *                piece of armour gold.
 */
public string
gold_herb(object player)
{
    return (GOLD_ING[NAME_TO_RANDOM(player->query_real_name(),
      GIDENT, GRANGE)]);
}

/*
 * Function name: red
 * Description  : Notify the player that asks what ingredient they
 *                need for red paint.
 */
public string
red()
{
    command("whisper to " + OB_NAME(this_player()) + " I can mix red paint " +
        "if you fetch me " + LANG_ART(red_herb(this_player())) + " " +
        red_herb(this_player()) + ".");
    return "";
}

/*
 * Function name: gold
 * Description  : Notify the player that asks what ingredient they
 *                need for gold paint.
 */
public string
gold()
{
    command("whisper to " + OB_NAME(this_player()) + " I can mix gold paint " +
        "if you fetch me " + LANG_ART(gold_herb(this_player())) + " " +
        gold_herb(this_player()) + ".");
    return "";
}

/* Function name: give_colours
 * Description  : Give the ingredients needed for each colour, and
 *                let the player know about a minor quest.
 */
public string
give_colours()
{
    string rherb = red_herb(this_player()), 
           gherb = gold_herb(this_player());

    if (!this_player()->test_bit("gondor", PAINT_GROUP, PAINT_BIT))
    {
        command("whisper to " + OB_NAME(this_player()) + " The war has made " +
            "coloured paint rather scarce in supply. Unfortunately, " +
            "one of the more influential Mages of Minas Morgul wants his " +
            "helm painted gold. If you could find a " + gherb +
            " and a bag of gold dust for me, I could make gold " +
            "paint. I would be most " +
            "grateful, and I also might have some left over for you.");
        command("wink " + OB_NAME(this_player()));
        command("whisper to " + OB_NAME(this_player()) + " I can also make " +
            "red paint with " + rherb + ".");
        START_QUEST(this_player(), "GOLD PAINT QUEST");
    }
    else
    {
        command("whisper to " + OB_NAME(this_player()) + " I can make red " +
            "paint with " + rherb + " and gold paint with " + gherb +
            " and a bag of gold dust.");
    }
    return "";
}

/*
 * Function name: valid_herb
 * Description  : Tests to see if an herb is one of the ingredients
 *                needed. Returns the position of the herb in the
 *                array: red - 0, gold - 1.
*/
public int
valid_herb(string herb, object player)
{
    string *herbs = ({});

    herbs += ({ red_herb(player) });
    herbs += ({ gold_herb(player) });

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
    case "red":
        if (ing_map[who][0] > 0)
            return 1;
        break;
    case "gold":
        if (ing_map[who][1] > 0 &&
          ing_map[who][2] > 0)
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
 *                index: red - 0, gold - 1, dust - 2;
 *                change - the amount to increment or decrement the
 *                colour index.
 */
public void
alter_map(string name, int col_index, int change)
{
    int *col_arr = ({0,0,0});

    if (member_array(name, m_indexes(ing_map)) == -1)
    {
        col_arr[col_index] = 1;
    }
    else
    {
        col_arr = ing_map[name];
        col_arr[col_index] = col_arr[col_index] + change;
    }
    m_delete(ing_map, name);
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

    if (gPaint != "black")
    {
        if (colour != GOLD)
        {
            alter_map(person->query_real_name(), colour, -1);
        }
        else
        {
            alter_map(person->query_real_name(), GOLD, -1);
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
 * Function name: reward_gold_quest
 * Description  : Rewards the gold quest, sets the proper bits,
 *                gives messages.
 * Arguments    : object who - the rewarded player
 */
private void
reward_gold_quest(object who)
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
        LOG_QUEST(who, PAINT_REWARD, "GOLD PAINT QUEST");
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

        /* If it's the gold herb ingredient, dust has been
           received, and the quest hasn't been completed. */
        if (num == 1 &&
          ing_map[name][2] > 0 &&
          !from->test_bit("gondor", PAINT_GROUP, PAINT_BIT))
        {
            setuid();
            seteuid(getuid());
            set_alarm(1.0, 0.0, &command("say You brought the " +
                "ingredients I need to make gold paint! Now I " +
                "can paint that helm. I will also paint a piece " +
                "of armour gold for you when you wish.")); 
            reward_gold_quest(from); 
        }
        else
        {
            set_alarm(1.0, 0.0, &command("emote sets the " +
                ob->short() + " aside for you."));
        }
        set_alarm(1.6,0.0,&ob->remove_object());

        return;
    }

    if (ob->id("_gondor_gold_dust"))
    {
        alter_map(name, 2, 1);
        if (ing_map[name][1] > 0 &&
          !from->test_bit("gondor", PAINT_GROUP, PAINT_BIT))
        {
            setuid();
            seteuid(getuid());
            set_alarm(1.0, 0.0, &command("say You brought the " +
                "ingredients I need to make gold paint! Now I " +
                "can paint that helm. I will also paint a piece " +
                "of armour gold for you when you wish."));
            reward_gold_quest(from);
        }
        else
        {
            set_alarm(1.0, 0.0, &command("emote sets the " +
                ob->short() + " aside for you."));
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
    set_alarm(23.0, 0.0, &command("emote presents his work."));
    set_alarm(23.5, 0.0, &command("show full " + OB_NAME(arm)));
    set_alarm(25.0, 0.0, &command("give " + OB_NAME(arm) + " to " +
        OB_NAME(from)));
    set_alarm(25.1, 0.0, &command("put " + OB_NAME(arm)));
    set_alarm(25.2, 0.0, &command("say Would you like me to paint " +
        "it another colour now? I can paint it red, gold and of " +
        "course black. I might need an additive for my paint though."));
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
    set_alarm(6.0, 0.0, &command("emote furrows his brow in thought"));
    set_alarm(9.0, 0.0, &command("emote picks up a thick brush and " +
        "dips it in a bucket of " + query_colour() + " paint."));
    set_alarm(11.0, 0.0, &command("emote sweeps the brush across the " +
        name + " with confident strokes."));
    set_alarm(16.0, 0.0, &command("emote replaces the brush and picks " +
        "up a very fine one."));
    set_alarm(19.0, 0.0, &command("emote dips the brush into another " +
        "bucket of paint and bends over the " + arm->query_name() + 
        ", blocking your view. His face takes on a very intent look " +
        "as he works."));
    set_alarm(24.5, 0.0, &command("emote straightens and presents " +
        "his work."));
    set_alarm(27.0, 0.0, &command("show full " + OB_NAME(arm)));
    set_alarm(29.0, 0.0, &command("asay humbly I hope my work is " +
        "satisfactory."));
    set_alarm(30.0, 0.0, &command("give " + OB_NAME(arm) + " to " +
        OB_NAME(TP)));
    set_alarm(30.1, 0.0, &command("drop " + OB_NAME(arm)));
    set_alarm(30.2, 0.0, &command("say I can paint armours " +
        "in other colours too. I can paint with red, gold and of " +
        "course black."));
    set_alarm(30.2, 0.0, &set_marker(0));
    return 1;
}

