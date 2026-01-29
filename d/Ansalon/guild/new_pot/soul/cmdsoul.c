/*
 * Commandsoul for The Priests of Takhisis guild
 *
 * 7.7.2004 Milan Fixed runtimes with leftovers
 */

#pragma strict_types

inherit "/cmd/std/command_driver";
inherit "/d/Genesis/specials/abilities";
inherit "/d/Genesis/specials/guilds/lib/utility_functions";
inherit "/d/Genesis/specials/guilds/souls/spell_manager_soul";

inherit "/d/Ansalon/guild/new_pot/soul/help";
inherit "/d/Ansalon/guild/new_pot/soul/standing";

#include <wa_types.h>
#include <filter_funs.h>
#include <composite.h>
#include <macros.h>
#include <options.h>
#include <files.h>
#include <alignment.h>
#include <language.h>

#include "../guild.h"
#include "/d/Ansalon/common/defs.h"

mapping gEmotes = ([]);
mapping gLocs = ([]);

/* 
 * Function name: get_soul_id
 * Description:   Give a name for this soul
 * Returns:       string - the soul's id
 */
string
get_soul_id() 
{ 
    return GUILD_NAME + " soul"; 
}

/*
 * Function name: query_cmd_soul
 * Description:   identify this as a valid cmdsoul
 * Returns:       1
 */
int 
query_cmd_soul() 
{ 
    return 1; 
}

/*
 * Function name: query_cmdlist
 * Description:   Get the commands available on this soul and
 *                their corresponding function names.
 * Returns:       mapping - a mapping that maps command names
 *                          to function names.
 */
mapping
query_cmdlist()
{
    return ([
      /* Command name : Function name */
      "help"        : "do_help",
      "phelp"       : "do_help",

      // "battlemovements" : "battlemovements",

      "vitals"      : "vitals",
      "v"           : "vitals",

      "psay"        : "dsay",
      // "prayers"     : "prayers",
      "ptitle"      : "ptitle",

      "paccept"     : "paccept",
      "pannoyed"    : "pannoyed",

      "pbestow"     : "pbestow",

      "pchallenge"  : "pchallenge",
      "pclaim"      : "pclaim",
      "pclean"      : "pclean",
      "pconsider"   : "pconsider",
      "pcontemplate": "pcontemplate",
      "pcry"        : "pcry",

      "pdevout"     : "pdevout",
      "pdismiss"    : "pdismiss",
      "pdisplay"    : "pdisplay",
      "pdissect"    : "pdissect",
      "pdisturbed"  : "pdisturbed",
      
      "pfarewell"   : "pfarewell",
      "pflash"      : "pflash",

      "pglimmer"    : "pglimmer",
      "pgreet"      : "pgreet",
      "pguide"      : "pguide",

      "phymn"       : "phymn",

      "pinvoke"     : "pinvoke",

      "pkiss"       : "pkiss",
      "pknife"      : "pknife",

      "plaugh"      : "plaugh",
      "plist"       : "plist",

      "pmuse"       : "pmuse",

      "pnervous"    : "pnervous",
      "pnose"       : "pnose",

      "poffer"      : "poffer",

      "ppassion"    : "ppassion",
      "ppause"      : "ppause",
      "pplaneswalk"  : "pplaneswalk",
      "pponder"     : "pponder",
      "ppraise"     : "ppraise",
      "ppray"       : "ppray",

      "prage"       : "prage",
      "precognise"  : "precognise",

      "psacrifice"  : "psacrifice",
      "pscoff"      : "pscoff",
      "psmile"      : "psmile",

      "ptorture"    : "ptorture",
      "ptrim"       : "ptrim",

      "punimpressed": "punimpressed",

      "pwince"      : "pwince",
      "pwrinkle"    : "pwrinkle",

      // Casting and Spell Commands
      "prayers"       : "prayers",
      "pray"          : "pray",
      "prayereffects" :"list_prayer_effects",
    ]);
}

public mapping
query_ability_map(void)
{
    object gobj = present(MEDALLION_ID, this_player());

    if (!objectp(gobj))
	return ([]);

    return gobj->query_ability_map();
}

int
dsay(string str)
{
    return "/d/Ansalon/guild/dragonarmy/soul/dragonarmy_soul"->dsay(str);
}

/*
int
prayers(string str)
{
    return "/cmd/live/magic"->spells(str);
}
*/

int
ptitle(string str)
{
    string *arr, index;
    int x, size;
    mapping titles;
    
    if (member_array(this_player()->query_real_name(),
        GUILD_ADMIN->query_guild_council()) < 0)
        return 0;

    arr = ({ GUILD_TITLES[this_player()->query_priest_level()][
        this_player()->query_priest_sublevel() * 2 +
        (this_player()->query_gender() == G_FEMALE ? 1 : 0)] +
        " of Takhisis" });

    for (x = 0, titles = TITLES_COUNCIL ; x < 5 ; x++)
    {
        index = COUNCIL_TITLES[x];
        if (GUILD_ADMIN->query_council_seat(index) ==
            this_player()->query_real_name())
        {
            if (sizeof(titles[index]) && pointerp(titles[index][0]))
            {
                arr += titles[index][(this_player()->query_gender() == G_FEMALE ? 1 : 0)];
#ifdef 0
                if (stringp(titles[index][2][0]))
                    arr += titles[index][2];
#endif
            }
            else
                arr += titles[index];
        }
    }

    if (!str)
    {
        write("You may choose from the following titles: " +
            COMPOSITE_WORDS(arr) + "\n");
        return 1;
    }
    
    if ((x = member_array(lower_case(str), map(arr, lower_case))) < 0)
    {
        notify_fail("That is not a title you may choose from.\n");
        return 0;
    }
    
    if (x == 0)
        this_player()->remove_prop(POT_SPECIAL_TITLE);
    else
        this_player()->add_prop(POT_SPECIAL_TITLE, arr[x]);

    write("You will now be presented as " + arr[x] + ".\n");
    return 1;
}

/***
 *** Support functions
 ***/

int
filter_medallion(object m)
{
    return (m->id(MEDALLION_ID));
}

/*
 * Function name: pot_has_medallion
 * Description:   Checks if the priest has the medallion in his immediate
 *                inventory (that it is not in a pack)
 * Returns:       1 if the priest has the medallion, 0 otherwise
 */
int
pot_has_medallion()
{
    return !(!(sizeof(filter(all_inventory(this_player()),
        filter_medallion))));
}

/*
 * Function name: pot_wears_medallion
 * Description:   Checks if the priest is wearing the medallion
 * Returns:       1 if the priest wears the medallion, 0 otherwise
 */
int
pot_wears_medallion()
{
    object * m = filter(all_inventory(this_player()), filter_medallion);

    return (m[0]->query_worn());
}	

int
sort_pot(object a, object b)
{
    int t = b->query_priest_level() - a->query_priest_level();

    if (t < 0)
        return -1;
    else if (t > 0)
        return 1;
    else
    {
        t = b->query_priest_sublevel() - a->query_priest_sublevel();

        if (t < 0)
            return -1;
        else if (t > 0)
            return 1;
        else
            return 0;
    }
}

int
filter_corpse(object ob)
{
    return (function_exists("create_container", ob) == CORPSE_OBJECT);
}

int
filter_component_holder(object ob)
{
    return (ob->query_prop(CONT_I_HOLDS_COMPONENTS));
}

int
filter_sheathes(object ob)
{
    return (member_array("sheath", ob->query_names()) >= 0 ||
            member_array("scabbard", ob->query_names()) >= 0);
}

int
filter_pot(object who)
{
    if (!MEMBER(who))
    {
        return 0;
    }

    if (who == this_player())
    {
        return 1;
    }

    /* Wizards see everyone */
    if (this_player()->query_wiz_level())
    {
        return 1;
    }

    /* Invis wizards are not shown */
    if (who->query_wiz_level() && who->query_invis())
    {
        return 0;
    }

    /* Jr's are not shown */
    if (extract(who->query_real_name(), -2) == "jr")
    {
        return 0;
    }

    return 1;
}

