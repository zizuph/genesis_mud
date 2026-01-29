/* vamp_soul.c created by Shiva@Genesis 8/01/95
 * This is the vampire guild cmdsoul.  A few emotes
 * taken from Mylos' vampyr guild.
 */

#pragma save_binary
#pragma no_clone
#pragma strict_types

inherit "/cmd/std/command_driver";

#include "../guild.h"
#include <cmdparse.h>
#include <formulas.h>
#include <stdproperties.h>
#include <macros.h>
#include <stdproperties.h>
#include <files.h>
#include <filter_funs.h>
#include <composite.h>
#include <language.h>

#define SOULDESC(x)  (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define POSTP        (this_player()->query_possessive())
#define PROTP        (this_player()->query_pronoun())
#define OBJTP        (this_player()->query_objective()

#define EMOTE_LOG    ("/d/Emerald/common/guild/vamp/log/emotes/")

string get_soul_id() { return GUILD_NAME; }

int query_cmd_soul() { return 1; }

/* mapping of emotes to their functions.
 * Function names prefixed by an underscore are meant to be hidden,
 * i.e. they will not be written using dump_emotes.
 * These should only be simple emotes...nothing beneficial or
 * informational (in other words, taxable).  
 * This is done with simple management of help files in mind.
 */
mapping query_cmdlist()
{
    return ([
#ifndef NO_FREE_EMOTES
  	        "::"        : "_emote",
		"vemote"    : "_emote",
#endif
                "vbeckon"   : "vbeckon",
                "vblood"    : "vblood",
                "vbow"      : "vbow",
                "vbreathe"  : "vbreathe",
                "vbrush"    : "vbrush",
                "vcaress"   : "vcaress",
                "vchuckle"  : "vchuckle",
                "vclench"   : "vclench",
                "vconsider" : "vconsider",
                "vcurtsey"  : "vcurtsey",
                "vdance"    : "vdance",
                "vecstacy"  : "vecstacy",
                "ventrance" : "ventrance",
                "vfang"     : "vfang",
                "vgaze"     : "vgaze",
                "vglance"   : "vglance",
                "vglare"    : "vglare",
                "vglower"   : "vglower",
                "vgrin"     : "vgrin",
                "vgust"     : "vgust",
                "vhiss"     : "vhiss",
                "vhug"      : "vhug",
                "vkiss"     : "vkiss",
                "vlaugh"    : "vlaugh",
                "vlick"     : "vlick",
                "vlong"     : "vlong",
                "vlook"     : "vlook",
                "vnarrow"   : "vnarrow",
                "vnod"      : "vnod",
                "vpierce"   : "vpierce",
                "vpity"     : "vpity",
                "vpower"    : "vpower",
                "vrespect"  : "vrevere",
                "vreveal"   : "vreveal",
                "vrevere"   : "vrevere",
                "vrise"     : "vrise",
                "vroar"     : "vroar",
                "vscratch"  : "vscratch",
                "vscream"   : "vscream",
                "vshadow"   : "vshadow",
                "vsmile"    : "vsmile",
                "vsmirk"    : "vsmirk",
                "vsneer"    : "vsneer",
                "vsniff"    : "vsniff",
                "vsweat"    : "vsweat",
                "vtear"     : "vtear",
                "vthroat"   : "vthroat",
                "vturn"     : "vturn",
                "vyawn"     : "vyawn",
        ]);
}

/* write to a file the list of available emotes.  If the function name for
 * the emote is prefixed by an underscore, it will not be included.
 */
varargs void dump_emotes(string file, int append)
{
    string *dump_emotes, *vamp_emotes;
    mapping m_vamp_emotes;

    if (!strlen(file))
    {
        return;
    }
  
    m_vamp_emotes = query_cmdlist();
    vamp_emotes = m_indices(m_vamp_emotes);
    dump_emotes = filter(vamp_emotes, &operator(==)(0) @ &wildmatch("_*") @
                         &operator([])(m_vamp_emotes));
  
    setuid();
    seteuid(getuid());

    if (!append && file_size(file) > -1)
    {  
        rm(file);
    }

    if (!sizeof(dump_emotes))
    {
        write_file(file, "No emotes.\n");
    }
    else
    {
        dump_emotes = sort_array(dump_emotes);
        write_file(file, sprintf("%#-70s\n", implode(dump_emotes, "\n")));
    }
}


varargs void
tell_others(string str, object *exclude)
{
    object *players;

    players = all_inventory(environment(this_player())) - exclude;
    players = FILTER_PLAYERS(FILTER_CAN_SEE_IN_ROOM(players));

    if (sizeof(players))
    {
        players->catch_msg(str);
    }
}


string *
parse_adverb_with_space(string str, string def_adv, int trail)
{
    string *adv = ::parse_adverb_with_space(str, def_adv, trail);

    if (adv[1] == " ")
    {
        adv[1] = "";
    }

    return adv;
}


/*
 * Function name: find_neighbour
 * Description  : This function will recursively search through the
 *                neighbouring rooms to a particular room to find the
 *                players present in connecting rooms
 * Arguments    : object *found  - the rooms already found.
 *                object *search - the rooms still to search.
 *                object *ppl    - the people who have been found
 *                int    depth   - the depth still to search.
 * Returns      : object * - the people found
 */
