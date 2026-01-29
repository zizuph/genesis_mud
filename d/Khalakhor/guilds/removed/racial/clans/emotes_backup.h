/* File         : /d/Khalakhor/guilds/racial/clans/emotes.h
 * Creator      : Tomas@Genesis
 * Date         : September 2000         
 * Purpose      : Emotes for the Clans of Khalakhor Racial Guild
 * Related Files: /d/Khalakhor/sys/defs.h
 *                /d/Khalakhor/guilds/racial/clans/guild.h
 * Comments     :
 * Modifications: 
 */
#include <composite.h>
#include <const.h>
#include <cmdparse.h>
#include <filter_funs.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>
#include <tasks.h>
#include <guild.h>
#include <macros.h>
#include <state_desc.h>
#include <options.h>
#include <std.h>
#include <filter_funs.h>
#include <formulas.h>

#define race    this_player()->query_race_name()

#define HE_OB      oblist[0]->query_pronoun()
#define HIS_OB     oblist[0]->query_possessive()
#define HIM_OB     oblist[0]->query_objective()




/*
cgreet <target> - (to guild members) With a cheerful smile, Tomas says to
                  you, "The top o' the mornin' to ya'."  You 
                  instinctively reply, "And the rest o' the day to you."

                  (to others) Tomas eyes you warily as he salutes you 
                  with a flourish of his <sword>.

ctoast <string> - Tomas raises his mug, proposing a toast <string>


cassist - Tomas cries out, "For Clan <clan name>!" as he assists his
          teammates/clan member against <opponent>

claugh - Tomas throws his head back and laughs merrily.

cbare <target> - Tomas bares his teeth at <target>.  <target> backs up
                 a few steps in response.


cthrust - Tomas thrusts his <sword> into the ground, declaring he will
          follow no further.

cmock <target> - Tomas mocks <target> for his/her stupidity.

cslap <target> - Tomas slaps <target> on the back and roars with 
                 laughter.

ckilt <target> - Tomas turns around and lifts his kilt, mooning <target>.

csing - Tomas sings in Gaelic.

cblessing <target> - Tomas smiles softly at <target> and declares, "May
                     you live to bury me." (mostly father to son)

cbye <target> - Tomas bids you farewell, saying, "May the Lord protect
                you and guide your steps."

*/

