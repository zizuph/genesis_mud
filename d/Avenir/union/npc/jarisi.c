/* Union Librarian
 *   Cirion, 050196
 *
 * Revisions:
 * 	Lucius, Jul 2017: Re-Code.
 *      Lilith, May 2022: added asks about the gods.
 *
 */
#pragma strict_types

#include "../defs.h"
inherit (NPC + "npc");

// This file contains asks and answers about the gods. 
inherit "/d/Avenir/common/gods/god_asks";

#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>


public void
create_monster()
{
    set_name("jarisi");
    set_living_name("jarisi");
    add_name("librarian");
    set_race_name("elf");
    set_adj("sinuous");
    add_adj("dignified");
    set_title("the Librarian of Novices");
    set_long("She is of pale complexion, and her hair is "
      +"long and lustrously dark.\n"
      +"Her eyes are dark as the abyss and ever watchful.\n"
      +"She is of indeterminate age, but her manner is dignified "
      +"and her wisdom unquestionable.\n"
      +"She has a small ink-stain on her robe.\n");
    add_prop(CONT_I_HEIGHT, 250);
    add_prop(CONT_I_WEIGHT, 50000);

    set_gender(G_FEMALE);
    set_base_stat(SS_OCCUP, 45);
    set_stats(({ 24, 46, 25, 85, 71, 34 }));

    set_union_npc();
    TO->set_union_sphere(SPH_TRAINING);

    set_alignment(0);
    set_skill(SS_LANGUAGE, 99);

    set_act_time(45);
    add_act("ufinger sphere");
    add_act("sigh softly");
    add_act("murmur writing scrolls.");
    add_act("emote smiles gently.");
    add_act("brood");
    add_act("emote turns the pages of a slender volume.");
    add_act("emote hums softly to herself.");
    add_act("ustudy all");
    add_act("rub sphere");
    add_act("calm");
    add_act("dignity");
    add_act("ubrush");
    add_act("utremble");
    add_act("triumph");
    add_act("uturn");
    add_act("uraise");
    add_act("uslap all");
    add_act("uregard all");
    add_act("usay I recommend you practice your emotions downstairs.");

    set_cact_time(3);
    add_cact("wield all");
    add_cact("fling");
    add_cact("sway");

    add_ask(({"alcintaron"}),
	"usay Sonia may be of more assistance to you than I.", 1);
    add_ask(({"dowd"}),
	"usay Names have power. Speak not that name aloud, "+
	"lest you know what you are usaying, and where.", 1);
    add_ask(({"books"}), "usay Within them is held great wisdom.", 1);
    add_ask(({"council"}), "usay I cannot speak of that.", 1);
    add_ask(({"help"}),
	"usay Read the books on the shelves, it "+
	"is within them that you will find all the help you need.", 1);
    add_ask(({"skills", "language"}),
	"usay Languages bring order from chaos and understanding "+
	"from incomprehension. I can help you improve your skill "+
	"with languages, if you wish.", 1);
    add_ask(({"ink", "ink-stain", "stain"}),
	"usay Yes, I know. I have been writing scrolls. It doesn't make "+
	"sense to change my robe right now, I'll do it later.", 1);
    add_ask(({"emotion", "emotions", "emotes",
	    "[room] 'downstairs'"}),
	"usay You have but to embrace the shadows and your emotions "+
	"will be revealed unto you.", 1);
    add_ask(({"flame", "jazur flame"}),
	"usay It is what binds us to Jazur. All that we give and are "+
	"given is embodied within it. Should it go out, seek one "+
	"of the Tornu. Only they have the discipline needed to "+
	"brave the Abyss and reignite the Flame.", 1);
    add_ask(({"dagger", "knife"}),
	"usay Seek another within the Halls for that information. "+
	"It is not my specialty, though I am of course proficient "+
	"in its use.", 1);
    add_ask(({"darkness"}),
	"usay In the Sway we find refuge from the darkness.", 1);
    add_ask(({"death", "dying"}),
	"usay It comes to us all, yet all is not lost. If you meet "+
	"it with dignity, you will be granted rebirth by Mascarvin.", 1);
    add_ask(({"[who] [is] 'mascarvin'"}),
	"usay She is the one who will gather you to her breast and nuture "+
	"you until it is time for rebirth.", 1);
    add_ask(({"elder", "elders", "flari", "flarios"}),
	"usay They are the true Masters of the shadows, in unity "+
	"with the Flame.", 1);
    add_ask(({"tornu", "tornus"}),
	"usay Tornu have proved their mastery of the arts of Unity "+
	"and received Akram's blessing. Only Tornu may light "+
	"the Flame, should it ever go out.", 1);
    add_ask(({"jazur", "Jazur"}),
	"usay She and the Flame are synonymous.", 1);
    add_ask(({"[sphere] [of] 'duty'"}),
	"usay Once you have been Named you will enter into the Sphere "+
	"of Duty, thus acknowledged as a Warrior of Shadow. There "+
	"will you put what you have learned into practice, and from "+
	"there you will be placed in a Sphere, as the Elders decree.", 1);
    add_ask(({"ogre", "ogres"}),
	"usay Hideous creatures! They breed uncontrollably, yet it is "+
	"our Duty to keep their population under control, lest they "+
	"come up out of the deeps and bang upon our gate, or cross "+
	"the Abyss into Sybarus.", 1);
    add_ask(({"[ogres] [at] [the] 'gate'"}),
	"usay When ogres beat upon the Gate, take care. Remember that "+
	"you may ask Nadia and Cyrus to assist you.", 1);
    add_ask(({"passions of jazur"}),
	"usay I am not permitted to discuss that with you. You must seek "+
	"the answer beyond the Lanthorn.", 1);
    add_ask(({"[what] [is] 'lanthorn'"}),
	"usay Some mysteries will be revealed in time. Tornu may find "+
	"the Lanthorn, if they but look about then with new eyes.", 1);
    add_ask(({"link", "unity"}),
	"usay We are linked to each other through the Flame. This "+
	"link makes us part of a larger whole. Each of us, "+
	"alone, unlinked, is fallible, imperfect.  Yet, linked, "+
	"united, we attain what all others unconsciously desire. "+
	"Perfection. Oneness. Unity.", 1);
    add_ask(({"passion", "passions"}),
	VBFC_ME("answer_about_passion"));   
    add_ask(({"virtue", "virtues"}),
	"usay Our virtues are a measure of our drive to achieve perfection "+
	"as individuals, and what we contribute to the Union itself.",1);
    add_ask(({"[virtue] 'grace'"}),
	"usay Grace is the state of being favoured and protected by Jazur, "+
	"of being endowed with excellence, and being blessed in beauty of "+
	"form and movement, as well as gentility of manner and "+
	"magnanimity of spirit.", 1);
    add_ask(({"[virtue] 'dignity'"}),
	"usay It is a quality of self which inspires respect in others "+
	"and indicates worthiness and rank. Also, a stateliness and "+
	"formality of manner and appearance when dealing with "+
	"those who are not your intimates.", 1);
    add_ask(({"[virtue] 'pride'"}),
	VBFC_ME("answer_about_pride"));
    add_ask(({"[virtue] 'purity'"}),
	"usay It is the absense of impurity or corruption. It is a "+
	"measure or sense of cleanliness of mind, body, and soul.", 1);
    add_ask(({"[what] [is] sway"}),
	"usay Through the Sway we draw upon the power of the Flame "+
	"to enhance our abilities. It is a heightened mental state "+
	"through which the Elders and Jazur also speak to us.", 1);
    add_god_asks();  // These are from /d/Avenir/common/gods/god_asks.c
    equip(({OBJ+"knife", OBJ+"robe", OBJ+"sandals"}));
}