static varargs object *
find_neighbour(object *found, object *search, object *ppl = ({}), 
    int depth = 2)
{
    int index;
    int size;
    int index2;
    int size2;
    mixed *exit_arr;
    object *new_search, *rooms, troom;

    if (!depth)
        return ppl;

    rooms = found;
    new_search = ({ });

    index = -1;
    size = sizeof(search);
    while(++index < size)
    {
        exit_arr = (mixed *) search[index]->query_exit();

        index2 = -3;
        size2 = sizeof(exit_arr);
        while((index2 += 3) < size2)
        {
            if (functionp(exit_arr[index2]))
                continue;
            if (objectp(exit_arr[index2]))
                troom = exit_arr[index2];
            else
                troom = find_object(exit_arr[index2]);
            if (objectp(troom) &&
                (member_array(troom, rooms) < 0))
            {
                rooms += ({ troom });
                new_search += ({ troom });
                ppl |= FILTER_PLAYERS(all_inventory(troom));
            }
        }
    }

    return find_neighbour(rooms, new_search, ppl, depth - 1);
}

    
/*
 * Function name: find_area
 * Description:   Get everyone else within the area.  We define "area" as
 *                all rooms within the same directory as the one we're in or
 *                within a two-room radius.  This isn't perfect, but it's
 *                the best that can be done without requiring an enormous
 *                amount of processing.
 * Arguments:     object room - our room
 * Returns:       The players in the area
 */
static varargs object *
find_area(object room)
{
    object env, *all, *ppl = ({});
    string dir;
    int i;

    dir = implode(explode(file_name(room), "/")[..-2], "/") + "/*";

    all = users();
    for (i = 0; i < sizeof(all); i++)
    {   
        if (!(env = environment(all[i])))
        {
            continue;
        }

        if (wildmatch(dir, file_name(env)))
        {
            ppl += ({ all[i] });
        }
    }

    ppl |= find_neighbour(({ room }), ({ room }));
    ppl -= all_inventory(room);

    return ppl;
}

#ifndef NO_FREE_EMOTES
public string
query_item_desc(string item_id, object for_whom)
{
    object item = find_object(item_id);

    if (!item)
    {
        return "";
    }

    if (item == for_whom)
    {
        return "you";
    }

    if (living(item))
    {
        return item->query_the_name(for_whom);
    }

    return item->short(for_whom);
}    

public string
query_poss_item_desc(string item_id, object for_whom)
{
    object item = find_object(item_id);

    if (!item)
    {
        return "";
    }

    if (item == for_whom)
    {
        return "your";
    }

    if (living(item))
    {
        return item->query_the_possessive_name(for_whom);
    }

    return LANG_POSS(item->short(for_whom));
}    


public string
desc_items(string item_id, ...)
{
    object for_whom = previous_object(-1);
    return COMPOSITE_WORDS(map(({ item_id }) + argv,
        &query_item_desc(, for_whom)));
}    

public string
desc_poss_items(string item_id, ...)
{
    object for_whom = previous_object(-1);
    return COMPOSITE_WORDS(map(({ item_id }) + argv,
        &query_poss_item_desc(, for_whom)));
}    

public string
desc_cap_items(string item_id, ...)
{
    //return capitalize(applyv(&desc_items(item_id), argv));
    object for_whom = previous_object(-1);
    return capitalize(COMPOSITE_WORDS(map(({ item_id }) + argv,
        &query_poss_item_desc(, for_whom))));
}

varargs public string
desc_many_items(object *obs, int cap, int poss)
{
    string args = "|" + implode(map(obs, file_name), "|");
    
    if (poss)
    {
    	if (cap)
    	{    
    	    return "@@desc_cap_poss_items:" + file_name(this_object()) + args + "@@";
    	}
    
    	return "@@desc_poss_items:" + file_name(this_object()) + args + "@@";
    }
    if (cap)
    {    
        return "@@desc_cap_items:" + file_name(this_object()) + args + "@@";
    }

    return "@@desc_items:" + file_name(this_object()) + args + "@@";
}

int
_emote(string str)
{
    string new, desc, *parts;
    object *obs;
    int i;
    int possessive;

    setuid();
    seteuid(getuid());

    if (!MANAGER->query_free_emotes_enabled(this_player()) &&
        !this_player()->query_wiz_level() &&
        !IS_JR(this_player()))
    {
        return 0;
    }

    if (!strlen(str))
    {
        notify_fail("Usage: \"vemote <message>\"\n");
        return 0;
    }

    parts = explode(str, "|");
    new = "";
    for (i = 0; i < sizeof(parts); i++)
    {
	possessive = 0;

        if ((i % 2) == 0)
	{
	   new += parts[i];
	}
	else
        {
	    if (sscanf(parts[i], "%s'", parts[i]) ||
		sscanf(parts[i], "%s's", parts[i]))
	    {
		possessive = 1;
	    }

            obs = parse_this(lower_case(parts[i]), "[the] %i");
            if (!sizeof(obs))
	    {
		if ((lower_case(parts[i]) == "me") ||
                    (lower_case(parts[i]) == this_player()->query_real_name()))
		{
		    obs = ({ this_player() });
		}
		else if (lower_case(parts[i]) == "my")
		{
		    obs = ({ this_player() });
		    possessive = 1;
		}
		else
		{
		    notify_fail("Not present: " + parts[i] + ".\n");
        	    return 0;
		}
	    }

            new += desc_many_items(obs, (parts[i][0] <= 'Z'), possessive);
	}

    }

    /* The log is intentionally put before the emote output.  This way,
     * if the log write incurs an error, no emote happens.  We don't
     * want to allow any unlogged emotes to happen.
     */
    write_file(EMOTE_LOG + this_player()->query_real_name(),
       ctime(time()) + ": " + str + 
       " [" + implode(sort_array(map(all_inventory(environment(this_player())), capitalize @ &->query_real_name())), ", ") + "]\n");

    write("You emote: " + str + "\n");
    say(new + "\n");

    return 1;
}
#endif
        
