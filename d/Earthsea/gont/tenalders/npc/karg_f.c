/* These are emotes and reactions of the female karg priestesses. */
#include <macros.h>

public void
emote_hook(string emote, object enemy, string adverb = 0)
{
    object me = this_object();

    if(!interactive(enemy))
        return;

    if(emote == "smile")
    {
        me->command("slap " + enemy->query_real_name());
        me->command("say Wipe that smile from your face, weasel breath!");
        return;
    }

    if(emote == "grin")
    {
        me->command("say What are you grinning about, worm?");
        me->command("kick " + enemy->query_real_name());
        return;
    }

    if(emote == "smirk")
    {
        me->command("smirk " + enemy->query_real_name());
        me->command("say Be careful how wise you are, wise guy!");
        return;
    }

    if(emote == "laugh" || emote == "giggle")
    {
        me->command("say You won't be laughing in a minute!");
        me->command("say Come and fight me, coward!");
        return;
    }

    if(emote == "kiss" || emote == "french")
    {
        me->command("spit");
        me->command("say Disgusting!");
	me->command("kick " + enemy->query_real_name());
    }
}

public void
trash_talk(object enemy)
{
    int i = random(7), j = random(2);
    object me = this_object();
    string occ_name = enemy->query_guild_name_occ(),
        lay_name = enemy->query_guild_name_lay(),
        qtname = me->query_address(enemy),
        qctname, str;
    mixed *ptr = enemy->query_weapon(-1);
    object weapon;

    switch(i)
    {
        case 0:
            if(occ_name == "Order of the Dragon")
            {
                if(j == 0)
                {
		  me->command("say You Dragon Order folks _think_ " +
			      "you are so "+
			      "tough! But listen to this!");
                    me->command("shout HIIIIIIIIIIIIII-YAAAAAAAAAAA!!");
                    enemy->command("panic");
                } else {
                    if(present("cloak", me))
                    {
                        me->command("swirl cloak");
                        me->command("say How do you like my robe? Much "+
                            "finer than that shabby monk rag.");
                    }

                    me->command("smirk " + enemy->query_real_name());
                }
            }

            if(occ_name == "Solamnian Knights")
            {
                if(j == 0)
                {
                    me->command("say Hey knigget! Consider me this!");
                    me->command("wiggle");
                } else {
                    me->command("say Funny how knights are always playing with " +
                        "their swords!");
                    me->command("cackle");
                }
            }

            if(occ_name == "Angmar Army")
                me->command("say I will smash YOU, Angmarim!");

            if(occ_name == "Gladiator guild")
            {
                me->command("say This to you, Gladiator!");
                me->command("emote makes a gesture of thumbs down.");
            }

            if(occ_name == "Calian warrior's guild")
            {
                me->command("say I can't believe you Calians " +
                    "have to train to learn how to move your behinds!");
                me->command("laugh " + enemy->query_real_name());
            }

            if(occ_name == "Morgul Mages")
            {
                me->command("beckon " + enemy->query_real_name());
                me->command("say Magey, Come with me! To Atuan, to Atuan " +
                    "I will take you!!");
                me->command("cackle");
            }
        break;

        case 1:
            me->command("say Hmm... looks like a good day for a " +
                enemy->query_race_name() + " sacrifice!");
            me->command("grin " + enemy->query_real_name());
        break;

        case 2:
            str = " Hey, "+ qtname + ", are you afraid to " +
                "be beaten up by a woman?";

            if(enemy->query_gender() == G_MALE)
            {
                me->command("say" + str);
                me->command("cackle");
            } else {
                me->command("say Hey little girl! better go back and " +
                    "help your mother in the kitchen!");
            }
        break;

        case 3:
            if(enemy->query_gender() == G_MALE)
            {
                me->command("beckon " + enemy->query_real_name());
                me->command("say Little boy, why not come and join " +
                    "my guards?");
                me->command("point eunuch");
                me->command("grin " + enemy->query_real_name());
            } else {
                str = "Come join us, " + qtname + ". You will make a " +
                    "fine priestess for the Nameless Ones!";
                me->command("say " + str);
            }
        break;

        case 4:
            me->command("say Resistance is futile! We will dominate all " +
                "of Earthsea! Starting with you!!");
            me->command("point " + enemy->query_real_name());
        break;

        case 5:
            me->command("shout Guards! Prepare the sacrifice! We " +
                "have a live one, but not for long!");
            me->command("grin " + enemy->query_real_name());
        break;

        case 6:
            if(sizeof(ptr))
            {
                weapon = present(ptr[0], enemy);

                if(enemy->query_gender() == G_MALE)
                {
                    str = "man";
                } else if(enemy->query_gender() == G_FEMALE) {
                    str = "woman";
                } else {
                    str = "being";
                }

                if(objectp(weapon) && weapon->query_wielded())
                {
                    me->command("say Nice " + weapon->query_short() + ", " +
                        qtname + ", think you are _" + str + "_ enough to " +
                        "wield it??");
                }
            }

            me->command("smirk " + enemy->query_real_name());
        break;

        default:
            me->command("say I will feed your body raw to the Nameless " +
                "Ones!");
        break;
    }
}

public int
query_knight_prestige()
{
    return 20;
}

public void
intro_hook(object ob)
{
}