/*
 * Function name: pot_online
 * Description:   Gets a list of online guild members
 */
object *
pot_online()
{
    object *list = users();
#ifdef STATUE_WHEN_LINKDEAD
#ifdef OWN_STATUE
    list += filter(all_inventory(find_object(OWN_STATUE))-list,
      &not() @ &->query_npc());
#endif OWN_STATUE
#endif STATUE_WHEN_LINKDEAD
    list -= ({ this_player() });
    return sort_array(filter(list, filter_pot), sort_pot);
}

mapping
debug()
{
    return gEmotes;
}

void
update_from_emote(string verb, int change)
{
    if (gEmotes[verb + ":" + TP->query_real_name()])
        if ((gEmotes[verb + ":" + TP->query_real_name()] + 10 +
            random(10)) > time())
            change -= random(50);

    gEmotes[verb + ":" + TP->query_real_name()] = time();
    TP->adjust_standing(change);
}

varargs void
do_dissect(object pl, object corpse, object knife, object paralyze, int round = 0)
{
    object leftover;
    mixed list;

    if (round <= 4 && !corpse)
    {
        pl->catch_tell("But the corpse is no corpse anylonger.\n");
        tell_room(QCTNAME(pl) + " stops performing " + HIS(pl) + " ritual.\n", pl);
        paralyze->remove_object();
        return;
    }

    list = corpse->query_leftover("heart");

    if (round <= 4 && (sizeof(list) < 3 || list[2] < 1))
    {
        pl->catch_tell("But the corpse has been robbed of its price.\n");
        tell_room(QCTNAME(pl) + " stops performing " + HIS(pl) + " ritual.\n", pl);
        paralyze->remove_object();
        return;
    }

    switch (round)
    {
        case 0:
            pl->catch_msg("You kneel over the " + corpse->short(pl) +
                " and begin to dissect it.\n");
            tell_room(environment(pl), QCTNAME(pl) + " kneels over " +
                "the " + corpse->short() + " with " + HIS(pl) +
                " " + knife->short() + " ready at hand.\n", pl);
            break;
        case 1:
            pl->catch_tell("You slowly make a long incision along " +
                "the chest.\n");
            tell_room(environment(pl), QCTNAME(pl) + " slowly makes " +
                "a long incision along the chest. You see the skin " +
                "open up, revealing blood-red flesh beneath it.\n", pl);
            break;
        case 2:
            pl->catch_msg("With a sharp stab with your " + knife->short() +
                " you break open the ribcage.\n");
            tell_room(environment(pl), "With a sharp stab of " + HIS(pl) +
                " " + knife->short() + ", " + HE(pl) + " breaks open the " +
                "ribcage with a sickening crunching sound.\n", pl);
             
            if (present("sheath", pl))
                present("sheath", pl)->do_sheathe(OB_NAME(knife));
             
            break;
        case 3:
            pl->catch_tell("You dig your hands into the still warm chest " +
                "and move the lungs to the side, searching for your prize.\n");
            tell_room(environment(pl), QCTNAME(pl) + " digs " + HIS(pl) +
                " hands into the opened chest of the corpse with an " +
                "expectant look on " + HIS(pl) + " face.\n", pl);
            break;
        case 4:
            pl->catch_tell("You grip the heart and pull it out of the " +
                "corpse, rising and showing the blood-dripping heart to " +
                "all.\n");
            tell_room(environment(pl), "A triumphant smile crosses " +
                QTNAME(pl) + "'s face as " + HE(pl) + " pulls something out " +
                "of the corpse. " + capitalize(HE(pl)) + " rises and holds " +
                "out a blood-dropping heart infront of you.\n", pl);

            setuid();
            seteuid(getuid());

            leftover = clone_object(list[0]);
            leftover->leftover_init(list[1], corpse->query_prop(CORPSE_S_RACE));
            leftover->move(pl, 0);

            if (--list[2] == 0)
                corpse->remove_leftover(list[1]);
            else
                corpse->set_leftover_list(list);

            break;
        case 5:
            paralyze->remove_object();
            pl->command("$smile bloodthirstily");
            update_from_emote("pdissect", RND_RANGE(20, 10));
            return;
        default:
            paralyze->remove_object();
            return;
    }

    round++;
    set_alarm(3.5 + (itof(random(3))), 0.0, &do_dissect(pl, corpse, knife, paralyze, round));
}

/***
 *** Emotes and commands, in alphabetical order
 ***/

/* Command and functionality removed with review 
int
battlemovements(string arg)
{
    int old_bm = TP->query_battlemovements();
    int new_bm;
    
    if (!arg)
        TP->set_battlemovements(!old_bm);
    else if (arg == "on" || arg == "yes")
        TP->set_battlemovements(1);
    else if (arg == "off" || arg == "no")
        TP->set_battlemovements(0);
    else
    {
        notify_fail("Battlemovements how?\n");
        return 0;
    }
    
    new_bm = TP->query_battlemovements();
   
    if (new_bm)
        write("You get ready to command battle movements.\n");
    else
        write("You stop commanding battle movements.\n");
    
    return 1;
}

*/

int
paccept(string arg)
{
    if (stringp(arg))
    {
        notify_fail("Paccept how?\n");
        return 0;
    }

    write("You close your eyes and exhale, preparing to accept your " +
        "punishment.\n");
    all(" closes " + HIS(TP) + " eyes and exhales, preparing to " +
        "accept " + HIS(TP) + " punishment.");

    update_from_emote(query_verb(), RND_RANGE(-100, 50));
        
    return 1;
}

int
pannoyed(string arg)
{
    object *oblist;

    if (!arg || !(oblist = parse_this(arg, "[about] [the] %i")))
        oblist = filter(all_inventory(TP), filter_component_holder);

    oblist = filter(oblist, filter_component_holder);

    if (!sizeof(oblist))
    {
        notify_fail("To be annoyed about the shortcomings of a " +
            "component pouch, one would obviously be needed.\n");
        return 0;
    }
    
    oblist = ({ oblist[0] });
    
    write("You discard " + LANG_ADDART(LANG_SHORT(oblist[0])) + " and " +
        "mutter something about inadequate quality.\n");
    say("With annoyance in " + HIS(TP) + " eyes, " + QTNAME(TP) + 
        " discards " + LANG_ADDART(LANG_SHORT(oblist[0])) + " containing " +
        "components and mutters something about inadequate quality.\n");
    
    return 1;
}

int
pbestow(string arg)
{
    string *how;
    object *oblist;
    int size;
    
    if (!arg)
    {
        notify_fail("Bestow a blessing to whom?\n");
        return 0;
    }
    
    how = parse_adverb_with_space(arg, "approvingly", 0);
    oblist = parse_this(how[0], "[the] %l");
    
    if (!oblist || !sizeof(oblist))
    {
        notify_fail("Bestow a blessing to whom?\n");
        return 0;
    }
    
    actor("You glance" + how[1] + " at", oblist, ", bestowing the " +
        "Dark Queen's blessing upon " + (((size = sizeof(oblist))) > 1 ?
        "them" : HIM(oblist[0])) + ".");
    all2act(" glances" + how[1] + " at", oblist, ", bestowing the " +
        "Dark Queen's blessing upon " + (size > 1 ? "them" :
        HIM(oblist[0])) + ".");
    target(" glances" + how[1] + " at you, bestowing the Dark Queen's " +
        "blessing upon you.", oblist);

    return 1;
}