int
vbeckon(string str)
{
    object *oblist;

    if (!strlen(str) || !sizeof(oblist = parse_this(str, "[to] [the] %l")))
    {
        notify_fail("Beckon to whom?\n");
        return 0;
    }

    targetbb(" beckons to you with "+ POSTP + " glass-nailed finger.", oblist);
    actor("You beckon to", oblist, " with your glass-nailed finger.");
    all2actbb(" beckons to", oblist, " with " + POSTP +
              " glass-nailed finger.");

    return 1;
}

int
vblood(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        string floor = environment(this_player())->query_prop(ROOM_I_INSIDE) ? "floor" : "ground";
        write("You open your mouth slightly, letting a drop of blood "+
              "spill onto the " + floor + ".\n");
        allbb(" opens " + POSTP + " mouth, letting a drop of blood " +
              "spill onto the " + floor + ".");

        return 1;
    }

    if (sizeof(oblist = parse_this(str, "[on] / [onto] [the] %l")) != 1)
    {
        notify_fail("Drip blood where?\n");
        return 0;
    }

    targetbb(" opens " + POSTP + " mouth slightly, letting a drop "+
             "of blood spill onto you.", oblist);
    actor("You open your mouth near", oblist,", letting a drop "+
          "of blood spill onto " + OBJ(oblist[0]) + ".");
    all2actbb(" opens " + POSTP + " mouth slightly, letting a drop "+
              "of blood spill onto", oblist, ".");

    return 1;
}

int
vbow(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You bow with preternatural grace.\n");
        allbb(" bows with preternatural grace.");
        return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[to] / [before] [the] %l")))
    {
        notify_fail("Bow before whom?\n");
        return 0;
    }

    if (sizeof(oblist) == 1)
    {
        write("You gaze deep into " + 
            LANG_POSS(oblist[0]->query_the_name(this_player())) +
            " eyes and bow with preternatural grace.\n");
        targetbb(" gazes deep into your eyes and bows with preternatural " +
            "grace.", oblist);
    }
    else
    {
        actor("You bow before", oblist, " with preternatural grace.");
        target(" bows before you with preternatural grace.", oblist);
    }

    all2actbb(" bows before", oblist, " with preternatural grace.");
    return 1;
}

int
vbreathe(string str)
{
    object *oblist;

    if (!strlen(str) ||
        sizeof(oblist = parse_this(str, "[on] / [the] %l")) != 1)
    {
        notify_fail("Breathe on whom?\n");
        return 0;
    }

    target(" steps behind you, and you can feel " + POSTP +
           " hot breath on your neck.", oblist);
    actor("You step behind", oblist, " and breathe on " + POS(oblist[0]) +
          " neck.");
    all2actbb(" steps behind", oblist, " and lingers behind " +
              OBJ(oblist[0]) + ", examining " + POS(oblist[0]) + " neck.");

    return 1;
}

int
vbrush(string str)
{
    object *oblist;

    if (!strlen(str) ||
        sizeof(oblist = parse_this(str, "[the] %l")) != 1)
    {
        notify_fail("Brush your fangs against whom?\n");
        return 0;
    }

    target(" bends to gently kiss your neck, and brushes " + POSTP +
           " fangs against your neck.", oblist);
    write("You bend to gently kiss " + 
        LANG_POSS(oblist[0]->query_the_name(this_player())) + 
        " neck and brush your fangs against " + POS(oblist[0]) + " skin.\n");
    tell_others(QCTNAME(this_player()) + " bends and gently kisses " +
        QTPNAME(oblist[0]) + " neck.\n", ({ this_player(), oblist[0] }));

    return 1;
}

int
vclench(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You tightly clench your fist, barely able to control " +
              "your anger.\n");
        allbb(" tightly clenches " + POSTP + " fist, barely able " +
              "to control " + POSTP + " anger.");

        return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[my] [fist] [at] [the] %l")))
    {
        notify_fail("Clench your fist at whom?\n");
        return 0;
    }

    target(" tightly clenches " + POSTP + " fist, barely able " +
           "to control " + POSTP + " anger and hatred for you.", oblist);
    actor("You tightly clench your fist, barely able to control " +
          "your anger and hatred for", oblist, ".");
    all2actbb(" tightly clenches " + POSTP + " fist, barely able " +
              "to control " + POSTP + " anger and hatred for", oblist,
              ".");

    return 1;
}

int
vconsider(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You consider your options.\n");
        allbb(" considers " + POSTP + " options.");
        return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail("Consider whom?\n");
        return 0;
    }

    targetbb(" looks at you carefully, considering " + POSTP +
             " options.", oblist);
    actor("You look carefully at", oblist, " considering your options.");
    all2actbb(" looks carefully at", oblist, " and considers " +
              POSTP + " options.");

    return 1;
}

int
vcurtsey(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You curtsey with preternatural grace.\n");
        allbb(" curtseys with preternatural grace.");
        return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[to] / [before] [the] %l")))
    {
        notify_fail(capitalize(query_verb()) + " before whom?\n");
        return 0;
    }

    if (sizeof(oblist) == 1)
    {
        write("You gaze deep into " + 
            LANG_POSS(oblist[0]->query_the_name(this_player())) +
            " eyes and curtsey with preternatural grace.\n");
        targetbb(" gazes deep into your eyes and curtseys with " +
            "preternatural grace.", oblist);
    }
    else
    {
        actor("You curtsey before", oblist, " with preternatural grace.");
        target(" curtseys before you with preternatural grace.", oblist);
    }

    all2actbb("  curtseys before", oblist, " with preternatural grace.");
    return 1;
}

