/*
 * Louie July 2006 - Added add_prop in do_die() so he doesn't have to
 * be reattacked.
 */
#include <stdproperties.h>
#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include "/d/Ansalon/common/defs.h"
#include "../local.h"

inherit AM_FILE
inherit "/lib/unique";

#define NERAKA_MI_DRAGONBREW        "_neraka_mi_dragonbrew"

void get_me_soul();
int soul_id;
object weapon;
int kdied = 0;

#define OLD_SS_BLOCK   67532
#define SS_KATTACK 67531

#define WEP MOBJ + "greatsword"
#define SPEAR MOBJ + "shimmering_spear"
#define ARM1 MOBJ + "chainhelm"
#define ARM2 MOBJ + "mailshirt"
#define ARM3 MOBJ + "cloak"
#define KEY MOBJ + "key"

#define SISTER_PROP "_garren_prop_asked_about_sister"
#define ALANNA_PROP "_garren_prop_asked_about_alanna"
#define SLAVE_PROP "_garren_prop_asked_slaver"
#define KALEN_PROP "_garren_prop_asked_kalen"
#define MEETING_PROP "_garren_prop_asked_meeting"
#define GARREN_NOTE "_garren_quest_note"

// Prototypes
string alanna_response();
string help_response();
string sister_response();

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("garren");
    set_living_name("garren");
    set_title("Uth Parreth of Kalaman, Fallen Knight of the Sword");
    set_race_name("human");
    set_adj("frustrated");
    add_adj("noble");
    set_gender("G_MALE");
    set_long("Before you stands a knight of Solamnia. Unlike most " +
      "you have come across, his tabard and clothing is well worn, " +
      "and his armour tarnished... you would imagine he has fallen " +
      "upon hard times recently.  However, his casual stance and " +
      "movements make it obvious his fighting skills are far from " +
      "rusty, so he should certainly not be taken lightly.\n");

    set_stats(({180, 190, 200, 150, 100, 200}));
    set_hp(query_max_hp());
    set_all_hitloc_unarmed(35);

    set_skill(SS_WEP_SWORD, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_BLIND_COMBAT, 90);
    set_skill(SS_AWARENESS, 75);
    set_skill(SS_LANGUAGE, 75);
    set_skill(SS_BLOCK, 200);
    set_skill(OLD_SS_BLOCK, 200);
    set_skill(SS_KATTACK, 150);

    set_alignment(1000);
    set_knight_prestige(-3);
    set_act_time(7);
    add_act("say My dear sister... I pray to the past and present gods " +
      "that you are still well!");
    add_act("emote peers frustratedly at a map of Sanction.");
    add_act("say On my Honour, I will rescue her! The Measure be damned!");
    add_act("say The slaver is somewhere in the city of Sanction... his " +
      "caravan led there.");
    add_act("ksmooth h");
    add_act("say These men are no knights, but they fight a noble cause... " +
      "the downfall of the Dragonarmies and the freedom of their city!");
    add_act("ksweat");

    set_cact_time(2);
    add_cact("say By Huma! You will regret your foolish attack!");
    add_cact("shout Say your prayers, fool!  You are about to meet your maker!");
    add_cact("emote narrows his eyes threateningly.");
    add_cact("kswear");

    add_prop(CONT_I_WEIGHT, 60000);
    add_prop(CONT_I_HEIGHT, 185);
    remove_prop(LIVE_M_NO_ACCEPT_GIVE);
    
    add_ask(({"quest","task","help"}), help_response, 1);
    add_ask(({"sister","slavers","rescue"}), sister_response, 1);
    add_ask(({"knights","knighthood","measure","fallen knight","knight"}),
      "ksay The Measure states I should stay at my post, protect Solamnia... " +
      "However with my sisters kidnapping, the Measure has put me at odds " +
      "with the needs of my family. I feel honour bound to rescue my sister, " +
      "so here I am. The Measure has failed me, however I will stand by my " +
      "oath!", 1);
    add_ask("oath","ksay What is the oath? What it is for all knights! My " +
      "Honour is my life!", 1);

    add_ask("alanna", alanna_response, 1);

    soul_id = set_alarm(0.5, 0.0, &get_me_soul());

    trig_new("%w 'introduces' %s","react_to_intro");
}

string sister_response()
{
    TP->add_prop(SISTER_PROP, 1);
    
    return  "ksay My sister Alanna was kidnapped " +
            "by slavers outside of Kalaman... I have tracked them to Sanction, " +
            "however cannot go any further... their defences of the city are too " +
            "strong. Curse them!";
}

string alanna_response()
{
    TP->add_prop(ALANNA_PROP, 1);
    return  "ksay The fair Alanna is my sister! I get sick to the heart " +
            "thinking about what the slavers might be doing to her while I am "+
            "unable to prevent it. What am I to do?";
}

