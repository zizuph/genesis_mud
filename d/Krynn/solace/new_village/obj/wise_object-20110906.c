/*
 * /d/Krynn/solace/new_village/obj/wise_object.c
 *
 * created by Aridor 12/01/94
 * 
 * The pin of the Wise People of Genesis
 * It's the guild (club) object.
 *
 * Stralle 010212: Fixed a problem with the leave_env() function.
 *                 Now checking if there is an objectpointer.
 *
 * Gorboth 080314: Added free emotes as a feature of this club. This is
 *                 a privelidge which can be revoked by adding the name
 *                 of people who abuse this ability to the EmoteBan
 *                 variable below. Only the AoP or some other Archwizard
 *                 has permission to do this, however.
 *
 * Gorboth 090224: Added special emote for people over 1000 days.
 * Navarre 110305: Fixed help pin bug that write 'no help on pin
 *                 available' eventhrough it showed.
 */
inherit "/std/object";

#include <macros.h>
#include <stdproperties.h>
#include <composite.h>
#include <language.h>
#include <filter_funs.h>
#include <cmdparse.h>
#include <options.h>
#include "/d/Krynn/common/defs.h"

#define WISE_ID        "krynn_wise_object"
#define EMOTELOG       "/d/Krynn/log/PLAYER_EMOTES"
#define OLD_AGE        43200000 /* 1000 days */

/* Prototypes */
nomask int        wemote(string arg);
public int        wreverie(string arg);

/* Global Variables */
public string *EmoteBan = ({
                          });
int worn = 0;


string 
query_auto_load() 
{
    return MASTER_OB(TO) + ":";
}

void
init_arg(string arg)
{ 
}

string
query_color(object owner)
{
    int age;

    if (!owner)
      return "";

    age = REALAGE(owner);
    if (age >= 86400000)
      return "mithril";
    else if (age > 51840000)
      return "platinum";
    else if (age > 43200000)
      return "gold";
    else if (age > 34560000)
      return "silver";
    else if (age > 25920000)
      return "bronze";
    else if (age > 17280000)
      return "copper";
    else if (age > 8640000)
      return "brass";
    else
      return "";
}


void
create_object()
{
    set_name("pin");
    add_pname(WISE_ID + "s");
    add_name(WISE_ID);
    set_adj("plain");
    set_long("@@my_long");
    add_prop(OBJ_M_NO_DROP, "You cannot drop the pin.\n");

    //set_at(131072);
    //set_af(TO);

    setuid();
    seteuid(getuid());
}

int
query_worn()
{
  return worn;
}

