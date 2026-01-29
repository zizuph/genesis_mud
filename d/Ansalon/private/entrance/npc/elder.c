/* Elder kender that gives out the kender quest */

#include <macros.h>
#include <ss_types.h>
#include "/d/Ansalon/common/defs.h"
#include "/d/Ansalon/guild/society/guild.h"
#include <math.h>

inherit "/std/act/action.c";
inherit AM_FILE

string *areas = ({ "just south of a beautiful city with a magical tower.", 
"near a city that REFUSED to let me in. They called me a thief! I got in anyway. You can't stop a kender!", 
"after I ran into a bunch of armoured men on horses who didn't want to get too close. It was very hot there. Good thing I found a solution to that problem!",
"in this place with snow all around. I thought I was going to catch pneumonia after I got my clothes all wet!", "on some boring plains near a bunch of grumpy hill dwarves.",
"near this town with a wonderful magic tunnel. It was a bit stinky, but I managed to not breathe too much through my nose.", 
"near some very interesting centaurs.", 
"in a ruined city with a dragon! There were lots of things that would be scary to anyone but a kender.",
"on the shore of a beautiful lake. I found the most interesting cave there!",
"by a bunch of gnomes.", 
"amidst a group of barbarians.", "by a city in the trees!",
"near a fortress with a lot of gully dwarves." });

string *prooms = ({ "/d/Krynn/solamn/vin_mount/room/road12.c",
"/d/Ansalon/kalaman/city/outside_wall.c",
"/d/Krynn/solamn/splains/room/under_bridge.c",
"/d/Krynn/icewall/castle/caverns/quest/cave.c",
"/d/Ansalon/estwilde/plains/trail1.c",
"/d/Krynn/tant/room/sewer1.c",
"/d/Ansalon/balifor/flotsam_forest/room/f8.c",
"/d/Krynn/xak/crypt/northcrypt4.c",
"/d/Krynn/darkenwd/road/shore2.c",
"/d/Krynn/gnome/boulder.c",
"/d/Krynn/que/shu/room/temple.c",
"/d/Krynn/solace/new_village/park2.c",
"/d/Krynn/pax/valley/forest9.c" });

int quest_in_progress = 0;

#define ODIR                  "/d/Ansalon/private/entrance/obj/"
#define KENDER_AM_QUESTING    "_kender_am_questing"
#define AREA_IDENT            94216066
#define AREA_RANGE            13

// Set this equal to anything other than 1 to open
int ken_mem_closed = 0;

public void
create_krynn_monster()
{
    if (!IS_CLONE)
        return;

    set_name("merldon");
    set_living_name("merldon");
    set_race_name("kender");
    set_title("Metwinger of Kendermore");
    set_long("This old kender's face is covered in wrinkles. Hidden " + 
        "amongst the wrinkles are two shining green eyes. They have " + 
        "a sparkle of mischief in them yet. His hair is tied up in a " + 
        "grey topknot, and his cheek braids mark him as having noble " + 
        "blood. This particular kender is one of Kendermore's many " + 
        "ex-mayors. His left leg is slightly crooked, and he often rubs " + 
        "it mumbling something under his breath.\n");
    set_adj("wise");
    add_adj("wrinkled");
    set_gender(G_MALE);
    set_introduce(1);

    remove_prop(NPC_M_NO_ACCEPT_GIVE);
    set_stats(({150,130,150,140,150,160}));
    set_skill(SS_DEFENCE, 100);
    set_skill(SS_AWARENESS, 100);
    set_skill(SS_2H_COMBAT, 100);
    set_skill(SS_WEP_POLEARM, 100);
    set_skill(SS_WEP_KNIFE, 100);
    set_alignment(350);
    set_knight_prestige(-40);
    set_default_answer("The old kender doesn't hear your words since " + 
        "he's mumbling something under his breath.\n");
    add_ask(({"help", "task", "quest"}), "emote sighs and rubs his leg.", 1);
    add_ask(({"join", "kender", "guild"}), "say Read the book!", 1);
    add_ask(({"leg", "left leg"}), "say I injured it in my travels. I " + 
        "don't mind it too much, but sometimes I wish I could travel " + 
        "back to some of my favourite places.", 1);
    add_ask(({"places", "favourite places", "favourite", "back", "travel",
        "travels"}),
        "say I saw some of the most wonderful things! Did I ever show " + 
        "you this neat mask that I found just lying around " + 
        "somewhere?", 1);
    add_ask("locket", "say It was a silver locket that I gave to him in " + 
        "friendship. It had a drawing of us on the inside.", 1);
    add_ask(({"gusslehan", "friend", "friendship"}), "say Gusslehan was " +
        "my best friend and cousin.", 1);
    add_ask(({"found", "mask", "neat mask"}),
        "say I think it used to belong to a magician. I was wearing it " + 
        "one time when I found this magical portal.", 1);
    add_ask("magician", "say I knew a magician one time. He was very " + 
        "powerful. For some reason, he didn't like it when I stopped by " + 
        "to visit him. Something about missing spellbooks and magical " + 
        "artifacts.", 1);
    add_ask(({"portal", "magical portal"}), "@@portal_loc");
    add_ask(({"books", "book", "spellbook", "spellbooks", "spells"}),
        "say He got very annoyed when I tried to look in his spellbooks. " + 
        "I never did manage to read any of those spells.", 1);
    add_ask(({"magical artifacts", "artifacts"}), "say He had a sparkly " + 
        "red mask. In fact, it looked a lot like this one that I found " + 
        "just lying on the ground somewhere. People really should be more " + 
        "careful with their things.", 1);
    add_ask("adventure", "emote stares briefly into space as if " + 
        "lost in happy memories.", 1);
}

