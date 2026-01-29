/* 
 * /d/Gondor/minas/npc/shadowfax.c  
 *
 * Shadowfax, Lord of the Meara
 *
 * Alto, 11 April 2001
 *
 */

#pragma strict_types

inherit "/d/Gondor/minas/npc/mtirith_monster.c";
inherit "/d/Gondor/common/lib/binbit.c";
inherit "/std/act/domove";
inherit "/std/act/action";
inherit "/std/act/attack";
inherit "/std/combat/unarmed";

#include <wa_types.h>
#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>

#include "/d/Gondor/defs.h"
#include "/d/Gondor/bits.h"
#include "/d/Gondor/minas/lib/porter_defs.h"


/* Define some attack and hitloc id's */

#define A_GNASH  0
#define A_HHEAD 1
#define A_FHOOVES 2
#define A_RHOOVES 3

#define H_HEAD 0
#define H_BODY 1
#define H_LEGS 2


object actor, *inv;

public void
create_monster()
{
    int rnd;
    if (!IS_CLONE) return;
    seteuid(getuid());

    set_adj("strong");
    set_adj("silver-grey");
    set_name("Shadowfax");
    set_pname("horses");
    add_name("horse");
    add_name("meara");
    add_name("stallion");
    add_name("shadowfax");
    add_name("_porter_q_horse_");
    set_race_name("horse");

    set_long("This is Shadowfax, Lord of the Meara. He is the mightiest "
        + "of horses in Middle Earth, strong and swift, able to outrun "
        + "even the black steeds of Mordor. He will suffer neither bridle "
        + "nor saddle, but will faithfully bear those of his "
        + "choosing. He looks to be the kind of horse that is above "
        + "petting or hugging. It seems unlikely a commoner like you could "
        + "even mount him.\n");

    rnd = random(60);
    default_config_npc(150+rnd/2);
    set_base_stat(SS_DIS, 150 + rnd);
    set_alignment(400+rnd*10);

    set_gender(0);
    set_skill(SS_UNARM_COMBAT,100+random(10));
    set_skill(SS_DEFENCE,100+random(10));
    set_skill(SS_PARRY,100+random(10));
    set_whimpy(random(100));
    set_random_move(5);

    set_m_out("gallops");
    set_m_in("gallops majestically in");

    add_prop(LIVE_I_NEVERKNOWN, 1);


    set_act_time(10);
    add_act("emote shakes his massive head and his mane whips about.");
    add_act("emote snorts so loud the ground trembles.");
    add_act("emote gazes disdainfully at his surroundings.");
    add_act("emote nickers and canters about in tight circles.");
    add_act("emote flicks his silver-grey tail.");
    add_act("drink water from basin");

    set_cact_time(2);
    add_cact("emote rears up on his hind limbs and roars in fury.");
    add_cact("emote retreats briefly and charges again with hooves flying.");
    add_cact("emote rolls his eyes and whips his massive head about.");
    add_cact("emote turns his hindquarters and kicks brutally.");

    refresh_mobile();

}


/*
 * Add attacks and hitlocations:
 *     add_attack(int wchit, int wcpen, int damtype, int prcuse, int id)
 *     add_hitloc(int *ac, int prchit, string desc, int id)
 *
 * *ac == ({ ac-impale, ac-slash, ac-bludgeon })
 */

public void
cr_configure()
{
    add_attack(40+random(5),30+random(5),W_IMPALE,10,A_GNASH);
    add_attack(15+random(15),20+random(5),W_BLUDGEON,30,A_HHEAD);
    add_attack(35+random(5),25+random(5),W_SLASH,20,A_FHOOVES);
    add_attack(40+random(10),30+random(5),W_SLASH,40,A_RHOOVES);

    add_hitloc(({25+random(15),20+random(10),15+random(5)}),10,"head",H_HEAD);
    add_hitloc(({25+random(5),15+random(5),20+random(10)}),50,"body",H_BODY);
    add_hitloc(({25+random(15),15+random(5),20+random(10)}),40,"flank",H_LEGS);
}

/*
 * Give description of each attack. We could also redefine the entire
 * hitdescription by redefining 'cr_did_hit'
 */

public string
cr_attack_desc(int aid)
{
    switch(aid)
    {
    case A_GNASH:return "gnashing teeth";
    case A_HHEAD:return "massive head";
    case A_FHOOVES:return "front hoof";
    case A_RHOOVES:return "rear hoof";
    }
    return "mind"; /* should never occur */
}

public string
query_combat_file()
{
    return "/std/combat/cplain";
}


void
init_living()
{
   ::init_living();
   add_action("mount_horse", "mount");
   add_action("brush_horse", "brush");

}

int
mount_horse(string str)
{

    actor = TP;

    if (!strlen(str))
        NF0("Mount what?\n");

    if (str != "horse")
        NF0("What do you want to mount?\n");

    switch (random(3))
    {
    case 0:
        write("The strong silver-grey male horse refuses "
            + "to be mounted by the likes of you.\n");
        say("The strong silver-grey male horse refuses to be mounted "
            + "by the likes of "
            + QTNAME(actor) + ".\n");
        break;
    case 1:
        write("Ouch! The strong silver-grey male horse rears up "
            + "on his hind legs and you fall off before you get a "
            + "chance to even get on.\n");
        say(QCTNAME(actor) + " tries to mount the strong silver-grey male "
            + "horse, but he rears up on his hind legs and " + QTNAME(actor)
            + " falls off before even getting on.\n");
        break;
    case 2:
        write("As you try to mount the strong silver-grey "
            + "male horse, he crunches you against the wall. As you "
            + "crumple to the ground it becomes clear that trying to "
            + "ride this horse without his consent is a bad idea.\n");
        say("As " + QTNAME(actor) + " tries to mount the strong "
            + "silver-grey male horse it slams against the wall. "
            + "As " + QTNAME(actor) + " crumples to the ground, it "
            + "becomes clear that trying to ride this horse without "
            + "his consent is a bad idea.\n");
        break;
    default:
        break;
    }
        return 1;

}

