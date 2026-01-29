/*
 * Shindig Lockpicker by Morrigan. 10/8/96
 * modified from Verminaard and Toede.
 *
 * 17.12.1998 Optimized slightly by Milan (use function VBFC).
 */

#include <std.h>
#include <ss_types.h>
#include <wa_types.h>
#include <filter_funs.h>
#include <macros.h>
#include "/d/Krynn/common/defs.h";
#include "../local.h";
#include CLOCKH
inherit M_FILE

/* Prototypes */
string shop();
string new_road();
string silly_solace();
string seekers();
string see_dragon();
string steal_something();

void
create_krynn_monster()
{
    string str;

    set_name("shindig");
    set_living_name("shindig");
    set_race_name("kender");
    set_title("Lockpicker");
    set_long("This is a kender, a race known on Krynn to be as much "+
      "a nuisance as a mosquito. Inflicted with wanderlust at "+
      "a young age, they've spread all over Krynn; and their "+
      "reputation for being `handlers' has spread with them. "+
      "This particular kender is small even by kender standards, "+
      "standing only around 90 centimeters and very thin. His "+
      "childish face has a few wrinkles, so you assume he's been "+
      "at his travels for at least some measure of time. At the "+
      "moment, he's regarding his surroundings, and you, you "+
      "notice with a bit of unease, with wide-eyed curiousity.\n");
    set_adj("tiny");
    add_adj("curious");
    set_gender(G_MALE);
    add_prop("_ranger_i_not_brawl", 1);
    add_prop(NPC_I_NO_LOOKS,1);
    set_introduce(1);

    set_stats(({70,120,100,60,60,100}));
    set_skill(SS_DEFENCE,        60);
    set_skill(SS_PARRY,          100);
    set_skill(SS_WEP_POLEARM,    90);
    set_skill(SS_BLIND_COMBAT,   50);
    set_skill(SS_AWARENESS,      70);

    set_alignment(300);
    set_knight_prestige(-200);

    set_default_answer("For some reason, the kender ignores you.\n");

    add_ask(" [about] 'story'", "say I have a wonderful story about " +
      "a magical ring! There was this angry wizard, he was quite mad " +
      "at me, oh, and hey, look at that! No! Over there! Oh, nevermind.",1);
    add_ask(" [about] [magic] [magical] 'ring'", "say Oh, "+
      "it was wonderful! I found it in that wizard's desk. He was "+
      "really mad when he saw me, saying I'd stolen the ring! Imagine "+
      "the nerve! He was lucky I picked it up, someone might have "+
      "stolen it otherwise.",1);

    set_act_time(1);
    add_act(steal_something);
    add_act(({silly_solace, steal_something}));
    add_act(({"say The other day, I got chased out of the store. And all I was "+
        "doing was cleaning it, honest. It was dirty, all that tarnish "+
        "on the shiny silver.", "frown", steal_something}));
    add_act("say I don't like all these goblins in Solace. They smell bad "+
      "and they have no sense of humour! That Fewmaster Toede is the "+
      "worst of them all! I asked him once if he was too stupid to be "+
      "Lotmaster, and that's why he was only master of a few and he "+
      "attacked me!");
    add_act("say Have you ever seen a wooly mammoth? Uncle Trapspringer has! "+
      "He told me. He said it was a great big hulking thing, with grey "+
      "fur and tusks.");
    add_act(seekers);
    add_act("emote lovingly strokes his copper red topknot.");
    add_act(steal_something);
    add_act("emote starts to search here for something to do.");
    add_act("emote solemnly announces: I'm bored.\n"+
      "You notice a few of the villagers hurrying away from the area, "+
      "with alarmed expressions on their faces.");
    add_act("emote looks around, wide-eyed with curiousity.");
    add_act(new_road);
    set_cact_time(3);
    add_cact("say You aren't very good at fighting. Maybe you should find a "+
      "new hobby, that you are more proficient at? I would suggest "+
      "a job washing dishes at the Inn of the Last Home, but from the "+
      "looks of you, that might be too challenging.");
    add_cact("say I saw an old lady somewhere around here. You should go talk "+
      "to her, maybe she'll give you a few fighting tips. You're "+
      "clumsier than a one-legged gully dwarf!");
    add_cact(see_dragon);
    add_cact("emote throws his hoopak harmlessly over your head.\n"+
      "Wondering what on Krynn he was doing, you are startled to see "+
      "him scramble between your legs, only to retrieve it and continue "+
      "fighting as if nothing happened.");
    add_cact("say And I thought draconians were ugly! You make them look like "+
      "a ravishing beauty! And what is that thing on your face? Is that "+
      "a nose or a beak?");
    add_cact("say Judging from your smell, you must be half goblin and half "+
      "gully dwarf. Well, maybe not... they have a certain measure of "+
      "intelligence.");
    add_cact("say I once met a hobgoblin who'd been charred by dragon breath. "+
      "I didn't think I'd ever see an uglier creature, but Uncle Trap"+
      "springer was right - You learn something new every day!");
    add_cact("swing hoopak");

    set_patrol_time(25);
    set_patrol_path(({"w", "say That mean ship captain won't let me on "+
        "his boat for some reason!", "e", "se", "ne", "e", "n", "emote "+
        "looks at the sky with great wonder.", 2, "say I love dragons! "+
        "Sometimes, he lets me ride on his back. Well, he used to any"+
        "way, until I accidently jumped off, now he says I'm too scat"+
        "terbrained to ride. The way I see it, if he would have been "+
        "flying right, I wouldn't have gotten bored and jumped, so it's "+
        "his fault, not mine.", "s",
        "ne", "u", "w", "sw", "se", "flirt sasha", 2, "say I think she "+
        "likes me.", 1, "smile dreamily sasha", "nw", "sw", "s", "se",
        "sw", "think", 1, "say I wonder why people think that they are "+
        "wise just from wearing that pin? I found one of them one day, it "+
        "was really shiny and pretty, but when I wore it I didn't feel any "+
        "wiser.", 3, "brighten", 1, "say I guess I'm already as wise as you "+
        "can get.", "ne", "se", "se", "say I used to go visit the pretty "+
        "green dragon all the time, but now he won't let me.", 1, "pout", 2,
        "say He said if I come up there one more time, he'll take all my "+
        "pouches away, and tie me to a tree and make me watch while he plays "+
        "with all my stuff!", 3, "smile thoughtfully", 2, "say Maybe I will "+
        "go up there two more times instead of just one, to trick him!",
        "se", "n", "n", "se", "e", "s", "say I don't see why people spend "+
        "all day long in here writing messages. If you want to talk to some"+
        "one, just go visit!", 1, "say It's lots more fun that way, too!", 2,
        "smile brightly", "n", "ne", "nw", 2, shop, 10, "n", "nw", "exa board", 2,
        "say What's "+
        "so interesting about this board anyway? People are always coming to "+
        "look at all this scribbling.", "nw", "ne", "e", "enter", "sit at bar",
        "emote looks around the bustling inn.", "say The next "+
        "round is on me! Put it on my tab!\n"+
        "Tika notices the kender and groans loudly.\n"+
        "Tika says in a hushed voice: Watch yer purses, gentlemen...", 2,
        "emote studies his purse interestedly.", 5, "say Well, my purse isn't "+
        "doing anything exciting...", "out", "e", "e", "n", "say For some "+
        "reason, Tarshir doesn't give me any quests. He said something about "+
        "losing all his friends if he sent me around searching for things, but "+
        "I think they'd be happy to have them found, don't you? I'm good at "+
        "finding things.\n"+
        "Tarshir mumbles under his breath: A bit too good, methinks.", "s", "s",
        "say Such a pretty door, why ruin it with a lock?", 1, "emote rummages "+
        "through his pouches and retrieves a slender piece of wire, with a "+
        "hooked end.", 2, "emote begins fidgeting with the door and within "+
        "seconds, the door swings open.", 1, "open door", "s", "s", "s", "s", "d",
        "n", "e", "se", "emote looks towards the graveyard with great wonder, "+
        "and squirms as if he's trying to decide whether or not to enter.", 3,
        "emote confides in you: It's not that I'm scared to go in there, it's "+
        "just that I feel bad for the caretaker.", 2, "say He said if I ever "+
        "slipped by him, he'd probably be haunted by the dead forever. I told "+
        "him I thought it would be fun, to see a spirit close up.. but he "+
        "seemed to think it would be a terrible thing.", "say I wonder what "+
        "they are made of?", 1, "say Spirits, I mean.", "nw", "w", "w", "w", "w",
        "w", "w", "w", "nw", "nw", "nw"}));
}