string
portal_loc()
{
    string pname, area;
    int area_loc;
    object mag_mask, portal;

    pname = TP->query_real_name();
    area_loc = NAME_TO_RANDOM(pname, AREA_IDENT, AREA_RANGE);
    area = areas[area_loc];

    if (ken_mem_closed == 1)
    {
        TO->command("say I don't have any adventures for you to " +
            "go on...yet! Maybe if you came back later?");
        return "";
    }

    if (TP->query_race_name() != "kender")
    {
        TO->command("say I don't think you're up to it, not being " + 
            "a kender.");
        return "";
    }

    if (TP->test_bit("ansalon",3,0))
    {
        TO->command("say Thanks for your help! I can't think of " +
            "anything else for you to do right now. Maybe if you came " +
            "back later...");
        return "";
    }

    if (TP->query_prop(KENDER_AM_QUESTING))
    {
        TO->command("say Yes, I saw it " + area + " Now that was an " +
            "adventure! If only I had that locket to remind me of my " +
            "friend, Gusslehan and that wonderful adventure. " +
            "Did you find it yet?\n");
        return "";
    }

    setuid();
    seteuid(getuid());
    mag_mask = clone_object(ODIR + "mask");
    mag_mask->move(TP);
    if(quest_in_progress)
        TO->command("say Some other adventurer is working on this " +
            "for me right now, but you can try it anyways. Better for " +
            "me if more than one are trying to do it, but maybe not " +
            "better for you. Anyways...\n");

    TO->command("say Yes, I saw it " + area + " Now that was an " + 
        "adventure! I went with my good friend Gusslehan, but he " + 
        "wandered off somewhere. If only I had something to remind " + 
        "me of him and " + 
        "that fabulous adventure! He had this beautiful locket... Hey, " + 
        "why don't you try to find it for me! I'll even let you borrow " + 
        "this sparkly mask, but I'll be wanting it back!");
    TP->add_prop(KENDER_AM_QUESTING, 1);
    TP->catch_tell("Merldon hands you a red sparkly mask.\n");
    tell_room(environment(TP), "Merldon hands " + QTNAME(TP) + " a " + 
        "red sparkly mask.\n", TP);

    setuid();
    seteuid(getuid());

    if(file_size(prooms[area_loc]) != -1)
    {
        prooms[area_loc]->teleledningsanka();
        if(!present("_kender_quest_portal", find_object(prooms[area_loc])))
        {
            portal = clone_object(ODIR + "portal");
            portal->move(prooms[area_loc]);
            quest_in_progress = 1;
        }
    }
    else
        return "Portal failed to load. Please make a bug report.\n";

    return "";
}

void
give_it_back(object ob, object from)
{
    string what, who;
    what = L(ob->query_short());
    who = from->query_real_name();
    command("give " + what + " to " + who);
    command("say That's not what I want!");
}

void
reward_kender(object from)
{
    int xp_base = 1500;
    string who;
    who = from->query_real_name();
    if (from->test_bit("ansalon",3,0))
    {
        from->catch_msg("Why don't you go find a different adventure, " + 
            "instead of doing the same one over again?\n");
        return;
    }

    if (!from->query_prop("_kender_am_questing"))
    {
        from->catch_msg("Thank you for returning these to me...but " + 
            "I never asked for your help in the first place!\n");
        return;
    }

    from->set_bit(3,0);
    A_QUEST_LOG("quest", "Kender Entrance Quest", from, xp_base);
    from->add_prop("_kender_just_did_quest", 1);
    set_alarm(3.0,0.0,&command("emote announces that " + C(who) + " has " + 
        "completed the adventure required to join the guild!"));
    return;
}

