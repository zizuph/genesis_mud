// file name:    /d/Avenir/common/dead/obj/eldritch_cloak.c
// creator(s):   Lilith Aug 2021
// purpose:      Skin of the eldritch abomination. Reward for tough kill.
//         Requirements: It checks DIS > 75 +random 30. 
//                       Adds panic equivalent to stat av to player when 
//                       worn and removed.
//              Effects: RES_MAGIC 20, +25 ACROBAT, AC 50
//  Cut from corpse of : /d/Avenir/common/dead/mon/cthulujr.c
// revisions:    Lilith Oct 2021 Gorboth approved Ogre usage.
//               Lilith Dec 2021 reduced panic on wear penalty--players 
//                       are getting stuck at high panic levels.
//               Lilith June 2022 bugfix, acrobat was being remvoed twice when
//                       the cloak was breaking.

inherit "/d/Avenir/inherit/cloth_arm";
inherit "/lib/keep";
#include "../dead.h"
#include "/d/Avenir/include/basic.h"
#include <wa_types.h>
#include <formulas.h>

#define ACROBAT_BOOST 25
#define WEAR_PROP     "_live_i_wear_Eldritch_Cloak"

int acrobat_given = 0;

string my_short()
{
    if (query_worn())
	return "oversized eldritch cloak";
    else
	return "blanket-sized skin of the eldritch abomination";
}

string my_long()
{
    if (query_worn())
	return "This is a cloak of sorts cut from the pallid skin of the "+
	"eldritch abomination. It is very large, the size of a blanket, "+
	"and it flaps loosely around whoever wears it, providing both "+
	"excellent coverage of the wearer, and a distraction to attackers. "+
	"The skin itself is scaled and reptilian-looking, with some random "+
	"feelers and tendrils still attached to it.\n";
    else
	return "This is a blanket-sized piece of skin cut from the body of "+
	"the eldritch abomination. It is scaled and reptilian-looking, with "+
	"some random feelers and tendrils still attached to it. You could "+
	"probably wear it as a cloak if you wanted to.\n";	
}	   


void
create_armour()
{
    if (!IS_CLONE)
	return;

    set_name("skin");
    add_name(({"cloak", "piece of skin", "blanket", "_skin_of_Eldritch_Abomination"}));
    set_adj("eldritch");
    add_adj(({"flapping", "oversized", "white", "pallid", "abomination", 
	"reptilian", "scaled"}));
    set_short(my_short);
    set_long(my_long);
    add_item(({"feeler", "feelers", "tendril", "tendrils"}), 
      "It is a somewhat dehydrated appendage of the eldritch abomination, "+
      "still attached to the skin.\n");
    set_keep(1);

    // The eldritch abomination has 75 native armour so 
    // passing some of that on to the player. 	
    set_ac(50);  
    set_at(A_ROBE);
    set_af(TO);

    // This is a big, big heavy piece of skin.
    add_prop(OBJ_I_WEIGHT, 7500);   // More weight and volume than most 
    add_prop(OBJ_I_VOLUME, 7500);   // magical armours are set to.
    add_prop("_aod_wear_prop", 1);  // Its so big, an ogre can wear it, I hope.


    add_prop(OBJ_I_VALUE, F_VALUE_ARMOUR(50) + random (200));
    add_prop(OBJ_I_IS_MAGIC_ARMOUR, 1);
    add_prop(MAGIC_AM_MAGIC, ({ 60, "death" }));
    add_prop(MAGIC_I_RES_MAGIC, 20); // The eldritch abomination has high 
    // res magic so passing some of that on.

    add_prop(OBJ_S_WIZINFO, "This the skin of the eldritch abomination, "+
      "worn as a cloak. It has AC 50, Res Magic of 20, and adds 25 "+
      "Acrobat. It is quite heavy and voluminous for a magical armour.\n");
    add_prop(MAGIC_AM_ID_INFO,  ({ 
	"                        A voice drops sounds in your mind\n"+
	"                            clicks and moans it mostly is\n"+
	"                                           unintelligible\n", 10,   
	"                          Yet you understand the meaning:\n"+
	"    SKIN! SKin! My skin.                Flesh of my FlESh\n"+
	"               Wearrrr.       Wear skin, this. You.  YOU.\n", 15,
	"             sKIn heavy yessss sssssKIN thick yesssss....\n", 20,
	" SKIN my SKIN  skin protectsssss  goodgoodmuchgood yessss\n", 25,
	"     ogres too... ogres use... goodmuchgood protectsss...\n", 30,
	"        Resist. MaGIck.       All Magicks doth SkIn shrug\n", 40,
	"      A series of images tumble in your mind, impressions\n"+
	"                       of acrobatic feats awaiting you...\n", 45,
	"Numinous knowledge, ineffable. Horror invades your psyche\n", 50,
	"  this      is      but    the skin        off a tiny bud\n", 55,
	"                      of a much much  L A R G E R  being.\n", 60 }));
}

mixed
wear(object ob)
{

    if (DIS(TP) > (75 + random(30)))
    {
	TP->catch_msg("As you wear the skin of the eldritch abomination "+
	  "you feel as though an oppressive weight has fallen upon your "+
	  "shoulders.\n");
	say(QCTNAME(TP) + " looks as though the weight of the world is on "+ 
	  TP->query_possessive() +" shoulders as "+ TP->query_pronoun() +
	  " wears "+ short() +".\n");
	  
        // There is an unsettling gross/ick factor to wearing this skin.	  
        TP->add_panic(TP->add_panic(TP->query_average_stat() / 5)); 
	
	TP->add_magic_effect(this_object());
        acrobat_given = ACROBAT_BOOST;

	ALTER_SKILL(TP, SS_ACROBAT, acrobat_given); 
    
	TP->add_prop(WEAR_PROP, 1);                 
	return 1;
    }
    return -1;
}

int
remove(object ob)
{
    object tp = query_worn();

    ALTER_SKILL(tp, SS_ACROBAT, -acrobat_given);
    acrobat_given = 0;
    
    tp->remove_magic_effect(this_object());
    tp->catch_msg("The weight of the "+ short() +" has lifted from your "+
      "shoulders.\n");

    return 0;
}

void
leave_env(object to,object from)
{
    ::leave_env(to,from);

    if (!living(from))
	return;

    from->remove_magic_effect(TO);
}

varargs mixed
query_magic_protection(string prop, object protectee = previous_object())
{
    if (protectee == query_worn())
    {
	if (prop == MAGIC_I_RES_MAGIC)
	{
	    protectee->catch_msg("The feelers and tendrils on your "+ short() 
	      +" suddenly flail around as though they are resisting some " +
	      "magical force!\n");
	    tell_room(environment(this_object()), "The feelers and tendrils "+
	      "on the "+short()+" that " +QCTNAME(protectee)+ " is wearing "+
	      "suddenly start flailing around!\n", protectee);
	    return ({ 20, 1}); // additive
	}
    }
}
