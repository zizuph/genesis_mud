/* vamp_soul.c created by Shiva@Genesis 8/01/95
 * This is the vampire guild cmdsoul.  A few emotes
 * taken from Mylos' vampyr guild.
 *
 * Reused for the new Vampire guild. Nerull 2021
 */
inherit "/lib/commands";

#pragma save_binary
#pragma no_clone
#pragma strict_types

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
#define POSSTP        (this_player()->query_possessive())
#define PROTP        (this_player()->query_pronoun())
#define OBJTP        (this_player()->query_objective()
#define CQV          capitalize(query_verb())
#define TP           this_player()

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

public string query_eyes_desc(object player)
{
    string desc=player->query_eyes();
    if (!desc)
    {
        return "eyes";
    }
    return desc+(player->query_eyes_number()==1 ? " eye" : " eyes");
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

int burp(string str)
{
    write("Your undead body is no longer effective at burping.\n");
    return 1;
}

int fart(string str)
{
    write("Your undead body is no longer effective at farting.\n");
    return 1;
}

public int
valign(string str)
{
    object *oblist;

    if (!strlen(str) ||
        !sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail(CQV + " whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can only align your breath with one prey at a time.\n");
        return 1;
    }

    target(" stares deeply into your eyes, and after a moment you notice "+
        "that "+ POSSTP + " breaths are aligned perfectly to the timing "+
        "of your heartbeats.",oblist);
    
    write("You start deeply into the eyes of "+
        oblist[0]->query_the_name(this_player()) + 
        " and breathe in perfect timing to "+POSS(oblist[0])+
        " heartbeats.\n");
    all2actbb(" stares deeply into", oblist,"'s eyes.");

    return 1;

}


int vbeam(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    write("You beam with malicious delight.\n");
    allbb(" beams with malicious delight.");

    return 1;
}

int vblink(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    write("You blink with feigned surprise.\n");
    allbb(" blinks with feigned surprise.");

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
        allbb(" opens " + POSSTP + " mouth, letting a drop of blood " +
              "spill onto the " + floor + ".");

        return 1;
    }

    if (sizeof(oblist = parse_this(str, "[on] / [onto] [the] %l")) != 1)
    {
        notify_fail("Drip blood where?\n");
        return 0;
    }

    targetbb(" opens " + POSSTP + " mouth slightly, letting a drop "+
             "of blood spill onto you.", oblist);
    actor("You open your mouth near", oblist,", letting a drop "+
          "of blood spill onto " + OBJ(oblist[0]) + ".");
    all2actbb(" opens " + POSSTP + " mouth slightly, letting a drop "+
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
            LANG_POSS(oblist[0]->query_the_name(this_player())) + " " +
                query_eyes_desc(oblist[0])+" and bow with preternatural "+
                "grace.\n");
        targetbb(" gazes deep into your eyes and bows with preternatural " 
        +
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

    target(" steps behind you, and you can feel " + POSSTP +
           " hot breath on your neck.", oblist);
    actor("You step behind", oblist, " and breathe on " + POSS(oblist[0]) +
          " neck.");
    all2actbb(" steps behind", oblist, " and lingers behind " +
              OBJ(oblist[0]) + ", examining " + POSS(oblist[0]) + " neck.");

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

    target(" bends to gently kiss your neck, and brushes " + POSSTP +
           " fangs against your neck.", oblist);
    write("You bend to gently kiss " + 
        LANG_POSS(oblist[0]->query_the_name(this_player())) + 
        " neck and brush your fangs against " + POSS(oblist[0]) + " skin.\n");
    tell_others(QCTNAME(this_player()) + " bends and gently kisses " +
        QTPNAME(oblist[0]) + " neck.\n", ({ this_player(), oblist[0] }));

    return 1;
}

int
vburn(string str)
{
    string eyes=query_eyes_desc(TP);
    string burn=(TP->query_eyes_number()==1 ? 
        " burns" : " burn");
    
    write("Your "+eyes+burn+" like the fire of a hundred "+
        "dancing torches.\n");
    
    allbb("'s "+eyes+burn+" like the fire of a hundred dancing torches.");
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
 
    target(" runs " + POSSTP + " long fingernails along your shoulder "+
           "and neck.", oblist);
    actor("You run your fingernails down", oblist,"'s shoulder and neck.");
    all2actbb(" runs " + POSSTP + " long fingernails down", oblist, "'s "+
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
        allbb(" chuckles softly, a sneer forming on " + POSSTP +
              " face.");
        return 1;
    }

    notify_fail(CQV+" at whom?\n");
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        return 0;
    }

    actor("You chuckle softly at", oblist, ", a sneer forming on your " +
          "face.");
    targetbb(" chuckles softly at you, a sneer forming on " + POSSTP +
             " face.", oblist);
    all2actbb(" chuckles softly at", oblist, ", a sneer forming on " +
              POSSTP + " face.");

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
        allbb(" tightly clenches " + POSSTP + " fist, barely able " +
              "to control " + POSSTP + " anger.");

        return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[my] [fist] [at] [the] %l")))
    {
        notify_fail("Clench your fist at whom?\n");
        return 0;
    }

    target(" tightly clenches " + POSSTP + " fist, barely able " +
           "to control " + POSSTP + " anger and hatred for you.", oblist);
    actor("You tightly clench your fist, barely able to control " +
          "your anger and hatred for", oblist, ".");
    all2actbb(" tightly clenches " + POSSTP + " fist, barely able " +
              "to control " + POSSTP + " anger and hatred for", oblist,
              ".");

    return 1;
}

