/*
 * Explorer Club Emotes
 * 
 * Tomas -- Dec. 1999
 *
 * 2005-09-01 - Cotillion
 *   AoB/AoD/AoP has discussed this club and come to the conclusion that
 *   only letting wiz appointed members allow others to join is not allowed
 *   in the guild rules.
 *   So I have made all members able to accept others again.
 */

#pragma save_binary

#include <wa_types.h>
#include <composite.h>
#include <cmdparse.h>
#include <macros.h>
#include "/d/Terel/include/Terel.h"

#define SOULDESC(x)     (this_player()->add_prop(LIVE_S_SOULEXTRA, x))
#define PRO(x)   (x->query_pronoun())
#define PS(x)    (x->query_possessive())

#ifndef SCROLLING_LOG
#define SCROLLING_LOG(file, entry)   ((file_size(file) > 10000) ? \
          (rm(file) && write_file(file, ctime(time()) + ": " + entry + "\n")) : \
          (write_file(file, ctime(time()) + ": " + entry + "\n")))
#endif


/* Some filter functions */
private int male (object ob) { return ob->query_gender() == G_MALE; }
private int female (object ob) { return ob->query_gender() == G_FEMALE; }

void response(string offer, int answer);



                     /*    E M O T I O N S    */

/*
 *     echaos
 */
int
e_chaos(string str)
{
    if (!IS_MEMBER(TP))
    {
        NF("You're not a Explorer of the Arcane!\n");
        return 0;
    }        

    write("You try to take control of the chaotic " +
       "situation at hand.\n");
    allbb(" tries to bring order to the chaos that " +
       "has developed.");
    return 1;
}



/*
expjourney  A-Blake prepares himself for the long
     road ahead of him.
     M-You begin to ready yourself in preparation 
     of your long journey.
*/
int
e_journey(string str)
{
    if (!IS_MEMBER(TP))
    {
        NF("You're not a Explorer of the Arcane!\n");
        return 0;
    }        

    write("You begin to ready yourself in preparation " +
       "of your long journey.\n");
    allbb(" prepares for the long road ahead.");
    return 1;
}



/*
expnofind   A-Blake begins a hasty search of the area but
     only seems to find himself more frustrated.
     M-You search everywhere in frustration but 
     suprisingly find nothing.
*/
int
e_nofind(string str)
{
    if (!IS_MEMBER(TP))
    {
        NF("You're not a Explorer of the Arcane!\n");
        return 0;
    }        

    write("You search everywhere in frustration but " +
       "surprisingly find nothing.\n");
    allbb(" begins a hasty search of the area but " +
       "comes up empty-handed.");
    return 1;
}


/*
expobserve   A-Blake begins looking all around himself,
     seemingly searching for something or someone.
     (or Blake looks all around the area...)
     M-You begin taking careful note of your surroundings,
     looking for anything unusual.
*/
int
e_observe(string str)
{
    if (!IS_MEMBER(TP))
    {
        NF("You're not a Explorer of the Arcane!\n");
        return 0;
    }        

    write("You begin taking careful note of your surroundings " +
       "looking for anything unusual.\n");
    allbb(" begins looking all around, seemingly searching " +
       "for something.");
    return 1;
}



/*
 *     ereel
 */
int
e_reel(string str)
{
    if (!IS_MEMBER(TP))
    {
        NF("You're not a Explorer of the Arcane!\n");
        return 0;
    }        

    write("You reel in delight as you uncover " +
       "another mystery of the arcane.\n");
    allbb(" reels in delight as "+ PRO(TP) +" uncovers " +
       "another mystery of the arcane.");
    return 1;
}


/*
      esmell 
*/
int e_smell(string str)
{
  object *oblist;

  if(!strlen(str))
  {
    write("You wrinkle your nose as you smell something putrid.\n");
    allbb("'s nose wrinkles as "+ PRO(TP) +" smells something.");
    return 1;
  }

  oblist = parse_this(str, "[before] / [at] / [to] [the] %l");
  if(!sizeof(oblist))
  {
    notify_fail("You esmell whom?\n");
    return 0;
  }

  actor("You can't stand the disgusting odour coming from",oblist,".\n");
  targetbb(" wrinkles "+ PS(TP) +" nose at the stench coming "
          +"from your presence.", oblist);
  all2actbb(" nose wrinkles as "+ PRO(TP) +" catches an " +
            "unpleasant stench coming from",oblist,".");
  return 1;
}



/*
 *     esmile 
 */
int
e_smile(string str)
{
    if (!IS_MEMBER(TP))
    {
        NF("You're not a Explorer of the Arcane!\n");
        return 0;
    }        

    write("You smile revealing wisdom of ages past.\n");
    allbb(" smiles revealing wisdom of ages past.");
    return 1;
}


/*
expquest   A-Blake looks determined to continue onward 
     with his quest.
     M-You resolve to finish your task at hand before 
     doing anything else.
*/
int
e_quest(string str)
{
    if (!IS_MEMBER(TP))
    {
        NF("You're not a Explorer of the Arcane!\n");
        return 0;
    }        
    write("You resolve to finish your task at hand " +
       "before doing anything else.\n");
    allbb(" looks determined to continue onward with his " +
       "quest.");
    return 1;
}



