#include <ss_types.h>
#include <macros.h>
#include <stdproperties.h>
#include "/d/Krynn/common/defs.h"
#include "guild.h"
#include <wa_types.h>

inherit M_FILE

void
create_krynn_monster()
{
    if(!IS_CLONE)
	return;

    set_name("Grullurkhan");
    add_name("trainer");
    set_living_name("grullurkhan");
    set_title("the Dread Shaman of Mwarg");
    set_race_name("hobgoblin");
    set_adj("ancient");
    add_adj("deformed");
    set_gender("G_MALE");
    set_long("Before you hunches a hobgoblin shaman, wearing the totems of " +
        "the Throtyl hobgoblin tribes. No doubt he is quite knowledgeable " +
        "about them, and the 'Throtyl Raiders' that maraud through these " +
        "lands.\n");

    set_stats(({120,120,120,170,170,90}));
    set_hp(query_max_hp());
    set_skill(SS_UNARM_COMBAT, 100);
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_PARRY, 100);
    set_skill(SS_AWARENESS, 80);
    set_skill(SS_BLIND_COMBAT, 100);

    set_alignment(-900);
    set_knight_prestige(3);
    set_all_hitloc_unarmed(200);

    add_prop(OBJ_M_NO_ATTACK,"The hobgoblin shaman cunningly positions himself " +
       "between you and the great pit. You find yourself unable to attack him!\n");

    set_default_answer("The hobgoblin shaman cackles inanely.\n");

    set_act_time(75);
    add_act("emote yelps: Mwarg, da Great Serpent! I am yours to command!");
    add_act("emote rattles what look like human knuckle bones in his hands.");
    add_act("emote growls: The hobgoblin tribes will raid and pillage da plains " +
       "of Solamnia!");
    add_act("emote looks greedily into the great pit at the riches the " +
       "Throtyl Raiders have pillaged.");
    add_act("emote growls: Ogres and men of dark heart flock to join da " +
       "Raiders!");

    set_introduce(1);

}

void
arm_me()
{
    seteuid(getuid(TO));

}

void
return_intro(string who)
{
    who = L(who);
    if (P(who, E(TO)))
    {
	command("introduce myself");
    }
}

