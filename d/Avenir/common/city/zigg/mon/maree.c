// file name:   maree.c
// creator(s):  Zielia and Lucius, Sept 2006
// last update:
// purpose: Head gardener of the ziggurat.
// note:
// bug(s):
// to-do:
#pragma strict_types

#include "zigg.h"

#include <macros.h>
#include <ss_types.h>

inherit ZIG_NPC;

#include "../garden/flowers.h"

#define SHADOW  ZIG_OBJ +"vines_sh"
#define POISON  ZIG_OBJ +"m_poison"
#define ACT	(45 + random(15))
#define WAIT	itof(random(7) + 7)

private string *flowers = m_indices(m_flowers);
private static int am_busy, aseq, hour, week;

public string
ask_seq(string *ask, int count = 0, object tp = TP)
{
    set_this_player(tp);  

    if (aseq)
    {
        write(TO->query_The_name(tp) +" looks too irritated to answer you.\n");
        return "";
    }        
        
    if (count == 0 && am_busy)
    {
        write(TO->query_The_name(tp) +" is too busy to answer.\n");
        return "";
    }
        
    am_busy = 0;

    if (ENV(TO) != ENV(tp))
        return "";
    	
    command(ask[count]);
    
    if (++count != sizeof(ask))
	am_busy = set_alarm(2.5, 0.0, &ask_seq(ask, count, tp));
    
    return "";
}

private string
ask_quest(void)
{
    if (am_busy || aseq)
    {
        command("emote is too busy to answer.");
        return "";
    }
	
    return "say to "+ OB_NAME(TP) +" If you check back later, I might have "+
	"something.";
}

private string
ask_zig(void)
{
    ask_seq(({"say to "+ OB_NAME(TP) +" The Ziggurat is a place where all "+
	"manner of desires may be sated, and a great many of us work to "+
	"make it so.", "say Ae still cannot believe the Hegemon has "+
	"allowed all manner of people to enter, but at least the lower "+
	"levels remain pure."}));

    return "";
}

private string
ask_city(void)
{
    if (am_busy || aseq)
    {
        command("emote is too busy to answer.");
        return "";
    }

    return "say to "+ OB_NAME(TP) +" Just look around, for you are "+
	"already standing within it.";
}

private string
ask_infidel(void)
{
    if (am_busy || aseq)
    {
        command("emote is too busy to answer.");
        return "";
    }

    return "say to "+ OB_NAME(TP) +" Ae do not wish to speak to you of "+
	"Infidels.";
}

private string
ask_grow(void)
{
    if (am_busy || aseq)
    {
        command("emote is too busy to answer.");
        return "";
    }

    return "say to "+ OB_NAME(TP) +" It grows well, of course. Why do "+
	"people always ask that?";
}

private string
ask_magic(void)
{
    if (am_busy || aseq)
    {
        command("emote is too busy to answer.");
        return "";
    }

    return "say to "+ OB_NAME(TP) +" The blessings "+
	"bestowed to an Anchorite are not for you to know";
}

public void
f_path(void)
{
    string str;
    int count = hour;

    if (count > 12)
	count = 1;

    str = ZIG_RLG + "room" + (13 - count);

    if (ENV(TO) && (str == file_name(ENV(TO))))
	return;

    TO->move_living("X", str, 0, 1);
    filter(deep_inventory(), &->is_zig_food())->remove_food();
}

