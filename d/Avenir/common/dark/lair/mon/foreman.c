// Shadow elf foreman for Avenir dark area
// Made by Boriska@Genesis Nov 1994
// Cloned at: /d/Avenir/common/dark/l2/n6.c
/*
 * Revisions:
 *	Cirion, Jul 1996: Made him a Shadow Union Warrior
 *	Cirion, May 1998: Had him inherit the room creator
 *	Lilith, Jun 1999: Updated appearance and emotes.
 *	Lilith, Nov 2003: Updated apperance again.
 *	Cotillion, Jan 2012: Added missing sword skill
 *	Lilith, Feb 2015: Updated appearance, asks, cchats, etc
 *	Lucius, Aug 2017: Fixes for union/defs.h changes.
 *      Arman, Feb 2020: Increased armour value and quickness to 
 *                       reduce incentive to farm.
 */
#pragma strict_types

inherit "/d/Avenir/union/npc/npc";
inherit "/d/Avenir/inherit/room_creator";

#include <money.h>
#include <macros.h>
#include <ss_types.h>
#include <stdproperties.h>

#include "/d/Avenir/union/defs.h"
#include "/d/Avenir/include/relation.h"

int alarm_id;

void
arm_me()
{
    object arm;

    arm = clone_object(TOKEN_OBJ);
	arm->move(TO);

    clone_object(UNION + "obj/slash")->move(TO);
    command("wield all");

    arm = clone_object(UNION+"obj/knife");
        arm->move(TO);
    arm = clone_object(UNION+"obj/knife");
      arm->move(TO);
    arm = clone_object(UNION+"obj/knife");
        arm->move(TO);
    arm = clone_object(UNION+"obj/knife");
        arm->move(TO);
    arm = clone_object(UNION+"obj/knife");
        arm->move(TO);
    arm = clone_object(UNION+"obj/knife");
        arm->move(TO);

    arm = clone_object(UNION+"obj/shirt");
        arm->move(TO);
    arm = clone_object(UNION+"obj/boots");
        arm->move(TO);
    arm = clone_object(UNION+"obj/cape");
    arm->move(TO);

    command("wear all");
    command("wield all");

    arm = clone_object(OCC_SHADOW);
    if (arm->shadow_me(TO, OCC_TYPE, OCC_STYLE, OCC_NAME) != 1)
    {
        write("Unable to be a Shadow Warrior.\n");
        "/secure/master"->do_debug("destroy", arm);
    }
}

string
my_long()
{
    string  str;

    str = "He is a shadowy, veiled "+ query_race_name() +", a member "+
		"of the Union of the Warriors of Shadow.\n";
    if (IS_SYBARITE(TP))
    {
        str += "His long dark hair is twisted in a single braid whose "+
             "end has been tied up where the braid begins, forming "+
             "the long, prominent loop of punishment that proclaims "+
             "to all his disgraced status.\n";
    }
    else
    {
        str += "His long dark hair is twisted in a single braid whose "+
             "end has been tied up where the braid begins, forming "+
             "a long, prominent loop of hair behind his head.\n";
    }

    str += "He has about him the air of one who is suffering the "+
         "punishment of supervising and protecting the work crew "+
         "with as much dignity as he can muster.\n"+
         "This foreman also seems to be looking for suggestions for expansion "+
         "of the area. You might try to ask him about 'building'.\n";

    return str;
}