/*
 * Function name : classist
 * Description   : Emote to assist a teammate.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 * Comments      : Many thanks to Gwyneth for the following emote!
*/
int
cl_assist(string str)
{
    object *obs;
    object friend;
    object victim;
    int    index;
    string *assist;
    string fr;
    string str2;
    mixed  tmp;
    string MYCLAN;
    MYCLAN  = (SERVER->query_clan(this_player()->query_real_name()));

    if (!CAN_SEE_IN_ROOM(this_player()))
    {
        notify_fail("You can't see anything here.\n");
        return 0;
    }

    if (this_player()->query_ghost())
    {
        notify_fail("Umm yes, killed. That's what you are.\n");
        return 0;
    }

    if (!stringp(str))
    {
        if (!sizeof(obs = this_player()->query_team_others()))
        {
            notify_fail("Assist whom? You are not in a team.\n");
            return 0;
        }

        obs = ({ this_player()->query_leader() }) - ({ 0 }) + obs;

        for (index = 0; index < sizeof(obs); index++)
        {
            if ((environment(this_player()) == environment(obs[index])) &&
              (objectp(victim = obs[index]->query_attack())))
            {
                friend = obs[index];
                break;
            }
        }

        if (!objectp(friend))
        {
            notify_fail("None of your team members is in combat.\n");
            return 0;
        }
    }
    else
    {
        obs = parse_this(str, "[the] %l");

        if (sizeof(obs) > 1)
        {
            notify_fail(break_string("Be specific, you can't assist " +
                COMPOSITE_LIVE(obs) + " at the same time.", 76) + "\n");
            return 0;
        }
        else if (sizeof(obs) == 0)
        {
            notify_fail("Assist whom?\n");
            return 0;
        }

        friend = obs[0];
    }

    if (friend == this_player())
    {
        write("Sure! Assist yourself!\n");
        return 1;
    }

    if (member_array(friend, this_player()->query_enemy(-1)) != -1)
    {
        write(break_string("Help " + friend->query_the_name(this_player()) +
            " to kill you? There are easier ways to commit seppuku!", 76) +
          "\n");
        return 1;
    }

    victim = friend->query_attack();
    if (!objectp(victim))
    {
        write(friend->query_The_name(this_player()) +
          " is not fighting anyone.\n");
        return 1;
    }

    if (environment(victim) != environment(this_player()))
    {
        notify_fail("The main target of " +
          victim->query_the_name(this_player()) + " is not in this room.\n");
        return 0;
    }

    if (member_array(victim, this_player()->query_team_others()) != -1)
    {
        notify_fail("But " + victim->query_the_name(this_player()) +
          " is a team with you.\n");
        return 0;
    }

    if (this_player()->query_attack() == victim)
    {
        write("You are already fighting " +
          victim->query_the_name(this_player()) + ".\n");
        return 1;
    }

    if (tmp = environment(this_player())->query_prop(ROOM_M_NO_ATTACK))
    {
        if (stringp(tmp))
            write(tmp);
        else
            write("You sense a divine force preventing your attack.\n");
        return 1;
    }

    if (tmp = victim->query_prop(OBJ_M_NO_ATTACK))
    {
        if (stringp(tmp))
            write(tmp);
        else
            write("You feel a divine force protecting this being, your " +
              "attack fails.\n");
        return 1;
    }

    if ((!this_player()->query_npc()) &&
      (this_player()->query_met(victim)) &&
      (this_player()->query_prop(LIVE_O_LAST_KILL) != victim))
    {
        write("Attack " + victim->query_the_name(this_player()) +
          "?!? Please confirm by trying again.\n");
        this_player()->add_prop(LIVE_O_LAST_KILL, victim);
        return 1;
    }

    this_player()->reveal_me(1);
    /*
    * Check if we dare!
    */
    if (!F_DARE_ATTACK(this_player(), victim))
    {
        write("Umm... no! You do not have enough self-discipline to dare!\n");
        return 1;
    }

    str = "";

    if (IS_MEMBER(friend))
        str = "fellow kinsman";
    else if (TP->query_leader() == friend)
        str = "leader";
    else if (member_array(friend, TP->query_team()) >= 0)
        str = "party";
    else
        assist = ({ "Ok.",
          TP->query_The_name(victim)+" attacks you!",
          TP->query_The_name(friend)+" assists you and attacks "+
          victim->query_the_name(friend)+".",
          QCTNAME(TP) + " assists " + QTNAME(friend) + " and attacks " + 
          QTNAME(victim)+"." });

    if (str != "")

        assist = ({ "You cry out: for Clan " + MYCLAN + 
        "! Then render assistance to your " + str + ", " + friend->query_the_name(TP) + 
        ", against " + HIS_HER(friend) + " enemy " + victim->query_the_name(TP) +
          ".", TP->query_the_name(victim) + " cries out, for Clan " + MYCLAN + "! " +
        "Then assists " + friend->query_the_name(victim) + " against you!",
          "You hear " + TP->query_the_name(friend) + " cry out, for Clan " + MYCLAN + 
        "! as " +HE_SHE(TP)+ " renders assistance against "+
          victim->query_the_name(friend) + ".", QTNAME(TP) +
          " shouts, for Clan " + MYCLAN + "! Then renders assistance " + 
        "to " + QTNAME(friend) + " in attacking " + QTNAME(victim) + "." });


    say(assist[3] + "\n", ({ this_player(), friend, victim }) );
    tell_object(victim, assist[1]+"\n");
    tell_object(friend, assist[2]+"\n");

    this_player()->attack_object(victim);
    this_player()->add_prop(LIVE_O_LAST_KILL, victim);

    write(assist[0]+"\n");
    return 1;
}


public int
cl_brand(string str)
{
    object *oblist,
           *weplist;
    string wepshort;

    NF("clbrand who?\n");

    if (!str || !strlen(str))
        return 0;

    weplist = (TP->query_weapon(-1));

    if (!sizeof(weplist))
    {
        NF("You must be wielding a weapon to clbrand someone.\n");
        return 0;
    }

    wepshort = weplist[0]->short();

    oblist = parse_this(str, " %l");

    if (!sizeof(oblist))
        return 0;

    actor("You brandish your " + wepshort + " at", oblist, " while declaring " +
          "that " + HE + " is no better than a common goblin.");
    targetbb(" brandishes " +HIS+ " " + wepshort + " at you, saying you are " +
             "no better than a common goblin.",  oblist);
    all2actbb(" brandishes" +HIS+ " " + wepshort + " at", oblist, " and " +
             "declares them no better than a common goblin.");
    return 1;
}





