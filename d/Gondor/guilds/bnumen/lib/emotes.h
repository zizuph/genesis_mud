/*
 *	The emotes in the soul of the Black Numenoreans.
 *  
 *	Created by Sir Toby 2006-08-25
 *
 *	Modification log:
 *	
 */
#include <adverbs.h>
#include <cmdparse.h>
#include <composite.h>
#include <filter_funs.h>
#include <formulas.h>
#include <stdproperties.h>
#include <std.h>
#include <files.h>


#include "/d/Gondor/defs.h"

#define SOULDESC(x)	(this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define ADV_DUMMY	"ADVERB"
#define BNTITLE(x)  (("/d/Gondor/guilds/bnumen/bnumen_soul.c")->query_internal_title(x))

/*
 * Language support
 */
/**************************************************************************
 *        Language support.    Emotions further below                     *
 **************************************************************************/
int
understand_adunaic(object pl)
{
    int		langsk = pl->query_skill(SS_LANGUAGE);
    string	name = pl->query_real_name();

    if (IS_RANGER(pl) && (langsk > 10))
        return 1;
    else if(IS_NRANGER(pl) && (langsk > 10))
        return 1;
    else if (query_is_bnumen(pl) && (langsk > 1))
        return 1;
    else if (IS_SINDAR(pl) && (langsk > ADUNAIC_DIFF - 25))
        return 1;
    else if (langsk > ADUNAIC_DIFF)
        return 1;
    else if ((SECURITY->query_wiz_dom(name) == "Gondor") ||
	     (SECURITY->query_wiz_rank(name) >= WIZ_ARCH))
	return 1;
    else
        return 0;
}

int
speak_adunaic(string str)
{
    string   cap_name, 
             tmpstr, 
             wrtstr, 
             prestr, 
            *expl_arr, 
            *tell_arr;
    int      i,
             sobj,
             argnum, 
             cnt,
             cnt2;
    object  *obj;
    mixed    gag;
   
    if (!strlen(str)) 
        NFN0("Say what in Adunaic?");

    gag = TP->query_prop(LIVE_M_MOUTH_BLOCKED);
    if (gag)
    {
        if (stringp(gag))
            TP->catch_msg(gag);
        else if (intp(gag))
            TP->catch_msg("You are unable to speak right now!\n");
        return 1;
    }

    if (TP->query_invis()) 
        cap_name = "Someone";
    if (!tell_arr)
        tell_arr = allocate(20);
    if (!expl_arr)
        expl_arr = allocate(100);
    str += " ";
    if (str != " ") 
    { 
        /* Now let's cut the string in pieces! */
        expl_arr = explode(str," ");
        argnum = sizeof(expl_arr);
        cnt = cnt2 = 0;
        while (cnt < argnum && cnt2 < 20) 
        {
            wrtstr = expl_arr[cnt++];
            while (cnt < argnum && strlen(wrtstr + " " + expl_arr[cnt]) < 60) 
            {
                wrtstr = wrtstr + " " + expl_arr[cnt++];
            }
            tell_arr[cnt2++] = wrtstr;
        }
    }
    write("You spoke in Adunaic: " + str + "\n");
    obj = all_inventory(environment(TP));
    sobj = sizeof(obj);
    while (i < sobj)
    {
        if ((living(obj[i])) && (obj[i] != TP))
        {
             if (!understand_adunaic(obj[i]))
             {
                 if (CAN_SEE(obj[i],TP))
                     obj[i]->catch_msg(QCTNAME(TP)
                       + " says something in an unknown language.\n");
                 else 
                     obj[i]->catch_msg("Someone says something in an "
                       + "unknown language.\n");
            }
            else
            { 
                if (CAN_SEE(obj[i],TP))
                    for (cnt = 0; cnt < cnt2; cnt++)
                        obj[i]->catch_msg(QCTNAME(TP)
                          + " speaks in Adunaic: "+tell_arr[cnt] + "\n");
                else
                    for (cnt = 0; cnt < cnt2; cnt++)
                        obj[i]->catch_msg("Someone speaks in Adunaic: "
                          + tell_arr[cnt]+"\n");
            }
        }
        i++;
    }
    return 1;
}

