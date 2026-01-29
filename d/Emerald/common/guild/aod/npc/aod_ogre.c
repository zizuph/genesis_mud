/*
 *  /d/Emerald/common/guild/aod/npc/aod_ogre.c
 *
 *  This is the base file for Ogre npcs for the Army of Darkness.
 *
 *  Created June 2006, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit "/d/Emerald/std/ogre";

#include <formulas.h>
#include <login.h>
#include <macros.h>
#include <ss_types.h>
#include <time.h>
#include <wa_types.h>

/* definitions */
#define            OGRE_WEAPONS  ({ AOD_WEP_DIR + "forgeclub0", \
                                    AOD_WEP_DIR + "forgeclub1", \
                                    AOD_WEP_DIR + "forgeclub2", \
                                    AOD_WEP_DIR + "forgeclub3", \
                                 })
#define            GUILD_SUBLOC  GUILD_NAME + " subloc"


/* prototypes */
public void        create_aod_ogre();
public void        create_ogre();
public int         special_attack(object victim);
public string      adj1();
public string      adj2();
public string      describe();
public void        add_ogre_acts();
public void        add_ogre_asks();
public string      job_answer();
public string      army_answer();
public string      darkling_answer();
public string      trick_answer();
public void        catch_question(string question);
public int         not_here_func();
public string      default_answer();
public string      trick_answer();
public string      skull_answer();
public string      ogre_answer();
public void        add_introduced(string name);
public void        react_intro(object tp);
public void        return_object(object obj, object to);
public void        enter_inv(object ob, object from);
public mixed       wield(object weapon);
public void        leave_inv(object ob, object to);
public void        loot_corpse();
public void        loot_corpse2();
public int         notify_you_killed_me(object player);
public void        reset_crush();
public mixed       can_attack_with_occ_special(object target, string attack);
public void        ogre_crush(object target);
public void        ogre_crush2(object target);
public int         query_crush();


/* global variables */
static string       OrigQuestion;
public string       Job_Response;
public string       Ogre_Weapon = "";

/* A global variable to hold the id for the alarm used for the special */
static private int crush_alarm = 0;


public void         set_job_response(string s) { Job_Response = s; }
public string       query_job_response() { return Job_Response; }
public void         set_ogre_weapon(string s) { Ogre_Weapon = s; }
public string       query_ogre_weapon() { return Ogre_Weapon; }



/*
 * Function name:        create_aod_ogre
 * Description  :        dummy routine for inheriting files
 */
public void
create_aod_ogre()
{
} /* create_aod_ogre */


/*
 * Function name:        create_ogre
 * Description  :        set up some standard things for the
 *                       guild npcs
 */
public void
create_ogre()
{
    object   sh,
             rsh,
             guild_emblem,
             guild_emblem2;

    setuid();
    seteuid(getuid());

    add_name(AOD_NPC);
    remove_adj("ogre");
    remove_adj("ogrish");
    remove_adj("ogreish");
    add_adj( ({ adj1(), adj2() }) );
    set_long(describe());

    set_job_response("Huh ... ? Job? Me smash faces! Bring back skulls"
      + " for Darkling bosses!");

    set_default_answer(VBFC_ME("default_answer"));
    add_ogre_asks();
    add_ogre_acts();
    set_not_here_func("not_here_func");

    config_ogre(150);

    set_skill(SS_WEP_CLUB, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_PARRY, 75);
    set_skill(SS_DEFENCE, 75);
    set_skill(SS_AOD_WALLOP, 100);

    remove_prop(LIVE_M_NO_ACCEPT_GIVE);

    create_aod_ogre();

    if (Ogre_Weapon == "")
    {
        Ogre_Weapon = OGRE_WEAPONS[random(4)];
    }
    add_equipment(Ogre_Weapon);

    /* clone the guild emblem and move it to the player */    
    if (guild_emblem = clone_object(AOD_RACE_EMBLEM))
    {    
        guild_emblem->move(this_object(), 1);
        set_alarm(1.0, 0.0, &command("$wear belt"));
        guild_emblem->init();
    }

    /* clone the guild emblem and move it to the player */    
    if (guild_emblem2 = clone_object(AOD_EMBLEM))
    {    
        guild_emblem2->move(this_object(), 1);
        /* add the guild subloc */
        this_object()->add_subloc(GUILD_SUBLOC, AOD_SHADOW);
    }

    if (member_array(AOD_CMDSOUL, query_cmdsoul_list()) < 0)
    {
        add_cmdsoul(AOD_CMDSOUL);
        update_hooks();
    }
} /* create_ogre */


/*
 * Function name:        special_attack
 * Description  :        Lets give the npc the ability to use the
 *                       combat special of the guild.
 * Arguments    :        victim: the one we are fighting right now
 * Returns      :        0: we want the round to continue
 *                       1: we are done with this round
 */
public int
special_attack(object victim)
{
    if (!query_crush())
    {
        command("crush");
    }

    return 0;
} /* special_attack */


/*
 * Function name:        adj1
 * Description  :        provides a random adjective for the npc
 * Returns      :        str -- one from the list of adjectives
 */
public string
adj1()
{
    return one_of_list(
       ({ "huge", "towering", "enormous",
          "gigantic", "massive", "gargantuan",
          "immense", "monstrous", "mighty",
          "mountanous", "colossal", "mammoth" }) );
} /* adj1 */


