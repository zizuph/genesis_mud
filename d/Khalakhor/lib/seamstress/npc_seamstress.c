/**********************************************************************
 * - seam_exp.c                                                     - *
 * - An example on how to create a seamstress.                      - *
 * - Created by Damaris@Genesis 03/2005                             - *
 **********************************************************************/

# pragma strict_types
#include <stdproperties.h>
#include <macros.h>
#include <language.h>
#include <money.h>
#include <ss_types.h>
#include <files.h>
#include <std.h>
#include "/d/Khalakhor/sys/defs.h"
inherit "/d/Khalakhor/lib/gks/knowledge_base";
inherit "/std/monster";
inherit "/d/Khalakhor/lib/seamstress/seamstress";
object
hook_seamstress_select_create_clothing(mapping design)
{
	object  clothing;
	clothing= ::seamstress_select_create_clothing(design);
	clothing->set_long("This is " + LANG_ASHORT(clothing) + " that "+
	"is quite stunning to behold. The fabric is smooth with a small "+
	"tag that has been discretely sewn into it that reads:\n"+
	"Sissy Saggart of Khalakhor.\n");
	clothing->set_may_not_recover();
	clothing->add_item("tag", "Sissy Saggart of Khalakhor.\n");
	clothing->add_cmd_item("tag", "read", "Sissy Saggart of "+
	"Khalakhor.\n");
	clothing->add_name(({"clothing", "clothes"}));
	return clothing;
}
static mapping remembered = ([]), failed = ([]);
void
create_monster()
{
	set_name("sissy");
	set_title("Saggart Seamstress of Khalakhor");
	add_name(({"female", "woman", "seamstress", "tailor"}));
	set_race_name("elf");
	set_gender(G_FEMALE);
	add_adj(({"slender", "taunt"}));
	set_long("She is a special seamstress to teach how to "+
	"create one.\n"+
	"She has piercing black eyes.\n"+
	"She has red hair pulled up ontop her head.\n"+
	"She has smooth fair skin.\n");
	set_all_hitloc_unarmed(50);
	set_stats(({150,150,150,150,150}));
	set_skill(SS_UNARM_COMBAT,50);
	set_skill(SS_BLIND_COMBAT,100);
	set_skill(SS_PARRY,90);
	set_skill(SS_DEFENCE,90);
	set_skill(SS_AWARENESS,90);
	set_skill(SS_WEP_SWORD,90);
	set_skill(SS_WEP_POLEARM,90);
	set_skill(SS_WEP_CLUB,90);
	set_skill(SS_WEP_KNIFE,90);
	add_prop(CONT_I_WEIGHT,70000);
	add_prop(CONT_I_HEIGHT,190);
	add_prop(NPC_I_NO_RUN_AWAY,1);
	set_alignment(100);
	set_mm_in("arrives.");
	set_default_answer(QCTNAME(TP)+" mumbles: Do you wish to "+
	"talk clothing or what? I haven't time for this nonsense.\n");
	add_ask(({"clothing", "fabric", "fabrics"}),
	"say Just <check clothing> to make it easier.", 1);
	add_ask(({"clothes"}),
	"say I have plenty of clothes to make for you, <check clothing> "+
	"to make it easier.", 1);
	add_ask(({"order", "ordering"}),
	"say To place an order you simply <order 'item'>.", 1);  
   
/**********************************************************************
 * - add_seamstress_clothing - configuring pants                    - *
 **********************************************************************/
        add_seamstress_clothing("pants", "pattern",
        ({"pants", "leggings", "chaps"}));
        add_seamstress_clothing("pants", "fabric",
        ({"wool", "silk", "cotton", "satin", "taffeta"}));
        add_seamstress_clothing("pants", "color",
        ({"crimson", "black", "green", "midnight blue",
        "white", "blue", "pink", "grey"}));

/**********************************************************************
 * - add_seamstress_clothing - configuring pants                    - *
 **********************************************************************/
        add_seamstress_clothing("shoes", "pattern",
        ({"slippers", "sandals"}));
        add_seamstress_clothing("shoes", "fabric",
        ({"leather", "silk", "satin"}));
        add_seamstress_clothing("shoes", "color",
        ({"crimson", "black", "green", "midnight blue",
        "white", "blue", "pink", "grey"}));
        
/**********************************************************************
 * - add_seamstress_clothing - configuring gloves                   - *
 **********************************************************************/
        add_seamstress_clothing("gloves", "pattern",
        ({"gloves"}));
        add_seamstress_clothing("gloves", "fabric",
        ({"wool", "silk", "cotton", "satin", "taffeta"}));
        add_seamstress_clothing("gloves", "color",
        ({"crimson", "black", "green", "midnight blue",
        "white", "blue", "pink", "grey"}));

/**********************************************************************
 * - add_seamstress_clothing - configuring shirt                    - *
 **********************************************************************/
       add_seamstress_clothing("shirt", "pattern",
       ({"blouse", "shirt", "vest"}));
       add_seamstress_clothing("shirt", "fabric",
       ({"wool", "silk", "cotton", "satin", "taffeta"}));
       add_seamstress_clothing("shirt", "color",
       ({"crimson", "black", "green", "midnight blue", 
       "white", "blue", "pink", "grey"}));      

/**********************************************************************
 * - add_seamstress_clothing - configuring dress                    - *
 **********************************************************************/
      add_seamstress_clothing("dress", "pattern",
      ({"dress", "short dress", "long dress", "gown"}));
      add_seamstress_clothing("dress", "fabric",
      ({"wool", "silk", "cotton", "satin", "taffeta"}));
      add_seamstress_clothing("dress", "color",
      ({"crimson", "black", "green", "midnight blue",
      "white", "blue", "pink", "grey"})); 
 /**********************************************************************
  * - add_seamstress_clothing - configuring skirt                    - *
  **********************************************************************/
     add_seamstress_clothing("skirt", "pattern",
     ({"skirt", "short skirt", "long skirt"}));
     add_seamstress_clothing("skirt", "fabric",
     ({"wool", "silk", "cotton", "satin", "taffeta"}));
     add_seamstress_clothing("skirt", "color",
     ({"crimson", "black", "green", "midnight blue",
     "white", "blue", "pink", "grey"}));
     config_default_trade();
}
  
 /**********************************************************************
 * - Function name: hook_return_intro                                - *
 * - Description  : Called when someone introduces themselves        - *
 * -              to us.                                             - *
 * - Arguments    : str - Name of the player introducing.            - *
 * - Returns      : 1                                                - *
 ***********************************************************************/
