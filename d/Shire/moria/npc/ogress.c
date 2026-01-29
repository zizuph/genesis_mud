#include "defs.h"

inherit "/std/monster";  // Base monster.
inherit "/d/Immortal/rogon/open/string";  // Needs the index()-function.

#include <const.h>
#include <stdproperties.h>
#include <macros.h>

#define OGRESS_CODE        "_ogress_code"
#define Q_CODE(obj)        obj->query_prop(OGRESS_CODE)
#define S_CODE(obj, num)   obj->add_prop(OGRESS_CODE, num)
#define SET_BIT(obj, bit)  S_CODE(obj, Q_CODE(obj) | bit)
#define TEST_BIT(obj, bit) ((Q_CODE(obj) & bit) != 0)

#define CLEAR            0
#define BIT_GOT_OFFER    1        /* Has got offer.          */
#define BIT_DARED_IT     2        /* Dared to answer!        */
#define BIT_SISSY        4        /* Did not dare to answer. */
#define MASK_QUESTION    (8+16)   /* Question number bits.   */
#define BIT_FAILED       32       /* Failed a question!      */
#define BIT_SUCCESS      64       /* Did succeed!            */

#define IS_A_SISSY(obj)   (Q_CODE(obj) & BIT_SISSY)
#define QUESTION(obj)     ((Q_CODE(obj) & MASK_QUESTION) >> 3)
#define INC_QUESTION(obj) S_CODE(obj, (Q_CODE(obj) & ~MASK_QUESTION) \
                                      | (QUESTION(obj)+1) << 3)
#define FAILED(obj)       (obj->query_prop(OGRESS_CODE)==BIT_FAILED)

#define DEBUG(str)       /**/

static object talking_to;
static string hidden_name;
int forget_alarm;

//-------------- Prototypes. ----------------------------------------
string query_hidden_name();		       // Name.
int here(object who);			       // Is he here? 
int query_allowed(object who);		       // Allowed leave? 
void w(object who, string what);
void t(string what);
void s(string what);

void force_out(object who);		       // Get out! 
void recieve_say(object who, string what);     // Init for says 
void init_ask(object who);		       // Init asking 
void ask_first();			       // Want to answer? 
void first_respond(string str); 	       // Response to willingness	
void piss_off(object who);		       // Don't want to answer!!!  
void forget_it();			       // Waiting. Don't answer..  
void start_to_ask();			       // Start asking questions.	
void ask();			               // Ask question no. nr	   
void respond(string str);		       // Response of questions    
void wrong();				       // Wrong answer. 	   
void done_it(); 			       // Congrats! You made it!   
void late_recieve(string str);


//-------------- Construct the Ogress ------------------------------
create_monster()
{
    hidden_name = explode("zvdrcs","")[random(6)] + "icci";
    set_race_name("ogre");
    set_name("ogress");
    add_name("witch");
    add_adj("wicked");
    set_short("An old wicked ogress");
    set_long("She is an old witch sitting on a chair held up by pillows.\n");
    set_gender(1);
    set_alignment(-250);

    add_prop(CONT_I_WEIGHT, 70*1000);
    add_prop(CONT_I_HEIGHT, 130);
    set_stats( ({ 50, 70, 99, 126, 129, 134 }) );
    set_hp(10000);
    set_skill(SS_UNARM_COMBAT,	30);
    set_skill(SS_WEP_SWORD,    100);
    set_skill(SS_WEP_AXE,      100);
    set_skill(SS_WEP_CLUB,	80);
    set_skill(SS_WEP_KNIFE,	90);
    set_skill(SS_DEFENCE,	45);
    set_skill(SS_PARRY,        100);
    set_skill(SS_AWARENESS,	90);
    set_skill(SS_BLIND_COMBAT, 100);

    add_prop(NPC_I_NO_LOOKS, 1);
    add_prop(LIVE_I_NEVERKNOWN, 1);
    set_alarm(1.0, 10.0, "check_visitors");
}

