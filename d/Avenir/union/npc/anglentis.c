/* Npc trainer for the Union
 *
 * Revisions:
 * 	Lucius, Jul 2017: Re-Code.
 *      Lilith, May 2022: upped numer of items in inventory
 *
 */
#pragma strict_types
#include "../defs.h"

inherit (NPC + "npc");
inherit "/d/Avenir/inherit/shop_list";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>


public void
create_monster(void)
{
    if (!IS_CLONE)
	return;

    set_name("anglentis");
    set_living_name("anglentis");
    set_race_name("human");
    set_adj("dark-eyed");
    add_adj("slender");
    add_name("human");
    set_long("He stands tall and proud, his "+
      "dark eyes watching you intently.\n");

    set_base_stat(SS_OCCUP, 150);
    set_stats(({ 144, 166, 145, 165, 161, 134 }));

    set_alignment(0);
    set_gender(G_MALE);
    set_appearance(45);

    set_union_npc();
    TO->set_union_sphere(SPH_WEAPONRY);

    set_skill(SS_LANGUAGE,      20);
    set_skill(SS_WEP_KNIFE,     99);
    set_skill(SS_PARRY,         85);
    set_skill(SS_WEP_MISSILE,  100);
    set_skill(SS_ACROBAT,       80);
    set_skill(SS_AWARENESS,    120);
    set_skill(SS_DEFENCE,       90);
    set_skill(SS_UNARM_COMBAT,  34);
    set_skill(SS_SWIM,          30);
    set_skill(SS_CLIMB,         61);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_HERBALISM,     91);
    set_skill(SS_LOC_SENSE,     54);
    set_skill(SS_SWAY,          90);
    set_skill(SS_FLING,        100);
    set_skill(SS_SLASH,        100);

    set_act_time(95);

    add_act("stare intent");
    add_act("glare search");
    add_act("sigh gently");
    add_act("rub sphere");
    add_act("peer .");
    add_act(({"throw knife at target","dget"}));
    add_act("clean knife");
    add_act("polish knife");
    add_act("flip knife");
    add_act("flex fingers");
    add_act("stretch fingers");
    add_act("tighten");

    add_ask(({ "union", "guild", "shadow"}),
	"say We follow a path of darkness and grace.", 1);
    add_ask(({ "join", "joining", "to join" }),
	"say Provide an application note to our Voice, "+
	"tell us what you think need be known. "+
	"A meeting will be arranged by our choice, "+
	"and of your life will be no unturned stone.", 1);
    add_ask(({ "skills", "skill" }),
	"say I am the Warrior trainer of the Union. Learn the "+
	"skills of battle through me.", 1);
    add_ask(({ "shard" }), "say It lies hidden.", 1);
    add_ask(({ "warriors" }),
	"say We are Warriors of grace and beauty.", 1);
    add_ask(({ "arches" }),
	"say They lie above, protecting us from "+
	"the weight of the world.", 1);
    add_ask(({ "bazaar" }),
	"say It lies east, over the dark Sybarus Sea.", 1);
    add_ask(({ "[to] 'change' [the] 'target'" }), "say I cannot.", 1);
    add_ask(({ "dagger", "knife" }),
	"say The knife is the symbol of our strength and grace, "+
	"a delicate and beautiful weapon.", 1);
    add_ask(({ "daggers", "knives" }),
	"say We shall fling them into our enemies.", 1);
    add_ask(({ "darkness" }), "say Darkness lies all about.", 1);
    add_ask(({ "dead" }),
	"say The unworthy dead are said to walk in "+
	"a hideous state of unlife far over the waters.", 1);
    add_ask(({ "death" }), "say It comes to us all.", 1);
    add_ask(({ "dome" }), "say It protects and shields us.", 1);
    add_ask(({ "elder", "elders", "flari", "flarios" }),
	"say They are masters of the shadows, in unity with the Flame.", 1);
    add_ask(({ "elf" }), "say I am one.", 1);
    add_ask(({ "'entrance' 'quest'" }), "chuckle", 1);
    add_ask(({ "entry" }), "say It lies between within and without.", 1);
    add_ask(({ "game" }), "say This is not a game.", 1);
    add_ask(({ "gate" }), "say It is impenetrable.", 1);
    add_ask(({ "gemstone" }), "smile myst", 1);
    add_ask(({ "grace" }), "say It touches us through the Flame.", 1);
    add_ask(({ "help" }), "say There is none.", 1);
    add_ask(({ "heroes" }),
	"say There were great and proud, crushing the Infidels "+
	"beneath their infinite superiority.", 1);
    add_ask(({ "hizbarin" }), "say His is the realm of water.", 1);
    add_ask(({ "improve" }), "say Perhaps...", 1);
    add_ask(({ "info" }), "gaze", 1);
    add_ask(({ "isle", "isles", "island", "islands" }),
	"say There are many, scattered throughout the Sybarus Sea.", 1);
    add_ask(({ "jazur" }), "say She and the Flame are synonymous.", 1);
    add_ask(({ "jazur flame" }),
	"say The Flame is what holds us, binds us, creates our "+
	"union with the shadows.", 1);
    add_ask(({ "job", "task" }), "say I have none.", 1);
    add_ask(({ "key" }), "say I think not.", 1);
    add_ask(({ "learn" }), "say Learning comes to those worthy.", 1);
    add_ask(({ "members" }),
	"say They are great and proud, they walk the path along "+
	"which the shadows gather.", 1);
    add_ask(({ "name" }), "say Mine is Anglentis.", 1);
    add_ask(({ "open gate", "close gate" }), "say I will not.", 1);
    add_ask(({ "overhang" }),
	"say It looks out over the splendor of the Chasm.", 1);
    add_ask(({ "path" }),
	"say Each has their own path, I can say nothing of yours.", 1);
    add_ask(({ "pendentive" }),
	"say The Pendentive is where the shadows gather to "+
	"purify those found worthy.", 1);
    add_ask(({ "pillar" }),
	"say Symbols of our power, they hold the world up over us.", 1);
    add_ask(({ "play" }), "say I think not.", 1);
    add_ask(({ "practice", "practise" }),
	"say And just what would you like to practice?", 1);
    add_ask(({ "quest" }), "say I will tell you nothing of that.", 1);
    add_ask(({ "reach' 'within' [the] 'stone" }),
	"say You may do so in the Pendentive. Only do so "+
	"if you are worthy, for though the shadows are "+
	"without flesh, they are not without substance.", 1);
    add_ask(({ "repository" }),
	"say Darkness and Shadows dwell within there.", 1);
    add_ask(({ "seek shadows" }),
	"say Take care what you seek, lest it find you instead...", 1);
    add_ask(({ "shadow union" }),
	"say This is the dark and masterful Union of all that "+
	"lies between darkness and light.", 1);
    add_ask(({ "shadows" }), "say They dwell everywhere.", 1);
    add_ask(({ "slash" }),
	"say It shall tear our enemies apart, "+
	"the wrathful Hand of our tradition and ways.", 1);
    add_ask(({ "sliver" }), "emote tilts his head slightly.", 1);
    add_ask(({ "sliver of gemstone" }),
	"say Through death you may need to pass to find it.", 1);
    add_ask(({ "source" }),
	"say It is the gift of the Gods, light from darkness, "+
	"salvation from damnation.", 1);
    add_ask(({ "standard" }),
	"say Our standard is that of the dark sphere upon the flame.", 1);
    add_ask(({ "strength" }),
	"say Our strength has the Flame at its source.", 1);
    add_ask(({ "sword" }),
	"say Our alternate weapon, we deal out death with both our hands.", 1);
    add_ask(({ "tall warrior" }), "say He is the great Akram.", 1);
    add_ask(({ "target" }),
	"say We use this for practice, "+
	"to hone our skills to perfection.", 1);
    add_ask(({ "teach" }), "say Yes, I will teach those worthy.", 1);
    add_ask(({ "throw" }),
	"say Through the air we will fling our weapons, death from afar.", 1);
    add_ask(({ "train" }),
	"say I can aid you in the learning of certain skills.", 1);
    add_ask(({ "voice" }),
	"say The Voice of the Elders will echo across the lands, "+
	"fear ye who may defy it.", 1);
    add_ask(({ "warrior" }), "say We are the Warriors of Shadow.", 1);
    add_ask(({ "water" }), "say Above and below, it surrounds us.", 1);
    add_ask(({ "weapons" }),
	"say Many are the weapons of the Union... Not all can be seen.", 1);
    add_ask(({ "within" }), "say Yes, we dwell within.", 1);
    add_ask(({ "[for] [some] 'advice'" }),
	"say I am afraid I have none to offer.", 1);
    add_ask(({ "bandeleria" }), "say They are valuable indeed.", 1);
    add_ask(({ "boat" }),
	"say The outpost boat ferries people from the "+
	"Outpost to the Bazaar.", 1);
    add_ask(({ "crack" }),
	"say From within the crack rises the dark flame of Jazur.", 1);
    add_ask(({ "dignity" }), "say Our dignity is our life.", 1);
    add_ask(({ "dust" }),
	"say Dust we are from, dust shall we return to.", 1);
    add_ask(({ "enemies" }),
	"say Those that defile the Union shall always be known as Enemy.", 1);
    add_ask(({ "evil" }),
	"say Evil? Such words have little meaning to us.", 1);
    add_ask(({ "fling" }),
	"say It is our most devestating ability, to fling daggers "+
	"into the heart of our enemy.", 1);
    add_ask(({ "forge" }),
	"say Within the forge can be made the weapons which "+
	"are Our salvation.", 1);
    add_ask(({ "gather" }),
	"say All that shall be gathered here are shadows.", 1);
    add_ask(({ "hephamenios" }), "say He is the forge-master.", 1);
    add_ask(({ "hide" }),
	"say Hiding is undignified, we shall do no such thing.", 1);
    add_ask(({ "hint" }), "smirk", 1);
    add_ask(({ "history" }),
	"say A lesson in history can be learned within the Archives.", 1);
    add_ask(({ "improve" }),
	"say The road to perfection is travelled through practice.", 1);
    add_ask(({ "life" }),
	"say It burns within us when the Flame glows bright.", 1);
    add_ask(({ "link" }),
	"say May our link to the shadows never be severed.", 1);
    add_ask(({ "ogres" }),
	"say Wretched and vile creatures, they reside in the depths "+
	"of the Utterdark.", 1);
    add_ask(({ "pride" }),
	"say A Union Warrior walks with pride in all he does.", 1);
    add_ask(({ "purify" }),
	"say Within the pendentive shall we be purified.", 1);
    add_ask(({ "purity" }),
	"say Through the Jazur Flame and the waters of the "+
	"Astuary shall we attain Purity.", 1);
    add_ask(({ "sneak" }),
	"say A Union Warrior shall do no such thing.", 1);
    add_ask(({ "song" }),
	"say Song and Dance? What, am I your fool?", 1);
    add_ask(({ "sonia" }),
	"say She is the keeper of the Archives.", 1);
    add_ask(({ "sphere" }),
	"say The Sphere is a reflection of the soul of the Union.", 1);
    add_ask(({ "symbol" }),
	"say Symbols have no meaning by themselves.", 1);
    add_ask(({ "test" }), "say The test is not mine to offer you.", 1);
    add_ask(({ "thief" }), "spit", 1);
    add_ask(({ "torch" }), "say Light is sometimes necessary too...", 1);
    add_ask(({ "worth worthy" }), "say Worth is not measured in blood.", 1);
    add_ask(({ "whistle whistles" }),
	"say That which whistles also summons.", 1);

    set_all_attack_unarmed(30, 20);
    set_all_hitloc_unarmed(50);

    add_prop(CONT_I_HEIGHT, 200);

    config_default_trade();
    set_money_give_reduce( ({ 0, 2, 3, 3 }) );
    set_store_room(file_name(TO));

    set_maxlist(50);
    set_show_price(1);
    set_blank_lines(0);

    give(50, TO);
    enable_reset();

    equip(({OBJ+"knife", OBJ+"knife", OBJ+"knife",
	    OBJ+"shirt", OBJ+"pants", OBJ+"boots",
	    OBJ+"cape", OBJ+"gloves" }), 1);
    set_alarm(1.0, 0.0, &command("mark all"));
}