int vecstacy(string str)
{
    object *oblist;

    if (!strlen(str) ||
        (sizeof(oblist = parse_this(str, "[over] [the] %l")) != 1))
    {
        notify_fail("Go into ecstacy over whom?\n");
        return 0;
    }

    targetbb(" closes " + POSTP + " eyes in ecstacy, savoring the " +
        "taste of your blood.", oblist);
    actor("You close your eyes in ecstacy, savoring the taste of",
        oblist, "'s blood.");
    tell_others(QCTNAME(this_player()) + " closes " + POSTP +
        " eyes in ecstacy, savoring the taste of " + QTPNAME(oblist[0]) +
        " blood.\n", ({ this_player(), oblist[0] }));

    return 1;
}

int
vdance(string str)
{
    mixed *oblist;
    object ob;

    if (!strlen(str))
    {
        write("You perform an elegant dance.\n");
        allbb(" performs an elegant dance of delicate poise and " +
            "fluid motion.");
        return 1;
    }

    if (!CAN_SEE_IN_ROOM(this_player()) || 
        !parse_command(str, all_inventory(environment(this_player())),
        "[with] [the] %i", oblist) || 
        !sizeof(oblist = NORMAL_ACCESS(oblist, 0, 0)))
    {
        notify_fail(capitalize(query_verb()) + " with whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only dance with one person at a time.\n");
        return 1;
    }

    ob = oblist[0];

    if (living(ob))
    {
        if (!ob->query_humanoid())
        {
            write(ob->query_The_name(this_player()) + " doesn't appear to " +
                "be a good partner.\n");
            return 1;
        }

        actor("You take", oblist, " in your arms and lead " + 
            ob->query_objective() + " in an elegant dance.");
        target(" takes you in " + POSTP + " arms and leads you in an " +
            "elegant dance.\nYou feel an extraordinary lightness in your " +
            "body, as if you might float away if not for " + 
            LANG_POSS(this_player()->query_the_name(ob)) + " grasp.  " +
            "Without a thought, you find yourself moving in perfect sync " +
            "with " + POSTP + " steps, floating back and forth with " +
            "absolute poise and twirling with rapturous abandon.", oblist);
        all2actbb(" takes", oblist, " in " + POSTP + " arms and leads " +
            ob->query_objective() + " in an elegant dance.\nThe two move " +
            "in perfect sync, floating back and forth with absolute poise " +
            "and twirling with rapturous abandon.");
        return 1;
    }
    else if (IS_CORPSE_OBJECT(ob))
    {
        // Is there an easier way to do this?
        if ((ob->query_prop(OBJ_I_WEIGHT) > 
            ((this_player()->query_prop(CONT_I_MAX_WEIGHT) - 
            (this_player()->query_prop(OBJ_I_WEIGHT) -
            this_player()->query_prop(CONT_I_WEIGHT))) * 3 / 2)) ||
            (ob->query_prop(OBJ_I_VOLUME) >
            ((this_player()->query_prop(CONT_I_MAX_VOLUME) -
            (this_player()->query_prop(OBJ_I_VOLUME) -
            this_player()->query_prop(CONT_I_VOLUME))) * 3 / 2)))
        {
            write("You can't manage to pick up the corpse.\n");
            return 1;
        }

        write("You pick up the " + ob->short() + " and perform a " +
            "jaunty dance with it.\n");

        tell_others(QCTNAME(this_player()) + " picks up the " + 
            "@@short:" + file_name(ob) + "@@ and performs a jaunty " +
            "dance with it.\n", ({ this_player() }));

        return 1;
    }

    write("The " + ob->short() + " doesn't appear to abe a good partner.\n");
    return 1;
}

int
ventrance(string str)
{
    object *oblist, *tmp;

    if (!strlen(str) || sizeof(oblist = parse_this(str, "[the] %l")) != 1)
    {
        notify_fail("Ventrance whom?\n");
        return 0;
    }

    targetbb(" gazes deep into your eyes.  You find yourself transfixed by " +
        "the strange beauty of " + POSTP + " eyes--the mysterious " +
        "luminescence of " + POSTP + " irises contrasting the profound " +
        "blackness of " + POSTP + " pupils.  Lost in " + POSTP +
        " entrancing gaze, blissful hours pass, until " + PROTP + " turns " +
        "aside " + POSTP + " gaze.  You regain your faculties and realize " +
        "that only a moment has passed.", oblist);
    actor("You turn your entrancing gaze toward", oblist, ".");

    all2actbb(" gazes deep into", oblist, "'s eyes.  A serene expression " +
        "passes over " +  oblist[0]->query_possessive() + " face, as if " +
        "lost in a blissful daydream.");

    /* Would prefer to make this all one call to all2actbb(), but the
     * function doesn't allow me to use QCTNAME :-/.  Until all2actbb()
     * takes VBFCs, I'll have to do the messages separately.
     */
    tell_others(QCTNAME(this_player()) + " turns aside " + POSTP +
        " gaze, and " + oblist[0]->query_pronoun() + " quickly regains " +
        oblist[0]->query_possessive() + " composure.\n",
        ({ this_player(), oblist[0] }));

    return 1;
}

int vfang(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You bare your fangs in abject anger.\n");
        allbb(" bares " + POSTP + " fangs.");
        return 1;
    }

    notify_fail("Bare thy fangs at whom?\n");
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        return 0;
    }

    targetbb(" bares " + POSTP + " fangs at you in anticipation " +
             "of your blood.", oblist);
    actor("You bare your fangs at", oblist, " in anticipation of "+
          "fresh blood.");
    all2actbb(" bares " + POSTP + " fangs at", oblist,
              " in anticipation of fresh blood.");

    return 1;
}