/*
      cbye <target> - Tomas bids you farewell, saying, "May the Lord protect
                      you and guide your steps." 
*/
int
cl_bye(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Say goodbye to whom?\n");
        return 0;
    }

    actor("You bid", oblist, " farewell, saying, May the Lord protect "+
      "you and guide your steps.");
    all2act(" bids", oblist, " farewell, saying May the lord protect "+
      "you and guide your steps.");
    target(" bids you farewell, saying, May the Lord protect " +
      "you and guide your steps.", oblist,"");
    return 1;
}


/*
        clcross - Tomas makes the sign of the cross.
*/
int
cl_cross()
{
    write("You make the sign of a cross in the air before you.\n");
    allbb(" draws the sign of a cross in the air before you.");
    return 1;
}


int
cl_curse(string str)
{
    object *oblist;

    oblist = parse_this(str, "[the] %l");

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Curse whom?\n");
        return 0;
    }

    actor("You sneer at", oblist, " then spit in their direction and say, " +
       "May the worms feast on your rotting corpse, and may your bloody soul " +
       "never find rest.");
    all2act(" sneers as " +HE+" spits at ", oblist, ", May the worms " +
       "feast on your rotting corpse, and may your bloody soul never rest.");
    target(" sneers as " +HE+ " spits in your direction then says, " +
       "May the worms feast on your rotting corpse, and may your bloody " +
       "soul never find rest.", oblist);
    return 1;
}


/*
        cldare - Tomas stares at you defiantly, daring you to raise your weapon
                 against him.
*/
int 
cl_dare(string str)
{
  object *oblist;

  oblist = parse_this(str, "[before] / [at] / [to] [the] %l");
  if(!sizeof(oblist))
  {
    notify_fail("Dare whom?\n");
    return 0;
  }

  actor("You stare at ",oblist," defiantly, daring " +HIM+ " to raise " +
         HIS + " weapons against you.\n",1);
  all2actbb(" stares at ",oblist," defiantly, daring " +HIM+ " to raise " +
              HIS + " weapons against " + HIM +".", oblist);
  targetbb(" stares at you defiantly, daring you to raise your " +
           "weapons against " +HIM+".",oblist);
  return 1;
}



/*
      cenjoy - Tomas smiles blissfully as he inhales the scent of the heather
               crushed underfoot.
*/
int
cl_enjoy()
{
    write("You smile blissfully as you inhale the fresh scent of the heather " +
          "crushed underfoot.\n");
    allbb(" smiles blissfully as he inhales the fresh scent of the heather " +
          "crushed underfoot.");
    return 1;
}



public int
cl_greet(string str)
{
    object *oblist,
           *weplist;
    string wepshort;

    NF("clgreet who?\n");

    if (!str || !strlen(str))
        return 0;

    weplist = (TP->query_weapon(-1));

    if (!sizeof(weplist))
    {
        NF("You must be wielding a weapon to clgreet someone.\n");
        return 0;
    }

    wepshort = weplist[0]->short();

    oblist = parse_this(str, " %l");

    if (!sizeof(oblist))
        return 0;

    actor("You eye", oblist, " warily then greet " +HIM+ 
          " with a quick flourish of your " + wepshort + ".");
    targetbb(" eyes you warily then greets you with a quick flourish of " +
        HIS + " " + wepshort + ".", oblist);
    all2actbb(" eyes", oblist, "warily then greets " +HIM+
        " with a quick flourish of " + HIS + " " + wepshort + ".");
    return 1;
}