static void
zig_npc(void)
{
    set_mm_in("arrives following the white flagstone path.");
    set_mm_out("leaves following the white flagstone path.");

    set_name(({"maree", "anchorite", "gardener"}));
    set_race_name("elf");
    set_title("dei Contrae'ree, Anchorite of Sachluph and High "+
	"Mistress Gardener of the Ziggurat");
    set_syb_house("Contrae'ree");
    set_adj(({"pale", "emaciated"}));
    set_size_descs("tall", "very skinny");
    default_config_npc(100, 30);
    set_alignment(0);
    set_appearance_offset(0);
    set_gender(G_FEMALE);

    set_knight_prestige(-5);
    add_prop("_ranger_i_not_disarm", 100);

    set_skill(SS_DEFENSE, 90);
    set_skill(SS_AWARENESS, 90);

    set_dont_answer_unseen(1);
    set_default_answer("@@what_me@@");

    add_ask(({"market", "bazaar", "marketplace", "merchantile pale"}),
	&ask_seq(({"say to There are two markets: the one for "+
	"outlanders, and the one for Sybarites.", "say You passed through "+
	"the bazaar to get here. That one is for outlanders. The "+
	"merchantile pale is what sybarites use most."})), 0);
    add_ask(({"park","island", "holm", "Holm"}), &ask_seq(({
	"say The Holm of the Icondite is where the noble Hunt. They're "+
	"pretty particular about who they let on that island and "+
	"when, but then ae expect you know that by now."})), 0);
    add_ask(({"bath", "melchior's bath"}), &ask_seq(({"say It is near the "+
        "First Gate."})), 0);
    add_ask(({"forbidden city", "city", "City", "Forbidden City"}),
	ask_city, 1);
    add_ask(({"task", "job", "quest", "help"}), &ask_seq(({
	"say Our only duty is to serve the Idrys."})), 0);
    add_ask(({"infidel", "infidels"}), ask_infidel, 1);
    add_ask(({"faithful", "Faithful", "faithfuls", "Faithfuls"}),
	&ask_seq(({"say The Faithful serve the Will of the "+
	"Idrys."})), 0);
    add_ask(({"master", "Master", "god", "God","Mistress","mistress"}),
	&ask_seq(({"say My Mistress is Sachluph."})), 0);
    add_ask(({"hizarbin", "Hizarbin"}), &ask_seq(({"say Hizarbin is the "+
        "Idrys of the Eleventh Hour, husband to my Mistress, Sachluph."})), 
        0);
    add_ask(({"sachluph", "Sachluph"}), &ask_seq(({"say Sachluph is the "+
        "Idrys of the Eleventh Hour, regent of all that grows from the "+
        "earth."})), 0);
    add_ask(({"priest","priestess", "anchorite", "guild"}), &ask_seq(({
	"say Ae am an Anchorite of Sachluph, a priestess who has "+
	"dedicated my life to serving Her will."})), 0);
    add_ask(({"union", "shadow union", "shadow warrior"}), &ask_seq(({
	"say Few dare speak of them, but ae say they've spent too long "+
	"in those tunnels."})), 0);
    add_ask(({"dej-minha"}), &ask_seq(({"say They are the Hegemon's... "+
    	"guard.", "say They must be quite skilled."})), 0);
    add_ask(({"jadestone", "jadestone doll"}), &ask_seq(({
	"say She is out of favor with the Hegemon.", "say That is but a "+
	"short step from infidel."})), 0);
    add_ask(({"hegemon", "Hegemon"}), &ask_seq(({"say He is one of the "+
	"Cambion and leader of all Syb'arus."})), 0);
    add_ask(({"cambion", "Cambion"}), &ask_seq(({"say They are liken to the "+
	"Idrys. But we should not speak of it."})), 0);
    add_ask(({"idrys", "Idrys"}), &ask_seq(({"say They are true Gods, "+
	"the ones who saved us from the horror of the Reshaping."})), 0);
    add_ask(({"reshaping", "Reshaping"}), &ask_seq(({"say Ae am glad "+
	"ae didn't live in those times. It must have been terrible."})), 0);
    add_ask(({"garden",}), &ask_seq(({"say My House has tended the gardens "+
	"of the Ziggurat since it was first built. Sachluph has honored "+
	"us with such service."})), 0);
    add_ask(({"grow","how does your garden grow"}), ask_grow, 1);
    add_ask(({"ziggurat","Ziggurat"}), ask_zig, 1);
    add_ask(({"kesoit","kesoit tree", "kesoit fruit"}), &ask_seq(({
	"say Truly it is a creation of the Idrys and a testament to "+
	"Their power.", "say The wood of the tree is fireproof and the "+
        "fruit only ripens in flame.", "say Caring for the kesoit tree is "+
        "serious business and can be quite dangerous if you don't know "+
        "what you're doing.", "say I usually leave it to one of my "+
        "assistants... ", "emote looks slightly ashamed.", "say the sap "+
        "of the kesoit tree is quite volatile and can combust when "+
        "combined with the correct ratio of water.", "say All "+
        "year long the tree slowly sucks up water, which blends with "+
        "the sap until, at the right mixture, it ignites into a glorious "+
        "blaze, ripening the fruit and burning until the water is "+
        "exhausted.",})), 0);    
    add_ask(({"flower","flowers"}), &ask_seq(({"say T'cael ae know much "+
        "about flowers!", "say Nearly all the flowers we grow here are "+ 
        "native of the Outlands.", " say It is only with Sachluph's "+
        "blessing that many are able to grow at all, and still they "+
        "require constant rejuvination and must be replaced often. But "+
        "it is a great pleasure to have a place with flowers all hena "+
        "long."})), 0);
    add_ask(({"rejuvination","magic","spell","power"}), ask_magic, 1);

    set_act_time(ACT);
    add_act("@@do_ritual");

    add_ask(flowers, "@@ask_flowers");
    configure_eyes("keen", "cornflower blue", 2);
    configure_hair("short", "dark brown", "falls in loose curls which just "+
	"reach the nape of her neck");

    if (!IS_CLONE)
	return;

    /* Avtime events. */
    AVTIME->add_event(TO);
    hour = AVTIME->get_avenir_hour();
    set_alarm(1.0, 0.0, f_path);
}

