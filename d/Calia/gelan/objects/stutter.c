
/*  Stutter object, a possible side-effect of Raspatoon the Alchemist's 
    experiment in the Alchemist quest of Gelan.
  

    coder(s):   Maniac

    history:    
                23.7.96     updated                          Maniac
                19.12.95    amendment to ask for npcs        Maniac
                19.1.95                 Created              Maniac

*/

inherit "/std/object";
inherit "/cmd/std/command_driver";
#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include <filter_funs.h>
#include <composite.h>
#include <cmdparse.h>
#include <language.h>
#include <formulas.h>
#include <living_desc.h>
#include <options.h>

#include "object.h"
#include ALCHEMIST_QUEST

/* Next four taken from /cmd/std/soul_cmd */
#define SUBLOC_SOULEXTRADESC "_std_soul_extra"
#define SOULDESC(x) (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define LANGUAGE_FOR_RSAY 45   /* When will you understand an rsay */
#define DEPTH 1  /*  How many rooms away the shout will be heard.  */


void
create_object()
{
    set_name(STUTTER_NAME);
    set_short("stutter");
    set_long(
        "A stuttering object.\n");
    set_no_show();   /* Don't want people to be able to see in inventory */
    add_prop(OBJ_I_VALUE, 0);
    add_prop(OBJ_I_WEIGHT, 0);
    add_prop(OBJ_M_NO_DROP, 1);
    add_prop(OBJ_M_NO_GIVE, 1);
    add_prop(OBJ_I_VOLUME, 0);
}

void
enter_env(object dest, object old)
{
    ::enter_env(dest, old);

    if (!living(dest)) remove_object();
    dest->catch_msg("You f-feel that something has ch-changed " +
                    "in your p-p-powers of speech.\n");
}

void
remove_object()
{
    object e = environment(this_object());
    
    if (living(e)) 
        e->catch_msg("You feel that your powers of speech " +
                     "have returned to normal.\n");
    ::remove_object();
}

void
init()
{
    ::init();
    /* Intercept various commands so stuttering can be added */
    add_action("do_ask", "ask");
    add_action("do_ponder", "ponder");
    add_action("do_rsay", "rsay");
    add_action("do_say", "say");
    add_action("do_say", "'", 1);
    add_action("do_shout", "shout");
    add_action("do_whisper", "whisper");
}


/* Is this a consonant and one that can typically be stuttered on */
int
stutter_consonant(string str)
{
    str = lower_case(str);

    if (str == "b" || str == "c" || str == "d" || str == "f" || 
        str == "g" || str == "j" || str == "k" || str == "l" ||
        str == "m" || str == "n" || str == "p" || str == "q" ||
        str == "r" || str == "s" || str == "t" || str == "v" ||
        str == "w" || str == "y" || str == "z" || str == "h")
        return 1;
    else
        return 0;
}



string *
get_start_clusters(string str)
{
    int i;
    string s = "";
    string *clusters = ({ });
    
    for (i = 0; i < strlen(str); i++) {
       if (stutter_consonant(strchar(str[i]))) { 
          s += strchar(str[i]);
          clusters += ({ s });
       }
       else return clusters;
    }
   return clusters;
}




/* Ok things to stutter on for a given word */
string *
ok_stutters(string *sc)
{
    string *new_sc = sc;

    if (member_array("th", new_sc) > -1) 
        new_sc = new_sc - ({ "t" }); 
    if (member_array("sh", new_sc) > -1)
        new_sc = new_sc - ({ "s" });
    if (member_array("ch", new_sc) > -1)
        new_sc = new_sc - ({ "c" });
    return new_sc; 
}


/* Stutter a particular word, perhaps */
string
stutter_word(string str)
{
   int i, j;
   string *start_clusters = ok_stutters(get_start_clusters(str));
   string stuttered_word = "";
   
   if ((random(5) > 1) || !sizeof(start_clusters) || (strlen(str) < 2)) 
       return str;

   switch (random(7))
   {
       case 0: 
       case 1:
       case 3:
          i = 1;
          break;
       case 4:
       case 5:
          i = 2;
          break;
       case 6:
          i = random(2) + 3;
          break;
    } 
    
    for (j = 0; j < i; j++)
      stuttered_word += start_clusters[random(sizeof(start_clusters))] +
                        "-"; 
    stuttered_word += str;
    return stuttered_word;
}