int
understand_ancient_adunaic(object pl)
{
    int		langsk = pl->query_skill(SS_LANGUAGE);
    string	name = pl->query_real_name();

    if (IS_RANGER(pl) && (langsk > 10))
        return 1;
    else if (IS_NRANGER(pl) && (langsk > 10))
        return 1;
    else if (query_is_bnumen(pl) && (langsk > 1))
        return 1;
    else if (IS_SINDAR(pl) && (langsk > ANCIENT_ADUNAIC_DIFF - 25))
        return 1;
    else if (langsk > ANCIENT_ADUNAIC_DIFF)
        return 1;
    else if ((SECURITY->query_wiz_dom(name) == "Gondor") ||
	     (SECURITY->query_wiz_rank(name) >= WIZ_ARCH))
	return 1;
    else
        return 0;
}

int
speak_ancient_adunaic(string str)
{
    string   cap_name, 
             tmpstr, 
             wrtstr, 
             prestr, 
            *expl_arr, 
            *tell_arr;
    int      i,
             sobj,
             argnum, 
             cnt,
             cnt2;
    object  *obj;
    mixed    gag;
   
    if (!strlen(str)) 
        NFN0("Say what in Ancient Adunaic?");

    gag = TP->query_prop(LIVE_M_MOUTH_BLOCKED);
    if (gag)
    {
        if (stringp(gag))
            TP->catch_msg(gag);
        else if (intp(gag))
            TP->catch_msg("You are unable to speak right now!\n");
        return 1;
    }

    if (TP->query_invis()) 
        cap_name = "Someone";
    if (!tell_arr)
        tell_arr = allocate(20);
    if (!expl_arr)
        expl_arr = allocate(100);
    str += " ";
    if (str != " ") 
    { 
        /* Now let's cut the string in pieces! */
        expl_arr = explode(str," ");
        argnum = sizeof(expl_arr);
        cnt = cnt2 = 0;
        while (cnt < argnum && cnt2 < 20) 
        {
            wrtstr = expl_arr[cnt++];
            while (cnt < argnum && strlen(wrtstr + " " + expl_arr[cnt]) < 60) 
            {
                wrtstr = wrtstr + " " + expl_arr[cnt++];
            }
            tell_arr[cnt2++] = wrtstr;
        }
    }
    write("Speaking Ancient Adunaic you say: " + str + "\n");
    obj = all_inventory(environment(TP));
    sobj = sizeof(obj);
    while (i < sobj)
    {
        if ((living(obj[i])) && (obj[i] != TP))
        {
             if (!understand_adunaic(obj[i]))
             {
                 if (CAN_SEE(obj[i],TP))
                     obj[i]->catch_msg(QCTNAME(TP)
                       + " says something in an unknown language.\n");
                 else 
                     obj[i]->catch_msg("Someone says something in an "
                       + "unknown language.\n");
            }
            else
            { 
                if (CAN_SEE(obj[i],TP))
                    for (cnt = 0; cnt < cnt2; cnt++)
                        obj[i]->catch_msg(QCTNAME(TP)
                          + " speaks in Ancient Adunaic: "+tell_arr[cnt] + "\n");
                else
                    for (cnt = 0; cnt < cnt2; cnt++)
                        obj[i]->catch_msg("Someone speaks in Ancient Adunaic: "
                          + tell_arr[cnt]+"\n");
            }
        }
        i++;
    }
    return 1;
}

/**************************************************************************
 *                  Emotions, ordered alphabetically                      *
 **************************************************************************/
int
bnamazed(string str)
{
   object *oblist,
          tp = TP;

   if (!strlen(str))
      NFN0("You need to supply a target! [bnamaze <target>]");

   oblist = parse_this(str, "[at] [the] %l");
   oblist -= ({ TP });

   if (!sizeof(oblist))
      NFN0("Look amazed at whom?");

   SOULDESC("looking amazed");
   actor("You look at", oblist, " and are amazed at the stupidity of " +
         "the inferior people of Westerness.");
   targetbb(" looks at you with obvious disdain and is amazed.", oblist);
   all2actbb(" look at", oblist, " with obvious disdain and is amazed.");

   return 1;
}