/*
 * Function name : clintro
 * Description   : Emote to introduce oneself.
 * Arguments     : string str
 * Returns       : Returns 0 on failure, 1 on success.
 * Comments      : Many thanks to Gwyneth for the following emote!
*/
public int
cl_intro(string str)
{
    int size, index;
    object *oblist, *targets, *others = ({}), *knows_member = ({}),
           *known_by_member = ({}), *unknown_to_member = ({});
    string title, arg;
 
    oblist = FILTER_OTHER_LIVE(all_inventory(environment(this_player())));
 
    if (!sizeof(oblist))
    {
        notify_fail("Introduce yourself to whom?\n");
        return 0;
    }
    else if (!strlen(str))
    {
        targets = oblist;
        others = ({});
    }
    else
    {
        targets = parse_this(str, "[to] [the] %l");
 
        if (!sizeof(targets))
        {
            notify_fail("Introduce yourself to whom?\n");
            return 0;
        }
 
        others = (oblist - targets);
    }
 
    for (index = 0, size = sizeof(targets); index < size; index++)
    {
        if (this_player()->query_met(targets[index]->query_real_name()))
            known_by_member += ({ targets[index] });
        if (targets[index]->query_met(this_player()->query_real_name()) &&
          !targets[index]->query_npc())
            knows_member += ({ targets[index] });
    }
 
    unknown_to_member = targets - known_by_member;
 
    title = capitalize(this_player()->query_real_name()) + " " +
        this_player()->query_title();
 
    this_player()->reveal_me(1);
 
    say(QCTNAME(this_player()) + " introduces " +
        this_player()->query_objective() + "self to " +
        COMPOSITE_LIVE(targets) + ".\n", targets + ({ this_player() }));


    say(QCTNAME(this_player()) + " says, Tis a pleasure to meet thee. You are " +
        "in the presence of "+ title + "!\n", others + ({ this_player() }));

    write("You say, Tis a pleasure to meet thee, " +
        COMPOSITE_LIVE(targets) + ". You are in the presence of " + title + "!\n");
/*
    if (sizeof(unknown_to_member))
    {
        say(QCTNAME(this_player()) + " looks at you expectantly.\n",
            others + known_by_member + ({ this_player() }));
        if (sizeof(unknown_to_member) > 1)
        {
            write("You look around expectantly at those you don't know.\n");
        }
        else
        {
            write("You look at " +
                unknown_to_member[0]->query_the_name(this_player()) +
                " expectantly.\n");
        }

    }
 */
    targets -= knows_member;
 
    for (index = 0, size = sizeof(targets); index < size; index++)
    {
        targets[index]->add_introduced(this_player()->query_real_name());
    }
 
    return 1;
}



string
cl_jig(string dance)
{
    int guildstat;
    guildstat = TP->query_base_stat(6);
    dance = "";

    switch (guildstat)
    {
       case 1..24: 
           dance = "awkwardly"; 
           break;
       case 25..48:
           dance = "clumsily";
           break;
       case 49..72:
           dance = "expertly";
           break;
       case 73..96:
           dance = "gracefully";
           break;
       case 97..1000:
           dance = "flawlessly";
           break;
    }          

   write("You dance the jig " + dance + ".\n");
   allbb(" dances the jig " + dance + ".");
   return "";
}



/*
    claugh - Tomas throws his head back and laughs merrily.
*/
int 
cl_laugh()
{
    write("You throw your head back, laughing merrily.\n");
    allbb(" throws " +HIS+ " head back and laughs merrily.");
    return 1;
}



int
cl_mock(string str)
{

    object *oblist;

    oblist = parse_this(str, "[the] %l", ACTION_INGRATIATORY);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("clmock whom?\n");
        return 0;
    }

    actor("You mock", oblist, " for being so stupid!",1);
    all2act(" mocks", oblist, " for being so stupid!", "", 0, 1 );
    target(" mocks you for being so stupid!",oblist, "");
    return 1;
}


/*
        cmutter - Tomas mutters something under his breath about the "Little
                  People".
*/
cl_mutter()
{
   write("You mutter something under your breath about the Little People.\n");
   allbb(" mutters something under " +HIS+" breath about the Little People.");
   return 1;
}


public int
cl_raise(string str)
{
    object *oblist,
           *weplist;
    string wepshort;

    NF("clraise who?\n");

    if (!str || !strlen(str))
        return 0;

    weplist = (TP->query_weapon(-1));

    if (!sizeof(weplist))
    {
        NF("You must be wielding a weapon to clraise someone.\n");
        return 0;
    }

    wepshort = weplist[0]->short();

    oblist = parse_this(str, " %l");

    if (!sizeof(oblist))
        return 0;

    actor("You raise your " + wepshort + " pointing it at",oblist, ".");
    targetbb(" raises " +HIS+ " " + wepshort + " then points it at you.", oblist);
    all2actbb(" raises his " + wepshort + " then points it at", oblist, ".");
    return 1;
}





/*
      crub - Tomas rubs the fabric of his tartan between thumb and forefinger
             as he thinks of family.
*/
int 
cl_rub()
{
    write("You rub the fabric of your tartan between your thumb and " +
          "forefinger thinking of your family.\n");
    allbb(" rubs the fabric of " +HIS+ " tartan between " +HIS+ " thumb and " +
          "forefinger.");
    return 1;
}