int
wear(string str)
{
    int i;
    mixed oblist;

    if (query_worn() || !strlen(str))
    {
        notify_fail("Wear what?\n");
        return 0;
    }

    i = parse_command(str,TP,"[the] %i",oblist);
    if (i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
      return 0;

    write("You wear the plain " + query_color(TP) + " pin on your chest.\n");
    say(QCTNAME(TP) + " wears a plain " + query_color(TP) + " pin on " +
	POSSESSIVE(TP) + " chest.\n");
    TP->add_subloc("the_wise_club", TO);
    set_no_show_composite(1);
    worn = 1;

    if (sizeof(oblist) > 2)
      return 0;

    return 1;
}

varargs int
remove(string str,object who = TP)
{
    int i;
    mixed oblist;
    
    if (!query_worn() || !strlen(str))
    {
      notify_fail("Remove what?\n");
      return 0;
    }
    
    i = parse_command(str,who,"[the] %i",oblist);
    if (i != 1 || !oblist || member_array(TO,oblist) < 0 || oblist[0] == 0)
    {
      notify_fail("Remove what?\n");
      return 0;
    }
    
    who->catch_msg("You remove the plain " + query_color(who) + " pin from your chest.\n");
    tell_room(E(who),QCTNAME(who) + " removes a plain " + query_color(who) + " pin from " +
	      POSSESSIVE(who) + " chest.\n",who);
    who->remove_subloc("the_wise_club");
    set_no_show_composite(0);
    worn = 0;

    if (sizeof(oblist) > 2)
      return 0;

    return 1;
}

string
my_long()
{
    return "This is a plain " + query_color(E(TO)) + " pin identifying you as " +
      "a Wise Person Of Genesis. Do 'help pin' to see what you can " +
      "do with it.\n";
}


void
init()
{
    if (!interactive(TP))
      return;
    if (REALAGE(TP) < 8640000) /* 100 days!!! */
      set_alarm(3.0,0.0,"destroy");
    ADA("help");
    ADA("remove");
    ADA("wcalm");
    ADA("wcounsel");
    ADA("wear");
    ADA("wpatient");
    ADD("wsmile","wpsmile")
    ADA("wrelax");
    ADA("wemote");
    ADA("wreverie");
    add_action(wemote, "@");
    
    add_adj(query_color(TP));
}


string
show_subloc(string subloc, object me, object for_obj)
{
    if (me->query_prop(TEMP_SUBLOC_SHOW_ONLY_THINGS))
      return "You are wearing your plain pin.\n";
    
    if (for_obj == me)
      return "You are wearing your plain " + query_color(me) + " pin.\n";
    else
      return C(PRONOUN(me)) + " is wearing " + POSSESSIVE(me) +
	" plain " + query_color(me) + " pin, identifying " + OBJECTIVE(me) +
	" as a Wise Person of Genesis.\n";

}

int
help(string str)
{
    if (str == "pin")
    {
	  write("The pin of the Wise People of Genesis can do this:\n" +
		"- help pin          This help.\n" +
		"- wcalm             Stay calm.\n" +
		"- wcounsel          Counsel someone something.\n" +
                "- wemote            Free emotes. Do not abuse!\n" +
		"- wrelax            Relax.\n" +
		"- wpatient          Advise someone to be patient.\n" +
		"- wpsmile           Smile showing your wisdom.\n" +
		"You can wear and remove the pin, too.\n\n");

          /* If they are 1000 days old, they get something extra!
           * Added by Gorboth, February 2009
           */
          if (this_player()->query_age() > (OLD_AGE - 1))
          {
              write("Oh truly ancient one! You get one extra command:\n\n" +
                    "- wreverie          Display the depth of knowledge that\n"
                  + "                    comes only when one has reached such\n"
                  + "                    a venerable age as you have.\n\n");
	  }
	  return 1;
    }
    return 0;
}


/*
 * Function name:        wreverie
 * Description  :        You are old. Show it!
 */
public int
wreverie(string arg)
{
    if (this_player()->query_age() < OLD_AGE)
    {
        return 0;
    }

    if (arg)
    {
        notify_fail("Just go ahead and use wglance. No need to aim it"
          + " at anything or anyone in partiular. You are old! You"
          + " can compete with the universe itself if you wish!\n");
        return 0;
    }

    tell_room(environment(this_player()), QCTNAME(this_player())
      + " is suddenly very still, seemingly in communion with the"
      + " universe around " + this_player()->query_objective()
      + ", yet with eyes open and fully alert. Indeed, you feel drawn"
      + " onto those eyes. Eyes that have seen much ... the drowning"
      + " of Emerald ... the departure of the Mystic Prophet ..."
      + " the Kahedan Monastery filled with disciples ... and suddenly"
      + " the eyes close, and open refocused - you step back, humbled"
      + " by the depth of experience before you.\n", this_player());
    this_player()->catch_tell("You pause in brief reverie, remembering"
      + " the many sights and sounds of your seemingly unnumbered"
      + " days in these lands ... the drowning of Emerald ... the"
      + " Kahedan Monastery filled with disciples ... the departure"
      + " of the Mystic Prophet ... blinking, you come out of your"
      + " reverie and refocus on the matters at hand.\n");
    return 1;
} /* wreverie */


int
wcalm(string str)
{
    NF("Use just wcalm, without argument.\n");
    if (str)
      return 0;
    tell_room(E(TP), QCTNAME(TP) + " stays totally calm, despite the situation.\n", ({ TP }));
    TP->catch_msg("You stay calm, despite the situation.\n");
    return 1;
}

int
wcounsel(string str)
{
    object *pers;
    string str1, str2;
    NF("Wcounsel who what?\n");
    if (!str)
      return 0;
    if (sscanf(str, "%s %s", str1, str2) != 2)
      return 0;
    pers = FILTER_OTHER_LIVE(FIND_STR_IN_OBJECT(str1, E(TP)));
    if (!pers || !sizeof(pers))
      return 0;
    tell_room(E(TP), QCTNAME(TP) + " counsels " + COMPOSITE_LIVE(pers) + " " + str2 + "\n", pers + ({TP}));
    TP->catch_msg("You counsel " + QCOMPLIVE + " " + str2 + "\n");
    pers->catch_msg(QCTNAME(TP) + " counsels you " + str2 + "\n");
    return 1;
}

int
wrelax(string str)
{
    NF("Use just wrelax, without argument.\n");
    if (str)
      return 0;
    tell_room(E(TP), QCTNAME(TP) + " relaxes, apparently knowing the ways " +
	      "of the world.\n", ({ TP }));
    TP->catch_msg("You relax, knowing the ways of the world.\n");
    return 1;
}

int
wpatient(string str)
{
    object *pers;
    if (!str || str == "me" || L(str) == TP->query_real_name())
      {
	  write("Be more patient, be more patient.\n");
	  say(QCTNAME(TP) + " mumbles something about patience.\n");
	  return 1;
      }
    pers = FILTER_OTHER_LIVE(FIND_STR_IN_OBJECT(str, E(TP)));
    NF("Wpatient who?\n");
    if (!pers || !sizeof(pers))
      return 0;
    tell_room(E(TP), QCTNAME(TP) + " advises " + COMPOSITE_LIVE(pers) +
	      " to be patient.\n", pers + ({TP}));
    TP->catch_msg("You advise " + QCOMPLIVE + " to be patient.\n");
    pers->catch_msg(QCTNAME(TP) + " advises you to be patient.\n");
    return 1;
}

int
wsmile(string str)
{
    object *pers;
    if (!str)
    {
	write("You smile, knowing the ways of the world.\n");
	say(QCTNAME(TP) + " smiles with the wisdom of the ages in " + HIS(TP) +
	    " eyes.\n");
	return 1;
    }
    pers = PARSE_THIS(str, "[at] %l");
    NF("Wsmile at who?\n");
    if (!pers || !sizeof(pers))
      return 0;
    tell_room(E(TP), QCTNAME(TP) + " smiles at " + COMPOSITE_LIVE(pers) +
	      " with the wisdom of the ages in " + HIS(TP) + "eyes.\n",
	      pers + ({TP}));
    TP->catch_msg("You smile at " + QCOMPLIVE + ", knowing the ways of the world.\n");
    pers->catch_msg(QCTNAME(TP) + " smiles at you with the wisdom of the ages in " +
		    HIS(TP) + " eyes.\n");
    return 1;
}


void
destroy()
{
    tell_object(E(TO), "Accidentally, you drop the pin, and you just cannot " +
		"find it again.\n");
    remove_object();
}

void
leave_env(object from, object to)
{
    if (objectp(from))
       remove("pin",from);

    ::leave_env(from,to);
}

void
enter_env(object dest, object old)
{
    mixed oblist;
    if (dest)
      {
	  oblist = FIND_STR_IN_OBJECT("all " + WISE_ID + "s",dest);
	  oblist -= ({ 0, TO });
	  if(oblist && sizeof(oblist) > 0)
	    set_alarm(4.0,0.0,"destroy");
      }

    if (this_player()->query_age() > (OLD_AGE - 1))
    {
        dest->catch_tell("The " + short() + " gleams vividly, your"
          + " venerable age reflecting in its surface. You notice"
          + " something a bit different about the pin than you"
          + " remember from when you were younger.\n");
    }

    ::enter_env(dest,old);
}


/* **************************************************************************
 * emote, : - emote something
 *
 * This has been taken directly from:
 *
 *    /cmd/wiz/apprentice/communication.c (Gorboth)
 */

static nomask string
cat_string(mixed org, string what, object pl, int up)
{
    if (objectp(pl))
        org[1] += (pl == org[0] ? (up == 1 ? "You" : "you") :
            (up == 1 ? QCTNAME(pl) : QTNAME(pl)));
    else
        org[1] += what;
    
    return org;
}

static nomask mixed
mk_item(object ob)
{
    return ({ ob, "" });
}

static nomask void
tell_them(object ob, mixed arg)
{
    arg[0]->catch_msg(QCTNAME(ob) + arg[1] + "\n");
}

nomask int
wemote(string arg)
{
    object      pl, *pls;
    string      *args, *nms, oarg;
    int         i, sz, up;
    mapping     emap;

    if (member_array(this_player()->query_real_name(), EmoteBan) != -1)
    {
        write("This command is no longer available to you. You may mail"
          + " the Archwizard of Players to politely explain why you"
          + " think you deserve to be entrusted with it again.\n");
        return 1;
    }

    pls = FILTER_LIVE(all_inventory(environment(this_player()))) -
        ({ this_player() });
    emap = mkmapping(pls, map(pls, mk_item));

    if (!stringp(arg))
    {
        notify_fail("Usage: @ <emote string>, emote string can contain " +
            "names of present people enclosed in '|' characters, which " +
            "then will be identified by their met/nonmet names to observers. " +
            "e.g. ': smile fondly at |mrpr|.'\n");
        return 0;
    }

    /* Allows "emote 's head ..." -> "Mrpr's head ..." and yes the ''' does
     * look funny, but that's the syntax for getting the integer value of a
     * single quote.
     */
    if (arg[0] != ''')
    {
        arg = " " + arg;
    }

    oarg = arg;
    args = explode(arg, "|");
    emap = map(emap, &cat_string(, args[0], 0, 0));

    if ((sz = sizeof(args)) > 1)
    {
        for (i = 1 ; i < sz ; i ++)
        {
            nms = explode(args[i], " ");
            up = nms[0] == lower_case(nms[0]) ? 0 : 1;
            nms[0] = lower_case(nms[0]);
            if (objectp((pl = present(nms[0], environment(this_player())))))
            {
                emap = map(emap, &cat_string(, "", pl, up));
                if (sizeof(nms) > 1)
                {
                    arg = implode(nms[1..], " ");
                    emap = map(emap, &cat_string(, arg, 0, up));
                }
            }
            else if (i % 2)
                return notify_fail("You cannot see " + nms[0] + " here.\n");
            else
                emap = map(emap, &cat_string(, args[i], 0, up));
        }
    }

    map(emap, &tell_them(this_player(), ));

    if (this_player()->query_option(OPT_ECHO))
    {
        write("You emote: |" + capitalize(this_player()->query_real_name()) +
            "|" + oarg + "\n");
    }
    else
    {
        write("Ok.\n");
    }

    write_file(EMOTELOG, 
        ctime(time()) + " - " + capitalize(this_player()->query_real_name())
      + " emotes: |" + capitalize(this_player()->query_real_name())
      + "|" + oarg + "\n");
    return 1;
}