/*
 * Function name:        adj2
 * Description  :        provides a random adjective for the npc
 * Returns      :        str -- one from the list of adjectives
 */
public string
adj2()
{
    return one_of_list(
       ({ "drooling", "black-skinned", "foul-smelling",
          "happy-faced", "flabby", "black-toothed",
          "cross-eyed", "sleepy", "two-headed",
          "one-eyed", "small-headed", "sweat-covered" }) );
} /* adj2 */


/*
 * Function name:        describe
 * Description  :        based on the adjective given to this orc,
 *                       we provide a nice long description
 * Returns      :        str -- the long description for the npc
 */
public string
describe()
{
    string *adj_array = query_adj(1);

    switch(adj_array[1])
    {
        case "drooling":
            return("Though vast and intimidating in size, this ogre"
              + " seems to be just standing around drooling. Perhaps "
              + this_object()->query_pronoun() + " has something"
              + " complicated to think about, like raindrops.\n");
            break;
        case "black-skinned":
            return("Beneath what it is wearing, this ogre has a skin so"
              + " black that it makes surrounding colors seem much"
              + " brighter. Its eyes, a dull white, glow with hatred.\n");
            break;
        case "foul-smelling":
            return("The stench which wafts from this ogre is completely"
              + " vile, as if to suggest that this creature had been"
              + " wallowing in its own refuse. The look in its eyes makes"
              + " clear the foul personality which accompanies the"
              + " smell.\n");
            break;
        case "happy-faced":
            return("Though it could probably knock over a house without"
              + " breaking a sweat, the expression on this ogre's face"
              + " is oddly sweet and happy. If you didn't know better"
              + " you'd think it might be ready to give you a hug.\n");
            break;
        case "flabby":
            return("This ogre is a ridiculous sight! Huge rolls of"
              + " flab roll down from its enormous shoulders like"
              + " layers of chocolate fudge on an ice-cream sundae."
              + " As it moves about, the fat undulates and swings to"
              + " and fro.\n"); 
            break;
        case "black-toothed":
            return("The hideous grin of this ogre reveals many"
              + " gnarled and broken teeth, all of which are coated with"
              + " some form of black substance. From the appearance of"
              + " things, it would seem as if this vile creature had been"
              + " gnawing on charcoal.\n");
            break;
        case "cross-eyed":
            return("Though clearly ferocious and deadly, one almost"
              + " has to stand back and laugh at the pathetic expression"
              + " on this ogre's face. Its eyes appear locked on the"
              + " bridge of its nose, completely crossed!\n");
            break;
        case "sleepy":
            return("This ogre is moving very slowly, its eyes heavily"
              + " lidded, and struggling to stay open. Perhaps it has"
              + " had trouble sleeping? Whatever the case, it still"
              + " looks as if it could kick a tree over.\n");
            break;
        case "two-headed":
            return("If this ogre is any indication, two heads are"
              + " definitely not better than one! Amusingly, the heads"
              + " do not seem to be getting along very well, and"
              + " continuously snarl and bite at eachother.\n");
            break;
        case "one-eyed":
            return("This ogre is a vertiable cyclops! Through some cruel"
              + " twist of nature, its face has been misshapen to include"
              + " only a single, swiveling eyeball in the center of"
              + " its forehead. Truly, this monster is the stuff of"
              + " nightmares!\n");
            break;
        case "small-headed":
            return("This ogre's head is clearly too small for its body."
              + " Perhaps it was dropped too many times as an infant,"
              + " but whatever the case, it now is a ridiculous sight"
              + " to behold. Of course, in the ogre world, this is"
              + " probably some kind of plus.\n");
            break;
        case "sweat-covered":
            return("This ogre is nasty! Steaming sweat is dripping from"
              + " every inch of its massive body, stinking up the"
              + " entire area, and causing its massive frame to"
              + " glisten.\n");
            break;
        default:
            return("Massive, powerful, and dumber than its own"
              + " toenails, this ogre is a typical specimen of its"
              + " horrible race. It towers above the area, standing"
              + " a good fifteen feet off the ground. It could probably"
              + " kill an ox with a single well-placed kick.\n");
            break;
    }

    return "";
} /* describe */


/*
 * Function name:        add_ogre_acts
 * Description  :        These are the standard acts defined for the
 *                       Army of Darkness npcs. They can be redefined in
 *                       inheriting npcs for more specific responses
 */
public void
add_ogre_acts()
{
    set_act_time(5);
    add_act("emote stomps around, looking confused.");
    add_act("emote bellows: Me hungry! Where me put horse?");
    add_act("emote bellows: Not like tricks! SMASH IF TRICK!");
    add_act("emote bellows: Elf faces best to smash. COME, ELF! ME"
      + " WANT SMASH FACE!");
    add_act("emote stares at " + this_object()->query_possessive()
      + " fingers, apparently fascinated.");
    add_act("emote stands still for a moment, drooling. After a bit"
      + " of time, " + this_object()->query_pronoun() + " blinks"
      + " a few times, and looks around as if confused.");
    add_act("emote sniffs " + this_object()->query_possessive()
       + " fingers and chuckles.");
    add_act("emote bellows: Head ripping best fun! Bosses give"
       + " treats when bring back!");
    add_act("emote bellows: Bosses tricky, but not bad tricky. Me"
       + " like bosses.");
} /* add_ogre_acts */