/* Stutter the words in a sentence */
string
stutter_sentence(string str)
{
    int i;
    string stuttered_sentence = "";
    string *words = explode(str, " ");

    for (i = 0; i < sizeof(words); i++)
      if (!(words[i] == " " || words[i] == ""))
         stuttered_sentence += stutter_word(words[i]) + " ";

   return stuttered_sentence;
}


int
do_ponder(string str)
{
    object tp = this_player();
    object *oblist;

    if (!strlen(str))
    {
        write("You ponder the s-s-situation.\n");
        all(" ponders the s-s-situation.");
        SOULDESC("pondering the s-s-situation");
        return 1;
    }

    if (strlen(str) > 60)
    {
        write("Y-you ponder beyond th-the end of the l-l-ine and wake up f-f-from your reveries.\n");
        all(" ponders the s-s-ituation.");
        SOULDESC("pondering the s-s-ituation");
        return 1;
    }

    str = stutter_sentence(str);
    oblist = parse_this(str, "[about] [the] [proposal] [of] [the] %l");

    if (!sizeof(oblist))
    {
        write("You ponder " + str + ".\n");
        all(" ponders " + str + ".");
        SOULDESC("pondering about s-s-something");
        return 1;
    }

    target(" ponders about your proposal.", oblist);
    actor("You ponder about the proposal of", oblist);
    all2act(" ponders about the proposal of", oblist);
    SOULDESC("pondering about a proposal");
    return 1;
}



/* copied from /cmd/live/social.c and stutter added.
 */
int
do_ask(string str)
{
    object tp = this_player();
    string msg1, msg2, firststr, players;
    object *oblist, *tmplist;
    int i;

    if (!CAN_SEE_IN_ROOM(tp))
    {
        notify_fail("You c-c-can't s-see in here.\n");
        return 0;
    }

    tmplist = ({ });
    notify_fail("Ask w-w-what?\n");

    if (!str)
        return 0;

    if (parse_command(str, environment(tp), "%l %s", oblist, msg1)) 
        oblist = NORMAL_ACCESS(oblist, 0, 0);
       
    if (!sizeof(oblist))
    {
        notify_fail("Can't f-f-find that p-person.\n");
        return 0;
    }
    else if (oblist[0] == tp)
    {
        notify_fail("D-d-don't ask me, I w-wouldn't kn-know.\n");
        return 0;
    }
    else
    {
        for (i = 0; i < sizeof(oblist); i++)
        {
            if (objectp(oblist[i]) && living(oblist[i]) &&
                        tp != oblist[i])
                tmplist += ({ oblist[i] });
        }

        if (!strlen(msg1))
        {
            write("Ask w-what to " + COMPOSITE_LIVE(oblist) + "?\n");
            return 1;
        }

        msg2 = stutter_sentence(msg1);
        tp->reveal_me(1);

        players = COMPOSITE_LIVE(oblist);
        if (tp->query_option(OPT_ECHO))
            tp->catch_msg("Y-you ask "+players+": " + msg2 + "\n");
        else
            write("Ok.\n");

        say(QCTNAME(tp) + " asks " + QCOMPLIVE + " something.\n",
                        oblist + ({ tp }) );

        for (i = 0; i < sizeof(oblist); i++)
        {
            if (oblist[i]->query_npc()) {
                oblist[i]->catch_msg(tp->query_The_name(oblist[i]) +
                                     " asks you: " + msg1 + "\n");
                oblist[i]->catch_question(msg1);
            }
            else  {
                oblist[i]->catch_msg(tp->query_The_name(oblist[i]) +
                                     " asks you: " + msg2 + "\n");
                oblist[i]->catch_question(msg2);
            }
            oblist[i]->reveal_me(1);
        }
    }

    return 1;
}