int
pchallenge(string arg)
{
    object *oblist;
    int size;

    if (!arg)
    {
        notify_fail("Challenge whom?\n");
        return 0;
    }
    
    oblist = parse_this(arg, "[the] %l");
    
    if (!oblist || !sizeof(oblist))
    {
        notify_fail("Challenge whom?\n");
        return 0;
    }
    
    actor("You stand defiantly before", oblist, ", challenging " +
        (((size = sizeof(oblist))) > 1 ? "them" : HIM(oblist[0])) +
        " in the name of Takhisis.");
    all2act(" stands defiantly before", oblist, ", challenging " +
        (size > 1 ? "them" : HIM(oblist[0])) + " in the name of " +
        "Takhisis.");
    target(" stands defiantly before you, challenging you in the " +
        "name of Takhisis.", oblist);

    update_from_emote(query_verb(), TP->query_standing() ?
        RND_RANGE(10, 5) : RND_RANGE(-10, 5));

    return 1;
}

int
pclaim(string arg)
{
    mixed oblist;

    if (!arg)
    {
        notify_fail("Pclaim who/what?\n");
        return 0;
    }

    oblist = parse_this(arg, "[the] %l");

    if (!sizeof(oblist))
    {
        int i;
        string odesc;

        if (!parse_command(arg, environment(this_player()),
            "[the] %i", oblist))
        {
            notify_fail("You find no " + arg + " here.\n");
            return 0;
        }

        i = (int)oblist[0];

        if (i == 0)
        {
            oblist = oblist[1..];
        }
        else if (i < 0)
        {
            oblist = slice_array(oblist,1,-i);
        }
        else
        {
            oblist = ({ oblist[i] });
        }

        odesc = COMPOSITE_DEAD(oblist);

        write("You claim " + odesc + " in the name of Takhisis, " +
            "Queen of Darkness.\n");

        all(" claims " + odesc + " in the name of Takhisis, " +
            "Queen of Darkness.");

        update_from_emote(query_verb(), RND_RANGE(5, 2));

        return 1;
    }

    actor("You claim", oblist, "'s soul" + (sizeof(oblist) > 1 ? "s" : "") +
        " in the name of Takhisis, Queen of Darkness.");
    all2act(" claims", oblist, "'s soul" + (sizeof(oblist) > 1 ? "s" : "") +
        " in the name of Takhisis, Queen of Darkness.");
    target(" claims your soul in the name of Takhisis, Queen of Darkness!",
        oblist);

    update_from_emote(query_verb(), RND_RANGE(5, 2));

    return 1;
}

int
pclean(string arg)
{
    object *oblist;

    if (!arg || !(oblist = parse_this(arg, "[the] %i ")))
    {
        notify_fail("Wipe your hands clean from what corpse?\n");
        return 0;
    }

    oblist = filter(oblist, filter_corpse);
    if (!oblist || !sizeof(oblist))
    {
        notify_fail("Wipe your hands clean from what corpse?\n");
        return 0;
    }
    
    actor("You pick up a piece of clothing from", oblist, " and " +
        "wipe your hands clean to then toss the torn garment " +
        "disdainfully to the ground.");
    all2actbb(" picks up a piece of clothing from", oblist, " and " +
        "wipes " + HIS(TP) + " bloodied hands clean to then toss " +
        "the torn garment disdainfully to the ground.");
   
    return 1;
}
    
int
pconsider(string arg)
{
    string *how, str;

    how = parse_adverb_with_space(arg, "carefully", 0);
    
    if (strlen(how[0]))
    {
        notify_fail("Pconsider how?\n");
        return 0;
    }

    write("You" + how[1] + " consider what sort of wickedness to " +
        "engage in next.\n");
    allbb(how[1] + " considers what sort of wickedness to engage " +
        "in next.");

    return 1;
}

int
pcontemplate(string arg)
{
    string *how, str;

    how = parse_adverb_with_space(arg, "silently", 0);

    if (strlen(how[0]))
    {
        notify_fail("Contemplate how?\n");
        return 0;
    }

    write("You tug thoughtfully on your black medallion as you" +
        how[1] + " contemplate the matter.\n");
    allbb(" tugs thoughtfully on " + HIS(TP) + " black medallion " +
        "while" + how[1] + " contemplating the matter.");

    return 1;
}

int
pcry(string arg)
{
    object *takh, *others;

    if (stringp(arg))
    {
        notify_fail("Cry what?\n");
        return 0;
    }

    others = FILTER_OTHER_LIVE(all_inventory(environment(TP)));
    takh = filter(others, &operator(==)("Dragonarmy") @
        &->query_guild_name_occ()) + filter(others,
        &operator(==)("Priests of Takhisis") @ &->query_guild_name_occ());
    others -= takh;
    
    write("You cry out to Takhisis, causing fear and chaos around you.\n");

    others->catch_msg(QCTNAME(TP) + " cries out to She of Many " +
        "Faces, filling your heart with fear and chaos.\n");
    takh->catch_msg(QCTNAME(TP) + " cries out to She of Many Faces, " +
        "filling your heart with " + (({"bloodlust",
        "vengeance", "hatred", "zeal"})[random(4)]) + ".\n");

    update_from_emote(query_verb(), TP->query_standing() ?
        RND_RANGE(10, 5) : RND_RANGE(-20, 10));

    return 1;
}

int
pdevout(string arg)
{
    object *oblist;
    string *how;
        
    how = parse_adverb_with_space(arg, "gleefully", 0);
        
    if (!strlen(how[0]))
    {
        write("You smile" + how[1] + ", knowing the depth of your " +
            "devotion to the Dark Queen.\n");
        allbb(" smiles" + how[1] + ", " + HIS(TP) + " eyes burning " + 
            "with devotion to the Dark Queen.");

        update_from_emote(query_verb(), TP->query_standing() ?
            RND_RANGE(10, 5) : RND_RANGE(-10, 5));

        return 1;
    }
    
    oblist = parse_this(how[0], "[at] [the] %l");
    
    if (!sizeof(oblist)) 
    {
        notify_fail("Show your devotion [how] at whom?\n");
        return 0;
    }
 
    actor("You smile" + how[1] + " at", oblist, ", knowing the depth of "+
        "your devotion to the Dark Queen.");
    all2actbb(" smiles" + how[1] + " at", oblist, ", eyes burning " +
        "with devotion to the Dark Queen.");
    targetbb(" smiles" + how[1] + " at you, eyes burning with devotion "+
        "to the Dark Queen.", oblist);

    update_from_emote(query_verb(), TP->query_standing() ?
        RND_RANGE(10, 5) : RND_RANGE(-10, 5));
        
    return 1;
}

int
pdismiss(string arg)
{
    object *oblist;
    string str;

    if (!stringp(arg))
    {
        notify_fail("Dismiss whom?\n");
    	return 0;
    }

    oblist = parse_this(arg, "[the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Dismiss whom?\n");
    	return 0;
    }

#ifdef 0
    str = " with a muttered 'Bah', and a wave of the hand.";
#else
    str = " with a slight wave of the hand.";
#endif
    actor("You dismiss", oblist, str);
    all2act(" dismisses", oblist, str);
    target(" dismisses you" + str, oblist);

    return 1;
}

int
pdisplay(string arg)
{
    object *oblist;

    if (!pot_has_medallion())
    {
        notify_fail("You must have your medallion accessible.\n");
        return 0;
    }

    if (!stringp(arg))
    {
        write("You hold out your black medallion, displaying that you " +
            "are a Priest of Takhisis, and not to be trifled with!\n");

        allbb(" holds out " + HIS(TP) + " black medallion, displaying that " +
            HE(TP) + " is a Priest of Takhisis, and not to be trifled with!");

        update_from_emote(query_verb(), TP->query_standing() ?
            RND_RANGE(20, 10) : RND_RANGE(-20, 10));

        return 1;
    }

    oblist = parse_this(arg, "[to] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Show your medallion to whom?\n");
        return 0;
    }

    actor("You thrust your black medallion before", oblist, ", displaying " +
        "that you are a Priest of Takhisis, and not to be trifled with!");

    all2actbb(" thrusts " + HIS(TP) + " black medallion before", oblist,
        ", displaying that " + HE(TP) + " is a Priest of Takhisis, and " +
        "not to be trifled with.");

    targetbb(" thrusts " + HIS(TP) + " black medallion before you, " +
        "displaying that " + HE(TP) + " is a Priest of Takhisis, and not " +
        "to be trifled with!", oblist);

    update_from_emote(query_verb(), TP->query_standing() ?
        RND_RANGE(20, 10) : RND_RANGE(-20, 10));

    return 1;
}