static void
add_clothing(void)
{
    object cm = CM->get_this_object();

    cm->set_cset("nature");
    cm->make_girl(TO, -1);

    object pouch = clone_object(BAZAAR +"Obj/worn/pouch_belt");
    pouch->move(TO, 1);
    clone_object(ZIG_OBJ +"m_dagger")->move(pouch, 1);
    clone_object(ZIG_OBJ +"thorn")->move(pouch, 1);
    command("wear garments");
    command("wear belt");
}

public string
ask_flowers(void)
{
    string question = query_question();
    command("say "+ m_flowers[question][1]);
    return "";
}

public void
f_ritual1(int count, string plant)
{

    if (!sizeof(environment(TO)->query_flowers()))
    {
	am_busy = 0;
	return;
    }

    switch(++count)
    {
    case 1:
	command("emote produces a large, very sharp thorn and uses it to "+
	    "prick her finger.");
	break;
    case 2:
	command("emote appears impassive as blood begins to well from her "+
	    "finger, forming a dark red pearl as she looks on.");
	break;
    case 3:
	plant = one_of_list(environment(TO)->query_flowers());
	command("emote strokes the leaves of a wilted "+ plant +" with her "+
	    "bloody fingers, leaving red smears behind.");
	break;
    case 4:
	command("emote croons in a singsong voice to the "+ plant +". The "+
	    "air around the "+ plant +" seems to shimmer and the bloody "+
	    "smears disappear.");
	break;
    case 5:
	command("emote smiles with satisfaction as somehow the "+ plant +
	" seems to regain strength, looking revitalized and healthy.");
	break;
    }
    if (count < 5)
    {
	am_busy = set_alarm(WAIT, 0.0, &f_ritual1(count, plant));
    }
    else
    {
	am_busy = 0;
    }
}

public void
f_ritual2(int count, string plant)
{
    if (!environment(TO)->query_trees())
    {
	am_busy = 0;
	return;
    }

    object room = environment(TO);

    switch(++count)
    {
    case 1:
	command("get knife from pouch");
	command("wield knife");
	break;
    case 2:
	command("emote washes her encorcelled black pruning knife in the "+
	    "flowing waters of the aqueduct.");
	break;
    case 3:
	command("emote shakes the water off her encorcelled black pruning "+
	    "knife.");
	break;
    case 4:
	command("emote winces as she closes her hand upon the blade of the "+
	    "pruning knife and draws it out with a sharp motion, slicing "+
	    "a line across her palm.");
	break;
    case 5:
	command("emote holds her hand up and out as though making an offering "+
	    "to someone unseen. Her hand is rough and covered with many fine, "+
	    "white lines: scars testifying to the frequency of this "+
	    "ritual.");
	break;
    case 6:
	plant = environment(TO)->query_trees();
	command("emote whispers a word of Power which rings like thunder "+
	    "in the air as she presses her hand against the nearby "+
	    plant +".");
	break;
    case 7:
	tell_room(room, "The "+ plant +" doesn't change noticeably, but "+
	    "somehow looks stronger even as "+ QCTNAME(TO) +" looks weaker.\n",
	    0, TO);
	break;
    case 8:
	command("emote removes her hand, leaving a dark reddish blot on the "+
	    "bark of the "+ plant +".");
	break;
    case 9:
	tell_room(room, "The blot slowly disappears, seemly absorbed into "+
	    "the "+ plant +".\n", 0, TO);
	break;
    case 10:
	command("put knife in belt");
	break;
    }
    if (count < 10)
    {
	am_busy = set_alarm(WAIT, 0.0, &f_ritual2(count, plant));
    }
    else
    {
	am_busy = 0;
    }

}