public void
arm_me()
{
    clone_object(OBJ + "shindig_vest")->move(TO);
    clone_object(OBJ + "shindig_leggings")->move(TO);
    clone_object(OBJ + "shindig_cape")->move(TO);
    clone_object("/d/Krynn/solamn/splains/obj/map")->move(TO);
    clone_object("/d/Krynn/solamn/splains/obj/kknife")->move(TO);
    clone_object("/d/Krynn/solamn/splains/obj/feather")->move(TO);
    clone_object("/d/Krynn/solamn/splains/obj/stone")->move(TO);
    clone_object(OBJ + "shindig_hoopak")->move(TO);
    clone_object(KRSCROLL + "ansamap_scroll")->move(TO);
    clone_object(KROBJECT + "scroll_casebb")->move(TO);
    command("say What is this doing outside of its case?");
    command("put scroll in case");
    command("close scrollcase");
    command("wear all");
    command("wield all");
}

string
shop()
{
    int *the_time = GET_TIME;

    if (the_time[HOUR] > 6 && the_time[HOUR] < 20)
    {
        command("e");
        set_alarm(2.0, 0.0,
      &command("say Oh wow, that sure is pretty!"));
        set_alarm(2.2, 0.0,
      &command("emote reaches out to pick up a shiny bauble.\n"+
          "The shopkeeper yells: You rascal! I told you never to come back "+
          "here, that's it. Come here you little thief!\n"));
        set_alarm(2.4, 0.0,
      &command("emote evades the shopkeeper's clumsy grasp, and darts out of "+
          "the store."));
        set_alarm(2.6, 0.0, &command("w"));
        set_alarm(2.8, 0.0,
      &command("shout Thief?! You're the thief, you great oaf, charging "+
          "those outrageous prices!"));
        set_alarm(3.0, 0.0,
      &command("shout I didn't want to shop in your store anyway!!"));
        set_alarm(4.0, 0.0,
      &command("emote mumbles, `I'm not a thief' in a hurt tone of voice."));
    return "";
    }
    command("time");
    command("pout");
    return "say I wish they would leave the shop open all night. Maybe I "+
      "will volunteer to watch the store at night, so it can stay open.";
}