/*
       clpray - Tomas looks up and mumbles a quiet prayer to the Lord.  
                Strengthened by the renewal of his faith, he seems ready to face 
                anything.
 */  
int
cl_pray()
{
    write("You look up and mumble a quiet prayer to the Lord. " +
          "Feeling strengthened by the renewal of your faith, you stand " +
          "confidently ready to face anything.\n");
    allbb(" looks up and mumbles a quiet prayer. Strengthened by the " +
          "renewal of " + HIS + " faith, " + HE +" seems ready to face anything.");
    return 1;
}


/*
     clraise - Tomas raises his <weapon> into the air, declaring victory for
             Clan <clan name>.
*/
int
cl_victory(object *weapons)
{
    object wepdesc;
    string MYCLAN;
    
    MYCLAN  = (SERVER->query_clan(this_player()->query_real_name()));
    weapons = (TP->query_weapon(-1));

     if (!sizeof(weapons))
     {
        write("You need to wield your weapon first.\n");
        return 1;
     }

     wepdesc = weapons[random(sizeof(weapons))]->query_short();
        write("You raise your " + wepdesc + " into the air, declaring victory " +
              "for Clan " + MYCLAN + "!\n");
        allbb(" raises " + HIS + " " + wepdesc + " into the air, " +
              "declaring victory for Clan " + MYCLAN + "!"); 
        return 1;

}


/*
 *    clsay
 */
int
cl_say(string str)
{
    object *oblist;
    int i;

    if (!strlen(str))
    {
        notify_fail("You wish to say what in Gaelic?\n");
        return 0;
    }

    oblist = FILTER_PLAYERS(all_inventory(environment(this_player())));
    oblist -= ({ this_player() });

    write("You say in Gaelic: " + str + "\n");

    for (i = 0; i < sizeof(oblist); i++)
    {
        if ((IS_MEMBER(oblist[i])) || oblist[i]->query_wiz_level())
        {
            oblist[i]->catch_tell(this_player()->query_The_name(oblist[i]) +
                " speaks in Gaelic saying: " + str + "\n");
        }
        else
        {
            oblist[i]->catch_tell(this_player()->query_The_name(oblist[i]) +
                " speaks in Gaelic.  You marvel at the sheer beauty of the " +
             "tongue, but have no idea what " +HE+ " just said.\n");
        }
    }

    return 1;
}


public int
cl_salute(string str)
{
    object *oblist,
           *weplist;
    string wepshort;

    NF("clsalute who?\n");

    if (!str || !strlen(str))
        return 0;

    weplist = (TP->query_weapon(-1));

    if (!sizeof(weplist))
    {
        NF("You must be wielding a weapon to clsalute someone.\n");
        return 0;
    }

    wepshort = weplist[0]->short();

    oblist = parse_this(str, " %l");

    if (!sizeof(oblist))
        return 0;

    actor("You salute", oblist, " with a flourish of your " +
        wepshort + ".");
    targetbb(" salutes you with a flourish of " +
        HIS + " " + wepshort + ".", oblist);
    all2actbb(" salutes", oblist, " with a flourish of " +
        HIS + " " + wepshort + ".");
    return 1;
}



/*
 * cscan  -- look beyond someone for farie rings.
 */
int
cl_scan(string str)
{

    object *oblist;

    oblist = parse_this(str, "[the] %l", ACTION_INGRATIATORY);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("Look beyond whom?\n");
        return 0;
    }

    actor(" You look behind", oblist, " scanning the area for faerie rings",1);
    all2act(" looks past", oblist, " as if scanning the area for faerie rings", "", 0, 1 );
    target(" looks past you, scanning the area for faerie rings.",oblist, "");
    return 1;
}


/*
      csearch - Tomas looks off into the distance for possible signs of danger.
*/
int
cl_search()
{
   write("You look off into the distance for possible signs of danger.\n");
   allbb(" looks off into the distance for possible signs of danger.");
   return 1;
}


/*
      clscratch - Tomas scratches his chin, deep in thought.
*/
int
cl_scratch()
{
    write("You scratch your chin while you think.\n");
    allbb(" scratches " +HIS+ " chin, deep in thought.");
    return 1;
}



int
cl_slap(string str)
{

    object *oblist;

    oblist = parse_this(str, "[the] %l", ACTION_INGRATIATORY);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("clslap whom?\n");
        return 0;
    }

    actor(" You slap", oblist, " on the back and roar with laughter.",1);
    all2act(" slaps", oblist, " on the back and roars with laughter.", "", 0, 1 );
    target(" slaps you on the back, roaring with laughter.",oblist, "");
    return 1;
}