public void
f_ritual3(int count, string plant)
{
    object room = environment(TO);

    if (!sizeof(environment(TO)->query_fruits()) || week > 10 || week < 8)
    {
	am_busy = 0;
	return;
    }

    switch(++count)
    {
    case 1:
	plant = one_of_list(ENV()->query_fruits());
	command("pluck "+ plant );
	break;
    case 2:
	command("put "+ plant +" in pouch");
	break;
    case 3:
	plant = one_of_list(ENV()->query_fruits());
	command("pluck "+ plant );
	break;
    case 4:
	command("put "+ plant +" in pouch");
	break;
    case 5:
	plant = one_of_list(ENV()->query_fruits());
	command("pluck "+ plant );
	break;
    case 6:
	command("put "+ plant +" in pouch");
	break;
    }
    if (count < 6)
    {
	am_busy = set_alarm(WAIT, 0.0, &f_ritual3(count, plant));
    }
    else
    {
	am_busy = 0;
    }

}
public void
f_ritual4(int count, string plant)
{
    string plant;
    object room = environment(TO);

    if (!sizeof(environment(TO)->query_flowers()))
    {
	am_busy = 0;
	return;
    }

    switch(++count)
    {
    case 1:
	command("emote feels around in her belt of pouches, searching "+
	    "for something.");
	break;
    case 2:
	command("emote pulls a loosely curled fist from her belt of pouches "+
	    "and raises it to her lips for a momentary kiss.");
	break;
    case 3:
	tell_room(room, "With a whispered prayer and a quick flinging motion "+
	    QTNAME(TO) +" scatters a handful of tiny seeds amongst the "+
	    "nearby flowers.\n", 0, TO);
	break;
    case 4:
	tell_room(room, "The seeds settle on the soil but begin to sink into "+
	    "it after a moment and disappear, as though absorbed by the "+
	    "ground.\n", 0, TO);
	break;
    case 5:
	command("emote begins to chant and sway, watching the ground with "+
	    "clouded, unseeing eyes.");
	break;
    case 6:
	tell_room(room, "Incredibly, tiny seedling begin to sprout in the "+
	    "wake of "+ QTPNAME(TO) +" seeds.\n", 0, TO);
	break;
    case 7:
	plant = one_of_list(ENV()->query_flowers());
	tell_room(room, "The seedlings continue to grow, unfurling and "+
	    "stretching until they transform into full-grown, blooming "+
	    LANG_PWORD(plant) +".\n", 0, TO);
	break;
    case 8:
	command("emote smiles in satisfaction, her eyes seeming sharp and "+
	    "aware once more.");
	break;
    }
    if (count < 8)
    {
	am_busy = set_alarm(WAIT, 0.0, &f_ritual4(count, plant));
    }
    else
    {
	am_busy = 0;
    }
}

public string
do_ritual(void)
{
    string plant = one_of_list(environment(TO)->query_flowers());
    int num = random(9);

    if (am_busy || aseq)
    {
	return "";
    }

    switch(num)
    {
    case 0:
	f_ritual1(0, plant);
	break;
    case 1:
	f_ritual2(0, plant);
	break;
    case 2:
	f_ritual3(0, plant);
	break;
    case 3:
	f_ritual4(0, plant);
	break;
    case 5:
	if (sizeof(environment(TO)->query_flowers()))
	{
	    command("emote plucks a weed growing amongst the "+
	        LANG_PWORD(plant) +".");
	}
	break;
    case 6:
	if (sizeof(environment(TO)->query_flowers()))
	{
	    command("smell "+ plant);
	}
	break;
    case 7:
	if (sizeof(environment(TO)->query_flowers()))
	{
	    command("pluck "+ plant);
	}
	break;
    case 8:
	if (sizeof(environment(TO)->query_flowers()))
	{
	    command("emote sighs sadly as she removes a dead "+ plant +
		" hidden amongst the healthy plants.");
	}
	break;
    }

    return "";
}

public void
equip_me(void)
{
}

public void
unseen_hook(void)
{
    command("emote peers thoughtfully around.");
}