int vgaze(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You gaze around the room, seeking a soul to entice.\n");
        allbb(" gazes around the room, seeking a soul to ensnare.");
        return 1;
    }

    notify_fail("Gaze at whom?\n");
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        return 0;
    }

    targetbb(" gazes deep into your eyes.", oblist);
    actor("You gaze deep into", oblist, "'s eyes.");
    all2actbb(" gazes deep into", oblist, "'s eyes.");

    return 1;
}

int vglower(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You glower around the room in rage and anger.\n");
        allbb(" glowers around the room in rage and anger.");
        return 1;
    }

    notify_fail("Glower at whom?\n");
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        return 0;
    }

    target(" glowers at you angrily, you can see the rage deep in "+
           POSTP + " eyes.", oblist);
    actor("You glower at", oblist, ", the rage clearly visible in your "+
          "eyes.");
    all2actbb(" glowers angrily at", oblist);

    return 1;
}

int vgust(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("A gust of icy air as cold as death swirls around you.\n");
        say(({ "A gust of icy air as cold as death swirls around " +
                   this_player()->query_name() + ".\n", 
                   "A gust of icy air as cold as death swirls around " +
                   this_player()->query_nonmet_name() + ".\n", "" }));

        return 1;
    }
 
    notify_fail("Gust what?\n");
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        return 0;
    }

    target(" causes a gust of icy air as cold as death " +
           "to swirl around you.", oblist);
    actor("You cause a gust of icy air as cold as death "+
          "to swirl around", oblist);
    all2actbb(" causes a gust of icy air as cold as death "+
              "to swirl around", oblist);

    return 1;
}

int vhiss(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "venomously", 0);

    if (!stringp(how[0]))
    {
        write("You hiss" + how[1] + ".\n");
        allbb(" hisses" + how[1] + ".");
    }
    else
    {
        notify_fail("Hiss at whom?\n");
        if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
        {
            return 0;
        }

        target(" hisses at you" + how[1] + ".", oblist);
        actor("You hiss" + how[1] + " at", oblist, ".");
        all2act(" hisses" + how[1] + " at", oblist);
    }

    SOULDESC("hissing" + how[1]);
    return 1;
}

public int
vhug(string str)
{
    object *oblist;

    if (!strlen(str) ||
        !sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail(capitalize(query_verb()) + " whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can't manage to get your arms around that " +
            "many people.\n");
        return 1;
    }

    target(" enfolds you in " + POSTP + " arms, holding you tightly in " +
        POSTP + " embrace.  " + capitalize(POSTP) + " body is as cold and unyielding " +
        "as stone; only the slow, soothing beating of " + POSTP + " heart " +
        "reminds you that " + PROTP + " isn't a statue of marble.", oblist);
    write("You take " + oblist[0]->query_the_name(this_player()) + 
        " in your arms and hold " + OBJ(oblist[0]) + " tightly in your " +
        "embrace.\n");
    all2actbb(" takes", oblist, " in " + POSTP + " arms, holding " +
        OBJ(oblist[0]) + " tightly in " + POSTP + " embrace.");

    return 1;

}

public int
vlong(string str)
{
    object *oblist;

    if (!strlen(str) || sizeof(oblist = parse_this(str,
                   "[at] / [for] [the] %l")) != 1)
    {
        notify_fail("Long at whose neck?\n");
        return 0;
    }

    target(" gazes longingly at your neck.", oblist);
    actor("You gaze longingly at", oblist,"'s neck.");
    all2actbb(" gazes longingly at", oblist,"'s neck.");

    return 1;
}

public int
vnarrow(string str)
{
    object *oblist;
  
    if (!strlen(str))
    {
        write("You narrow your eyes in contemplation.\n");
        allbb(" narrows " + POSTP + " eyes in contemplation.");
        return 1;
    }
  
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        notify_fail("Narrow your eyes at whom?\n");
        return 0;
    }
  
    targetbb(" narrows " + POSTP + " eyes at you, deep in thought.",
             oblist);
    actor("You narrow your eyes at", oblist,", deep in thought.");
    all2actbb(" narrows " + POSTP + " eyes at", oblist, ", deep " +
              "in thought.");
  
    return 1;
}

public int
vpierce(string str)
{
    object *oblist;
    string his_her;
    
    if (!strlen(str) ||
        sizeof(oblist = parse_this(str, "[the] %l")) != 1)
    {
        notify_fail("Pierce whom?\n");
        return 0;
    }
  
    his_her = POS(oblist[0]);
  
    target(" stares at you, and you feel your soul laid bare by " +
           POSTP + " intense stare.", oblist);
    actor("You stare intensely at", oblist, " laying bare " +
          his_her + " soul.");
    all2actbb(" stares intensely at", oblist, " laying bare " +
              his_her + " soul.");
  
    return 1;
}

int vpity(string str)
{
    object *oblist;
  
    notify_fail("Pity whom?\n");
    if (!strlen(str) ||
        !sizeof(oblist = parse_this(str, "[the] %l")))
    {
        return 0;
    }

    target(" looks upon you with pity.", oblist);
    actor("You look upon", oblist, " with pity.");
    all2actbb(" looks upon", oblist, " with pity.");
  
    return 1;
}

int vpower(string str)
{
    if (strlen(str)) return 0;
  
    write("You infuse yourself with the dark power of the ancient Gods.\n");
    allbb(" infuses " + POSTP + " body with the power of the dark Gods.");
  
    return 1;
}

int vrevere(string str)
{
    object *oblist;

    if (!strlen(str) ||
        !sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail(capitalize(query_verb()) + " whom?\n");
        return 0;
    }

    if (sizeof(oblist) == 1)
    {
        target(" falls to " + POSTP + " knees in total reverence to you.",
               oblist);
        actor("You fall to your knees in total reverence to", oblist);
        all2actbb(" falls to "+POSTP+" knees in reverence towards", oblist);

        return 1;
    }

    return 0;
}