/*
 * Function name:        add_ogre_asks
 * Description  :        These are the standard asks defined for the
 *                       Army of Darkness npcs. They can be redefined in
 *                       inheriting npcs for more specific responses
 */
public void
add_ogre_asks()
{
    add_ask( ({ "guild", "army", "army of darkness" }),
        VBFC_ME("army_answer"));
    add_ask( ({ "darkling", "darklings", "boss", "bosses",
                "darking boss", "darkling bosses" }),
        VBFC_ME("darkling_answer"));
    add_ask( ({ "ogre", "ogres" }), 
        VBFC_ME("ogre_answer"));
    add_ask( ({ "trick", "tricks", "tricky" }),
        VBFC_ME("trick_answer"));
    add_ask( ({ "job", "occupation", "work", "career" }),
        VBFC_ME("job_answer"));
    add_ask( ({ "skull", "skulls", "head", "heads", "harvest" }),
        VBFC_ME("skull_answer"));
    add_ask( ({ "treat", "treats", "gift", "gifts", "juice",
                "mind juice", "mind fluid", "fluid" }),
        VBFC_ME("juice_answer"));
} /* add_ogre_asks */



/*
 * Function name:       army_answer
 * Description  :       response to an add_ask
 */
public string
army_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Army of Darkness powerful! Smash all faces!");
        break;
    case 1:
        command("say Army! Army!! ARMY!!!!!");
        break;
    case 2:
        command("say Army Destroy puny elves! Destroy! Destroy!");
        break;
    }
    return "";
} /* army_answer */


/*
 * Function name:        job_answer
 * Description  :        repond to an add_ask
 */
public string
job_answer()
{
    command("peer confus");
    command("say " + Job_Response);

    return "";
} /* job_answer */


/*
 * Function name:       darkling_answer
 * Description  :       response to an add_ask
 */
public string
darkling_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Bosses ... ? They give good treats. Make ogres"
              + " stronger!");
        break;
    case 1:
        command("say Bosses make ogre nervous. They dark and"
              + " tricky!");
    case 2:
        command("say C'mere ... tell secret. You not tell anyone ... "
              + " but ... BOSSES MAGIC!!! SHHHHHHHHHHHH!!!!!");
        command("peer nerv");
        break;
    }
    return "";
} /* darkling_answer */


/*
 * Function name:        ogre_answer
 * Description  :        respond to an add_ask
 */
public string
ogre_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Ogres are best! Smash faces for fun!");
        break;
    case 1:
        command("say Not mess with ogres! Not try to trick!");
    case 2:
        command("say Tricks make ogres ANGRY! SMASH FACES AND BONES!!");
        command("peer nerv");
        break;
    }
    return "";
} /* ogre_answer */


/*
 * Function name:       trick_answer
 * Description  :       response to an add_ask
 */
public string
trick_answer()
{
    switch (random(3))
    {
    case 0:
        command("say NO TRICKS! Be good and I not smash face.");
        break;
    case 1:
        command("grumble omin");
        command("say Tricks are for smashing. NOT TRICK!");
    case 2:
        command("say YOU MAKE TRICK, I MAKE PULP!!!");
        command("roar uncon");
        break;
    }
    return "";
} /* trick_answer */


/*
 * Function name:       skull_answer
 * Description  :       response to an add_ask
 */
public string
skull_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Me help with Harvest. Get good treats!");
        break;
    case 1:
        command("say Face smashing funnest ever! Head ripping second"
              + " best!");
    case 2:
        command("say Tukatog beating me ... it stupid! NEED MORE"
              + " ELF SKULLS!");
        command("sulk");
        break;
    }
    return "";
} /* skull_answer */


/*
 * Function name:       juice_answer
 * Description  :       response to an add_ask
 */
public string
juice_answer()
{
    switch (random(3))
    {
    case 0:
        command("say Mind Juice funny! Me big smarter now!");
        break;
    case 1:
        command("say Bosses give mind juice. Now can count toes!"
              + " ... ONE ... ... uh ... OTHER ONE ... uh ... ");
        command("explode");
        command("say NEED MORE TREATS!");
    case 2:
        command("say I drink up mind juice! Now not trick me. EVER!!");
        command("frown susp");
        break;
    }
    return "";
} /* juice_answer */


/*
 * Function name:       catch_question
 * Description  :       intercept /std/act/asking.c's catch_question() to:
 *                      1) strip leading "for", "about" and trailing "?"
 *                      2) remember the original question
 * Arguments:           string question -- whatever the player asked
 */
public void
catch_question(string question)
{
    string      *tmp_arr,                       /* preps/verbs of interest */
                stuff1, stuff2, stuff3;         /* tmp strings */

    if (objectp(query_attack()))
    {
        return; /* no answers if fighting */
    }

    OrigQuestion = question;
    if (strlen(question))
    {
        /* strip off leading "for", "about" and trailing " ?" */
        tmp_arr = ({ "for", "about" });
        if (parse_command(question, ({}), "%p %s", tmp_arr, stuff1))
        {
            question = stuff1;
        }
        if (sscanf(question, "%s ?", stuff1) ||
            sscanf(question, "%s?", stuff1))
        {
            question = stuff1;
        }
    }
    ::catch_question(question);
} /* catch_question */