int
pdissect(string arg)
{
	mixed leftover;
    object paralyze, *oblist, *knives = filter(TP->query_weapon(-1), &operator(==)(W_KNIFE) @ &->query_wt());
    
    if (!arg)
    {
        notify_fail("Begin dissecting what?\n");
        return 0;
    }
    
    if (!sizeof(knives))
    {
        notify_fail("Surely you would not do that without a " +
            "cermonial knife?\n");
        return 0;
    }
    
    if (sizeof(knives) >= 2)
    {
        notify_fail("You would need atleast one hand free.\n");
        return 0;
    }
    
    oblist = parse_this(arg, "[the] %l");

    if (sizeof(oblist))
    {
        notify_fail((oblist[0])->query_The_name(TP) + " is not dead yet!\n");
        return 0;
    }

    oblist = parse_this(arg, "[the] %i");
    oblist = filter(oblist, filter_corpse);
    
    if (!sizeof(oblist))
    {
        notify_fail("You need a fresh corpse to begin with.\n");
        return 0;
    }
    
	leftover = oblist[0]->query_leftover("heart");
    if (sizeof(leftover) < 3 || leftover[2] < 1)
    {
        notify_fail("Somehow you doubt you would find an intact heart " +
            "in the corpse.\n");
        return 0;
    }

    setuid();
    seteuid(getuid());
    
    paralyze = clone_object("/std/paralyze");
    paralyze->set_remove_time(600);
    paralyze->set_fail_time("Not while performing a disection!\n");
    paralyze->move(TP, 1);

    do_dissect(TP, oblist[0], knives[0], paralyze);

    return 1;
}
    
int
pdisturbed(string arg)
{
    object *oblist;

    if(!arg)
    {
        notify_fail("Pdisturbed by whom?\n");
        return 0;
    }
   
    oblist = parse_this(arg, "[at] [the] %l");
    
    if (!sizeof(oblist))
    {
        notify_fail("Pdisturbed by whom?\n");
        return 0;
    }
        
    actor("You stop suddenly and turn towards", oblist, " who dared " +
        "disturb you.");
    all2actbb(" freezes suddenly and straightens " + HIS(TP) + " back. " +
        "Slowly " + HE(TP) + " turns towards", oblist, " with a piercing "+
        "gaze, obviously annoyed by the disturbance."); 
    targetbb(" freezes suddenly and straightens " + HIS(TP) + " back. " +
        "Slowly " + HE(TP) + " turns towards you, obviously annoyed by " +
        "the disturbance.", oblist);
        
    return 1;
}

int
pfarewell(string arg)
{
    object *oblist;
    string str;

    if(!arg)
    {
        notify_fail("Pfarewell to whom?\n");
        return 0;
    }

    oblist = parse_this(arg, "[to] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Pfarewell to whom?\n");
        return 0;
    }

    str = (sizeof(oblist) > 1 ? "them" : HIM(oblist[0]));

    actor("You bid", oblist, " farewell in the name of Takhisis, the " +
        "Queen of Darkness.");
    all2act(" bids", oblist, " farewell in the name of Takhisis, the " +
        "Queen of Darkness.");
    target(" bids you farewell in the name of Takhisis, the Queen of " +
        "Darkness.", oblist);

    return 1;
}

int
pflash(string arg)
{
    object *oblist;
    string *how, str;

    how = parse_adverb_with_space(arg, "angrily", 0);
    
    if (!strlen(how[0]))
    {
        write("You flash your eyes" + how[1] + ".\n");
        allbb(" flashes " + HIS(TP) + " eyes" + how[1] + ".\n");
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");
    
    if (!sizeof(oblist))
    {
        notify_fail("Flash your eyes [how] at whom?\n");
        return 0;
    }
    
    str = (sizeof(oblist) > 1 ? "them" : HIM(oblist[0]));
    actor("You flash your eyes" + how[1] + " at", oblist, ", giving " +
        str + " a smoldering look.");
    all2actbb(" flashes " + HIS(TP) + " eyes" + how[1] + " at", oblist,
        ", giving " + str + " a smoldering look.");
    targetbb(" flashes " + HIS(TP) + " eyes" + how[1] + " at you, " +
        "giving you a smoldering look.", oblist);
    
    return 1;
}

int
pglimmer(string arg)
{
    if (stringp(arg))
    {
        notify_fail("Pglimmer how?\n");
        return 0;
    }

    write("Your eyes glimmer as a dark plan begins to hatch in your " +
        "mind, like a dragon from its egg.\n");
    all("'s eyes glimmer, suggesting that a dark plan is hatching " +
        "in " + HIS(TP) + " mind, like a dragon from its egg.");

    return 1;
}

int
pgreet(string arg)
{
    object *oblist;
    string str;
    int x, size, goodies;

    if (!stringp(arg))
    {
        notify_fail("Greet whom?\n");
        return 0;
    }

    oblist = parse_this(arg, "[the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Greet whom?\n");
        return 0;
    }

    str = "Hail in the name of " + ({ "the Queen of Darkness", "Takhisis",
        "the Dark Temptress" })[random(3)] + "!";

    actor("You greet", oblist, ", saying: " + str);
    all2act(" greets", oblist, ", saying: " + str);
    target(" greets you, saying: " + str, oblist);

    for (x = 0, size = sizeof(oblist) ; x < size ; x++)
    {
        if (objectp(oblist[x]) && oblist[x]->query_alignment() >= ALIGN_NEUTRAL)
            goodies++;
    }

    if (TP->query_wiz_level())
        dump_array(oblist);
    
    if (goodies >= min(sizeof(oblist) / 2, 1))
        update_from_emote(query_verb(), RND_RANGE(-2, 5));
    else
        update_from_emote(query_verb(), RND_RANGE(10, 5));

    return 1;
}

int
pguide(string arg)
{
    object *oblist;
    string str;

    if(!arg)
    {
        notify_fail("Pguide to whom?\n");
        return 0;
    }

    oblist = parse_this(arg, "[to] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Pguide to whom?\n");
        return 0;
    }

    str = (sizeof(oblist) > 1 ? "them" : HIM(oblist[0]));

    actor("You bid", oblist, " farewell with the words: May the Dark " +
        "Queen guide your weapons in the slaughter of Her enemies.");
    all2act(" bids", oblist, " farewell with the words: May the Dark " +
        "Queen guide your weapons in the slaughter of Her enemies.");
    target(" bids you farewell with the words: May the Dark Queen " +
        "guide your weapons in the slaughter of Her enemies.", oblist);

    return 1;
}

int
phymn(string arg)
{
    if (stringp(arg))
    {
        notify_fail("Phymn how?\n");
        return 0;
    }

    write("In a soft haunting voice, you sing a hymn of praise to the " +
        "Queen of Darkness.\n");
    all(" sings, in a soft haunting voice, a hymn of praise to the " +
        "Queen of Darkness.");

    update_from_emote(query_verb(), TP->query_standing() ?
        RND_RANGE(20, 5) : RND_RANGE(-20, 5));

    return 1;
}

int
pinvoke(string arg)
{
    object *oblist;

    if (!arg)
    {
        notify_fail("Invoke desire in whose mind?\n");
        return 0;
    }
    
    oblist = parse_this(arg, "[the] %l");

    if (!oblist || !sizeof(oblist))
    {
        notify_fail("Invoke desire in whose mind?\n");
        return 0;
    }

    actor("You invoke the name of the Dark Temptress, filling",
        oblist, "'s mind with images of everything " +
        (sizeof(oblist) > 1 ? "they" : HE(oblist[0])) + " desires.");
    all2act(" invokes the name of the Dark Temptress in", oblist, ".");
    target(" invokes the name of the Dark Temptress and your mind " +
        "is filled with images of everything your heart desires.",
        oblist);

    update_from_emote(query_verb(), TP->query_standing() ?
        RND_RANGE(20, 10) : RND_RANGE(-8, 10));
    
    return 1;
}