int vreveal(string str)
{
    if (!strlen(str) ||
        (str == "me") ||
        (str == "myself") || 
        (str == this_player()->query_real_name()))
    {
        if (this_player()->query_prop(OBJ_I_HIDE))
        {
            this_player()->remove_prop(OBJ_I_HIDE);
            allbb(" appears from out of the shadows.");
            write("You decide to come out of hiding.\n");
            return 1;
        }

        notify_fail("You aren't hidden, though!\n");
    }

    return 0;
}

int vrise(string str)
{
    if (strlen(str)) return 0;

    write("You rise to your full height and power.\n");
    allbb(" rises to " + POSTP + " full height and power.");

    return 1;
}

int
vroar(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "savagely", 0);

    if (!stringp(how[0]))
    {
        write("You roar" + how[1] + ".\n");
        
        allbb(" roars" + how[1] + ".");
    }
    else
    {
        notify_fail("Roar at whom?\n");
        if (!sizeof(oblist = parse_this(how[0], "[at] [the] [the] %l")))
        {
            return 0;
        }

        targetbb(" roar" + how[1] + " at you.", oblist);
        actor("You roar" + how[1] + " at", oblist, ".");
        all2actbb(" roar" + how[1] + " at", oblist, ".");
    }

    SOULDESC("roaring" + how[1]);
    return 1;
}

int
vscratch(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You look around the area, absentmindedly scratching one of "+
              "your fangs.\n");
        allbb(" looks around the area, absentmindedly scratching one of "+
              POSTP + " fangs.");

        return 1;
    }

    if (!sizeof(oblist = parse_this(str,  "[at] [the] %l")))
    {
        return 0;
    }

    target(" glances at you, absentmindedly scratching one of " +
           POSTP + " fangs.\n", oblist);
    actor("You glance at", oblist, ", absentmindedly scratching one of "+
          "your fangs.");
    all2act(" glances at", oblist, ", absentmindedly scratching one of "+
            POSTP + " fangs.");

    return 1;
}

int
vscream(string str)
{
    object *oblist, *ppl, troom;
    string *how = parse_adverb_with_space(str, "vexedly", 0);

    if (!stringp(how[0]))
    {
        write("You scream" + how[1] + ".\n");
        all(" screams" + how[1] + "; the deafening volume leaves " +
            "your ears ringing.");
    }
    else
    {
        notify_fail("Scream [how] at whom?\n");
        if (!sizeof(oblist = parse_this(how[0], "[at] [the] [the] %l")))
        {
            return 0;
        }

        targetbb(" screams" + how[1] + " at you; the deafening volume " +
            "leaves your ears ringing.", oblist);
        actor("You scream" + how[1] + " at", oblist, ".");
        all2actbb(" screams" + how[1] + " at", oblist, "; the deafening " +
            "volume leaves your ears ringing.");
    }

    if (!objectp(troom = environment(this_player())))
    {
        return 1;
    }

    /* Get everyone in a two-room radius */
    ppl = find_area(troom);
    ppl->catch_tell("You hear someone scream" + how[1] + 
        " in the distance.\n");

    SOULDESC("screaming" + how[1]);
    return 1;
}
    
int vshadow(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You throw your shadow about the room.\n");
        allbb("'s shadow flows around the room like a ghost.");
        return 1;
    }

    notify_fail("Cast a shadow across whom?\n");
    if (sizeof(oblist = parse_this(str, "[the] %l")) != 1)
    {
        return 0;
    }

    target("'s shadow detaches and flows towards you, finally "+
           "dissipating into a swirl of black smoke at your feet.", oblist);
    actor("You cause your shadow to flow at", oblist, ".");
    all2act(" \b's shadow flows towards", oblist,
            ", finally dissipating into a swirl of black smoke at " +
            POS(oblist[0]) + " feet.");

    return 1;
}

int vsneer(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "contemptuously", 0);

    if (!stringp(how[0]))
    {
        write("You sneer" + how[1] + ".\n");
        allbb(" sneers" + how[1] + ".");
    }
    else
    {
        notify_fail("Sneer at whom?\n");
        if (!sizeof(oblist = parse_this(how[0], "[at] [the] [the] %l")))
        {
            return 0;
        }

        targetbb(" sneers" + how[1] + " at you.", oblist);
        actor("You sneer" + how[1] + " at", oblist, ".");
        all2actbb(" sneers" + how[1] + " at", oblist, ".");
    }

    SOULDESC("sneering" + how[1]);
    return 1;
}

int
vsniff(string str)
{
    object *oblist;
    string pos;

    if (!strlen(str))
    {
        write("You sniff the air for traces of blood.\n");
        allbb(" sniffs the air for something.");
        return 1;
    }

    notify_fail("Sniff at whom?\n");
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        return 0;
    }

    pos = (sizeof(oblist) > 1 ? "their" : POS(oblist[0]));

    targetbb(" sniffs around you, for " + PROTP + " can smell your blood.",
             oblist);
    actor("You sniff the air around", oblist, ", for you can smell "+
          pos + " blood.");
    all2actbb(" sniffs the air around", oblist, " for " + PROTP +
              " can smell " + pos + " blood.");

    return 1;
}

int vglance(string str)
{
    if (strlen(str) && parse_command(str, ({}), "[at] [the] 'sun'"))
    {

        if (environment(this_player())->query_prop(ROOM_I_INSIDE) &&
            (environment(this_player())->query_prop("_room_i_sunlight") < 1))
        {
            write("There is no sun in here, you are inside.\n");           
            return 1;
        }

        write("You glance up with a look of both fear and contempt as the " +
            "accursed rays of the sun shine down upon you.\n");
        allbb(" glances up with a look of both fear and contempt in " + 
             POSTP + " eyes, as the rays of the sun are cast into the room.");

        return 1;
    }

    notify_fail("Vglance at the sun?\n");
    return 0;
}