/*
 * Function name:       not_here_func
 * Description  :       called when player asks question & leaves
 * Returns      :       0 -> don't answer the question
 */
public int
not_here_func()
{
     command("peer");
     command("shout WHERE YOU GO!? NOT TRY TO TRICK!!!");
     return 0;
} /* not_here_func */


/* 
 * Function name:       default_answer
 * Description  :       give the default response to questions
 */
public string
default_answer()
{
    command("peer stupid "+this_player()->query_real_name());
    command("say Uh ... what that mean?");
    return "";
} /* default_answer */


/* 
 * Function name:       name_answer
 * Description  :       respond to questions about name
 *
 */
public string
name_answer()
{
    object      tp = this_player();

    /* probably unnecessary, since we set not_here_func, but ... */
    if (!objectp(tp))
    {
        return "";
    }

    command("nod conf");
    command("say You, "+
        this_player()->query_race_name()+". Me, uh ... ... ");
    command("think");

    return "";
} /* name_answer */


/*
 * Function name:       add_introduced
 * Description  :       Add the name of a living who has introduced to us
 * Arguments    :       string name -- name of the introduced living
 */
public void
add_introduced(string name)
{
    /* wizards always know the npc name, so query_met() is true.
     * however, assume that if a wiz intro'd, we should respond
     */
    if (interactive(this_player()) &&
        CAN_SEE_IN_ROOM(this_object()) &&
        CAN_SEE(this_object(), this_player()) &&
        (!this_player()->query_met(query_name()) ||
         this_player()->query_wiz_level()))
    {
        set_alarm(1.0, 0.0, &react_intro(this_player()));
    }
} /* add_introduced */


/*
 * Function name:        react_intro
 * Description  :        respond to introduction
 * Arguments    :        object tp -- the person who intro'd
 */
public void
react_intro(object tp)
{
    if (environment(tp) != environment())
    {
        command("emote looks around as if trying to find someone.");
        return;
    }

    if (query_real_name() != "ogre")
    {
        command("introduce me");
        return;
    }

    switch(random(6))
    {
    case 0:
        command("peer blank "+tp->query_real_name());
        break;
    case 1:
        command("say That name too long.");
        break;
    case 2:
        command("say Don't tell name! I busy thinking.");
        break;
    case 3:
        command("say Why you here? I not want name.");
        break;
    case 4: 
        command("say That name stupid. It ... ... STUPID!!!");
        break;
    case 5:
        command("say Stop trying to trick! I not say name. Too hard.");
        break;
    }
} /* react_intro */


/* 
 * Function name:        return_object
 * Description  :        have npcs give things they are given back
 *                       to players
 * Arguments    :        object obj - the object given
 *                       object to  - the player who gave it
 */
public void
return_object(object obj, object to)
{
    command("say Not want!");
    command("give " + OB_NAME(obj) + " to " + OB_NAME(to));
    if (environment(obj) == this_object())
    {
       command("drop " + OB_NAME(obj));
    }
} /* return_object */


/* 
 * Function name: enter_inv
 * Description:   Called when objects enter this container or when an
 *                object has just changed its weight/volume/light status.
 * Arguments:     ob: The object that just entered this inventory
 *                from: The object from which it came.
 *
 * We want to allow ogres to wield 2-handers one-handed.
 */
public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);

    if (!objectp(ob) || !objectp(from) || !living(from))
    {
        if (ob->weapon_type())
        {
            if (ob->query_hands() == W_BOTH)
            {
                ob->add_prop(AOD_WIELD_PROP, 1);
                ob->set_hands(W_ANYH);
            }
        }
        return;
    }

    set_alarm(0.5, 0.0, &return_object(ob, from));
} /* enter_inv */


/*
 * Function name:        loot_corpse
 * Description  :        The ogre does what ogres do to corpses.
 */
public void
loot_corpse()
{
    command("rip head from corpse");
    set_alarm(2.0, 0.0, loot_corpse2);
} /* loot_corpse */


/*
 * Function name:        loot_corpse2
 * Description  :        The ogre does what ogres do to corpses.
 */
public void
loot_corpse2()
{
    command("collect skull");
} /* loot_corpse2 */


/*
 * Function name:        notify_you_killed_me
 * Description  :        Called when this npc kills something. We want
 *                       our ogres to do what ogres do.
 * Arguments    :        object player: the one who was killed
 * Returns      :        1
 */
public int
notify_you_killed_me(object player)
{
    set_alarm(2.0, 0.0, loot_corpse);

    if (player->query_npc())
    {
        return 1;
    }

    write_file(AOD_LOG_DIR + "npc_kills",
        TIME2FORMAT(time(), "mm/dd/yyyy") + " (" + ctime(time())[11..18]
      + ") " + capitalize(player->query_name()) + " was killed by "
      + query_real_name() + "\n");

    return 1;
} /* notify_you_killed_me */


/*
 * Functions below are added from:
 *     /d/Emerald/common/guild/aod/aod_shadow.c
 ***********************************************************************
 */