int
brush_horse(string str)
{

    actor = TP;

    inv = all_inventory(TP);
    if (!sizeof(filter(inv, &->id("_minas_horse_brush_"))))
        NF0("You cannot groom a horse without the proper tools!\n");

    if (!strlen(str))
        NF0("Brush what?\n");

    if (!TP->query_prop(QUESTING_FOR_BRUSH))
        NF0("The Stablemaster has not given you permission to groom "
            + "the horses!\n");

    if (TP->test_bit("gondor", MTIRITH_PORTER_GROUP, MTIRITH_PORTER_BIT))
        NF0("The horse has already been groomed enough.\n");


    switch (str)
    {
    case "horse":
        NF0("What part of the horse do you want to brush? You "
            + "may brush the mane, body or tail.\n");
    case "mane":
        write("You run the small wooden brush gently through the "
            + "mane of the " + TO->short() + ". He seems to enjoy it so much "
            + "that he rests his warm velvet-smooth nose on your "
            + "shoulder and sighs deeply.\n");
        say(QCTNAME(actor) + " runs the small wooden brush gently through "
            + "the mane of the " + TO->short() + ". The " + TO->short() 
            + " seems to "
            + "enjoy it so much that he rests his warm velvet-smooth "
            + "nose on " + QTNAME(actor) + "'s shoulder and sighs "
            + "deeply.\n");

        TP->add_prop(GROOMED_SHADOWFAX_MANE, 1);

        return 1;
    case "tail":
        write("You brush the " + TO->short() + "'s tail with the small wooden "
            + "brush until it is free of tangles and snarls.\n");
        say(QCTNAME(actor) + " brushes the " + TO->short() + "'s tail with the "
            + "small wooden brush until it is free of tangles and "
            + "snarls.\n");

        TP->add_prop(GROOMED_SHADOWFAX_TAIL, 1);

        return 1;
    case "body":
        write("You brush the " + TO->short() + "'s body with the small "
            + "wooden brush. He trembles beneath your careful attentions.\n");
        say(QCTNAME(actor) + " brushes the " + TO->short() + "'s body with "
            + "the small wooden brush. He trembles beneath "
            + actor->query_possessive() + " careful attentions.\n");

        TP->add_prop(GROOMED_SHADOWFAX_BODY, 1);

        return 1;
    default:
        NF0("What do you want to brush?\n");
    }        

}




/* Set up the reaction of NPC to player */

public void
return_hug(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
    return;

    switch (random(3))
    {
    case 0:
        write("The strong silver-grey male horse seems to be "
            + "above such common things as hugs. He peers down his long "
            + "face at you in disdain.\n");
        say("The strong silver-grey male horse seems to be above such "
            + "common things as hugs. He peers down his long face at "
            + QTNAME(actor) + " in disdain.\n");
        break;
    case 1:
        write("The strong silver-grey male horse consents "
            + "to be hugged. He bends his forelegs a little to permit "
            + "your embrace.\n");
        say("The strong silver-grey male horse consents to be hugged. "
            + "He bends his forelegs a little to permit the embrace of "
            + QTNAME(actor) + ".\n");
        break;
    case 2:
        write("The strong silver-grey male horse decides that "
            + "hugs from common people are not so bad after all. He "
            + "nickers and prances around you.\n");
        say("The strong silver-grey male horse decides that hugs from "
            + "common people are not so bad after all. He nickers and "
            + "prances around " + QTNAME(actor) + ".\n");
        break;
    default:
        break;
    }
}


public void
return_pet(object actor)
{
    if (!objectp(present(actor, ENV(TO))))
    return;

    switch (random(3))
    {
    case 0:
        write("The strong silver-grey male horse dances "
            + "away from you.\n");
        say("The strong silver-grey male horse dances away from "
            + QTNAME(actor) + ".\n");
        break;
    case 1:
        write("The strong silver-grey male horse rears up "
            + "on his hind legs threateningly. Apparently you did not "
            + "have his permission to pet him.\n");
        say("The strong silver-grey male horse rears up on his hind legs "
            + "threateningly. Apparently " + QTNAME(actor) + " did not "
            + "have his permission to pet him.\n");
        break;
    case 2:
        write("The strong silver-grey male horse decides that "
            + "being petted by commoners is not so terrible. He nuzzles "
            + "his velvet-soft nose against your hand.\n");
        say("The strong silver-grey male horse decides that being petted "
            + "by commoners is not so terrible. He nuzzles his velvet-soft "
            + "nose against " + QTNAME(actor) + "'s hand.\n");
        break;
    default:
        break;
    }
}



public void
emote_hook(string emote, object actor, string adverb = "")
{
    if (!objectp(actor) || !interactive(actor))
        return 0;

    switch (emote)
        {
        case "hug":
	           set_alarm(2.0, 0.0, &return_hug(actor));
	           break;
        case "pet":
            set_alarm(2.0, 0.0, &return_pet(actor));
            break;
    }
}