public int
vclose(string str)
{
    object *oblist;

    if (!strlen(str) ||
        !sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail(CQV + " whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can't move close to many people at once.\n");
        return 1;
    }

    target(" moves uncomfortably close to you, within "+
        POSSTP + " arms reach.", oblist);
    write("You move with arms reach of "+
        oblist[0]->query_the_name(this_player())+".\n");
    all2actbb(" moves with arms reach of", oblist, ".");
    return 1;

}


int
vconsider(string str)
{
    object *oblist;

    if (!strlen(str))
    {
        write("You consider your options.\n");
        allbb(" considers " + POSSTP + " options.");
        return 1;
    }

    if (!sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail("Consider whom?\n");
        return 0;
    }

    targetbb(" looks at you carefully, considering " + POSSTP +
             " options.", oblist);
    actor("You look carefully at", oblist, " considering your options.");
    all2actbb(" looks carefully at", oblist, " and considers " +
              POSSTP + " options.");

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
        notify_fail(CQV + " before whom?\n");
        return 0;
    }

    if (sizeof(oblist) == 1)
    {
        write("You gaze deep into " + 
            LANG_POSS(oblist[0]->query_the_name(this_player())) + " "+
            query_eyes_desc(oblist[0])+
            " and curtsey with preternatural grace.\n");
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
        notify_fail(CQV + " with whom?\n");
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
        target(" takes you in " + POSSTP + " arms and leads you in an " +
            "elegant dance.\nYou feel an extraordinary lightness in your " +
            "body, as if you might float away if not for " + 
            LANG_POSS(this_player()->query_the_name(ob)) + " grasp.  " +
            "Without a thought, you find yourself moving in perfect sync " +
            "with " + POSSTP + " steps, floating back and forth with " +
            "absolute poise and twirling with rapturous abandon.", oblist);
        all2actbb(" takes", oblist, " in " + POSSTP + " arms and leads " +
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

int vdistant(string str)
{
    write("Your gaze becomes distant and unfocused, with all of your "+
        "attention focused inwards.\n");
    allbb("'s gaze becomes distant and unfocused, as if all of "+
    POSSTP+" attention has turned inwards.");
    return 1;
}

int vdismiss(string str)
{
    object *oblist;

    if (!strlen(str) ||
        (!sizeof(oblist = parse_this(str, "[the] %l"))))
    {
        notify_fail("Dismiss whom from your sight?\n");
        return 0;
    }

    targetbb(" dismisses you in one succinct gesture, as if whisking " +
        "a fly from "+POSSTP+" sight.", oblist);
    actor("You dismiss", oblist, 
        " in one succinct gesture, as if whisking flies from "+
        "your sight.");
    all2actbb(" dismisses",oblist," in one succinct gesture, as if "+
        "whisking a fly from "+POSSTP+" sight.");
    return 1;
}

int vecstasy(string str)
{
    object *oblist;

    if (!strlen(str) ||
        (sizeof(oblist = parse_this(str, "[over] [the] %l")) != 1))
    {
        notify_fail("Go into ecstasy over whom?\n");
        return 0;
    }

    string eyes=query_eyes_desc(TP);

    targetbb(" closes " + POSSTP + " "+eyes+" in ecstasy, savoring the " +
        "taste of your blood.", oblist);
    actor("You close your "+eyes+" in ecstasy, savoring the taste of",
        oblist, "'s blood.");
    tell_others(QCTNAME(this_player()) + " closes " + POSSTP +
        " "+eyes+" in ecstasy, savoring the taste of " + 
        QTPNAME(oblist[0]) + " blood.\n", ({ this_player(), oblist[0] }));

    return 1;
}


int
ventrance(string str)
{
    object *oblist, *tmp;

    if (!strlen(str) || sizeof(oblist = parse_this(str, "[the] %l")) != 1)
    {
        notify_fail(CQV + " whom?\n");
        return 0;
    }

    targetbb(" gazes deep into your eyes.  You find yourself transfixed by " +
        "the strange beauty of " + POSSTP + " eyes--the mysterious " +
        "luminescence of " + POSSTP + " irises contrasting the profound " +
        "blackness of " + POSSTP + " pupils.  Lost in " + POSSTP +
        " entrancing gaze, blissful hours pass, until " + PROTP + " turns " +
        "aside " + POSSTP + " gaze.  You regain your faculties and realize " +
        "that only a moment has passed.", oblist);
    actor("You turn your entrancing gaze toward", oblist, ".");

    all2actbb(" gazes deep into", oblist, "'s eyes.  A serene expression " +
        "passes over " +  oblist[0]->query_possessive() + " face, as if " +
        "lost in a blissful daydream.");

    /* Would prefer to make this all one call to all2actbb(), but the
     * function doesn't allow me to use QCTNAME :-/.  Until all2actbb()
     * takes VBFCs, I'll have to do the messages separately.
     */
    tell_others(QCTNAME(this_player()) + " turns aside " + POSSTP +
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
        allbb(" bares " + POSSTP + " fangs.");
        return 1;
    }

    notify_fail("Bare thy fangs at whom?\n");
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        return 0;
    }

    targetbb(" bares " + POSSTP + " fangs at you in anticipation " +
             "of your blood.", oblist);
    actor("You bare your fangs at", oblist, " in anticipation of "+
          "fresh blood.");
    all2actbb(" bares " + POSSTP + " fangs at", oblist,
              " in anticipation of fresh blood.");

    return 1;
}

int vfrown(string str)
{
    string eyes=query_eyes_desc(TP);
    write("You narrow your "+eyes+" and frown, a deep melancholy "+
    "overtaking your features.\n");
    allbb(" narrows " + POSSTP + " "+eyes+" and frowns, a deep " +
    "melancholy overtaking " + POSSTP + " features.");
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
             POSSTP + " eyes, as the rays of the sun are cast into the room.");

        return 1;
    }

    notify_fail(CQV+" at the sun?\n");
    return 0;
}