void
create_monster()
{
    if (!IS_CLONE)
	return;

    reset_euid();

    set_name ("foreman");
    set_pname ("foremen");
    set_adj (({"shadowy", "veiled", "union", "shadow"}));
    set_long (my_long);
	set_race_name ("human");
    set_short("shadowy veiled human");
    add_prop(CONT_I_WEIGHT, 56000);
    add_prop(CONT_I_HEIGHT, 252);
    add_prop(LIVE_I_QUICKNESS, 200);
    set_all_hitloc_unarmed(45);

    set_appearance_offset(-40);

    set_stats(({ 80+random(60), 85+random(15), 80+random(50),
                 90+random(50), 80+random(50), 80+random(50) }));
    set_base_stat(SS_OCCUP, 85);

    set_skill(SS_LANGUAGE,      40);
    set_skill(SS_WEP_KNIFE,     50 + random(40));
    set_skill(SS_WEP_SWORD,     50 + random(40));
    set_skill(SS_PARRY,         55);
    set_skill(SS_ACROBAT,       60);
    set_skill(SS_AWARENESS,     71);
    set_skill(SS_DEFENCE,       50);
    set_skill(SS_LOC_SENSE,     80);
    set_skill(SS_SWAY,          50 + random(10));
    set_skill(SS_FLING,         60 + random(10));
    set_skill(SS_SLASH,         60 + random(10));

    set_alignment (0);

    set_act_time (10);
    add_act ("say Move, you lazy wretches!");
    add_act ("say There is another crew, moving towards us from the opposite side.");
    add_act ("say We have driven back the Ogres and the Dark Elves. "+
        "Victory is ours!");
    add_act ("say Trolls are the most lazy workers.");
    add_act ("say Oh, would that I had not put my pride before Service!");
    add_act ("say There is nothing quite like Unity.");
    add_act ("emote examines tunnel chart.");
    add_act ("uprepare");
    add_act ("dignity");
    add_act ("emote writes something in his notepad.");
    add_act ("emote examines the wall.");
    add_act ("emote checks his timetable and frowns.");
    add_act ("say The Gods provide for us as we Deserve.");
	add_act ("say We are the Many who are One.");
	add_act ("say I've but to complete this Duty and my penance is completed.");
    add_act ("murmur dignity and grace in hardship.");
    add_act ("murmur always seeking the Gods with reverence and dread.");
    add_act("brood");
    add_act("sway");

	set_cact_time(2);
	add_cact("say I'm a Shadow Warrior. I'll fight you to the death, and then "+
			  "my other Selves will avenge me.");
	add_cact("say Ambushing me will have consequences. The Union will find you.");
	add_cact("say Surely you've had a lapse in judgement!");
	add_cact("say Leave now, and I'll not report this to the Union.");
	add_cact("say May Plalgus smite thee, fool!");
	add_cact("say I will laugh at you from my grave on the Necronisi.");
	add_cact("say Mascarvin will come for me when I die, and I will return.");
    add_cact("angry");
    add_cact("clash");
    add_cact("cross");
    add_cact("curse");
    add_cact("pain");
    add_cact("wrath");

    seteuid(getuid());
    clone_object (DARK + "obj/f_chart")->move(this_object());
    MONEY_MAKE_SC(30)->move(this_object());

    arm_me();

    // path to which we will write out our generated rooms
    set_room_path ("/d/Avenir/common/dark/submissions/");
    // path to which we will log room creations
    set_room_log_file ("/d/Avenir/common/dark/submissions/sublog");

    // reset all variables
    reset_room_creator ();

    // allow the player to obtain help by asking
    set_room_creation_ask_help ();

    set_room_includes (({ "\"defs.h\"" }));
    set_min_room_items (2);
    set_min_room_cmd_items (2);

	add_ask(({ "[how] [do] [i] 'join' [the] [union]" }),
			"say Provide an application note to "
			+ "our Voice, tell us what you think need be known. "
			+ "A meeting will be arranged by our choice, "
			+ "and of your life will be no unturned stone.", 1);
	add_ask(({ "[about] [the] [shadow] 'union' [of] [warriors]"}),
		"say We are the Many who are One. We are charged with "+
		"protecting Sybarus from all threats, external and internal.", 1);
	add_ask(({"[about] [the] 'undead' / 'necronisi'"}),
		"say The  "+
		"Necronisi, or Isle of the Dead, is where the bodies of the dead, "+
		"both Faithful and Infidel, are disposed. The infidels become undead "+
		"and wait the chance to redeem themslves by answering the call "+
		"to defend Sybarus. They are terrible foes.", 1);
	add_ask(({"mascarvin"}),
		"say She is the Goddess of Death, the one who gathers us to her breast "+
		"and nurtures us until it is time for rebirth.", 1);
	add_ask(({"plalgus"}),
		"say He is the God of Judgement. Fear his hammer.", 1);
	add_ask(({"[about] [the] 'halls' 'of' 'shadow'"}),
			"say They are here, in the Deep. A more beautiful place "+
			"you will not find.", 1);
	add_ask(({"[about] [your] 'duty' / 'punishment' / 'penance'"}),
			"say It is impolite to ask about such things.", 1);
	set_default_answer("say I have little time for questions.", 1);
}

string race_sound()
{
   string *strs = ({ "says with a sybarite lilt" });

   return strs[random(sizeof(strs))];
}

int valid_help(object ob)
{
    if(interactive(ob) || !ob->id("troll") || ob->query_attack())
        return 0;

    return 1;
}

int special_attack(object enemy)
{
    object   *people;

    switch (random(7))
    {
		clone_object(UNION+"obj/knife")->move(TO);
        case 0: command("slash");
            return 0;
        case 1: command("fling");
            return 0;
        case 2: command("usrage");
            return 0;
        case 3: command("threaten enemy");
            return 0;
        case 4: command("slash");
            return 0;
        case 5: command("fling");
            return 0;
        default:
            command("fling");
    }

    people = filter(all_inventory(ENV(TO)), valid_help);

    if (!sizeof(people))
        return 0;

    call_other(people, "command", "kill " + enemy->query_real_name());
        return 0;
}

/*
 * check_meet enables the npc to greet players it
 * comes into contact with.
 */
void
check_meet(object tp)
{
    string  occ;
    int     i = random(10);
    alarm_id = 0;

    if (!present(tp, environment(TO)))
        return;

    occ = tp->query_guild_name_occ();
    if (occ == OCC_NAME)
    {
        if (i == 0)
            command("bow deep "+ tp->query_real_name());
        if (i < 6)
            command("respect "+ tp->query_real_name());
        if (i > 6)
            command("greet "+ tp->query_real_name());
        return;
    }
    if (IS_INFIDEL(tp))
    {
        if (i < 6)
        {
            command("curse");
            command("shout Infidel!");
            command("kill "+ tp->query_real_nme());
        }
        return;
    }
    if (IS_DANCER(tp))
    {
        if (i > 6)
            command("bow gallant to "+ tp->query_real_name());
            return;
    }
    else
    {
        if (i == 2)
            command("say to "+ tp->query_real_name() + " "+
               " This isn't a safe place for Outlanders.");
        if (i == 4)
            command("say to "+ tp->query_real_name() + " "+
               "If the imps and dark elves don't get you, "+
               "the ogres surely will.");
        if (i > 6)
            command("nod recog "+ tp->query_real_name());
            return;
    }
}

void
init_living()
{
    ::init_living();

    init_room_creator ();

    if (interactive(TP) && CAN_SEE(TO, TP))
    {
        if (alarm_id)
            return;
        alarm_id = set_alarm(2.0, 0.0, &check_meet(TP));
    }
}