int
bnclench(string str)
{
   string *how;

   how = parse_adverb_with_space(str, "firmly", 0);
   
   write("You clench a fist" + how[1] + " in an attempt to calm yourself.\n");
   allbb(" clenches a fist" + how[1] + " in an attempt to calm " + 
         TP->query_objective() + "self.");

   SOULDESC("clenching a fist" + how[1]);

   return 1;
}

int
bneye(string str)
{
   object *oblist,
          item,
          *items;
   string *how,
          eye_how = one_of_list(({"ill-disguised contempt",
                                  "obvious discontent",
                                  "great misgiving"})),
          item_str;


   if(!str)
      NFN0("You need to eye someone or something! [bneye [<adverb>] [<target/object>]");

   how = parse_adverb_with_space(str, "slowly", 0);

   oblist = parse_this(how[0], "[the] %l");

   if(sizeof(oblist))
   {
      actor("You" + how[1] + " eye", oblist, " with " + eye_how + ".");
      targetbb(how[1] + " eyes you with " + eye_how + ".", oblist);
      all2actbb(how[1] + " eyes", oblist, " with " + eye_how + ".");

      return 1;
   }

   if(ENV(TP)->item_id(how[0]))
      item_str = "the " + how[0];
   else if(parse_command(how[0], all_inventory(ENV(TP)), "%i", items))
   {
      items = NORMAL_ACCESS(items, 0, 0);
      items = FILTER_DEAD(items);

      if (!sizeof(items))
         NFN0("Eye which item?");

      item_str = COMPOSITE_DEAD(items);
   }
   else
      NFN0("Behold which item?");

   write("You" + how[1] + " eye " + item_str + " with " + eye_how + ".\n");

   if (sizeof(oblist))
   {
      target(how[1] + " eyes " + item_str + " with " + eye_how + ".", oblist);
   }

   return 1;
}

int
bngaze(string str)
{
   string *how;

   how = parse_adverb_with_space(str, "wistfully", 0);

   write("You stop a moment and gaze Westwards," + how[1] + " towards " +
         "Akallabeth and then, with pride and hatred, beyond.\n");
   allbb(" stops a moment and gazes Westwards," + how[1] + " towards " +
             "Akallabeth and then, with pride and hatred, beyond.");

   SOULDESC("gazing" + how[1]);

   return 1;
}

int
bngloat()
{
   write("You gloat unabashedly in your triumph.\n");
   allbb(" gloats unabashedly in " + TP->query_possessive() + " triumph.");

   return 1;
}

int
bngrin(string str)
{
   object *oblist;
   string *how;

   how = parse_adverb_with_space(str, "haughtily", 0);

   SOULDESC("grinning" + how[1]);

   if (!stringp(how[0]))
   {
      write("You grin" + how[1] + " at the thought of opressing the " +
            "inferior people of Westernesse.\n");
      allbb(" grins" + how[1] + " apparently lost in thought.", how[1]);
      return 1;
   }

   oblist = parse_this(how[0], "[at] [the] %l");

   if (!sizeof(oblist))
   {
      notify_fail("Grin [how] at whom?\n");
      return 0;
   }

   actor("With a sly look you grin" + how[1] + " at", oblist);
   targetbb(" gets a sly look in " + TP->query_possessive() + 
      " eyes and grins" + how[1] + " at you.", oblist, how[1]);
   all2act(" gets a sly look in " + TP->query_possessive() + 
      " eyes and grins" + how[1] + " at", oblist, 0, how[1]);

   return 1;
}

int
bnheckle()
{
   SOULDESC("cackling in a raw way");

   write("With a raw cackle, you heckle the 'porter' of Gondor.\n");
   allbb(" gives off a raw cackle as " + TP->query_pronoun() + 
         " heckles the 'porter' of Gondor.");

   return 1;

}