//////////////////////////////////
int vglare(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "inspectingly", 0);

    string eyes=query_eyes_desc(TP);
    
    if (!stringp(how[0]))
    {
        write("You glare" + how[1] + ", your "+eyes+" aglow with " +
            "preternatural power.\n");
        allbb(" glares" + how[1] + ", " + POSSTP +
        " "+eyes+" aglow with preternatural power.");
    }
    else
    {
        notify_fail(CQV + " at whom?\n");
        if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
        {
            return 0;
        }

        targetbb(" glares" + how[1] + " at you, " + POSSTP +
                 " "+eyes+" aglow with preternatural power.", oblist);
        actor("You glare" + how[1] + " at", oblist, ", your "+eyes+
              " aglow with preternatural power.");
        all2actbb(" glares" + how[1] + " at", oblist, ", " + POSSTP + 
            " "+eyes+" aglow with preternatural power.");
    }

    SOULDESC("glaring" + how[1]);
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
           POSSTP + " eyes.", oblist);
    actor("You glower at", oblist, ", the rage clearly visible in your "+
          "eyes.");
    all2actbb(" glowers angrily at", oblist);

    return 1;
}


/////////////////////////////////////////
int vgrin(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "charmingly", 0);

    if (!stringp(how[0]))
    {
        write("You grin" + how[1] + ", biting into your bottom lip " +
              "with your fangs.\n");
        allbb(" grins" + how[1] + ", biting into " + POSSTP +
              " bottom lip with " + POSSTP + " fangs.");
    }
    else
    {
        notify_fail("Grin at whom?\n");
        if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
        {
            return 0;
        }

        targetbb(" grins" + how[1] + " at you, biting into " + POSSTP +
                 " bottom lip with " + POSSTP + " fangs.", oblist);
        actor("You grin" + how[1] + " at", oblist, ", biting into " +
              "your bottom lip with your fangs.");
        all2actbb(" grins" + how[1] + " at", oblist, ", biting into " +
                  POSSTP + " bottom lip with " + POSSTP + " fangs.");
    }

    SOULDESC("grinning" + how[1]);
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


