/*
 * Gear Painter at the fort in Sybarus, based on:
 *           /d/Gondor/minas/npc/painterq.c
 *           Coded by Gwyneth on August 28, 2000
 * Creator:    Lilith, March 2022
 * Revisions:  Lilith, May 2022: Removed the need for gems for colors.
 *                     Too much bother for players I think.
 */

inherit "/d/Avenir/inherit/sybarite";
#include "/d/Avenir/include/paths.h"
#include "/d/Avenir/include/defs.h"

#include <files.h>
#include <macros.h>
#include <math.h>
#include <ss_types.h>
#include <stdproperties.h>
#include "/d/Avenir/common/outpost/paint_shop.h"

/* Global variables */
static int gMarker;
static string gPaint;
public mapping ing_map = ([]);

/* Numbers to allow name-to-random pigments given 
 * Should be a constant during Armageddon but 
 * Change with each reboot so people don't get 
 * stuck with a rare or expensive gem type for
 * eternity.
 */
static int gTimeNum = time(); 
#define G_IDENT 180643536 + gTimeNum
#define G_RANGE 4
#define R_IDENT 297456530 + gTimeNum
#define R_RANGE 4
#define P_IDENT 354345891 + gTimeNum 
#define P_RANGE 4

/* Index positions for the mapping values that keep track
   of who brought which pigments. 
*/
#define RED    0
#define GREEN  1
#define PURPLE 2
#define GREY   3

/* Prototypes */
public int paint_tells(object arm, object from);

void
cleanup_voloda()
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
create_sybarite()
{
    set_name("voloda");
    add_name("painter");
    set_living_name("voloda");
    set_race_name("dwarf");
    set_title("icu Ler-iss, Proprietor of the paint shop");
    set_adj(({"artistic", "thin-bearded"}));
    set_long("This woman seems short even for a dwarf -- but don't " +
	    "tell her that! What she lacks in stature she makes up for "+
        "with a vibrant, engaging personality.\n"+
        "She's a flurry of activity, seeming to go in many "+
        "directions at once.\n"+
		"She is wearing a paint-spattered smock.\n"+
		"Her long, dark hair is plaited into many braids and held at "+
        "the nape of her neck with a metal clasp.\n"+
        "Her beard is thin and fuzzy.\n"+
		"She has pale grey eyes with a dreamy look to them.\n");
    set_gender(G_FEMALE);
	set_alignment(0);
	
    default_config_npc(80 + random(10));

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(OBJ_M_NO_ATTACK, "A power greater than you protects her.\n");
    add_prop(CONT_I_HEIGHT, 70);
	add_prop(CONT_I_WEIGHT, 35000);
	
	set_chat_time(15);
    add_chat("Ae like being where the action is.");
    add_chat("Ae have never been this close to the Underdark before.");
    add_chat("Outlanders aren't as different from us as ae thought.");
    add_chat("Keep your gear as good as new with frequent touch-ups.");
    add_chat("It is better to repair the paint on gear here rather "+
        "than wait until the men are rotated to the Village, because "+
        "rust happens.");
    add_chat("Painting is joyful work. I love it!");
    add_chat("Be sure you've read the sign before you interrupt "+
        "my work, ok?");
    add_chat("Sometimes adjusting to change is hard, but the pain "+
        "is temporary. Plus, it is an opportunity to grow!");
	add_chat("Blink not at doing the Will of the Gods.");
	add_chat("Without fear, there is no courage.");
	add_chat("There is little advantage in pleasing ourselves if "+
        "we are not pleasing the Gods.");
    add_chat("It takes a long time for excellence to reach maturity.");
    add_chat("The Gods charge no soul beyond its capacity to achieve "+
        "Their Will.");
		
    set_act_time(10);
    add_act("emote blends some paints together.");
    add_act("emote dabs paint carefully on the surface.");
    add_act("emote wipes her fingers on her smock.");	
    add_act("emote pauses for a brief moment, then erupts into "+
        "action.");
    add_act("emote hums to herself.");
    add_act("emote smiles brightly.");
    add_act("emote changes brushes.");
    add_act("dances around the table.");
    add_act("fans a recently-painted shield dry.");	
   
    add_ask(({"paint", "gear", "paint gear", "paint item"}), 
	    "say Ae can paint just about anything su want. " +
        " Please read the sign for more information.", 1);
    add_ask(({"sigil", "symbol", "trefoil", "golden trefoil"}), 
      	"say The golden trefoil is the symbol of Sybarus.", 1);
    add_ask(({"additive", "additives", "paint additives", 
	    "pigments", "ingredients", "minerals"}),
        "say Ae am always short on paint pigments. It's a pity, since " +
        "ae can make such beautiful colours! Ae have a rule now that "+
	    "if su want me to paint your gear you have to fetch me "+
		"something ae need as part of the payment.", 1);
    add_ask(({ "fetch", "colours", "colour", "help", "task",
	    "ingredients" }), "@@give_colours");
    add_ask(({"purple", "purple paint", "purple additive"}), "@@purple");
    add_ask(({"red", "red paint", "red additive"}), "@@red");
    add_ask(({"green", "green paint", "green additive"}), "@@green");
    set_default_answer("@@default_ans");
	seteuid(getuid());
	
    restore_object(MASTER);
    cleanup_voloda();
	
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
        command("emote appears to be hyper-focussed on something.");
        break;
    case 1:
        command("say Ae am sorry, ae don't understand what you're asking.");
        break;
    case 2:
        command("say Some questions just don't have answers.");
        break;
    case 3:
        command("emote looks irritated.");
        command("say That knowledge is above my pay grade.");
        break;
    case 4:
        command("emote shrugs.");
        command("say Ae don't understand your accent.");
        break;
    }
    return "";
}