string short() { return "wicked Ogress"; }
string query_nonmet_name() { return "ogress"; }
string query_hidden_name() { return hidden_name; }

int here(object who) { if(objectp(who)) return ENV(who) == ETO; }

/*
 * Is the player 'who' allowed to leave this room?
 */
int
query_allowed(object who) 
{
    return (who != talking_to ||              // Ok, since we're not busy. 
	    (TEST_BIT(who, BIT_GOT_OFFER) &&   
	     !TEST_BIT(who, BIT_SUCCESS | BIT_FAILED))); // Is busy.
}

void w(object o,string str) { tell_object(o,str); }
void t(string str)	    { tell_object(talking_to,str); }

void
s(string str)  
{
    talking_to->catch_msg("The ogress says: "+str+"\n");
    tell_room(ETO, 
	      "The ogress says to "+QTNAME(talking_to)+": \n   "+
	      str+"\n", talking_to);
}

void
init_living() 
{
    if (TP == TO) 
	return;
    if (TP == talking_to) 
	return;
    if (talking_to && !present(talking_to, ETO))
	talking_to = 0;
    set_alarm(itof(2 + random(5)), 0.0, &init_ask(TP));
}

void
force_out(object p) 
{
    if(!here(p) || !living(p))
      return;
    w(p,"The ogress forces you to: north\n");
    say("The ogress turns to "+QTNAME(p)+" and forces "+
	HIM_HER(p)+": north\n",p);
    p->move_living("north", MINES_DIR + "rattrap");
    p->catch_msg("You run to avoid the wrath of the witch.\n");
    if(talking_to==p) {
	talking_to = 0;
    remove_alarm(forget_alarm);
    }
}

void
recieve_say(object who, string str) {
    str = lower_case(str);
    if (who == TO || !talking_to || !here(talking_to)) return;
    set_alarm(2.0, 0.0, &late_recieve(str));
}

void
late_recieve(string str)
{
    DEBUG("In late_recieve(\"" + str + "\")\n");
    if (FAILED(talking_to))
	force_out(talking_to);
    else if (!TEST_BIT(talking_to, BIT_DARED_IT)) 
	first_respond(str);
    else 
	respond(str);
}

void
init_ask(object who) {
    if (talking_to) {
	w(who,"The ogress witch points her finger upon you!\n");
	w(who,"The ogress witch grins: I am busy. Come later!\n");
	force_out(who);
    }
    talking_to = who;
    ask_first();
}

void
ask_first() {
    t("The ogress turns her hidious face into a grotesque grin.\n");
    if (IS_A_SISSY(talking_to))
	{
	    command("say Are you here again, sissy!");
	    force_out(talking_to);
	    command("shout Dare not come back, fool!");
	    return;
	}
    else if (TEST_BIT(talking_to, BIT_FAILED))
	{
	    command("laugh merrily");
	    command("say So, you thought you should get a second chance?");
	    command("grin");
	    force_out(talking_to);
	    return;
	}
    else if (TEST_BIT(talking_to, BIT_SUCCESS))
	{
	    command("shout WHAT??? What are you doing here again!");
	    command("grin");
	    command("say Sorry, I remember that you should not come here again.");
	    force_out(talking_to);
	    return;
	}
    else
	{
	    command("say Are you prepared to answer three difficult and "+
		    "fatal questions?");
	    SET_BIT(talking_to, BIT_GOT_OFFER);
        remove_alarm(forget_alarm);
        forget_alarm = set_alarm(60.0, 0.0, &forget_it());
	}
}

void
forget_it() 
{
    if (here(talking_to) && !TEST_BIT(talking_to, BIT_DARED_IT)) 
	{
	    command("say Have you thought of using all day?");
	    force_out(talking_to);
	    SET_BIT(talking_to, BIT_SISSY);
	    talking_to = 0;
	}
    if (!here(talking_to)) 
	talking_to=0;
}