///////////////////////////////////////////
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
        notify_fail(CQV + " whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        write("You can't manage to get your arms around that " +
            "many people.\n");
        return 1;
    }

    target(" enfolds you in " + POSSTP + " arms, holding you tightly in " +
        POSSTP + " embrace.  " + capitalize(POSSTP) + " body is as cold and unyielding " +
        "as stone; only the slow, soothing beating of " + POSSTP + " heart " +
        "reminds you that " + PROTP + " isn't a statue of marble.", oblist);
    write("You take " + oblist[0]->query_the_name(this_player()) + 
        " in your arms and hold " + OBJ(oblist[0]) + " tightly in your " +
        "embrace.\n");
    all2actbb(" takes", oblist, " in " + POSSTP + " arms, holding " +
        OBJ(oblist[0]) + " tightly in " + POSSTP + " embrace.");

    return 1;

}

int vkiss(string str)
{
    mixed *oblist;
    string his_her;
    string location;

    notify_fail(CQV + " whom?\n");
    if (!strlen(str))
    {
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
              "trickle onto " + POSS(oblist[0]) + " lips.");
        target(" kisses you gently....  You feel a drop of blood " +
               "trickle onto your lips.", oblist);
        all2actbb(" kisses", oblist, " gently, letting a drop of blood " +
              "trickle onto " + POSS(oblist[0]) + " lips.");
        return 1;
    }

    switch (location)
    {
        case "hand":
            his_her = POSS(oblist[0]);

            target(" gazes deep into your eyes, and gently kisses your hand.",
                oblist);
            actor("You gaze deep into", oblist,"'s eyes, and gently kiss "+
                his_her + " hand.");
            all2actbb(" gazes", oblist," deep in the eyes, and kisses "+
                his_her + " hand.");
            return 1;

        default:
            notify_fail(CQV + oblist[0]->query_the_name(this_player()) + 
                " where?\n");
            return 0;
    }

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
                  POSS(this_player()) + " fangs.");
            return 1;
        }

        if (str == "mouth")
        {
            write("You slowly lick a drop of blood from the corner " +
                  "of your mouth.\n");
            allbb(" slowly licks a drop of blood from the corner of " +
                  POSS(this_player()) + " mouth.");
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

    if (VAMPIRES_MASTER->is_lay_vampires(TP->query_name()) == 0)
    {
        return 1;
    }
    
    int neck=oblist[0]->query_id_for_hitloc_name("head");
    int tasted=0;
    
    if (neck>0 && oblist[0]->query_hitloc_bleeding(neck))
    {
        write("The puncture wounds on " + POSS(oblist[0]) + " neck close and " +
            "heal instantly, leaving not even a bruise!\n");
        oblist[0]->heal_wound(neck);
        tasted=1;
    }
    if (oblist[0]->query_hp()*4/3<oblist[0]->query_max_hp())
    {
        tasted=1;
    }
    if (tasted && !IS_WIZ(oblist[0]) && !oblist[0]->query_npc())
    {
        if (member_array(oblist[0]->query_real_name(),
            TP->query_tasted_blood())==-1)
        {
            TP->set_tasted_blood(TP->query_tasted_blood()+
                ({ oblist[0]->query_real_name()}));
            write("You let the delight of the new taste linger on your "+
                "lips.\n");
        }
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
              POSSTP+" face.");

        return 1;
    }

    notify_fail(CQV + " at whom?\n");
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        return 0;
    }

    targetbb(" looks at you with utter disbelief written on " +
             POSSTP + " undead face.", oblist);
    actor("You look at", oblist, " with utter disbelief written on your "+
          "face.");
    all2actbb(" looks at", oblist, " with utter disbelief written on "+
              POSSTP+" undead face.");

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
vmelancholy(string str)
{
    write("You frown, your face becoming the very image of melancholy.\n");
    allbb(" frowns, "+POSSTP+" face becoming the very image of "+
        "melancholy.");

    return 1;
}