int
pkiss(string arg)
{
    object *oblist, *robes;
    string *adjs;
    int x;
    
    if (!arg || !(oblist = parse_this(arg,
        "[the] 'sleeve' / 'hem' [of] %l [robe]")))
    {
        notify_fail("Kiss the sleeve or hem of whose robe?\n");
        return 0;
    }

    if (!sizeof(oblist))
    {
        notify_fail("Kiss the sleeve or hem of whose robe?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("It would be difficult to do so before several " +
            "people at once.\n");
        return 0;
    }

    robes = oblist[0]->query_clothing(TS_ROBE);
    if (!sizeof(robes))
        robes = oblist[0]->query_armour(TS_ROBE);
    if (!sizeof(robes))
    {
        notify_fail("But " + (oblist[0])->query_the_name(TP) +
            " is not wearing any robe.\n");
        return 0;
    }
    
    adjs = robes[0]->query_adj(-1);
    adjs -= ({ "worn", "unworn" });
    for (x = 0 ; x < sizeof(adjs) ; x++)
        adjs[x] = " " + adjs[x];
    if (sizeof(adjs) < 2)
        adjs = ({ "" }) + adjs;
        
    if (member_array("sleeve", explode(arg, " ")) >= 0)
    {
        actor("You bow your head and kneel respectfully before", oblist,
            ", kissing the fold of " + HIS(oblist[0]) +
            adjs[sizeof(adjs) - 2] + " lined sleeve.");
        all2actbb(" bows " + HIS(TP) + " head and kneels respectfully " +
            "before", oblist, ", kissing the fold of " + HIS(oblist[0]) +
            adjs[sizeof(adjs) - 2] + " lined sleeve.");
        target(" bows " + HIS(TP) + " head and kneels respectfully before " +
            "you, kissing the fold of your" + adjs[sizeof(adjs) - 2] +
            " lined sleeve.", oblist);
    }
    else
    {
        actor("You kneel before", oblist, " and bow down to the ground. " +
            "Reverently you lift the hem of " + HIS(oblist[0]) +
            adjs[sizeof(adjs) - 1] + " robe and kiss it.");
        all2actbb(" kneels before", oblist, " and bows down to the ground. " +
            "Reverently " + HE(TP) + " lifts the hem of " + HIS(oblist[0]) +
            adjs[sizeof(adjs) - 1] + " robe and kiss it.");
        target(" kneels before you and bow down to the ground. Reverently " +
            HE(TP) + " lifts the hem of your" + adjs[sizeof(adjs) - 1] +
            " robe and kiss it.", oblist);
    }
    
    return 1;
}

int
pknife(string arg)
{
    object *sheathes, *knives;
    string *adjs;
    int x, y, size, flag;
    
    sheathes = filter(all_inventory(TP), filter_sheathes);

    if (!sizeof(sheathes))
    {
        notify_fail("Obviously you would need a sheath.\n");
        return 0;
    }
    
    for (x = 0, size = sizeof(sheathes) ; x < size ; x++)
    {
        knives = filter(all_inventory(sheathes[x]),
            &operator(==)(W_KNIFE) @ &->query_wt());
        
        if (sizeof(knives))
        {
            if (knives[0]->move(TP))
            {
                write(capitalize(LANG_THESHORT(knives[0])) + " resists.\n");
            }
            else
            {
                adjs = knives[0]->query_adj(-1);
                adjs -= ({ "wielded", "unwielded" });
                for (y = 0 ; y < sizeof(adjs) ; y++)
                    adjs[y] = " " + adjs[y];
                if (sizeof(adjs) < 2)
                    adjs = ({ "" }) + adjs;
         
                write("With a fluent move you draw your " +
                    LANG_SHORT(knives[0]) + " from its sheath and with a black " +
                    "piece of cloth you clean fresh blood off the" +
                    adjs[sizeof(adjs) - 1] + " blade.\n");
                say("With a fluent move " + QTNAME(TP) + " draws " + HIS(TP) +
                    " " + LANG_SHORT(knives[0]) + " from its sheath and " +
                    "with a black piece of cloth " + HE(TP) + " cleans fresh " +
                    "blood off the" + adjs[sizeof(adjs) - 1] + " blade.\n");

                flag = 1;
                
                break;
            }
        }
    }
    
    if (!flag)
    {
        notify_fail("But there is no knife in any of your sheathes.\n");
        return 0;
    }
    
    return 1;
}

int
plaugh(string arg)
{
    if (stringp(arg))
    {
        notify_fail("Plaugh how?\n");
        return 0;
    }

    write("You throw your head back and laugh maniacally, your " +
        "faith in the Queen of Darkness evident.\n");
    all(" throws " + HIS(TP) + " head back and laughs maniacally, " +
        HIS(TP) + " faith in the Queen of Darkness evident.");

    update_from_emote(query_verb(), TP->query_standing() ?
        RND_RANGE(10, 5) : RND_RANGE(-10, 5));

    return 1;
}

int
plist(string arg)
{
    object *members;
    int i, sz;
    
    if (!stringp(arg))
    {
        notify_fail("List what? Members?\n");
        return 0;
    }

    if (arg != "members")
        return 0;

    members = pot_online();
    sz = sizeof(members);

    if (sz == 0)
    {
        write("There are no other Priests of Takhisis in the realms.\n");
        return 1;
    }
    else
    {
        write("There " + (sz > 1 ? "are" : "is") + " currently " +
            LANG_WNUM(sz) + " other Priest" + (sz > 1 ? "s" : "") +
            " of Takhisis in the realms:\n");

        for (i = 0; i < sz; i++)
        {
            string str;

            str = members[i]->query_name();
            str += " " + (members[i]->query_guild_family_name() &&
                !members[i]->query_guild_incognito_race() ?
                members[i]->query_title() :
                members[i]->query_guild_title_occ());
            if (GUILD_ADMIN->query_council_seat("leader") ==
                members[i]->query_real_name())
                str = "The favoured " + str;
            else if (member_array(members[i]->query_real_name(),
                GUILD_ADMIN->query_guild_council()) >= 0)
                str = "The respected " + str;

            if (members[i]->query_wiz_level())
                str = "The blessed " + str;
            if (!interactive(members[i]))
                str = "The unavailable " + str;

            write("  " + str + "\n");
        }

        return 1;
    }
}

int
pmuse(string arg)
{
    object *oblist;
    string *how, *races = ({ "human", "elf", "half-elf" });

    if (!arg)
    {
        notify_fail("Muse [how] over whose death?\n");
        return 0;
    }

    how = parse_adverb_with_space(arg, "quietly", 0);    
    oblist = parse_this(how[0], "[over] [the] [death] %l [death]");

    if (sizeof(oblist))
    {
        notify_fail((oblist[0])->query_The_name(TP) + " is not dead yet!\n");
        return 0;
    }

    oblist = parse_this(how[0], "[over] [the] [death] %i [death]");
    oblist = filter(oblist, filter_corpse);

    if (!sizeof(oblist))
    {
        notify_fail("Muse [how] over whose death?\n");
        return 0;
    }

    actor("You grin" + how[1] + " at", oblist, ", realising " +
        "your chance to gain prestige in the eyes of Takhisis.");
    all2actbb(" grins" + how[1] + " as " + HE(TP) + " muses " +
        "over the death of", oblist, ".");
    /* We cannot have a target for a nonliving */

    update_from_emote(query_verb(),
        member_array(oblist[0]->query_prop(CORPSE_S_RACE), races) >= 0 ?
        RND_RANGE(20, 10) : RND_RANGE(-150, 10));

    return 1;
}