private void
react_infidel(object who)
{
    command("say to "+ OB_NAME(who) +" You sour the earth with your "+
	"presence, Sin'ur. Be gone from this place!");
}

/* default answer to questions */
public string
what_me(void)
{
    if (am_busy || aseq)
    {
        command("emote is too busy to answer.");
        return "";
    }	
	
    if (IS_INFIDEL(TP))
    {
	command("frown pious");
	react_infidel(TP);
	return "";
    }

#ifdef LOG_QUESTIONS
    logrotate(LOG_QUESTIONS, TP->query_cap_name() +" asked "+
       CAP(query_name()) +" about: "+ query_question() +".\n");
#endif

    switch(random(5))
    {
    case 0:
	command("say It is in silence a flower blooms, in silence it falls "+
	    "away, and in silence we might best enjoy them.");
	command("emote presses a thin finger to her lips.");
	break;
    case 1:
	command("say Ae would not presume to offer an opinion on that.");
	command("smile tight");
	break;
    case 2:
	command("say Ae am not the person to ask that of. Ae am but "+
	    "a humble gardener, a servant of Sachluph.");
	break;
    case 3:
	command("say Flowers are the poetry of the Idrys. "+
	    "Speak to me only of flowers.");
	break;
    case 4:
	command("say Questions are as varied as flowers in a field, and some "+
	    "amongst them weeds, and some amongst them poisonous. Beware the "+
	    "answers you seek.");
	break;
    }
    return "";
}

static void
return_intro(object who, string oname)
{
    if (IS_INFIDEL(who))
	return;

    command("emote bows her frail body with careful grace.");
    command("introduce me to "+ oname);
    command("say to "+ oname +" Ta'haveth, "+
	who->query_name() +"! May the Source shine brightly on you.");
}

static void
check_meet(object who, string oname)
{
    if (IS_INFIDEL(who))
    {
	react_infidel(who);
	return;
    }

    int i = random(15);

    if (who->query_prop(DANCER))
    {
	if (i < 4)
	    command("say to "+ oname +" Shouldn't you be dancing below?");
    }
    else if (IS_SYBARITE(who))
    {
	if (i < 7)
	    command("bow respect "+ oname);
	else if (i == 7)
	    command("smile weakly "+ oname);
	else if (i > 7)
	    command("say to "+ oname +" Celebrate the Source!");
    }
    else
    {
	if (i > 5)
	    command("say Celebrate the Source and tread lightly, Outlander.");
    }
}

public void
f_vines2(object ob)
{
    object room = environment(TO);
    object shd;

    if (!present(ob, room))
    {
	return;
    }
    if (ob->query_trapped_object())
    {
	ob->catch_msg("The thorny vines wrap tighter around you, distracting "+
	    "you and keeping "+ QTNAME(TO) +" just out of reach.\n");

	return;
    }
    if (!objectp(shd = clone_object(SHADOW)) || !shd->shadow_me(ob))
    {
	ob->catch_msg("You freeze in the middle of your attack on "+
	    QTNAME(TO) +". You get the sense she is protected by a "+
	    "great and terrible Power.\nYou don't dare attack again.\n");

	shd->remove_shadow();
	return;
    }
    else
    {
	ob->catch_tell("Before you can attack, the ground "+
	    "shifts beneath you. Suddenly thick, thorny vines sprout "+
	    "from the ground and lash about your legs, twisting and "+
	    "tangling about them until you are thoroughly bound.\n");
	tell_room(room, "Thick, thorny vines sprout from the ground "+
	    "and lash about "+ QTPNAME(ob) +" legs, twisting and "+
	    "tangling about them until "+ HE(ob) +" is thoroughly "+
	    "bound.\n", ob, room);
	shd->set_trapped_object(room);
    }
}