public int
vnarrow(string str)
{
    object *oblist;
  
    string eyes=query_eyes_desc(TP);
  
    if (!strlen(str))
    {
        write("You narrow your "+eyes+" in contemplation.\n");
        allbb(" narrows " + POSSTP + " "+eyes+" in contemplation.");
        return 1;
    }
  
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        notify_fail("Narrow your eyes at whom?\n");
        return 0;
    }
  
    targetbb(" narrows " + POSSTP + " "+eyes+" at you, deep in thought.",
             oblist);
    actor("You narrow your "+eyes+" at", oblist,", deep in thought.");
    all2actbb(" narrows " + POSSTP + " "+eyes+" at", oblist, ", deep " +
              "in thought.");
  
    return 1;
}

int vnod(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "respectfully", 0);


    if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
    {
        notify_fail(CQV+" [how] at whom?\n");
        return 0;
    }

    target(" nods" + how[1] + " at you in acknowledgement.", oblist);
    actor("You nod" + how[1] + " at", oblist, " in acknowledgement.");
    all2actbb(" nods" + how[1] + " at", oblist, " in acknowledgement.");

    SOULDESC("nodding" + how[1]);

    return 1;
}

public int
vpast(string str)
{
    notify_fail(CQV+" ?\n");
    if (stringp(str))
    {
        return 0;
    }
    
    write("You recall having seen this drama enacted in the past.\n");
    
    WATCHERS(TP)->catch_msg("You can't help but notice how calm "+
        QTNAME(TP)+" appears, as if "+PRO(TP)+" has seen this drama "+
        "enacted before in "+POSS(TP)+" past.\n");
    return 1;
}


public int
vpensive(string str)
{
    notify_fail(CQV+" how?\n");
    string *how = parse_adverb_with_space(str, "soberly", 0);
    if (!stringp(how[0]))
    {
        write("You become absorbed in your own thoughts,"+how[1]+
            " considering some troubling matter.\n");

        allbb(" becomes absorbed in "+POSSTP+" thoughts,"+how[1]+
        " considering some troubling matter.");    
        return 1;
    }
    return 0;
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
  
    his_her = POSS(oblist[0]);
  
    target(" stares at you, and you feel your soul laid bare by " +
           POSSTP + " intense stare.", oblist);
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
    allbb(" infuses " + POSSTP + " body with the power of the dark Gods.");
  
    return 1;
}

int vrecall(string str)
{
    object * targets=TP->query_available_scry_targets();
    if (!strlen(str))
    {
        write("You recall the taste of your various prey of the past.\n");
        if (sizeof(targets))
        {
            write("The " + (sizeof(targets)==1 ? "taste" : "tastes") + 
                " of " + COMPOSITE_LIVE(targets) +
                (sizeof(targets)==1 ? " is" : " are" ) +
                " still familiar to you.\n");
        }
    }
    else
    {
        object target;
        if (parse_command(str,targets,"%o",target))
        {
            TP->catch_msg("You focus on recalling the taste of "+
                QTNAME(target) + " on your lips.\n");
            string * names=TP->query_known_scries();
            names-=({ target->query_real_name() });
            names+=({ target->query_real_name() });
            TP->set_known_scries(names);
        }
        else
        {
            write("You try to recall the taste of that blood, but "+
                "cannot remember it.\n");
        }
    }
    allbb(" looks reminscent while licking " + POSSTP + " lips.\n");
    return 1;
}

int vrevel(string str)
{
    if (strlen(str))
    {
        return 0;
    }

    write("You revel in uninhibited triumph.\n");
    allbb(" revels in uninhibited triumph.");

    return 1;
}

int vrevere(string str)
{
    object *oblist;

    if (!strlen(str) ||
        !sizeof(oblist = parse_this(str, "[the] %l")))
    {
        notify_fail(CQV + " whom?\n");
        return 0;
    }

    if (sizeof(oblist) == 1)
    {
        target(" falls to " + POSSTP + " knees in total reverence to you.",
               oblist);
        actor("You fall to your knees in total reverence to", oblist);
        all2actbb(" falls to "+POSSTP+" knees in reverence towards", oblist);

        return 1;
    }

    return 0;
}