/*
    clthrust -
*/

int
cl_thrust(object *weapons)
{
    object wepdesc;
    weapons = (TP->query_weapon(-1));

     if (!sizeof(weapons))
     {
        write("You need to wield your weapon first.\n");
        return 1;
     }

     wepdesc = weapons[random(sizeof(weapons))]->query_short();
        write("You turn your " + wepdesc + " upside down pointing " +
              "its tip on the ground and state that you wont go " +
              "a step further.\n");
        allbb(" promptly turns " + HIS + " " + wepdesc + " upside down, " +
              "pointing its tip on the ground and states that " +HE+ " isn't " +
              "going a step further."); 
        return 1;

}


/*
   cltight -  Tomas's eyes blaze with a fierce light as he tightens his grip
              on his <weapon>.
*/
int
cl_tight(object *weapons)
{
    object wepdesc;
    weapons = (TP->query_weapon(-1));

    if (!sizeof(weapons))
     {
        NF("You need to wield your weapon first.\n");
        return 0;
     } 

      wepdesc = weapons[random(sizeof(weapons))]->query_short();

      write("Your eyes blaze intensely as you tighten your grip " +
            "on your " +wepdesc+ ".\n");
      allbb("'s eyes blaze intensely as " + HE + " tightens " + HIS +
            " grip on "+ HIS + " "+wepdesc+".", 0, 1);

    return 1;
}



int
cl_trace(object *weapons)
{
    object wepdesc;
    weapons = (TP->query_weapon(-1));
    wepdesc = weapons[random(sizeof(weapons))]->query_short();

     if (!sizeof(weapons))
     {
        write("You need a weapon for that first.\n");
        return 0;
     }

        write("You slowly trace your finger along your " + wepdesc + ".\n");
        say(QCTNAME(TP) + " slowly traces " + HIS + " finger along " +HIS+ " " + wepdesc + 
           ".");
        return 1;
}


int
cl_warcry(string str)
{
 
  object *oblist;
  oblist = parse_this(str, "[the] %l", ACTION_INGRATIATORY);

  if(!strlen(str))
  {
     write("You shout out the ancient warcry: EULALIA!!! As you throw " +
           "yourself at your enemies.\n");
     allbb(" shouts out in Gaelic: EULALIA!!! As " +HE+ " charges " +
           "into battle.\n");
     return 1;
  }

    if (!sizeof(oblist))
    {
         if (strlen(parse_msg))
         {
             write(parse_msg);
             return 1;
         }

        notify_fail("clwarcry whom?\n");
        return 0;
    }

    actor("You shout out the ancient warcry: EULALIA!!! As you rush " +
          "towards", oblist, "!");
    all2act(" shouts out EULALIA!!! as " +HE+ " rushes towards", oblist, "!");
    target(" shouts EULALIA!!! as " +HE+ " rushes towards you!",oblist);
    return 1;
}


int
cl_wipe(string str, object *weapons) 
{
    object wepdesc;
    weapons = (TP->query_weapon(-1));

    if (!present("corpse",ENV(TP))) 
    {
        write("There aren't any corpses in which to clean your weapon on!\n");
        return 1;
    }


    if (!sizeof(weapons))
    {
        NF("You need to wield your weapon first.\n");
        return 0;
    } 

      wepdesc = weapons[random(sizeof(weapons))]->query_short();
    
    write("You wipe the blood and gore from your " + wepdesc + " on the corpse before you.\n");
    allbb(" kneels down and wipes the blood and gore from " +HIS+ " " + wepdesc + 
          " on the corpse before " +HIM+ ".");
    return 1;
}


int
cl_yawn(string str)
{

    object *oblist;

    oblist = parse_this(str, "[the] %l", ACTION_INGRATIATORY);

    if (!sizeof(oblist))
    {
        if (strlen(parse_msg))
        {
            write(parse_msg);
            return 1;
        }

        notify_fail("clyawn at whom?\n");
        return 0;
    }

    actor(" You yawn at", oblist, ". Clearly, " + HE_OB + 
          " poses no real threat.");
    all2act(" yawns at", oblist, ". Clearly, " + HE_OB + 
          " poses no real threat.");
    target(" yawns at you. Clearly, " + HE + " see's you as no real threat.",oblist);
    return 1;
}