string
new_road()
{
    set_alarm(1.0,0.0, &command("say Every new road requires a hoopak!"));
    set_alarm(2.0, 0.0, &command("emote lifts his hoopak above his "+
      "head and thrusts the pointed end into the ground."));
    set_alarm(2.5, 0.0, &command("emote proclaims: And there are no old "+
      "roads!"));
}

string
silly_solace()
{
    set_alarm(1.0, 0.0, &command("say These Solace people are silly, "+
      "they ruin their perfectly good doors by putting a lock on "+
      "them!"));
    set_alarm(1.5, 0.0, &command("boggle"));
}

string
seekers()
{
    set_alarm(1.0, 0.0, &command("say These Seeker are a strange sort. "+
      "Everyone knows the only way to find anything is to look, "+
      "so why do they all just sit around in the Inn of the Last "+
      "Home all the time? Occasionally they chase after me, maybe "+
      "they are just practicing seeking so they don't forget how. "+
      "It's great fun, but they aren't very good, they never catch "+
      "me."));
    set_alarm(2.0, 0.0, &command("giggle gleefully"));
}

string
see_dragon()
{
    set_alarm(1.0, 0.0, &command("emote suddenly stops fighting and "+
      "points upwards with a look of terror on his face."));
    set_alarm(2.0, 0.0, &command("shout It's a dragon!"));
    set_alarm(4.0, 0.0, &command("emote grins mischievously and taunts: "+
      "Made you look!"));
}