/*
 *     estare 
 */
int
e_stare(string str)
{
    if (!IS_MEMBER(TP))
    {
        NF("You're not a Explorer of the Arcane!\n");
        return 0;
    }        

    write("You stare distantly as you attempt to recall something " +
       "learned in the past.\n");
    allbb(" stares distantly as if trying to remember something.\n");
    return 1;
}


/*
expthump <person>   A-Blake twists his gold signet
     ring around and thumps <person> on the head.
     M-You try to thump <person> on the head with 
      your gold signet ring.
*/
int e_thump(string str)
{
  object *oblist;
 
  oblist = parse_this(str, "[before] / [at] / [to] [the] %l");
  if(!sizeof(oblist))
  {
    notify_fail("Who do you want to Ethump?\n");
    return 0;
  }

  actor("You thump",oblist," on the head with your " +
        "golden signet ring.\n");
  targetbb(" twists "+PS(TP)+" golden signet ring around then " +
           "thumps you on the head.", oblist);
  all2actbb(" twists "+ PS(TP) +" golden signet ring around then " +
            "thumps",oblist," on the head.");
  return 1;
}



public int
other_members(object ob)
{
    if (IS_MEMBER(ob) && present(EXPLORER_RING, ob) && ob != TP)
        return 1;
    return 0;
}



public int
e_who(string str)
{
    object *mm;
    int i;
    mm = filter(users(), other_members);

    if (!sizeof(mm)) {
        TP->catch_msg("You do not sense the presence of " +
                      "other Explorers.\n");
        return 1;
    }
    TP->catch_msg("You sense the presence of:\n");
    for (i=0; i<sizeof(mm); i++)
         TP->catch_msg(capitalize(mm[i]->query_real_name()) + " " +
                   mm[i]->query_title() + "\n");
    return 1;
}



/* Thank you Shiva for your example of the following */
public int
e_accept(string str)
{ 
    object accept_me, yn_ob;
    object *arg;
  
    if (!strlen(str) || (sizeof(arg = parse_this(str, "[the] %l")) != 1))
    {
        notify_fail("Accept whom?\n");
        return 0;
    }
  
    if (IS_MEMBER(arg[0]))
    {
        write(arg[0]->query_name(this_player()) + 
            " is already an Explorer!\n");
        return 1;
    }
  
  
    actor("You offer a position within the Explorers to", arg, ".");
    target(" offers you a position " +
       "within the Terellian Explorers of Arcanum.\nDo you accept? (Yes/No)\n", arg);
    all2actbb(" takes", arg, " to the side and asks " + 
        "something.\n");
    
    setuid();
    seteuid(getuid());
  
    /* This is where I use Shiva's ~shiva/open/yes_no.c code thanks Shiva */
    if (accept_me = clone_object(GUILDOBJ))
    {

        if (yn_ob = clone_object(TEREL_DIR + "std/yes_no"))
        {
            if (yn_ob->get_answer(arg[0], &response(this_player()->query_real_name(),), 20.0))
            {
                return 1;
            }
            else
            {
                yn_ob->remove_object();
                accept_me->remove_accept_me();
            }
        }
        else
        {
            accept_me->remove_accept_me();
        }
    }
    actor("For some reason you choose not to Accept", arg, ".");
    return 1;
}

  

public int
e_retire(string str)
{
    object ring;
    string name;
  
    NF("Retire what?\n");
    if (!str || str != "ring") 
    return 0;

    ring = present(EXPLORER_RING, TP);
    
    if (TP->query_wiz_level())
    {
        write("You'll have to remove the cmdsoul manually.\n");
        if (objectp(ring)) 
            ring->remove_object();
        return 1;
    }        

    /* does not work for wizards */
    if (!TP->remove_cmdsoul(EXPLORER_SOUL)) 
    {
        if (objectp(ring)) 
            ring->remove_object();
        write("It doesn't seem you were a member anyway.\n");
        return 1;
    }
    else 
    {
        ring = present(EXPLORER_RING, TP);
        if (objectp(ring)) 
        {
            ring->remove_object();
            write("You drop the ring which breaks into small pieces as it " +
               "hits the ground.\n");
            say(QCTNAME(TP) + " left the Explorers of Arcanum.\n");
            SCROLLING_LOG(EXPLORER_LOG, capitalize(TP->query_real_name())+ 
                " left the Explorers. <--");
        return 1;
        }

    }
}

void
response(string offer, int answer)
{
    object ring;

    if (answer == 1)
    {
        write("You joined the Terellian Explorers of Arcanum.\n " +
              "Type: exphelp for more information.\n");
        SCROLLING_LOG(EXPLORER_LOG, capitalize(TP->query_real_name())+ 
            " joined the Explorers. <-- (" + offer + ")");
        ring = clone_object("/d/Terel/clubs/explorer/explorer_ring");
        ring->move(TP, 1);
    }
}