private string *snds = ({ "says", "yells", "speaks" });

public string
race_sound()
{
    return one_of_list(snds);
}

public void
reset_monster(void)
{
    int size = NUM_ITEMS(BAND_ID + "_gold");;
    while(size < 5)
    {
	size++;
	clone_object(OBJ+"band_c")->move(TO);
    }

    size = NUM_ITEMS(BAND_ID + "_black");;
    while(size < 5)
    {
	size++;
	clone_object(OBJ+"band_e")->move(TO);
    }

    size = NUM_ITEMS(BAND_ID + "_war");;
    while(size < 5)
    {
	size++;
	clone_object(OBJ+"band_w")->move(TO);
    }

    size = NUM_ITEMS("gloves");
    while(size < 10)
    {
	size++;
	clone_object(OBJ+"gloves")->move(TO);
    }

    size = NUM_ITEMS("whistle");
    while(size < 10)
    {
	size++;
	clone_object(OBJ+"whistle")->move(TO);
    }
}

public void
refresh_living(void)
{
    reset_monster();
    ::refresh_living();
}

public void
init_living()
{
    ::init_living();

    add_action(do_value, "value");
    add_action(do_list,  "list");
    add_action(do_buy,   "buy");
    add_action(do_show,  "show");
}

/* Shop function redefinitions */

