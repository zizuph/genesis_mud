/* **********************************************************
 *
 *    Freed Draconian Prisoner, Knights' Spur
 *    Grace, Apr - May 1995
 *          Last Update:  4/20/96
 *
 *          modified from ~solamn/splains/living/baaz
 *            *  created by Aridor 04/19/94  * 
 *          'follow' code modified from Jeremiah's Maritta
 * ********************************************************* */

#include "../local.h"
#include <ss_types.h>

inherit "/d/Krynn/common/monster/baaz_base";

#define ESCAPE_DRAC      "_escape_draconian"

string color = "blue";
string i_follow; /* 0(empty string) = following nobody, */
                 /* still in cell.                      */
int freedom_flag;

void
create_baaz()
{
    int i, j = random(6) + 2; /* j is the level of the draconian */
    string str;

    if (j < 1)
      j = 1;
    add_prop(OBJ_I_COLORABLE, 1);

    set_short("draconian prisoner");
    set_long("This baaz draconian seems to have been injured " +
        "in battle. His left eye darts about, watching you "+
        "warily, while the other one is swollen painfully "+
        "shut. His scaly flesh is marred with unsightly "+
        "slashes and large blood-stained bandages. Manacles "+
        "encircle each wrist and ankle, and they are attached "+
	"to a cumbersome length of chain which he holds in his "+
	"claws to prevent them from dragging on the ground.\n");
    set_name("draconian");
    set_adj(({ "prisoner" }));
    add_name(({"_qdrac2_", "prisoner", "drac","draconian prisoner"}));
    
    set_hp(30); // important, he's supposed to be near death

    for(i=0; i<6; i++)
        set_base_stat(i, j * 7 + random(10) + 40);
    set_skill(SS_DEFENCE,     j + random(5) + 50);
    set_skill(SS_PARRY,       j + random(5) + 50);
    set_skill(SS_WEP_SWORD,   j + random(5) + 50);
    set_skill(SS_WEP_KNIFE,   j + random(5) + 50);

    set_act_time(25);
    add_act("emote rubs a bruise on his arm, causing his "+
            "chains to rattle.");
    add_act("say Get me from the Spur and I will reward you.");
    add_act("say Oh yes! Yes!");

    add_ask(({"task", "help", "quest", "job", "errand", "where"}), 
     	    "say Help me escape to the solamnian plains"+
            " and I will reward you.", 1);
    add_ask(({"question", "interrogate"}),"say I'm not answering any, "+
            "so forget it!", 1);
    add_ask(({"directions", "for directions"}), "Go straight south in the "+
            "plains until we come to the Vingaard River. Then follow the "+
            "riverbank to the west. The spot is marked by a twisted tree. "+
            "Once we get there, I will reward you.\n");
    add_ask(({"water", "about water"}),
            "say I'll get water later.", 1);
    add_ask(({"follow me", "join me", "follow", "join", "team"}),
	    VBFC_ME("follow"));

   add_prop(NPC_I_NO_LOOKS, 1);

   set_default_answer(VBFC_ME("what_me"));
   freedom_flag = 1;
}

string
what_me()
{
    command("emote grins stubbornly.");
    command("emote croaks: I won't tell you.");
    return "";
}

follow()
{
   string who;

   if (query_follow())
      return "";

   if (!present(TP, E(TO)))
      return "";
   
   command("say Ok. Now get me out of the Spur and on the plains. "+
       "Once we're there, ask me for directions.");
   command("say When my escape is accomplished, I will reward you.");
   TP->add_prop(ESCAPE_DRAC,1); 
   set_follow(TP);
   return "";
}