/*
 * Function name:        wield
 * Description  :        Redefinition to prevent Ogres from wielding
 *                       one handed weapons, and to give them a way
 *                       to wield 2-handers in a single hand.
 * Arguments    :        object weapon - the weapon to wield
 * Returns      :        string - error message (weapon not wielded)
 *                       1 - successs (weapon wielded)
 */
public mixed
wield(object weapon)
{
    if (weapon->query_prop(AOD_WIELD_PROP))
    {
        return ::wield(weapon);
    }

    return "This weapon is too small for your hands!\n";
} /* wield */


/* 
 * Function name: leave_inv
 * Description:   Called when objects leave this container or when an
 *                object is about to change its weight/volume/light status.
 * Arguments:     ob: The object that just left this inventory.
 *                to: Where it went.
 *
 * See previous function header. This mask is to deal with the same issues.
 */
public void
leave_inv(object ob, object to)
{
    if (ob->query_prop(AOD_WIELD_PROP))
    {
        ob->set_hands(W_BOTH);
        ob->remove_prop(AOD_WIELD_PROP);
    }

    ::enter_inv(ob, to);
} /* leave_inv */


/*
 * Function name:        race_sound
 * Description  :        make it so that others hear ogres "boom" when they
 *                       speak.
 * Returns      :        string - the verb to hear
 */
public string
race_sound()
{
    return "booms";
} /* race_sound */


/*
 * Function name:        actor_race_sound
 * Description  :        make it so that others hear ogres "boom" when they
 *                       speak.
 * Returns      :        string - the verb to hear
 */
public string
actor_race_sound()
{
    return "boom";
} /* actor_race_sound */

/*
 * And then, from:
 *     /d/Emerald/common/guild/aod/race_shadow.c
 ***********************************************************************
 */


/*
 * Function name:        query_m_in
 * Description  :        we mask this function to give ogres a unique
 *                       entrance message.
 * Returns      :        string - the m_in description
 */
public string
query_m_in()
{
    return "stomps in";
} /* query_m_in */


/*
 * Function name:        query_m_out
 * Description  :        we mask this function to give ogres a unique
 *                       exit message.
 * Returns      :        string - the m_out description
 */
public string
query_m_out()
{
    return "stomps off, leaving";
} /* query_m_out */


/*
 * Function name: enter_env
 * Description  : This function is called each time this object enters a
 *                new environment. If you mask it, be sure that you
 *                _always_ call the ::enter_env(dest, old) function.
 * Arguments    : object dest - the destination we are entering.
 *                object old  - the location we came from. This can be 0.
 *
 * I'm redefining this function to allow ogres to stomp around so loudly
 * that their footfalls echo into adjascent rooms.
 */
public void
enter_env(object dest, object old)
{
    mixed  *exit_array = environment(this_player())->query_exit(),
           *room_array = allocate(sizeof(exit_array) / 3),
           *direction_array = allocate(sizeof(exit_array) / 3);
    int     i, n, d;
    string  stomp_text, direction;

    /* If rooms are not connected by normal exit code, we assume that
     * the player has been teleported somehow, or moved in some non-
     * standard way. So, we don't have them broadcast stomps.
     */
    if (old)
    {
        if (member_array(file_name(old), exit_array) == -1)
        {
            ::enter_env(dest, old);
            return;
        }
    }

    n = 0;
    for (i = 1; i < sizeof(exit_array); i = i + 3)
    {
        direction_array[n] = exit_array[i];
        room_array[n] = exit_array[i-1];
        n++;
    }

    for (i = 0; i < sizeof(direction_array); i++)
    {
        switch(direction_array[i])
        {
            case "north":
                direction = "the south";
                break;
            case "northeast":
                direction = "the southwest";
                break;
            case "east":
                direction = "the west";
                break;
            case "southeast":
                direction = "the northwest";
                break;
            case "south":
                direction = "the north";
                break;
            case "southwest":
                direction = "the northeast";
                break;
            case "west":
                direction = "the east";
                break;
            case "northwest":
                direction = "the southeast";
                break;
            case "up":
                direction = "below";
                break;
            case "down":
                direction = "above";
                break;
            default:
                direction = "somewhere nearby";
                break;
        }

        if (old) /* sanity check! */
        {
            if (room_array[i] != file_name(old))
            {
                tell_room(room_array[i], "You hear thunderous footfalls"
                  + " approaching from " + direction + ".\n");
            }
        }
    }

    ::enter_env(dest, old);
} /* enter_env */


/*
 * Function name: leave_env
 * Description  : This function is called each time this object leaves an
 *                old environment. If you mask it, be sure that you
 *                _always_ call the ::leave_env(dest, old) function.
 * Arguments    : object old  - the location we are leaving.
 *                object dest - the destination we are going to. Can be 0.
 *
 * I'm redefining this function to allow ogres to stomp around so loudly
 * that their footfalls echo into adjascent rooms. Also, this can help
 * prevent bouncing with special attacks.
 */