void
check_visitors()
{
    if (!here(talking_to))
	{
	    talking_to = 0;
        remove_alarm(forget_alarm);
	}
}

void
piss_off(object who) {
    command("say Well, then get the hell out of here, "+
	    who->query_name()+"!");
    force_out(who);
    SET_BIT(who, BIT_SISSY);
    command("shout And do not come back before you are properly prepared!"); 
}

void
first_respond(string str)
{
    if (!talking_to)
	return;
    if (!str || str=="")
	piss_off(talking_to);
    str = lower_case(str);
    if ((str=="y" || str=="yes" || index(str, "yes")>=0 || 
	 index(str,"sure")>=0) && QUESTION(talking_to)==0)
	start_to_ask();
    else
	piss_off(talking_to);
}

void
start_to_ask() 
{
    remove_alarm(forget_alarm);
    SET_BIT(talking_to, BIT_DARED_IT);
    ask();
}

void
ask() 
{
    int nr = QUESTION(talking_to);
    
    if (nr == 0)
	{
	    s("Thank you, here comes the first:");
	    s("  Round it is, made of purest gold.");
	    s("  A creature covets it more than anyone other.");
	    s("  The Lord of Darkness. What is his name?");
	}
    else if (nr == 1) 
	{
	    s("Excellent!");
	    s("  A dwarf made The Great Western Gate.");
	    s("  What was his name?");
	}
    else if (nr == 2) 
	{
	    s("You know your things, I hear.");
	    s("Now to the last, and decisive question:");
	    s("  Deep in the Mountains, in the heart of Moria.");
	    s("  Ogress and witch, what is my name?");
	}
}

void
respond(string ans) 
{
    string correct =({"sauron", "narvi", hidden_name}) [QUESTION(talking_to)];
    int ind;

    ans = lower_case(ans);
    ind = index(ans, correct);

    if (ind >= 0)
	{
	    INC_QUESTION(talking_to);
	    if (QUESTION(talking_to)<3)
		ask();
	    else
		done_it();
	} 
    else
	wrong();
}

void
wrong() 
{
    s("Wrong, so wrong fool!\n");
    s("Hm, what should the punish be, hmm...");
    s("What!!?! Do I not have the mushroom?");
    s("This must be your lucky day!!");
    s("I can't transform you to a toad!! Yet..");
    s("Out, out, out! You miserable fool!");
    SET_BIT(talking_to, BIT_FAILED);
    force_out(talking_to);
    talking_to = 0;
}

void
done_it() {
    s("What! How did you know that?");
    s("Don't you dare coming back to me again!");
    t("As the ogress disappears, she reveals a hidden hole in the floor.\n");
    SET_BIT(talking_to, BIT_SUCCESS);
    ETO->open_hole();
    TO->remove_object();
    return;
}

int
special_attack(object who)
{
    command("say Fool!! You cannot harm me!");
    force_out(who);
    return 1;
}

string
stats()
{
    int bits = Q_CODE(TP);
   
    return ("\n--------------------------------------------\n" +
	    " Her hidden name : " + hidden_name + "\n" +
	    sprintf(" Your Bits = %xX (%d)\n", bits, bits) +
	    "--------------------------------------------\n" +
	    "BIT_GOT_OFFER : " + TEST_BIT(TP, BIT_GOT_OFFER) + "\n" +
	    "BIT_DARED_IT  : " + TEST_BIT(TP, BIT_DARED_IT) + "\n" +
	    "BIT_SISSY     : " + TEST_BIT(TP, BIT_SISSY) + "\n" +
	    "QUESTION      : " + QUESTION(TP) + "\n" +
	    "BIT_FAILED    : " + TEST_BIT(TP, BIT_FAILED) + "\n" +
	    "BIT_SUCCESS   : " + TEST_BIT(TP, BIT_SUCCESS) + "\n" +
	    "---------------------------------------------\n");
}
    