public string
answer_about_passion()
{
    command("usay Passion is a multifaceted thing within the Union. There are "+
      "the Passions of Jazur, about which you will learn more once "+
      "you are Tornu. But for the purposese of training...");
    command("usay Passion is any intense emotion, ranging from pleasure to rage. "+
      "We feed our Passion to Jazur, that it may return to us, enhanced "+
      "by Her Grace, through the Sway.");
    command("usay We are taught to master our passions so that they do not "+
      "control us. And we are taught about control of passion so that we "+ 
      "may master others through theirs.");
    return "";
}

public string
answer_about_pride()
{
    command("uwet");
    command("usay This is the virtue most Warriors have difficulty with.");
    command("usay Pride is the sense of one's own dignity or value. It is a "+
      "measure of our self-respect, and of satisfaction in our "+
      "accomplishments in performing our duties.");
    command("usay It is not arrogance or braggadocio, it is not swaggering around "+
      "like some common swashbuckler.");
    command("smile fiercely");
    command("usay It is a calm confidence of manner that is leavened with "+
      "humility, because, for all that you are extraordinary, still "+
      "you Serve the Idrys, in whose eyes you are a small, but vital, "+
      "piece of the Whole.");
    return "";
}

private void 
return_unwanted(object what, object who)
{
    if (!objectp(what))
	return;

    if (present(who, environment()))
	command("usto "+ who->query_real_name() +" That is not for me.");

    if (!command("give "+ OB_NAME(what) +" to "+ OB_NAME(who)))
	what->remove_object();  
}

public void
enter_inv(object obj, object from)
{
    ::enter_inv(obj, from);

    if (!living(from))
	return;

    set_alarm(2.0, 0.0, &return_unwanted(obj, from));
}