int
pnervous(string arg)
{
    if (stringp(arg))
    {
        notify_fail("Pnervous how?\n");
        return 0;
    }

    write("You wonder nervously whether your actions will put you out " +
        "of favour with Takhisis.\n");
    all(" wonders nervously whether " + HIS(TP) + " actions will put " +
        HIM(TP) + " out of favour with " + HIS(TP) + " Goddess, the " +
        "Queen of Darkness.");

    update_from_emote(query_verb(), random(3) ?
        RND_RANGE(5, 5) : RND_RANGE(-20, 10));

    return 1;
}

int
pnose(string arg)
{
    if (stringp(arg))
    {
        notify_fail("Pnose how?\n");
        return 0;
    }

    write("You tap your nose in a surreptitious manner.\n");
    all(" taps " + HIS(TP) + " nose in a surreptitious manner.");

    return 1;
}

int
poffer(string arg)
{
    object *oblist, *robes;
    string *adjs;
    int x;
    
    if (!arg || !(oblist = parse_this(arg,
        "[the] 'sleeve / 'hem' [of] [your] [robe] [to] [be] [kissed] [by] %l")))
    {
        notify_fail("Offer the sleeve or hem of your robe to be " +
            "kissed by whom?\n");
        return 0;
    }

    if (!sizeof(oblist))
    {
        notify_fail("Offer the sleeve or hem of your robe to be " +
            "kissed by whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("It would be difficult to do so before several " +
            "people at once.\n");
        return 0;
    }

    robes = TP->query_clothing(TS_ROBE);
    if (!sizeof(robes))
        robes = TP->query_armour(TS_ROBE);
    if (!sizeof(robes))
    {
        notify_fail("But your are not wearing any robe.\n");
        return 0;
    }
    
    adjs = robes[0]->query_adj(-1);
    adjs -= ({ "worn", "unworn" });
    for (x = 0 ; x < sizeof(adjs) ; x++)
        adjs[x] = " " + adjs[x];
    if (sizeof(adjs) < 2)
        adjs = ({ "" }) + adjs;
        
    if (member_array("sleeve", explode(arg, " ")) >= 0)
    {
        actor("You offer the fold of your" + adjs[sizeof(adjs) - 2] +
            " lined sleeve for", oblist, " to kiss.");
        all2actbb(" offers the fold of " + HIS(TP) +
            adjs[sizeof(adjs) - 2] + " lined sleeve for", oblist,
            " to kiss.");
        target(" offers the fold of " + HIS(TP) +
            adjs[sizeof(adjs) - 2] + " lined sleeve for you to kiss.",
            oblist);
    }
    else
    {
        actor("You put one foot before the other, offering the " +
            "hem of your" + adjs[sizeof(adjs) - 1] + " robe for",
            oblist, " to kiss.");
        all2actbb(" puts one foot before the other, offering the " +
            "hem of " + HIS(TP) + adjs[sizeof(adjs) - 1] +
            " robe for", oblist, " to kiss.");
        target(" puts one foot before the other, offering the hem of " +
            HIS(TP) + adjs[sizeof(adjs) - 1] + " robe for you " +
            "to kiss.", oblist);
    }
    
    return 1;
}

int
ppassion(string arg)
{
    object *oblist;
    
    if (!arg)
    {
        notify_fail("Seduce whom?\n");
        return 0;
    }
    
    oblist = parse_this(arg, "[the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Seduce whom?\n");
        return 0;
    }

    if (sizeof(oblist) > 1)
    {
        notify_fail("Seducing is an act best done at one person.\n");
        return 0;
    }
    
    actor("You gaze into", oblist, "'s eyes. Keeping " + HIS(oblist[0]) +
        " gaze captive in yours, you lure " + HIM(oblist[0]) + " to " +
        "feel unbridled passion.");
    all2actbb(" gazes seductively into", oblist, "'s eyes, who seems " +
        "rather taken.");
    target(" gazes into your eyes. You see " + HIS(TP) + " eyes slowly " +
        "become iridescent black and your mind is muddled as you feel " +
        "unbridled passion rise within you.", oblist);

    return 1;
}

int
ppause(string arg)
{
    if (stringp(arg))
    {
        notify_fail("Pause how?\n");
        return 0;
    }

    write("You pause for a moment while collecting your thoughts.\n");
    all(" pauses, collecting " + HIS(TP) + " thoughts.");

    return 1;
}

int
pplaneswalk(string str)
{
    object caster = TP;
    int x, size;
    mapping locs;
    string *a_locs, fail, arg, room;
    object tp, abyss;
    object env = environment(caster);

    if((caster->query_skill(PS_GUILD_LEVEL) / 10 + 1) < 13)
    {
          notify_fail("You have not been granted such a command.\n");
          return 0;
    }

    if (!str)
    {
          write("Those pplaneswalk commands available to you:\n\n"+
                "    <pplaneswalk list> for a list of memorised locations " +
                "you can planeswalk to.\n    <pplaneswalk set [location]> to set " +
                "where you stand as a location to planeswalk to.\n    <pplaneswalk " +
                "remove [location]> to forget one of your planeswalk locations.\n    " +
                "<cast pplaneswalk [location]> to planeswalk to a remembered location.\n\n");
          return 1;
    }

    if(str == "list" || str == "locations")
    {
       if(!m_sizeof(GUILD_ADMIN->query_planeswalk_locations(caster->query_real_name())))
       {
          write("You cannot recall having previously set any locations.\n");
          return 1;
       }

       write("You remember having previously set the following locations:\n");
          for (x = 0, locs = GUILD_ADMIN->query_planeswalk_locations(caster->query_real_name()),
          size = m_sizeof(locs), a_locs = m_indices(locs) ; x < size ; x++)
          {
            caster->catch_tell(sprintf("  %15s - %s\n",
             capitalize(a_locs[x]), locs[a_locs[x]][1]));
          }
          x = GUILD_ADMIN->query_planeswalk_slots(caster->query_real_name());
          write("You believe you can" + (!(x - size) ?
                "not keep any" : " keep " + LANG_WNUM(x - size)) +
                " more location" + ((x - size) > 1 ? "s" : "") + " in " +
                "memory.\n");
          return 1;
    }

    if (str == "set")
    {
       write("By what name do you want to set this location that you want to " + 
             "planeswalk to?\n");
       return 1;          
     }

     if (parse_command(str, environment(caster), "[to] 'set' %s", arg))
    {
        if (stringp(env->query_prop(ROOM_M_NO_TELEPORT)))
            fail = env->query_prop(ROOM_M_NO_TELEPORT);
        else if (stringp(env->query_prop(ROOM_M_NO_TELEPORT_TO)))
            fail = env->query_prop(ROOM_M_NO_TELEPORT_TO);
        else if (env->query_prop(ROOM_M_NO_TELEPORT) ||
            env->query_prop(ROOM_M_NO_TELEPORT_TO))
            fail = "There is no way to open a portal to another plane " +
                "from here.\n";
        
        if (GUILD_ADMIN->query_planeswalk_loc(caster->query_real_name(),
            lower_case(arg)))
        {
            write("You already have that location memorised.\n");
            return 1;
        }

        if (m_sizeof(GUILD_ADMIN->query_planeswalk_locations(caster->query_real_name())) >=
            GUILD_ADMIN->query_planeswalk_slots(caster->query_real_name()))
        {
            write("You cannot remember any more locations.\n");
            return 1;
        }

        if (!arg)
        {
            write("By what name do you want to set this location you want to " + 
              "planeswalk to?\n");
            return 1;          
        } 
        
        if (!file_size(file_name(env) + ".c"))
        {
            write("The fabric of space seems different here, you " +
                "don't think you are able to open a portal to " +
                "another plane from here.\n");
            return 1;
          
        }    

        if (strlen(arg) > 15 || sizeof(explode(arg, " ")) > 1)
        {
            write("Please refrain from any longer names and use single words.\n");
            return 1;
        }

        gLocs[caster->query_real_name()] = lower_case(arg);

        write("You trace an X-like figure on the " +
            (env->query_prop(ROOM_I_INSIDE) ? "floor" : "ground") +
            ", mumble a prayer and commit this place to memory " +
            "as " + capitalize(gLocs[caster->query_real_name()]) + ".\n");
        tp = this_player();
        set_this_player(caster);

        string set_room = file_name(env);

        all(" traces an X-like figure on the " +
            (env->query_prop(ROOM_I_INSIDE) ? "floor" : "ground") +
            " and mumbles a prayer.\n");

        set_this_player(tp);
        GUILD_ADMIN->set_planeswalk_loc(caster->query_real_name(),
            set_room, gLocs[caster->query_real_name()]);
        return 1;

    }

    else if (parse_command(str, environment(caster), "[to] 'remove' %s", arg))
    {        
        if (!GUILD_ADMIN->query_planeswalk_loc(caster->query_real_name(),
            lower_case(arg)))
        {
            write("You cannot recall having previously named such a location.\n");
            return 1;
        }
        write("You mumble a prayer and decide to uncommit " +
            "the place you knew as " + arg + " from memory.\n");  
        GUILD_ADMIN->remove_planeswalk_loc(caster->query_real_name(),
            lower_case(arg));      
        return 1;
    } 

    notify_fail("Pplaneswalk what?\n");
    return 0;
}