void
catch_question(string str)
{
    string question, answ;
    mixed minfo;

    string race_name = this_player()->query_race_name();
 
    if(!TP->check_seen(TO) || !CAN_SEE_IN_ROOM(TO))
    {
        set_alarm(rnd()*3.0 + 1.0, 0.0, &command("say Mwarg! Have " +
            "you come? I cannot see!"));
        return;
    }
 
    if(!parse_command(str, ({}), "[about] [the] %s", question))
    {
        set_alarm(rnd()*3.0 + 1.0, 0.0, &command("say to "+
            OB_NAME(TP)+" I do not understand your question."));
        return;
    }

    question = lower_case(question);
 
    if (question == "hobgoblin" || question == "hobgoblins" || question == "goblins")
    {
 
        command("scratch chin");
        command("say Yes! Grullurkhan knows much!");
        set_alarm(1.0,0.0,&command("cackle"));
        set_alarm(2.0,0.0,&command("say Gobbers and Hobgobbers... One lot " +
            "are littl' green snivlars, bootlickas, and whinas... Da odher " +
            "born killas, strong n powerful..."));
        set_alarm(3.0,0.0,&command("think"));
        set_alarm(4.0,0.0,&command("say Which one which? Hmmm... not so sure."));
        set_alarm(5.0,0.0,&command("shrug"));
        set_alarm(5.5,0.0,&command("say No important. Tha tribes of Throtyl " +
            "gather, war parties merge as tha <Throtyl Raiders>!"));

        return;
    }

    if (question == "throtyl raiders" || question == "raiders")
    {
        string race_name = this_player()->query_race_name();

        if(!IN_ARRAY(race_name, HOBGOB_ELIGIBLE_RACES))
        {
        command("emote belches loudly.");
        command("say Ah, da Throtyl Raiders! We are da scourge of da " +
            "human plains to da west, da beardy grunts to da north...");
        set_alarm(1.0,0.0,&command("say Da Tyrants of Throt burn, and burn, " +
            "and burn..."));
        set_alarm(2.0,0.0,&command("cackle"));
        set_alarm(4.0,0.0,&command("say Farmers flee da sound of our wardrums..."));
        set_alarm(5.0,0.0,&command("say And when da bloodlust takes us, " +
            "even da kniggets hide behind their walls from da horde " +
            "of Raiders!"));
            return;
        }
 
        command("emote belches loudly.");
        command("say Ah, da Throtyl Raiders! We are da scourge of da " +
            "human plains to da west, da beardy grunts to da north...");
        set_alarm(1.0,0.0,&command("say Da Tyrants of Throt burn, and burn, " +
            "and burn..."));
        set_alarm(2.0,0.0,&command("cackle"));
        set_alarm(4.0,0.0,&command("say Farmers flee da sound of our wardrums..."));
        set_alarm(5.0,0.0,&command("say And when da bloodlust takes us, " +
            "even da kniggets hide behind their walls from da horde " +
            "of Raiders!"));
        set_alarm(5.5,0.0,&command("say Me think you have come to <claim a " +
            "place> wit da Throtyl Raiders!"));
        set_alarm(6.0,0.0,&command("grin knowing"));

        return;
    }
 
    if (question == "claim a place")
    {
        if(!IN_ARRAY(race_name, HOBGOB_ELIGIBLE_RACES))
        {
            command("spit");
            command("say Smeg off tarkin " +race_name+ 
                "! 'fore I summon tha rage of Mwarg!");
            return;
        }
 
        command("emote leers at you.");
        command("say To join us, <claim my rightful place amongst the " +
            "throtyl raiders>.");
        set_alarm(1.0,0.0,&command("say But know, you must EARN any respect."));
        set_alarm(2.0,0.0,&command("emote sneers at you."));
        set_alarm(3.0,0.0,&command("say We respect strength. And da strong " +
           "bring in da best of der spoils, and get tha respect and fear of " +
           "da tribes."));
        set_alarm(3.5,0.0,&command("emote points at the great pit full of " +
            "pillaged loot."));
        set_alarm(4.0,0.0,&command("say And I will teach you ways of the strong! " +
           "Teach you good... tricks in battle. How to make " +
           "nasty bleeding wounds! How to fill the pit with bloody loot!"));
        set_alarm(4.5,0.0,&command("cackle"));
        set_alarm(5.5,0.0,&command("say If you want to know more about tha " +
           "Throtyl Raiders, <stare into the bonfire> of bones..."));
        set_alarm(6.5,0.0,&command("grin evil"));
        return;
    }

    if (question == "spoils" || question == "great pit" || question == "pit" ||
        question == "loot" || question == "pillaged loot" )
    { 
        command("say Dere are da strong dat sit in dere caves or hide in da " +
            "forest.");
        command("say Dey are owed no respect. Dey waste Mwarg's gift to them.");
        set_alarm(1.0,0.0,&command("say Those who are truly strong take!"));
        set_alarm(1.5,0.0,&command("emote gazes down into the great pit, admiring " +
            "the loot collected there."));
        set_alarm(2.0,0.0,&command("say And those dat want to lead the hordes of " +
            "Throtyl <contribute> loot of their pillage to the pit."));
        set_alarm(2.5,0.0,&command("say Platinum. Gold. Silver. The wealth of " +
            "our enemies..."));
        set_alarm(3.0,0.0,&command("say ...but steel coins! That is the coin " +
            "of true strength! Da coin of weapons and blood!"));
        set_alarm(3.0,0.0,&command("grin greed"));

        return;
    }

    if (question == "mwarg")
    { 
        command("say Mwarg? Da ancient serpent?");
        command("say One to fear... one to respect.");
        set_alarm(1.0,0.0,&command("say She breathes darkness. Endless " +
           "does she battle da bright one, Skyblade!"));
        set_alarm(1.5,0.0,&command("emote gazes up into the sky."));

        return;
    }

    if (question == "join" || question == "guild" || question == "joining" ||
        question == "help" || question == "join guild")
    {
        if(!IN_ARRAY(race_name, HOBGOB_ELIGIBLE_RACES))
        {
            if(race_name == "minotaur")
            {
                command("eyebrow scept");
                command("say " +C(LANG_ART(race_name))+ " " +race_name+ 
                    " join da Throtyl Raiders?");
                command("laugh mocking");
                set_alarm(1.0,0.0,&command("say Cows and their honour have "+ 
                    "no place with the Raiders!"));

                return;
            }

            command("eyebrow scept");
            command("say " +C(LANG_ART(race_name))+ " " +race_name+ 
                " join da Throtyl Raiders?");
            command("laugh mocking");
            set_alarm(1.0,0.0,&command("say Raiders are wolves. You " +race_name+ 
                " are da sheep."));

            return;
        }

        if (TP->query_alignment() > 100)
        {
            command("laugh mocking");
            set_alarm(0.5,0.0,&command("say Goodie two-shoes! Ya don't " +
                "have the black heart to be a Raider!"));

            return;
        }
 
        command("say You want to join with da hobgoblins and maraud " +
            "tha lands?");
        command("frown thought");
        command("nod .");
        set_alarm(0.5,0.0,&command("say If you want to know more about tha " +
           "Throtyl Raiders, <stare into the bonfire> of bones..."));
        set_alarm(1.0,0.0,&command("say ..and ask me then about da <Throtyl Raiders>."));

        return;
    }

    if (question == "quest" || question == "task")
    {
 
        command("emote rattles what look like human knuckle bones thoughtfully.");
        command("say I have no tasks or quests for you.");

        return;
    }

    if (question == "special" || question == "bleeding wounds" ||
        question == "bleeding wound" || question == "wound")
    {

        command("ponder"); 
        command("say I can train Throtyl Raiders how to deal nasty bleeding wounds.");
        set_alarm(0.5,0.0,&command("say Your enemies bleed out their life before you!"));
        set_alarm(1.0,0.0,&command("cackle"));
        set_alarm(1.5,0.0,&command("say Those with strength and cunning I find are " +
            "best able to deal the nastiest of wounds!"));
        set_alarm(2.0,0.0,&command("grin blood"));

        return;
    }

    if (question == "leave" || question == "quit" || question == "desert" || 
        question == "leave guild")
    {
 
        command("emote snorts.");
        command("say Hah! Weakling! You wish to <desert the throtyl raiders>?");
        command("say Leave then. But know all tha loot you have accumulated will " +
            "amount ta nothin' if ya return!");
        return;
    }
 
    set_alarm(2.0, 0.0, &command("say to "+OB_NAME(TP)+
        " You can find dat answer elsewhere."));
}