int vrise(string str)
{
    if (strlen(str)) return 0;

    write("You rise to your full height and power.\n");
    allbb(" rises to " + POSSTP + " full height and power.");

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

int vsadness(string str)
{
    string eyes=query_eyes_desc(TP);
    string close=TP->query_eyes_number()==1 ? " closes" : " close";
    write("You close your "+eyes+" for a moment, and a shuddering sob "+
    "wracks your entire body.\n");
    
    all("'s "+eyes+close+" for a moment, and a shuddering sob wracks "+
    POSSTP+" entire body.");
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
              POSSTP + " fangs.");

        return 1;
    }

    if (!sizeof(oblist = parse_this(str,  "[at] [the] %l")))
    {
        return 0;
    }

    target(" glances at you, absentmindedly scratching one of " +
           POSSTP + " fangs.\n", oblist);
    actor("You glance at", oblist, ", absentmindedly scratching one of "+
          "your fangs.");
    all2act(" glances at", oblist, ", absentmindedly scratching one of "+
            POSSTP + " fangs.");

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
            POSS(oblist[0]) + " feet.");

    return 1;
}

int
vshine(string str)
{
    write("Your skin seems to shine with a soft luminescence.\n");
    allbb("'s skin seems to shine with a soft luminescence.");
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
    string *how = parse_adverb_with_space(str, "slightly", 0);

    if (!stringp(how[0]))
    {
        write("You smirk" + how[1] + ", revealing a razor-sharp fang.\n");
        allbb(" smirks" + how[1] + ", revealing a razor-sharp fang.");
    }
    else
    {
        notify_fail(CQV+" at whom?\n");
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
          "beading on " + POSSTP + " forehead.");
    return 1;
}


int vtaste(string str)
{
    write("You inhale deeply while softening your vision, as you "+
        "taste blood in the air.\n");
        
    allbb(" inhales deeply while softening "+POSSTP+" vision, as "+
        "if "+PRO(TP)+" can taste something in the air.");

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

int vthoughtful(string str)
{
    string *how = parse_adverb_with_space(str, "thoughtfully", 0);
    
    write("You stroke your chin"+how[1]+", brooding over some matter.\n");
    
    allbb(" strokes "+POSSTP+" chin"+how[1]+", brooding over some "+
        "matter.");

    return 1;
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

int vtouched(string str)
{
    object * oblist;
    
    notify_fail(CQV+" at whom?\n");
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        return 0;
    }

    targetbb(" seems utterly touched by your show of affection.", oblist);
    actor("You seem utterly touched by",oblist,"'s show of affection.");
    all2actbb(" seems utterly touched by ", oblist, " show of affection.");
    return 1;
}

int vtrace(string str)
{
    object * oblist;
    
    notify_fail(CQV+" at whom?\n");
    if (!sizeof(oblist = parse_this(str, "[at] [the] %l")))
    {
        return 0;
    }

    if (sizeof(oblist)!=1)
    {
        write("You can only trace your finger along one neck at a "+
            "time.\n");
        return 1;
    }

    target(" traces a finger along the side of your neck, "+
        "sending a chill down into your heart.", oblist);
    actor("You trace a finger along the side of",oblist,"'s neck, "+
        "sending a chill down into "+POSS(oblist[0])+" heart.");
    all2actbb(" traces a finger along the side of", oblist, "'s neck."); 
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

int vyawn(string str)
{
    object *oblist;
    string *how = parse_adverb_with_space(str, "slightly", 0);

    if (!stringp(how[0]))
    {
        write("You yawn" + how[1] + ", flashing your beautiful " +
              "white fangs.\n");
        allbb(" yawns" + how[1] + ", flashing " + POSSTP +
              " beautiful white fangs.");
    }
    else
    {
        notify_fail("Yawn how?\n");
        if (!sizeof(oblist = parse_this(how[0], "[at] [the] %l")))
        {
            return 0;
        }

        targetbb(" yawns" + how[1] + " at you, flashing " + POSSTP +
                 " beautiful white fangs.", oblist);
        actor("You yawn" + how[1] + " at", oblist,
              ", flashing your beautiful white fangs.");
        all2actbb(" yawns" + how[1] + " at", oblist, ", flashing " +
                  POSSTP + " beautiful white fangs.");
    }

    SOULDESC("yawning" + how[1]);
    return 1;
}