/* From the kender_base file, modified slightly. */
string
steal_something()
{
    int i;
    object *ob;
    object who, what;
    if (E(TO))
        ob = all_inventory(E(TO));
    if (!ob)
        return "";
    ob = FILTER_PLAYERS(ob);
    if (ob && sizeof(ob))
        who = ob[random(sizeof(ob))];
    else
        return "";
    ob = all_inventory(who);
    if (ob && sizeof(ob))
        what = ob[random(sizeof(ob))];
    else
        return "";
    if (what->query_no_show() || what->query_no_show_composite() ||
      what->query_prop(OBJ_M_NO_STEAL) || what->query_prop(OBJ_M_NO_DROP) ||
      what->query_prop(OBJ_M_NO_GIVE)||(who->query_wiz_level()))
        /* The check for wiz-level was added by Macker after
        a kender stole Grace's racenamer. *grin* */
        return "";
    if (what->query_value() < (who->query_average_stat() - 20) && random(2))
    {
        if (who->query_skill(SS_AWARENESS) > random(50) + 50)
            who->catch_msg("You catch " + QTNAME(TO) + " rifling through your "+
              "private belongings.\n");
        else
            what->move(TO);
    }
    else
    {
        switch(random(6))
        {
        case 0:
            command("say Where does this come from?");
            if (random(2))
                break;
        case 1:
            command("say Is that yours?");
            if (random(2))
                break;
        case 2:
            command("say I was keeping it safe for you.");
            if (random(2))
                break;
        case 3:
            command("say You must have lost it. What would have happened "+
              "if I hadn't found it?");
        case 4:
            command("say This looks just like yours, doesn't it?");
        case 5:
            command("say Maybe it fell into my pocket?");
        case 6:
            command("say You said you didn't want it anymore!");
        }
        tell_room(QCTNAME(TO) + " gives " + LANG_ASHORT(what) + " to " +
          QTNAME(who) + ".\n", who);
        who->catch_msg(QCTNAME(TO) + " gives you " + LANG_ASHORT(what) +
          ".\n");
    }
    return "";
}

int
special_attack(object enemy)
{
    int attacktype, i, penet;
    mixed* hitresult;
    string how, you;
    object me=TO;

    attacktype = random(3);
    if (attacktype == 1)
    {
        penet = query_stat(SS_DEX);
        penet += random(1*penet);
        hitresult = enemy->hit_me(penet, W_IMPALE, me, -1);
        how = QCTNAME(me) + " swings his hoopak around, but misses "+
        QTNAME(enemy)+".";
        you = QCTNAME(me) + " swings his hoopak around, but misses you.";
        if (hitresult[0] > 0)
        {
            how = QCTNAME(me) + " swings his hoopak, striking "+QTNAME(enemy)+
            "'s shin painfully.";
            you = QCTNAME(me) + " swings his hoopak, striking your shin "+
            "painfully.";
        }
        if (hitresult[0] > 10)
        {
            how = QCTNAME(me) + " lifts the hoopak up, then stabs downward, "+
            "driving the pointed end of his hoopak into "+
            QTNAME(enemy)+"'s foot.";
            you = QCTNAME(me) + " lifts his hoopak up, then stabs downward, "+
            "driving the pointed end of his hoopak into your "+
            "foot.";
        }
        if (hitresult[0] > 20)
        {
            how = QCTNAME(me) + " swings his hoopak upwards, catching "+
            QTNAME(enemy)+" below the chin.";
            you = QCTNAME(me) + " swings his hoopak upwards, catching "+
            "you below the chin.";
        }
        if (hitresult[0] > 40)
        {
            how = QCTNAME(me) + " slams his hoopak into "+QTNAME(enemy)+"'s "+
            "chest with amazing force.";
            you = QCTNAME(me) + " slams his hoopak into your chest, with "+
            "amazing force.";
        }
        if (hitresult[0] > 70)
        {
            how = QCTNAME(me) + " twirls his hoopak around, reversing his "+
            "grip, and impales "+QTNAME(enemy)+" with the point "+
            "of his hoopak.";
            you = QCTNAME(me) + " twirls his hoopak around, reversing his "+
            "grip, and impales you with the point of his hoopak.";
        }
        enemy->catch_msg(you + "\n");
        tell_watcher(how + "\n",enemy);

        if (enemy->query_hp() <= 0)
            write(QCTNAME(me) + " sets his feet firmly in the ground, and yanks "+
              "the hoopak free from "+QTNAME(enemy)+"'s chest, "+
              "muttering: I didn't want to kill the poor fellow, but "+
              "he just wouldn't leave me alone.\n");
        enemy->do_die(TO);

        return 1;
    }
    return 0;
}

public int
second_life(object killer)
{
    K_KILL_LOG("kills", "Shindig", killer);
    return 0;
}