public void
leave_env(object old, object dest)
{
    mixed  *exit_array = old->query_exit(),
           *room_array = allocate(sizeof(exit_array) / 3),
           *direction_array = allocate(sizeof(exit_array) / 3);
    int     i, n, d;
    string  stomp_text, direction;

    /* If rooms are not connected by normal exit code, we assume that
     * the player has been teleported somehow, or moved in some non-
     * standard way. So, we don't have them broadcast stomps.
     */
    if (dest)
    {
        if (member_array(file_name(dest), exit_array) == -1)
        {
            ::leave_env(dest, old);
            return;
        }
    }

    n = 0;
    for (i = 1; i < sizeof(exit_array); i = i + 3)
    {
        direction_array[n] = exit_array[i];
        room_array[n] = exit_array[i-1];
        n++;
    }

    for (i = 0; i < sizeof(direction_array); i++)
    {
        switch(direction_array[i])
        {
            case "north":
                direction = "the south";
                break;
            case "northeast":
                direction = "the southwest";
                break;
            case "east":
                direction = "the west";
                break;
            case "southeast":
                direction = "the northwest";
                break;
            case "south":
                direction = "the north";
                break;
            case "southwest":
                direction = "the northeast";
                break;
            case "west":
                direction = "the east";
                break;
            case "northwest":
                direction = "the southeast";
                break;
            case "up":
                direction = "below";
                break;
            case "down":
                direction = "above";
                break;
            default:
                direction = "somewhere nearby";
                break;
        }

        if (dest) /* sanity check! */
        {
            if (room_array[i] != file_name(dest))
            {
                tell_room(room_array[i], "From " + direction + " you hear"
              + " thunderous footfalls fading into the distance.\n");
            }
        }
    }

    ::leave_env(dest, old);
} /* leave_env */


/*
 * And, finally, from:
 *     /d/Emerald/common/guild/aod/special_attacks.c
 **********************************************************************
 */


/*
 * Function name:        reset_crush
 * Description  :        set the crush_alarm variable to 0, indicating
 *                       that a crush is no longer being prepared.
 */
public void
reset_crush()
{
    remove_alarm(crush_alarm);
    crush_alarm = 0;
} /* reset_crush */


/*
 * Function name: can_attack_with_occ_special
 * Description:   See if we are allowed to attack someone
 * Arguments:     object target - the thing we want to attack
 *                string attack - a name for the attack we want to use
 * Returns:       A string describing why we cannot attack or 0 if
 *                we can attack
 */
mixed
can_attack_with_occ_special(object target, string attack)
{
    mixed    why;
    object   who = this_object(),
            *enemies = who->query_enemy(-1);

    if (!target || !living(target) || !present(target, environment(who)))
    {
        return attack + " whom?\n";
    }

    if (who->query_prop(LIVE_I_ATTACK_DELAY) ||
        who->query_prop(LIVE_I_STUNNED))
    {
        return "You are too stunned to " + attack + ".\n";
    }
 
    if (stringp(why = target->query_prop(OBJ_M_NO_ATTACK)) ||
        stringp(why = environment(target)->query_prop(ROOM_M_NO_ATTACK)))
    {
        return why;
    }
    else if (why)
    {
        return "You sense a force protecting " + 
            target->query_the_name(who) + ".\n";
    }

    /* Someone might try defining this to block all special attacks */
    if (target->query_not_attack_me(who, -1))
    {
        /* A message should be given by query_not_attack_me(), so
         * no need to specify one here.
         */
        return "";
    }

    if ((!who->query_npc()) && (who->query_met(target)) &&
        !(who == target->query_attack()) &&
        (who->query_prop(LIVE_O_LAST_KILL) != target))
    {
        who->add_prop(LIVE_O_LAST_KILL, target);
        return "Attack " + target->query_the_name(who) + 
            "?!? Please confirm by trying again.\n";
    }
 
    if (!F_DARE_ATTACK(who, target))
    {
        /* The dis check should only be done if the player is not 
         * currently fighting the target. If they have been attacked
         * by the target, they should not be prevented from using
         * the special.
         */
        if (member_array(target, enemies) == -1)
        {
            return "Ogre or not, you don't dare to attack.\n";
        }
    }

    
    return 0;
}

/*
 * Function name: ogre_crush
 * Description:   Start the 'crush' attack.
 * Arguments:     object target - the person to attack
 */
public void
ogre_crush(object target)
{
    object who = this_object();
    int    cdelay;

    /* 15 second base delay plus a random 10 extra seconds with the
     * greater potiential to be lower the higher your "crush" skill
     * is. Avg is 20 seconds at max skills.
     */
    cdelay = (15 + (10 - (random(who->query_skills(
              SS_AOD_WALLOP)) / 10)));

    who->catch_msg("Your ogre mind starts trying to recall how to"
      + " manage a crushing blow.\n");
    
    crush_alarm = set_alarm(itof(cdelay), 0.0, &ogre_crush2(target));

    /* Initiate battle with the target */
    who->attack_object(target);

    /* reveal the player if he is hiding */
    who->reveal_me(0);
} /* ogre_crush */

 
/*
 * Function name: ogre_crush2
 * Description:   This is the unarmed combat attack for the Army of
 *                Darkness guild. It provides a 5% chance of knocking
 *                someone's shield to the ground in addition to the
 *                damage it causes.
 * Arguments:     object target - the target of the attack
 */
