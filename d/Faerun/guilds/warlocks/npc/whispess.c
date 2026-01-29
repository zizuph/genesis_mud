/* /d/Faerun/guilds/warlocks/npc/whisperess/
 * 
 * "Trainer" for the warlock guilds. She serves as
 * the guiding voice, luring new recruits to join and 
 * may be slightly informative for members. Whispess is
 * also the covenmaster of the Warlocks of Faerun.
 *
 * Nerull 2018
 */
 
inherit "std/monster.c";
inherit "/std/combat/unarmed";   /* Get standard unarmed routines */
 
#include <macros.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>


/*
* Function name: create_monster()
* Description  : Constructor. Edit this to change monster.
*/
nomask void create_monster()
{
    seteuid(getuid());

    set_race_name("hag");
    add_name("whispess");
    add_name("_whispess");

    add_adj("old");
    add_adj("gruesome");

    set_gender(G_FEMALE);

    add_prop(LIVE_I_NEVERKNOWN, 1);
    add_prop(LIVE_I_SEE_DARK, 100);
    add_prop(LIVE_I_NO_CORPSE, 1);
    add_prop(LIVE_I_SEE_INVIS, 99);
    add_prop(NPC_I_NO_FEAR, 1);
    add_prop(NPC_I_NO_RUN_AWAY, 1);
    add_prop(LIVE_I_NO_STUN, 1);
    add_prop(NPC_M_NO_ACCEPT_GIVE, 1);
    add_prop(OBJ_I_RES_MAGIC, 100);
    add_prop(OBJ_I_NO_ATTACK, 1);
    add_prop(OBJ_I_NO_MAGIC_ATTACK, 1);
    
    set_short("old gruesome hag");
    
    set_long("This is the Whispess, the leader of this secret "
    +"underground coven of Warlocks. She is an old powerful Witch "
    +"responsible for recruiting and training new potential servants "
    +"that one day may rise and become Warlocks themselves that may "
    +"be bound in servitude to far more powerful entities than "
    +"herself. She train servants and Warlocks alike in the various "
    +"necessary skills related to spellcraft, herblore and magic. She "
    +"wears a brown patched "
    +"robe with various pockets and a large blood-stained satchel "
    +"filled with visible infant humanoid body-parts. A huge meat cleaver "
    +"and several fillet knives hang from her "
    +"sticky black leather belt. Her long ugly wart-infested face "
    +"is partially visible from the hood, glancing at you and the "
    +"content of the large iron cauldron. From time to time she "
    +"stirs the boiling content with a huge wooden spoon and "
    +"keep adding more infant body-parts from her large satchel. She "
    +"is outright gruesome to watch, but she may aid you in learning "
    +"skills and maybe answering a few questions if you have something "
    +"on your mind.\n");

    add_prop(CONT_I_WEIGHT, 70000);
    add_prop(CONT_I_HEIGHT, 170);

    set_stats(({ 110, 110, 120,
                 243, 320, 280 }));

    set_hitloc_unarmed(A_HEAD, 25, 15, "stone head");
    set_hitloc_unarmed(A_R_ARM, 25, 10, "right stone arm");
    set_hitloc_unarmed(A_L_ARM, 25, 10, "left stone arm");
    set_hitloc_unarmed(A_BODY, 25, 45, "stone body");
    set_hitloc_unarmed(A_LEGS, 25, 20, "stone legs");

    set_attack_unarmed(W_LEFT,  55, 55, W_BLUDGEON,
    80, "left fist");

    set_attack_unarmed(W_RIGHT,  55, 55, W_BLUDGEON,
    80, "right fist");
    
    set_attack_unarmed(W_FOOTR, 40, 40, W_BLUDGEON,
    0, "left foot");

    set_attack_unarmed(W_FOOTL, 40, 40, W_BLUDGEON,
    0, "right foot");

    set_skill(SS_UNARM_COMBAT,100);
    set_skill(SS_DEFENCE,100);
    set_skill(SS_AWARENESS,100);
    
    set_appearance(-1000);

    set_act_time(5);
    add_act("emote grins wickedly while adding more infant "
    +"flesh to the large iron cauldron.");
    add_act("emote stirs the boiling content of the large "
    +"iron cauldron with her huge wooden spoon.");
    add_act("emote uses her huge wooden spoon to taste the "
    +"content of the large iron cauldron.");
    add_act("emote uses one of her fillet knives to clean the "
    +"meat from some infant bones and tosses it into the large "
    +"iron cauldron.");
    add_act("emote cuts her own hand with one of the fillet "
    +"knives while chanting some magical words. Blood spills "
    +"into the large iron cauldron and creates a red puff "
    +"of smoke.");
    add_act("emote stokes the fire under the large iron "
    +"cauldron. It grows more itense.");
    add_act("emote absentminded for a few moments, apparently "
    +"communicating with something or someone distant.");
    add_act("emote picks some herbs from her satchel and "
    +"tosses them into the large iron cauldron.");
    add_act("emote absentminded for a few moments, apparently "
    +"communicating with something or someone distant.");
    add_act("emote scatches her warty back with the "
    +"huge wooden spoon.");
    add_act("emote picks her ugly warty nose.");
    add_act("leer hungri");
    add_act("emote whispers: Do you need any training, warlock?");
    add_act("emote whispers: Feel free to taste some of the delicatesses "
    +"from the cauldron. They are yours to take...");
    add_act("emote whispers: The fools from the farms are reckless with "
    +"their children. Ripe for picking!");
    add_act("emote whispers: The flesh, the blood from the youth! So "
    +"sweet, so powerful!");
      
    add_ask( ({ "patron", "patrons" }),
    "say Yes yes...it is almost inevitable. Sooner or later, anyone walking "
    +"these halls may submit to a specific patron in order to fulfill "
    +"his or her true potential. Be warned though, they are quite...."
    +"Demanding. Oh, before I forget, it is your journey to find and "
    +"select your own without any aid from any of us. That is the "
    +"rule, do don't bother asking for aid in finding them, or asking "
    +"about details about them, for I will share...none.", 1);
    
    add_ask( ({ "infant", "infants", "infant flesh" }),
    "say Mmmmhmm...do not underestimate the power of the "
    +"young...their flesh and blood! For us to gain, we may drain! "
    +"Ha ha ha!", 1);
    
    add_ask( ({ "whispess" }),
    "say Yes young one, that is me. Mortals both close and far away have "
    +"labeled me as the Whispess for ages, for when I communicate with "
    +"them, they only hear my voice, or my whispers. A nice name, isn't it?", 1);
    
    add_ask( ({ "help", "emotes" }),
    "say You need help, young one? Feel free to ask me about a great many "
    +"things, and in addition, 'wahelp' should aid you quite alot.", 1);
    
    add_ask( ({ "pact" }),
    "say As you now are well aware of, creating the pact with me is the "
    +"pathway to many abilities many consider to be...unnatural and "
    +"evil. As with everything, there must be balance, for no knowledge "
    +"and power is truly free. To gain, one has to give, and this "
    +"becomes even more important if or when you serve a patron. You will "
    +"serve me and my coven until I see you unfit, or until you flee "
    +"from this place. Even if you are bond to a powerful entity, you "
    +"will ofcourse still be true to me and the coven.", 1);
    
    add_ask( ({ "spell", "spells", "gift", "gifts", "power", 
    "powers", "pact magic" }),
    "say I will reveal that some are granted for free, others by "
    +"proper servitude and dedication, and others selected as rewards. You "
    +"will know in due time.", 1);
    
    add_ask( ({ "train", "training" }),
    "say Yes yes...I will train all of you. Simply 'learn' or 'improve' "
    +"your skills in this very chamber, and I shall assist, but, you better "
    +"bring coin though.", 1);
    
    add_ask( ({ "ritual", "rituals" }),
    "say Warlocks that serve a patron will regulary perform various "
    +"rituals. This is unavoidable, for the entities they serve are "
    +"demanding, and constantly crawing. One must sacrifice in order "
    +"to receive.", 1);
    
    add_ask( ({ "charm", "charms" }),
    "say Indeed. We don't use potions or shards from gems as our primary "
    +"component, but charms we have created! A charm will infuse your "
    +"essence with sufficient magical power to cast a gift several "
    +"times in row.", 1);
    
    add_ask( ({ "large iron cauldron", "cauldron", "large cauldron",
    "iron cauldron"}),
    "say Ooh...you want a taste, perhaps? If you can stomac it, feel "
    +"free to grab a piece or two from the cauldron! The flesh of "
    +"infants are truly sweet and empowering!", 1);
    
    add_ask( ({ "warlock", "warlocks" }),
    "say Yes, Warlocks! I help powerful entities to find "
    +"suitable hosts that can serve them well! One cannot truly call "
    +"himself a Warlock before the bond with the patron is forged. Do "
    +"not listen to the common man about the likes of us though - they "
    +"do not understand!", 1);
    
    add_ask( ({ "leaving", "quitting"}),
    "say A member may decide to break the pact and leave, but then "
    +"it was destined anyway. Such fools will not be welcome back "
    +"for a great period of time, if ever. Maybe it will depend "
    +"on my mood? Ha ha ha!", 1);
    
    add_ask( ({ "evil", "good", "alignment" }),
    "say Truly...what is Evil, and what is Good? It's all an illusion and "
    +"dogmatic views of the ignorant. Mother nature do not care about such "
    +"petty concepts, and nor do we, but maybe more important, it's "
    +"completely irrelevant to the powerful entities the Warlocks serve. "
    +"Therefore, while such labels means nothing to us, it is still wise "
    +"to travel with causion as it still means something to the dogmatic views "
    +"of man.", 1);
}