/*
 * Function name: red_gem
 * Description  : Returns the name-to-random specific gem for
 *                the player (object player) that they need
 *                to find and return to be able to paint a
 *                piece of armour red.
 */
public string
red_gem(object player)
{
    return (RED_ING[NAME_TO_RANDOM(player->query_real_name(),
      R_IDENT, R_RANGE)]);
}

/*
 * Function name: green_gem
 * Description  : Returns the name-to-random specific gem for
 *                the player (object player) that they need
 *                to find and return to be able to paint a
 *                piece of armour green.
 */
public string
green_gem(object player)
{
    return (GREEN_ING[NAME_TO_RANDOM(player->query_real_name(),
      G_IDENT, G_RANGE)]);
}

/*
 * Function name: purple_gem
 * Description  : Returns the name-to-random specific gem for
 *                the player (object player) that they need
 *                to find and return to be able to paint a
 *                piece of armour purple.
 */
public string
purple_gem(object player)
{
    return (PURPLE_ING[NAME_TO_RANDOM(player->query_real_name(),
      P_IDENT, P_RANGE)]);
}

/*
 * Function name: purple_id
 * Description  : Returns the name-to-random specific gem for
 *                the player (object player) that they need
 *                to find and return to be able to paint a
 *                piece of armour purple. Purple gems have 
 *                different name.
 */
public string
purple_id(object player)
{
    return (PURPLE_ID[NAME_TO_RANDOM(player->query_real_name(),
      P_IDENT, P_RANGE)]);
}




/*
 * Function name: red
 * Description  : Notify the player that asks what ingredient they
 *                need for red paint.
 */
public string
red()
{
    command("whisper to " + OB_NAME(this_player()) + " Red is for "+
        "those Sybarun Houses that are allied with the Lord High "+
        "executioner.");		
/*	
    command("whisper to " + OB_NAME(this_player()) + " I can mix red paint " +
        "if you fetch me " + LANG_ART(red_gem(this_player())) + " " +
        red_gem(this_player()) + ".");
 */
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
    command("whisper to " + OB_NAME(this_player()) + " Green is for "+
        "those Sybarun Houses that are allied with the Lord High "+
        "Inquisitor.");
/* 
    command("whisper to " + OB_NAME(this_player()) + " I can mix green paint " +
        "if you fetch me " + LANG_ART(green_gem(this_player())) + " " +
        green_gem(this_player()) + ".");
*/		
    return "";
}

/*
 * Function name: purple
 * Description  : Notify the player that asks what ingredients they
 *                need for purple paint.
 */
public string
purple()
{

   command("whisper to " + OB_NAME(this_player()) + " Purple is for "+
        "those Sybarun Houses that are allied with the Lord High "+
        "Commissioner, who is also the Hegemon.");
/*	
    command("whisper to " + OB_NAME(this_player()) + " I can mix purple " +
        "paint if you fetch me " + LANG_ART(purple_gem(this_player())) + " " +
        purple_gem(this_player()) + ".");
*/
    return "";
}


public string
give_colours()
{
    command("whisper to " + OB_NAME(this_player()) + " I can paint "+
        "just about anything in green, red, purple, or grey.");	
/*	
    string ggem = green_gem(this_player()), 
           bgem = red_gem(this_player()),
           sgem = purple_gem(this_player());

  
    command("whisper to " + OB_NAME(this_player()) + " I can make green " +
            "paint with " + ggem + ", red paint with " + bgem + " or " +
            "purple paint with " + sgem + ".");
*/   
    return "";
}

