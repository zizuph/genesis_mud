/* 
 * Divorce judge - this 
 * 
 * created by Aridor 03/27/94 
 * 
 * updated 08-December-2000 by Shadowlynx 
 *    - To allow a single person to force a divorce under special 
 *      circumstances (ie partner gone over 70 days, or refuses) 
 * 
 * some re-organisation, updates and documentation added, 
 * 1-2/2001, Maniac 
 * 
 */ 

#include "../local.h"

#pragma strict_types

inherit M_FILE
inherit "/lib/trade";

#include "/d/Genesis/homes/relation.h"
#include <ss_types.h>
#include <macros.h>
#include <cmdparse.h>
#include <std.h>
#define DIVORCELOG    (TDIR + "log/divorcelog")
#define MARRIAGE_DIR "/d/Emerald/common/marriage/"


/*prototypes*/
string my_answer();

object pers1, pers2; 
string reason1, reason2; 

EMOTE_HOOK


void
clean_me_up()
{
    pers1 = 0;
    pers2 = 0;
}


void
create_krynn_monster()
{
    config_default_trade();
    set_name("devirco");
    set_race_name("human");
    set_adj("friendly");
    add_adj("sad");
    add_name("judge");

    set_long(BS("This is the divorce judge of Palanthas. His sad task " +
	"is to divorce couples who, for some reason or other, " +
	"cannot live together anymore.", SL));

    set_stats(({60, 64, 65, 80, 111, 60}));
    set_hp(5000);

    add_ask(({"fee","payment","money","pay"}), VBFC_ME("answer_pay"));
    add_ask(({"divorce"}),VBFC_ME("divorce_answer"));
    add_ask(({"special divorce","special","circumstances","special circumstances"}),
      VBFC_ME("special_divorce_answer"));
    add_ask(({"syntax"}),"say The syntax is 'divorce me from <who> because <reason>'.",1);
    add_ask(({"form","sign form","to sign form"}),
      "say I don't sign forms, I just divorce couples here.",1); 
    set_default_answer(VBFC_ME("my_answer")); 
    set_introduce(1); 
    add_emote_hook("bow", 1.0, &command("bow")); 

    clean_me_up();
}


/* 
 * Function:     special_divorce_answer 
 * Description:  A response to an ask, this makes the judge 
 *               explain divorce fees.  
 */ 
string
answer_pay()
{
    command("say Yes, you have to pay the fee of 16 platinum coins to get divorced.");
    command("say Both persons involved will be charged 8 platinum coins each if " +
      "the divorce was successful.");
    command("say In the event of divorce under special circumstances, the 16 platinum " +
      "coins must be covered by the person alone.");
    return "";
}


void 
init_living() 
{
    ::init_living(); 
    ADA("divorce"); 
}


/* 
 * Function:     my_answer 
 * Description:  A response to an ask which the judge has no 
 *               knowledge of. 
 */ 
string 
my_answer() 
{ 
    set_alarm(1.0,0.0, &command("shrug")); 
    set_alarm(3.0,0.0, &command("say I cannot help you with that.")); 
    return ""; 
} 


/* 
 * Function:     special_divorce_answer 
 * Description:  A response to an ask, this makes the judge 
 *               explain divorces in special circumstances, 
 *               including the price. 
 */ 
string 
special_divorce_answer() 
{ 
    command("say A divorce under special circumstances is if your" + 
      " spouse is not able to make it to this event."); 
    command("say Typically," + 
      " a valid reason is if your spouse is no longer around, has" + 
      " been lost in the void for awhile, or simply refuses to" + 
      " allow a divorce to happen."); 
    command("say The fee for a special divorce is 16 platinum coins."); 
    return ""; 
} 


/* 
 * Function:     divorce_answer 
 * Description:  A response to an ask, this makes the judge 
 *               explain divorces in general. 
 * 
 */ 