/* Only sell what I am supposed to */
public int
shop_hook_allow_buy(object ob)
{
    if (ob->query_worn() || ob->query_wielded())
	return 0;

    return (ob->id(BAND_ID) || ob->id("gloves") || ob->id("whistle"));
}

public void
shop_hook_list_empty_store(string str)
{
    command("say I have nothing left.");
}

public string
shop_hook_list_object(object ob, int amount)
{
    if (!shop_hook_allow_buy(ob))
	return "";
    else
	return ::shop_hook_list_object(ob, amount);
}

public int
do_buy(string str)
{
    if (query_attack())
    {
	write(CAP(query_pronoun()) + " seems too busy right now.\n");
	return 1;
    }

    if (U_IS_PUNISHED(TP, U_PUNISHED_NOBUY))
    {
	command("us I have been instructed by the Elders to sell "+
	    "you nothing, " + TP->query_name() + ".");
	return 1;
    }

    if (!IS_MEMBER(TP) && !FRIEND(TP))
    {
	command("say You are not permitted to buy anything here, "+
	    TP->query_race_name() + ".");
	return 1;
    }

    return ::do_buy(str);
}

public string
category(object ob)
{
    if (ob->id("belt"))
	return "Belt";
}

public void
update_internal(int l, int w, int v)
{
    ::update_internal(l, w, v);
    force_new_list();
}