int
pponder(string arg)
{
    object *oblist;
    
    if (!arg)
    {
        notify_fail("Ponder whose suggestion?\n");
        return 0;
    }
    
    oblist = parse_this(arg, "[the] %l");
    
    if (!oblist || !sizeof(oblist))
    {
        notify_fail("Ponder whose suggestion?\n");
        return 0;
    }
    
    if (sizeof(oblist) > 1)
    {
        notify_fail("Suggestions are best pondered one at a time.\n");
        return 0;
    }
    
    actor("You ponder", oblist, "'s suggestion and consider how " +
        "you might please your Queen by presenting it as your own.");
    all2act(" ponders", oblist, "'s suggestions and agrees to " +
        "present it for " + HIM(oblist[0]) + ".");
    target(" ponders your suggestion and agrees to present it for you.",
        oblist);

    update_from_emote(query_verb(), RND_RANGE(20, 10));

    return 1;
}

int
ppraise(string arg)
{
    if(stringp(arg))
    {
        notify_fail("Praise how?\n");
        return 0;
    }

    write("You lift your voice in praise of the Queen of Darkness!\n");
    all(" lifts " + HIS(TP) + " voice in praise of the Queen of " +
        "Darkness!");

    update_from_emote(query_verb(), TP->query_standing() ?
        RND_RANGE(10, 5) : RND_RANGE(-10, 5));

    return 1;
}

int
ppray(string arg)
{
    if (stringp(arg))
    {
        notify_fail("Ppray how?\n");
        return 0;
    }

    write("You bow your head in prayer to the Queen of Darkness.\n");
    allbb(" bows " + HIS(TP) + " head in prayer to the Queen of Darkness.");

    update_from_emote(query_verb(), RND_RANGE(15, 5));

    return 1;
}

int
prage(string arg)
{
    if (arg)
    {
        notify_fail("Rage what?\n");
        return 0;
    }

    if (!pot_wears_medallion())
    {
        write("Your hand wanders to your chest but unable to clasp " +
            "your medallion, your rage increases.\n");
        all(" clasps an imaginary medallion, " + HIS(TP) + " rage " +
            "increasing.");

        update_from_emote(query_verb(), RND_RANGE(-20, 5));
        
        return 1;
    }

    write("You clasp your medallion, drawing power from Takhisis " +
        "in an effort to control your rage.\n");
    all(" clasps " + HIS(TP) + " medallion, drawing power from " +
        "Takhisis in an effort to control " + HIS(TP) + " rage.");

    update_from_emote(query_verb(), RND_RANGE(0, 5));

    return 1;        
}

int
precognise(string arg)
{
    object *oblist;
    string str;

    if(!arg)
    {
        notify_fail("Precognise whom?\n");
        return 0;
    }

    oblist = parse_this(arg, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Precognise whom?\n");
        return 0;
    }
    
    str = (sizeof(oblist) > 1 ? "them" : HIM(oblist[0]));
    actor("You bow before", oblist, " in the ancient manner of the " +
        "Priesthood, displaying your recognition of services done to " +
        "the Temple.");
    all2actbb(" bows before", oblist, " in the ancient manner of the " +
        "Priesthood, thereby displaying " + HIS(TP) + " recognition of " +
        "services done towards the Temple of Takhisis.");
    targetbb(" bows before you in the ancient manner of the Priesthood, "+
        "thereby displaying recognition of your services done towards " +
        "the Temple of Takhisis.", oblist);
    
    return 1;
}

int
psacrifice(string arg)
{
    object *oblist;
    
    if (!arg || !(oblist = parse_this(arg, "[the] %i")))
    {
        notify_fail("Prepare what corpse for the journey to the Abyss?\n");
        return 0;
    }
    
    oblist = filter(oblist, filter_corpse);
    if (!sizeof(oblist))
    {
        notify_fail("Prepare what corpse for the journey to the Abyss?\n");
        return 0;
    }
    
    if (sizeof(oblist) > 1)
    {
        notify_fail("This is a delicate ritual best performed on one " +
            "corpse at a time.\n");
        return 0;
    }
    
    write("Deploying immense strength you roll over " +
        LANG_THESHORT(oblist[0]) + " and scratches the mark of the Dark " +
        "Queen into the thorax preparing its soul for the journey into the " +
        "Abyss.\n");
    say("Deploying immense strength " + QTNAME(TP) + " rolls over " +
        LANG_THESHORT(oblist[0]) + " and scratches the mark of the Dark " +
        "Queen into the thorax preparing its soul for the journey into the " +
        "Abyss.\n");
    
    update_from_emote(query_verb(), TP->query_standing() ?
        RND_RANGE(20, 5) : RND_RANGE(-10, 5));

    return 1;
}

int
pscoff(string arg)
{
    object *oblist;
     
    if (!arg)
    {
        write("You scoff at such a naive remark.\n");
        allbb(" scoffs at such a naive remark.");
        return 1;
    }

    oblist = parse_this(arg, "[at] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Scoff at whose remark?\n");
        return 0;
    }
    
    actor("You scoff at", oblist, "'s naive remark.");
    all2actbb(" scoffs at", oblist, "'s naive remark.");
    targetbb(" scoffs at your remark, clearly thinking it naive.",
        oblist);
    
    return 1;
}

int
psmile(string arg)
{
    object *oblist;
    string *how;

    if (!pot_wears_medallion())
    {
        notify_fail("You must be wearing your medallion.\n");
        return 0;
    }

    how = parse_adverb_with_space(arg, "mysteriously", 0);

    if (!strlen(how[0]))
    {
        write("You smile" + how[1] + " as you stroke your black " +
            "medallion.\n");
        allbb(" smiles" + how[1] + " as " + HE(TP) + " strokes " +
            HIS(TP) + " black medallion.");

        update_from_emote(query_verb(), RND_RANGE(5, 2));
        return 1;
    }

    oblist = parse_this(how[0], "[at] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Smile at whom?\n");
        return 0;
    }

    actor("You smile" + how[1] + " at", oblist, " while stroking your " +
        "black medallion.");
    all2actbb(" smiles" + how[1] + " at", oblist, " while stroking " +
        HIS(TP) + " black medallion.");
    targetbb(" smiles" + how[1] + " at you while stroking " + HIS(TP) +
        " black medallion.", oblist);

    update_from_emote(query_verb(), RND_RANGE(5, 2));

    return 1;
}