string 
divorce_answer() 
{ 
    command("say You have come to the right person."); 
    command("say My sad job is to divorce couples who do not want " + 
      "to stay together any more."); 
    command("say Both partners have to be present so I can perform " + 
      "my duties."); 
    command("say There is a fee to pay for the service, though."); 
    command("say Under special circumstances, a divorce can be conducted " + 
      "with only one person present."); 
    return ""; 
} 


/* 
 * Function:  remove_marriage_items 
 * Description:  removes the marriage-related items from 
 *               one or two people. The person2 argument 
 *               may be zero. If a ring argument (ring1 or ring2) 
 *               is zero, the inventory of the corresponding 
 *               person is checked. 
 * 
 */ 
private varargs void 
remove_marriage_items(object person1, object ring1, 
                      object person2, object ring2) 
{ 
    object *tmp; 

    if (objectp(person1)) { 
        if (!objectp(ring1)) { 
            if (pointerp(tmp = FIND_STR_IN_OBJECT("marriage ring", person1)) 
                && sizeof(tmp)) 
                ring1 = tmp[0]; 
        } 
        ring1->remove_object(); 
        person1->remove_cmdsoul(MARRIAGE_DIR + "wedding_soul"); 
        person1->update_hooks(); 
    } 

    if (objectp(person2)) { 
        if (!objectp(ring2)) { 
            if (pointerp(tmp = FIND_STR_IN_OBJECT("marriage ring", person2)) 
                && sizeof(tmp)) 
                ring2 = tmp[0]; 
        } 
        ring2->remove_object(); 
        person2->remove_cmdsoul(MARRIAGE_DIR + "wedding_soul"); 
        person2->update_hooks(); 
    } 
} 



/* 
 * Function:     are_married 
 * Description:  Returns 1 if the people are married, 0 otherwise. 
 *               The arguments person1 and person2 may either be 
 *               real names or player objects. The arguments 
 *               ring1 and ring2 must be their corresponding ring 
 *               objects. 
 * 
 */ 
int 
are_married(mixed person1, object ring1, mixed person2, object ring2) 
{ 
   string n1, n2; 

   if (objectp(person1)) 
       n1 = person1->query_real_name(); 
   else if (stringp(person1)) 
       n1 = person1; 
   else 
       return 0; 

   if (objectp(person2)) 
       n2 = person2->query_real_name(); 
   else if (stringp(person2)) 
       n2 = person2; 
   else 
       return 0; 

   return (QUERY_HAVE_A_RELATION(n1, n2) && 
           L(ring1->query_person()) == n2 && 
           L(ring2->query_person()) == n1); 
} 


/* 
 * Function:    perform_divorce 
 * Description: Realises a divorce for players who are both present. 
 */ 