/*
 * Function name: valid_gem
 * Description  : Tests to see if an gem is one of the ingredients
 *                needed. Returns the position of the gem in the
 *                array: red - 0, green - 1, purple - 2.
*/
public int
valid_gem(string gem, object player)
{
    string *pigments = ({});

    pigments += ({ red_gem(player) });
    pigments += ({ green_gem(player) });
    pigments += ({ purple_id(player) });

    return (member_array(gem, pigments));
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
    case "green":
        if (ing_map[who][1] > 0)
            return 1;
        break;
    case "purple":
        if (ing_map[who][2] > 0)
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
 *                index: red - 0, green - 1, purple - 2;
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

    if (gPaint != "grey")
    {
        alter_map(person->query_real_name(), colour, -1);
    }
    arm->move(this_object(), 1);

    mon = ((arm->query_prop(OBJ_I_VOLUME) * 22) / 7);
    if (mon < 144) mon = 864;
    if (mon > 175000) mon = 17500;
  	    
    /* If the armour has never been painted, find the long and short. */
    if (!repaint)
    {
        desc = arm->short();
        ldesc = arm->query_long();
        sdesc = arm->query_short();
        pdesc = arm->plural_short();
        arm->set_long( LONG(arm) );
        write_file(PAINT_LOG, ctime(time()) + " " + this_player()->query_name() +
            " " + file_name(arm) +
            " " + COLOUR[colour] + "(" + SHORT(arm) + "/" +
            PSHORT(arm) + ") for " + mon + " copper.\n");
    }
    /* If the gear has been painted, find the original short. */
    else
    {
        desc = arm->query_prop(OBJ_S_PAINTED)[1];
        arm->set_long( RLONG(arm) );
        arm->remove_name("_sybarus_painted");
        write_file(PAINT_LOG, ctime(time()) + " " +
            this_player()->query_name() + " " + file_name(arm) +
            " from " + (arm->query_prop(OBJ_S_PAINTED))[2] +
            "to " + COLOUR[colour] + "(" + SHORT(arm) + "/" +
            PSHORT(arm) + ") for " + mon + " copper.\n");
    }

    set_alarm(1.3, 0.0, &person->catch_tell("You request to have your " +
        arm->short() + (repaint ? " repainted " : " painted ") + 
        COLOUR[colour] + " with the symbol of " + PLACE + ".\n"));

    paint_tells(arm, person);

    arm->add_prop(OBJ_S_PAINTED, ({ PLACE, desc, COLOUR[colour] }));
    arm->add_prop(OBJ_S_PAINT_INFO, ({ ldesc, sdesc, pdesc, adjs }));
	arm->add_item(({"trefoil", "golden trefoil"}), "The golden trefoil "+
       "is the symbol of Sybarus.\n");
    arm->remove_adj(adjs);
    arm->add_adj(ADJS);
    arm->add_adj("unworn");
    arm->set_short( SHORT(arm) );
    arm->set_pshort( PSHORT(arm) );
    arm->add_name("_sybarus_painted");
    return 1;
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
/*
    if (ob->query_gem())
    {
        num = valid_gem(ob->query_gem_name(), from);
        if (num >= 0)
        {
            alter_map(name, num, 1);
        }
        else
        {
            set_alarm(0.8, 0.0, &command("say That's not " +
                "a gem I wanted you to get for me."));
            set_alarm(1.0, 0.0, &command("put " + OB_NAME(ob)));
            return;
        }
    }
*/	
	
    if (previous_object(-1) != this_object() &&
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
    set_alarm(9.0, 0.0, &command("emote picks up a crock full of " +
        "paint solvent."));
    set_alarm(11.0, 0.0, &command("emote saturates a cloth with " +
        "the solvent and starts to rub the paint off of the " +
        name + "."));
    set_alarm(15.0, 0.0, &tell_room(environment(TO), "The paint " +
        "dissolves like magic as she scrubs the "+ name +".\n"));
    set_alarm(18.0, 0.0, &command("emote rinses off the cloth and "+
        "wipes the "+ name +" down with it."));
    set_alarm(20.0, 0.0, &command("emote buffs the "+ name +" with "+
        "a fresh cloth."));
    set_alarm(23.0, 0.0, &command("emote presents her work."));
    set_alarm(23.5, 0.0, &command("show full " + OB_NAME(arm)));
    set_alarm(25.0, 0.0, &command("give " + OB_NAME(arm) + " to " +
        OB_NAME(from)));
    set_alarm(25.1, 0.0, &command("put " + OB_NAME(arm)));
    set_alarm(25.1, 0.0, &command("say Would you like me to paint it " +
        "another colour now? I can paint it red, purple, green, and " +
        "of course grey. You might need to get a pigment for my " +
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
    set_alarm(18.0, 0.0, &command("emote dips the brush in gold leaf " +
        "paint and draws three overlapping circles on the " + 
        arm->query_name() + " in the shape of a trefoil."));
    set_alarm(21.0, 0.0, &command("emote straightens and presents " +
        "her work."));
    set_alarm(22.0, 0.0, &command("show full " + OB_NAME(arm)));
    set_alarm(24.0, 0.0, &command("give " + OB_NAME(arm) + " to " +
        OB_NAME(from)));
    set_alarm(26.1, 0.0, &command("drop " + OB_NAME(arm)));
    set_alarm(26.2, 0.0, &command("say I can paint armours " +
        "red, purple, green, and of course grey. I might ask " +
        "you to get me gems for pigments for my paint."));
    set_alarm(28.0, 0.0, &set_marker(0));
    return 1;
}