int
ptorture(string arg)
{
    object *oblist;

    oblist = parse_this(arg, "[at] [the] %l");
    
    if (!sizeof(oblist))
    {
        notify_fail("Plan on torturing whom?\n");
        return 0;
    }
    
    actor("You intently study", oblist, "'s size with your keen eyes, " +
        "trying to determine if it would fit into one " +
        "of the torture cages in the Temple.");
    all2actbb(" intently studies", oblist, "'s size with " + HIS(TP) +
        " keen eyes, seemingly comparing it with " +
        "something.");
    targetbb(" studies you intently with a piercing gaze, assessing " +
        "your size and comparing it with something.", oblist);
    return 1;
}

int
ptrim(string arg)
{
    string odesc;
    object knife;
    object *knives = filter(TP->query_weapon(-1),
      &operator(==)(W_KNIFE) @ &->query_wt());

    if (!sizeof(knives))
    {
        NF("You need to wield a knife to trim nails with.\n");
        return 0;
    }

    if (!arg)
    {
        knife = knives[random(sizeof(knives))];
    }
    else if (!parse_command(arg, knives, "[nails] [with] [the] %o", knife))
    {
        NF("You are not wielding such a knife.\n");
        return 0;
    }

    odesc = knife->short();

    write("You casually trim your fingernails with your " + odesc + ".\n");
    allbb(" casually trims " + HIS(TP) + " fingernails with " +
        HIS(TP) + " " + odesc + ", while studying the surroundings.");

    return 1;
}

int
punimpressed(string arg)
{
    object *oblist;
    string str;

    if(!arg)
    {
        notify_fail("Punimpressed by whom?\n");
        return 0;
    }

    oblist = parse_this(arg, "[by] [the] %l");

    if (!sizeof(oblist))
    {
        notify_fail("Punimpressed by whom?\n");
        return 0;
    }

    str = (sizeof(oblist) > 1 ? "them" : HIM(oblist[0]));

    actor("You look slowly up and down at", oblist, ", evidently not " +
        "impressed.");
    all2act(" looks slowly up and down at", oblist, ", evidently not " +
        "impressed.");
    target(" looks up and down at you, evidently not impressed.", oblist);

    return 1;
}

int
pwince(string arg)
{
    string *how, str;

    how = parse_adverb_with_space(arg, "silently", 0);

    if (!strlen(how[0]))
    {
        write("You grit your teeth and wince" + how[1] + ".\n");
        allbb(" grits " + HIS(TP) + " teeth and winces" + how[1] + ".");
        return 1;
    }

    notify_fail("Pwince how?\n");
    return 0;
}

int
pwrinkle(string arg)
{
    object *oblist;
    string *how;
    
    how = parse_adverb_with_space(arg, "disgustedly", 0);
    
    if (!strlen(how[0]))
    {
        write("You wrinkle your nose" + how[1] + ".\n");
        allbb(" wrinkles " + HIS(TP) + " nose" + how[1] + ".");
        return 1;
    }
    
    oblist = parse_this(how[0], "[at] [the] %l");
    
    if (!sizeof(oblist))
    {
        notify_fail("Wrinkle your [how] nose at whom?\n");
        return 0;
    }
    
    actor("You wrinkle your nose" + how[1] + " at", oblist, ".");
    all2actbb(" wrinkles " + HIS(TP) + " nose" + how[1] + " at", oblist,
        ".");
    targetbb(" wrinkles " + HIS(TP) + " nose" + how[1] + " at you.", oblist);
    
    return 1;
}


/*
 * Function:    print_spell_list
 * Description: Used in the prayers command, this will print out
 *              each classification of spells with a header.
 */
public string
print_spell_list(object * spellobjs)
{
    string message_text = "";
    int spells_known = 0; 

    if (sizeof(spellobjs))
    {
        foreach (object spellobj : spellobjs)
        {
            if (!spellobj->query_spell_can_be_learned(this_player()))
            {
                // Only show spells that we actually know
                continue;
            }
            spells_known++;
            message_text += sprintf("%-=12.12s %-=57.57s\n", 
                spellobj->query_spell_name(), spellobj->query_spell_desc());
/*

            When component messaging added to PoT spells

            message_text += sprintf("%-=12.12s %-=57.57s\n", 
                spellobj->query_spell_name(), spellobj->query_spell_desc() 
                + " (" + spellobj->query_spell_ingredients_description() 
                + ")");
*/
        }

        message_text += "\n";
    }

    if (spells_known == 0) 
    {
        return "";
    }

    return message_text;
}

/*
 * Function name: prayers
 * Description:   List the active prayers.
 */
public int
prayers(string str)
{
    object *spellobjs = this_player()->query_spellobjs();
    spellobjs = filter(spellobjs, &wildmatch(GUILDDIRSPELL + "*") @ file_name);
    
    if (!sizeof(spellobjs))
    {
        write("You have no prayers active.\n");
        return 1;
    }
    
    string message_text = "Prayers granted to you by Takhisis\n\n";
    message_text += print_spell_list(spellobjs);

    this_player()->more(generate_scroll_text(message_text, 
                        "help priest <prayer name> for " +
                        "specific prayer information"));
    return 1;
}

/*
 * Function name: pray
 * Description:   The "pray" command.
 * Arguments:     string str - arguments to "pray" command
 * Returns:       1/0 - pray command executed/not executed
 */
public int
pray(string str)
{
    object ob;
    string spell, arg;
    if (!strlen(str))
    {
        notify_fail("Pray what?\n", 0);
        return 0;
    }

    if (!sscanf(str, "%s %s", spell, arg))
    {
        spell = str;
    }

    if (ob = this_player()->find_spell(spell)) 
    {    
        this_player()->start_spell(spell, arg, ob);
        return 1;
    }

    notify_fail("Pray what?\n", 0);
    return 0;
}

/*
 * Function:    list_song_effects
 * Description: This function gets called when the command <songeffects>
 *              executes. It goes through all the currently maintained
 *              effects (including spells) and presents it to the player.
 */
public int
list_prayer_effects(string str) 
{
    object player = this_player();
    object * effects = query_magic_effects(player);
    
    int bViewOtherPlayer = 0;
    if (player->query_wiz_level() && strlen(str))
    {
        // Wizards are allowed to see the spelleffects for players.
        bViewOtherPlayer = 1;
        str = lower_case(str);
        if (!objectp(player = find_player(str)))
        {
            notify_fail("There is no player named " + capitalize(str)
                + " that you can view prayereffects for.\n");
            return 0;
        }
        effects = query_magic_effects(player);
    }
    
    int index = 1;
    string message_text = "Currently Active Prayer Effects\n\n";

    if (bViewOtherPlayer)
    {
        message_text = "Currently Active Effects on " 
            + capitalize(player->query_real_name()) + "\n\n";
    }

    message_text += sprintf("### %-15s %-20s %-20s %-5s\n", "Name", 
        "Description","Target", "Notes");
    message_text += sprintf("--- %'-'15s %'-'20s %'-'20s %'-'|5s\n", "", "", "", "");

    foreach (object effect : effects)
    {
        string affecting = query_affecting_desc(player, 
            effect->query_effect_target());

        if (effect->query_about_to_expire())
        {
            affecting += " *";
        }
        
        message_text += sprintf("%-3d %-=15.15s %-=20.20s %-=20.20s %|=5.5s\n", 
            index++,
            effect->query_spell_effect_name(),  
            effect->query_spell_effect_desc(),
            affecting,
            strlen(effect->query_spell_effect_notes()) ? "Yes" : "No");
    }

    if (!sizeof(effects))
    {
        message_text += sprintf("%|=64s\n", "-= No Active Effects =-"); 
    }
        
    message_text += "\n* indicates effect is about to expire\n";
    message_text += "\nTo end a prayer effect:  dispel <num>\n";
    message_text += "                         dispel <name>\n";
    message_text += "                         dispel <name> on <target>\n";
    message_text += "\nTo dispel all effects: dispel all\n";

    string additional_messages = player->customize_guild_spell_effect_messages(effects,
        message_text);

    if (strlen(additional_messages))
    {
        message_text += additional_messages;
    }

    
    write(generate_scroll_text(message_text, "Dark Gifts Courtesy of the " +
        "Queen of Darkness"));
    
    return 1;
}