int vthroat(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You growl slightly in the back of your throat.\n");
        all(" growls so very softly.");
        return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        notify_fail("Growl at whom?\n");
        return 0;
    }

    target(" growls softly in anger at you.", oblist);
    actor("You growl softly in anger at", oblist, ".");
    all2act(" growls softly in anger at", oblist, ".");

    return 1;
}

int vturn(string str)
{
    object *oblist;

    notify_fail("Turn to face whom?\n");
    if (!strlen(str) ||
        !sizeof(oblist = parse_this(str, "[to] [the] %l")))
    {
        return 0;
    }

    targetbb(" turns slowly to face you.", oblist);
    actor("You turn slowly to face", oblist, ".");
    all2actbb(" turns slowly to face", oblist, ".");

    return 1;
}

int vcaress(string str)
{
    object *oblist;

    notify_fail("Caress whom?\n");
    if (!strlen(str) ||
        sizeof(oblist = parse_this(str, "[the] %l")) != 1)
    {
        return 0;
    }
 
    target(" runs " + POSTP + " long fingernails along your shoulder "+
           "and neck.", oblist);
    actor("You run your fingernails down", oblist,"'s shoulder and neck.");
    all2actbb(" runs " + POSTP + " long fingernails down", oblist, "'s "+
              "shoulder and neck.");

    oblist[0]->command("shiver");

    return 1;
}

int vchuckle(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You chuckle softly, a sneer forming on your face.\n");
        allbb(" chuckles softly, a sneer forming on " + POSTP +
              " face.");
        return 1;
    }

    notify_fail("Vchuckle at whom?\n");
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        return 0;
    }

    actor("You chuckle softly at", oblist, ", a sneer forming on your " +
          "face.");
    targetbb(" chuckles softly at you, a sneer forming on " + POSTP +
             " face.", oblist);
    all2actbb(" chuckles softly at", oblist, ", a sneer forming on " +
              POSTP + " face.");

    return 1;
}

int vglare(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "", 0);

    if (!stringp(how[0]))
    {
        write("You glare" + how[1] + ", your eyes aglow with " +
            "preternatural power.\n");
        allbb(" glares" + how[1] + ", " + POSTP +
        " eyes aglow with preternatural power.");
    }
    else
    {
        notify_fail("Vglare at whom?\n");
        if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
        {
            return 0;
        }

        targetbb(" glares" + how[1] + " at you, " + POSTP +
                 " eyes aglow with preternatural power.", oblist);
        actor("You glare" + how[1] + " at", oblist, ", your eyes " +
              "aglow with preternatural power.");
        all2actbb(" glares" + how[1] + " at", oblist, ", " + POSTP + 
            " eyes aglow with preternatural power.");
    }

    SOULDESC("glaring" + how[1]);
    return 1;
}

int vlaugh(string str)
{
    say("Deafening sound assaults your ears as " + QTNAME(this_player()) +
        " explodes in peals of maniacal laughter.\n");
    write("You explode into peals of maniacal laughter.\n");

    return 1;
}

int vlick(string str)
{
    object *oblist;
    object bite;

    notify_fail("Lick what?\n");
    if (!sizeof(oblist = parse_this(str, "[the] %l")))
    {
        if (!strlen(str) || (str == "fangs") || (str == "fang"))
        {
            write("You slowly lick a drop of blood from a fang.\n");
            allbb(" slowly licks a drop of blood from one of " +
                  POS(this_player()) + " fangs.");
            return 1;
        }

        if (str == "mouth")
        {
            write("You slowly lick a drop of blood from the corner " +
                  "of your mouth.\n");
            allbb(" slowly licks a drop of blood from the corner of " +
                  POS(this_player()) + " mouth.");
            return 1;
        }

        return 0;
    }
   
    if (sizeof(oblist) > 1)
    {
        notify_fail("Not even your tongue is dextrous enough to " +
            "lick more than one neck!\n");
        return 0;
    }

    target(" licks your neck slowly and sensuously.", oblist);
    actor("You lick", oblist, "'s neck slowly and sensuously.");
    all2actbb(" licks", oblist, "'s neck slowly and sensuously.");

    if (bite = present("_vamp_bite_mark", oblist[0]))
    {
        oblist[0]->catch_tell("The puncture wounds on your neck close and " +
            "heal instantly, leaving not even a bruise!\n");
        write("The puncture wounds on " + POS(oblist[0]) + " neck close and " +
            "heal instantly, leaving not even a bruise!\n");
        bite->remove_object();
    }
        
    return 1;
}

int vgrin(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "", 0);

    if (!stringp(how[0]))
    {
        write("You grin" + how[1] + ", biting into your bottom lip " +
              "with your fangs.\n");
        allbb(" grins" + how[1] + ", biting into " + POSTP +
              " bottom lip with " + POSTP + " fangs.");
    }
    else
    {
        notify_fail("Grin at whom?\n");
        if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
        {
            return 0;
        }

        targetbb(" grins" + how[1] + " at you, biting into " + POSTP +
                 " bottom lip with " + POSTP + " fangs.", oblist);
        actor("You grin" + how[1] + " at", oblist, ", biting into " +
              "your bottom lip with your fangs.");
        all2actbb(" grins" + how[1] + " at", oblist, ", biting into " +
                  POSTP + " bottom lip with " + POSTP + " fangs.");
    }

    SOULDESC("grinning" + how[1]);
    return 1;
}