public int
hook_return_intro(string str)
{
	if (SECURITY->query_wiz_rank(TIQRN) >= WIZ_ARCH)
	{
		command("asay devoted Blessed be my soul!");
		command("kneel " + str);
		command("asay devoted Greetings to thee, "+
		"" + capitalize(str) + ". I am " + query_name() + " "+
		"" + query_title() + ", thy humble servant.");
		command("asay devoted Ask anything of me and I shall do "+
		"my best to please thee.");
		remembered[str] = "nice";
		present(str, environment(TO))->add_introduced("sissy");
	}
	else if (SECURITY->query_wiz_rank(TIQRN, "Khalakhor"))
	{
		command("asay devoted Greetings to thee, "+
		"" + capitalize(str) + ". I am " + query_name() + " "+
		"" + query_title() + ". I am most pleased that thee "+
		"has graced me with thy pressence. "+
		"How may I serve thee?");
		command("kneel " + str);
		remembered[str] = "nice";
		present(str, environment(TO))->add_introduced("sissy");
	}
	else if (!remembered[str])
	{
		command("say Greetings to thee, "+
		"" + capitalize(str) + ", I am " + query_name() + " "+
		"" + query_title() + ". Tis a pleasure to meet thee, "+
		"may I be of assistance in choosing or creating "+
		"some clothing for thee?");
		command("bow " + str);
		remembered[str] = "nice";
		present(str, environment(TO))->add_introduced("sissy");
	}
	else if (remembered[str] == "bad")
	{
		command("growl sof");
		command("say I remember thee very well, so be off "+
		"with thee!");
	}
	else
	{
		command("chuckle");
		command("say Ahh, yes, of course, How can I forget "+
		"thee from thy last visit, " + capitalize(str) + ", "+
		"I hope thou art well?");
	}
	return 1;
}

public void
add_introduced(string who)
{
	kb_add_introduced(who);
}


public void
init_living()
{
	::init_living();
	kb_init_living();
	init_seamstress();
}

public void
enter_env(object to, object from)
{
	::enter_env(to, from);
	kb_enter_env(to, from);
}