void 
perform_divorce() 
{
    object *ring1, *ring2; 

    command("emote has finished reading and writing and turns " + 
        "towards you."); 
    ring1 = FIND_STR_IN_OBJECT("marriage ring", pers1); 
    ring2 = FIND_STR_IN_OBJECT("marriage ring", pers2); 

    if (sizeof(ring1) > 1 || sizeof(ring2) > 1) 
    { 
        command("say Oh my, everything seems to go wrong today."); 
        command("say I must take back your marriage ring. Since " + 
                "one of you has more than one marriage ring, I " + 
                "cannot divorce you."); 
        command("shrug"); 
        clean_me_up(); 
        return; 
    } 

    if (sizeof(ring1) < 1 || sizeof(ring2) < 1)
    { 
        command("say Oh my, everything seems to go wrong today."); 
        command("say I must take back your marriage ring. Since " + 
                "you don't have one, I cannot divorce you."); 
        command("shrug"); 
        clean_me_up(); 
        return; 
    } 

    if (!are_married(pers1, ring1[0], pers2, ring2[0])) 
    { 
        command("hmm"); 
        command("frown"); 
        command("say It appears you have not been married " + 
            "correctly - or not at all."); 
        command("say I'm afraid I can't divorce you now."); 
        clean_me_up(); 
        return; 
    } 

    command("nod"); 
    command("smile sadly"); 
    command("say Ah, yes, I have found the registration."); 

    if (!pers1 || !pers2 || (E(pers1) != E(TO)) || (E(pers2) != E(TO))) 
    { 
        command("peer all"); 
        command("say Where have you gone??"); 
        command("say Well, I cannot proceed then."); 
        command("shrug"); 
        clean_me_up(); 
        return; 
    } 

    command("emote makes a short remark on his scroll."); 
    if (!sizeof(pay(13824, pers1, "platinum gold silver copper", 1, 0)) || 
        !sizeof(pay(13824, pers2, "platinum gold silver copper", 1, 0))) 
    { 
        command("say Hmmmm, you don't seem to have enough money to " + 
            "pay the price."); 
        command("say Well, I cannot divorce you now."); 
        command("shrug"); 
        clean_me_up(); 
        return; 
    } 

    seteuid(getuid(TO)); 
    pay(13824, pers1, "platinum gold silver copper", 0, 0); 
    pay(13824, pers2, "platinum gold silver copper", 0, 0); 
    pers1->catch_tell("You pay the necessary sum of 8 platinum coins.\n"); 
    pers2->catch_tell("You pay the necessary sum of 8 platinum coins.\n"); 

    (MARRIAGE_DIR + "marriage_manager")->divorce(pers1->query_real_name()); 

    remove_marriage_items(pers1, ring1[0], pers2, ring2[0]); 

    REMOVE_PLAYER_FROM_RELATION(pers1->query_real_name()); 

    /* how about:  CHANGE_RELATION_TYPE(pers1->query_real_name(), "divorced"); 
		  CHANGE_RELATION_TYPE(pers2->query_real_name(), "divorced"); 
      ???????*/ 
    write_file(DIVORCELOG, ctime(time())[4..23] + ": " + 
        pers1->query_name() + " because " + reason1 + "; " + 
        pers2->query_name() + " because " + reason2 + ".\n"); 
    command("say I hereby declare you divorced."); 
    clean_me_up(); 
} 


/* 
 * Function:    perform_single_divorce 
 * Description: Realises a divorce for players only one of whom 
 *              is present. 
 */ 
void 
perform_single_divorce(object pers, string spouse, string reason) 
{ 
    object *ring = FIND_STR_IN_OBJECT("marriage ring", pers); 
    string spouse_test; 

    command("emote has finished reading and writing and turns " + 
        "towards you."); 

    if (!ring || sizeof(ring) == 0) 
    { 
        command("say You don't seem to have a marriage ring. " + 
            "I'm afraid I cannot divorce you now."); 
        return; 
    } 

    if (sizeof(ring) > 1) 
    { 
        command("say Oh my, everything seems to go wrong today."); 
        command("say I must take back your marriage ring. Since you have " + 
            "more than one marriage ring, I cannot divorce you."); 
        command("shrug"); 
        return; 
    } 

    if (!(spouse_test = ring[0]->query_person()) || spouse != spouse_test || 
        !QUERY_HAVE_A_RELATION(pers->query_real_name(), spouse)) 
    { 
        if (!spouse_test) 
            spouse_test = "'unknown'"; 
        command("say The marriage ring you are wearing indicates that you " + 
            "are married to " + C(spouse_test) + ", not to " + C(spouse) + 
            " from whom you intend to be divorced.\n"); 
        command("say I'm afraid I cannot divorce you."); 
        return; 
    } 

    if (!sizeof(pay(27648, pers, "platinum gold silver copper", 1, 0))) 
    { 
        command("say Hmmmm, you don't seem to have enough money to " + 
                "pay the price."); 
        command("say Well, I cannot divorce you now."); 
        command("shrug"); 
        return; 
    } 

    pay(27648, pers, "platinum gold silver copper", 0 , 0); 
    pers->catch_tell("You pay the necessary sum of 16 platinum coins.\n"); 

    (MARRIAGE_DIR + "marriage_manager")->divorce(pers->query_real_name()); 
    remove_marriage_items(pers, ring[0]); 
    REMOVE_PLAYER_FROM_RELATION(pers->query_real_name()); 
    /*how about:  CHANGE_RELATION_TYPE(pers->query_real_name(), "divorced"); 
      ?????? */ 

    write_file(DIVORCELOG, ctime(time())[4..23] + ": " + 
        pers->query_name() + " because " + reason + "; " + 
        C(spouse) + " because I was unable or refused to attend this" + 
        " divorce hearing.\n"); 
    command("say I hereby declare you divorced."); 
} 