int vkiss(string str)
{
    mixed *oblist;
    string his_her;
    string location;

    if (!strlen(str))
    {
        notify_fail("Vkiss whom?\n");
        return 0;
    }

    if (parse_command(str, all_inventory(environment(this_player())),
        "[the] %l [on] [the] %s", oblist, location))
    {
        oblist = NORMAL_ACCESS(oblist - ({ this_player() }), 0, 0);
        oblist = check_block_action(oblist, ACTION_CONTACT);
    }
    else
    {
        oblist = parse_this(str, "[the] %l");
    }

    if (!sizeof(oblist))
    {
        notify_fail("Vkiss whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("Be more specific!  You can only kiss one at a time.\n");
        return 1;
    }

    if (!strlen(location) || (location == "lips") || (location == "mouth"))
    {
        actor("You kiss", oblist, " gently, letting a droplet of blood " +
              "trickle onto " + POS(oblist[0]) + " lips.");
        target(" kisses you gently....  You feel a drop of blood " +
               "trickle onto your your lips.", oblist);
        all2actbb(" kisses", oblist, " gently, letting a drop of blood " +
              "trickle onto " + POS(oblist[0]) + " lips.");
        return 1;
    }

    switch (location)
    {
        case "hand":
            his_her = POS(oblist[0]);

            target(" gazes deep into your eyes, and gently kisses your hand.",
                oblist);
            actor("You gaze deep into", oblist,"'s eyes, and gently kiss "+
                his_her + " hand.");
            all2actbb(" gazes", oblist," deep in the eyes, and kisses "+
                his_her + " hand.");
            return 1;

        default:
            notify_fail("Vkiss " + oblist[0]->query_the_name(this_player()) +
                " where?\n");
            return 0;
    }

    return 1;
}

int vlook(string str)
{
    object *oblist;
    string his_her;

    if (!strlen(str))
    {
        write("You look around the room with utter disbelief written over " +
              "your face.\n");
        allbb(" looks around the room with utter disbelief written on " +
              POSTP+" face.");

        return 1;
    }

    notify_fail("Vlook at whom?\n");
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        return 0;
    }

    targetbb(" looks at you with utter disbelief written on " +
             POSTP + " undead face.", oblist);
    actor("You look at", oblist, " with utter disbelief written on your "+
          "face.");
    all2actbb(" looks at", oblist, " with utter disbelief written on "+
              POSTP+" undead face.");

    return 1;
}

int vnod(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "respectfully", 0);


    if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
    {
        notify_fail("Vnod [how] at whom?\n");
        return 0;
    }

    target(" nods" + how[1] + " at you in acknowledgement.", oblist);
    actor("You nod" + how[1] + " at", oblist, " in acknowledgement.");
    all2actbb(" nods" + how[1] + " at", oblist, " in acknowledgement.");

    SOULDESC("nodding" + how[1]);

    return 1;
}

int vyawn(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "", 0);

    if (!stringp(how[0]))
    {
        write("You yawn" + how[1] + ", flashing your beautiful " +
              "white fangs.\n");
        allbb(" yawns" + how[1] + ", flashing " + POSTP +
              " beautiful white fangs.");
    }
    else
    {
        notify_fail("Yawn how?\n");
        if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
        {
            return 0;
        }

        targetbb(" yawns" + how[1] + " at you, flashing " + POSTP +
                 " beautiful white fangs.", oblist);
        actor("You yawn" + how[1] + " at", oblist,
              ", flashing your beautiful white fangs.");
        all2actbb(" yawns" + how[1] + " at", oblist, ", flashing " +
                  POSTP + " beautiful white fangs.");
    }

    SOULDESC("yawning" + how[1]);
    return 1;
}

int vsmile(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "charmingly", 0);

    if (!stringp(how[0]))
    {
        write("You smile" + how[1] + ", revealing two white " +
              "pearlescent fangs.\n");
        allbb(" smiles" + how[1] + ", revealing two white " +
              "pearlescent fangs.");
    }
    else
    {
        notify_fail("Smile at whom?\n");
        if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
        {
            return 0;
        }

        targetbb(" smiles" + how[1] + " at you, revealing two " +
                 "white, pearlescent fangs.", oblist);
        actor("You smile" + how[1] + " at", oblist, ", revealing " +
              "two white, pearlescent fangs.");
        all2actbb(" smiles" + how[1] + " at", oblist, ", revealing " +
                  "two white, pearlescent fangs.");
    }

    SOULDESC("smiling" + how[1]);
    return 1;
}

int vsmirk(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "", 0);

    if (!stringp(how[0]))
    {
        write("You smirk" + how[1] + ", revealing a razor-sharp fang.\n");
        allbb(" smirks" + how[1] + ", revealing a razor-sharp fang.");
    }
    else
    {
        notify_fail("Vsmirk at whom?\n");
        if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
        {
            return 0;
        }

        targetbb(" smirks" + how[1] + " at you, revealing a " +
                 "razor-sharp fang.", oblist);
        actor("You smirk"  + how[1] + " at", oblist, ", revealing " +
              "a razor-sharp fang.");
        all2actbb(" smirks" + how[1] + " at", oblist, ", revealing " +
                  "a razor-sharp fang.");
    }

    SOULDESC("smirking" + how[1]);
    return 1;
}

int vsweat(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    write("You break out in a blood-sweat.\n");
    allbb(" breaks out in a light sweat, small droplets of blood " +
          "beading on " + POSTP + " forehead.");
    return 1;
}

int vtear(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    write("A single blood red tear runs down your cheek.\n");
    allbb(" cries a single blood red tear.");

    return 1;
}