/* Mostly taken from /cmd/std/soul_cmd.c */
int
do_rsay(string str)
{
    object tp = this_player();
    int i;
    object *oblist;

    if (!environment(tp))
        return 0;

    if (!strlen(str))
    {
        notify_fail("Say wh-what in your r-r-racial tongue?\n");
        return 0;
    }

    str = stutter_sentence(str);
    oblist = FILTER_OTHER_LIVE(all_inventory(environment(tp)));

    for (i = 0; i < sizeof(oblist); i++)
    {
        if ((tp->query_race_name() ==
                oblist[i]->query_race_name()) ||
            (oblist[i]->query_wiz_level()) ||
            (oblist[i]->query_skill(SS_LANGUAGE) >= LANGUAGE_FOR_RSAY))
        {
            oblist[i]->catch_msg(QCTNAME(tp) + " says: " + str +
                "\n");
        }
        else
        {
            oblist[i]->catch_msg(QCTNAME(tp) +
                " says something completely incomprehensible.\n");
        }
    }

    if (tp->query_option(OPT_ECHO))
        write("You rsay: " + str + "\n");
    else
        write("Ok.\n");

    return 1;
}


/* Modified from /std/living/cmdhooks.c */
int
do_say(string str = "")
{
    object tp = this_player();

    if (str == "") {
        tp->catch_msg("Say what?\n");
        return 1;
    }

    if (query_verb()[0] == ''')
    {
        str = extract(query_verb(), 1) + " " + str;
    }

    str = stutter_sentence(str);
    say( ({ METNAME + LD_SAYS + LD_UNDERSTANDS(str) + "\n",
            TART_NONMETNAME + LD_SAYS + LD_UNDERSTANDS(str) + "\n",
            UNSEEN_NAME + LD_SAYS + LD_UNDERSTANDS(str) + "\n" }) );

    if (tp->query_option(OPT_ECHO))
        write("You say: " + str + "\n");
    else
        write("Ok.\n");
    return 1;
}


/* Unchanged from /cmd/std/soul_cmd.c */
string
shout_name()
{
    object pobj;
    string str;

    pobj = previous_object(); /* Reciever of message */
    if (file_name(pobj) == "/secure/vbfc_object")
        pobj = previous_object(-1);
    if (pobj->query_met(this_player()))
        return this_player()->query_name();
    else
    {
        if (environment(pobj) == environment(this_player()))
            str = this_player()->query_nonmet_name();
        else
            str = this_player()->query_gender_string() + " " +
                this_player()->query_race_name() + " voice";
        return capitalize(LANG_ADDART(str));
    }
}


/* Modified from /cmd/std/soul_cmd.c */
int
do_shout(string what)
{
    object tp = this_player();
    object *rooms;
    object troom;
    int il;

    if (!tp)
        return 0;

    if (!what)
    {
        notify_fail("Sh-sh-shout what?\n");
        return 0;
    }

    if (!(troom = environment(tp)))
        return 0;

    what = stutter_sentence(what);
    rooms = FIND_NEIGHBOURS(troom, DEPTH);

    for (il = 0; il < sizeof(rooms); il++)
        tell_room(rooms[il], "@@shout_name:" + file_name(this_object()) +
                  "@@ shouts: " + what + "\n", tp);
    if (tp->query_option(OPT_ECHO))
        write("You shout: " + what + "\n");
    else
        write("Ok.\n");
    return 1;
}


/* Copied from /cmd/std/soul_cmd.c with stuttering added */
int
do_whisper(string str)
{
    object *oblist, *tmplist;
    object tp = this_player();
    string msg;
    int i;

    tmplist = ({});
    notify_fail("Whisper to wh-wh-whom?\n");

    if (!str || (!parse_command(str, environment(tp),
            "[to] [the] %l %s", oblist, msg)))
        return 0;

    oblist = NORMAL_ACCESS(oblist, 0, 0);

    if (!sizeof(oblist))
        return 0;

    for (i = 0; i < sizeof(oblist); i++)
    {
        if (!(!objectp(oblist[i]) || !living(oblist[i]) ||
                tp == oblist[i]))
            tmplist = tmplist + ({ oblist[i] });
    }

    oblist = tmplist;

    if (!sizeof(oblist))
        return 0;

    if (!strlen(msg))
    {
        actor("Whisper wh-what t-t-to", oblist, "?");
        return 1;
    }

    msg = stutter_sentence(msg);
    target(" whispers to you: " + msg, oblist);
    all2act(" whispers something to", oblist);

    if (tp->query_option(OPT_ECHO))
        write("You whisper: " + msg + "\n");
    else
        write("Ok.\n");

    return 1;
}