void
accept_locket(object ob, object from)
{
    string who;
    who = from->query_real_name();
    command("say Gusslehan's locket! You found it!");
    set_alarm(1.5,0.0,&command("emote looks at the locket, obviously " + 
        "lost in old memories, then stuffs it in a pocket."));
    ob->remove_object();
    set_alarm(5.0,0.0,&command("thank " + who));
    set_alarm(7.0,0.0,&command("emote looks a bit sad when he hears " + 
        "that Gusslehan is dead, then brightens " + 
        "saying, 'I bet Gusslehan enjoyed his final adventure!'"));
    set_alarm(9.0,0.0,&command("whisper " + who + " If you found his " + 
        "hoopak, I'd love to see that too!"));
    from->add_prop("_kender_returned_locket", 1);
    if (!from->query_prop("_kender_returned_mask"))
        set_alarm(12.0,0.0,&command("say Oh! Do you still have my mask?"));
    else
        set_alarm(12.0,0.0,&reward_kender(from));
}

void
accept_hoopak(object ob, object from)
{
    string who, what;
    what = L(ob->query_short());
    who = from->query_real_name();
    if (from->query_prop("_kender_just_did_quest"))
    {
        ob->remove_object();
        clone_object("/d/Ansalon/private/entrance/obj/hoopak2")->move(TO);
        from->remove_prop("_kender_just_did_quest");
        set_alarm(2.0,0.0,&command("say Oh! Gusslehan's hoopak!"));
        set_alarm(3.5,0.0,&command("say I'll fix it for you now that " + 
            "you've returned this locket to me!"));
        set_alarm(4.5,0.0,&command("emote sets to work on the broken hoopak."));
        set_alarm(7.0,0.0,&command("give " + what + " to " + who));
        set_alarm(8.0,0.0,&command("say There you are! Take good care of it!"));
        return;
    }

    if (from->test_bit("ansalon",3,0))
    {
        set_alarm(2.0,0.0,&command("say Oh! Gusslehan's hoopak!"));
        set_alarm(3.5,0.0,&command("say Don't take advantage of a good " + 
            "thing!"));
        return;
    }

    else
    {
        set_alarm(2.0,0.0,&command("say Oh! Gusslehan's hoopak!"));
        set_alarm(3.5,0.0,&command("say I'll fix it for you right after " + 
            "you return my mask and find that locket for me."));
        set_alarm(4.5,0.0,&command("give " + what + " to " + who));
        return;
    }
}

void
accept_mask(object ob, object from)
{
    string who;
    who = from->query_real_name();
    set_alarm(1.8,0.0,&command("emote smiles as his mask is returned, " + 
        "and stuffs it in one of his pouches."));
    ob->remove_object();
    from->add_prop("_kender_returned_mask", 1);
    if (!from->query_prop("_kender_returned_locket"))
        set_alarm(3.0,0.0, &command("say Did you find Gusslehan's locket?"));
    else
        set_alarm(3.0,0.0,&reward_kender(from));
}

void
accept_skeleton(object ob, object from)
{
    string who;
    who = from->query_real_name();
    set_alarm(1.5,0.0,&command("emote gets a sad expression on his " + 
        "face as big tears well up in his eyes."));
    set_alarm(3.2,0.0,&command("say I will bury him in his favorite " + 
        "spot in the forest."));
    set_alarm(4.0,0.0,&command("emote seems lost in his memories."));
    ob->remove_object();
}

public void
enter_inv(object ob, object from)
{
    ::enter_inv(ob, from);
    if (ob->id("_kender_quest_mask_"))
    {
        set_alarm(0.1,0.0,&accept_mask(ob, from));
        return;
    }
    if (ob->id("_kender_quest_locket_"))
    {
        set_alarm(0.1,0.0,&accept_locket(ob, from));
        return;
    }
    if (ob->id("_quest_hoopak_"))
    {
        set_alarm(0.1,0.0,&accept_hoopak(ob, from));
        return;
    }   
    if (ob->id("_kender_quest_skeleton_"))
    {
        set_alarm(0.1,0.0,&accept_skeleton(ob, from));
        return;
    }
    set_alarm(1.0,0.0, &give_it_back(ob, from));
   
}

void
start_invite(string who)
{
    move_living("into the guild", VMASTER, 1,1);
    command("call vote " + who + "-invite");
    move_living("skipping away", KGROOM + "joinroom", 1, 1);
    VMASTER->add_requested(who);
}