string help_response()
{
    if(TP->query_prop(ALANNA_PROP) && TP->query_prop(SISTER_PROP))
    {
        return "ksay I don't know why you would help me, but I am running out of options. "+
            "If you can return my sister to me or obtain the location of her where abouts, " +
            "I would be in your debt forever.";
    }
    return "ksay Leave me alone.";
}


void
block_attacker()
{
    command("block north");
}


void
attacked_by(object ob)
{
    command("kd2 " +ob->query_real_name());
    command("ksalute2 "+ob->query_real_name());
    set_alarm(4.0, 0.0, block_attacker);    

    ::attacked_by(ob);
}


void
get_me_soul()
{
    TO->add_cmdsoul("/d/Ansalon/taman_busuk/mountains/living/knight_soul");
    TO->update_hooks();
    remove_alarm(soul_id);
}


int
special_attack(object enemy)
{
    command("kattack");    
}


void
react_to_intro(string who,string garbage)
{
    set_alarm(2.0,0.0,"return_intro",who);
}

void
return_intro(string who)
{
    who = L(who);
    if (P(who,E(TO)))
    {
	command("introduce myself");
    }
}

void
close_chest()
{
    command("close chest");
    command("lock chest with key");
}

void
arm_me()
{
    seteuid(getuid(this_object()));
    object spearob;

    weapon = clone_unique(WEP, 3, "/d/Krynn/solamn/vin/weapon/two_handed_sword");
    weapon->move(this_object(),1);
    command("wield all");

    /* add the spear after trying to wield all */
    /*
	  clone_object(SPEAR)->move(this_object(), 1);
    */
     spearob = clone_unique(SPEAR, 10);
    if (spearob) {
	spearob->move(this_object(), 1);
    }
    clone_object(ARM1)->move(this_object(),1);
    clone_object(ARM2)->move(this_object(),1);
    clone_object(ARM3)->move(this_object(),1);
    command("wear all");

    clone_object(KEY)->move(this_object(),1);
}

int
query_knight_level()
{
    return 4;
}


public void
do_die(object killer)
{
    object room = E(TO);

    if(!kdied)
    {
	command("kdie true");
	command("kdie true");
        heal_hp(1900);
	kdied = 1; 
    killer->add_prop(LIVE_O_LAST_KILL, this_object());

	return;
    } 

    command("say My sister... I have failed you."); 
    command("emote falls upon his " +weapon->short()+ " as he dies, driving it " +
      "into the ground.");

    setuid(); seteuid(getuid());
    weapon->add_prop(OBJ_M_NO_GET, "The weapon cannot be taken,"+
      " it is lodged firmly in the ground.\n");
    clone_object("/d/Krynn/solamn/vin/knight/obj/kthrust_weapon_shadow")->shadow_me(weapon);
    weapon->setup_things();
    weapon->move(room);
    weapon->set_depth(180 + random(40));

    /* Silly wizards calling do_die in him will not have 'killer'
     * contain anything meaningful :)
     */
    if (objectp(killer) && living(killer))
    {
	if (!killer->query_prop(NERAKA_MI_DRAGONBREW))
	    killer->add_prop(NERAKA_MI_DRAGONBREW, ([ ]));
	killer->add_prop(NERAKA_MI_DRAGONBREW,
	  killer->query_prop(NERAKA_MI_DRAGONBREW) +
                         ([ "cave_slayed_knight" : time() ]));
    }
    
    ::do_die(killer);
}

void
deligate_work3(object garren)
{
    garren->command("ksay Since you have discovered this lead, I would like for you to see it through. " +
                    "Bring me back any new discoveries you should make.");
}

void deligate_work2(object garren)
{
    garren->command("ksay It is not because I doubt your abilities, al though I do, but I " +
                    "cannot risk being discovered unless I know for sure that Alanna will be there.");
    set_alarm(4.0, 0.0, &deligate_work3(garren));
}

void
deligate_work(object garren)
{
    garren->command("ksay So you believe that this is somehow related to my sisters captures...");
    set_alarm(4.0, 0.0, &deligate_work2(garren));
}


void
be_lazy(object garren)
{
    // Handle that you gave him the right parchment
    garren->command("emote looks over the yellow parchment.");
    set_alarm(2.0, 0.0, &deligate_work(garren));
}

/*
 * Function name: prevent_enter
 * Description:   Called when an object is trying to enter this container to
 *                see if we will allow it in.
 * Arguments:     object ob - the object that is trying to enter.
 * Returns:       1 - The object is not allowed to enter
 *                0 - The object is allowed to enter
 */
public int
prevent_enter(object ob)
{
    if(!ob->id(GARREN_NOTE) || !TP->query_prop(MEETING_PROP))
    {
        TP->catch_tell("Garren doesn't accept any gifts from you.\n");
        return 1;
    }
    set_alarm(1.0, 0.0, &be_lazy(this_object()));
    return 0;
}