int
bnintro(string str)
{
   object *oblist;
   string *how;

   how = parse_adverb_with_space(str, "fiercly", 0);

   oblist = parse_this(how[0], "[to] %l");

   if (!sizeof(oblist))
   {
      notify_fail("Introduce your rank to whom?\n");
      return 0;
   }

   actor("You move closer to", oblist, ", speaking in a low voice in " +HIS_HER(oblist[0])+ 
         " ear: I am " +TP->query_name()+ " the " +BNTITLE(TP)+ " of the Black Numenoreans.");
   target(" moves close to you and speaks silently in your ear: I am " +TP->query_name()+
          " the " +BNTITLE(TP)+ " of the Black Numenoreans.", oblist);
   all2act(" moves close to", oblist, " and speaks silently, though you can not hear what is said.");

   return 1;
}

int
bnmock(string str)
{
   object *oblist,
          tp = TP;

   if (!strlen(str))
      NFN0("You need to supply a target! [bnmock <target>]");

   oblist = parse_this(str, "[at] [the] %l");
   oblist -= ({ TP });

   if (!sizeof(oblist))
      NFN0("mock whom?");

   SOULDESC("looking arrogant");
   actor("You mock", oblist, "'s misery with imperious arrogance.");
   targetbb(" mocks you with imperious arrogance claiming you are in misery.", oblist);
   all2actbb(" mocks", oblist, "'s misery with imperious arrogance.");

   return 1;
}

int
bnshake(string str)
{
   string *how;

   how = parse_adverb_with_space(str, "calmly", 0);

   write("You your fists at heaven and" + how[1] + " you declare: They strike first, " +
         "the next blow shall be ours!\n");
   allbb(" shakes " + TP->query_possessive() + " fists at heaven," +
         how[1] + " declaring: They strike first, the next blow shall be ours!");
   return 1;
}

int
bnsilence(string str)
{
   object *oblist;
   string *how;

   how = parse_adverb_with_space(str, "fiercly", 0);

   if (!stringp(how[0]))
   {
      write("You gesture" + how[1] + ", motioning for silence.\n");
      allbb(" gestures" + how[1] + ", motioning for silence.");
      return 1;
   }

   oblist = parse_this(how[0], "[the] %l");

   if (!sizeof(oblist))
   {
      notify_fail("Silence [how] and whom?\n");
      return 0;
   }

   actor("You gesture" + how[1] + " at", oblist, " motioning for " +
         oblist[0]->query_objective() + " to be silent.");
   targetbb(" gestures" + how[1] + " at you, motioning you to be " +
         "silent", oblist, how[1]);
   all2act(" gestures" + how[1] + " at", oblist, ", motioning " +
         oblist[0]->query_objective() + " to be silent.", how[1]);

   return 1;
}

int
bntall(string str)
{
   string *how;

   how = parse_adverb_with_space(str, "slowly", 0);

   write("You straighten yourself" + how[1] + ", standing tall and proud.\n");
   allbb(how[1] + " straightens up, standing tall and proud.");
   return 1;
}

int
bnwellmet(string str)
{
   object *oblist,
          tp = TP;
   string *how;

   how = parse_adverb_with_space(str, "briskly", 0);

   if (!strlen(how[0]))
      how[0] = "all";

   oblist = parse_this(how[0], "%l");
   oblist -= ({ TP });
   oblist = filter(oblist, query_is_bnumen);

   if (!sizeof(oblist))
      NFN0("Hail whom?");

   actor("You call out" + how[1] + " at", oblist, ": "
      + "Ai na vedui Black Numenorean! Mae govannen!");
   target(" calls out" + how[1] + " at you: "
      + "Ai na vedui Black Numenorean! Mae govannen!", oblist);
   all2act(" calls out" + how[1] + " at", oblist, ": "
      + "Ai na vedui Black Numenorean! Mae govannen!");
   return 1;
}