/* 
 * Function:     divorce 
 * Description:  Action function enabling divorces. These can be 
 *               with both people present, or just one. 
 */ 
int 
divorce(string str) 
{ 
    string str1, str2; 
    object *dummy, person; 

    if (!str || sscanf(str, "me from %s because %s", str1, str2) != 2) 
    { 
        NF("Divorce yourself from who because what?\n"); 
        return 0; 
    } 

    if (strlen(str2) < 10) 
    { 
        NF("Your reasoning is too short to be accepted.\n"); 
        return 0; 
    } 

    if (sizeof(dummy = FIND_STR_IN_OBJECT(str1, E(TO))) > 1) 
    { 
        NF("You have to be specific, you cannot get a divorce " + 
           "from more than one person at the same time.\n"); 
        return 0; 
    } 

    // OBSOLETE code commented out over next next 10 lines 
    /* 
    branch off here to players whose spouse has been deleted or 
    hasn't logged on for a while 
     */ 
    /* 
    if (!SECURITY->exist_player(str1) || 
       (SECURITY->exist_player(str1) && 
       file_time("/players/" + str1[0..0] + "/" + str1 + ".o") + 6048000 < time())) 
    */ 


    // branch off here to players whose spouse isn't present 
    if (!sizeof(dummy)) 
    { 
        write("You have asked for a divorce from " + C(str1) + 
              ", because " + str2 + ".\n"); 
        say(QCTNAME(TP) + " has asked for a divorce from " + 
            C(str1) + ", because " + str2 + ".\n"); 
        command("say You have asked for a divorce under special " + 
                "circumstances. So be it."); 
        command("emote gets out a scroll and starts reading and writing."); 
        set_alarm(3.0, 0.0, &perform_single_divorce(TP, str1, str2)); 
        return 1; 
    } 

    // OBSOLETE code commented out next 
    /* 
    NF(capitalize(str1) + " is not present in this room.\n"); 
    if (sizeof(dummy) == 0) 
        return 0; 
    */ 

    if (sizeof(dummy) == 1) 
        person = dummy[0]; 

    if (TP == person) 
    { 
        NF("You can't get a divorce from yourself! Be serious!\n"); 
        return 0; 
    } 

    if (!pers1 && !pers2) 
    { 
        pers1 = TP; 
        pers2 = person; 
        reason1 = str2; 
        write("You have asked for a divorce from " + 
              capitalize(person->query_real_name()) + 
              ", because " + str2 + ".\n"); 
        say(QCTNAME(TP) + " has asked for a divorce from " + 
            QCTNAME(person) + ", because " + str2 + ".\n"); 
        return 1; 
    } 

    if (person != pers1 || TP != pers2) 
    { 
        write("The previous request did not match this request. " + 
            "Please try again.\n"); 
        say(QCTNAME(TP) + " requested a divorce, but it did not " + 
            "get approved.\n"); 
        clean_me_up(); 
        return 1; 
    } 

    /*  perform the divorce itself */ 
    reason2 = str2; 
    write("You have asked for a divorce from " + person->query_name() + 
        ", because " + str2 + ".\n"); 
    say(QCTNAME(TP) + " has asked for a divorce from " + 
        QCTNAME(person) + ", because " + str2 + ".\n"); 

    command("say You have both given your consent into this divorce. " + 
        "So be it."); 
    command("emote gets out a scroll and starts reading and writing."); 
    set_alarm(3.0, 0.0, &perform_divorce()); 
    return 1; 
} 