public void
f_vines(int count, object ob)
{
    string oname = OB_NAME(ob);
    object room = environment(TO);
    object shd, poison;
    float wait = 7.0;
    aseq = 0;
    
    if (!present(ob, room))
    {
	command("smirk .");
	return;
    }

    switch(++count)
    {
    case 1:
	ob->catch_msg(QCTNAME(TO) +" fixes you with a penetrating stare "+
	    "making you stop in your tracks. The color bleeds from her "+
	    "eyes turning them a cloudy white, and the air reverberates "+
	    "with Power as she whispers an indecernable word.\n");
	tell_room(room, QCTNAME(TO) +" fixes "+ QTNAME(ob) +" with a "+
	    "penetrating stare making "+ HIM(ob) +" stop in "+ HIS(ob) +
	    " tracks. The color bleeds from her eyes, turning them a "+
	    "cloudy white, and the air reverberates with Power as she "+
	    "whispers an indecernable word.\n", ob, room);
	wait = 4.0;
	break;
    case 2:
	if (ob->query_trapped_object())
	{
	    ob->catch_msg("The thorny vines wrap tighter around you, "+
		"distracting you and keeping "+ QTNAME(TO) +" just out "+
		"of reach.\n");
	    return;
	}
	if (!objectp(shd = clone_object(SHADOW)) || !shd->shadow_me(ob))
	{
	    ob->catch_msg("You freeze in the middle of your attack on "+
		QTNAME(TO) +". You get the sense she is protected by a "+
		"great and terrible Power.\nYou don't dare attack again.\n");

	    shd->remove_shadow();
	    return;
	}
	else
	{
	    ob->catch_tell("Before you can attack, the ground "+
		"shifts beneath you. Suddenly thick, thorny vines sprout "+
		"from the ground and lash about your legs, twisting and "+
		"tangling about them until you are thoroughly bound.\n");
	    tell_room(room, "Thick, thorny vines sprout from the ground "+
		"and lash about "+ QTPNAME(ob) +" legs, twisting and "+
		"tangling about them until "+ HE(ob) +" is thoroughly "+
		"bound.\n", ob, room);
	    shd->set_trapped_object(room);
	}
	break;
    case 3:
	command("emote says in a distorted voice that rings with Power: "+
	    "Infidel! Did you truly believe that one such as you could "+
	    "harm the favored of Sachluph?");
	break;
    case 4:
	tell_room(room, QCTPNAME(TO) +" laugh hangs in the air, echoing in "+
	    "your ears.\n", 0, TO);
	break;
    case 5:
	command("say to "+ oname +" Your corpse shall make a lovely compost.");
	break;
    case 6:
	//Add poison later, 'cause it's fun to be mean.
	foreach(object who : filter(all_inventory(room), query_interactive))
	{
	    if (who->query_trapped_object())
	    {
		who->catch_msg("The vines about your legs tighten, the thorns "+
		    "finding their way into your skin as "+ QTNAME(TO) +
		    " smiles darkly.\n");

		if(objectp(poison = clone_object(POISON)))
		{
		    poison->move(who, 1);
		    poison->reconfig_me(who->query_max_hp() * 7);
		    poison->start_poison(TO);
		}
	    }
	    else
	    {
		who->catch_msg(QCTNAME(TO) +" smiles darkly.\n");
	    }
	}
	break;
    case 7:
	ob->catch_msg(QCTNAME(TO) +" turns on her heel, deliberately "+
	    "turning her back to you and leaving you to your fate.\n");
	tell_room(room, QCTNAME(TO) +" turns on her heel, deliberately "+
	    "turning her back to "+ QTNAME(ob) +" and leaving "+
	    HIM(ob) +" to "+ HIS(ob) +" fate.\n", ob, TO);
	break;
    case 8:
	TO->move_living("along the flagstone path without looking back",
	    one_of_list(environment(TO)->query_exit_rooms()), 0, 1);
	break;
    }

    if (count < 8)
    {
	aseq = set_alarm(wait, 0.0, &f_vines(count, ob));
    }
}

public void
notify_ob_attacked_me(object me, object foe)
{
    /* We don't assist. */
}

public void
attacked_by(object ob)
{
    ::attacked_by(ob);

    ob->stop_fight(TO);
    TO->stop_fight(ob);

    if (am_busy)
    {
	remove_alarm(am_busy);
	am_busy = 0;
    }

    if (aseq)
    {
	set_alarm(2.0, 0.0, &f_vines2(ob));
    }
    else
    {
	aseq = set_alarm(0.0, 0.0, &f_vines(0, ob));
    }

}

public int
query_not_attack_me(object who, int aid)
{
    who->stop_fight(TO);
    TO->stop_fight(who);

    return 1;
}

public int
avenir_event(int av_year, int av_week, int av_day, int av_hour)
{
    hour = av_hour;
    week = av_week;

    if (am_busy || aseq)
	set_alarm(60.0, 0.0, &f_path());
    else
	f_path();

    return 1;
}