public void
ogre_crush2(object target)
{
    int     hitsuc, 
            phurt,
            ogrewc,
            wielded = 0; /* 0 - unarmed,
                          * 1 - one weapon,
                          * 2 - two weapons */
    string  how, 
            how2,
            how3,
            why,
            club_name;
    object  attacker = this_object(),
           *weapons = attacker->query_weapon(-1);

    /* The player must have moved between rooms ... no bouncing! lets
     * cancel the attack.
     */
    if (!crush_alarm)
    {
        return;
    }

    crush_alarm = 0;

    if (sizeof(weapons))
    {
        if (weapons[0]->query_wt() != W_CLUB)
        {
            attacker->catch_msg(
                "ERRRRR ... ?!? What's this fancy thing? " + capitalize(
                LANG_ADDART(weapons[0]->short())) + "?? How is an ogre"
              + " supposed to crush anything using that? Find a club"
              + " or use your fists!\n");
            return;
        }

        if(sizeof(weapons) > 1)
        {
            club_name = weapons[0]->short() + " and "
                      + weapons[1]->short();
            wielded = 2;
            if (weapons[1]->query_wt() != W_CLUB)
            {
                attacker->catch_msg(
                    "ERRRRR ... ?!? What's this fancy thing? "
                  + capitalize(LANG_ADDART(weapons[1]->short()))
                  + "?? How is an ogre supposed to"
                  + " crush anything using that? Find a club or"
                  + " use your fists!\n");
                return;
            }
        }
        else
        {
            club_name = weapons[0]->short();
            wielded = 1;
        }
    }
 
    /* make sure the target is still in the same room as the attacker */
    if (!target || (environment(target) != environment(attacker)))
    {
        attacker->catch_msg("You suddenly realize there is no one"
          + " here to crush. They must have slipped away!\n");
        return;
    }

    /* Has target become invalid somehow? */
    if (stringp(why = can_attack_with_occ_special(target, "crush")))
    {
        attacker->catch_msg(why);
        return;
    }

    /* The formulae below are much the same in terms of damage
     * potential as the gladiator charge (I believe.) The difference
     * is that we do not base things on dex. Ogres rely on their
     * strength and size. Ogres aren't the fastest or most dextrous
     * beings. Therefore, we use at flat value of 65 as the to_hit
     * chance.
     */
    if ((hitsuc = attacker->query_combat_object()->cb_tohit(-1, 65,
        target)) > 0)
    {
        /* attack successful! */
        phurt = target->hit_me(3 * 
           (F_PENMOD(MIN(attacker->query_stat(SS_STR), 150) / 5,
            attacker->query_skill(SS_AOD_WALLOP)) + 50),
            W_BLUDGEON, attacker, -1)[0];
    }
    else
    {
        /* attack missed. */
        phurt = target->hit_me(hitsuc, 0, attacker, -1)[0];
    }
 
    /* add fatigue */
    if (attacker->query_fatigue() < 5)
    {
        attacker->heal_hp(-(5 - attacker->query_fatigue()));
        attacker->set_fatigue(0);
        attacker->catch_msg("Ooof! Your ogre limbs are feeling tired and"
          + " drained.\n");
    }
    else
    {
        attacker->add_fatigue(-5);
    }

    if (phurt >= 0) 
    {
        /* remove some of the attacker's panic */
        attacker->add_panic(-3 - phurt / 5);

        how = "!\n" + QCTNAME(target) + " seems ";
        how2 = "!\nYou feel ";

        /* Give combat descriptions based on the percent damage done.
         * Because players spend such a huge percentage of their time
         * on combat, lets add lots of variety. */
        switch (phurt)
        {
            case 0:
                how += "to have avoided any damage.";
                how2 = "You seem to have avoided any damage.";
                break;
            case 1:
                how3  = "slightly rattled.";
                how2 += how3;
                how  += how3;
                break;
            case 2:
                how3  = "somewhat rattled.";
                how2 += how3;
                how  += how3;
                break;
            case 3:
                how3  = "slightly battered.";
                how2 += how3;
                how  += how3;
                break;
            case 4:
                how3  = "somewhat battered.";
                how2 += how3;
                how  += how3;
                break;
            case 5:
                how3  = "seriously battered.";
                how2 += how3;
                how  += how3;
                break;
            case 6:
                how3  = "somewhat bashed.";
                how2 += how3;
                how  += how3;
                break;
            case 7:
                how3  = "seriously bashed.";
                how2 += how3;
                how  += how3;
                break;
            case 8:
                how3  = "thoroughly bashed.";
                how2 += how3;
                how  += how3;
                break;
            case 9:
                how3  = "clearly throttled.";
                how2 += how3;
                how  += how3;
                break;
            case 10:
                how3  = "thoroughly throttled.";
                how2 += how3;
                how  += how3;
                break;
            case 11:
                how3  = "absolutely throttled.";
                how2 += how3;
                how  += how3;
                break;
            case 12:
                how3  = "rather pulverized.";
                how2 += how3;
                how  += how3;
                break;
            case 13:
                how3  = "thoroughly pulverized.";
                how2 += how3;
                how  += how3;
                break;
            case 14:
                how3  = "horribly pulverized.";
                how2 += how3;
                how  += how3;
                break;
            case 15..20:
                how3  = "fairly devastated.";
                how2 += how3;
                how  += how3;
                break;
            case 21..33:
                how3  = "seriously devastated.";
                how2 += how3;
                how  += how3;
                break;
            case 34..49:
                how3  = "thoroughly devastated.";
                how2 += how3;
                how  += how3;
                break;
            case 50..99:
                how3  = "completely devastated.";
                how2 += how3;
                how  += how3;
                break;
            default:
                how = " like an avalanche of death and destruction! Ribs"
                    + " crack and bones snap as "
                    + target->query_possessive() + " body is mashed"
                    + " into a lifeless pulp!";
                how2 = " like an avalanche of death and destruction! The"
                     + " last thing you remember is the sound of your"
                     + " own spine splintering as hot pain washes over"
                     + " your mind!";
                break;
        }

        switch (wielded)
        {
            default:
            case 0:
                attacker->catch_msg("SLAM!!! You bring your mighty fists"
                  + " down on " + target->query_the_name(attacker)
                  + how + "\n");
                target->catch_msg("SLAM!!! "
                  + attacker->query_The_name(target) + " brings "
                  + attacker->query_possessive() + " mighty fists"
                  + " down on you" + how2 + "\n");
                attacker->tell_watcher("SLAM!!! " + QCTNAME(attacker)
                  + " brings " + attacker->query_possessive()
                  + " mighty fists down on " + QTNAME(target)
                  + how + "\n", target);
                break;
            case 1:
                attacker->catch_msg("SWAT!!! You swing your " + club_name
                  + " down into " + target->query_the_name(attacker)
                  + how + "\n");
                target->catch_msg("SWAT!!! "
                  + attacker->query_The_name(target) + " swings "
                  + attacker->query_possessive() + " " + club_name
                  + " down into you" + how2 + "\n");
                attacker->tell_watcher("SWAT!!! " + QCTNAME(attacker)
                  + " swings " + attacker->query_possessive() + " "
                  + club_name + " down into " + QTNAME(target)
                  + how + "\n", target);
                break;
            case 2:
                attacker->catch_msg("BLAM!! BLAM!! One after the other"
                  + " you bring your " + club_name + " hurtling down"
                  + " on " + target->query_the_name(attacker)
                  + how + "\n");
                target->catch_msg("BLAM!! BLAM!! One after the other "
                  + attacker->query_The_name(target) + " brings "
                  + attacker->query_possessive() + " " + club_name
                  + " hurtling down on you" + how2 + "\n");
                attacker->tell_watcher("BLAM!! BLAM!! " + QCTNAME(target)
                  + " brings " + attacker->query_possessive() + " "
                  + club_name + " hurtling down on " + QTNAME(target)
                  + how + "\n", target);
                break;
        }

        if (target->query_hp() <= 0)
        {
            target->do_die(attacker);
        }

        return;
    }
            
    /* We get here if the attack missed */

    /* add some panic to the attacker */
    attacker->add_panic(1);
    attacker->add_attack_delay(5);

    switch (wielded)
    {
        default:
        case 0:
            attacker->catch_msg("THUD!!! Your mighty fists smash"
              + " harmlessly into the ground, completely missing "
              + target->query_the_name(attacker) + ".\n");
            target->catch_msg("THUD!!! " + attacker->query_The_name(target)
              + " brings " + attacker->query_possessive() + " mighty fists"
              + " crashing harmlessly into the ground beside you.\n");
            attacker->tell_watcher("THUD!!! " + QCTNAME(attacker)
              + " brings " + attacker->query_possessive() + " mighty fists"
              + " crashing harmlessly into the ground beside "
              + QTNAME(target) + ".\n", target);
            break;
        case 1:
            attacker->catch_msg("WHOOSH!! Your " + club_name + " sails "
              + " cleanly over " + target->query_the_name(attacker)
              + "'s head, missing " + target->query_objective()
              + " entirely.\n");
            target->catch_msg("WHOOSH!! " + attacker->query_The_name(target)
              + "'s " + club_name + " sails cleanly over your head,"
              + " missing you entirely.\n");
            attacker->tell_watcher("WHOOSH!! " + QCTNAME(attacker)
              + "'s " + club_name + " sails cleanly over "
              + QTNAME(target) + "'s head, missing "
              + target->query_objective() + " entirely.\n", target);
            break;
        case 2: 
            attacker->catch_msg("WHUMP!! WHUMP!! Your " + club_name
              + " plow into the ground on either side of "
              + target->query_the_name(attacker) + ", missing "
              + target->query_objective() + " completely.\n");
            target->catch_msg("WHUMP!! WHUMP!! "
              + attacker->query_The_name(target) + "'s " + club_name
              + " plow into the ground on either side of you, missing"
              + " you completely.\n");
            attacker->tell_watcher("WHUMP!! WHUMP!! " + QCTNAME(attacker)
              + "'s " + club_name + " plow into the ground on either side"
              + " of " + QTNAME(target) + ", missing "
              + target->query_objective() + " completely.\n", target);
            break;
    }
} /* ogre_crush2 */


/*
 * Function name: query_crush
 * Description:   See if we are currently preparing to perform
 *                the special attack
 * Returns:       1 / 0 - preparing / not preparing
 */
public int
query_crush()
{
    return !!crush_alarm;
} /* query_crush */